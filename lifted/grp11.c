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

static void lift_466120(X86 *m);
static void lift_470ad0(X86 *m);

/* scene_reset (0x470ad0), lifted by tools/lift.py */
static void lift_470ad0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470ad0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 470ad1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 470ad2: push edi */
	m->esi = m->ecx;	/* 470ad3: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x470adau; native_call(m, 0x4723e0u);	/* 470ad5: call 0x4723e0 */
	m->edi = (DWORD)(m->esi + 0x202ea80u);	/* 470ada: lea edi, [esi + 0x202ea80] */
	m->ecx = 0x64u;	/* 470ae0: mov ecx, 0x64 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 470ae5: xor eax, eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 470ae7: xor ebx, ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 470ae9: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->esi;	/* 470aeb: mov ecx, esi */
	M32((DWORD)(m->esi + 0x202ef30u)) = m->ebx;	/* 470aed: mov dword ptr [esi + 0x202ef30], ebx */
	m->esp -= 4; M32(m->esp) = 0x470af8u; native_call(m, 0x490d10u);	/* 470af3: call 0x490d10 */
	m->ecx = m->esi;	/* 470af8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470affu; native_call(m, 0x47cfd0u);	/* 470afa: call 0x47cfd0 */
	m->ecx = m->esi;	/* 470aff: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470b06u; native_call(m, 0x479a60u);	/* 470b01: call 0x479a60 */
	m->ecx = m->esi;	/* 470b06: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470b0du; native_call(m, 0x48fe10u);	/* 470b08: call 0x48fe10 */
	M32((DWORD)(m->esi + 0x20f3970u)) = m->ebx;	/* 470b0d: mov dword ptr [esi + 0x20f3970], ebx */
	M32((DWORD)(m->esi + 0x20f3974u)) = m->ebx;	/* 470b13: mov dword ptr [esi + 0x20f3974], ebx */
	M32((DWORD)(m->esi + 0x20f3978u)) = m->ebx;	/* 470b19: mov dword ptr [esi + 0x20f3978], ebx */
	m->eax = 0x3f800000u;	/* 470b1f: mov eax, 0x3f800000 */
	M32((DWORD)(m->esi + 0x20f397cu)) = m->ebx;	/* 470b24: mov dword ptr [esi + 0x20f397c], ebx */
	M32((DWORD)(m->esi + 0x20f3980u)) = m->ebx;	/* 470b2a: mov dword ptr [esi + 0x20f3980], ebx */
	M32((DWORD)(m->esi + 0x20f3984u)) = 0xbf800000u;	/* 470b30: mov dword ptr [esi + 0x20f3984], 0xbf800000 */
	M32((DWORD)(m->esi + 0x20f3988u)) = m->ebx;	/* 470b3a: mov dword ptr [esi + 0x20f3988], ebx */
	M32((DWORD)(m->esi + 0x20f398cu)) = m->eax;	/* 470b40: mov dword ptr [esi + 0x20f398c], eax */
	M32((DWORD)(m->esi + 0x20f3990u)) = m->ebx;	/* 470b46: mov dword ptr [esi + 0x20f3990], ebx */
	m->edx = M32((DWORD)(m->esi + 0x20f3970u));	/* 470b4c: mov edx, dword ptr [esi + 0x20f3970] */
	m->ecx = (DWORD)(m->esi + 0x20f3994u);	/* 470b52: lea ecx, [esi + 0x20f3994] */
	m->edi = (DWORD)(m->esi + 0x20fce50u);	/* 470b58: lea edi, [esi + 0x20fce50] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 470b5e: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esi + 0x20f3974u));	/* 470b60: mov edx, dword ptr [esi + 0x20f3974] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 470b66: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esi + 0x20f3978u));	/* 470b69: mov edx, dword ptr [esi + 0x20f3978] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 470b6f: mov dword ptr [ecx + 8], edx */
	M32((DWORD)(m->esi + 0x20f39a0u)) = m->eax;	/* 470b72: mov dword ptr [esi + 0x20f39a0], eax */
	M32((DWORD)(m->esi + 0x20f39b0u)) = m->ebx;	/* 470b78: mov dword ptr [esi + 0x20f39b0], ebx */
	M32((DWORD)(m->esi + 0x20f39c0u)) = m->ebx;	/* 470b7e: mov dword ptr [esi + 0x20f39c0], ebx */
	M32((DWORD)(m->esi + 0x20f39d0u)) = m->ebx;	/* 470b84: mov dword ptr [esi + 0x20f39d0], ebx */
	M32((DWORD)(m->esi + 0x20f39a4u)) = m->ebx;	/* 470b8a: mov dword ptr [esi + 0x20f39a4], ebx */
	M32((DWORD)(m->esi + 0x20f39b4u)) = m->eax;	/* 470b90: mov dword ptr [esi + 0x20f39b4], eax */
	M32((DWORD)(m->esi + 0x20f39c4u)) = m->ebx;	/* 470b96: mov dword ptr [esi + 0x20f39c4], ebx */
	M32((DWORD)(m->esi + 0x20f39d4u)) = m->ebx;	/* 470b9c: mov dword ptr [esi + 0x20f39d4], ebx */
	M32((DWORD)(m->esi + 0x20f39a8u)) = m->ebx;	/* 470ba2: mov dword ptr [esi + 0x20f39a8], ebx */
	M32((DWORD)(m->esi + 0x20f39b8u)) = m->ebx;	/* 470ba8: mov dword ptr [esi + 0x20f39b8], ebx */
	M32((DWORD)(m->esi + 0x20f39c8u)) = m->eax;	/* 470bae: mov dword ptr [esi + 0x20f39c8], eax */
	M32((DWORD)(m->esi + 0x20f39d8u)) = m->ebx;	/* 470bb4: mov dword ptr [esi + 0x20f39d8], ebx */
	M32((DWORD)(m->esi + 0x20f39acu)) = m->ebx;	/* 470bba: mov dword ptr [esi + 0x20f39ac], ebx */
	M32((DWORD)(m->esi + 0x20f39bcu)) = m->ebx;	/* 470bc0: mov dword ptr [esi + 0x20f39bc], ebx */
	M32((DWORD)(m->esi + 0x20f39ccu)) = m->ebx;	/* 470bc6: mov dword ptr [esi + 0x20f39cc], ebx */
	M32((DWORD)(m->esi + 0x20f39dcu)) = m->eax;	/* 470bcc: mov dword ptr [esi + 0x20f39dc], eax */
	M32((DWORD)(m->esi + 0x20f39e0u)) = m->eax;	/* 470bd2: mov dword ptr [esi + 0x20f39e0], eax */
	M32((DWORD)(m->esi + 0x20f39f4u)) = m->eax;	/* 470bd8: mov dword ptr [esi + 0x20f39f4], eax */
	M32((DWORD)(m->esi + 0x20f3a08u)) = m->eax;	/* 470bde: mov dword ptr [esi + 0x20f3a08], eax */
	M32((DWORD)(m->esi + 0x20f3a1cu)) = m->eax;	/* 470be4: mov dword ptr [esi + 0x20f3a1c], eax */
	M32((DWORD)(m->esi + 0x20f39f0u)) = m->ebx;	/* 470bea: mov dword ptr [esi + 0x20f39f0], ebx */
	M32((DWORD)(m->esi + 0x20f3a00u)) = m->ebx;	/* 470bf0: mov dword ptr [esi + 0x20f3a00], ebx */
	M32((DWORD)(m->esi + 0x20f3a10u)) = m->ebx;	/* 470bf6: mov dword ptr [esi + 0x20f3a10], ebx */
	M32((DWORD)(m->esi + 0x20f39e4u)) = m->ebx;	/* 470bfc: mov dword ptr [esi + 0x20f39e4], ebx */
	M32((DWORD)(m->esi + 0x20f3a04u)) = m->ebx;	/* 470c02: mov dword ptr [esi + 0x20f3a04], ebx */
	M32((DWORD)(m->esi + 0x20f3a14u)) = m->ebx;	/* 470c08: mov dword ptr [esi + 0x20f3a14], ebx */
	M32((DWORD)(m->esi + 0x20f39e8u)) = m->ebx;	/* 470c0e: mov dword ptr [esi + 0x20f39e8], ebx */
	M32((DWORD)(m->esi + 0x20f39f8u)) = m->ebx;	/* 470c14: mov dword ptr [esi + 0x20f39f8], ebx */
	M32((DWORD)(m->esi + 0x20f3a18u)) = m->ebx;	/* 470c1a: mov dword ptr [esi + 0x20f3a18], ebx */
	M32((DWORD)(m->esi + 0x20f39ecu)) = m->ebx;	/* 470c20: mov dword ptr [esi + 0x20f39ec], ebx */
	M32((DWORD)(m->esi + 0x20f39fcu)) = m->ebx;	/* 470c26: mov dword ptr [esi + 0x20f39fc], ebx */
	M32((DWORD)(m->esi + 0x20f3a0cu)) = m->ebx;	/* 470c2c: mov dword ptr [esi + 0x20f3a0c], ebx */
	m->ecx = 0x64u;	/* 470c32: mov ecx, 0x64 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 470c37: or eax, 0xffffffff */
	M32((DWORD)(m->esi + 0x20f3adcu)) = m->ebx;	/* 470c3a: mov dword ptr [esi + 0x20f3adc], ebx */
	M32((DWORD)(m->esi + 0x20fadf4u)) = m->ebx;	/* 470c40: mov dword ptr [esi + 0x20fadf4], ebx */
	M32((DWORD)(m->esi + 0x20fcd38u)) = m->ebx;	/* 470c46: mov dword ptr [esi + 0x20fcd38], ebx */
	M32((DWORD)(m->esi + 0x20fcd3cu)) = 0xffffffffu;	/* 470c4c: mov dword ptr [esi + 0x20fcd3c], 0xffffffff */
	M32((DWORD)(m->esi + 0x20fcd40u)) = m->ebx;	/* 470c56: mov dword ptr [esi + 0x20fcd40], ebx */
	M32((DWORD)(m->esi + 0x20fcd44u)) = m->ebx;	/* 470c5c: mov dword ptr [esi + 0x20fcd44], ebx */
	M32((DWORD)(m->esi + 0x20fcd48u)) = m->ebx;	/* 470c62: mov dword ptr [esi + 0x20fcd48], ebx */
	M8((DWORD)(m->esi + 0x20fcd4cu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 470c68: mov byte ptr [esi + 0x20fcd4c], bl */
	M32((DWORD)(m->esi + 0x20fce4cu)) = 0xffffffffu;	/* 470c6e: mov dword ptr [esi + 0x20fce4c], 0xffffffff */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 470c78: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->esi;	/* 470c7a: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470c81u; native_call(m, 0x48fc30u);	/* 470c7c: call 0x48fc30 */
	m->ecx = m->esi;	/* 470c81: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470c88u; native_call(m, 0x48fca0u);	/* 470c83: call 0x48fca0 */
	m->ecx = m->esi;	/* 470c88: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470c8fu; native_call(m, 0x471010u);	/* 470c8a: call 0x471010 */
	m->edi = (DWORD)(m->esi + 0x1cd6968u);	/* 470c8f: lea edi, [esi + 0x1cd6968] */
	m->ecx = 0x32u;	/* 470c95: mov ecx, 0x32 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 470c9a: or eax, 0xffffffff */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 470c9d: rep stosd dword ptr es:[edi], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 470c9f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 470ca0: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 470ca1: pop ebx */
	m->esp += 4 + 0; return;	/* 470ca2: ret  */
}

/* shape_read (0x466120), lifted by tools/lift.py */
static void lift_466120(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466120: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466121: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 466122: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466123: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 466124: push edi */
	m->ebx = m->ecx;	/* 466125: mov ebx, ecx */
	m->esp -= 4; M32(m->esp) = 0x46612cu; native_call(m, 0x464bc0u);	/* 466127: call 0x464bc0 */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 46612c: mov ebp, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 466130: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 466131: push 1 */
	{ DWORD v_ = 0x34u; m->esp -= 4; M32(m->esp) = v_; }	/* 466133: push 0x34 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466135: push ebx */
	m->esp -= 4; M32(m->esp) = 0x46613bu; native_call(m, 0x49e836u);	/* 466136: call 0x49e836 */
	m->eax = M32((DWORD)(m->ebx + 0x30u));	/* 46613b: mov eax, dword ptr [ebx + 0x30] */
	m->edi = 0x71110300u;	/* 46613e: mov edi, 0x71110300 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466143: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466146: cmp eax, edi */
	if (m->zf) goto L_466179;	/* 466148: je 0x466179 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46614a: push ebp */
	m->esp -= 4; M32(m->esp) = 0x466150u; native_call(m, 0x49efddu);	/* 46614b: call 0x49efdd */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 466150: push 1 */
	{ DWORD v_ = 0xfffffffcu; m->esp -= 4; M32(m->esp) = v_; }	/* 466152: push -4 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 466154: push ebp */
	m->esi = m->eax;	/* 466155: mov esi, eax */
	m->esp -= 4; M32(m->esp) = 0x46615cu; native_call(m, 0x49e91eu);	/* 466157: call 0x49e91e */
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 46615c: mov eax, dword ptr [ebx + 0x10] */
	m->ecx = M32((DWORD)(m->ebx + 0x4u));	/* 46615f: mov ecx, dword ptr [ebx + 4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 466162: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466164: push esi */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 466165: lea eax, [eax + eax*2] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 466168: push ebp */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 466169: shl eax, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46616c: add ecx, eax */
	M32((DWORD)(m->ebx + 0x4u)) = m->ecx;	/* 46616e: mov dword ptr [ebx + 4], ecx */
	m->esp -= 4; M32(m->esp) = 0x466176u; native_call(m, 0x49e91eu);	/* 466171: call 0x49e91e */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466176: add esp, 0x1c */
L_466179:
	m->esi = M32((DWORD)(m->esp + 0x1cu));	/* 466179: mov esi, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46617d: test esi, esi */
	if (!m->zf) goto L_4661b3;	/* 46617f: jne 0x4661b3 */
	m->ecx = M32((DWORD)(m->ebx + 0x4u));	/* 466181: mov ecx, dword ptr [ebx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466184: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46618au; native_call(m, 0x49f1aau);	/* 466185: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46618a: add esp, 4 */
	M32((DWORD)(m->ebx + 0x8u)) = m->eax;	/* 46618d: mov dword ptr [ebx + 8], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466190: test eax, eax */
	if (!m->zf) goto L_4661aa;	/* 466192: jne 0x4661aa */
	m->edx = M32((DWORD)(m->ebx + 0x4u));	/* 466194: mov edx, dword ptr [ebx + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466197: push edx */
	{ DWORD v_ = 0x4c4becu; m->esp -= 4; M32(m->esp) = v_; }	/* 466198: push 0x4c4bec */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 46619d: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x4661a7u; native_call(m, 0x46c710u);	/* 4661a2: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4661a7: add esp, 0xc */
L_4661aa:
	M32((DWORD)(m->ebx + 0xcu)) = 0x1u;	/* 4661aa: mov dword ptr [ebx + 0xc], 1 */
	goto L_4661dc;	/* 4661b1: jmp 0x4661dc */
L_4661b3:
	m->eax = M32((DWORD)(m->ebx + 0x4u));	/* 4661b3: mov eax, dword ptr [ebx + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4661b6: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4661ba: cmp ecx, eax */
	if (m->sf == m->of) goto L_4661d2;	/* 4661bc: jge 0x4661d2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4661be: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4661bf: push eax */
	{ DWORD v_ = 0x4c4b08u; m->esp -= 4; M32(m->esp) = v_; }	/* 4661c0: push 0x4c4b08 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 4661c5: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x4661cfu; native_call(m, 0x46c710u);	/* 4661ca: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4661cf: add esp, 0x10 */
L_4661d2:
	M32((DWORD)(m->ebx + 0x8u)) = m->esi;	/* 4661d2: mov dword ptr [ebx + 8], esi */
	M32((DWORD)(m->ebx + 0xcu)) = 0x0u;	/* 4661d5: mov dword ptr [ebx + 0xc], 0 */
L_4661dc:
	m->ecx = M32((DWORD)(m->ebx + 0x30u));	/* 4661dc: mov ecx, dword ptr [ebx + 0x30] */
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 4661df: mov eax, dword ptr [ebx + 8] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4661e2: cmp ecx, edi */
	M32((DWORD)(m->ebx + 0x14u)) = m->eax;	/* 4661e4: mov dword ptr [ebx + 0x14], eax */
	if (!m->zf) goto L_4661fe;	/* 4661e7: jne 0x4661fe */
	m->ecx = M32((DWORD)(m->ebx + 0x10u));	/* 4661e9: mov ecx, dword ptr [ebx + 0x10] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4661ec: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4661ed: push ecx */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 4661ee: push 0x80 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4661f3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4661f9u; native_call(m, 0x49e836u);	/* 4661f4: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4661f9: add esp, 0x10 */
	goto L_46622c;	/* 4661fc: jmp 0x46622c */
L_4661fe:
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 4661fe: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 466201: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466203: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46622c;	/* 466205: jle 0x46622c */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 466207: xor esi, esi */
L_466209:
	m->eax = M32((DWORD)(m->ebx + 0x14u));	/* 466209: mov eax, dword ptr [ebx + 0x14] */
	m->edx = m->esi;	/* 46620c: mov edx, esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46620e: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46620f: push 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 466211: add edx, eax */
	{ DWORD v_ = 0x68u; m->esp -= 4; M32(m->esp) = v_; }	/* 466213: push 0x68 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466215: push edx */
	m->esp -= 4; M32(m->esp) = 0x46621bu; native_call(m, 0x49e836u);	/* 466216: call 0x49e836 */
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 46621b: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46621e: add esp, 0x10 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 466221: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 466222: add esi, 0x80 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466228: cmp edi, eax */
	if (m->sf != m->of) goto L_466209;	/* 46622a: jl 0x466209 */
L_46622c:
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 46622c: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46622f: xor ecx, ecx */
	m->edi = m->eax;	/* 466231: mov edi, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 466233: mov dword ptr [esp + 0x10], ecx */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 466237: shl edi, 7 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46623a: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_466361;	/* 46623c: jle 0x466361 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 466242: mov dword ptr [esp + 0x1c], ecx */
L_466246:
	m->esi = M32((DWORD)(m->esp + 0x1cu));	/* 466246: mov esi, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->ebx + 0x14u));	/* 46624a: mov edx, dword ptr [ebx + 0x14] */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46624d: add esi, edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46624f: push ebp */
	M32((DWORD)(m->esi + 0x44u)) = 0xffffffffu;	/* 466250: mov dword ptr [esi + 0x44], 0xffffffff */
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 466257: mov eax, dword ptr [ebx + 8] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46625a: add eax, edi */
	M32((DWORD)(m->esi + 0x50u)) = m->eax;	/* 46625c: mov dword ptr [esi + 0x50], eax */
	m->eax = M32((DWORD)(m->esi + 0x4cu));	/* 46625f: mov eax, dword ptr [esi + 0x4c] */
	m->edx = M32((DWORD)(m->ebx + 0x8u));	/* 466262: mov edx, dword ptr [ebx + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466265: push eax */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 466266: lea ecx, [eax + eax*2] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 466269: push 0xc */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46626b: shl ecx, 2 */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46626e: add edi, ecx */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 466270: add edx, edi */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 466272: add edi, ecx */
	M32((DWORD)(m->esi + 0x54u)) = m->edx;	/* 466274: mov dword ptr [esi + 0x54], edx */
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 466277: mov ecx, dword ptr [ebx + 8] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46627a: add ecx, edi */
	m->edi = (DWORD)(m->edi + m->eax*4 + 0x0u);	/* 46627c: lea edi, [edi + eax*4] */
	M32((DWORD)(m->esi + 0x58u)) = m->ecx;	/* 46627f: mov dword ptr [esi + 0x58], ecx */
	m->edx = M32((DWORD)(m->ebx + 0x8u));	/* 466282: mov edx, dword ptr [ebx + 8] */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 466285: add edx, edi */
	m->edi = (DWORD)(m->edi + m->eax*8 + 0x0u);	/* 466287: lea edi, [edi + eax*8] */
	m->eax = M32((DWORD)(m->esi + 0x50u));	/* 46628a: mov eax, dword ptr [esi + 0x50] */
	M32((DWORD)(m->esi + 0x5cu)) = m->edx;	/* 46628d: mov dword ptr [esi + 0x5c], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466290: push eax */
	m->esp -= 4; M32(m->esp) = 0x466296u; native_call(m, 0x49e836u);	/* 466291: call 0x49e836 */
	m->ecx = M32((DWORD)(m->esi + 0x4cu));	/* 466296: mov ecx, dword ptr [esi + 0x4c] */
	m->edx = M32((DWORD)(m->esi + 0x54u));	/* 466299: mov edx, dword ptr [esi + 0x54] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46629c: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46629d: push ecx */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46629e: push 0xc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4662a0: push edx */
	m->esp -= 4; M32(m->esp) = 0x4662a6u; native_call(m, 0x49e836u);	/* 4662a1: call 0x49e836 */
	m->eax = M32((DWORD)(m->esi + 0x4cu));	/* 4662a6: mov eax, dword ptr [esi + 0x4c] */
	m->ecx = M32((DWORD)(m->esi + 0x58u));	/* 4662a9: mov ecx, dword ptr [esi + 0x58] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4662ac: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4662ad: push eax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4662ae: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4662b0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4662b6u; native_call(m, 0x49e836u);	/* 4662b1: call 0x49e836 */
	m->edx = M32((DWORD)(m->esi + 0x4cu));	/* 4662b6: mov edx, dword ptr [esi + 0x4c] */
	m->eax = M32((DWORD)(m->esi + 0x5cu));	/* 4662b9: mov eax, dword ptr [esi + 0x5c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4662bc: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4662bd: push edx */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4662be: push 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4662c0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4662c6u; native_call(m, 0x49e836u);	/* 4662c1: call 0x49e836 */
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 4662c6: mov ecx, dword ptr [ebx + 8] */
	m->edx = M32((DWORD)(m->esi + 0x60u));	/* 4662c9: mov edx, dword ptr [esi + 0x60] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4662cc: add esp, 0x40 */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4662cf: add ecx, edi */
	m->eax = m->ecx;	/* 4662d1: mov eax, ecx */
	M32((DWORD)(m->esi + 0x64u)) = m->ecx;	/* 4662d3: mov dword ptr [esi + 0x64], ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4662d6: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4662d7: push edx */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4662d8: push 0xc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4662da: push eax */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4662db: add edi, 0xc */
	m->esp -= 4; M32(m->esp) = 0x4662e3u; native_call(m, 0x49e836u);	/* 4662de: call 0x49e836 */
	m->ecx = M32((DWORD)(m->esi + 0x60u));	/* 4662e3: mov ecx, dword ptr [esi + 0x60] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4662e6: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4662e8: add esp, 0x10 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4662eb: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4662ed: mov dword ptr [esp + 0x20], eax */
	if (m->zf || m->sf != m->of) goto L_46633f;	/* 4662f1: jle 0x46633f */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4662f3: mov dword ptr [esp + 0x18], eax */
	goto L_4662fd;	/* 4662f7: jmp 0x4662fd */
L_4662f9:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4662f9: mov eax, dword ptr [esp + 0x18] */
L_4662fd:
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 4662fd: mov ecx, dword ptr [ebx + 8] */
	m->edx = M32((DWORD)(m->esi + 0x64u));	/* 466300: mov edx, dword ptr [esi + 0x64] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 466303: add ecx, edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 466305: push ebp */
	M32((DWORD)(m->edx + m->eax*1 + 0x8u)) = m->ecx;	/* 466306: mov dword ptr [edx + eax + 8], ecx */
	m->ecx = M32((DWORD)(m->esi + 0x64u));	/* 46630a: mov ecx, dword ptr [esi + 0x64] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46630d: add eax, ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 46630f: mov ecx, dword ptr [eax + 4] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 466312: mov edx, dword ptr [eax + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466315: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 466316: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466318: push edx */
	m->edi = (DWORD)(m->edi + m->ecx*4 + 0x0u);	/* 466319: lea edi, [edi + ecx*4] */
	m->esp -= 4; M32(m->esp) = 0x466321u; native_call(m, 0x49e836u);	/* 46631c: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 466321: mov eax, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 466325: mov edx, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esi + 0x60u));	/* 466329: mov ecx, dword ptr [esi + 0x60] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46632c: add esp, 0x10 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46632f: inc eax */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 466330: add edx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466333: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 466335: mov dword ptr [esp + 0x20], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 466339: mov dword ptr [esp + 0x18], edx */
	if (m->sf != m->of) goto L_4662f9;	/* 46633d: jl 0x4662f9 */
L_46633f:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46633f: mov eax, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 466343: mov edx, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->ebx + 0x10u));	/* 466347: mov ecx, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46634a: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46634b: add edx, 0x80 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466351: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 466353: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 466357: mov dword ptr [esp + 0x1c], edx */
	if (m->sf != m->of) goto L_466246;	/* 46635b: jl 0x466246 */
L_466361:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x30u)), b_ = 0x71110300u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466361: cmp dword ptr [ebx + 0x30], 0x71110300 */
	if (m->zf) goto L_466371;	/* 466368: je 0x466371 */
	m->ecx = m->ebx;	/* 46636a: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x466371u; native_call(m, 0x4666d0u);	/* 46636c: call 0x4666d0 */
L_466371:
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 466371: lea eax, [ebx + 0x20] */
	m->edx = (DWORD)(m->ebx + 0x34u);	/* 466374: lea edx, [ebx + 0x34] */
	m->ecx = m->eax;	/* 466377: mov ecx, eax */
	m->esi = m->edx;	/* 466379: mov esi, edx */
	m->edi = M32((DWORD)(m->ecx + 0x0u));	/* 46637b: mov edi, dword ptr [ecx] */
	M32((DWORD)(m->esi + 0x0u)) = m->edi;	/* 46637d: mov dword ptr [esi], edi */
	m->edi = M32((DWORD)(m->ecx + 0x4u));	/* 46637f: mov edi, dword ptr [ecx + 4] */
	M32((DWORD)(m->esi + 0x4u)) = m->edi;	/* 466382: mov dword ptr [esi + 4], edi */
	m->edi = M32((DWORD)(m->eax + 0x0u));	/* 466385: mov edi, dword ptr [eax] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 466387: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esi + 0x8u)) = m->ecx;	/* 46638a: mov dword ptr [esi + 8], ecx */
	m->esi = (DWORD)(m->ebx + 0x40u);	/* 46638d: lea esi, [ebx + 0x40] */
	m->ecx = m->esi;	/* 466390: mov ecx, esi */
	M32((DWORD)(m->ecx + 0x0u)) = m->edi;	/* 466392: mov dword ptr [ecx], edi */
	m->edi = M32((DWORD)(m->eax + 0x4u));	/* 466394: mov edi, dword ptr [eax + 4] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 466397: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 46639a: mov dword ptr [ecx + 4], edi */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 46639d: mov dword ptr [ecx + 8], eax */
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 4663a0: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4663a3: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_466424;	/* 4663a5: jle 0x466424 */
	m->ecx = M32((DWORD)(m->ebx + 0x14u));	/* 4663a7: mov ecx, dword ptr [ebx + 0x14] */
	m->edi = m->eax;	/* 4663aa: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4663ac: add ecx, 0x6c */
L_4663af:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 4663af: fld dword ptr [edx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0xfffffffcu)); FPOP();	/* 4663b1: fcomp dword ptr [ecx - 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4663b4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4663b6: test ah, 0x41 */
	if (!m->zf) goto L_4663c0;	/* 4663b9: jne 0x4663c0 */
	m->eax = M32((DWORD)(m->ecx + 0xfffffffcu));	/* 4663bb: mov eax, dword ptr [ecx - 4] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 4663be: mov dword ptr [edx], eax */
L_4663c0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x38u)));	/* 4663c0: fld dword ptr [ebx + 0x38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x0u)); FPOP();	/* 4663c3: fcomp dword ptr [ecx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4663c5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4663c7: test ah, 0x41 */
	if (!m->zf) goto L_4663d1;	/* 4663ca: jne 0x4663d1 */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 4663cc: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->ebx + 0x38u)) = m->eax;	/* 4663ce: mov dword ptr [ebx + 0x38], eax */
L_4663d1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x3cu)));	/* 4663d1: fld dword ptr [ebx + 0x3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x4u)); FPOP();	/* 4663d4: fcomp dword ptr [ecx + 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4663d7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4663d9: test ah, 0x41 */
	if (!m->zf) goto L_4663e4;	/* 4663dc: jne 0x4663e4 */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 4663de: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->ebx + 0x3cu)) = m->eax;	/* 4663e1: mov dword ptr [ebx + 0x3c], eax */
L_4663e4:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 4663e4: fld dword ptr [esi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x8u)); FPOP();	/* 4663e6: fcomp dword ptr [ecx + 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4663e9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4663eb: test ah, 1 */
	if (m->zf) goto L_4663f5;	/* 4663ee: je 0x4663f5 */
	m->eax = M32((DWORD)(m->ecx + 0x8u));	/* 4663f0: mov eax, dword ptr [ecx + 8] */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 4663f3: mov dword ptr [esi], eax */
L_4663f5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x44u)));	/* 4663f5: fld dword ptr [ebx + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0xcu)); FPOP();	/* 4663f8: fcomp dword ptr [ecx + 0xc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4663fb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4663fd: test ah, 1 */
	if (m->zf) goto L_466408;	/* 466400: je 0x466408 */
	m->eax = M32((DWORD)(m->ecx + 0xcu));	/* 466402: mov eax, dword ptr [ecx + 0xc] */
	M32((DWORD)(m->ebx + 0x44u)) = m->eax;	/* 466405: mov dword ptr [ebx + 0x44], eax */
L_466408:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x48u)));	/* 466408: fld dword ptr [ebx + 0x48] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x10u)); FPOP();	/* 46640b: fcomp dword ptr [ecx + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46640e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 466410: test ah, 1 */
	if (m->zf) goto L_46641b;	/* 466413: je 0x46641b */
	m->eax = M32((DWORD)(m->ecx + 0x10u));	/* 466415: mov eax, dword ptr [ecx + 0x10] */
	M32((DWORD)(m->ebx + 0x48u)) = m->eax;	/* 466418: mov dword ptr [ebx + 0x48], eax */
L_46641b:
	{ DWORD a_ = m->ecx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46641b: add ecx, 0x80 */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 466421: dec edi */
	if (!m->zf) goto L_4663af;	/* 466422: jne 0x4663af */
L_466424:
	m->edi = M32(m->esp); m->esp += 4;	/* 466424: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 466425: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 466426: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 466427: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 466428: pop ecx */
	m->esp += 4 + 12; return;	/* 466429: ret 0xc */
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
