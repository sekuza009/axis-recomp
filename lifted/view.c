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

static void lift_4853c0(X86 *m);
static void lift_46f8c0(X86 *m);

/* actor_46f8c0 (0x46f8c0), lifted by tools/lift.py */
static void lift_46f8c0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xa4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f8c0: sub esp, 0xa4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f8c6: push ebx */
	m->ebx = m->ecx;	/* 46f8c7: mov ebx, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46f8c9: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 46f8ca: xor ebp, ebp */
	m->eax = M32((DWORD)(m->ebx + 0x1cu));	/* 46f8cc: mov eax, dword ptr [ebx + 0x1c] */
	M32((DWORD)(m->esp + 0x24u)) = m->ebx;	/* 46f8cf: mov dword ptr [esp + 0x24], ebx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f8d3: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_46fd06;	/* 46f8d5: jle 0x46fd06 */
	m->eax = (DWORD)(m->esp + 0x6cu);	/* 46f8db: lea eax, [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f8df: push eax */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f8e0: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x46f8ebu; native_call(m, M32(0x4a9270u));	/* 46f8e5: call dword ptr [0x4a9270] */
	m->eax = M32((DWORD)(m->esp + 0xb0u));	/* 46f8eb: mov eax, dword ptr [esp + 0xb0] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f8f2: cmp eax, ebp */
	if (m->zf) goto L_46f8fe;	/* 46f8f4: je 0x46f8fe */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 46f8f6: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f8fa: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f8fb: push ecx */
	goto L_46f908;	/* 46f8fc: jmp 0x46f908 */
L_46f8fe:
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 46f8fe: lea edx, [esp + 0x6c] */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 46f902: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f906: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f907: push eax */
L_46f908:
	m->esp -= 4; M32(m->esp) = 0x46f90du; native_call(m, 0x47d5a0u);	/* 46f908: call 0x47d5a0 */
	m->ecx = M32((DWORD)(m->ebx + 0x24u));	/* 46f90d: mov ecx, dword ptr [ebx + 0x24] */
	m->edx = M32((DWORD)(m->ebx + 0x20u));	/* 46f910: mov edx, dword ptr [ebx + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f913: add esp, 8 */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 46f916: lea eax, [edx + ecx*4] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 46f919: mov dword ptr [esp + 0x28], eax */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f91d: cmp dword ptr [eax], ebp */
	if (m->zf) goto L_46fd06;	/* 46f91f: je 0x46fd06 */
	m->ecx = M32((DWORD)(m->ebx + 0x10u));	/* 46f925: mov ecx, dword ptr [ebx + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f928: push esi */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f929: cmp ecx, ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f92b: push edi */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebp;	/* 46f92c: mov dword ptr [esp + 0x1c], ebp */
	if (m->zf || m->sf != m->of) goto L_46fcf9;	/* 46f930: jle 0x46fcf9 */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 46f936: mov dword ptr [esp + 0x24], ebp */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 46f93a: mov dword ptr [esp + 0x18], ebp */
	goto L_46f948;	/* 46f93e: jmp 0x46f948 */
L_46f940:
	m->ebx = M32((DWORD)(m->esp + 0x2cu));	/* 46f940: mov ebx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 46f944: mov eax, dword ptr [esp + 0x30] */
L_46f948:
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 46f948: mov ecx, dword ptr [eax] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 46f94a: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->ebx + 0x28u));	/* 46f94e: mov eax, dword ptr [ebx + 0x28] */
	m->edi = M32((DWORD)(m->ebx + 0x14u));	/* 46f951: mov edi, dword ptr [ebx + 0x14] */
	m->esi = M32((DWORD)(m->ecx + 0x14u));	/* 46f954: mov esi, dword ptr [ecx + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 46f957: mov dword ptr [esp + 0x20], edi */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46f95b: add esi, edx */
	m->edx = M32((DWORD)(m->ecx + 0x20u));	/* 46f95d: mov edx, dword ptr [ecx + 0x20] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 46f960: inc edx */
	m->ebx = m->edx;	/* 46f961: mov ebx, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46f963: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ebx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46f964: idiv ebx */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 46f966: mov eax, dword ptr [esp + 0x1c] */
	m->ebx = m->edx;	/* 46f96a: mov ebx, edx */
	m->edx = M32((DWORD)(m->ecx + 0x10u));	/* 46f96c: mov edx, dword ptr [ecx + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f96f: cmp eax, edx */
	if (m->sf == m->of) goto L_46fcf9;	/* 46f971: jge 0x46fcf9 */
	m->eax = M32((DWORD)(m->esi + 0x40u));	/* 46f977: mov eax, dword ptr [esi + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f97a: test eax, eax */
	if (m->sf == m->of) goto L_46f985;	/* 46f97c: jge 0x46f985 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 46f97e: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f982: push ecx */
	goto L_46f990;	/* 46f983: jmp 0x46f990 */
L_46f985:
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46f985: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46f988: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->edi + m->edx*4 + 0xcu);	/* 46f98b: lea eax, [edi + edx*4 + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f98f: push eax */
L_46f990:
	m->esp -= 4; M32(m->esp) = 0x46f996u; native_call(m, M32(0x4a926cu));	/* 46f990: call dword ptr [0x4a926c] */
	m->edx = M32((DWORD)(m->esi + 0x60u));	/* 46f996: mov edx, dword ptr [esi + 0x60] */
	M32((DWORD)(m->esp + 0x14u)) = m->ebx;	/* 46f999: mov dword ptr [esp + 0x14], ebx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f99d: test edx, edx */
	if (m->zf || m->sf != m->of) goto L_46fa46;	/* 46f99f: jle 0x46fa46 */
	m->ebp = M32((DWORD)(m->esi + 0x64u));	/* 46f9a5: mov ebp, dword ptr [esi + 0x64] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46f9a8: xor ecx, ecx */
	m->eax = M32((DWORD)(m->ebp + 0x0u));	/* 46f9aa: mov eax, dword ptr [ebp] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f9ad: cmp ebx, eax */
	if (m->sf == m->of) goto L_46f9b5;	/* 46f9af: jge 0x46f9b5 */
	m->edx = m->eax;	/* 46f9b1: mov edx, eax */
	goto L_46f9e2;	/* 46f9b3: jmp 0x46f9e2 */
L_46f9b5:
	m->edi = (DWORD)(m->edx + 0xffffffffu);	/* 46f9b5: lea edi, [edx - 1] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f9b8: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46f9da;	/* 46f9ba: jle 0x46f9da */
L_46f9bc:
	m->eax = (DWORD)(m->edi + m->ecx*1 + 0x1u);	/* 46f9bc: lea eax, [edi + ecx + 1] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46f9c0: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46f9c1: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46f9c3: sar eax, 1 */
	m->edx = m->eax;	/* 46f9c5: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46f9c7: shl edx, 5 */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->edx + m->ebp*1 + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f9ca: cmp ebx, dword ptr [edx + ebp] */
	if (m->sf == m->of) goto L_46f9d4;	/* 46f9cd: jge 0x46f9d4 */
	m->edi = (DWORD)(m->eax + 0xffffffffu);	/* 46f9cf: lea edi, [eax - 1] */
	goto L_46f9d6;	/* 46f9d2: jmp 0x46f9d6 */
L_46f9d4:
	m->ecx = m->eax;	/* 46f9d4: mov ecx, eax */
L_46f9d6:
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f9d6: cmp ecx, edi */
	if (m->sf != m->of) goto L_46f9bc;	/* 46f9d8: jl 0x46f9bc */
L_46f9da:
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 46f9da: mov edi, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46f9de: mov edx, dword ptr [esp + 0x14] */
L_46f9e2:
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46f9e2: shl ecx, 5 */
	m->eax = (DWORD)(m->ecx + m->ebp*1 + 0x0u);	/* 46f9e5: lea eax, [ecx + ebp] */
	m->ecx = M32((DWORD)(m->ecx + m->ebp*1 + 0x4u));	/* 46f9e8: mov ecx, dword ptr [ecx + ebp + 4] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f9ec: test ecx, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 46f9ee: mov dword ptr [esp + 0x10], ecx */
	if (m->zf || m->sf != m->of) goto L_46fa04;	/* 46f9f2: jle 0x46fa04 */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->eax + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46f9f4: sub edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 46f9f6: mov dword ptr [esp + 0x14], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 46f9fa: fild dword ptr [esp + 0x14] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x10u));	/* 46f9fe: fidiv dword ptr [esp + 0x10] */
	goto L_46fa0a;	/* 46fa02: jmp 0x46fa0a */
L_46fa04:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 46fa04: fld dword ptr [0x4a93e8] */
L_46fa0a:
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 46fa0a: mov ecx, dword ptr [esp + 0x18] */
	{ long double t = ST(0); FPUSH(t); }	/* 46fa0e: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x1cu));	/* 46fa10: fmul dword ptr [eax + 0x1c] */
	m->ecx = (DWORD)(m->ecx + m->edi*1 + 0x4u);	/* 46fa13: lea ecx, [ecx + edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fa17: push ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 46fa18: fadd dword ptr [eax + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 46fa1b: fmul dword ptr [ecx] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46fa1d: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fa20: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 46fa21: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 46fa23: fmul dword ptr [eax + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0xcu));	/* 46fa26: fadd dword ptr [eax + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 46fa29: fmul dword ptr [ecx] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46fa2b: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fa2e: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 46fa2f: fmul dword ptr [eax + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 46fa32: fadd dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 46fa35: fmul dword ptr [ecx] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46fa37: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x46fa40u; native_call(m, M32(0x4a9214u));	/* 46fa3a: call dword ptr [0x4a9214] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 46fa40: mov ebp, dword ptr [esp + 0x18] */
	goto L_46fa6d;	/* 46fa44: jmp 0x46fa6d */
L_46fa46:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4cu)));	/* 46fa46: fld dword ptr [esi + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + m->ebp*1 + 0x4u));	/* 46fa49: fmul dword ptr [edi + ebp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fa4d: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46fa4e: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x48u)));	/* 46fa51: fld dword ptr [esi + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + m->ebp*1 + 0x4u));	/* 46fa54: fmul dword ptr [edi + ebp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fa58: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46fa59: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 46fa5c: fld dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + m->ebp*1 + 0x4u));	/* 46fa5f: fmul dword ptr [edi + ebp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fa63: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46fa64: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x46fa6du; native_call(m, M32(0x4a9214u));	/* 46fa67: call dword ptr [0x4a9214] */
L_46fa6d:
	m->edx = M32((DWORD)(m->esi + 0x68u));	/* 46fa6d: mov edx, dword ptr [esi + 0x68] */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 46fa70: mov dword ptr [esp + 0x10], ebx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fa74: test edx, edx */
	if (m->zf || m->sf != m->of) goto L_46fb85;	/* 46fa76: jle 0x46fb85 */
	m->esi = M32((DWORD)(m->esi + 0x6cu));	/* 46fa7c: mov esi, dword ptr [esi + 0x6c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46fa7f: xor ecx, ecx */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 46fa81: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fa83: cmp ebx, eax */
	if (m->sf == m->of) goto L_46fa8b;	/* 46fa85: jge 0x46fa8b */
	m->edx = m->eax;	/* 46fa87: mov edx, eax */
	goto L_46faba;	/* 46fa89: jmp 0x46faba */
L_46fa8b:
	m->edi = (DWORD)(m->edx + 0xffffffffu);	/* 46fa8b: lea edi, [edx - 1] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fa8e: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46faae;	/* 46fa90: jle 0x46faae */
L_46fa92:
	m->eax = (DWORD)(m->edi + m->ecx*1 + 0x1u);	/* 46fa92: lea eax, [edi + ecx + 1] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46fa96: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46fa97: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46fa99: sar eax, 1 */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46fa9b: lea edx, [eax + eax*4] */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->esi + m->edx*8 + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fa9e: cmp ebx, dword ptr [esi + edx*8] */
	if (m->sf == m->of) goto L_46faa8;	/* 46faa1: jge 0x46faa8 */
	m->edi = (DWORD)(m->eax + 0xffffffffu);	/* 46faa3: lea edi, [eax - 1] */
	goto L_46faaa;	/* 46faa6: jmp 0x46faaa */
L_46faa8:
	m->ecx = m->eax;	/* 46faa8: mov ecx, eax */
L_46faaa:
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46faaa: cmp ecx, edi */
	if (m->sf != m->of) goto L_46fa92;	/* 46faac: jl 0x46fa92 */
L_46faae:
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 46faae: mov edi, dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 46fab2: mov ebp, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46fab6: mov edx, dword ptr [esp + 0x10] */
L_46faba:
	m->eax = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 46faba: lea eax, [ecx + ecx*4] */
	m->esi = (DWORD)(m->esi + m->eax*8 + 0x0u);	/* 46fabd: lea esi, [esi + eax*8] */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 46fac0: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fac3: test eax, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 46fac5: mov dword ptr [esp + 0x14], eax */
	if (m->zf || m->sf != m->of) goto L_46fadf;	/* 46fac9: jle 0x46fadf */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esi + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46facb: sub edx, dword ptr [esi] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 46facd: mov dword ptr [esp + 0x10], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 46fad1: fild dword ptr [esp + 0x10] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x14u));	/* 46fad5: fidiv dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 46fad9: fstp dword ptr [esp + 0x28] */
	goto L_46fae7;	/* 46fadd: jmp 0x46fae7 */
L_46fadf:
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 46fadf: mov dword ptr [esp + 0x28], 0 */
L_46fae7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xcu)));	/* 46fae7: fld dword ptr [esi + 0xc] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 46faea: fst dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46faee: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46faf4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46faf6: test ah, 0x40 */
	if (m->zf) goto L_46fb1b;	/* 46faf9: je 0x46fb1b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 46fafb: fld dword ptr [esi + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46fafe: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46fb04: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46fb06: test ah, 0x40 */
	if (m->zf) goto L_46fb1b;	/* 46fb09: je 0x46fb1b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 46fb0b: fld dword ptr [esi + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46fb0e: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46fb14: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46fb16: test ah, 0x40 */
	if (!m->zf) goto L_46fb3b;	/* 46fb19: jne 0x46fb3b */
L_46fb1b:
	m->ecx = M32((DWORD)(m->esi + 0x14u));	/* 46fb1b: mov ecx, dword ptr [esi + 0x14] */
	m->edx = M32((DWORD)(m->esi + 0x10u));	/* 46fb1e: mov edx, dword ptr [esi + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 46fb21: fld dword ptr [esi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46fb24: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fb28: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa270u));	/* 46fb29: fmul dword ptr [0x4aa270] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fb2f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fb30: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fb31: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46fb32: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x46fb3bu; native_call(m, M32(0x4a91f8u));	/* 46fb35: call dword ptr [0x4a91f8] */
L_46fb3b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1cu)));	/* 46fb3b: fld dword ptr [esi + 0x1c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 46fb3e: fst dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46fb42: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46fb48: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46fb4a: test ah, 0x40 */
	if (m->zf) goto L_46fb6f;	/* 46fb4d: je 0x46fb6f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 46fb4f: fld dword ptr [esi + 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46fb52: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46fb58: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46fb5a: test ah, 0x40 */
	if (m->zf) goto L_46fb6f;	/* 46fb5d: je 0x46fb6f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 46fb5f: fld dword ptr [esi + 0x24] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46fb62: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46fb68: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46fb6a: test ah, 0x40 */
	if (!m->zf) goto L_46fbd9;	/* 46fb6d: jne 0x46fbd9 */
L_46fb6f:
	m->ecx = M32((DWORD)(m->esi + 0x24u));	/* 46fb6f: mov ecx, dword ptr [esi + 0x24] */
	m->edx = M32((DWORD)(m->esi + 0x20u));	/* 46fb72: mov edx, dword ptr [esi + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46fb75: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fb79: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 46fb7a: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 46fb7e: fmul dword ptr [esi + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fb81: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fb82: push eax */
	goto L_46fbc9;	/* 46fb83: jmp 0x46fbc9 */
L_46fb85:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x54u)));	/* 46fb85: fld dword ptr [esi + 0x54] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 46fb88: fst dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46fb8c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46fb92: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46fb94: test ah, 0x40 */
	if (m->zf) goto L_46fbb9;	/* 46fb97: je 0x46fbb9 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x58u)));	/* 46fb99: fld dword ptr [esi + 0x58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46fb9c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46fba2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46fba4: test ah, 0x40 */
	if (m->zf) goto L_46fbb9;	/* 46fba7: je 0x46fbb9 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x5cu)));	/* 46fba9: fld dword ptr [esi + 0x5c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46fbac: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46fbb2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46fbb4: test ah, 0x40 */
	if (!m->zf) goto L_46fbd9;	/* 46fbb7: jne 0x46fbd9 */
L_46fbb9:
	m->ecx = M32((DWORD)(m->esi + 0x5cu));	/* 46fbb9: mov ecx, dword ptr [esi + 0x5c] */
	m->edx = M32((DWORD)(m->esi + 0x58u));	/* 46fbbc: mov edx, dword ptr [esi + 0x58] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46fbbf: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fbc3: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x50u)));	/* 46fbc4: fld dword ptr [esi + 0x50] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fbc7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fbc8: push eax */
L_46fbc9:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa270u));	/* 46fbc9: fmul dword ptr [0x4aa270] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fbcf: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46fbd0: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x46fbd9u; native_call(m, M32(0x4a91f8u));	/* 46fbd3: call dword ptr [0x4a91f8] */
L_46fbd9:
	m->esi = (DWORD)(m->edi + m->ebp*1 + 0xcu);	/* 46fbd9: lea esi, [edi + ebp + 0xc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46fbdd: push esi */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fbde: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x46fbe9u; native_call(m, M32(0x4a9270u));	/* 46fbe3: call dword ptr [0x4a9270] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 46fbe9: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 46fbef: fmul dword ptr [esi + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 46fbf2: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 46fbf8: fmul dword ptr [esi + 0x10] */
	m->ecx = (DWORD)(m->edi + m->ebp*1 + 0x4cu);	/* 46fbfb: lea ecx, [edi + ebp + 0x4c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fbff: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 46fc01: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 46fc07: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc09: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 46fc0b: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 46fc0e: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 46fc10: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 46fc16: fmul dword ptr [esi + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 46fc19: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 46fc1f: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc22: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 46fc24: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 46fc2a: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc2d: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 46fc2f: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 46fc32: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7b0u)));	/* 46fc35: fld dword ptr [0xa0e7b0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 46fc3b: fmul dword ptr [esi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7acu)));	/* 46fc3e: fld dword ptr [0xa0e7ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 46fc44: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc47: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7a8u)));	/* 46fc49: fld dword ptr [0xa0e7a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 46fc4f: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc52: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 46fc54: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 46fc57: fstp dword ptr [ecx + 8] */
	m->eax = M32((DWORD)(m->edi + m->ebp*1 + 0x0u));	/* 46fc5a: mov eax, dword ptr [edi + ebp] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46fc5d: test eax, eax */
	if (m->zf) goto L_46fcb9;	/* 46fc5f: je 0x46fcb9 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 46fc61: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 46fc64: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 46fc67: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 46fc6a: fmul dword ptr [eax + 0x24] */
	m->ecx = (DWORD)(m->edi + m->ebp*1 + 0x58u);	/* 46fc6d: lea ecx, [edi + ebp + 0x58] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc71: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 46fc73: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 46fc75: fmul dword ptr [eax + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc78: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 46fc7a: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 46fc7d: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 46fc7f: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 46fc82: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 46fc85: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 46fc88: fmul dword ptr [eax + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc8b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 46fc8d: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 46fc90: fmul dword ptr [eax + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fc93: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 46fc95: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 46fc98: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 46fc9b: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 46fc9e: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 46fca1: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 46fca4: fmul dword ptr [eax + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fca7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 46fca9: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 46fcac: fmul dword ptr [eax + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46fcaf: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 46fcb1: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 46fcb4: fstp dword ptr [ecx + 8] */
	goto L_46fccf;	/* 46fcb7: jmp 0x46fccf */
L_46fcb9:
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 46fcb9: mov eax, dword ptr [ecx] */
	m->edx = (DWORD)(m->edi + m->ebp*1 + 0x58u);	/* 46fcbb: lea edx, [edi + ebp + 0x58] */
	M32((DWORD)(m->edi + m->ebp*1 + 0x58u)) = m->eax;	/* 46fcbf: mov dword ptr [edi + ebp + 0x58], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 46fcc3: mov eax, dword ptr [ecx + 4] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 46fcc6: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 46fcc9: mov dword ptr [edx + 4], eax */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 46fccc: mov dword ptr [edx + 8], ecx */
L_46fccf:
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 46fccf: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 46fcd3: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->edx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46fcd7: add edx, 0x70 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46fcda: inc eax */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 46fcdb: mov dword ptr [esp + 0x24], edx */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 46fcdf: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ebp, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46fce3: add ebp, 0x64 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 46fce6: mov dword ptr [esp + 0x1c], eax */
	m->ecx = M32((DWORD)(m->edx + 0x10u));	/* 46fcea: mov ecx, dword ptr [edx + 0x10] */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 46fced: mov dword ptr [esp + 0x18], ebp */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46fcf1: cmp eax, ecx */
	if (m->sf != m->of) goto L_46f940;	/* 46fcf3: jl 0x46f940 */
L_46fcf9:
	m->eax = (DWORD)(m->esp + 0x74u);	/* 46fcf9: lea eax, [esp + 0x74] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46fcfd: push eax */
	m->esp -= 4; M32(m->esp) = 0x46fd04u; native_call(m, M32(0x4a926cu));	/* 46fcfe: call dword ptr [0x4a926c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46fd04: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46fd05: pop esi */
L_46fd06:
	m->ebp = M32(m->esp); m->esp += 4;	/* 46fd06: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46fd07: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46fd08: add esp, 0xa4 */
	m->esp += 4 + 4; return;	/* 46fd0e: ret 4 */
}

/* ViewVolume_projectObject (0x4853c0), lifted by tools/lift.py */
static void lift_4853c0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4853c0: sub esp, 0xd8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4853c6: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0xe0u));	/* 4853c7: mov ebx, dword ptr [esp + 0xe0] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4853ce: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4853cf: xor ebp, ebp */
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 4853d1: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4853d4: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4853d5: push edi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4853d6: cmp eax, ebp */
	m->edi = m->ecx;	/* 4853d8: mov edi, ecx */
	if (m->zf || m->sf != m->of) goto L_485ada;	/* 4853da: jle 0x485ada */
	m->eax = M32((DWORD)(m->esp + 0xf4u));	/* 4853e0: mov eax, dword ptr [esp + 0xf4] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4853e7: cmp eax, ebp */
	if (!m->zf) goto L_485440;	/* 4853e9: jne 0x485440 */
	m->eax = M32((DWORD)(m->edi + 0x9044u));	/* 4853eb: mov eax, dword ptr [edi + 0x9044] */
	m->ecx = M32((DWORD)(m->edi + 0x903cu));	/* 4853f1: mov ecx, dword ptr [edi + 0x903c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4853f7: cmp eax, ecx */
	if (m->sf == m->of) goto L_485429;	/* 4853f9: jge 0x485429 */
	m->ecx = M32((DWORD)(m->edi + 0x9040u));	/* 4853fb: mov ecx, dword ptr [edi + 0x9040] */
	m->esi = m->eax;	/* 485401: mov esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 485403: shl esi, 6 */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 485406: add esi, ecx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 485408: inc eax */
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485409: cmp esi, ebp */
	M32((DWORD)(m->edi + 0x9044u)) = m->eax;	/* 48540b: mov dword ptr [edi + 0x9044], eax */
	if (m->zf) goto L_485ada;	/* 485411: je 0x485ada */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 485417: push esi */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 485418: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x485423u; native_call(m, M32(0x4a9270u));	/* 48541d: call dword ptr [0x4a9270] */
	M32((DWORD)(m->esp + 0x60u)) = m->esi;	/* 485423: mov dword ptr [esp + 0x60], esi */
	goto L_485444;	/* 485427: jmp 0x485444 */
L_485429:
	M32((DWORD)(m->edi + 0x9094u)) = 0x1u;	/* 485429: mov dword ptr [edi + 0x9094], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 485433: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 485434: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 485435: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 485436: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485437: add esp, 0xd8 */
	m->esp += 4 + 32; return;	/* 48543d: ret 0x20 */
L_485440:
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 485440: mov dword ptr [esp + 0x60], eax */
L_485444:
	m->eax = M32((DWORD)(m->esp + 0x60u));	/* 485444: mov eax, dword ptr [esp + 0x60] */
	m->ecx = (DWORD)(m->edi + 0x9130u);	/* 485448: lea ecx, [edi + 0x9130] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48544e: push eax */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 48544f: lea edx, [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 485453: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485454: push edx */
	m->esp -= 4; M32(m->esp) = 0x48545au; native_call(m, 0x47d380u);	/* 485455: call 0x47d380 */
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 48545a: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48545d: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485460: cmp eax, ebp */
	M32((DWORD)(m->esp + 0x64u)) = m->ebp;	/* 485462: mov dword ptr [esp + 0x64], ebp */
	if (m->zf || m->sf != m->of) goto L_485ada;	/* 485466: jle 0x485ada */
	M32((DWORD)(m->esp + 0x5cu)) = m->ebp;	/* 48546c: mov dword ptr [esp + 0x5c], ebp */
L_485470:
	m->esi = M32((DWORD)(m->ebx + 0x14u));	/* 485470: mov esi, dword ptr [ebx + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 485473: mov ecx, dword ptr [esp + 0x5c] */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 485477: add esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x60u));	/* 485479: mov eax, dword ptr [esi + 0x60] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48547c: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_485aad;	/* 48547e: jle 0x485aad */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x100u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485484: cmp dword ptr [esp + 0x100], 1 */
	if (!m->zf) goto L_4859de;	/* 48548c: jne 0x4859de */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x7cu)));	/* 485492: fld dword ptr [esi + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x78u)));	/* 485495: fld dword ptr [esi + 0x78] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 485498: fld dword ptr [esi + 0x68] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 48549b: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 48549f: fst dword ptr [esp + 0x14] */
	{ long double t = ST(1); FPUSH(t); }	/* 4854a3: fld st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4854a5: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4854a9: fld dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 4854ad: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4854af: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4854b3: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4854b7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4854b9: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(3);	/* 4854bd: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4854bf: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 4854c1: fadd dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 4854c5: fstp dword ptr [esp + 0x68] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4854c9: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4854cd: fmul dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4854d1: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(2);	/* 4854d5: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4854d7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4854d9: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(3);	/* 4854dd: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4854df: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 4854e1: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 4854e5: fstp dword ptr [esp + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4854e9: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4854ed: fmul dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 4854f1: fld dword ptr [esp + 0x34] */
	ST(0) = ST(0) * ST(2);	/* 4854f5: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4854f7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4854f9: fld dword ptr [esp + 0x44] */
	ST(0) = ST(0) * ST(3);	/* 4854fd: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4854ff: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 485501: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 485505: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 485509: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48550d: fmul dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 485511: fld dword ptr [esp + 0x38] */
	ST(0) = ST(0) * ST(2);	/* 485515: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485517: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 485519: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(3);	/* 48551d: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48551f: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 485521: fadd dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 485525: fstp dword ptr [esp + 0x74] */
	ST(0) = ST(0); FPOP();	/* 485529: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 48552b: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x7cu)));	/* 48552d: fld dword ptr [esi + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x78u)));	/* 485530: fld dword ptr [esi + 0x78] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x74u)));	/* 485533: fld dword ptr [esi + 0x74] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 485536: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 48553a: fst dword ptr [esp + 0x14] */
	{ long double t = ST(1); FPUSH(t); }	/* 48553e: fld st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 485540: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 485544: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(2);	/* 485548: fmul st(2) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 48554a: fld dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(2);	/* 48554e: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485550: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 485552: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485556: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48555a: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 48555c: fadd dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x78u)) = (float)ST(0); FPOP();	/* 485560: fstp dword ptr [esp + 0x78] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 485564: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(1);	/* 485568: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 48556a: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(3);	/* 48556e: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485570: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 485572: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485576: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48557a: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 48557c: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0); FPOP();	/* 485580: fstp dword ptr [esp + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 485584: fld dword ptr [esp + 0x34] */
	ST(0) = ST(0) * ST(1);	/* 485588: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 48558a: fld dword ptr [esp + 0x44] */
	ST(0) = ST(0) * ST(3);	/* 48558e: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485590: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 485592: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485596: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48559a: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 48559c: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0x80u)) = (float)ST(0); FPOP();	/* 4855a0: fstp dword ptr [esp + 0x80] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4855a7: fld dword ptr [esp + 0x38] */
	ST(0) = ST(0) * ST(1);	/* 4855ab: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4855ad: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(3);	/* 4855b1: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4855b3: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4855b5: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4855b9: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4855bd: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 4855bf: fadd dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 4855c3: fstp dword ptr [esp + 0x84] */
	ST(0) = ST(0); FPOP();	/* 4855ca: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 4855cc: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 4855ce: fld dword ptr [esi + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x78u)));	/* 4855d1: fld dword ptr [esi + 0x78] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 4855d4: fld dword ptr [esi + 0x68] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4855d7: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4855db: fst dword ptr [esp + 0x14] */
	{ long double t = ST(1); FPUSH(t); }	/* 4855df: fld st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4855e1: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4855e5: fld dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 4855e9: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4855eb: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(3);	/* 4855ef: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4855f1: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4855f3: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4855f7: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4855fb: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 4855fd: fadd dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 485601: fstp dword ptr [esp + 0x88] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 485608: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(1);	/* 48560c: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 48560e: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(3);	/* 485612: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485614: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 485616: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48561a: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48561e: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 485620: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x8cu)) = (float)ST(0); FPOP();	/* 485624: fstp dword ptr [esp + 0x8c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 48562b: fld dword ptr [esp + 0x34] */
	ST(0) = ST(0) * ST(1);	/* 48562f: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 485631: fld dword ptr [esp + 0x44] */
	ST(0) = ST(0) * ST(3);	/* 485635: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485637: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 485639: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48563d: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485641: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 485643: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0x90u)) = (float)ST(0); FPOP();	/* 485647: fstp dword ptr [esp + 0x90] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48564e: fld dword ptr [esp + 0x38] */
	ST(0) = ST(0) * ST(1);	/* 485652: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 485654: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(3);	/* 485658: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48565a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 48565c: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485660: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485664: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 485666: fadd dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0x94u)) = (float)ST(0); FPOP();	/* 48566a: fstp dword ptr [esp + 0x94] */
	ST(0) = ST(0); FPOP();	/* 485671: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 485673: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 485675: fld dword ptr [esi + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x78u)));	/* 485678: fld dword ptr [esi + 0x78] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x74u)));	/* 48567b: fld dword ptr [esi + 0x74] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 48567e: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 485682: fst dword ptr [esp + 0x14] */
	{ long double t = ST(1); FPUSH(t); }	/* 485686: fld st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 485688: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 48568c: fld dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 485690: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 485692: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(3);	/* 485696: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485698: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 48569a: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48569e: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4856a2: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 4856a4: fadd dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x98u)) = (float)ST(0); FPOP();	/* 4856a8: fstp dword ptr [esp + 0x98] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4856af: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(1);	/* 4856b3: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4856b5: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(3);	/* 4856b9: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4856bb: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4856bd: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4856c1: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4856c5: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 4856c7: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x9cu)) = (float)ST(0); FPOP();	/* 4856cb: fstp dword ptr [esp + 0x9c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 4856d2: fld dword ptr [esp + 0x34] */
	ST(0) = ST(0) * ST(1);	/* 4856d6: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4856d8: fld dword ptr [esp + 0x44] */
	ST(0) = ST(0) * ST(3);	/* 4856dc: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4856de: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4856e0: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4856e4: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4856e8: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 4856ea: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0xa0u)) = (float)ST(0); FPOP();	/* 4856ee: fstp dword ptr [esp + 0xa0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4856f5: fld dword ptr [esp + 0x38] */
	ST(0) = ST(0) * ST(1);	/* 4856f9: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4856fb: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(3);	/* 4856ff: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485701: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 485703: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485707: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48570b: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 48570d: fadd dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0xa4u)) = (float)ST(0); FPOP();	/* 485711: fstp dword ptr [esp + 0xa4] */
	ST(0) = ST(0); FPOP();	/* 485718: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 48571a: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x7cu)));	/* 48571c: fld dword ptr [esi + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 48571f: fld dword ptr [esi + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 485722: fld dword ptr [esi + 0x68] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 485725: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 485729: fst dword ptr [esp + 0x14] */
	{ long double t = ST(1); FPUSH(t); }	/* 48572d: fld st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 48572f: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 485733: fld dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 485737: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 485739: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(3);	/* 48573d: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48573f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 485741: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485745: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485749: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 48574b: fadd dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0xa8u)) = (float)ST(0); FPOP();	/* 48574f: fstp dword ptr [esp + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 485756: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(1);	/* 48575a: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 48575c: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(3);	/* 485760: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485762: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 485764: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485768: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48576c: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 48576e: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0xacu)) = (float)ST(0); FPOP();	/* 485772: fstp dword ptr [esp + 0xac] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 485779: fld dword ptr [esp + 0x34] */
	ST(0) = ST(0) * ST(1);	/* 48577d: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 48577f: fld dword ptr [esp + 0x44] */
	ST(0) = ST(0) * ST(3);	/* 485783: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485785: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 485787: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48578b: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48578f: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 485791: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0xb0u)) = (float)ST(0); FPOP();	/* 485795: fstp dword ptr [esp + 0xb0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48579c: fld dword ptr [esp + 0x38] */
	ST(0) = ST(0) * ST(1);	/* 4857a0: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4857a2: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(3);	/* 4857a6: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4857a8: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4857aa: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4857ae: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4857b2: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 4857b4: fadd dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0xb4u)) = (float)ST(0); FPOP();	/* 4857b8: fstp dword ptr [esp + 0xb4] */
	ST(0) = ST(0); FPOP();	/* 4857bf: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 4857c1: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x7cu)));	/* 4857c3: fld dword ptr [esi + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 4857c6: fld dword ptr [esi + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x74u)));	/* 4857c9: fld dword ptr [esi + 0x74] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4857cc: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4857d0: fst dword ptr [esp + 0x14] */
	{ long double t = ST(1); FPUSH(t); }	/* 4857d4: fld st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4857d6: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4857da: fld dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 4857de: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4857e0: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(3);	/* 4857e4: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4857e6: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4857e8: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4857ec: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4857f0: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 4857f2: fadd dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0xb8u)) = (float)ST(0); FPOP();	/* 4857f6: fstp dword ptr [esp + 0xb8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4857fd: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(1);	/* 485801: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 485803: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(3);	/* 485807: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485809: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 48580b: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48580f: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485813: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 485815: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0xbcu)) = (float)ST(0); FPOP();	/* 485819: fstp dword ptr [esp + 0xbc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 485820: fld dword ptr [esp + 0x34] */
	ST(0) = ST(0) * ST(1);	/* 485824: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 485826: fld dword ptr [esp + 0x44] */
	ST(0) = ST(0) * ST(3);	/* 48582a: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48582c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 48582e: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485832: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485836: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 485838: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0xc0u)) = (float)ST(0); FPOP();	/* 48583c: fstp dword ptr [esp + 0xc0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 485843: fld dword ptr [esp + 0x38] */
	ST(0) = ST(0) * ST(1);	/* 485847: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 485849: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(3);	/* 48584d: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48584f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 485851: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485855: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485859: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 48585b: fadd dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0xc4u)) = (float)ST(0); FPOP();	/* 48585f: fstp dword ptr [esp + 0xc4] */
	ST(0) = ST(0); FPOP();	/* 485866: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 485868: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 48586a: fld dword ptr [esi + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 48586d: fld dword ptr [esi + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 485870: fld dword ptr [esi + 0x68] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 485873: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 485877: fst dword ptr [esp + 0x14] */
	{ long double t = ST(1); FPUSH(t); }	/* 48587b: fld st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 48587d: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 485881: fld dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 485885: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 485887: fld dword ptr [esp + 0x3c] */
	ST(0) = ST(0) * ST(3);	/* 48588b: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48588d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 48588f: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 485893: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485897: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 485899: fadd dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0xc8u)) = (float)ST(0); FPOP();	/* 48589d: fstp dword ptr [esp + 0xc8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4858a4: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(1);	/* 4858a8: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4858aa: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(3);	/* 4858ae: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4858b0: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4858b2: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4858b6: fmul dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 4858ba: lea eax, [esp + 0x10] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 4858be: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4858c2: push eax */
	m->edx = (DWORD)(m->esp + 0xdcu);	/* 4858c3: lea edx, [esp + 0xdc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4858ca: faddp st(1) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4858cc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4858cd: push edx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 4858ce: fadd dword ptr [esp + 0x5c] */
	MF((DWORD)(m->esp + 0xd8u)) = (float)ST(0); FPOP();	/* 4858d2: fstp dword ptr [esp + 0xd8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4858d9: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(1);	/* 4858dd: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 4858df: fld dword ptr [esp + 0x50] */
	ST(0) = ST(0) * ST(3);	/* 4858e3: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4858e5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4858e7: fld dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 4858eb: fmul dword ptr [esp + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4858ef: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 4858f1: fadd dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0xdcu)) = (float)ST(0); FPOP();	/* 4858f5: fstp dword ptr [esp + 0xdc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4858fc: fld dword ptr [esp + 0x44] */
	ST(0) = ST(0) * ST(1);	/* 485900: fmul st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 485902: fld dword ptr [esp + 0x54] */
	ST(0) = ST(0) * ST(3);	/* 485906: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485908: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 48590a: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 48590e: fmul dword ptr [esp + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 485912: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 485914: fadd dword ptr [esp + 0x64] */
	MF((DWORD)(m->esp + 0xe0u)) = (float)ST(0); FPOP();	/* 485918: fstp dword ptr [esp + 0xe0] */
	ST(0) = ST(0); FPOP();	/* 48591f: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 485921: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 485923: fld dword ptr [esi + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 485926: fld dword ptr [esi + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x74u)));	/* 485929: fld dword ptr [esi + 0x74] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 48592c: fstp dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 485930: fstp dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 485934: fstp dword ptr [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x48593du; native_call(m, 0x484860u);	/* 485938: call 0x484860 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48593d: add esp, 0xc */
	m->ebx = 0x111111u;	/* 485940: mov ebx, 0x111111 */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 485945: lea edx, [esp + 0x74] */
	m->ebp = 0x8u;	/* 485949: mov ebp, 8 */
L_48594e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 48594e: fld dword ptr [edx] */
	ST(0) = -ST(0);	/* 485950: fchs  */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0xfffffff4u));	/* 485952: fcom dword ptr [edx - 0xc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 485955: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 485957: test ah, 1 */
	if (!m->zf) goto L_485963;	/* 48595a: jne 0x485963 */
	m->ecx = 0x1u;	/* 48595c: mov ecx, 1 */
	goto L_485978;	/* 485961: jmp 0x485978 */
L_485963:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0xfffffff4u)));	/* 485963: fld dword ptr [edx - 0xc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x0u)); FPOP();	/* 485966: fcomp dword ptr [edx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 485968: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48596a: test ah, 1 */
	if (!m->zf) goto L_485976;	/* 48596d: jne 0x485976 */
	m->ecx = 0x10u;	/* 48596f: mov ecx, 0x10 */
	goto L_485978;	/* 485974: jmp 0x485978 */
L_485976:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 485976: xor ecx, ecx */
L_485978:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0xfffffff8u));	/* 485978: fcom dword ptr [edx - 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48597b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48597d: test ah, 1 */
	if (!m->zf) goto L_485987;	/* 485980: jne 0x485987 */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 485982: or ch, 1 */
	goto L_485996;	/* 485985: jmp 0x485996 */
L_485987:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0xfffffff8u)));	/* 485987: fld dword ptr [edx - 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x0u)); FPOP();	/* 48598a: fcomp dword ptr [edx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48598c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48598e: test ah, 1 */
	if (!m->zf) goto L_485996;	/* 485991: jne 0x485996 */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 485993: or ch, 0x10 */
L_485996:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0xfffffffcu)); FPOP();	/* 485996: fcomp dword ptr [edx - 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 485999: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48599b: test ah, 1 */
	if (!m->zf) goto L_4859a8;	/* 48599e: jne 0x4859a8 */
	{ DWORD a_ = m->ecx, b_ = 0x10000u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4859a0: or ecx, 0x10000 */
	goto L_4859ba;	/* 4859a6: jmp 0x4859ba */
L_4859a8:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0xfffffffcu)));	/* 4859a8: fld dword ptr [edx - 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x0u)); FPOP();	/* 4859ab: fcomp dword ptr [edx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4859ad: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4859af: test ah, 1 */
	if (!m->zf) goto L_4859ba;	/* 4859b2: jne 0x4859ba */
	{ DWORD a_ = m->ecx, b_ = 0x100000u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4859b4: or ecx, 0x100000 */
L_4859ba:
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4859ba: and ebx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4859bc: add edx, 0x10 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 4859bf: dec ebp */
	if (!m->zf) goto L_48594e;	/* 4859c0: jne 0x48594e */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x11u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4859c2: test bl, 0x11 */
	if (!m->zf) goto L_485aa6;	/* 4859c5: jne 0x485aa6 */
	{ DWORD a_ = m->ebx, b_ = 0x111100u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4859cb: test ebx, 0x111100 */
	if (!m->zf) goto L_485aa6;	/* 4859d1: jne 0x485aa6 */
	m->ebx = M32((DWORD)(m->esp + 0xecu));	/* 4859d7: mov ebx, dword ptr [esp + 0xec] */
L_4859de:
	m->ecx = M32((DWORD)(m->esp + 0x104u));	/* 4859de: mov ecx, dword ptr [esp + 0x104] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4859e5: test ecx, ecx */
	if (m->sf == m->of) goto L_4859ec;	/* 4859e7: jge 0x4859ec */
	m->ecx = M32((DWORD)(m->esi + 0x44u));	/* 4859e9: mov ecx, dword ptr [esi + 0x44] */
L_4859ec:
	m->edx = M32((DWORD)(m->edi + 0x9038u));	/* 4859ec: mov edx, dword ptr [edi + 0x9038] */
	m->eax = M32((DWORD)(m->edi + 0x9030u));	/* 4859f2: mov eax, dword ptr [edi + 0x9030] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4859f8: inc ecx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4859f9: cmp edx, eax */
	if (m->sf == m->of) goto L_485ad0;	/* 4859fb: jge 0x485ad0 */
	m->ebp = M32((DWORD)(m->edi + 0x9034u));	/* 485a01: mov ebp, dword ptr [edi + 0x9034] */
	m->eax = (DWORD)(m->edx*8 + 0x0u);	/* 485a07: lea eax, [edx*8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 485a0e: sub eax, edx */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 485a10: inc edx */
	M32((DWORD)(m->edi + 0x9038u)) = m->edx;	/* 485a11: mov dword ptr [edi + 0x9038], edx */
	m->eax = (DWORD)(m->ebp + m->eax*4 + 0x0u);	/* 485a17: lea eax, [ebp + eax*4] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 485a1b: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485a1d: cmp eax, ebp */
	if (m->zf) goto L_485ada;	/* 485a1f: je 0x485ada */
	{ DWORD a_ = M32((DWORD)(m->edi + m->ecx*4 + 0x3028u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485a25: cmp dword ptr [edi + ecx*4 + 0x3028], ebp */
	if (!m->zf) goto L_485a4c;	/* 485a2c: jne 0x485a4c */
	m->edx = M32((DWORD)(m->edi + 0x3024u));	/* 485a2e: mov edx, dword ptr [edi + 0x3024] */
	M32((DWORD)(m->edi + m->edx*4 + 0x20u)) = m->ecx;	/* 485a34: mov dword ptr [edi + edx*4 + 0x20], ecx */
	m->edx = M32((DWORD)(m->edi + 0x3024u));	/* 485a38: mov edx, dword ptr [edi + 0x3024] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 485a3e: inc edx */
	M32((DWORD)(m->edi + 0x3024u)) = m->edx;	/* 485a3f: mov dword ptr [edi + 0x3024], edx */
	M32((DWORD)(m->edi + m->ecx*4 + 0x3028u)) = m->eax;	/* 485a45: mov dword ptr [edi + ecx*4 + 0x3028], eax */
L_485a4c:
	m->edx = M32((DWORD)(m->edi + m->ecx*4 + 0x602cu));	/* 485a4c: mov edx, dword ptr [edi + ecx*4 + 0x602c] */
	{ DWORD a_ = m->edx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485a53: cmp edx, ebp */
	if (m->zf) goto L_485a5a;	/* 485a55: je 0x485a5a */
	M32((DWORD)(m->edx + 0x18u)) = m->eax;	/* 485a57: mov dword ptr [edx + 0x18], eax */
L_485a5a:
	M32((DWORD)(m->edi + m->ecx*4 + 0x602cu)) = m->eax;	/* 485a5a: mov dword ptr [edi + ecx*4 + 0x602c], eax */
	m->ecx = M32((DWORD)(m->esp + 0xf0u));	/* 485a61: mov ecx, dword ptr [esp + 0xf0] */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485a68: cmp ecx, ebp */
	M32((DWORD)(m->eax + 0x0u)) = m->esi;	/* 485a6a: mov dword ptr [eax], esi */
	if (m->zf) goto L_485a79;	/* 485a6c: je 0x485a79 */
	m->edx = M32((DWORD)(m->esi + 0x48u));	/* 485a6e: mov edx, dword ptr [esi + 0x48] */
	m->ecx = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 485a71: lea ecx, [ecx + edx*4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 485a74: mov dword ptr [eax + 4], ecx */
	goto L_485a7c;	/* 485a77: jmp 0x485a7c */
L_485a79:
	M32((DWORD)(m->eax + 0x4u)) = m->ebp;	/* 485a79: mov dword ptr [eax + 4], ebp */
L_485a7c:
	m->edx = M32((DWORD)(m->esp + 0xf8u));	/* 485a7c: mov edx, dword ptr [esp + 0xf8] */
	m->ecx = M32((DWORD)(m->esp + 0xfcu));	/* 485a83: mov ecx, dword ptr [esp + 0xfc] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 485a8a: mov dword ptr [eax + 8], edx */
	m->edx = M32((DWORD)(m->esp + 0x60u));	/* 485a8d: mov edx, dword ptr [esp + 0x60] */
	M32((DWORD)(m->eax + 0xcu)) = m->ecx;	/* 485a91: mov dword ptr [eax + 0xc], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x108u));	/* 485a94: mov ecx, dword ptr [esp + 0x108] */
	M32((DWORD)(m->eax + 0x10u)) = m->edx;	/* 485a9b: mov dword ptr [eax + 0x10], edx */
	M32((DWORD)(m->eax + 0x14u)) = m->ecx;	/* 485a9e: mov dword ptr [eax + 0x14], ecx */
	M32((DWORD)(m->eax + 0x18u)) = m->ebp;	/* 485aa1: mov dword ptr [eax + 0x18], ebp */
	goto L_485aad;	/* 485aa4: jmp 0x485aad */
L_485aa6:
	m->ebx = M32((DWORD)(m->esp + 0xecu));	/* 485aa6: mov ebx, dword ptr [esp + 0xec] */
L_485aad:
	m->eax = M32((DWORD)(m->esp + 0x64u));	/* 485aad: mov eax, dword ptr [esp + 0x64] */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 485ab1: mov edx, dword ptr [esp + 0x5c] */
	m->ecx = M32((DWORD)(m->ebx + 0x10u));	/* 485ab5: mov ecx, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 485ab8: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 485ab9: add edx, 0x80 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485abf: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x64u)) = m->eax;	/* 485ac1: mov dword ptr [esp + 0x64], eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 485ac5: mov dword ptr [esp + 0x5c], edx */
	if (m->sf == m->of) goto L_485ada;	/* 485ac9: jge 0x485ada */
	goto L_485470;	/* 485acb: jmp 0x485470 */
L_485ad0:
	M32((DWORD)(m->edi + 0x9090u)) = 0x1u;	/* 485ad0: mov dword ptr [edi + 0x9090], 1 */
L_485ada:
	m->edi = M32(m->esp); m->esp += 4;	/* 485ada: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 485adb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 485adc: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 485add: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485ade: add esp, 0xd8 */
	m->esp += 4 + 32; return;	/* 485ae4: ret 0x20 */
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
