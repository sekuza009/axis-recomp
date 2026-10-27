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

static void lift_479a90(X86 *m);
static void lift_47d000(X86 *m);

/* bullet_updateAll (0x47d000), lifted by tools/lift.py */
static void lift_47d000(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47d000: push esi */
	m->esi = m->ecx;	/* 47d001: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47d003: push edi */
	m->eax = M32((DWORD)(m->esi + 0x2149308u));	/* 47d004: mov eax, dword ptr [esi + 0x2149308] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47d00a: test eax, eax */
	if (m->zf) goto L_47d017;	/* 47d00c: je 0x47d017 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x214930cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47d00e: cmp dword ptr [esi + 0x214930c], 1 */
	if (m->zf) goto L_47d050;	/* 47d015: je 0x47d050 */
L_47d017:
	m->eax = M32((DWORD)(m->esi + 0x20a99b4u));	/* 47d017: mov eax, dword ptr [esi + 0x20a99b4] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 47d01d: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47d01f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_47d050;	/* 47d021: jle 0x47d050 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47d023: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47d024: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 47d025: mov ebp, dword ptr [esp + 0x14] */
	m->ebx = (DWORD)(m->esi + 0x202ef38u);	/* 47d029: lea ebx, [esi + 0x202ef38] */
L_47d02f:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47d02f: cmp dword ptr [ebx], 1 */
	if (!m->zf) goto L_47d03d;	/* 47d032: jne 0x47d03d */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47d034: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47d035: push edi */
	m->ecx = m->esi;	/* 47d036: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x47d03du; native_call(m, 0x47a2d0u);	/* 47d038: call 0x47a2d0 */
L_47d03d:
	m->eax = M32((DWORD)(m->esi + 0x20a99b4u));	/* 47d03d: mov eax, dword ptr [esi + 0x20a99b4] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 47d043: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x4e8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 47d044: add ebx, 0x4e8 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47d04a: cmp edi, eax */
	if (m->sf != m->of) goto L_47d02f;	/* 47d04c: jl 0x47d02f */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47d04e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47d04f: pop ebx */
L_47d050:
	m->edi = M32(m->esp); m->esp += 4;	/* 47d050: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47d051: pop esi */
	m->esp += 4 + 4; return;	/* 47d052: ret 4 */
}

/* match_479a90 (0x479a90), lifted by tools/lift.py */
static void lift_479a90(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 479a90: push esi */
	m->esi = m->ecx;	/* 479a91: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 479a93: push edi */
	m->eax = M32((DWORD)(m->esi + 0x2149308u));	/* 479a94: mov eax, dword ptr [esi + 0x2149308] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 479a9a: test eax, eax */
	if (m->zf) goto L_479aa7;	/* 479a9c: je 0x479aa7 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x214930cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479a9e: cmp dword ptr [esi + 0x214930c], 1 */
	if (m->zf) goto L_479ae0;	/* 479aa5: je 0x479ae0 */
L_479aa7:
	m->eax = M32((DWORD)(m->esi + 0x20f2da0u));	/* 479aa7: mov eax, dword ptr [esi + 0x20f2da0] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 479aad: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 479aaf: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_479ae0;	/* 479ab1: jle 0x479ae0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 479ab3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 479ab4: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 479ab5: mov ebp, dword ptr [esp + 0x14] */
	m->ebx = (DWORD)(m->esi + 0x20a99c4u);	/* 479ab9: lea ebx, [esi + 0x20a99c4] */
L_479abf:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479abf: cmp dword ptr [ebx], 1 */
	if (!m->zf) goto L_479acd;	/* 479ac2: jne 0x479acd */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 479ac4: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 479ac5: push edi */
	m->ecx = m->esi;	/* 479ac6: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x479acdu; native_call(m, 0x476410u);	/* 479ac8: call 0x476410 */
L_479acd:
	m->eax = M32((DWORD)(m->esi + 0x20f2da0u));	/* 479acd: mov eax, dword ptr [esi + 0x20f2da0] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 479ad3: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 479ad4: add ebx, 0x12c */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479ada: cmp edi, eax */
	if (m->sf != m->of) goto L_479abf;	/* 479adc: jl 0x479abf */
	m->ebp = M32(m->esp); m->esp += 4;	/* 479ade: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 479adf: pop ebx */
L_479ae0:
	m->edi = M32(m->esp); m->esp += 4;	/* 479ae0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 479ae1: pop esi */
	m->esp += 4 + 4; return;	/* 479ae2: ret 4 */
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
