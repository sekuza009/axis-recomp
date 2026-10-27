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

static void lift_40b420(X86 *m);
static void lift_43bcb0(X86 *m);
static void lift_419000(X86 *m);

/* armc_snapshot (0x419000), lifted by tools/lift.py */
static void lift_419000(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419000: sub esp, 0xc0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419006: or ecx, 0xffffffff */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419009: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0xc8u));	/* 41900a: mov ebx, dword ptr [esp + 0xc8] */
	m->eax = m->ebx;	/* 419011: mov eax, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 419013: push edi */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 419014: shl eax, 7 */
	m->edx = (DWORD)(m->eax + 0x4dbe50u);	/* 419017: lea edx, [eax + 0x4dbe50] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41901d: xor eax, eax */
	m->edi = m->edx;	/* 41901f: mov edi, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419021: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419023: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 419025: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419026: cmp ecx, 1 */
	if (!m->cf && !m->zf) goto L_419039;	/* 419029: ja 0x419039 */
	m->edi = M32(m->esp); m->esp += 4;	/* 41902b: pop edi */
	M32((DWORD)(0x4dcc64u)) = m->eax;	/* 41902c: mov dword ptr [0x4dcc64], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 419031: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419032: add esp, 0xc0 */
	m->esp += 4 + 0; return;	/* 419038: ret  */
L_419039:
	m->ecx = 0x20u;	/* 419039: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41903e: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x8u);	/* 419040: lea edi, [esp + 8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419044: push ebp */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419045: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419047: or ecx, 0xffffffff */
	m->edi = 0x4b036cu;	/* 41904a: mov edi, 0x4b036c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41904f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419051: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419053: sub edi, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 419055: push esi */
	m->eax = m->ecx;	/* 419056: mov eax, ecx */
	m->ebp = (DWORD)(m->esp + 0x10u);	/* 419058: lea ebp, [esp + 0x10] */
	m->esi = m->edi;	/* 41905c: mov esi, edi */
	m->edi = m->ebp;	/* 41905e: mov edi, ebp */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419060: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419063: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 419065: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419067: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419069: and ecx, 3 */
	m->ebp = (DWORD)(m->esp + 0x10u);	/* 41906c: lea ebp, [esp + 0x10] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419070: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419072: or ecx, 0xffffffff */
	m->edi = m->edx;	/* 419075: mov edi, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419077: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419079: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41907b: sub edi, ecx */
	m->edx = m->ecx;	/* 41907d: mov edx, ecx */
	m->esi = m->edi;	/* 41907f: mov esi, edi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419081: or ecx, 0xffffffff */
	m->edi = m->ebp;	/* 419084: mov edi, ebp */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419086: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 419088: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41908a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41908b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41908e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 419090: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 419092: lea edx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419096: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419099: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4ad564u;	/* 41909b: mov edi, 0x4ad564 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4190a0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4190a3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4190a5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4190a7: sub edi, ecx */
	m->esi = m->edi;	/* 4190a9: mov esi, edi */
	m->ebp = m->ecx;	/* 4190ab: mov ebp, ecx */
	m->edi = m->edx;	/* 4190ad: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4190af: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4190b2: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 4190b4: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4190b6: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4190b7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4190ba: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 4190bc: mov ecx, ebp */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 4190be: lea edx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4190c2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4190c5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0360u;	/* 4190c7: mov edi, 0x4b0360 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4190cc: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4190cf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4190d1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4190d3: sub edi, ecx */
	m->esi = m->edi;	/* 4190d5: mov esi, edi */
	m->ebp = m->ecx;	/* 4190d7: mov ebp, ecx */
	m->edi = m->edx;	/* 4190d9: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4190db: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4190de: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 4190e0: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4190e2: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4190e3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4190e6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 4190e8: mov ecx, ebp */
	m->edx = (DWORD)(m->esp + 0x90u);	/* 4190ea: lea edx, [esp + 0x90] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4190f1: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4190f4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 4190f6: lea edi, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4190fa: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4190fd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4190ff: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419101: sub edi, ecx */
	m->eax = m->ecx;	/* 419103: mov eax, ecx */
	m->esi = m->edi;	/* 419105: mov esi, edi */
	m->edi = m->edx;	/* 419107: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419109: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41910b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41910e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 419110: mov ecx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419112: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419114: push 0 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419116: and ecx, 3 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419119: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41911b: push 0 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41911d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 41911f: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419125: push 0 */
	m->edx = (DWORD)(m->esp + 0xa8u);	/* 419127: lea edx, [esp + 0xa8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41912e: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419130: push edx */
	m->esp -= 4; M32(m->esp) = 0x419136u; native_call(m, 0x456be0u);	/* 419131: call 0x456be0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 419136: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 419137: pop ebp */
	M32((DWORD)(m->ebx*4 + 0x4dcc70u)) = m->eax;	/* 419138: mov dword ptr [ebx*4 + 0x4dcc70], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 41913f: pop edi */
	M32((DWORD)(0x4dcc64u)) = 0x0u;	/* 419140: mov dword ptr [0x4dcc64], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41914a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41914b: add esp, 0xc0 */
	m->esp += 4 + 0; return;	/* 419151: ret  */
}

/* arena_40b420 (0x40b420), lifted by tools/lift.py */
static void lift_40b420(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b420: sub esp, 0xc0 */
	m->ecx = 0x20u;	/* 40b426: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40b42b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 40b42d: lea edx, [esp] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b431: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40b432: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b433: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b434: push edi */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 40b435: lea edi, [esp + 0x10] */
	m->ebx = (DWORD)(m->esp + 0x10u);	/* 40b439: lea ebx, [esp + 0x10] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40b43d: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b43f: or ecx, 0xffffffff */
	m->edi = 0x680bc4u;	/* 40b442: mov edi, 0x680bc4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b447: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40b449: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40b44b: sub edi, ecx */
	m->eax = m->ecx;	/* 40b44d: mov eax, ecx */
	m->esi = m->edi;	/* 40b44f: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40b451: shr ecx, 2 */
	m->edi = m->edx;	/* 40b454: mov edi, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40b456: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 40b458: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40b45a: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b45c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40b45f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4db548u)));	/* 40b461: movsx ecx, byte ptr [0x4db548] */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40b468: shl ecx, 5 */
	m->edx = (DWORD)(m->ecx + 0x907b30u);	/* 40b46b: lea edx, [ecx + 0x907b30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b471: or ecx, 0xffffffff */
	m->edi = m->edx;	/* 40b474: mov edi, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b476: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40b478: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40b47a: sub edi, ecx */
	m->ebp = m->ecx;	/* 40b47c: mov ebp, ecx */
	m->esi = m->edi;	/* 40b47e: mov esi, edi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b480: or ecx, 0xffffffff */
	m->edi = m->ebx;	/* 40b483: mov edi, ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b485: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 40b487: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 40b489: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40b48a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40b48d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 40b48f: mov ecx, ebp */
	m->ebx = (DWORD)(m->esp + 0x10u);	/* 40b491: lea ebx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b495: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40b498: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4ad564u;	/* 40b49a: mov edi, 0x4ad564 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b49f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b4a2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40b4a4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40b4a6: sub edi, ecx */
	m->esi = m->edi;	/* 40b4a8: mov esi, edi */
	m->ebp = m->ecx;	/* 40b4aa: mov ebp, ecx */
	m->edi = m->ebx;	/* 40b4ac: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b4ae: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b4b1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 40b4b3: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 40b4b5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40b4b6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40b4b9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 40b4bb: mov ecx, ebp */
	m->ebx = (DWORD)(m->esp + 0x10u);	/* 40b4bd: lea ebx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b4c1: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40b4c4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 40b4c6: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b4c8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b4cb: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40b4cd: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40b4cf: sub edi, ecx */
	m->esi = m->edi;	/* 40b4d1: mov esi, edi */
	m->edx = m->ecx;	/* 40b4d3: mov edx, ecx */
	m->edi = m->ebx;	/* 40b4d5: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b4d7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b4da: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 40b4dc: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 40b4de: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40b4df: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40b4e2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 40b4e4: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b4e6: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40b4e9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 40b4eb: lea edi, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b4ef: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40b4f2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40b4f4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40b4f6: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x90u);	/* 40b4f8: lea edx, [esp + 0x90] */
	m->eax = m->ecx;	/* 40b4ff: mov eax, ecx */
	m->esi = m->edi;	/* 40b501: mov esi, edi */
	m->edi = m->edx;	/* 40b503: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b505: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40b507: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40b50a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 40b50c: mov ecx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b50e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b510: push 0 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b512: and ecx, 3 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b515: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b517: push 0 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40b519: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 40b51b: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b521: push 0 */
	m->edx = (DWORD)(m->esp + 0xa8u);	/* 40b523: lea edx, [esp + 0xa8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b52a: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b52c: push edx */
	m->esp -= 4; M32(m->esp) = 0x40b532u; native_call(m, 0x456be0u);	/* 40b52d: call 0x456be0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40b532: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40b533: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40b534: pop ebp */
	M32((DWORD)(0x9da324u)) = m->eax;	/* 40b535: mov dword ptr [0x9da324], eax */
	M32((DWORD)(0x680cd0u)) = 0x0u;	/* 40b53a: mov dword ptr [0x680cd0], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40b544: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b545: add esp, 0xc0 */
	m->esp += 4 + 0; return;	/* 40b54b: ret  */
}

/* room_43bcb0 (0x43bcb0), lifted by tools/lift.py */
static void lift_43bcb0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bcb0: sub esp, 0xc0 */
	m->ecx = 0x20u;	/* 43bcb6: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43bcbb: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 43bcbd: lea edx, [esp] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bcc1: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43bcc2: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43bcc3: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43bcc4: push edi */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 43bcc5: lea edi, [esp + 0x10] */
	m->ebx = (DWORD)(m->esp + 0x10u);	/* 43bcc9: lea ebx, [esp + 0x10] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43bccd: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bccf: or ecx, 0xffffffff */
	m->edi = 0x680bc4u;	/* 43bcd2: mov edi, 0x680bc4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43bcd7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43bcd9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43bcdb: sub edi, ecx */
	m->eax = m->ecx;	/* 43bcdd: mov eax, ecx */
	m->esi = m->edi;	/* 43bcdf: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43bce1: shr ecx, 2 */
	m->edi = m->edx;	/* 43bce4: mov edi, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43bce6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43bce8: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43bcea: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bcec: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43bcef: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9e8u)));	/* 43bcf1: movsx ecx, byte ptr [0x4df9e8] */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43bcf8: shl ecx, 5 */
	m->edx = (DWORD)(m->ecx + 0x907b30u);	/* 43bcfb: lea edx, [ecx + 0x907b30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd01: or ecx, 0xffffffff */
	m->edi = m->edx;	/* 43bd04: mov edi, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43bd06: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43bd08: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43bd0a: sub edi, ecx */
	m->ebp = m->ecx;	/* 43bd0c: mov ebp, ecx */
	m->esi = m->edi;	/* 43bd0e: mov esi, edi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd10: or ecx, 0xffffffff */
	m->edi = m->ebx;	/* 43bd13: mov edi, ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43bd15: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 43bd17: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43bd19: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43bd1a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43bd1d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 43bd1f: mov ecx, ebp */
	m->ebx = (DWORD)(m->esp + 0x10u);	/* 43bd21: lea ebx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd25: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43bd28: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4ad564u;	/* 43bd2a: mov edi, 0x4ad564 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd2f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43bd32: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43bd34: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43bd36: sub edi, ecx */
	m->esi = m->edi;	/* 43bd38: mov esi, edi */
	m->ebp = m->ecx;	/* 43bd3a: mov ebp, ecx */
	m->edi = m->ebx;	/* 43bd3c: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd3e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43bd41: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 43bd43: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43bd45: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43bd46: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43bd49: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 43bd4b: mov ecx, ebp */
	m->ebx = (DWORD)(m->esp + 0x10u);	/* 43bd4d: lea ebx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd51: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43bd54: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 43bd56: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd58: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43bd5b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43bd5d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43bd5f: sub edi, ecx */
	m->esi = m->edi;	/* 43bd61: mov esi, edi */
	m->edx = m->ecx;	/* 43bd63: mov edx, ecx */
	m->edi = m->ebx;	/* 43bd65: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd67: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43bd6a: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 43bd6c: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43bd6e: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43bd6f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43bd72: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43bd74: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd76: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43bd79: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 43bd7b: lea edi, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bd7f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43bd82: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43bd84: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43bd86: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x90u);	/* 43bd88: lea edx, [esp + 0x90] */
	m->eax = m->ecx;	/* 43bd8f: mov eax, ecx */
	m->esi = m->edi;	/* 43bd91: mov esi, edi */
	m->edi = m->edx;	/* 43bd93: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bd95: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43bd97: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43bd9a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43bd9c: mov ecx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bd9e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bda0: push 0 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43bda2: and ecx, 3 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bda5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bda7: push 0 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43bda9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43bdab: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bdb1: push 0 */
	m->edx = (DWORD)(m->esp + 0xa8u);	/* 43bdb3: lea edx, [esp + 0xa8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bdba: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bdbc: push edx */
	m->esp -= 4; M32(m->esp) = 0x43bdc2u; native_call(m, 0x456be0u);	/* 43bdbd: call 0x456be0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43bdc2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43bdc3: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43bdc4: pop ebp */
	M32((DWORD)(0x9da324u)) = m->eax;	/* 43bdc5: mov dword ptr [0x9da324], eax */
	M32((DWORD)(0x680cd0u)) = 0x0u;	/* 43bdca: mov dword ptr [0x680cd0], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43bdd4: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bdd5: add esp, 0xc0 */
	m->esp += 4 + 0; return;	/* 43bddb: ret  */
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
