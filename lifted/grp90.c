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

static void lift_412650(X86 *m);

/* armc_drawStatsPanel (0x412650), lifted by tools/lift.py */
static void lift_412650(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 412650: push ebp */
	m->ebp = m->esp;	/* 412651: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 412653: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412656: sub esp, 0x58 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 412659: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 41265e: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 412664: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 412665: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 412666: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 412667: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412668: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412669: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41266fu; native_call(m, 0x40e450u);	/* 41266a: call 0x40e450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41266f: add esp, 8 */
	m->ebp = m->eax;	/* 412672: mov ebp, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 412674: mov dword ptr [esp + 0x14], ebp */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 412678: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x412683u; native_call(m, M32(0x4a9224u));	/* 41267d: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 412683: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 412688: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41268a: and edx, 0x800001ff */
	if (!m->sf) goto L_41269a;	/* 412690: jns 0x41269a */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 412692: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 412693: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 412699: inc edx */
L_41269a:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41269a: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 41269b: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4126a1: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4126a2: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4126a8: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4126aa: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4126ad: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4126b6u; native_call(m, 0x4566c0u);	/* 4126b1: call 0x4566c0 */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 4126b6: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4126bc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4126c1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4126c6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4126cb: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4126d2u; native_call(m, m->ebx);	/* 4126d0: call ebx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4126d2: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4126d4: xor esi, esi */
L_4126d6:
	{ DWORD a_ = M32((DWORD)(0x4dbc6cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4126d6: cmp dword ptr [0x4dbc6c], edi */
	if (!m->zf) goto L_412702;	/* 4126dc: jne 0x412702 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4126de: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4126e3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4126e8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4126ed: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4126f4u; native_call(m, m->ebx);	/* 4126f2: call ebx */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 4126f4: mov eax, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4126f9: push 1 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x6cu);	/* 4126fb: lea edx, [esi + eax + 0x6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4126ff: push edx */
	goto L_412724;	/* 412700: jmp 0x412724 */
L_412702:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 412702: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412707: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41270c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412711: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x412718u; native_call(m, m->ebx);	/* 412716: call ebx */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 412718: mov eax, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41271d: push 1 */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x6cu);	/* 41271f: lea ecx, [esi + eax + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412723: push ecx */
L_412724:
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 412724: mov ecx, dword ptr [0x4dcc90] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x40u);	/* 41272a: lea eax, [esi + eax + 0x40] */
	m->edx = (DWORD)(m->ecx + 0xb0u);	/* 41272e: lea edx, [ecx + 0xb0] */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412734: add ecx, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412737: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412738: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412739: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41273fu; native_call(m, 0x4283e0u);	/* 41273a: call 0x4283e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41273f: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 412742: add esi, 0x30 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 412745: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x120u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412746: cmp esi, 0x120 */
	if (m->sf != m->of) goto L_4126d6;	/* 41274c: jl 0x4126d6 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41274e: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 412750: xor esi, esi */
L_412752:
	m->ecx = (DWORD)(m->edi + 0x3u);	/* 412752: lea ecx, [edi + 3] */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412755: cmp ebp, ecx */
	if (!m->zf) goto L_412760;	/* 412757: jne 0x412760 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 412759: push 0x3f4ccccd */
	goto L_412765;	/* 41275e: jmp 0x412765 */
L_412760:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 412760: push 0x3ecccccd */
L_412765:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412765: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41276a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41276f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x412776u; native_call(m, m->ebx);	/* 412774: call ebx */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 412776: mov eax, dword ptr [0x4dcc90] */
	m->ecx = M32((DWORD)(0x4dcc9cu));	/* 41277b: mov ecx, dword ptr [0x4dcc9c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 412781: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412783: push ecx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x70u);	/* 412784: lea edx, [esi + eax + 0x70] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412788: add ecx, -0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41278b: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x10u);	/* 41278c: lea eax, [esi + eax + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412790: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412791: push eax */
	m->esp -= 4; M32(m->esp) = 0x412797u; native_call(m, 0x4282f0u);	/* 412792: call 0x4282f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412797: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 41279a: add esi, 0x64 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 41279d: inc edi */
	{ DWORD a_ = m->esi, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41279e: cmp esi, 0xc8 */
	if (m->sf != m->of) goto L_412752;	/* 4127a4: jl 0x412752 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4127a6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4127ab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4127b0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4127b5: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4127bcu; native_call(m, m->ebx);	/* 4127ba: call ebx */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 4127bc: mov ecx, dword ptr [0x4dcc90] */
	m->eax = M32((DWORD)(0x4dcc9cu));	/* 4127c2: mov eax, dword ptr [0x4dcc9c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4127c7: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4127c9: push eax */
	m->edx = (DWORD)(m->ecx + 0x174u);	/* 4127ca: lea edx, [ecx + 0x174] */
	{ DWORD a_ = m->eax, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4127d0: add eax, -0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4127d3: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4127d4: add ecx, 0x114 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4127da: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4127db: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4127e1u; native_call(m, 0x4282f0u);	/* 4127dc: call 0x4282f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4127e1: add esp, 0x14 */
	{ DWORD a_ = m->ebp, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4127e4: cmp ebp, 0xe */
	if (!m->zf) goto L_4128fe;	/* 4127e7: jne 0x4128fe */
	m->eax = M32((DWORD)(0x4dcc9cu));	/* 4127ed: mov eax, dword ptr [0x4dcc9c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4127f2: push 1 */
	m->ecx = (DWORD)(m->eax + 0xfffffffcu);	/* 4127f4: lea ecx, [eax - 4] */
	{ DWORD a_ = m->eax, b_ = 0xffffffe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4127f7: add eax, -0x1c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4127fa: push ecx */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 4127fb: mov ecx, dword ptr [0x4dcc90] */
	m->edx = (DWORD)(m->ecx + 0x114u);	/* 412801: lea edx, [ecx + 0x114] */
	{ DWORD a_ = m->ecx, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412807: add ecx, 0xe4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41280d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41280e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41280f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x412815u; native_call(m, 0x4284d0u);	/* 412810: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412815: add esp, 0x14 */
L_412818:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412818: push 0 */
L_41281a:
	m->eax = M32((DWORD)(0x4dcc9cu));	/* 41281a: mov eax, dword ptr [0x4dcc9c] */
	m->ecx = (DWORD)(m->eax + 0xfffffffau);	/* 41281f: lea ecx, [eax - 6] */
	{ DWORD a_ = m->eax, b_ = 0xffffffe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412822: add eax, -0x1c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412825: push ecx */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 412826: mov ecx, dword ptr [0x4dcc90] */
	m->edx = (DWORD)(m->ecx + 0x1a4u);	/* 41282c: lea edx, [ecx + 0x1a4] */
	{ DWORD a_ = m->ecx, b_ = 0x174u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412832: add ecx, 0x174 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412838: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412839: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41283a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x412840u; native_call(m, 0x4285c0u);	/* 41283b: call 0x4285c0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412840: add esp, 0x14 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 412843: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412848: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41284d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412852: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x412859u; native_call(m, m->ebx);	/* 412857: call ebx */
	m->eax = M32((DWORD)(0x4dcc9cu));	/* 412859: mov eax, dword ptr [0x4dcc9c] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41285e: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 412864: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412866: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412867: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412868: add eax, -0x20 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41286b: add ecx, 0xffffff60 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412871: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412872: push ecx */
	m->esp -= 4; M32(m->esp) = 0x412878u; native_call(m, 0x4282f0u);	/* 412873: call 0x4282f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412878: add esp, 0x14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41287b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x412886u; native_call(m, M32(0x4a922cu));	/* 412880: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 412886: mov eax, dword ptr [0x4dcc98] */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 41288b: mov ecx, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412891: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412896: push 0x3f000000 */
	m->ebp = (DWORD)(m->eax + 0xffffff24u);	/* 41289b: lea ebp, [eax - 0xdc] */
	m->eax = M32((DWORD)(0x9dae74u));	/* 4128a1: mov eax, dword ptr [0x9dae74] */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4128a6: push 0x3e4ccccd */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4128ab: cmp eax, 1 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4128ae: push 0x3dcccccd */
	m->ebx = (DWORD)(m->ecx + 0x40u);	/* 4128b3: lea ebx, [ecx + 0x40] */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4128b6: push 0x9da480 */
	if (!m->zf) goto L_412939;	/* 4128bb: jne 0x412939 */
	m->esp -= 4; M32(m->esp) = 0x4128c2u; native_call(m, 0x41f0e0u);	/* 4128bd: call 0x41f0e0 */
	m->edx = (DWORD)(m->ebx + 0x154u);	/* 4128c2: lea edx, [ebx + 0x154] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4128c8: push 1 */
	m->eax = (DWORD)(m->ebp + 0xe0u);	/* 4128ca: lea eax, [ebp + 0xe0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4128d0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4128d1: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4128d2: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4128d3: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4128d9u; native_call(m, 0x427970u);	/* 4128d4: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4128d9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4128de: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4128e3: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4128e8: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4128ea: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4128f4u; native_call(m, 0x41f0e0u);	/* 4128ef: call 0x41f0e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4128f4: push 0 */
	m->ecx = (DWORD)(m->ebx + 0x150u);	/* 4128f6: lea ecx, [ebx + 0x150] */
	goto L_412978;	/* 4128fc: jmp 0x412978 */
L_4128fe:
	m->eax = M32((DWORD)(0x4dcc9cu));	/* 4128fe: mov eax, dword ptr [0x4dcc9c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412903: push 0 */
	m->ecx = (DWORD)(m->eax + 0xfffffffcu);	/* 412905: lea ecx, [eax - 4] */
	{ DWORD a_ = m->eax, b_ = 0xffffffe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412908: add eax, -0x1c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41290b: push ecx */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 41290c: mov ecx, dword ptr [0x4dcc90] */
	m->edx = (DWORD)(m->ecx + 0x114u);	/* 412912: lea edx, [ecx + 0x114] */
	{ DWORD a_ = m->ecx, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412918: add ecx, 0xe4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41291e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41291f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412920: push ecx */
	m->esp -= 4; M32(m->esp) = 0x412926u; native_call(m, 0x4284d0u);	/* 412921: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412926: add esp, 0x14 */
	{ DWORD a_ = m->ebp, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412929: cmp ebp, 0xf */
	if (!m->zf) goto L_412818;	/* 41292c: jne 0x412818 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 412932: push 1 */
	goto L_41281a;	/* 412934: jmp 0x41281a */
L_412939:
	m->esp -= 4; M32(m->esp) = 0x41293eu; native_call(m, 0x41f0e0u);	/* 412939: call 0x41f0e0 */
	m->edx = (DWORD)(m->ebx + 0xdcu);	/* 41293e: lea edx, [ebx + 0xdc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 412944: push 1 */
	m->eax = (DWORD)(m->ebp + 0xe0u);	/* 412946: lea eax, [ebp + 0xe0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41294c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41294d: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41294e: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41294f: push ebp */
	m->esp -= 4; M32(m->esp) = 0x412955u; native_call(m, 0x427970u);	/* 412950: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412955: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41295a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41295f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412964: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 412966: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x412970u; native_call(m, 0x41f0e0u);	/* 41296b: call 0x41f0e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412970: push 0 */
	m->ecx = (DWORD)(m->ebx + 0xd8u);	/* 412972: lea ecx, [ebx + 0xd8] */
L_412978:
	m->edx = (DWORD)(m->ebp + 0xdcu);	/* 412978: lea edx, [ebp + 0xdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41297e: push ecx */
	m->eax = (DWORD)(m->ebx + 0x4u);	/* 41297f: lea eax, [ebx + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412982: push edx */
	m->ecx = (DWORD)(m->ebp + 0x4u);	/* 412983: lea ecx, [ebp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412986: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412987: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41298du; native_call(m, 0x427970u);	/* 412988: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41298d: add esp, 0x50 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 412990: xor esi, esi */
L_412992:
	{ DWORD a_ = M32((DWORD)(0x4dbc6cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412992: cmp dword ptr [0x4dbc6c], esi */
	if (!m->zf) goto L_4129b7;	/* 412998: jne 0x4129b7 */
	m->edx = M32((DWORD)(0x4dbc64u));	/* 41299a: mov edx, dword ptr [0x4dbc64] */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 4129a0: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 4129a5: mov ecx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4129ab: push edx */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 4129ac: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4129b2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4129b3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4129b4: push edx */
	goto L_4129d1;	/* 4129b5: jmp 0x4129d1 */
L_4129b7:
	m->eax = M32((DWORD)(0x4dc1dcu));	/* 4129b7: mov eax, dword ptr [0x4dc1dc] */
	m->ecx = M32((DWORD)(0x4dc1d8u));	/* 4129bc: mov ecx, dword ptr [0x4dc1d8] */
	m->edx = M32((DWORD)(0x4dc1d4u));	/* 4129c2: mov edx, dword ptr [0x4dc1d4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4129c8: push eax */
	m->eax = M32((DWORD)(0x4dc1d0u));	/* 4129c9: mov eax, dword ptr [0x4dc1d0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4129ce: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4129cf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4129d0: push eax */
L_4129d1:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4129d1: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4129dbu; native_call(m, 0x41f0e0u);	/* 4129d6: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4129db: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4129de: cmp esi, 5 */
	if (!m->zf) goto L_412a0f;	/* 4129e1: jne 0x412a0f */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 4129e3: mov eax, dword ptr [0x4dcc90] */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 4129e8: mov edx, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x756d24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4129ee: push 0x756d24 */
	{ DWORD a_ = m->edx, b_ = 0x13du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4129f3: add edx, 0x13d */
	m->ecx = (DWORD)(m->eax + 0xb0u);	/* 4129f9: lea ecx, [eax + 0xb0] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4129ff: add eax, 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412a02: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412a03: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412a04: push eax */
	m->esp -= 4; M32(m->esp) = 0x412a0au; native_call(m, 0x4029d0u);	/* 412a05: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412a0a: add esp, 0x10 */
	goto L_412a3d;	/* 412a0d: jmp 0x412a3d */
L_412a0f:
	m->edx = M32((DWORD)(0x4dcc94u));	/* 412a0f: mov edx, dword ptr [0x4dcc94] */
	m->eax = m->esi;	/* 412a15: mov eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 412a17: shl eax, 7 */
	m->ecx = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 412a1a: lea ecx, [esi + esi*2] */
	{ DWORD a_ = m->eax, b_ = 0x756aa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412a1d: add eax, 0x756aa4 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412a22: shl ecx, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412a25: push eax */
	m->eax = (DWORD)(m->ecx + m->edx*1 + 0x44u);	/* 412a26: lea eax, [ecx + edx + 0x44] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 412a2a: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->ecx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412a30: add ecx, 0x18 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412a33: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412a34: push ecx */
	m->esp -= 4; M32(m->esp) = 0x412a3au; native_call(m, 0x402620u);	/* 412a35: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412a3a: add esp, 0xc */
L_412a3d:
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 412a3d: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412a3e: cmp esi, 6 */
	if (m->sf != m->of) goto L_412992;	/* 412a41: jl 0x412992 */
	m->eax = M32((DWORD)(0x4dbc68u));	/* 412a47: mov eax, dword ptr [0x4dbc68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 412a4c: test eax, eax */
	if (m->zf) goto L_412b1c;	/* 412a4e: je 0x412b1c */
	m->edx = M32((DWORD)(0x4dbc64u));	/* 412a54: mov edx, dword ptr [0x4dbc64] */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 412a5a: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 412a5f: mov ecx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412a65: push edx */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 412a66: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412a6c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412a6d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412a6e: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412a6f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412a79u; native_call(m, 0x41f0e0u);	/* 412a74: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 412a79: mov eax, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 412a7e: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->eax, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412a84: add eax, 0x54 */
	{ DWORD v_ = 0x4dceb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 412a87: push 0x4dceb8 */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412a8c: add ecx, 0x28 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412a8f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412a90: push ecx */
	m->esp -= 4; M32(m->esp) = 0x412a96u; native_call(m, 0x402620u);	/* 412a91: call 0x402620 */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 412a96: mov edx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 412a9c: mov eax, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->edx, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 412aa1: add edx, 0x84 */
	{ DWORD v_ = 0x4dbc08u; m->esp -= 4; M32(m->esp) = v_; }	/* 412aa7: push 0x4dbc08 */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412aac: add eax, 0x28 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412aaf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412ab0: push eax */
	m->esp -= 4; M32(m->esp) = 0x412ab6u; native_call(m, 0x402620u);	/* 412ab1: call 0x402620 */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 412ab6: mov ecx, dword ptr [0x4dcc94] */
	m->edx = M32((DWORD)(0x4dcc90u));	/* 412abc: mov edx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->ecx, b_ = 0xb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412ac2: add ecx, 0xb4 */
	{ DWORD v_ = 0x4dc250u; m->esp -= 4; M32(m->esp) = v_; }	/* 412ac8: push 0x4dc250 */
	{ DWORD a_ = m->edx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 412acd: add edx, 0x28 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412ad0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412ad1: push edx */
	m->esp -= 4; M32(m->esp) = 0x412ad7u; native_call(m, 0x402620u);	/* 412ad2: call 0x402620 */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 412ad7: mov eax, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 412adc: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->eax, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412ae2: add eax, 0xe4 */
	{ DWORD v_ = 0x4dc1e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 412ae7: push 0x4dc1e8 */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412aec: add ecx, 0x28 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412aef: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412af0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x412af6u; native_call(m, 0x402620u);	/* 412af1: call 0x402620 */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 412af6: mov edx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 412afc: mov eax, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412b01: add esp, 0x44 */
	{ DWORD a_ = m->edx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 412b04: add edx, 0x114 */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412b0a: add eax, 0x28 */
	{ DWORD v_ = 0x4dce40u; m->esp -= 4; M32(m->esp) = v_; }	/* 412b0d: push 0x4dce40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412b12: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412b13: push eax */
	m->esp -= 4; M32(m->esp) = 0x412b19u; native_call(m, 0x402620u);	/* 412b14: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412b19: add esp, 0xc */
L_412b1c:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 412b1c: xor edi, edi */
	m->esi = 0x7517a4u;	/* 412b1e: mov esi, 0x7517a4 */
	M32((DWORD)(m->esp + 0x18u)) = m->edi;	/* 412b23: mov dword ptr [esp + 0x18], edi */
L_412b27:
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 412b27: mov ecx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 412b2b: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412b2f: add ecx, 3 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412b32: cmp eax, ecx */
	if (!m->zf) goto L_412b53;	/* 412b34: jne 0x412b53 */
	m->edx = M32((DWORD)(0x4dbc64u));	/* 412b36: mov edx, dword ptr [0x4dbc64] */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 412b3c: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 412b41: mov ecx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412b47: push edx */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 412b48: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412b4e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412b4f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412b50: push edx */
	goto L_412b6d;	/* 412b51: jmp 0x412b6d */
L_412b53:
	m->eax = M32((DWORD)(0x4dc1dcu));	/* 412b53: mov eax, dword ptr [0x4dc1dc] */
	m->ecx = M32((DWORD)(0x4dc1d8u));	/* 412b58: mov ecx, dword ptr [0x4dc1d8] */
	m->edx = M32((DWORD)(0x4dc1d4u));	/* 412b5e: mov edx, dword ptr [0x4dc1d4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412b64: push eax */
	m->eax = M32((DWORD)(0x4dc1d0u));	/* 412b65: mov eax, dword ptr [0x4dc1d0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412b6a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412b6b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412b6c: push eax */
L_412b6d:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412b6d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412b77u; native_call(m, 0x41f0e0u);	/* 412b72: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 412b77: mov eax, dword ptr [0x4dcc90] */
	m->edx = M32((DWORD)(0x4dcc9cu));	/* 412b7c: mov edx, dword ptr [0x4dcc9c] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412b82: add esp, 0x14 */
	{ DWORD a_ = m->edx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 412b85: add edx, -0x18 */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x70u);	/* 412b88: lea ecx, [edi + eax + 0x70] */
	m->eax = (DWORD)(m->edi + m->eax*1 + 0x10u);	/* 412b8c: lea eax, [edi + eax + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 412b90: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412b91: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412b92: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412b93: push eax */
	m->esp -= 4; M32(m->esp) = 0x412b99u; native_call(m, 0x4029d0u);	/* 412b94: call 0x4029d0 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 412b99: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412b9d: add esp, 0x10 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 412ba0: add esi, 0x80 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 412ba6: inc eax */
	{ DWORD a_ = m->edi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412ba7: add edi, 0x64 */
	{ DWORD a_ = m->esi, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412baa: cmp esi, 0x7518a4 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 412bb0: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_412b27;	/* 412bb4: jl 0x412b27 */
	m->ecx = M32((DWORD)(0x4dbc64u));	/* 412bba: mov ecx, dword ptr [0x4dbc64] */
	m->edx = M32((DWORD)(0x4dbc60u));	/* 412bc0: mov edx, dword ptr [0x4dbc60] */
	m->eax = M32((DWORD)(0x4dbc5cu));	/* 412bc6: mov eax, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412bcb: push ecx */
	m->ecx = M32((DWORD)(0x4dbc58u));	/* 412bcc: mov ecx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412bd2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412bd3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412bd4: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412bd5: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412bdfu; native_call(m, 0x41f0e0u);	/* 412bda: call 0x41f0e0 */
	m->ecx = 0xcu;	/* 412bdf: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412be4: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 412be6: lea edi, [esp + 0x48] */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 412bea: lea edx, [esp + 0x48] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 412bee: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 412bf0: stosw word ptr es:[edi], ax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412bf2: or ecx, 0xffffffff */
	m->edi = 0x756da4u;	/* 412bf5: mov edi, 0x756da4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412bfa: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412bfc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 412bfe: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412c00: sub edi, ecx */
	m->eax = m->ecx;	/* 412c02: mov eax, ecx */
	m->esi = m->edi;	/* 412c04: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412c06: shr ecx, 2 */
	m->edi = m->edx;	/* 412c09: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 412c0b: lea edx, [esp + 0x48] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 412c0f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 412c11: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412c13: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412c15: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 412c18: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b035cu;	/* 412c1a: mov edi, 0x4b035c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412c1f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412c22: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 412c24: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412c26: sub edi, ecx */
	m->esi = m->edi;	/* 412c28: mov esi, edi */
	m->edi = m->edx;	/* 412c2a: mov edi, edx */
	m->edx = m->ecx;	/* 412c2c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412c2e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412c31: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 412c33: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 412c35: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412c36: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 412c39: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 412c3b: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 412c3d: lea edx, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412c41: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 412c44: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32((DWORD)(0x4dceacu));	/* 412c46: mov edi, dword ptr [0x4dceac] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412c4c: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 412c4f: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x751924u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412c52: add edi, 0x751924 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412c58: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 412c5a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412c5c: sub edi, ecx */
	m->esi = m->edi;	/* 412c5e: mov esi, edi */
	m->edi = m->edx;	/* 412c60: mov edi, edx */
	m->edx = m->ecx;	/* 412c62: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412c64: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412c67: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 412c69: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 412c6b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412c6c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 412c6f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 412c71: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 412c73: lea eax, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412c77: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412c7a: push eax */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 412c7b: mov eax, dword ptr [0x4dcc98] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 412c80: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dcc9cu));	/* 412c82: mov ecx, dword ptr [0x4dcc9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412c88: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 412c89: add ecx, -0x18 */
	{ DWORD a_ = m->eax, b_ = 0xffffff60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412c8c: add eax, 0xffffff60 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412c91: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412c92: push eax */
	m->esp -= 4; M32(m->esp) = 0x412c98u; native_call(m, 0x4029d0u);	/* 412c93: call 0x4029d0 */
	m->edx = M32((DWORD)(0x4dbc64u));	/* 412c98: mov edx, dword ptr [0x4dbc64] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412c9e: push edx */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 412c9f: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 412ca4: mov ecx, dword ptr [0x4dbc5c] */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 412caa: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412cb0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412cb1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412cb2: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412cb3: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412cbdu; native_call(m, 0x41f0e0u);	/* 412cb8: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 412cbd: mov eax, dword ptr [0x4dcc90] */
	m->edx = M32((DWORD)(0x4dcc9cu));	/* 412cc2: mov edx, dword ptr [0x4dcc9c] */
	{ DWORD v_ = 0x7568a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 412cc8: push 0x7568a4 */
	{ DWORD a_ = m->edx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 412ccd: add edx, -0x18 */
	m->ecx = (DWORD)(m->eax + 0x174u);	/* 412cd0: lea ecx, [eax + 0x174] */
	{ DWORD a_ = m->eax, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 412cd6: add eax, 0x114 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412cdb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412cdc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412cdd: push eax */
	m->esp -= 4; M32(m->esp) = 0x412ce3u; native_call(m, 0x4029d0u);	/* 412cde: call 0x4029d0 */
	m->eax = M32((DWORD)(0x9dae74u));	/* 412ce3: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412ce8: add esp, 0x48 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412ceb: cmp eax, 1 */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 412cee: mov eax, dword ptr [0x4dbc6c] */
	if (!m->zf) goto L_4160d9;	/* 412cf3: jne 0x4160d9 */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412cf9: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_418fbb;	/* 412cfc: ja 0x418fbb */
	switch (m->eax) { case 0: goto L_412d09; case 1: goto L_413842; case 2: goto L_413ca2; case 3: goto L_4143eb; case 4: goto L_414c35; case 5: goto L_415902; default: abort(); }	/* 412d02: jmp dword ptr [eax*4 + 0x418fc4] */
L_412d09:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d09: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d0e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d13: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d18: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d1d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412d27u; native_call(m, 0x41f0e0u);	/* 412d22: call 0x41f0e0 */
	m->ecx = (DWORD)(m->ebx + 0x8u);	/* 412d27: lea ecx, [ebx + 8] */
	m->eax = (DWORD)(m->ebp + 0xau);	/* 412d2a: lea eax, [ebp + 0xa] */
	{ DWORD v_ = 0x760aa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d2d: push 0x760aa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412d32: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412d33: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 412d34: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x412d3du; native_call(m, 0x402620u);	/* 412d38: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcef8u)));	/* 412d3d: fld dword ptr [0x4dcef8] */
	m->ecx = 0xcu;	/* 412d43: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412d48: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 412d4a: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 412d4e: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412d52: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 412d55: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 412d57: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d5b: push 0x4b0354 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412d60: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 412d61: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x412d68u; native_call(m, 0x49e9ddu);	/* 412d63: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d68: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d6d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d72: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d77: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412d79: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412d83u; native_call(m, 0x41f0e0u);	/* 412d7e: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 412d83: lea edx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x17u);	/* 412d87: lea eax, [ebx + 0x17] */
	m->ecx = (DWORD)(m->ebp + 0x1au);	/* 412d8a: lea ecx, [ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412d8d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412d8e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412d8f: push ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 412d90: mov dword ptr [esp + 0x48], ecx */
	m->esp -= 4; M32(m->esp) = 0x412d99u; native_call(m, 0x402620u);	/* 412d94: call 0x402620 */
	m->eax = M32((DWORD)(0x9f1818u));	/* 412d99: mov eax, dword ptr [0x9f1818] */
	m->edi = (DWORD)(m->esp + 0x64u);	/* 412d9e: lea edi, [esp + 0x64] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412da2: add esp, 0x30 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 412da5: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 412da8: lea edx, [eax + ecx*2] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412dab: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412dae: xor eax, eax */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9084u)));	/* 412db0: fild dword ptr [edx*4 + 0x9f9084] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412db7: repne scasb al, byte ptr es:[edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 412db9: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dcef8u));	/* 412dbf: fmul dword ptr [0x4dcef8] */
	m->ecx = ~m->ecx;	/* 412dc5: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 412dc7: dec ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dbc78u));	/* 412dc8: fadd dword ptr [0x4dbc78] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412dce: shl ecx, 3 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 412dd1: mov dword ptr [esp + 0x14], ecx */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 412dd5: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 412ddb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 412ddd: test ah, 0x40 */
	if (!m->zf) goto L_412eb0;	/* 412de0: jne 0x412eb0 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 412de6: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 412dec: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 412dee: test ah, 1 */
	if (m->zf) goto L_412e05;	/* 412df1: je 0x412e05 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412df3: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 412df6: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 412dfa: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b034cu; m->esp -= 4; M32(m->esp) = v_; }	/* 412dfd: push 0x4b034c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412e02: push eax */
	goto L_412e15;	/* 412e03: jmp 0x412e15 */
L_412e05:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412e05: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 412e08: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 412e0c: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0344u; m->esp -= 4; M32(m->esp) = v_; }	/* 412e0f: push 0x4b0344 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412e14: push ecx */
L_412e15:
	m->esp -= 4; M32(m->esp) = 0x412e1au; native_call(m, 0x49e9ddu);	/* 412e15: call 0x49e9dd */
	m->edi = 0x7655a4u;	/* 412e1a: mov edi, 0x7655a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412e1f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412e22: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412e24: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412e27: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 412e29: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412e2b: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 412e2d: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 412e31: mov esi, edi */
	m->edi = m->edx;	/* 412e33: mov edi, edx */
	m->edx = m->ecx;	/* 412e35: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412e37: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412e3a: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 412e3c: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 412e3e: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412e3f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 412e42: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 412e44: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 412e46: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412e4a: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412e4d: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 412e52: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 412e54: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412e59: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412e5c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 412e5e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412e60: sub edi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412e62: push eax */
	m->esi = m->edi;	/* 412e63: mov esi, edi */
	m->edi = m->edx;	/* 412e65: mov edi, edx */
	m->edx = m->ecx;	/* 412e67: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412e69: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412e6c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 412e6e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 412e70: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412e71: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 412e74: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 412e76: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412e78: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412e7d: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412e80: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 412e85: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412e87: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412e91u; native_call(m, 0x41f0e0u);	/* 412e8c: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 412e91: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 412e95: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412e99: push eax */
	m->eax = (DWORD)(m->ebx + 0x17u);	/* 412e9a: lea eax, [ebx + 0x17] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 412e9d: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412ea1: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412ea2: push edx */
	m->esp -= 4; M32(m->esp) = 0x412ea8u; native_call(m, 0x402620u);	/* 412ea3: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412ea8: add esp, 0x20 */
	goto L_412f4c;	/* 412eab: jmp 0x412f4c */
L_412eb0:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412eb0: or ecx, 0xffffffff */
	m->edi = 0x4b033cu;	/* 412eb3: mov edi, 0x4b033c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412eb8: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 412eba: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412ebe: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 412ec0: fstp st(0) */
	m->ecx = ~m->ecx;	/* 412ec2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412ec4: sub edi, ecx */
	m->eax = m->ecx;	/* 412ec6: mov eax, ecx */
	m->esi = m->edi;	/* 412ec8: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412eca: shr ecx, 2 */
	m->edi = m->edx;	/* 412ecd: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 412ecf: lea edx, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 412ed3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 412ed5: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412ed7: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412ed9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 412edc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x7655a4u;	/* 412ede: mov edi, 0x7655a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412ee3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412ee6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 412ee8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412eea: sub edi, ecx */
	m->esi = m->edi;	/* 412eec: mov esi, edi */
	m->edi = m->edx;	/* 412eee: mov edi, edx */
	m->edx = m->ecx;	/* 412ef0: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412ef2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412ef5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 412ef7: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 412ef9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412efa: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 412efd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 412eff: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 412f01: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412f05: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 412f08: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 412f0a: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412f0f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412f12: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 412f14: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 412f16: sub edi, ecx */
	m->esi = m->edi;	/* 412f18: mov esi, edi */
	m->edi = m->edx;	/* 412f1a: mov edi, edx */
	m->edx = m->ecx;	/* 412f1c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412f1e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412f21: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 412f23: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 412f25: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412f26: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 412f29: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 412f2b: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 412f2d: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412f31: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412f34: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 412f35: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 412f37: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->ebx + 0x17u);	/* 412f3b: lea eax, [ebx + 0x17] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412f3e: push eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 412f3f: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412f43: push edx */
	m->esp -= 4; M32(m->esp) = 0x412f49u; native_call(m, 0x402620u);	/* 412f44: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412f49: add esp, 0xc */
L_412f4c:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412f4c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412f51: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412f56: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412f5b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412f60: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412f6au; native_call(m, 0x41f0e0u);	/* 412f65: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 412f6a: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x28u);	/* 412f6e: lea eax, [ebx + 0x28] */
	{ DWORD v_ = 0x760b24u; m->esp -= 4; M32(m->esp) = v_; }	/* 412f71: push 0x760b24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412f76: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412f77: push ecx */
	m->esp -= 4; M32(m->esp) = 0x412f7du; native_call(m, 0x402620u);	/* 412f78: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcefcu)));	/* 412f7d: fld dword ptr [0x4dcefc] */
	m->ecx = 0xcu;	/* 412f83: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412f88: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 412f8a: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 412f8e: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412f92: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 412f95: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 412f97: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 412f9b: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412fa0: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 412fa1: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x412fa8u; native_call(m, 0x49e9ddu);	/* 412fa3: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412fa8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412fad: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412fb2: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412fb7: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412fb9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412fc3u; native_call(m, 0x41f0e0u);	/* 412fbe: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 412fc3: mov edx, dword ptr [esp + 0x3c] */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 412fc7: lea ecx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 412fcb: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412fce: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412fcf: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412fd0: push edx */
	m->esp -= 4; M32(m->esp) = 0x412fd6u; native_call(m, 0x402620u);	/* 412fd1: call 0x402620 */
	m->eax = M32((DWORD)(0x9f1818u));	/* 412fd6: mov eax, dword ptr [0x9f1818] */
	m->edi = (DWORD)(m->esp + 0x64u);	/* 412fdb: lea edi, [esp + 0x64] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412fdf: add esp, 0x30 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 412fe2: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 412fe5: lea edx, [eax + ecx*2] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412fe8: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412feb: xor eax, eax */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9084u)));	/* 412fed: fild dword ptr [edx*4 + 0x9f9084] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 412ff4: repne scasb al, byte ptr es:[edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 412ff6: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dcefcu));	/* 412ffc: fmul dword ptr [0x4dcefc] */
	m->ecx = ~m->ecx;	/* 413002: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 413004: dec ecx */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 413005: fcom dword ptr [0x4a93e8] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41300b: shl ecx, 3 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 41300e: mov dword ptr [esp + 0x14], ecx */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413012: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 413014: test ah, 0x40 */
	if (!m->zf) goto L_4130e7;	/* 413017: jne 0x4130e7 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41301d: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413023: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 413025: test ah, 1 */
	if (m->zf) goto L_41303c;	/* 413028: je 0x41303c */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41302a: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41302d: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 413031: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b032cu; m->esp -= 4; M32(m->esp) = v_; }	/* 413034: push 0x4b032c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413039: push eax */
	goto L_41304c;	/* 41303a: jmp 0x41304c */
L_41303c:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41303c: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 41303f: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 413043: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0324u; m->esp -= 4; M32(m->esp) = v_; }	/* 413046: push 0x4b0324 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41304b: push ecx */
L_41304c:
	m->esp -= 4; M32(m->esp) = 0x413051u; native_call(m, 0x49e9ddu);	/* 41304c: call 0x49e9dd */
	m->edi = 0x765624u;	/* 413051: mov edi, 0x765624 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413056: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413059: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41305b: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41305e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413060: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413062: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413064: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 413068: mov esi, edi */
	m->edi = m->edx;	/* 41306a: mov edi, edx */
	m->edx = m->ecx;	/* 41306c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41306e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413071: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413073: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413075: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413076: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413079: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41307b: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41307d: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413081: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413084: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413089: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 41308b: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413090: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413093: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413095: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413097: sub edi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413099: push eax */
	m->esi = m->edi;	/* 41309a: mov esi, edi */
	m->edi = m->edx;	/* 41309c: mov edi, edx */
	m->edx = m->ecx;	/* 41309e: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4130a0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4130a3: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4130a5: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4130a7: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4130a8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4130ab: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4130ad: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4130af: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4130b4: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4130b7: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4130bc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4130be: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4130c8u; native_call(m, 0x41f0e0u);	/* 4130c3: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4130c8: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4130cc: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4130d0: push eax */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 4130d1: lea eax, [ebx + 0x37] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 4130d4: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4130d8: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4130d9: push edx */
	m->esp -= 4; M32(m->esp) = 0x4130dfu; native_call(m, 0x402620u);	/* 4130da: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4130df: add esp, 0x20 */
	goto L_413183;	/* 4130e2: jmp 0x413183 */
L_4130e7:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4130e7: or ecx, 0xffffffff */
	m->edi = 0x4b033cu;	/* 4130ea: mov edi, 0x4b033c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4130ef: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4130f1: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4130f5: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4130f7: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4130f9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4130fb: sub edi, ecx */
	m->eax = m->ecx;	/* 4130fd: mov eax, ecx */
	m->esi = m->edi;	/* 4130ff: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413101: shr ecx, 2 */
	m->edi = m->edx;	/* 413104: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413106: lea edx, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41310a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41310c: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41310e: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413110: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413113: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x765624u;	/* 413115: mov edi, 0x765624 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41311a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41311d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41311f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413121: sub edi, ecx */
	m->esi = m->edi;	/* 413123: mov esi, edi */
	m->edi = m->edx;	/* 413125: mov edi, edx */
	m->edx = m->ecx;	/* 413127: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413129: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41312c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41312e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413130: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413131: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413134: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413136: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413138: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41313c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41313f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 413141: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413146: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413149: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41314b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41314d: sub edi, ecx */
	m->esi = m->edi;	/* 41314f: mov esi, edi */
	m->edi = m->edx;	/* 413151: mov edi, edx */
	m->edx = m->ecx;	/* 413153: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413155: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413158: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41315a: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41315c: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41315d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413160: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413162: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 413164: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413168: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41316b: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41316c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 41316e: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 413172: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413175: push eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 413176: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41317a: push edx */
	m->esp -= 4; M32(m->esp) = 0x413180u; native_call(m, 0x402620u);	/* 41317b: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413180: add esp, 0xc */
L_413183:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413183: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413188: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41318d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413192: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413197: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4131a1u; native_call(m, 0x41f0e0u);	/* 41319c: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4131a1: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 4131a5: lea eax, [ebx + 0x48] */
	{ DWORD v_ = 0x760ba4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4131a8: push 0x760ba4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4131ad: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4131ae: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4131b4u; native_call(m, 0x402620u);	/* 4131af: call 0x402620 */
	m->ecx = 0xcu;	/* 4131b4: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4131b9: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 4131bb: lea edi, [esp + 0x54] */
	m->edx = M32((DWORD)(0x4dcf00u));	/* 4131bf: mov edx, dword ptr [0x4dcf00] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4131c5: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4131c7: stosw word ptr es:[edi], ax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4131c9: push edx */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 4131ca: lea eax, [esp + 0x58] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 4131ce: push 0x4b0320 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4131d3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4131d9u; native_call(m, 0x49e9ddu);	/* 4131d4: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4131d9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4131de: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4131e3: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4131e8: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4131ea: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4131f4u; native_call(m, 0x41f0e0u);	/* 4131ef: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 4131f4: mov edx, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4131f8: add esp, 0x40 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 4131fb: lea ecx, [esp + 0x34] */
	m->esi = (DWORD)(m->ebx + 0x57u);	/* 4131ff: lea esi, [ebx + 0x57] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413202: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 413203: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413204: push edx */
	m->esp -= 4; M32(m->esp) = 0x41320au; native_call(m, 0x402620u);	/* 413205: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dceb4u)));	/* 41320a: fld dword ptr [0x4dceb4] */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 413210: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413214: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413217: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413219: add esp, 0xc */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41321c: fcom dword ptr [0x4a93e8] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413222: repne scasb al, byte ptr es:[edi] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413224: fnstsw ax */
	m->ecx = ~m->ecx;	/* 413226: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 413228: dec ecx */
	m->edi = m->ecx;	/* 413229: mov edi, ecx */
	{ DWORD a_ = m->edi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 41322b: shl edi, 3 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41322e: test ah, 0x40 */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 413231: mov dword ptr [esp + 0x14], edi */
	if (!m->zf) goto L_41329e;	/* 413235: jne 0x41329e */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 413237: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41323d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41323f: test ah, 1 */
	if (m->zf) goto L_413256;	/* 413242: je 0x413256 */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413244: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413249: push eax */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 41324a: lea eax, [esp + 0x38] */
	{ DWORD v_ = 0x4b0318u; m->esp -= 4; M32(m->esp) = v_; }	/* 41324e: push 0x4b0318 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413253: push eax */
	goto L_413266;	/* 413254: jmp 0x413266 */
L_413256:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413256: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41325b: push eax */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 41325c: lea ecx, [esp + 0x38] */
	{ DWORD v_ = 0x4b030cu; m->esp -= 4; M32(m->esp) = v_; }	/* 413260: push 0x4b030c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413265: push ecx */
L_413266:
	m->esp -= 4; M32(m->esp) = 0x41326bu; native_call(m, 0x49e9ddu);	/* 413266: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41326b: add esp, 0xc */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41326e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413273: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413275: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41327a: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41327f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413289u; native_call(m, 0x41f0e0u);	/* 413284: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 413289: lea edx, [esp + 0x48] */
	m->eax = (DWORD)(m->edi + m->ebp*1 + 0x1au);	/* 41328d: lea eax, [edi + ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413291: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 413292: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413293: push eax */
	m->esp -= 4; M32(m->esp) = 0x413299u; native_call(m, 0x402620u);	/* 413294: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413299: add esp, 0x20 */
	goto L_4132e0;	/* 41329c: jmp 0x4132e0 */
L_41329e:
	m->edi = 0x4b0304u;	/* 41329e: mov edi, 0x4b0304 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4132a3: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4132a6: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4132a8: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4132ac: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4132ae: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4132b0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4132b2: sub edi, ecx */
	m->eax = m->ecx;	/* 4132b4: mov eax, ecx */
	m->esi = m->edi;	/* 4132b6: mov esi, edi */
	m->edi = m->edx;	/* 4132b8: mov edi, edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4132ba: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4132be: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4132c1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4132c3: mov ecx, eax */
	m->eax = (DWORD)(m->ebx + 0x57u);	/* 4132c5: lea eax, [ebx + 0x57] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4132c8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4132cb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 4132cd: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4132d1: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4132d2: push eax */
	m->eax = (DWORD)(m->edx + m->ebp*1 + 0x1au);	/* 4132d3: lea eax, [edx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4132d7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4132ddu; native_call(m, 0x402620u);	/* 4132d8: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4132dd: add esp, 0xc */
L_4132e0:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4132e0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4132e5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4132ea: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4132ef: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4132f4: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4132feu; native_call(m, 0x41f0e0u);	/* 4132f9: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4132fe: mov edx, dword ptr [esp + 0x24] */
	m->ecx = (DWORD)(m->ebx + 0x68u);	/* 413302: lea ecx, [ebx + 0x68] */
	{ DWORD v_ = 0x760c24u; m->esp -= 4; M32(m->esp) = v_; }	/* 413305: push 0x760c24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41330a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41330b: push edx */
	m->esp -= 4; M32(m->esp) = 0x413311u; native_call(m, 0x402620u);	/* 41330c: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93f4u)));	/* 413311: fld dword ptr [0x4a93f4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcf04u));	/* 413317: fdiv dword ptr [0x4dcf04] */
	m->ecx = 0xcu;	/* 41331d: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413322: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 413324: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413328: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41332b: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41332d: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41332f: lea eax, [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 413333: fmul dword ptr [0x4a93f4] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0);	/* 413339: fst dword ptr [esp + 0x1c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41333d: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 413340: push 0x4b0334 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413345: push eax */
	m->esp -= 4; M32(m->esp) = 0x41334bu; native_call(m, 0x49e9ddu);	/* 413346: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41334b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413350: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413355: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41335a: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41335c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413366u; native_call(m, 0x41f0e0u);	/* 413361: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 413366: mov edx, dword ptr [esp + 0x3c] */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 41336a: lea ecx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x77u);	/* 41336e: lea eax, [ebx + 0x77] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413371: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413372: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413373: push edx */
	m->esp -= 4; M32(m->esp) = 0x413379u; native_call(m, 0x402620u);	/* 413374: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc898u)));	/* 413379: fld dword ptr [0x4dc898] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 41337f: fmul dword ptr [esp + 0x44] */
	m->edi = (DWORD)(m->esp + 0x64u);	/* 413383: lea edi, [esp + 0x64] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413387: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41338a: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41338c: add esp, 0x30 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41338f: fcom dword ptr [0x4a93e8] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413395: repne scasb al, byte ptr es:[edi] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413397: fnstsw ax */
	m->ecx = ~m->ecx;	/* 413399: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41339b: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41339c: shl ecx, 3 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41339f: test ah, 0x40 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 4133a2: mov dword ptr [esp + 0x14], ecx */
	if (!m->zf) goto L_413476;	/* 4133a6: jne 0x413476 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4133ac: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4133b2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4133b4: test ah, 1 */
	if (m->zf) goto L_4133cb;	/* 4133b7: je 0x4133cb */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4133b9: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4133bc: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4133c0: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b032cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4133c3: push 0x4b032c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4133c8: push eax */
	goto L_4133db;	/* 4133c9: jmp 0x4133db */
L_4133cb:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4133cb: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 4133ce: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4133d2: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0324u; m->esp -= 4; M32(m->esp) = v_; }	/* 4133d5: push 0x4b0324 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4133da: push ecx */
L_4133db:
	m->esp -= 4; M32(m->esp) = 0x4133e0u; native_call(m, 0x49e9ddu);	/* 4133db: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 4133e0: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4133e5: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4133e8: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4133ea: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4133ed: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4133ef: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4133f1: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4133f3: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4133f7: mov esi, edi */
	m->edi = m->edx;	/* 4133f9: mov edi, edx */
	m->edx = m->ecx;	/* 4133fb: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4133fd: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413400: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413402: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413404: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413405: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413408: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41340a: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41340c: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413410: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413413: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413418: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 41341a: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41341f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413422: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413424: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413426: sub edi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413428: push eax */
	m->esi = m->edi;	/* 413429: mov esi, edi */
	m->edi = m->edx;	/* 41342b: mov edi, edx */
	m->edx = m->ecx;	/* 41342d: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41342f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413432: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413434: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413436: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413437: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41343a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41343c: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41343e: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413443: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413446: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41344b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41344d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413457u; native_call(m, 0x41f0e0u);	/* 413452: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 413457: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 41345b: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41345f: push eax */
	m->eax = (DWORD)(m->ebx + 0x77u);	/* 413460: lea eax, [ebx + 0x77] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 413463: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413467: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413468: push edx */
	m->esp -= 4; M32(m->esp) = 0x41346eu; native_call(m, 0x402620u);	/* 413469: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41346e: add esp, 0x20 */
	goto L_413512;	/* 413471: jmp 0x413512 */
L_413476:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413476: or ecx, 0xffffffff */
	m->edi = 0x4b033cu;	/* 413479: mov edi, 0x4b033c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41347e: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413480: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413484: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 413486: fstp st(0) */
	m->ecx = ~m->ecx;	/* 413488: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41348a: sub edi, ecx */
	m->eax = m->ecx;	/* 41348c: mov eax, ecx */
	m->esi = m->edi;	/* 41348e: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413490: shr ecx, 2 */
	m->edi = m->edx;	/* 413493: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413495: lea edx, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413499: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41349b: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41349d: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41349f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4134a2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x7656a4u;	/* 4134a4: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4134a9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4134ac: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4134ae: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4134b0: sub edi, ecx */
	m->esi = m->edi;	/* 4134b2: mov esi, edi */
	m->edi = m->edx;	/* 4134b4: mov edi, edx */
	m->edx = m->ecx;	/* 4134b6: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4134b8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4134bb: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4134bd: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4134bf: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4134c0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4134c3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4134c5: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4134c7: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4134cb: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4134ce: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4134d0: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4134d5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4134d8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4134da: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4134dc: sub edi, ecx */
	m->esi = m->edi;	/* 4134de: mov esi, edi */
	m->edi = m->edx;	/* 4134e0: mov edi, edx */
	m->edx = m->ecx;	/* 4134e2: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4134e4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4134e7: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4134e9: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4134eb: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4134ec: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4134ef: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4134f1: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 4134f3: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4134f7: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4134fa: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4134fb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4134fd: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->ebx + 0x77u);	/* 413501: lea eax, [ebx + 0x77] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413504: push eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 413505: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413509: push edx */
	m->esp -= 4; M32(m->esp) = 0x41350fu; native_call(m, 0x402620u);	/* 41350a: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41350f: add esp, 0xc */
L_413512:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413512: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413517: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41351c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413521: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413526: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413530u; native_call(m, 0x41f0e0u);	/* 41352b: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 413530: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x88u);	/* 413534: lea eax, [ebx + 0x88] */
	{ DWORD v_ = 0x760ca4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41353a: push 0x760ca4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41353f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413540: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413546u; native_call(m, 0x402620u);	/* 413541: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcf08u)));	/* 413546: fld dword ptr [0x4dcf08] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 41354c: fmul dword ptr [0x4a9480] */
	m->ecx = 0xcu;	/* 413552: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413557: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 413559: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41355d: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413560: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 413562: fstp qword ptr [esp] */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 413565: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 413569: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41356e: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41356f: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x413576u; native_call(m, 0x49e9ddu);	/* 413571: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413576: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41357b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413580: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413585: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413587: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413591u; native_call(m, 0x41f0e0u);	/* 41358c: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 413591: mov edx, dword ptr [esp + 0x3c] */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 413595: lea ecx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x97u);	/* 413599: lea eax, [ebx + 0x97] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41359f: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4135a0: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4135a1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4135a7u; native_call(m, 0x402620u);	/* 4135a2: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc88cu)));	/* 4135a7: fld dword ptr [0x4dc88c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dcf08u));	/* 4135ad: fmul dword ptr [0x4dcf08] */
	m->edi = (DWORD)(m->esp + 0x64u);	/* 4135b3: lea edi, [esp + 0x64] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4135b7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4135ba: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4135bc: add esp, 0x30 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 4135bf: fmul dword ptr [0x4a9480] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4135c5: repne scasb al, byte ptr es:[edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4135c7: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4135cd: fnstsw ax */
	m->ecx = ~m->ecx;	/* 4135cf: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4135d1: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4135d2: shl ecx, 3 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4135d5: test ah, 0x40 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 4135d8: mov dword ptr [esp + 0x14], ecx */
	if (!m->zf) goto L_4136af;	/* 4135dc: jne 0x4136af */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4135e2: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4135e8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4135ea: test ah, 1 */
	if (m->zf) goto L_413601;	/* 4135ed: je 0x413601 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4135ef: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4135f2: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4135f6: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b032cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4135f9: push 0x4b032c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4135fe: push eax */
	goto L_413611;	/* 4135ff: jmp 0x413611 */
L_413601:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413601: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 413604: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 413608: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0324u; m->esp -= 4; M32(m->esp) = v_; }	/* 41360b: push 0x4b0324 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413610: push ecx */
L_413611:
	m->esp -= 4; M32(m->esp) = 0x413616u; native_call(m, 0x49e9ddu);	/* 413611: call 0x49e9dd */
	m->edi = 0x765aa4u;	/* 413616: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41361b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41361e: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413620: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413623: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413625: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413627: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413629: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 41362d: mov esi, edi */
	m->edi = m->edx;	/* 41362f: mov edi, edx */
	m->edx = m->ecx;	/* 413631: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413633: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413636: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413638: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41363a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41363b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41363e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413640: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413642: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413646: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413649: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41364e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 413650: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413655: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413658: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41365a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41365c: sub edi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41365e: push eax */
	m->esi = m->edi;	/* 41365f: mov esi, edi */
	m->edi = m->edx;	/* 413661: mov edi, edx */
	m->edx = m->ecx;	/* 413663: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413665: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413668: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41366a: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41366c: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41366d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413670: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413672: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413674: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413679: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41367c: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413681: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413683: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41368du; native_call(m, 0x41f0e0u);	/* 413688: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 41368d: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 413691: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413695: push eax */
	m->eax = (DWORD)(m->ebx + 0x97u);	/* 413696: lea eax, [ebx + 0x97] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 41369c: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4136a0: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4136a1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4136a7u; native_call(m, 0x402620u);	/* 4136a2: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4136a7: add esp, 0x20 */
	goto L_41374e;	/* 4136aa: jmp 0x41374e */
L_4136af:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4136af: or ecx, 0xffffffff */
	m->edi = 0x4b033cu;	/* 4136b2: mov edi, 0x4b033c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4136b7: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4136b9: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4136bd: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4136bf: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4136c1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4136c3: sub edi, ecx */
	m->eax = m->ecx;	/* 4136c5: mov eax, ecx */
	m->esi = m->edi;	/* 4136c7: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4136c9: shr ecx, 2 */
	m->edi = m->edx;	/* 4136cc: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4136ce: lea edx, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4136d2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4136d4: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4136d6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4136d8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4136db: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x765aa4u;	/* 4136dd: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4136e2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4136e5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4136e7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4136e9: sub edi, ecx */
	m->esi = m->edi;	/* 4136eb: mov esi, edi */
	m->edi = m->edx;	/* 4136ed: mov edi, edx */
	m->edx = m->ecx;	/* 4136ef: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4136f1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4136f4: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4136f6: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4136f8: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4136f9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4136fc: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4136fe: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413700: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413704: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413707: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 413709: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41370e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413711: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413713: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413715: sub edi, ecx */
	m->esi = m->edi;	/* 413717: mov esi, edi */
	m->edi = m->edx;	/* 413719: mov edi, edx */
	m->edx = m->ecx;	/* 41371b: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41371d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413720: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413722: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413724: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413725: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413728: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41372a: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 41372c: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413730: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413733: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413734: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 413736: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->ebx + 0x97u);	/* 41373a: lea eax, [ebx + 0x97] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413740: push eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 413741: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413745: push edx */
	m->esp -= 4; M32(m->esp) = 0x41374bu; native_call(m, 0x402620u);	/* 413746: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41374b: add esp, 0xc */
L_41374e:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41374e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413753: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413758: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41375d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413762: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41376cu; native_call(m, 0x41f0e0u);	/* 413767: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 41376c: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0xa8u);	/* 413770: lea eax, [ebx + 0xa8] */
	{ DWORD v_ = 0x760d24u; m->esp -= 4; M32(m->esp) = v_; }	/* 413776: push 0x760d24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41377b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41377c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413782u; native_call(m, 0x402620u);	/* 41377d: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcf0cu)));	/* 413782: fld dword ptr [0x4dcf0c] */
	m->ecx = 0xcu;	/* 413788: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41378d: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 41378f: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 413793: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413797: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41379a: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41379c: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4137a0: push 0x4b02fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4137a5: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4137a6: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x4137adu; native_call(m, 0x49e9ddu);	/* 4137a8: call 0x49e9dd */
	m->edi = 0x7657a4u;	/* 4137ad: mov edi, 0x7657a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4137b2: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4137b5: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 4137b7: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4137bb: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4137bd: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4137bf: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4137c1: push 0x3f800000 */
	m->esi = m->edi;	/* 4137c6: mov esi, edi */
	m->ebp = m->ecx;	/* 4137c8: mov ebp, ecx */
	m->edi = m->edx;	/* 4137ca: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4137cc: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4137cf: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 4137d1: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4137d3: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4137d4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4137d7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 4137d9: mov ecx, ebp */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 4137db: lea edx, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4137df: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4137e2: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4137e7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4137e9: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4137ee: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4137f1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4137f3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4137f5: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4137f7: push 0x3f800000 */
	m->esi = m->edi;	/* 4137fc: mov esi, edi */
	m->ebp = m->ecx;	/* 4137fe: mov ebp, ecx */
	m->edi = m->edx;	/* 413800: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413802: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413805: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 413807: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413809: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41380a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41380d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 41380f: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413811: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413812: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413815: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41381a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x413821u; native_call(m, 0x41f0e0u);	/* 41381c: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 413821: mov ecx, dword ptr [esp + 0x3c] */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 413825: lea eax, [esp + 0x58] */
	{ DWORD a_ = m->ebx, b_ = 0xb7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 413829: add ebx, 0xb7 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41382f: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 413830: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413831: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413837u; native_call(m, 0x402620u);	/* 413832: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413837: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 41383a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41383b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41383c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41383d: pop ebx */
	m->esp = m->ebp;	/* 41383e: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 413840: pop ebp */
	m->esp += 4 + 0; return;	/* 413841: ret  */
L_413842:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413842: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413847: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41384c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413851: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413856: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413860u; native_call(m, 0x41f0e0u);	/* 41385b: call 0x41f0e0 */
	m->edx = (DWORD)(m->ebx + 0x8u);	/* 413860: lea edx, [ebx + 8] */
	m->eax = (DWORD)(m->ebp + 0xau);	/* 413863: lea eax, [ebp + 0xa] */
	{ DWORD v_ = 0x760fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 413866: push 0x760fa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41386b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41386c: push eax */
	m->esp -= 4; M32(m->esp) = 0x413872u; native_call(m, 0x402620u);	/* 41386d: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc48u)));	/* 413872: fld dword ptr [0x4dbc48] */
	m->ecx = 0xcu;	/* 413878: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41387d: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 41387f: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413883: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413886: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 413888: fstp qword ptr [esp] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41388b: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41388d: lea eax, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 413891: push 0x4b0334 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413896: push eax */
	m->esp -= 4; M32(m->esp) = 0x41389cu; native_call(m, 0x49e9ddu);	/* 413897: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41389c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4138a1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4138a6: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4138ab: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4138ad: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4138b7u; native_call(m, 0x41f0e0u);	/* 4138b2: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 4138b7: lea edx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x17u);	/* 4138bb: lea eax, [ebx + 0x17] */
	m->ecx = (DWORD)(m->ebp + 0x1au);	/* 4138be: lea ecx, [ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4138c1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4138c2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4138c3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4138c9u; native_call(m, 0x402620u);	/* 4138c4: call 0x402620 */
	m->eax = M32((DWORD)(0x9f1818u));	/* 4138c9: mov eax, dword ptr [0x9f1818] */
	m->edi = (DWORD)(m->esp + 0x64u);	/* 4138ce: lea edi, [esp + 0x64] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4138d2: add esp, 0x30 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4138d5: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4138d8: lea edx, [eax + ecx*2] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4138db: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4138de: xor eax, eax */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9088u)));	/* 4138e0: fild dword ptr [edx*4 + 0x9f9088] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4138e7: repne scasb al, byte ptr es:[edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4138e9: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc48u));	/* 4138ef: fmul dword ptr [0x4dbc48] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dceb0u)));	/* 4138f5: fld dword ptr [0x4dceb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc48u));	/* 4138fb: fmul dword ptr [0x4dbc48] */
	m->ecx = ~m->ecx;	/* 413901: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 413903: dec ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 413904: faddp st(1) */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413906: shl ecx, 3 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 413909: mov dword ptr [esp + 0x14], ecx */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41390d: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413913: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 413915: test ah, 0x40 */
	if (!m->zf) goto L_41395b;	/* 413918: jne 0x41395b */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41391a: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413920: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 413922: test ah, 1 */
	if (m->zf) goto L_413941;	/* 413925: je 0x413941 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413927: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41392a: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41392e: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b032cu; m->esp -= 4; M32(m->esp) = v_; }	/* 413931: push 0x4b032c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413936: push eax */
	m->esp -= 4; M32(m->esp) = 0x41393cu; native_call(m, 0x49e9ddu);	/* 413937: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41393c: add esp, 0x10 */
	goto L_413983;	/* 41393f: jmp 0x413983 */
L_413941:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413941: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 413944: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 413948: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0324u; m->esp -= 4; M32(m->esp) = v_; }	/* 41394b: push 0x4b0324 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413950: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413956u; native_call(m, 0x49e9ddu);	/* 413951: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413956: add esp, 0x10 */
	goto L_413983;	/* 413959: jmp 0x413983 */
L_41395b:
	m->edi = 0x4b033cu;	/* 41395b: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413960: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413963: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413965: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413969: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 41396b: fstp st(0) */
	m->ecx = ~m->ecx;	/* 41396d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41396f: sub edi, ecx */
	m->eax = m->ecx;	/* 413971: mov eax, ecx */
	m->esi = m->edi;	/* 413973: mov esi, edi */
	m->edi = m->edx;	/* 413975: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413977: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41397a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41397c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41397e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413981: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_413983:
	m->edi = 0x7657a4u;	/* 413983: mov edi, 0x7657a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413988: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41398b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41398d: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413991: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413993: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413995: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413997: push 0x3f800000 */
	m->esi = m->edi;	/* 41399c: mov esi, edi */
	m->edi = m->edx;	/* 41399e: mov edi, edx */
	m->edx = m->ecx;	/* 4139a0: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4139a2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4139a5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4139a7: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4139a9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4139aa: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4139ad: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4139af: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 4139b1: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4139b5: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4139b8: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4139b9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4139bb: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4139c0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4139c3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4139c5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4139c7: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4139c9: push 0x3f800000 */
	m->esi = m->edi;	/* 4139ce: mov esi, edi */
	m->edi = m->edx;	/* 4139d0: mov edi, edx */
	m->edx = m->ecx;	/* 4139d2: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4139d4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4139d7: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4139d9: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4139db: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4139dc: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4139df: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4139e1: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4139e3: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4139e8: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4139eb: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4139f0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4139f7u; native_call(m, 0x41f0e0u);	/* 4139f2: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4139f7: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4139fb: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4139ff: push eax */
	m->eax = (DWORD)(m->ebx + 0x17u);	/* 413a00: lea eax, [ebx + 0x17] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 413a03: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413a07: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413a08: push edx */
	m->esp -= 4; M32(m->esp) = 0x413a0eu; native_call(m, 0x402620u);	/* 413a09: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413a0e: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a11: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a16: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a1b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a20: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a25: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413a2fu; native_call(m, 0x41f0e0u);	/* 413a2a: call 0x41f0e0 */
	m->eax = (DWORD)(m->ebx + 0x28u);	/* 413a2f: lea eax, [ebx + 0x28] */
	{ DWORD v_ = 0x761024u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a32: push 0x761024 */
	m->esi = (DWORD)(m->ebp + 0xau);	/* 413a37: lea esi, [ebp + 0xa] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413a3a: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 413a3b: push esi */
	m->esp -= 4; M32(m->esp) = 0x413a41u; native_call(m, 0x402620u);	/* 413a3c: call 0x402620 */
	m->ecx = 0xcu;	/* 413a41: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413a46: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 413a48: lea edi, [esp + 0x54] */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 413a4c: lea edx, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413a50: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dbc4cu));	/* 413a52: mov ecx, dword ptr [0x4dbc4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413a58: push ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a59: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413a5e: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 413a5f: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x413a66u; native_call(m, 0x49e9ddu);	/* 413a61: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a66: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a6b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a70: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a75: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413a77: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413a81u; native_call(m, 0x41f0e0u);	/* 413a7c: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413a81: add esp, 0x40 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 413a84: lea ecx, [esp + 0x34] */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 413a88: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413a8b: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413a8c: push eax */
	m->eax = (DWORD)(m->ebp + 0x1au);	/* 413a8d: lea eax, [ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413a90: push eax */
	m->esp -= 4; M32(m->esp) = 0x413a96u; native_call(m, 0x402620u);	/* 413a91: call 0x402620 */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 413a96: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413a9a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413a9d: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413a9f: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413aa2: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9f1818u));	/* 413aa4: mov eax, dword ptr [0x9f1818] */
	m->ecx = ~m->ecx;	/* 413aa9: not ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 413aab: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 413aae: dec ecx */
	m->edi = m->ecx;	/* 413aaf: mov edi, ecx */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 413ab1: lea eax, [eax + edx*2] */
	{ DWORD a_ = m->edi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 413ab4: shl edi, 3 */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9080u)));	/* 413ab7: fild dword ptr [eax*4 + 0x9f9080] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 413abe: fmul dword ptr [0x4a9420] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x4dbc4cu));	/* 413ac4: fimul dword ptr [0x4dbc4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 413aca: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413ad0: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 413ad5: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 413ad9: fild dword ptr [esp + 0x18] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 413add: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413ae3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 413ae5: test ah, 0x40 */
	if (!m->zf) goto L_413b54;	/* 413ae8: jne 0x413b54 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 413aea: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413af0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 413af2: test ah, 1 */
	if (m->zf) goto L_413b09;	/* 413af5: je 0x413b09 */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413af7: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413afc: push eax */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 413afd: lea ecx, [esp + 0x38] */
	{ DWORD v_ = 0x4b02f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b01: push 0x4b02f8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413b06: push ecx */
	goto L_413b19;	/* 413b07: jmp 0x413b19 */
L_413b09:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413b09: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413b0e: push eax */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 413b0f: lea edx, [esp + 0x38] */
	{ DWORD v_ = 0x4b02f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b13: push 0x4b02f0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413b18: push edx */
L_413b19:
	m->esp -= 4; M32(m->esp) = 0x413b1eu; native_call(m, 0x49e9ddu);	/* 413b19: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413b1e: add esp, 0xc */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b21: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b26: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b28: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b2d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b32: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413b3cu; native_call(m, 0x41f0e0u);	/* 413b37: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 413b3c: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->edi + m->ebp*1 + 0x1au);	/* 413b40: lea ecx, [edi + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413b44: push eax */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 413b45: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413b48: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413b49: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413b4fu; native_call(m, 0x402620u);	/* 413b4a: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413b4f: add esp, 0x20 */
	goto L_413b56;	/* 413b52: jmp 0x413b56 */
L_413b54:
	ST(0) = ST(0); FPOP();	/* 413b54: fstp st(0) */
L_413b56:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b56: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b5b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b60: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b65: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b6a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413b74u; native_call(m, 0x41f0e0u);	/* 413b6f: call 0x41f0e0 */
	m->edx = (DWORD)(m->ebx + 0x48u);	/* 413b74: lea edx, [ebx + 0x48] */
	{ DWORD v_ = 0x7610a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b77: push 0x7610a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413b7c: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 413b7d: push esi */
	m->esp -= 4; M32(m->esp) = 0x413b83u; native_call(m, 0x402620u);	/* 413b7e: call 0x402620 */
	m->ecx = 0xcu;	/* 413b83: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413b88: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 413b8a: lea edi, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413b8e: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 413b90: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dbc50u));	/* 413b92: mov eax, dword ptr [0x4dbc50] */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 413b97: lea ecx, [esp + 0x54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413b9b: push eax */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 413b9c: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413ba1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413ba7u; native_call(m, 0x49e9ddu);	/* 413ba2: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413ba7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413bac: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413bb1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413bb6: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413bb8: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413bc2u; native_call(m, 0x41f0e0u);	/* 413bbd: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413bc2: add esp, 0x40 */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413bc5: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ebx, b_ = 0x57u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 413bc9: add ebx, 0x57 */
	m->eax = (DWORD)(m->ebp + 0x1au);	/* 413bcc: lea eax, [ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413bcf: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 413bd0: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413bd1: push eax */
	m->esp -= 4; M32(m->esp) = 0x413bd7u; native_call(m, 0x402620u);	/* 413bd2: call 0x402620 */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 413bd7: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413bdb: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413bde: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413be0: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413be3: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9f1818u));	/* 413be5: mov eax, dword ptr [0x9f1818] */
	m->ecx = ~m->ecx;	/* 413bea: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 413bec: dec ecx */
	m->esi = m->ecx;	/* 413bed: mov esi, ecx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 413bef: lea ecx, [eax + eax*8] */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 413bf2: shl esi, 3 */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 413bf5: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9080u)));	/* 413bf8: fild dword ptr [edx*4 + 0x9f9080] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 413bff: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcc68u));	/* 413c05: fadd dword ptr [0x4dcc68] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x4dbc50u));	/* 413c0b: fimul dword ptr [0x4dbc50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 413c11: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413c17: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 413c1c: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 413c20: fild dword ptr [esp + 0x18] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 413c24: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413c2a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 413c2c: test ah, 0x40 */
	if (!m->zf) goto L_418fb9;	/* 413c2f: jne 0x418fb9 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 413c35: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 413c3b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 413c3d: test ah, 1 */
	if (m->zf) goto L_413c54;	/* 413c40: je 0x413c54 */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413c42: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413c47: push eax */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 413c48: lea eax, [esp + 0x38] */
	{ DWORD v_ = 0x4b02f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 413c4c: push 0x4b02f8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413c51: push eax */
	goto L_413c64;	/* 413c52: jmp 0x413c64 */
L_413c54:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413c54: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413c59: push eax */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 413c5a: lea ecx, [esp + 0x38] */
	{ DWORD v_ = 0x4b02f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413c5e: push 0x4b02f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413c63: push ecx */
L_413c64:
	m->esp -= 4; M32(m->esp) = 0x413c69u; native_call(m, 0x49e9ddu);	/* 413c64: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413c69: add esp, 0xc */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413c6c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413c71: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413c73: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413c78: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413c7d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413c87u; native_call(m, 0x41f0e0u);	/* 413c82: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 413c87: lea edx, [esp + 0x48] */
	m->eax = (DWORD)(m->esi + m->ebp*1 + 0x1au);	/* 413c8b: lea eax, [esi + ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413c8f: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 413c90: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413c91: push eax */
	m->esp -= 4; M32(m->esp) = 0x413c97u; native_call(m, 0x402620u);	/* 413c92: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413c97: add esp, 0x20 */
	m->edi = M32(m->esp); m->esp += 4;	/* 413c9a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 413c9b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 413c9c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 413c9d: pop ebx */
	m->esp = m->ebp;	/* 413c9e: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 413ca0: pop ebp */
	m->esp += 4 + 0; return;	/* 413ca1: ret  */
L_413ca2:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413ca2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413ca7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413cac: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413cb1: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413cb6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413cc0u; native_call(m, 0x41f0e0u);	/* 413cbb: call 0x41f0e0 */
	m->ecx = (DWORD)(m->ebx + 0x8u);	/* 413cc0: lea ecx, [ebx + 8] */
	m->esi = (DWORD)(m->ebp + 0xau);	/* 413cc3: lea esi, [ebp + 0xa] */
	{ DWORD v_ = 0x7614a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 413cc6: push 0x7614a4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413ccb: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 413ccc: push esi */
	M32((DWORD)(m->esp + 0x30u)) = m->esi;	/* 413ccd: mov dword ptr [esp + 0x30], esi */
	m->esp -= 4; M32(m->esp) = 0x413cd6u; native_call(m, 0x402620u);	/* 413cd1: call 0x402620 */
	m->ecx = 0xcu;	/* 413cd6: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413cdb: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 413cdd: lea edi, [esp + 0x54] */
	m->edx = M32((DWORD)(0x4dc290u));	/* 413ce1: mov edx, dword ptr [0x4dc290] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413ce7: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 413ce9: stosw word ptr es:[edi], ax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413ceb: push edx */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 413cec: lea eax, [esp + 0x58] */
	{ DWORD v_ = 0x4b02e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 413cf0: push 0x4b02e8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413cf5: push eax */
	m->esp -= 4; M32(m->esp) = 0x413cfbu; native_call(m, 0x49e9ddu);	/* 413cf6: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413cfb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d00: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d05: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d0a: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d0c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413d16u; native_call(m, 0x41f0e0u);	/* 413d11: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413d16: add esp, 0x40 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 413d19: lea ecx, [esp + 0x34] */
	m->edx = (DWORD)(m->ebx + 0x17u);	/* 413d1d: lea edx, [ebx + 0x17] */
	{ DWORD a_ = m->ebp, b_ = 0x1au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 413d20: add ebp, 0x1a */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413d23: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413d24: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 413d25: push ebp */
	m->esp -= 4; M32(m->esp) = 0x413d2bu; native_call(m, 0x402620u);	/* 413d26: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d2b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d30: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d35: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d3a: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d3f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413d49u; native_call(m, 0x41f0e0u);	/* 413d44: call 0x41f0e0 */
	m->eax = (DWORD)(m->ebx + 0x28u);	/* 413d49: lea eax, [ebx + 0x28] */
	{ DWORD v_ = 0x761524u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d4c: push 0x761524 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413d51: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 413d52: push esi */
	m->esp -= 4; M32(m->esp) = 0x413d58u; native_call(m, 0x402620u);	/* 413d53: call 0x402620 */
	FPUSH((long double)(int)M32((DWORD)(0x4dc294u)));	/* 413d58: fild dword ptr [0x4dc294] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413d5e: add esp, 0x2c */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc70u));	/* 413d61: fmul dword ptr [0x4dbc70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcc6cu));	/* 413d67: fadd dword ptr [0x4dcc6c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413d6d: call 0x49ec14 */
	m->esi = m->eax;	/* 413d72: mov esi, eax */
	m->ecx = 0xcu;	/* 413d74: mov ecx, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 413d79: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_413df5;	/* 413d7b: jle 0x413df5 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413d7d: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 413d7f: lea edi, [esp + 0x34] */
	m->edx = M32((DWORD)(0x4dc294u));	/* 413d83: mov edx, dword ptr [0x4dc294] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413d89: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413d8b: xor ecx, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413d8d: push edx */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 413d8e: mov dword ptr [esp + 0x24], ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 413d92: push 0x4b0320 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 413d97: mov dword ptr [esp + 0x2c], ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 413d9b: stosw word ptr es:[edi], ax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 413d9d: mov dword ptr [esp + 0x30], ecx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 413da1: lea eax, [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 413da5: mov dword ptr [esp + 0x34], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413da9: push eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 413daa: mov dword ptr [esp + 0x3c], ecx */
	m->esp -= 4; M32(m->esp) = 0x413db3u; native_call(m, 0x49e9ddu);	/* 413dae: call 0x49e9dd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 413db3: push esi */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 413db4: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x4b02e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413db8: push 0x4b02e0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413dbd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413dc3u; native_call(m, 0x49e9ddu);	/* 413dbe: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 413dc3: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413dc7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413dca: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413dcc: add esp, 0x18 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413dcf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413dd1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413dd3: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413dd5: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 413dd9: mov esi, edi */
	m->edi = m->edx;	/* 413ddb: mov edi, edx */
	m->edx = m->ecx;	/* 413ddd: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413ddf: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413de2: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413de4: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413de6: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413de7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413dea: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413dec: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413dee: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413df1: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_413e17;	/* 413df3: jmp 0x413e17 */
L_413df5:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413df5: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 413df7: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413dfb: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 413dfd: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc294u));	/* 413dff: mov eax, dword ptr [0x4dc294] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 413e04: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413e08: push eax */
	{ DWORD v_ = 0x4b02dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 413e09: push 0x4b02dc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413e0e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413e14u; native_call(m, 0x49e9ddu);	/* 413e0f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413e14: add esp, 0xc */
L_413e17:
	m->edi = 0x765824u;	/* 413e17: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413e1c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413e1f: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413e21: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413e25: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413e27: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413e29: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413e2b: push 0x3f800000 */
	m->esi = m->edi;	/* 413e30: mov esi, edi */
	m->edi = m->edx;	/* 413e32: mov edi, edx */
	m->edx = m->ecx;	/* 413e34: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413e36: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413e39: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413e3b: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413e3d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413e3e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413e41: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413e43: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 413e45: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413e49: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413e4c: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413e51: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 413e53: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413e58: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413e5b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413e5d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413e5f: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413e61: push 0x3f800000 */
	m->esi = m->edi;	/* 413e66: mov esi, edi */
	m->edi = m->edx;	/* 413e68: mov edi, edx */
	m->edx = m->ecx;	/* 413e6a: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413e6c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413e6f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413e71: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413e73: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413e74: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413e77: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413e79: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413e7b: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413e7c: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413e7f: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413e84: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x413e8bu; native_call(m, 0x41f0e0u);	/* 413e86: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 413e8b: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0x37u);	/* 413e8f: lea ecx, [ebx + 0x37] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413e92: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413e93: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 413e94: push ebp */
	m->esp -= 4; M32(m->esp) = 0x413e9au; native_call(m, 0x402620u);	/* 413e95: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413e9a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413e9f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413ea4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413ea9: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413eae: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x413eb8u; native_call(m, 0x41f0e0u);	/* 413eb3: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 413eb8: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0x48u);	/* 413ebc: lea edx, [ebx + 0x48] */
	{ DWORD v_ = 0x7615a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 413ebf: push 0x7615a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413ec4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413ec5: push eax */
	m->esp -= 4; M32(m->esp) = 0x413ecbu; native_call(m, 0x402620u);	/* 413ec6: call 0x402620 */
	FPUSH((long double)(int)M32((DWORD)(0x4dc298u)));	/* 413ecb: fild dword ptr [0x4dc298] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413ed1: add esp, 0x40 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc70u));	/* 413ed4: fmul dword ptr [0x4dbc70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dc548u));	/* 413eda: fadd dword ptr [0x4dc548] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 413ee0: call 0x49ec14 */
	m->esi = m->eax;	/* 413ee5: mov esi, eax */
	m->ecx = 0xcu;	/* 413ee7: mov ecx, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 413eec: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_413f68;	/* 413eee: jle 0x413f68 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413ef0: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 413ef2: lea edi, [esp + 0x34] */
	m->edx = M32((DWORD)(0x4dc298u));	/* 413ef6: mov edx, dword ptr [0x4dc298] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413efc: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413efe: xor ecx, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 413f00: push edx */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 413f01: mov dword ptr [esp + 0x24], ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 413f05: push 0x4b0320 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 413f0a: mov dword ptr [esp + 0x2c], ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 413f0e: stosw word ptr es:[edi], ax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 413f10: mov dword ptr [esp + 0x30], ecx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 413f14: lea eax, [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 413f18: mov dword ptr [esp + 0x34], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413f1c: push eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 413f1d: mov dword ptr [esp + 0x3c], ecx */
	m->esp -= 4; M32(m->esp) = 0x413f26u; native_call(m, 0x49e9ddu);	/* 413f21: call 0x49e9dd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 413f26: push esi */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 413f27: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x4b02e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 413f2b: push 0x4b02e0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413f30: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413f36u; native_call(m, 0x49e9ddu);	/* 413f31: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 413f36: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413f3a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413f3d: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413f3f: add esp, 0x18 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413f42: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413f44: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413f46: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413f48: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 413f4c: mov esi, edi */
	m->edi = m->edx;	/* 413f4e: mov edi, edx */
	m->edx = m->ecx;	/* 413f50: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413f52: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413f55: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413f57: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413f59: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413f5a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413f5d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413f5f: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413f61: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413f64: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_413f8a;	/* 413f66: jmp 0x413f8a */
L_413f68:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413f68: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 413f6a: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 413f6e: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 413f70: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc298u));	/* 413f72: mov eax, dword ptr [0x4dc298] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 413f77: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413f7b: push eax */
	{ DWORD v_ = 0x4b02dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 413f7c: push 0x4b02dc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 413f81: push ecx */
	m->esp -= 4; M32(m->esp) = 0x413f87u; native_call(m, 0x49e9ddu);	/* 413f82: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 413f87: add esp, 0xc */
L_413f8a:
	m->edi = 0x765824u;	/* 413f8a: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413f8f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 413f92: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 413f94: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413f98: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413f9a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413f9c: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413f9e: push 0x3f800000 */
	m->esi = m->edi;	/* 413fa3: mov esi, edi */
	m->edi = m->edx;	/* 413fa5: mov edi, edx */
	m->edx = m->ecx;	/* 413fa7: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413fa9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413fac: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413fae: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413fb0: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413fb1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413fb4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413fb6: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 413fb8: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413fbc: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413fbf: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413fc4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 413fc6: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413fcb: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413fce: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 413fd0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 413fd2: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 413fd4: push 0x3f800000 */
	m->esi = m->edi;	/* 413fd9: mov esi, edi */
	m->edi = m->edx;	/* 413fdb: mov edi, edx */
	m->edx = m->ecx;	/* 413fdd: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413fdf: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 413fe2: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 413fe4: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 413fe6: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 413fe7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 413fea: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 413fec: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 413fee: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 413fef: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 413ff2: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 413ff7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x413ffeu; native_call(m, 0x41f0e0u);	/* 413ff9: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 413ffe: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0x57u);	/* 414002: lea ecx, [ebx + 0x57] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414005: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414006: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 414007: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41400du; native_call(m, 0x402620u);	/* 414008: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41400d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414012: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414017: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41401c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414021: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41402bu; native_call(m, 0x41f0e0u);	/* 414026: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 41402b: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0x68u);	/* 41402f: lea edx, [ebx + 0x68] */
	{ DWORD v_ = 0x761624u; m->esp -= 4; M32(m->esp) = v_; }	/* 414032: push 0x761624 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414037: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414038: push eax */
	m->esp -= 4; M32(m->esp) = 0x41403eu; native_call(m, 0x402620u);	/* 414039: call 0x402620 */
	FPUSH((long double)(int)M32((DWORD)(0x4dc29cu)));	/* 41403e: fild dword ptr [0x4dc29c] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414044: add esp, 0x40 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc70u));	/* 414047: fmul dword ptr [0x4dbc70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dc248u));	/* 41404d: fadd dword ptr [0x4dc248] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 414053: call 0x49ec14 */
	m->esi = m->eax;	/* 414058: mov esi, eax */
	m->ecx = 0xcu;	/* 41405a: mov ecx, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41405f: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_4140db;	/* 414061: jle 0x4140db */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414063: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 414065: lea edi, [esp + 0x34] */
	m->edx = M32((DWORD)(0x4dc29cu));	/* 414069: mov edx, dword ptr [0x4dc29c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41406f: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414071: xor ecx, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414073: push edx */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 414074: mov dword ptr [esp + 0x24], ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 414078: push 0x4b0320 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 41407d: mov dword ptr [esp + 0x2c], ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414081: stosw word ptr es:[edi], ax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 414083: mov dword ptr [esp + 0x30], ecx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 414087: lea eax, [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 41408b: mov dword ptr [esp + 0x34], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41408f: push eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 414090: mov dword ptr [esp + 0x3c], ecx */
	m->esp -= 4; M32(m->esp) = 0x414099u; native_call(m, 0x49e9ddu);	/* 414094: call 0x49e9dd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 414099: push esi */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 41409a: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x4b02e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41409e: push 0x4b02e0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4140a3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4140a9u; native_call(m, 0x49e9ddu);	/* 4140a4: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 4140a9: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4140ad: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4140b0: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4140b2: add esp, 0x18 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4140b5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4140b7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4140b9: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4140bb: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4140bf: mov esi, edi */
	m->edi = m->edx;	/* 4140c1: mov edi, edx */
	m->edx = m->ecx;	/* 4140c3: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4140c5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4140c8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4140ca: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4140cc: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4140cd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4140d0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4140d2: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4140d4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4140d7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_4140fd;	/* 4140d9: jmp 0x4140fd */
L_4140db:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4140db: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 4140dd: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4140e1: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4140e3: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc29cu));	/* 4140e5: mov eax, dword ptr [0x4dc29c] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 4140ea: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4140ee: push eax */
	{ DWORD v_ = 0x4b02dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4140ef: push 0x4b02dc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4140f4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4140fau; native_call(m, 0x49e9ddu);	/* 4140f5: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4140fa: add esp, 0xc */
L_4140fd:
	m->edi = 0x765824u;	/* 4140fd: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414102: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414105: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414107: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41410b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41410d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41410f: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414111: push 0x3f800000 */
	m->esi = m->edi;	/* 414116: mov esi, edi */
	m->edi = m->edx;	/* 414118: mov edi, edx */
	m->edx = m->ecx;	/* 41411a: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41411c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41411f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414121: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414123: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414124: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414127: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414129: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 41412b: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41412f: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414132: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414137: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 414139: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41413e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414141: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414143: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414145: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414147: push 0x3f800000 */
	m->esi = m->edi;	/* 41414c: mov esi, edi */
	m->edi = m->edx;	/* 41414e: mov edi, edx */
	m->edx = m->ecx;	/* 414150: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414152: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414155: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414157: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414159: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41415a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41415d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41415f: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414161: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414162: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414165: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41416a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x414171u; native_call(m, 0x41f0e0u);	/* 41416c: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 414171: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0x77u);	/* 414175: lea ecx, [ebx + 0x77] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414178: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414179: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41417a: push ebp */
	m->esp -= 4; M32(m->esp) = 0x414180u; native_call(m, 0x402620u);	/* 41417b: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414180: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414185: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41418a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41418f: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414194: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41419eu; native_call(m, 0x41f0e0u);	/* 414199: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 41419e: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0x88u);	/* 4141a2: lea edx, [ebx + 0x88] */
	{ DWORD v_ = 0x7616a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4141a8: push 0x7616a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4141ad: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4141ae: push eax */
	m->esp -= 4; M32(m->esp) = 0x4141b4u; native_call(m, 0x402620u);	/* 4141af: call 0x402620 */
	FPUSH((long double)(int)M32((DWORD)(0x4dc2a0u)));	/* 4141b4: fild dword ptr [0x4dc2a0] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4141ba: add esp, 0x40 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc70u));	/* 4141bd: fmul dword ptr [0x4dbc70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcb34u));	/* 4141c3: fadd dword ptr [0x4dcb34] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4141c9: call 0x49ec14 */
	m->esi = m->eax;	/* 4141ce: mov esi, eax */
	m->ecx = 0xcu;	/* 4141d0: mov ecx, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4141d5: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_414251;	/* 4141d7: jle 0x414251 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4141d9: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 4141db: lea edi, [esp + 0x34] */
	m->edx = M32((DWORD)(0x4dc2a0u));	/* 4141df: mov edx, dword ptr [0x4dc2a0] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4141e5: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4141e7: xor ecx, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4141e9: push edx */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 4141ea: mov dword ptr [esp + 0x24], ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 4141ee: push 0x4b0320 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 4141f3: mov dword ptr [esp + 0x2c], ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4141f7: stosw word ptr es:[edi], ax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 4141f9: mov dword ptr [esp + 0x30], ecx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4141fd: lea eax, [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 414201: mov dword ptr [esp + 0x34], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414205: push eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 414206: mov dword ptr [esp + 0x3c], ecx */
	m->esp -= 4; M32(m->esp) = 0x41420fu; native_call(m, 0x49e9ddu);	/* 41420a: call 0x49e9dd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41420f: push esi */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 414210: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x4b02e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 414214: push 0x4b02e0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414219: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41421fu; native_call(m, 0x49e9ddu);	/* 41421a: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 41421f: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414223: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414226: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414228: add esp, 0x18 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41422b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41422d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41422f: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414231: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 414235: mov esi, edi */
	m->edi = m->edx;	/* 414237: mov edi, edx */
	m->edx = m->ecx;	/* 414239: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41423b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41423e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414240: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414242: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414243: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414246: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414248: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41424a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41424d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_414273;	/* 41424f: jmp 0x414273 */
L_414251:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414251: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 414253: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414257: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414259: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc2a0u));	/* 41425b: mov eax, dword ptr [0x4dc2a0] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 414260: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414264: push eax */
	{ DWORD v_ = 0x4b02dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 414265: push 0x4b02dc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41426a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x414270u; native_call(m, 0x49e9ddu);	/* 41426b: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414270: add esp, 0xc */
L_414273:
	m->edi = 0x765824u;	/* 414273: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414278: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41427b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41427d: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414281: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414283: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414285: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414287: push 0x3f800000 */
	m->esi = m->edi;	/* 41428c: mov esi, edi */
	m->edi = m->edx;	/* 41428e: mov edi, edx */
	m->edx = m->ecx;	/* 414290: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414292: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414295: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414297: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414299: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41429a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41429d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41429f: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 4142a1: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4142a5: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4142a8: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4142ad: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4142af: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4142b4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4142b7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4142b9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4142bb: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4142bd: push 0x3f800000 */
	m->esi = m->edi;	/* 4142c2: mov esi, edi */
	m->edi = m->edx;	/* 4142c4: mov edi, edx */
	m->edx = m->ecx;	/* 4142c6: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4142c8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4142cb: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4142cd: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4142cf: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4142d0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4142d3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4142d5: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4142d7: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4142d8: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4142db: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4142e0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4142e7u; native_call(m, 0x41f0e0u);	/* 4142e2: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4142e7: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0x97u);	/* 4142eb: lea ecx, [ebx + 0x97] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4142f1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4142f2: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4142f3: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4142f9u; native_call(m, 0x402620u);	/* 4142f4: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4142f9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4142fe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414303: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414308: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41430d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414317u; native_call(m, 0x41f0e0u);	/* 414312: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 414317: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0xa8u);	/* 41431b: lea edx, [ebx + 0xa8] */
	{ DWORD v_ = 0x761724u; m->esp -= 4; M32(m->esp) = v_; }	/* 414321: push 0x761724 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414326: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414327: push eax */
	m->esp -= 4; M32(m->esp) = 0x41432du; native_call(m, 0x402620u);	/* 414328: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc2a4u)));	/* 41432d: fld dword ptr [0x4dc2a4] */
	m->ecx = 0xcu;	/* 414333: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414338: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 41433a: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41433e: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414341: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414343: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 414346: lea ecx, [esp + 0x3c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41434a: stosw word ptr es:[edi], ax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41434c: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 41434f: push 0x4b02fc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414354: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41435au; native_call(m, 0x49e9ddu);	/* 414355: call 0x49e9dd */
	m->edi = 0x7657a4u;	/* 41435a: mov edi, 0x7657a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41435f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414362: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 414364: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414368: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41436a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41436c: sub edi, ecx */
	m->esi = m->edi;	/* 41436e: mov esi, edi */
	m->edi = m->edx;	/* 414370: mov edi, edx */
	m->edx = m->ecx;	/* 414372: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414374: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414377: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414379: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41437b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41437c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41437f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414381: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 414383: lea edx, [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414387: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41438a: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41438f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 414391: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414396: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414399: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41439b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41439d: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41439f: push 0x3f800000 */
	m->esi = m->edi;	/* 4143a4: mov esi, edi */
	m->edi = m->edx;	/* 4143a6: mov edi, edx */
	m->edx = m->ecx;	/* 4143a8: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4143aa: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4143ad: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4143af: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4143b1: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4143b2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4143b5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4143b7: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4143b9: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4143be: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4143c1: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4143c2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4143c4: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4143ceu; native_call(m, 0x41f0e0u);	/* 4143c9: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 4143ce: lea eax, [esp + 0x58] */
	{ DWORD a_ = m->ebx, b_ = 0xb7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4143d2: add ebx, 0xb7 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4143d8: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4143d9: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4143da: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4143e0u; native_call(m, 0x402620u);	/* 4143db: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4143e0: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4143e3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4143e4: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4143e5: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4143e6: pop ebx */
	m->esp = m->ebp;	/* 4143e7: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4143e9: pop ebp */
	m->esp += 4 + 0; return;	/* 4143ea: ret  */
L_4143eb:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4143eb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4143f0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4143f5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4143fa: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4143ff: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414409u; native_call(m, 0x41f0e0u);	/* 414404: call 0x41f0e0 */
	m->ecx = (DWORD)(m->ebx + 0x8u);	/* 414409: lea ecx, [ebx + 8] */
	m->esi = (DWORD)(m->ebp + 0xau);	/* 41440c: lea esi, [ebp + 0xa] */
	{ DWORD v_ = 0x7619a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41440f: push 0x7619a4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414414: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 414415: push esi */
	M32((DWORD)(m->esp + 0x30u)) = m->esi;	/* 414416: mov dword ptr [esp + 0x30], esi */
	m->esp -= 4; M32(m->esp) = 0x41441fu; native_call(m, 0x402620u);	/* 41441a: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc228u)));	/* 41441f: fld dword ptr [0x4dc228] */
	m->ecx = 0xcu;	/* 414425: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41442a: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 41442c: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 414430: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414434: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414437: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 414439: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 41443d: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414442: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414443: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x41444au; native_call(m, 0x49e9ddu);	/* 414445: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41444a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41444f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414454: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 414459: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41445b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414465u; native_call(m, 0x41f0e0u);	/* 414460: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 414465: lea edx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x17u);	/* 414469: lea eax, [ebx + 0x17] */
	m->ecx = (DWORD)(m->ebp + 0x1au);	/* 41446c: lea ecx, [ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41446f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414470: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414471: push ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 414472: mov dword ptr [esp + 0x48], ecx */
	m->esp -= 4; M32(m->esp) = 0x41447bu; native_call(m, 0x402620u);	/* 414476: call 0x402620 */
	m->eax = M32((DWORD)(0x9f1818u));	/* 41447b: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414480: add esp, 0x30 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 414483: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 414486: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9078u)));	/* 414489: fild dword ptr [edx*4 + 0x9f9078] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 414490: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc228u));	/* 414496: fmul dword ptr [0x4dc228] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41449c: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 4144a2: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4144a8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4144aa: test ah, 0x41 */
	if (!m->zf) goto L_4144d1;	/* 4144ad: jne 0x4144d1 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 4144af: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4144b5: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4144bb: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 4144c1: fmul dword ptr [0x4a947c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc228u));	/* 4144c7: fmul dword ptr [0x4dc228] */
	ST(0) = -ST(0);	/* 4144cd: fchs  */
	goto L_4144d7;	/* 4144cf: jmp 0x4144d7 */
L_4144d1:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 4144d1: fld dword ptr [0x4a93e8] */
L_4144d7:
	m->edi = (DWORD)(m->esp + 0x34u);	/* 4144d7: lea edi, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4144db: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4144de: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4144e0: repne scasb al, byte ptr es:[edi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4144e2: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4144e4: fcom dword ptr [0x4a93e8] */
	m->ecx = ~m->ecx;	/* 4144ea: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4144ec: dec ecx */
	m->edi = m->ecx;	/* 4144ed: mov edi, ecx */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4144ef: fnstsw ax */
	{ DWORD a_ = m->edi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4144f1: shl edi, 3 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4144f4: test ah, 0x40 */
	if (!m->zf) goto L_414582;	/* 4144f7: jne 0x414582 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4144fd: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414503: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414505: test ah, 1 */
	if (m->zf) goto L_414537;	/* 414508: je 0x414537 */
	{ long double t = ST(0); FPUSH(t); }	/* 41450a: fld st(0) */
	ST(0) = -ST(0);	/* 41450c: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dc228u)); FPOP();	/* 41450e: fcomp dword ptr [0x4dc228] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414514: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414516: test ah, 0x41 */
	if (!m->zf) goto L_414525;	/* 414519: jne 0x414525 */
	ST(0) = ST(0); FPOP();	/* 41451b: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc228u)));	/* 41451d: fld dword ptr [0x4dc228] */
	ST(0) = -ST(0);	/* 414523: fchs  */
L_414525:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414525: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 414528: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41452c: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02d4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41452f: push 0x4b02d4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414534: push eax */
	goto L_414547;	/* 414535: jmp 0x414547 */
L_414537:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414537: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 41453a: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41453e: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 414541: push 0x4b02cc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414546: push ecx */
L_414547:
	m->esp -= 4; M32(m->esp) = 0x41454cu; native_call(m, 0x49e9ddu);	/* 414547: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41454c: add esp, 0x10 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41454f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 414554: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414556: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41455b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414560: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41456au; native_call(m, 0x41f0e0u);	/* 414565: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 41456a: lea edx, [esp + 0x48] */
	m->eax = (DWORD)(m->ebx + 0x17u);	/* 41456e: lea eax, [ebx + 0x17] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414571: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414572: push eax */
	m->eax = (DWORD)(m->edi + m->ebp*1 + 0x1au);	/* 414573: lea eax, [edi + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414577: push eax */
	m->esp -= 4; M32(m->esp) = 0x41457du; native_call(m, 0x402620u);	/* 414578: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41457d: add esp, 0x20 */
	goto L_414584;	/* 414580: jmp 0x414584 */
L_414582:
	ST(0) = ST(0); FPOP();	/* 414582: fstp st(0) */
L_414584:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414584: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414589: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41458e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414593: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414598: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4145a2u; native_call(m, 0x41f0e0u);	/* 41459d: call 0x41f0e0 */
	m->ecx = (DWORD)(m->ebx + 0x28u);	/* 4145a2: lea ecx, [ebx + 0x28] */
	{ DWORD v_ = 0x761a24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4145a5: push 0x761a24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4145aa: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4145ab: push esi */
	m->esp -= 4; M32(m->esp) = 0x4145b1u; native_call(m, 0x402620u);	/* 4145ac: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc22cu)));	/* 4145b1: fld dword ptr [0x4dc22c] */
	m->ecx = 0xcu;	/* 4145b7: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4145bc: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 4145be: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 4145c2: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4145c6: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4145c9: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 4145cb: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 4145cf: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4145d4: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4145d5: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x4145dcu; native_call(m, 0x49e9ddu);	/* 4145d7: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4145dc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4145e1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4145e6: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4145eb: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4145ed: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4145f7u; native_call(m, 0x41f0e0u);	/* 4145f2: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 4145f7: mov edx, dword ptr [esp + 0x3c] */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 4145fb: lea ecx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 4145ff: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414602: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414603: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414604: push edx */
	m->esp -= 4; M32(m->esp) = 0x41460au; native_call(m, 0x402620u);	/* 414605: call 0x402620 */
	m->eax = M32((DWORD)(0x9f1818u));	/* 41460a: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41460f: add esp, 0x30 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 414612: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 414615: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9078u)));	/* 414618: fild dword ptr [edx*4 + 0x9f9078] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41461f: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc22cu));	/* 414625: fmul dword ptr [0x4dc22c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41462b: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 414631: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414637: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414639: test ah, 0x41 */
	if (!m->zf) goto L_414660;	/* 41463c: jne 0x414660 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41463e: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 414644: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 41464a: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 414650: fmul dword ptr [0x4a947c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc22cu));	/* 414656: fmul dword ptr [0x4dc22c] */
	ST(0) = -ST(0);	/* 41465c: fchs  */
	goto L_414666;	/* 41465e: jmp 0x414666 */
L_414660:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 414660: fld dword ptr [0x4a93e8] */
L_414666:
	m->edi = (DWORD)(m->esp + 0x34u);	/* 414666: lea edi, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41466a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41466d: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41466f: repne scasb al, byte ptr es:[edi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 414671: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 414673: fcom dword ptr [0x4a93e8] */
	m->ecx = ~m->ecx;	/* 414679: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41467b: dec ecx */
	m->edi = m->ecx;	/* 41467c: mov edi, ecx */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41467e: fnstsw ax */
	{ DWORD a_ = m->edi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 414680: shl edi, 3 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414683: test ah, 0x40 */
	if (!m->zf) goto L_414711;	/* 414686: jne 0x414711 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41468c: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414692: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414694: test ah, 1 */
	if (m->zf) goto L_4146c6;	/* 414697: je 0x4146c6 */
	{ long double t = ST(0); FPUSH(t); }	/* 414699: fld st(0) */
	ST(0) = -ST(0);	/* 41469b: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dc22cu)); FPOP();	/* 41469d: fcomp dword ptr [0x4dc22c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4146a3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4146a5: test ah, 0x41 */
	if (!m->zf) goto L_4146b4;	/* 4146a8: jne 0x4146b4 */
	ST(0) = ST(0); FPOP();	/* 4146aa: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc22cu)));	/* 4146ac: fld dword ptr [0x4dc22c] */
	ST(0) = -ST(0);	/* 4146b2: fchs  */
L_4146b4:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4146b4: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4146b7: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4146bb: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02d4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4146be: push 0x4b02d4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4146c3: push eax */
	goto L_4146d6;	/* 4146c4: jmp 0x4146d6 */
L_4146c6:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4146c6: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 4146c9: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4146cd: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 4146d0: push 0x4b02cc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4146d5: push ecx */
L_4146d6:
	m->esp -= 4; M32(m->esp) = 0x4146dbu; native_call(m, 0x49e9ddu);	/* 4146d6: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4146db: add esp, 0x10 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4146de: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4146e3: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4146e5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4146ea: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4146ef: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4146f9u; native_call(m, 0x41f0e0u);	/* 4146f4: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 4146f9: lea edx, [esp + 0x48] */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 4146fd: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414700: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414701: push eax */
	m->eax = (DWORD)(m->edi + m->ebp*1 + 0x1au);	/* 414702: lea eax, [edi + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414706: push eax */
	m->esp -= 4; M32(m->esp) = 0x41470cu; native_call(m, 0x402620u);	/* 414707: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41470c: add esp, 0x20 */
	goto L_414713;	/* 41470f: jmp 0x414713 */
L_414711:
	ST(0) = ST(0); FPOP();	/* 414711: fstp st(0) */
L_414713:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414713: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414718: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41471d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414722: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414727: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414731u; native_call(m, 0x41f0e0u);	/* 41472c: call 0x41f0e0 */
	m->ecx = (DWORD)(m->ebx + 0x48u);	/* 414731: lea ecx, [ebx + 0x48] */
	{ DWORD v_ = 0x761aa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 414734: push 0x761aa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414739: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41473a: push esi */
	m->esp -= 4; M32(m->esp) = 0x414740u; native_call(m, 0x402620u);	/* 41473b: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc230u)));	/* 414740: fld dword ptr [0x4dc230] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 414746: fcomp dword ptr [0x4a93e8] */
	m->ecx = 0xcu;	/* 41474c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414751: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 414753: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414757: add esp, 0x20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41475a: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc230u)));	/* 41475c: fld dword ptr [0x4dc230] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414762: stosw word ptr es:[edi], ax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414764: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414766: test ah, 1 */
	if (m->zf) goto L_41477d;	/* 414769: je 0x41477d */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41476b: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41476e: lea edx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414772: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 414775: push 0x4b02fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41477a: push edx */
	goto L_41478d;	/* 41477b: jmp 0x41478d */
L_41477d:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41477d: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 414780: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414784: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 414787: push 0x4b02c4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41478c: push eax */
L_41478d:
	m->esp -= 4; M32(m->esp) = 0x414792u; native_call(m, 0x49e9ddu);	/* 41478d: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 414792: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414797: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41479a: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41479c: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41479f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4147a1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4147a3: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4147a5: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4147a9: mov esi, edi */
	m->ebp = m->ecx;	/* 4147ab: mov ebp, ecx */
	m->edi = m->edx;	/* 4147ad: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4147af: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4147b2: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 4147b4: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4147b6: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4147b7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4147ba: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 4147bc: mov ecx, ebp */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4147be: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4147c2: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4147c5: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4147ca: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4147cc: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4147d1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4147d4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4147d6: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4147d8: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4147da: push 0x3f800000 */
	m->esi = m->edi;	/* 4147df: mov esi, edi */
	m->ebp = m->ecx;	/* 4147e1: mov ebp, ecx */
	m->edi = m->edx;	/* 4147e3: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4147e5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4147e8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 4147ea: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4147ec: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4147ed: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4147f0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 4147f2: mov ecx, ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4147f4: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4147f9: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4147fc: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4147fd: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4147ff: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414809u; native_call(m, 0x41f0e0u);	/* 414804: call 0x41f0e0 */
	m->ebp = M32((DWORD)(m->esp + 0x2cu));	/* 414809: mov ebp, dword ptr [esp + 0x2c] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 41480d: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0x57u);	/* 414811: lea ecx, [ebx + 0x57] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414814: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414815: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 414816: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41481cu; native_call(m, 0x402620u);	/* 414817: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41481c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414821: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414826: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41482b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414830: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41483au; native_call(m, 0x41f0e0u);	/* 414835: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 41483a: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0x68u);	/* 41483e: lea edx, [ebx + 0x68] */
	{ DWORD v_ = 0x761b24u; m->esp -= 4; M32(m->esp) = v_; }	/* 414841: push 0x761b24 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414846: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414847: push eax */
	m->esp -= 4; M32(m->esp) = 0x41484du; native_call(m, 0x402620u);	/* 414848: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc234u)));	/* 41484d: fld dword ptr [0x4dc234] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 414853: fcomp dword ptr [0x4a93e8] */
	m->ecx = 0xcu;	/* 414859: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41485e: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 414860: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414864: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414867: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc234u)));	/* 414869: fld dword ptr [0x4dc234] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41486f: stosw word ptr es:[edi], ax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414871: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414873: test ah, 1 */
	if (m->zf) goto L_41488a;	/* 414876: je 0x41488a */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414878: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 41487b: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41487f: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 414882: push 0x4b02fc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414887: push ecx */
	goto L_41489a;	/* 414888: jmp 0x41489a */
L_41488a:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41488a: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41488d: lea edx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414891: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 414894: push 0x4b02c4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414899: push edx */
L_41489a:
	m->esp -= 4; M32(m->esp) = 0x41489fu; native_call(m, 0x49e9ddu);	/* 41489a: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 41489f: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4148a4: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4148a7: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4148a9: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4148ac: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4148ae: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4148b0: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4148b2: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4148b6: mov esi, edi */
	m->edi = m->edx;	/* 4148b8: mov edi, edx */
	m->edx = m->ecx;	/* 4148ba: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4148bc: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4148bf: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4148c1: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4148c3: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4148c4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4148c7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4148c9: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4148cb: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4148cf: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4148d2: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4148d7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4148d9: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4148de: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4148e1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4148e3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4148e5: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4148e7: push 0x3f800000 */
	m->esi = m->edi;	/* 4148ec: mov esi, edi */
	m->edi = m->edx;	/* 4148ee: mov edi, edx */
	m->edx = m->ecx;	/* 4148f0: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4148f2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4148f5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4148f7: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4148f9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4148fa: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4148fd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4148ff: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414901: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414906: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414909: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41490a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41490c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414916u; native_call(m, 0x41f0e0u);	/* 414911: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 414916: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0x77u);	/* 41491a: lea ecx, [ebx + 0x77] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41491d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41491e: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41491f: push ebp */
	m->esp -= 4; M32(m->esp) = 0x414925u; native_call(m, 0x402620u);	/* 414920: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414925: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41492a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41492f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414934: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414939: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414943u; native_call(m, 0x41f0e0u);	/* 41493e: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 414943: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0x88u);	/* 414947: lea edx, [ebx + 0x88] */
	{ DWORD v_ = 0x761ba4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41494d: push 0x761ba4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414952: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414953: push eax */
	m->esp -= 4; M32(m->esp) = 0x414959u; native_call(m, 0x402620u);	/* 414954: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc238u)));	/* 414959: fld dword ptr [0x4dc238] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41495f: fcomp dword ptr [0x4a93e8] */
	m->ecx = 0xcu;	/* 414965: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41496a: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 41496c: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414970: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414973: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc238u)));	/* 414975: fld dword ptr [0x4dc238] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41497b: stosw word ptr es:[edi], ax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41497d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41497f: test ah, 1 */
	if (m->zf) goto L_414996;	/* 414982: je 0x414996 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414984: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 414987: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41498b: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 41498e: push 0x4b02fc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414993: push ecx */
	goto L_4149a6;	/* 414994: jmp 0x4149a6 */
L_414996:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414996: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 414999: lea edx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41499d: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4149a0: push 0x4b02c4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4149a5: push edx */
L_4149a6:
	m->esp -= 4; M32(m->esp) = 0x4149abu; native_call(m, 0x49e9ddu);	/* 4149a6: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 4149ab: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4149b0: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4149b3: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4149b5: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4149b8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4149ba: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4149bc: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4149be: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4149c2: mov esi, edi */
	m->edi = m->edx;	/* 4149c4: mov edi, edx */
	m->edx = m->ecx;	/* 4149c6: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4149c8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4149cb: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4149cd: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4149cf: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4149d0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4149d3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4149d5: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4149d7: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4149db: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4149de: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4149e3: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4149e5: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4149ea: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4149ed: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4149ef: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4149f1: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4149f3: push 0x3f800000 */
	m->esi = m->edi;	/* 4149f8: mov esi, edi */
	m->edi = m->edx;	/* 4149fa: mov edi, edx */
	m->edx = m->ecx;	/* 4149fc: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4149fe: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414a01: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414a03: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414a05: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414a06: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414a09: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414a0b: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414a0d: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414a12: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414a15: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414a16: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414a18: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414a22u; native_call(m, 0x41f0e0u);	/* 414a1d: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 414a22: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0x97u);	/* 414a26: lea ecx, [ebx + 0x97] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414a2c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414a2d: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 414a2e: push ebp */
	m->esp -= 4; M32(m->esp) = 0x414a34u; native_call(m, 0x402620u);	/* 414a2f: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414a34: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414a39: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414a3e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414a43: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414a48: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414a52u; native_call(m, 0x41f0e0u);	/* 414a4d: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 414a52: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0xa8u);	/* 414a56: lea edx, [ebx + 0xa8] */
	{ DWORD v_ = 0x761c24u; m->esp -= 4; M32(m->esp) = v_; }	/* 414a5c: push 0x761c24 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414a61: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414a62: push eax */
	m->esp -= 4; M32(m->esp) = 0x414a68u; native_call(m, 0x402620u);	/* 414a63: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc23cu)));	/* 414a68: fld dword ptr [0x4dc23c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 414a6e: fcomp dword ptr [0x4a93e8] */
	m->ecx = 0xcu;	/* 414a74: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414a79: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 414a7b: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414a7f: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414a82: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc23cu)));	/* 414a84: fld dword ptr [0x4dc23c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414a8a: stosw word ptr es:[edi], ax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414a8c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414a8e: test ah, 1 */
	if (m->zf) goto L_414aa5;	/* 414a91: je 0x414aa5 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414a93: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 414a96: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414a9a: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 414a9d: push 0x4b02fc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414aa2: push ecx */
	goto L_414ab5;	/* 414aa3: jmp 0x414ab5 */
L_414aa5:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414aa5: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 414aa8: lea edx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414aac: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 414aaf: push 0x4b02c4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414ab4: push edx */
L_414ab5:
	m->esp -= 4; M32(m->esp) = 0x414abau; native_call(m, 0x49e9ddu);	/* 414ab5: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 414aba: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414abf: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414ac2: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414ac4: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414ac7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414ac9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414acb: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414acd: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 414ad1: mov esi, edi */
	m->edi = m->edx;	/* 414ad3: mov edi, edx */
	m->edx = m->ecx;	/* 414ad5: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414ad7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414ada: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414adc: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414ade: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414adf: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414ae2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414ae4: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414ae6: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414aea: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414aed: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414af2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 414af4: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414af9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414afc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414afe: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414b00: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b02: push 0x3f800000 */
	m->esi = m->edi;	/* 414b07: mov esi, edi */
	m->edi = m->edx;	/* 414b09: mov edi, edx */
	m->edx = m->ecx;	/* 414b0b: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414b0d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414b10: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414b12: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414b14: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414b15: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414b18: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414b1a: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b1c: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414b21: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414b24: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414b25: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b27: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414b31u; native_call(m, 0x41f0e0u);	/* 414b2c: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 414b31: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0xb7u);	/* 414b35: lea ecx, [ebx + 0xb7] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414b3b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414b3c: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 414b3d: push ebp */
	m->esp -= 4; M32(m->esp) = 0x414b43u; native_call(m, 0x402620u);	/* 414b3e: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b43: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b48: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b4d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b52: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b57: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414b61u; native_call(m, 0x41f0e0u);	/* 414b5c: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 414b61: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0xc8u);	/* 414b65: lea edx, [ebx + 0xc8] */
	{ DWORD v_ = 0x761ca4u; m->esp -= 4; M32(m->esp) = v_; }	/* 414b6b: push 0x761ca4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414b70: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414b71: push eax */
	m->esp -= 4; M32(m->esp) = 0x414b77u; native_call(m, 0x402620u);	/* 414b72: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc240u)));	/* 414b77: fld dword ptr [0x4dc240] */
	m->ecx = 0xcu;	/* 414b7d: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414b82: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 414b84: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414b88: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414b8b: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414b8d: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 414b90: lea ecx, [esp + 0x3c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414b94: stosw word ptr es:[edi], ax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414b96: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 414b99: push 0x4b02fc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414b9e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x414ba4u; native_call(m, 0x49e9ddu);	/* 414b9f: call 0x49e9dd */
	m->edi = 0x7657a4u;	/* 414ba4: mov edi, 0x7657a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414ba9: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414bac: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 414bae: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414bb2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414bb4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414bb6: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414bb8: push 0x3f800000 */
	m->esi = m->edi;	/* 414bbd: mov esi, edi */
	m->edi = m->edx;	/* 414bbf: mov edi, edx */
	m->edx = m->ecx;	/* 414bc1: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414bc3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414bc6: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414bc8: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414bca: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414bcb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414bce: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414bd0: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 414bd2: lea edx, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414bd6: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414bd9: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414bde: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 414be0: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414be5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414be8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414bea: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414bec: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414bee: push 0x3f800000 */
	m->esi = m->edi;	/* 414bf3: mov esi, edi */
	m->edi = m->edx;	/* 414bf5: mov edi, edx */
	m->edx = m->ecx;	/* 414bf7: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414bf9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414bfc: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414bfe: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414c00: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414c01: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414c04: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414c06: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414c08: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414c09: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414c0c: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414c11: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x414c18u; native_call(m, 0x41f0e0u);	/* 414c13: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 414c18: lea eax, [esp + 0x58] */
	{ DWORD a_ = m->ebx, b_ = 0xd7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 414c1c: add ebx, 0xd7 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414c22: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 414c23: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 414c24: push ebp */
	m->esp -= 4; M32(m->esp) = 0x414c2au; native_call(m, 0x402620u);	/* 414c25: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414c2a: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 414c2d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 414c2e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 414c2f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 414c30: pop ebx */
	m->esp = m->ebp;	/* 414c31: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 414c33: pop ebp */
	m->esp += 4 + 0; return;	/* 414c34: ret  */
L_414c35:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414c35: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414c3a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414c3f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414c44: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414c49: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414c53u; native_call(m, 0x41f0e0u);	/* 414c4e: call 0x41f0e0 */
	m->ecx = (DWORD)(m->ebx + 0x8u);	/* 414c53: lea ecx, [ebx + 8] */
	m->eax = (DWORD)(m->ebp + 0xau);	/* 414c56: lea eax, [ebp + 0xa] */
	{ DWORD v_ = 0x761ea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 414c59: push 0x761ea4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414c5e: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414c5f: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 414c60: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x414c69u; native_call(m, 0x402620u);	/* 414c64: call 0x402620 */
	m->ecx = 0xcu;	/* 414c69: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414c6e: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 414c70: lea edi, [esp + 0x54] */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 414c74: lea edx, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414c78: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414c7a: stosw word ptr es:[edi], ax */
	m->edi = M32((DWORD)(0x4dce80u));	/* 414c7c: mov edi, dword ptr [0x4dce80] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414c82: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 414c85: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x7623a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414c88: add edi, 0x7623a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414c8e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414c90: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414c92: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414c94: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414c96: push 0x3f800000 */
	m->esi = m->edi;	/* 414c9b: mov esi, edi */
	m->edi = m->edx;	/* 414c9d: mov edi, edx */
	m->edx = m->ecx;	/* 414c9f: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414ca1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414ca4: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414ca6: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414ca8: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414ca9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414cac: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414cae: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414cb0: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414cb5: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414cb8: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414cbd: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414cbe: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414cc3: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x414ccau; native_call(m, 0x41f0e0u);	/* 414cc5: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x68u);	/* 414cca: lea eax, [esp + 0x68] */
	m->ecx = (DWORD)(m->ebx + 0x17u);	/* 414cce: lea ecx, [ebx + 0x17] */
	m->esi = (DWORD)(m->ebp + 0x1au);	/* 414cd1: lea esi, [ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414cd4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414cd5: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 414cd6: push esi */
	M32((DWORD)(m->esp + 0x58u)) = m->esi;	/* 414cd7: mov dword ptr [esp + 0x58], esi */
	m->esp -= 4; M32(m->esp) = 0x414ce0u; native_call(m, 0x402620u);	/* 414cdb: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414ce0: add esp, 0x40 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414ce3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414ce8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414ced: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414cf2: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414cf7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414d01u; native_call(m, 0x41f0e0u);	/* 414cfc: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 414d01: mov eax, dword ptr [esp + 0x24] */
	m->edx = (DWORD)(m->ebx + 0x28u);	/* 414d05: lea edx, [ebx + 0x28] */
	{ DWORD v_ = 0x761f24u; m->esp -= 4; M32(m->esp) = v_; }	/* 414d08: push 0x761f24 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414d0d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414d0e: push eax */
	m->esp -= 4; M32(m->esp) = 0x414d14u; native_call(m, 0x402620u);	/* 414d0f: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce84u)));	/* 414d14: fld dword ptr [0x4dce84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 414d1a: fmul dword ptr [0x4a9480] */
	m->ecx = 0xcu;	/* 414d20: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414d25: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 414d27: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414d2b: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414d2e: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414d30: fstp qword ptr [esp] */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 414d33: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 414d37: push 0x4b0334 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414d3c: push ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414d3d: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x414d44u; native_call(m, 0x49e9ddu);	/* 414d3f: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414d44: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414d49: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414d4e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 414d53: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414d55: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414d5fu; native_call(m, 0x41f0e0u);	/* 414d5a: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 414d5f: lea edx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 414d63: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414d66: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414d67: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 414d68: push esi */
	m->esp -= 4; M32(m->esp) = 0x414d6eu; native_call(m, 0x402620u);	/* 414d69: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcca0u)));	/* 414d6e: fld dword ptr [0x4dcca0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce84u));	/* 414d74: fmul dword ptr [0x4dce84] */
	m->edi = (DWORD)(m->esp + 0x64u);	/* 414d7a: lea edi, [esp + 0x64] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414d7e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414d81: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414d83: add esp, 0x30 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 414d86: fmul dword ptr [0x4a9480] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414d8c: repne scasb al, byte ptr es:[edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 414d8e: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414d94: fnstsw ax */
	m->ecx = ~m->ecx;	/* 414d96: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 414d98: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414d99: shl ecx, 3 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414d9c: test ah, 0x40 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 414d9f: mov dword ptr [esp + 0x14], ecx */
	if (!m->zf) goto L_414e73;	/* 414da3: jne 0x414e73 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 414da9: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414daf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414db1: test ah, 1 */
	if (m->zf) goto L_414dc8;	/* 414db4: je 0x414dc8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414db6: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 414db9: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414dbd: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b032cu; m->esp -= 4; M32(m->esp) = v_; }	/* 414dc0: push 0x4b032c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414dc5: push eax */
	goto L_414dd8;	/* 414dc6: jmp 0x414dd8 */
L_414dc8:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414dc8: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 414dcb: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414dcf: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0324u; m->esp -= 4; M32(m->esp) = v_; }	/* 414dd2: push 0x4b0324 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414dd7: push ecx */
L_414dd8:
	m->esp -= 4; M32(m->esp) = 0x414dddu; native_call(m, 0x49e9ddu);	/* 414dd8: call 0x49e9dd */
	m->edi = 0x765aa4u;	/* 414ddd: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414de2: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414de5: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414de7: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414dea: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414dec: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414dee: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414df0: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 414df4: mov esi, edi */
	m->edi = m->edx;	/* 414df6: mov edi, edx */
	m->edx = m->ecx;	/* 414df8: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414dfa: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414dfd: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414dff: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414e01: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414e02: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414e05: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414e07: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414e09: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414e0d: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414e10: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414e15: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 414e17: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414e1c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414e1f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414e21: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414e23: sub edi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414e25: push eax */
	m->esi = m->edi;	/* 414e26: mov esi, edi */
	m->edi = m->edx;	/* 414e28: mov edi, edx */
	m->edx = m->ecx;	/* 414e2a: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414e2c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414e2f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414e31: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414e33: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414e34: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414e37: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414e39: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414e3b: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414e40: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414e43: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414e48: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414e4a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414e54u; native_call(m, 0x41f0e0u);	/* 414e4f: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 414e54: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 414e58: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414e5c: push eax */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 414e5d: lea eax, [ebx + 0x37] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 414e60: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414e64: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414e65: push edx */
	m->esp -= 4; M32(m->esp) = 0x414e6bu; native_call(m, 0x402620u);	/* 414e66: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414e6b: add esp, 0x20 */
	goto L_414f0f;	/* 414e6e: jmp 0x414f0f */
L_414e73:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414e73: or ecx, 0xffffffff */
	m->edi = 0x4b033cu;	/* 414e76: mov edi, 0x4b033c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414e7b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414e7d: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414e81: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 414e83: fstp st(0) */
	m->ecx = ~m->ecx;	/* 414e85: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414e87: sub edi, ecx */
	m->eax = m->ecx;	/* 414e89: mov eax, ecx */
	m->esi = m->edi;	/* 414e8b: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414e8d: shr ecx, 2 */
	m->edi = m->edx;	/* 414e90: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414e92: lea edx, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414e96: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 414e98: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414e9a: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414e9c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414e9f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x765aa4u;	/* 414ea1: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414ea6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414ea9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414eab: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414ead: sub edi, ecx */
	m->esi = m->edi;	/* 414eaf: mov esi, edi */
	m->edi = m->edx;	/* 414eb1: mov edi, edx */
	m->edx = m->ecx;	/* 414eb3: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414eb5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414eb8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414eba: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414ebc: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414ebd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414ec0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414ec2: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 414ec4: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414ec8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414ecb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 414ecd: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414ed2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414ed5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 414ed7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 414ed9: sub edi, ecx */
	m->esi = m->edi;	/* 414edb: mov esi, edi */
	m->edi = m->edx;	/* 414edd: mov edi, edx */
	m->edx = m->ecx;	/* 414edf: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414ee1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414ee4: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 414ee6: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 414ee8: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414ee9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 414eec: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 414eee: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 414ef0: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414ef4: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414ef7: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 414ef8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 414efa: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 414efe: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414f01: push eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 414f02: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414f06: push edx */
	m->esp -= 4; M32(m->esp) = 0x414f0cu; native_call(m, 0x402620u);	/* 414f07: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414f0c: add esp, 0xc */
L_414f0f:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f0f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f14: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f19: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f1e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f23: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414f2du; native_call(m, 0x41f0e0u);	/* 414f28: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 414f2d: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 414f31: lea eax, [ebx + 0x48] */
	{ DWORD v_ = 0x761fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f34: push 0x761fa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414f39: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414f3a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x414f40u; native_call(m, 0x402620u);	/* 414f3b: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce88u)));	/* 414f40: fld dword ptr [0x4dce88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 414f46: fmul dword ptr [0x4a9480] */
	m->ecx = 0xcu;	/* 414f4c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414f51: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 414f53: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414f57: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 414f5a: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414f5c: fstp qword ptr [esp] */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 414f5f: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f63: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414f68: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 414f69: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x414f70u; native_call(m, 0x49e9ddu);	/* 414f6b: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f70: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f75: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f7a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f7f: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 414f81: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x414f8bu; native_call(m, 0x41f0e0u);	/* 414f86: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 414f8b: mov edx, dword ptr [esp + 0x3c] */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 414f8f: lea ecx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x57u);	/* 414f93: lea eax, [ebx + 0x57] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 414f96: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414f97: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 414f98: push edx */
	m->esp -= 4; M32(m->esp) = 0x414f9eu; native_call(m, 0x402620u);	/* 414f99: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce88u)));	/* 414f9e: fld dword ptr [0x4dce88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc894u));	/* 414fa4: fmul dword ptr [0x4dc894] */
	m->edi = (DWORD)(m->esp + 0x64u);	/* 414faa: lea edi, [esp + 0x64] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 414fae: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 414fb1: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414fb3: add esp, 0x30 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 414fb6: fmul dword ptr [0x4a9480] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 414fbc: repne scasb al, byte ptr es:[edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 414fbe: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414fc4: fnstsw ax */
	m->ecx = ~m->ecx;	/* 414fc6: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 414fc8: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 414fc9: shl ecx, 3 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414fcc: test ah, 0x40 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 414fcf: mov dword ptr [esp + 0x14], ecx */
	if (!m->zf) goto L_4150a3;	/* 414fd3: jne 0x4150a3 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 414fd9: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 414fdf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 414fe1: test ah, 1 */
	if (m->zf) goto L_414ff8;	/* 414fe4: je 0x414ff8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414fe6: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 414fe9: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414fed: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b032cu; m->esp -= 4; M32(m->esp) = v_; }	/* 414ff0: push 0x4b032c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 414ff5: push eax */
	goto L_415008;	/* 414ff6: jmp 0x415008 */
L_414ff8:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 414ff8: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 414ffb: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 414fff: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0324u; m->esp -= 4; M32(m->esp) = v_; }	/* 415002: push 0x4b0324 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415007: push ecx */
L_415008:
	m->esp -= 4; M32(m->esp) = 0x41500du; native_call(m, 0x49e9ddu);	/* 415008: call 0x49e9dd */
	m->edi = 0x765aa4u;	/* 41500d: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415012: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415015: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415017: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41501a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41501c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41501e: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 415020: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 415024: mov esi, edi */
	m->edi = m->edx;	/* 415026: mov edi, edx */
	m->edx = m->ecx;	/* 415028: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41502a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41502d: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41502f: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415031: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415032: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415035: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415037: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 415039: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41503d: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415040: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415045: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 415047: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41504c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41504f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415051: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415053: sub edi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415055: push eax */
	m->esi = m->edi;	/* 415056: mov esi, edi */
	m->edi = m->edx;	/* 415058: mov edi, edx */
	m->edx = m->ecx;	/* 41505a: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41505c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41505f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415061: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415063: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415064: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415067: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415069: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41506b: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415070: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415073: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415078: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41507a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415084u; native_call(m, 0x41f0e0u);	/* 41507f: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 415084: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 415088: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41508c: push eax */
	m->eax = (DWORD)(m->ebx + 0x57u);	/* 41508d: lea eax, [ebx + 0x57] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 415090: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415094: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415095: push edx */
	m->esp -= 4; M32(m->esp) = 0x41509bu; native_call(m, 0x402620u);	/* 415096: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41509b: add esp, 0x20 */
	goto L_41513f;	/* 41509e: jmp 0x41513f */
L_4150a3:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4150a3: or ecx, 0xffffffff */
	m->edi = 0x4b033cu;	/* 4150a6: mov edi, 0x4b033c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4150ab: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4150ad: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4150b1: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4150b3: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4150b5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4150b7: sub edi, ecx */
	m->eax = m->ecx;	/* 4150b9: mov eax, ecx */
	m->esi = m->edi;	/* 4150bb: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4150bd: shr ecx, 2 */
	m->edi = m->edx;	/* 4150c0: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4150c2: lea edx, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4150c6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4150c8: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4150ca: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4150cc: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4150cf: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x765aa4u;	/* 4150d1: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4150d6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4150d9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4150db: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4150dd: sub edi, ecx */
	m->esi = m->edi;	/* 4150df: mov esi, edi */
	m->edi = m->edx;	/* 4150e1: mov edi, edx */
	m->edx = m->ecx;	/* 4150e3: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4150e5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4150e8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4150ea: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4150ec: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4150ed: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4150f0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4150f2: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4150f4: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4150f8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4150fb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4150fd: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415102: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415105: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415107: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415109: sub edi, ecx */
	m->esi = m->edi;	/* 41510b: mov esi, edi */
	m->edi = m->edx;	/* 41510d: mov edi, edx */
	m->edx = m->ecx;	/* 41510f: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415111: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415114: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415116: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415118: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415119: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41511c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41511e: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 415120: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415124: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415127: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415128: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 41512a: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->ebx + 0x57u);	/* 41512e: lea eax, [ebx + 0x57] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415131: push eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 415132: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415136: push edx */
	m->esp -= 4; M32(m->esp) = 0x41513cu; native_call(m, 0x402620u);	/* 415137: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41513c: add esp, 0xc */
L_41513f:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41513f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415144: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415149: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41514e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415153: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41515du; native_call(m, 0x41f0e0u);	/* 415158: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 41515d: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x68u);	/* 415161: lea eax, [ebx + 0x68] */
	{ DWORD v_ = 0x762024u; m->esp -= 4; M32(m->esp) = v_; }	/* 415164: push 0x762024 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415169: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41516a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x415170u; native_call(m, 0x402620u);	/* 41516b: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce8cu)));	/* 415170: fld dword ptr [0x4dce8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 415176: fmul dword ptr [0x4a9480] */
	m->ecx = 0xcu;	/* 41517c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415181: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 415183: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415187: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41518a: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41518c: fstp qword ptr [esp] */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41518f: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 415193: push 0x4b02fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415198: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415199: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x4151a0u; native_call(m, 0x49e9ddu);	/* 41519b: call 0x49e9dd */
	m->edi = 0x765aa4u;	/* 4151a0: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4151a5: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4151a8: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 4151aa: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4151ae: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4151b0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4151b2: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4151b4: push 0x3f800000 */
	m->esi = m->edi;	/* 4151b9: mov esi, edi */
	m->edi = m->edx;	/* 4151bb: mov edi, edx */
	m->edx = m->ecx;	/* 4151bd: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4151bf: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4151c2: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4151c4: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4151c6: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4151c7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4151ca: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4151cc: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 4151ce: lea edx, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4151d2: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4151d5: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4151da: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4151dc: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4151e1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4151e4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4151e6: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4151e8: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4151ea: push 0x3f800000 */
	m->esi = m->edi;	/* 4151ef: mov esi, edi */
	m->edi = m->edx;	/* 4151f1: mov edi, edx */
	m->edx = m->ecx;	/* 4151f3: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4151f5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4151f8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4151fa: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4151fc: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4151fd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415200: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415202: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415204: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415205: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415208: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41520d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x415214u; native_call(m, 0x41f0e0u);	/* 41520f: call 0x41f0e0 */
	m->esi = M32((DWORD)(m->esp + 0x3cu));	/* 415214: mov esi, dword ptr [esp + 0x3c] */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 415218: lea eax, [esp + 0x58] */
	m->ecx = (DWORD)(m->ebx + 0x77u);	/* 41521c: lea ecx, [ebx + 0x77] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41521f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415220: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 415221: push esi */
	m->esp -= 4; M32(m->esp) = 0x415227u; native_call(m, 0x402620u);	/* 415222: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415227: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41522c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415231: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415236: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41523b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415245u; native_call(m, 0x41f0e0u);	/* 415240: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 415245: mov eax, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415249: add esp, 0x44 */
	m->edx = (DWORD)(m->ebx + 0x88u);	/* 41524c: lea edx, [ebx + 0x88] */
	{ DWORD v_ = 0x7620a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 415252: push 0x7620a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415257: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415258: push eax */
	m->esp -= 4; M32(m->esp) = 0x41525eu; native_call(m, 0x402620u);	/* 415259: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce90u)));	/* 41525e: fld dword ptr [0x4dce90] */
	m->ecx = 0xcu;	/* 415264: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415269: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x4u)) = (double)ST(0); FPOP();	/* 41526b: fstp qword ptr [esp + 4] */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 41526f: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415273: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415276: rep stosd dword ptr es:[edi], eax */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 415278: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 41527c: push 0x4b0354 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415281: push ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415282: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x415289u; native_call(m, 0x49e9ddu);	/* 415284: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415289: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41528e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415293: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 415298: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41529a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4152a4u; native_call(m, 0x41f0e0u);	/* 41529f: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 4152a4: lea edx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x97u);	/* 4152a8: lea eax, [ebx + 0x97] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4152ae: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4152af: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4152b0: push esi */
	m->esp -= 4; M32(m->esp) = 0x4152b6u; native_call(m, 0x402620u);	/* 4152b1: call 0x402620 */
	m->eax = M32((DWORD)(0x9f1818u));	/* 4152b6: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4152bb: add esp, 0x30 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4152be: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4152c1: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f907cu)));	/* 4152c4: fild dword ptr [edx*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4152cb: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce90u));	/* 4152d1: fmul dword ptr [0x4dce90] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc230u)));	/* 4152d7: fld dword ptr [0x4dc230] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4152dd: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce90u));	/* 4152e3: fmul dword ptr [0x4dce90] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4152e9: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 4152eb: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 4152f1: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4152f7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4152f9: test ah, 0x41 */
	if (!m->zf) goto L_415324;	/* 4152fc: jne 0x415324 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 4152fe: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 415304: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 41530a: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 415310: fmul dword ptr [0x4a947c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce90u)));	/* 415316: fld dword ptr [0x4dce90] */
	ST(0) = ST(0) + ST(2);	/* 41531c: fadd st(2) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 41531e: fmulp st(1) */
	ST(0) = -ST(0);	/* 415320: fchs  */
	goto L_41532a;	/* 415322: jmp 0x41532a */
L_415324:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 415324: fld dword ptr [0x4a93e8] */
L_41532a:
	m->edi = (DWORD)(m->esp + 0x34u);	/* 41532a: lea edi, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41532e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415331: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415333: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0) + ST(1);	/* 415335: fadd st(1) */
	m->ecx = ~m->ecx;	/* 415337: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 415339: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41533a: shl ecx, 3 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 41533d: mov dword ptr [esp + 0x14], ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 415341: call 0x49ec14 */
	ST(0) = ST(0); FPOP();	/* 415346: fstp st(0) */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 415348: mov dword ptr [esp + 0x1c], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 41534c: fild dword ptr [esp + 0x1c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 415350: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 415356: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 415358: test ah, 0x40 */
	if (!m->zf) goto L_415446;	/* 41535b: jne 0x415446 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 415361: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 415367: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 415369: test ah, 1 */
	if (m->zf) goto L_41539b;	/* 41536c: je 0x41539b */
	{ long double t = ST(0); FPUSH(t); }	/* 41536e: fld st(0) */
	ST(0) = -ST(0);	/* 415370: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dce90u)); FPOP();	/* 415372: fcomp dword ptr [0x4dce90] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 415378: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41537a: test ah, 0x41 */
	if (!m->zf) goto L_415389;	/* 41537d: jne 0x415389 */
	ST(0) = ST(0); FPOP();	/* 41537f: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce90u)));	/* 415381: fld dword ptr [0x4dce90] */
	ST(0) = -ST(0);	/* 415387: fchs  */
L_415389:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415389: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41538c: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 415390: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b034cu; m->esp -= 4; M32(m->esp) = v_; }	/* 415393: push 0x4b034c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415398: push eax */
	goto L_4153ab;	/* 415399: jmp 0x4153ab */
L_41539b:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41539b: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 41539e: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4153a2: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0344u; m->esp -= 4; M32(m->esp) = v_; }	/* 4153a5: push 0x4b0344 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4153aa: push ecx */
L_4153ab:
	m->esp -= 4; M32(m->esp) = 0x4153b0u; native_call(m, 0x49e9ddu);	/* 4153ab: call 0x49e9dd */
	m->edi = 0x7658a4u;	/* 4153b0: mov edi, 0x7658a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4153b5: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4153b8: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4153ba: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4153bd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4153bf: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4153c1: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4153c3: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4153c7: mov esi, edi */
	m->edi = m->edx;	/* 4153c9: mov edi, edx */
	m->edx = m->ecx;	/* 4153cb: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4153cd: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4153d0: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4153d2: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4153d4: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4153d5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4153d8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4153da: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4153dc: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4153e0: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4153e3: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4153e8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4153ea: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4153ef: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4153f2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4153f4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4153f6: sub edi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4153f8: push eax */
	m->esi = m->edi;	/* 4153f9: mov esi, edi */
	m->edi = m->edx;	/* 4153fb: mov edi, edx */
	m->edx = m->ecx;	/* 4153fd: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4153ff: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415402: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415404: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415406: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415407: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41540a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41540c: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41540e: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415413: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415416: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41541b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41541d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415427u; native_call(m, 0x41f0e0u);	/* 415422: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 415427: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 41542b: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41542f: push eax */
	m->eax = (DWORD)(m->ebx + 0x97u);	/* 415430: lea eax, [ebx + 0x97] */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x1au);	/* 415436: lea edx, [ecx + ebp + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41543a: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41543b: push edx */
	m->esp -= 4; M32(m->esp) = 0x415441u; native_call(m, 0x402620u);	/* 41543c: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415441: add esp, 0x20 */
	goto L_415448;	/* 415444: jmp 0x415448 */
L_415446:
	ST(0) = ST(0); FPOP();	/* 415446: fstp st(0) */
L_415448:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415448: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41544d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415452: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415457: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41545c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415466u; native_call(m, 0x41f0e0u);	/* 415461: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 415466: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0xa8u);	/* 41546a: lea eax, [ebx + 0xa8] */
	{ DWORD v_ = 0x762124u; m->esp -= 4; M32(m->esp) = v_; }	/* 415470: push 0x762124 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415475: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415476: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41547cu; native_call(m, 0x402620u);	/* 415477: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce94u)));	/* 41547c: fld dword ptr [0x4dce94] */
	m->ecx = 0xcu;	/* 415482: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415487: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 415489: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 41548d: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415491: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415494: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 415496: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0x4b02bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 41549a: push 0x4b02bc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41549f: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4154a0: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x4154a7u; native_call(m, 0x49e9ddu);	/* 4154a2: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 4154a7: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4154ab: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4154ae: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 4154b0: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4154b4: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce9cu)));	/* 4154b6: fld dword ptr [0x4dce9c] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 4154bc: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 4154c0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4154c2: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4154c4: add esp, 8 */
	m->esi = m->edi;	/* 4154c7: mov esi, edi */
	m->edi = m->edx;	/* 4154c9: mov edi, edx */
	m->edx = m->ecx;	/* 4154cb: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4154cd: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4154d0: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4154d2: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4154d4: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4154d5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4154d8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4154da: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4154dc: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4154e0: and ecx, 3 */
	{ DWORD v_ = 0x4b02b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4154e3: push 0x4b02b4 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4154e8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4154ea: push eax */
	m->esp -= 4; M32(m->esp) = 0x4154f0u; native_call(m, 0x49e9ddu);	/* 4154eb: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 4154f0: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4154f4: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4154f7: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 4154f9: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4154fd: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce98u)));	/* 4154ff: fld dword ptr [0x4dce98] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 415505: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 415509: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41550b: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41550d: add esp, 8 */
	m->esi = m->edi;	/* 415510: mov esi, edi */
	m->edi = m->edx;	/* 415512: mov edi, edx */
	m->edx = m->ecx;	/* 415514: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415516: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415519: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41551b: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41551d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41551e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415521: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415523: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 415525: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415529: and ecx, 3 */
	{ DWORD v_ = 0x4b02a8u; m->esp -= 4; M32(m->esp) = v_; }	/* 41552c: push 0x4b02a8 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415531: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415533: push eax */
	m->esp -= 4; M32(m->esp) = 0x415539u; native_call(m, 0x49e9ddu);	/* 415534: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 415539: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41553d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415540: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 415542: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415546: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415548: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41554a: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41554c: push 0x3f800000 */
	m->esi = m->edi;	/* 415551: mov esi, edi */
	m->edi = m->edx;	/* 415553: mov edi, edx */
	m->edx = m->ecx;	/* 415555: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415557: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41555a: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41555c: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41555e: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41555f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415562: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415564: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415566: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41556b: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41556e: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415573: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415574: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415579: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x415580u; native_call(m, 0x41f0e0u);	/* 41557b: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 415580: mov edx, dword ptr [esp + 0x3c] */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 415584: lea eax, [esp + 0x58] */
	m->ecx = (DWORD)(m->ebx + 0xb7u);	/* 415588: lea ecx, [ebx + 0xb7] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41558e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41558f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415590: push edx */
	m->esp -= 4; M32(m->esp) = 0x415596u; native_call(m, 0x402620u);	/* 415591: call 0x402620 */
	m->eax = M32((DWORD)(0x9f1818u));	/* 415596: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41559b: add esp, 0x30 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 41559e: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4155a1: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f907cu)));	/* 4155a4: fild dword ptr [edx*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4155ab: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce94u));	/* 4155b1: fmul dword ptr [0x4dce94] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc234u)));	/* 4155b7: fld dword ptr [0x4dc234] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4155bd: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce94u));	/* 4155c3: fmul dword ptr [0x4dce94] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4155c9: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 4155cb: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 4155d1: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4155d7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4155d9: test ah, 0x41 */
	if (!m->zf) goto L_415604;	/* 4155dc: jne 0x415604 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 4155de: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4155e4: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4155ea: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 4155f0: fmul dword ptr [0x4a947c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce94u)));	/* 4155f6: fld dword ptr [0x4dce94] */
	ST(0) = ST(0) + ST(2);	/* 4155fc: fadd st(2) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 4155fe: fmulp st(1) */
	ST(0) = -ST(0);	/* 415600: fchs  */
	goto L_41560a;	/* 415602: jmp 0x41560a */
L_415604:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 415604: fld dword ptr [0x4a93e8] */
L_41560a:
	ST(1) = ST(1) + ST(0); FPOP();	/* 41560a: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41560c: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 415612: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 415614: test ah, 1 */
	if (m->zf) goto L_415642;	/* 415617: je 0x415642 */
	ST(0) = -ST(0);	/* 415619: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dce94u));	/* 41561b: fcom dword ptr [0x4dce94] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 415621: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 415623: test ah, 0x41 */
	if (!m->zf) goto L_415630;	/* 415626: jne 0x415630 */
	ST(0) = ST(0); FPOP();	/* 415628: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce94u)));	/* 41562a: fld dword ptr [0x4dce94] */
L_415630:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415630: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 415633: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 415637: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41563a: push 0x4b02a0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41563f: push eax */
	goto L_415652;	/* 415640: jmp 0x415652 */
L_415642:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415642: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 415645: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 415649: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0298u; m->esp -= 4; M32(m->esp) = v_; }	/* 41564c: push 0x4b0298 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415651: push ecx */
L_415652:
	m->esp -= 4; M32(m->esp) = 0x415657u; native_call(m, 0x49e9ddu);	/* 415652: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 415657: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41565c: add esp, 0x10 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 41565f: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 415662: lea eax, [eax + edx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 415665: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41566c: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce9cu));	/* 415672: fmul dword ptr [0x4dce9c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc238u)));	/* 415678: fld dword ptr [0x4dc238] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41567e: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce9cu));	/* 415684: fmul dword ptr [0x4dce9c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 41568a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41568c: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 415692: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 415698: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41569a: test ah, 0x41 */
	if (!m->zf) goto L_4156c5;	/* 41569d: jne 0x4156c5 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41569f: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4156a5: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4156ab: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 4156b1: fmul dword ptr [0x4a947c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce9cu)));	/* 4156b7: fld dword ptr [0x4dce9c] */
	ST(0) = ST(0) + ST(2);	/* 4156bd: fadd st(2) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 4156bf: fmulp st(1) */
	ST(0) = -ST(0);	/* 4156c1: fchs  */
	goto L_4156cb;	/* 4156c3: jmp 0x4156cb */
L_4156c5:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 4156c5: fld dword ptr [0x4a93e8] */
L_4156cb:
	ST(1) = ST(1) + ST(0); FPOP();	/* 4156cb: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4156cd: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4156d3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4156d5: test ah, 1 */
	if (m->zf) goto L_415703;	/* 4156d8: je 0x415703 */
	ST(0) = -ST(0);	/* 4156da: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dce9cu));	/* 4156dc: fcom dword ptr [0x4dce9c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4156e2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4156e4: test ah, 0x41 */
	if (!m->zf) goto L_4156f1;	/* 4156e7: jne 0x4156f1 */
	ST(0) = ST(0); FPOP();	/* 4156e9: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce9cu)));	/* 4156eb: fld dword ptr [0x4dce9c] */
L_4156f1:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4156f1: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 4156f4: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4156f8: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4156fb: push 0x4b02a0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415700: push ecx */
	goto L_415713;	/* 415701: jmp 0x415713 */
L_415703:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415703: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 415706: lea edx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41570a: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0298u; m->esp -= 4; M32(m->esp) = v_; }	/* 41570d: push 0x4b0298 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415712: push edx */
L_415713:
	m->esp -= 4; M32(m->esp) = 0x415718u; native_call(m, 0x49e9ddu);	/* 415713: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 415718: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41571c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41571f: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415721: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415724: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415726: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415728: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41572a: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 41572e: mov esi, edi */
	m->edi = m->edx;	/* 415730: mov edi, edx */
	m->edx = m->ecx;	/* 415732: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415734: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415737: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415739: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41573b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41573c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41573f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f1818u));	/* 415741: mov eax, dword ptr [0x9f1818] */
	m->ecx = m->edx;	/* 415746: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415748: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41574b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 41574d: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 415750: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f907cu)));	/* 415753: fild dword ptr [edx*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41575a: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce98u));	/* 415760: fmul dword ptr [0x4dce98] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc23cu)));	/* 415766: fld dword ptr [0x4dc23c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41576c: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce98u));	/* 415772: fmul dword ptr [0x4dce98] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 415778: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41577a: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 415780: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 415786: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 415788: test ah, 0x41 */
	if (!m->zf) goto L_4157b3;	/* 41578b: jne 0x4157b3 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41578d: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 415793: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 415799: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 41579f: fmul dword ptr [0x4a947c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce98u)));	/* 4157a5: fld dword ptr [0x4dce98] */
	ST(0) = ST(0) + ST(2);	/* 4157ab: fadd st(2) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 4157ad: fmulp st(1) */
	ST(0) = -ST(0);	/* 4157af: fchs  */
	goto L_4157b9;	/* 4157b1: jmp 0x4157b9 */
L_4157b3:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 4157b3: fld dword ptr [0x4a93e8] */
L_4157b9:
	ST(1) = ST(1) + ST(0); FPOP();	/* 4157b9: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4157bb: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4157c1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4157c3: test ah, 1 */
	if (m->zf) goto L_4157f1;	/* 4157c6: je 0x4157f1 */
	ST(0) = -ST(0);	/* 4157c8: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dce98u));	/* 4157ca: fcom dword ptr [0x4dce98] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4157d0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4157d2: test ah, 0x41 */
	if (!m->zf) goto L_4157df;	/* 4157d5: jne 0x4157df */
	ST(0) = ST(0); FPOP();	/* 4157d7: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce98u)));	/* 4157d9: fld dword ptr [0x4dce98] */
L_4157df:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4157df: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4157e2: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4157e6: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0290u; m->esp -= 4; M32(m->esp) = v_; }	/* 4157e9: push 0x4b0290 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4157ee: push eax */
	goto L_415801;	/* 4157ef: jmp 0x415801 */
L_4157f1:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4157f1: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 4157f4: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4157f8: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0288u; m->esp -= 4; M32(m->esp) = v_; }	/* 4157fb: push 0x4b0288 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415800: push ecx */
L_415801:
	m->esp -= 4; M32(m->esp) = 0x415806u; native_call(m, 0x49e9ddu);	/* 415801: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 415806: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41580a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41580d: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41580f: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415812: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415814: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415816: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 415818: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 41581c: mov esi, edi */
	m->edi = m->edx;	/* 41581e: mov edi, edx */
	m->edx = m->ecx;	/* 415820: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415822: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415825: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415827: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415829: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41582a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41582d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41582f: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415831: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415836: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415837: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41583a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41583f: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415844: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415846: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415850u; native_call(m, 0x41f0e0u);	/* 41584b: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 415850: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0xc6u);	/* 415854: lea ecx, [ebx + 0xc6] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41585a: push eax */
	{ DWORD a_ = m->ebp, b_ = 0x12u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 41585b: add ebp, 0x12 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41585e: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41585f: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415865u; native_call(m, 0x402620u);	/* 415860: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415865: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41586a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41586f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415874: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415879: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415883u; native_call(m, 0x41f0e0u);	/* 41587e: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 415883: mov eax, dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->ebx + 0xd8u);	/* 415887: lea edx, [ebx + 0xd8] */
	{ DWORD v_ = 0x7621a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41588d: push 0x7621a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415892: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415893: push eax */
	m->esp -= 4; M32(m->esp) = 0x415899u; native_call(m, 0x402620u);	/* 415894: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcea0u)));	/* 415899: fld dword ptr [0x4dcea0] */
	m->ecx = 0xcu;	/* 41589f: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4158a4: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 4158a6: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4158aa: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4158ad: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4158af: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 4158b2: lea ecx, [esp + 0x3c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4158b6: stosw word ptr es:[edi], ax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4158b8: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b027cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4158bb: push 0x4b027c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4158c0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4158c6u; native_call(m, 0x49e9ddu);	/* 4158c1: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4158c6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4158cb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4158d0: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4158d5: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4158d7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4158e1u; native_call(m, 0x41f0e0u);	/* 4158dc: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 4158e1: mov eax, dword ptr [esp + 0x3c] */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 4158e5: lea edx, [esp + 0x58] */
	{ DWORD a_ = m->ebx, b_ = 0xe7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4158e9: add ebx, 0xe7 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4158ef: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4158f0: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4158f1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4158f7u; native_call(m, 0x402620u);	/* 4158f2: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4158f7: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4158fa: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4158fb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4158fc: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4158fd: pop ebx */
	m->esp = m->ebp;	/* 4158fe: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 415900: pop ebp */
	m->esp += 4 + 0; return;	/* 415901: ret  */
L_415902:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415902: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415907: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41590c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415911: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415916: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415920u; native_call(m, 0x41f0e0u);	/* 41591b: call 0x41f0e0 */
	m->ecx = (DWORD)(m->ebx + 0x8u);	/* 415920: lea ecx, [ebx + 8] */
	m->esi = (DWORD)(m->ebp + 0xau);	/* 415923: lea esi, [ebp + 0xa] */
	{ DWORD v_ = 0x762da4u; m->esp -= 4; M32(m->esp) = v_; }	/* 415926: push 0x762da4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41592b: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41592c: push esi */
	M32((DWORD)(m->esp + 0x30u)) = m->esi;	/* 41592d: mov dword ptr [esp + 0x30], esi */
	m->esp -= 4; M32(m->esp) = 0x415936u; native_call(m, 0x402620u);	/* 415931: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcaa0u)));	/* 415936: fld dword ptr [0x4dcaa0] */
	m->ecx = 0xcu;	/* 41593c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415941: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 415943: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 415947: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41594b: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41594e: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 415950: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0274u; m->esp -= 4; M32(m->esp) = v_; }	/* 415954: push 0x4b0274 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415959: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41595a: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x415961u; native_call(m, 0x49e9ddu);	/* 41595c: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415961: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415966: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41596b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 415970: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415972: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41597cu; native_call(m, 0x41f0e0u);	/* 415977: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 41597c: lea eax, [esp + 0x58] */
	m->ecx = (DWORD)(m->ebx + 0x17u);	/* 415980: lea ecx, [ebx + 0x17] */
	{ DWORD a_ = m->ebp, b_ = 0x1au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 415983: add ebp, 0x1a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415986: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415987: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415988: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41598eu; native_call(m, 0x402620u);	/* 415989: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41598e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415993: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415998: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41599d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4159a2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4159acu; native_call(m, 0x41f0e0u);	/* 4159a7: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4159ac: add esp, 0x44 */
	m->edx = (DWORD)(m->ebx + 0x28u);	/* 4159af: lea edx, [ebx + 0x28] */
	{ DWORD v_ = 0x762e24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4159b2: push 0x762e24 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4159b7: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4159b8: push esi */
	m->esp -= 4; M32(m->esp) = 0x4159beu; native_call(m, 0x402620u);	/* 4159b9: call 0x402620 */
	m->ecx = 0xcu;	/* 4159be: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4159c3: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 4159c5: lea edi, [esp + 0x40] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4159c9: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4159cb: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dcaa8u));	/* 4159cd: mov eax, dword ptr [0x4dcaa8] */
	m->ecx = (DWORD)(m->esp + 0x40u);	/* 4159d2: lea ecx, [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4159d6: push eax */
	{ DWORD v_ = 0x4b02e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4159d7: push 0x4b02e8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4159dc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4159e2u; native_call(m, 0x49e9ddu);	/* 4159dd: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4159e2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4159e7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4159ec: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4159f1: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4159f3: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4159fdu; native_call(m, 0x41f0e0u);	/* 4159f8: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x60u);	/* 4159fd: lea edx, [esp + 0x60] */
	m->eax = (DWORD)(m->ebx + 0x37u);	/* 415a01: lea eax, [ebx + 0x37] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415a04: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415a05: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415a06: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415a0cu; native_call(m, 0x402620u);	/* 415a07: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a0c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a11: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a16: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a1b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a20: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415a2au; native_call(m, 0x41f0e0u);	/* 415a25: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415a2a: add esp, 0x4c */
	{ DWORD v_ = 0x762ea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a2d: push 0x762ea4 */
	m->ecx = (DWORD)(m->ebx + 0x48u);	/* 415a32: lea ecx, [ebx + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415a35: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 415a36: push esi */
	m->esp -= 4; M32(m->esp) = 0x415a3cu; native_call(m, 0x402620u);	/* 415a37: call 0x402620 */
	m->ecx = 0xcu;	/* 415a3c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415a41: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 415a43: lea edi, [esp + 0x40] */
	m->edx = M32((DWORD)(0x4dcab4u));	/* 415a47: mov edx, dword ptr [0x4dcab4] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415a4d: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415a4f: stosw word ptr es:[edi], ax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415a51: push edx */
	m->eax = (DWORD)(m->esp + 0x44u);	/* 415a52: lea eax, [esp + 0x44] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a56: push 0x4b0320 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415a5b: push eax */
	m->esp -= 4; M32(m->esp) = 0x415a61u; native_call(m, 0x49e9ddu);	/* 415a5c: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a61: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a66: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a6b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a70: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a72: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415a7cu; native_call(m, 0x41f0e0u);	/* 415a77: call 0x41f0e0 */
	m->ecx = (DWORD)(m->esp + 0x60u);	/* 415a7c: lea ecx, [esp + 0x60] */
	m->edx = (DWORD)(m->ebx + 0x57u);	/* 415a80: lea edx, [ebx + 0x57] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415a83: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415a84: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415a85: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415a8bu; native_call(m, 0x402620u);	/* 415a86: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a8b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a90: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a95: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a9a: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415a9f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415aa9u; native_call(m, 0x41f0e0u);	/* 415aa4: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415aa9: add esp, 0x4c */
	m->eax = (DWORD)(m->ebx + 0x68u);	/* 415aac: lea eax, [ebx + 0x68] */
	{ DWORD v_ = 0x762f24u; m->esp -= 4; M32(m->esp) = v_; }	/* 415aaf: push 0x762f24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415ab4: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 415ab5: push esi */
	m->esp -= 4; M32(m->esp) = 0x415abbu; native_call(m, 0x402620u);	/* 415ab6: call 0x402620 */
	m->ecx = 0xcu;	/* 415abb: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415ac0: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 415ac2: lea edi, [esp + 0x40] */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 415ac6: lea edx, [esp + 0x40] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415aca: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dcab8u));	/* 415acc: mov ecx, dword ptr [0x4dcab8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415ad2: push ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 415ad3: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415ad8: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415ad9: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x415ae0u; native_call(m, 0x49e9ddu);	/* 415adb: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415ae0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415ae5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415aea: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 415aef: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415af1: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415afbu; native_call(m, 0x41f0e0u);	/* 415af6: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 415afb: lea eax, [esp + 0x60] */
	m->ecx = (DWORD)(m->ebx + 0x77u);	/* 415aff: lea ecx, [ebx + 0x77] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415b02: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415b03: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415b04: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415b0au; native_call(m, 0x402620u);	/* 415b05: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b0a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b0f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b14: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b19: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b1e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415b28u; native_call(m, 0x41f0e0u);	/* 415b23: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415b28: add esp, 0x4c */
	m->edx = (DWORD)(m->ebx + 0x88u);	/* 415b2b: lea edx, [ebx + 0x88] */
	{ DWORD v_ = 0x762fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b31: push 0x762fa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415b36: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 415b37: push esi */
	m->esp -= 4; M32(m->esp) = 0x415b3du; native_call(m, 0x402620u);	/* 415b38: call 0x402620 */
	m->ecx = 0xcu;	/* 415b3d: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415b42: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 415b44: lea edi, [esp + 0x40] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415b48: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415b4a: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dcabcu));	/* 415b4c: mov eax, dword ptr [0x4dcabc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415b51: push eax */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 415b52: lea ecx, [esp + 0x44] */
	{ DWORD v_ = 0x4b02e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b56: push 0x4b02e8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415b5b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x415b61u; native_call(m, 0x49e9ddu);	/* 415b5c: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b61: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b66: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b6b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b70: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b72: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415b7cu; native_call(m, 0x41f0e0u);	/* 415b77: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x60u);	/* 415b7c: lea edx, [esp + 0x60] */
	m->eax = (DWORD)(m->ebx + 0x97u);	/* 415b80: lea eax, [ebx + 0x97] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415b86: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415b87: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415b88: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415b8eu; native_call(m, 0x402620u);	/* 415b89: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b8e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b93: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b98: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415b9d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415ba2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415bacu; native_call(m, 0x41f0e0u);	/* 415ba7: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415bac: add esp, 0x4c */
	m->ecx = (DWORD)(m->ebx + 0xa8u);	/* 415baf: lea ecx, [ebx + 0xa8] */
	{ DWORD v_ = 0x763024u; m->esp -= 4; M32(m->esp) = v_; }	/* 415bb5: push 0x763024 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415bba: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 415bbb: push esi */
	m->esp -= 4; M32(m->esp) = 0x415bc1u; native_call(m, 0x402620u);	/* 415bbc: call 0x402620 */
	m->ecx = 0xcu;	/* 415bc1: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415bc6: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 415bc8: lea edi, [esp + 0x40] */
	m->edx = M32((DWORD)(0x4dcac0u));	/* 415bcc: mov edx, dword ptr [0x4dcac0] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415bd2: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415bd4: stosw word ptr es:[edi], ax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415bd6: push edx */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 415bd7: lea eax, [esp + 0x30] */
	{ DWORD v_ = 0x4b0270u; m->esp -= 4; M32(m->esp) = v_; }	/* 415bdb: push 0x4b0270 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415be0: push eax */
	m->esp -= 4; M32(m->esp) = 0x415be6u; native_call(m, 0x49e9ddu);	/* 415be1: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 415be6: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415bea: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415bed: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 415bef: lea edx, [esp + 0x4c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415bf3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415bf5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415bf7: sub edi, ecx */
	m->esi = m->edi;	/* 415bf9: mov esi, edi */
	m->edi = m->edx;	/* 415bfb: mov edi, edx */
	m->edx = m->ecx;	/* 415bfd: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415bff: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415c02: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415c04: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415c06: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415c07: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415c0a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x4dcac4u));	/* 415c0c: mov eax, dword ptr [0x4dcac4] */
	m->ecx = m->edx;	/* 415c11: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415c13: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415c16: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415c17: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 415c19: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0270u; m->esp -= 4; M32(m->esp) = v_; }	/* 415c1d: push 0x4b0270 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415c22: push ecx */
	m->esp -= 4; M32(m->esp) = 0x415c28u; native_call(m, 0x49e9ddu);	/* 415c23: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x44u);	/* 415c28: lea edi, [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415c2c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415c2f: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 415c31: lea edx, [esp + 0x58] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415c35: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415c37: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415c39: sub edi, ecx */
	m->esi = m->edi;	/* 415c3b: mov esi, edi */
	m->edi = m->edx;	/* 415c3d: mov edi, edx */
	m->edx = m->ecx;	/* 415c3f: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415c41: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415c44: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415c46: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415c48: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415c49: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415c4c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415c4e: mov ecx, edx */
	m->eax = M32((DWORD)(0x4dcac8u));	/* 415c50: mov eax, dword ptr [0x4dcac8] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415c55: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415c58: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415c5a: push eax */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 415c5b: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x4b0270u; m->esp -= 4; M32(m->esp) = v_; }	/* 415c5f: push 0x4b0270 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415c64: push ecx */
	m->esp -= 4; M32(m->esp) = 0x415c6au; native_call(m, 0x49e9ddu);	/* 415c65: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x50u);	/* 415c6a: lea edi, [esp + 0x50] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415c6e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415c71: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x64u);	/* 415c73: lea edx, [esp + 0x64] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415c77: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415c79: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415c7b: sub edi, ecx */
	m->esi = m->edi;	/* 415c7d: mov esi, edi */
	m->edi = m->edx;	/* 415c7f: mov edi, edx */
	m->edx = m->ecx;	/* 415c81: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415c83: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415c86: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415c88: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415c8a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415c8b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415c8e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x4dcaccu));	/* 415c90: mov eax, dword ptr [0x4dcacc] */
	m->ecx = m->edx;	/* 415c95: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415c97: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415c9a: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415c9b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 415c9d: lea ecx, [esp + 0x54] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 415ca1: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415ca6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x415cacu; native_call(m, 0x49e9ddu);	/* 415ca7: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x5cu);	/* 415cac: lea edi, [esp + 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415cb0: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415cb3: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x70u);	/* 415cb5: lea edx, [esp + 0x70] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415cb9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415cbb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415cbd: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415cbf: push 0x3f800000 */
	m->esi = m->edi;	/* 415cc4: mov esi, edi */
	m->edi = m->edx;	/* 415cc6: mov edi, edx */
	m->edx = m->ecx;	/* 415cc8: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415cca: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415ccd: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415ccf: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415cd1: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415cd2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415cd5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415cd7: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415cd9: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415cde: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415ce1: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415ce6: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415ce7: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415cec: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x415cf3u; native_call(m, 0x41f0e0u);	/* 415cee: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415cf3: add esp, 0x50 */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 415cf6: lea eax, [esp + 0x34] */
	m->ecx = (DWORD)(m->ebx + 0xb7u);	/* 415cfa: lea ecx, [ebx + 0xb7] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415d00: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415d01: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415d02: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415d08u; native_call(m, 0x402620u);	/* 415d03: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d08: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d0d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d12: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d17: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d1c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415d26u; native_call(m, 0x41f0e0u);	/* 415d21: call 0x41f0e0 */
	m->esi = M32((DWORD)(m->esp + 0x30u));	/* 415d26: mov esi, dword ptr [esp + 0x30] */
	m->edx = (DWORD)(m->ebx + 0xc8u);	/* 415d2a: lea edx, [ebx + 0xc8] */
	{ DWORD v_ = 0x7630a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d30: push 0x7630a4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415d35: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 415d36: push esi */
	m->esp -= 4; M32(m->esp) = 0x415d3cu; native_call(m, 0x402620u);	/* 415d37: call 0x402620 */
	m->ecx = 0xcu;	/* 415d3c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415d41: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x60u);	/* 415d43: lea edi, [esp + 0x60] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415d47: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcad0u)));	/* 415d49: fld dword ptr [0x4dcad0] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415d4f: add esp, 0x24 */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415d52: stosw word ptr es:[edi], ax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 415d54: fstp qword ptr [esp] */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 415d57: lea eax, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0268u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d5b: push 0x4b0268 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415d60: push eax */
	m->esp -= 4; M32(m->esp) = 0x415d66u; native_call(m, 0x49e9ddu);	/* 415d61: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d66: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d6b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d70: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d75: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d77: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415d81u; native_call(m, 0x41f0e0u);	/* 415d7c: call 0x41f0e0 */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 415d81: lea ecx, [esp + 0x58] */
	m->edx = (DWORD)(m->ebx + 0xd7u);	/* 415d85: lea edx, [ebx + 0xd7] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415d8b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415d8c: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415d8d: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415d93u; native_call(m, 0x402620u);	/* 415d8e: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d93: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d98: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415d9d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415da2: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415da7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415db1u; native_call(m, 0x41f0e0u);	/* 415dac: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415db1: add esp, 0x44 */
	m->eax = (DWORD)(m->ebx + 0xe8u);	/* 415db4: lea eax, [ebx + 0xe8] */
	{ DWORD v_ = 0x763124u; m->esp -= 4; M32(m->esp) = v_; }	/* 415dba: push 0x763124 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415dbf: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 415dc0: push esi */
	m->esp -= 4; M32(m->esp) = 0x415dc6u; native_call(m, 0x402620u);	/* 415dc1: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcaf8u)));	/* 415dc6: fld dword ptr [0x4dcaf8] */
	m->ecx = 0xcu;	/* 415dcc: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415dd1: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x4u)) = (double)ST(0); FPOP();	/* 415dd3: fstp qword ptr [esp + 4] */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 415dd7: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415ddb: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415dde: rep stosd dword ptr es:[edi], eax */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 415de0: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b025cu; m->esp -= 4; M32(m->esp) = v_; }	/* 415de4: push 0x4b025c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415de9: push ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415dea: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x415df1u; native_call(m, 0x49e9ddu);	/* 415dec: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415df1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415df6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415dfb: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 415e00: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415e02: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415e0cu; native_call(m, 0x41f0e0u);	/* 415e07: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 415e0c: lea edx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0xf7u);	/* 415e10: lea eax, [ebx + 0xf7] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415e16: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415e17: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415e18: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415e1eu; native_call(m, 0x402620u);	/* 415e19: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415e1e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415e23: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415e28: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415e2d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415e32: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415e3cu; native_call(m, 0x41f0e0u);	/* 415e37: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415e3c: add esp, 0x44 */
	m->ecx = (DWORD)(m->ebx + 0x108u);	/* 415e3f: lea ecx, [ebx + 0x108] */
	{ DWORD v_ = 0x7631a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 415e45: push 0x7631a4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415e4a: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 415e4b: push esi */
	m->esp -= 4; M32(m->esp) = 0x415e51u; native_call(m, 0x402620u);	/* 415e4c: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcafcu)));	/* 415e51: fld dword ptr [0x4dcafc] */
	m->ecx = 0xcu;	/* 415e57: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415e5c: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x4u)) = (double)ST(0); FPOP();	/* 415e5e: fstp qword ptr [esp + 4] */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 415e62: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415e66: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415e69: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 415e6b: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0x4b02bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 415e6f: push 0x4b02bc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415e74: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415e75: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x415e7cu; native_call(m, 0x49e9ddu);	/* 415e77: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 415e7c: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415e80: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415e83: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415e85: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcb04u)));	/* 415e87: fld dword ptr [0x4dcb04] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 415e8d: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 415e91: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415e93: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 415e95: lea edx, [esp + 0x44] */
	m->esi = m->edi;	/* 415e99: mov esi, edi */
	m->edi = m->edx;	/* 415e9b: mov edi, edx */
	m->edx = m->ecx;	/* 415e9d: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415e9f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415ea2: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415ea4: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415ea6: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415ea7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415eaa: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415eac: add esp, 8 */
	m->ecx = m->edx;	/* 415eaf: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415eb1: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 415eb4: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x4b02bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 415eb8: push 0x4b02bc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415ebd: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415ebe: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x415ec5u; native_call(m, 0x49e9ddu);	/* 415ec0: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 415ec5: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415ec9: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415ecc: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 415ece: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415ed2: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcb00u)));	/* 415ed4: fld dword ptr [0x4dcb00] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 415eda: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 415ede: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415ee0: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415ee2: add esp, 8 */
	m->esi = m->edi;	/* 415ee5: mov esi, edi */
	m->edi = m->edx;	/* 415ee7: mov edi, edx */
	m->edx = m->ecx;	/* 415ee9: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415eeb: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415eee: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415ef0: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415ef2: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415ef3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415ef6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415ef8: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 415efa: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415efe: and ecx, 3 */
	{ DWORD v_ = 0x4b025cu; m->esp -= 4; M32(m->esp) = v_; }	/* 415f01: push 0x4b025c */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415f06: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415f08: push eax */
	m->esp -= 4; M32(m->esp) = 0x415f0eu; native_call(m, 0x49e9ddu);	/* 415f09: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 415f0e: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415f12: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415f15: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 415f17: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415f1b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 415f1d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415f1f: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f21: push 0x3f800000 */
	m->esi = m->edi;	/* 415f26: mov esi, edi */
	m->edi = m->edx;	/* 415f28: mov edi, edx */
	m->edx = m->ecx;	/* 415f2a: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415f2c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415f2f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415f31: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 415f33: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 415f34: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 415f37: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 415f39: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f3b: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415f40: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f43: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415f48: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f49: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 415f4e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x415f55u; native_call(m, 0x41f0e0u);	/* 415f50: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 415f55: lea eax, [esp + 0x58] */
	m->ecx = (DWORD)(m->ebx + 0x117u);	/* 415f59: lea ecx, [ebx + 0x117] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415f5f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415f60: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 415f61: push ebp */
	m->esp -= 4; M32(m->esp) = 0x415f67u; native_call(m, 0x402620u);	/* 415f62: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f67: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f6c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f71: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f76: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f7b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x415f85u; native_call(m, 0x41f0e0u);	/* 415f80: call 0x41f0e0 */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 415f85: mov eax, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415f89: add esp, 0x44 */
	m->edx = (DWORD)(m->ebx + 0x128u);	/* 415f8c: lea edx, [ebx + 0x128] */
	{ DWORD v_ = 0x763224u; m->esp -= 4; M32(m->esp) = v_; }	/* 415f92: push 0x763224 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 415f97: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 415f98: push eax */
	m->esp -= 4; M32(m->esp) = 0x415f9eu; native_call(m, 0x402620u);	/* 415f99: call 0x402620 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcaecu)));	/* 415f9e: fld dword ptr [0x4dcaec] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 415fa4: fmul dword ptr [0x4a9480] */
	m->ecx = 0xcu;	/* 415faa: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415faf: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 415fb1: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415fb5: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 415fb8: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 415fba: fstp qword ptr [esp] */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 415fbd: lea ecx, [esp + 0x28] */
	{ DWORD v_ = 0x4b0254u; m->esp -= 4; M32(m->esp) = v_; }	/* 415fc1: push 0x4b0254 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 415fc6: push ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 415fc7: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x415fceu; native_call(m, 0x49e9ddu);	/* 415fc9: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 415fce: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415fd2: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 415fd5: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 415fd7: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415fdb: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcaf0u)));	/* 415fdd: fld dword ptr [0x4dcaf0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 415fe3: fmul dword ptr [0x4a9480] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 415fe9: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 415fed: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 415fef: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 415ff1: add esp, 8 */
	m->esi = m->edi;	/* 415ff4: mov esi, edi */
	m->edi = m->edx;	/* 415ff6: mov edi, edx */
	m->edx = m->ecx;	/* 415ff8: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 415ffa: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 415ffd: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 415fff: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416001: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416002: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416005: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416007: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 416009: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41600d: and ecx, 3 */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 416010: push 0x4b02fc */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416015: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416017: push eax */
	m->esp -= 4; M32(m->esp) = 0x41601du; native_call(m, 0x49e9ddu);	/* 416018: call 0x49e9dd */
	m->edi = 0x765aa4u;	/* 41601d: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416022: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416025: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 416027: lea edx, [esp + 0x30] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41602b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41602d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41602f: sub edi, ecx */
	m->esi = m->edi;	/* 416031: mov esi, edi */
	m->edi = m->edx;	/* 416033: mov edi, edx */
	m->edx = m->ecx;	/* 416035: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416037: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41603a: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41603c: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41603e: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41603f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416042: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416044: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 416046: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41604a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41604d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 41604f: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416054: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416057: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416059: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41605b: sub edi, ecx */
	m->esi = m->edi;	/* 41605d: mov esi, edi */
	m->edi = m->edx;	/* 41605f: mov edi, edx */
	m->edx = m->ecx;	/* 416061: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416063: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416066: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416068: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41606a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41606b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41606e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416070: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 416072: lea edx, [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416076: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416079: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41607e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 416080: lea edi, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416084: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416087: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416089: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41608b: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41608d: push 0x3f800000 */
	m->esi = m->edi;	/* 416092: mov esi, edi */
	m->edi = m->edx;	/* 416094: mov edi, edx */
	m->edx = m->ecx;	/* 416096: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416098: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41609b: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41609d: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41609f: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4160a0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4160a3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4160a5: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4160a7: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4160ac: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4160af: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4160b0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4160b2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4160bcu; native_call(m, 0x41f0e0u);	/* 4160b7: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 4160bc: lea eax, [esp + 0x58] */
	{ DWORD a_ = m->ebx, b_ = 0x137u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4160c0: add ebx, 0x137 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4160c6: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4160c7: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4160c8: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4160ceu; native_call(m, 0x402620u);	/* 4160c9: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4160ce: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4160d1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4160d2: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4160d3: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4160d4: pop ebx */
	m->esp = m->ebp;	/* 4160d5: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4160d7: pop ebp */
	m->esp += 4 + 0; return;	/* 4160d8: ret  */
L_4160d9:
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4160d9: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_418fbb;	/* 4160dc: ja 0x418fbb */
	switch (m->eax) { case 0: goto L_4160e9; case 1: goto L_4168f9; case 2: goto L_416d17; case 3: goto L_4173b6; case 4: goto L_417c0a; case 5: goto L_4187f0; default: abort(); }	/* 4160e2: jmp dword ptr [eax*4 + 0x418fdc] */
L_4160e9:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4160e9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4160ee: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4160f3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4160f8: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4160fd: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416107u; native_call(m, 0x41f0e0u);	/* 416102: call 0x41f0e0 */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 416107: lea eax, [ebx + 0xc] */
	m->ecx = (DWORD)(m->ebp + 0xau);	/* 41610a: lea ecx, [ebp + 0xa] */
	{ DWORD v_ = 0x760aa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41610d: push 0x760aa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416112: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416113: push ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 416114: mov dword ptr [esp + 0x30], ecx */
	m->esp -= 4; M32(m->esp) = 0x41611du; native_call(m, 0x403170u);	/* 416118: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcef8u)));	/* 41611d: fld dword ptr [0x4dcef8] */
	m->ecx = 0xcu;	/* 416123: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416128: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 41612a: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 41612e: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416132: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416135: rep stosd dword ptr es:[edi], eax */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 416137: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 41613b: push 0x4b0354 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416140: push ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416141: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x416148u; native_call(m, 0x49e9ddu);	/* 416143: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 416148: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41614d: add esp, 0x10 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 416150: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 416153: lea eax, [eax + edx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9084u)));	/* 416156: fild dword ptr [eax*4 + 0x9f9084] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41615d: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dcef8u));	/* 416163: fmul dword ptr [0x4dcef8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dbc78u));	/* 416169: fadd dword ptr [0x4dbc78] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41616f: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 416175: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 416177: test ah, 0x40 */
	if (!m->zf) goto L_4161bd;	/* 41617a: jne 0x4161bd */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41617c: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 416182: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 416184: test ah, 1 */
	if (m->zf) goto L_4161a3;	/* 416187: je 0x4161a3 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416189: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 41618c: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 416190: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b024cu; m->esp -= 4; M32(m->esp) = v_; }	/* 416193: push 0x4b024c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416198: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41619eu; native_call(m, 0x49e9ddu);	/* 416199: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41619e: add esp, 0x10 */
	goto L_4161e5;	/* 4161a1: jmp 0x4161e5 */
L_4161a3:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4161a3: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 4161a6: lea edx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4161aa: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0244u; m->esp -= 4; M32(m->esp) = v_; }	/* 4161ad: push 0x4b0244 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4161b2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4161b8u; native_call(m, 0x49e9ddu);	/* 4161b3: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4161b8: add esp, 0x10 */
	goto L_4161e5;	/* 4161bb: jmp 0x4161e5 */
L_4161bd:
	m->edi = 0x4b033cu;	/* 4161bd: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4161c2: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4161c5: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 4161c7: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4161cb: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4161cd: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4161cf: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4161d1: sub edi, ecx */
	m->eax = m->ecx;	/* 4161d3: mov eax, ecx */
	m->esi = m->edi;	/* 4161d5: mov esi, edi */
	m->edi = m->edx;	/* 4161d7: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4161d9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4161dc: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4161de: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4161e0: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4161e3: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_4161e5:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4161e5: or ecx, 0xffffffff */
	m->edi = 0x7655a4u;	/* 4161e8: mov edi, 0x7655a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4161ed: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 4161ef: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4161f3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4161f5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4161f7: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4161f9: push 0x3f800000 */
	m->esi = m->edi;	/* 4161fe: mov esi, edi */
	m->edi = m->edx;	/* 416200: mov edi, edx */
	m->edx = m->ecx;	/* 416202: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416204: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416207: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416209: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41620b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41620c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41620f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416211: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 416213: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416217: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41621a: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41621f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 416221: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416226: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416229: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41622b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41622d: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41622f: push 0x3f800000 */
	m->esi = m->edi;	/* 416234: mov esi, edi */
	m->edi = m->edx;	/* 416236: mov edi, edx */
	m->edx = m->ecx;	/* 416238: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41623a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41623d: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41623f: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416241: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416242: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416245: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416247: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 416249: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41624d: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416250: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416251: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 416253: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416257: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41625a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41625c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41625e: sub edi, ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416260: push 0x76d438 */
	m->esi = m->edi;	/* 416265: mov esi, edi */
	m->edi = m->edx;	/* 416267: mov edi, edx */
	m->edx = m->ecx;	/* 416269: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41626b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41626e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416270: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416272: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416273: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416276: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416278: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41627a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41627d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x416284u; native_call(m, 0x41f0e0u);	/* 41627f: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 416284: lea eax, [esp + 0x48] */
	{ DWORD a_ = m->ebp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 416288: add ebp, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41628e: push eax */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 41628f: lea eax, [ebx + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416292: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416293: push ebp */
	m->esp -= 4; M32(m->esp) = 0x416299u; native_call(m, 0x4125f0u);	/* 416294: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416299: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41629c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4162a1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4162a6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4162ab: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4162b0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4162bau; native_call(m, 0x41f0e0u);	/* 4162b5: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4162ba: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 4162be: lea eax, [ebx + 0x20] */
	{ DWORD v_ = 0x760b24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4162c1: push 0x760b24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4162c6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4162c7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4162cdu; native_call(m, 0x403170u);	/* 4162c8: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcefcu)));	/* 4162cd: fld dword ptr [0x4dcefc] */
	m->ecx = 0xcu;	/* 4162d3: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4162d8: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 4162da: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 4162de: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4162e2: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4162e5: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 4162e7: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 4162eb: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4162f0: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4162f1: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x4162f8u; native_call(m, 0x49e9ddu);	/* 4162f3: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 4162f8: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4162fd: add esp, 0x10 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 416300: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 416303: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9084u)));	/* 416306: fild dword ptr [edx*4 + 0x9f9084] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41630d: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dcefcu));	/* 416313: fmul dword ptr [0x4dcefc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416319: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41631f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 416321: test ah, 0x40 */
	if (!m->zf) goto L_416367;	/* 416324: jne 0x416367 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416326: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41632c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41632e: test ah, 1 */
	if (m->zf) goto L_41634d;	/* 416331: je 0x41634d */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416333: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 416336: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41633a: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 41633d: push 0x4b02fc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416342: push eax */
	m->esp -= 4; M32(m->esp) = 0x416348u; native_call(m, 0x49e9ddu);	/* 416343: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416348: add esp, 0x10 */
	goto L_41638f;	/* 41634b: jmp 0x41638f */
L_41634d:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41634d: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 416350: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 416354: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 416357: push 0x4b02c4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41635c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x416362u; native_call(m, 0x49e9ddu);	/* 41635d: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416362: add esp, 0x10 */
	goto L_41638f;	/* 416365: jmp 0x41638f */
L_416367:
	m->edi = 0x4b033cu;	/* 416367: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41636c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41636f: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 416371: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416375: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 416377: fstp st(0) */
	m->ecx = ~m->ecx;	/* 416379: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41637b: sub edi, ecx */
	m->eax = m->ecx;	/* 41637d: mov eax, ecx */
	m->esi = m->edi;	/* 41637f: mov esi, edi */
	m->edi = m->edx;	/* 416381: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416383: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416386: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 416388: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41638a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41638d: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_41638f:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41638f: or ecx, 0xffffffff */
	m->edi = 0x765624u;	/* 416392: mov edi, 0x765624 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416397: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 416399: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41639d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41639f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4163a1: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4163a3: push 0x3f800000 */
	m->esi = m->edi;	/* 4163a8: mov esi, edi */
	m->edi = m->edx;	/* 4163aa: mov edi, edx */
	m->edx = m->ecx;	/* 4163ac: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4163ae: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4163b1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4163b3: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4163b5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4163b6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4163b9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4163bb: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 4163bd: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4163c1: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4163c4: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4163c9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4163cb: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4163d0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4163d3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4163d5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4163d7: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4163d9: push 0x3f800000 */
	m->esi = m->edi;	/* 4163de: mov esi, edi */
	m->edi = m->edx;	/* 4163e0: mov edi, edx */
	m->edx = m->ecx;	/* 4163e2: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4163e4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4163e7: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4163e9: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4163eb: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4163ec: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4163ef: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4163f1: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 4163f3: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4163f7: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4163fa: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4163fb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 4163fd: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416401: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416404: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416406: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416408: sub edi, ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41640a: push 0x76d438 */
	m->esi = m->edi;	/* 41640f: mov esi, edi */
	m->edi = m->edx;	/* 416411: mov edi, edx */
	m->edx = m->ecx;	/* 416413: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416415: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416418: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41641a: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41641c: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41641d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416420: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416422: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416424: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416427: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x41642eu; native_call(m, 0x41f0e0u);	/* 416429: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 41642e: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416432: push eax */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 416433: lea eax, [ebx + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416436: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416437: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41643du; native_call(m, 0x4125f0u);	/* 416438: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41643d: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416440: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416445: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41644a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41644f: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416454: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41645eu; native_call(m, 0x41f0e0u);	/* 416459: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 41645e: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 416462: lea eax, [ebx + 0x34] */
	{ DWORD v_ = 0x760ba4u; m->esp -= 4; M32(m->esp) = v_; }	/* 416465: push 0x760ba4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41646a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41646b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x416471u; native_call(m, 0x403170u);	/* 41646c: call 0x403170 */
	m->ecx = 0xcu;	/* 416471: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416476: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 416478: lea edi, [esp + 0x54] */
	m->edx = M32((DWORD)(0x4dcf00u));	/* 41647c: mov edx, dword ptr [0x4dcf00] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416482: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416484: stosw word ptr es:[edi], ax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 416486: push edx */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 416487: lea eax, [esp + 0x58] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 41648b: push 0x4b0320 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416490: push eax */
	m->esp -= 4; M32(m->esp) = 0x416496u; native_call(m, 0x49e9ddu);	/* 416491: call 0x49e9dd */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dceb4u)));	/* 416496: fld dword ptr [0x4dceb4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41649c: fcom dword ptr [0x4a93e8] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4164a2: add esp, 0x2c */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4164a5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4164a7: test ah, 0x40 */
	if (!m->zf) goto L_4164ed;	/* 4164aa: jne 0x4164ed */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4164ac: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4164b2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4164b4: test ah, 1 */
	if (m->zf) goto L_4164d3;	/* 4164b7: je 0x4164d3 */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4164b9: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4164be: push eax */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 4164bf: lea ecx, [esp + 0x24] */
	{ DWORD v_ = 0x4b02e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4164c3: push 0x4b02e8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4164c8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4164ceu; native_call(m, 0x49e9ddu);	/* 4164c9: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4164ce: add esp, 0xc */
	goto L_416515;	/* 4164d1: jmp 0x416515 */
L_4164d3:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4164d3: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4164d8: push eax */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 4164d9: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x4b023cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4164dd: push 0x4b023c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4164e2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4164e8u; native_call(m, 0x49e9ddu);	/* 4164e3: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4164e8: add esp, 0xc */
	goto L_416515;	/* 4164eb: jmp 0x416515 */
L_4164ed:
	m->edi = 0x4b0304u;	/* 4164ed: mov edi, 0x4b0304 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4164f2: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4164f5: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 4164f7: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4164fb: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4164fd: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4164ff: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416501: sub edi, ecx */
	m->eax = m->ecx;	/* 416503: mov eax, ecx */
	m->esi = m->edi;	/* 416505: mov esi, edi */
	m->edi = m->edx;	/* 416507: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416509: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41650c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41650e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416510: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416513: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_416515:
	m->edi = (DWORD)(m->esp + 0x20u);	/* 416515: lea edi, [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416519: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41651c: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41651e: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416522: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416524: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416526: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416528: push 0x3f800000 */
	m->esi = m->edi;	/* 41652d: mov esi, edi */
	m->edi = m->edx;	/* 41652f: mov edi, edx */
	m->edx = m->ecx;	/* 416531: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416533: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416536: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416538: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41653a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41653b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41653e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416540: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416542: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416547: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41654a: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41654f: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416550: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416555: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x41655cu; native_call(m, 0x41f0e0u);	/* 416557: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 41655c: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416560: push eax */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 416561: lea eax, [ebx + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416564: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416565: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41656bu; native_call(m, 0x4125f0u);	/* 416566: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41656b: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41656e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416573: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416578: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41657d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416582: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41658cu; native_call(m, 0x41f0e0u);	/* 416587: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 41658c: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 416590: lea eax, [ebx + 0x48] */
	{ DWORD v_ = 0x760c24u; m->esp -= 4; M32(m->esp) = v_; }	/* 416593: push 0x760c24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416598: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416599: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41659fu; native_call(m, 0x403170u);	/* 41659a: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93f4u)));	/* 41659f: fld dword ptr [0x4a93f4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcf04u));	/* 4165a5: fdiv dword ptr [0x4dcf04] */
	m->ecx = 0xcu;	/* 4165ab: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4165b0: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 4165b2: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4165b6: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4165b9: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 4165bb: lea edx, [esp + 0x3c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4165bf: stosw word ptr es:[edi], ax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 4165c1: fmul dword ptr [0x4a93f4] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0);	/* 4165c7: fst dword ptr [esp + 0x1c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4165cb: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 4165ce: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4165d3: push edx */
	m->esp -= 4; M32(m->esp) = 0x4165d9u; native_call(m, 0x49e9ddu);	/* 4165d4: call 0x49e9dd */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc898u)));	/* 4165d9: fld dword ptr [0x4dc898] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 4165df: fmul dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4165e3: add esp, 0x10 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4165e6: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4165ec: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4165ee: test ah, 0x40 */
	if (!m->zf) goto L_416634;	/* 4165f1: jne 0x416634 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4165f3: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4165f9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4165fb: test ah, 1 */
	if (m->zf) goto L_41661a;	/* 4165fe: je 0x41661a */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416600: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 416603: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 416607: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 41660a: push 0x4b02fc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41660f: push eax */
	m->esp -= 4; M32(m->esp) = 0x416615u; native_call(m, 0x49e9ddu);	/* 416610: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416615: add esp, 0x10 */
	goto L_41665c;	/* 416618: jmp 0x41665c */
L_41661a:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41661a: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 41661d: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 416621: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 416624: push 0x4b02c4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416629: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41662fu; native_call(m, 0x49e9ddu);	/* 41662a: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41662f: add esp, 0x10 */
	goto L_41665c;	/* 416632: jmp 0x41665c */
L_416634:
	m->edi = 0x4b033cu;	/* 416634: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416639: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41663c: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 41663e: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416642: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 416644: fstp st(0) */
	m->ecx = ~m->ecx;	/* 416646: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416648: sub edi, ecx */
	m->eax = m->ecx;	/* 41664a: mov eax, ecx */
	m->esi = m->edi;	/* 41664c: mov esi, edi */
	m->edi = m->edx;	/* 41664e: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416650: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416653: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 416655: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416657: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41665a: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_41665c:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41665c: or ecx, 0xffffffff */
	m->edi = 0x7656a4u;	/* 41665f: mov edi, 0x7656a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416664: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 416666: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41666a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41666c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41666e: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416670: push 0x3f800000 */
	m->esi = m->edi;	/* 416675: mov esi, edi */
	m->edi = m->edx;	/* 416677: mov edi, edx */
	m->edx = m->ecx;	/* 416679: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41667b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41667e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416680: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416682: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416683: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416686: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416688: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 41668a: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41668e: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416691: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416696: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 416698: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41669d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4166a0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4166a2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4166a4: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4166a6: push 0x3f800000 */
	m->esi = m->edi;	/* 4166ab: mov esi, edi */
	m->edi = m->edx;	/* 4166ad: mov edi, edx */
	m->edx = m->ecx;	/* 4166af: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4166b1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4166b4: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4166b6: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4166b8: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4166b9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4166bc: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4166be: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 4166c0: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4166c4: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4166c7: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4166c8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 4166ca: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4166ce: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4166d1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4166d3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4166d5: sub edi, ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4166d7: push 0x76d438 */
	m->esi = m->edi;	/* 4166dc: mov esi, edi */
	m->edi = m->edx;	/* 4166de: mov edi, edx */
	m->edx = m->ecx;	/* 4166e0: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4166e2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4166e5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4166e7: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4166e9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4166ea: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4166ed: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4166ef: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4166f1: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4166f4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4166fbu; native_call(m, 0x41f0e0u);	/* 4166f6: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4166fb: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4166ff: push eax */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 416700: lea eax, [ebx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416703: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416704: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41670au; native_call(m, 0x4125f0u);	/* 416705: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41670a: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41670d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416712: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416717: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41671c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416721: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41672bu; native_call(m, 0x41f0e0u);	/* 416726: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 41672b: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 41672f: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = 0x760ca4u; m->esp -= 4; M32(m->esp) = v_; }	/* 416732: push 0x760ca4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416737: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416738: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41673eu; native_call(m, 0x403170u);	/* 416739: call 0x403170 */
	m->ecx = 0xcu;	/* 41673e: mov ecx, 0xc */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcf08u)));	/* 416743: fld dword ptr [0x4dcf08] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 416749: fmul dword ptr [0x4a9480] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41674f: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 416751: lea edi, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416755: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 416757: fstp qword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41675b: add esp, 0x18 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41675e: lea edx, [esp + 0x3c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416762: stosw word ptr es:[edi], ax */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 416764: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 416769: push edx */
	m->esp -= 4; M32(m->esp) = 0x41676fu; native_call(m, 0x49e9ddu);	/* 41676a: call 0x49e9dd */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc88cu)));	/* 41676f: fld dword ptr [0x4dc88c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dcf08u));	/* 416775: fmul dword ptr [0x4dcf08] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41677b: add esp, 0x10 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 41677e: fmul dword ptr [0x4a9480] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416784: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41678a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41678c: test ah, 0x40 */
	if (!m->zf) goto L_4167d2;	/* 41678f: jne 0x4167d2 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416791: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 416797: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 416799: test ah, 1 */
	if (m->zf) goto L_4167b8;	/* 41679c: je 0x4167b8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41679e: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4167a1: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4167a5: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4167a8: push 0x4b02fc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4167ad: push eax */
	m->esp -= 4; M32(m->esp) = 0x4167b3u; native_call(m, 0x49e9ddu);	/* 4167ae: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4167b3: add esp, 0x10 */
	goto L_4167fa;	/* 4167b6: jmp 0x4167fa */
L_4167b8:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4167b8: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 4167bb: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4167bf: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4167c2: push 0x4b02c4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4167c7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4167cdu; native_call(m, 0x49e9ddu);	/* 4167c8: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4167cd: add esp, 0x10 */
	goto L_4167fa;	/* 4167d0: jmp 0x4167fa */
L_4167d2:
	m->edi = 0x4b033cu;	/* 4167d2: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4167d7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4167da: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 4167dc: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4167e0: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4167e2: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4167e4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4167e6: sub edi, ecx */
	m->eax = m->ecx;	/* 4167e8: mov eax, ecx */
	m->esi = m->edi;	/* 4167ea: mov esi, edi */
	m->edi = m->edx;	/* 4167ec: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4167ee: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4167f1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4167f3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4167f5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4167f8: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_4167fa:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4167fa: or ecx, 0xffffffff */
	m->edi = 0x765aa4u;	/* 4167fd: mov edi, 0x765aa4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416802: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 416804: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416808: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41680a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41680c: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41680e: push 0x3f800000 */
	m->esi = m->edi;	/* 416813: mov esi, edi */
	m->edi = m->edx;	/* 416815: mov edi, edx */
	m->edx = m->ecx;	/* 416817: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416819: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41681c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41681e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416820: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416821: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416824: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416826: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 416828: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41682c: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41682f: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416834: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 416836: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41683b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41683e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416840: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416842: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416844: push 0x3f800000 */
	m->esi = m->edi;	/* 416849: mov esi, edi */
	m->edi = m->edx;	/* 41684b: mov edi, edx */
	m->edx = m->ecx;	/* 41684d: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41684f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416852: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416854: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416856: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416857: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41685a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41685c: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 41685e: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416862: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416865: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416866: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 416868: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41686c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41686f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416871: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416873: sub edi, ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416875: push 0x76d438 */
	m->esi = m->edi;	/* 41687a: mov esi, edi */
	m->edi = m->edx;	/* 41687c: mov edi, edx */
	m->edx = m->ecx;	/* 41687e: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416880: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416883: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416885: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416887: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416888: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41688b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41688d: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41688f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416892: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x416899u; native_call(m, 0x41f0e0u);	/* 416894: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 416899: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41689d: push eax */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 41689e: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4168a1: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4168a2: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4168a8u; native_call(m, 0x4125f0u);	/* 4168a3: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4168a8: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4168ab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4168b0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4168b5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4168ba: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4168bf: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4168c9u; native_call(m, 0x41f0e0u);	/* 4168c4: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4168c9: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ebx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4168cd: add ebx, 0x70 */
	{ DWORD v_ = 0x760d24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4168d0: push 0x760d24 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4168d5: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4168d6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4168dcu; native_call(m, 0x403170u);	/* 4168d7: call 0x403170 */
	m->ecx = 0xcu;	/* 4168dc: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4168e1: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 4168e3: lea edi, [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcf0cu)));	/* 4168e7: fld dword ptr [0x4dcf0c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4168ed: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4168ef: stosw word ptr es:[edi], ax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4168f1: add esp, 0x18 */
	goto L_417b6d;	/* 4168f4: jmp 0x417b6d */
L_4168f9:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4168f9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4168fe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416903: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416908: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41690d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416917u; native_call(m, 0x41f0e0u);	/* 416912: call 0x41f0e0 */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 416917: lea eax, [ebx + 0xc] */
	m->ecx = (DWORD)(m->ebp + 0xau);	/* 41691a: lea ecx, [ebp + 0xa] */
	{ DWORD v_ = 0x760fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41691d: push 0x760fa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416922: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416923: push ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 416924: mov dword ptr [esp + 0x30], ecx */
	m->esp -= 4; M32(m->esp) = 0x41692du; native_call(m, 0x403170u);	/* 416928: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc48u)));	/* 41692d: fld dword ptr [0x4dbc48] */
	m->ecx = 0xcu;	/* 416933: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416938: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 41693a: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 41693e: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416942: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416945: rep stosd dword ptr es:[edi], eax */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 416947: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 41694b: push 0x4b0334 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416950: push ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416951: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x416958u; native_call(m, 0x49e9ddu);	/* 416953: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 416958: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41695d: add esp, 0x10 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 416960: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 416963: lea eax, [eax + edx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9088u)));	/* 416966: fild dword ptr [eax*4 + 0x9f9088] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41696d: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc48u));	/* 416973: fmul dword ptr [0x4dbc48] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dceb0u)));	/* 416979: fld dword ptr [0x4dceb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc48u));	/* 41697f: fmul dword ptr [0x4dbc48] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 416985: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416987: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41698d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41698f: test ah, 0x40 */
	if (!m->zf) goto L_4169d5;	/* 416992: jne 0x4169d5 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416994: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41699a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41699c: test ah, 1 */
	if (m->zf) goto L_4169bb;	/* 41699f: je 0x4169bb */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4169a1: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 4169a4: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4169a8: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4169ab: push 0x4b02fc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4169b0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4169b6u; native_call(m, 0x49e9ddu);	/* 4169b1: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4169b6: add esp, 0x10 */
	goto L_4169fd;	/* 4169b9: jmp 0x4169fd */
L_4169bb:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4169bb: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 4169be: lea edx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4169c2: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4169c5: push 0x4b02c4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4169ca: push edx */
	m->esp -= 4; M32(m->esp) = 0x4169d0u; native_call(m, 0x49e9ddu);	/* 4169cb: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4169d0: add esp, 0x10 */
	goto L_4169fd;	/* 4169d3: jmp 0x4169fd */
L_4169d5:
	m->edi = 0x4b033cu;	/* 4169d5: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4169da: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4169dd: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 4169df: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4169e3: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4169e5: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4169e7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4169e9: sub edi, ecx */
	m->eax = m->ecx;	/* 4169eb: mov eax, ecx */
	m->esi = m->edi;	/* 4169ed: mov esi, edi */
	m->edi = m->edx;	/* 4169ef: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4169f1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4169f4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4169f6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4169f8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4169fb: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_4169fd:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4169fd: or ecx, 0xffffffff */
	m->edi = 0x7657a4u;	/* 416a00: mov edi, 0x7657a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416a05: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 416a07: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416a0b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416a0d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416a0f: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416a11: push 0x3f800000 */
	m->esi = m->edi;	/* 416a16: mov esi, edi */
	m->edi = m->edx;	/* 416a18: mov edi, edx */
	m->edx = m->ecx;	/* 416a1a: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416a1c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416a1f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416a21: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416a23: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416a24: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416a27: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416a29: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 416a2b: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416a2f: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416a32: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416a37: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 416a39: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416a3e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416a41: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416a43: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416a45: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416a47: push 0x3f800000 */
	m->esi = m->edi;	/* 416a4c: mov esi, edi */
	m->edi = m->edx;	/* 416a4e: mov edi, edx */
	m->edx = m->ecx;	/* 416a50: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416a52: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416a55: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416a57: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416a59: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416a5a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416a5d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416a5f: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 416a61: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416a65: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416a68: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416a69: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 416a6b: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416a6f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416a72: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416a74: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416a76: sub edi, ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416a78: push 0x76d438 */
	m->esi = m->edi;	/* 416a7d: mov esi, edi */
	m->edi = m->edx;	/* 416a7f: mov edi, edx */
	m->edx = m->ecx;	/* 416a81: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416a83: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416a86: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416a88: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416a8a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416a8b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416a8e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416a90: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416a92: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416a95: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x416a9cu; native_call(m, 0x41f0e0u);	/* 416a97: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 416a9c: lea eax, [esp + 0x48] */
	{ DWORD a_ = m->ebp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 416aa0: add ebp, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416aa6: push eax */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 416aa7: lea eax, [ebx + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416aaa: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416aab: push ebp */
	m->esp -= 4; M32(m->esp) = 0x416ab1u; native_call(m, 0x4125f0u);	/* 416aac: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416ab1: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ab4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ab9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416abe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ac3: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ac8: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416ad2u; native_call(m, 0x41f0e0u);	/* 416acd: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 416ad2: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 416ad6: lea eax, [ebx + 0x20] */
	{ DWORD v_ = 0x761024u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ad9: push 0x761024 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416ade: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416adf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x416ae5u; native_call(m, 0x403170u);	/* 416ae0: call 0x403170 */
	m->ecx = 0xcu;	/* 416ae5: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416aea: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 416aec: lea edi, [esp + 0x54] */
	m->edx = M32((DWORD)(0x4dbc4cu));	/* 416af0: mov edx, dword ptr [0x4dbc4c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416af6: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416af8: stosw word ptr es:[edi], ax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 416afa: push edx */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 416afb: lea eax, [esp + 0x58] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 416aff: push 0x4b0320 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416b04: push eax */
	m->esp -= 4; M32(m->esp) = 0x416b0au; native_call(m, 0x49e9ddu);	/* 416b05: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 416b0a: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416b0f: add esp, 0x2c */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 416b12: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 416b15: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9080u)));	/* 416b18: fild dword ptr [edx*4 + 0x9f9080] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 416b1f: fmul dword ptr [0x4a9420] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x4dbc4cu));	/* 416b25: fimul dword ptr [0x4dbc4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 416b2b: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 416b31: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 416b36: mov dword ptr [esp + 0x1c], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 416b3a: fild dword ptr [esp + 0x1c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416b3e: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 416b44: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 416b46: test ah, 0x40 */
	if (!m->zf) goto L_416bb1;	/* 416b49: jne 0x416bb1 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416b4b: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 416b51: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 416b53: test ah, 1 */
	if (m->zf) goto L_416b6a;	/* 416b56: je 0x416b6a */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 416b58: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416b5d: push eax */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 416b5e: lea eax, [esp + 0x24] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 416b62: push 0x4b0320 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416b67: push eax */
	goto L_416b7a;	/* 416b68: jmp 0x416b7a */
L_416b6a:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 416b6a: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416b6f: push eax */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 416b70: lea ecx, [esp + 0x24] */
	{ DWORD v_ = 0x4b0238u; m->esp -= 4; M32(m->esp) = v_; }	/* 416b74: push 0x4b0238 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416b79: push ecx */
L_416b7a:
	m->esp -= 4; M32(m->esp) = 0x416b7fu; native_call(m, 0x49e9ddu);	/* 416b7a: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x2cu);	/* 416b7f: lea edi, [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416b83: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416b86: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416b88: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416b8b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416b8d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416b8f: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 416b91: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 416b95: mov esi, edi */
	m->edi = m->edx;	/* 416b97: mov edi, edx */
	m->edx = m->ecx;	/* 416b99: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416b9b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416b9e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416ba0: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416ba2: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416ba3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416ba6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416ba8: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416baa: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416bad: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_416bb3;	/* 416baf: jmp 0x416bb3 */
L_416bb1:
	ST(0) = ST(0); FPOP();	/* 416bb1: fstp st(0) */
L_416bb3:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416bb3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416bb8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416bbd: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 416bc2: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416bc4: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416bceu; native_call(m, 0x41f0e0u);	/* 416bc9: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 416bce: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416bd2: push eax */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 416bd3: lea eax, [ebx + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416bd6: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416bd7: push ebp */
	m->esp -= 4; M32(m->esp) = 0x416bddu; native_call(m, 0x4125f0u);	/* 416bd8: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416bdd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416be2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416be7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416bec: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416bf1: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416bfbu; native_call(m, 0x41f0e0u);	/* 416bf6: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 416bfb: mov ecx, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->ebx, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 416bff: add ebx, 0x34 */
	{ DWORD v_ = 0x7610a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 416c02: push 0x7610a4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 416c07: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416c08: push ecx */
	m->esp -= 4; M32(m->esp) = 0x416c0eu; native_call(m, 0x403170u);	/* 416c09: call 0x403170 */
	m->ecx = 0xcu;	/* 416c0e: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416c13: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 416c15: lea edi, [esp + 0x74] */
	m->edx = M32((DWORD)(0x4dbc50u));	/* 416c19: mov edx, dword ptr [0x4dbc50] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416c1f: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416c21: add esp, 0x40 */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416c24: stosw word ptr es:[edi], ax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 416c26: push edx */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 416c27: lea eax, [esp + 0x38] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 416c2b: push 0x4b0320 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416c30: push eax */
	m->esp -= 4; M32(m->esp) = 0x416c36u; native_call(m, 0x49e9ddu);	/* 416c31: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 416c36: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416c3b: add esp, 0xc */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 416c3e: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 416c41: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9080u)));	/* 416c44: fild dword ptr [edx*4 + 0x9f9080] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 416c4b: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcc68u));	/* 416c51: fadd dword ptr [0x4dcc68] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x4dbc50u));	/* 416c57: fimul dword ptr [0x4dbc50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 416c5d: fadd dword ptr [0x4a942c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 416c63: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 416c68: mov dword ptr [esp + 0x1c], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 416c6c: fild dword ptr [esp + 0x1c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416c70: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 416c76: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 416c78: test ah, 0x40 */
	if (!m->zf) goto L_416ce3;	/* 416c7b: jne 0x416ce3 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 416c7d: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 416c83: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 416c85: test ah, 1 */
	if (m->zf) goto L_416c9c;	/* 416c88: je 0x416c9c */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 416c8a: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416c8f: push eax */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 416c90: lea eax, [esp + 0x24] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 416c94: push 0x4b0320 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416c99: push eax */
	goto L_416cac;	/* 416c9a: jmp 0x416cac */
L_416c9c:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 416c9c: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416ca1: push eax */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 416ca2: lea ecx, [esp + 0x24] */
	{ DWORD v_ = 0x4b0238u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ca6: push 0x4b0238 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416cab: push ecx */
L_416cac:
	m->esp -= 4; M32(m->esp) = 0x416cb1u; native_call(m, 0x49e9ddu);	/* 416cac: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x2cu);	/* 416cb1: lea edi, [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416cb5: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416cb8: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416cba: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416cbd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416cbf: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416cc1: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 416cc3: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 416cc7: mov esi, edi */
	m->edi = m->edx;	/* 416cc9: mov edi, edx */
	m->edx = m->ecx;	/* 416ccb: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416ccd: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416cd0: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416cd2: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416cd4: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416cd5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416cd8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416cda: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416cdc: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416cdf: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_416ce5;	/* 416ce1: jmp 0x416ce5 */
L_416ce3:
	ST(0) = ST(0); FPOP();	/* 416ce3: fstp st(0) */
L_416ce5:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ce5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416cea: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416cef: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 416cf4: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416cf6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416d00u; native_call(m, 0x41f0e0u);	/* 416cfb: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 416d00: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416d04: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 416d05: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416d06: push ebp */
	m->esp -= 4; M32(m->esp) = 0x416d0cu; native_call(m, 0x4125f0u);	/* 416d07: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416d0c: add esp, 0x20 */
	m->edi = M32(m->esp); m->esp += 4;	/* 416d0f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 416d10: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 416d11: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 416d12: pop ebx */
	m->esp = m->ebp;	/* 416d13: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 416d15: pop ebp */
	m->esp += 4 + 0; return;	/* 416d16: ret  */
L_416d17:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d17: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d1c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d21: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d26: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d2b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416d35u; native_call(m, 0x41f0e0u);	/* 416d30: call 0x41f0e0 */
	m->esi = (DWORD)(m->ebx + 0xcu);	/* 416d35: lea esi, [ebx + 0xc] */
	m->eax = (DWORD)(m->ebp + 0xau);	/* 416d38: lea eax, [ebp + 0xa] */
	{ DWORD v_ = 0x7614a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d3b: push 0x7614a4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 416d40: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416d41: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 416d42: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x416d4bu; native_call(m, 0x403170u);	/* 416d46: call 0x403170 */
	m->ecx = 0xcu;	/* 416d4b: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416d50: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 416d52: lea edi, [esp + 0x54] */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 416d56: lea edx, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416d5a: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dc290u));	/* 416d5c: mov ecx, dword ptr [0x4dc290] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416d62: push ecx */
	{ DWORD v_ = 0x4b02e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d63: push 0x4b02e8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 416d68: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416d69: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x416d70u; native_call(m, 0x49e9ddu);	/* 416d6b: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d70: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d75: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d7a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d7f: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416d81: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416d8bu; native_call(m, 0x41f0e0u);	/* 416d86: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416d8b: add esp, 0x40 */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 416d8e: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ebp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 416d92: add ebp, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416d98: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 416d99: push esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416d9a: push ebp */
	m->esp -= 4; M32(m->esp) = 0x416da0u; native_call(m, 0x4125f0u);	/* 416d9b: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416da0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416da5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416daa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416daf: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416db4: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416dbeu; native_call(m, 0x41f0e0u);	/* 416db9: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 416dbe: mov ecx, dword ptr [esp + 0x30] */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 416dc2: lea eax, [ebx + 0x20] */
	{ DWORD v_ = 0x761524u; m->esp -= 4; M32(m->esp) = v_; }	/* 416dc5: push 0x761524 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416dca: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416dcb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x416dd1u; native_call(m, 0x403170u);	/* 416dcc: call 0x403170 */
	FPUSH((long double)(int)M32((DWORD)(0x4dc294u)));	/* 416dd1: fild dword ptr [0x4dc294] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416dd7: add esp, 0x2c */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc70u));	/* 416dda: fmul dword ptr [0x4dbc70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcc6cu));	/* 416de0: fadd dword ptr [0x4dcc6c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 416de6: call 0x49ec14 */
	m->esi = m->eax;	/* 416deb: mov esi, eax */
	m->ecx = 0xcu;	/* 416ded: mov ecx, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 416df2: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_416e6d;	/* 416df4: jle 0x416e6d */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416df6: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 416df8: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416dfc: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 416dfe: xor edx, edx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 416e00: lea ecx, [esp + 0x34] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 416e04: mov dword ptr [esp + 0x20], edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416e08: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc294u));	/* 416e0a: mov eax, dword ptr [0x4dc294] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 416e0f: mov dword ptr [esp + 0x24], edx */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 416e13: mov dword ptr [esp + 0x28], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416e17: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 416e18: mov dword ptr [esp + 0x30], edx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 416e1c: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416e21: push ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 416e22: mov dword ptr [esp + 0x3c], edx */
	m->esp -= 4; M32(m->esp) = 0x416e2bu; native_call(m, 0x49e9ddu);	/* 416e26: call 0x49e9dd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 416e2b: push esi */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 416e2c: lea edx, [esp + 0x30] */
	{ DWORD v_ = 0x4b02e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 416e30: push 0x4b02e0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 416e35: push edx */
	m->esp -= 4; M32(m->esp) = 0x416e3bu; native_call(m, 0x49e9ddu);	/* 416e36: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 416e3b: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416e3f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416e42: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416e44: add esp, 0x18 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416e47: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416e49: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416e4b: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 416e4d: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 416e51: mov esi, edi */
	m->edi = m->edx;	/* 416e53: mov edi, edx */
	m->edx = m->ecx;	/* 416e55: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416e57: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416e5a: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416e5c: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416e5e: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416e5f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416e62: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416e64: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416e66: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416e69: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_416e8f;	/* 416e6b: jmp 0x416e8f */
L_416e6d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416e6d: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 416e6f: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416e73: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416e75: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc294u));	/* 416e77: mov eax, dword ptr [0x4dc294] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 416e7c: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416e80: push eax */
	{ DWORD v_ = 0x4b02dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 416e81: push 0x4b02dc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416e86: push ecx */
	m->esp -= 4; M32(m->esp) = 0x416e8cu; native_call(m, 0x49e9ddu);	/* 416e87: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416e8c: add esp, 0xc */
L_416e8f:
	m->edi = 0x765824u;	/* 416e8f: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416e94: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416e97: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 416e99: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416e9d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416e9f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416ea1: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ea3: push 0x3f800000 */
	m->esi = m->edi;	/* 416ea8: mov esi, edi */
	m->edi = m->edx;	/* 416eaa: mov edi, edx */
	m->edx = m->ecx;	/* 416eac: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416eae: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416eb1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416eb3: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416eb5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416eb6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416eb9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416ebb: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 416ebd: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416ec1: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ec4: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416ec9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 416ecb: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416ed0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416ed3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416ed5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416ed7: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ed9: push 0x3f800000 */
	m->esi = m->edi;	/* 416ede: mov esi, edi */
	m->edi = m->edx;	/* 416ee0: mov edi, edx */
	m->edx = m->ecx;	/* 416ee2: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416ee4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416ee7: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416ee9: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416eeb: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416eec: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416eef: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416ef1: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416ef3: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416ef4: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416ef7: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416efc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x416f03u; native_call(m, 0x41f0e0u);	/* 416efe: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 416f03: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416f07: push eax */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 416f08: lea eax, [ebx + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416f0b: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 416f0c: push ebp */
	m->esp -= 4; M32(m->esp) = 0x416f12u; native_call(m, 0x4125f0u);	/* 416f0d: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416f12: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416f17: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416f1c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 416f21: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 416f26: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x416f30u; native_call(m, 0x41f0e0u);	/* 416f2b: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 416f30: mov ecx, dword ptr [esp + 0x44] */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 416f34: lea eax, [ebx + 0x34] */
	{ DWORD v_ = 0x7615a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 416f37: push 0x7615a4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416f3c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416f3d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x416f43u; native_call(m, 0x403170u);	/* 416f3e: call 0x403170 */
	FPUSH((long double)(int)M32((DWORD)(0x4dc298u)));	/* 416f43: fild dword ptr [0x4dc298] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416f49: add esp, 0x40 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc70u));	/* 416f4c: fmul dword ptr [0x4dbc70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dc548u));	/* 416f52: fadd dword ptr [0x4dc548] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 416f58: call 0x49ec14 */
	m->esi = m->eax;	/* 416f5d: mov esi, eax */
	m->ecx = 0xcu;	/* 416f5f: mov ecx, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 416f64: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_416fdf;	/* 416f66: jle 0x416fdf */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416f68: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 416f6a: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416f6e: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 416f70: xor edx, edx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 416f72: lea ecx, [esp + 0x34] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 416f76: mov dword ptr [esp + 0x20], edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416f7a: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc298u));	/* 416f7c: mov eax, dword ptr [0x4dc298] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 416f81: mov dword ptr [esp + 0x24], edx */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 416f85: mov dword ptr [esp + 0x28], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416f89: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 416f8a: mov dword ptr [esp + 0x30], edx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 416f8e: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416f93: push ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 416f94: mov dword ptr [esp + 0x3c], edx */
	m->esp -= 4; M32(m->esp) = 0x416f9du; native_call(m, 0x49e9ddu);	/* 416f98: call 0x49e9dd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 416f9d: push esi */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 416f9e: lea edx, [esp + 0x30] */
	{ DWORD v_ = 0x4b02e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 416fa2: push 0x4b02e0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 416fa7: push edx */
	m->esp -= 4; M32(m->esp) = 0x416fadu; native_call(m, 0x49e9ddu);	/* 416fa8: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 416fad: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416fb1: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416fb4: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416fb6: add esp, 0x18 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416fb9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 416fbb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 416fbd: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 416fbf: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 416fc3: mov esi, edi */
	m->edi = m->edx;	/* 416fc5: mov edi, edx */
	m->edx = m->ecx;	/* 416fc7: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416fc9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 416fcc: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 416fce: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 416fd0: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 416fd1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 416fd4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 416fd6: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 416fd8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 416fdb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_417001;	/* 416fdd: jmp 0x417001 */
L_416fdf:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 416fdf: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 416fe1: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 416fe5: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 416fe7: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc298u));	/* 416fe9: mov eax, dword ptr [0x4dc298] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 416fee: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 416ff2: push eax */
	{ DWORD v_ = 0x4b02dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 416ff3: push 0x4b02dc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 416ff8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x416ffeu; native_call(m, 0x49e9ddu);	/* 416ff9: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 416ffe: add esp, 0xc */
L_417001:
	m->edi = 0x765824u;	/* 417001: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417006: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417009: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41700b: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41700f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417011: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417013: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417015: push 0x3f800000 */
	m->esi = m->edi;	/* 41701a: mov esi, edi */
	m->edi = m->edx;	/* 41701c: mov edi, edx */
	m->edx = m->ecx;	/* 41701e: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417020: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417023: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417025: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417027: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417028: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41702b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41702d: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 41702f: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417033: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417036: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41703b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 41703d: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417042: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417045: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417047: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417049: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41704b: push 0x3f800000 */
	m->esi = m->edi;	/* 417050: mov esi, edi */
	m->edi = m->edx;	/* 417052: mov edi, edx */
	m->edx = m->ecx;	/* 417054: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417056: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417059: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41705b: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41705d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41705e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417061: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417063: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417065: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417066: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417069: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41706e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x417075u; native_call(m, 0x41f0e0u);	/* 417070: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 417075: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417079: push eax */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 41707a: lea eax, [ebx + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41707d: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41707e: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417084u; native_call(m, 0x4125f0u);	/* 41707f: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417084: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417089: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41708e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417093: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417098: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4170a2u; native_call(m, 0x41f0e0u);	/* 41709d: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 4170a2: mov ecx, dword ptr [esp + 0x44] */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 4170a6: lea eax, [ebx + 0x48] */
	{ DWORD v_ = 0x761624u; m->esp -= 4; M32(m->esp) = v_; }	/* 4170a9: push 0x761624 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4170ae: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4170af: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4170b5u; native_call(m, 0x403170u);	/* 4170b0: call 0x403170 */
	FPUSH((long double)(int)M32((DWORD)(0x4dc29cu)));	/* 4170b5: fild dword ptr [0x4dc29c] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4170bb: add esp, 0x40 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc70u));	/* 4170be: fmul dword ptr [0x4dbc70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dc248u));	/* 4170c4: fadd dword ptr [0x4dc248] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4170ca: call 0x49ec14 */
	m->esi = m->eax;	/* 4170cf: mov esi, eax */
	m->ecx = 0xcu;	/* 4170d1: mov ecx, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4170d6: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_417151;	/* 4170d8: jle 0x417151 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4170da: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 4170dc: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4170e0: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4170e2: xor edx, edx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 4170e4: lea ecx, [esp + 0x34] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 4170e8: mov dword ptr [esp + 0x20], edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4170ec: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc29cu));	/* 4170ee: mov eax, dword ptr [0x4dc29c] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 4170f3: mov dword ptr [esp + 0x24], edx */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 4170f7: mov dword ptr [esp + 0x28], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4170fb: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 4170fc: mov dword ptr [esp + 0x30], edx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 417100: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417105: push ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 417106: mov dword ptr [esp + 0x3c], edx */
	m->esp -= 4; M32(m->esp) = 0x41710fu; native_call(m, 0x49e9ddu);	/* 41710a: call 0x49e9dd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41710f: push esi */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 417110: lea edx, [esp + 0x30] */
	{ DWORD v_ = 0x4b02e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 417114: push 0x4b02e0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 417119: push edx */
	m->esp -= 4; M32(m->esp) = 0x41711fu; native_call(m, 0x49e9ddu);	/* 41711a: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 41711f: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417123: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417126: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417128: add esp, 0x18 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41712b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41712d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41712f: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 417131: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 417135: mov esi, edi */
	m->edi = m->edx;	/* 417137: mov edi, edx */
	m->edx = m->ecx;	/* 417139: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41713b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41713e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417140: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417142: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417143: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417146: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417148: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41714a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41714d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_417173;	/* 41714f: jmp 0x417173 */
L_417151:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417151: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 417153: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417157: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 417159: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc29cu));	/* 41715b: mov eax, dword ptr [0x4dc29c] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 417160: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417164: push eax */
	{ DWORD v_ = 0x4b02dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 417165: push 0x4b02dc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41716a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417170u; native_call(m, 0x49e9ddu);	/* 41716b: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417170: add esp, 0xc */
L_417173:
	m->edi = 0x765824u;	/* 417173: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417178: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41717b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41717d: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417181: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417183: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417185: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417187: push 0x3f800000 */
	m->esi = m->edi;	/* 41718c: mov esi, edi */
	m->edi = m->edx;	/* 41718e: mov edi, edx */
	m->edx = m->ecx;	/* 417190: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417192: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417195: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417197: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417199: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41719a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41719d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41719f: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 4171a1: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4171a5: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4171a8: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4171ad: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4171af: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4171b4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4171b7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4171b9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4171bb: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4171bd: push 0x3f800000 */
	m->esi = m->edi;	/* 4171c2: mov esi, edi */
	m->edi = m->edx;	/* 4171c4: mov edi, edx */
	m->edx = m->ecx;	/* 4171c6: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4171c8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4171cb: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4171cd: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4171cf: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4171d0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4171d3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4171d5: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4171d7: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4171d8: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4171db: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4171e0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4171e7u; native_call(m, 0x41f0e0u);	/* 4171e2: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4171e7: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4171eb: push eax */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 4171ec: lea eax, [ebx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4171ef: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4171f0: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4171f6u; native_call(m, 0x4125f0u);	/* 4171f1: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4171f6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4171fb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417200: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417205: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41720a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417214u; native_call(m, 0x41f0e0u);	/* 41720f: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 417214: mov ecx, dword ptr [esp + 0x44] */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 417218: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = 0x7616a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41721b: push 0x7616a4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417220: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417221: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417227u; native_call(m, 0x403170u);	/* 417222: call 0x403170 */
	FPUSH((long double)(int)M32((DWORD)(0x4dc2a0u)));	/* 417227: fild dword ptr [0x4dc2a0] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41722d: add esp, 0x40 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dbc70u));	/* 417230: fmul dword ptr [0x4dbc70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcb34u));	/* 417236: fadd dword ptr [0x4dcb34] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41723c: call 0x49ec14 */
	m->esi = m->eax;	/* 417241: mov esi, eax */
	m->ecx = 0xcu;	/* 417243: mov ecx, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 417248: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_4172c3;	/* 41724a: jle 0x4172c3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41724c: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 41724e: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417252: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 417254: xor edx, edx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 417256: lea ecx, [esp + 0x34] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 41725a: mov dword ptr [esp + 0x20], edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41725e: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc2a0u));	/* 417260: mov eax, dword ptr [0x4dc2a0] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 417265: mov dword ptr [esp + 0x24], edx */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 417269: mov dword ptr [esp + 0x28], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41726d: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 41726e: mov dword ptr [esp + 0x30], edx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 417272: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417277: push ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 417278: mov dword ptr [esp + 0x3c], edx */
	m->esp -= 4; M32(m->esp) = 0x417281u; native_call(m, 0x49e9ddu);	/* 41727c: call 0x49e9dd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 417281: push esi */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 417282: lea edx, [esp + 0x30] */
	{ DWORD v_ = 0x4b02e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 417286: push 0x4b02e0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41728b: push edx */
	m->esp -= 4; M32(m->esp) = 0x417291u; native_call(m, 0x49e9ddu);	/* 41728c: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 417291: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417295: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417298: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41729a: add esp, 0x18 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41729d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41729f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4172a1: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4172a3: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4172a7: mov esi, edi */
	m->edi = m->edx;	/* 4172a9: mov edi, edx */
	m->edx = m->ecx;	/* 4172ab: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4172ad: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4172b0: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4172b2: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4172b4: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4172b5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4172b8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4172ba: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4172bc: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4172bf: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_4172e5;	/* 4172c1: jmp 0x4172e5 */
L_4172c3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4172c3: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 4172c5: lea edi, [esp + 0x34] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4172c9: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4172cb: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc2a0u));	/* 4172cd: mov eax, dword ptr [0x4dc2a0] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 4172d2: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4172d6: push eax */
	{ DWORD v_ = 0x4b02dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4172d7: push 0x4b02dc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4172dc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4172e2u; native_call(m, 0x49e9ddu);	/* 4172dd: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4172e2: add esp, 0xc */
L_4172e5:
	m->edi = 0x765824u;	/* 4172e5: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4172ea: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4172ed: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4172ef: lea edx, [esp + 0x34] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4172f3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4172f5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4172f7: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4172f9: push 0x3f800000 */
	m->esi = m->edi;	/* 4172fe: mov esi, edi */
	m->edi = m->edx;	/* 417300: mov edi, edx */
	m->edx = m->ecx;	/* 417302: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417304: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417307: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417309: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41730b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41730c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41730f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417311: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 417313: lea edx, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417317: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41731a: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41731f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 417321: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417326: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417329: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41732b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41732d: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41732f: push 0x3f800000 */
	m->esi = m->edi;	/* 417334: mov esi, edi */
	m->edi = m->edx;	/* 417336: mov edi, edx */
	m->edx = m->ecx;	/* 417338: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41733a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41733d: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41733f: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417341: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417342: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417345: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417347: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417349: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41734a: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41734d: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417352: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x417359u; native_call(m, 0x41f0e0u);	/* 417354: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 417359: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41735d: push eax */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 41735e: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417361: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417362: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417368u; native_call(m, 0x4125f0u);	/* 417363: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417368: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41736d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417372: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417377: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41737c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417386u; native_call(m, 0x41f0e0u);	/* 417381: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 417386: mov ecx, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->ebx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 41738a: add ebx, 0x70 */
	{ DWORD v_ = 0x761724u; m->esp -= 4; M32(m->esp) = v_; }	/* 41738d: push 0x761724 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 417392: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417393: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417399u; native_call(m, 0x403170u);	/* 417394: call 0x403170 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417399: add esp, 0x40 */
	m->ecx = 0xcu;	/* 41739c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4173a1: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 4173a3: lea edi, [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc2a4u)));	/* 4173a7: fld dword ptr [0x4dc2a4] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4173ad: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4173af: stosw word ptr es:[edi], ax */
	goto L_417b6a;	/* 4173b1: jmp 0x417b6a */
L_4173b6:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4173b6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4173bb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4173c0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4173c5: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4173ca: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4173d4u; native_call(m, 0x41f0e0u);	/* 4173cf: call 0x41f0e0 */
	m->esi = (DWORD)(m->ebx + 0xcu);	/* 4173d4: lea esi, [ebx + 0xc] */
	m->eax = (DWORD)(m->ebp + 0xau);	/* 4173d7: lea eax, [ebp + 0xa] */
	{ DWORD v_ = 0x7619a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4173da: push 0x7619a4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4173df: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4173e0: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 4173e1: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x4173eau; native_call(m, 0x403170u);	/* 4173e5: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc228u)));	/* 4173ea: fld dword ptr [0x4dc228] */
	m->ecx = 0xcu;	/* 4173f0: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4173f5: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 4173f7: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 4173fb: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4173ff: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417402: rep stosd dword ptr es:[edi], eax */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 417404: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 417408: push 0x4b0334 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41740d: push ecx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41740e: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x417415u; native_call(m, 0x49e9ddu);	/* 417410: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 417415: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41741a: add esp, 0x10 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 41741d: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 417420: lea eax, [eax + edx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9078u)));	/* 417423: fild dword ptr [eax*4 + 0x9f9078] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41742a: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc228u));	/* 417430: fmul dword ptr [0x4dc228] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 417436: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 41743c: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417442: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417444: test ah, 0x41 */
	if (!m->zf) goto L_41746b;	/* 417447: jne 0x41746b */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 417449: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 41744f: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 417455: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 41745b: fmul dword ptr [0x4a947c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc228u));	/* 417461: fmul dword ptr [0x4dc228] */
	ST(0) = -ST(0);	/* 417467: fchs  */
	goto L_417471;	/* 417469: jmp 0x417471 */
L_41746b:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 41746b: fld dword ptr [0x4a93e8] */
L_417471:
	ST(1) = ST(1) + ST(0); FPOP();	/* 417471: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 417473: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417479: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41747b: test ah, 0x40 */
	if (!m->zf) goto L_41752e;	/* 41747e: jne 0x41752e */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 417484: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41748a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41748c: test ah, 1 */
	if (m->zf) goto L_4174be;	/* 41748f: je 0x4174be */
	{ long double t = ST(0); FPUSH(t); }	/* 417491: fld st(0) */
	ST(0) = -ST(0);	/* 417493: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dc228u)); FPOP();	/* 417495: fcomp dword ptr [0x4dc228] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41749b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41749d: test ah, 0x41 */
	if (!m->zf) goto L_4174ac;	/* 4174a0: jne 0x4174ac */
	ST(0) = ST(0); FPOP();	/* 4174a2: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc228u)));	/* 4174a4: fld dword ptr [0x4dc228] */
	ST(0) = -ST(0);	/* 4174aa: fchs  */
L_4174ac:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4174ac: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 4174af: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4174b3: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0268u; m->esp -= 4; M32(m->esp) = v_; }	/* 4174b6: push 0x4b0268 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4174bb: push ecx */
	goto L_4174ce;	/* 4174bc: jmp 0x4174ce */
L_4174be:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4174be: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 4174c1: lea edx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4174c5: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0230u; m->esp -= 4; M32(m->esp) = v_; }	/* 4174c8: push 0x4b0230 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4174cd: push edx */
L_4174ce:
	m->esp -= 4; M32(m->esp) = 0x4174d3u; native_call(m, 0x49e9ddu);	/* 4174ce: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 4174d3: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4174d7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4174da: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4174dc: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4174df: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4174e1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4174e3: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4174e5: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4174e9: mov esi, edi */
	m->edi = m->edx;	/* 4174eb: mov edi, edx */
	m->edx = m->ecx;	/* 4174ed: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4174ef: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4174f2: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4174f4: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4174f6: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4174f7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4174fa: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4174fc: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4174fe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417503: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417508: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41750b: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417510: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417511: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417513: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41751du; native_call(m, 0x41f0e0u);	/* 417518: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 41751d: lea eax, [esp + 0x48] */
	{ DWORD a_ = m->ebp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 417521: add ebp, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417527: push eax */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 417528: lea eax, [ebx + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41752b: push eax */
	goto L_417557;	/* 41752c: jmp 0x417557 */
L_41752e:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41752e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417533: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417538: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41753d: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41753f: push 0x76d438 */
	ST(0) = ST(0); FPOP();	/* 417544: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x41754bu; native_call(m, 0x41f0e0u);	/* 417546: call 0x41f0e0 */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 41754b: lea ecx, [esp + 0x48] */
	{ DWORD a_ = m->ebp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 41754f: add ebp, 0xd8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417555: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 417556: push esi */
L_417557:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417557: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41755du; native_call(m, 0x4125f0u);	/* 417558: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41755d: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417560: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417565: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41756a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41756f: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417574: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41757eu; native_call(m, 0x41f0e0u);	/* 417579: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 41757e: mov edx, dword ptr [esp + 0x24] */
	m->esi = (DWORD)(m->ebx + 0x20u);	/* 417582: lea esi, [ebx + 0x20] */
	{ DWORD v_ = 0x761a24u; m->esp -= 4; M32(m->esp) = v_; }	/* 417585: push 0x761a24 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41758a: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41758b: push edx */
	m->esp -= 4; M32(m->esp) = 0x417591u; native_call(m, 0x403170u);	/* 41758c: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc22cu)));	/* 417591: fld dword ptr [0x4dc22c] */
	m->ecx = 0xcu;	/* 417597: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41759c: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 41759e: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4175a2: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4175a5: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4175a7: fstp qword ptr [esp] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4175aa: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4175ac: lea eax, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 4175b0: push 0x4b0334 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4175b5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4175bbu; native_call(m, 0x49e9ddu);	/* 4175b6: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 4175bb: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4175c0: add esp, 0x10 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4175c3: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4175c6: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9078u)));	/* 4175c9: fild dword ptr [edx*4 + 0x9f9078] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4175d0: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc22cu));	/* 4175d6: fmul dword ptr [0x4dc22c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 4175dc: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 4175e2: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4175e8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4175ea: test ah, 0x41 */
	if (!m->zf) goto L_417611;	/* 4175ed: jne 0x417611 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 4175ef: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4175f5: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4175fb: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 417601: fmul dword ptr [0x4a947c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc22cu));	/* 417607: fmul dword ptr [0x4dc22c] */
	ST(0) = -ST(0);	/* 41760d: fchs  */
	goto L_417617;	/* 41760f: jmp 0x417617 */
L_417611:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 417611: fld dword ptr [0x4a93e8] */
L_417617:
	ST(1) = ST(1) + ST(0); FPOP();	/* 417617: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 417619: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41761f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417621: test ah, 0x40 */
	if (!m->zf) goto L_4176ce;	/* 417624: jne 0x4176ce */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41762a: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417630: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417632: test ah, 1 */
	if (m->zf) goto L_417664;	/* 417635: je 0x417664 */
	{ long double t = ST(0); FPUSH(t); }	/* 417637: fld st(0) */
	ST(0) = -ST(0);	/* 417639: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dc22cu)); FPOP();	/* 41763b: fcomp dword ptr [0x4dc22c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417641: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417643: test ah, 0x41 */
	if (!m->zf) goto L_417652;	/* 417646: jne 0x417652 */
	ST(0) = ST(0); FPOP();	/* 417648: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc22cu)));	/* 41764a: fld dword ptr [0x4dc22c] */
	ST(0) = -ST(0);	/* 417650: fchs  */
L_417652:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417652: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 417655: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417659: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0268u; m->esp -= 4; M32(m->esp) = v_; }	/* 41765c: push 0x4b0268 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417661: push eax */
	goto L_417674;	/* 417662: jmp 0x417674 */
L_417664:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417664: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 417667: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41766b: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0230u; m->esp -= 4; M32(m->esp) = v_; }	/* 41766e: push 0x4b0230 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417673: push ecx */
L_417674:
	m->esp -= 4; M32(m->esp) = 0x417679u; native_call(m, 0x49e9ddu);	/* 417674: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 417679: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41767d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417680: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417682: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417685: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417687: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417689: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41768b: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 41768f: mov esi, edi */
	m->edi = m->edx;	/* 417691: mov edi, edx */
	m->edx = m->ecx;	/* 417693: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417695: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417698: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41769a: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41769c: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41769d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4176a0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4176a2: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176a4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176a9: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4176ae: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176b1: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4176b6: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4176b7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176b9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4176c3u; native_call(m, 0x41f0e0u);	/* 4176be: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4176c3: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4176c7: push eax */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 4176c8: lea eax, [ebx + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4176cb: push eax */
	goto L_4176f1;	/* 4176cc: jmp 0x4176f1 */
L_4176ce:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176ce: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176d3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176d8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176dd: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176df: push 0x76d438 */
	ST(0) = ST(0); FPOP();	/* 4176e4: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x4176ebu; native_call(m, 0x41f0e0u);	/* 4176e6: call 0x41f0e0 */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 4176eb: lea ecx, [esp + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4176ef: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4176f0: push esi */
L_4176f1:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4176f1: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4176f7u; native_call(m, 0x4125f0u);	/* 4176f2: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4176f7: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176fa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4176ff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417704: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417709: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41770e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417718u; native_call(m, 0x41f0e0u);	/* 417713: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 417718: mov edx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 41771c: lea eax, [ebx + 0x34] */
	{ DWORD v_ = 0x761aa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41771f: push 0x761aa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417724: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 417725: push edx */
	m->esp -= 4; M32(m->esp) = 0x41772bu; native_call(m, 0x403170u);	/* 417726: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc230u)));	/* 41772b: fld dword ptr [0x4dc230] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 417731: fcomp dword ptr [0x4a93e8] */
	m->ecx = 0xcu;	/* 417737: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41773c: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 41773e: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417742: add esp, 0x20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417745: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc230u)));	/* 417747: fld dword ptr [0x4dc230] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41774d: stosw word ptr es:[edi], ax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41774f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417751: test ah, 1 */
	if (m->zf) goto L_417768;	/* 417754: je 0x417768 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417756: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 417759: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41775d: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 417760: push 0x4b02fc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417765: push eax */
	goto L_417778;	/* 417766: jmp 0x417778 */
L_417768:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417768: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 41776b: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41776f: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417772: push 0x4b02c4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417777: push ecx */
L_417778:
	m->esp -= 4; M32(m->esp) = 0x41777du; native_call(m, 0x49e9ddu);	/* 417778: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 41777d: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417782: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417785: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417787: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41778a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41778c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41778e: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 417790: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 417794: mov esi, edi */
	m->edi = m->edx;	/* 417796: mov edi, edx */
	m->edx = m->ecx;	/* 417798: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41779a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41779d: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41779f: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4177a1: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4177a2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4177a5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4177a7: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4177a9: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4177ad: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4177b0: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4177b5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4177b7: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4177bc: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4177bf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4177c1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4177c3: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4177c5: push 0x3f800000 */
	m->esi = m->edi;	/* 4177ca: mov esi, edi */
	m->edi = m->edx;	/* 4177cc: mov edi, edx */
	m->edx = m->ecx;	/* 4177ce: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4177d0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4177d3: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4177d5: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4177d7: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4177d8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4177db: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4177dd: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4177df: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4177e4: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4177e7: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4177e8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4177ea: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4177f4u; native_call(m, 0x41f0e0u);	/* 4177ef: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4177f4: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4177f8: push eax */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 4177f9: lea eax, [ebx + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4177fc: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4177fd: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417803u; native_call(m, 0x4125f0u);	/* 4177fe: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417803: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417808: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41780d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417812: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417817: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417821u; native_call(m, 0x41f0e0u);	/* 41781c: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 417821: mov ecx, dword ptr [esp + 0x44] */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 417825: lea eax, [ebx + 0x48] */
	{ DWORD v_ = 0x761b24u; m->esp -= 4; M32(m->esp) = v_; }	/* 417828: push 0x761b24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41782d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41782e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417834u; native_call(m, 0x403170u);	/* 41782f: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc234u)));	/* 417834: fld dword ptr [0x4dc234] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41783a: fcomp dword ptr [0x4a93e8] */
	m->ecx = 0xcu;	/* 417840: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417845: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 417847: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41784b: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41784e: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc234u)));	/* 417850: fld dword ptr [0x4dc234] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 417856: stosw word ptr es:[edi], ax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417858: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41785a: test ah, 1 */
	if (m->zf) goto L_417871;	/* 41785d: je 0x417871 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41785f: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 417862: lea edx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417866: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 417869: push 0x4b02fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41786e: push edx */
	goto L_417881;	/* 41786f: jmp 0x417881 */
L_417871:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417871: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 417874: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417878: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41787b: push 0x4b02c4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417880: push eax */
L_417881:
	m->esp -= 4; M32(m->esp) = 0x417886u; native_call(m, 0x49e9ddu);	/* 417881: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 417886: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41788b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41788e: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417890: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417893: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417895: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417897: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 417899: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 41789d: mov esi, edi */
	m->edi = m->edx;	/* 41789f: mov edi, edx */
	m->edx = m->ecx;	/* 4178a1: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4178a3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4178a6: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4178a8: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4178aa: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4178ab: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4178ae: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4178b0: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4178b2: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4178b6: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4178b9: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4178be: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4178c0: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4178c5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4178c8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4178ca: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4178cc: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4178ce: push 0x3f800000 */
	m->esi = m->edi;	/* 4178d3: mov esi, edi */
	m->edi = m->edx;	/* 4178d5: mov edi, edx */
	m->edx = m->ecx;	/* 4178d7: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4178d9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4178dc: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4178de: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4178e0: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4178e1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4178e4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4178e6: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4178e8: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4178ed: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4178f0: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4178f1: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4178f3: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4178fdu; native_call(m, 0x41f0e0u);	/* 4178f8: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4178fd: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417901: push eax */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 417902: lea eax, [ebx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417905: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417906: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41790cu; native_call(m, 0x4125f0u);	/* 417907: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41790c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417911: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417916: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41791b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417920: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41792au; native_call(m, 0x41f0e0u);	/* 417925: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 41792a: mov ecx, dword ptr [esp + 0x44] */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 41792e: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = 0x761ba4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417931: push 0x761ba4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417936: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417937: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41793du; native_call(m, 0x403170u);	/* 417938: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc238u)));	/* 41793d: fld dword ptr [0x4dc238] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 417943: fcomp dword ptr [0x4a93e8] */
	m->ecx = 0xcu;	/* 417949: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41794e: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 417950: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417954: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417957: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc238u)));	/* 417959: fld dword ptr [0x4dc238] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41795f: stosw word ptr es:[edi], ax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417961: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417963: test ah, 1 */
	if (m->zf) goto L_41797a;	/* 417966: je 0x41797a */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417968: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41796b: lea edx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41796f: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 417972: push 0x4b02fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 417977: push edx */
	goto L_41798a;	/* 417978: jmp 0x41798a */
L_41797a:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41797a: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41797d: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417981: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417984: push 0x4b02c4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417989: push eax */
L_41798a:
	m->esp -= 4; M32(m->esp) = 0x41798fu; native_call(m, 0x49e9ddu);	/* 41798a: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 41798f: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417994: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417997: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417999: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41799c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41799e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4179a0: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4179a2: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4179a6: mov esi, edi */
	m->edi = m->edx;	/* 4179a8: mov edi, edx */
	m->edx = m->ecx;	/* 4179aa: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4179ac: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4179af: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4179b1: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4179b3: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4179b4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4179b7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4179b9: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4179bb: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4179bf: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4179c2: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4179c7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 4179c9: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4179ce: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4179d1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4179d3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4179d5: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4179d7: push 0x3f800000 */
	m->esi = m->edi;	/* 4179dc: mov esi, edi */
	m->edi = m->edx;	/* 4179de: mov edi, edx */
	m->edx = m->ecx;	/* 4179e0: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4179e2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4179e5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4179e7: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4179e9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4179ea: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4179ed: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4179ef: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4179f1: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4179f6: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4179f9: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4179fa: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4179fc: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417a06u; native_call(m, 0x41f0e0u);	/* 417a01: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 417a06: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417a0a: push eax */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 417a0b: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417a0e: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417a0f: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417a15u; native_call(m, 0x4125f0u);	/* 417a10: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417a15: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417a1a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417a1f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417a24: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417a29: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417a33u; native_call(m, 0x41f0e0u);	/* 417a2e: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 417a33: mov ecx, dword ptr [esp + 0x44] */
	m->eax = (DWORD)(m->ebx + 0x70u);	/* 417a37: lea eax, [ebx + 0x70] */
	{ DWORD v_ = 0x761c24u; m->esp -= 4; M32(m->esp) = v_; }	/* 417a3a: push 0x761c24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417a3f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417a40: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417a46u; native_call(m, 0x403170u);	/* 417a41: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc23cu)));	/* 417a46: fld dword ptr [0x4dc23c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 417a4c: fcomp dword ptr [0x4a93e8] */
	m->ecx = 0xcu;	/* 417a52: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417a57: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 417a59: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417a5d: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417a60: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc23cu)));	/* 417a62: fld dword ptr [0x4dc23c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 417a68: stosw word ptr es:[edi], ax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417a6a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417a6c: test ah, 1 */
	if (m->zf) goto L_417a83;	/* 417a6f: je 0x417a83 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417a71: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 417a74: lea edx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417a78: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 417a7b: push 0x4b02fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 417a80: push edx */
	goto L_417a93;	/* 417a81: jmp 0x417a93 */
L_417a83:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417a83: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 417a86: lea eax, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417a8a: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417a8d: push 0x4b02c4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417a92: push eax */
L_417a93:
	m->esp -= 4; M32(m->esp) = 0x417a98u; native_call(m, 0x49e9ddu);	/* 417a93: call 0x49e9dd */
	m->edi = 0x7656a4u;	/* 417a98: mov edi, 0x7656a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417a9d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417aa0: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417aa2: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417aa5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417aa7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417aa9: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 417aab: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 417aaf: mov esi, edi */
	m->edi = m->edx;	/* 417ab1: mov edi, edx */
	m->edx = m->ecx;	/* 417ab3: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417ab5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417ab8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417aba: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417abc: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417abd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417ac0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417ac2: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 417ac4: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417ac8: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417acb: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417ad0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 417ad2: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417ad7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417ada: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417adc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417ade: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417ae0: push 0x3f800000 */
	m->esi = m->edi;	/* 417ae5: mov esi, edi */
	m->edi = m->edx;	/* 417ae7: mov edi, edx */
	m->edx = m->ecx;	/* 417ae9: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417aeb: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417aee: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417af0: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417af2: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417af3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417af6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417af8: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417afa: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417aff: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417b02: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417b03: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417b05: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417b0fu; native_call(m, 0x41f0e0u);	/* 417b0a: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 417b0f: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417b13: push eax */
	m->eax = (DWORD)(m->ebx + 0x70u);	/* 417b14: lea eax, [ebx + 0x70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417b17: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417b18: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417b1eu; native_call(m, 0x4125f0u);	/* 417b19: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417b1e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417b23: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417b28: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417b2d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417b32: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417b3cu; native_call(m, 0x41f0e0u);	/* 417b37: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 417b3c: mov ecx, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->ebx, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 417b40: add ebx, 0x84 */
	{ DWORD v_ = 0x761ca4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417b46: push 0x761ca4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 417b4b: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417b4c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417b52u; native_call(m, 0x403170u);	/* 417b4d: call 0x403170 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417b52: add esp, 0x40 */
	m->ecx = 0xcu;	/* 417b55: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417b5a: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 417b5c: lea edi, [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc240u)));	/* 417b60: fld dword ptr [0x4dc240] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417b66: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 417b68: stosw word ptr es:[edi], ax */
L_417b6a:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417b6a: sub esp, 8 */
L_417b6d:
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417b6d: fstp qword ptr [esp] */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 417b70: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 417b74: push 0x4b02fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 417b79: push edx */
	m->esp -= 4; M32(m->esp) = 0x417b7fu; native_call(m, 0x49e9ddu);	/* 417b7a: call 0x49e9dd */
	m->edi = 0x7657a4u;	/* 417b7f: mov edi, 0x7657a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417b84: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417b87: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 417b89: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417b8d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417b8f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417b91: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417b93: push 0x3f800000 */
	m->esi = m->edi;	/* 417b98: mov esi, edi */
	m->edi = m->edx;	/* 417b9a: mov edi, edx */
	m->edx = m->ecx;	/* 417b9c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417b9e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417ba1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417ba3: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417ba5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417ba6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417ba9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417bab: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 417bad: lea edx, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417bb1: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417bb4: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417bb9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 417bbb: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417bc0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417bc3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417bc5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417bc7: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417bc9: push 0x3f800000 */
	m->esi = m->edi;	/* 417bce: mov esi, edi */
	m->edi = m->edx;	/* 417bd0: mov edi, edx */
	m->edx = m->ecx;	/* 417bd2: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417bd4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417bd7: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417bd9: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417bdb: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417bdc: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417bdf: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417be1: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417be3: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417be4: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417be7: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417bec: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x417bf3u; native_call(m, 0x41f0e0u);	/* 417bee: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 417bf3: lea eax, [esp + 0x58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417bf7: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 417bf8: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417bf9: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417bffu; native_call(m, 0x4125f0u);	/* 417bfa: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417bff: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 417c02: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 417c03: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 417c04: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 417c05: pop ebx */
	m->esp = m->ebp;	/* 417c06: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 417c08: pop ebp */
	m->esp += 4 + 0; return;	/* 417c09: ret  */
L_417c0a:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c0a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c0f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c14: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c19: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c1e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417c28u; native_call(m, 0x41f0e0u);	/* 417c23: call 0x41f0e0 */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 417c28: lea eax, [ebx + 0xc] */
	m->ecx = (DWORD)(m->ebp + 0xau);	/* 417c2b: lea ecx, [ebp + 0xa] */
	{ DWORD v_ = 0x761ea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c2e: push 0x761ea4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417c33: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417c34: push ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 417c35: mov dword ptr [esp + 0x30], ecx */
	m->esp -= 4; M32(m->esp) = 0x417c3eu; native_call(m, 0x403170u);	/* 417c39: call 0x403170 */
	m->ecx = 0xcu;	/* 417c3e: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417c43: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 417c45: lea edi, [esp + 0x54] */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 417c49: lea edx, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417c4d: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 417c4f: stosw word ptr es:[edi], ax */
	m->edi = M32((DWORD)(0x4dce80u));	/* 417c51: mov edi, dword ptr [0x4dce80] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417c57: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 417c5a: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x7623a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417c5d: add edi, 0x7623a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417c63: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417c65: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417c67: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417c69: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c6b: push 0x3f800000 */
	m->esi = m->edi;	/* 417c70: mov esi, edi */
	m->edi = m->edx;	/* 417c72: mov edi, edx */
	m->edx = m->ecx;	/* 417c74: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417c76: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417c79: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417c7b: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417c7d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417c7e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417c81: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417c83: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c85: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417c8a: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c8d: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417c92: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417c93: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417c98: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x417c9fu; native_call(m, 0x41f0e0u);	/* 417c9a: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x68u);	/* 417c9f: lea eax, [esp + 0x68] */
	{ DWORD a_ = m->ebp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 417ca3: add ebp, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417ca9: push eax */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 417caa: lea eax, [ebx + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417cad: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417cae: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417cb4u; native_call(m, 0x4125f0u);	/* 417caf: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417cb4: add esp, 0x40 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417cb7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417cbc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417cc1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417cc6: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417ccb: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417cd5u; native_call(m, 0x41f0e0u);	/* 417cd0: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 417cd5: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 417cd9: lea eax, [ebx + 0x20] */
	{ DWORD v_ = 0x761f24u; m->esp -= 4; M32(m->esp) = v_; }	/* 417cdc: push 0x761f24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417ce1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417ce2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417ce8u; native_call(m, 0x403170u);	/* 417ce3: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce84u)));	/* 417ce8: fld dword ptr [0x4dce84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 417cee: fmul dword ptr [0x4a9480] */
	m->ecx = 0xcu;	/* 417cf4: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417cf9: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 417cfb: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417cff: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417d02: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417d04: fstp qword ptr [esp] */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 417d07: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 417d0b: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 417d10: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 417d11: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x417d18u; native_call(m, 0x49e9ddu);	/* 417d13: call 0x49e9dd */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcca0u)));	/* 417d18: fld dword ptr [0x4dcca0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce84u));	/* 417d1e: fmul dword ptr [0x4dce84] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417d24: add esp, 0x10 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 417d27: fmul dword ptr [0x4a9480] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 417d2d: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417d33: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417d35: test ah, 0x40 */
	if (!m->zf) goto L_417d7b;	/* 417d38: jne 0x417d7b */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 417d3a: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417d40: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417d42: test ah, 1 */
	if (m->zf) goto L_417d61;	/* 417d45: je 0x417d61 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417d47: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 417d4a: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417d4e: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 417d51: push 0x4b02fc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417d56: push eax */
	m->esp -= 4; M32(m->esp) = 0x417d5cu; native_call(m, 0x49e9ddu);	/* 417d57: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417d5c: add esp, 0x10 */
	goto L_417da3;	/* 417d5f: jmp 0x417da3 */
L_417d61:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417d61: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 417d64: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417d68: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417d6b: push 0x4b02c4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417d70: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417d76u; native_call(m, 0x49e9ddu);	/* 417d71: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417d76: add esp, 0x10 */
	goto L_417da3;	/* 417d79: jmp 0x417da3 */
L_417d7b:
	m->edi = 0x4b033cu;	/* 417d7b: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417d80: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417d83: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 417d85: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417d89: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 417d8b: fstp st(0) */
	m->ecx = ~m->ecx;	/* 417d8d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417d8f: sub edi, ecx */
	m->eax = m->ecx;	/* 417d91: mov eax, ecx */
	m->esi = m->edi;	/* 417d93: mov esi, edi */
	m->edi = m->edx;	/* 417d95: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417d97: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417d9a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 417d9c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417d9e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417da1: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_417da3:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417da3: or ecx, 0xffffffff */
	m->edi = 0x765aa4u;	/* 417da6: mov edi, 0x765aa4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417dab: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 417dad: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417db1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417db3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417db5: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417db7: push 0x3f800000 */
	m->esi = m->edi;	/* 417dbc: mov esi, edi */
	m->edi = m->edx;	/* 417dbe: mov edi, edx */
	m->edx = m->ecx;	/* 417dc0: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417dc2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417dc5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417dc7: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417dc9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417dca: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417dcd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417dcf: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 417dd1: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417dd5: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417dd8: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417ddd: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 417ddf: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417de4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417de7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417de9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417deb: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417ded: push 0x3f800000 */
	m->esi = m->edi;	/* 417df2: mov esi, edi */
	m->edi = m->edx;	/* 417df4: mov edi, edx */
	m->edx = m->ecx;	/* 417df6: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417df8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417dfb: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417dfd: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417dff: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417e00: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417e03: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417e05: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 417e07: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417e0b: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417e0e: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417e0f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 417e11: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417e15: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417e18: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417e1a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417e1c: sub edi, ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417e1e: push 0x76d438 */
	m->esi = m->edi;	/* 417e23: mov esi, edi */
	m->edi = m->edx;	/* 417e25: mov edi, edx */
	m->edx = m->ecx;	/* 417e27: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417e29: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417e2c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417e2e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417e30: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417e31: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417e34: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417e36: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417e38: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417e3b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x417e42u; native_call(m, 0x41f0e0u);	/* 417e3d: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 417e42: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417e46: push eax */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 417e47: lea eax, [ebx + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417e4a: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417e4b: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417e51u; native_call(m, 0x4125f0u);	/* 417e4c: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417e51: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417e54: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417e59: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417e5e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417e63: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417e68: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x417e72u; native_call(m, 0x41f0e0u);	/* 417e6d: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 417e72: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 417e76: lea eax, [ebx + 0x34] */
	{ DWORD v_ = 0x761fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417e79: push 0x761fa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417e7e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417e7f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417e85u; native_call(m, 0x403170u);	/* 417e80: call 0x403170 */
	m->ecx = 0xcu;	/* 417e85: mov ecx, 0xc */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce88u)));	/* 417e8a: fld dword ptr [0x4dce88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 417e90: fmul dword ptr [0x4a9480] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417e96: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 417e98: lea edi, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 417e9c: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 417e9e: fstp qword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417ea2: add esp, 0x18 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 417ea5: lea edx, [esp + 0x3c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 417ea9: stosw word ptr es:[edi], ax */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 417eab: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 417eb0: push edx */
	m->esp -= 4; M32(m->esp) = 0x417eb6u; native_call(m, 0x49e9ddu);	/* 417eb1: call 0x49e9dd */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce88u)));	/* 417eb6: fld dword ptr [0x4dce88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dc894u));	/* 417ebc: fmul dword ptr [0x4dc894] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417ec2: add esp, 0x10 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 417ec5: fmul dword ptr [0x4a9480] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 417ecb: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417ed1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417ed3: test ah, 0x40 */
	if (!m->zf) goto L_417f19;	/* 417ed6: jne 0x417f19 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 417ed8: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 417ede: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 417ee0: test ah, 1 */
	if (m->zf) goto L_417eff;	/* 417ee3: je 0x417eff */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417ee5: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 417ee8: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417eec: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 417eef: push 0x4b02fc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417ef4: push eax */
	m->esp -= 4; M32(m->esp) = 0x417efau; native_call(m, 0x49e9ddu);	/* 417ef5: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417efa: add esp, 0x10 */
	goto L_417f41;	/* 417efd: jmp 0x417f41 */
L_417eff:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417eff: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 417f02: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 417f06: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b02c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 417f09: push 0x4b02c4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 417f0e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x417f14u; native_call(m, 0x49e9ddu);	/* 417f0f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417f14: add esp, 0x10 */
	goto L_417f41;	/* 417f17: jmp 0x417f41 */
L_417f19:
	m->edi = 0x4b033cu;	/* 417f19: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417f1e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417f21: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 417f23: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417f27: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 417f29: fstp st(0) */
	m->ecx = ~m->ecx;	/* 417f2b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417f2d: sub edi, ecx */
	m->eax = m->ecx;	/* 417f2f: mov eax, ecx */
	m->esi = m->edi;	/* 417f31: mov esi, edi */
	m->edi = m->edx;	/* 417f33: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417f35: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417f38: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 417f3a: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417f3c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417f3f: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_417f41:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417f41: or ecx, 0xffffffff */
	m->edi = 0x765aa4u;	/* 417f44: mov edi, 0x765aa4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 417f49: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 417f4b: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417f4f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417f51: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417f53: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417f55: push 0x3f800000 */
	m->esi = m->edi;	/* 417f5a: mov esi, edi */
	m->edi = m->edx;	/* 417f5c: mov edi, edx */
	m->edx = m->ecx;	/* 417f5e: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417f60: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417f63: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417f65: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417f67: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417f68: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417f6b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417f6d: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 417f6f: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417f73: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417f76: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417f7b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 417f7d: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417f82: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417f85: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417f87: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417f89: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417f8b: push 0x3f800000 */
	m->esi = m->edi;	/* 417f90: mov esi, edi */
	m->edi = m->edx;	/* 417f92: mov edi, edx */
	m->edx = m->ecx;	/* 417f94: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417f96: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417f99: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417f9b: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417f9d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417f9e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417fa1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417fa3: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 417fa5: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417fa9: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417fac: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417fad: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 417faf: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417fb3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417fb6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 417fb8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 417fba: sub edi, ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 417fbc: push 0x76d438 */
	m->esi = m->edi;	/* 417fc1: mov esi, edi */
	m->edi = m->edx;	/* 417fc3: mov edi, edx */
	m->edx = m->ecx;	/* 417fc5: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417fc7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 417fca: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 417fcc: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 417fce: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 417fcf: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 417fd2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 417fd4: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 417fd6: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 417fd9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x417fe0u; native_call(m, 0x41f0e0u);	/* 417fdb: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 417fe0: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417fe4: push eax */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 417fe5: lea eax, [ebx + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 417fe8: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 417fe9: push ebp */
	m->esp -= 4; M32(m->esp) = 0x417fefu; native_call(m, 0x4125f0u);	/* 417fea: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 417fef: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417ff2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417ff7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 417ffc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418001: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418006: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418010u; native_call(m, 0x41f0e0u);	/* 41800b: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 418010: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 418014: lea eax, [ebx + 0x48] */
	{ DWORD v_ = 0x762024u; m->esp -= 4; M32(m->esp) = v_; }	/* 418017: push 0x762024 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41801c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41801d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x418023u; native_call(m, 0x403170u);	/* 41801e: call 0x403170 */
	m->ecx = 0xcu;	/* 418023: mov ecx, 0xc */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce8cu)));	/* 418028: fld dword ptr [0x4dce8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 41802e: fmul dword ptr [0x4a9480] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418034: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 418036: lea edi, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41803a: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 41803c: fstp qword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418040: add esp, 0x18 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 418043: lea edx, [esp + 0x3c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418047: stosw word ptr es:[edi], ax */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 418049: push 0x4b02fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41804e: push edx */
	m->esp -= 4; M32(m->esp) = 0x418054u; native_call(m, 0x49e9ddu);	/* 41804f: call 0x49e9dd */
	m->edi = 0x765aa4u;	/* 418054: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418059: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41805c: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 41805e: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418062: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418064: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418066: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418068: push 0x3f800000 */
	m->esi = m->edi;	/* 41806d: mov esi, edi */
	m->edi = m->edx;	/* 41806f: mov edi, edx */
	m->edx = m->ecx;	/* 418071: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418073: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418076: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418078: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41807a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41807b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41807e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418080: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 418082: lea edx, [esp + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418086: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418089: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41808e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 418090: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418095: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418098: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41809a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41809c: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41809e: push 0x3f800000 */
	m->esi = m->edi;	/* 4180a3: mov esi, edi */
	m->edi = m->edx;	/* 4180a5: mov edi, edx */
	m->edx = m->ecx;	/* 4180a7: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4180a9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4180ac: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4180ae: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4180b0: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4180b1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4180b4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4180b6: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4180b8: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4180b9: and ecx, 3 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4180bc: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4180c1: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4180c8u; native_call(m, 0x41f0e0u);	/* 4180c3: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 4180c8: lea eax, [esp + 0x58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4180cc: push eax */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 4180cd: lea eax, [ebx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4180d0: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4180d1: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4180d7u; native_call(m, 0x4125f0u);	/* 4180d2: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4180d7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4180dc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4180e1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4180e6: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4180eb: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4180f5u; native_call(m, 0x41f0e0u);	/* 4180f0: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 4180f5: mov ecx, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4180f9: add esp, 0x44 */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 4180fc: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = 0x7620a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4180ff: push 0x7620a4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418104: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418105: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41810bu; native_call(m, 0x403170u);	/* 418106: call 0x403170 */
	m->ecx = 0xcu;	/* 41810b: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418110: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 418112: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418116: add esp, 4 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce90u)));	/* 418119: fld dword ptr [0x4dce90] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41811f: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418121: stosw word ptr es:[edi], ax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 418123: fstp qword ptr [esp] */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 418126: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 41812a: push 0x4b0354 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41812f: push edx */
	m->esp -= 4; M32(m->esp) = 0x418135u; native_call(m, 0x49e9ddu);	/* 418130: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 418135: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41813a: add esp, 0x10 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 41813d: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 418140: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f907cu)));	/* 418143: fild dword ptr [edx*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41814a: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce90u));	/* 418150: fmul dword ptr [0x4dce90] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc230u)));	/* 418156: fld dword ptr [0x4dc230] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41815c: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce90u));	/* 418162: fmul dword ptr [0x4dce90] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 418168: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41816a: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 418170: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 418176: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 418178: test ah, 0x41 */
	if (!m->zf) goto L_4181a3;	/* 41817b: jne 0x4181a3 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41817d: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 418183: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 418189: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 41818f: fmul dword ptr [0x4a947c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce90u)));	/* 418195: fld dword ptr [0x4dce90] */
	ST(0) = ST(0) + ST(2);	/* 41819b: fadd st(2) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 41819d: fmulp st(1) */
	ST(0) = -ST(0);	/* 41819f: fchs  */
	goto L_4181a9;	/* 4181a1: jmp 0x4181a9 */
L_4181a3:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 4181a3: fld dword ptr [0x4a93e8] */
L_4181a9:
	ST(1) = ST(1) + ST(0); FPOP();	/* 4181a9: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4181ab: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4181b1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4181b3: test ah, 0x40 */
	if (!m->zf) goto L_418214;	/* 4181b6: jne 0x418214 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4181b8: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4181be: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4181c0: test ah, 1 */
	if (m->zf) goto L_4181fa;	/* 4181c3: je 0x4181fa */
	{ long double t = ST(0); FPUSH(t); }	/* 4181c5: fld st(0) */
	ST(0) = -ST(0);	/* 4181c7: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dce90u)); FPOP();	/* 4181c9: fcomp dword ptr [0x4dce90] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4181cf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4181d1: test ah, 0x41 */
	if (!m->zf) goto L_4181e0;	/* 4181d4: jne 0x4181e0 */
	ST(0) = ST(0); FPOP();	/* 4181d6: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce90u)));	/* 4181d8: fld dword ptr [0x4dce90] */
	ST(0) = -ST(0);	/* 4181de: fchs  */
L_4181e0:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4181e0: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4181e3: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4181e7: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b024cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4181ea: push 0x4b024c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4181ef: push eax */
	m->esp -= 4; M32(m->esp) = 0x4181f5u; native_call(m, 0x49e9ddu);	/* 4181f0: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4181f5: add esp, 0x10 */
	goto L_418244;	/* 4181f8: jmp 0x418244 */
L_4181fa:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4181fa: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 4181fd: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 418201: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0244u; m->esp -= 4; M32(m->esp) = v_; }	/* 418204: push 0x4b0244 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418209: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41820fu; native_call(m, 0x49e9ddu);	/* 41820a: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41820f: add esp, 0x10 */
	goto L_418244;	/* 418212: jmp 0x418244 */
L_418214:
	m->edi = 0x4b033cu;	/* 418214: mov edi, 0x4b033c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418219: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41821c: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 41821e: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418222: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 418224: fstp st(0) */
	m->ecx = ~m->ecx;	/* 418226: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418228: sub edi, ecx */
	m->esi = m->edi;	/* 41822a: mov esi, edi */
	m->edi = m->edx;	/* 41822c: mov edi, edx */
	m->edx = m->ecx;	/* 41822e: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418230: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418233: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418235: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418237: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418238: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41823b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41823d: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41823f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418242: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_418244:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418244: or ecx, 0xffffffff */
	m->edi = 0x7658a4u;	/* 418247: mov edi, 0x7658a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41824c: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 41824e: lea edx, [esp + 0x20] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418252: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418254: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418256: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418258: push 0x3f800000 */
	m->esi = m->edi;	/* 41825d: mov esi, edi */
	m->edi = m->edx;	/* 41825f: mov edi, edx */
	m->edx = m->ecx;	/* 418261: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418263: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418266: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418268: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41826a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41826b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41826e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418270: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 418272: lea edx, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418276: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418279: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41827e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 418280: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418285: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418288: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41828a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41828c: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41828e: push 0x3f800000 */
	m->esi = m->edi;	/* 418293: mov esi, edi */
	m->edi = m->edx;	/* 418295: mov edi, edx */
	m->edx = m->ecx;	/* 418297: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418299: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41829c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41829e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4182a0: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4182a1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4182a4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4182a6: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 4182a8: lea edx, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4182ac: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4182af: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4182b0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 4182b2: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4182b6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4182b9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4182bb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4182bd: sub edi, ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4182bf: push 0x76d438 */
	m->esi = m->edi;	/* 4182c4: mov esi, edi */
	m->edi = m->edx;	/* 4182c6: mov edi, edx */
	m->edx = m->ecx;	/* 4182c8: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4182ca: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4182cd: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4182cf: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4182d1: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4182d2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4182d5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4182d7: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4182d9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4182dc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4182e3u; native_call(m, 0x41f0e0u);	/* 4182de: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 4182e3: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4182e7: push eax */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 4182e8: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4182eb: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4182ec: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4182f2u; native_call(m, 0x4125f0u);	/* 4182ed: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4182f2: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4182f5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4182fa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4182ff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418304: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418309: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418313u; native_call(m, 0x41f0e0u);	/* 41830e: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 418313: mov edx, dword ptr [esp + 0x24] */
	m->ecx = (DWORD)(m->ebx + 0x70u);	/* 418317: lea ecx, [ebx + 0x70] */
	{ DWORD v_ = 0x762124u; m->esp -= 4; M32(m->esp) = v_; }	/* 41831a: push 0x762124 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41831f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 418320: push edx */
	m->esp -= 4; M32(m->esp) = 0x418326u; native_call(m, 0x403170u);	/* 418321: call 0x403170 */
	m->ecx = 0xcu;	/* 418326: mov ecx, 0xc */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce94u)));	/* 41832b: fld dword ptr [0x4dce94] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418331: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 418333: lea edi, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 418337: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 418339: fstp qword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41833d: add esp, 0x18 */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418340: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 418342: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x4b0228u; m->esp -= 4; M32(m->esp) = v_; }	/* 418346: push 0x4b0228 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41834b: push eax */
	m->esp -= 4; M32(m->esp) = 0x418351u; native_call(m, 0x49e9ddu);	/* 41834c: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 418351: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418355: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418358: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 41835a: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41835e: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce9cu)));	/* 418360: fld dword ptr [0x4dce9c] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 418366: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 41836a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41836c: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41836e: add esp, 8 */
	m->esi = m->edi;	/* 418371: mov esi, edi */
	m->edi = m->edx;	/* 418373: mov edi, edx */
	m->edx = m->ecx;	/* 418375: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418377: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41837a: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41837c: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41837e: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41837f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418382: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418384: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 418386: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41838a: and ecx, 3 */
	{ DWORD v_ = 0x4b021cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41838d: push 0x4b021c */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418392: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418394: push eax */
	m->esp -= 4; M32(m->esp) = 0x41839au; native_call(m, 0x49e9ddu);	/* 418395: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 41839a: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41839e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4183a1: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 4183a3: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4183a7: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce98u)));	/* 4183a9: fld dword ptr [0x4dce98] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 4183af: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 4183b3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4183b5: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4183b7: add esp, 8 */
	m->esi = m->edi;	/* 4183ba: mov esi, edi */
	m->edi = m->edx;	/* 4183bc: mov edi, edx */
	m->edx = m->ecx;	/* 4183be: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4183c0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4183c3: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4183c5: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4183c7: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4183c8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4183cb: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4183cd: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4183cf: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4183d3: and ecx, 3 */
	{ DWORD v_ = 0x4b0214u; m->esp -= 4; M32(m->esp) = v_; }	/* 4183d6: push 0x4b0214 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4183db: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4183dd: push eax */
	m->esp -= 4; M32(m->esp) = 0x4183e3u; native_call(m, 0x49e9ddu);	/* 4183de: call 0x49e9dd */
	m->edi = 0x7658a4u;	/* 4183e3: mov edi, 0x7658a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4183e8: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4183eb: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 4183ed: lea edx, [esp + 0x30] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4183f1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4183f3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4183f5: sub edi, ecx */
	m->esi = m->edi;	/* 4183f7: mov esi, edi */
	m->edi = m->edx;	/* 4183f9: mov edi, edx */
	m->edx = m->ecx;	/* 4183fb: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4183fd: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418400: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418402: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418404: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418405: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418408: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41840a: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41840c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41840f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 418411: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418415: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418418: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41841a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41841c: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 41841e: lea edx, [esp + 0x44] */
	m->esi = m->edi;	/* 418422: mov esi, edi */
	m->edi = m->edx;	/* 418424: mov edi, edx */
	m->edx = m->ecx;	/* 418426: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418428: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41842b: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41842d: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41842f: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418430: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418433: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418435: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418437: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41843c: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418441: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418444: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418449: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41844a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41844c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418456u; native_call(m, 0x41f0e0u);	/* 418451: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 418456: lea eax, [esp + 0x58] */
	m->ecx = (DWORD)(m->ebx + 0x7au);	/* 41845a: lea ecx, [ebx + 0x7a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41845d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41845e: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41845f: push ebp */
	m->esp -= 4; M32(m->esp) = 0x418465u; native_call(m, 0x4125f0u);	/* 418460: call 0x4125f0 */
	m->eax = M32((DWORD)(0x9f1818u));	/* 418465: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41846a: add esp, 0x30 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 41846d: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 418470: lea eax, [eax + edx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f907cu)));	/* 418473: fild dword ptr [eax*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41847a: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce94u));	/* 418480: fmul dword ptr [0x4dce94] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc234u)));	/* 418486: fld dword ptr [0x4dc234] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41848c: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce94u));	/* 418492: fmul dword ptr [0x4dce94] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 418498: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41849a: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 4184a0: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4184a6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4184a8: test ah, 0x41 */
	if (!m->zf) goto L_4184d3;	/* 4184ab: jne 0x4184d3 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 4184ad: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4184b3: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 4184b9: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 4184bf: fmul dword ptr [0x4a947c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce94u)));	/* 4184c5: fld dword ptr [0x4dce94] */
	ST(0) = ST(0) + ST(2);	/* 4184cb: fadd st(2) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 4184cd: fmulp st(1) */
	ST(0) = -ST(0);	/* 4184cf: fchs  */
	goto L_4184d9;	/* 4184d1: jmp 0x4184d9 */
L_4184d3:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 4184d3: fld dword ptr [0x4a93e8] */
L_4184d9:
	ST(1) = ST(1) + ST(0); FPOP();	/* 4184d9: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4184db: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4184e1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4184e3: test ah, 1 */
	if (m->zf) goto L_418511;	/* 4184e6: je 0x418511 */
	ST(0) = -ST(0);	/* 4184e8: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dce94u));	/* 4184ea: fcom dword ptr [0x4dce94] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4184f0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4184f2: test ah, 0x41 */
	if (!m->zf) goto L_4184ff;	/* 4184f5: jne 0x4184ff */
	ST(0) = ST(0); FPOP();	/* 4184f7: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce94u)));	/* 4184f9: fld dword ptr [0x4dce94] */
L_4184ff:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4184ff: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 418502: lea ecx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 418506: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0208u; m->esp -= 4; M32(m->esp) = v_; }	/* 418509: push 0x4b0208 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41850e: push ecx */
	goto L_418521;	/* 41850f: jmp 0x418521 */
L_418511:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418511: sub esp, 8 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 418514: lea edx, [esp + 0x3c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 418518: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b01fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 41851b: push 0x4b01fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 418520: push edx */
L_418521:
	m->esp -= 4; M32(m->esp) = 0x418526u; native_call(m, 0x49e9ddu);	/* 418521: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9f1818u));	/* 418526: mov eax, dword ptr [0x9f1818] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41852b: add esp, 0x10 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 41852e: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 418531: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f907cu)));	/* 418534: fild dword ptr [edx*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41853b: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce9cu));	/* 418541: fmul dword ptr [0x4dce9c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc238u)));	/* 418547: fld dword ptr [0x4dc238] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41854d: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce9cu));	/* 418553: fmul dword ptr [0x4dce9c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 418559: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41855b: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 418561: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 418567: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 418569: test ah, 0x41 */
	if (!m->zf) goto L_418594;	/* 41856c: jne 0x418594 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41856e: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 418574: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 41857a: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 418580: fmul dword ptr [0x4a947c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce9cu)));	/* 418586: fld dword ptr [0x4dce9c] */
	ST(0) = ST(0) + ST(2);	/* 41858c: fadd st(2) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 41858e: fmulp st(1) */
	ST(0) = -ST(0);	/* 418590: fchs  */
	goto L_41859a;	/* 418592: jmp 0x41859a */
L_418594:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 418594: fld dword ptr [0x4a93e8] */
L_41859a:
	ST(1) = ST(1) + ST(0); FPOP();	/* 41859a: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41859c: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4185a2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4185a4: test ah, 1 */
	if (m->zf) goto L_4185d2;	/* 4185a7: je 0x4185d2 */
	ST(0) = -ST(0);	/* 4185a9: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dce9cu));	/* 4185ab: fcom dword ptr [0x4dce9c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4185b1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4185b3: test ah, 0x41 */
	if (!m->zf) goto L_4185c0;	/* 4185b6: jne 0x4185c0 */
	ST(0) = ST(0); FPOP();	/* 4185b8: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce9cu)));	/* 4185ba: fld dword ptr [0x4dce9c] */
L_4185c0:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4185c0: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4185c3: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4185c7: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0208u; m->esp -= 4; M32(m->esp) = v_; }	/* 4185ca: push 0x4b0208 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4185cf: push eax */
	goto L_4185e2;	/* 4185d0: jmp 0x4185e2 */
L_4185d2:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4185d2: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 4185d5: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4185d9: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b01fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4185dc: push 0x4b01fc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4185e1: push ecx */
L_4185e2:
	m->esp -= 4; M32(m->esp) = 0x4185e7u; native_call(m, 0x49e9ddu);	/* 4185e2: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 4185e7: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4185eb: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4185ee: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4185f0: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4185f3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4185f5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4185f7: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4185f9: lea edx, [esp + 0x34] */
	m->esi = m->edi;	/* 4185fd: mov esi, edi */
	m->edi = m->edx;	/* 4185ff: mov edi, edx */
	m->edx = m->ecx;	/* 418601: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418603: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418606: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418608: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41860a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41860b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41860e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f1818u));	/* 418610: mov eax, dword ptr [0x9f1818] */
	m->ecx = m->edx;	/* 418615: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418617: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41861a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 41861c: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 41861f: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f907cu)));	/* 418622: fild dword ptr [edx*4 + 0x9f907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 418629: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce98u));	/* 41862f: fmul dword ptr [0x4dce98] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc23cu)));	/* 418635: fld dword ptr [0x4dc23c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41863b: fmul dword ptr [0x4a9420] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4dce98u));	/* 418641: fmul dword ptr [0x4dce98] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 418647: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 418649: fld dword ptr [0x4dc78c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dcb0cu)); FPOP();	/* 41864f: fcomp dword ptr [0x4dcb0c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 418655: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 418657: test ah, 0x41 */
	if (!m->zf) goto L_418682;	/* 41865a: jne 0x418682 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc78cu)));	/* 41865c: fld dword ptr [0x4dc78c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 418662: fsub dword ptr [0x4dcb0c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(0x4dcb0cu));	/* 418668: fdiv dword ptr [0x4dcb0c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 41866e: fmul dword ptr [0x4a947c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce98u)));	/* 418674: fld dword ptr [0x4dce98] */
	ST(0) = ST(0) + ST(2);	/* 41867a: fadd st(2) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 41867c: fmulp st(1) */
	ST(0) = -ST(0);	/* 41867e: fchs  */
	goto L_418688;	/* 418680: jmp 0x418688 */
L_418682:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 418682: fld dword ptr [0x4a93e8] */
L_418688:
	ST(1) = ST(1) + ST(0); FPOP();	/* 418688: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 41868a: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 418690: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 418692: test ah, 1 */
	if (m->zf) goto L_4186c0;	/* 418695: je 0x4186c0 */
	ST(0) = -ST(0);	/* 418697: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4dce98u));	/* 418699: fcom dword ptr [0x4dce98] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41869f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4186a1: test ah, 0x41 */
	if (!m->zf) goto L_4186ae;	/* 4186a4: jne 0x4186ae */
	ST(0) = ST(0); FPOP();	/* 4186a6: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dce98u)));	/* 4186a8: fld dword ptr [0x4dce98] */
L_4186ae:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4186ae: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4186b1: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4186b5: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b01f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4186b8: push 0x4b01f4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4186bd: push eax */
	goto L_4186d0;	/* 4186be: jmp 0x4186d0 */
L_4186c0:
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4186c0: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 4186c3: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4186c7: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b01ecu; m->esp -= 4; M32(m->esp) = v_; }	/* 4186ca: push 0x4b01ec */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4186cf: push ecx */
L_4186d0:
	m->esp -= 4; M32(m->esp) = 0x4186d5u; native_call(m, 0x49e9ddu);	/* 4186d0: call 0x49e9dd */
	m->edi = 0x7658a4u;	/* 4186d5: mov edi, 0x7658a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4186da: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4186dd: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4186df: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4186e2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4186e4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4186e6: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 4186e8: lea edx, [esp + 0x20] */
	m->esi = m->edi;	/* 4186ec: mov esi, edi */
	m->edi = m->edx;	/* 4186ee: mov edi, edx */
	m->edx = m->ecx;	/* 4186f0: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4186f2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4186f5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4186f7: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4186f9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4186fa: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4186fd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4186ff: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 418701: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418705: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418708: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41870d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 41870f: lea edi, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418713: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418716: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418718: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41871a: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41871c: push 0x3f800000 */
	m->esi = m->edi;	/* 418721: mov esi, edi */
	m->edi = m->edx;	/* 418723: mov edi, edx */
	m->edx = m->ecx;	/* 418725: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418727: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41872a: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41872c: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41872e: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41872f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418732: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418734: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418736: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41873b: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41873e: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41873f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418741: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41874bu; native_call(m, 0x41f0e0u);	/* 418746: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 41874b: lea eax, [esp + 0x48] */
	m->ecx = (DWORD)(m->ebx + 0x84u);	/* 41874f: lea ecx, [ebx + 0x84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418755: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418756: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418757: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41875du; native_call(m, 0x4125f0u);	/* 418758: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41875d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418762: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418767: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41876c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418771: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41877bu; native_call(m, 0x41f0e0u);	/* 418776: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 41877b: mov edx, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->ebx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 41877f: add ebx, 0x98 */
	{ DWORD v_ = 0x7621a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 418785: push 0x7621a4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41878a: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41878b: push edx */
	m->esp -= 4; M32(m->esp) = 0x418791u; native_call(m, 0x403170u);	/* 41878c: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcea0u)));	/* 418791: fld dword ptr [0x4dcea0] */
	m->ecx = 0xcu;	/* 418797: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41879c: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x74u);	/* 41879e: lea edi, [esp + 0x74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4187a2: add esp, 0x40 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4187a5: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4187a7: sub esp, 8 */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4187aa: stosw word ptr es:[edi], ax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 4187ac: fstp qword ptr [esp] */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4187af: lea eax, [esp + 0x3c] */
	{ DWORD v_ = 0x4b027cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4187b3: push 0x4b027c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4187b8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4187beu; native_call(m, 0x49e9ddu);	/* 4187b9: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187be: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187c3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187c8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187cd: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187cf: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4187d9u; native_call(m, 0x41f0e0u);	/* 4187d4: call 0x41f0e0 */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 4187d9: lea ecx, [esp + 0x58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4187dd: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4187de: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4187df: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4187e5u; native_call(m, 0x4125f0u);	/* 4187e0: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4187e5: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4187e8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4187e9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4187ea: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4187eb: pop ebx */
	m->esp = m->ebp;	/* 4187ec: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4187ee: pop ebp */
	m->esp += 4 + 0; return;	/* 4187ef: ret  */
L_4187f0:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187f0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187f5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187fa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4187ff: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418804: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41880eu; native_call(m, 0x41f0e0u);	/* 418809: call 0x41f0e0 */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 41880e: lea eax, [ebx + 0xc] */
	m->esi = (DWORD)(m->ebp + 0xau);	/* 418811: lea esi, [ebp + 0xa] */
	{ DWORD v_ = 0x762da4u; m->esp -= 4; M32(m->esp) = v_; }	/* 418814: push 0x762da4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418819: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41881a: push esi */
	M32((DWORD)(m->esp + 0x30u)) = m->esi;	/* 41881b: mov dword ptr [esp + 0x30], esi */
	m->esp -= 4; M32(m->esp) = 0x418824u; native_call(m, 0x403170u);	/* 41881f: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcaa0u)));	/* 418824: fld dword ptr [0x4dcaa0] */
	m->ecx = 0xcu;	/* 41882a: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41882f: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 418831: fstp qword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 418835: lea edi, [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418839: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41883c: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41883e: lea edx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0274u; m->esp -= 4; M32(m->esp) = v_; }	/* 418842: push 0x4b0274 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 418847: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418848: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x41884fu; native_call(m, 0x49e9ddu);	/* 41884a: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41884f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418854: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418859: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41885e: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418860: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41886au; native_call(m, 0x41f0e0u);	/* 418865: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 41886a: lea eax, [esp + 0x58] */
	{ DWORD a_ = m->ebp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 41886e: add ebp, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418874: push eax */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 418875: lea eax, [ebx + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418878: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418879: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41887fu; native_call(m, 0x4125f0u);	/* 41887a: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41887f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418884: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418889: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41888e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418893: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41889du; native_call(m, 0x41f0e0u);	/* 418898: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41889d: add esp, 0x44 */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 4188a0: lea eax, [ebx + 0x20] */
	{ DWORD v_ = 0x762e24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4188a3: push 0x762e24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4188a8: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4188a9: push esi */
	m->esp -= 4; M32(m->esp) = 0x4188afu; native_call(m, 0x403170u);	/* 4188aa: call 0x403170 */
	m->ecx = 0xcu;	/* 4188af: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4188b4: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 4188b6: lea edi, [esp + 0x40] */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 4188ba: lea edx, [esp + 0x40] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4188be: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dcaa8u));	/* 4188c0: mov ecx, dword ptr [0x4dcaa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4188c6: push ecx */
	{ DWORD v_ = 0x4b02e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4188c7: push 0x4b02e8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4188cc: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4188cd: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x4188d4u; native_call(m, 0x49e9ddu);	/* 4188cf: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4188d4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4188d9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4188de: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4188e3: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4188e5: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4188efu; native_call(m, 0x41f0e0u);	/* 4188ea: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 4188ef: lea eax, [esp + 0x60] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4188f3: push eax */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 4188f4: lea eax, [ebx + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4188f7: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4188f8: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4188feu; native_call(m, 0x4125f0u);	/* 4188f9: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4188fe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418903: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418908: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41890d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418912: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41891cu; native_call(m, 0x41f0e0u);	/* 418917: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41891c: add esp, 0x4c */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 41891f: lea eax, [ebx + 0x34] */
	{ DWORD v_ = 0x762ea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 418922: push 0x762ea4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418927: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 418928: push esi */
	m->esp -= 4; M32(m->esp) = 0x41892eu; native_call(m, 0x403170u);	/* 418929: call 0x403170 */
	m->ecx = 0xcu;	/* 41892e: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418933: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 418935: lea edi, [esp + 0x40] */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 418939: lea edx, [esp + 0x40] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41893d: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dcab4u));	/* 41893f: mov ecx, dword ptr [0x4dcab4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418945: push ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 418946: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41894b: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41894c: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x418953u; native_call(m, 0x49e9ddu);	/* 41894e: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418953: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418958: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41895d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 418962: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418964: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41896eu; native_call(m, 0x41f0e0u);	/* 418969: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 41896e: lea eax, [esp + 0x60] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418972: push eax */
	m->eax = (DWORD)(m->ebx + 0x34u);	/* 418973: lea eax, [ebx + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418976: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418977: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41897du; native_call(m, 0x4125f0u);	/* 418978: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41897d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418982: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418987: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41898c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418991: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41899bu; native_call(m, 0x41f0e0u);	/* 418996: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41899b: add esp, 0x4c */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 41899e: lea eax, [ebx + 0x48] */
	{ DWORD v_ = 0x762f24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4189a1: push 0x762f24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4189a6: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4189a7: push esi */
	m->esp -= 4; M32(m->esp) = 0x4189adu; native_call(m, 0x403170u);	/* 4189a8: call 0x403170 */
	m->ecx = 0xcu;	/* 4189ad: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4189b2: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 4189b4: lea edi, [esp + 0x40] */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 4189b8: lea edx, [esp + 0x40] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4189bc: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dcab8u));	/* 4189be: mov ecx, dword ptr [0x4dcab8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4189c4: push ecx */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 4189c5: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4189ca: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4189cb: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x4189d2u; native_call(m, 0x49e9ddu);	/* 4189cd: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4189d2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4189d7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4189dc: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4189e1: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4189e3: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4189edu; native_call(m, 0x41f0e0u);	/* 4189e8: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 4189ed: lea eax, [esp + 0x60] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4189f1: push eax */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 4189f2: lea eax, [ebx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4189f5: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4189f6: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4189fcu; native_call(m, 0x4125f0u);	/* 4189f7: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4189fc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a01: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a06: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a0b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a10: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418a1au; native_call(m, 0x41f0e0u);	/* 418a15: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418a1a: add esp, 0x4c */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 418a1d: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = 0x762fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a20: push 0x762fa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418a25: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 418a26: push esi */
	m->esp -= 4; M32(m->esp) = 0x418a2cu; native_call(m, 0x403170u);	/* 418a27: call 0x403170 */
	m->ecx = 0xcu;	/* 418a2c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418a31: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 418a33: lea edi, [esp + 0x40] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 418a37: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dcabcu));	/* 418a39: mov ecx, dword ptr [0x4dcabc] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418a3f: stosw word ptr es:[edi], ax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418a41: push ecx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 418a42: lea edx, [esp + 0x44] */
	{ DWORD v_ = 0x4b02e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a46: push 0x4b02e8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 418a4b: push edx */
	m->esp -= 4; M32(m->esp) = 0x418a51u; native_call(m, 0x49e9ddu);	/* 418a4c: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a51: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a56: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a5b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a60: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a62: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418a6cu; native_call(m, 0x41f0e0u);	/* 418a67: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 418a6c: lea eax, [esp + 0x60] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418a70: push eax */
	m->eax = (DWORD)(m->ebx + 0x5cu);	/* 418a71: lea eax, [ebx + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418a74: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418a75: push ebp */
	m->esp -= 4; M32(m->esp) = 0x418a7bu; native_call(m, 0x4125f0u);	/* 418a76: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a7b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a80: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a85: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a8a: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a8f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418a99u; native_call(m, 0x41f0e0u);	/* 418a94: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418a99: add esp, 0x4c */
	m->eax = (DWORD)(m->ebx + 0x70u);	/* 418a9c: lea eax, [ebx + 0x70] */
	{ DWORD v_ = 0x763024u; m->esp -= 4; M32(m->esp) = v_; }	/* 418a9f: push 0x763024 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418aa4: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 418aa5: push esi */
	m->esp -= 4; M32(m->esp) = 0x418aabu; native_call(m, 0x403170u);	/* 418aa6: call 0x403170 */
	m->ecx = 0xcu;	/* 418aab: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418ab0: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 418ab2: lea edi, [esp + 0x40] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 418ab6: lea edx, [esp + 0x2c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 418aba: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dcac0u));	/* 418abc: mov ecx, dword ptr [0x4dcac0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418ac2: push ecx */
	{ DWORD v_ = 0x4b0270u; m->esp -= 4; M32(m->esp) = v_; }	/* 418ac3: push 0x4b0270 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 418ac8: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418ac9: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x418ad0u; native_call(m, 0x49e9ddu);	/* 418acb: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 418ad0: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418ad4: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418ad7: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 418ad9: lea edx, [esp + 0x4c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418add: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418adf: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418ae1: sub edi, ecx */
	m->esi = m->edi;	/* 418ae3: mov esi, edi */
	m->edi = m->edx;	/* 418ae5: mov edi, edx */
	m->edx = m->ecx;	/* 418ae7: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418ae9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418aec: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418aee: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418af0: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418af1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418af4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x4dcac4u));	/* 418af6: mov eax, dword ptr [0x4dcac4] */
	m->ecx = m->edx;	/* 418afb: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418afd: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418b00: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418b01: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 418b03: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = 0x4b0270u; m->esp -= 4; M32(m->esp) = v_; }	/* 418b07: push 0x4b0270 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418b0c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x418b12u; native_call(m, 0x49e9ddu);	/* 418b0d: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x44u);	/* 418b12: lea edi, [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418b16: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418b19: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 418b1b: lea edx, [esp + 0x58] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418b1f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418b21: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418b23: sub edi, ecx */
	m->esi = m->edi;	/* 418b25: mov esi, edi */
	m->edi = m->edx;	/* 418b27: mov edi, edx */
	m->edx = m->ecx;	/* 418b29: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418b2b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418b2e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418b30: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418b32: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418b33: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418b36: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418b38: mov ecx, edx */
	m->eax = M32((DWORD)(0x4dcac8u));	/* 418b3a: mov eax, dword ptr [0x4dcac8] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418b3f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418b42: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418b44: push eax */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 418b45: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x4b0270u; m->esp -= 4; M32(m->esp) = v_; }	/* 418b49: push 0x4b0270 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418b4e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x418b54u; native_call(m, 0x49e9ddu);	/* 418b4f: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x50u);	/* 418b54: lea edi, [esp + 0x50] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418b58: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418b5b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x64u);	/* 418b5d: lea edx, [esp + 0x64] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418b61: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418b63: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418b65: sub edi, ecx */
	m->esi = m->edi;	/* 418b67: mov esi, edi */
	m->edi = m->edx;	/* 418b69: mov edi, edx */
	m->edx = m->ecx;	/* 418b6b: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418b6d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418b70: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418b72: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418b74: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418b75: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418b78: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x4dcaccu));	/* 418b7a: mov eax, dword ptr [0x4dcacc] */
	m->ecx = m->edx;	/* 418b7f: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418b81: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418b84: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418b85: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 418b87: lea ecx, [esp + 0x54] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 418b8b: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418b90: push ecx */
	m->esp -= 4; M32(m->esp) = 0x418b96u; native_call(m, 0x49e9ddu);	/* 418b91: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x5cu);	/* 418b96: lea edi, [esp + 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418b9a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418b9d: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x70u);	/* 418b9f: lea edx, [esp + 0x70] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418ba3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418ba5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418ba7: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418ba9: push 0x3f800000 */
	m->esi = m->edi;	/* 418bae: mov esi, edi */
	m->edi = m->edx;	/* 418bb0: mov edi, edx */
	m->edx = m->ecx;	/* 418bb2: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418bb4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418bb7: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418bb9: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418bbb: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418bbc: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418bbf: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418bc1: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418bc3: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418bc8: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418bcb: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418bd0: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418bd1: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418bd6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x418bddu; native_call(m, 0x41f0e0u);	/* 418bd8: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418bdd: add esp, 0x50 */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 418be0: lea eax, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418be4: push eax */
	m->eax = (DWORD)(m->ebx + 0x70u);	/* 418be5: lea eax, [ebx + 0x70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418be8: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418be9: push ebp */
	m->esp -= 4; M32(m->esp) = 0x418befu; native_call(m, 0x4125f0u);	/* 418bea: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418bef: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418bf4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418bf9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418bfe: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c03: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418c0du; native_call(m, 0x41f0e0u);	/* 418c08: call 0x41f0e0 */
	m->esi = M32((DWORD)(m->esp + 0x30u));	/* 418c0d: mov esi, dword ptr [esp + 0x30] */
	m->eax = (DWORD)(m->ebx + 0x84u);	/* 418c11: lea eax, [ebx + 0x84] */
	{ DWORD v_ = 0x7630a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c17: push 0x7630a4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418c1c: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 418c1d: push esi */
	m->esp -= 4; M32(m->esp) = 0x418c23u; native_call(m, 0x403170u);	/* 418c1e: call 0x403170 */
	m->ecx = 0xcu;	/* 418c23: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418c28: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x60u);	/* 418c2a: lea edi, [esp + 0x60] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 418c2e: rep stosd dword ptr es:[edi], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcad0u)));	/* 418c30: fld dword ptr [0x4dcad0] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418c36: add esp, 0x24 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 418c39: lea ecx, [esp + 0x3c] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418c3d: stosw word ptr es:[edi], ax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 418c3f: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b0268u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c42: push 0x4b0268 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418c47: push ecx */
	m->esp -= 4; M32(m->esp) = 0x418c4du; native_call(m, 0x49e9ddu);	/* 418c48: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c4d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c52: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c57: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c5c: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c5e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418c68u; native_call(m, 0x41f0e0u);	/* 418c63: call 0x41f0e0 */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 418c68: lea edx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x84u);	/* 418c6c: lea eax, [ebx + 0x84] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 418c72: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418c73: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418c74: push ebp */
	m->esp -= 4; M32(m->esp) = 0x418c7au; native_call(m, 0x4125f0u);	/* 418c75: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c7a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c7f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c84: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c89: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418c8e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418c98u; native_call(m, 0x41f0e0u);	/* 418c93: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418c98: add esp, 0x44 */
	m->eax = (DWORD)(m->ebx + 0x98u);	/* 418c9b: lea eax, [ebx + 0x98] */
	{ DWORD v_ = 0x763124u; m->esp -= 4; M32(m->esp) = v_; }	/* 418ca1: push 0x763124 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418ca6: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 418ca7: push esi */
	m->esp -= 4; M32(m->esp) = 0x418cadu; native_call(m, 0x403170u);	/* 418ca8: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcaf8u)));	/* 418cad: fld dword ptr [0x4dcaf8] */
	m->ecx = 0xcu;	/* 418cb3: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418cb8: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 418cba: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418cbe: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 418cc1: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 418cc3: fstp qword ptr [esp] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418cc6: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 418cc8: lea eax, [esp + 0x3c] */
	{ DWORD v_ = 0x4b01e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 418ccc: push 0x4b01e0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418cd1: push eax */
	m->esp -= 4; M32(m->esp) = 0x418cd7u; native_call(m, 0x49e9ddu);	/* 418cd2: call 0x49e9dd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418cd7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418cdc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418ce1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 418ce6: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418ce8: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418cf2u; native_call(m, 0x41f0e0u);	/* 418ced: call 0x41f0e0 */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 418cf2: lea ecx, [esp + 0x58] */
	m->eax = (DWORD)(m->ebx + 0x98u);	/* 418cf6: lea eax, [ebx + 0x98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418cfc: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418cfd: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418cfe: push ebp */
	m->esp -= 4; M32(m->esp) = 0x418d04u; native_call(m, 0x4125f0u);	/* 418cff: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418d04: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418d09: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418d0e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418d13: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418d18: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418d22u; native_call(m, 0x41f0e0u);	/* 418d1d: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418d22: add esp, 0x44 */
	m->eax = (DWORD)(m->ebx + 0xacu);	/* 418d25: lea eax, [ebx + 0xac] */
	{ DWORD v_ = 0x7631a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 418d2b: push 0x7631a4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418d30: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 418d31: push esi */
	m->esp -= 4; M32(m->esp) = 0x418d37u; native_call(m, 0x403170u);	/* 418d32: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcafcu)));	/* 418d37: fld dword ptr [0x4dcafc] */
	m->ecx = 0xcu;	/* 418d3d: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418d42: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x4u)) = (double)ST(0); FPOP();	/* 418d44: fstp qword ptr [esp + 4] */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 418d48: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418d4c: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 418d4f: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 418d51: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0x4b0254u; m->esp -= 4; M32(m->esp) = v_; }	/* 418d55: push 0x4b0254 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 418d5a: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418d5b: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x418d62u; native_call(m, 0x49e9ddu);	/* 418d5d: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 418d62: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418d66: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418d69: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418d6b: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcb04u)));	/* 418d6d: fld dword ptr [0x4dcb04] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 418d73: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 418d77: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418d79: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 418d7b: lea edx, [esp + 0x44] */
	m->esi = m->edi;	/* 418d7f: mov esi, edi */
	m->edi = m->edx;	/* 418d81: mov edi, edx */
	m->edx = m->ecx;	/* 418d83: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418d85: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418d88: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418d8a: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418d8c: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418d8d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418d90: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418d92: add esp, 8 */
	m->ecx = m->edx;	/* 418d95: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418d97: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 418d9a: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x4b0254u; m->esp -= 4; M32(m->esp) = v_; }	/* 418d9e: push 0x4b0254 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418da3: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418da4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x418dabu; native_call(m, 0x49e9ddu);	/* 418da6: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 418dab: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418daf: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418db2: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 418db4: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418db8: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcb00u)));	/* 418dba: fld dword ptr [0x4dcb00] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 418dc0: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 418dc4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418dc6: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418dc8: add esp, 8 */
	m->esi = m->edi;	/* 418dcb: mov esi, edi */
	m->edi = m->edx;	/* 418dcd: mov edi, edx */
	m->edx = m->ecx;	/* 418dcf: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418dd1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418dd4: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418dd6: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418dd8: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418dd9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418ddc: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418dde: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 418de0: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418de4: and ecx, 3 */
	{ DWORD v_ = 0x4b01e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 418de7: push 0x4b01e0 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418dec: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418dee: push eax */
	m->esp -= 4; M32(m->esp) = 0x418df4u; native_call(m, 0x49e9ddu);	/* 418def: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 418df4: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418df8: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418dfb: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 418dfd: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418e01: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418e03: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418e05: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e07: push 0x3f800000 */
	m->esi = m->edi;	/* 418e0c: mov esi, edi */
	m->edi = m->edx;	/* 418e0e: mov edi, edx */
	m->edx = m->ecx;	/* 418e10: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418e12: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418e15: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418e17: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418e19: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418e1a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418e1d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418e1f: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e21: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418e26: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e29: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418e2e: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e2f: push 0x76d438 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418e34: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x418e3bu; native_call(m, 0x41f0e0u);	/* 418e36: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 418e3b: lea eax, [esp + 0x58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418e3f: push eax */
	m->eax = (DWORD)(m->ebx + 0xacu);	/* 418e40: lea eax, [ebx + 0xac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418e46: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418e47: push ebp */
	m->esp -= 4; M32(m->esp) = 0x418e4du; native_call(m, 0x4125f0u);	/* 418e48: call 0x4125f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e4d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e52: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e57: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e5c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e61: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418e6bu; native_call(m, 0x41f0e0u);	/* 418e66: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 418e6b: mov ecx, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418e6f: add esp, 0x44 */
	{ DWORD a_ = m->ebx, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 418e72: add ebx, 0xc0 */
	{ DWORD v_ = 0x763224u; m->esp -= 4; M32(m->esp) = v_; }	/* 418e78: push 0x763224 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 418e7d: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 418e7e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x418e84u; native_call(m, 0x403170u);	/* 418e7f: call 0x403170 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcaecu)));	/* 418e84: fld dword ptr [0x4dcaec] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 418e8a: fmul dword ptr [0x4a9480] */
	m->ecx = 0xcu;	/* 418e90: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418e95: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 418e97: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418e9b: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 418e9e: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 418ea0: fstp qword ptr [esp] */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 418ea3: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0x4b0254u; m->esp -= 4; M32(m->esp) = v_; }	/* 418ea7: push 0x4b0254 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 418eac: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 418ead: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x418eb4u; native_call(m, 0x49e9ddu);	/* 418eaf: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 418eb4: lea edi, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418eb8: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418ebb: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 418ebd: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418ec1: repne scasb al, byte ptr es:[edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dcaf0u)));	/* 418ec3: fld dword ptr [0x4dcaf0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 418ec9: fmul dword ptr [0x4a9480] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 418ecf: fstp qword ptr [esp + 8] */
	m->ecx = ~m->ecx;	/* 418ed3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418ed5: sub edi, ecx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418ed7: add esp, 8 */
	m->esi = m->edi;	/* 418eda: mov esi, edi */
	m->edi = m->edx;	/* 418edc: mov edi, edx */
	m->edx = m->ecx;	/* 418ede: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418ee0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418ee3: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418ee5: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418ee7: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418ee8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418eeb: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418eed: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 418eef: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418ef3: and ecx, 3 */
	{ DWORD v_ = 0x4b02fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 418ef6: push 0x4b02fc */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418efb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418efd: push eax */
	m->esp -= 4; M32(m->esp) = 0x418f03u; native_call(m, 0x49e9ddu);	/* 418efe: call 0x49e9dd */
	m->edi = 0x765aa4u;	/* 418f03: mov edi, 0x765aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f08: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 418f0b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 418f0d: lea edx, [esp + 0x30] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418f11: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418f13: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418f15: sub edi, ecx */
	m->esi = m->edi;	/* 418f17: mov esi, edi */
	m->edi = m->edx;	/* 418f19: mov edi, edx */
	m->edx = m->ecx;	/* 418f1b: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f1d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418f20: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418f22: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418f24: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418f25: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418f28: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418f2a: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 418f2c: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f30: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418f33: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0340u;	/* 418f35: mov edi, 0x4b0340 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f3a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418f3d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418f3f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418f41: sub edi, ecx */
	m->esi = m->edi;	/* 418f43: mov esi, edi */
	m->edi = m->edx;	/* 418f45: mov edi, edx */
	m->edx = m->ecx;	/* 418f47: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f49: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418f4c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418f4e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418f50: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418f51: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418f54: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418f56: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 418f58: lea edx, [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f5c: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418f5f: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418f64: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 418f66: lea edi, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f6a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418f6d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 418f6f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 418f71: sub edi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418f73: push 0x3f800000 */
	m->esi = m->edi;	/* 418f78: mov esi, edi */
	m->edi = m->edx;	/* 418f7a: mov edi, edx */
	m->edx = m->ecx;	/* 418f7c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f7e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 418f81: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 418f83: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 418f85: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 418f86: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 418f89: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 418f8b: mov ecx, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 418f8d: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 418f92: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418f95: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 418f96: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 418f98: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x418fa2u; native_call(m, 0x41f0e0u);	/* 418f9d: call 0x41f0e0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 418fa2: lea eax, [esp + 0x58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 418fa6: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 418fa7: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 418fa8: push ebp */
	m->esp -= 4; M32(m->esp) = 0x418faeu; native_call(m, 0x4125f0u);	/* 418fa9: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 418fae: add esp, 0x30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 418fb1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 418fb2: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 418fb3: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 418fb4: pop ebx */
	m->esp = m->ebp;	/* 418fb5: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 418fb7: pop ebp */
	m->esp += 4 + 0; return;	/* 418fb8: ret  */
L_418fb9:
	ST(0) = ST(0); FPOP();	/* 418fb9: fstp st(0) */
L_418fbb:
	m->edi = M32(m->esp); m->esp += 4;	/* 418fbb: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 418fbc: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 418fbd: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 418fbe: pop ebx */
	m->esp = m->ebp;	/* 418fbf: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 418fc1: pop ebp */
	m->esp += 4 + 0; return;	/* 418fc2: ret  */
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
