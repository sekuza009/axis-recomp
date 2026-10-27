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

static void lift_43f460(X86 *m);
static void lift_42bee0(X86 *m);
static void lift_4734d0(X86 *m);
static void lift_473780(X86 *m);
static void lift_4813e0(X86 *m);
static void lift_4819b0(X86 *m);
static void lift_471010(X86 *m);
static void lift_484050(X86 *m);
static void lift_4569d0(X86 *m);
static void lift_46aa10(X86 *m);
static void lift_49d150(X86 *m);

/* match_49d150 (0x49d150), lifted by tools/lift.py */
static void lift_49d150(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49d150: push esi */
	m->esi = m->ecx;	/* 49d151: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49d153: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d159: test eax, eax */
	if (m->sf != m->of) goto L_49d272;	/* 49d15b: jl 0x49d272 */
	m->ecx = m->eax;	/* 49d161: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d163: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d166: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d168: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d16b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d16d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d170: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb54u));	/* 49d172: mov edx, dword ptr [esi + ecx*8 + 0x1eccb54] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 49d179: lea eax, [esi + ecx*8] */
	m->ecx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb60u));	/* 49d17c: mov ecx, dword ptr [esi + ecx*8 + 0x1eccb60] */
	m->eax = M32((DWORD)(0x4de72eu));	/* 49d183: mov eax, dword ptr [0x4de72e] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49d188: sub edx, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49d18a: add eax, edx */
	M32((DWORD)(0x4de72eu)) = m->eax;	/* 49d18c: mov dword ptr [0x4de72e], eax */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49d191: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 49d197: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d199: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d19c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d19e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d1a1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d1a3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d1a6: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb58u));	/* 49d1a8: mov edx, dword ptr [esi + ecx*8 + 0x1eccb58] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 49d1af: lea eax, [esi + ecx*8] */
	m->ecx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb64u));	/* 49d1b2: mov ecx, dword ptr [esi + ecx*8 + 0x1eccb64] */
	m->eax = M32((DWORD)(0x4de732u));	/* 49d1b9: mov eax, dword ptr [0x4de732] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49d1be: sub edx, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49d1c0: add eax, edx */
	M32((DWORD)(0x4de732u)) = m->eax;	/* 49d1c2: mov dword ptr [0x4de732], eax */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49d1c7: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 49d1cd: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d1cf: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d1d2: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d1d4: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d1d7: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d1d9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d1dc: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb5cu));	/* 49d1de: mov edx, dword ptr [esi + ecx*8 + 0x1eccb5c] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 49d1e5: lea eax, [esi + ecx*8] */
	m->ecx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb68u));	/* 49d1e8: mov ecx, dword ptr [esi + ecx*8 + 0x1eccb68] */
	m->eax = M32((DWORD)(0x4de722u));	/* 49d1ef: mov eax, dword ptr [0x4de722] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49d1f4: sub edx, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49d1f6: add eax, edx */
	M32((DWORD)(0x4de722u)) = m->eax;	/* 49d1f8: mov dword ptr [0x4de722], eax */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49d1fd: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 49d203: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d205: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d208: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d20a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d20d: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d20f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d212: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb54u));	/* 49d214: mov edx, dword ptr [esi + ecx*8 + 0x1eccb54] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 49d21b: lea eax, [esi + ecx*8] */
	M32((DWORD)(m->eax + 0x1eccb60u)) = m->edx;	/* 49d21e: mov dword ptr [eax + 0x1eccb60], edx */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49d224: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 49d22a: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d22c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d22f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d231: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d234: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d236: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d239: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb58u));	/* 49d23b: mov edx, dword ptr [esi + ecx*8 + 0x1eccb58] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 49d242: lea eax, [esi + ecx*8] */
	M32((DWORD)(m->eax + 0x1eccb64u)) = m->edx;	/* 49d245: mov dword ptr [eax + 0x1eccb64], edx */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49d24b: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 49d251: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d253: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d256: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d258: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d25b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49d25d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49d260: add ecx, eax */
	m->edx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb5cu));	/* 49d262: mov edx, dword ptr [esi + ecx*8 + 0x1eccb5c] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 49d269: lea eax, [esi + ecx*8] */
	M32((DWORD)(m->eax + 0x1eccb68u)) = m->edx;	/* 49d26c: mov dword ptr [eax + 0x1eccb68], edx */
L_49d272:
	m->eax = M32((DWORD)(m->esi + 0x23423a1u));	/* 49d272: mov eax, dword ptr [esi + 0x23423a1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d278: test eax, eax */
	if (!m->zf) goto L_49d281;	/* 49d27a: jne 0x49d281 */
	m->esp -= 4; M32(m->esp) = 0x49d281u; native_call(m, 0x44aee0u);	/* 49d27c: call 0x44aee0 */
L_49d281:
	M32((DWORD)(m->esi + 0x233cc50u)) = 0x43960000u;	/* 49d281: mov dword ptr [esi + 0x233cc50], 0x43960000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 49d28b: pop esi */
	m->esp += 4 + 0; return;	/* 49d28c: ret  */
}

/* chat_createEdit (0x43f460), lifted by tools/lift.py */
static void lift_43f460(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f460: sub esp, 0x3c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f463: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f464: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f465: push edi */
	m->ecx = 0xfu;	/* 43f466: mov ecx, 0xf */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f46b: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0xcu);	/* 43f46d: lea edi, [esp + 0xc] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43f471: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x4b29b0u;	/* 43f473: mov edi, 0x4b29b0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f478: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43f47b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43f47d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43f47f: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 43f481: lea edx, [esp + 0x28] */
	m->eax = m->ecx;	/* 43f485: mov eax, ecx */
	m->esi = m->edi;	/* 43f487: mov esi, edi */
	m->edi = m->edx;	/* 43f489: mov edi, edx */
	M8((DWORD)(m->esp + 0x23u)) = (BYTE)(0x1u);	/* 43f48b: mov byte ptr [esp + 0x23], 1 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43f490: shr ecx, 2 */
	M32((DWORD)(m->esp + 0xcu)) = 0xfffffff4u;	/* 43f493: mov dword ptr [esp + 0xc], 0xfffffff4 */
	m->ebx = M32((DWORD)(m->esp + 0x4cu));	/* 43f49b: mov ebx, dword ptr [esp + 0x4c] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43f49f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43f4a1: mov ecx, eax */
	M32((DWORD)(0x76d418u)) = m->ebx;	/* 43f4a3: mov dword ptr [0x76d418], ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f4a9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43f4ac: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0xcu);	/* 43f4ae: lea ecx, [esp + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4b2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43f4b9u; native_call(m, M32(0x4a9038u));	/* 43f4b3: call dword ptr [0x4a9038] */
	m->edx = M32((DWORD)(0x67ef18u));	/* 43f4b9: mov edx, dword ptr [0x67ef18] */
	M32((DWORD)(0x9dd8e4u)) = m->eax;	/* 43f4bf: mov dword ptr [0x9dd8e4], eax */
	m->eax = M32((DWORD)(0x4ded18u));	/* 43f4c4: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4c9: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4cb: push edx */
	m->edx = M32((DWORD)(0x9da3dcu));	/* 43f4cc: mov edx, dword ptr [0x9da3dc] */
	{ DWORD v_ = 0xcau; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4d2: push 0xca */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4d7: push eax */
	m->eax = M32((DWORD)(0x9da3d8u));	/* 43f4d8: mov eax, dword ptr [0x9da3d8] */
	m->ecx = (DWORD)(m->ebx*8 + 0x0u);	/* 43f4dd: lea ecx, [ebx*8] */
	{ DWORD v_ = 0x18u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4e4: push 0x18 */
	{ DWORD a_ = m->edx, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43f4e6: add edx, 0x21 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4e9: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xfffffffbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43f4ea: add eax, -5 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4ed: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4ee: push eax */
	{ DWORD v_ = 0x40000400u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4ef: push 0x40000400 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4f4: push 0 */
	{ DWORD v_ = 0x4b29a8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4f6: push 0x4b29a8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f4fb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43f503u; native_call(m, M32(0x4a9350u));	/* 43f4fd: call dword ptr [0x4a9350] */
	m->ebx = M32((DWORD)(0x4a92ecu));	/* 43f503: mov ebx, dword ptr [0x4a92ec] */
	M32((DWORD)(0x9dd888u)) = m->eax;	/* 43f509: mov dword ptr [0x9dd888], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43f50e: test eax, eax */
	if (m->zf) goto L_43f525;	/* 43f510: je 0x43f525 */
	m->ecx = M32((DWORD)(0x9dd8e4u));	/* 43f512: mov ecx, dword ptr [0x9dd8e4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f518: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f51a: push ecx */
	{ DWORD v_ = 0x30u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f51b: push 0x30 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f51d: push eax */
	m->esp -= 4; M32(m->esp) = 0x43f520u; native_call(m, m->ebx);	/* 43f51e: call ebx */
	m->eax = M32((DWORD)(0x9dd888u));	/* 43f520: mov eax, dword ptr [0x9dd888] */
L_43f525:
	{ DWORD v_ = 0x440840u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f525: push 0x440840 */
	{ DWORD v_ = 0xfffffffcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f52a: push -4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f52c: push eax */
	m->esp -= 4; M32(m->esp) = 0x43f533u; native_call(m, M32(0x4a9354u));	/* 43f52d: call dword ptr [0x4a9354] */
	m->edx = M32((DWORD)(0x9dd888u));	/* 43f533: mov edx, dword ptr [0x9dd888] */
	M32((DWORD)(0x9dd868u)) = m->eax;	/* 43f539: mov dword ptr [0x9dd868], eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f53e: push edx */
	m->esp -= 4; M32(m->esp) = 0x43f545u; native_call(m, M32(0x4a935cu));	/* 43f53f: call dword ptr [0x4a935c] */
	m->edi = 0x9dc92cu;	/* 43f545: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f54a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f54d: xor eax, eax */
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f54f: push 0x9dc92c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43f554: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43f556: not ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f558: push eax */
	m->eax = M32((DWORD)(0x9dd888u));	/* 43f559: mov eax, dword ptr [0x9dd888] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43f55e: dec ecx */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f55f: push 0xc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f561: push eax */
	m->esi = m->ecx;	/* 43f562: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x43f566u; native_call(m, m->ebx);	/* 43f564: call ebx */
	m->ecx = M32((DWORD)(0x9dd888u));	/* 43f566: mov ecx, dword ptr [0x9dd888] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f56c: push esi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f56d: push esi */
	{ DWORD v_ = 0xb1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f56e: push 0xb1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f573: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43f576u; native_call(m, m->ebx);	/* 43f574: call ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 43f576: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43f577: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43f578: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f579: add esp, 0x3c */
	m->esp += 4 + 0; return;	/* 43f57c: ret  */
}

/* reg_readCharacterSettings (0x42bee0), lifted by tools/lift.py */
static void lift_42bee0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x414u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bee0: sub esp, 0x414 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bee6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42bee7: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bee8: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42bee9: push edi */
	m->edi = 0x4b17d0u;	/* 42beea: mov edi, 0x4b17d0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42beef: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42bef2: xor eax, eax */
	m->ebx = 0x1eu;	/* 42bef4: mov ebx, 0x1e */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42bef9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42befb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42befd: sub edi, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->ebx;	/* 42beff: mov dword ptr [esp + 0x18], ebx */
	m->eax = m->ecx;	/* 42bf03: mov eax, ecx */
	m->esi = m->edi;	/* 42bf05: mov esi, edi */
	m->edi = 0x9dd570u;	/* 42bf07: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42bf0c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42bf0f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42bf11: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42bf13: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42bf15: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42bf18: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b17bcu;	/* 42bf1a: mov edi, 0x4b17bc */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42bf1f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42bf22: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42bf24: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42bf26: sub edi, ecx */
	m->edx = m->ecx;	/* 42bf28: mov edx, ecx */
	m->esi = m->edi;	/* 42bf2a: mov esi, edi */
	m->edi = 0x5b1b30u;	/* 42bf2c: mov edi, 0x5b1b30 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42bf31: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42bf34: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42bf36: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42bf38: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42bf3b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M8((DWORD)(0x5b1b50u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42bf3d: mov byte ptr [0x5b1b50], al */
	M8((DWORD)(0x5b1b53u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42bf42: mov byte ptr [0x5b1b53], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0xau) & 0xff) << 0);	/* 42bf47: mov al, 0xa */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 42bf49: lea ecx, [esp + 0x14] */
	M8((DWORD)(0x5b1b54u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42bf4d: mov byte ptr [0x5b1b54], al */
	M8((DWORD)(0x5b1b55u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42bf52: mov byte ptr [0x5b1b55], al */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 42bf57: lea eax, [esp + 0x20] */
	M8((DWORD)(0x5b1b51u)) = (BYTE)(0x8u);	/* 42bf5b: mov byte ptr [0x5b1b51], 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf62: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf63: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf64: push 0 */
	{ DWORD v_ = 0xf003fu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf66: push 0xf003f */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf6b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf6d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf6f: push 0 */
	{ DWORD v_ = 0x4b179cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf71: push 0x4b179c */
	{ DWORD v_ = 0x80000001u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf76: push 0x80000001 */
	M8((DWORD)(0x5b1b52u)) = (BYTE)(0x0u);	/* 42bf7b: mov byte ptr [0x5b1b52], 0 */
	m->esp -= 4; M32(m->esp) = 0x42bf88u; native_call(m, M32(0x4a9010u));	/* 42bf82: call dword ptr [0x4a9010] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 42bf88: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42bf8c: cmp eax, 1 */
	if (!m->zf) goto L_42c09e;	/* 42bf8f: jne 0x42c09e */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 42bf95: mov edx, dword ptr [esp + 0x14] */
	m->esi = M32((DWORD)(0x4a9000u));	/* 42bf99: mov esi, dword ptr [0x4a9000] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bf9f: push ebx */
	{ DWORD v_ = 0x9dd570u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfa0: push 0x9dd570 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfa5: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfa6: push 0 */
	{ DWORD v_ = 0x4b1794u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfa8: push 0x4b1794 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfad: push edx */
	m->esp -= 4; M32(m->esp) = 0x42bfb0u; native_call(m, m->esi);	/* 42bfae: call esi */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42bfb0: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfb4: push 0x20 */
	{ DWORD v_ = 0x5b1b30u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfb6: push 0x5b1b30 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfbb: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfbd: push 0 */
	{ DWORD v_ = 0x4b1788u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfbf: push 0x4b1788 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfc4: push eax */
	m->esp -= 4; M32(m->esp) = 0x42bfc7u; native_call(m, m->esi);	/* 42bfc5: call esi */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b50u)));	/* 42bfc7: movsx ecx, byte ptr [0x5b1b50] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42bfce: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42bfd2: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfd6: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfd8: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfd9: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfdb: push 0 */
	{ DWORD v_ = 0x4b1784u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfdd: push 0x4b1784 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfe2: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 42bfe3: mov dword ptr [esp + 0x28], ecx */
	m->esp -= 4; M32(m->esp) = 0x42bfe9u; native_call(m, m->esi);	/* 42bfe7: call esi */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b51u)));	/* 42bfe9: movsx ecx, byte ptr [0x5b1b51] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42bff0: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42bff4: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bff8: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bffa: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bffb: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bffd: push 0 */
	{ DWORD v_ = 0x4b1778u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bfff: push 0x4b1778 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c004: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 42c005: mov dword ptr [esp + 0x28], ecx */
	m->esp -= 4; M32(m->esp) = 0x42c00bu; native_call(m, m->esi);	/* 42c009: call esi */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b53u)));	/* 42c00b: movsx ecx, byte ptr [0x5b1b53] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42c012: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c016: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c01a: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c01c: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c01d: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c01f: push 0 */
	{ DWORD v_ = 0x4b176cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c021: push 0x4b176c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c026: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 42c027: mov dword ptr [esp + 0x28], ecx */
	m->esp -= 4; M32(m->esp) = 0x42c02du; native_call(m, m->esi);	/* 42c02b: call esi */
	m->ecx = M32((DWORD)(0x5b1b54u));	/* 42c02d: mov ecx, dword ptr [0x5b1b54] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42c033: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c037: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c03b: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c03d: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c03e: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c040: push 0 */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42c042: and ecx, 0xff */
	{ DWORD v_ = 0x4b1760u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c048: push 0x4b1760 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c04d: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 42c04e: mov dword ptr [esp + 0x28], ecx */
	m->esp -= 4; M32(m->esp) = 0x42c054u; native_call(m, m->esi);	/* 42c052: call esi */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42c054: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c058: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c05c: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c05e: push edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42c05f: xor ecx, ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c061: push 4 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b55u))) & 0xff) << 0);	/* 42c063: mov cl, byte ptr [0x5b1b55] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c069: push 0 */
	{ DWORD v_ = 0x4b1754u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c06b: push 0x4b1754 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c070: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 42c071: mov dword ptr [esp + 0x28], ecx */
	m->esp -= 4; M32(m->esp) = 0x42c077u; native_call(m, m->esi);	/* 42c075: call esi */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b52u)));	/* 42c077: movsx ecx, byte ptr [0x5b1b52] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c07e: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c082: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c084: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c085: push 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 42c087: mov dword ptr [esp + 0x1c], ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c08b: push 0 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 42c08d: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x4b1748u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c091: push 0x4b1748 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c096: push eax */
	m->esp -= 4; M32(m->esp) = 0x42c099u; native_call(m, m->esi);	/* 42c097: call esi */
	goto L_42c381;	/* 42c099: jmp 0x42c381 */
L_42c09e:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42c09e: cmp eax, 2 */
	if (!m->zf) goto L_42c402;	/* 42c0a1: jne 0x42c402 */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 42c0a7: lea ecx, [esp + 0x18] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 42c0ab: lea edx, [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c0af: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 42c0b0: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 42c0b4: lea eax, [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c0b8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c0b9: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c0ba: push 0 */
	M32((DWORD)(m->esp + 0x28u)) = m->ebx;	/* 42c0bc: mov dword ptr [esp + 0x28], ebx */
	m->ebx = M32((DWORD)(0x4a9008u));	/* 42c0c0: mov ebx, dword ptr [0x4a9008] */
	{ DWORD v_ = 0x4b1794u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c0c6: push 0x4b1794 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c0cb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c0ceu; native_call(m, m->ebx);	/* 42c0cc: call ebx */
	m->ebp = M32((DWORD)(0x4a9000u));	/* 42c0ce: mov ebp, dword ptr [0x4a9000] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42c0d4: test eax, eax */
	if (!m->zf) goto L_42c10e;	/* 42c0d6: jne 0x42c10e */
	m->ecx = 0x7u;	/* 42c0d8: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42c0dd: xor eax, eax */
	m->edi = 0x9dd570u;	/* 42c0df: mov edi, 0x9dd570 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42c0e4: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 42c0e6: stosw word ptr es:[edi], ax */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 42c0e8: lea edi, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42c0ec: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42c0ef: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42c0f1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42c0f3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42c0f5: sub edi, ecx */
	m->edx = m->ecx;	/* 42c0f7: mov edx, ecx */
	m->esi = m->edi;	/* 42c0f9: mov esi, edi */
	m->edi = 0x9dd570u;	/* 42c0fb: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42c100: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42c103: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42c105: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42c107: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42c10a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42c125;	/* 42c10c: jmp 0x42c125 */
L_42c10e:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42c10e: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c112: push 0x1e */
	{ DWORD v_ = 0x9dd570u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c114: push 0x9dd570 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c119: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c11b: push 0 */
	{ DWORD v_ = 0x4b1794u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c11d: push 0x4b1794 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c122: push eax */
	m->esp -= 4; M32(m->esp) = 0x42c125u; native_call(m, m->ebp);	/* 42c123: call ebp */
L_42c125:
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 42c125: lea ecx, [esp + 0x18] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 42c129: lea edx, [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c12d: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 42c12e: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 42c132: lea eax, [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c136: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c137: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c138: push 0 */
	{ DWORD v_ = 0x4b1788u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c13a: push 0x4b1788 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c13f: push ecx */
	M32((DWORD)(m->esp + 0x30u)) = 0x20u;	/* 42c140: mov dword ptr [esp + 0x30], 0x20 */
	m->esp -= 4; M32(m->esp) = 0x42c14au; native_call(m, m->ebx);	/* 42c148: call ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42c14a: test eax, eax */
	if (!m->zf) goto L_42c17e;	/* 42c14c: jne 0x42c17e */
	m->ecx = 0x8u;	/* 42c14e: mov ecx, 8 */
	m->edi = 0x5b1b30u;	/* 42c153: mov edi, 0x5b1b30 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42c158: rep stosd dword ptr es:[edi], eax */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 42c15a: lea edi, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42c15e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42c161: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42c163: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42c165: sub edi, ecx */
	m->edx = m->ecx;	/* 42c167: mov edx, ecx */
	m->esi = m->edi;	/* 42c169: mov esi, edi */
	m->edi = 0x5b1b30u;	/* 42c16b: mov edi, 0x5b1b30 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42c170: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42c173: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42c175: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42c177: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42c17a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42c195;	/* 42c17c: jmp 0x42c195 */
L_42c17e:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42c17e: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c182: push 0x20 */
	{ DWORD v_ = 0x5b1b30u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c184: push 0x5b1b30 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c189: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c18b: push 0 */
	{ DWORD v_ = 0x4b1788u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c18d: push 0x4b1788 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c192: push eax */
	m->esp -= 4; M32(m->esp) = 0x42c195u; native_call(m, m->ebp);	/* 42c193: call ebp */
L_42c195:
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 42c195: lea ecx, [esp + 0x18] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c199: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c19d: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 42c19e: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 42c1a2: lea eax, [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1a6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1a7: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1a8: push 0 */
	{ DWORD v_ = 0x4b1784u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1aa: push 0x4b1784 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1af: push ecx */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 42c1b0: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x4u;	/* 42c1b8: mov dword ptr [esp + 0x30], 4 */
	m->esp -= 4; M32(m->esp) = 0x42c1c2u; native_call(m, m->ebx);	/* 42c1c0: call ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42c1c2: test eax, eax */
	if (!m->zf) goto L_42c1d2;	/* 42c1c4: jne 0x42c1d2 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 42c1c6: mov dl, byte ptr [esp + 0x10] */
	M8((DWORD)(0x5b1b50u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 42c1ca: mov byte ptr [0x5b1b50], dl */
	goto L_42c1f4;	/* 42c1d0: jmp 0x42c1f4 */
L_42c1d2:
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b50u)));	/* 42c1d2: movsx eax, byte ptr [0x5b1b50] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 42c1d9: mov edx, dword ptr [esp + 0x14] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 42c1dd: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1e1: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1e3: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1e4: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1e6: push 0 */
	{ DWORD v_ = 0x4b1784u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1e8: push 0x4b1784 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1ed: push edx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 42c1ee: mov dword ptr [esp + 0x28], eax */
	m->esp -= 4; M32(m->esp) = 0x42c1f4u; native_call(m, m->ebp);	/* 42c1f2: call ebp */
L_42c1f4:
	m->eax = (DWORD)(m->esp + 0x18u);	/* 42c1f4: lea eax, [esp + 0x18] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 42c1f8: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c1fc: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 42c1fd: mov eax, dword ptr [esp + 0x18] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 42c201: lea edx, [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c205: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c206: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c207: push 0 */
	{ DWORD v_ = 0x4b1778u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c209: push 0x4b1778 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c20e: push eax */
	m->esp -= 4; M32(m->esp) = 0x42c211u; native_call(m, m->ebx);	/* 42c20f: call ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42c211: test eax, eax */
	if (!m->zf) goto L_42c221;	/* 42c213: jne 0x42c221 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 42c215: mov cl, byte ptr [esp + 0x10] */
	M8((DWORD)(0x5b1b51u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 42c219: mov byte ptr [0x5b1b51], cl */
	goto L_42c243;	/* 42c21f: jmp 0x42c243 */
L_42c221:
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b51u)));	/* 42c221: movsx edx, byte ptr [0x5b1b51] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 42c228: mov ecx, dword ptr [esp + 0x14] */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42c22c: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c230: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c232: push eax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c233: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c235: push 0 */
	{ DWORD v_ = 0x4b1778u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c237: push 0x4b1778 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c23c: push ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 42c23d: mov dword ptr [esp + 0x28], edx */
	m->esp -= 4; M32(m->esp) = 0x42c243u; native_call(m, m->ebp);	/* 42c241: call ebp */
L_42c243:
	m->edx = (DWORD)(m->esp + 0x18u);	/* 42c243: lea edx, [esp + 0x18] */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42c247: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c24b: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 42c24c: mov edx, dword ptr [esp + 0x18] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 42c250: lea ecx, [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c254: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c255: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c256: push 0 */
	{ DWORD v_ = 0x4b176cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c258: push 0x4b176c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c25d: push edx */
	m->esp -= 4; M32(m->esp) = 0x42c260u; native_call(m, m->ebx);	/* 42c25e: call ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42c260: test eax, eax */
	if (!m->zf) goto L_42c26f;	/* 42c262: jne 0x42c26f */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 42c264: mov al, byte ptr [esp + 0x10] */
	M8((DWORD)(0x5b1b53u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42c268: mov byte ptr [0x5b1b53], al */
	goto L_42c291;	/* 42c26d: jmp 0x42c291 */
L_42c26f:
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b53u)));	/* 42c26f: movsx ecx, byte ptr [0x5b1b53] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42c276: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c27a: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c27e: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c280: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c281: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c283: push 0 */
	{ DWORD v_ = 0x4b176cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c285: push 0x4b176c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c28a: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 42c28b: mov dword ptr [esp + 0x28], ecx */
	m->esp -= 4; M32(m->esp) = 0x42c291u; native_call(m, m->ebp);	/* 42c28f: call ebp */
L_42c291:
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 42c291: lea ecx, [esp + 0x18] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c295: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c299: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 42c29a: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 42c29e: lea eax, [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2a2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2a3: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2a4: push 0 */
	{ DWORD v_ = 0x4b1760u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2a6: push 0x4b1760 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2ab: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c2aeu; native_call(m, m->ebx);	/* 42c2ac: call ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42c2ae: test eax, eax */
	if (!m->zf) goto L_42c2be;	/* 42c2b0: jne 0x42c2be */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 42c2b2: mov dl, byte ptr [esp + 0x10] */
	M8((DWORD)(0x5b1b54u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 42c2b6: mov byte ptr [0x5b1b54], dl */
	goto L_42c2e3;	/* 42c2bc: jmp 0x42c2e3 */
L_42c2be:
	m->eax = M32((DWORD)(0x5b1b54u));	/* 42c2be: mov eax, dword ptr [0x5b1b54] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 42c2c3: mov edx, dword ptr [esp + 0x14] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 42c2c7: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2cb: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2cd: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2ce: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2d0: push 0 */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42c2d2: and eax, 0xff */
	{ DWORD v_ = 0x4b1760u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2d7: push 0x4b1760 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2dc: push edx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 42c2dd: mov dword ptr [esp + 0x28], eax */
	m->esp -= 4; M32(m->esp) = 0x42c2e3u; native_call(m, m->ebp);	/* 42c2e1: call ebp */
L_42c2e3:
	m->eax = (DWORD)(m->esp + 0x18u);	/* 42c2e3: lea eax, [esp + 0x18] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 42c2e7: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2eb: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 42c2ec: mov eax, dword ptr [esp + 0x18] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 42c2f0: lea edx, [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2f4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2f5: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2f6: push 0 */
	{ DWORD v_ = 0x4b1754u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2f8: push 0x4b1754 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c2fd: push eax */
	m->esp -= 4; M32(m->esp) = 0x42c300u; native_call(m, m->ebx);	/* 42c2fe: call ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42c300: test eax, eax */
	if (!m->zf) goto L_42c310;	/* 42c302: jne 0x42c310 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 42c304: mov cl, byte ptr [esp + 0x10] */
	M8((DWORD)(0x5b1b55u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 42c308: mov byte ptr [0x5b1b55], cl */
	goto L_42c333;	/* 42c30e: jmp 0x42c333 */
L_42c310:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 42c310: mov ecx, dword ptr [esp + 0x14] */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42c314: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c318: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c31a: push eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42c31b: xor edx, edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c31d: push 4 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b55u))) & 0xff) << 0);	/* 42c31f: mov dl, byte ptr [0x5b1b55] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c325: push 0 */
	{ DWORD v_ = 0x4b1754u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c327: push 0x4b1754 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c32c: push ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 42c32d: mov dword ptr [esp + 0x28], edx */
	m->esp -= 4; M32(m->esp) = 0x42c333u; native_call(m, m->ebp);	/* 42c331: call ebp */
L_42c333:
	m->edx = (DWORD)(m->esp + 0x18u);	/* 42c333: lea edx, [esp + 0x18] */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42c337: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c33b: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 42c33c: mov edx, dword ptr [esp + 0x18] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 42c340: lea ecx, [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c344: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c345: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c346: push 0 */
	{ DWORD v_ = 0x4b1748u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c348: push 0x4b1748 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c34d: push edx */
	m->esp -= 4; M32(m->esp) = 0x42c350u; native_call(m, m->ebx);	/* 42c34e: call ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42c350: test eax, eax */
	if (!m->zf) goto L_42c35f;	/* 42c352: jne 0x42c35f */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 42c354: mov al, byte ptr [esp + 0x10] */
	M8((DWORD)(0x5b1b52u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42c358: mov byte ptr [0x5b1b52], al */
	goto L_42c381;	/* 42c35d: jmp 0x42c381 */
L_42c35f:
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b52u)));	/* 42c35f: movsx ecx, byte ptr [0x5b1b52] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42c366: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c36a: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c36e: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c370: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c371: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c373: push 0 */
	{ DWORD v_ = 0x4b1748u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c375: push 0x4b1748 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c37a: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 42c37b: mov dword ptr [esp + 0x28], ecx */
	m->esp -= 4; M32(m->esp) = 0x42c381u; native_call(m, m->ebp);	/* 42c37f: call ebp */
L_42c381:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b54u))) & 0xff) << 0);	/* 42c381: mov al, byte ptr [0x5b1b54] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((0x5u) & 0xff) << 0);	/* 42c386: mov cl, 5 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42c388: cmp al, cl */
	if (!m->cf) goto L_42c394;	/* 42c38a: jae 0x42c394 */
	M8((DWORD)(0x5b1b54u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 42c38c: mov byte ptr [0x5b1b54], cl */
	goto L_42c39f;	/* 42c392: jmp 0x42c39f */
L_42c394:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1eu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42c394: cmp al, 0x1e */
	if (m->cf || m->zf) goto L_42c39f;	/* 42c396: jbe 0x42c39f */
	M8((DWORD)(0x5b1b54u)) = (BYTE)(0x1eu);	/* 42c398: mov byte ptr [0x5b1b54], 0x1e */
L_42c39f:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b55u))) & 0xff) << 0);	/* 42c39f: mov al, byte ptr [0x5b1b55] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42c3a4: cmp al, cl */
	if (!m->cf) goto L_42c3b0;	/* 42c3a6: jae 0x42c3b0 */
	M8((DWORD)(0x5b1b55u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 42c3a8: mov byte ptr [0x5b1b55], cl */
	goto L_42c3bb;	/* 42c3ae: jmp 0x42c3bb */
L_42c3b0:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1eu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42c3b0: cmp al, 0x1e */
	if (m->cf || m->zf) goto L_42c3bb;	/* 42c3b2: jbe 0x42c3bb */
	M8((DWORD)(0x5b1b55u)) = (BYTE)(0x1eu);	/* 42c3b4: mov byte ptr [0x5b1b55], 0x1e */
L_42c3bb:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b50u))) & 0xff) << 0);	/* 42c3bb: mov al, byte ptr [0x5b1b50] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42c3c0: test al, al */
	if (m->sf != m->of) goto L_42c3c8;	/* 42c3c2: jl 0x42c3c8 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x15u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42c3c4: cmp al, 0x15 */
	if (m->zf || m->sf != m->of) goto L_42c3cf;	/* 42c3c6: jle 0x42c3cf */
L_42c3c8:
	M8((DWORD)(0x5b1b50u)) = (BYTE)(0x0u);	/* 42c3c8: mov byte ptr [0x5b1b50], 0 */
L_42c3cf:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b51u))) & 0xff) << 0);	/* 42c3cf: mov al, byte ptr [0x5b1b51] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42c3d4: test al, al */
	if (m->sf != m->of) goto L_42c3dc;	/* 42c3d6: jl 0x42c3dc */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42c3d8: cmp al, 0x10 */
	if (m->zf || m->sf != m->of) goto L_42c3e3;	/* 42c3da: jle 0x42c3e3 */
L_42c3dc:
	M8((DWORD)(0x5b1b51u)) = (BYTE)(0x8u);	/* 42c3dc: mov byte ptr [0x5b1b51], 8 */
L_42c3e3:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b53u))) & 0xff) << 0);	/* 42c3e3: mov al, byte ptr [0x5b1b53] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42c3e8: test al, al */
	if (m->sf != m->of) goto L_42c3f0;	/* 42c3ea: jl 0x42c3f0 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xbu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42c3ec: cmp al, 0xb */
	if (m->zf || m->sf != m->of) goto L_42c3f7;	/* 42c3ee: jle 0x42c3f7 */
L_42c3f0:
	M8((DWORD)(0x5b1b53u)) = (BYTE)(0x0u);	/* 42c3f0: mov byte ptr [0x5b1b53], 0 */
L_42c3f7:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 42c3f7: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c3fb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c402u; native_call(m, M32(0x4a900cu));	/* 42c3fc: call dword ptr [0x4a900c] */
L_42c402:
	m->edi = M32(m->esp); m->esp += 4;	/* 42c402: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42c403: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42c404: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42c405: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x414u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c406: add esp, 0x414 */
	m->esp += 4 + 0; return;	/* 42c40c: ret  */
}

/* gfx_saveScreenshot (0x4734d0), lifted by tools/lift.py */
static void lift_4734d0(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4734d0: push -1 */
	{ DWORD v_ = 0x4a8e0bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4734d2: push 0x4a8e0b */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 4734d7: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4734dd: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 4734de: mov dword ptr fs:[0], esp */
	{ DWORD a_ = m->esp, b_ = 0x148u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4734e5: sub esp, 0x148 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4734eb: push ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4734ec: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4734ee: push esi */
	M32((DWORD)(m->esp + 0x8u)) = 0x4a96f8u;	/* 4734ef: mov dword ptr [esp + 8], 0x4a96f8 */
	M32((DWORD)(m->esp + 0xcu)) = m->ebx;	/* 4734f7: mov dword ptr [esp + 0xc], ebx */
	m->edx = M32((DWORD)(m->esp + 0x160u));	/* 4734fb: mov edx, dword ptr [esp + 0x160] */
	M32((DWORD)(m->esp + 0x158u)) = m->ebx;	/* 473502: mov dword ptr [esp + 0x158], ebx */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 473509: lea eax, [edx + edx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47350c: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47350f: sub eax, edx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 473511: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 473514: lea edx, [edx + eax*8] */
	m->esi = (DWORD)(m->ecx + m->edx*2 + 0x1561b68u);	/* 473517: lea esi, [ecx + edx*2 + 0x1561b68] */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 47351e: lea ecx, [esp + 0x50] */
	m->eax = (DWORD)(m->esi + 0x4u);	/* 473522: lea eax, [esi + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 473525: push eax */
	{ DWORD v_ = 0x4c74e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 473526: push 0x4c74e8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47352b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x473531u; native_call(m, 0x49e9ddu);	/* 47352c: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473531: add esp, 0xc */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 473534: lea edx, [esp + 0x50] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 473538: lea ecx, [esp + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47353c: push edx */
	m->esp -= 4; M32(m->esp) = 0x473542u; native_call(m, 0x46cdc0u);	/* 47353d: call 0x46cdc0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473542: test eax, eax */
	if (m->zf) goto L_4735d5;	/* 473544: je 0x4735d5 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x46u)), b_ = 0x17u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47354a: cmp dword ptr [esp + 0x46], 0x17 */
	if (m->sf != m->of) goto L_4735cc;	/* 47354f: jl 0x4735cc */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x4au)), b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473551: cmp dword ptr [esp + 0x4a], 0xf */
	if (m->sf != m->of) goto L_4735cc;	/* 473556: jl 0x4735cc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473558: push ebx */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 473559: push 0x10 */
	{ DWORD v_ = 0x18u; m->esp -= 4; M32(m->esp) = v_; }	/* 47355b: push 0x18 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47355d: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47355e: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47355f: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473560: push ebx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 473561: push 4 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 473563: push 0x10 */
	m->eax = (DWORD)(m->esi + 0x479c2u);	/* 473565: lea eax, [esi + 0x479c2] */
	{ DWORD v_ = 0x18u; m->esp -= 4; M32(m->esp) = v_; }	/* 47356b: push 0x18 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47356d: push eax */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 47356e: lea ecx, [esp + 0x34] */
	m->esp -= 4; M32(m->esp) = 0x473577u; native_call(m, 0x46ce80u);	/* 473572: call 0x46ce80 */
	m->eax = (DWORD)(m->esi + 0x479c4u);	/* 473577: lea eax, [esi + 0x479c4] */
	m->esi = 0x10u;	/* 47357d: mov esi, 0x10 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((0xffu) & 0xff) << 0);	/* 473582: mov dl, 0xff */
L_473584:
	m->ecx = 0x18u;	/* 473584: mov ecx, 0x18 */
L_473589:
	{ DWORD a_ = M8((DWORD)(m->eax + 0xfffffffeu)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 473589: cmp byte ptr [eax - 2], bl */
	if (!m->zf) goto L_47359c;	/* 47358c: jne 0x47359c */
	{ DWORD a_ = M8((DWORD)(m->eax + 0xffffffffu)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 47358e: cmp byte ptr [eax - 1], bl */
	if (!m->zf) goto L_47359c;	/* 473591: jne 0x47359c */
	{ DWORD a_ = M8((DWORD)(m->eax + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 473593: cmp byte ptr [eax], bl */
	if (!m->zf) goto L_47359c;	/* 473595: jne 0x47359c */
	M8((DWORD)(m->eax + 0x1u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 473597: mov byte ptr [eax + 1], bl */
	goto L_47359f;	/* 47359a: jmp 0x47359f */
L_47359c:
	M8((DWORD)(m->eax + 0x1u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 47359c: mov byte ptr [eax + 1], dl */
L_47359f:
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47359f: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4735a2: dec ecx */
	if (!m->zf) goto L_473589;	/* 4735a3: jne 0x473589 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 4735a5: dec esi */
	if (!m->zf) goto L_473584;	/* 4735a6: jne 0x473584 */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4735a8: lea ecx, [esp + 8] */
	m->esp -= 4; M32(m->esp) = 0x4735b1u; native_call(m, 0x46ce50u);	/* 4735ac: call 0x46ce50 */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4735b1: lea ecx, [esp + 8] */
	M32((DWORD)(m->esp + 0x158u)) = 0xffffffffu;	/* 4735b5: mov dword ptr [esp + 0x158], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x4735c5u; native_call(m, 0x46ce60u);	/* 4735c0: call 0x46ce60 */
	m->eax = 0x1u;	/* 4735c5: mov eax, 1 */
	goto L_4735eb;	/* 4735ca: jmp 0x4735eb */
L_4735cc:
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4735cc: lea ecx, [esp + 8] */
	m->esp -= 4; M32(m->esp) = 0x4735d5u; native_call(m, 0x46ce50u);	/* 4735d0: call 0x46ce50 */
L_4735d5:
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4735d5: lea ecx, [esp + 8] */
	M32((DWORD)(m->esp + 0x158u)) = 0xffffffffu;	/* 4735d9: mov dword ptr [esp + 0x158], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x4735e9u; native_call(m, 0x46ce60u);	/* 4735e4: call 0x46ce60 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4735e9: xor eax, eax */
L_4735eb:
	m->ecx = M32((DWORD)(m->esp + 0x150u));	/* 4735eb: mov ecx, dword ptr [esp + 0x150] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4735f2: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4735f3: pop ebx */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 4735f4: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x154u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4735fb: add esp, 0x154 */
	m->esp += 4 + 4; return;	/* 473601: ret 4 */
}

/* catalogue_loadComponents (0x473780), lifted by tools/lift.py */
static void lift_473780(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473780: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x8u));	/* 473781: mov ebx, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473785: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473786: push edi */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 473787: push 0x4ad170 */
	m->esi = m->ecx;	/* 47378c: mov esi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47378e: push ebx */
	m->esp -= 4; M32(m->esp) = 0x473794u; native_call(m, 0x49e9cau);	/* 47378f: call 0x49e9ca */
	m->edi = m->eax;	/* 473794: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473796: add esp, 8 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473799: test edi, edi */
	if (!m->zf) goto L_4737b0;	/* 47379b: jne 0x4737b0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47379d: push ebx */
	{ DWORD v_ = 0x4c75bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 47379e: push 0x4c75bc */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737a3: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x4737adu; native_call(m, 0x46c710u);	/* 4737a8: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4737ad: add esp, 0xc */
L_4737b0:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4737b0: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737b1: push 1 */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 4737b3: lea eax, [esp + 0x18] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737b7: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4737b9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4737bfu; native_call(m, 0x49e836u);	/* 4737ba: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4737bf: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4737c3: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1204u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4737c6: cmp eax, 0x1204 */
	if (m->zf) goto L_4737e0;	/* 4737cb: je 0x4737e0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4737cd: push ebx */
	{ DWORD v_ = 0x4c7570u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737ce: push 0x4c7570 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737d3: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x4737ddu; native_call(m, 0x46c710u);	/* 4737d8: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4737dd: add esp, 0xc */
L_4737e0:
	{ DWORD v_ = 0x4c755cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4737e0: push 0x4c755c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737e5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737e7: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4737e9: push esi */
	m->esp -= 4; M32(m->esp) = 0x4737efu; native_call(m, 0x470fc0u);	/* 4737ea: call 0x470fc0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4737ef: push edi */
	m->ebx = (DWORD)(m->esi + 0x13eb000u);	/* 4737f0: lea ebx, [esi + 0x13eb000] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737f6: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4737f8: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4737fa: push ebx */
	m->esp -= 4; M32(m->esp) = 0x473800u; native_call(m, 0x46cbe0u);	/* 4737fb: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->ebx + 0x0u));	/* 473800: mov ecx, dword ptr [ebx] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473802: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 473803: push ecx */
	m->edx = (DWORD)(m->esi + 0x13c9b30u);	/* 473804: lea edx, [esi + 0x13c9b30] */
	{ DWORD v_ = 0xaa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 47380a: push 0xaa8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47380f: push edx */
	m->esp -= 4; M32(m->esp) = 0x473815u; native_call(m, 0x46cbe0u);	/* 473810: call 0x46cbe0 */
	{ DWORD v_ = 0x4c7548u; m->esp -= 4; M32(m->esp) = v_; }	/* 473815: push 0x4c7548 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47381a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47381c: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47381e: push esi */
	m->esp -= 4; M32(m->esp) = 0x473824u; native_call(m, 0x470fc0u);	/* 47381f: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473824: add esp, 0x40 */
	m->ebx = (DWORD)(m->esi + 0x140c8bcu);	/* 473827: lea ebx, [esi + 0x140c8bc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47382d: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47382e: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 473830: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473832: push ebx */
	m->esp -= 4; M32(m->esp) = 0x473838u; native_call(m, 0x46cbe0u);	/* 473833: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 473838: mov eax, dword ptr [ebx] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47383a: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47383b: push eax */
	m->ecx = (DWORD)(m->esi + 0x13eb004u);	/* 47383c: lea ecx, [esi + 0x13eb004] */
	{ DWORD v_ = 0xabcu; m->esp -= 4; M32(m->esp) = v_; }	/* 473842: push 0xabc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 473847: push ecx */
	m->esp -= 4; M32(m->esp) = 0x47384du; native_call(m, 0x46cbe0u);	/* 473848: call 0x46cbe0 */
	{ DWORD v_ = 0x4c7534u; m->esp -= 4; M32(m->esp) = v_; }	/* 47384d: push 0x4c7534 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 473852: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 473854: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473856: push esi */
	m->esp -= 4; M32(m->esp) = 0x47385cu; native_call(m, 0x470fc0u);	/* 473857: call 0x470fc0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47385c: push edi */
	m->ebx = (DWORD)(m->esi + 0x1447ec0u);	/* 47385d: lea ebx, [esi + 0x1447ec0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 473863: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 473865: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473867: push ebx */
	m->esp -= 4; M32(m->esp) = 0x47386du; native_call(m, 0x46cbe0u);	/* 473868: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 47386d: mov edx, dword ptr [ebx] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47386f: add esp, 0x40 */
	m->eax = (DWORD)(m->esi + 0x140c8c0u);	/* 473872: lea eax, [esi + 0x140c8c0] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473878: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 473879: push edx */
	{ DWORD v_ = 0x1300u; m->esp -= 4; M32(m->esp) = v_; }	/* 47387a: push 0x1300 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47387f: push eax */
	m->esp -= 4; M32(m->esp) = 0x473885u; native_call(m, 0x46cbe0u);	/* 473880: call 0x46cbe0 */
	{ DWORD v_ = 0x4c7520u; m->esp -= 4; M32(m->esp) = v_; }	/* 473885: push 0x4c7520 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47388a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47388c: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47388e: push esi */
	m->esp -= 4; M32(m->esp) = 0x473894u; native_call(m, 0x470fc0u);	/* 47388f: call 0x470fc0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473894: push edi */
	m->ebx = (DWORD)(m->esi + 0x148646cu);	/* 473895: lea ebx, [esi + 0x148646c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47389b: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 47389d: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47389f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4738a5u; native_call(m, 0x46cbe0u);	/* 4738a0: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->ebx + 0x0u));	/* 4738a5: mov ecx, dword ptr [ebx] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4738a7: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4738a8: push ecx */
	m->edx = (DWORD)(m->esi + 0x1447ec4u);	/* 4738a9: lea edx, [esi + 0x1447ec4] */
	{ DWORD v_ = 0x13f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738af: push 0x13f4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4738b4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4738bau; native_call(m, 0x46cbe0u);	/* 4738b5: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4738ba: add esp, 0x40 */
	{ DWORD v_ = 0x4c7508u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738bd: push 0x4c7508 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738c2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738c4: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4738c6: push esi */
	m->esp -= 4; M32(m->esp) = 0x4738ccu; native_call(m, 0x470fc0u);	/* 4738c7: call 0x470fc0 */
	m->ebx = (DWORD)(m->esi + 0x14d1ab0u);	/* 4738cc: lea ebx, [esi + 0x14d1ab0] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4738d2: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738d3: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738d5: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4738d7: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4738ddu; native_call(m, 0x46cbe0u);	/* 4738d8: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 4738dd: mov eax, dword ptr [ebx] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4738df: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4738e0: push eax */
	m->ecx = (DWORD)(m->esi + 0x1486470u);	/* 4738e1: lea ecx, [esi + 0x1486470] */
	{ DWORD v_ = 0x1820u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738e7: push 0x1820 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4738ec: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4738f2u; native_call(m, 0x46cbe0u);	/* 4738ed: call 0x46cbe0 */
	{ DWORD v_ = 0x4c74f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738f2: push 0x4c74f4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738f7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4738f9: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4738fb: push esi */
	m->esp -= 4; M32(m->esp) = 0x473901u; native_call(m, 0x470fc0u);	/* 4738fc: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473901: add esp, 0x40 */
	m->ebx = (DWORD)(m->esi + 0x1561b64u);	/* 473904: lea ebx, [esi + 0x1561b64] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47390a: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47390b: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 47390d: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47390f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x473915u; native_call(m, 0x46cbe0u);	/* 473910: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 473915: mov edx, dword ptr [ebx] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 473917: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 473918: push edx */
	{ DWORD a_ = m->esi, b_ = 0x14d1ab4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 473919: add esi, 0x14d1ab4 */
	{ DWORD v_ = 0x2e18u; m->esp -= 4; M32(m->esp) = v_; }	/* 47391f: push 0x2e18 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473924: push esi */
	m->esp -= 4; M32(m->esp) = 0x47392au; native_call(m, 0x46cbe0u);	/* 473925: call 0x46cbe0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47392a: push edi */
	m->esp -= 4; M32(m->esp) = 0x473930u; native_call(m, 0x49e7e0u);	/* 47392b: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473930: add esp, 0x24 */
	m->eax = 0x1u;	/* 473933: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 473938: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 473939: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47393a: pop ebx */
	m->esp += 4 + 4; return;	/* 47393b: ret 4 */
}

/* space_initBy (0x4813e0), lifted by tools/lift.py */
static void lift_4813e0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4813e0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4813e1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4813e2: push edi */
	m->esi = m->ecx;	/* 4813e3: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x4813eau; native_call(m, 0x4813b0u);	/* 4813e5: call 0x4813b0 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4813ea: mov eax, dword ptr [esp + 0x18] */
	m->edi = M32((DWORD)(m->esp + 0x1cu));	/* 4813ee: mov edi, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4813f2: mov ecx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esi + 0x30u)) = m->eax;	/* 4813f6: mov dword ptr [esi + 0x30], eax */
	m->eax = (DWORD)(m->eax + m->edi*4 + 0x0u);	/* 4813f9: lea eax, [eax + edi*4] */
	M32((DWORD)(m->esi + 0x40u)) = m->edi;	/* 4813fc: mov dword ptr [esi + 0x40], edi */
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 4813ff: mov ebx, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 481403: mov edx, dword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 481407: lea edi, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx*8 + 0x0u);	/* 48140a: lea eax, [ecx*8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 481411: sub eax, ecx */
	M32((DWORD)(m->esi + 0x10u)) = m->ecx;	/* 481413: mov dword ptr [esi + 0x10], ecx */
	M32((DWORD)(m->esi + 0x20u)) = m->edx;	/* 481416: mov dword ptr [esi + 0x20], edx */
	M32((DWORD)(m->esi + 0x50u)) = m->ebx;	/* 481419: mov dword ptr [esi + 0x50], ebx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48141c: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*2 + 0x0u);	/* 48141f: lea ecx, [ecx + eax*2] */
	m->eax = (DWORD)(m->ebx + m->edi*2 + 0x0u);	/* 481422: lea eax, [ebx + edi*2] */
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 481425: mov edi, dword ptr [esp + 0x24] */
	m->ecx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 481429: lea ecx, [eax + ecx*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 48142c: lea eax, [ecx + edx*8] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48142f: shl eax, 1 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481431: test edi, edi */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 481433: mov dword ptr [esi + 4], eax */
	if (!m->zf) goto L_481467;	/* 481436: jne 0x481467 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481438: push eax */
	m->esp -= 4; M32(m->esp) = 0x48143eu; native_call(m, 0x49f1aau);	/* 481439: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48143e: add esp, 4 */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 481441: mov dword ptr [esi + 8], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481444: test eax, eax */
	if (!m->zf) goto L_48145e;	/* 481446: jne 0x48145e */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 481448: mov edx, dword ptr [esi + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48144b: push edx */
	{ DWORD v_ = 0x4c4cecu; m->esp -= 4; M32(m->esp) = v_; }	/* 48144c: push 0x4c4cec */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481451: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x48145bu; native_call(m, 0x46c710u);	/* 481456: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48145b: add esp, 0xc */
L_48145e:
	M32((DWORD)(m->esi + 0xcu)) = 0x1u;	/* 48145e: mov dword ptr [esi + 0xc], 1 */
	goto L_481486;	/* 481465: jmp 0x481486 */
L_481467:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 481467: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48146b: cmp ecx, eax */
	if (m->sf == m->of) goto L_481483;	/* 48146d: jge 0x481483 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48146f: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481470: push eax */
	{ DWORD v_ = 0x4c4cbcu; m->esp -= 4; M32(m->esp) = v_; }	/* 481471: push 0x4c4cbc */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481476: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x481480u; native_call(m, 0x46c710u);	/* 48147b: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481480: add esp, 0x10 */
L_481483:
	M32((DWORD)(m->esi + 0x8u)) = m->edi;	/* 481483: mov dword ptr [esi + 8], edi */
L_481486:
	m->edx = M32((DWORD)(m->esi + 0x10u));	/* 481486: mov edx, dword ptr [esi + 0x10] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 481489: mov eax, dword ptr [esi + 8] */
	M32((DWORD)(m->esi + 0x14u)) = m->eax;	/* 48148c: mov dword ptr [esi + 0x14], eax */
	M32((DWORD)(m->esi + 0x18u)) = m->eax;	/* 48148f: mov dword ptr [esi + 0x18], eax */
	m->ecx = (DWORD)(m->edx*8 + 0x0u);	/* 481492: lea ecx, [edx*8] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 481499: sub ecx, edx */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48149b: lea ecx, [ecx + ecx*2] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x0u);	/* 48149e: lea ecx, [edx + ecx*2] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4814a1: shl ecx, 2 */
	m->edx = (DWORD)(m->eax + m->ecx*1 + 0x0u);	/* 4814a4: lea edx, [eax + ecx] */
	M32((DWORD)(m->esi + 0x24u)) = m->edx;	/* 4814a7: mov dword ptr [esi + 0x24], edx */
	m->edx = M32((DWORD)(m->esi + 0x20u));	/* 4814aa: mov edx, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4814ad: shl edx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4814b0: add ecx, edx */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 4814b2: mov edx, dword ptr [esi + 0x24] */
	M32((DWORD)(m->esi + 0x28u)) = m->edx;	/* 4814b5: mov dword ptr [esi + 0x28], edx */
	m->edx = (DWORD)(m->eax + m->ecx*1 + 0x0u);	/* 4814b8: lea edx, [eax + ecx] */
	M32((DWORD)(m->esi + 0x34u)) = m->edx;	/* 4814bb: mov dword ptr [esi + 0x34], edx */
	m->edx = M32((DWORD)(m->esi + 0x30u));	/* 4814be: mov edx, dword ptr [esi + 0x30] */
	m->edx = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 4814c1: lea edx, [edx + edx*4] */
	m->ecx = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 4814c4: lea ecx, [ecx + edx*4] */
	m->edx = M32((DWORD)(m->esi + 0x34u));	/* 4814c7: mov edx, dword ptr [esi + 0x34] */
	M32((DWORD)(m->esi + 0x38u)) = m->edx;	/* 4814ca: mov dword ptr [esi + 0x38], edx */
	m->edx = (DWORD)(m->eax + m->ecx*1 + 0x0u);	/* 4814cd: lea edx, [eax + ecx] */
	M32((DWORD)(m->esi + 0x44u)) = m->edx;	/* 4814d0: mov dword ptr [esi + 0x44], edx */
	M32((DWORD)(m->esi + 0x48u)) = m->edx;	/* 4814d3: mov dword ptr [esi + 0x48], edx */
	m->edx = M32((DWORD)(m->esi + 0x40u));	/* 4814d6: mov edx, dword ptr [esi + 0x40] */
	m->edx = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 4814d9: lea edx, [edx + edx*4] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4814dc: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4814df: add edx, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4814e1: or eax, 0xffffffff */
	m->edi = (DWORD)(m->edx + m->ecx*1 + 0x0u);	/* 4814e4: lea edi, [edx + ecx] */
	m->ecx = M32((DWORD)(m->esi + 0x50u));	/* 4814e7: mov ecx, dword ptr [esi + 0x50] */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4814ea: shl ecx, 1 */
	m->edx = m->ecx;	/* 4814ec: mov edx, ecx */
	M32((DWORD)(m->esi + 0x54u)) = m->edi;	/* 4814ee: mov dword ptr [esi + 0x54], edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4814f1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4814f4: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 4814f6: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4814f8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 4814fb: rep stosb byte ptr es:[edi], al */
	m->ecx = m->esi;	/* 4814fd: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x481504u; native_call(m, 0x481520u);	/* 4814ff: call 0x481520 */
	m->ecx = m->esi;	/* 481504: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48150bu; native_call(m, 0x481630u);	/* 481506: call 0x481630 */
	m->ecx = m->esi;	/* 48150b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x481512u; native_call(m, 0x481760u);	/* 48150d: call 0x481760 */
	m->ecx = m->esi;	/* 481512: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x481519u; native_call(m, 0x481860u);	/* 481514: call 0x481860 */
	m->edi = M32(m->esp); m->esp += 4;	/* 481519: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48151a: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48151b: pop ebx */
	m->esp += 4 + 28; return;	/* 48151c: ret 0x1c */
}

/* space_setBy (0x4819b0), lifted by tools/lift.py */
static void lift_4819b0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4819b0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4819b1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4819b2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4819b3: push edi */
	m->esi = m->ecx;	/* 4819b4: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x4819bbu; native_call(m, 0x481520u);	/* 4819b6: call 0x481520 */
	m->ecx = m->esi;	/* 4819bb: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4819c2u; native_call(m, 0x481630u);	/* 4819bd: call 0x481630 */
	m->ecx = m->esi;	/* 4819c2: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4819c9u; native_call(m, 0x481760u);	/* 4819c4: call 0x481760 */
	m->ecx = m->esi;	/* 4819c9: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4819d0u; native_call(m, 0x481860u);	/* 4819cb: call 0x481860 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4819d0: mov eax, dword ptr [esp + 0x14] */
	m->ebx = (DWORD)(m->esi + 0x5cu);	/* 4819d4: lea ebx, [esi + 0x5c] */
	m->ecx = m->ebx;	/* 4819d7: mov ecx, ebx */
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 4819d9: mov edi, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 4819dd: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 4819df: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 4819e1: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 4819e4: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 4819e7: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 4819ea: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4819ed: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->esi + 0x68u);	/* 4819f1: lea eax, [esi + 0x68] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 4819f4: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 4819f6: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 4819f8: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4819fb: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4819fe: mov edx, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 481a02: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esi + 0x78u)) = m->edx;	/* 481a05: mov dword ptr [esi + 0x78], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 481a08: mov dword ptr [eax + 8], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 481a0b: mov ecx, dword ptr [esp + 0x1c] */
	m->eax = m->ecx;	/* 481a0f: mov eax, ecx */
	M32((DWORD)(m->esi + 0x74u)) = m->ecx;	/* 481a11: mov dword ptr [esi + 0x74], ecx */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 481a14: imul eax, edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->edi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 481a17: imul eax, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481a1a: test eax, eax */
	M32((DWORD)(m->esi + 0x7cu)) = m->edi;	/* 481a1c: mov dword ptr [esi + 0x7c], edi */
	M32((DWORD)(m->esi + 0x58u)) = m->eax;	/* 481a1f: mov dword ptr [esi + 0x58], eax */
	if (!m->zf && m->sf == m->of) goto L_481a3b;	/* 481a22: jg 0x481a3b */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 481a24: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481a25: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 481a26: push ecx */
	{ DWORD v_ = 0x4c79f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 481a27: push 0x4c79f4 */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481a2c: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x481a36u; native_call(m, 0x46c710u);	/* 481a31: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481a36: add esp, 0x14 */
	goto L_481a59;	/* 481a39: jmp 0x481a59 */
L_481a3b:
	m->ebp = M32((DWORD)(m->esi + 0x50u));	/* 481a3b: mov ebp, dword ptr [esi + 0x50] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481a3e: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_481a59;	/* 481a40: jle 0x481a59 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 481a42: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481a43: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 481a44: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481a45: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 481a46: push ecx */
	{ DWORD v_ = 0x4c79bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 481a47: push 0x4c79bc */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481a4c: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x481a56u; native_call(m, 0x46c710u);	/* 481a51: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481a56: add esp, 0x1c */
L_481a59:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 481a59: fld dword ptr [esi + 0x70] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 481a5c: fsub dword ptr [esi + 0x64] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esi + 0x74u));	/* 481a5f: fidiv dword ptr [esi + 0x74] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 481a62: mov eax, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 481a66: mov edx, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esi + 0x90u)) = m->eax;	/* 481a6a: mov dword ptr [esi + 0x90], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 481a70: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481a74: cmp eax, 8 */
	M32((DWORD)(m->esi + 0x8cu)) = m->edx;	/* 481a77: mov dword ptr [esi + 0x8c], edx */
	M32((DWORD)(m->esi + 0x94u)) = m->eax;	/* 481a7d: mov dword ptr [esi + 0x94], eax */
	MF((DWORD)(m->esi + 0x80u)) = (float)ST(0); FPOP();	/* 481a83: fstp dword ptr [esi + 0x80] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 481a89: fld dword ptr [esi + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 481a8c: fsub dword ptr [ebx] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esi + 0x78u));	/* 481a8e: fidiv dword ptr [esi + 0x78] */
	MF((DWORD)(m->esi + 0x84u)) = (float)ST(0); FPOP();	/* 481a91: fstp dword ptr [esi + 0x84] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 481a97: fld dword ptr [esi + 0x6c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 481a9a: fsub dword ptr [esi + 0x60] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esi + 0x7cu));	/* 481a9d: fidiv dword ptr [esi + 0x7c] */
	MF((DWORD)(m->esi + 0x88u)) = (float)ST(0); FPOP();	/* 481aa0: fstp dword ptr [esi + 0x88] */
	if (m->zf || m->sf != m->of) goto L_481abd;	/* 481aa6: jle 0x481abd */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 481aa8: push 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481aaa: push eax */
	{ DWORD v_ = 0x4c7980u; m->esp -= 4; M32(m->esp) = v_; }	/* 481aab: push 0x4c7980 */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481ab0: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x481abau; native_call(m, 0x46c710u);	/* 481ab5: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481aba: add esp, 0x10 */
L_481abd:
	m->ecx = M32((DWORD)(m->esi + 0x50u));	/* 481abd: mov ecx, dword ptr [esi + 0x50] */
	m->edi = M32((DWORD)(m->esi + 0x54u));	/* 481ac0: mov edi, dword ptr [esi + 0x54] */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 481ac3: shl ecx, 1 */
	m->edx = m->ecx;	/* 481ac5: mov edx, ecx */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481ac7: or eax, 0xffffffff */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 481aca: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 481acd: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 481acf: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 481ad1: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 481ad4: rep stosb byte ptr es:[edi], al */
	m->edi = M32(m->esp); m->esp += 4;	/* 481ad6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 481ad7: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 481ad8: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 481ad9: pop ebx */
	m->esp += 4 + 32; return;	/* 481ada: ret 0x20 */
}

/* load_471010 (0x471010), lifted by tools/lift.py */
static void lift_471010(X86 *m)
{
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471010: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471012: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 471014: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 471016: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 471018: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9ef910u);	/* 47101a: lea eax, [ecx + 0x9ef910] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 471020: push 1 */
	m->edx = (DWORD)(m->ecx + 0x9ef904u);	/* 471022: lea edx, [ecx + 0x9ef904] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 471028: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 471029: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47102a: add ecx, 0xa10 */
	m->esp -= 4; M32(m->esp) = 0x471035u; lift_4819b0(m);	/* 471030: call 0x4819b0 */
	m->esp += 4 + 0; return;	/* 471035: ret  */
}

/* factor_initBy (0x484050), lifted by tools/lift.py */
static void lift_484050(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 484050: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 484051: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 484052: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 484053: push edi */
	m->esi = m->ecx;	/* 484054: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x48405bu; native_call(m, 0x483fd0u);	/* 484056: call 0x483fd0 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48405b: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 48405f: mov ecx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 484063: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esi + 0x9048u)) = m->ecx;	/* 484067: mov dword ptr [esi + 0x9048], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 48406d: mov ecx, dword ptr [esp + 0x20] */
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 484071: mov edi, dword ptr [esp + 0x24] */
	m->ebp = (DWORD)(m->edx*8 + 0x0u);	/* 484075: lea ebp, [edx*8] */
	M32((DWORD)(m->esi + 0x9030u)) = m->edx;	/* 48407c: mov dword ptr [esi + 0x9030], edx */
	M32((DWORD)(m->esi + 0x903cu)) = m->eax;	/* 484082: mov dword ptr [esi + 0x903c], eax */
	{ DWORD a_ = m->ebp, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 484088: sub ebp, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48408a: shl eax, 4 */
	m->edx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48408d: lea edx, [ecx + ecx*2] */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 484090: add ebp, eax */
	m->ebx = M32((DWORD)(m->esp + 0x28u));	/* 484092: mov ebx, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esi + 0x9054u)) = m->ecx;	/* 484096: mov dword ptr [esi + 0x9054], ecx */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 48409c: lea eax, [ecx + edx*4] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 48409f: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esi + 0x9068u)) = m->edi;	/* 4840a3: mov dword ptr [esi + 0x9068], edi */
	M32((DWORD)(m->esi + 0x9084u)) = m->ebx;	/* 4840a9: mov dword ptr [esi + 0x9084], ebx */
	m->edx = (DWORD)(m->ebp + m->eax*2 + 0x0u);	/* 4840af: lea edx, [ebp + eax*2] */
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 4840b3: lea eax, [edi + edi*4] */
	m->edi = M32((DWORD)(m->esp + 0x2cu));	/* 4840b6: mov edi, dword ptr [esp + 0x2c] */
	m->ecx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 4840ba: lea ecx, [ecx + eax*4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4840bd: add eax, ecx */
	m->ecx = (DWORD)(m->ebx + m->ebx*8 + 0x0u);	/* 4840bf: lea ecx, [ebx + ebx*8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4840c2: add eax, edx */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4840c4: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4840c6: shl ecx, 2 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4840c9: test edi, edi */
	M32((DWORD)(m->esi + 0x4u)) = m->ecx;	/* 4840cb: mov dword ptr [esi + 4], ecx */
	if (!m->zf) goto L_4840ff;	/* 4840ce: jne 0x4840ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4840d0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4840d6u; native_call(m, 0x49f1aau);	/* 4840d1: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4840d6: add esp, 4 */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 4840d9: mov dword ptr [esi + 8], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4840dc: test eax, eax */
	if (!m->zf) goto L_4840f6;	/* 4840de: jne 0x4840f6 */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 4840e0: mov edx, dword ptr [esi + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4840e3: push edx */
	{ DWORD v_ = 0x4c4cecu; m->esp -= 4; M32(m->esp) = v_; }	/* 4840e4: push 0x4c4cec */
	{ DWORD v_ = 0xae2ef0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4840e9: push 0xae2ef0 */
	m->esp -= 4; M32(m->esp) = 0x4840f3u; native_call(m, 0x46c710u);	/* 4840ee: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4840f3: add esp, 0xc */
L_4840f6:
	M32((DWORD)(m->esi + 0xcu)) = 0x1u;	/* 4840f6: mov dword ptr [esi + 0xc], 1 */
	goto L_48411e;	/* 4840fd: jmp 0x48411e */
L_4840ff:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4840ff: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 484103: cmp eax, ecx */
	if (m->sf == m->of) goto L_48411b;	/* 484105: jge 0x48411b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 484107: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 484108: push ecx */
	{ DWORD v_ = 0x4c4cbcu; m->esp -= 4; M32(m->esp) = v_; }	/* 484109: push 0x4c4cbc */
	{ DWORD v_ = 0xae2ef0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48410e: push 0xae2ef0 */
	m->esp -= 4; M32(m->esp) = 0x484118u; native_call(m, 0x46c710u);	/* 484113: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 484118: add esp, 0x10 */
L_48411b:
	M32((DWORD)(m->esi + 0x8u)) = m->edi;	/* 48411b: mov dword ptr [esi + 8], edi */
L_48411e:
	m->edx = M32((DWORD)(m->esi + 0x9030u));	/* 48411e: mov edx, dword ptr [esi + 0x9030] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 484124: mov eax, dword ptr [esi + 8] */
	M32((DWORD)(m->esi + 0x9034u)) = m->eax;	/* 484127: mov dword ptr [esi + 0x9034], eax */
	m->ecx = (DWORD)(m->edx*8 + 0x0u);	/* 48412d: lea ecx, [edx*8] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 484134: sub ecx, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 484136: shl ecx, 2 */
	m->edx = (DWORD)(m->eax + m->ecx*1 + 0x0u);	/* 484139: lea edx, [eax + ecx] */
	M32((DWORD)(m->esi + 0x9040u)) = m->edx;	/* 48413c: mov dword ptr [esi + 0x9040], edx */
	m->edx = M32((DWORD)(m->esi + 0x903cu));	/* 484142: mov edx, dword ptr [esi + 0x903c] */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 484148: shl edx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48414b: add ecx, edx */
	m->edx = (DWORD)(m->eax + m->ecx*1 + 0x0u);	/* 48414d: lea edx, [eax + ecx] */
	M32((DWORD)(m->esi + 0x904cu)) = m->edx;	/* 484150: mov dword ptr [esi + 0x904c], edx */
	m->edx = M32((DWORD)(m->esi + 0x9048u));	/* 484156: mov edx, dword ptr [esi + 0x9048] */
	m->ecx = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 48415c: lea ecx, [ecx + edx*4] */
	m->edx = (DWORD)(m->eax + m->ecx*1 + 0x0u);	/* 48415f: lea edx, [eax + ecx] */
	M32((DWORD)(m->esi + 0x9058u)) = m->edx;	/* 484162: mov dword ptr [esi + 0x9058], edx */
	m->edx = M32((DWORD)(m->esi + 0x9054u));	/* 484168: mov edx, dword ptr [esi + 0x9054] */
	m->edi = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 48416e: lea edi, [edx + edx*2] */
	{ DWORD a_ = m->edi, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 484171: shl edi, 5 */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 484174: add ecx, edi */
	m->edx = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 484176: lea edx, [ecx + edx*8] */
	m->edi = (DWORD)(m->eax + m->ecx*1 + 0x0u);	/* 484179: lea edi, [eax + ecx] */
	M32((DWORD)(m->esi + 0x9060u)) = m->edi;	/* 48417c: mov dword ptr [esi + 0x9060], edi */
	m->ecx = (DWORD)(m->eax + m->edx*1 + 0x0u);	/* 484182: lea ecx, [eax + edx] */
	M32((DWORD)(m->esi + 0x906cu)) = m->ecx;	/* 484185: mov dword ptr [esi + 0x906c], ecx */
	m->ecx = M32((DWORD)(m->esi + 0x9068u));	/* 48418b: mov ecx, dword ptr [esi + 0x9068] */
	m->edi = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 484191: lea edi, [ecx + ecx*2] */
	{ DWORD a_ = m->edi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 484194: shl edi, 3 */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 484197: sub edi, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 484199: shl ecx, 3 */
	m->edx = (DWORD)(m->edx + m->edi*4 + 0x0u);	/* 48419c: lea edx, [edx + edi*4] */
	m->edi = (DWORD)(m->eax + m->edx*1 + 0x0u);	/* 48419f: lea edi, [eax + edx] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4841a2: add edx, ecx */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4841a4: add ecx, eax */
	M32((DWORD)(m->esi + 0x9074u)) = m->edi;	/* 4841a6: mov dword ptr [esi + 0x9074], edi */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4841ac: add ecx, edx */
	m->edi = (DWORD)(m->eax + m->edx*1 + 0x0u);	/* 4841ae: lea edi, [eax + edx] */
	M32((DWORD)(m->esi + 0x9088u)) = m->ecx;	/* 4841b1: mov dword ptr [esi + 0x9088], ecx */
	m->ecx = m->esi;	/* 4841b7: mov ecx, esi */
	M32((DWORD)(m->esi + 0x907cu)) = m->edi;	/* 4841b9: mov dword ptr [esi + 0x907c], edi */
	m->esp -= 4; M32(m->esp) = 0x4841c4u; native_call(m, 0x4841d0u);	/* 4841bf: call 0x4841d0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4841c4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4841c5: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4841c6: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4841c7: pop ebx */
	m->esp += 4 + 32; return;	/* 4841c8: ret 0x20 */
}

/* texSmall_initBy (0x4569d0), lifted by tools/lift.py */
static void lift_4569d0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4569d0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4569d1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4569d2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4569d3: push edi */
	m->esi = m->ecx;	/* 4569d4: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x4569dbu; native_call(m, 0x4569b0u);	/* 4569d6: call 0x4569b0 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4569db: mov ecx, dword ptr [esp + 0x14] */
	m->ebx = 0x40u;	/* 4569df: mov ebx, 0x40 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4569e4: test ecx, ecx */
	if (m->zf) goto L_456a14;	/* 4569e6: je 0x456a14 */
	m->eax = M32((DWORD)(m->ecx + 0xc0118u));	/* 4569e8: mov eax, dword ptr [ecx + 0xc0118] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4569ee: cmp eax, ebx */
	if (!m->zf) goto L_4569fa;	/* 4569f0: jne 0x4569fa */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0xc011cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4569f2: cmp dword ptr [ecx + 0xc011c], ebx */
	if (m->zf) goto L_456a14;	/* 4569f8: je 0x456a14 */
L_4569fa:
	m->ecx = M32((DWORD)(m->ecx + 0xc011cu));	/* 4569fa: mov ecx, dword ptr [ecx + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456a00: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456a01: push eax */
	{ DWORD v_ = 0x4b4278u; m->esp -= 4; M32(m->esp) = v_; }	/* 456a02: push 0x4b4278 */
	{ DWORD v_ = 0xa0e000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456a07: push 0xa0e000 */
	m->esp -= 4; M32(m->esp) = 0x456a11u; native_call(m, 0x46c710u);	/* 456a0c: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456a11: add esp, 0x10 */
L_456a14:
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 456a14: mov ecx, dword ptr [esp + 0x18] */
	m->edi = 0x80u;	/* 456a18: mov edi, 0x80 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456a1d: test ecx, ecx */
	if (m->zf) goto L_456a4d;	/* 456a1f: je 0x456a4d */
	m->eax = M32((DWORD)(m->ecx + 0xc0118u));	/* 456a21: mov eax, dword ptr [ecx + 0xc0118] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456a27: cmp eax, edi */
	if (!m->zf) goto L_456a33;	/* 456a29: jne 0x456a33 */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0xc011cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456a2b: cmp dword ptr [ecx + 0xc011c], ebx */
	if (m->zf) goto L_456a4d;	/* 456a31: je 0x456a4d */
L_456a33:
	m->edx = M32((DWORD)(m->ecx + 0xc011cu));	/* 456a33: mov edx, dword ptr [ecx + 0xc011c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456a39: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456a3a: push eax */
	{ DWORD v_ = 0x4b423cu; m->esp -= 4; M32(m->esp) = v_; }	/* 456a3b: push 0x4b423c */
	{ DWORD v_ = 0xa0e000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456a40: push 0xa0e000 */
	m->esp -= 4; M32(m->esp) = 0x456a4au; native_call(m, 0x46c710u);	/* 456a45: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456a4a: add esp, 0x10 */
L_456a4d:
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 456a4d: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456a51: test ecx, ecx */
	if (m->zf) goto L_456a84;	/* 456a53: je 0x456a84 */
	m->eax = M32((DWORD)(m->ecx + 0xc0118u));	/* 456a55: mov eax, dword ptr [ecx + 0xc0118] */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456a5b: cmp eax, 0x100 */
	if (!m->zf) goto L_456a6a;	/* 456a60: jne 0x456a6a */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0xc011cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456a62: cmp dword ptr [ecx + 0xc011c], ebx */
	if (m->zf) goto L_456a84;	/* 456a68: je 0x456a84 */
L_456a6a:
	m->ecx = M32((DWORD)(m->ecx + 0xc011cu));	/* 456a6a: mov ecx, dword ptr [ecx + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456a70: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456a71: push eax */
	{ DWORD v_ = 0x4b4200u; m->esp -= 4; M32(m->esp) = v_; }	/* 456a72: push 0x4b4200 */
	{ DWORD v_ = 0xa0e000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456a77: push 0xa0e000 */
	m->esp -= 4; M32(m->esp) = 0x456a81u; native_call(m, 0x46c710u);	/* 456a7c: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456a81: add esp, 0x10 */
L_456a84:
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 456a84: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456a88: test ebp, ebp */
	if (m->zf) goto L_456ab8;	/* 456a8a: je 0x456ab8 */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 456a8c: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456a92: cmp eax, edi */
	if (!m->zf) goto L_456a9e;	/* 456a94: jne 0x456a9e */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xc011cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456a96: cmp dword ptr [ebp + 0xc011c], edi */
	if (m->zf) goto L_456ab8;	/* 456a9c: je 0x456ab8 */
L_456a9e:
	m->edx = M32((DWORD)(m->ebp + 0xc011cu));	/* 456a9e: mov edx, dword ptr [ebp + 0xc011c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456aa4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456aa5: push eax */
	{ DWORD v_ = 0x4b41c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 456aa6: push 0x4b41c4 */
	{ DWORD v_ = 0xa0e000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456aab: push 0xa0e000 */
	m->esp -= 4; M32(m->esp) = 0x456ab5u; native_call(m, 0x46c710u);	/* 456ab0: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456ab5: add esp, 0x10 */
L_456ab8:
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 456ab8: mov ebx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456abc: test ebx, ebx */
	if (m->zf) goto L_456aef;	/* 456abe: je 0x456aef */
	m->eax = M32((DWORD)(m->ebx + 0xc0118u));	/* 456ac0: mov eax, dword ptr [ebx + 0xc0118] */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456ac6: cmp eax, 0x100 */
	if (!m->zf) goto L_456ad5;	/* 456acb: jne 0x456ad5 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0xc011cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456acd: cmp dword ptr [ebx + 0xc011c], edi */
	if (m->zf) goto L_456aef;	/* 456ad3: je 0x456aef */
L_456ad5:
	m->ecx = M32((DWORD)(m->ebx + 0xc011cu));	/* 456ad5: mov ecx, dword ptr [ebx + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456adb: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456adc: push eax */
	{ DWORD v_ = 0x4b4188u; m->esp -= 4; M32(m->esp) = v_; }	/* 456add: push 0x4b4188 */
	{ DWORD v_ = 0xa0e000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456ae2: push 0xa0e000 */
	m->esp -= 4; M32(m->esp) = 0x456aecu; native_call(m, 0x46c710u);	/* 456ae7: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456aec: add esp, 0x10 */
L_456aef:
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 456aef: mov edi, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456af3: test edi, edi */
	if (m->zf) goto L_456b26;	/* 456af5: je 0x456b26 */
	m->eax = M32((DWORD)(m->edi + 0xc0118u));	/* 456af7: mov eax, dword ptr [edi + 0xc0118] */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456afd: cmp eax, 0x100 */
	if (!m->zf) goto L_456b0c;	/* 456b02: jne 0x456b0c */
	{ DWORD a_ = M32((DWORD)(m->edi + 0xc011cu)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456b04: cmp dword ptr [edi + 0xc011c], eax */
	if (m->zf) goto L_456b26;	/* 456b0a: je 0x456b26 */
L_456b0c:
	m->edx = M32((DWORD)(m->edi + 0xc011cu));	/* 456b0c: mov edx, dword ptr [edi + 0xc011c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456b12: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456b13: push eax */
	{ DWORD v_ = 0x4b414cu; m->esp -= 4; M32(m->esp) = v_; }	/* 456b14: push 0x4b414c */
	{ DWORD v_ = 0xa0e000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456b19: push 0xa0e000 */
	m->esp -= 4; M32(m->esp) = 0x456b23u; native_call(m, 0x46c710u);	/* 456b1e: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456b23: add esp, 0x10 */
L_456b26:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 456b26: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 456b2a: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 456b2e: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esi + 0x18u)) = m->edi;	/* 456b32: mov dword ptr [esi + 0x18], edi */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 456b35: mov dword ptr [esi + 4], eax */
	M32((DWORD)(m->esi + 0x8u)) = m->ecx;	/* 456b38: mov dword ptr [esi + 8], ecx */
	M32((DWORD)(m->esi + 0xcu)) = m->edx;	/* 456b3b: mov dword ptr [esi + 0xc], edx */
	M32((DWORD)(m->esi + 0x10u)) = m->ebp;	/* 456b3e: mov dword ptr [esi + 0x10], ebp */
	M32((DWORD)(m->esi + 0x14u)) = m->ebx;	/* 456b41: mov dword ptr [esi + 0x14], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 456b44: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 456b45: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 456b46: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 456b47: pop ebx */
	m->esp += 4 + 24; return;	/* 456b48: ret 0x18 */
}

/* skel_loadFrom_46aa10 (0x46aa10), lifted by tools/lift.py */
static void lift_46aa10(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa10: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa11: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa12: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa13: push edi */
	m->edi = m->ecx;	/* 46aa14: mov edi, ecx */
	m->esp -= 4; M32(m->esp) = 0x46aa1bu; native_call(m, 0x4699a0u);	/* 46aa16: call 0x4699a0 */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 46aa1b: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa1f: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa20: push 1 */
	{ DWORD v_ = 0x24u; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa22: push 0x24 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa24: push edi */
	m->esp -= 4; M32(m->esp) = 0x46aa2au; native_call(m, 0x49e836u);	/* 46aa25: call 0x49e836 */
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 46aa2a: mov esi, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 46aa2e: mov eax, dword ptr [edi + 4] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 46aa31: xor ebp, ebp */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46aa33: add esp, 0x10 */
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46aa36: cmp esi, ebp */
	if (!m->zf) goto L_46aa69;	/* 46aa38: jne 0x46aa69 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa3a: push eax */
	m->esp -= 4; M32(m->esp) = 0x46aa40u; native_call(m, 0x49f1aau);	/* 46aa3b: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46aa40: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46aa43: cmp eax, ebp */
	M32((DWORD)(m->edi + 0x8u)) = m->eax;	/* 46aa45: mov dword ptr [edi + 8], eax */
	if (!m->zf) goto L_46aa60;	/* 46aa48: jne 0x46aa60 */
	m->ecx = M32((DWORD)(m->edi + 0x4u));	/* 46aa4a: mov ecx, dword ptr [edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa4d: push ecx */
	{ DWORD v_ = 0x4c4becu; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa4e: push 0x4c4bec */
	{ DWORD v_ = 0xa0eaa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa53: push 0xa0eaa8 */
	m->esp -= 4; M32(m->esp) = 0x46aa5du; native_call(m, 0x46c710u);	/* 46aa58: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46aa5d: add esp, 0xc */
L_46aa60:
	M32((DWORD)(m->edi + 0xcu)) = 0x1u;	/* 46aa60: mov dword ptr [edi + 0xc], 1 */
	goto L_46aa8b;	/* 46aa67: jmp 0x46aa8b */
L_46aa69:
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 46aa69: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46aa6d: cmp ecx, eax */
	if (m->sf == m->of) goto L_46aa85;	/* 46aa6f: jge 0x46aa85 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa71: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa72: push eax */
	{ DWORD v_ = 0x4c4b08u; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa73: push 0x4c4b08 */
	{ DWORD v_ = 0xa0eaa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa78: push 0xa0eaa8 */
	m->esp -= 4; M32(m->esp) = 0x46aa82u; native_call(m, 0x46c710u);	/* 46aa7d: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46aa82: add esp, 0x10 */
L_46aa85:
	M32((DWORD)(m->edi + 0x8u)) = m->esi;	/* 46aa85: mov dword ptr [edi + 8], esi */
	M32((DWORD)(m->edi + 0xcu)) = m->ebp;	/* 46aa88: mov dword ptr [edi + 0xc], ebp */
L_46aa8b:
	m->edx = M32((DWORD)(m->edi + 0x10u));	/* 46aa8b: mov edx, dword ptr [edi + 0x10] */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 46aa8e: mov eax, dword ptr [edi + 8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa91: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa92: push edx */
	{ DWORD v_ = 0x70u; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa93: push 0x70 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46aa95: push eax */
	M32((DWORD)(m->edi + 0x14u)) = m->eax;	/* 46aa96: mov dword ptr [edi + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x46aa9eu; native_call(m, 0x49e836u);	/* 46aa99: call 0x49e836 */
	m->eax = M32((DWORD)(m->edi + 0x10u));	/* 46aa9e: mov eax, dword ptr [edi + 0x10] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46aaa1: add esp, 0x10 */
	m->ebx = (DWORD)(m->eax*8 + 0x0u);	/* 46aaa4: lea ebx, [eax*8] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46aaab: sub ebx, eax */
	{ DWORD a_ = m->ebx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 46aaad: shl ebx, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46aab0: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_46ab23;	/* 46aab2: jle 0x46ab23 */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 46aab4: mov dword ptr [esp + 0x18], ebp */
L_46aab8:
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 46aab8: mov esi, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->edi + 0x14u));	/* 46aabc: mov edx, dword ptr [edi + 0x14] */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 46aabf: mov ecx, dword ptr [edi + 8] */
	m->eax = m->ebx;	/* 46aac2: mov eax, ebx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46aac4: add esi, edx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46aac6: add eax, ecx */
	M32((DWORD)(m->esi + 0x64u)) = m->eax;	/* 46aac8: mov dword ptr [esi + 0x64], eax */
	m->eax = M32((DWORD)(m->esi + 0x60u));	/* 46aacb: mov eax, dword ptr [esi + 0x60] */
	m->ecx = m->eax;	/* 46aace: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46aad0: shl ecx, 5 */
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46aad3: add ebx, ecx */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 46aad5: mov ecx, dword ptr [edi + 8] */
	m->edx = m->ebx;	/* 46aad8: mov edx, ebx */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46aada: add edx, ecx */
	m->ecx = M32((DWORD)(m->esi + 0x68u));	/* 46aadc: mov ecx, dword ptr [esi + 0x68] */
	M32((DWORD)(m->esi + 0x6cu)) = m->edx;	/* 46aadf: mov dword ptr [esi + 0x6c], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46aae2: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46aae6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46aae7: push eax */
	m->eax = M32((DWORD)(m->esi + 0x64u));	/* 46aae8: mov eax, dword ptr [esi + 0x64] */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 46aaeb: lea ecx, [ecx + ecx*4] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 46aaee: push 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46aaf0: push eax */
	m->ebx = (DWORD)(m->ebx + m->ecx*8 + 0x0u);	/* 46aaf1: lea ebx, [ebx + ecx*8] */
	m->esp -= 4; M32(m->esp) = 0x46aaf9u; native_call(m, 0x49e836u);	/* 46aaf4: call 0x49e836 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 46aaf9: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esi + 0x68u));	/* 46aafd: mov edx, dword ptr [esi + 0x68] */
	m->eax = M32((DWORD)(m->esi + 0x6cu));	/* 46ab00: mov eax, dword ptr [esi + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab03: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab04: push edx */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab05: push 0x28 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab07: push eax */
	m->esp -= 4; M32(m->esp) = 0x46ab0du; native_call(m, 0x49e836u);	/* 46ab08: call 0x49e836 */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 46ab0d: mov ecx, dword ptr [esp + 0x38] */
	m->eax = M32((DWORD)(m->edi + 0x10u));	/* 46ab11: mov eax, dword ptr [edi + 0x10] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ab14: add esp, 0x20 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 46ab17: inc ebp */
	{ DWORD a_ = m->ecx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46ab18: add ecx, 0x70 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ab1b: cmp ebp, eax */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 46ab1d: mov dword ptr [esp + 0x18], ecx */
	if (m->sf != m->of) goto L_46aab8;	/* 46ab21: jl 0x46aab8 */
L_46ab23:
	m->edi = M32(m->esp); m->esp += 4;	/* 46ab23: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46ab24: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46ab25: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46ab26: pop ebx */
	m->esp += 4 + 12; return;	/* 46ab27: ret 0xc */
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
