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

static void lift_46fd20(X86 *m);
static void lift_46f7a0(X86 *m);

/* data_46f7a0 (0x46f7a0), lifted by tools/lift.py */
static void lift_46f7a0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f7a0: sub esp, 0x4c */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7a3: push edi */
	m->edi = m->ecx;	/* 46f7a4: mov edi, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46f7a6: xor eax, eax */
	M32((DWORD)(m->esp + 0x8u)) = m->edi;	/* 46f7a8: mov dword ptr [esp + 8], edi */
	m->ecx = M32((DWORD)(m->edi + 0x10u));	/* 46f7ac: mov ecx, dword ptr [edi + 0x10] */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 46f7af: mov dword ptr [esp + 0xc], eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f7b3: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_46f8b9;	/* 46f7b5: jle 0x46f8b9 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7bb: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x58u));	/* 46f7bc: mov ebx, dword ptr [esp + 0x58] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7c0: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x60u));	/* 46f7c1: mov ebp, dword ptr [esp + 0x60] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7c5: push esi */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 46f7c6: mov dword ptr [esp + 0x10], eax */
L_46f7ca:
	m->esi = M32((DWORD)(m->edi + 0x14u));	/* 46f7ca: mov esi, dword ptr [edi + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46f7cd: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46f7d1: add esi, edx */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 46f7d3: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f7d5: test eax, eax */
	if (m->zf) goto L_46f897;	/* 46f7d7: je 0x46f897 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f7dd: test ebp, ebp */
	if (!m->zf) goto L_46f82e;	/* 46f7df: jne 0x46f82e */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f7e1: test ebx, ebx */
	if (m->zf) goto L_46f80f;	/* 46f7e3: je 0x46f80f */
	m->eax = (DWORD)(m->esi + 0xcu);	/* 46f7e5: lea eax, [esi + 0xc] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 46f7e8: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7ec: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7ed: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46f7f3u; native_call(m, 0x47d740u);	/* 46f7ee: call 0x47d740 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 46f7f3: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 46f7f5: mov ecx, dword ptr [esi + 8] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 46f7f8: lea edx, [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7fc: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7fd: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7fe: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f7ff: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f801: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46f807u; native_call(m, 0x466910u);	/* 46f802: call 0x466910 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f807: add esp, 0x1c */
	goto L_46f897;	/* 46f80a: jmp 0x46f897 */
L_46f80f:
	m->ecx = M32((DWORD)(m->eax + 0x18u));	/* 46f80f: mov ecx, dword ptr [eax + 0x18] */
	m->edi = M32((DWORD)(m->esi + 0x8u));	/* 46f812: mov edi, dword ptr [esi + 8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46f815: shl ecx, 2 */
	m->edx = m->ecx;	/* 46f818: mov edx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46f81a: xor eax, eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46f81c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 46f81f: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 46f821: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46f823: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 46f826: rep stosb byte ptr es:[edi], al */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 46f828: mov edi, dword ptr [esp + 0x14] */
	goto L_46f897;	/* 46f82c: jmp 0x46f897 */
L_46f82e:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f82e: test ebx, ebx */
	if (m->zf) goto L_46f877;	/* 46f830: je 0x46f877 */
	m->edi = (DWORD)(m->esi + 0xcu);	/* 46f832: lea edi, [esi + 0xc] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 46f835: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f839: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f83a: push eax */
	m->esp -= 4; M32(m->esp) = 0x46f840u; native_call(m, 0x47d740u);	/* 46f83b: call 0x47d740 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 46f840: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 46f842: mov eax, dword ptr [esi + 8] */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 46f845: lea ecx, [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f849: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f84a: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f84b: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f84c: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f84e: push eax */
	m->esp -= 4; M32(m->esp) = 0x46f854u; native_call(m, 0x466910u);	/* 46f84f: call 0x466910 */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 46f854: lea ecx, [esp + 0x38] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f858: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f859: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46f85fu; native_call(m, 0x47d740u);	/* 46f85a: call 0x47d740 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 46f85f: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 46f861: mov eax, dword ptr [esi + 8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46f864: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f865: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f866: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f868: push eax */
	m->esp -= 4; M32(m->esp) = 0x46f86eu; native_call(m, 0x466960u);	/* 46f869: call 0x466960 */
	m->edi = M32((DWORD)(m->esp + 0x48u));	/* 46f86e: mov edi, dword ptr [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f872: add esp, 0x34 */
	goto L_46f897;	/* 46f875: jmp 0x46f897 */
L_46f877:
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 46f877: lea ecx, [esi + 0xc] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 46f87a: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f87e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f87f: push edx */
	m->esp -= 4; M32(m->esp) = 0x46f885u; native_call(m, 0x47d740u);	/* 46f880: call 0x47d740 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 46f885: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 46f887: mov ecx, dword ptr [esi + 8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46f88a: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f88b: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f88c: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f88e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46f894u; native_call(m, 0x466960u);	/* 46f88f: call 0x466960 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f894: add esp, 0x18 */
L_46f897:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 46f897: mov eax, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46f89b: mov edx, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->edi + 0x10u));	/* 46f89f: mov ecx, dword ptr [edi + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46f8a2: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46f8a3: add edx, 0x64 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f8a6: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 46f8a8: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 46f8ac: mov dword ptr [esp + 0x10], edx */
	if (m->sf != m->of) goto L_46f7ca;	/* 46f8b0: jl 0x46f7ca */
	m->esi = M32(m->esp); m->esp += 4;	/* 46f8b6: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46f8b7: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46f8b8: pop ebx */
L_46f8b9:
	m->edi = M32(m->esp); m->esp += 4;	/* 46f8b9: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f8ba: add esp, 0x4c */
	m->esp += 4 + 8; return;	/* 46f8bd: ret 8 */
}

/* hud_46fd20 (0x46fd20), lifted by tools/lift.py */
static void lift_46fd20(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46fd20: sub esp, 0x4c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fd23: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46fd24: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46fd25: push edi */
	m->edi = m->ecx;	/* 46fd26: mov edi, ecx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 46fd28: xor esi, esi */
	M32((DWORD)(m->esp + 0xcu)) = m->edi;	/* 46fd2a: mov dword ptr [esp + 0xc], edi */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x1cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fd2e: cmp dword ptr [edi + 0x1c], esi */
	if (m->zf || m->sf != m->of) goto L_46febf;	/* 46fd31: jle 0x46febf */
	m->eax = M32((DWORD)(m->edi + 0x10u));	/* 46fd37: mov eax, dword ptr [edi + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fd3a: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_46febf;	/* 46fd3c: jle 0x46febf */
	m->ecx = M32((DWORD)(m->edi + 0x24u));	/* 46fd42: mov ecx, dword ptr [edi + 0x24] */
	m->edx = M32((DWORD)(m->edi + 0x20u));	/* 46fd45: mov edx, dword ptr [edi + 0x20] */
	{ DWORD a_ = M32((DWORD)(m->edx + m->ecx*4 + 0x0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fd48: cmp dword ptr [edx + ecx*4], esi */
	if (m->zf) goto L_46febf;	/* 46fd4b: je 0x46febf */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fd51: cmp eax, esi */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 46fd53: mov dword ptr [esp + 0x10], esi */
	if (m->zf || m->sf != m->of) goto L_46feb1;	/* 46fd57: jle 0x46feb1 */
	m->ebx = M32((DWORD)(m->esp + 0x60u));	/* 46fd5d: mov ebx, dword ptr [esp + 0x60] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46fd61: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x68u));	/* 46fd62: mov ebp, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 46fd66: mov dword ptr [esp + 0x18], esi */
L_46fd6a:
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->edi + 0x14u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46fd6a: add esi, dword ptr [edi + 0x14] */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 46fd6d: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fd6f: test eax, eax */
	if (m->zf) goto L_46fe91;	/* 46fd71: je 0x46fe91 */
	m->edx = M32((DWORD)(m->edi + 0x2cu));	/* 46fd77: mov edx, dword ptr [edi + 0x2c] */
	m->ecx = 0x1u;	/* 46fd7a: mov ecx, 1 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fd7f: cmp edx, ecx */
	if (!m->zf) goto L_46fe6d;	/* 46fd81: jne 0x46fe6d */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fd87: test ebp, ebp */
	if (!m->zf) goto L_46fde4;	/* 46fd89: jne 0x46fde4 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fd8b: test ebx, ebx */
	if (m->zf) goto L_46fdc5;	/* 46fd8d: je 0x46fdc5 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0xb00cu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fd8f: cmp dword ptr [ebx + 0xb00c], ecx */
	if (!m->zf) goto L_46fe4d;	/* 46fd95: jne 0x46fe4d */
	m->eax = (DWORD)(m->esi + 0xcu);	/* 46fd9b: lea eax, [esi + 0xc] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 46fd9e: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fda2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fda3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46fda9u; native_call(m, 0x47d740u);	/* 46fda4: call 0x47d740 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 46fda9: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 46fdab: mov ecx, dword ptr [esi + 8] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 46fdae: lea edx, [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fdb2: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fdb3: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fdb4: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fdb5: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fdb7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46fdbdu; native_call(m, 0x466910u);	/* 46fdb8: call 0x466910 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46fdbd: add esp, 0x1c */
	goto L_46fe4d;	/* 46fdc0: jmp 0x46fe4d */
L_46fdc5:
	m->ecx = M32((DWORD)(m->eax + 0x18u));	/* 46fdc5: mov ecx, dword ptr [eax + 0x18] */
	m->edi = M32((DWORD)(m->esi + 0x8u));	/* 46fdc8: mov edi, dword ptr [esi + 8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46fdcb: shl ecx, 2 */
	m->edx = m->ecx;	/* 46fdce: mov edx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46fdd0: xor eax, eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46fdd2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 46fdd5: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 46fdd7: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46fdd9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 46fddc: rep stosb byte ptr es:[edi], al */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 46fdde: mov edi, dword ptr [esp + 0x10] */
	goto L_46fe4d;	/* 46fde2: jmp 0x46fe4d */
L_46fde4:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fde4: test ebx, ebx */
	if (m->zf) goto L_46fe2d;	/* 46fde6: je 0x46fe2d */
	m->edi = (DWORD)(m->esi + 0xcu);	/* 46fde8: lea edi, [esi + 0xc] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 46fdeb: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46fdef: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fdf0: push eax */
	m->esp -= 4; M32(m->esp) = 0x46fdf6u; native_call(m, 0x47d740u);	/* 46fdf1: call 0x47d740 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 46fdf6: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 46fdf8: mov eax, dword ptr [esi + 8] */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 46fdfb: lea ecx, [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fdff: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe00: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe01: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe02: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe04: push eax */
	m->esp -= 4; M32(m->esp) = 0x46fe0au; native_call(m, 0x466910u);	/* 46fe05: call 0x466910 */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 46fe0a: lea ecx, [esp + 0x38] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe0e: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe0f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46fe15u; native_call(m, 0x47d740u);	/* 46fe10: call 0x47d740 */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 46fe15: mov edx, dword ptr [esi] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 46fe17: mov eax, dword ptr [esi + 8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe1a: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe1b: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe1c: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe1e: push eax */
	m->esp -= 4; M32(m->esp) = 0x46fe24u; native_call(m, 0x466960u);	/* 46fe1f: call 0x466960 */
	m->edi = M32((DWORD)(m->esp + 0x44u));	/* 46fe24: mov edi, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46fe28: add esp, 0x34 */
	goto L_46fe4d;	/* 46fe2b: jmp 0x46fe4d */
L_46fe2d:
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 46fe2d: lea ecx, [esi + 0xc] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 46fe30: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe34: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe35: push edx */
	m->esp -= 4; M32(m->esp) = 0x46fe3bu; native_call(m, 0x47d740u);	/* 46fe36: call 0x47d740 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 46fe3b: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 46fe3d: mov ecx, dword ptr [esi + 8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe40: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe41: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe42: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe44: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46fe4au; native_call(m, 0x466960u);	/* 46fe45: call 0x466960 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46fe4a: add esp, 0x18 */
L_46fe4d:
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 46fe4d: mov edx, dword ptr [esp + 0x74] */
	m->eax = M32((DWORD)(m->esp + 0x70u));	/* 46fe51: mov eax, dword ptr [esp + 0x70] */
	m->ecx = M32((DWORD)(m->esp + 0x6cu));	/* 46fe55: mov ecx, dword ptr [esp + 0x6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe59: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe5a: push eax */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 46fe5b: mov eax, dword ptr [esi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe5e: push ecx */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 46fe5f: mov ecx, dword ptr [esi] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe61: push 0 */
	m->edx = (DWORD)(m->esi + 0xcu);	/* 46fe63: lea edx, [esi + 0xc] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe66: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe68: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe69: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe6a: push ecx */
	goto L_46fe85;	/* 46fe6b: jmp 0x46fe85 */
L_46fe6d:
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 46fe6d: mov edx, dword ptr [esp + 0x74] */
	m->ecx = M32((DWORD)(m->esp + 0x70u));	/* 46fe71: mov ecx, dword ptr [esp + 0x70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe75: push edx */
	m->edx = M32((DWORD)(m->esp + 0x70u));	/* 46fe76: mov edx, dword ptr [esp + 0x70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe7a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe7b: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe7c: push ebp */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46fe7d: add esi, 0xc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe80: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe81: push esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe82: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fe84: push eax */
L_46fe85:
	m->ecx = M32((DWORD)(m->esp + 0x80u));	/* 46fe85: mov ecx, dword ptr [esp + 0x80] */
	m->esp -= 4; M32(m->esp) = 0x46fe91u; native_call(m, 0x4853c0u);	/* 46fe8c: call 0x4853c0 */
L_46fe91:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 46fe91: mov eax, dword ptr [esp + 0x14] */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 46fe95: mov esi, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->edi + 0x10u));	/* 46fe99: mov ecx, dword ptr [edi + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46fe9c: inc eax */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46fe9d: add esi, 0x64 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fea0: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 46fea2: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 46fea6: mov dword ptr [esp + 0x18], esi */
	if (m->sf != m->of) goto L_46fd6a;	/* 46feaa: jl 0x46fd6a */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46feb0: pop ebp */
L_46feb1:
	m->edi = M32(m->esp); m->esp += 4;	/* 46feb1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46feb2: pop esi */
	m->eax = 0x1u;	/* 46feb3: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46feb8: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46feb9: add esp, 0x4c */
	m->esp += 4 + 24; return;	/* 46febc: ret 0x18 */
L_46febf:
	m->edi = M32(m->esp); m->esp += 4;	/* 46febf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46fec0: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46fec1: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46fec3: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46fec4: add esp, 0x4c */
	m->esp += 4 + 24; return;	/* 46fec7: ret 0x18 */
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
