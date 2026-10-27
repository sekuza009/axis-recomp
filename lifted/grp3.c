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

static void lift_460270(X86 *m);
static void lift_41cf20(X86 *m);
static void lift_41d280(X86 *m);
static void lift_42eca0(X86 *m);

/* cfg_writeDefaultAxisCfg (0x42eca0), lifted by tools/lift.py */
static void lift_42eca0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x208u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42eca0: sub esp, 0x208 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42eca6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42eca9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x84u);	/* 42ecab: lea edx, [esp + 0x84] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ecb2: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42ecb3: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ecb4: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ecb5: push edi */
	m->edi = 0x9dae7cu;	/* 42ecb6: mov edi, 0x9dae7c */
	{ DWORD v_ = 0x4ad5e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ecbb: push 0x4ad5e0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42ecc0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42ecc2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42ecc4: sub edi, ecx */
	m->eax = m->ecx;	/* 42ecc6: mov eax, ecx */
	m->esi = m->edi;	/* 42ecc8: mov esi, edi */
	m->edi = m->edx;	/* 42ecca: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x98u);	/* 42eccc: lea edx, [esp + 0x98] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42ecd3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42ecd6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42ecd8: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ecda: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ecdc: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42ecdf: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2198u;	/* 42ece1: mov edi, 0x4b2198 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ece6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42ece9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42eceb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42eced: sub edi, ecx */
	m->esi = m->edi;	/* 42ecef: mov esi, edi */
	m->ebx = m->ecx;	/* 42ecf1: mov ebx, ecx */
	m->edi = m->edx;	/* 42ecf3: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ecf5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42ecf8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 42ecfa: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42ecfc: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42ecfd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42ed00: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 42ed02: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ed04: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42ed07: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = 0x8u;	/* 42ed09: mov ecx, 8 */
	m->edi = 0x4dedb0u;	/* 42ed0e: mov edi, 0x4dedb0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42ed13: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x8u;	/* 42ed15: mov ecx, 8 */
	m->edi = 0x4ded20u;	/* 42ed1a: mov edi, 0x4ded20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42ed1f: rep stosd dword ptr es:[edi], eax */
	m->eax = (DWORD)(m->esp + 0x98u);	/* 42ed21: lea eax, [esp + 0x98] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42ed28: push eax */
	m->esp -= 4; M32(m->esp) = 0x42ed2eu; native_call(m, 0x49e9cau);	/* 42ed29: call 0x49e9ca */
	m->ebp = m->eax;	/* 42ed2e: mov ebp, eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 42ed30: xor ebx, ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ed32: add esp, 8 */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ed35: cmp ebp, ebx */
	if (m->zf) goto L_42eda2;	/* 42ed37: je 0x42eda2 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42ed39: push ebp */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 42ed3a: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ed3e: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ed40: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42ed46u; native_call(m, 0x49ecd7u);	/* 42ed41: call 0x49ecd7 */
	m->edi = (DWORD)(m->esp + 0x1cu);	/* 42ed46: lea edi, [esp + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ed4a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ed4d: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ed4f: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42ed52: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42ed54: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42ed56: dec ecx */
	m->edi = 0x4b0f50u;	/* 42ed57: mov edi, 0x4b0f50 */
	m->esi = (DWORD)(m->esp + 0x10u);	/* 42ed5c: lea esi, [esp + 0x10] */
	M8((DWORD)(m->esp + m->ecx*1 + 0xfu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42ed60: mov byte ptr [esp + ecx + 0xf], bl */
L_42ed64:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 42ed64: mov dl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 42ed66: mov cl, byte ptr [edi] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42ed68: mov al, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42ed6a: cmp dl, cl */
	if (!m->zf) goto L_42ed8c;	/* 42ed6c: jne 0x42ed8c */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42ed6e: cmp al, bl */
	if (m->zf) goto L_42ed88;	/* 42ed70: je 0x42ed88 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 42ed72: mov cl, byte ptr [esi + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 42ed75: mov dl, byte ptr [edi + 1] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((((m->ecx >> 0) & 0xff)) & 0xff) << 0);	/* 42ed78: mov al, cl */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42ed7a: cmp cl, dl */
	if (!m->zf) goto L_42ed8c;	/* 42ed7c: jne 0x42ed8c */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42ed7e: add esi, 2 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42ed81: add edi, 2 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42ed84: cmp al, bl */
	if (!m->zf) goto L_42ed64;	/* 42ed86: jne 0x42ed64 */
L_42ed88:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42ed88: xor eax, eax */
	goto L_42ed91;	/* 42ed8a: jmp 0x42ed91 */
L_42ed8c:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42ed8c: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42ed8e: sbb eax, -1 */
L_42ed91:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ed91: cmp eax, ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42ed93: push ebp */
	if (m->zf) goto L_42ee76;	/* 42ed94: je 0x42ee76 */
	m->esp -= 4; M32(m->esp) = 0x42ed9fu; native_call(m, 0x49e7e0u);	/* 42ed9a: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ed9f: add esp, 4 */
L_42eda2:
	m->edi = 0x4ad4b0u;	/* 42eda2: mov edi, 0x4ad4b0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42eda7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42edaa: xor eax, eax */
	M32((DWORD)(0x4e0c9cu)) = m->ebx;	/* 42edac: mov dword ptr [0x4e0c9c], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42edb2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42edb4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42edb6: sub edi, ecx */
	M32((DWORD)(0x83a9c4u)) = m->ebx;	/* 42edb8: mov dword ptr [0x83a9c4], ebx */
	m->edx = m->ecx;	/* 42edbe: mov edx, ecx */
	m->esi = m->edi;	/* 42edc0: mov esi, edi */
	m->edi = 0x4dedb0u;	/* 42edc2: mov edi, 0x4dedb0 */
	M32((DWORD)(0x83a9c0u)) = m->ebx;	/* 42edc7: mov dword ptr [0x83a9c0], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42edcd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42edd0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42edd2: mov ecx, edx */
	M32((DWORD)(0x83a9d4u)) = m->ebx;	/* 42edd4: mov dword ptr [0x83a9d4], ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42edda: and ecx, 3 */
	M32((DWORD)(0x83a9d8u)) = m->ebx;	/* 42eddd: mov dword ptr [0x83a9d8], ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42ede3: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4ad4a4u;	/* 42ede5: mov edi, 0x4ad4a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42edea: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42eded: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42edef: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42edf1: sub edi, ecx */
	M32((DWORD)(0x4dedd0u)) = m->ebx;	/* 42edf3: mov dword ptr [0x4dedd0], ebx */
	m->eax = m->ecx;	/* 42edf9: mov eax, ecx */
	m->esi = m->edi;	/* 42edfb: mov esi, edi */
	m->edi = 0x4ded20u;	/* 42edfd: mov edi, 0x4ded20 */
	M32((DWORD)(0x4dedd4u)) = m->ebx;	/* 42ee02: mov dword ptr [0x4dedd4], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42ee08: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42ee0b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42ee0d: mov ecx, eax */
	m->eax = 0x64u;	/* 42ee0f: mov eax, 0x64 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42ee14: and ecx, 3 */
	M32((DWORD)(0x4e0c90u)) = m->eax;	/* 42ee17: mov dword ptr [0x4e0c90], eax */
	M32((DWORD)(0x4e0c94u)) = m->eax;	/* 42ee1c: mov dword ptr [0x4e0c94], eax */
	m->eax = 0x1u;	/* 42ee21: mov eax, 1 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42ee26: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M8((DWORD)(0x4ded40u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42ee28: mov byte ptr [0x4ded40], bl */
	M8((DWORD)(0x4ded41u)) = (BYTE)(0x8u);	/* 42ee2e: mov byte ptr [0x4ded41], 8 */
	M8((DWORD)(0x4ded42u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42ee35: mov byte ptr [0x4ded42], bl */
	M8((DWORD)(0x4ded43u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42ee3b: mov byte ptr [0x4ded43], bl */
	M8((DWORD)(0x4ded44u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42ee41: mov byte ptr [0x4ded44], bl */
	M8((DWORD)(0x4ded45u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42ee47: mov byte ptr [0x4ded45], bl */
	M32((DWORD)(0x4e0c98u)) = m->eax;	/* 42ee4d: mov dword ptr [0x4e0c98], eax */
	M32((DWORD)(0x83a9c8u)) = m->eax;	/* 42ee52: mov dword ptr [0x83a9c8], eax */
	M32((DWORD)(0x83a9d0u)) = m->eax;	/* 42ee57: mov dword ptr [0x83a9d0], eax */
	M32((DWORD)(0x83a9ccu)) = m->eax;	/* 42ee5c: mov dword ptr [0x83a9cc], eax */
	m->esp -= 4; M32(m->esp) = 0x42ee66u; native_call(m, 0x42c410u);	/* 42ee61: call 0x42c410 */
	m->esp -= 4; M32(m->esp) = 0x42ee6bu; native_call(m, 0x42d730u);	/* 42ee66: call 0x42d730 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42ee6b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42ee6c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42ee6d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42ee6e: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x208u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ee6f: add esp, 0x208 */
	m->esp += 4 + 0; return;	/* 42ee75: ret  */
L_42ee76:
	m->esp -= 4; M32(m->esp) = 0x42ee7bu; native_call(m, 0x42d7f0u);	/* 42ee76: call 0x42d7f0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42ee7b: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42ee81u; native_call(m, 0x42da70u);	/* 42ee7c: call 0x42da70 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42ee81: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42ee87u; native_call(m, 0x42e080u);	/* 42ee82: call 0x42e080 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42ee87: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42ee8du; native_call(m, 0x42e240u);	/* 42ee88: call 0x42e240 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42ee8d: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42ee93u; native_call(m, 0x42e730u);	/* 42ee8e: call 0x42e730 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42ee93: push ebp */
	m->esp -= 4; M32(m->esp) = 0x42ee99u; native_call(m, 0x49e7e0u);	/* 42ee94: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ee99: add esp, 0x18 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42ee9c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42ee9d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42ee9e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42ee9f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x208u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42eea0: add esp, 0x208 */
	m->esp += 4 + 0; return;	/* 42eea6: ret  */
}

/* actor_checkLineOfSight (0x460270), lifted by tools/lift.py */
static void lift_460270(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x54u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460270: sub esp, 0x54 */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 460273: mov eax, dword ptr [esp + 0x58] */
	m->edx = m->ecx;	/* 460277: mov edx, ecx */
	m->ecx = m->eax;	/* 460279: mov ecx, eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46027b: push ebp */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46027c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46027f: add ecx, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 460281: push esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 460282: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 460285: add ecx, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 460287: xor esi, esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 460289: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46028c: add ecx, eax */
	m->eax = M32((DWORD)(m->edx + 0xe3c938u));	/* 46028e: mov eax, dword ptr [edx + 0xe3c938] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460294: cmp eax, esi */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 460296: mov dword ptr [esp + 0x10], edx */
	m->ebp = (DWORD)(m->edx + m->ecx*8 + 0x1cd93a8u);	/* 46029a: lea ebp, [edx + ecx*8 + 0x1cd93a8] */
	M32((DWORD)(m->esp + 0x60u)) = m->esi;	/* 4602a1: mov dword ptr [esp + 0x60], esi */
	if (m->zf || m->sf != m->of) goto L_4604e8;	/* 4602a5: jle 0x4604e8 */
	m->eax = (DWORD)(m->edx + 0xe3b03cu);	/* 4602ab: lea eax, [edx + 0xe3b03c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4602b1: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4602b2: push edi */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4602b3: mov dword ptr [esp + 0x10], eax */
L_4602b7:
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 4602b7: mov ecx, dword ptr [esp + 0x68] */
	m->edi = M32((DWORD)(m->ebp + 0x8870u));	/* 4602bb: mov edi, dword ptr [ebp + 0x8870] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4602c1: cmp ecx, edi */
	if (m->zf) goto L_460447;	/* 4602c3: je 0x460447 */
	m->ecx = M32((DWORD)(m->eax + 0xfffffffcu));	/* 4602c9: mov ecx, dword ptr [eax - 4] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4602cc: xor edi, edi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4602ce: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_460447;	/* 4602d0: jle 0x460447 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4602d6: xor ecx, ecx */
	m->ebx = (DWORD)(m->ebp + 0x154u);	/* 4602d8: lea ebx, [ebp + 0x154] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 4602de: mov dword ptr [esp + 0x14], ecx */
	goto L_4602e8;	/* 4602e2: jmp 0x4602e8 */
L_4602e4:
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4602e4: mov edx, dword ptr [esp + 0x18] */
L_4602e8:
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 4602e8: mov eax, dword ptr [eax] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4602ea: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 4602ec: fld dword ptr [ecx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 4602ee: fsub dword ptr [ebx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4602f0: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4602f6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4602f8: test ah, 1 */
	if (m->zf) goto L_4602ff;	/* 4602fb: je 0x4602ff */
	ST(0) = -ST(0);	/* 4602fd: fchs  */
L_4602ff:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x8848u)); FPOP();	/* 4602ff: fcomp dword ptr [ebp + 0x8848] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 460305: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 460307: test ah, 0x41 */
	if (m->zf) goto L_46040c;	/* 46030a: je 0x46040c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 460310: fld dword ptr [ecx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x158u));	/* 460313: fsub dword ptr [ebp + 0x158] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 460319: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46031f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 460321: test ah, 1 */
	if (m->zf) goto L_460328;	/* 460324: je 0x460328 */
	ST(0) = -ST(0);	/* 460326: fchs  */
L_460328:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x8848u)); FPOP();	/* 460328: fcomp dword ptr [ebp + 0x8848] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46032e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 460330: test ah, 0x41 */
	if (m->zf) goto L_46040c;	/* 460333: je 0x46040c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 460339: fld dword ptr [ecx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x15cu));	/* 46033c: fsub dword ptr [ebp + 0x15c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 460342: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 460348: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46034a: test ah, 1 */
	if (m->zf) goto L_460351;	/* 46034d: je 0x460351 */
	ST(0) = -ST(0);	/* 46034f: fchs  */
L_460351:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x8848u)); FPOP();	/* 460351: fcomp dword ptr [ebp + 0x8848] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 460357: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 460359: test ah, 0x41 */
	if (m->zf) goto L_46040c;	/* 46035c: je 0x46040c */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460362: cmp esi, 5 */
	if (m->sf == m->of) goto L_46039b;	/* 460365: jge 0x46039b */
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 460367: mov eax, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + m->esi*4 + 0x50u)) = m->edi;	/* 46036b: mov dword ptr [esp + esi*4 + 0x50], edi */
	M32((DWORD)(m->esp + m->esi*4 + 0x3cu)) = m->eax;	/* 46036f: mov dword ptr [esp + esi*4 + 0x3c], eax */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 460373: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 460377: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 460378: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 460379: push ebx */
	m->ecx = m->edx;	/* 46037a: mov ecx, edx */
	m->esp -= 4; M32(m->esp) = 0x460381u; native_call(m, 0x471740u);	/* 46037c: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 460381: test eax, eax */
	if (!m->zf) goto L_460390;	/* 460383: jne 0x460390 */
	M32((DWORD)(m->esp + m->esi*4 + 0x28u)) = 0x1u;	/* 460385: mov dword ptr [esp + esi*4 + 0x28], 1 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 46038d: inc esi */
	goto L_46040c;	/* 46038e: jmp 0x46040c */
L_460390:
	M32((DWORD)(m->esp + m->esi*4 + 0x28u)) = 0x0u;	/* 460390: mov dword ptr [esp + esi*4 + 0x28], 0 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 460398: inc esi */
	goto L_46040c;	/* 460399: jmp 0x46040c */
L_46039b:
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 46039b: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46039f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4603a0: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4603a1: push ebx */
	m->ecx = m->edx;	/* 4603a2: mov ecx, edx */
	m->esp -= 4; M32(m->esp) = 0x4603a9u; native_call(m, 0x471740u);	/* 4603a4: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4603a9: test eax, eax */
	if (!m->zf) goto L_46040c;	/* 4603ab: jne 0x46040c */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4603ad: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_4603d3;	/* 4603af: jle 0x4603d3 */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 4603b1: mov ecx, dword ptr [0xa1efb8] */
	m->edx = m->ecx;	/* 4603b7: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4603b9: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 4603bf: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4603c6: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->esi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 4603c8: div esi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4603ca: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 4603cb: mov dword ptr [0xa1efb8], ecx */
	goto L_4603d5;	/* 4603d1: jmp 0x4603d5 */
L_4603d3:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4603d3: xor edx, edx */
L_4603d5:
	m->eax = M32((DWORD)(m->esp + m->edx*4 + 0x28u));	/* 4603d5: mov eax, dword ptr [esp + edx*4 + 0x28] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4603d9: test eax, eax */
	if (m->zf) goto L_460429;	/* 4603db: je 0x460429 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4603dd: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_460402;	/* 4603df: jle 0x460402 */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 4603e1: mov ecx, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4603e7: xor edx, edx */
	m->eax = m->ecx;	/* 4603e9: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4603eb: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 4603f0: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->esi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 4603f7: div esi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4603f9: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 4603fa: mov dword ptr [0xa1efb8], ecx */
	goto L_460404;	/* 460400: jmp 0x460404 */
L_460402:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 460402: xor edx, edx */
L_460404:
	m->eax = M32((DWORD)(m->esp + m->edx*4 + 0x28u));	/* 460404: mov eax, dword ptr [esp + edx*4 + 0x28] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 460408: test eax, eax */
	if (m->zf) goto L_460433;	/* 46040a: je 0x460433 */
L_46040c:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46040c: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 460410: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 460414: inc edi */
	{ DWORD a_ = m->ecx, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 460415: add ecx, 0x14 */
	m->edx = M32((DWORD)(m->eax + 0xfffffffcu));	/* 460418: mov edx, dword ptr [eax - 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 46041b: mov dword ptr [esp + 0x14], ecx */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46041f: cmp edi, edx */
	if (m->sf != m->of) goto L_4602e4;	/* 460421: jl 0x4602e4 */
	goto L_460447;	/* 460427: jmp 0x460447 */
L_460429:
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 460429: mov ecx, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + m->edx*4 + 0x3cu)) = m->ecx;	/* 46042d: mov dword ptr [esp + edx*4 + 0x3c], ecx */
	goto L_46043b;	/* 460431: jmp 0x46043b */
L_460433:
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 460433: mov eax, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + m->edx*4 + 0x3cu)) = m->eax;	/* 460437: mov dword ptr [esp + edx*4 + 0x3c], eax */
L_46043b:
	M32((DWORD)(m->esp + m->edx*4 + 0x50u)) = m->edi;	/* 46043b: mov dword ptr [esp + edx*4 + 0x50], edi */
	M32((DWORD)(m->esp + m->edx*4 + 0x28u)) = 0x1u;	/* 46043f: mov dword ptr [esp + edx*4 + 0x28], 1 */
L_460447:
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 460447: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 46044b: mov ecx, dword ptr [esp + 0x68] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46044f: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 460453: inc ecx */
	m->edi = M32((DWORD)(m->edx + 0xe3c938u));	/* 460454: mov edi, dword ptr [edx + 0xe3c938] */
	{ DWORD a_ = m->eax, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46045a: add eax, 0x1c */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46045d: cmp ecx, edi */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 46045f: mov dword ptr [esp + 0x68], ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 460463: mov dword ptr [esp + 0x10], eax */
	if (m->sf != m->of) goto L_4602b7;	/* 460467: jl 0x4602b7 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46046d: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46046e: pop ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46046f: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_4604e8;	/* 460471: jle 0x4604e8 */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 460473: mov ecx, dword ptr [0xa1efb8] */
	m->edx = m->ecx;	/* 460479: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46047b: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 460481: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 460488: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->esi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 46048a: div esi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 46048c: inc ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 46048d: pop esi */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 46048e: mov dword ptr [0xa1efb8], ecx */
	m->eax = M32((DWORD)(m->esp + m->edx*4 + 0x30u));	/* 460494: mov eax, dword ptr [esp + edx*4 + 0x30] */
	m->ecx = M32((DWORD)(m->esp + m->edx*4 + 0x44u));	/* 460498: mov ecx, dword ptr [esp + edx*4 + 0x44] */
	M32((DWORD)(m->ebp + 0x87f8u)) = m->eax;	/* 46049c: mov dword ptr [ebp + 0x87f8], eax */
	M32((DWORD)(m->ebp + 0x87fcu)) = m->ecx;	/* 4604a2: mov dword ptr [ebp + 0x87fc], ecx */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 4604a8: mov ecx, dword ptr [0xa1efb8] */
	m->edx = m->ecx;	/* 4604ae: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4604b0: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 4604b6: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4604bd: and eax, 1 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4604c0: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 4604c1: mov dword ptr [0xa1efb8], ecx */
	M32((DWORD)(m->ebp + 0x8800u)) = m->eax;	/* 4604c7: mov dword ptr [ebp + 0x8800], eax */
	M32((DWORD)(m->ebp + 0x8870u)) = 0xffffffffu;	/* 4604cd: mov dword ptr [ebp + 0x8870], 0xffffffff */
	M32((DWORD)(m->ebp + 0x8848u)) = 0x44bb8000u;	/* 4604d7: mov dword ptr [ebp + 0x8848], 0x44bb8000 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4604e1: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4604e2: add esp, 0x54 */
	m->esp += 4 + 4; return;	/* 4604e5: ret 4 */
L_4604e8:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8848u)));	/* 4604e8: fld dword ptr [ebp + 0x8848] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a974cu));	/* 4604ee: fmul dword ptr [0x4a974c] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4604f4: pop esi */
	MF((DWORD)(m->ebp + 0x8848u)) = (float)ST(0); FPOP();	/* 4604f5: fstp dword ptr [ebp + 0x8848] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4604fb: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4604fc: add esp, 0x54 */
	m->esp += 4 + 4; return;	/* 4604ff: ret 4 */
}

/* armc_41cf20 (0x41cf20), lifted by tools/lift.py */
static void lift_41cf20(X86 *m)
{
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41cf20: mov eax, dword ptr [0x4dc4b0] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41cf25: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_41d25d;	/* 41cf28: ja 0x41d25d */
	switch (m->eax) { case 0: goto L_41cf35; case 1: goto L_41cf8c; case 2: goto L_41cfe3; case 3: goto L_41d03a; case 4: goto L_41d207; case 5: goto L_41d091; default: abort(); }	/* 41cf2e: jmp dword ptr [eax*4 + 0x41d260] */
L_41cf35:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41cf35: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41cf38: shl eax, 3 */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41cf3b: mov ecx, dword ptr [eax + 0x4dc4cc] */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41cf41: mov edx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cf47: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41cf48: mov ecx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cf4e: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41cf4f: mov edx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cf55: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41cf56: mov ecx, dword ptr [eax + 0x4dc4bc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cf5c: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41cf5d: mov edx, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cf63: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cf64: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41cf65: mov edx, dword ptr [0x9087b4] */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41cf6b: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41cf71: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41cf74: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41cf77: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41cf79: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41cf7c: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1755568u);	/* 41cf7f: lea ecx, [edx + ecx*2 + 0x1755568] */
	m->esp -= 4; M32(m->esp) = 0x41cf8bu; native_call(m, 0x467660u);	/* 41cf86: call 0x467660 */
	m->esp += 4 + 0; return;	/* 41cf8b: ret  */
L_41cf8c:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41cf8c: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41cf8f: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41cf92: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41cf98: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cf9e: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41cf9f: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cfa5: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41cfa6: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cfac: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41cfad: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41cfb3: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cfb9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cfba: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41cfbb: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41cfc1: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41cfc2: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41cfc8: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41cfcb: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41cfce: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41cfd0: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41cfd3: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x175d4b4u);	/* 41cfd6: lea ecx, [edx + ecx*2 + 0x175d4b4] */
	m->esp -= 4; M32(m->esp) = 0x41cfe2u; native_call(m, 0x467660u);	/* 41cfdd: call 0x467660 */
	m->esp += 4 + 0; return;	/* 41cfe2: ret  */
L_41cfe3:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41cfe3: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41cfe6: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41cfe9: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41cfef: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cff5: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41cff6: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41cffc: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41cffd: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d003: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d004: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d00a: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d010: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d011: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d012: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d018: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d019: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d01f: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d022: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d025: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d027: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d02a: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1765400u);	/* 41d02d: lea ecx, [edx + ecx*2 + 0x1765400] */
	m->esp -= 4; M32(m->esp) = 0x41d039u; native_call(m, 0x467660u);	/* 41d034: call 0x467660 */
	m->esp += 4 + 0; return;	/* 41d039: ret  */
L_41d03a:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d03a: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d03d: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d040: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d046: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d04c: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d04d: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d053: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d054: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d05a: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d05b: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d061: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d067: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d068: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d069: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d06f: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d070: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d076: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d079: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d07c: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d07e: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d081: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x177504cu);	/* 41d084: lea ecx, [edx + ecx*2 + 0x177504c] */
	m->esp -= 4; M32(m->esp) = 0x41d090u; native_call(m, 0x467660u);	/* 41d08b: call 0x467660 */
	m->esp += 4 + 0; return;	/* 41d090: ret  */
L_41d091:
	m->esp -= 4; M32(m->esp) = 0x41d096u; native_call(m, 0x41ced0u);	/* 41d091: call 0x41ced0 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41d096: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d09b: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d09e: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d0a1: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d0a7: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d0ad: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d0ae: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d0b4: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d0b5: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d0bb: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d0bc: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d0c2: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d0c8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d0c9: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d0ca: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d0d0: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d0d1: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d0d7: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d0da: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d0dd: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d0df: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d0e2: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1755568u);	/* 41d0e5: lea ecx, [edx + ecx*2 + 0x1755568] */
	m->esp -= 4; M32(m->esp) = 0x41d0f1u; native_call(m, 0x467660u);	/* 41d0ec: call 0x467660 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41d0f1: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d0f6: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d0f9: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d0fc: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d102: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d108: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d109: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d10f: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d110: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d116: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d117: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d11d: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d123: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d124: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d125: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d12b: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d12c: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d132: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d135: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d138: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d13a: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d13d: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x175d4b4u);	/* 41d140: lea ecx, [edx + ecx*2 + 0x175d4b4] */
	m->esp -= 4; M32(m->esp) = 0x41d14cu; native_call(m, 0x467660u);	/* 41d147: call 0x467660 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41d14c: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d151: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d154: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d157: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d15d: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d163: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d164: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d16a: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d16b: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d171: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d172: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d178: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d17e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d17f: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d180: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d186: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d187: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d18d: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d190: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d193: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d195: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d198: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1765400u);	/* 41d19b: lea ecx, [edx + ecx*2 + 0x1765400] */
	m->esp -= 4; M32(m->esp) = 0x41d1a7u; native_call(m, 0x467660u);	/* 41d1a2: call 0x467660 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41d1a7: mov eax, dword ptr [0x4dc4b0] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d1ac: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d1af: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d1b2: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d1b8: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d1be: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d1bf: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d1c5: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d1c6: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d1cc: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d1cd: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d1d3: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d1d9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d1da: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d1db: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d1e1: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d1e2: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d1e8: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d1eb: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d1ee: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d1f0: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d1f3: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x177504cu);	/* 41d1f6: lea ecx, [edx + ecx*2 + 0x177504c] */
	m->esp -= 4; M32(m->esp) = 0x41d202u; native_call(m, 0x467660u);	/* 41d1fd: call 0x467660 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41d202: mov eax, dword ptr [0x4dc4b0] */
L_41d207:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d207: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d20a: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d20d: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d213: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d219: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d21a: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d220: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d221: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d227: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d228: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d22e: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d234: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d235: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d236: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d23c: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d23d: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d243: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d246: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d249: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d24b: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d24e: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1784c98u);	/* 41d251: lea ecx, [edx + ecx*2 + 0x1784c98] */
	m->esp -= 4; M32(m->esp) = 0x41d25du; native_call(m, 0x467660u);	/* 41d258: call 0x467660 */
L_41d25d:
	m->esp += 4 + 0; return;	/* 41d25d: ret  */
}

/* armc_41d280 (0x41d280), lifted by tools/lift.py */
static void lift_41d280(X86 *m)
{
	m->eax = M32((DWORD)(0x4dd074u));	/* 41d280: mov eax, dword ptr [0x4dd074] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41d285: test eax, eax */
	if (m->zf) goto L_41d41d;	/* 41d287: je 0x41d41d */
	m->eax = M32((DWORD)(0x4dc4ccu));	/* 41d28d: mov eax, dword ptr [0x4dc4cc] */
	m->ecx = M32((DWORD)(0x4dc4c8u));	/* 41d292: mov ecx, dword ptr [0x4dc4c8] */
	m->edx = M32((DWORD)(0x4dc4c4u));	/* 41d298: mov edx, dword ptr [0x4dc4c4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d29e: push eax */
	m->eax = M32((DWORD)(0x4dc4c0u));	/* 41d29f: mov eax, dword ptr [0x4dc4c0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d2a4: push ecx */
	m->ecx = M32((DWORD)(0x4dc4bcu));	/* 41d2a5: mov ecx, dword ptr [0x4dc4bc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d2ab: push edx */
	m->edx = M32((DWORD)(0x4dc4b8u));	/* 41d2ac: mov edx, dword ptr [0x4dc4b8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d2b2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d2b3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d2b4: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d2b5: mov edx, dword ptr [0x9087b4] */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d2bb: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d2c1: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d2c4: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d2c7: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d2c9: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d2cc: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1755568u);	/* 41d2cf: lea ecx, [edx + ecx*2 + 0x1755568] */
	m->esp -= 4; M32(m->esp) = 0x41d2dbu; native_call(m, 0x467660u);	/* 41d2d6: call 0x467660 */
	m->edx = M32((DWORD)(0x4dc4e4u));	/* 41d2db: mov edx, dword ptr [0x4dc4e4] */
	m->eax = M32((DWORD)(0x4dc4e0u));	/* 41d2e1: mov eax, dword ptr [0x4dc4e0] */
	m->ecx = M32((DWORD)(0x4dc4dcu));	/* 41d2e6: mov ecx, dword ptr [0x4dc4dc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d2ec: push edx */
	m->edx = M32((DWORD)(0x4dc4d8u));	/* 41d2ed: mov edx, dword ptr [0x4dc4d8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d2f3: push eax */
	m->eax = M32((DWORD)(0x4dc4d4u));	/* 41d2f4: mov eax, dword ptr [0x4dc4d4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d2f9: push ecx */
	m->ecx = M32((DWORD)(0x4dc4d0u));	/* 41d2fa: mov ecx, dword ptr [0x4dc4d0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d300: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d301: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d307: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d308: push ecx */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d309: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d30f: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d312: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d315: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d317: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d31a: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x175d4b4u);	/* 41d31d: lea ecx, [edx + ecx*2 + 0x175d4b4] */
	m->esp -= 4; M32(m->esp) = 0x41d329u; native_call(m, 0x467660u);	/* 41d324: call 0x467660 */
	m->edx = M32((DWORD)(0x4dc4fcu));	/* 41d329: mov edx, dword ptr [0x4dc4fc] */
	m->eax = M32((DWORD)(0x4dc4f8u));	/* 41d32f: mov eax, dword ptr [0x4dc4f8] */
	m->ecx = M32((DWORD)(0x4dc4f4u));	/* 41d334: mov ecx, dword ptr [0x4dc4f4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d33a: push edx */
	m->edx = M32((DWORD)(0x4dc4f0u));	/* 41d33b: mov edx, dword ptr [0x4dc4f0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d341: push eax */
	m->eax = M32((DWORD)(0x4dc4ecu));	/* 41d342: mov eax, dword ptr [0x4dc4ec] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d347: push ecx */
	m->ecx = M32((DWORD)(0x4dc4e8u));	/* 41d348: mov ecx, dword ptr [0x4dc4e8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d34e: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d34f: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d355: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d356: push ecx */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d357: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d35d: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d360: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d363: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d365: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d368: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1765400u);	/* 41d36b: lea ecx, [edx + ecx*2 + 0x1765400] */
	m->esp -= 4; M32(m->esp) = 0x41d377u; native_call(m, 0x467660u);	/* 41d372: call 0x467660 */
	m->edx = M32((DWORD)(0x4dc514u));	/* 41d377: mov edx, dword ptr [0x4dc514] */
	m->eax = M32((DWORD)(0x4dc510u));	/* 41d37d: mov eax, dword ptr [0x4dc510] */
	m->ecx = M32((DWORD)(0x4dc50cu));	/* 41d382: mov ecx, dword ptr [0x4dc50c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d388: push edx */
	m->edx = M32((DWORD)(0x4dc508u));	/* 41d389: mov edx, dword ptr [0x4dc508] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d38f: push eax */
	m->eax = M32((DWORD)(0x4dc504u));	/* 41d390: mov eax, dword ptr [0x4dc504] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d395: push ecx */
	m->ecx = M32((DWORD)(0x4dc500u));	/* 41d396: mov ecx, dword ptr [0x4dc500] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d39c: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d39d: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d3a3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d3a4: push ecx */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d3a5: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d3ab: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d3ae: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d3b1: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d3b3: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d3b6: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x177504cu);	/* 41d3b9: lea ecx, [edx + ecx*2 + 0x177504c] */
	m->esp -= 4; M32(m->esp) = 0x41d3c5u; native_call(m, 0x467660u);	/* 41d3c0: call 0x467660 */
	m->edx = M32((DWORD)(0x4dc52cu));	/* 41d3c5: mov edx, dword ptr [0x4dc52c] */
	m->eax = M32((DWORD)(0x4dc528u));	/* 41d3cb: mov eax, dword ptr [0x4dc528] */
	m->ecx = M32((DWORD)(0x4dc524u));	/* 41d3d0: mov ecx, dword ptr [0x4dc524] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d3d6: push edx */
	m->edx = M32((DWORD)(0x4dc520u));	/* 41d3d7: mov edx, dword ptr [0x4dc520] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d3dd: push eax */
	m->eax = M32((DWORD)(0x4dc51cu));	/* 41d3de: mov eax, dword ptr [0x4dc51c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d3e3: push ecx */
	m->ecx = M32((DWORD)(0x4dc518u));	/* 41d3e4: mov ecx, dword ptr [0x4dc518] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d3ea: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d3eb: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d3f1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d3f2: push ecx */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d3f3: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d3f9: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d3fc: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d3ff: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d401: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d404: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1784c98u);	/* 41d407: lea ecx, [edx + ecx*2 + 0x1784c98] */
	m->esp -= 4; M32(m->esp) = 0x41d413u; native_call(m, 0x467660u);	/* 41d40e: call 0x467660 */
	M32((DWORD)(0x4dd074u)) = 0x0u;	/* 41d413: mov dword ptr [0x4dd074], 0 */
L_41d41d:
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 41d41d: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d422: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_41d5e4;	/* 41d425: ja 0x41d5e4 */
	switch (m->eax) { case 0: goto L_41d432; case 1: goto L_41d489; case 2: goto L_41d4e0; case 3: goto L_41d537; case 4: goto L_41d58e; default: abort(); }	/* 41d42b: jmp dword ptr [eax*4 + 0x41d5e8] */
L_41d432:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d432: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d435: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d438: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d43e: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d444: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d445: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d44b: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d44c: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d452: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d453: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d459: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d45f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d460: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d461: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d467: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d468: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d46e: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d471: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d474: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d476: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d479: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1755568u);	/* 41d47c: lea ecx, [edx + ecx*2 + 0x1755568] */
	m->esp -= 4; M32(m->esp) = 0x41d488u; native_call(m, 0x467660u);	/* 41d483: call 0x467660 */
	m->esp += 4 + 0; return;	/* 41d488: ret  */
L_41d489:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d489: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d48c: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d48f: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d495: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d49b: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d49c: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d4a2: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d4a3: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d4a9: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d4aa: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d4b0: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d4b6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d4b7: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d4b8: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d4be: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d4bf: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d4c5: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d4c8: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d4cb: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d4cd: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d4d0: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x175d4b4u);	/* 41d4d3: lea ecx, [edx + ecx*2 + 0x175d4b4] */
	m->esp -= 4; M32(m->esp) = 0x41d4dfu; native_call(m, 0x467660u);	/* 41d4da: call 0x467660 */
	m->esp += 4 + 0; return;	/* 41d4df: ret  */
L_41d4e0:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d4e0: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d4e3: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d4e6: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d4ec: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d4f2: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d4f3: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d4f9: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d4fa: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d500: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d501: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d507: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d50d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d50e: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d50f: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d515: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d516: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d51c: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d51f: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d522: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d524: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d527: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1765400u);	/* 41d52a: lea ecx, [edx + ecx*2 + 0x1765400] */
	m->esp -= 4; M32(m->esp) = 0x41d536u; native_call(m, 0x467660u);	/* 41d531: call 0x467660 */
	m->esp += 4 + 0; return;	/* 41d536: ret  */
L_41d537:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d537: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d53a: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d53d: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d543: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d549: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d54a: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d550: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d551: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d557: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d558: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d55e: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d564: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d565: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d566: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d56c: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d56d: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d573: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d576: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d579: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d57b: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d57e: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x177504cu);	/* 41d581: lea ecx, [edx + ecx*2 + 0x177504c] */
	m->esp -= 4; M32(m->esp) = 0x41d58du; native_call(m, 0x467660u);	/* 41d588: call 0x467660 */
	m->esp += 4 + 0; return;	/* 41d58d: ret  */
L_41d58e:
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d58e: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d591: shl eax, 3 */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 41d594: mov edx, dword ptr [eax + 0x4dc4cc] */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 41d59a: mov ecx, dword ptr [eax + 0x4dc4c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d5a0: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 41d5a1: mov edx, dword ptr [eax + 0x4dc4c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d5a7: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 41d5a8: mov ecx, dword ptr [eax + 0x4dc4c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d5ae: push edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 41d5af: mov edx, dword ptr [eax + 0x4dc4bc] */
	m->eax = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 41d5b5: mov eax, dword ptr [eax + 0x4dc4b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d5bb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d5bc: push edx */
	m->edx = M32((DWORD)(0x9087b4u));	/* 41d5bd: mov edx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d5c3: push eax */
	m->ecx = M32((DWORD)(m->edx + 0x234240du));	/* 41d5c4: mov ecx, dword ptr [edx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 41d5ca: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41d5cd: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41d5d0: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41d5d2: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 41d5d5: lea ecx, [ecx + eax*8] */
	m->ecx = (DWORD)(m->edx + m->ecx*2 + 0x1784c98u);	/* 41d5d8: lea ecx, [edx + ecx*2 + 0x1784c98] */
	m->esp -= 4; M32(m->esp) = 0x41d5e4u; native_call(m, 0x467660u);	/* 41d5df: call 0x467660 */
L_41d5e4:
	m->esp += 4 + 0; return;	/* 41d5e4: ret  */
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
