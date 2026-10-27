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

static void lift_46f4e0(X86 *m);

/* data_loadFrom_46f4e0 (0x46f4e0), lifted by tools/lift.py */
static void lift_46f4e0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f4e0: sub esp, 0x10c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f4e6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46f4e7: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f4e8: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f4e9: push edi */
	m->esi = m->ecx;	/* 46f4ea: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x46f4f1u; native_call(m, 0x46f4b0u);	/* 46f4ec: call 0x46f4b0 */
	m->eax = M32((DWORD)(m->esp + 0x128u));	/* 46f4f1: mov eax, dword ptr [esp + 0x128] */
	m->ecx = M32((DWORD)(m->esp + 0x130u));	/* 46f4f8: mov ecx, dword ptr [esp + 0x130] */
	m->edx = M32((DWORD)(m->esp + 0x138u));	/* 46f4ff: mov edx, dword ptr [esp + 0x138] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 46f506: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f508: cmp eax, 0x40 */
	M32((DWORD)(m->esi + 0x10u)) = m->eax;	/* 46f50b: mov dword ptr [esi + 0x10], eax */
	M32((DWORD)(m->esi + 0x1cu)) = m->ecx;	/* 46f50e: mov dword ptr [esi + 0x1c], ecx */
	M32((DWORD)(m->esi + 0x2cu)) = m->edx;	/* 46f511: mov dword ptr [esi + 0x2c], edx */
	M32((DWORD)(m->esi + 0x18u)) = m->ebp;	/* 46f514: mov dword ptr [esi + 0x18], ebp */
	if (m->sf == m->of) goto L_46f55c;	/* 46f517: jge 0x46f55c */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f519: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_46f5d7;	/* 46f51b: jle 0x46f5d7 */
	m->edi = M32((DWORD)(m->esp + 0x12cu));	/* 46f521: mov edi, dword ptr [esp + 0x12c] */
	m->ebx = (DWORD)(m->esp + 0x1cu);	/* 46f528: lea ebx, [esp + 0x1c] */
L_46f52c:
	m->ecx = M32((DWORD)(m->esp + 0x120u));	/* 46f52c: mov ecx, dword ptr [esp + 0x120] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f533: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f535: push edi */
	m->esp -= 4; M32(m->esp) = 0x46f53bu; native_call(m, 0x466dc0u);	/* 46f536: call 0x466dc0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f53b: test eax, eax */
	M32((DWORD)(m->ebx + 0x0u)) = m->eax;	/* 46f53d: mov dword ptr [ebx], eax */
	if (m->zf) goto L_46f54c;	/* 46f53f: je 0x46f54c */
	m->eax = M32((DWORD)(m->eax + 0x18u));	/* 46f541: mov eax, dword ptr [eax + 0x18] */
	m->ecx = M32((DWORD)(m->esi + 0x18u));	/* 46f544: mov ecx, dword ptr [esi + 0x18] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46f547: add ecx, eax */
	M32((DWORD)(m->esi + 0x18u)) = m->ecx;	/* 46f549: mov dword ptr [esi + 0x18], ecx */
L_46f54c:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46f54c: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 46f54f: inc ebp */
	{ DWORD a_ = m->edi, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46f550: add edi, 0x44 */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46f553: add ebx, 4 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f556: cmp ebp, eax */
	if (m->sf != m->of) goto L_46f52c;	/* 46f558: jl 0x46f52c */
	goto L_46f5d7;	/* 46f55a: jmp 0x46f5d7 */
L_46f55c:
	m->edi = M32((DWORD)(m->esp + 0x12cu));	/* 46f55c: mov edi, dword ptr [esp + 0x12c] */
	m->ebx = (DWORD)(m->esp + 0x1cu);	/* 46f563: lea ebx, [esp + 0x1c] */
	m->ebp = 0x40u;	/* 46f567: mov ebp, 0x40 */
L_46f56c:
	m->ecx = M32((DWORD)(m->esp + 0x120u));	/* 46f56c: mov ecx, dword ptr [esp + 0x120] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f573: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f575: push edi */
	m->esp -= 4; M32(m->esp) = 0x46f57bu; native_call(m, 0x466dc0u);	/* 46f576: call 0x466dc0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f57b: test eax, eax */
	M32((DWORD)(m->ebx + 0x0u)) = m->eax;	/* 46f57d: mov dword ptr [ebx], eax */
	if (m->zf) goto L_46f58c;	/* 46f57f: je 0x46f58c */
	m->ecx = M32((DWORD)(m->eax + 0x18u));	/* 46f581: mov ecx, dword ptr [eax + 0x18] */
	m->eax = M32((DWORD)(m->esi + 0x18u));	/* 46f584: mov eax, dword ptr [esi + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46f587: add eax, ecx */
	M32((DWORD)(m->esi + 0x18u)) = m->eax;	/* 46f589: mov dword ptr [esi + 0x18], eax */
L_46f58c:
	{ DWORD a_ = m->edi, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46f58c: add edi, 0x44 */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46f58f: add ebx, 4 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 46f592: dec ebp */
	if (!m->zf) goto L_46f56c;	/* 46f593: jne 0x46f56c */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46f595: mov eax, dword ptr [esi + 0x10] */
	m->ebx = 0x40u;	/* 46f598: mov ebx, 0x40 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f59d: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_46f5d7;	/* 46f59f: jle 0x46f5d7 */
	m->edx = M32((DWORD)(m->esp + 0x12cu));	/* 46f5a1: mov edx, dword ptr [esp + 0x12c] */
	m->edi = (DWORD)(m->edx + 0x1100u);	/* 46f5a8: lea edi, [edx + 0x1100] */
L_46f5ae:
	m->ecx = M32((DWORD)(m->esp + 0x120u));	/* 46f5ae: mov ecx, dword ptr [esp + 0x120] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f5b5: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46f5b7: push edi */
	m->esp -= 4; M32(m->esp) = 0x46f5bdu; native_call(m, 0x466dc0u);	/* 46f5b8: call 0x466dc0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f5bd: test eax, eax */
	if (m->zf) goto L_46f5cc;	/* 46f5bf: je 0x46f5cc */
	m->eax = M32((DWORD)(m->eax + 0x18u));	/* 46f5c1: mov eax, dword ptr [eax + 0x18] */
	m->ecx = M32((DWORD)(m->esi + 0x18u));	/* 46f5c4: mov ecx, dword ptr [esi + 0x18] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46f5c7: add ecx, eax */
	M32((DWORD)(m->esi + 0x18u)) = m->ecx;	/* 46f5c9: mov dword ptr [esi + 0x18], ecx */
L_46f5cc:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46f5cc: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 46f5cf: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46f5d0: add edi, 0x44 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f5d3: cmp ebx, eax */
	if (m->sf != m->of) goto L_46f5ae;	/* 46f5d5: jl 0x46f5ae */
L_46f5d7:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46f5d7: mov eax, dword ptr [esi + 0x10] */
	m->edi = M32((DWORD)(m->esi + 0x1cu));	/* 46f5da: mov edi, dword ptr [esi + 0x1c] */
	m->ecx = M32((DWORD)(m->esi + 0x2cu));	/* 46f5dd: mov ecx, dword ptr [esi + 0x2c] */
	m->ebx = 0x1u;	/* 46f5e0: mov ebx, 1 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46f5e5: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46f5e8: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46f5eb: add eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46f5ed: shl eax, 2 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f5f0: cmp ecx, ebx */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 46f5f2: mov dword ptr [esi + 4], eax */
	if (!m->zf) goto L_46f600;	/* 46f5f5: jne 0x46f600 */
	m->ecx = M32((DWORD)(m->esi + 0x18u));	/* 46f5f7: mov ecx, dword ptr [esi + 0x18] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 46f5fa: lea edx, [eax + ecx*4] */
	M32((DWORD)(m->esi + 0x4u)) = m->edx;	/* 46f5fd: mov dword ptr [esi + 4], edx */
L_46f600:
	m->edi = M32((DWORD)(m->esp + 0x144u));	/* 46f600: mov edi, dword ptr [esp + 0x144] */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 46f607: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f60a: test edi, edi */
	if (!m->zf) goto L_46f639;	/* 46f60c: jne 0x46f639 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f60e: push eax */
	m->esp -= 4; M32(m->esp) = 0x46f614u; native_call(m, 0x49f1aau);	/* 46f60f: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f614: add esp, 4 */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 46f617: mov dword ptr [esi + 8], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f61a: test eax, eax */
	if (!m->zf) goto L_46f634;	/* 46f61c: jne 0x46f634 */
	m->ecx = M32((DWORD)(m->esi + 0x4u));	/* 46f61e: mov ecx, dword ptr [esi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f621: push ecx */
	{ DWORD v_ = 0x4c4becu; m->esp -= 4; M32(m->esp) = v_; }	/* 46f622: push 0x4c4bec */
	{ DWORD v_ = 0xae2e98u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f627: push 0xae2e98 */
	m->esp -= 4; M32(m->esp) = 0x46f631u; native_call(m, 0x46c710u);	/* 46f62c: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f631: add esp, 0xc */
L_46f634:
	M32((DWORD)(m->esi + 0xcu)) = m->ebx;	/* 46f634: mov dword ptr [esi + 0xc], ebx */
	goto L_46f65b;	/* 46f637: jmp 0x46f65b */
L_46f639:
	m->ecx = M32((DWORD)(m->esp + 0x148u));	/* 46f639: mov ecx, dword ptr [esp + 0x148] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f640: cmp ecx, eax */
	if (m->sf == m->of) goto L_46f658;	/* 46f642: jge 0x46f658 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f644: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f645: push eax */
	{ DWORD v_ = 0x4c4b08u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f646: push 0x4c4b08 */
	{ DWORD v_ = 0xae2e98u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f64b: push 0xae2e98 */
	m->esp -= 4; M32(m->esp) = 0x46f655u; native_call(m, 0x46c710u);	/* 46f650: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f655: add esp, 0x10 */
L_46f658:
	M32((DWORD)(m->esi + 0x8u)) = m->edi;	/* 46f658: mov dword ptr [esi + 8], edi */
L_46f65b:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46f65b: mov eax, dword ptr [esi + 0x10] */
	m->edx = M32((DWORD)(m->esi + 0x8u));	/* 46f65e: mov edx, dword ptr [esi + 8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46f661: xor ecx, ecx */
	M32((DWORD)(m->esi + 0x14u)) = m->edx;	/* 46f663: mov dword ptr [esi + 0x14], edx */
	m->ebx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46f666: lea ebx, [eax + eax*4] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 46f669: mov dword ptr [esp + 0x14], ecx */
	m->ebx = (DWORD)(m->ebx + m->ebx*4 + 0x0u);	/* 46f66d: lea ebx, [ebx + ebx*4] */
	{ DWORD a_ = m->ebx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 46f670: shl ebx, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f673: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_46f70c;	/* 46f675: jle 0x46f70c */
	m->ebp = M32((DWORD)(m->esp + 0x12cu));	/* 46f67b: mov ebp, dword ptr [esp + 0x12c] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 46f682: lea eax, [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 46f686: mov dword ptr [esp + 0x18], ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 46f68a: mov dword ptr [esp + 0x10], eax */
L_46f68e:
	m->edx = M32((DWORD)(m->esi + 0x14u));	/* 46f68e: mov edx, dword ptr [esi + 0x14] */
	m->edi = m->ecx;	/* 46f691: mov edi, ecx */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46f693: add edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0x1900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f695: cmp ecx, 0x1900 */
	if (m->sf == m->of) goto L_46f6a7;	/* 46f69b: jge 0x46f6a7 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46f69d: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 46f6a1: mov eax, dword ptr [edx] */
	M32((DWORD)(m->edi + 0x0u)) = m->eax;	/* 46f6a3: mov dword ptr [edi], eax */
	goto L_46f6bc;	/* 46f6a5: jmp 0x46f6bc */
L_46f6a7:
	m->ecx = M32((DWORD)(m->esp + 0x120u));	/* 46f6a7: mov ecx, dword ptr [esp + 0x120] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46f6ae: push 0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46f6b0: push ebp */
	m->esp -= 4; M32(m->esp) = 0x46f6b6u; native_call(m, 0x466dc0u);	/* 46f6b1: call 0x466dc0 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 46f6b6: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->edi + 0x0u)) = m->eax;	/* 46f6ba: mov dword ptr [edi], eax */
L_46f6bc:
	m->edx = M32((DWORD)(m->ebp + 0x40u));	/* 46f6bc: mov edx, dword ptr [ebp + 0x40] */
	M32((DWORD)(m->edi + 0x4u)) = m->edx;	/* 46f6bf: mov dword ptr [edi + 4], edx */
	m->eax = M32((DWORD)(m->esi + 0x2cu));	/* 46f6c2: mov eax, dword ptr [esi + 0x2c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f6c5: cmp eax, 1 */
	if (!m->zf) goto L_46f6e0;	/* 46f6c8: jne 0x46f6e0 */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 46f6ca: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f6cc: test eax, eax */
	if (m->zf) goto L_46f6e0;	/* 46f6ce: je 0x46f6e0 */
	m->edx = m->ebx;	/* 46f6d0: mov edx, ebx */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esi + 0x8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46f6d2: add edx, dword ptr [esi + 8] */
	M32((DWORD)(m->edi + 0x8u)) = m->edx;	/* 46f6d5: mov dword ptr [edi + 8], edx */
	m->eax = M32((DWORD)(m->eax + 0x18u));	/* 46f6d8: mov eax, dword ptr [eax + 0x18] */
	m->ebx = (DWORD)(m->ebx + m->eax*4 + 0x0u);	/* 46f6db: lea ebx, [ebx + eax*4] */
	goto L_46f6e7;	/* 46f6de: jmp 0x46f6e7 */
L_46f6e0:
	M32((DWORD)(m->edi + 0x8u)) = 0x0u;	/* 46f6e0: mov dword ptr [edi + 8], 0 */
L_46f6e7:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46f6e7: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 46f6eb: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46f6ef: add edx, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46f6f2: inc eax */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 46f6f3: mov dword ptr [esp + 0x10], edx */
	m->edx = M32((DWORD)(m->esi + 0x10u));	/* 46f6f7: mov edx, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46f6fa: add ecx, 0x64 */
	{ DWORD a_ = m->ebp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46f6fd: add ebp, 0x44 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f700: cmp eax, edx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 46f702: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 46f706: mov dword ptr [esp + 0x18], ecx */
	if (m->sf != m->of) goto L_46f68e;	/* 46f70a: jl 0x46f68e */
L_46f70c:
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 46f70c: mov ecx, dword ptr [esi + 8] */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 46f70f: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46f712: add ebx, ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46f714: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46f716: test eax, eax */
	M32((DWORD)(m->esi + 0x20u)) = m->ebx;	/* 46f718: mov dword ptr [esi + 0x20], ebx */
	if (m->zf || m->sf != m->of) goto L_46f745;	/* 46f71b: jle 0x46f745 */
	m->ebx = M32((DWORD)(m->esp + 0x134u));	/* 46f71d: mov ebx, dword ptr [esp + 0x134] */
L_46f724:
	m->ecx = M32((DWORD)(m->esi + 0x20u));	/* 46f724: mov ecx, dword ptr [esi + 0x20] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f727: push ebx */
	m->ebp = (DWORD)(m->ecx + m->edi*4 + 0x0u);	/* 46f728: lea ebp, [ecx + edi*4] */
	m->ecx = M32((DWORD)(m->esp + 0x128u));	/* 46f72b: mov ecx, dword ptr [esp + 0x128] */
	m->esp -= 4; M32(m->esp) = 0x46f737u; native_call(m, 0x46b1a0u);	/* 46f732: call 0x46b1a0 */
	M32((DWORD)(m->ebp + 0x0u)) = m->eax;	/* 46f737: mov dword ptr [ebp], eax */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 46f73a: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 46f73d: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46f73e: add ebx, 0x40 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f741: cmp edi, eax */
	if (m->sf != m->of) goto L_46f724;	/* 46f743: jl 0x46f724 */
L_46f745:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46f745: cmp dword ptr [esi + 0x2c], 1 */
	if (!m->zf) goto L_46f762;	/* 46f749: jne 0x46f762 */
	m->edx = M32((DWORD)(m->esp + 0x140u));	/* 46f74b: mov edx, dword ptr [esp + 0x140] */
	m->eax = M32((DWORD)(m->esp + 0x13cu));	/* 46f752: mov eax, dword ptr [esp + 0x13c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46f759: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46f75a: push eax */
	m->ecx = m->esi;	/* 46f75b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x46f762u; native_call(m, 0x46f7a0u);	/* 46f75d: call 0x46f7a0 */
L_46f762:
	m->edi = M32(m->esp); m->esp += 4;	/* 46f762: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46f763: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46f764: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46f765: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46f766: add esp, 0x10c */
	m->esp += 4 + 44; return;	/* 46f76c: ret 0x2c */
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
