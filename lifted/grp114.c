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

static void lift_44aa20(X86 *m);
static void lift_448ac0(X86 *m);

/* missionsel_448ac0 (0x448ac0), lifted by tools/lift.py */
static void lift_448ac0(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 448ac0: push ebp */
	m->ebp = m->esp;	/* 448ac1: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 448ac3: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x228u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448ac6: sub esp, 0x228 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 448acc: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 448ad1: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 448ad7: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 448ad8: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 448ad9: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 448ada: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448adb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448adc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x448ae2u; native_call(m, 0x447710u);	/* 448add: call 0x447710 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 448ae2: push 2 */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 448ae4: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x448aedu; native_call(m, 0x41ef90u);	/* 448ae8: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448aed: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x448af6u; native_call(m, M32(0x4a9218u));	/* 448af0: call dword ptr [0x4a9218] */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 448af6: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448afc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448b01: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448b06: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448b0b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448b12u; native_call(m, m->ebx);	/* 448b10: call ebx */
	m->edx = M32((DWORD)(0x4deb50u));	/* 448b12: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9f6314u));	/* 448b18: mov eax, dword ptr [0x9f6314] */
	m->ecx = M32((DWORD)(0x9f6310u));	/* 448b1d: mov ecx, dword ptr [0x9f6310] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448b23: push edx */
	m->edx = M32((DWORD)(0x9f630cu));	/* 448b24: mov edx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448b2a: push eax */
	m->eax = M32((DWORD)(0x9f6308u));	/* 448b2b: mov eax, dword ptr [0x9f6308] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448b30: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448b31: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448b32: push eax */
	m->esp -= 4; M32(m->esp) = 0x448b38u; native_call(m, 0x427a90u);	/* 448b33: call 0x427a90 */
	m->ecx = M32((DWORD)(0x9f6324u));	/* 448b38: mov ecx, dword ptr [0x9f6324] */
	m->edx = M32((DWORD)(0x9f6320u));	/* 448b3e: mov edx, dword ptr [0x9f6320] */
	m->eax = M32((DWORD)(0x9f631cu));	/* 448b44: mov eax, dword ptr [0x9f631c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448b49: push ecx */
	m->ecx = M32((DWORD)(0x9f6318u));	/* 448b4a: mov ecx, dword ptr [0x9f6318] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448b50: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448b51: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448b52: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 448b53: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x448b5du; native_call(m, 0x41f0e0u);	/* 448b58: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 448b5d: mov eax, dword ptr [0x9f63b4] */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 448b62: lea edx, [esp + 0x58] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 448b66: push 0xa */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 448b68: inc eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448b69: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448b6a: push eax */
	m->esp -= 4; M32(m->esp) = 0x448b70u; native_call(m, 0x49fb53u);	/* 448b6b: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9f63b4u));	/* 448b70: mov edx, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448b76: add esp, 0x34 */
	m->eax = (DWORD)(m->edx + 0x1u);	/* 448b79: lea eax, [edx + 1] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 448b7c: dec eax */
	if (m->zf) goto L_448ba2;	/* 448b7d: je 0x448ba2 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 448b7f: dec eax */
	if (m->zf) goto L_448b97;	/* 448b80: je 0x448b97 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 448b82: dec eax */
	m->ebp = (DWORD)(m->esp + 0x30u);	/* 448b83: lea ebp, [esp + 0x30] */
	if (m->zf) goto L_448b90;	/* 448b87: je 0x448b90 */
	m->edi = 0x4b2b2cu;	/* 448b89: mov edi, 0x4b2b2c */
	goto L_448bab;	/* 448b8e: jmp 0x448bab */
L_448b90:
	m->edi = 0x4b2b28u;	/* 448b90: mov edi, 0x4b2b28 */
	goto L_448bab;	/* 448b95: jmp 0x448bab */
L_448b97:
	m->ebp = (DWORD)(m->esp + 0x30u);	/* 448b97: lea ebp, [esp + 0x30] */
	m->edi = 0x4b2b24u;	/* 448b9b: mov edi, 0x4b2b24 */
	goto L_448bab;	/* 448ba0: jmp 0x448bab */
L_448ba2:
	m->ebp = (DWORD)(m->esp + 0x30u);	/* 448ba2: lea ebp, [esp + 0x30] */
	m->edi = 0x4b2b20u;	/* 448ba6: mov edi, 0x4b2b20 */
L_448bab:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448bab: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 448bae: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448bb0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448bb2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448bb4: sub edi, ecx */
	m->esi = m->edi;	/* 448bb6: mov esi, edi */
	m->edi = m->ebp;	/* 448bb8: mov edi, ebp */
	m->ebp = m->ecx;	/* 448bba: mov ebp, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448bbc: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448bbf: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 448bc1: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 448bc3: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448bc4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448bc7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 448bc9: mov ecx, ebp */
	m->ebp = (DWORD)(m->esp + 0x30u);	/* 448bcb: lea ebp, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448bcf: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448bd2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448bd4: or ecx, 0xffffffff */
	m->edi = 0x75f1a4u;	/* 448bd7: mov edi, 0x75f1a4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448bdc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448bde: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448be0: sub edi, ecx */
	m->esi = m->edi;	/* 448be2: mov esi, edi */
	m->edi = m->ebp;	/* 448be4: mov edi, ebp */
	m->ebp = m->ecx;	/* 448be6: mov ebp, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448be8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448beb: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 448bed: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 448bef: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448bf0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448bf3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 448bf5: mov ecx, ebp */
	m->ebp = (DWORD)(m->esp + 0x30u);	/* 448bf7: lea ebp, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448bfb: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448bfe: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b18u;	/* 448c00: mov edi, 0x4b2b18 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c05: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448c08: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448c0a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448c0c: sub edi, ecx */
	m->esi = m->edi;	/* 448c0e: mov esi, edi */
	m->edi = m->ebp;	/* 448c10: mov edi, ebp */
	m->ebp = m->ecx;	/* 448c12: mov ebp, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c14: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448c17: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 448c19: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 448c1b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448c1c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448c1f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 448c21: mov ecx, ebp */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c23: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448c26: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 448c28: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c2a: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 448c2d: shl edi, 5 */
	{ DWORD a_ = m->edi, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448c30: add edi, 0x907b30 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 448c36: lea edx, [esp + 0x30] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448c3a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448c3c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448c3e: sub edi, ecx */
	m->esi = m->edi;	/* 448c40: mov esi, edi */
	m->ebp = m->ecx;	/* 448c42: mov ebp, ecx */
	m->edi = m->edx;	/* 448c44: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c46: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448c49: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 448c4b: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 448c4d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448c4e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448c51: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 448c53: mov ecx, ebp */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 448c55: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c59: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448c5c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b14u;	/* 448c5e: mov edi, 0x4b2b14 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c63: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448c66: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448c68: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448c6a: sub edi, ecx */
	m->esi = m->edi;	/* 448c6c: mov esi, edi */
	m->ebp = m->ecx;	/* 448c6e: mov ebp, ecx */
	m->edi = m->edx;	/* 448c70: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c72: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448c75: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 448c77: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 448c79: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448c7a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448c7d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->edx = M32((DWORD)(0x9f630cu));	/* 448c7f: mov edx, dword ptr [0x9f630c] */
	m->ecx = m->ebp;	/* 448c85: mov ecx, ebp */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448c87: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 448c8a: lea eax, [esp + 0x30] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448c8e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f6310u));	/* 448c90: mov ecx, dword ptr [0x9f6310] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448c96: push eax */
	m->eax = M32((DWORD)(0x9f6308u));	/* 448c97: mov eax, dword ptr [0x9f6308] */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 448c9c: add edx, 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448c9f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448ca0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448ca1: push eax */
	m->esp -= 4; M32(m->esp) = 0x448ca7u; native_call(m, 0x4029d0u);	/* 448ca2: call 0x4029d0 */
	m->eax = M32((DWORD)(0x9f63b0u));	/* 448ca7: mov eax, dword ptr [0x9f63b0] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448cac: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 448caf: test eax, eax */
	if (m->zf) goto L_448ddf;	/* 448cb1: je 0x448ddf */
	m->ecx = 0x20u;	/* 448cb7: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 448cbc: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x130u);	/* 448cbe: lea edi, [esp + 0x130] */
	m->edx = (DWORD)(m->esp + 0x130u);	/* 448cc5: lea edx, [esp + 0x130] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 448ccc: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448cce: or ecx, 0xffffffff */
	m->edi = 0x680bc4u;	/* 448cd1: mov edi, 0x680bc4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448cd6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448cd8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448cda: sub edi, ecx */
	m->ebp = (DWORD)(m->esp + 0x130u);	/* 448cdc: lea ebp, [esp + 0x130] */
	m->eax = m->ecx;	/* 448ce3: mov eax, ecx */
	m->esi = m->edi;	/* 448ce5: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448ce7: shr ecx, 2 */
	m->edi = m->edx;	/* 448cea: mov edi, edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448cec: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 448cee: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 448cf0: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448cf2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448cf5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f63b4u));	/* 448cf7: mov ecx, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448cfd: shl ecx, 5 */
	m->edx = (DWORD)(m->ecx + 0x907b30u);	/* 448d00: lea edx, [ecx + 0x907b30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d06: or ecx, 0xffffffff */
	m->edi = m->edx;	/* 448d09: mov edi, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448d0b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448d0d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448d0f: sub edi, ecx */
	m->esi = m->edi;	/* 448d11: mov esi, edi */
	m->edi = m->ebp;	/* 448d13: mov edi, ebp */
	m->ebp = m->ecx;	/* 448d15: mov ebp, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d17: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448d1a: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 448d1c: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 448d1e: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448d1f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448d22: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 448d24: mov ecx, ebp */
	m->ebp = (DWORD)(m->esp + 0x130u);	/* 448d26: lea ebp, [esp + 0x130] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d2d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448d30: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4ad564u;	/* 448d32: mov edi, 0x4ad564 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d37: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448d3a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448d3c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448d3e: sub edi, ecx */
	m->esi = m->edi;	/* 448d40: mov esi, edi */
	m->edi = m->ebp;	/* 448d42: mov edi, ebp */
	m->ebp = m->ecx;	/* 448d44: mov ebp, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d46: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448d49: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 448d4b: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 448d4d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448d4e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448d51: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 448d53: mov ecx, ebp */
	m->ebp = (DWORD)(m->esp + 0x130u);	/* 448d55: lea ebp, [esp + 0x130] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d5c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448d5f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 448d61: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d63: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448d66: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448d68: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448d6a: sub edi, ecx */
	m->esi = m->edi;	/* 448d6c: mov esi, edi */
	m->edx = m->ecx;	/* 448d6e: mov edx, ecx */
	m->edi = m->ebp;	/* 448d70: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d72: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448d75: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 448d77: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 448d79: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448d7a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448d7d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 448d7f: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0xf0u);	/* 448d81: lea edx, [esp + 0xf0] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d88: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448d8b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x130u);	/* 448d8d: lea edi, [esp + 0x130] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448d94: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 448d97: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 448d99: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 448d9b: sub edi, ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448d9d: push 0 */
	m->eax = m->ecx;	/* 448d9f: mov eax, ecx */
	m->esi = m->edi;	/* 448da1: mov esi, edi */
	m->edi = m->edx;	/* 448da3: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448da5: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 448da7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 448daa: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 448dac: mov ecx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448dae: push 0 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448db0: and ecx, 3 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448db3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448db5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448db7: push 0 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 448db9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 448dbb: mov ecx, dword ptr [0xa0e010] */
	m->edx = (DWORD)(m->esp + 0x108u);	/* 448dc1: lea edx, [esp + 0x108] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448dc8: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448dca: push edx */
	m->esp -= 4; M32(m->esp) = 0x448dd0u; native_call(m, 0x456be0u);	/* 448dcb: call 0x456be0 */
	M32((DWORD)(0x9da324u)) = m->eax;	/* 448dd0: mov dword ptr [0x9da324], eax */
	M32((DWORD)(0x9f63b0u)) = 0x0u;	/* 448dd5: mov dword ptr [0x9f63b0], 0 */
L_448ddf:
	m->ebp = M32((DWORD)(0x4a9224u));	/* 448ddf: mov ebp, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 448de5: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x448decu; native_call(m, m->ebp);	/* 448dea: call ebp */
	m->eax = M32((DWORD)(0x9da324u));	/* 448dec: mov eax, dword ptr [0x9da324] */
	m->ecx = m->eax;	/* 448df1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448df3: and ecx, 0x800001ff */
	if (!m->sf) goto L_448e03;	/* 448df9: jns 0x448e03 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 448dfb: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448dfc: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 448e02: inc ecx */
L_448e03:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 448e03: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 448e04: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448e0a: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 448e0b: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 448e0d: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 448e13: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 448e16: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x448e1fu; native_call(m, 0x4566c0u);	/* 448e1a: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e1f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e24: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e29: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e2e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448e35u; native_call(m, m->ebx);	/* 448e33: call ebx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e35: push 7 */
	m->esp -= 4; M32(m->esp) = 0x448e3du; native_call(m, M32(0x4a921cu));	/* 448e37: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a9208u));	/* 448e3d: mov esi, dword ptr [0x4a9208] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e43: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e45: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e47: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e49: push 0 */
	m->esp -= 4; M32(m->esp) = 0x448e4du; native_call(m, m->esi);	/* 448e4b: call esi */
	m->eax = M32((DWORD)(0x9f630cu));	/* 448e4d: mov eax, dword ptr [0x9f630c] */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 448e52: mov ecx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 448e58: add eax, 0x20 */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 448e5b: add ecx, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448e61: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448e62: push ecx */
	m->esp -= 4; M32(m->esp) = 0x448e68u; native_call(m, 0x41ef60u);	/* 448e63: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448e68: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e6b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e6d: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e6f: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e74: push 0 */
	m->esp -= 4; M32(m->esp) = 0x448e78u; native_call(m, m->esi);	/* 448e76: call esi */
	m->edx = M32((DWORD)(0x9f630cu));	/* 448e78: mov edx, dword ptr [0x9f630c] */
	m->eax = M32((DWORD)(0x9f6308u));	/* 448e7e: mov eax, dword ptr [0x9f6308] */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 448e83: add edx, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x158u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 448e86: add eax, 0x158 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448e8b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448e8c: push eax */
	m->esp -= 4; M32(m->esp) = 0x448e92u; native_call(m, 0x41ef60u);	/* 448e8d: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448e92: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e95: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e9a: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448e9c: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448ea1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x448ea5u; native_call(m, m->esi);	/* 448ea3: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 448ea5: mov ecx, dword ptr [0x9f630c] */
	m->edx = M32((DWORD)(0x9f6308u));	/* 448eab: mov edx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->ecx, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 448eb1: add ecx, 0xa0 */
	{ DWORD a_ = m->edx, b_ = 0x158u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 448eb7: add edx, 0x158 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448ebd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448ebe: push edx */
	m->esp -= 4; M32(m->esp) = 0x448ec4u; native_call(m, 0x41ef60u);	/* 448ebf: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448ec4: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448ec7: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448ecc: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448ece: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448ed0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x448ed4u; native_call(m, m->esi);	/* 448ed2: call esi */
	m->eax = M32((DWORD)(0x9f630cu));	/* 448ed4: mov eax, dword ptr [0x9f630c] */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 448ed9: mov ecx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->eax, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 448edf: add eax, 0xa0 */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 448ee4: add ecx, 0xd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448eea: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448eeb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x448ef1u; native_call(m, 0x41ef60u);	/* 448eec: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448ef1: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x448efau; native_call(m, M32(0x4a9220u));	/* 448ef4: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 448efa: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x448f05u; native_call(m, M32(0x4a922cu));	/* 448eff: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f05: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f0a: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f0c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f11: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f16: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x448f20u; native_call(m, 0x41f0e0u);	/* 448f1b: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f630cu));	/* 448f20: mov eax, dword ptr [0x9f630c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f25: push 0 */
	m->edx = (DWORD)(m->eax + 0xa0u);	/* 448f27: lea edx, [eax + 0xa0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448f2d: push edx */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 448f2e: mov ecx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 448f34: add eax, 0x20 */
	m->edx = (DWORD)(m->ecx + 0x158u);	/* 448f37: lea edx, [ecx + 0x158] */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 448f3d: add ecx, 0xd8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448f43: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448f44: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448f45: push ecx */
	m->esp -= 4; M32(m->esp) = 0x448f4bu; native_call(m, 0x427970u);	/* 448f46: call 0x427970 */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 448f4b: mov eax, dword ptr [0x9db0a4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448f50: add esp, 0x28 */
	m->ecx = m->eax;	/* 448f53: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448f55: and ecx, 0x800001ff */
	if (!m->sf) goto L_448f65;	/* 448f5b: jns 0x448f65 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 448f5d: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448f5e: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 448f64: inc ecx */
L_448f65:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 448f65: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 448f66: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448f6c: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 448f6d: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 448f6f: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 448f75: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 448f78: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x448f81u; native_call(m, 0x4566c0u);	/* 448f7c: call 0x4566c0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f81: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x448f88u; native_call(m, m->ebp);	/* 448f86: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f88: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f8d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f92: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448f97: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448f9eu; native_call(m, m->ebx);	/* 448f9c: call ebx */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 448f9e: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 448fa3: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_448fb2;	/* 448fa5: jle 0x448fb2 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448fa7: cmp dword ptr [esp + 0x20], 2 */
	if (!m->zf) goto L_448fb2;	/* 448fac: jne 0x448fb2 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 448fae: push 1 */
	goto L_448fb4;	/* 448fb0: jmp 0x448fb4 */
L_448fb2:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448fb2: push 0 */
L_448fb4:
	m->eax = M32((DWORD)(0x9f630cu));	/* 448fb4: mov eax, dword ptr [0x9f630c] */
	m->ecx = (DWORD)(m->eax + 0x74u);	/* 448fb9: lea ecx, [eax + 0x74] */
	{ DWORD a_ = m->eax, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 448fbc: add eax, 0x4c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448fbf: push ecx */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 448fc0: mov ecx, dword ptr [0x9f6308] */
	m->edx = (DWORD)(m->ecx + 0xd0u);	/* 448fc6: lea edx, [ecx + 0xd0] */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 448fcc: add ecx, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448fd2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448fd3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448fd4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x448fdau; native_call(m, 0x4284d0u);	/* 448fd5: call 0x4284d0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 448fda: mov eax, dword ptr [0x9f63b4] */
	m->ecx = M32((DWORD)(0x9f181cu));	/* 448fdf: mov ecx, dword ptr [0x9f181c] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448fe5: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448fe8: cmp eax, ecx */
	if (m->sf == m->of) goto L_448ffc;	/* 448fea: jge 0x448ffc */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448fec: cmp dword ptr [esp + 0x20], 3 */
	if (!m->zf) goto L_448ffc;	/* 448ff1: jne 0x448ffc */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448ff3: cmp eax, 0xe */
	if (m->sf == m->of) goto L_448ffc;	/* 448ff6: jge 0x448ffc */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 448ff8: push 1 */
	goto L_448ffe;	/* 448ffa: jmp 0x448ffe */
L_448ffc:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448ffc: push 0 */
L_448ffe:
	m->eax = M32((DWORD)(0x9f630cu));	/* 448ffe: mov eax, dword ptr [0x9f630c] */
	m->ecx = (DWORD)(m->eax + 0x74u);	/* 449003: lea ecx, [eax + 0x74] */
	{ DWORD a_ = m->eax, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449006: add eax, 0x4c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449009: push ecx */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 44900a: mov ecx, dword ptr [0x9f6308] */
	m->edx = (DWORD)(m->ecx + 0x198u);	/* 449010: lea edx, [ecx + 0x198] */
	{ DWORD a_ = m->ecx, b_ = 0x160u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449016: add ecx, 0x160 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44901c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44901d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44901e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x449024u; native_call(m, 0x4285c0u);	/* 44901f: call 0x4285c0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449024: add esp, 0x14 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449027: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44902c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449031: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449036: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44903b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x449045u; native_call(m, 0x41f0e0u);	/* 449040: call 0x41f0e0 */
	m->ecx = 0x20u;	/* 449045: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44904a: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x44u);	/* 44904c: lea edi, [esp + 0x44] */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 449050: lea edx, [esp + 0x44] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 449054: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449056: or ecx, 0xffffffff */
	m->edi = 0x75f2a4u;	/* 449059: mov edi, 0x75f2a4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44905e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449060: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449062: sub edi, ecx */
	m->eax = m->ecx;	/* 449064: mov eax, ecx */
	m->esi = m->edi;	/* 449066: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449068: shr ecx, 2 */
	m->edi = m->edx;	/* 44906b: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 44906d: lea edx, [esp + 0x44] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449071: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 449073: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449075: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449077: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44907a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b10u;	/* 44907c: mov edi, 0x4b2b10 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449081: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449084: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449086: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449088: sub edi, ecx */
	m->esi = m->edi;	/* 44908a: mov esi, edi */
	m->edi = m->edx;	/* 44908c: mov edi, edx */
	m->edx = m->ecx;	/* 44908e: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449090: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449093: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 449095: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449097: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449098: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44909b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44909d: mov eax, dword ptr [0x9f63b4] */
	m->ecx = m->edx;	/* 4490a2: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4490a4: and ecx, 3 */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 4490a7: lea edx, [esp + 0x44] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4490ab: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4490ad: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4490b0: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4490b3: sub ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4490b5: xor eax, eax */
	m->edi = M32((DWORD)(m->ecx*4 + 0x9db9e4u));	/* 4490b7: mov edi, dword ptr [ecx*4 + 0x9db9e4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4490be: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4490c1: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x75c9a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4490c4: add edi, 0x75c9a4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4490ca: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4490cc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4490ce: sub edi, ecx */
	m->esi = m->edi;	/* 4490d0: mov esi, edi */
	m->edi = m->edx;	/* 4490d2: mov edi, edx */
	m->edx = m->ecx;	/* 4490d4: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4490d6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4490d9: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4490db: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4490dd: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4490de: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4490e1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4490e3: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x44u);	/* 4490e5: lea eax, [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4490e9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4490ec: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 4490ee: mov ecx, dword ptr [0x9f630c] */
	m->edx = M32((DWORD)(0x9f6308u));	/* 4490f4: mov edx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->ecx, b_ = 0xaau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4490fa: add ecx, 0xaa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449100: push eax */
	{ DWORD a_ = m->edx, b_ = 0xc4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449101: add edx, 0xc4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449107: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449108: push edx */
	m->esp -= 4; M32(m->esp) = 0x44910eu; native_call(m, 0x4028b0u);	/* 449109: call 0x4028b0 */
	m->ecx = 0x20u;	/* 44910e: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449113: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x50u);	/* 449115: lea edi, [esp + 0x50] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449119: add esp, 0x20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44911c: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x20u;	/* 44911e: mov ecx, 0x20 */
	m->edi = (DWORD)(m->esp + 0xb0u);	/* 449123: lea edi, [esp + 0xb0] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44912a: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x75f324u;	/* 44912c: mov edi, 0x75f324 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449131: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449134: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449136: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449138: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 44913a: lea edx, [esp + 0x30] */
	m->eax = m->ecx;	/* 44913e: mov eax, ecx */
	m->esi = m->edi;	/* 449140: mov esi, edi */
	m->edi = m->edx;	/* 449142: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 449144: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449148: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44914b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44914d: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44914f: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449151: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449154: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b10u;	/* 449156: mov edi, 0x4b2b10 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44915b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44915e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449160: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449162: sub edi, ecx */
	m->esi = m->edi;	/* 449164: mov esi, edi */
	m->edi = m->edx;	/* 449166: mov edi, edx */
	m->edx = m->ecx;	/* 449168: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44916a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44916d: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44916f: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449171: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449172: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449175: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 449177: mov eax, dword ptr [0x9f63b4] */
	m->ecx = m->edx;	/* 44917c: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44917e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449181: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 449183: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449186: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449189: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db9ecu));	/* 44918b: mov eax, dword ptr [ecx*4 + 0x9db9ec] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 449192: test eax, eax */
	if (!m->zf) goto L_4491a1;	/* 449194: jne 0x4491a1 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 449196: lea edx, [esp + 0x30] */
	m->edi = 0x75c0a4u;	/* 44919a: mov edi, 0x75c0a4 */
	goto L_4491ed;	/* 44919f: jmp 0x4491ed */
L_4491a1:
	m->ecx = (DWORD)(m->esp + 0xb0u);	/* 4491a1: lea ecx, [esp + 0xb0] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 4491a8: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4491aa: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4491ab: push eax */
	m->esp -= 4; M32(m->esp) = 0x4491b1u; native_call(m, 0x49fb53u);	/* 4491ac: call 0x49fb53 */
	m->edi = (DWORD)(m->esp + 0xbcu);	/* 4491b1: lea edi, [esp + 0xbc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4491b8: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4491bb: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4491bd: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4491c0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4491c2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4491c4: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 4491c6: lea edx, [esp + 0x30] */
	m->esi = m->edi;	/* 4491ca: mov esi, edi */
	m->edi = m->edx;	/* 4491cc: mov edi, edx */
	m->edx = m->ecx;	/* 4491ce: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4491d0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4491d3: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4491d5: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4491d7: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4491d8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4491db: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4491dd: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 4491df: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4491e3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4491e6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x75c124u;	/* 4491e8: mov edi, 0x75c124 */
L_4491ed:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4491ed: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4491f0: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4491f2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4491f4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4491f6: sub edi, ecx */
	m->esi = m->edi;	/* 4491f8: mov esi, edi */
	m->edi = m->edx;	/* 4491fa: mov edi, edx */
	m->edx = m->ecx;	/* 4491fc: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4491fe: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449201: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 449203: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449205: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449206: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449209: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 44920b: mov ecx, edx */
	m->edx = M32((DWORD)(0x9f6308u));	/* 44920d: mov edx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449213: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 449216: lea eax, [esp + 0x30] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44921a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44921c: mov ecx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449222: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449223: add ecx, 0xbc */
	{ DWORD a_ = m->edx, b_ = 0xc4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449229: add edx, 0xc4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44922f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449230: push edx */
	m->esp -= 4; M32(m->esp) = 0x449236u; native_call(m, 0x4028b0u);	/* 449231: call 0x4028b0 */
	m->ecx = 0x20u;	/* 449236: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44923b: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x3cu);	/* 44923d: lea edi, [esp + 0x3c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449241: add esp, 0xc */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 449244: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x20u;	/* 449246: mov ecx, 0x20 */
	m->edi = (DWORD)(m->esp + 0xb0u);	/* 44924b: lea edi, [esp + 0xb0] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 449252: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x75f3a4u;	/* 449254: mov edi, 0x75f3a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449259: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44925c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44925e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449260: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 449262: lea edx, [esp + 0x30] */
	m->eax = m->ecx;	/* 449266: mov eax, ecx */
	m->esi = m->edi;	/* 449268: mov esi, edi */
	m->edi = m->edx;	/* 44926a: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 44926c: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449270: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449273: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 449275: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449277: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449279: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44927c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2b10u;	/* 44927e: mov edi, 0x4b2b10 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449283: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449286: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 449288: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44928a: sub edi, ecx */
	m->esi = m->edi;	/* 44928c: mov esi, edi */
	m->edi = m->edx;	/* 44928e: mov edi, edx */
	m->edx = m->ecx;	/* 449290: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449292: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449295: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 449297: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 449299: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44929a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44929d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44929f: mov eax, dword ptr [0x9f63b4] */
	m->ecx = m->edx;	/* 4492a4: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4492a6: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4492a9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4492ab: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4492ae: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4492b1: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db9e8u));	/* 4492b3: mov eax, dword ptr [ecx*4 + 0x9db9e8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4492ba: test eax, eax */
	if (!m->zf) goto L_4492c9;	/* 4492bc: jne 0x4492c9 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 4492be: lea edx, [esp + 0x30] */
	m->edi = 0x75bfa4u;	/* 4492c2: mov edi, 0x75bfa4 */
	goto L_449315;	/* 4492c7: jmp 0x449315 */
L_4492c9:
	m->ecx = (DWORD)(m->esp + 0xb0u);	/* 4492c9: lea ecx, [esp + 0xb0] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 4492d0: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4492d2: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4492d3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4492d9u; native_call(m, 0x49fb53u);	/* 4492d4: call 0x49fb53 */
	m->edi = (DWORD)(m->esp + 0xbcu);	/* 4492d9: lea edi, [esp + 0xbc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4492e0: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4492e3: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4492e5: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4492e8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4492ea: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4492ec: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 4492ee: lea edx, [esp + 0x30] */
	m->esi = m->edi;	/* 4492f2: mov esi, edi */
	m->edi = m->edx;	/* 4492f4: mov edi, edx */
	m->edx = m->ecx;	/* 4492f6: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4492f8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4492fb: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4492fd: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4492ff: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449300: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449303: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 449305: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 449307: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44930b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44930e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x75c024u;	/* 449310: mov edi, 0x75c024 */
L_449315:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449315: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 449318: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44931a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44931c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44931e: sub edi, ecx */
	m->esi = m->edi;	/* 449320: mov esi, edi */
	m->edi = m->edx;	/* 449322: mov edi, edx */
	m->edx = m->ecx;	/* 449324: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 449326: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 449329: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44932b: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44932d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44932e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 449331: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 449333: mov ecx, edx */
	m->edx = M32((DWORD)(0x9f6308u));	/* 449335: mov edx, dword ptr [0x9f6308] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44933b: and ecx, 3 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 44933e: lea eax, [esp + 0x30] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 449342: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 449344: mov ecx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44934a: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44934b: add ecx, 0xce */
	{ DWORD a_ = m->edx, b_ = 0xc4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449351: add edx, 0xc4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449357: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449358: push edx */
	m->esp -= 4; M32(m->esp) = 0x44935eu; native_call(m, 0x4028b0u);	/* 449359: call 0x4028b0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44935e: mov eax, dword ptr [0x9f63b4] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 449363: mov esi, dword ptr [0x4a920c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449369: add esp, 0xc */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44936c: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44936f: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449372: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db9c0u));	/* 449374: mov eax, dword ptr [ecx*4 + 0x9db9c0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44937b: test eax, eax */
	if (m->zf) goto L_44960c;	/* 44937d: je 0x44960c */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449383: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449388: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44938d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449392: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 449397: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4493a1u; native_call(m, 0x41f0e0u);	/* 44939c: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f630cu));	/* 4493a1: mov eax, dword ptr [0x9f630c] */
	m->edx = M32((DWORD)(0x9f6310u));	/* 4493a6: mov edx, dword ptr [0x9f6310] */
	m->ecx = M32((DWORD)(0x9f6308u));	/* 4493ac: mov ecx, dword ptr [0x9f6308] */
	{ DWORD v_ = 0x75f524u; m->esp -= 4; M32(m->esp) = v_; }	/* 4493b2: push 0x75f524 */
	{ DWORD a_ = m->eax, b_ = 0xf2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4493b7: add eax, 0xf2 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4493bc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4493bd: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4493be: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4493c4u; native_call(m, 0x4029d0u);	/* 4493bf: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4493c4: add esp, 0x24 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4493c7: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4493ceu; native_call(m, m->ebp);	/* 4493cc: call ebp */
	m->eax = M32((DWORD)(0x4dfa00u));	/* 4493ce: mov eax, dword ptr [0x4dfa00] */
	m->edx = m->eax;	/* 4493d3: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4493d5: and edx, 0x800001ff */
	if (!m->sf) goto L_4493e5;	/* 4493db: jns 0x4493e5 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4493dd: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4493de: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4493e4: inc edx */
L_4493e5:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4493e5: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4493e6: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4493ec: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4493ed: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4493f3: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4493f5: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4493f8: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x449401u; native_call(m, 0x4566c0u);	/* 4493fc: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449401: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449406: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44940b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449410: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x449417u; native_call(m, m->ebx);	/* 449415: call ebx */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 449417: mov eax, dword ptr [0x9f63b4] */
	m->edi = 0x146u;	/* 44941c: mov edi, 0x146 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 449421: xor ebx, ebx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 449423: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 449426: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449429: sub edx, eax */
	m->ecx = M32((DWORD)(m->edx*4 + 0x9db9c0u));	/* 44942b: mov ecx, dword ptr [edx*4 + 0x9db9c0] */
	m->edx = m->ecx;	/* 449432: mov edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 449434: shl edx, 5 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449437: sub edi, edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 449439: test ecx, ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->edi;	/* 44943b: mov dword ptr [esp + 0x28], edi */
	if (m->zf || m->sf != m->of) goto L_44958b;	/* 44943f: jle 0x44958b */
L_449445:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 449445: lea ecx, [eax + eax*2] */
	m->ebp = 0x3u;	/* 449448: mov ebp, 3 */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44944d: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449450: sub ecx, eax */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 449452: push 7 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449454: add ecx, ebx */
	m->ecx = M32((DWORD)(m->ecx*4 + 0x9db9c4u));	/* 449456: mov ecx, dword ptr [ecx*4 + 0x9db9c4] */
	m->eax = m->ecx;	/* 44945d: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44945f: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ebp; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 449460: idiv ebp */
	m->eax = 0x55555556u;	/* 449462: mov eax, 0x55555556 */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 449467: mov dword ptr [esp + 0x18], edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 44946b: imul ecx */
	m->eax = m->edx;	/* 44946d: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44946f: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449472: add edx, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 449474: mov dword ptr [esp + 0x20], edx */
	m->esp -= 4; M32(m->esp) = 0x44947eu; native_call(m, M32(0x4a921cu));	/* 449478: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 44947e: fild dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 449482: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0);	/* 449488: fst dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44948c: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 449492: fstp dword ptr [esp + 0x24] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 449496: fild dword ptr [esp + 0x14] */
	m->ebp = M32((DWORD)(m->esp + 0x24u));	/* 44949a: mov ebp, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44949e: push ebp */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44949f: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0);	/* 4494a5: fst dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4494a9: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4494af: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4494b3: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4494b7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4494bau; native_call(m, m->esi);	/* 4494b8: call esi */
	m->edx = M32((DWORD)(0x9f630cu));	/* 4494ba: mov edx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->edx, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4494c0: add edx, 0x104 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4494c6: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4494c7: push edi */
	m->esp -= 4; M32(m->esp) = 0x4494cdu; native_call(m, 0x41ef60u);	/* 4494c8: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4494cd: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 4494d1: fadd dword ptr [0x4a95e8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4494d7: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4494da: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4494e0: push ebp */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4494e1: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4494e5: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4494e9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4494ecu; native_call(m, m->esi);	/* 4494ea: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 4494ec: mov ecx, dword ptr [0x9f630c] */
	m->ebp = (DWORD)(m->edi + 0x30u);	/* 4494f2: lea ebp, [edi + 0x30] */
	{ DWORD a_ = m->ecx, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4494f5: add ecx, 0x104 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4494fb: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4494fc: push ebp */
	m->esp -= 4; M32(m->esp) = 0x449502u; native_call(m, 0x41ef60u);	/* 4494fd: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 449502: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 449506: fadd dword ptr [0x4a95e8] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 44950c: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449510: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 449513: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 449519: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 44951d: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449521: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449522: push eax */
	m->esp -= 4; M32(m->esp) = 0x449525u; native_call(m, m->esi);	/* 449523: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 449525: mov ecx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->ecx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44952b: add ecx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449531: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 449532: push ebp */
	m->esp -= 4; M32(m->esp) = 0x449538u; native_call(m, 0x41ef60u);	/* 449533: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 449538: mov edx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 44953c: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449540: add esp, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449543: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449544: push eax */
	m->esp -= 4; M32(m->esp) = 0x449547u; native_call(m, m->esi);	/* 449545: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 449547: mov ecx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->ecx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44954d: add ecx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449553: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 449554: push edi */
	m->esp -= 4; M32(m->esp) = 0x44955au; native_call(m, 0x41ef60u);	/* 449555: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44955a: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x449563u; native_call(m, M32(0x4a9220u));	/* 44955d: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 449563: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 449568: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 449569: add edi, 0x40 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44956c: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44956f: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449572: sub edx, eax */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->edx*4 + 0x9db9c0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 449574: cmp ebx, dword ptr [edx*4 + 0x9db9c0] */
	if (m->sf != m->of) goto L_449445;	/* 44957b: jl 0x449445 */
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 449581: mov edi, dword ptr [esp + 0x28] */
	m->ebp = M32((DWORD)(0x4a9224u));	/* 449585: mov ebp, dword ptr [0x4a9224] */
L_44958b:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44958b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x449596u; native_call(m, M32(0x4a922cu));	/* 449590: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449596: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44959b: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4495a0: push 0x3dcccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4495a5: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4495aa: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4495b4u; native_call(m, 0x41f0e0u);	/* 4495af: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 4495b4: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4495b9: add esp, 0x14 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4495bc: xor ebx, ebx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4495be: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4495c1: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4495c4: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9db9c0u));	/* 4495c6: mov eax, dword ptr [ecx*4 + 0x9db9c0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4495cd: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_44960c;	/* 4495cf: jle 0x44960c */
L_4495d1:
	m->eax = M32((DWORD)(0x9f630cu));	/* 4495d1: mov eax, dword ptr [0x9f630c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4495d6: push 0 */
	m->ecx = (DWORD)(m->edi + 0x30u);	/* 4495d8: lea ecx, [edi + 0x30] */
	m->edx = (DWORD)(m->eax + 0x134u);	/* 4495db: lea edx, [eax + 0x134] */
	{ DWORD a_ = m->eax, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4495e1: add eax, 0x104 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4495e6: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4495e7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4495e8: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4495e9: push edi */
	m->esp -= 4; M32(m->esp) = 0x4495efu; native_call(m, 0x427970u);	/* 4495ea: call 0x427970 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 4495ef: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4495f4: add esp, 0x14 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4495f7: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4495f8: add edi, 0x40 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4495fb: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4495fe: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449601: sub edx, eax */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->edx*4 + 0x9db9c0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 449603: cmp ebx, dword ptr [edx*4 + 0x9db9c0] */
	if (m->sf != m->of) goto L_4495d1;	/* 44960a: jl 0x4495d1 */
L_44960c:
	m->ecx = M32((DWORD)(0x9f630cu));	/* 44960c: mov ecx, dword ptr [0x9f630c] */
	m->eax = M32((DWORD)(0x9f6310u));	/* 449612: mov eax, dword ptr [0x9f6310] */
	m->edx = M32((DWORD)(0x9f6308u));	/* 449617: mov edx, dword ptr [0x9f6308] */
	{ DWORD v_ = 0x75f5a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44961d: push 0x75f5a4 */
	{ DWORD a_ = m->ecx, b_ = 0x142u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449622: add ecx, 0x142 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449628: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449629: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44962a: push edx */
	m->esp -= 4; M32(m->esp) = 0x449630u; native_call(m, 0x4029d0u);	/* 44962b: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449630: add esp, 0x10 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 449633: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44963au; native_call(m, m->ebp);	/* 449638: call ebp */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 44963a: mov eax, dword ptr [0x9f63b4] */
	m->edi = 0x146u;	/* 44963f: mov edi, 0x146 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 449644: xor ebp, ebp */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 449646: lea ecx, [eax + eax*2] */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebp;	/* 449649: mov dword ptr [esp + 0x2c], ebp */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44964d: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449650: sub ecx, eax */
	m->ecx = M32((DWORD)(m->ecx*4 + 0x9db99cu));	/* 449652: mov ecx, dword ptr [ecx*4 + 0x9db99c] */
	m->edx = m->ecx;	/* 449659: mov edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44965b: shl edx, 5 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44965e: sub edi, edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 449660: test ecx, ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->edi;	/* 449662: mov dword ptr [esp + 0x28], edi */
	if (m->zf || m->sf != m->of) goto L_44982b;	/* 449666: jle 0x44982b */
L_44966c:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44966c: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44966f: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449672: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449674: add ecx, ebp */
	m->ebx = M32((DWORD)(m->ecx*4 + 0x9db9a0u));	/* 449676: mov ebx, dword ptr [ecx*4 + 0x9db9a0] */
	m->ecx = 0x3u;	/* 44967d: mov ecx, 3 */
	m->eax = m->ebx;	/* 449682: mov eax, ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 449684: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 449685: idiv ecx */
	m->eax = 0x55555556u;	/* 449687: mov eax, 0x55555556 */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 44968c: mov dword ptr [esp + 0x14], edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 449690: imul ebx */
	m->eax = m->edx;	/* 449692: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 449694: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449697: add edx, eax */
	m->eax = M32((DWORD)(0x4dfa00u));	/* 449699: mov eax, dword ptr [0x4dfa00] */
	m->ecx = m->eax;	/* 44969e: mov ecx, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 4496a0: mov dword ptr [esp + 0x1c], edx */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4496a4: and ecx, 0x800001ff */
	if (!m->sf) goto L_4496b4;	/* 4496aa: jns 0x4496b4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4496ac: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4496ad: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4496b3: inc ecx */
L_4496b4:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4496b4: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4496b5: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4496bb: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4496bc: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4496be: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4496c4: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4496c7: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4496d0u; native_call(m, 0x4566c0u);	/* 4496cb: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4496d0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4496d5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4496da: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4496df: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4496eau; native_call(m, M32(0x4a9228u));	/* 4496e4: call dword ptr [0x4a9228] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4496ea: test ebx, ebx */
	if (m->sf != m->of) goto L_4497e8;	/* 4496ec: jl 0x4497e8 */
	{ DWORD a_ = m->ebx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4496f2: cmp ebx, 8 */
	if (!m->zf && m->sf == m->of) goto L_4497e8;	/* 4496f5: jg 0x4497e8 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4496fb: push 7 */
	m->esp -= 4; M32(m->esp) = 0x449703u; native_call(m, M32(0x4a921cu));	/* 4496fd: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 449703: fild dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 449707: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0);	/* 44970d: fst dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 449711: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 449717: fstp dword ptr [esp + 0x24] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 44971b: fild dword ptr [esp + 0x14] */
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 44971f: mov ebx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 449723: push ebx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 449724: fmul dword ptr [0x4a95ec] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0);	/* 44972a: fst dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44972e: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 449734: fstp dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 449738: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44973c: push ebp */
	m->esp -= 4; M32(m->esp) = 0x44973fu; native_call(m, m->esi);	/* 44973d: call esi */
	m->eax = M32((DWORD)(0x9f630cu));	/* 44973f: mov eax, dword ptr [0x9f630c] */
	{ DWORD a_ = m->eax, b_ = 0x154u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449744: add eax, 0x154 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449749: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44974a: push edi */
	m->esp -= 4; M32(m->esp) = 0x449750u; native_call(m, 0x41ef60u);	/* 44974b: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 449750: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 449754: fadd dword ptr [0x4a95e8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44975a: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44975d: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 449763: push ebx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 449764: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 449768: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44976c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44976fu; native_call(m, m->esi);	/* 44976d: call esi */
	m->edx = M32((DWORD)(0x9f630cu));	/* 44976f: mov edx, dword ptr [0x9f630c] */
	m->ebx = (DWORD)(m->edi + 0x30u);	/* 449775: lea ebx, [edi + 0x30] */
	{ DWORD a_ = m->edx, b_ = 0x154u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449778: add edx, 0x154 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44977e: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44977f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x449785u; native_call(m, 0x41ef60u);	/* 449780: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 449785: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 449789: fadd dword ptr [0x4a95e8] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 44978f: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449793: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 449796: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 44979c: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4497a0: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4497a4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4497a5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4497a8u; native_call(m, m->esi);	/* 4497a6: call esi */
	m->edx = M32((DWORD)(0x9f630cu));	/* 4497a8: mov edx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->edx, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4497ae: add edx, 0x184 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4497b4: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4497b5: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4497bbu; native_call(m, 0x41ef60u);	/* 4497b6: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4497bb: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4497bf: add esp, 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4497c2: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4497c3: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4497c6u; native_call(m, m->esi);	/* 4497c4: call esi */
	m->ecx = M32((DWORD)(0x9f630cu));	/* 4497c6: mov ecx, dword ptr [0x9f630c] */
	{ DWORD a_ = m->ecx, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4497cc: add ecx, 0x184 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4497d2: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4497d3: push edi */
	m->esp -= 4; M32(m->esp) = 0x4497d9u; native_call(m, 0x41ef60u);	/* 4497d4: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4497d9: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4497e2u; native_call(m, M32(0x4a9220u));	/* 4497dc: call dword ptr [0x4a9220] */
	m->ebp = M32((DWORD)(m->esp + 0x2cu));	/* 4497e2: mov ebp, dword ptr [esp + 0x2c] */
	goto L_449805;	/* 4497e6: jmp 0x449805 */
L_4497e8:
	m->eax = M32((DWORD)(0x9f630cu));	/* 4497e8: mov eax, dword ptr [0x9f630c] */
	m->edx = (DWORD)(m->edi + 0x30u);	/* 4497ed: lea edx, [edi + 0x30] */
	{ DWORD v_ = 0x4b2b0cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4497f0: push 0x4b2b0c */
	{ DWORD a_ = m->eax, b_ = 0x164u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4497f5: add eax, 0x164 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4497fa: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4497fb: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4497fc: push edi */
	m->esp -= 4; M32(m->esp) = 0x449802u; native_call(m, 0x4029d0u);	/* 4497fd: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449802: add esp, 0x10 */
L_449805:
	m->eax = M32((DWORD)(0x9f63b4u));	/* 449805: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 44980a: inc ebp */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44980b: add edi, 0x40 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebp;	/* 44980e: mov dword ptr [esp + 0x2c], ebp */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 449812: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 449815: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449818: sub ecx, eax */
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ecx*4 + 0x9db99cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44981a: cmp ebp, dword ptr [ecx*4 + 0x9db99c] */
	if (m->sf != m->of) goto L_44966c;	/* 449821: jl 0x44966c */
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 449827: mov edi, dword ptr [esp + 0x28] */
L_44982b:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44982b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x449836u; native_call(m, M32(0x4a922cu));	/* 449830: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449836: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44983b: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 449840: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 449845: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44984a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x449854u; native_call(m, 0x41f0e0u);	/* 44984f: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 449854: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449859: add esp, 0x14 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 44985c: xor ebx, ebx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44985e: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 449861: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 449864: sub edx, eax */
	m->eax = M32((DWORD)(m->edx*4 + 0x9db99cu));	/* 449866: mov eax, dword ptr [edx*4 + 0x9db99c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44986d: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4498ae;	/* 44986f: jle 0x4498ae */
	m->esi = m->edi;	/* 449871: mov esi, edi */
L_449873:
	m->eax = M32((DWORD)(0x9f630cu));	/* 449873: mov eax, dword ptr [0x9f630c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 449878: push 0 */
	m->edx = (DWORD)(m->esi + 0x30u);	/* 44987a: lea edx, [esi + 0x30] */
	m->ecx = (DWORD)(m->eax + 0x184u);	/* 44987d: lea ecx, [eax + 0x184] */
	{ DWORD a_ = m->eax, b_ = 0x154u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 449883: add eax, 0x154 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449888: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449889: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44988a: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44988b: push esi */
	m->esp -= 4; M32(m->esp) = 0x449891u; native_call(m, 0x427970u);	/* 44988c: call 0x427970 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 449891: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449896: add esp, 0x14 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 449899: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44989a: add esi, 0x40 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44989d: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4498a0: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4498a3: sub ecx, eax */
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->ecx*4 + 0x9db99cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4498a5: cmp ebx, dword ptr [ecx*4 + 0x9db99c] */
	if (m->sf != m->of) goto L_449873;	/* 4498ac: jl 0x449873 */
L_4498ae:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4498ae: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4498b0: xor esi, esi */
	m->edi = 0x75f6a4u;	/* 4498b2: mov edi, 0x75f6a4 */
L_4498b7:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4498b7: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4498c2u; native_call(m, M32(0x4a9224u));	/* 4498bc: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 4498c2: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 4498c7: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4498c9: and edx, 0x800001ff */
	if (!m->sf) goto L_4498d9;	/* 4498cf: jns 0x4498d9 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4498d1: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4498d2: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4498d8: inc edx */
L_4498d9:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4498d9: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4498da: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4498e0: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4498e1: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4498e7: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4498e9: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4498ec: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4498f5u; native_call(m, 0x4566c0u);	/* 4498f0: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4498f5: cmp dword ptr [esp + 0x20], ebx */
	if (!m->zf) goto L_44995b;	/* 4498f9: jne 0x44995b */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4498fb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449900: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449905: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44990a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x449915u; native_call(m, M32(0x4a9228u));	/* 44990f: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x9f6314u));	/* 449915: mov ecx, dword ptr [0x9f6314] */
	m->eax = M32((DWORD)(0x9f6308u));	/* 44991b: mov eax, dword ptr [0x9f6308] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 449920: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 449922: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449925: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449928: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x10eu);	/* 449929: lea edx, [esi + eax + 0x10e] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449930: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x96u);	/* 449931: lea eax, [esi + eax + 0x96] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449938: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449939: push eax */
	m->esp -= 4; M32(m->esp) = 0x44993fu; native_call(m, 0x4282f0u);	/* 44993a: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f6324u));	/* 44993f: mov ecx, dword ptr [0x9f6324] */
	m->edx = M32((DWORD)(0x9f6320u));	/* 449945: mov edx, dword ptr [0x9f6320] */
	m->eax = M32((DWORD)(0x9f631cu));	/* 44994b: mov eax, dword ptr [0x9f631c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449950: push ecx */
	m->ecx = M32((DWORD)(0x9f6318u));	/* 449951: mov ecx, dword ptr [0x9f6318] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449957: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449958: push eax */
	goto L_4499b9;	/* 449959: jmp 0x4499b9 */
L_44995b:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44995b: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449960: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449965: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44996a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x449975u; native_call(m, M32(0x4a9228u));	/* 44996f: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x9f6314u));	/* 449975: mov ecx, dword ptr [0x9f6314] */
	m->eax = M32((DWORD)(0x9f6308u));	/* 44997b: mov eax, dword ptr [0x9f6308] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 449980: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 449982: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 449985: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449988: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x10eu);	/* 449989: lea edx, [esi + eax + 0x10e] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449990: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x96u);	/* 449991: lea eax, [esi + eax + 0x96] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449998: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449999: push eax */
	m->esp -= 4; M32(m->esp) = 0x44999fu; native_call(m, 0x4282f0u);	/* 44999a: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f62f4u));	/* 44999f: mov ecx, dword ptr [0x9f62f4] */
	m->edx = M32((DWORD)(0x9f62f0u));	/* 4499a5: mov edx, dword ptr [0x9f62f0] */
	m->eax = M32((DWORD)(0x9f62ecu));	/* 4499ab: mov eax, dword ptr [0x9f62ec] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4499b0: push ecx */
	m->ecx = M32((DWORD)(0x9f62e8u));	/* 4499b1: mov ecx, dword ptr [0x9f62e8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4499b7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4499b8: push eax */
L_4499b9:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4499b9: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4499ba: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4499c4u; native_call(m, 0x41f0e0u);	/* 4499bf: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f6308u));	/* 4499c4: mov eax, dword ptr [0x9f6308] */
	m->ecx = M32((DWORD)(0x9f6314u));	/* 4499c9: mov ecx, dword ptr [0x9f6314] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4499cf: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4499d2: add ecx, -0x28 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x10eu);	/* 4499d5: lea edx, [esi + eax + 0x10e] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4499dc: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4499dd: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x96u);	/* 4499de: lea edx, [esi + eax + 0x96] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4499e5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4499e6: push edx */
	m->esp -= 4; M32(m->esp) = 0x4499ecu; native_call(m, 0x4029d0u);	/* 4499e7: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4499ec: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4499ef: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4499f5: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4499f6: add esi, 0x8c */
	{ DWORD a_ = m->edi, b_ = 0x75f7a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4499fc: cmp edi, 0x75f7a4 */
	if (m->sf != m->of) goto L_4498b7;	/* 449a02: jl 0x4498b7 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a08: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a0d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a12: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 449a17: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x449a22u; native_call(m, M32(0x4a9228u));	/* 449a1c: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9f6314u));	/* 449a22: mov eax, dword ptr [0x9f6314] */
	m->ecx = M32((DWORD)(0x9f6310u));	/* 449a27: mov ecx, dword ptr [0x9f6310] */
	m->edx = M32((DWORD)(0x9f630cu));	/* 449a2d: mov edx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449a33: push eax */
	m->eax = M32((DWORD)(0x9f6308u));	/* 449a34: mov eax, dword ptr [0x9f6308] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 449a39: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 449a3a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 449a3b: push eax */
	m->esp -= 4; M32(m->esp) = 0x449a41u; native_call(m, 0x428a00u);	/* 449a3c: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 449a41: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 449a44: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 449a45: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 449a46: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 449a47: pop ebx */
	m->esp = m->ebp;	/* 449a48: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 449a4a: pop ebp */
	m->esp += 4 + 0; return;	/* 449a4b: ret  */
}

/* missionsel_44aa20 (0x44aa20), lifted by tools/lift.py */
static void lift_44aa20(X86 *m)
{
	lift_448ac0(m); return;	/* 44aa20: jmp 0x448ac0 */
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
