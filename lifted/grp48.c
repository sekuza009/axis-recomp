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

static void lift_474550(X86 *m);

/* map_loadActorInfoFrom (0x474550), lifted by tools/lift.py */
static void lift_474550(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x1fcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474550: sub esp, 0x1fc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 474556: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x204u));	/* 474557: mov ebx, dword ptr [esp + 0x204] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47455e: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47455f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474560: push edi */
	m->edi = m->ecx;	/* 474561: mov edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 474563: push ebx */
	m->ecx = (DWORD)(m->esp + 0x110u);	/* 474564: lea ecx, [esp + 0x110] */
	m->eax = (DWORD)(m->edi + 0x108u);	/* 47456b: lea eax, [edi + 0x108] */
	M32((DWORD)(m->esp + 0x70u)) = 0x43700000u;	/* 474571: mov dword ptr [esp + 0x70], 0x43700000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474579: push eax */
	{ DWORD v_ = 0x4c77f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47457a: push 0x4c77f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47457f: push ecx */
	M32((DWORD)(m->esp + 0x80u)) = 0x42200000u;	/* 474580: mov dword ptr [esp + 0x80], 0x42200000 */
	M32((DWORD)(m->esp + 0x84u)) = 0x0u;	/* 47458b: mov dword ptr [esp + 0x84], 0 */
	M32((DWORD)(m->esp + 0x88u)) = 0x0u;	/* 474596: mov dword ptr [esp + 0x88], 0 */
	M32((DWORD)(m->esp + 0x8cu)) = 0x42b40000u;	/* 4745a1: mov dword ptr [esp + 0x8c], 0x42b40000 */
	M32((DWORD)(m->esp + 0x90u)) = 0x43660000u;	/* 4745ac: mov dword ptr [esp + 0x90], 0x43660000 */
	M32((DWORD)(m->esp + 0x94u)) = 0x43820000u;	/* 4745b7: mov dword ptr [esp + 0x94], 0x43820000 */
	M32((DWORD)(m->esp + 0x98u)) = 0x42340000u;	/* 4745c2: mov dword ptr [esp + 0x98], 0x42340000 */
	M32((DWORD)(m->esp + 0x9cu)) = 0x42340000u;	/* 4745cd: mov dword ptr [esp + 0x9c], 0x42340000 */
	M32((DWORD)(m->esp + 0xa0u)) = 0x42340000u;	/* 4745d8: mov dword ptr [esp + 0xa0], 0x42340000 */
	M32((DWORD)(m->esp + 0xa4u)) = 0x42c80000u;	/* 4745e3: mov dword ptr [esp + 0xa4], 0x42c80000 */
	M32((DWORD)(m->esp + 0xa8u)) = 0x41200000u;	/* 4745ee: mov dword ptr [esp + 0xa8], 0x41200000 */
	M32((DWORD)(m->esp + 0xacu)) = 0x435c0000u;	/* 4745f9: mov dword ptr [esp + 0xac], 0x435c0000 */
	M32((DWORD)(m->esp + 0xb0u)) = 0x43390000u;	/* 474604: mov dword ptr [esp + 0xb0], 0x43390000 */
	M32((DWORD)(m->esp + 0xb4u)) = 0x435c0000u;	/* 47460f: mov dword ptr [esp + 0xb4], 0x435c0000 */
	M32((DWORD)(m->esp + 0xb8u)) = 0x435c0000u;	/* 47461a: mov dword ptr [esp + 0xb8], 0x435c0000 */
	M32((DWORD)(m->esp + 0xbcu)) = 0x43870000u;	/* 474625: mov dword ptr [esp + 0xbc], 0x43870000 */
	M32((DWORD)(m->esp + 0xc0u)) = 0x43af0000u;	/* 474630: mov dword ptr [esp + 0xc0], 0x43af0000 */
	M32((DWORD)(m->esp + 0xc4u)) = 0x0u;	/* 47463b: mov dword ptr [esp + 0xc4], 0 */
	M32((DWORD)(m->esp + 0xc8u)) = 0x0u;	/* 474646: mov dword ptr [esp + 0xc8], 0 */
	M32((DWORD)(m->esp + 0xccu)) = 0x3f4ccccdu;	/* 474651: mov dword ptr [esp + 0xcc], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0xd0u)) = 0x3f4ccccdu;	/* 47465c: mov dword ptr [esp + 0xd0], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0xd4u)) = 0x3f4ccccdu;	/* 474667: mov dword ptr [esp + 0xd4], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0xd8u)) = 0x3f4ccccdu;	/* 474672: mov dword ptr [esp + 0xd8], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0xdcu)) = 0x3f000000u;	/* 47467d: mov dword ptr [esp + 0xdc], 0x3f000000 */
	M32((DWORD)(m->esp + 0xe0u)) = 0x3f000000u;	/* 474688: mov dword ptr [esp + 0xe0], 0x3f000000 */
	M32((DWORD)(m->esp + 0xe4u)) = 0x3f000000u;	/* 474693: mov dword ptr [esp + 0xe4], 0x3f000000 */
	M32((DWORD)(m->esp + 0xe8u)) = 0x3f000000u;	/* 47469e: mov dword ptr [esp + 0xe8], 0x3f000000 */
	M32((DWORD)(m->esp + 0xecu)) = 0x3f4ccccdu;	/* 4746a9: mov dword ptr [esp + 0xec], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0xf0u)) = 0x3f4ccccdu;	/* 4746b4: mov dword ptr [esp + 0xf0], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0xf4u)) = 0x3f147ae1u;	/* 4746bf: mov dword ptr [esp + 0xf4], 0x3f147ae1 */
	M32((DWORD)(m->esp + 0xf8u)) = 0x3f19999au;	/* 4746ca: mov dword ptr [esp + 0xf8], 0x3f19999a */
	M32((DWORD)(m->esp + 0xfcu)) = 0x3f147ae1u;	/* 4746d5: mov dword ptr [esp + 0xfc], 0x3f147ae1 */
	M32((DWORD)(m->esp + 0x100u)) = 0x3f19999au;	/* 4746e0: mov dword ptr [esp + 0x100], 0x3f19999a */
	M32((DWORD)(m->esp + 0x104u)) = 0x3f07ae15u;	/* 4746eb: mov dword ptr [esp + 0x104], 0x3f07ae15 */
	M32((DWORD)(m->esp + 0x108u)) = 0x3f4ccccdu;	/* 4746f6: mov dword ptr [esp + 0x108], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0x10cu)) = 0x3f4ccccdu;	/* 474701: mov dword ptr [esp + 0x10c], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0x110u)) = 0x3f4ccccdu;	/* 47470c: mov dword ptr [esp + 0x110], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0x114u)) = 0x0u;	/* 474717: mov dword ptr [esp + 0x114], 0 */
	M32((DWORD)(m->esp + 0x118u)) = 0x0u;	/* 474722: mov dword ptr [esp + 0x118], 0 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x3f000000u;	/* 47472d: mov dword ptr [esp + 0x2c], 0x3f000000 */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 474735: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3f000000u;	/* 47473d: mov dword ptr [esp + 0x34], 0x3f000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f000000u;	/* 474745: mov dword ptr [esp + 0x38], 0x3f000000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f000000u;	/* 47474d: mov dword ptr [esp + 0x3c], 0x3f000000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3f000000u;	/* 474755: mov dword ptr [esp + 0x40], 0x3f000000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f4ccccdu;	/* 47475d: mov dword ptr [esp + 0x44], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0x48u)) = 0x3f147ae1u;	/* 474765: mov dword ptr [esp + 0x48], 0x3f147ae1 */
	M32((DWORD)(m->esp + 0x4cu)) = 0x3e99999au;	/* 47476d: mov dword ptr [esp + 0x4c], 0x3e99999a */
	M32((DWORD)(m->esp + 0x50u)) = 0x3e4ccccdu;	/* 474775: mov dword ptr [esp + 0x50], 0x3e4ccccd */
	M32((DWORD)(m->esp + 0x54u)) = 0x3e7fffffu;	/* 47477d: mov dword ptr [esp + 0x54], 0x3e7fffff */
	M32((DWORD)(m->esp + 0x58u)) = 0x3e7fffffu;	/* 474785: mov dword ptr [esp + 0x58], 0x3e7fffff */
	M32((DWORD)(m->esp + 0x5cu)) = 0x3f000000u;	/* 47478d: mov dword ptr [esp + 0x5c], 0x3f000000 */
	M32((DWORD)(m->esp + 0x60u)) = 0x3f19999au;	/* 474795: mov dword ptr [esp + 0x60], 0x3f19999a */
	M32((DWORD)(m->esp + 0x64u)) = 0x3e99999au;	/* 47479d: mov dword ptr [esp + 0x64], 0x3e99999a */
	M32((DWORD)(m->esp + 0x68u)) = 0x3f000000u;	/* 4747a5: mov dword ptr [esp + 0x68], 0x3f000000 */
	M32((DWORD)(m->esp + 0x6cu)) = 0x3f07ae15u;	/* 4747ad: mov dword ptr [esp + 0x6c], 0x3f07ae15 */
	M32((DWORD)(m->esp + 0x70u)) = 0x3f4ccccdu;	/* 4747b5: mov dword ptr [esp + 0x70], 0x3f4ccccd */
	M32((DWORD)(m->esp + 0x74u)) = 0x0u;	/* 4747bd: mov dword ptr [esp + 0x74], 0 */
	M32((DWORD)(m->esp + 0x78u)) = 0x0u;	/* 4747c5: mov dword ptr [esp + 0x78], 0 */
	m->esp -= 4; M32(m->esp) = 0x4747d2u; native_call(m, 0x49e9ddu);	/* 4747cd: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x11cu);	/* 4747d2: lea edx, [esp + 0x11c] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 4747d9: push 0x4ad170 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4747de: push edx */
	m->esp -= 4; M32(m->esp) = 0x4747e4u; native_call(m, 0x49e9cau);	/* 4747df: call 0x49e9ca */
	m->esi = m->eax;	/* 4747e4: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4747e6: add esp, 0x18 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4747e9: test esi, esi */
	if (!m->zf) goto L_474807;	/* 4747eb: jne 0x474807 */
	m->eax = (DWORD)(m->esp + 0x10cu);	/* 4747ed: lea eax, [esp + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4747f4: push eax */
	{ DWORD v_ = 0x4c77c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4747f5: push 0x4c77c4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4747fa: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x474804u; native_call(m, 0x46c710u);	/* 4747ff: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474804: add esp, 0xc */
L_474807:
	{ DWORD v_ = 0x4c77b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 474807: push 0x4c77b4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47480c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47480e: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474810: push edi */
	m->esp -= 4; M32(m->esp) = 0x474816u; native_call(m, 0x470fc0u);	/* 474811: call 0x470fc0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474816: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 474817: push 1 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 474819: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 47481d: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47481f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x474825u; native_call(m, 0x49e836u);	/* 474820: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 474825: mov eax, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474829: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x1201u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47482c: cmp eax, 0x1201 */
	if (m->zf) goto L_474846;	/* 474831: je 0x474846 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 474833: push ebx */
	{ DWORD v_ = 0x4c7768u; m->esp -= 4; M32(m->esp) = v_; }	/* 474834: push 0x4c7768 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 474839: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x474843u; native_call(m, 0x46c710u);	/* 47483e: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474843: add esp, 0xc */
L_474846:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474846: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 474847: push 1 */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 474849: lea edx, [esp + 0x18] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 47484d: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47484f: push edx */
	m->esp -= 4; M32(m->esp) = 0x474855u; native_call(m, 0x46cbe0u);	/* 474850: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 474855: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 474859: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47485b: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47485c: push esi */
	m->esp -= 4; M32(m->esp) = 0x474862u; native_call(m, 0x49e91eu);	/* 47485d: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474862: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 474863: push 1 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 474865: lea ecx, [esp + 0x34] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 474869: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47486b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x474871u; native_call(m, 0x46cbe0u);	/* 47486c: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 474871: mov edx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 474875: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474877: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474878: push esi */
	m->esp -= 4; M32(m->esp) = 0x47487eu; native_call(m, 0x49e91eu);	/* 474879: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47487e: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47487f: push 1 */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 474881: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 474885: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474887: push eax */
	m->esp -= 4; M32(m->esp) = 0x47488du; native_call(m, 0x46cbe0u);	/* 474888: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 47488d: mov ecx, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474891: add esp, 0x48 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 474894: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474896: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474897: push esi */
	m->esp -= 4; M32(m->esp) = 0x47489du; native_call(m, 0x49e91eu);	/* 474898: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47489d: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47489e: push 1 */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 4748a0: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748a4: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4748a6: push edx */
	m->esp -= 4; M32(m->esp) = 0x4748acu; native_call(m, 0x46cbe0u);	/* 4748a7: call 0x46cbe0 */
	{ DWORD v_ = 0x4c774cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4748ac: push 0x4c774c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748b1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748b3: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4748b5: push edi */
	m->esp -= 4; M32(m->esp) = 0x4748bbu; native_call(m, 0x470fc0u);	/* 4748b6: call 0x470fc0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4748bb: push esi */
	m->ebx = (DWORD)(m->edi + 0x1cd6fb0u);	/* 4748bc: lea ebx, [edi + 0x1cd6fb0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748c2: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748c4: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4748c6: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4748ccu; native_call(m, 0x46cbe0u);	/* 4748c7: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 4748cc: mov eax, dword ptr [ebx] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4748ce: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4748cf: push eax */
	m->ecx = (DWORD)(m->edi + 0x1cd6a30u);	/* 4748d0: lea ecx, [edi + 0x1cd6a30] */
	{ DWORD v_ = 0x58u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748d6: push 0x58 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4748d8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4748deu; native_call(m, 0x46cbe0u);	/* 4748d9: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4748de: add esp, 0x4c */
	{ DWORD v_ = 0x4c7734u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748e1: push 0x4c7734 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748e6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748e8: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4748ea: push edi */
	m->esp -= 4; M32(m->esp) = 0x4748f0u; native_call(m, 0x470fc0u);	/* 4748eb: call 0x470fc0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4748f0: push esi */
	m->ebp = (DWORD)(m->edi + 0x1cd93a4u);	/* 4748f1: lea ebp, [edi + 0x1cd93a4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748f7: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4748f9: push 4 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4748fb: push ebp */
	m->esp -= 4; M32(m->esp) = 0x474901u; native_call(m, 0x46cbe0u);	/* 4748fc: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->ebp + 0x0u));	/* 474901: mov edx, dword ptr [ebp] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474904: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474905: push edx */
	m->eax = (DWORD)(m->edi + 0x1cd6fb4u);	/* 474906: lea eax, [edi + 0x1cd6fb4] */
	{ DWORD v_ = 0x5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 47490c: push 0x5c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47490e: push eax */
	m->esp -= 4; M32(m->esp) = 0x474914u; native_call(m, 0x46cbe0u);	/* 47490f: call 0x46cbe0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474914: push esi */
	m->esp -= 4; M32(m->esp) = 0x47491au; native_call(m, 0x49e7e0u);	/* 474915: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47491a: add esp, 0x34 */
	m->ebp = 0x1u;	/* 47491d: mov ebp, 1 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474922: cmp dword ptr [ebx], ebp */
	if (m->zf || m->sf != m->of) goto L_474a71;	/* 474924: jle 0x474a71 */
	M32((DWORD)(m->esp + 0x14u)) = 0x735ab2u;	/* 47492a: mov dword ptr [esp + 0x14], 0x735ab2 */
	m->esi = (DWORD)(m->edi + 0x1cd6ac8u);	/* 474932: lea esi, [edi + 0x1cd6ac8] */
L_474938:
	m->eax = M32((DWORD)(m->esi + 0xffffffc4u));	/* 474938: mov eax, dword ptr [esi - 0x3c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 47493b: dec eax */
	M32((DWORD)(m->esi + 0xffffffc4u)) = m->eax;	/* 47493c: mov dword ptr [esi - 0x3c], eax */
	if (m->sf) goto L_47497c;	/* 47493f: js 0x47497c */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 474941: xor ebx, ebx */
L_474943:
	m->eax = M32((DWORD)(m->esi + 0xffffffc4u));	/* 474943: mov eax, dword ptr [esi - 0x3c] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 474946: shl eax, 3 */
	m->ecx = M32((DWORD)(m->esp + m->eax*1 + 0x20u));	/* 474949: mov ecx, dword ptr [esp + eax + 0x20] */
	m->edx = M32((DWORD)(m->esp + m->eax*1 + 0xc0u));	/* 47494d: mov edx, dword ptr [esp + eax + 0xc0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474954: push ecx */
	m->ecx = M32((DWORD)(m->esp + m->eax*1 + 0x74u));	/* 474955: mov ecx, dword ptr [esp + eax + 0x74] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474959: push edx */
	m->edx = M32((DWORD)(m->esp + m->eax*1 + 0x24u));	/* 47495a: mov edx, dword ptr [esp + eax + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47495e: push ecx */
	m->ecx = M32((DWORD)(m->esp + m->eax*1 + 0xc8u));	/* 47495f: mov ecx, dword ptr [esp + eax + 0xc8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474966: push edx */
	m->edx = M32((DWORD)(m->esp + m->eax*1 + 0x7cu));	/* 474967: mov edx, dword ptr [esp + eax + 0x7c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47496b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47496c: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47496d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47496e: push ebp */
	m->ecx = m->edi;	/* 47496f: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x474976u; native_call(m, 0x474b50u);	/* 474971: call 0x474b50 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 474976: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474977: cmp ebx, 5 */
	if (m->sf != m->of) goto L_474943;	/* 47497a: jl 0x474943 */
L_47497c:
	m->eax = M32((DWORD)(m->edi + 0x20f3ab8u));	/* 47497c: mov eax, dword ptr [edi + 0x20f3ab8] */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474982: add eax, -2 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474985: cmp eax, 9 */
	if (!m->cf && !m->zf) goto L_474a23;	/* 474988: ja 0x474a23 */
	switch (m->eax) { case 0: goto L_474995; case 1: goto L_474995; case 2: goto L_4749b1; case 3: goto L_4749b1; case 4: goto L_4749cd; case 5: goto L_4749cd; case 6: goto L_4749e9; case 7: goto L_4749e9; case 8: goto L_474a05; case 9: goto L_474a05; default: abort(); }	/* 47498e: jmp dword ptr [eax*4 + 0x474b20] */
L_474995:
	m->ecx = (DWORD)(m->esi + 0x4u);	/* 474995: lea ecx, [esi + 4] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 474998: or eax, 0xffffffff */
	M32((DWORD)(m->esi + 0x0u)) = 0x3u;	/* 47499b: mov dword ptr [esi], 3 */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 4749a1: mov dword ptr [ecx], eax */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 4749a3: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 4749a6: mov dword ptr [ecx + 8], eax */
	M32((DWORD)(m->ecx + 0xcu)) = m->eax;	/* 4749a9: mov dword ptr [ecx + 0xc], eax */
	M32((DWORD)(m->ecx + 0x10u)) = m->eax;	/* 4749ac: mov dword ptr [ecx + 0x10], eax */
	goto L_474a23;	/* 4749af: jmp 0x474a23 */
L_4749b1:
	m->eax = (DWORD)(m->esi + 0x4u);	/* 4749b1: lea eax, [esi + 4] */
	{ DWORD a_ = m->edx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4749b4: or edx, 0xffffffff */
	M32((DWORD)(m->esi + 0x0u)) = 0x5u;	/* 4749b7: mov dword ptr [esi], 5 */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 4749bd: mov dword ptr [eax], edx */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4749bf: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 4749c2: mov dword ptr [eax + 8], edx */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 4749c5: mov dword ptr [eax + 0xc], edx */
	M32((DWORD)(m->eax + 0x10u)) = m->edx;	/* 4749c8: mov dword ptr [eax + 0x10], edx */
	goto L_474a23;	/* 4749cb: jmp 0x474a23 */
L_4749cd:
	m->edx = (DWORD)(m->esi + 0x4u);	/* 4749cd: lea edx, [esi + 4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4749d0: or ecx, 0xffffffff */
	M32((DWORD)(m->esi + 0x0u)) = 0x24u;	/* 4749d3: mov dword ptr [esi], 0x24 */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 4749d9: mov dword ptr [edx], ecx */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 4749db: mov dword ptr [edx + 4], ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 4749de: mov dword ptr [edx + 8], ecx */
	M32((DWORD)(m->edx + 0xcu)) = m->ecx;	/* 4749e1: mov dword ptr [edx + 0xc], ecx */
	M32((DWORD)(m->edx + 0x10u)) = m->ecx;	/* 4749e4: mov dword ptr [edx + 0x10], ecx */
	goto L_474a23;	/* 4749e7: jmp 0x474a23 */
L_4749e9:
	m->ecx = (DWORD)(m->esi + 0x4u);	/* 4749e9: lea ecx, [esi + 4] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4749ec: or eax, 0xffffffff */
	M32((DWORD)(m->esi + 0x0u)) = 0x19u;	/* 4749ef: mov dword ptr [esi], 0x19 */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 4749f5: mov dword ptr [ecx], eax */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 4749f7: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 4749fa: mov dword ptr [ecx + 8], eax */
	M32((DWORD)(m->ecx + 0xcu)) = m->eax;	/* 4749fd: mov dword ptr [ecx + 0xc], eax */
	M32((DWORD)(m->ecx + 0x10u)) = m->eax;	/* 474a00: mov dword ptr [ecx + 0x10], eax */
	goto L_474a23;	/* 474a03: jmp 0x474a23 */
L_474a05:
	m->eax = (DWORD)(m->esi + 0x8u);	/* 474a05: lea eax, [esi + 8] */
	M32((DWORD)(m->esi + 0x0u)) = 0x16u;	/* 474a08: mov dword ptr [esi], 0x16 */
	{ DWORD a_ = m->edx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 474a0e: or edx, 0xffffffff */
	M32((DWORD)(m->esi + 0x4u)) = 0x17u;	/* 474a11: mov dword ptr [esi + 4], 0x17 */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 474a18: mov dword ptr [eax], edx */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 474a1a: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 474a1d: mov dword ptr [eax + 8], edx */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 474a20: mov dword ptr [eax + 0xc], edx */
L_474a23:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 474a23: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 474a27: xor eax, eax */
L_474a29:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 474a29: test eax, eax */
	if (m->zf) goto L_474a3c;	/* 474a2b: je 0x474a3c */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474a2d: cmp eax, 4 */
	if (m->zf) goto L_474a3c;	/* 474a30: je 0x474a3c */
	m->edx = (DWORD)(m->ecx + m->eax*1 + 0x0u);	/* 474a32: lea edx, [ecx + eax] */
	M32((DWORD)(m->edi + m->edx*4 + 0x0u)) = 0xffffffffu;	/* 474a35: mov dword ptr [edi + edx*4], 0xffffffff */
L_474a3c:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 474a3c: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474a3d: cmp eax, 6 */
	if (m->sf != m->of) goto L_474a29;	/* 474a40: jl 0x474a29 */
	m->eax = (DWORD)(m->esi + 0xffffffc0u);	/* 474a42: lea eax, [esi - 0x40] */
	m->ecx = m->edi;	/* 474a45: mov ecx, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474a47: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 474a48: push ebp */
	m->esp -= 4; M32(m->esp) = 0x474a4eu; native_call(m, 0x4742f0u);	/* 474a49: call 0x4742f0 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 474a4e: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x1cd6fb0u));	/* 474a52: mov eax, dword ptr [edi + 0x1cd6fb0] */
	m->ebx = (DWORD)(m->edi + 0x1cd6fb0u);	/* 474a58: lea ebx, [edi + 0x1cd6fb0] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 474a5e: inc ebp */
	{ DWORD a_ = m->edx, b_ = 0x16u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 474a5f: add edx, 0x16 */
	{ DWORD a_ = m->esi, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 474a62: add esi, 0x58 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474a65: cmp ebp, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 474a67: mov dword ptr [esp + 0x14], edx */
	if (m->sf != m->of) goto L_474938;	/* 474a6b: jl 0x474938 */
L_474a71:
	m->ecx = M32((DWORD)(m->ebx + 0x0u));	/* 474a71: mov ecx, dword ptr [ebx] */
	m->eax = 0x1u;	/* 474a73: mov eax, 1 */
	M32((DWORD)(m->edi + 0x19e1888u)) = m->ecx;	/* 474a78: mov dword ptr [edi + 0x19e1888], ecx */
	m->ecx = M32((DWORD)(m->edi + 0x1cd93a4u));	/* 474a7e: mov ecx, dword ptr [edi + 0x1cd93a4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474a84: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_474aa2;	/* 474a86: jle 0x474aa2 */
	m->ecx = (DWORD)(m->edi + 0x1cd7028u);	/* 474a88: lea ecx, [edi + 0x1cd7028] */
L_474a8e:
	M32((DWORD)(m->ecx + 0x0u)) = 0x1u;	/* 474a8e: mov dword ptr [ecx], 1 */
	m->edx = M32((DWORD)(m->edi + 0x1cd93a4u));	/* 474a94: mov edx, dword ptr [edi + 0x1cd93a4] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 474a9a: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 474a9b: add ecx, 0x5c */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474a9e: cmp eax, edx */
	if (m->sf != m->of) goto L_474a8e;	/* 474aa0: jl 0x474a8e */
L_474aa2:
	m->edx = (DWORD)(m->edi + 0x908u);	/* 474aa2: lea edx, [edi + 0x908] */
	m->eax = (DWORD)(m->esp + 0x10cu);	/* 474aa8: lea eax, [esp + 0x10c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474aaf: push edx */
	{ DWORD v_ = 0x4c7724u; m->esp -= 4; M32(m->esp) = v_; }	/* 474ab0: push 0x4c7724 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474ab5: push eax */
	m->esp -= 4; M32(m->esp) = 0x474abbu; native_call(m, 0x49e9ddu);	/* 474ab6: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474abb: add esp, 0xc */
	m->ecx = (DWORD)(m->esp + 0x10cu);	/* 474abe: lea ecx, [esp + 0x10c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474ac5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474ac7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474ac9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474acb: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474acd: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474acf: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 474ad1: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474ad3: push ecx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 474ad4: mov ecx, dword ptr [0xa0e010] */
	m->esp -= 4; M32(m->esp) = 0x474adfu; native_call(m, 0x456be0u);	/* 474ada: call 0x456be0 */
	m->edx = (DWORD)(m->edi + 0x1cd6fb0u);	/* 474adf: lea edx, [edi + 0x1cd6fb0] */
	M32((DWORD)(m->edi + 0x2104fe4u)) = m->eax;	/* 474ae5: mov dword ptr [edi + 0x2104fe4], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 474aeb: xor ecx, ecx */
	{ DWORD a_ = M32((DWORD)(m->edx + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474aed: cmp dword ptr [edx], 0 */
	if (m->zf || m->sf != m->of) goto L_474b11;	/* 474af0: jle 0x474b11 */
	m->eax = (DWORD)(m->edi + 0x15a9b36u);	/* 474af2: lea eax, [edi + 0x15a9b36] */
L_474af8:
	M32((DWORD)(m->eax + 0xfffffff8u)) = 0x1u;	/* 474af8: mov dword ptr [eax - 8], 1 */
	M32((DWORD)(m->eax + 0x0u)) = 0x180u;	/* 474aff: mov dword ptr [eax], 0x180 */
	m->esi = M32((DWORD)(m->edx + 0x0u));	/* 474b05: mov esi, dword ptr [edx] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 474b07: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x47fd2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474b08: add eax, 0x47fd2 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474b0d: cmp ecx, esi */
	if (m->sf != m->of) goto L_474af8;	/* 474b0f: jl 0x474af8 */
L_474b11:
	m->edi = M32(m->esp); m->esp += 4;	/* 474b11: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 474b12: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474b13: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474b14: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x1fcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474b15: add esp, 0x1fc */
	m->esp += 4 + 4; return;	/* 474b1b: ret 4 */
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
