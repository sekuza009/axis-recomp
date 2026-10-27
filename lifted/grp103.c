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

static void lift_453790(X86 *m);
static void lift_453cf0(X86 *m);
static void lift_453e60(X86 *m);
static void lift_454190(X86 *m);

/* dplay_getPlayerName (0x454190), lifted by tools/lift.py */
static void lift_454190(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b404u));	/* 454190: mov eax, dword ptr [0xa0b404] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 454195: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x8u));	/* 454196: mov ebx, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45419a: push esi */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 45419b: mov ecx, dword ptr [eax] */
	m->edx = (DWORD)(m->esp + 0xcu);	/* 45419d: lea edx, [esp + 0xc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4541a1: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4541a2: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4541a3: push 0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4541a5: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4541a6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4541aau; native_call(m, M32((DWORD)(m->ecx + 0x54u)));	/* 4541a7: call dword ptr [ecx + 0x54] */
	m->esi = m->eax;	/* 4541aa: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = 0x8877001eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4541ac: cmp esi, 0x8877001e */
	if (!m->zf) goto L_45420b;	/* 4541b2: jne 0x45420b */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4541b4: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4541b8: push eax */
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 4541b9: push 0x42 */
	m->esp -= 4; M32(m->esp) = 0x4541c1u; native_call(m, M32(0x4a9070u));	/* 4541bb: call dword ptr [0x4a9070] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4541c1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4541c8u; native_call(m, M32(0x4a9198u));	/* 4541c2: call dword ptr [0x4a9198] */
	m->edi = m->eax;	/* 4541c8: mov edi, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4541ca: test edi, edi */
	if (!m->zf) goto L_4541d5;	/* 4541cc: jne 0x4541d5 */
	m->esi = 0x8007000eu;	/* 4541ce: mov esi, 0x8007000e */
	goto L_4541ed;	/* 4541d3: jmp 0x4541ed */
L_4541d5:
	m->eax = M32((DWORD)(0xa0b404u));	/* 4541d5: mov eax, dword ptr [0xa0b404] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 4541da: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4541de: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4541df: push edi */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4541e0: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4541e2: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4541e3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4541e7u; native_call(m, M32((DWORD)(m->ecx + 0x54u)));	/* 4541e4: call dword ptr [ecx + 0x54] */
	m->esi = m->eax;	/* 4541e7: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4541e9: test esi, esi */
	if (m->sf == m->of) goto L_454211;	/* 4541eb: jge 0x454211 */
L_4541ed:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4541ed: test edi, edi */
	if (m->zf) goto L_45420b;	/* 4541ef: je 0x45420b */
	m->ebx = M32((DWORD)(0x4a9078u));	/* 4541f1: mov ebx, dword ptr [0x4a9078] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4541f7: push edi */
	m->esp -= 4; M32(m->esp) = 0x4541fau; native_call(m, m->ebx);	/* 4541f8: call ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4541fa: push eax */
	m->esp -= 4; M32(m->esp) = 0x454201u; native_call(m, M32(0x4a918cu));	/* 4541fb: call dword ptr [0x4a918c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 454201: push edi */
	m->esp -= 4; M32(m->esp) = 0x454204u; native_call(m, m->ebx);	/* 454202: call ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454204: push eax */
	m->esp -= 4; M32(m->esp) = 0x45420bu; native_call(m, M32(0x4a9190u));	/* 454205: call dword ptr [0x4a9190] */
L_45420b:
	m->eax = m->esi;	/* 45420b: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 45420d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45420e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45420f: pop ebx */
	m->esp += 4 + 0; return;	/* 454210: ret  */
L_454211:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 454211: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x0u)) = m->edi;	/* 454215: mov dword ptr [eax], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 454217: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 454218: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454219: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45421b: pop ebx */
	m->esp += 4 + 0; return;	/* 45421c: ret  */
}

/* dplay_create (0x453790), lifted by tools/lift.py */
static void lift_453790(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453790: sub esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453793: push esi */
	{ DWORD v_ = 0xa0b398u; m->esp -= 4; M32(m->esp) = v_; }	/* 453794: push 0xa0b398 */
	{ DWORD v_ = 0x4a9658u; m->esp -= 4; M32(m->esp) = v_; }	/* 453799: push 0x4a9658 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45379e: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4537a0: push 0 */
	{ DWORD v_ = 0x4a9648u; m->esp -= 4; M32(m->esp) = v_; }	/* 4537a2: push 0x4a9648 */
	m->esp -= 4; M32(m->esp) = 0x4537adu; native_call(m, M32(0x4a93b4u));	/* 4537a7: call dword ptr [0x4a93b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4537ad: test eax, eax */
	if (m->sf != m->of) goto L_4538b4;	/* 4537af: jl 0x4538b4 */
	m->eax = M32((DWORD)(0xa0b398u));	/* 4537b5: mov eax, dword ptr [0xa0b398] */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 4537ba: lea edx, [esp + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4537be: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4537bf: push 0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4537c1: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4537c3: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4537c5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4537c9u; native_call(m, M32((DWORD)(m->ecx + 0x20u)));	/* 4537c6: call dword ptr [ecx + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x8877001eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4537c9: cmp eax, 0x8877001e */
	if (!m->zf) goto L_4538b4;	/* 4537ce: jne 0x4538b4 */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4537d4: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4537d8: push eax */
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 4537d9: push 0x42 */
	m->esp -= 4; M32(m->esp) = 0x4537e1u; native_call(m, M32(0x4a9070u));	/* 4537db: call dword ptr [0x4a9070] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4537e1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4537e8u; native_call(m, M32(0x4a9198u));	/* 4537e2: call dword ptr [0x4a9198] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4537e8: test eax, eax */
	M32((DWORD)(0xa0baf4u)) = m->eax;	/* 4537ea: mov dword ptr [0xa0baf4], eax */
	if (m->zf) goto L_4538b4;	/* 4537ef: je 0x4538b4 */
	m->ecx = M32((DWORD)(0xa0b398u));	/* 4537f5: mov ecx, dword ptr [0xa0b398] */
	m->esi = (DWORD)(m->esp + 0x4u);	/* 4537fb: lea esi, [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4537ff: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453800: push eax */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 453801: mov edx, dword ptr [ecx] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453803: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453805: push ecx */
	m->esp -= 4; M32(m->esp) = 0x453809u; native_call(m, M32((DWORD)(m->edx + 0x20u)));	/* 453806: call dword ptr [edx + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453809: test eax, eax */
	if (m->sf != m->of) goto L_4538b4;	/* 45380b: jl 0x4538b4 */
	m->eax = M32((DWORD)(0xa0baf4u));	/* 453811: mov eax, dword ptr [0xa0baf4] */
	m->ecx = M32((DWORD)(m->eax + 0x8u));	/* 453816: mov ecx, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x4u)) = 0x44u;	/* 453819: mov dword ptr [ecx + 4], 0x44 */
	m->edx = M32((DWORD)(0xa0baf4u));	/* 453820: mov edx, dword ptr [0xa0baf4] */
	m->eax = M32((DWORD)(m->edx + 0x8u));	/* 453826: mov eax, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x28u)) = 0x10u;	/* 453829: mov dword ptr [eax + 0x28], 0x10 */
	m->edx = M32((DWORD)(0xa0baf4u));	/* 453830: mov edx, dword ptr [0xa0baf4] */
	m->eax = M32((DWORD)(0xa0b398u));	/* 453836: mov eax, dword ptr [0xa0b398] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45383b: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45383c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45383e: push 0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 453840: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453842: push eax */
	m->esp -= 4; M32(m->esp) = 0x453846u; native_call(m, M32((DWORD)(m->ecx + 0x30u)));	/* 453843: call dword ptr [ecx + 0x30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453846: test eax, eax */
	if (m->sf != m->of) goto L_4538b4;	/* 453848: jl 0x4538b4 */
	m->eax = M32((DWORD)(0xa0b398u));	/* 45384a: mov eax, dword ptr [0xa0b398] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45384f: push 0 */
	{ DWORD v_ = 0xa0b404u; m->esp -= 4; M32(m->esp) = v_; }	/* 453851: push 0xa0b404 */
	{ DWORD v_ = 0x4a9678u; m->esp -= 4; M32(m->esp) = v_; }	/* 453856: push 0x4a9678 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 45385b: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45385d: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45385f: push eax */
	m->esp -= 4; M32(m->esp) = 0x453863u; native_call(m, M32((DWORD)(m->ecx + 0x3cu)));	/* 453860: call dword ptr [ecx + 0x3c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453863: test eax, eax */
	if (m->sf != m->of) goto L_4538b4;	/* 453865: jl 0x4538b4 */
	m->ecx = M32((DWORD)(0xa0baf4u));	/* 453867: mov ecx, dword ptr [0xa0baf4] */
	m->eax = M32((DWORD)(0xa0b404u));	/* 45386d: mov eax, dword ptr [0xa0b404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453872: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453874: push 0 */
	m->ecx = M32((DWORD)(m->ecx + 0xcu));	/* 453876: mov ecx, dword ptr [ecx + 0xc] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 453879: mov edx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45387b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45387d: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45387f: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 453880: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453884: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453885: push eax */
	m->esp -= 4; M32(m->esp) = 0x453889u; native_call(m, M32((DWORD)(m->edx + 0x18u)));	/* 453886: call dword ptr [edx + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453889: test eax, eax */
	if (m->sf != m->of) goto L_4538b4;	/* 45388b: jl 0x4538b4 */
	m->edx = M32((DWORD)(0xa0baf4u));	/* 45388d: mov edx, dword ptr [0xa0baf4] */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 453893: mov eax, dword ptr [edx + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 453896: test al, 2 */
	if (m->zf) goto L_4538a6;	/* 453898: je 0x4538a6 */
	M32((DWORD)(0xa0baf8u)) = 0x1u;	/* 45389a: mov dword ptr [0xa0baf8], 1 */
	goto L_4538b4;	/* 4538a4: jmp 0x4538b4 */
L_4538a6:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4538a6: test al, 1 */
	if (m->zf) goto L_4538b4;	/* 4538a8: je 0x4538b4 */
	M32((DWORD)(0xa0baf8u)) = 0x0u;	/* 4538aa: mov dword ptr [0xa0baf8], 0 */
L_4538b4:
	{ DWORD v_ = 0xa0b404u; m->esp -= 4; M32(m->esp) = v_; }	/* 4538b4: push 0xa0b404 */
	m->esp -= 4; M32(m->esp) = 0x4538beu; native_call(m, 0x4539f0u);	/* 4538b9: call 0x4539f0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4538be: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4538c1: test eax, eax */
	if (m->sf != m->of) goto L_453916;	/* 4538c3: jl 0x453916 */
	m->eax = M32((DWORD)(0xa0b404u));	/* 4538c5: mov eax, dword ptr [0xa0b404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4538ca: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4538cc: push 0 */
	{ DWORD v_ = 0x4532f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4538ce: push 0x4532f0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4538d3: mov ecx, dword ptr [eax] */
	{ DWORD v_ = 0x4a96e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4538d5: push 0x4a96e8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4538da: push eax */
	m->esp -= 4; M32(m->esp) = 0x4538e1u; native_call(m, M32((DWORD)(m->ecx + 0x8cu)));	/* 4538db: call dword ptr [ecx + 0x8c] */
	m->esi = m->eax;	/* 4538e1: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4538e3: test esi, esi */
	if (m->sf != m->of) goto L_4538e9;	/* 4538e5: jl 0x4538e9 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4538e7: xor esi, esi */
L_4538e9:
	m->eax = M32((DWORD)(0xa0baf4u));	/* 4538e9: mov eax, dword ptr [0xa0baf4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4538ee: test eax, eax */
	if (m->zf) goto L_453914;	/* 4538f0: je 0x453914 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4538f2: push edi */
	m->edi = M32((DWORD)(0x4a9078u));	/* 4538f3: mov edi, dword ptr [0x4a9078] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4538f9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4538fcu; native_call(m, m->edi);	/* 4538fa: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4538fc: push eax */
	m->esp -= 4; M32(m->esp) = 0x453903u; native_call(m, M32(0x4a918cu));	/* 4538fd: call dword ptr [0x4a918c] */
	m->edx = M32((DWORD)(0xa0baf4u));	/* 453903: mov edx, dword ptr [0xa0baf4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453909: push edx */
	m->esp -= 4; M32(m->esp) = 0x45390cu; native_call(m, m->edi);	/* 45390a: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45390c: push eax */
	m->esp -= 4; M32(m->esp) = 0x453913u; native_call(m, M32(0x4a9190u));	/* 45390d: call dword ptr [0x4a9190] */
	m->edi = M32(m->esp); m->esp += 4;	/* 453913: pop edi */
L_453914:
	m->eax = m->esi;	/* 453914: mov eax, esi */
L_453916:
	m->esi = M32(m->esp); m->esp += 4;	/* 453916: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453917: add esp, 8 */
	m->esp += 4 + 0; return;	/* 45391a: ret  */
}

/* dplay_hostSession (0x453cf0), lifted by tools/lift.py */
static void lift_453cf0(X86 *m)
{
	m->edx = M32((DWORD)(0xa0b404u));	/* 453cf0: mov edx, dword ptr [0xa0b404] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453cf6: sub esp, 0x10 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453cf9: test edx, edx */
	if (!m->zf) goto L_453d03;	/* 453cfb: jne 0x453d03 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453cfd: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453cff: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453d02: ret  */
L_453d03:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 453d03: push edi */
	m->ecx = 0x14u;	/* 453d04: mov ecx, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453d09: xor eax, eax */
	m->edi = 0xa0b3b0u;	/* 453d0b: mov edi, 0xa0b3b0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 453d10: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0xa0bad8u));	/* 453d12: mov eax, dword ptr [0xa0bad8] */
	M32((DWORD)(0xa0b3b0u)) = 0x50u;	/* 453d17: mov dword ptr [0xa0b3b0], 0x50 */
	M32((DWORD)(0xa0b3b4u)) = 0x44u;	/* 453d21: mov dword ptr [0xa0b3b4], 0x44 */
	m->edi = M32(m->esp); m->esp += 4;	/* 453d2b: pop edi */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 453d2c: mov ecx, dword ptr [eax] */
	M32((DWORD)(0xa0b3b8u)) = m->ecx;	/* 453d2e: mov dword ptr [0xa0b3b8], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 453d34: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(0xa0b3bcu)) = m->ecx;	/* 453d37: mov dword ptr [0xa0b3bc], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x8u));	/* 453d3d: mov ecx, dword ptr [eax + 8] */
	M32((DWORD)(0xa0b3c0u)) = m->ecx;	/* 453d40: mov dword ptr [0xa0b3c0], ecx */
	m->ecx = M32((DWORD)(0x4a96e8u));	/* 453d46: mov ecx, dword ptr [0x4a96e8] */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 453d4c: mov eax, dword ptr [eax + 0xc] */
	M32((DWORD)(0xa0b3c8u)) = m->ecx;	/* 453d4f: mov dword ptr [0xa0b3c8], ecx */
	m->ecx = M32((DWORD)(0x4a96f0u));	/* 453d55: mov ecx, dword ptr [0x4a96f0] */
	M32((DWORD)(0xa0b3c4u)) = m->eax;	/* 453d5b: mov dword ptr [0xa0b3c4], eax */
	m->eax = M32((DWORD)(0x4a96ecu));	/* 453d60: mov eax, dword ptr [0x4a96ec] */
	M32((DWORD)(0xa0b3d0u)) = m->ecx;	/* 453d65: mov dword ptr [0xa0b3d0], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 453d6b: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(0xa0b3ccu)) = m->eax;	/* 453d6f: mov dword ptr [0xa0b3cc], eax */
	m->eax = M32((DWORD)(0x4a96f4u));	/* 453d74: mov eax, dword ptr [0x4a96f4] */
	M32((DWORD)(0xa0b3e0u)) = m->ecx;	/* 453d79: mov dword ptr [0xa0b3e0], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 453d7f: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(0xa0b3d4u)) = m->eax;	/* 453d83: mov dword ptr [0xa0b3d4], eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 453d88: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(0xa0b3d8u)) = m->ecx;	/* 453d8c: mov dword ptr [0xa0b3d8], ecx */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x28u)));	/* 453d92: movsx ecx, byte ptr [esp + 0x28] */
	M32((DWORD)(0xa0b3f0u)) = m->eax;	/* 453d97: mov dword ptr [0xa0b3f0], eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 453d9c: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(0xa0b3f4u)) = m->eax;	/* 453da0: mov dword ptr [0xa0b3f4], eax */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x2cu)));	/* 453da5: movsx eax, byte ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 453daa: shl ecx, 8 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 453dad: or ecx, eax */
	m->eax = M32((DWORD)(0xa0b418u));	/* 453daf: mov eax, dword ptr [0xa0b418] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453db4: test eax, eax */
	M32((DWORD)(0xa0b3f8u)) = m->ecx;	/* 453db6: mov dword ptr [0xa0b3f8], ecx */
	if (!m->zf) goto L_453dd3;	/* 453dbc: jne 0x453dd3 */
	m->esp -= 4; M32(m->esp) = 0x453dc3u; native_call(m, 0x454220u);	/* 453dbe: call 0x454220 */
	m->esp -= 4; M32(m->esp) = 0x453dc8u; native_call(m, 0x4542a0u);	/* 453dc3: call 0x4542a0 */
	m->edx = M32((DWORD)(0xa0b404u));	/* 453dc8: mov edx, dword ptr [0xa0b404] */
	M32((DWORD)(0xa0b3fcu)) = m->eax;	/* 453dce: mov dword ptr [0xa0b3fc], eax */
L_453dd3:
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 453dd3: mov ecx, dword ptr [edx] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 453dd5: push 2 */
	{ DWORD v_ = 0xa0b3b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453dd7: push 0xa0b3b0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453ddc: push edx */
	m->esp -= 4; M32(m->esp) = 0x453de0u; native_call(m, M32((DWORD)(m->ecx + 0x60u)));	/* 453ddd: call dword ptr [ecx + 0x60] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453de0: test eax, eax */
	if (m->sf != m->of) goto L_453e27;	/* 453de2: jl 0x453e27 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 453de4: xor edx, edx */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 453de6: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x0u)) = m->edx;	/* 453dea: mov dword ptr [esp], edx */
	M32((DWORD)(m->esp + 0x0u)) = 0x10u;	/* 453dee: mov dword ptr [esp], 0x10 */
	M32((DWORD)(m->esp + 0x4u)) = m->edx;	/* 453df6: mov dword ptr [esp + 4], edx */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 453dfa: mov dword ptr [esp + 8], edx */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 453dfe: mov dword ptr [esp + 8], eax */
	m->eax = M32((DWORD)(0xa0b404u));	/* 453e02: mov eax, dword ptr [0xa0b404] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453e07: push edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453e08: push edx */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 453e09: mov dword ptr [esp + 0x14], edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453e0d: push edx */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 453e0e: mov dword ptr [esp + 0x18], edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 453e12: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453e14: push edx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 453e15: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453e19: push edx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 453e1a: lea edx, [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453e1e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453e1f: push eax */
	m->esp -= 4; M32(m->esp) = 0x453e23u; native_call(m, M32((DWORD)(m->ecx + 0x18u)));	/* 453e20: call dword ptr [ecx + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453e23: test eax, eax */
	if (m->sf == m->of) goto L_453e2d;	/* 453e25: jge 0x453e2d */
L_453e27:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453e27: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453e29: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453e2c: ret  */
L_453e2d:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 453e2d: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 453e31: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(0xa0b428u)) = m->eax;	/* 453e35: mov dword ptr [0xa0b428], eax */
	M32((DWORD)(0xa0b424u)) = m->ecx;	/* 453e3a: mov dword ptr [0xa0b424], ecx */
	M32((DWORD)(0xa0baf8u)) = 0x1u;	/* 453e40: mov dword ptr [0xa0baf8], 1 */
	m->esp -= 4; M32(m->esp) = 0x453e4fu; native_call(m, 0x451410u);	/* 453e4a: call 0x451410 */
	m->eax = 0x1u;	/* 453e4f: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453e54: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453e57: ret  */
}

/* dplay_joinSession (0x453e60), lifted by tools/lift.py */
static void lift_453e60(X86 *m)
{
	m->edx = M32((DWORD)(0xa0b404u));	/* 453e60: mov edx, dword ptr [0xa0b404] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453e66: sub esp, 0x10 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453e69: test edx, edx */
	if (!m->zf) goto L_453e76;	/* 453e6b: jne 0x453e76 */
	m->eax = 0x1fbu;	/* 453e6d: mov eax, 0x1fb */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453e72: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453e75: ret  */
L_453e76:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 453e76: push edi */
	m->ecx = 0x14u;	/* 453e77: mov ecx, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453e7c: xor eax, eax */
	m->edi = 0xa0b3b0u;	/* 453e7e: mov edi, 0xa0b3b0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 453e83: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 453e85: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(0xa0b3b0u)) = 0x50u;	/* 453e89: mov dword ptr [0xa0b3b0], 0x50 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 453e93: push 1 */
	{ DWORD v_ = 0xa0b3b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453e95: push 0xa0b3b0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 453e9a: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453e9c: push edx */
	M32((DWORD)(0xa0b3b8u)) = m->ecx;	/* 453e9d: mov dword ptr [0xa0b3b8], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 453ea3: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(0xa0b3bcu)) = m->ecx;	/* 453ea6: mov dword ptr [0xa0b3bc], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x8u));	/* 453eac: mov ecx, dword ptr [eax + 8] */
	M32((DWORD)(0xa0b3c0u)) = m->ecx;	/* 453eaf: mov dword ptr [0xa0b3c0], ecx */
	m->ecx = M32((DWORD)(0x4a96e8u));	/* 453eb5: mov ecx, dword ptr [0x4a96e8] */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 453ebb: mov eax, dword ptr [eax + 0xc] */
	M32((DWORD)(0xa0b3c8u)) = m->ecx;	/* 453ebe: mov dword ptr [0xa0b3c8], ecx */
	m->ecx = M32((DWORD)(0x4a96f0u));	/* 453ec4: mov ecx, dword ptr [0x4a96f0] */
	M32((DWORD)(0xa0b3c4u)) = m->eax;	/* 453eca: mov dword ptr [0xa0b3c4], eax */
	m->eax = M32((DWORD)(0x4a96ecu));	/* 453ecf: mov eax, dword ptr [0x4a96ec] */
	M32((DWORD)(0xa0b3d0u)) = m->ecx;	/* 453ed4: mov dword ptr [0xa0b3d0], ecx */
	M32((DWORD)(0xa0b3ccu)) = m->eax;	/* 453eda: mov dword ptr [0xa0b3cc], eax */
	m->eax = M32((DWORD)(0x4a96f4u));	/* 453edf: mov eax, dword ptr [0x4a96f4] */
	M32((DWORD)(0xa0b3d4u)) = m->eax;	/* 453ee4: mov dword ptr [0xa0b3d4], eax */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 453ee9: mov ecx, dword ptr [edx] */
	m->esp -= 4; M32(m->esp) = 0x453eeeu; native_call(m, M32((DWORD)(m->ecx + 0x60u)));	/* 453eeb: call dword ptr [ecx + 0x60] */
	{ DWORD a_ = m->eax, b_ = 0x887700dcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453eee: cmp eax, 0x887700dc */
	m->edi = M32(m->esp); m->esp += 4;	/* 453ef3: pop edi */
	if (m->zf) goto L_453fc2;	/* 453ef4: je 0x453fc2 */
	{ DWORD a_ = m->eax, b_ = 0x887700f0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453efa: cmp eax, 0x887700f0 */
	if (m->zf) goto L_453fb9;	/* 453eff: je 0x453fb9 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453f05: test eax, eax */
	if (m->zf) goto L_453f12;	/* 453f07: je 0x453f12 */
	m->eax = 0x1f6u;	/* 453f09: mov eax, 0x1f6 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453f0e: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453f11: ret  */
L_453f12:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 453f12: xor edx, edx */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 453f14: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x0u)) = m->edx;	/* 453f18: mov dword ptr [esp], edx */
	M32((DWORD)(m->esp + 0x0u)) = 0x10u;	/* 453f1c: mov dword ptr [esp], 0x10 */
	M32((DWORD)(m->esp + 0x4u)) = m->edx;	/* 453f24: mov dword ptr [esp + 4], edx */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 453f28: mov dword ptr [esp + 8], edx */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 453f2c: mov dword ptr [esp + 8], eax */
	m->eax = M32((DWORD)(0xa0b404u));	/* 453f30: mov eax, dword ptr [0xa0b404] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453f35: push edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453f36: push edx */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 453f37: mov dword ptr [esp + 0x14], edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453f3b: push edx */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 453f3c: mov dword ptr [esp + 0x18], edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 453f40: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453f42: push edx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 453f43: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453f47: push edx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 453f48: lea edx, [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453f4c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453f4d: push eax */
	m->esp -= 4; M32(m->esp) = 0x453f51u; native_call(m, M32((DWORD)(m->ecx + 0x18u)));	/* 453f4e: call dword ptr [ecx + 0x18] */
	{ DWORD a_ = m->eax, b_ = 0x88770078u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453f51: cmp eax, 0x88770078 */
	if (!m->zf && m->sf == m->of) goto L_453f78;	/* 453f56: jg 0x453f78 */
	if (m->zf) goto L_453fb0;	/* 453f58: je 0x453fb0 */
	{ DWORD a_ = m->eax, b_ = 0x80070057u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453f5a: cmp eax, 0x80070057 */
	if (m->zf) goto L_453fb0;	/* 453f5f: je 0x453fb0 */
	{ DWORD a_ = m->eax, b_ = 0x88770028u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453f61: cmp eax, 0x88770028 */
	if (m->zf) goto L_453fb0;	/* 453f66: je 0x453fb0 */
	{ DWORD a_ = m->eax, b_ = 0x8877003cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453f68: cmp eax, 0x8877003c */
	if (m->zf) goto L_453fb0;	/* 453f6d: je 0x453fb0 */
	m->eax = 0x1f4u;	/* 453f6f: mov eax, 0x1f4 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453f74: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453f77: ret  */
L_453f78:
	{ DWORD a_ = m->eax, b_ = 0x887700aau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453f78: cmp eax, 0x887700aa */
	if (m->zf) goto L_453fb0;	/* 453f7d: je 0x453fb0 */
	{ DWORD a_ = m->eax, b_ = 0x88770168u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453f7f: cmp eax, 0x88770168 */
	if (m->zf) goto L_453fb0;	/* 453f84: je 0x453fb0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453f86: test eax, eax */
	if (!m->zf) goto L_453fa7;	/* 453f88: jne 0x453fa7 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 453f8a: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 453f8e: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(0xa0b428u)) = m->eax;	/* 453f92: mov dword ptr [0xa0b428], eax */
	M32((DWORD)(0xa0b424u)) = m->ecx;	/* 453f97: mov dword ptr [0xa0b424], ecx */
	M32((DWORD)(0xa0baf8u)) = 0x0u;	/* 453f9d: mov dword ptr [0xa0baf8], 0 */
L_453fa7:
	m->eax = 0x1f4u;	/* 453fa7: mov eax, 0x1f4 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453fac: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453faf: ret  */
L_453fb0:
	m->eax = 0x1fau;	/* 453fb0: mov eax, 0x1fa */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453fb5: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453fb8: ret  */
L_453fb9:
	m->eax = 0x1f8u;	/* 453fb9: mov eax, 0x1f8 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453fbe: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453fc1: ret  */
L_453fc2:
	m->eax = 0x1f9u;	/* 453fc2: mov eax, 0x1f9 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453fc7: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 453fca: ret  */
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
