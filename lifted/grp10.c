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

static void lift_48b5c0(X86 *m);
static void lift_4876b0(X86 *m);

/* map_loadPlayInfoFrom (0x4876b0), lifted by tools/lift.py */
static void lift_4876b0(X86 *m)
{
	m->eax = 0x10100u;	/* 4876b0: mov eax, 0x10100 */
	m->esp -= 4; M32(m->esp) = 0x4876bau; native_call(m, 0x49fc20u);	/* 4876b5: call 0x49fc20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4876ba: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4876bb: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4876bc: push esi */
	m->esi = m->ecx;	/* 4876bd: mov esi, ecx */
	m->ecx = M32((DWORD)(0xa0e7a8u));	/* 4876bf: mov ecx, dword ptr [0xa0e7a8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4876c5: push edi */
	m->edi = M32((DWORD)(m->esp + 0x10114u));	/* 4876c6: mov edi, dword ptr [esp + 0x10114] */
	m->eax = (DWORD)(m->esi + 0x20fab60u);	/* 4876cd: lea eax, [esi + 0x20fab60] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4876d3: push edi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4876d4: xor ebp, ebp */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 4876d6: mov dword ptr [eax], ecx */
	m->edx = M32((DWORD)(0xa0e7acu));	/* 4876d8: mov edx, dword ptr [0xa0e7ac] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4876de: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(0xa0e7b0u));	/* 4876e1: mov ecx, dword ptr [0xa0e7b0] */
	m->edx = (DWORD)(m->esi + 0x108u);	/* 4876e7: lea edx, [esi + 0x108] */
	M32((DWORD)(m->esi + 0x20fab6cu)) = m->ebp;	/* 4876ed: mov dword ptr [esi + 0x20fab6c], ebp */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 4876f3: mov dword ptr [eax + 8], ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4876f6: push edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 4876f7: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x4c77f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4876fb: push 0x4c77f0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487700: push eax */
	M32((DWORD)(m->esi + 0x20fab70u)) = m->ebp;	/* 487701: mov dword ptr [esi + 0x20fab70], ebp */
	M32((DWORD)(m->esi + 0x20fadf4u)) = m->ebp;	/* 487707: mov dword ptr [esi + 0x20fadf4], ebp */
	M32((DWORD)(m->esi + 0x20fcd38u)) = m->ebp;	/* 48770d: mov dword ptr [esi + 0x20fcd38], ebp */
	M32((DWORD)(m->esi + 0x20fcd3cu)) = 0xffffffffu;	/* 487713: mov dword ptr [esi + 0x20fcd3c], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x487722u; native_call(m, 0x49e9ddu);	/* 48771d: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 487722: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 487726: push 0x4ad170 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48772b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x487731u; native_call(m, 0x49e9cau);	/* 48772c: call 0x49e9ca */
	m->ebx = m->eax;	/* 487731: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487733: add esp, 0x18 */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487736: cmp ebx, ebp */
	if (!m->zf) goto L_487751;	/* 487738: jne 0x487751 */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 48773a: lea edx, [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48773e: push edx */
	{ DWORD v_ = 0x4c7c8cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48773f: push 0x4c7c8c */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487744: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48774eu; native_call(m, 0x46c710u);	/* 487749: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48774e: add esp, 0xc */
L_487751:
	{ DWORD v_ = 0x4c77b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487751: push 0x4c77b4 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487756: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487757: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487758: push esi */
	m->esp -= 4; M32(m->esp) = 0x48775eu; native_call(m, 0x470fc0u);	/* 487759: call 0x470fc0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48775e: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48775f: push 1 */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 487761: lea eax, [esp + 0x34] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487765: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487767: push eax */
	m->esp -= 4; M32(m->esp) = 0x48776du; native_call(m, 0x49e836u);	/* 487768: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 48776d: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487771: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x1201u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487774: cmp eax, 0x1201 */
	if (m->zf) goto L_48778e;	/* 487779: je 0x48778e */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48777b: push edi */
	{ DWORD v_ = 0x4c7768u; m->esp -= 4; M32(m->esp) = v_; }	/* 48777c: push 0x4c7768 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487781: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48778bu; native_call(m, 0x46c710u);	/* 487786: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48778b: add esp, 0xc */
L_48778e:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48778e: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48778f: push 1 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 487791: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487795: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487797: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48779du; native_call(m, 0x46cbe0u);	/* 487798: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 48779d: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4877a1: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4877a3: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4877a4: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4877aau; native_call(m, 0x49e91eu);	/* 4877a5: call 0x49e91e */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4877aa: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4877ab: push 1 */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4877ad: lea eax, [esp + 0x3c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4877b1: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4877b3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4877b9u; native_call(m, 0x46cbe0u);	/* 4877b4: call 0x46cbe0 */
	{ DWORD v_ = 0x4c7c7cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4877b9: push 0x4c7c7c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4877be: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4877bf: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4877c0: push esi */
	m->esp -= 4; M32(m->esp) = 0x4877c6u; native_call(m, 0x470fc0u);	/* 4877c1: call 0x470fc0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4877c6: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4877c7: push 1 */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 4877c9: lea ecx, [esp + 0x54] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4877cd: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4877cf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4877d5u; native_call(m, 0x46cbe0u);	/* 4877d0: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 4877d5: mov eax, dword ptr [esp + 0x5c] */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4877d9: add esp, 0x4c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4877dc: test eax, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 4877de: mov dword ptr [esp + 0x14], ebp */
	if (m->zf || m->sf != m->of) goto L_487b49;	/* 4877e2: jle 0x487b49 */
L_4877e8:
	m->eax = m->ebp;	/* 4877e8: mov eax, ebp */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4877ea: xor edx, edx */
	m->ecx = 0x71cu;	/* 4877ec: mov ecx, 0x71c */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 4877f1: div ecx */
	m->edi = m->edx;	/* 4877f3: mov edi, edx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4877f5: test edi, edi */
	if (!m->zf) goto L_48780d;	/* 4877f7: jne 0x48780d */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4877f9: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4877fa: push ecx */
	m->edx = (DWORD)(m->esp + 0x128u);	/* 4877fb: lea edx, [esp + 0x128] */
	{ DWORD v_ = 0x24u; m->esp -= 4; M32(m->esp) = v_; }	/* 487802: push 0x24 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487804: push edx */
	m->esp -= 4; M32(m->esp) = 0x48780au; native_call(m, 0x46cbe0u);	/* 487805: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48780a: add esp, 0x10 */
L_48780d:
	m->eax = (DWORD)(m->edi + m->edi*8 + 0x0u);	/* 48780d: lea eax, [edi + edi*8] */
	m->edi = (DWORD)(m->esp + m->eax*4 + 0x120u);	/* 487810: lea edi, [esp + eax*4 + 0x120] */
	m->eax = M32((DWORD)(m->esp + m->eax*4 + 0x120u));	/* 487817: mov eax, dword ptr [esp + eax*4 + 0x120] */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48781e: sub eax, 0 */
	if (m->zf) goto L_487b01;	/* 487821: je 0x487b01 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 487827: dec eax */
	if (m->zf) goto L_487a86;	/* 487828: je 0x487a86 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48782e: dec eax */
	if (!m->zf) goto L_487b38;	/* 48782f: jne 0x487b38 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x20fcd38u)), b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487835: cmp dword ptr [esi + 0x20fcd38], 0xc8 */
	if (m->sf != m->of) goto L_487855;	/* 48783f: jl 0x487855 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 487841: push 0x20 */
	{ DWORD v_ = 0x4c7c44u; m->esp -= 4; M32(m->esp) = v_; }	/* 487843: push 0x4c7c44 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487848: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x487852u; native_call(m, 0x46c710u);	/* 48784d: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487852: add esp, 0xc */
L_487855:
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487855: mov eax, dword ptr [esi + 0x20fcd38] */
	m->edx = M32((DWORD)(m->edi + 0x4u));	/* 48785b: mov edx, dword ptr [edi + 4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48785e: lea ecx, [eax + eax*4] */
	M32((DWORD)(m->esi + m->ecx*8 + 0x20fadf8u)) = m->edx;	/* 487861: mov dword ptr [esi + ecx*8 + 0x20fadf8], edx */
	m->eax = M32((DWORD)(m->esi + 0x20f3ac0u));	/* 487868: mov eax, dword ptr [esi + 0x20f3ac0] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48786e: cmp eax, 1 */
	if (!m->zf) goto L_4878c1;	/* 487871: jne 0x4878c1 */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487873: mov eax, dword ptr [esi + 0x20fcd38] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 487879: lea eax, [eax + eax*4] */
	m->ecx = M32((DWORD)(m->esi + m->eax*8 + 0x20fadf8u));	/* 48787c: mov ecx, dword ptr [esi + eax*8 + 0x20fadf8] */
	m->ebp = (DWORD)(m->esi + m->eax*8 + 0x20fadf8u);	/* 487883: lea ebp, [esi + eax*8 + 0x20fadf8] */
	m->eax = 0x66666667u;	/* 48788a: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 48788f: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 487891: sar edx, 2 */
	m->eax = m->edx;	/* 487894: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 487896: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 487899: add edx, eax */
	if (!m->zf) goto L_4878a6;	/* 48789b: jne 0x4878a6 */
	M32((DWORD)(m->ebp + 0x0u)) = 0x0u;	/* 48789d: mov dword ptr [ebp], 0 */
	goto L_4878c1;	/* 4878a4: jmp 0x4878c1 */
L_4878a6:
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4878a6: cmp edx, 1 */
	if (m->zf) goto L_4878ba;	/* 4878a9: je 0x4878ba */
	{ DWORD a_ = m->ecx, b_ = 0x1eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4878ab: cmp ecx, 0x1e */
	if (m->zf) goto L_4878ba;	/* 4878ae: je 0x4878ba */
	{ DWORD a_ = m->ecx, b_ = 0x1fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4878b0: cmp ecx, 0x1f */
	if (m->zf) goto L_4878ba;	/* 4878b3: je 0x4878ba */
	{ DWORD a_ = m->ecx, b_ = 0x25u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4878b5: cmp ecx, 0x25 */
	if (!m->zf) goto L_4878c1;	/* 4878b8: jne 0x4878c1 */
L_4878ba:
	M32((DWORD)(m->ebp + 0x0u)) = 0xffffffffu;	/* 4878ba: mov dword ptr [ebp], 0xffffffff */
L_4878c1:
	m->eax = M32((DWORD)(m->esi + 0x20f3ac4u));	/* 4878c1: mov eax, dword ptr [esi + 0x20f3ac4] */
	m->ebp = 0x1u;	/* 4878c7: mov ebp, 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4878cc: cmp eax, ebp */
	if (!m->zf) goto L_487900;	/* 4878ce: jne 0x487900 */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 4878d0: mov eax, dword ptr [esi + 0x20fcd38] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4878d6: lea ecx, [eax + eax*4] */
	m->eax = 0x66666667u;	/* 4878d9: mov eax, 0x66666667 */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x20fadf8u));	/* 4878de: mov edx, dword ptr [esi + ecx*8 + 0x20fadf8] */
	m->ecx = (DWORD)(m->esi + m->ecx*8 + 0x20fadf8u);	/* 4878e5: lea ecx, [esi + ecx*8 + 0x20fadf8] */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 4878ec: imul edx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4878ee: sar edx, 2 */
	m->eax = m->edx;	/* 4878f1: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4878f3: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4878f6: add edx, eax */
	if (!m->zf) goto L_487900;	/* 4878f8: jne 0x487900 */
	M32((DWORD)(m->ecx + 0x0u)) = 0x2u;	/* 4878fa: mov dword ptr [ecx], 2 */
L_487900:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x20f3ac8u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487900: cmp dword ptr [esi + 0x20f3ac8], ebp */
	if (!m->zf) goto L_487955;	/* 487906: jne 0x487955 */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487908: mov eax, dword ptr [esi + 0x20fcd38] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48790e: lea ecx, [eax + eax*4] */
	m->eax = 0x66666667u;	/* 487911: mov eax, 0x66666667 */
	m->ebp = (DWORD)(m->esi + m->ecx*8 + 0x20fadf8u);	/* 487916: lea ebp, [esi + ecx*8 + 0x20fadf8] */
	m->ecx = M32((DWORD)(m->esi + m->ecx*8 + 0x20fadf8u));	/* 48791d: mov ecx, dword ptr [esi + ecx*8 + 0x20fadf8] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 487924: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 487926: sar edx, 2 */
	m->eax = m->edx;	/* 487929: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48792b: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48792e: add edx, eax */
	if (!m->zf) goto L_48793b;	/* 487930: jne 0x48793b */
	M32((DWORD)(m->ebp + 0x0u)) = 0x3u;	/* 487932: mov dword ptr [ebp], 3 */
	goto L_487955;	/* 487939: jmp 0x487955 */
L_48793b:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48793b: xor edx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48793d: cmp ecx, 0x13 */
	m->edx = (m->edx & ~(0xffu << 0)) | ((((m->zf || m->sf != m->of) ? 1u : 0u) & 0xff) << 0);	/* 487940: setle dl */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 487943: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487945: cmp ecx, 0xf */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 487948: setge al */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48794b: test eax, edx */
	if (m->zf) goto L_487955;	/* 48794d: je 0x487955 */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48794f: add ecx, -5 */
	M32((DWORD)(m->ebp + 0x0u)) = m->ecx;	/* 487952: mov dword ptr [ebp], ecx */
L_487955:
	m->eax = M32((DWORD)(m->esi + 0x20f3accu));	/* 487955: mov eax, dword ptr [esi + 0x20f3acc] */
	m->ebp = 0x1u;	/* 48795b: mov ebp, 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487960: cmp eax, ebp */
	if (!m->zf) goto L_487994;	/* 487962: jne 0x487994 */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487964: mov eax, dword ptr [esi + 0x20fcd38] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48796a: lea ecx, [eax + eax*4] */
	m->eax = 0x66666667u;	/* 48796d: mov eax, 0x66666667 */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x20fadf8u));	/* 487972: mov edx, dword ptr [esi + ecx*8 + 0x20fadf8] */
	m->ecx = (DWORD)(m->esi + m->ecx*8 + 0x20fadf8u);	/* 487979: lea ecx, [esi + ecx*8 + 0x20fadf8] */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 487980: imul edx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 487982: sar edx, 2 */
	m->eax = m->edx;	/* 487985: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 487987: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48798a: add edx, eax */
	if (!m->zf) goto L_487994;	/* 48798c: jne 0x487994 */
	M32((DWORD)(m->ecx + 0x0u)) = 0x5u;	/* 48798e: mov dword ptr [ecx], 5 */
L_487994:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x20f3ad0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487994: cmp dword ptr [esi + 0x20f3ad0], ebp */
	if (!m->zf) goto L_4879cc;	/* 48799a: jne 0x4879cc */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 48799c: mov eax, dword ptr [esi + 0x20fcd38] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4879a2: lea ecx, [eax + eax*4] */
	m->eax = 0x66666667u;	/* 4879a5: mov eax, 0x66666667 */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x20fadf8u));	/* 4879aa: mov edx, dword ptr [esi + ecx*8 + 0x20fadf8] */
	m->ecx = (DWORD)(m->esi + m->ecx*8 + 0x20fadf8u);	/* 4879b1: lea ecx, [esi + ecx*8 + 0x20fadf8] */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 4879b8: imul edx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4879ba: sar edx, 2 */
	m->eax = m->edx;	/* 4879bd: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4879bf: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4879c2: add edx, eax */
	if (!m->zf) goto L_4879cc;	/* 4879c4: jne 0x4879cc */
	M32((DWORD)(m->ecx + 0x0u)) = 0xffffffffu;	/* 4879c6: mov dword ptr [ecx], 0xffffffff */
L_4879cc:
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 4879cc: mov eax, dword ptr [esi + 0x20fcd38] */
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 4879d2: mov edx, dword ptr [edi + 8] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 4879d5: mov ebp, dword ptr [esp + 0x14] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4879d9: lea ecx, [eax + eax*4] */
	M32((DWORD)(m->esi + m->ecx*8 + 0x20fadfcu)) = m->edx;	/* 4879dc: mov dword ptr [esi + ecx*8 + 0x20fadfc], edx */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 4879e3: mov eax, dword ptr [esi + 0x20fcd38] */
	m->ecx = M32((DWORD)(m->edi + 0xcu));	/* 4879e9: mov ecx, dword ptr [edi + 0xc] */
	m->edx = (DWORD)(m->edi + 0x10u);	/* 4879ec: lea edx, [edi + 0x10] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4879ef: lea eax, [eax + eax*4] */
	M32((DWORD)(m->esi + m->eax*8 + 0x20fae00u)) = m->ecx;	/* 4879f2: mov dword ptr [esi + eax*8 + 0x20fae00], ecx */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 4879f9: mov eax, dword ptr [esi + 0x20fcd38] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4879ff: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->esi + m->eax*8 + 0x20fae04u);	/* 487a02: lea ecx, [esi + eax*8 + 0x20fae04] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 487a09: mov eax, dword ptr [edx] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 487a0b: mov dword ptr [ecx], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 487a0d: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 487a10: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 487a13: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 487a16: mov dword ptr [ecx + 8], edx */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487a19: mov eax, dword ptr [esi + 0x20fcd38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x1cu)));	/* 487a1f: fld dword ptr [edi + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 487a22: fmul dword ptr [0x4a9418] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 487a28: lea eax, [eax + eax*4] */
	MF((DWORD)(m->esi + m->eax*8 + 0x20fae10u)) = (float)ST(0); FPOP();	/* 487a2b: fstp dword ptr [esi + eax*8 + 0x20fae10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20u)));	/* 487a32: fld dword ptr [edi + 0x20] */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487a35: mov eax, dword ptr [esi + 0x20fcd38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 487a3b: fmul dword ptr [0x4a9418] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 487a41: lea ecx, [eax + eax*4] */
	MF((DWORD)(m->esi + m->ecx*8 + 0x20fae14u)) = (float)ST(0); FPOP();	/* 487a44: fstp dword ptr [esi + ecx*8 + 0x20fae14] */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487a4b: mov eax, dword ptr [esi + 0x20fcd38] */
	{ DWORD a_ = m->eax, b_ = 0xd3127u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 487a51: add eax, 0xd3127 */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 487a56: lea edx, [eax + eax*4] */
	M32((DWORD)(m->esi + m->edx*8 + 0x0u)) = 0x0u;	/* 487a59: mov dword ptr [esi + edx*8], 0 */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487a60: mov eax, dword ptr [esi + 0x20fcd38] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 487a66: lea eax, [eax + eax*4] */
	M32((DWORD)(m->esi + m->eax*8 + 0x20fae1cu)) = 0x0u;	/* 487a69: mov dword ptr [esi + eax*8 + 0x20fae1c], 0 */
	m->eax = M32((DWORD)(m->esi + 0x20fcd38u));	/* 487a74: mov eax, dword ptr [esi + 0x20fcd38] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 487a7a: inc eax */
	M32((DWORD)(m->esi + 0x20fcd38u)) = m->eax;	/* 487a7b: mov dword ptr [esi + 0x20fcd38], eax */
	goto L_487b38;	/* 487a81: jmp 0x487b38 */
L_487a86:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x20fadf4u)), b_ = 0x20u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487a86: cmp dword ptr [esi + 0x20fadf4], 0x20 */
	if (m->sf != m->of) goto L_487aa3;	/* 487a8d: jl 0x487aa3 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 487a8f: push 0x20 */
	{ DWORD v_ = 0x4c7c00u; m->esp -= 4; M32(m->esp) = v_; }	/* 487a91: push 0x4c7c00 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487a96: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x487aa0u; native_call(m, 0x46c710u);	/* 487a9b: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487aa0: add esp, 0xc */
L_487aa3:
	m->eax = M32((DWORD)(m->esi + 0x20fadf4u));	/* 487aa3: mov eax, dword ptr [esi + 0x20fadf4] */
	m->ecx = (DWORD)(m->edi + 0x10u);	/* 487aa9: lea ecx, [edi + 0x10] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 487aac: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->esi + m->edx*4 + 0x20fab74u);	/* 487aaf: lea eax, [esi + edx*4 + 0x20fab74] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 487ab6: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 487ab8: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 487aba: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 487abd: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 487ac0: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 487ac3: mov dword ptr [eax + 8], ecx */
	m->eax = M32((DWORD)(m->esi + 0x20fadf4u));	/* 487ac6: mov eax, dword ptr [esi + 0x20fadf4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x1cu)));	/* 487acc: fld dword ptr [edi + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 487acf: fmul dword ptr [0x4a9418] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 487ad5: lea edx, [eax + eax*4] */
	MF((DWORD)(m->esi + m->edx*4 + 0x20fab80u)) = (float)ST(0); FPOP();	/* 487ad8: fstp dword ptr [esi + edx*4 + 0x20fab80] */
	m->eax = M32((DWORD)(m->esi + 0x20fadf4u));	/* 487adf: mov eax, dword ptr [esi + 0x20fadf4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20u)));	/* 487ae5: fld dword ptr [edi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 487ae8: fmul dword ptr [0x4a9418] */
	{ DWORD a_ = m->eax, b_ = 0x1a622du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 487aee: add eax, 0x1a622d */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 487af3: lea eax, [eax + eax*4] */
	MF((DWORD)(m->esi + m->eax*4 + 0x0u)) = (float)ST(0); FPOP();	/* 487af6: fstp dword ptr [esi + eax*4] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x20fadf4u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x20fadf4u)) = r_; }	/* 487af9: inc dword ptr [esi + 0x20fadf4] */
	goto L_487b38;	/* 487aff: jmp 0x487b38 */
L_487b01:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x1cu)));	/* 487b01: fld dword ptr [edi + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 487b04: fmul dword ptr [0x4a9418] */
	m->ecx = (DWORD)(m->edi + 0x10u);	/* 487b0a: lea ecx, [edi + 0x10] */
	m->eax = (DWORD)(m->esi + 0x20fab60u);	/* 487b0d: lea eax, [esi + 0x20fab60] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 487b13: mov edx, dword ptr [ecx] */
	MF((DWORD)(m->esi + 0x20fab6cu)) = (float)ST(0); FPOP();	/* 487b15: fstp dword ptr [esi + 0x20fab6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20u)));	/* 487b1b: fld dword ptr [edi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 487b1e: fmul dword ptr [0x4a9418] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 487b24: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 487b26: mov edx, dword ptr [ecx + 4] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 487b29: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 487b2c: mov dword ptr [eax + 4], edx */
	MF((DWORD)(m->esi + 0x20fab70u)) = (float)ST(0); FPOP();	/* 487b2f: fstp dword ptr [esi + 0x20fab70] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 487b35: mov dword ptr [eax + 8], ecx */
L_487b38:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 487b38: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 487b3c: inc ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487b3d: cmp ebp, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 487b3f: mov dword ptr [esp + 0x14], ebp */
	if (m->sf != m->of) goto L_4877e8;	/* 487b43: jl 0x4877e8 */
L_487b49:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 487b49: push ebx */
	m->esp -= 4; M32(m->esp) = 0x487b4fu; native_call(m, 0x49e7e0u);	/* 487b4a: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487b4f: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 487b52: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 487b53: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 487b54: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 487b55: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x10100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487b56: add esp, 0x10100 */
	m->esp += 4 + 4; return;	/* 487b5c: ret 4 */
}

/* map_loadMissionInfoFrom (0x48b5c0), lifted by tools/lift.py */
static void lift_48b5c0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b5c0: sub esp, 0x108 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5c6: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x110u));	/* 48b5c7: mov ebx, dword ptr [esp + 0x110] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5ce: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5cf: push edi */
	m->edi = m->ecx;	/* 48b5d0: mov edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5d2: push ebx */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 48b5d3: lea ecx, [esp + 0x18] */
	m->eax = (DWORD)(m->edi + 0x108u);	/* 48b5d7: lea eax, [edi + 0x108] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5dd: push eax */
	{ DWORD v_ = 0x4c77f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5de: push 0x4c77f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5e3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b5e9u; native_call(m, 0x49e9ddu);	/* 48b5e4: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 48b5e9: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5ed: push 0x4ad170 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5f2: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b5f8u; native_call(m, 0x49e9cau);	/* 48b5f3: call 0x49e9ca */
	m->esi = m->eax;	/* 48b5f8: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b5fa: add esp, 0x18 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b5fd: test esi, esi */
	if (!m->zf) goto L_48b618;	/* 48b5ff: jne 0x48b618 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 48b601: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b605: push eax */
	{ DWORD v_ = 0x4c7decu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b606: push 0x4c7dec */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b60b: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48b615u; native_call(m, 0x46c710u);	/* 48b610: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b615: add esp, 0xc */
L_48b618:
	{ DWORD v_ = 0x4c77b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b618: push 0x4c77b4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b61d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b61f: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b621: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b627u; native_call(m, 0x470fc0u);	/* 48b622: call 0x470fc0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b627: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b628: push 1 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 48b62a: lea ecx, [esp + 0x28] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b62e: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b630: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b636u; native_call(m, 0x49e836u);	/* 48b631: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 48b636: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b63a: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x1201u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b63d: cmp eax, 0x1201 */
	if (m->zf) goto L_48b657;	/* 48b642: je 0x48b657 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b644: push ebx */
	{ DWORD v_ = 0x4c7768u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b645: push 0x4c7768 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b64a: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48b654u; native_call(m, 0x46c710u);	/* 48b64f: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b654: add esp, 0xc */
L_48b657:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b657: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b658: push 1 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 48b65a: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b65e: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b660: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b666u; native_call(m, 0x46cbe0u);	/* 48b661: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 48b666: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b66a: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b66c: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b66d: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b673u; native_call(m, 0x49e91eu);	/* 48b66e: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b673: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b674: push 1 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 48b676: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b67a: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b67c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b682u; native_call(m, 0x46cbe0u);	/* 48b67d: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 48b682: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b686: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b688: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b689: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b68fu; native_call(m, 0x49e91eu);	/* 48b68a: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b68f: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b690: push 1 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 48b692: lea eax, [esp + 0x4c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b696: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b698: push eax */
	m->esp -= 4; M32(m->esp) = 0x48b69eu; native_call(m, 0x46cbe0u);	/* 48b699: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b69e: add esp, 0x48 */
	{ DWORD v_ = 0x4c7ddcu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6a1: push 0x4c7ddc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6a6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6a8: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6aa: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b6b0u; native_call(m, 0x470fc0u);	/* 48b6ab: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6b0: add esp, 0x10 */
	m->ecx = m->edi;	/* 48b6b3: mov ecx, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6b5: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b6bbu; native_call(m, 0x48b460u);	/* 48b6b6: call 0x48b460 */
	{ DWORD v_ = 0x4c7dccu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6bb: push 0x4c7dcc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6c0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6c2: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6c4: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b6cau; native_call(m, 0x470fc0u);	/* 48b6c5: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6ca: add esp, 0x10 */
	m->ecx = m->edi;	/* 48b6cd: mov ecx, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6cf: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b6d5u; native_call(m, 0x48b4a0u);	/* 48b6d0: call 0x48b4a0 */
	{ DWORD v_ = 0x4c7dbcu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6d5: push 0x4c7dbc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6da: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6dc: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6de: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b6e4u; native_call(m, 0x470fc0u);	/* 48b6df: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6e4: add esp, 0x10 */
	m->ecx = m->edi;	/* 48b6e7: mov ecx, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6e9: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b6efu; native_call(m, 0x48b530u);	/* 48b6ea: call 0x48b530 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6ef: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b6f5u; native_call(m, 0x49e7e0u);	/* 48b6f0: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6f5: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48b6f8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48b6f9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48b6fa: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6fb: add esp, 0x108 */
	m->esp += 4 + 4; return;	/* 48b701: ret 4 */
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
