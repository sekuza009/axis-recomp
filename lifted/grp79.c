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

static void lift_449a50(X86 *m);

/* missionsel_drawScreen (0x449a50), lifted by tools/lift.py */
static void lift_449a50(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 449a50: push ebp */
	m->ebp = m->esp;	/* 449a51: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 449a53: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x220u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449a56: sub esp, 0x220 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 449a5c: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 449a61: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 449a67: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 449a68: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 449a69: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 449a6a: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449a6b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449a6c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x449a72u; native_call(m, 0x447710u);	/* 449a6d: call 0x447710 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a72: push 2 */
	m->esp -= 4; M32(m->esp) = 0x449a79u; native_call(m, 0x41ef90u);	/* 449a74: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449a79: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x449a82u; native_call(m, M32(0x4a9218u));	/* 449a7c: call dword ptr [0x4a9218] */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 449a82: mov ebp, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a88: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a8d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a92: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a97: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x449a9eu; native_call(m, m->ebp);	/* 449a9c: call ebp */
	m->edx = M32((DWORD)(0x4deb50u));	/* 449a9e: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9f6314u));	/* 449aa4: mov eax, dword ptr [0x9f6314] */
	m->ecx = M32((DWORD)(0x9f6310u));	/* 449aa9: mov ecx, dword ptr [0x9f6310] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449aaf: push edx */
	m->edx = M32((DWORD)(0x9f630cu));	/* 449ab0: mov edx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449ab6: push eax */
	m->eax = M32((DWORD)(0x9f6308u));	/* 449ab7: mov eax, dword ptr [0x9f6308] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449abc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449abd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449abe: push eax */
	m->esp -= 4; M32(m->esp) = 0x449ac4u; native_call(m, 0x427a90u);	/* 449abf: call 0x427a90 */
	m->ecx = M32((DWORD)(0x9f6324u));	/* 449ac4: mov ecx, dword ptr [0x9f6324] */
	m->edx = M32((DWORD)(0x9f6320u));	/* 449aca: mov edx, dword ptr [0x9f6320] */
	m->eax = M32((DWORD)(0x9f631cu));	/* 449ad0: mov eax, dword ptr [0x9f631c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449ad5: push ecx */
	m->ecx = M32((DWORD)(0x9f6318u));	/* 449ad6: mov ecx, dword ptr [0x9f6318] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449adc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449add: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449ade: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 449adf: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x449ae9u; native_call(m, 0x41f0e0u);	/* 449ae4: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 449ae9: mov eax, dword ptr [0x9f63b4] */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 449aee: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 449af2: push 0xa */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 449af4: inc eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449af5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449af6: push eax */
	m->esp -= 4; M32(m->esp) = 0x449afcu; native_call(m, 0x49fb53u);	/* 449af7: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9f63b4u));	/* 449afc: mov edx, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449b02: add esp, 0x34 */
	m->eax = (DWORD)(m->edx + 0x1u);	/* 449b05: lea eax, [edx + 1] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 449b08: dec eax */
	if (m->zf) goto L_449b2e;	/* 449b09: je 0x449b2e */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 449b0b: dec eax */
	if (m->zf) goto L_449b23;	/* 449b0c: je 0x449b23 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 449b0e: dec eax */
	m->ebx = (DWORD)(m->esp + 0x28u);	/* 449b0f: lea ebx, [esp + 0x28] */
	if (m->zf) goto L_449b1c;	/* 449b13: je 0x449b1c */
	m->edi = 0x4b2b2cu;	/* 449b15: mov edi, 0x4b2b2c */
	goto L_449b37;	/* 449b1a: jmp 0x449b37 */
L_449b1c:
	m->edi = 0x4b2b28u;	/* 449b1c: mov edi, 0x4b2b28 */
	goto L_449b37;	/* 449b21: jmp 0x449b37 */
L_449b23:
	m->ebx = (DWORD)(m->esp + 0x28u);	/* 449b23: lea ebx, [esp + 0x28] */
	m->edi = 0x4b2b24u;	/* 449b27: mov edi, 0x4b2b24 */
	goto L_449b37;	/* 449b2c: jmp 0x449b37 */
L_449b2e:
	m->ebx = (DWORD)(m->esp + 0x28u);	/* 449b2e: lea ebx, [esp + 0x28] */
	m->edi = 0x4b2b20u;	/* 449b32: mov edi, 0x4b2b20 */
L_449b37:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449b37: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449b3a: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449b3c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449b3e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449b40: sub edi, ecx */
	m->esi = m->edi;	/* 449b42: mov esi, edi */
	m->edi = m->ebx;	/* 449b44: mov edi, ebx */
	m->ebx = m->ecx;	/* 449b46: mov ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449b48: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449b4b: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 449b4d: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449b4f: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449b50: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449b53: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 449b55: mov ecx, ebx */
	m->ebx = (DWORD)(m->esp + 0x28u);	/* 449b57: lea ebx, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449b5b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449b5e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449b60: or ecx, 0xffffffff */
	m->edi = 0x75f1a4u;	/* 449b63: mov edi, 0x75f1a4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449b68: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449b6a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449b6c: sub edi, ecx */
	m->esi = m->edi;	/* 449b6e: mov esi, edi */
	m->edi = m->ebx;	/* 449b70: mov edi, ebx */
	m->ebx = m->ecx;	/* 449b72: mov ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449b74: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449b77: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 449b79: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449b7b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449b7c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449b7f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 449b81: mov ecx, ebx */
	m->ebx = (DWORD)(m->esp + 0x28u);	/* 449b83: lea ebx, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449b87: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449b8a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b18u;	/* 449b8c: mov edi, 0x4b2b18 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449b91: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449b94: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449b96: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449b98: sub edi, ecx */
	m->esi = m->edi;	/* 449b9a: mov esi, edi */
	m->edi = m->ebx;	/* 449b9c: mov edi, ebx */
	m->ebx = m->ecx;	/* 449b9e: mov ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449ba0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449ba3: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 449ba5: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449ba7: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449ba8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449bab: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 449bad: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449baf: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449bb2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 449bb4: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449bb6: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 449bb9: shl edi, 5 */
	{ DWORD a_ = m->edi, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449bbc: add edi, 0x907b30 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 449bc2: lea edx, [esp + 0x28] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449bc6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449bc8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449bca: sub edi, ecx */
	m->esi = m->edi;	/* 449bcc: mov esi, edi */
	m->ebx = m->ecx;	/* 449bce: mov ebx, ecx */
	m->edi = m->edx;	/* 449bd0: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449bd2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449bd5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 449bd7: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449bd9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449bda: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449bdd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 449bdf: mov ecx, ebx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 449be1: lea edx, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449be5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449be8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b14u;	/* 449bea: mov edi, 0x4b2b14 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449bef: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449bf2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449bf4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449bf6: sub edi, ecx */
	m->esi = m->edi;	/* 449bf8: mov esi, edi */
	m->ebx = m->ecx;	/* 449bfa: mov ebx, ecx */
	m->edi = m->edx;	/* 449bfc: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449bfe: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449c01: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 449c03: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449c05: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449c06: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449c09: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->edx = M32((DWORD)(0x9f630cu));	/* 449c0b: mov edx, dword ptr [0x9f630c] */
	m->ecx = m->ebx;	/* 449c11: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449c13: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 449c16: lea eax, [esp + 0x28] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449c1a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f6310u));	/* 449c1c: mov ecx, dword ptr [0x9f6310] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449c22: push eax */
	m->eax = M32((DWORD)(0x9f6308u));	/* 449c23: mov eax, dword ptr [0x9f6308] */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449c28: add edx, 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449c2b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449c2c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449c2d: push eax */
	m->esp -= 4; M32(m->esp) = 0x449c33u; native_call(m, 0x4029d0u);	/* 449c2e: call 0x4029d0 */
	m->eax = M32((DWORD)(0x9f63b0u));	/* 449c33: mov eax, dword ptr [0x9f63b0] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449c38: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 449c3b: test eax, eax */
	if (m->zf) goto L_449d6b;	/* 449c3d: je 0x449d6b */
	m->ecx = 0x20u;	/* 449c43: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449c48: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x128u);	/* 449c4a: lea edi, [esp + 0x128] */
	m->edx = (DWORD)(m->esp + 0x128u);	/* 449c51: lea edx, [esp + 0x128] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 449c58: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449c5a: or ecx, 0xffffffff */
	m->edi = 0x680bc4u;	/* 449c5d: mov edi, 0x680bc4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449c62: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449c64: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449c66: sub edi, ecx */
	m->ebx = (DWORD)(m->esp + 0x128u);	/* 449c68: lea ebx, [esp + 0x128] */
	m->eax = m->ecx;	/* 449c6f: mov eax, ecx */
	m->esi = m->edi;	/* 449c71: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449c73: shr ecx, 2 */
	m->edi = m->edx;	/* 449c76: mov edi, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449c78: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 449c7a: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449c7c: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449c7e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449c81: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f63b4u));	/* 449c83: mov ecx, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449c89: shl ecx, 5 */
	m->edx = (DWORD)(m->ecx + 0x907b30u);	/* 449c8c: lea edx, [ecx + 0x907b30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449c92: or ecx, 0xffffffff */
	m->edi = m->edx;	/* 449c95: mov edi, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449c97: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449c99: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449c9b: sub edi, ecx */
	m->esi = m->edi;	/* 449c9d: mov esi, edi */
	m->edi = m->ebx;	/* 449c9f: mov edi, ebx */
	m->ebx = m->ecx;	/* 449ca1: mov ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449ca3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449ca6: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 449ca8: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449caa: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449cab: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449cae: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 449cb0: mov ecx, ebx */
	m->ebx = (DWORD)(m->esp + 0x128u);	/* 449cb2: lea ebx, [esp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449cb9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449cbc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4ad564u;	/* 449cbe: mov edi, 0x4ad564 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449cc3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449cc6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449cc8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449cca: sub edi, ecx */
	m->esi = m->edi;	/* 449ccc: mov esi, edi */
	m->edi = m->ebx;	/* 449cce: mov edi, ebx */
	m->ebx = m->ecx;	/* 449cd0: mov ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449cd2: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449cd5: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 449cd7: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449cd9: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449cda: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449cdd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 449cdf: mov ecx, ebx */
	m->ebx = (DWORD)(m->esp + 0x128u);	/* 449ce1: lea ebx, [esp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449ce8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449ceb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 449ced: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449cef: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449cf2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449cf4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449cf6: sub edi, ecx */
	m->esi = m->edi;	/* 449cf8: mov esi, edi */
	m->edx = m->ecx;	/* 449cfa: mov edx, ecx */
	m->edi = m->ebx;	/* 449cfc: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449cfe: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449d01: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 449d03: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449d05: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449d06: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449d09: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 449d0b: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0xe8u);	/* 449d0d: lea edx, [esp + 0xe8] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449d14: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449d17: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x128u);	/* 449d19: lea edi, [esp + 0x128] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449d20: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449d23: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449d25: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449d27: sub edi, ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449d29: push 0 */
	m->eax = m->ecx;	/* 449d2b: mov eax, ecx */
	m->esi = m->edi;	/* 449d2d: mov esi, edi */
	m->edi = m->edx;	/* 449d2f: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449d31: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449d33: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449d36: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 449d38: mov ecx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449d3a: push 0 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449d3c: and ecx, 3 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449d3f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449d41: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449d43: push 0 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449d45: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 449d47: mov ecx, dword ptr [0xa0e010] */
	m->edx = (DWORD)(m->esp + 0x100u);	/* 449d4d: lea edx, [esp + 0x100] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449d54: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449d56: push edx */
	m->esp -= 4; M32(m->esp) = 0x449d5cu; native_call(m, 0x456be0u);	/* 449d57: call 0x456be0 */
	M32((DWORD)(0x9da324u)) = m->eax;	/* 449d5c: mov dword ptr [0x9da324], eax */
	M32((DWORD)(0x9f63b0u)) = 0x0u;	/* 449d61: mov dword ptr [0x9f63b0], 0 */
L_449d6b:
	m->ebx = M32((DWORD)(0x4a9224u));	/* 449d6b: mov ebx, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 449d71: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x449d78u; native_call(m, m->ebx);	/* 449d76: call ebx */
	m->eax = M32((DWORD)(0x9da324u));	/* 449d78: mov eax, dword ptr [0x9da324] */
	m->ecx = m->eax;	/* 449d7d: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449d7f: and ecx, 0x800001ff */
	if (!m->sf) goto L_449d8f;	/* 449d85: jns 0x449d8f */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 449d87: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449d88: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 449d8e: inc ecx */
L_449d8f:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 449d8f: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 449d90: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449d96: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449d97: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 449d99: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 449d9f: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 449da2: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x449dabu; native_call(m, 0x4566c0u);	/* 449da6: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449dab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449db0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449db5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449dba: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x449dc1u; native_call(m, m->ebp);	/* 449dbf: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 449dc1: push 7 */
	m->esp -= 4; M32(m->esp) = 0x449dc9u; native_call(m, M32(0x4a921cu));	/* 449dc3: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a9208u));	/* 449dc9: mov esi, dword ptr [0x4a9208] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449dcf: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449dd1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449dd3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449dd5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x449dd9u; native_call(m, m->esi);	/* 449dd7: call esi */
	m->eax = M32((DWORD)(0x9f630cu));	/* 449dd9: mov eax, dword ptr [0x9f630c] */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 449dde: mov ecx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449de4: add eax, 0x20 */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449de7: add ecx, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449ded: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449dee: push ecx */
	m->esp -= 4; M32(m->esp) = 0x449df4u; native_call(m, 0x41ef60u);	/* 449def: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449df4: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449df7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449df9: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449dfb: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e00: push 0 */
	m->esp -= 4; M32(m->esp) = 0x449e04u; native_call(m, m->esi);	/* 449e02: call esi */
	m->edx = M32((DWORD)(0x9f630cu));	/* 449e04: mov edx, dword ptr [0x9f630c] */
	m->eax = M32((DWORD)(0x9f6308u));	/* 449e0a: mov eax, dword ptr [0x9f6308] */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449e0f: add edx, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x158u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449e12: add eax, 0x158 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449e17: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449e18: push eax */
	m->esp -= 4; M32(m->esp) = 0x449e1eu; native_call(m, 0x41ef60u);	/* 449e19: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449e1e: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e21: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e26: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e28: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e2d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x449e31u; native_call(m, m->esi);	/* 449e2f: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 449e31: mov ecx, dword ptr [0x9f630c] */
	m->edx = M32((DWORD)(0x9f6308u));	/* 449e37: mov edx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->ecx, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449e3d: add ecx, 0xa0 */
	{ DWORD a_ = m->edx, b_ = 0x158u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449e43: add edx, 0x158 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449e49: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449e4a: push edx */
	m->esp -= 4; M32(m->esp) = 0x449e50u; native_call(m, 0x41ef60u);	/* 449e4b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449e50: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e53: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e58: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e5a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e5c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x449e60u; native_call(m, m->esi);	/* 449e5e: call esi */
	m->eax = M32((DWORD)(0x9f630cu));	/* 449e60: mov eax, dword ptr [0x9f630c] */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 449e65: mov ecx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->eax, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449e6b: add eax, 0xa0 */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449e70: add ecx, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449e76: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449e77: push ecx */
	m->esp -= 4; M32(m->esp) = 0x449e7du; native_call(m, 0x41ef60u);	/* 449e78: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449e7d: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x449e86u; native_call(m, M32(0x4a9220u));	/* 449e80: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e86: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x449e91u; native_call(m, M32(0x4a922cu));	/* 449e8b: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e91: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e96: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e98: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449e9d: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 449ea2: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x449eacu; native_call(m, 0x41f0e0u);	/* 449ea7: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f630cu));	/* 449eac: mov eax, dword ptr [0x9f630c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449eb1: push 0 */
	m->edx = (DWORD)(m->eax + 0xa0u);	/* 449eb3: lea edx, [eax + 0xa0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449eb9: push edx */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 449eba: mov ecx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449ec0: add eax, 0x20 */
	m->edx = (DWORD)(m->ecx + 0x158u);	/* 449ec3: lea edx, [ecx + 0x158] */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449ec9: add ecx, 0xd8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449ecf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449ed0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449ed1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x449ed7u; native_call(m, 0x427970u);	/* 449ed2: call 0x427970 */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 449ed7: mov eax, dword ptr [0x9db0a4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449edc: add esp, 0x28 */
	m->ecx = m->eax;	/* 449edf: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449ee1: and ecx, 0x800001ff */
	if (!m->sf) goto L_449ef1;	/* 449ee7: jns 0x449ef1 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 449ee9: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449eea: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 449ef0: inc ecx */
L_449ef1:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 449ef1: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 449ef2: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449ef8: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449ef9: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 449efb: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 449f01: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 449f04: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x449f0du; native_call(m, 0x4566c0u);	/* 449f08: call 0x4566c0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f0d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x449f14u; native_call(m, m->ebx);	/* 449f12: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f14: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f19: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f1e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f23: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x449f2au; native_call(m, m->ebp);	/* 449f28: call ebp */
	m->eax = M32((DWORD)(0x9f630cu));	/* 449f2a: mov eax, dword ptr [0x9f630c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f2f: push 0 */
	m->ecx = (DWORD)(m->eax + 0x74u);	/* 449f31: lea ecx, [eax + 0x74] */
	{ DWORD a_ = m->eax, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449f34: add eax, 0x4c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449f37: push ecx */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 449f38: mov ecx, dword ptr [0x9f6308] */
	m->edx = (DWORD)(m->ecx + 0xd0u);	/* 449f3e: lea edx, [ecx + 0xd0] */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449f44: add ecx, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449f4a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449f4b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449f4c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x449f52u; native_call(m, 0x4284d0u);	/* 449f4d: call 0x4284d0 */
	m->eax = M32((DWORD)(0x9f630cu));	/* 449f52: mov eax, dword ptr [0x9f630c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f57: push 0 */
	m->ecx = (DWORD)(m->eax + 0x74u);	/* 449f59: lea ecx, [eax + 0x74] */
	{ DWORD a_ = m->eax, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449f5c: add eax, 0x4c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449f5f: push ecx */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 449f60: mov ecx, dword ptr [0x9f6308] */
	m->edx = (DWORD)(m->ecx + 0x198u);	/* 449f66: lea edx, [ecx + 0x198] */
	{ DWORD a_ = m->ecx, b_ = 0x160u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449f6c: add ecx, 0x160 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449f72: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449f73: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449f74: push ecx */
	m->esp -= 4; M32(m->esp) = 0x449f7au; native_call(m, 0x4285c0u);	/* 449f75: call 0x4285c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f7a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f7f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f84: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f89: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 449f8e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x449f98u; native_call(m, 0x41f0e0u);	/* 449f93: call 0x41f0e0 */
	m->ecx = 0x20u;	/* 449f98: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449f9d: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x64u);	/* 449f9f: lea edi, [esp + 0x64] */
	m->edx = (DWORD)(m->esp + 0x64u);	/* 449fa3: lea edx, [esp + 0x64] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 449fa7: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x75f2a4u;	/* 449fa9: mov edi, 0x75f2a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449fae: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449fb1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449fb3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449fb5: sub edi, ecx */
	m->eax = m->ecx;	/* 449fb7: mov eax, ecx */
	m->esi = m->edi;	/* 449fb9: mov esi, edi */
	m->edi = m->edx;	/* 449fbb: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x64u);	/* 449fbd: lea edx, [esp + 0x64] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449fc1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449fc4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 449fc6: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449fc8: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449fca: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449fcd: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b10u;	/* 449fcf: mov edi, 0x4b2b10 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449fd4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449fd7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449fd9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449fdb: sub edi, ecx */
	m->esi = m->edi;	/* 449fdd: mov esi, edi */
	m->edi = m->edx;	/* 449fdf: mov edi, edx */
	m->edx = m->ecx;	/* 449fe1: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449fe3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449fe6: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 449fe8: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449fea: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449feb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449fee: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 449ff0: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449ff2: and ecx, 3 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 449ff5: mov eax, dword ptr [0x9f63b4] */
	m->edx = (DWORD)(m->esp + 0x64u);	/* 449ffa: lea edx, [esp + 0x64] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449ffe: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a000: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a003: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a006: sub ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a008: xor eax, eax */
	m->edi = M32((DWORD)(m->ecx*4 + 0x9db9e4u));	/* 44a00a: mov edi, dword ptr [ecx*4 + 0x9db9e4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a011: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 44a014: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x75c9a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a017: add edi, 0x75c9a4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a01d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a01f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a021: sub edi, ecx */
	m->esi = m->edi;	/* 44a023: mov esi, edi */
	m->edi = m->edx;	/* 44a025: mov edi, edx */
	m->edx = m->ecx;	/* 44a027: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a029: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a02c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44a02e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44a030: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a031: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a034: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 44a036: mov ecx, edx */
	m->edx = M32((DWORD)(0x9f6308u));	/* 44a038: mov edx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a03e: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x64u);	/* 44a041: lea eax, [esp + 0x64] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a045: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44a047: mov ecx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a04d: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xaau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a04e: add ecx, 0xaa */
	{ DWORD a_ = m->edx, b_ = 0xc4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a054: add edx, 0xc4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a05a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a05b: push edx */
	m->esp -= 4; M32(m->esp) = 0x44a061u; native_call(m, 0x4028b0u);	/* 44a05c: call 0x4028b0 */
	m->ecx = 0x20u;	/* 44a061: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a066: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x70u);	/* 44a068: lea edi, [esp + 0x70] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a06c: add esp, 0x48 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44a06f: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x20u;	/* 44a071: mov ecx, 0x20 */
	m->edi = (DWORD)(m->esp + 0xa8u);	/* 44a076: lea edi, [esp + 0xa8] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44a07d: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x75f324u;	/* 44a07f: mov edi, 0x75f324 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a084: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a087: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a089: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a08b: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a08d: lea edx, [esp + 0x28] */
	m->eax = m->ecx;	/* 44a091: mov eax, ecx */
	m->esi = m->edi;	/* 44a093: mov esi, edi */
	m->edi = m->edx;	/* 44a095: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a097: lea edx, [esp + 0x28] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a09b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a09e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44a0a0: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a0a2: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a0a4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a0a7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b10u;	/* 44a0a9: mov edi, 0x4b2b10 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a0ae: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a0b1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a0b3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a0b5: sub edi, ecx */
	m->esi = m->edi;	/* 44a0b7: mov esi, edi */
	m->edi = m->edx;	/* 44a0b9: mov edi, edx */
	m->edx = m->ecx;	/* 44a0bb: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a0bd: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a0c0: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44a0c2: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44a0c4: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a0c5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a0c8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a0ca: mov eax, dword ptr [0x9f63b4] */
	m->ecx = m->edx;	/* 44a0cf: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a0d1: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a0d4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a0d6: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a0d9: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a0dc: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db9ecu));	/* 44a0de: mov eax, dword ptr [ecx*4 + 0x9db9ec] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44a0e5: test eax, eax */
	if (!m->zf) goto L_44a0f4;	/* 44a0e7: jne 0x44a0f4 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a0e9: lea edx, [esp + 0x28] */
	m->edi = 0x75c0a4u;	/* 44a0ed: mov edi, 0x75c0a4 */
	goto L_44a140;	/* 44a0f2: jmp 0x44a140 */
L_44a0f4:
	m->ecx = (DWORD)(m->esp + 0xa8u);	/* 44a0f4: lea ecx, [esp + 0xa8] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44a0fb: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a0fd: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a0fe: push eax */
	m->esp -= 4; M32(m->esp) = 0x44a104u; native_call(m, 0x49fb53u);	/* 44a0ff: call 0x49fb53 */
	m->edi = (DWORD)(m->esp + 0xb4u);	/* 44a104: lea edi, [esp + 0xb4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a10b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a10e: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a110: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a113: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a115: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a117: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a119: lea edx, [esp + 0x28] */
	m->esi = m->edi;	/* 44a11d: mov esi, edi */
	m->edi = m->edx;	/* 44a11f: mov edi, edx */
	m->edx = m->ecx;	/* 44a121: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a123: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a126: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44a128: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44a12a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a12b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a12e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 44a130: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a132: lea edx, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a136: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a139: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x75c124u;	/* 44a13b: mov edi, 0x75c124 */
L_44a140:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a140: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a143: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a145: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a147: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a149: sub edi, ecx */
	m->esi = m->edi;	/* 44a14b: mov esi, edi */
	m->edi = m->edx;	/* 44a14d: mov edi, edx */
	m->edx = m->ecx;	/* 44a14f: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a151: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a154: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44a156: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44a158: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a159: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a15c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 44a15e: mov ecx, edx */
	m->edx = M32((DWORD)(0x9f6308u));	/* 44a160: mov edx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a166: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 44a169: lea eax, [esp + 0x28] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a16d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44a16f: mov ecx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a175: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a176: add ecx, 0xbc */
	{ DWORD a_ = m->edx, b_ = 0xc4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a17c: add edx, 0xc4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a182: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a183: push edx */
	m->esp -= 4; M32(m->esp) = 0x44a189u; native_call(m, 0x4028b0u);	/* 44a184: call 0x4028b0 */
	m->ecx = 0x20u;	/* 44a189: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a18e: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 44a190: lea edi, [esp + 0x34] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a194: add esp, 0xc */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44a197: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x20u;	/* 44a199: mov ecx, 0x20 */
	m->edi = (DWORD)(m->esp + 0xa8u);	/* 44a19e: lea edi, [esp + 0xa8] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44a1a5: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x75f3a4u;	/* 44a1a7: mov edi, 0x75f3a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a1ac: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a1af: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a1b1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a1b3: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a1b5: lea edx, [esp + 0x28] */
	m->eax = m->ecx;	/* 44a1b9: mov eax, ecx */
	m->esi = m->edi;	/* 44a1bb: mov esi, edi */
	m->edi = m->edx;	/* 44a1bd: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a1bf: lea edx, [esp + 0x28] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a1c3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a1c6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44a1c8: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a1ca: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a1cc: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a1cf: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b10u;	/* 44a1d1: mov edi, 0x4b2b10 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a1d6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a1d9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a1db: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a1dd: sub edi, ecx */
	m->esi = m->edi;	/* 44a1df: mov esi, edi */
	m->edi = m->edx;	/* 44a1e1: mov edi, edx */
	m->edx = m->ecx;	/* 44a1e3: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a1e5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a1e8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44a1ea: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44a1ec: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a1ed: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a1f0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a1f2: mov eax, dword ptr [0x9f63b4] */
	m->ecx = m->edx;	/* 44a1f7: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a1f9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a1fc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a1fe: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a201: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a204: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db9e8u));	/* 44a206: mov eax, dword ptr [ecx*4 + 0x9db9e8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44a20d: test eax, eax */
	if (!m->zf) goto L_44a21c;	/* 44a20f: jne 0x44a21c */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a211: lea edx, [esp + 0x28] */
	m->edi = 0x75bfa4u;	/* 44a215: mov edi, 0x75bfa4 */
	goto L_44a268;	/* 44a21a: jmp 0x44a268 */
L_44a21c:
	m->ecx = (DWORD)(m->esp + 0xa8u);	/* 44a21c: lea ecx, [esp + 0xa8] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44a223: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a225: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a226: push eax */
	m->esp -= 4; M32(m->esp) = 0x44a22cu; native_call(m, 0x49fb53u);	/* 44a227: call 0x49fb53 */
	m->edi = (DWORD)(m->esp + 0xb4u);	/* 44a22c: lea edi, [esp + 0xb4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a233: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a236: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a238: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a23b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a23d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a23f: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a241: lea edx, [esp + 0x28] */
	m->esi = m->edi;	/* 44a245: mov esi, edi */
	m->edi = m->edx;	/* 44a247: mov edi, edx */
	m->edx = m->ecx;	/* 44a249: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a24b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a24e: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44a250: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44a252: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a253: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a256: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 44a258: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 44a25a: lea edx, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a25e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a261: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x75c024u;	/* 44a263: mov edi, 0x75c024 */
L_44a268:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a268: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44a26b: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a26d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44a26f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a271: sub edi, ecx */
	m->esi = m->edi;	/* 44a273: mov esi, edi */
	m->edi = m->edx;	/* 44a275: mov edi, edx */
	m->edx = m->ecx;	/* 44a277: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a279: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44a27c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44a27e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44a280: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a281: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44a284: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 44a286: mov ecx, edx */
	m->edx = M32((DWORD)(0x9f6308u));	/* 44a288: mov edx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a28e: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 44a291: lea eax, [esp + 0x28] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44a295: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44a297: mov ecx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a29d: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a29e: add ecx, 0xce */
	{ DWORD a_ = m->edx, b_ = 0xc4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a2a4: add edx, 0xc4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a2aa: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a2ab: push edx */
	m->esp -= 4; M32(m->esp) = 0x44a2b1u; native_call(m, 0x4028b0u);	/* 44a2ac: call 0x4028b0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a2b1: mov eax, dword ptr [0x9f63b4] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 44a2b6: mov esi, dword ptr [0x4a920c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a2bc: add esp, 0xc */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a2bf: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a2c2: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a2c5: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db9c0u));	/* 44a2c7: mov eax, dword ptr [ecx*4 + 0x9db9c0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44a2ce: test eax, eax */
	if (m->zf) goto L_44a565;	/* 44a2d0: je 0x44a565 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a2d6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a2db: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a2e0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a2e5: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a2ea: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44a2f4u; native_call(m, 0x41f0e0u);	/* 44a2ef: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f630cu));	/* 44a2f4: mov eax, dword ptr [0x9f630c] */
	m->edx = M32((DWORD)(0x9f6310u));	/* 44a2f9: mov edx, dword ptr [0x9f6310] */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 44a2ff: mov ecx, dword ptr [0x9f6308] */
	{ DWORD v_ = 0x75f524u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a305: push 0x75f524 */
	{ DWORD a_ = m->eax, b_ = 0xf2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a30a: add eax, 0xf2 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a30f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a310: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a311: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44a317u; native_call(m, 0x4029d0u);	/* 44a312: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a317: add esp, 0x24 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a31a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44a321u; native_call(m, m->ebx);	/* 44a31f: call ebx */
	m->eax = M32((DWORD)(0x4dfa00u));	/* 44a321: mov eax, dword ptr [0x4dfa00] */
	m->edx = m->eax;	/* 44a326: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44a328: and edx, 0x800001ff */
	if (!m->sf) goto L_44a338;	/* 44a32e: jns 0x44a338 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 44a330: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44a331: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44a337: inc edx */
L_44a338:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a338: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 44a339: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44a33f: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44a340: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a346: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44a348: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 44a34b: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44a354u; native_call(m, 0x4566c0u);	/* 44a34f: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a354: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a359: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a35e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a363: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44a36au; native_call(m, m->ebp);	/* 44a368: call ebp */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a36a: mov eax, dword ptr [0x9f63b4] */
	m->edi = 0x146u;	/* 44a36f: mov edi, 0x146 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 44a374: xor ebx, ebx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a376: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44a379: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a37c: sub edx, eax */
	m->ecx = M32((DWORD)(m->edx*4 + 0x9db9c0u));	/* 44a37e: mov ecx, dword ptr [edx*4 + 0x9db9c0] */
	m->edx = m->ecx;	/* 44a385: mov edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44a387: shl edx, 5 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a38a: sub edi, edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44a38c: test ecx, ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 44a38e: mov dword ptr [esp + 0x20], edi */
	if (m->zf || m->sf != m->of) goto L_44a4de;	/* 44a392: jle 0x44a4de */
L_44a398:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a398: lea ecx, [eax + eax*2] */
	m->ebp = 0x3u;	/* 44a39b: mov ebp, 3 */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a3a0: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a3a3: sub ecx, eax */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a3a5: push 7 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a3a7: add ecx, ebx */
	m->ecx = M32((DWORD)(m->ecx*4 + 0x9db9c4u));	/* 44a3a9: mov ecx, dword ptr [ecx*4 + 0x9db9c4] */
	m->eax = m->ecx;	/* 44a3b0: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44a3b2: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ebp; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 44a3b3: idiv ebp */
	m->eax = 0x55555556u;	/* 44a3b5: mov eax, 0x55555556 */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 44a3ba: mov dword ptr [esp + 0x14], edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 44a3be: imul ecx */
	m->eax = m->edx;	/* 44a3c0: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44a3c2: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a3c5: add edx, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 44a3c7: mov dword ptr [esp + 0x1c], edx */
	m->esp -= 4; M32(m->esp) = 0x44a3d1u; native_call(m, M32(0x4a921cu));	/* 44a3cb: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 44a3d1: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44a3d5: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 44a3db: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44a3df: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 44a3e5: fstp dword ptr [esp + 0x24] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 44a3e9: fild dword ptr [esp + 0x10] */
	m->ebp = M32((DWORD)(m->esp + 0x24u));	/* 44a3ed: mov ebp, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44a3f1: push ebp */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44a3f2: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 44a3f8: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44a3fc: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 44a402: fstp dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 44a406: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a40a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44a40du; native_call(m, m->esi);	/* 44a40b: call esi */
	m->edx = M32((DWORD)(0x9f630cu));	/* 44a40d: mov edx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->edx, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a413: add edx, 0x104 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a419: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44a41a: push edi */
	m->esp -= 4; M32(m->esp) = 0x44a420u; native_call(m, 0x41ef60u);	/* 44a41b: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 44a420: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44a424: fadd dword ptr [0x4a95e8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a42a: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44a42d: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44a433: push ebp */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 44a434: fstp dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 44a438: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a43c: push eax */
	m->esp -= 4; M32(m->esp) = 0x44a43fu; native_call(m, m->esi);	/* 44a43d: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44a43f: mov ecx, dword ptr [0x9f630c] */
	m->ebp = (DWORD)(m->edi + 0x30u);	/* 44a445: lea ebp, [edi + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a448: add ecx, 0x104 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a44e: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44a44f: push ebp */
	m->esp -= 4; M32(m->esp) = 0x44a455u; native_call(m, 0x41ef60u);	/* 44a450: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 44a455: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44a459: fadd dword ptr [0x4a95e8] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 44a45f: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a463: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44a466: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 44a46c: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 44a470: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a474: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a475: push eax */
	m->esp -= 4; M32(m->esp) = 0x44a478u; native_call(m, m->esi);	/* 44a476: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44a478: mov ecx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->ecx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a47e: add ecx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a484: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44a485: push ebp */
	m->esp -= 4; M32(m->esp) = 0x44a48bu; native_call(m, 0x41ef60u);	/* 44a486: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 44a48b: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 44a48f: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a493: add esp, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a496: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a497: push eax */
	m->esp -= 4; M32(m->esp) = 0x44a49au; native_call(m, m->esi);	/* 44a498: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44a49a: mov ecx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->ecx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a4a0: add ecx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a4a6: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44a4a7: push edi */
	m->esp -= 4; M32(m->esp) = 0x44a4adu; native_call(m, 0x41ef60u);	/* 44a4a8: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a4ad: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x44a4b6u; native_call(m, M32(0x4a9220u));	/* 44a4b0: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a4b6: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 44a4bb: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a4bc: add edi, 0x40 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a4bf: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44a4c2: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a4c5: sub edx, eax */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->edx*4 + 0x9db9c0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44a4c7: cmp ebx, dword ptr [edx*4 + 0x9db9c0] */
	if (m->sf != m->of) goto L_44a398;	/* 44a4ce: jl 0x44a398 */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 44a4d4: mov ebp, dword ptr [0x4a9228] */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 44a4da: mov edi, dword ptr [esp + 0x20] */
L_44a4de:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a4de: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44a4e9u; native_call(m, M32(0x4a922cu));	/* 44a4e3: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a4e9: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a4ee: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a4f3: push 0x3dcccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a4f8: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a4fd: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44a507u; native_call(m, 0x41f0e0u);	/* 44a502: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a507: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a50c: add esp, 0x14 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 44a50f: xor ebx, ebx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a511: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a514: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a517: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db9c0u));	/* 44a519: mov eax, dword ptr [ecx*4 + 0x9db9c0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44a520: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_44a55f;	/* 44a522: jle 0x44a55f */
L_44a524:
	m->eax = M32((DWORD)(0x9f630cu));	/* 44a524: mov eax, dword ptr [0x9f630c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a529: push 0 */
	m->ecx = (DWORD)(m->edi + 0x30u);	/* 44a52b: lea ecx, [edi + 0x30] */
	m->edx = (DWORD)(m->eax + 0x134u);	/* 44a52e: lea edx, [eax + 0x134] */
	{ DWORD a_ = m->eax, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a534: add eax, 0x104 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a539: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a53a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a53b: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44a53c: push edi */
	m->esp -= 4; M32(m->esp) = 0x44a542u; native_call(m, 0x427970u);	/* 44a53d: call 0x427970 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a542: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a547: add esp, 0x14 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 44a54a: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a54b: add edi, 0x40 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a54e: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44a551: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a554: sub edx, eax */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->edx*4 + 0x9db9c0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44a556: cmp ebx, dword ptr [edx*4 + 0x9db9c0] */
	if (m->sf != m->of) goto L_44a524;	/* 44a55d: jl 0x44a524 */
L_44a55f:
	m->ebx = M32((DWORD)(0x4a9224u));	/* 44a55f: mov ebx, dword ptr [0x4a9224] */
L_44a565:
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44a565: mov ecx, dword ptr [0x9f630c] */
	m->eax = M32((DWORD)(0x9f6310u));	/* 44a56b: mov eax, dword ptr [0x9f6310] */
	m->edx = M32((DWORD)(0x9f6308u));	/* 44a570: mov edx, dword ptr [0x9f6308] */
	{ DWORD v_ = 0x75f5a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a576: push 0x75f5a4 */
	{ DWORD a_ = m->ecx, b_ = 0x142u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a57b: add ecx, 0x142 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a581: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a582: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a583: push edx */
	m->esp -= 4; M32(m->esp) = 0x44a589u; native_call(m, 0x4029d0u);	/* 44a584: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a589: add esp, 0x10 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a58c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44a593u; native_call(m, m->ebx);	/* 44a591: call ebx */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a593: mov eax, dword ptr [0x9f63b4] */
	m->edi = 0x146u;	/* 44a598: mov edi, 0x146 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 44a59d: mov dword ptr [esp + 0x1c], 0 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a5a5: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a5a8: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a5ab: sub ecx, eax */
	m->ecx = M32((DWORD)(m->ecx*4 + 0x9db99cu));	/* 44a5ad: mov ecx, dword ptr [ecx*4 + 0x9db99c] */
	m->edx = m->ecx;	/* 44a5b4: mov edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44a5b6: shl edx, 5 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a5b9: sub edi, edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44a5bb: test ecx, ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 44a5bd: mov dword ptr [esp + 0x20], edi */
	if (m->zf || m->sf != m->of) goto L_44a78a;	/* 44a5c1: jle 0x44a78a */
L_44a5c7:
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 44a5c7: mov edx, dword ptr [esp + 0x1c] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a5cb: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a5ce: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a5d1: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a5d3: add ecx, edx */
	m->ebx = M32((DWORD)(m->ecx*4 + 0x9db9a0u));	/* 44a5d5: mov ebx, dword ptr [ecx*4 + 0x9db9a0] */
	m->ecx = 0x3u;	/* 44a5dc: mov ecx, 3 */
	m->eax = m->ebx;	/* 44a5e1: mov eax, ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44a5e3: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 44a5e4: idiv ecx */
	m->eax = 0x55555556u;	/* 44a5e6: mov eax, 0x55555556 */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 44a5eb: mov dword ptr [esp + 0x10], edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 44a5ef: imul ebx */
	m->eax = m->edx;	/* 44a5f1: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44a5f3: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a5f6: add edx, eax */
	m->eax = M32((DWORD)(0x4dfa00u));	/* 44a5f8: mov eax, dword ptr [0x4dfa00] */
	m->ecx = m->eax;	/* 44a5fd: mov ecx, eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 44a5ff: mov dword ptr [esp + 0x18], edx */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a603: and ecx, 0x800001ff */
	if (!m->sf) goto L_44a613;	/* 44a609: jns 0x44a613 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44a60b: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a60c: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44a612: inc ecx */
L_44a613:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44a613: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44a614: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a61a: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a61b: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44a61d: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44a623: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44a626: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44a62fu; native_call(m, 0x4566c0u);	/* 44a62a: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a62f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a634: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a639: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a63e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44a645u; native_call(m, m->ebp);	/* 44a643: call ebp */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44a645: test ebx, ebx */
	if (m->sf != m->of) goto L_44a73f;	/* 44a647: jl 0x44a73f */
	{ DWORD a_ = m->ebx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44a64d: cmp ebx, 8 */
	if (!m->zf && m->sf == m->of) goto L_44a73f;	/* 44a650: jg 0x44a73f */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a656: push 7 */
	m->esp -= 4; M32(m->esp) = 0x44a65eu; native_call(m, M32(0x4a921cu));	/* 44a658: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 44a65e: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44a662: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 44a668: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44a66c: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 44a672: fstp dword ptr [esp + 0x24] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 44a676: fild dword ptr [esp + 0x10] */
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 44a67a: mov ebx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a67e: push ebx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44a67f: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 44a685: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44a689: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 44a68f: fstp dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 44a693: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a697: push eax */
	m->esp -= 4; M32(m->esp) = 0x44a69au; native_call(m, m->esi);	/* 44a698: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44a69a: mov ecx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->ecx, b_ = 0x154u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a6a0: add ecx, 0x154 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a6a6: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44a6a7: push edi */
	m->esp -= 4; M32(m->esp) = 0x44a6adu; native_call(m, 0x41ef60u);	/* 44a6a8: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 44a6ad: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44a6b1: fadd dword ptr [0x4a95e8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a6b7: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44a6ba: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a6c0: push ebx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 44a6c1: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 44a6c5: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a6c9: push edx */
	m->esp -= 4; M32(m->esp) = 0x44a6ccu; native_call(m, m->esi);	/* 44a6ca: call esi */
	m->eax = M32((DWORD)(0x9f630cu));	/* 44a6cc: mov eax, dword ptr [0x9f630c] */
	m->ebx = (DWORD)(m->edi + 0x30u);	/* 44a6d1: lea ebx, [edi + 0x30] */
	{ DWORD a_ = m->eax, b_ = 0x154u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a6d4: add eax, 0x154 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a6d9: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a6da: push ebx */
	m->esp -= 4; M32(m->esp) = 0x44a6e0u; native_call(m, 0x41ef60u);	/* 44a6db: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 44a6e0: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44a6e4: fadd dword ptr [0x4a95e8] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 44a6ea: mov edx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a6ee: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44a6f1: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 44a6f7: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 44a6fb: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a6ff: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a700: push edx */
	m->esp -= 4; M32(m->esp) = 0x44a703u; native_call(m, m->esi);	/* 44a701: call esi */
	m->eax = M32((DWORD)(0x9f630cu));	/* 44a703: mov eax, dword ptr [0x9f630c] */
	{ DWORD a_ = m->eax, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a708: add eax, 0x184 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a70d: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a70e: push ebx */
	m->esp -= 4; M32(m->esp) = 0x44a714u; native_call(m, 0x41ef60u);	/* 44a70f: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 44a714: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 44a718: mov edx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a71c: add esp, 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a71f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a720: push edx */
	m->esp -= 4; M32(m->esp) = 0x44a723u; native_call(m, m->esi);	/* 44a721: call esi */
	m->eax = M32((DWORD)(0x9f630cu));	/* 44a723: mov eax, dword ptr [0x9f630c] */
	{ DWORD a_ = m->eax, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a728: add eax, 0x184 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a72d: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44a72e: push edi */
	m->esp -= 4; M32(m->esp) = 0x44a734u; native_call(m, 0x41ef60u);	/* 44a72f: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a734: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x44a73du; native_call(m, M32(0x4a9220u));	/* 44a737: call dword ptr [0x4a9220] */
	goto L_44a75e;	/* 44a73d: jmp 0x44a75e */
L_44a73f:
	m->edx = M32((DWORD)(0x9f630cu));	/* 44a73f: mov edx, dword ptr [0x9f630c] */
	m->ecx = (DWORD)(m->edi + 0x30u);	/* 44a745: lea ecx, [edi + 0x30] */
	{ DWORD v_ = 0x4b2b0cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a748: push 0x4b2b0c */
	{ DWORD a_ = m->edx, b_ = 0x164u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a74d: add edx, 0x164 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a753: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a754: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44a755: push edi */
	m->esp -= 4; M32(m->esp) = 0x44a75bu; native_call(m, 0x4029d0u);	/* 44a756: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a75b: add esp, 0x10 */
L_44a75e:
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a75e: mov eax, dword ptr [0x9f63b4] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 44a763: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44a767: inc ecx */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a768: add edi, 0x40 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a76b: lea edx, [eax + eax*2] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 44a76e: mov dword ptr [esp + 0x1c], ecx */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44a772: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a775: sub edx, eax */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->edx*4 + 0x9db99cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44a777: cmp ecx, dword ptr [edx*4 + 0x9db99c] */
	if (m->sf != m->of) goto L_44a5c7;	/* 44a77e: jl 0x44a5c7 */
	m->ebx = M32((DWORD)(0x4a9224u));	/* 44a784: mov ebx, dword ptr [0x4a9224] */
L_44a78a:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a78a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44a795u; native_call(m, M32(0x4a922cu));	/* 44a78f: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a795: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a79a: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a79f: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a7a4: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a7a9: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44a7b3u; native_call(m, 0x41f0e0u);	/* 44a7ae: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a7b3: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a7b8: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 44a7bb: xor edi, edi */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a7bd: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44a7c0: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a7c3: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db99cu));	/* 44a7c5: mov eax, dword ptr [ecx*4 + 0x9db99c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44a7cc: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_44a80f;	/* 44a7ce: jle 0x44a80f */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 44a7d0: mov esi, dword ptr [esp + 0x20] */
L_44a7d4:
	m->eax = M32((DWORD)(0x9f630cu));	/* 44a7d4: mov eax, dword ptr [0x9f630c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a7d9: push 0 */
	m->ecx = (DWORD)(m->esi + 0x30u);	/* 44a7db: lea ecx, [esi + 0x30] */
	m->edx = (DWORD)(m->eax + 0x184u);	/* 44a7de: lea edx, [eax + 0x184] */
	{ DWORD a_ = m->eax, b_ = 0x154u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a7e4: add eax, 0x154 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a7e9: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a7ea: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a7eb: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44a7ec: push esi */
	m->esp -= 4; M32(m->esp) = 0x44a7f2u; native_call(m, 0x427970u);	/* 44a7ed: call 0x427970 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44a7f2: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a7f7: add esp, 0x14 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 44a7fa: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44a7fb: add esi, 0x40 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44a7fe: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44a801: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44a804: sub edx, eax */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->edx*4 + 0x9db99cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44a806: cmp edi, dword ptr [edx*4 + 0x9db99c] */
	if (m->sf != m->of) goto L_44a7d4;	/* 44a80d: jl 0x44a7d4 */
L_44a80f:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44a80f: xor esi, esi */
	m->edi = 0x75f6a4u;	/* 44a811: mov edi, 0x75f6a4 */
L_44a816:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a816: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44a81du; native_call(m, m->ebx);	/* 44a81b: call ebx */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44a81d: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44a822: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a824: and ecx, 0x800001ff */
	if (!m->sf) goto L_44a834;	/* 44a82a: jns 0x44a834 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44a82c: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44a82d: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44a833: inc ecx */
L_44a834:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44a834: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44a835: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a83b: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44a83c: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44a83e: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44a844: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44a847: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44a850u; native_call(m, 0x4566c0u);	/* 44a84b: call 0x4566c0 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a850: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a855: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a85a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a85f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44a866u; native_call(m, m->ebp);	/* 44a864: call ebp */
	m->ecx = M32((DWORD)(0x9f6314u));	/* 44a866: mov ecx, dword ptr [0x9f6314] */
	m->eax = M32((DWORD)(0x9f6308u));	/* 44a86c: mov eax, dword ptr [0x9f6308] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a871: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 44a873: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a876: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a879: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x10eu);	/* 44a87a: lea edx, [esi + eax + 0x10e] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a881: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x96u);	/* 44a882: lea eax, [esi + eax + 0x96] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a889: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a88a: push eax */
	m->esp -= 4; M32(m->esp) = 0x44a890u; native_call(m, 0x4282f0u);	/* 44a88b: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f62f4u));	/* 44a890: mov ecx, dword ptr [0x9f62f4] */
	m->edx = M32((DWORD)(0x9f62f0u));	/* 44a896: mov edx, dword ptr [0x9f62f0] */
	m->eax = M32((DWORD)(0x9f62ecu));	/* 44a89c: mov eax, dword ptr [0x9f62ec] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8a1: push ecx */
	m->ecx = M32((DWORD)(0x9f62e8u));	/* 44a8a2: mov ecx, dword ptr [0x9f62e8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8a8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8a9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8aa: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8ab: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44a8b5u; native_call(m, 0x41f0e0u);	/* 44a8b0: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f6308u));	/* 44a8b5: mov eax, dword ptr [0x9f6308] */
	m->ecx = M32((DWORD)(0x9f6314u));	/* 44a8ba: mov ecx, dword ptr [0x9f6314] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8c0: push edi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44a8c1: add ecx, -0x28 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x10eu);	/* 44a8c4: lea edx, [esi + eax + 0x10e] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8cb: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x96u);	/* 44a8cc: lea edx, [esi + eax + 0x96] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8d3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8d4: push edx */
	m->esp -= 4; M32(m->esp) = 0x44a8dau; native_call(m, 0x4029d0u);	/* 44a8d5: call 0x4029d0 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44a8da: add edi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a8e0: add esp, 0x38 */
	{ DWORD a_ = m->esi, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44a8e3: add esi, 0x8c */
	{ DWORD a_ = m->edi, b_ = 0x75f7a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44a8e9: cmp edi, 0x75f7a4 */
	if (m->sf != m->of) goto L_44a816;	/* 44a8ef: jl 0x44a816 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8f5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8fa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a8ff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a904: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44a90bu; native_call(m, m->ebp);	/* 44a909: call ebp */
	m->eax = M32((DWORD)(0x9f6314u));	/* 44a90b: mov eax, dword ptr [0x9f6314] */
	m->ecx = M32((DWORD)(0x9f6310u));	/* 44a910: mov ecx, dword ptr [0x9f6310] */
	m->edx = M32((DWORD)(0x9f630cu));	/* 44a916: mov edx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a91c: push eax */
	m->eax = M32((DWORD)(0x9f6308u));	/* 44a91d: mov eax, dword ptr [0x9f6308] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a922: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44a923: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44a924: push eax */
	m->esp -= 4; M32(m->esp) = 0x44a92au; native_call(m, 0x428a00u);	/* 44a925: call 0x428a00 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a92a: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a92f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a931: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a933: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a935: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44a93fu; native_call(m, 0x41f0e0u);	/* 44a93a: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a93f: push 1 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a941: push 0x1e0 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a946: push 0x280 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a94b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a94d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44a954u; native_call(m, 0x427970u);	/* 44a94f: call 0x427970 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a954: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a959: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a95e: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a963: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a968: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44a972u; native_call(m, 0x41f0e0u);	/* 44a96d: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a972: add esp, 0x4c */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a975: push 1 */
	{ DWORD v_ = 0x122u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a977: push 0x122 */
	{ DWORD v_ = 0x244u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a97c: push 0x244 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a981: push 0xc8 */
	{ DWORD v_ = 0x3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a986: push 0x3c */
	m->esp -= 4; M32(m->esp) = 0x44a98du; native_call(m, 0x427970u);	/* 44a988: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a98d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a992: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a997: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a99c: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a99e: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44a9a8u; native_call(m, 0x41f0e0u);	/* 44a9a3: call 0x41f0e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9a8: push 0 */
	{ DWORD v_ = 0x11du; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9aa: push 0x11d */
	{ DWORD v_ = 0x23fu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9af: push 0x23f */
	{ DWORD v_ = 0xcdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9b4: push 0xcd */
	{ DWORD v_ = 0x41u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9b9: push 0x41 */
	m->esp -= 4; M32(m->esp) = 0x44a9c0u; native_call(m, 0x427970u);	/* 44a9bb: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9c0: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9c5: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9c7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9cc: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9d1: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44a9dbu; native_call(m, 0x41f0e0u);	/* 44a9d6: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44a9db: add esp, 0x50 */
	{ DWORD v_ = 0x75f7a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9de: push 0x75f7a4 */
	{ DWORD v_ = 0x23au; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9e3: push 0x23a */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9e8: push 0xdc */
	{ DWORD v_ = 0x46u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9ed: push 0x46 */
	m->esp -= 4; M32(m->esp) = 0x44a9f4u; native_call(m, 0x4029d0u);	/* 44a9ef: call 0x4029d0 */
	{ DWORD v_ = 0x74de24u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9f4: push 0x74de24 */
	{ DWORD v_ = 0x23au; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9f9: push 0x23a */
	{ DWORD v_ = 0xf5u; m->esp -= 4; M32(m->esp) = v_; }	/* 44a9fe: push 0xf5 */
	{ DWORD v_ = 0x46u; m->esp -= 4; M32(m->esp) = v_; }	/* 44aa03: push 0x46 */
	m->esp -= 4; M32(m->esp) = 0x44aa0au; native_call(m, 0x4029d0u);	/* 44aa05: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44aa0a: add esp, 0x20 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44aa0d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44aa0e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44aa0f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44aa10: pop ebx */
	m->esp = m->ebp;	/* 44aa11: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44aa13: pop ebp */
	m->esp += 4 + 0; return;	/* 44aa14: ret  */
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
