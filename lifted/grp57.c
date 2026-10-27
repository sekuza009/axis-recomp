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

static void lift_48b9d0(X86 *m);

/* map_loadGroundInfoFrom (0x48b9d0), lifted by tools/lift.py */
static void lift_48b9d0(X86 *m)
{
	m->eax = 0x30394u;	/* 48b9d0: mov eax, 0x30394 */
	m->esp -= 4; M32(m->esp) = 0x48b9dau; native_call(m, 0x49fc20u);	/* 48b9d5: call 0x49fc20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9da: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9db: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9dc: push esi */
	m->esi = M32((DWORD)(m->esp + 0x303a4u));	/* 48b9dd: mov esi, dword ptr [esp + 0x303a4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9e4: push edi */
	m->edi = m->ecx;	/* 48b9e5: mov edi, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9e7: push esi */
	m->ecx = (DWORD)(m->esp + 0x2a8u);	/* 48b9e8: lea ecx, [esp + 0x2a8] */
	m->eax = (DWORD)(m->edi + 0x108u);	/* 48b9ef: lea eax, [edi + 0x108] */
	M32((DWORD)(m->esp + 0x40u)) = m->edi;	/* 48b9f5: mov dword ptr [esp + 0x40], edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9f9: push eax */
	{ DWORD v_ = 0x4c77f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9fa: push 0x4c77f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9ff: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48ba05u; native_call(m, 0x49e9ddu);	/* 48ba00: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x2b4u);	/* 48ba05: lea edx, [esp + 0x2b4] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba0c: push 0x4ad170 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba11: push edx */
	m->esp -= 4; M32(m->esp) = 0x48ba17u; native_call(m, 0x49e9cau);	/* 48ba12: call 0x49e9ca */
	m->ebx = m->eax;	/* 48ba17: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ba19: add esp, 0x18 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48ba1c: test ebx, ebx */
	M32((DWORD)(m->esp + 0x38u)) = m->ebx;	/* 48ba1e: mov dword ptr [esp + 0x38], ebx */
	if (!m->zf) goto L_48ba3e;	/* 48ba22: jne 0x48ba3e */
	m->eax = (DWORD)(m->esp + 0x2a4u);	/* 48ba24: lea eax, [esp + 0x2a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba2b: push eax */
	{ DWORD v_ = 0x4c806cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba2c: push 0x4c806c */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba31: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48ba3bu; native_call(m, 0x46c710u);	/* 48ba36: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ba3b: add esp, 0xc */
L_48ba3e:
	{ DWORD v_ = 0x4c77b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba3e: push 0x4c77b4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba43: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba45: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba47: push edi */
	m->esp -= 4; M32(m->esp) = 0x48ba4du; native_call(m, 0x470fc0u);	/* 48ba48: call 0x470fc0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba4d: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba4e: push 1 */
	m->ecx = (DWORD)(m->esp + 0x88u);	/* 48ba50: lea ecx, [esp + 0x88] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba57: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba59: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48ba5fu; native_call(m, 0x49e836u);	/* 48ba5a: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x90u));	/* 48ba5f: mov eax, dword ptr [esp + 0x90] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ba66: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x1201u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ba69: cmp eax, 0x1201 */
	if (m->zf) goto L_48ba83;	/* 48ba6e: je 0x48ba83 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba70: push esi */
	{ DWORD v_ = 0x4c7768u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba71: push 0x4c7768 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba76: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48ba80u; native_call(m, 0x46c710u);	/* 48ba7b: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ba80: add esp, 0xc */
L_48ba83:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba83: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba84: push 1 */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 48ba86: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba8a: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba8c: push edx */
	m->esp -= 4; M32(m->esp) = 0x48ba92u; native_call(m, 0x46cbe0u);	/* 48ba8d: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 48ba92: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba96: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba98: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba99: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48ba9fu; native_call(m, 0x49e91eu);	/* 48ba9a: call 0x49e91e */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ba9f: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48baa0: push 1 */
	m->ecx = (DWORD)(m->esp + 0x40u);	/* 48baa2: lea ecx, [esp + 0x40] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48baa6: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48baa8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48baaeu; native_call(m, 0x46cbe0u);	/* 48baa9: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->esp + 0x48u));	/* 48baae: mov edx, dword ptr [esp + 0x48] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bab2: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bab4: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bab5: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48babbu; native_call(m, 0x49e91eu);	/* 48bab6: call 0x49e91e */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48babb: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48babc: push 1 */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 48babe: lea eax, [esp + 0x5c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bac2: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bac4: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bacau; native_call(m, 0x46cbe0u);	/* 48bac5: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->esp + 0x64u));	/* 48baca: mov ecx, dword ptr [esp + 0x64] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bace: add esp, 0x48 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bad1: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bad3: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bad4: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48badau; native_call(m, 0x49e91eu);	/* 48bad5: call 0x49e91e */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bada: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48badb: push 1 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 48badd: lea edx, [esp + 0x30] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bae1: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bae3: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bae9u; native_call(m, 0x46cbe0u);	/* 48bae4: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 48bae9: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48baed: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48baef: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48baf0: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48baf6u; native_call(m, 0x49e91eu);	/* 48baf1: call 0x49e91e */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48baf6: push ebx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 48baf7: push 0x100 */
	m->ecx = (DWORD)(m->esp + 0x1d4u);	/* 48bafc: lea ecx, [esp + 0x1d4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb03: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb05: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48bb0bu; native_call(m, 0x46cbe0u);	/* 48bb06: call 0x46cbe0 */
	{ DWORD v_ = 0x4c804cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb0b: push 0x4c804c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb10: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb12: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb14: push edi */
	m->esp -= 4; M32(m->esp) = 0x48bb1au; native_call(m, 0x470fc0u);	/* 48bb15: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bb1a: add esp, 0x48 */
	m->edx = (DWORD)(m->edi + 0xa08u);	/* 48bb1d: lea edx, [edi + 0xa08] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb23: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb24: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb26: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb28: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bb2eu; native_call(m, 0x46cbe0u);	/* 48bb29: call 0x46cbe0 */
	{ DWORD v_ = 0x4c8040u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb2e: push 0x4c8040 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb33: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb35: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb37: push edi */
	m->esp -= 4; M32(m->esp) = 0x48bb3du; native_call(m, 0x470fc0u);	/* 48bb38: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bb3d: add esp, 0x20 */
	m->ecx = (DWORD)(m->edi + 0x9ccffcu);	/* 48bb40: lea ecx, [edi + 0x9ccffc] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb46: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48bb4cu; native_call(m, 0x483d70u);	/* 48bb47: call 0x483d70 */
	{ DWORD v_ = 0x4c802cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb4c: push 0x4c802c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb51: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb53: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb55: push edi */
	m->esp -= 4; M32(m->esp) = 0x48bb5bu; native_call(m, 0x470fc0u);	/* 48bb56: call 0x470fc0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb5b: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb5c: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb5e: push 4 */
	m->eax = (DWORD)(m->edi + 0x9ee030u);	/* 48bb60: lea eax, [edi + 0x9ee030] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb66: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bb6cu; native_call(m, 0x46cbe0u);	/* 48bb67: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb6c: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb6d: push 1 */
	m->ecx = (DWORD)(m->edi + 0x9ee034u);	/* 48bb6f: lea ecx, [edi + 0x9ee034] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb75: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb77: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48bb7du; native_call(m, 0x46cbe0u);	/* 48bb78: call 0x46cbe0 */
	{ DWORD v_ = 0x4c801cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb7d: push 0x4c801c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb82: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb84: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb86: push edi */
	m->esp -= 4; M32(m->esp) = 0x48bb8cu; native_call(m, 0x470fc0u);	/* 48bb87: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bb8c: add esp, 0x40 */
	m->edx = (DWORD)(m->edi + 0x9ee044u);	/* 48bb8f: lea edx, [edi + 0x9ee044] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb95: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb96: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb98: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bb9a: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bba0u; native_call(m, 0x46cbe0u);	/* 48bb9b: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bba0: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bba1: push 1 */
	m->eax = (DWORD)(m->edi + 0x9ee048u);	/* 48bba3: lea eax, [edi + 0x9ee048] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bba9: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbab: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bbb1u; native_call(m, 0x46cbe0u);	/* 48bbac: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbb1: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbb2: push 1 */
	m->ecx = (DWORD)(m->edi + 0x9ee058u);	/* 48bbb4: lea ecx, [edi + 0x9ee058] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbba: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbbc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48bbc2u; native_call(m, 0x46cbe0u);	/* 48bbbd: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbc2: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbc3: push 1 */
	m->edx = (DWORD)(m->edi + 0x9ee05cu);	/* 48bbc5: lea edx, [edi + 0x9ee05c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbcb: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbcd: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bbd3u; native_call(m, 0x46cbe0u);	/* 48bbce: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bbd3: add esp, 0x40 */
	m->eax = (DWORD)(m->edi + 0x9ee060u);	/* 48bbd6: lea eax, [edi + 0x9ee060] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbdc: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbdd: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbdf: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbe1: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bbe7u; native_call(m, 0x46cbe0u);	/* 48bbe2: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbe7: push ebx */
	m->esi = (DWORD)(m->edi + 0x9ee064u);	/* 48bbe8: lea esi, [edi + 0x9ee064] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbee: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbf0: push 4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbf2: push esi */
	m->esp -= 4; M32(m->esp) = 0x48bbf8u; native_call(m, 0x46cbe0u);	/* 48bbf3: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbf8: push ebx */
	m->ebp = (DWORD)(m->edi + 0x9eee48u);	/* 48bbf9: lea ebp, [edi + 0x9eee48] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bbff: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc01: push 4 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc03: push ebp */
	m->esp -= 4; M32(m->esp) = 0x48bc09u; native_call(m, 0x46cbe0u);	/* 48bc04: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc09: push ebx */
	m->eax = (DWORD)(m->edi + 0x9ef0b0u);	/* 48bc0a: lea eax, [edi + 0x9ef0b0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc10: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc12: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc14: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bc1au; native_call(m, 0x46cbe0u);	/* 48bc15: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bc1a: add esp, 0x40 */
	m->eax = (DWORD)(m->edi + 0x9ef30cu);	/* 48bc1d: lea eax, [edi + 0x9ef30c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc23: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc24: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc26: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc28: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bc2eu; native_call(m, 0x46cbe0u);	/* 48bc29: call 0x46cbe0 */
	{ DWORD v_ = 0x4c8004u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc2e: push 0x4c8004 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc33: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc35: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc37: push edi */
	m->esp -= 4; M32(m->esp) = 0x48bc3du; native_call(m, 0x470fc0u);	/* 48bc38: call 0x470fc0 */
	m->esi = M32((DWORD)(m->esi + 0x0u));	/* 48bc3d: mov esi, dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bc3f: add esp, 0x20 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 48bc42: dec esi */
	if (m->zf) goto L_48bc8a;	/* 48bc43: je 0x48bc8a */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 48bc45: dec esi */
	if (!m->zf) goto L_48bdc0;	/* 48bc46: jne 0x48bdc0 */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48bc4c: lea ecx, [esp + 0x1a4] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48bc53: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc57: push ecx */
	{ DWORD v_ = 0x4c7ff4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc58: push 0x4c7ff4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc5d: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bc63u; native_call(m, 0x49e9ddu);	/* 48bc5e: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bc63: add esp, 0xc */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48bc66: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bc6c: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc70: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc72: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc74: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc76: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc78: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc7a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc7c: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc7e: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bc84u; native_call(m, 0x456be0u);	/* 48bc7f: call 0x456be0 */
	M32((DWORD)(m->edi + 0x9ee07cu)) = m->eax;	/* 48bc84: mov dword ptr [edi + 0x9ee07c], eax */
L_48bc8a:
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48bc8a: lea ecx, [esp + 0x1a4] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48bc91: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc95: push ecx */
	{ DWORD v_ = 0x4c7fe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc96: push 0x4c7fe0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bc9b: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bca1u; native_call(m, 0x49e9ddu);	/* 48bc9c: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bca1: add esp, 0xc */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48bca4: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bcaa: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcae: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcb0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcb2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcb4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcb6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcb8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcba: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcbc: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bcc2u; native_call(m, 0x456be0u);	/* 48bcbd: call 0x456be0 */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48bcc2: lea ecx, [esp + 0x1a4] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48bcc9: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bccd: push ecx */
	{ DWORD v_ = 0x4c7fd0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcce: push 0x4c7fd0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcd3: push edx */
	M32((DWORD)(m->edi + 0x9ee068u)) = m->eax;	/* 48bcd4: mov dword ptr [edi + 0x9ee068], eax */
	m->esp -= 4; M32(m->esp) = 0x48bcdfu; native_call(m, 0x49e9ddu);	/* 48bcda: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bcdf: add esp, 0xc */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48bce2: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bce8: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcec: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcee: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcf0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcf2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcf4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcf6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcf8: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bcfa: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bd00u; native_call(m, 0x456be0u);	/* 48bcfb: call 0x456be0 */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48bd00: lea ecx, [esp + 0x1a4] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48bd07: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd0b: push ecx */
	{ DWORD v_ = 0x4c7fc0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd0c: push 0x4c7fc0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd11: push edx */
	M32((DWORD)(m->edi + 0x9ee06cu)) = m->eax;	/* 48bd12: mov dword ptr [edi + 0x9ee06c], eax */
	m->esp -= 4; M32(m->esp) = 0x48bd1du; native_call(m, 0x49e9ddu);	/* 48bd18: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bd1d: add esp, 0xc */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48bd20: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bd26: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd2a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd2c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd2e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd30: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd32: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd34: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd36: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd38: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bd3eu; native_call(m, 0x456be0u);	/* 48bd39: call 0x456be0 */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48bd3e: lea ecx, [esp + 0x1a4] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48bd45: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd49: push ecx */
	{ DWORD v_ = 0x4c7fb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd4a: push 0x4c7fb0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd4f: push edx */
	M32((DWORD)(m->edi + 0x9ee070u)) = m->eax;	/* 48bd50: mov dword ptr [edi + 0x9ee070], eax */
	m->esp -= 4; M32(m->esp) = 0x48bd5bu; native_call(m, 0x49e9ddu);	/* 48bd56: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bd5b: add esp, 0xc */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48bd5e: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bd64: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd68: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd6a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd6c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd6e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd70: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd72: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd74: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd76: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bd7cu; native_call(m, 0x456be0u);	/* 48bd77: call 0x456be0 */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48bd7c: lea ecx, [esp + 0x1a4] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48bd83: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd87: push ecx */
	{ DWORD v_ = 0x4c7fa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd88: push 0x4c7fa0 */
	M32((DWORD)(m->edi + 0x9ee074u)) = m->eax;	/* 48bd8d: mov dword ptr [edi + 0x9ee074], eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bd93: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bd99u; native_call(m, 0x49e9ddu);	/* 48bd94: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bd99: add esp, 0xc */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48bd9c: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bda2: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bda6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bda8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdaa: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdac: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdae: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdb0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdb2: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdb4: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bdbau; native_call(m, 0x456be0u);	/* 48bdb5: call 0x456be0 */
	M32((DWORD)(m->edi + 0x9ee078u)) = m->eax;	/* 48bdba: mov dword ptr [edi + 0x9ee078], eax */
L_48bdc0:
	{ DWORD v_ = 0x4c7f8cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdc0: push 0x4c7f8c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdc5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdc7: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdc9: push edi */
	m->esp -= 4; M32(m->esp) = 0x48bdcfu; native_call(m, 0x470fc0u);	/* 48bdca: call 0x470fc0 */
	m->ebp = M32((DWORD)(m->ebp + 0x0u));	/* 48bdcf: mov ebp, dword ptr [ebp] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bdd2: add esp, 0x10 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 48bdd5: dec ebp */
	if (m->zf) goto L_48be19;	/* 48bdd6: je 0x48be19 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 48bdd8: dec ebp */
	if (!m->zf) goto L_48be57;	/* 48bdd9: jne 0x48be57 */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48bddb: lea ecx, [esp + 0x1a4] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48bde2: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bde6: push ecx */
	{ DWORD v_ = 0x4c7f78u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bde7: push 0x4c7f78 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdec: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bdf2u; native_call(m, 0x49e9ddu);	/* 48bded: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bdf2: add esp, 0xc */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48bdf5: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bdfb: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bdff: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be01: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be03: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be05: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be07: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be09: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be0b: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48be0d: push eax */
	m->esp -= 4; M32(m->esp) = 0x48be13u; native_call(m, 0x456be0u);	/* 48be0e: call 0x456be0 */
	M32((DWORD)(m->edi + 0x9eee50u)) = m->eax;	/* 48be13: mov dword ptr [edi + 0x9eee50], eax */
L_48be19:
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48be19: lea ecx, [esp + 0x1a4] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48be20: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48be24: push ecx */
	{ DWORD v_ = 0x4c7f64u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be25: push 0x4c7f64 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48be2a: push edx */
	m->esp -= 4; M32(m->esp) = 0x48be30u; native_call(m, 0x49e9ddu);	/* 48be2b: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48be30: add esp, 0xc */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48be33: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48be39: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be3d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be3f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be41: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be43: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be45: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be47: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be49: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48be4b: push eax */
	m->esp -= 4; M32(m->esp) = 0x48be51u; native_call(m, 0x456be0u);	/* 48be4c: call 0x456be0 */
	M32((DWORD)(m->edi + 0x9eee4cu)) = m->eax;	/* 48be51: mov dword ptr [edi + 0x9eee4c], eax */
L_48be57:
	{ DWORD v_ = 0x4c7f4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48be57: push 0x4c7f4c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be5c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48be5e: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48be60: push edi */
	m->esp -= 4; M32(m->esp) = 0x48be66u; native_call(m, 0x470fc0u);	/* 48be61: call 0x470fc0 */
	m->eax = M32((DWORD)(m->edi + 0x9ef0b0u));	/* 48be66: mov eax, dword ptr [edi + 0x9ef0b0] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48be6c: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48be6f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48bec9;	/* 48be71: jle 0x48bec9 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48be73: cmp eax, 2 */
	if (!m->zf && m->sf == m->of) goto L_48bec9;	/* 48be76: jg 0x48bec9 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48be78: xor eax, eax */
	m->ebp = (DWORD)(m->edi + 0x9ef0b4u);	/* 48be7a: lea ebp, [edi + 0x9ef0b4] */
L_48be80:
	m->esi = (DWORD)(m->eax + 0x1u);	/* 48be80: lea esi, [eax + 1] */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48be83: lea ecx, [esp + 0x1a4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48be8a: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48be8b: push ecx */
	m->edx = (DWORD)(m->esp + 0x7cu);	/* 48be8c: lea edx, [esp + 0x7c] */
	{ DWORD v_ = 0x4c7f3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48be90: push 0x4c7f3c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48be95: push edx */
	m->esp -= 4; M32(m->esp) = 0x48be9bu; native_call(m, 0x49e9ddu);	/* 48be96: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48be9b: add esp, 0x10 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48be9e: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bea4: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bea8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48beaa: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48beac: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48beae: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48beb0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48beb2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48beb4: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48beb6: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bebcu; native_call(m, 0x456be0u);	/* 48beb7: call 0x456be0 */
	M32((DWORD)(m->ebp + 0x0u)) = m->eax;	/* 48bebc: mov dword ptr [ebp], eax */
	m->eax = m->esi;	/* 48bebf: mov eax, esi */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 48bec1: add ebp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48bec4: cmp eax, 6 */
	if (m->sf != m->of) goto L_48be80;	/* 48bec7: jl 0x48be80 */
L_48bec9:
	{ DWORD v_ = 0x4c7f24u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bec9: push 0x4c7f24 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bece: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bed0: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bed2: push edi */
	m->esp -= 4; M32(m->esp) = 0x48bed8u; native_call(m, 0x470fc0u);	/* 48bed3: call 0x470fc0 */
	m->eax = M32((DWORD)(m->edi + 0x9ef30cu));	/* 48bed8: mov eax, dword ptr [edi + 0x9ef30c] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bede: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48bee1: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48bf3b;	/* 48bee3: jle 0x48bf3b */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48bee5: cmp eax, 2 */
	if (!m->zf && m->sf == m->of) goto L_48bf3b;	/* 48bee8: jg 0x48bf3b */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48beea: xor eax, eax */
	m->ebp = (DWORD)(m->edi + 0x9ef310u);	/* 48beec: lea ebp, [edi + 0x9ef310] */
L_48bef2:
	m->esi = (DWORD)(m->eax + 0x1u);	/* 48bef2: lea esi, [eax + 1] */
	m->ecx = (DWORD)(m->esp + 0x1a4u);	/* 48bef5: lea ecx, [esp + 0x1a4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48befc: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48befd: push ecx */
	m->edx = (DWORD)(m->esp + 0x7cu);	/* 48befe: lea edx, [esp + 0x7c] */
	{ DWORD v_ = 0x4c7f14u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf02: push 0x4c7f14 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf07: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bf0du; native_call(m, 0x49e9ddu);	/* 48bf08: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bf0d: add esp, 0x10 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48bf10: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 48bf16: lea eax, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf1a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf1c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf1e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf20: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf22: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf24: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf26: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf28: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bf2eu; native_call(m, 0x456be0u);	/* 48bf29: call 0x456be0 */
	M32((DWORD)(m->ebp + 0x0u)) = m->eax;	/* 48bf2e: mov dword ptr [ebp], eax */
	m->eax = m->esi;	/* 48bf31: mov eax, esi */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 48bf33: add ebp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48bf36: cmp eax, 0x10 */
	if (m->sf != m->of) goto L_48bef2;	/* 48bf39: jl 0x48bef2 */
L_48bf3b:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48bf3b: xor ebp, ebp */
	{ DWORD v_ = 0x4c7f04u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf3d: push 0x4c7f04 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf42: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf43: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf44: push edi */
	m->esp -= 4; M32(m->esp) = 0x48bf4au; native_call(m, 0x470fc0u);	/* 48bf45: call 0x470fc0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf4a: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf4b: push 1 */
	m->ecx = (DWORD)(m->edi + 0x9ef904u);	/* 48bf4d: lea ecx, [edi + 0x9ef904] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf53: push 0xc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf55: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48bf5bu; native_call(m, 0x46cbe0u);	/* 48bf56: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf5b: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf5c: push 1 */
	m->edx = (DWORD)(m->edi + 0x9ef910u);	/* 48bf5e: lea edx, [edi + 0x9ef910] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf64: push 0xc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf66: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bf6cu; native_call(m, 0x46cbe0u);	/* 48bf67: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf6c: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf6d: push 1 */
	m->eax = (DWORD)(m->edi + 0x9ef91cu);	/* 48bf6f: lea eax, [edi + 0x9ef91c] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf75: push 0xc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf77: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bf7du; native_call(m, 0x46cbe0u);	/* 48bf78: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bf7d: add esp, 0x40 */
	m->ecx = (DWORD)(m->edi + 0x9ef928u);	/* 48bf80: lea ecx, [edi + 0x9ef928] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf86: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf87: push 1 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf89: push 0xc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf8b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48bf91u; native_call(m, 0x46cbe0u);	/* 48bf8c: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf91: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf92: push 1 */
	m->edx = (DWORD)(m->edi + 0x9ef934u);	/* 48bf94: lea edx, [edi + 0x9ef934] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf9a: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bf9c: push edx */
	m->esp -= 4; M32(m->esp) = 0x48bfa2u; native_call(m, 0x46cbe0u);	/* 48bf9d: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfa2: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfa3: push 1 */
	m->eax = (DWORD)(m->edi + 0x9ef938u);	/* 48bfa5: lea eax, [edi + 0x9ef938] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfab: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfad: push eax */
	m->esp -= 4; M32(m->esp) = 0x48bfb3u; native_call(m, 0x46cbe0u);	/* 48bfae: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfb3: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfb4: push 1 */
	m->ecx = (DWORD)(m->edi + 0x9ef93cu);	/* 48bfb6: lea ecx, [edi + 0x9ef93c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfbc: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfbe: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48bfc4u; native_call(m, 0x46cbe0u);	/* 48bfbf: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bfc4: add esp, 0x40 */
	m->esi = (DWORD)(m->edi + 0xdc0a74u);	/* 48bfc7: lea esi, [edi + 0xdc0a74] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfcd: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfce: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfd0: push 4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48bfd2: push esi */
	m->esp -= 4; M32(m->esp) = 0x48bfd8u; native_call(m, 0x46cbe0u);	/* 48bfd3: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 48bfd8: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48bfda: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48bfdd: cmp eax, ebp */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->ebp;	/* 48bfdf: mov dword ptr [edi + 0xdc0240], ebp */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 48bfe5: mov dword ptr [esp + 0x24], ebp */
	if (m->zf || m->sf != m->of) goto L_48c802;	/* 48bfe9: jle 0x48c802 */
	m->ebp = (DWORD)(m->edi + 0xdc0264u);	/* 48bfef: lea ebp, [edi + 0xdc0264] */
	M32((DWORD)(m->esp + 0x34u)) = m->ebp;	/* 48bff5: mov dword ptr [esp + 0x34], ebp */
	goto L_48c003;	/* 48bff9: jmp 0x48c003 */
L_48bffb:
	m->ebp = M32((DWORD)(m->esp + 0x34u));	/* 48bffb: mov ebp, dword ptr [esp + 0x34] */
	m->ebx = M32((DWORD)(m->esp + 0x38u));	/* 48bfff: mov ebx, dword ptr [esp + 0x38] */
L_48c003:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 48c003: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c007: push eax */
	{ DWORD v_ = 0x4c7ef4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c008: push 0x4c7ef4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c00d: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c00e: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c010: push edi */
	m->esp -= 4; M32(m->esp) = 0x48c016u; native_call(m, 0x470fc0u);	/* 48c011: call 0x470fc0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c016: push ebx */
	m->esi = (DWORD)(m->ebp + 0xffffffe0u);	/* 48c017: lea esi, [ebp - 0x20] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c01a: push 1 */
	{ DWORD v_ = 0x20cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48c01c: push 0x20c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c021: push esi */
	m->esp -= 4; M32(m->esp) = 0x48c027u; native_call(m, 0x46cbe0u);	/* 48c022: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->esp + 0x48u));	/* 48c027: mov edx, dword ptr [esp + 0x48] */
	m->eax = (DWORD)(m->esp + 0x1c8u);	/* 48c02b: lea eax, [esp + 0x1c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c032: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c033: push eax */
	m->ecx = (DWORD)(m->esp + 0xa0u);	/* 48c034: lea ecx, [esp + 0xa0] */
	{ DWORD v_ = 0x4c7ee4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c03b: push 0x4c7ee4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c040: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48c046u; native_call(m, 0x49e9ddu);	/* 48c041: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c046: add esp, 0x34 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48c049: mov ecx, dword ptr [0xa0e010] */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48c04f: lea edx, [esp + 0x74] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c053: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c055: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c057: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c059: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c05b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c05d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c05f: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c061: push edx */
	m->esp -= 4; M32(m->esp) = 0x48c067u; native_call(m, 0x456be0u);	/* 48c062: call 0x456be0 */
	M32((DWORD)(m->ebp + 0x14u)) = m->eax;	/* 48c067: mov dword ptr [ebp + 0x14], eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c06a: push ebx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c06b: push 0x100 */
	m->eax = (DWORD)(m->esp + 0x3acu);	/* 48c070: lea eax, [esp + 0x3ac] */
	{ DWORD v_ = 0x300u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c077: push 0x300 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c07c: push eax */
	m->esp -= 4; M32(m->esp) = 0x48c082u; native_call(m, 0x46cbe0u);	/* 48c07d: call 0x46cbe0 */
	m->ebx = M32((DWORD)(m->ebp + 0x0u));	/* 48c082: mov ebx, dword ptr [ebp] */
	m->ecx = M32((DWORD)(m->ebp + 0xfffffffcu));	/* 48c085: mov ecx, dword ptr [ebp - 4] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c088: add esp, 0x10 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 48c08b: inc ebx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c08c: inc ecx */
	m->edx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c08d: mov edx, dword ptr [edi + 0xdc0240] */
	{ long long p_ = (long long)(int)m->ebx * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebx = r_; }	/* 48c093: imul ebx, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->ebx;	/* 48c096: mov dword ptr [esp + 0x18], ebx */
	m->eax = (DWORD)(m->edx + m->ebx*1 + 0x0u);	/* 48c09a: lea eax, [edx + ebx] */
	{ DWORD a_ = m->eax, b_ = 0x3d0900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c09d: cmp eax, 0x3d0900 */
	if (m->zf || m->sf != m->of) goto L_48c0bc;	/* 48c0a2: jle 0x48c0bc */
	{ DWORD v_ = 0x3d0900u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c0a4: push 0x3d0900 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c0a9: push eax */
	{ DWORD v_ = 0x4c7eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c0aa: push 0x4c7eb4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c0af: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48c0b9u; native_call(m, 0x46c710u);	/* 48c0b4: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c0b9: add esp, 0x10 */
L_48c0bc:
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c0bc: mov eax, dword ptr [edi + 0xdc0240] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 48c0c2: mov dword ptr [esp + 0x10], 0 */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x9ef940u);	/* 48c0ca: lea ecx, [eax + edi + 0x9ef940] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffffcu));	/* 48c0d1: mov eax, dword ptr [ebp - 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c0d4: test eax, eax */
	M32((DWORD)(m->ebp + 0x18u)) = m->ecx;	/* 48c0d6: mov dword ptr [ebp + 0x18], ecx */
	if (m->sf != m->of) goto L_48c149;	/* 48c0d9: jl 0x48c149 */
	m->edx = (DWORD)(m->esp + 0x3a4u);	/* 48c0db: lea edx, [esp + 0x3a4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 48c0e2: mov dword ptr [esp + 0x14], edx */
L_48c0e6:
	m->eax = M32((DWORD)(m->ebp + 0x0u));	/* 48c0e6: mov eax, dword ptr [ebp] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48c0e9: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c0eb: test eax, eax */
	if (m->sf != m->of) goto L_48c12b;	/* 48c0ed: jl 0x48c12b */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 48c0ef: mov ebx, dword ptr [esp + 0x14] */
L_48c0f3:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x0u))) & 0xff) << 0);	/* 48c0f3: mov dl, byte ptr [ebx] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ebx + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c0f5: cmp dl, byte ptr [ebx + 1] */
	if (!m->zf) goto L_48c10d;	/* 48c0f8: jne 0x48c10d */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ebx + 0x2u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c0fa: cmp dl, byte ptr [ebx + 2] */
	if (!m->zf) goto L_48c10d;	/* 48c0fd: jne 0x48c10d */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c0ff: inc eax */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c100: imul eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + 0x38u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c105: add eax, dword ptr [esi + 0x38] */
	M8((DWORD)(m->eax + m->ecx*1 + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 48c108: mov byte ptr [eax + ecx], dl */
	goto L_48c11c;	/* 48c10b: jmp 0x48c11c */
L_48c10d:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c10d: inc eax */
	m->edx = M32((DWORD)(m->esi + 0x38u));	/* 48c10e: mov edx, dword ptr [esi + 0x38] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c111: imul eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c116: add eax, edx */
	M8((DWORD)(m->eax + m->ecx*1 + 0x0u)) = (BYTE)(0x0u);	/* 48c118: mov byte ptr [eax + ecx], 0 */
L_48c11c:
	m->eax = M32((DWORD)(m->ebp + 0x0u));	/* 48c11c: mov eax, dword ptr [ebp] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c11f: inc ecx */
	{ DWORD a_ = m->ebx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48c120: add ebx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c123: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48c0f3;	/* 48c125: jle 0x48c0f3 */
	m->ebx = M32((DWORD)(m->esp + 0x18u));	/* 48c127: mov ebx, dword ptr [esp + 0x18] */
L_48c12b:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48c12b: mov eax, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48c12f: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->ebp + 0xfffffffcu));	/* 48c133: mov ecx, dword ptr [ebp - 4] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c136: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x300u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48c137: add edx, 0x300 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c13d: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 48c13f: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 48c143: mov dword ptr [esp + 0x14], edx */
	if (m->zf || m->sf != m->of) goto L_48c0e6;	/* 48c147: jle 0x48c0e6 */
L_48c149:
	m->edx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c149: mov edx, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48c14f: add edx, ebx */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->edx;	/* 48c151: mov dword ptr [edi + 0xdc0240], edx */
	m->ebp = M32((DWORD)(m->esi + 0x20u));	/* 48c157: mov ebp, dword ptr [esi + 0x20] */
	{ long long p_ = (long long)(int)m->ebp * (int)M32((DWORD)(m->esi + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebp = r_; }	/* 48c15a: imul ebp, dword ptr [esi + 0x1c] */
	m->eax = m->edx;	/* 48c15e: mov eax, edx */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 48c160: mov dword ptr [esp + 0x18], ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c164: add eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0x3d0900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c166: cmp eax, 0x3d0900 */
	if (m->zf || m->sf != m->of) goto L_48c185;	/* 48c16b: jle 0x48c185 */
	{ DWORD v_ = 0x3d0900u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c16d: push 0x3d0900 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c172: push eax */
	{ DWORD v_ = 0x4c7eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c173: push 0x4c7eb4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c178: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48c182u; native_call(m, 0x46c710u);	/* 48c17d: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c182: add esp, 0x10 */
L_48c185:
	m->ecx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c185: mov ecx, dword ptr [edi + 0xdc0240] */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c18b: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48c18e: xor ebx, ebx */
	m->edx = (DWORD)(m->ecx + m->edi*1 + 0x9ef940u);	/* 48c190: lea edx, [ecx + edi + 0x9ef940] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c197: test eax, eax */
	M32((DWORD)(m->esi + 0x3cu)) = m->edx;	/* 48c199: mov dword ptr [esi + 0x3c], edx */
	if (m->zf || m->sf != m->of) goto L_48c23a;	/* 48c19c: jle 0x48c23a */
	m->ecx = (DWORD)(m->esp + 0x3a4u);	/* 48c1a2: lea ecx, [esp + 0x3a4] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 48c1a9: mov dword ptr [esp + 0x20], ecx */
L_48c1ad:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c1ad: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48c1b0: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c1b2: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48c21c;	/* 48c1b4: jle 0x48c21c */
L_48c1b6:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 48c1b6: mov dl, byte ptr [ecx] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c1b8: cmp dl, byte ptr [ecx + 1] */
	if (!m->zf) goto L_48c207;	/* 48c1bb: jne 0x48c207 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x2u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c1bd: cmp dl, byte ptr [ecx + 2] */
	if (!m->zf) goto L_48c207;	/* 48c1c0: jne 0x48c207 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x300u))) & 0xff) << 0);	/* 48c1c2: mov dl, byte ptr [ecx + 0x300] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x301u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c1c8: cmp dl, byte ptr [ecx + 0x301] */
	if (!m->zf) goto L_48c207;	/* 48c1ce: jne 0x48c207 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x302u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c1d0: cmp dl, byte ptr [ecx + 0x302] */
	if (!m->zf) goto L_48c207;	/* 48c1d6: jne 0x48c207 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x303u))) & 0xff) << 0);	/* 48c1d8: mov dl, byte ptr [ecx + 0x303] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x304u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c1de: cmp dl, byte ptr [ecx + 0x304] */
	if (!m->zf) goto L_48c207;	/* 48c1e4: jne 0x48c207 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x305u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c1e6: cmp dl, byte ptr [ecx + 0x305] */
	if (!m->zf) goto L_48c207;	/* 48c1ec: jne 0x48c207 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x3u))) & 0xff) << 0);	/* 48c1ee: mov dl, byte ptr [ecx + 3] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x4u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c1f1: cmp dl, byte ptr [ecx + 4] */
	if (!m->zf) goto L_48c207;	/* 48c1f4: jne 0x48c207 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x5u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48c1f6: cmp dl, byte ptr [ecx + 5] */
	if (!m->zf) goto L_48c207;	/* 48c1f9: jne 0x48c207 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c1fb: imul eax, ebx */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + 0x3cu)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c1fe: add eax, dword ptr [esi + 0x3c] */
	M8((DWORD)(m->eax + m->ebp*1 + 0x0u)) = (BYTE)(0x1u);	/* 48c201: mov byte ptr [eax + ebp], 1 */
	goto L_48c211;	/* 48c205: jmp 0x48c211 */
L_48c207:
	{ long long p_ = (long long)(int)m->eax * (int)m->ebx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c207: imul eax, ebx */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + 0x3cu)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c20a: add eax, dword ptr [esi + 0x3c] */
	M8((DWORD)(m->eax + m->ebp*1 + 0x0u)) = (BYTE)(0x0u);	/* 48c20d: mov byte ptr [eax + ebp], 0 */
L_48c211:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c211: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 48c214: inc ebp */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48c215: add ecx, 3 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c218: cmp ebp, eax */
	if (m->sf != m->of) goto L_48c1b6;	/* 48c21a: jl 0x48c1b6 */
L_48c21c:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 48c21c: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c220: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 48c223: inc ebx */
	{ DWORD a_ = m->ecx, b_ = 0x300u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48c224: add ecx, 0x300 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c22a: cmp ebx, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 48c22c: mov dword ptr [esp + 0x20], ecx */
	if (m->sf != m->of) goto L_48c1ad;	/* 48c230: jl 0x48c1ad */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 48c236: mov ebp, dword ptr [esp + 0x18] */
L_48c23a:
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c23a: mov eax, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c240: add eax, ebp */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->eax;	/* 48c242: mov dword ptr [edi + 0xdc0240], eax */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c248: mov eax, dword ptr [esi + 0x20] */
	m->ecx = M32((DWORD)(m->esi + 0x1cu));	/* 48c24b: mov ecx, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c24e: inc eax */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c24f: inc ecx */
	m->edx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c250: mov edx, dword ptr [edi + 0xdc0240] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c256: imul eax, ecx */
	m->ebx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c259: lea ebx, [eax + eax*2] */
	{ DWORD a_ = m->ebx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 48c25c: shl ebx, 2 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebx;	/* 48c25f: mov dword ptr [esp + 0x2c], ebx */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x0u);	/* 48c263: lea eax, [ebx + edx] */
	{ DWORD a_ = m->eax, b_ = 0x3d0900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c266: cmp eax, 0x3d0900 */
	if (m->zf || m->sf != m->of) goto L_48c285;	/* 48c26b: jle 0x48c285 */
	{ DWORD v_ = 0x3d0900u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c26d: push 0x3d0900 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c272: push eax */
	{ DWORD v_ = 0x4c7eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c273: push 0x4c7eb4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c278: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48c282u; native_call(m, 0x46c710u);	/* 48c27d: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c282: add esp, 0x10 */
L_48c285:
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c285: mov eax, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48c28b: xor ebp, ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->ebp;	/* 48c28d: mov dword ptr [esp + 0x10], ebp */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x9ef940u);	/* 48c291: lea ecx, [eax + edi + 0x9ef940] */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c298: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c29b: test eax, eax */
	M32((DWORD)(m->esi + 0x40u)) = m->ecx;	/* 48c29d: mov dword ptr [esi + 0x40], ecx */
	if (m->sf != m->of) goto L_48c310;	/* 48c2a0: jl 0x48c310 */
L_48c2a2:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c2a2: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48c2a5: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c2a7: test eax, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 48c2a9: mov dword ptr [esp + 0x14], ecx */
	if (m->sf != m->of) goto L_48c304;	/* 48c2ad: jl 0x48c304 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 48c2af: fild dword ptr [esp + 0x10] */
L_48c2b3:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c2b3: inc eax */
	m->edx = M32((DWORD)(m->esi + 0x38u));	/* 48c2b4: mov edx, dword ptr [esi + 0x38] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c2b7: imul eax, ebp */
	{ long double t = ST(0); FPUSH(t); }	/* 48c2ba: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 48c2bc: fmul dword ptr [esi + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0xcu));	/* 48c2bf: fadd dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c2c2: add eax, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48c2c4: xor ebx, ebx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c2c6: inc ecx */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + m->eax*1 + 0x0u))) & 0xff) << 0);	/* 48c2c7: mov bl, byte ptr [edx + eax] */
	m->edx = M32((DWORD)(m->esi + 0x40u));	/* 48c2ca: mov edx, dword ptr [esi + 0x40] */
	M32((DWORD)(m->esp + 0x28u)) = m->ebx;	/* 48c2cd: mov dword ptr [esp + 0x28], ebx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c2d1: lea eax, [eax + eax*2] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 48c2d4: fild dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48c2d8: lea eax, [edx + eax*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 48c2db: fmul dword ptr [esi + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 48c2de: fadd dword ptr [esi + 8] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 48c2e1: fild dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 48c2e5: mov dword ptr [esp + 0x14], ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 48c2e9: fmul dword ptr [esi + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 48c2ec: fadd dword ptr [esi + 4] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 48c2ef: fstp dword ptr [eax] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 48c2f1: fstp dword ptr [eax + 4] */
	MF((DWORD)(m->eax + 0x8u)) = (float)ST(0); FPOP();	/* 48c2f4: fstp dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c2f7: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c2fa: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48c2b3;	/* 48c2fc: jle 0x48c2b3 */
	m->ebx = M32((DWORD)(m->esp + 0x2cu));	/* 48c2fe: mov ebx, dword ptr [esp + 0x2c] */
	ST(0) = ST(0); FPOP();	/* 48c302: fstp st(0) */
L_48c304:
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c304: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 48c307: inc ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c308: cmp ebp, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ebp;	/* 48c30a: mov dword ptr [esp + 0x10], ebp */
	if (m->zf || m->sf != m->of) goto L_48c2a2;	/* 48c30e: jle 0x48c2a2 */
L_48c310:
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c310: mov eax, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c316: add eax, ebx */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->eax;	/* 48c318: mov dword ptr [edi + 0xdc0240], eax */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c31e: mov eax, dword ptr [esi + 0x20] */
	m->ecx = M32((DWORD)(m->esi + 0x1cu));	/* 48c321: mov ecx, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c324: inc eax */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c325: inc ecx */
	m->edx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c326: mov edx, dword ptr [edi + 0xdc0240] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c32c: imul eax, ecx */
	m->ebx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c32f: lea ebx, [eax + eax*2] */
	{ DWORD a_ = m->ebx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 48c332: shl ebx, 2 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebx;	/* 48c335: mov dword ptr [esp + 0x2c], ebx */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x0u);	/* 48c339: lea eax, [ebx + edx] */
	{ DWORD a_ = m->eax, b_ = 0x3d0900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c33c: cmp eax, 0x3d0900 */
	if (m->zf || m->sf != m->of) goto L_48c35b;	/* 48c341: jle 0x48c35b */
	{ DWORD v_ = 0x3d0900u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c343: push 0x3d0900 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c348: push eax */
	{ DWORD v_ = 0x4c7eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c349: push 0x4c7eb4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c34e: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48c358u; native_call(m, 0x46c710u);	/* 48c353: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c358: add esp, 0x10 */
L_48c35b:
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c35b: mov eax, dword ptr [edi + 0xdc0240] */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x9ef940u);	/* 48c361: lea ecx, [eax + edi + 0x9ef940] */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c368: mov eax, dword ptr [esi + 0x1c] */
	M32((DWORD)(m->esi + 0x44u)) = m->ecx;	/* 48c36b: mov dword ptr [esi + 0x44], ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48c36e: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c370: test eax, eax */
	if (m->sf != m->of) goto L_48c3ce;	/* 48c372: jl 0x48c3ce */
L_48c374:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c374: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c377: inc eax */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c378: imul eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c37b: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 48c37e: mov eax, dword ptr [esi + 0x44] */
	m->edx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 48c381: lea edx, [eax + edx*4] */
	m->eax = M32((DWORD)(0xa0e7d8u));	/* 48c384: mov eax, dword ptr [0xa0e7d8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 48c389: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(0xa0e7dcu));	/* 48c38b: mov eax, dword ptr [0xa0e7dc] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 48c390: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(0xa0e7e0u));	/* 48c393: mov eax, dword ptr [0xa0e7e0] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 48c398: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->esi + 0x20u));	/* 48c39b: mov edx, dword ptr [esi + 0x20] */
	m->eax = (DWORD)(m->edx + 0x1u);	/* 48c39e: lea eax, [edx + 1] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c3a1: imul eax, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c3a4: add eax, edx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c3a6: inc ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c3a7: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 48c3aa: mov eax, dword ptr [esi + 0x44] */
	m->edx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 48c3ad: lea edx, [eax + edx*4] */
	m->eax = M32((DWORD)(0xa0e7d8u));	/* 48c3b0: mov eax, dword ptr [0xa0e7d8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 48c3b5: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(0xa0e7dcu));	/* 48c3b7: mov eax, dword ptr [0xa0e7dc] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 48c3bc: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(0xa0e7e0u));	/* 48c3bf: mov eax, dword ptr [0xa0e7e0] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 48c3c4: mov dword ptr [edx + 8], eax */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c3c7: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c3ca: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48c374;	/* 48c3cc: jle 0x48c374 */
L_48c3ce:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c3ce: mov eax, dword ptr [esi + 0x20] */
	m->ecx = 0x1u;	/* 48c3d1: mov ecx, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c3d6: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_48c43e;	/* 48c3d8: jle 0x48c43e */
	m->edx = 0xcu;	/* 48c3da: mov edx, 0xc */
L_48c3df:
	m->ebp = M32((DWORD)(m->esi + 0x44u));	/* 48c3df: mov ebp, dword ptr [esi + 0x44] */
	m->eax = m->edx;	/* 48c3e2: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c3e4: add eax, ebp */
	m->ebp = M32((DWORD)(0xa0e7d8u));	/* 48c3e6: mov ebp, dword ptr [0xa0e7d8] */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48c3ec: add edx, 0xc */
	M32((DWORD)(m->eax + 0x0u)) = m->ebp;	/* 48c3ef: mov dword ptr [eax], ebp */
	m->ebp = M32((DWORD)(0xa0e7dcu));	/* 48c3f1: mov ebp, dword ptr [0xa0e7dc] */
	M32((DWORD)(m->eax + 0x4u)) = m->ebp;	/* 48c3f7: mov dword ptr [eax + 4], ebp */
	m->ebp = M32((DWORD)(0xa0e7e0u));	/* 48c3fa: mov ebp, dword ptr [0xa0e7e0] */
	M32((DWORD)(m->eax + 0x8u)) = m->ebp;	/* 48c400: mov dword ptr [eax + 8], ebp */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c403: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c406: inc eax */
	m->ebp = M32((DWORD)(m->esi + 0x44u));	/* 48c407: mov ebp, dword ptr [esi + 0x44] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esi + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c40a: imul eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c40e: add eax, ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c410: inc ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c411: lea eax, [eax + eax*2] */
	m->eax = (DWORD)(m->ebp + m->eax*4 + 0x0u);	/* 48c414: lea eax, [ebp + eax*4] */
	m->ebp = M32((DWORD)(0xa0e7d8u));	/* 48c418: mov ebp, dword ptr [0xa0e7d8] */
	M32((DWORD)(m->eax + 0x0u)) = m->ebp;	/* 48c41e: mov dword ptr [eax], ebp */
	m->ebp = M32((DWORD)(0xa0e7dcu));	/* 48c420: mov ebp, dword ptr [0xa0e7dc] */
	M32((DWORD)(m->eax + 0x4u)) = m->ebp;	/* 48c426: mov dword ptr [eax + 4], ebp */
	m->ebp = M32((DWORD)(0xa0e7e0u));	/* 48c429: mov ebp, dword ptr [0xa0e7e0] */
	M32((DWORD)(m->eax + 0x8u)) = m->ebp;	/* 48c42f: mov dword ptr [eax + 8], ebp */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c432: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c435: cmp ecx, eax */
	if (m->sf != m->of) goto L_48c3df;	/* 48c437: jl 0x48c3df */
	m->ecx = 0x1u;	/* 48c439: mov ecx, 1 */
L_48c43e:
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c43e: mov eax, dword ptr [esi + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 48c441: mov dword ptr [esp + 0x10], ecx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c445: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_48c60e;	/* 48c447: jle 0x48c60e */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 48c44d: mov dword ptr [esp + 0x20], 0 */
L_48c455:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c455: mov eax, dword ptr [esi + 0x20] */
	M32((DWORD)(m->esp + 0x14u)) = 0x1u;	/* 48c458: mov dword ptr [esp + 0x14], 1 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c460: cmp eax, 1 */
	if (m->zf || m->sf != m->of) goto L_48c5ef;	/* 48c463: jle 0x48c5ef */
	M32((DWORD)(m->esp + 0x18u)) = 0xcu;	/* 48c469: mov dword ptr [esp + 0x18], 0xc */
L_48c471:
	m->edx = (DWORD)(m->eax + 0x1u);	/* 48c471: lea edx, [eax + 1] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48c474: mov eax, dword ptr [esp + 0x14] */
	m->ecx = m->edx;	/* 48c478: mov ecx, edx */
	m->edi = m->edx;	/* 48c47a: mov edi, edx */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 48c47c: imul ecx, dword ptr [esp + 0x10] */
	{ long long p_ = (long long)(int)m->edi * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 48c481: imul edi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c486: add eax, ecx */
	m->ecx = M32((DWORD)(m->esi + 0x40u));	/* 48c488: mov ecx, dword ptr [esi + 0x40] */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48c48b: add edi, ecx */
	m->ebx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c48d: lea ebx, [eax + eax*2] */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->esp + 0x18u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48c490: add edi, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x3u);	/* 48c494: lea eax, [eax + eax*2 + 3] */
	{ DWORD a_ = m->ebx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 48c498: shl ebx, 2 */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 48c49b: lea eax, [ecx + eax*4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c49e: push edi */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 48c49f: mov dword ptr [esp + 0x2c], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48c4a3: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c4a7: inc eax */
	m->ebp = (DWORD)(m->ebx + m->ecx*1 + 0x0u);	/* 48c4a8: lea ebp, [ebx + ecx] */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c4ab: imul eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 48c4ae: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48c4b2: push ebp */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c4b3: add eax, edx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c4b5: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 48c4b8: lea eax, [ecx + edx*4] */
	m->ecx = (DWORD)(m->esp + 0x188u);	/* 48c4bb: lea ecx, [esp + 0x188] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 48c4c2: mov dword ptr [esp + 0x38], eax */
	m->eax = (DWORD)(m->ebp + 0xfffffff4u);	/* 48c4c6: lea eax, [ebp - 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c4c9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c4ca: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48c4d0u; native_call(m, 0x4679a0u);	/* 48c4cb: call 0x4679a0 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 48c4d0: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x74u)) = m->edx;	/* 48c4d2: mov dword ptr [esp + 0x74], edx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 48c4d6: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 48c4d9: mov dword ptr [esp + 0x78], ecx */
	m->ecx = (DWORD)(m->esp + 0x184u);	/* 48c4dd: lea ecx, [esp + 0x184] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 48c4e4: mov edx, dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 48c4e7: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c4eb: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48c4ec: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c4ed: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c4ee: push ecx */
	M32((DWORD)(m->esp + 0x8cu)) = m->edx;	/* 48c4ef: mov dword ptr [esp + 0x8c], edx */
	m->esp -= 4; M32(m->esp) = 0x48c4fbu; native_call(m, 0x4679a0u);	/* 48c4f6: call 0x4679a0 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 48c4fb: mov edx, dword ptr [eax] */
	m->edi = M32((DWORD)(m->esp + 0x50u));	/* 48c4fd: mov edi, dword ptr [esp + 0x50] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 48c501: mov dword ptr [esp + 0x6c], edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c505: push edi */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 48c506: mov ecx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48c509: push ebp */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 48c50a: mov dword ptr [esp + 0x78], ecx */
	m->ecx = (DWORD)(m->esp + 0x1c0u);	/* 48c50e: lea ecx, [esp + 0x1c0] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 48c515: mov edx, dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 48c518: mov eax, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c51c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c51d: push ecx */
	M32((DWORD)(m->esp + 0x84u)) = m->edx;	/* 48c51e: mov dword ptr [esp + 0x84], edx */
	m->esp -= 4; M32(m->esp) = 0x48c52au; native_call(m, 0x4679a0u);	/* 48c525: call 0x4679a0 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 48c52a: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 48c52c: mov dword ptr [esp + 0x70], edx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 48c530: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 48c533: mov dword ptr [esp + 0x74], ecx */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 48c537: mov edx, dword ptr [eax + 8] */
	m->eax = (DWORD)(m->ebp + 0xfffffff4u);	/* 48c53a: lea eax, [ebp - 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c53d: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48c53e: push ebp */
	m->eax = (DWORD)(m->esp + 0x1c4u);	/* 48c53f: lea eax, [esp + 0x1c4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c546: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c547: push eax */
	M32((DWORD)(m->esp + 0x88u)) = m->edx;	/* 48c548: mov dword ptr [esp + 0x88], edx */
	m->esp -= 4; M32(m->esp) = 0x48c554u; native_call(m, 0x4679a0u);	/* 48c54f: call 0x4679a0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 48c554: mov ecx, dword ptr [eax] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c556: add esp, 0x40 */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 48c559: mov dword ptr [esp + 0x58], ecx */
	m->ecx = M32((DWORD)(m->esi + 0x44u));	/* 48c55d: mov ecx, dword ptr [esi + 0x44] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 48c560: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 48c563: mov dword ptr [esp + 0x5c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 48c567: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 48c56a: mov dword ptr [esp + 0x60], eax */
	m->eax = m->ebx;	/* 48c56e: mov eax, ebx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c570: add eax, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 48c572: fld dword ptr [esp + 0x58] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 48c576: fadd dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 48c57a: fadd dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 48c57e: fadd dword ptr [esp + 0x64] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 48c582: fstp dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 48c584: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 48c588: fadd dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 48c58c: fadd dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x68u));	/* 48c590: fadd dword ptr [esp + 0x68] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 48c594: fstp dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 48c597: fld dword ptr [esp + 0x60] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 48c59b: fadd dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 48c59f: fadd dword ptr [esp + 0x54] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x6cu));	/* 48c5a3: fadd dword ptr [esp + 0x6c] */
	MF((DWORD)(m->eax + 0x8u)) = (float)ST(0); FPOP();	/* 48c5a7: fstp dword ptr [eax + 8] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c5aa: cmp dword ptr [esi], 1 */
	if (!m->zf) goto L_48c5c8;	/* 48c5ad: jne 0x48c5c8 */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->esi + 0x44u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48c5af: add ebx, dword ptr [esi + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 48c5b2: fld dword ptr [ebx] */
	ST(0) = -ST(0);	/* 48c5b4: fchs  */
	MF((DWORD)(m->ebx + 0x0u)) = (float)ST(0); FPOP();	/* 48c5b6: fstp dword ptr [ebx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 48c5b8: fld dword ptr [ebx + 4] */
	ST(0) = -ST(0);	/* 48c5bb: fchs  */
	MF((DWORD)(m->ebx + 0x4u)) = (float)ST(0); FPOP();	/* 48c5bd: fstp dword ptr [ebx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 48c5c0: fld dword ptr [ebx + 8] */
	ST(0) = -ST(0);	/* 48c5c3: fchs  */
	MF((DWORD)(m->ebx + 0x8u)) = (float)ST(0); FPOP();	/* 48c5c5: fstp dword ptr [ebx + 8] */
L_48c5c8:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 48c5c8: mov ecx, dword ptr [esp + 0x14] */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 48c5cc: mov edi, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c5d0: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c5d3: inc ecx */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48c5d4: add edi, 0xc */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c5d7: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 48c5d9: mov dword ptr [esp + 0x14], ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->edi;	/* 48c5dd: mov dword ptr [esp + 0x18], edi */
	if (m->sf != m->of) goto L_48c471;	/* 48c5e1: jl 0x48c471 */
	m->edi = M32((DWORD)(m->esp + 0x3cu));	/* 48c5e7: mov edi, dword ptr [esp + 0x3c] */
	m->ebx = M32((DWORD)(m->esp + 0x2cu));	/* 48c5eb: mov ebx, dword ptr [esp + 0x2c] */
L_48c5ef:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48c5ef: mov eax, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 48c5f3: mov edx, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esi + 0x1cu));	/* 48c5f7: mov ecx, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c5fa: inc eax */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48c5fb: add edx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c5fe: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 48c600: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 48c604: mov dword ptr [esp + 0x20], edx */
	if (m->sf != m->of) goto L_48c455;	/* 48c608: jl 0x48c455 */
L_48c60e:
	m->ebp = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c60e: mov ebp, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 48c614: add ebp, ebx */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->ebp;	/* 48c616: mov dword ptr [edi + 0xdc0240], ebp */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c61c: mov eax, dword ptr [esi + 0x20] */
	m->ecx = M32((DWORD)(m->esi + 0x1cu));	/* 48c61f: mov ecx, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c622: inc eax */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c623: inc ecx */
	m->edx = m->ebp;	/* 48c624: mov edx, ebp */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c626: imul eax, ecx */
	m->ebx = (DWORD)(m->eax*4 + 0x0u);	/* 48c629: lea ebx, [eax*4] */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x0u);	/* 48c630: lea eax, [ebx + edx] */
	{ DWORD a_ = m->eax, b_ = 0x3d0900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c633: cmp eax, 0x3d0900 */
	if (m->zf || m->sf != m->of) goto L_48c652;	/* 48c638: jle 0x48c652 */
	{ DWORD v_ = 0x3d0900u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c63a: push 0x3d0900 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c63f: push eax */
	{ DWORD v_ = 0x4c7eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c640: push 0x4c7eb4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c645: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48c64fu; native_call(m, 0x46c710u);	/* 48c64a: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c64f: add esp, 0x10 */
L_48c652:
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c652: mov eax, dword ptr [edi + 0xdc0240] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48c658: push esi */
	m->ecx = (DWORD)(m->eax + m->edi*1 + 0x9ef940u);	/* 48c659: lea ecx, [eax + edi + 0x9ef940] */
	M32((DWORD)(m->esi + 0x48u)) = m->ecx;	/* 48c660: mov dword ptr [esi + 0x48], ecx */
	m->ecx = m->edi;	/* 48c663: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x48c66au; native_call(m, 0x4728e0u);	/* 48c665: call 0x4728e0 */
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c66a: mov eax, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c670: add eax, ebx */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->eax;	/* 48c672: mov dword ptr [edi + 0xdc0240], eax */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c678: mov eax, dword ptr [esi + 0x20] */
	m->edx = M32((DWORD)(m->esi + 0x1cu));	/* 48c67b: mov edx, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c67e: inc eax */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 48c67f: inc edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c680: imul eax, edx */
	m->ebp = (DWORD)(m->eax*8 + 0x0u);	/* 48c683: lea ebp, [eax*8] */
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c68a: mov eax, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c690: add eax, ebp */
	M32((DWORD)(m->esp + 0x30u)) = m->ebp;	/* 48c692: mov dword ptr [esp + 0x30], ebp */
	{ DWORD a_ = m->eax, b_ = 0x3d0900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c696: cmp eax, 0x3d0900 */
	if (m->zf || m->sf != m->of) goto L_48c6b5;	/* 48c69b: jle 0x48c6b5 */
	{ DWORD v_ = 0x3d0900u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c69d: push 0x3d0900 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c6a2: push eax */
	{ DWORD v_ = 0x4c7eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c6a3: push 0x4c7eb4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c6a8: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48c6b2u; native_call(m, 0x46c710u);	/* 48c6ad: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c6b2: add esp, 0x10 */
L_48c6b5:
	m->ecx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c6b5: mov ecx, dword ptr [edi + 0xdc0240] */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c6bb: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48c6be: xor ebx, ebx */
	m->edx = (DWORD)(m->ecx + m->edi*1 + 0x9ef940u);	/* 48c6c0: lea edx, [ecx + edi + 0x9ef940] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c6c7: test eax, eax */
	M32((DWORD)(m->esi + 0x50u)) = m->edx;	/* 48c6c9: mov dword ptr [esi + 0x50], edx */
	if (m->sf != m->of) goto L_48c713;	/* 48c6cc: jl 0x48c713 */
L_48c6ce:
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c6ce: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48c6d1: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48c6d3: test eax, eax */
	if (m->sf != m->of) goto L_48c707;	/* 48c6d5: jl 0x48c707 */
L_48c6d7:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c6d7: inc eax */
	m->ebp = M32((DWORD)(m->esi + 0x40u));	/* 48c6d8: mov ebp, dword ptr [esi + 0x40] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 48c6db: imul eax, ebx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c6de: add eax, ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48c6e0: inc ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48c6e1: lea edx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*4 + 0x8u)));	/* 48c6e4: fld dword ptr [ebp + edx*4 + 8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x2cu));	/* 48c6e8: fdiv dword ptr [esi + 0x2c] */
	m->edx = (DWORD)(m->ebp + m->edx*4 + 0x0u);	/* 48c6eb: lea edx, [ebp + edx*4] */
	m->ebp = M32((DWORD)(m->esi + 0x50u));	/* 48c6ef: mov ebp, dword ptr [esi + 0x50] */
	m->eax = (DWORD)(m->ebp + m->eax*8 + 0x0u);	/* 48c6f2: lea eax, [ebp + eax*8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 48c6f6: fld dword ptr [edx] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x2cu));	/* 48c6f8: fdiv dword ptr [esi + 0x2c] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 48c6fb: fstp dword ptr [eax] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 48c6fd: fstp dword ptr [eax + 4] */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48c700: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c703: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48c6d7;	/* 48c705: jle 0x48c6d7 */
L_48c707:
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c707: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 48c70a: inc ebx */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c70b: cmp ebx, eax */
	if (m->zf || m->sf != m->of) goto L_48c6ce;	/* 48c70d: jle 0x48c6ce */
	m->ebp = M32((DWORD)(m->esp + 0x30u));	/* 48c70f: mov ebp, dword ptr [esp + 0x30] */
L_48c713:
	m->eax = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c713: mov eax, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c719: add eax, ebp */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->eax;	/* 48c71b: mov dword ptr [edi + 0xdc0240], eax */
	m->ebx = M32((DWORD)(m->esi + 0x20u));	/* 48c721: mov ebx, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->ebx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48c724: add ebx, 0xc8 */
	{ long long p_ = (long long)(int)m->ebx * (int)M32((DWORD)(m->esi + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebx = r_; }	/* 48c72a: imul ebx, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ebx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 48c72e: shl ebx, 1 */
	m->ebp = (DWORD)(m->ebx*4 + 0x0u);	/* 48c730: lea ebp, [ebx*4] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48c737: add eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0x3d0900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c739: cmp eax, 0x3d0900 */
	if (m->zf || m->sf != m->of) goto L_48c758;	/* 48c73e: jle 0x48c758 */
	{ DWORD v_ = 0x3d0900u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c740: push 0x3d0900 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c745: push eax */
	{ DWORD v_ = 0x4c7eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c746: push 0x4c7eb4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c74b: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48c755u; native_call(m, 0x46c710u);	/* 48c750: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c755: add esp, 0x10 */
L_48c758:
	M32((DWORD)(m->esi + 0x54u)) = m->ebx;	/* 48c758: mov dword ptr [esi + 0x54], ebx */
	m->ecx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c75b: mov ecx, dword ptr [edi + 0xdc0240] */
	m->edx = (DWORD)(m->ecx + m->edi*1 + 0x9ef940u);	/* 48c761: lea edx, [ecx + edi + 0x9ef940] */
	M32((DWORD)(m->esi + 0x58u)) = m->edx;	/* 48c768: mov dword ptr [esi + 0x58], edx */
	m->ebx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c76b: mov ebx, dword ptr [edi + 0xdc0240] */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48c771: add ebx, ebp */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->ebx;	/* 48c773: mov dword ptr [edi + 0xdc0240], ebx */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 48c779: mov eax, dword ptr [esi + 0x1c] */
	m->ecx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c77c: mov ecx, dword ptr [edi + 0xdc0240] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48c782: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48c785: lea eax, [eax + eax*4] */
	m->ebp = (DWORD)(m->eax*8 + 0x4u);	/* 48c788: lea ebp, [eax*8 + 4] */
	m->ebx = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 48c78f: lea ebx, [ebp + ebp*2] */
	{ DWORD a_ = m->ebx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 48c793: shl ebx, 2 */
	m->eax = (DWORD)(m->ebx + m->ecx*1 + 0x0u);	/* 48c796: lea eax, [ebx + ecx] */
	{ DWORD a_ = m->eax, b_ = 0x3d0900u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c799: cmp eax, 0x3d0900 */
	if (m->zf || m->sf != m->of) goto L_48c7b8;	/* 48c79e: jle 0x48c7b8 */
	{ DWORD v_ = 0x3d0900u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c7a0: push 0x3d0900 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48c7a5: push eax */
	{ DWORD v_ = 0x4c7eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c7a6: push 0x4c7eb4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48c7ab: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48c7b5u; native_call(m, 0x46c710u);	/* 48c7b0: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c7b5: add esp, 0x10 */
L_48c7b8:
	M32((DWORD)(m->esi + 0x60u)) = m->ebp;	/* 48c7b8: mov dword ptr [esi + 0x60], ebp */
	m->edx = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c7bb: mov edx, dword ptr [edi + 0xdc0240] */
	m->eax = (DWORD)(m->edx + m->edi*1 + 0x9ef940u);	/* 48c7c1: lea eax, [edx + edi + 0x9ef940] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 48c7c8: mov edx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esi + 0x64u)) = m->eax;	/* 48c7cc: mov dword ptr [esi + 0x64], eax */
	m->ebp = M32((DWORD)(m->edi + 0xdc0240u));	/* 48c7cf: mov ebp, dword ptr [edi + 0xdc0240] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 48c7d5: mov eax, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->edi + 0xdc0a74u));	/* 48c7d9: mov ecx, dword ptr [edi + 0xdc0a74] */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 48c7df: add ebp, ebx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48c7e1: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48c7e2: add edx, 0x20c */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48c7e8: cmp eax, ecx */
	M32((DWORD)(m->edi + 0xdc0240u)) = m->ebp;	/* 48c7ea: mov dword ptr [edi + 0xdc0240], ebp */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 48c7f0: mov dword ptr [esp + 0x24], eax */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 48c7f4: mov dword ptr [esp + 0x34], edx */
	if (m->sf != m->of) goto L_48bffb;	/* 48c7f8: jl 0x48bffb */
	m->ebx = M32((DWORD)(m->esp + 0x38u));	/* 48c7fe: mov ebx, dword ptr [esp + 0x38] */
L_48c802:
	m->ecx = m->edi;	/* 48c802: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x48c809u; native_call(m, 0x497a90u);	/* 48c804: call 0x497a90 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48c809: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48c80fu; native_call(m, 0x49e7e0u);	/* 48c80a: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c80f: add esp, 4 */
	m->eax = 0x1u;	/* 48c812: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48c817: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48c818: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48c819: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48c81a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x30394u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48c81b: add esp, 0x30394 */
	m->esp += 4 + 4; return;	/* 48c821: ret 4 */
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
