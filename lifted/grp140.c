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

static void lift_49ca70(X86 *m);
static void lift_4314e0(X86 *m);
static void lift_48fd50(X86 *m);
static void lift_49df10(X86 *m);

/* game_processGameModeInit (0x49df10), lifted by tools/lift.py */
static void lift_49df10(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49df10: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49df11: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49df12: push ebp */
	m->ebp = m->ecx;	/* 49df13: mov ebp, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49df15: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49df17: push esi */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9e8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49df18: cmp dword ptr [ebp + 0x233c9e8], ebx */
	if (!m->zf) goto L_49e419;	/* 49df1e: jne 0x49e419 */
	{ DWORD a_ = M32((DWORD)(0x5ae9c4u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49df24: cmp dword ptr [0x5ae9c4], 2 */
	if (!m->zf) goto L_49df3a;	/* 49df2b: jne 0x49df3a */
	m->ecx = 0x1u;	/* 49df2d: mov ecx, 1 */
	M32((DWORD)(m->ebp + 0x233c9f0u)) = m->ecx;	/* 49df32: mov dword ptr [ebp + 0x233c9f0], ecx */
	goto L_49df45;	/* 49df38: jmp 0x49df45 */
L_49df3a:
	M32((DWORD)(m->ebp + 0x233c9f0u)) = m->ebx;	/* 49df3a: mov dword ptr [ebp + 0x233c9f0], ebx */
	m->ecx = 0x1u;	/* 49df40: mov ecx, 1 */
L_49df45:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9f0u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49df45: cmp dword ptr [ebp + 0x233c9f0], ecx */
	if (!m->zf) goto L_49df6a;	/* 49df4b: jne 0x49df6a */
	M32((DWORD)(m->ebp + 0x233cc50u)) = 0x43960000u;	/* 49df4d: mov dword ptr [ebp + 0x233cc50], 0x43960000 */
	m->eax = M32((DWORD)(0x4de72au));	/* 49df57: mov eax, dword ptr [0x4de72a] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49df5c: inc eax */
	M32((DWORD)(0x4de72au)) = m->eax;	/* 49df5d: mov dword ptr [0x4de72a], eax */
	M32((DWORD)(m->ebp + 0x22e717cu)) = m->ecx;	/* 49df62: mov dword ptr [ebp + 0x22e717c], ecx */
	goto L_49df70;	/* 49df68: jmp 0x49df70 */
L_49df6a:
	M32((DWORD)(m->ebp + 0x22e717cu)) = m->ebx;	/* 49df6a: mov dword ptr [ebp + 0x22e717c], ebx */
L_49df70:
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 49df70: mov eax, dword ptr [ebp + 8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49df73: push edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49df74: cmp eax, ebx */
	if (!m->zf) goto L_49e002;	/* 49df76: jne 0x49e002 */
	M32((DWORD)(m->ebp + 0x1f1ca8u)) = m->ebx;	/* 49df7c: mov dword ptr [ebp + 0x1f1ca8], ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 49df82: xor esi, esi */
	m->eax = 0x9db9ecu;	/* 49df84: mov eax, 0x9db9ec */
L_49df89:
	m->ecx = M32((DWORD)(m->eax + 0xfffffff8u));	/* 49df89: mov ecx, dword ptr [eax - 8] */
	m->edx = M32((DWORD)(m->ebp + 0x1f1ca8u));	/* 49df8c: mov edx, dword ptr [ebp + 0x1f1ca8] */
	m->edi = M32((DWORD)(m->eax + 0xfffffffcu));	/* 49df92: mov edi, dword ptr [eax - 4] */
	m->ebx = M32((DWORD)(m->eax + 0x0u));	/* 49df95: mov ebx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 49df97: mov dword ptr [esp + 0x10], ecx */
	m->ecx = m->edx;	/* 49df9b: mov ecx, edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49df9d: shl ecx, 4 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 49dfa0: inc edx */
	{ DWORD a_ = m->eax, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49dfa1: add eax, 0x5c */
	m->ecx = (DWORD)(m->ecx + m->ebp*1 + 0x1f1668u);	/* 49dfa4: lea ecx, [ecx + ebp + 0x1f1668] */
	M32((DWORD)(m->ebp + 0x1f1ca8u)) = m->edx;	/* 49dfab: mov dword ptr [ebp + 0x1f1ca8], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 49dfb1: mov edx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ecx + 0x0u)) = m->esi;	/* 49dfb5: mov dword ptr [ecx], esi */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49dfb7: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x9dbf50u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49dfb8: cmp eax, 0x9dbf50 */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 49dfbd: mov dword ptr [ecx + 4], edx */
	M32((DWORD)(m->ecx + 0x8u)) = m->ebx;	/* 49dfc0: mov dword ptr [ecx + 8], ebx */
	M32((DWORD)(m->ecx + 0xcu)) = m->edi;	/* 49dfc3: mov dword ptr [ecx + 0xc], edi */
	if (m->sf != m->of) goto L_49df89;	/* 49dfc6: jl 0x49df89 */
	m->eax = M32((DWORD)(0x9dad94u));	/* 49dfc8: mov eax, dword ptr [0x9dad94] */
	m->edx = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 49dfcd: lea edx, [esi + esi*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49dfd0: shl edx, 3 */
	m->ecx = (DWORD)(m->esi + 0x1u);	/* 49dfd3: lea ecx, [esi + 1] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49dfd6: sub edx, esi */
	M32((DWORD)(m->ebp + 0x1f1cacu)) = m->eax;	/* 49dfd8: mov dword ptr [ebp + 0x1f1cac], eax */
	M32((DWORD)(m->ebp + 0x1f1cb4u)) = m->ecx;	/* 49dfde: mov dword ptr [ebp + 0x1f1cb4], ecx */
	m->eax = M32((DWORD)(m->edx*4 + 0x9dba40u));	/* 49dfe4: mov eax, dword ptr [edx*4 + 0x9dba40] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49dfeb: xor ebx, ebx */
	M32((DWORD)(m->ebp + 0x1f1cb8u)) = m->eax;	/* 49dfed: mov dword ptr [ebp + 0x1f1cb8], eax */
	M32((DWORD)(m->ebp + 0x1f1cb0u)) = 0x0u;	/* 49dff3: mov dword ptr [ebp + 0x1f1cb0], 0 */
	goto L_49e137;	/* 49dffd: jmp 0x49e137 */
L_49e002:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e002: cmp eax, ecx */
	if (!m->zf) goto L_49e125;	/* 49e004: jne 0x49e125 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e00a: cmp dword ptr [ebp + 4], ebx */
	if (!m->zf) goto L_49e125;	/* 49e00d: jne 0x49e125 */
	{ DWORD a_ = M32((DWORD)(0x9da3e0u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e013: cmp dword ptr [0x9da3e0], ecx */
	if (!m->zf) goto L_49e09a;	/* 49e019: jne 0x49e09a */
	M32((DWORD)(m->ebp + 0x1f1ca8u)) = m->ebx;	/* 49e01b: mov dword ptr [ebp + 0x1f1ca8], ebx */
	m->eax = M32((DWORD)(0x67ef00u));	/* 49e021: mov eax, dword ptr [0x67ef00] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 49e026: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e028: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_49e0cf;	/* 49e02a: jle 0x49e0cf */
	m->eax = 0x4d950cu;	/* 49e030: mov eax, 0x4d950c */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 49e035: mov dword ptr [esp + 0x10], eax */
L_49e039:
	{ DWORD a_ = M32((DWORD)(m->eax + 0xfffffffcu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e039: cmp dword ptr [eax - 4], ecx */
	if (!m->zf) goto L_49e086;	/* 49e03c: jne 0x49e086 */
	m->ebx = M32((DWORD)(0x76d368u));	/* 49e03e: mov ebx, dword ptr [0x76d368] */
	{ DWORD a_ = m->ebx, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e044: cmp ebx, 0xe */
	if (m->sf != m->of) goto L_49e04b;	/* 49e047: jl 0x49e04b */
	m->ebx = M32((DWORD)(m->eax + 0x0u));	/* 49e049: mov ebx, dword ptr [eax] */
L_49e04b:
	m->ecx = M32((DWORD)(m->ebp + 0x1f1ca8u));	/* 49e04b: mov ecx, dword ptr [ebp + 0x1f1ca8] */
	m->edx = M32((DWORD)(0x76d408u));	/* 49e051: mov edx, dword ptr [0x76d408] */
	m->esi = M32((DWORD)(0x4df8e8u));	/* 49e057: mov esi, dword ptr [0x4df8e8] */
	m->eax = m->ecx;	/* 49e05d: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49e05f: shl eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49e062: inc ecx */
	m->eax = (DWORD)(m->eax + m->ebp*1 + 0x1f1668u);	/* 49e063: lea eax, [eax + ebp + 0x1f1668] */
	M32((DWORD)(m->ebp + 0x1f1ca8u)) = m->ecx;	/* 49e06a: mov dword ptr [ebp + 0x1f1ca8], ecx */
	m->ecx = 0x1u;	/* 49e070: mov ecx, 1 */
	M32((DWORD)(m->eax + 0x0u)) = m->edi;	/* 49e075: mov dword ptr [eax], edi */
	M32((DWORD)(m->eax + 0x4u)) = m->ebx;	/* 49e077: mov dword ptr [eax + 4], ebx */
	M32((DWORD)(m->eax + 0x8u)) = m->esi;	/* 49e07a: mov dword ptr [eax + 8], esi */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 49e07d: mov dword ptr [eax + 0xc], edx */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49e080: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49e084: xor ebx, ebx */
L_49e086:
	m->edx = M32((DWORD)(0x67ef00u));	/* 49e086: mov edx, dword ptr [0x67ef00] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 49e08c: inc edi */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e08d: add eax, 8 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e090: cmp edi, edx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 49e092: mov dword ptr [esp + 0x10], eax */
	if (m->sf != m->of) goto L_49e039;	/* 49e096: jl 0x49e039 */
	goto L_49e0cf;	/* 49e098: jmp 0x49e0cf */
L_49e09a:
	M32((DWORD)(m->ebp + 0x1f1ca8u)) = m->ecx;	/* 49e09a: mov dword ptr [ebp + 0x1f1ca8], ecx */
	m->eax = M32((DWORD)(0x76d408u));	/* 49e0a0: mov eax, dword ptr [0x76d408] */
	m->ecx = M32((DWORD)(0x4df8e8u));	/* 49e0a5: mov ecx, dword ptr [0x4df8e8] */
	m->edx = M32((DWORD)(0x76d368u));	/* 49e0ab: mov edx, dword ptr [0x76d368] */
	m->esi = M32((DWORD)(0x9dad94u));	/* 49e0b1: mov esi, dword ptr [0x9dad94] */
	M32((DWORD)(m->ebp + 0x1f166cu)) = m->edx;	/* 49e0b7: mov dword ptr [ebp + 0x1f166c], edx */
	M32((DWORD)(m->ebp + 0x1f1668u)) = m->esi;	/* 49e0bd: mov dword ptr [ebp + 0x1f1668], esi */
	M32((DWORD)(m->ebp + 0x1f1670u)) = m->ecx;	/* 49e0c3: mov dword ptr [ebp + 0x1f1670], ecx */
	M32((DWORD)(m->ebp + 0x1f1674u)) = m->eax;	/* 49e0c9: mov dword ptr [ebp + 0x1f1674], eax */
L_49e0cf:
	M32((DWORD)(m->ebp + 0x1f1cacu)) = m->ebx;	/* 49e0cf: mov dword ptr [ebp + 0x1f1cac], ebx */
	m->ecx = M32((DWORD)(m->ebp + 0x1f1668u));	/* 49e0d5: mov ecx, dword ptr [ebp + 0x1f1668] */
	M32((DWORD)(0x9dad94u)) = m->ecx;	/* 49e0db: mov dword ptr [0x9dad94], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x1f1cacu));	/* 49e0e1: mov eax, dword ptr [ebp + 0x1f1cac] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49e0e7: inc eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49e0e8: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x1f1ca8u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49e0e9: idiv dword ptr [ebp + 0x1f1ca8] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49e0ef: shl edx, 4 */
	m->edx = M32((DWORD)(m->edx + m->ebp*1 + 0x1f1668u));	/* 49e0f2: mov edx, dword ptr [edx + ebp + 0x1f1668] */
	M32((DWORD)(m->ebp + 0x1f1cb4u)) = m->edx;	/* 49e0f9: mov dword ptr [ebp + 0x1f1cb4], edx */
	m->eax = M32((DWORD)(m->ebp + 0x1f1cacu));	/* 49e0ff: mov eax, dword ptr [ebp + 0x1f1cac] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49e105: inc eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49e106: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x1f1ca8u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49e107: idiv dword ptr [ebp + 0x1f1ca8] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49e10d: shl edx, 4 */
	m->eax = M32((DWORD)(m->edx + m->ebp*1 + 0x1f166cu));	/* 49e110: mov eax, dword ptr [edx + ebp + 0x1f166c] */
	M32((DWORD)(m->ebp + 0x1f1cb8u)) = m->eax;	/* 49e117: mov dword ptr [ebp + 0x1f1cb8], eax */
	M32((DWORD)(m->ebp + 0x1f1cb0u)) = m->ebx;	/* 49e11d: mov dword ptr [ebp + 0x1f1cb0], ebx */
	goto L_49e137;	/* 49e123: jmp 0x49e137 */
L_49e125:
	M32((DWORD)(m->ebp + 0x1f1ca8u)) = m->ebx;	/* 49e125: mov dword ptr [ebp + 0x1f1ca8], ebx */
	M32((DWORD)(m->ebp + 0x1f1cacu)) = m->ebx;	/* 49e12b: mov dword ptr [ebp + 0x1f1cac], ebx */
	M32((DWORD)(m->ebp + 0x1f1cb0u)) = m->ecx;	/* 49e131: mov dword ptr [ebp + 0x1f1cb0], ecx */
L_49e137:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x1f1ca8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e137: cmp dword ptr [ebp + 0x1f1ca8], ebx */
	if (m->zf || m->sf != m->of) goto L_49e15b;	/* 49e13d: jle 0x49e15b */
	m->ecx = M32((DWORD)(m->ebp + 0x1f1cacu));	/* 49e13f: mov ecx, dword ptr [ebp + 0x1f1cac] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e145: shl ecx, 4 */
	m->edx = M32((DWORD)(m->ecx + m->ebp*1 + 0x1f166cu));	/* 49e148: mov edx, dword ptr [ecx + ebp + 0x1f166c] */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49e14f: lea ecx, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49e155: push edx */
	m->esp -= 4; M32(m->esp) = 0x49e15bu; native_call(m, 0x4732f0u);	/* 49e156: call 0x4732f0 */
L_49e15b:
	m->eax = M32((DWORD)(0x4df8e8u));	/* 49e15b: mov eax, dword ptr [0x4df8e8] */
	m->edi = 0x4dedd8u;	/* 49e160: mov edi, 0x4dedd8 */
	M32((DWORD)(m->ebp + 0x23423adu)) = m->eax;	/* 49e165: mov dword ptr [ebp + 0x23423ad], eax */
	m->ecx = M32((DWORD)(0x76d408u));	/* 49e16b: mov ecx, dword ptr [0x76d408] */
	M32((DWORD)(m->ebp + 0x23423b1u)) = m->ecx;	/* 49e171: mov dword ptr [ebp + 0x23423b1], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49e177: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49e17a: xor eax, eax */
	m->edx = (DWORD)(m->ebp + 0x2342429u);	/* 49e17c: lea edx, [ebp + 0x2342429] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 49e182: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 49e184: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49e186: sub edi, ecx */
	m->eax = m->ecx;	/* 49e188: mov eax, ecx */
	m->esi = m->edi;	/* 49e18a: mov esi, edi */
	m->edi = m->edx;	/* 49e18c: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e18e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 49e191: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 49e193: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49e195: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 49e198: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f1818u));	/* 49e19a: mov ecx, dword ptr [0x9f1818] */
	m->esi = 0x1u;	/* 49e1a0: mov esi, 1 */
	M32((DWORD)(m->ebp + 0x234243au)) = m->ecx;	/* 49e1a5: mov dword ptr [ebp + 0x234243a], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x233c9f0u));	/* 49e1ab: mov eax, dword ptr [ebp + 0x233c9f0] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e1b1: cmp eax, esi */
	if (!m->zf) goto L_49e1f0;	/* 49e1b3: jne 0x49e1f0 */
	m->edx = M32((DWORD)(0x4de722u));	/* 49e1b5: mov edx, dword ptr [0x4de722] */
	m->eax = m->edx;	/* 49e1bb: mov eax, edx */
	M32((DWORD)(m->ebp + 0x2342446u)) = m->edx;	/* 49e1bd: mov dword ptr [ebp + 0x2342446], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49e1c3: push eax */
	m->esp -= 4; M32(m->esp) = 0x49e1c9u; native_call(m, 0x4326f0u);	/* 49e1c4: call 0x4326f0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49e1c9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e1cc: cmp eax, esi */
	M32((DWORD)(m->ebp + 0x2342442u)) = m->eax;	/* 49e1ce: mov dword ptr [ebp + 0x2342442], eax */
	if (m->sf != m->of) goto L_49e1db;	/* 49e1d4: jl 0x49e1db */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e1d6: cmp eax, 0x14 */
	if (m->zf || m->sf != m->of) goto L_49e1fc;	/* 49e1d9: jle 0x49e1fc */
L_49e1db:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49e1db: push eax */
	{ DWORD v_ = 0x4d0710u; m->esp -= 4; M32(m->esp) = v_; }	/* 49e1dc: push 0x4d0710 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 49e1e1: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x49e1ebu; native_call(m, 0x46c710u);	/* 49e1e6: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49e1eb: add esp, 0xc */
	goto L_49e1fc;	/* 49e1ee: jmp 0x49e1fc */
L_49e1f0:
	M32((DWORD)(m->ebp + 0x2342446u)) = m->ebx;	/* 49e1f0: mov dword ptr [ebp + 0x2342446], ebx */
	M32((DWORD)(m->ebp + 0x2342442u)) = m->esi;	/* 49e1f6: mov dword ptr [ebp + 0x2342442], esi */
L_49e1fc:
	m->ecx = M32((DWORD)(0x4dc878u));	/* 49e1fc: mov ecx, dword ptr [0x4dc878] */
	M32((DWORD)(m->ebp + 0x234244au)) = m->ecx;	/* 49e202: mov dword ptr [ebp + 0x234244a], ecx */
	m->edx = M32((DWORD)(0x4dc87cu));	/* 49e208: mov edx, dword ptr [0x4dc87c] */
	M32((DWORD)(m->ebp + 0x234244eu)) = m->edx;	/* 49e20e: mov dword ptr [ebp + 0x234244e], edx */
	m->eax = M32((DWORD)(0x4dc880u));	/* 49e214: mov eax, dword ptr [0x4dc880] */
	M32((DWORD)(m->ebp + 0x2342452u)) = m->eax;	/* 49e219: mov dword ptr [ebp + 0x2342452], eax */
	m->ecx = M32((DWORD)(0x4dc884u));	/* 49e21f: mov ecx, dword ptr [0x4dc884] */
	M32((DWORD)(m->ebp + 0x2342456u)) = m->ecx;	/* 49e225: mov dword ptr [ebp + 0x2342456], ecx */
	m->edx = M32((DWORD)(0x4dc888u));	/* 49e22b: mov edx, dword ptr [0x4dc888] */
	M32((DWORD)(m->ebp + 0x234245au)) = m->edx;	/* 49e231: mov dword ptr [ebp + 0x234245a], edx */
	m->eax = M32((DWORD)(0x4dcf20u));	/* 49e237: mov eax, dword ptr [0x4dcf20] */
	M32((DWORD)(m->ebp + 0x234245eu)) = m->eax;	/* 49e23c: mov dword ptr [ebp + 0x234245e], eax */
	m->ecx = M32((DWORD)(0x4dcf24u));	/* 49e242: mov ecx, dword ptr [0x4dcf24] */
	M32((DWORD)(m->ebp + 0x2342462u)) = m->ecx;	/* 49e248: mov dword ptr [ebp + 0x2342462], ecx */
	m->edx = M32((DWORD)(0x4dcf28u));	/* 49e24e: mov edx, dword ptr [0x4dcf28] */
	M32((DWORD)(m->ebp + 0x2342466u)) = m->edx;	/* 49e254: mov dword ptr [ebp + 0x2342466], edx */
	m->eax = M32((DWORD)(0x4dcf2cu));	/* 49e25a: mov eax, dword ptr [0x4dcf2c] */
	M32((DWORD)(m->ebp + 0x234246au)) = m->eax;	/* 49e25f: mov dword ptr [ebp + 0x234246a], eax */
	m->ecx = M32((DWORD)(0x4dcf18u));	/* 49e265: mov ecx, dword ptr [0x4dcf18] */
	M32((DWORD)(m->ebp + 0x234246eu)) = m->ecx;	/* 49e26b: mov dword ptr [ebp + 0x234246e], ecx */
	m->edx = M32((DWORD)(0x4dcf1cu));	/* 49e271: mov edx, dword ptr [0x4dcf1c] */
	M32((DWORD)(m->ebp + 0x2342472u)) = m->edx;	/* 49e277: mov dword ptr [ebp + 0x2342472], edx */
	m->eax = 0x4dcfe4u;	/* 49e27d: mov eax, 0x4dcfe4 */
	m->ecx = (DWORD)(m->ebp + 0x234249eu);	/* 49e282: lea ecx, [ebp + 0x234249e] */
L_49e288:
	m->edx = M32((DWORD)(m->eax + 0xfffffffcu));	/* 49e288: mov edx, dword ptr [eax - 4] */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e28b: add eax, 0x18 */
	M32((DWORD)(m->ecx + 0xffffffd8u)) = m->edx;	/* 49e28e: mov dword ptr [ecx - 0x28], edx */
	m->edx = M32((DWORD)(m->eax + 0xffffffe8u));	/* 49e291: mov edx, dword ptr [eax - 0x18] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 49e294: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0xffffffecu));	/* 49e296: mov edx, dword ptr [eax - 0x14] */
	M32((DWORD)(m->ecx + 0x28u)) = m->edx;	/* 49e299: mov dword ptr [ecx + 0x28], edx */
	m->edx = M32((DWORD)(m->eax + 0xfffffff0u));	/* 49e29c: mov edx, dword ptr [eax - 0x10] */
	M32((DWORD)(m->ecx + 0xffffffdcu)) = m->edx;	/* 49e29f: mov dword ptr [ecx - 0x24], edx */
	m->edx = M32((DWORD)(m->eax + 0xfffffff4u));	/* 49e2a2: mov edx, dword ptr [eax - 0xc] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 49e2a5: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->eax + 0xfffffff8u));	/* 49e2a8: mov edx, dword ptr [eax - 8] */
	M32((DWORD)(m->ecx + 0x2cu)) = m->edx;	/* 49e2ab: mov dword ptr [ecx + 0x2c], edx */
	{ DWORD a_ = m->ecx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e2ae: add ecx, 8 */
	{ DWORD a_ = m->eax, b_ = 0x4dd05cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e2b1: cmp eax, 0x4dd05c */
	if (m->sf != m->of) goto L_49e288;	/* 49e2b6: jl 0x49e288 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e2b8: cmp dword ptr [ebp + 8], esi */
	if (!m->zf) goto L_49e3d6;	/* 49e2bb: jne 0x49e3d6 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e2c1: cmp dword ptr [ebp + 4], ebx */
	if (!m->zf) goto L_49e365;	/* 49e2c4: jne 0x49e365 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49e2ca: push esi */
	m->esp -= 4; M32(m->esp) = 0x49e2d0u; native_call(m, 0x4a8300u);	/* 49e2cb: call 0x4a8300 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49e2d0: add esp, 4 */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 49e2d3: lea esi, [ebp + 0x1f36c8] */
	m->ecx = m->esi;	/* 49e2d9: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x234240du)) = m->ebx;	/* 49e2db: mov dword ptr [ebp + 0x234240d], ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49e2e1: push ebx */
	m->esp -= 4; M32(m->esp) = 0x49e2e7u; native_call(m, 0x4743e0u);	/* 49e2e2: call 0x4743e0 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49e2e7: mov eax, dword ptr [ebp + 0x234240d] */
	m->edi = (DWORD)(m->ebp + 0x2342429u);	/* 49e2ed: lea edi, [ebp + 0x2342429] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49e2f3: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49e2f4: push eax */
	m->ecx = m->esi;	/* 49e2f5: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49e2fcu; native_call(m, 0x473940u);	/* 49e2f7: call 0x473940 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49e2fc: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49e302: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e304: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e307: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e309: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e30c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e30e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e311: add ecx, eax */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e313: cmp edi, ebx */
	m->edx = (DWORD)(m->ebp + m->ecx*8 + 0x1eccb08u);	/* 49e315: lea edx, [ebp + ecx*8 + 0x1eccb08] */
	if (m->zf) goto L_49e33d;	/* 49e31c: je 0x49e33d */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49e31e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49e321: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 49e323: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 49e325: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49e327: sub edi, ecx */
	m->eax = m->ecx;	/* 49e329: mov eax, ecx */
	m->esi = m->edi;	/* 49e32b: mov esi, edi */
	m->edi = m->edx;	/* 49e32d: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e32f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 49e332: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 49e334: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49e336: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 49e339: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_49e340;	/* 49e33b: jmp 0x49e340 */
L_49e33d:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 49e33d: mov byte ptr [edx], 0 */
L_49e340:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49e340: mov eax, dword ptr [ebp + 0x234240d] */
	m->esi = 0x1u;	/* 49e346: mov esi, 1 */
	m->ecx = m->eax;	/* 49e34b: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e34d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e350: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e352: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e355: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e357: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e35a: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb7cu)) = m->eax;	/* 49e35c: mov dword ptr [ebp + ecx*8 + 0x1eccb7c], eax */
	goto L_49e388;	/* 49e363: jmp 0x49e388 */
L_49e365:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49e365: push ebx */
	m->esp -= 4; M32(m->esp) = 0x49e36bu; native_call(m, 0x4a8300u);	/* 49e366: call 0x4a8300 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49e36b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49e36e: or eax, 0xffffffff */
	M32((DWORD)(m->ebp + 0x234240du)) = m->eax;	/* 49e371: mov dword ptr [ebp + 0x234240d], eax */
	M32((DWORD)(0x9dad94u)) = m->eax;	/* 49e377: mov dword ptr [0x9dad94], eax */
	M32((DWORD)(m->ebp + 0x1f1cb4u)) = m->eax;	/* 49e37c: mov dword ptr [ebp + 0x1f1cb4], eax */
	M32((DWORD)(m->ebp + 0x1f1cb8u)) = m->eax;	/* 49e382: mov dword ptr [ebp + 0x1f1cb8], eax */
L_49e388:
	M32((DWORD)(m->ebp + 0x2340c74u)) = m->ebx;	/* 49e388: mov dword ptr [ebp + 0x2340c74], ebx */
	M32((DWORD)(m->ebp + 0x2340c78u)) = m->ebx;	/* 49e38e: mov dword ptr [ebp + 0x2340c78], ebx */
	M32((DWORD)(m->ebp + 0x2340c7cu)) = m->ebx;	/* 49e394: mov dword ptr [ebp + 0x2340c7c], ebx */
	M32((DWORD)(m->ebp + 0x2340c80u)) = m->ebx;	/* 49e39a: mov dword ptr [ebp + 0x2340c80], ebx */
	M32((DWORD)(m->ebp + 0x2340c84u)) = m->ebx;	/* 49e3a0: mov dword ptr [ebp + 0x2340c84], ebx */
	M32((DWORD)(m->ebp + 0x2340c88u)) = m->ebx;	/* 49e3a6: mov dword ptr [ebp + 0x2340c88], ebx */
	M32((DWORD)(m->ebp + 0x2340c8cu)) = m->ebx;	/* 49e3ac: mov dword ptr [ebp + 0x2340c8c], ebx */
	M32((DWORD)(m->ebp + 0x2340c90u)) = m->ebx;	/* 49e3b2: mov dword ptr [ebp + 0x2340c90], ebx */
	M32((DWORD)(m->ebp + 0x2340c94u)) = m->ebx;	/* 49e3b8: mov dword ptr [ebp + 0x2340c94], ebx */
	M32((DWORD)(m->ebp + 0x2340d04u)) = m->esi;	/* 49e3be: mov dword ptr [ebp + 0x2340d04], esi */
	M32((DWORD)(m->ebp + 0x2342395u)) = m->ebx;	/* 49e3c4: mov dword ptr [ebp + 0x2342395], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 49e3ca: pop edi */
	M32((DWORD)(m->ebp + 0x23423a9u)) = m->ebx;	/* 49e3cb: mov dword ptr [ebp + 0x23423a9], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 49e3d1: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 49e3d2: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49e3d3: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 49e3d4: pop ecx */
	m->esp += 4 + 0; return;	/* 49e3d5: ret  */
L_49e3d6:
	m->eax = (DWORD)(m->ebp + 0x2342429u);	/* 49e3d6: lea eax, [ebp + 0x2342429] */
	M32((DWORD)(0x9fd94cu)) = m->ebx;	/* 49e3dc: mov dword ptr [0x9fd94c], ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49e3e2: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49e3e3: push ebx */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49e3e4: lea ecx, [ebp + 0x1f36c8] */
	M32((DWORD)(m->ebp + 0x234240du)) = m->ebx;	/* 49e3ea: mov dword ptr [ebp + 0x234240d], ebx */
	m->esp -= 4; M32(m->esp) = 0x49e3f5u; native_call(m, 0x473940u);	/* 49e3f0: call 0x473940 */
	M32((DWORD)(m->ebp + 0x2221f9cu)) = m->ebx;	/* 49e3f5: mov dword ptr [ebp + 0x2221f9c], ebx */
	M32((DWORD)(0x9da3e0u)) = m->esi;	/* 49e3fb: mov dword ptr [0x9da3e0], esi */
	M32((DWORD)(m->ebp + 0x2340d04u)) = m->ebx;	/* 49e401: mov dword ptr [ebp + 0x2340d04], ebx */
	M32((DWORD)(m->ebp + 0x2342395u)) = m->ebx;	/* 49e407: mov dword ptr [ebp + 0x2342395], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 49e40d: pop edi */
	M32((DWORD)(m->ebp + 0x23423a9u)) = m->ebx;	/* 49e40e: mov dword ptr [ebp + 0x23423a9], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 49e414: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 49e415: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49e416: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 49e417: pop ecx */
	m->esp += 4 + 0; return;	/* 49e418: ret  */
L_49e419:
	M32((DWORD)(m->ebp + 0x23423c9u)) = m->ebx;	/* 49e419: mov dword ptr [ebp + 0x23423c9], ebx */
	m->ecx = M32((DWORD)(m->ebp + 0x15de6c8u));	/* 49e41f: mov ecx, dword ptr [ebp + 0x15de6c8] */
	m->eax = m->ecx;	/* 49e425: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49e427: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e42a: add eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49e42c: lea edx, [eax + eax*4] */
	m->ecx = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 49e42f: lea ecx, [ecx + edx*4] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e432: shl ecx, 3 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e435: shr ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e438: cmp ecx, ebx */
	if (m->zf || m->sf != m->of) goto L_49e45d;	/* 49e43a: jle 0x49e45d */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 49e43c: mov esi, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e442: xor edx, edx */
	m->eax = m->esi;	/* 49e444: mov eax, esi */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49e446: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 49e44b: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 49e452: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49e454: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 49e455: mov dword ptr [0xa1efb8], esi */
	goto L_49e45f;	/* 49e45b: jmp 0x49e45f */
L_49e45d:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e45d: xor edx, edx */
L_49e45f:
	M32((DWORD)(m->ebp + 0x23423cdu)) = m->edx;	/* 49e45f: mov dword ptr [ebp + 0x23423cd], edx */
	m->ecx = M32((DWORD)(m->ebp + 0x15fff84u));	/* 49e465: mov ecx, dword ptr [ebp + 0x15fff84] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 49e46b: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49e46e: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e471: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49e473: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49e476: shl eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e478: sub eax, ecx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49e47a: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e47d: shl ecx, 2 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e480: shr ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e483: cmp ecx, ebx */
	if (m->zf || m->sf != m->of) goto L_49e4a9;	/* 49e485: jle 0x49e4a9 */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 49e487: mov esi, dword ptr [0xa1efb8] */
	m->edx = m->esi;	/* 49e48d: mov edx, esi */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e48f: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 49e495: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e49c: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 49e49e: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49e4a0: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 49e4a1: mov dword ptr [0xa1efb8], esi */
	goto L_49e4ab;	/* 49e4a7: jmp 0x49e4ab */
L_49e4a9:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e4a9: xor edx, edx */
L_49e4ab:
	M32((DWORD)(m->ebp + 0x23423d1u)) = m->edx;	/* 49e4ab: mov dword ptr [ebp + 0x23423d1], edx */
	m->eax = M32((DWORD)(m->ebp + 0x163b588u));	/* 49e4b1: mov eax, dword ptr [ebp + 0x163b588] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 49e4b7: lea ecx, [eax + eax*8] */
	m->ecx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 49e4ba: lea ecx, [eax + ecx*2] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e4bd: shl ecx, 8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e4c0: shr ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e4c3: cmp ecx, ebx */
	if (m->zf || m->sf != m->of) goto L_49e4e9;	/* 49e4c5: jle 0x49e4e9 */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 49e4c7: mov esi, dword ptr [0xa1efb8] */
	m->edx = m->esi;	/* 49e4cd: mov edx, esi */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e4cf: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 49e4d5: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e4dc: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 49e4de: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49e4e0: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 49e4e1: mov dword ptr [0xa1efb8], esi */
	goto L_49e4eb;	/* 49e4e7: jmp 0x49e4eb */
L_49e4e9:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e4e9: xor edx, edx */
L_49e4eb:
	M32((DWORD)(m->ebp + 0x23423d5u)) = m->edx;	/* 49e4eb: mov dword ptr [ebp + 0x23423d5], edx */
	m->eax = M32((DWORD)(m->ebp + 0x1679b34u));	/* 49e4f1: mov eax, dword ptr [ebp + 0x1679b34] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49e4f7: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e4fa: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e4fd: sub ecx, eax */
	m->ecx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 49e4ff: lea ecx, [eax + ecx*4] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e502: shl ecx, 2 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e505: shr ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e508: cmp ecx, ebx */
	if (m->zf || m->sf != m->of) goto L_49e52e;	/* 49e50a: jle 0x49e52e */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 49e50c: mov esi, dword ptr [0xa1efb8] */
	m->edx = m->esi;	/* 49e512: mov edx, esi */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e514: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 49e51a: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e521: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 49e523: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49e525: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 49e526: mov dword ptr [0xa1efb8], esi */
	goto L_49e530;	/* 49e52c: jmp 0x49e530 */
L_49e52e:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e52e: xor edx, edx */
L_49e530:
	M32((DWORD)(m->ebp + 0x23423d9u)) = m->edx;	/* 49e530: mov dword ptr [ebp + 0x23423d9], edx */
	m->eax = M32((DWORD)(m->ebp + 0x16c5178u));	/* 49e536: mov eax, dword ptr [ebp + 0x16c5178] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49e53c: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e53f: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49e542: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e544: shl ecx, 5 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e547: shr ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e54a: cmp ecx, ebx */
	if (m->zf || m->sf != m->of) goto L_49e56f;	/* 49e54c: jle 0x49e56f */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 49e54e: mov esi, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e554: xor edx, edx */
	m->eax = m->esi;	/* 49e556: mov eax, esi */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49e558: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 49e55d: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 49e564: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49e566: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 49e567: mov dword ptr [0xa1efb8], esi */
	goto L_49e571;	/* 49e56d: jmp 0x49e571 */
L_49e56f:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e56f: xor edx, edx */
L_49e571:
	M32((DWORD)(m->ebp + 0x23423ddu)) = m->edx;	/* 49e571: mov dword ptr [ebp + 0x23423dd], edx */
	m->ecx = M32((DWORD)(m->ebp + 0x175522cu));	/* 49e577: mov ecx, dword ptr [ebp + 0x175522c] */
	m->eax = m->ecx;	/* 49e57d: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49e57f: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e582: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49e584: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e587: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49e589: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49e58c: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e58f: shl ecx, 3 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49e592: shr ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e595: cmp ecx, ebx */
	if (m->zf || m->sf != m->of) goto L_49e5bb;	/* 49e597: jle 0x49e5bb */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 49e599: mov esi, dword ptr [0xa1efb8] */
	m->edx = m->esi;	/* 49e59f: mov edx, esi */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e5a1: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 49e5a7: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e5ae: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 49e5b0: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49e5b2: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 49e5b3: mov dword ptr [0xa1efb8], esi */
	goto L_49e5bd;	/* 49e5b9: jmp 0x49e5bd */
L_49e5bb:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49e5bb: xor edx, edx */
L_49e5bd:
	{ DWORD a_ = m->esi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 49e5bd: or esi, 0xffffffff */
	m->eax = (DWORD)(m->ebp + 0x22ee228u);	/* 49e5c0: lea eax, [ebp + 0x22ee228] */
	M32((DWORD)(m->ebp + 0x23423e1u)) = m->edx;	/* 49e5c6: mov dword ptr [ebp + 0x23423e1], edx */
	M32((DWORD)(m->ebp + 0x23423fdu)) = m->ebx;	/* 49e5cc: mov dword ptr [ebp + 0x23423fd], ebx */
	M32((DWORD)(m->ebp + 0x2342401u)) = m->esi;	/* 49e5d2: mov dword ptr [ebp + 0x2342401], esi */
	M32((DWORD)(m->ebp + 0x233cc30u)) = m->ebx;	/* 49e5d8: mov dword ptr [ebp + 0x233cc30], ebx */
	M32((DWORD)(m->ebp + 0x233cc34u)) = m->ebx;	/* 49e5de: mov dword ptr [ebp + 0x233cc34], ebx */
	M32((DWORD)(m->ebp + 0x233cc54u)) = 0x40400000u;	/* 49e5e4: mov dword ptr [ebp + 0x233cc54], 0x40400000 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 49e5ee: mov edx, dword ptr [eax] */
	m->ecx = (DWORD)(m->ebp + 0x233ca04u);	/* 49e5f0: lea ecx, [ebp + 0x233ca04] */
	M32((DWORD)(m->ebp + 0x233ca04u)) = m->edx;	/* 49e5f6: mov dword ptr [ebp + 0x233ca04], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 49e5fc: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 49e5ff: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 49e602: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 49e605: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x22ee234u));	/* 49e608: mov ecx, dword ptr [ebp + 0x22ee234] */
	M32((DWORD)(m->ebp + 0x233ca28u)) = m->ecx;	/* 49e60e: mov dword ptr [ebp + 0x233ca28], ecx */
	m->edx = M32((DWORD)(m->ebp + 0x22ee238u));	/* 49e614: mov edx, dword ptr [ebp + 0x22ee238] */
	M32((DWORD)(m->ebp + 0x233ca2cu)) = m->edx;	/* 49e61a: mov dword ptr [ebp + 0x233ca2c], edx */
	M32((DWORD)(m->ebp + 0x233cc10u)) = m->ebx;	/* 49e620: mov dword ptr [ebp + 0x233cc10], ebx */
L_49e626:
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49e626: mov eax, dword ptr [ebp + 0x233cc10] */
	m->ecx = M32((DWORD)(m->ebp + m->eax*4 + 0x233ca30u));	/* 49e62c: mov ecx, dword ptr [ebp + eax*4 + 0x233ca30] */
	M32((DWORD)(m->ebp + m->eax*4 + 0x233cb20u)) = m->ecx;	/* 49e633: mov dword ptr [ebp + eax*4 + 0x233cb20], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49e63a: mov eax, dword ptr [ebp + 0x233cc10] */
	m->edx = M32((DWORD)(m->ebp + m->eax*4 + 0x233ca58u));	/* 49e640: mov edx, dword ptr [ebp + eax*4 + 0x233ca58] */
	M32((DWORD)(m->ebp + m->eax*4 + 0x233cb48u)) = m->edx;	/* 49e647: mov dword ptr [ebp + eax*4 + 0x233cb48], edx */
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49e64e: mov eax, dword ptr [ebp + 0x233cc10] */
	m->ecx = M32((DWORD)(m->ebp + m->eax*4 + 0x233ca80u));	/* 49e654: mov ecx, dword ptr [ebp + eax*4 + 0x233ca80] */
	M32((DWORD)(m->ebp + m->eax*4 + 0x233cb70u)) = m->ecx;	/* 49e65b: mov dword ptr [ebp + eax*4 + 0x233cb70], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49e662: mov eax, dword ptr [ebp + 0x233cc10] */
	m->edx = M32((DWORD)(m->ebp + m->eax*4 + 0x233caa8u));	/* 49e668: mov edx, dword ptr [ebp + eax*4 + 0x233caa8] */
	M32((DWORD)(m->ebp + m->eax*4 + 0x233cb98u)) = m->edx;	/* 49e66f: mov dword ptr [ebp + eax*4 + 0x233cb98], edx */
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49e676: mov eax, dword ptr [ebp + 0x233cc10] */
	m->ecx = M32((DWORD)(m->ebp + m->eax*4 + 0x233cad0u));	/* 49e67c: mov ecx, dword ptr [ebp + eax*4 + 0x233cad0] */
	M32((DWORD)(m->ebp + m->eax*4 + 0x233cbc0u)) = m->ecx;	/* 49e683: mov dword ptr [ebp + eax*4 + 0x233cbc0], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49e68a: mov eax, dword ptr [ebp + 0x233cc10] */
	m->edx = M32((DWORD)(m->ebp + m->eax*4 + 0x233caf8u));	/* 49e690: mov edx, dword ptr [ebp + eax*4 + 0x233caf8] */
	M32((DWORD)(m->ebp + m->eax*4 + 0x233cbe8u)) = m->edx;	/* 49e697: mov dword ptr [ebp + eax*4 + 0x233cbe8], edx */
	m->ecx = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49e69e: mov ecx, dword ptr [ebp + 0x233cc10] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49e6a4: inc ecx */
	m->eax = m->ecx;	/* 49e6a5: mov eax, ecx */
	M32((DWORD)(m->ebp + 0x233cc10u)) = m->ecx;	/* 49e6a7: mov dword ptr [ebp + 0x233cc10], ecx */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e6ad: cmp eax, 0xa */
	if (m->sf != m->of) goto L_49e626;	/* 49e6b0: jl 0x49e626 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49e6b6: push esi */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49e6b7: lea ecx, [ebp + 0x1f36c8] */
	M32((DWORD)(m->ebp + 0x233cc10u)) = 0x1u;	/* 49e6bd: mov dword ptr [ebp + 0x233cc10], 1 */
	m->esp -= 4; M32(m->esp) = 0x49e6ccu; native_call(m, 0x45dfb0u);	/* 49e6c7: call 0x45dfb0 */
	m->ecx = (DWORD)(m->ebp + 0xcu);	/* 49e6cc: lea ecx, [ebp + 0xc] */
	M32((DWORD)(m->ebp + 0x2340c64u)) = m->esi;	/* 49e6cf: mov dword ptr [ebp + 0x2340c64], esi */
	M32((DWORD)(m->ebp + 0x2340c68u)) = m->ebx;	/* 49e6d5: mov dword ptr [ebp + 0x2340c68], ebx */
	M32((DWORD)(m->ebp + 0x2340c6cu)) = m->ebx;	/* 49e6db: mov dword ptr [ebp + 0x2340c6c], ebx */
	M32((DWORD)(m->ebp + 0x2340c70u)) = m->ebx;	/* 49e6e1: mov dword ptr [ebp + 0x2340c70], ebx */
	M32((DWORD)(m->ebp + 0x233c9fcu)) = m->ebx;	/* 49e6e7: mov dword ptr [ebp + 0x233c9fc], ebx */
	m->esp -= 4; M32(m->esp) = 0x49e6f2u; native_call(m, 0x487490u);	/* 49e6ed: call 0x487490 */
	ST(0) = ST(0); FPOP();	/* 49e6f2: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x49e6f9u; native_call(m, 0x4685b0u);	/* 49e6f4: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49e6f9: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e6fa: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49e6fc: sar eax, 1 */
	M32((DWORD)(0x4ded68u)) = m->eax;	/* 49e6fe: mov dword ptr [0x4ded68], eax */
	m->esp -= 4; M32(m->esp) = 0x49e708u; native_call(m, 0x4685c0u);	/* 49e703: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49e708: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49e709: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49e70b: sar eax, 1 */
	M32((DWORD)(0x4ded6cu)) = m->eax;	/* 49e70d: mov dword ptr [0x4ded6c], eax */
	m->eax = M32((DWORD)(0x4e0c90u));	/* 49e712: mov eax, dword ptr [0x4e0c90] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49e717: push eax */
	m->esp -= 4; M32(m->esp) = 0x49e71du; native_call(m, 0x456de0u);	/* 49e718: call 0x456de0 */
	m->ecx = M32((DWORD)(0x4e0c94u));	/* 49e71d: mov ecx, dword ptr [0x4e0c94] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49e723: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49e729u; native_call(m, 0x457140u);	/* 49e724: call 0x457140 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49e729: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49e72f: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e732: cmp eax, ebx */
	M32((DWORD)(m->ebp + 0x2342411u)) = m->ebx;	/* 49e734: mov dword ptr [ebp + 0x2342411], ebx */
	M32((DWORD)(m->ebp + 0x2342415u)) = m->ebx;	/* 49e73a: mov dword ptr [ebp + 0x2342415], ebx */
	if (m->sf != m->of) goto L_49e75a;	/* 49e740: jl 0x49e75a */
	m->edx = m->eax;	/* 49e742: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49e744: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49e747: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49e749: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49e74c: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49e74e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49e751: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb48u)) = m->ebx;	/* 49e753: mov dword ptr [ebp + edx*8 + 0x1eccb48], ebx */
L_49e75a:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49e75a: push esi */
	m->ecx = m->ebp;	/* 49e75b: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49e762u; native_call(m, 0x4613a0u);	/* 49e75d: call 0x4613a0 */
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49e762: mov eax, dword ptr [ebp + 0x233cc10] */
	m->ecx = m->ebp;	/* 49e768: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x23424eeu)) = m->eax;	/* 49e76a: mov dword ptr [ebp + 0x23424ee], eax */
	M32((DWORD)(m->ebp + 0x23424f2u)) = m->esi;	/* 49e770: mov dword ptr [ebp + 0x23424f2], esi */
	M32((DWORD)(m->ebp + 0x234297au)) = m->esi;	/* 49e776: mov dword ptr [ebp + 0x234297a], esi */
	m->esp -= 4; M32(m->esp) = 0x49e781u; native_call(m, 0x4620e0u);	/* 49e77c: call 0x4620e0 */
	{ DWORD v_ = 0x42700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49e781: push 0x42700000 */
	m->ecx = m->ebp;	/* 49e786: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49e78du; native_call(m, 0x4629c0u);	/* 49e788: call 0x4629c0 */
	M32((DWORD)(m->ebp + 0x2340d35u)) = m->ebx;	/* 49e78d: mov dword ptr [ebp + 0x2340d35], ebx */
	m->eax = M32((DWORD)(0x68039cu));	/* 49e793: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49e798: cmp eax, ebx */
	if (m->zf) goto L_49e7a1;	/* 49e79a: je 0x49e7a1 */
	m->esp -= 4; M32(m->esp) = 0x49e7a1u; native_call(m, 0x44ace0u);	/* 49e79c: call 0x44ace0 */
L_49e7a1:
	m->ecx = m->ebp;	/* 49e7a1: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x2340d39u)) = m->ebx;	/* 49e7a3: mov dword ptr [ebp + 0x2340d39], ebx */
	M32((DWORD)(m->ebp + 0x2342399u)) = m->ebx;	/* 49e7a9: mov dword ptr [ebp + 0x2342399], ebx */
	M32((DWORD)(m->ebp + 0x234239du)) = m->ebx;	/* 49e7af: mov dword ptr [ebp + 0x234239d], ebx */
	M32((DWORD)(m->ebp + 0x23423a1u)) = m->ebx;	/* 49e7b5: mov dword ptr [ebp + 0x23423a1], ebx */
	M32((DWORD)(m->ebp + 0x23423a5u)) = m->ebx;	/* 49e7bb: mov dword ptr [ebp + 0x23423a5], ebx */
	m->esp -= 4; M32(m->esp) = 0x49e7c6u; native_call(m, 0x4636d0u);	/* 49e7c1: call 0x4636d0 */
	M32((DWORD)(m->ebp + 0x233cc40u)) = m->ebx;	/* 49e7c6: mov dword ptr [ebp + 0x233cc40], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 49e7cc: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 49e7cd: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49e7ce: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 49e7cf: pop ecx */
	m->esp += 4 + 0; return;	/* 49e7d0: ret  */
}

/* match_escMenu (0x49ca70), lifted by tools/lift.py */
static void lift_49ca70(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49ca70: push esi */
	m->esi = m->ecx;	/* 49ca71: mov esi, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340c9cu)));	/* 49ca73: fld dword ptr [esi + 0x2340c9c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a941cu)); FPOP();	/* 49ca79: fcomp dword ptr [0x4a941c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49ca7f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49ca81: test ah, 1 */
	if (!m->zf) goto L_49d0e8;	/* 49ca84: jne 0x49d0e8 */
	m->eax = M32((DWORD)(m->esi + 0x2340cf8u));	/* 49ca8a: mov eax, dword ptr [esi + 0x2340cf8] */
	m->ecx = 0x4u;	/* 49ca90: mov ecx, 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49ca95: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49ca96: push ebp */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ca97: cmp eax, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49ca99: push edi */
	if (!m->cf && !m->zf) goto L_49d0b9;	/* 49ca9a: ja 0x49d0b9 */
	switch (m->eax) { case 0: goto L_49caa7; case 1: goto L_49cdb4; case 2: goto L_49cf92; case 3: goto L_49cfda; case 4: goto L_49d06c; default: abort(); }	/* 49caa0: jmp dword ptr [eax*4 + 0x49d0fc] */
L_49caa7:
	m->eax = M32((DWORD)(m->esi + 0x234330bu));	/* 49caa7: mov eax, dword ptr [esi + 0x234330b] */
	m->ebp = 0x1u;	/* 49caad: mov ebp, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49cab2: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cab4: cmp eax, ebp */
	m->edi = 0x2u;	/* 49cab6: mov edi, 2 */
	if (!m->zf) goto L_49cb3c;	/* 49cabb: jne 0x49cb3c */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 49cabd: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cac0: cmp eax, ebx */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 49cac2: mov eax, dword ptr [esi + 0x2340cfc] */
	if (!m->zf) goto L_49cb0a;	/* 49cac8: jne 0x49cb0a */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49caca: sub eax, ebx */
	if (m->zf) goto L_49cba4;	/* 49cacc: je 0x49cba4 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49cad2: sub eax, 3 */
	if (m->zf) goto L_49caed;	/* 49cad5: je 0x49caed */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49cad7: dec eax */
	if (!m->zf) goto L_49cba4;	/* 49cad8: jne 0x49cba4 */
L_49cade:
	M32((DWORD)(m->esi + 0x2340cfcu)) = 0x3u;	/* 49cade: mov dword ptr [esi + 0x2340cfc], 3 */
	goto L_49cbaa;	/* 49cae8: jmp 0x49cbaa */
L_49caed:
	m->edx = M32((DWORD)(m->esi + 0x234243eu));	/* 49caed: mov edx, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49caf3: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49caf5: cmp edx, ebx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 49caf7: setge al */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49cafa: dec eax */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xfcu & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 49cafb: and al, 0xfc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49cafd: add eax, ecx */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->eax;	/* 49caff: mov dword ptr [esi + 0x2340cfc], eax */
	goto L_49cbaa;	/* 49cb05: jmp 0x49cbaa */
L_49cb0a:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb0a: cmp eax, ecx */
	if (!m->cf && !m->zf) goto L_49cba4;	/* 49cb0c: ja 0x49cba4 */
	switch (m->eax) { case 0: goto L_49cba4; case 1: goto L_49cb19; case 2: goto L_49cb24; case 3: goto L_49cb9c; case 4: goto L_49cade; default: abort(); }	/* 49cb12: jmp dword ptr [eax*4 + 0x49d110] */
L_49cb19:
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebx;	/* 49cb19: mov dword ptr [esi + 0x2340cfc], ebx */
	goto L_49cbaa;	/* 49cb1f: jmp 0x49cbaa */
L_49cb24:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb24: cmp dword ptr [esi + 0x22e7184], ebp */
	if (!m->zf) goto L_49cb19;	/* 49cb2a: jne 0x49cb19 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234243eu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb2c: cmp dword ptr [esi + 0x234243e], ebx */
	if (m->sf != m->of) goto L_49cb19;	/* 49cb32: jl 0x49cb19 */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebp;	/* 49cb34: mov dword ptr [esi + 0x2340cfc], ebp */
	goto L_49cbaa;	/* 49cb3a: jmp 0x49cbaa */
L_49cb3c:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234330fu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb3c: cmp dword ptr [esi + 0x234330f], ebp */
	if (!m->zf) goto L_49cbaa;	/* 49cb42: jne 0x49cbaa */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 49cb44: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb47: cmp eax, ebx */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 49cb49: mov eax, dword ptr [esi + 0x2340cfc] */
	if (!m->zf) goto L_49cb79;	/* 49cb4f: jne 0x49cb79 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49cb51: sub eax, ebx */
	if (m->zf) goto L_49cade;	/* 49cb53: je 0x49cade */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49cb55: sub eax, 3 */
	if (m->zf) goto L_49cba4;	/* 49cb58: je 0x49cba4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49cb5a: dec eax */
	if (!m->zf) goto L_49cba4;	/* 49cb5b: jne 0x49cba4 */
	m->eax = M32((DWORD)(m->esi + 0x234243eu));	/* 49cb5d: mov eax, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49cb63: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb65: cmp eax, ebx */
	m->edx = (m->edx & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 49cb67: setge dl */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 49cb6a: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffffdu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49cb6b: and edx, 0xfffffffd */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49cb6e: add edx, 3 */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->edx;	/* 49cb71: mov dword ptr [esi + 0x2340cfc], edx */
	goto L_49cbaa;	/* 49cb77: jmp 0x49cbaa */
L_49cb79:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb79: cmp eax, ecx */
	if (!m->cf && !m->zf) goto L_49cba4;	/* 49cb7b: ja 0x49cba4 */
	switch (m->eax) { case 0: goto L_49cb84; case 1: goto L_49cb9c; case 2: goto L_49cade; case 3: goto L_49cba4; case 4: goto L_49cb19; case 5: goto L_49cbcb; case 6: goto L_49cd4b; case 7: goto L_49cd6d; case 8: goto L_49cd9b; case 9: goto L_49cda6; default: abort(); }	/* 49cb7d: jmp dword ptr [eax*4 + 0x49d124] */
L_49cb84:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb84: cmp dword ptr [esi + 0x22e7184], ebp */
	if (!m->zf) goto L_49cb9c;	/* 49cb8a: jne 0x49cb9c */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234243eu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cb8c: cmp dword ptr [esi + 0x234243e], ebx */
	if (m->sf != m->of) goto L_49cb9c;	/* 49cb92: jl 0x49cb9c */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebp;	/* 49cb94: mov dword ptr [esi + 0x2340cfc], ebp */
	goto L_49cbaa;	/* 49cb9a: jmp 0x49cbaa */
L_49cb9c:
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->edi;	/* 49cb9c: mov dword ptr [esi + 0x2340cfc], edi */
	goto L_49cbaa;	/* 49cba2: jmp 0x49cbaa */
L_49cba4:
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ecx;	/* 49cba4: mov dword ptr [esi + 0x2340cfc], ecx */
L_49cbaa:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343313u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cbaa: cmp dword ptr [esi + 0x2343313], ebp */
	if (!m->zf) goto L_49cf81;	/* 49cbb0: jne 0x49cf81 */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 49cbb6: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cbbc: cmp eax, ecx */
	if (!m->cf && !m->zf) goto L_49d0b9;	/* 49cbbe: ja 0x49d0b9 */
	switch (m->eax) { case 0: goto L_49cbcb; case 1: goto L_49cd4b; case 2: goto L_49cd6d; case 3: goto L_49cd9b; case 4: goto L_49cda6; default: abort(); }	/* 49cbc4: jmp dword ptr [eax*4 + 0x49d138] */
L_49cbcb:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234243eu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cbcb: cmp dword ptr [esi + 0x234243e], ebx */
	if (m->sf == m->of) goto L_49cc3b;	/* 49cbd1: jge 0x49cc3b */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cbd3: cmp dword ptr [esi + 0x22e7184], ebp */
	if (!m->zf) goto L_49cc30;	/* 49cbd9: jne 0x49cc30 */
	m->eax = M32((DWORD)(m->esi + 0x234241du));	/* 49cbdb: mov eax, dword ptr [esi + 0x234241d] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cbe1: cmp eax, ebx */
	if (m->sf != m->of) goto L_49cc12;	/* 49cbe3: jl 0x49cc12 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cbe5: cmp dword ptr [esi + 8], ebx */
	if (m->zf) goto L_49cc12;	/* 49cbe8: je 0x49cc12 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49cbea: push eax */
	m->ecx = m->esi;	/* 49cbeb: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cbf2u; native_call(m, 0x463740u);	/* 49cbed: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49cbf2: test eax, eax */
	if (!m->zf) goto L_49cc04;	/* 49cbf4: jne 0x49cc04 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cbf6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49cbf7: push ebp */
	m->ecx = m->esi;	/* 49cbf8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cbffu; native_call(m, 0x49ca20u);	/* 49cbfa: call 0x49ca20 */
	goto L_49d0b9;	/* 49cbff: jmp 0x49d0b9 */
L_49cc04:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49cc04: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49cc05: push ebp */
	m->ecx = m->esi;	/* 49cc06: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cc0du; native_call(m, 0x49ca20u);	/* 49cc08: call 0x49ca20 */
	goto L_49d0b9;	/* 49cc0d: jmp 0x49d0b9 */
L_49cc12:
	m->eax = M32((DWORD)(m->esi + 0x234297eu));	/* 49cc12: mov eax, dword ptr [esi + 0x234297e] */
	m->ecx = M32((DWORD)(m->esi + 0x2342982u));	/* 49cc18: mov ecx, dword ptr [esi + 0x2342982] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cc1e: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_49cc04;	/* 49cc20: jg 0x49cc04 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cc22: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49cc23: push ebp */
	m->ecx = m->esi;	/* 49cc24: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cc2bu; native_call(m, 0x49ca20u);	/* 49cc26: call 0x49ca20 */
	goto L_49d0b9;	/* 49cc2b: jmp 0x49d0b9 */
L_49cc30:
	M32((DWORD)(m->esi + 0x2342415u)) = m->ebp;	/* 49cc30: mov dword ptr [esi + 0x2342415], ebp */
	goto L_49d0b3;	/* 49cc36: jmp 0x49d0b3 */
L_49cc3b:
	m->ecx = M32((DWORD)(m->esi + 0x234240du));	/* 49cc3b: mov ecx, dword ptr [esi + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cc41: push ecx */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 49cc42: lea ecx, [esi + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x49cc4du; native_call(m, 0x45dca0u);	/* 49cc48: call 0x45dca0 */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 49cc4d: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->edi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 49cc50: or edi, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cc53: cmp eax, ebx */
	if (m->zf) goto L_49cc5d;	/* 49cc55: je 0x49cc5d */
	M32((DWORD)(m->esi + 0x234243eu)) = m->edi;	/* 49cc57: mov dword ptr [esi + 0x234243e], edi */
L_49cc5d:
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cc5d: cmp eax, ebp */
	M32((DWORD)(m->esi + 0x233c9fcu)) = m->ebx;	/* 49cc5f: mov dword ptr [esi + 0x233c9fc], ebx */
	if (!m->zf) goto L_49cd38;	/* 49cc65: jne 0x49cd38 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49cc6b: push edi */
	m->ecx = m->esi;	/* 49cc6c: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cc73u; native_call(m, 0x4613a0u);	/* 49cc6e: call 0x4613a0 */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49cc73: mov eax, dword ptr [esi + 0x234240d] */
	m->edx = m->eax;	/* 49cc79: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49cc7b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49cc7e: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49cc80: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49cc83: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49cc85: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49cc88: add edx, eax */
	M32((DWORD)(m->esi + m->edx*8 + 0x1eccb88u)) = m->edi;	/* 49cc8a: mov dword ptr [esi + edx*8 + 0x1eccb88], edi */
	m->eax = M32((DWORD)(m->esi + 0x233c9f0u));	/* 49cc91: mov eax, dword ptr [esi + 0x233c9f0] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cc97: cmp eax, ebp */
	if (!m->zf) goto L_49cca2;	/* 49cc99: jne 0x49cca2 */
	m->ecx = m->esi;	/* 49cc9b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cca2u; native_call(m, 0x49d150u);	/* 49cc9d: call 0x49d150 */
L_49cca2:
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49cca2: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49cca8: push edi */
	m->ecx = m->eax;	/* 49cca9: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ccab: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ccae: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ccb0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ccb3: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ccb5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ccb8: add ecx, eax */
	M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb60u)) = m->ebx;	/* 49ccba: mov dword ptr [esi + ecx*8 + 0x1eccb60], ebx */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49ccc1: mov eax, dword ptr [esi + 0x234240d] */
	m->edx = m->eax;	/* 49ccc7: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ccc9: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49cccc: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ccce: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ccd1: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ccd3: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ccd6: add edx, eax */
	M32((DWORD)(m->esi + m->edx*8 + 0x1eccb54u)) = m->ebx;	/* 49ccd8: mov dword ptr [esi + edx*8 + 0x1eccb54], ebx */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49ccdf: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 49cce5: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49cce7: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ccea: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ccec: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ccef: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ccf1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ccf4: add ecx, eax */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x1eccb58u);	/* 49ccf6: lea eax, [esi + ecx*8 + 0x1eccb58] */
	m->ecx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb58u));	/* 49ccfd: mov ecx, dword ptr [esi + ecx*8 + 0x1eccb58] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49cd04: inc ecx */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 49cd05: mov dword ptr [eax], ecx */
	m->edx = M32((DWORD)(m->esi + 0x234240du));	/* 49cd07: mov edx, dword ptr [esi + 0x234240d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd0d: push edx */
	m->ecx = m->esi;	/* 49cd0e: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cd15u; native_call(m, 0x462e30u);	/* 49cd10: call 0x462e30 */
	m->ecx = M32((DWORD)(m->esi + 0x234240du));	/* 49cd15: mov ecx, dword ptr [esi + 0x234240d] */
	m->eax = (DWORD)(m->esi + 0x2342429u);	/* 49cd1b: lea eax, [esi + 0x2342429] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd21: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd22: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd23: push ecx */
	m->ecx = m->esi;	/* 49cd24: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cd2bu; native_call(m, 0x463610u);	/* 49cd26: call 0x463610 */
	m->ecx = m->esi;	/* 49cd2b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cd32u; native_call(m, 0x462150u);	/* 49cd2d: call 0x462150 */
	M32((DWORD)(m->esi + 0x2340c64u)) = m->edi;	/* 49cd32: mov dword ptr [esi + 0x2340c64], edi */
L_49cd38:
	{ DWORD v_ = 0x4d06f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd38: push 0x4d06f4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd3d: push esi */
	m->esp -= 4; M32(m->esp) = 0x49cd43u; native_call(m, 0x463450u);	/* 49cd3e: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49cd43: add esp, 8 */
	goto L_49d0b3;	/* 49cd46: jmp 0x49d0b3 */
L_49cd4b:
	m->edx = M32((DWORD)(m->esi + 0x234297eu));	/* 49cd4b: mov edx, dword ptr [esi + 0x234297e] */
	m->eax = M32((DWORD)(m->esi + 0x2342982u));	/* 49cd51: mov eax, dword ptr [esi + 0x2342982] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cd57: cmp edx, eax */
	if (!m->zf && m->sf == m->of) goto L_49cc04;	/* 49cd59: jg 0x49cc04 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd5f: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd60: push ebp */
	m->ecx = m->esi;	/* 49cd61: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cd68u; native_call(m, 0x49ca20u);	/* 49cd63: call 0x49ca20 */
	goto L_49d0b9;	/* 49cd68: jmp 0x49d0b9 */
L_49cd6d:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340d1du)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cd6d: cmp dword ptr [esi + 0x2340d1d], ebx */
	if (!m->zf) goto L_49cd8f;	/* 49cd73: jne 0x49cd8f */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd75: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd76: push edi */
	m->ecx = m->esi;	/* 49cd77: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cd7eu; native_call(m, 0x49ca20u);	/* 49cd79: call 0x49ca20 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd7e: push 0x10 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd80: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cd81: push ebx */
	m->esp -= 4; M32(m->esp) = 0x49cd87u; native_call(m, 0x44ac90u);	/* 49cd82: call 0x44ac90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49cd87: add esp, 0xc */
	goto L_49d0b9;	/* 49cd8a: jmp 0x49d0b9 */
L_49cd8f:
	m->ecx = m->esi;	/* 49cd8f: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cd96u; native_call(m, 0x487ed0u);	/* 49cd91: call 0x487ed0 */
	goto L_49d0b3;	/* 49cd96: jmp 0x49d0b3 */
L_49cd9b:
	M32((DWORD)(m->esi + 0x2340cecu)) = m->ebp;	/* 49cd9b: mov dword ptr [esi + 0x2340cec], ebp */
	goto L_49d0b3;	/* 49cda1: jmp 0x49d0b3 */
L_49cda6:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cda6: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cda7: push ecx */
	m->ecx = m->esi;	/* 49cda8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cdafu; native_call(m, 0x49ca20u);	/* 49cdaa: call 0x49ca20 */
	goto L_49d0b9;	/* 49cdaf: jmp 0x49d0b9 */
L_49cdb4:
	m->eax = M32((DWORD)(m->esi + 0x234330bu));	/* 49cdb4: mov eax, dword ptr [esi + 0x234330b] */
	m->ebp = 0x1u;	/* 49cdba: mov ebp, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49cdbf: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cdc1: cmp eax, ebp */
	if (!m->zf) goto L_49cdcd;	/* 49cdc3: jne 0x49cdcd */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebx;	/* 49cdc5: mov dword ptr [esi + 0x2340cfc], ebx */
	goto L_49cddb;	/* 49cdcb: jmp 0x49cddb */
L_49cdcd:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234330fu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cdcd: cmp dword ptr [esi + 0x234330f], ebp */
	if (!m->zf) goto L_49cddb;	/* 49cdd3: jne 0x49cddb */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebp;	/* 49cdd5: mov dword ptr [esi + 0x2340cfc], ebp */
L_49cddb:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343313u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cddb: cmp dword ptr [esi + 0x2343313], ebp */
	if (!m->zf) goto L_49cf81;	/* 49cde1: jne 0x49cf81 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cde7: cmp dword ptr [esi + 8], ebx */
	if (!m->zf) goto L_49ce18;	/* 49cdea: jne 0x49ce18 */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 49cdec: mov eax, dword ptr [esi + 0x2340cfc] */
	M32((DWORD)(m->esi + 0x234243eu)) = m->ebx;	/* 49cdf2: mov dword ptr [esi + 0x234243e], ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cdf8: cmp eax, ebx */
	M32((DWORD)(m->esi + 0x2342415u)) = m->ebp;	/* 49cdfa: mov dword ptr [esi + 0x2342415], ebp */
	M32((DWORD)(m->esi + 0x234241du)) = m->ebx;	/* 49ce00: mov dword ptr [esi + 0x234241d], ebx */
	if (!m->zf) goto L_49ce10;	/* 49ce06: jne 0x49ce10 */
	M32((DWORD)(m->esi + 0x2342381u)) = m->ebx;	/* 49ce08: mov dword ptr [esi + 0x2342381], ebx */
	goto L_49ce46;	/* 49ce0e: jmp 0x49ce46 */
L_49ce10:
	M32((DWORD)(m->esi + 0x2342385u)) = m->ebx;	/* 49ce10: mov dword ptr [esi + 0x2342385], ebx */
	goto L_49ce46;	/* 49ce16: jmp 0x49ce46 */
L_49ce18:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340cfcu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ce18: cmp dword ptr [esi + 0x2340cfc], ebx */
	if (!m->zf) goto L_49ce2e;	/* 49ce1e: jne 0x49ce2e */
	m->eax = M32((DWORD)(m->esi + 0x2342381u));	/* 49ce20: mov eax, dword ptr [esi + 0x2342381] */
	M32((DWORD)(m->esi + 0x234243eu)) = m->eax;	/* 49ce26: mov dword ptr [esi + 0x234243e], eax */
	goto L_49ce3a;	/* 49ce2c: jmp 0x49ce3a */
L_49ce2e:
	m->ecx = M32((DWORD)(m->esi + 0x2342385u));	/* 49ce2e: mov ecx, dword ptr [esi + 0x2342385] */
	M32((DWORD)(m->esi + 0x234243eu)) = m->ecx;	/* 49ce34: mov dword ptr [esi + 0x234243e], ecx */
L_49ce3a:
	m->edx = M32((DWORD)(m->esi + 0x234243eu));	/* 49ce3a: mov edx, dword ptr [esi + 0x234243e] */
	M32((DWORD)(m->esi + 0x234241du)) = m->edx;	/* 49ce40: mov dword ptr [esi + 0x234241d], edx */
L_49ce46:
	m->ecx = M32((DWORD)(m->esi + 0x234240du));	/* 49ce46: mov ecx, dword ptr [esi + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 49ce4c: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49ce4f: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49ce52: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49ce54: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 49ce57: lea ecx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->esi + m->ecx*2 + 0x1755278u));	/* 49ce5a: mov eax, dword ptr [esi + ecx*2 + 0x1755278] */
	m->ecx = M32((DWORD)(m->esi + 0x234243eu));	/* 49ce61: mov ecx, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ce67: cmp eax, ecx */
	if (m->zf) goto L_49d0b3;	/* 49ce69: je 0x49d0b3 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ce6f: cmp eax, ebx */
	if (m->sf != m->of) goto L_49ceed;	/* 49ce71: jl 0x49ceed */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x233c9f0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ce73: cmp dword ptr [esi + 0x233c9f0], ebp */
	if (!m->zf) goto L_49ce82;	/* 49ce79: jne 0x49ce82 */
	m->ecx = m->esi;	/* 49ce7b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49ce82u; native_call(m, 0x49d150u);	/* 49ce7d: call 0x49d150 */
L_49ce82:
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49ce82: mov eax, dword ptr [esi + 0x234240d] */
	m->edx = m->eax;	/* 49ce88: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ce8a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ce8d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ce8f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ce92: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ce94: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ce97: add edx, eax */
	M32((DWORD)(m->esi + m->edx*8 + 0x1eccb60u)) = m->ebx;	/* 49ce99: mov dword ptr [esi + edx*8 + 0x1eccb60], ebx */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49cea0: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = m->eax;	/* 49cea6: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49cea8: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ceab: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49cead: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ceb0: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ceb2: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ceb5: add ecx, eax */
	M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb54u)) = m->ebx;	/* 49ceb7: mov dword ptr [esi + ecx*8 + 0x1eccb54], ebx */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49cebe: mov eax, dword ptr [esi + 0x234240d] */
	m->edx = m->eax;	/* 49cec4: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49cec6: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49cec9: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49cecb: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49cece: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ced0: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ced3: add edx, eax */
	m->ecx = M32((DWORD)(m->esi + m->edx*8 + 0x1eccb58u));	/* 49ced5: mov ecx, dword ptr [esi + edx*8 + 0x1eccb58] */
	m->eax = (DWORD)(m->esi + m->edx*8 + 0x1eccb58u);	/* 49cedc: lea eax, [esi + edx*8 + 0x1eccb58] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49cee3: inc ecx */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 49cee4: mov dword ptr [eax], ecx */
	m->ecx = m->esi;	/* 49cee6: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49ceedu; native_call(m, 0x462150u);	/* 49cee8: call 0x462150 */
L_49ceed:
	m->ecx = M32((DWORD)(m->esi + 0x234240du));	/* 49ceed: mov ecx, dword ptr [esi + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 49cef3: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49cef6: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49cef9: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49cefb: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 49cefe: lea edx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->esi + m->edx*2 + 0x1755278u));	/* 49cf01: mov eax, dword ptr [esi + edx*2 + 0x1755278] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cf08: cmp eax, ebx */
	if (m->sf == m->of) goto L_49cf39;	/* 49cf0a: jge 0x49cf39 */
	m->eax = M32((DWORD)(m->esi + 0x234243eu));	/* 49cf0c: mov eax, dword ptr [esi + 0x234243e] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf12: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf13: push ecx */
	m->ecx = m->esi;	/* 49cf14: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cf1bu; native_call(m, 0x462d30u);	/* 49cf16: call 0x462d30 */
	m->edx = M32((DWORD)(m->esi + 0x234243eu));	/* 49cf1b: mov edx, dword ptr [esi + 0x234243e] */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49cf21: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = (DWORD)(m->esi + 0x2342429u);	/* 49cf27: lea ecx, [esi + 0x2342429] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf2d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf2e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf2f: push eax */
	m->ecx = m->esi;	/* 49cf30: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cf37u; native_call(m, 0x4635b0u);	/* 49cf32: call 0x4635b0 */
	goto L_49cf68;	/* 49cf37: jmp 0x49cf68 */
L_49cf39:
	m->edx = M32((DWORD)(m->esi + 0x234243eu));	/* 49cf39: mov edx, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cf3f: cmp eax, edx */
	if (m->zf) goto L_49cf68;	/* 49cf41: je 0x49cf68 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf43: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf44: push ecx */
	m->ecx = m->esi;	/* 49cf45: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cf4cu; native_call(m, 0x462e30u);	/* 49cf47: call 0x462e30 */
	m->edx = M32((DWORD)(m->esi + 0x234243eu));	/* 49cf4c: mov edx, dword ptr [esi + 0x234243e] */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49cf52: mov eax, dword ptr [esi + 0x234240d] */
	m->ecx = (DWORD)(m->esi + 0x2342429u);	/* 49cf58: lea ecx, [esi + 0x2342429] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf5e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf5f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf60: push eax */
	m->ecx = m->esi;	/* 49cf61: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cf68u; native_call(m, 0x463610u);	/* 49cf63: call 0x463610 */
L_49cf68:
	m->ecx = M32((DWORD)(m->esi + 0x234243eu));	/* 49cf68: mov ecx, dword ptr [esi + 0x234243e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49cf6e: push ecx */
	m->ecx = m->esi;	/* 49cf6f: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cf76u; native_call(m, 0x4613a0u);	/* 49cf71: call 0x4613a0 */
	M32((DWORD)(m->esi + 0x2340d00u)) = m->ebp;	/* 49cf76: mov dword ptr [esi + 0x2340d00], ebp */
	goto L_49d0b3;	/* 49cf7c: jmp 0x49d0b3 */
L_49cf81:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343317u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cf81: cmp dword ptr [esi + 0x2343317], ebp */
	if (!m->zf) goto L_49d0b9;	/* 49cf87: jne 0x49d0b9 */
	goto L_49d0b3;	/* 49cf8d: jmp 0x49d0b3 */
L_49cf92:
	m->eax = M32((DWORD)(0x68039cu));	/* 49cf92: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49cf97: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cf99: cmp eax, ebx */
	if (!m->zf) goto L_49cfc8;	/* 49cf9b: jne 0x49cfc8 */
	m->esp -= 4; M32(m->esp) = 0x49cfa2u; native_call(m, 0x44ace0u);	/* 49cf9d: call 0x44ace0 */
	m->edi = 0x9f63e4u;	/* 49cfa2: mov edi, 0x9f63e4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49cfa7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49cfaa: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 49cfac: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 49cfae: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 49cfb0: dec ecx */
	if (m->zf) goto L_49d0b3;	/* 49cfb1: je 0x49d0b3 */
	{ DWORD v_ = 0x9f63e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 49cfb7: push 0x9f63e4 */
	m->ecx = m->esi;	/* 49cfbc: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49cfc3u; native_call(m, 0x487cb0u);	/* 49cfbe: call 0x487cb0 */
	goto L_49d0b3;	/* 49cfc3: jmp 0x49d0b3 */
L_49cfc8:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343317u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cfc8: cmp dword ptr [esi + 0x2343317], 1 */
	if (!m->zf) goto L_49d0b9;	/* 49cfcf: jne 0x49d0b9 */
	goto L_49d0b3;	/* 49cfd5: jmp 0x49d0b3 */
L_49cfda:
	m->eax = M32((DWORD)(m->esi + 0x234330bu));	/* 49cfda: mov eax, dword ptr [esi + 0x234330b] */
	m->ebp = 0x1u;	/* 49cfe0: mov ebp, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49cfe5: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cfe7: cmp eax, ebp */
	if (!m->zf) goto L_49cff3;	/* 49cfe9: jne 0x49cff3 */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebx;	/* 49cfeb: mov dword ptr [esi + 0x2340cfc], ebx */
	goto L_49d001;	/* 49cff1: jmp 0x49d001 */
L_49cff3:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234330fu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49cff3: cmp dword ptr [esi + 0x234330f], ebp */
	if (!m->zf) goto L_49d001;	/* 49cff9: jne 0x49d001 */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebp;	/* 49cffb: mov dword ptr [esi + 0x2340cfc], ebp */
L_49d001:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343313u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d001: cmp dword ptr [esi + 0x2343313], ebp */
	if (!m->zf) goto L_49d0b9;	/* 49d007: jne 0x49d0b9 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340cfcu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d00d: cmp dword ptr [esi + 0x2340cfc], ebx */
	if (!m->zf) goto L_49d0a3;	/* 49d013: jne 0x49d0a3 */
	M32((DWORD)(m->esi + 0x22f0410u)) = m->ebx;	/* 49d019: mov dword ptr [esi + 0x22f0410], ebx */
	m->edx = (DWORD)(m->esi + 0x22ee228u);	/* 49d01f: lea edx, [esi + 0x22ee228] */
	M32((DWORD)(m->esi + 0x22f0408u)) = m->ebx;	/* 49d025: mov dword ptr [esi + 0x22f0408], ebx */
	M32((DWORD)(m->esi + 0x22f040cu)) = m->ebx;	/* 49d02b: mov dword ptr [esi + 0x22f040c], ebx */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 49d031: mov ecx, dword ptr [edx] */
	m->eax = (DWORD)(m->esi + 0x233ca04u);	/* 49d033: lea eax, [esi + 0x233ca04] */
	M32((DWORD)(m->esi + 0x233ca04u)) = m->ecx;	/* 49d039: mov dword ptr [esi + 0x233ca04], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 49d03f: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 49d042: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 49d045: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 49d048: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->esi + 0x22ee234u));	/* 49d04b: mov eax, dword ptr [esi + 0x22ee234] */
	M32((DWORD)(m->esi + 0x233ca28u)) = m->eax;	/* 49d051: mov dword ptr [esi + 0x233ca28], eax */
	m->ecx = M32((DWORD)(m->esi + 0x22ee238u));	/* 49d057: mov ecx, dword ptr [esi + 0x22ee238] */
	M32((DWORD)(m->esi + 0x233ca2cu)) = m->ecx;	/* 49d05d: mov dword ptr [esi + 0x233ca2c], ecx */
	m->ecx = m->esi;	/* 49d063: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49d06au; native_call(m, 0x462850u);	/* 49d065: call 0x462850 */
	goto L_49d0b3;	/* 49d06a: jmp 0x49d0b3 */
L_49d06c:
	m->eax = M32((DWORD)(m->esi + 0x234330bu));	/* 49d06c: mov eax, dword ptr [esi + 0x234330b] */
	m->ebp = 0x1u;	/* 49d072: mov ebp, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49d077: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d079: cmp eax, ebp */
	if (!m->zf) goto L_49d085;	/* 49d07b: jne 0x49d085 */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebx;	/* 49d07d: mov dword ptr [esi + 0x2340cfc], ebx */
	goto L_49d093;	/* 49d083: jmp 0x49d093 */
L_49d085:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234330fu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d085: cmp dword ptr [esi + 0x234330f], ebp */
	if (!m->zf) goto L_49d093;	/* 49d08b: jne 0x49d093 */
	M32((DWORD)(m->esi + 0x2340cfcu)) = m->ebp;	/* 49d08d: mov dword ptr [esi + 0x2340cfc], ebp */
L_49d093:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343313u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d093: cmp dword ptr [esi + 0x2343313], ebp */
	if (!m->zf) goto L_49d0ab;	/* 49d099: jne 0x49d0ab */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340cfcu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d09b: cmp dword ptr [esi + 0x2340cfc], ebx */
	if (!m->zf) goto L_49d0b3;	/* 49d0a1: jne 0x49d0b3 */
L_49d0a3:
	M32((DWORD)(m->esi + 0x23432cfu)) = m->ebp;	/* 49d0a3: mov dword ptr [esi + 0x23432cf], ebp */
	goto L_49d0b3;	/* 49d0a9: jmp 0x49d0b3 */
L_49d0ab:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343317u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d0ab: cmp dword ptr [esi + 0x2343317], ebp */
	if (!m->zf) goto L_49d0b9;	/* 49d0b1: jne 0x49d0b9 */
L_49d0b3:
	M32((DWORD)(m->esi + 0x2340cf4u)) = m->ebx;	/* 49d0b3: mov dword ptr [esi + 0x2340cf4], ebx */
L_49d0b9:
	m->edx = M32((DWORD)(m->esi + 0x234330bu));	/* 49d0b9: mov edx, dword ptr [esi + 0x234330b] */
	m->edi = M32((DWORD)(m->esi + 0x234330fu));	/* 49d0bf: mov edi, dword ptr [esi + 0x234330f] */
	m->ecx = M32((DWORD)(m->esi + 0x2343313u));	/* 49d0c5: mov ecx, dword ptr [esi + 0x2343313] */
	m->eax = M32((DWORD)(m->esi + 0x2343317u));	/* 49d0cb: mov eax, dword ptr [esi + 0x2343317] */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49d0d1: or edx, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 49d0d3: pop edi */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49d0d4: or edx, ecx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 49d0d6: pop ebp */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49d0d7: or edx, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49d0d9: pop ebx */
	if (m->zf) goto L_49d0e8;	/* 49d0da: je 0x49d0e8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 49d0dc: push 0x64 */
	{ DWORD v_ = 0x9u; m->esp -= 4; M32(m->esp) = v_; }	/* 49d0de: push 9 */
	m->esp -= 4; M32(m->esp) = 0x49d0e5u; native_call(m, 0x456e50u);	/* 49d0e0: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d0e5: add esp, 8 */
L_49d0e8:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 49d0e8: fld dword ptr [esi + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x2340c9cu));	/* 49d0eb: fadd dword ptr [esi + 0x2340c9c] */
	MF((DWORD)(m->esi + 0x2340c9cu)) = (float)ST(0); FPOP();	/* 49d0f1: fstp dword ptr [esi + 0x2340c9c] */
	m->esi = M32(m->esp); m->esp += 4;	/* 49d0f7: pop esi */
	m->esp += 4 + 0; return;	/* 49d0f8: ret  */
}

/* wnd_setCursor (0x4314e0), lifted by tools/lift.py */
static void lift_4314e0(X86 *m)
{
	m->ecx = M32((DWORD)(0x9087b4u));	/* 4314e0: mov ecx, dword ptr [0x9087b4] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4314e6: test ecx, ecx */
	if (m->zf) goto L_4314f0;	/* 4314e8: je 0x4314f0 */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 4314ea: mov eax, dword ptr [ecx] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4314ec: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4314f0u; native_call(m, M32((DWORD)(m->eax + 0x0u)));	/* 4314ee: call dword ptr [eax] */
L_4314f0:
	m->ecx = M32((DWORD)(0x76d3ecu));	/* 4314f0: mov ecx, dword ptr [0x76d3ec] */
	m->edx = M32((DWORD)(0x76d430u));	/* 4314f6: mov edx, dword ptr [0x76d430] */
	m->eax = M32((DWORD)(0x67eefcu));	/* 4314fc: mov eax, dword ptr [0x67eefc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 431501: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 431502: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431503: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 431505: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 431506: push eax */
	m->esp -= 4; M32(m->esp) = 0x43150cu; native_call(m, 0x42eed0u);	/* 431507: call 0x42eed0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43150c: add esp, 0x10 */
	{ DWORD v_ = 0x7f00u; m->esp -= 4; M32(m->esp) = v_; }	/* 43150f: push 0x7f00 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 431514: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43151cu; native_call(m, M32(0x4a933cu));	/* 431516: call dword ptr [0x4a933c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43151c: push eax */
	m->esp -= 4; M32(m->esp) = 0x431523u; native_call(m, M32(0x4a9340u));	/* 43151d: call dword ptr [0x4a9340] */
	m->esp -= 4; M32(m->esp) = 0x431528u; native_call(m, 0x4014c0u);	/* 431523: call 0x4014c0 */
	m->esp -= 4; M32(m->esp) = 0x43152du; native_call(m, 0x457310u);	/* 431528: call 0x457310 */
	m->esi = 0x4dd4d4u;	/* 43152d: mov esi, 0x4dd4d4 */
L_431532:
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 431532: mov ecx, dword ptr [esi] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 431534: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43153au; native_call(m, 0x467d60u);	/* 431535: call 0x467d60 */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43153a: add esi, 4 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43153d: add esp, 4 */
	{ DWORD a_ = m->esi, b_ = 0x4dd4fcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431540: cmp esi, 0x4dd4fc */
	if (m->sf != m->of) goto L_431532;	/* 431546: jl 0x431532 */
	m->esp -= 4; M32(m->esp) = 0x43154du; native_call(m, 0x456cd0u);	/* 431548: call 0x456cd0 */
	m->esp -= 4; M32(m->esp) = 0x431552u; native_call(m, 0x467b70u);	/* 43154d: call 0x467b70 */
	m->esi = M32(m->esp); m->esp += 4;	/* 431552: pop esi */
	m->esp += 4 + 0; return;	/* 431553: ret  */
}

/* scene_loadPath (0x48fd50), lifted by tools/lift.py */
static void lift_48fd50(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48fd50: sub esp, 0x100 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48fd56: push esi */
	m->esi = m->ecx;	/* 48fd57: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x2149308u));	/* 48fd59: mov eax, dword ptr [esi + 0x2149308] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48fd5f: test eax, eax */
	if (m->zf) goto L_48fdd0;	/* 48fd61: je 0x48fdd0 */
	m->eax = M32((DWORD)(m->esi + 0x2148ee0u));	/* 48fd63: mov eax, dword ptr [esi + 0x2148ee0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48fd69: test eax, eax */
	if (!m->zf) goto L_48fd84;	/* 48fd6b: jne 0x48fd84 */
	m->eax = (DWORD)(m->esi + 0x2149208u);	/* 48fd6d: lea eax, [esi + 0x2149208] */
	{ DWORD v_ = 0x4c45e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fd73: push 0x4c45e4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48fd78: push eax */
	m->ecx = (DWORD)(m->esi + 0x2148ed8u);	/* 48fd79: lea ecx, [esi + 0x2148ed8] */
	m->esp -= 4; M32(m->esp) = 0x48fd84u; native_call(m, 0x48b430u);	/* 48fd7f: call 0x48b430 */
L_48fd84:
	m->ecx = M32((DWORD)(m->esp + 0x108u));	/* 48fd84: mov ecx, dword ptr [esp + 0x108] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fd8b: push ecx */
	m->ecx = (DWORD)(m->esi + 0x2148ed8u);	/* 48fd8c: lea ecx, [esi + 0x2148ed8] */
	m->esp -= 4; M32(m->esp) = 0x48fd97u; native_call(m, 0x48b440u);	/* 48fd92: call 0x48b440 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48fd97: test eax, eax */
	if (!m->zf) goto L_48fda1;	/* 48fd99: jne 0x48fda1 */
	M32((DWORD)(m->esi + 0x2149308u)) = m->eax;	/* 48fd9b: mov dword ptr [esi + 0x2149308], eax */
L_48fda1:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x2149108u))) & 0xff) << 0);	/* 48fda1: mov cl, byte ptr [esi + 0x2149108] */
	m->eax = (DWORD)(m->esi + 0x2149108u);	/* 48fda7: lea eax, [esi + 0x2149108] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48fdad: test cl, cl */
	if (m->zf) goto L_48fdd0;	/* 48fdaf: je 0x48fdd0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48fdb1: push eax */
	m->edx = (DWORD)(m->esp + 0x8u);	/* 48fdb2: lea edx, [esp + 8] */
	{ DWORD v_ = 0x4c8304u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fdb6: push 0x4c8304 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fdbb: push edx */
	m->esp -= 4; M32(m->esp) = 0x48fdc1u; native_call(m, 0x49e9ddu);	/* 48fdbc: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 48fdc1: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 48fdc5: push 0x64 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48fdc7: push eax */
	m->esp -= 4; M32(m->esp) = 0x48fdcdu; native_call(m, 0x457080u);	/* 48fdc8: call 0x457080 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48fdcd: add esp, 0x14 */
L_48fdd0:
	m->esi = M32(m->esp); m->esp += 4;	/* 48fdd0: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48fdd1: add esp, 0x100 */
	m->esp += 4 + 4; return;	/* 48fdd7: ret 4 */
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
