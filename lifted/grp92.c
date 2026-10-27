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

static void lift_40da40(X86 *m);

/* armc_buildPartLists (0x40da40), lifted by tools/lift.py */
static void lift_40da40(X86 *m)
{
	m->eax = M32((DWORD)(0x4dc24cu));	/* 40da40: mov eax, dword ptr [0x4dc24c] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40da45: cmp eax, 3 */
	if (m->zf) goto L_40da5c;	/* 40da48: je 0x40da5c */
	m->esp -= 4; M32(m->esp) = 0x40da4fu; native_call(m, 0x40da4fu + M32(0x40da4bu));	/* patch code (0xb68e80 here) */	/* 40da4a: call 0xb68e80 */
	;	/* 40da4f: nop  */
	{ DWORD a_ = m->ecx, b_ = 0x7fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40da50: cmp ecx, 0x7f */
	if (m->sf != m->of) goto L_40da63;	/* 40da53: jl 0x40da63 */
	m->ecx = 0xeu;	/* 40da55: mov ecx, 0xe */
	goto L_40da63;	/* 40da5a: jmp 0x40da63 */
L_40da5c:
	m->ecx = M32((DWORD)(0x9dd5d8u));	/* 40da5c: mov ecx, dword ptr [0x9dd5d8] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40da62: dec ecx */
L_40da63:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40da63: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40da64: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 40da65: xor ebp, ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40da67: push esi */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40da68: cmp eax, 3 */
	M32((DWORD)(0x4dc870u)) = m->ecx;	/* 40da6b: mov dword ptr [0x4dc870], ecx */
	M32((DWORD)(0x4dc784u)) = m->ecx;	/* 40da71: mov dword ptr [0x4dc784], ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40da77: push edi */
	M32((DWORD)(0x4dc780u)) = m->ebp;	/* 40da78: mov dword ptr [0x4dc780], ebp */
	M32((DWORD)(0x4dcc60u)) = m->ebp;	/* 40da7e: mov dword ptr [0x4dcc60], ebp */
	M32((DWORD)(0x4dca90u)) = m->ebp;	/* 40da84: mov dword ptr [0x4dca90], ebp */
	M32((DWORD)(0x4dca94u)) = m->ebp;	/* 40da8a: mov dword ptr [0x4dca94], ebp */
	M32((DWORD)(0x4dc890u)) = m->ebp;	/* 40da90: mov dword ptr [0x4dc890], ebp */
	if (m->zf) goto L_40dc28;	/* 40da96: je 0x40dc28 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40da9c: cmp ecx, ebp */
	if (m->sf != m->of) goto L_40db8b;	/* 40da9e: jl 0x40db8b */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40daa4: xor eax, eax */
	m->ebx = (DWORD)(m->ecx + 0x1u);	/* 40daa6: lea ebx, [ecx + 1] */
L_40daa9:
	m->ecx = M32((DWORD)(m->eax + 0x4ad5f0u));	/* 40daa9: mov ecx, dword ptr [eax + 0x4ad5f0] */
	m->esi = (DWORD)(m->eax + 0x4ad5f4u);	/* 40daaf: lea esi, [eax + 0x4ad5f4] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40dab5: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dab6: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40dad5;	/* 40dab9: jle 0x40dad5 */
	m->edx = M32((DWORD)(0x4dc780u));	/* 40dabb: mov edx, dword ptr [0x4dc780] */
	m->edi = (DWORD)(m->edx*4 + 0x4dc3e8u);	/* 40dac1: lea edi, [edx*4 + 0x4dc3e8] */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40dac8: lea edx, [ecx - 1] */
	m->ecx = m->edx;	/* 40dacb: mov ecx, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dacd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dc780u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4dc780u)) = r_; }	/* 40dacf: add dword ptr [0x4dc780], edx */
L_40dad5:
	m->ecx = M32((DWORD)(m->eax + 0x4ad910u));	/* 40dad5: mov ecx, dword ptr [eax + 0x4ad910] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40dadb: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dadc: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40db01;	/* 40dadf: jle 0x40db01 */
	m->edx = M32((DWORD)(0x4dcc60u));	/* 40dae1: mov edx, dword ptr [0x4dcc60] */
	m->esi = (DWORD)(m->eax + 0x4ad914u);	/* 40dae7: lea esi, [eax + 0x4ad914] */
	m->edi = (DWORD)(m->edx*4 + 0x4dcd6cu);	/* 40daed: lea edi, [edx*4 + 0x4dcd6c] */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40daf4: lea edx, [ecx - 1] */
	m->ecx = m->edx;	/* 40daf7: mov ecx, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40daf9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dcc60u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4dcc60u)) = r_; }	/* 40dafb: add dword ptr [0x4dcc60], edx */
L_40db01:
	m->ecx = M32((DWORD)(m->eax + 0x4adc30u));	/* 40db01: mov ecx, dword ptr [eax + 0x4adc30] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40db07: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40db08: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40db2d;	/* 40db0b: jle 0x40db2d */
	m->edx = M32((DWORD)(0x4dca90u));	/* 40db0d: mov edx, dword ptr [0x4dca90] */
	m->esi = (DWORD)(m->eax + 0x4adc34u);	/* 40db13: lea esi, [eax + 0x4adc34] */
	m->edi = (DWORD)(m->edx*4 + 0x4dc964u);	/* 40db19: lea edi, [edx*4 + 0x4dc964] */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40db20: lea edx, [ecx - 1] */
	m->ecx = m->edx;	/* 40db23: mov ecx, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40db25: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dca90u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4dca90u)) = r_; }	/* 40db27: add dword ptr [0x4dca90], edx */
L_40db2d:
	m->ecx = M32((DWORD)(m->eax + 0x4adf50u));	/* 40db2d: mov ecx, dword ptr [eax + 0x4adf50] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40db33: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40db34: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40db59;	/* 40db37: jle 0x40db59 */
	m->edx = M32((DWORD)(0x4dca94u));	/* 40db39: mov edx, dword ptr [0x4dca94] */
	m->esi = (DWORD)(m->eax + 0x4adf54u);	/* 40db3f: lea esi, [eax + 0x4adf54] */
	m->edi = (DWORD)(m->edx*4 + 0x4dc89cu);	/* 40db45: lea edi, [edx*4 + 0x4dc89c] */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40db4c: lea edx, [ecx - 1] */
	m->ecx = m->edx;	/* 40db4f: mov ecx, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40db51: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dca94u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4dca94u)) = r_; }	/* 40db53: add dword ptr [0x4dca94], edx */
L_40db59:
	m->ecx = M32((DWORD)(m->eax + 0x4ae270u));	/* 40db59: mov ecx, dword ptr [eax + 0x4ae270] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40db5f: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40db60: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40db7b;	/* 40db63: jle 0x40db7b */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40db65: lea edx, [ecx - 1] */
	m->edi = (DWORD)(m->ebp*4 + 0x4dbd7cu);	/* 40db68: lea edi, [ebp*4 + 0x4dbd7c] */
	m->ecx = m->edx;	/* 40db6f: mov ecx, edx */
	m->esi = (DWORD)(m->eax + 0x4ae274u);	/* 40db71: lea esi, [eax + 0x4ae274] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40db77: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = m->ebp, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 40db79: add ebp, edx */
L_40db7b:
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40db7b: add eax, 0x28 */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 40db7e: dec ebx */
	if (!m->zf) goto L_40daa9;	/* 40db7f: jne 0x40daa9 */
	M32((DWORD)(0x4dc890u)) = m->ebp;	/* 40db85: mov dword ptr [0x4dc890], ebp */
L_40db8b:
	m->ebp = M32((DWORD)(0x4dc784u));	/* 40db8b: mov ebp, dword ptr [0x4dc784] */
	m->ebx = 0x1u;	/* 40db91: mov ebx, 1 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40db96: test ebp, ebp */
	M32((DWORD)(0x4dc79cu)) = 0xffffffffu;	/* 40db98: mov dword ptr [0x4dc79c], 0xffffffff */
	M32((DWORD)(0x4dc244u)) = m->ebx;	/* 40dba2: mov dword ptr [0x4dc244], ebx */
	if (m->sf != m->of) goto L_40dbdb;	/* 40dba8: jl 0x40dbdb */
	m->edx = 0x4ae594u;	/* 40dbaa: mov edx, 0x4ae594 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40dbaf: inc ebp */
L_40dbb0:
	m->eax = M32((DWORD)(m->edx + 0xfffffffcu));	/* 40dbb0: mov eax, dword ptr [edx - 4] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40dbb3: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dbb4: cmp eax, 1 */
	if (m->zf || m->sf != m->of) goto L_40dbc9;	/* 40dbb7: jle 0x40dbc9 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40dbb9: dec eax */
	m->edi = (DWORD)(m->ebx*4 + 0x4dc79cu);	/* 40dbba: lea edi, [ebx*4 + 0x4dc79c] */
	m->ecx = m->eax;	/* 40dbc1: mov ecx, eax */
	m->esi = m->edx;	/* 40dbc3: mov esi, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dbc5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40dbc7: add ebx, eax */
L_40dbc9:
	{ DWORD a_ = m->edx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40dbc9: add edx, 0x28 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 40dbcc: dec ebp */
	if (!m->zf) goto L_40dbb0;	/* 40dbcd: jne 0x40dbb0 */
	m->ebp = M32((DWORD)(0x4dc784u));	/* 40dbcf: mov ebp, dword ptr [0x4dc784] */
	M32((DWORD)(0x4dc244u)) = m->ebx;	/* 40dbd5: mov dword ptr [0x4dc244], ebx */
L_40dbdb:
	m->ebx = 0x1u;	/* 40dbdb: mov ebx, 1 */
	M32((DWORD)(0x4dcca4u)) = 0xffffffffu;	/* 40dbe0: mov dword ptr [0x4dcca4], 0xffffffff */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40dbea: test ebp, ebp */
	M32((DWORD)(0x4dc778u)) = m->ebx;	/* 40dbec: mov dword ptr [0x4dc778], ebx */
	if (m->sf != m->of) goto L_40ddab;	/* 40dbf2: jl 0x40ddab */
	m->edx = 0x4ae8b4u;	/* 40dbf8: mov edx, 0x4ae8b4 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40dbfd: inc ebp */
L_40dbfe:
	m->eax = M32((DWORD)(m->edx + 0xfffffffcu));	/* 40dbfe: mov eax, dword ptr [edx - 4] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40dc01: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dc02: cmp eax, 1 */
	if (m->zf || m->sf != m->of) goto L_40dc17;	/* 40dc05: jle 0x40dc17 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40dc07: dec eax */
	m->edi = (DWORD)(m->ebx*4 + 0x4dcca4u);	/* 40dc08: lea edi, [ebx*4 + 0x4dcca4] */
	m->ecx = m->eax;	/* 40dc0f: mov ecx, eax */
	m->esi = m->edx;	/* 40dc11: mov esi, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dc13: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40dc15: add ebx, eax */
L_40dc17:
	{ DWORD a_ = m->edx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40dc17: add edx, 0x28 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 40dc1a: dec ebp */
	if (!m->zf) goto L_40dbfe;	/* 40dc1b: jne 0x40dbfe */
	m->edi = M32(m->esp); m->esp += 4;	/* 40dc1d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40dc1e: pop esi */
	M32((DWORD)(0x4dc778u)) = m->ebx;	/* 40dc1f: mov dword ptr [0x4dc778], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40dc25: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40dc26: pop ebx */
	m->esp += 4 + 0; return;	/* 40dc27: ret  */
L_40dc28:
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dc28: cmp ecx, ebp */
	if (m->sf != m->of) goto L_40dd17;	/* 40dc2a: jl 0x40dd17 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40dc30: xor eax, eax */
	m->ebx = (DWORD)(m->ecx + 0x1u);	/* 40dc32: lea ebx, [ecx + 1] */
L_40dc35:
	m->ecx = M32((DWORD)(m->eax + 0x4aebd0u));	/* 40dc35: mov ecx, dword ptr [eax + 0x4aebd0] */
	m->esi = (DWORD)(m->eax + 0x4aebd4u);	/* 40dc3b: lea esi, [eax + 0x4aebd4] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40dc41: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dc42: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40dc61;	/* 40dc45: jle 0x40dc61 */
	m->edx = M32((DWORD)(0x4dc780u));	/* 40dc47: mov edx, dword ptr [0x4dc780] */
	m->edi = (DWORD)(m->edx*4 + 0x4dc3e8u);	/* 40dc4d: lea edi, [edx*4 + 0x4dc3e8] */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40dc54: lea edx, [ecx - 1] */
	m->ecx = m->edx;	/* 40dc57: mov ecx, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dc59: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dc780u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4dc780u)) = r_; }	/* 40dc5b: add dword ptr [0x4dc780], edx */
L_40dc61:
	m->ecx = M32((DWORD)(m->eax + 0x4aeef0u));	/* 40dc61: mov ecx, dword ptr [eax + 0x4aeef0] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40dc67: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dc68: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40dc8d;	/* 40dc6b: jle 0x40dc8d */
	m->edx = M32((DWORD)(0x4dcc60u));	/* 40dc6d: mov edx, dword ptr [0x4dcc60] */
	m->esi = (DWORD)(m->eax + 0x4aeef4u);	/* 40dc73: lea esi, [eax + 0x4aeef4] */
	m->edi = (DWORD)(m->edx*4 + 0x4dcd6cu);	/* 40dc79: lea edi, [edx*4 + 0x4dcd6c] */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40dc80: lea edx, [ecx - 1] */
	m->ecx = m->edx;	/* 40dc83: mov ecx, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dc85: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dcc60u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4dcc60u)) = r_; }	/* 40dc87: add dword ptr [0x4dcc60], edx */
L_40dc8d:
	m->ecx = M32((DWORD)(m->eax + 0x4af210u));	/* 40dc8d: mov ecx, dword ptr [eax + 0x4af210] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40dc93: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dc94: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40dcb9;	/* 40dc97: jle 0x40dcb9 */
	m->edx = M32((DWORD)(0x4dca90u));	/* 40dc99: mov edx, dword ptr [0x4dca90] */
	m->esi = (DWORD)(m->eax + 0x4af214u);	/* 40dc9f: lea esi, [eax + 0x4af214] */
	m->edi = (DWORD)(m->edx*4 + 0x4dc964u);	/* 40dca5: lea edi, [edx*4 + 0x4dc964] */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40dcac: lea edx, [ecx - 1] */
	m->ecx = m->edx;	/* 40dcaf: mov ecx, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dcb1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dca90u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4dca90u)) = r_; }	/* 40dcb3: add dword ptr [0x4dca90], edx */
L_40dcb9:
	m->ecx = M32((DWORD)(m->eax + 0x4af530u));	/* 40dcb9: mov ecx, dword ptr [eax + 0x4af530] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40dcbf: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dcc0: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40dce5;	/* 40dcc3: jle 0x40dce5 */
	m->edx = M32((DWORD)(0x4dca94u));	/* 40dcc5: mov edx, dword ptr [0x4dca94] */
	m->esi = (DWORD)(m->eax + 0x4af534u);	/* 40dccb: lea esi, [eax + 0x4af534] */
	m->edi = (DWORD)(m->edx*4 + 0x4dc89cu);	/* 40dcd1: lea edi, [edx*4 + 0x4dc89c] */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40dcd8: lea edx, [ecx - 1] */
	m->ecx = m->edx;	/* 40dcdb: mov ecx, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dcdd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = M32((DWORD)(0x4dca94u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(0x4dca94u)) = r_; }	/* 40dcdf: add dword ptr [0x4dca94], edx */
L_40dce5:
	m->ecx = M32((DWORD)(m->eax + 0x4af850u));	/* 40dce5: mov ecx, dword ptr [eax + 0x4af850] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40dceb: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dcec: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_40dd07;	/* 40dcef: jle 0x40dd07 */
	m->edx = (DWORD)(m->ecx + 0xffffffffu);	/* 40dcf1: lea edx, [ecx - 1] */
	m->edi = (DWORD)(m->ebp*4 + 0x4dbd7cu);	/* 40dcf4: lea edi, [ebp*4 + 0x4dbd7c] */
	m->ecx = m->edx;	/* 40dcfb: mov ecx, edx */
	m->esi = (DWORD)(m->eax + 0x4af854u);	/* 40dcfd: lea esi, [eax + 0x4af854] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dd03: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = m->ebp, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 40dd05: add ebp, edx */
L_40dd07:
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40dd07: add eax, 0x28 */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 40dd0a: dec ebx */
	if (!m->zf) goto L_40dc35;	/* 40dd0b: jne 0x40dc35 */
	M32((DWORD)(0x4dc890u)) = m->ebp;	/* 40dd11: mov dword ptr [0x4dc890], ebp */
L_40dd17:
	m->ebp = M32((DWORD)(0x4dc784u));	/* 40dd17: mov ebp, dword ptr [0x4dc784] */
	m->ebx = 0x1u;	/* 40dd1d: mov ebx, 1 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40dd22: test ebp, ebp */
	M32((DWORD)(0x4dc79cu)) = 0xffffffffu;	/* 40dd24: mov dword ptr [0x4dc79c], 0xffffffff */
	M32((DWORD)(0x4dc244u)) = m->ebx;	/* 40dd2e: mov dword ptr [0x4dc244], ebx */
	if (m->sf != m->of) goto L_40dd67;	/* 40dd34: jl 0x40dd67 */
	m->edx = 0x4afb74u;	/* 40dd36: mov edx, 0x4afb74 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40dd3b: inc ebp */
L_40dd3c:
	m->eax = M32((DWORD)(m->edx + 0xfffffffcu));	/* 40dd3c: mov eax, dword ptr [edx - 4] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40dd3f: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dd40: cmp eax, 1 */
	if (m->zf || m->sf != m->of) goto L_40dd55;	/* 40dd43: jle 0x40dd55 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40dd45: dec eax */
	m->edi = (DWORD)(m->ebx*4 + 0x4dc79cu);	/* 40dd46: lea edi, [ebx*4 + 0x4dc79c] */
	m->ecx = m->eax;	/* 40dd4d: mov ecx, eax */
	m->esi = m->edx;	/* 40dd4f: mov esi, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dd51: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40dd53: add ebx, eax */
L_40dd55:
	{ DWORD a_ = m->edx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40dd55: add edx, 0x28 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 40dd58: dec ebp */
	if (!m->zf) goto L_40dd3c;	/* 40dd59: jne 0x40dd3c */
	m->ebp = M32((DWORD)(0x4dc784u));	/* 40dd5b: mov ebp, dword ptr [0x4dc784] */
	M32((DWORD)(0x4dc244u)) = m->ebx;	/* 40dd61: mov dword ptr [0x4dc244], ebx */
L_40dd67:
	m->ebx = 0x1u;	/* 40dd67: mov ebx, 1 */
	M32((DWORD)(0x4dcca4u)) = 0xffffffffu;	/* 40dd6c: mov dword ptr [0x4dcca4], 0xffffffff */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40dd76: test ebp, ebp */
	M32((DWORD)(0x4dc778u)) = m->ebx;	/* 40dd78: mov dword ptr [0x4dc778], ebx */
	if (m->sf != m->of) goto L_40ddab;	/* 40dd7e: jl 0x40ddab */
	m->edx = 0x4afe94u;	/* 40dd80: mov edx, 0x4afe94 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40dd85: inc ebp */
L_40dd86:
	m->eax = M32((DWORD)(m->edx + 0xfffffffcu));	/* 40dd86: mov eax, dword ptr [edx - 4] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40dd89: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40dd8a: cmp eax, 1 */
	if (m->zf || m->sf != m->of) goto L_40dd9f;	/* 40dd8d: jle 0x40dd9f */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40dd8f: dec eax */
	m->edi = (DWORD)(m->ebx*4 + 0x4dcca4u);	/* 40dd90: lea edi, [ebx*4 + 0x4dcca4] */
	m->ecx = m->eax;	/* 40dd97: mov ecx, eax */
	m->esi = m->edx;	/* 40dd99: mov esi, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40dd9b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40dd9d: add ebx, eax */
L_40dd9f:
	{ DWORD a_ = m->edx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40dd9f: add edx, 0x28 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 40dda2: dec ebp */
	if (!m->zf) goto L_40dd86;	/* 40dda3: jne 0x40dd86 */
	M32((DWORD)(0x4dc778u)) = m->ebx;	/* 40dda5: mov dword ptr [0x4dc778], ebx */
L_40ddab:
	m->edi = M32(m->esp); m->esp += 4;	/* 40ddab: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40ddac: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40ddad: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40ddae: pop ebx */
	m->esp += 4 + 0; return;	/* 40ddaf: ret  */
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
