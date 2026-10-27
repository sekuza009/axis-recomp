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

static void lift_455aa0(X86 *m);

/* tex_loadColorMask (0x455aa0), lifted by tools/lift.py */
static void lift_455aa0(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 455aa0: push -1 */
	{ DWORD v_ = 0x4a884eu; m->esp -= 4; M32(m->esp) = v_; }	/* 455aa2: push 0x4a884e */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 455aa7: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455aad: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 455aae: mov dword ptr fs:[0], esp */
	{ DWORD a_ = m->esp, b_ = 0x2e4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455ab5: sub esp, 0x2e4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455abb: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 455abc: push ebp */
	m->eax = 0x4a96f8u;	/* 455abd: mov eax, 0x4a96f8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 455ac2: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455ac4: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 455ac5: push edi */
	m->ebp = m->ecx;	/* 455ac6: mov ebp, ecx */
	M32((DWORD)(m->esp + 0x2acu)) = m->eax;	/* 455ac8: mov dword ptr [esp + 0x2ac], eax */
	M32((DWORD)(m->esp + 0x2b0u)) = m->ebx;	/* 455acf: mov dword ptr [esp + 0x2b0], ebx */
	M32((DWORD)(m->esp + 0x2fcu)) = m->ebx;	/* 455ad6: mov dword ptr [esp + 0x2fc], ebx */
	M32((DWORD)(m->esp + 0x164u)) = m->eax;	/* 455add: mov dword ptr [esp + 0x164], eax */
	M32((DWORD)(m->esp + 0x168u)) = m->ebx;	/* 455ae4: mov dword ptr [esp + 0x168], ebx */
	M32((DWORD)(m->esp + 0x11cu)) = m->eax;	/* 455aeb: mov dword ptr [esp + 0x11c], eax */
	M32((DWORD)(m->esp + 0x120u)) = m->ebx;	/* 455af2: mov dword ptr [esp + 0x120], ebx */
	m->eax = M32((DWORD)(m->esp + 0x304u));	/* 455af9: mov eax, dword ptr [esp + 0x304] */
	{ DWORD v_ = 0x4b12f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455b00: push 0x4b12f4 */
	M8((DWORD)(m->esp + 0x300u)) = (BYTE)(0x2u);	/* 455b05: mov byte ptr [esp + 0x300], 2 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 455b0d: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 455b10: lea edx, [eax + ecx*4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455b13: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 455b16: xor eax, eax */
	m->edi = (DWORD)(m->ebp + m->edx*8 + 0xc0128u);	/* 455b18: lea edi, [ebp + edx*8 + 0xc0128] */
	m->edx = (DWORD)(m->esp + 0x1b0u);	/* 455b1f: lea edx, [esp + 0x1b0] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 455b26: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 455b28: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 455b2a: sub edi, ecx */
	m->eax = m->ecx;	/* 455b2c: mov eax, ecx */
	m->esi = m->edi;	/* 455b2e: mov esi, edi */
	m->edi = m->edx;	/* 455b30: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 455b32: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 455b35: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 455b37: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455b39: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 455b3c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x1b0u);	/* 455b3e: lea ecx, [esp + 0x1b0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455b45: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455b4bu; native_call(m, 0x49ec3bu);	/* 455b46: call 0x49ec3b */
	m->eax = M32((DWORD)(m->ebp + 0xc0114u));	/* 455b4b: mov eax, dword ptr [ebp + 0xc0114] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455b51: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 455b54: sub eax, ebx */
	m->esi = 0x1u;	/* 455b56: mov esi, 1 */
	if (m->zf) goto L_456116;	/* 455b5b: je 0x456116 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 455b61: dec eax */
	if (m->zf) goto L_455e6f;	/* 455b62: je 0x455e6f */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 455b68: dec eax */
	if (!m->zf) goto L_45640a;	/* 455b69: jne 0x45640a */
	{ DWORD a_ = M32((DWORD)(0xa0e00cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455b6f: cmp dword ptr [0xa0e00c], ebx */
	if (!m->zf) goto L_455b82;	/* 455b75: jne 0x455b82 */
	m->esp -= 4; M32(m->esp) = 0x455b7cu; native_call(m, 0x46ea00u);	/* 455b77: call 0x46ea00 */
	M32((DWORD)(0xa0e00cu)) = m->esi;	/* 455b7c: mov dword ptr [0xa0e00c], esi */
L_455b82:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 455b82: mov al, byte ptr [ebp + 8] */
	m->esi = (DWORD)(m->ebp + 0x8u);	/* 455b85: lea esi, [ebp + 8] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 455b88: test al, al */
	if (m->zf) goto L_455ba9;	/* 455b8a: je 0x455ba9 */
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 455b8c: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 455b93: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455b97: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455b98: push esi */
	{ DWORD v_ = 0x4b4000u; m->esp -= 4; M32(m->esp) = v_; }	/* 455b99: push 0x4b4000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455b9e: push eax */
	m->esp -= 4; M32(m->esp) = 0x455ba4u; native_call(m, 0x49e9ddu);	/* 455b9f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455ba4: add esp, 0x10 */
	goto L_455bc3;	/* 455ba7: jmp 0x455bc3 */
L_455ba9:
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 455ba9: lea ecx, [esp + 0x1ac] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 455bb0: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455bb4: push ecx */
	{ DWORD v_ = 0x4b3ff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455bb5: push 0x4b3ff8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455bba: push edx */
	m->esp -= 4; M32(m->esp) = 0x455bc0u; native_call(m, 0x49e9ddu);	/* 455bbb: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455bc0: add esp, 0xc */
L_455bc3:
	m->eax = (DWORD)(m->esp + 0x10u);	/* 455bc3: lea eax, [esp + 0x10] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 455bc7: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455bcb: push eax */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 455bcc: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455bd0: push ecx */
	m->eax = (DWORD)(m->ebp + 0x114u);	/* 455bd1: lea eax, [ebp + 0x114] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455bd7: push edx */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 455bd8: lea ecx, [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455bdc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455bdd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455be3u; native_call(m, 0x46eb00u);	/* 455bde: call 0x46eb00 */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455be3: mov eax, dword ptr [ebp + 0xc0118] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 455be9: mov ecx, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 455bed: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455bf1: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455bf4: cmp eax, ecx */
	if (!m->zf) goto L_455c00;	/* 455bf6: jne 0x455c00 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xc011cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455bf8: cmp dword ptr [ebp + 0xc011c], edx */
	if (m->zf) goto L_455c1c;	/* 455bfe: je 0x455c1c */
L_455c00:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c00: push edx */
	m->edx = M32((DWORD)(m->ebp + 0xc011cu));	/* 455c01: mov edx, dword ptr [ebp + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c07: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c08: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455c09: push eax */
	{ DWORD v_ = 0x4b4104u; m->esp -= 4; M32(m->esp) = v_; }	/* 455c0a: push 0x4b4104 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455c0f: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x455c19u; native_call(m, 0x46c710u);	/* 455c14: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455c19: add esp, 0x18 */
L_455c1c:
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x0u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 455c1c: cmp byte ptr [esi], 0 */
	if (m->zf) goto L_455c3e;	/* 455c1f: je 0x455c3e */
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 455c21: lea eax, [esp + 0x1ac] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 455c28: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455c2c: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455c2d: push esi */
	{ DWORD v_ = 0x4b40f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455c2e: push 0x4b40f4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c33: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455c39u; native_call(m, 0x49e9ddu);	/* 455c34: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455c39: add esp, 0x10 */
	goto L_455c58;	/* 455c3c: jmp 0x455c58 */
L_455c3e:
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 455c3e: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 455c45: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c49: push edx */
	{ DWORD v_ = 0x4b40e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455c4a: push 0x4b40e4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455c4f: push eax */
	m->esp -= 4; M32(m->esp) = 0x455c55u; native_call(m, 0x49e9ddu);	/* 455c50: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455c55: add esp, 0xc */
L_455c58:
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 455c58: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 455c5c: push 0x4ad170 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c61: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455c67u; native_call(m, 0x49e9cau);	/* 455c62: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455c67: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455c6a: cmp eax, ebx */
	if (m->zf) goto L_455d35;	/* 455c6c: je 0x455d35 */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 455c72: lea edx, [esp + 0x10] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 455c76: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c7a: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c7b: push ecx */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 455c7c: lea edx, [esp + 0x20] */
	m->ecx = (DWORD)(m->ebp + 0x40114u);	/* 455c80: lea ecx, [ebp + 0x40114] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c86: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455c87: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455c88: push eax */
	m->esp -= 4; M32(m->esp) = 0x455c8eu; native_call(m, 0x46ed80u);	/* 455c89: call 0x46ed80 */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455c8e: mov eax, dword ptr [ebp + 0xc0118] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 455c94: mov ecx, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 455c98: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455c9c: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455c9f: cmp eax, ecx */
	if (!m->zf) goto L_455cab;	/* 455ca1: jne 0x455cab */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xc011cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455ca3: cmp dword ptr [ebp + 0xc011c], edx */
	if (m->zf) goto L_455cc7;	/* 455ca9: je 0x455cc7 */
L_455cab:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455cab: push edx */
	m->edx = M32((DWORD)(m->ebp + 0xc011cu));	/* 455cac: mov edx, dword ptr [ebp + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455cb2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455cb3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455cb4: push eax */
	{ DWORD v_ = 0x4b4104u; m->esp -= 4; M32(m->esp) = v_; }	/* 455cb5: push 0x4b4104 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455cba: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x455cc4u; native_call(m, 0x46c710u);	/* 455cbf: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455cc4: add esp, 0x18 */
L_455cc7:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455cc7: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 455ccd: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455ccf: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_455d71;	/* 455cd1: jle 0x455d71 */
L_455cd7:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455cd7: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 455cdd: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455cdf: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_455d28;	/* 455ce1: jle 0x455d28 */
L_455ce3:
	{ long long p_ = (long long)(int)m->eax * (int)m->edi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 455ce3: imul eax, edi */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 455ce6: xor edx, edx */
	m->ecx = (DWORD)(m->eax + m->esi*1 + 0x0u);	/* 455ce8: lea ecx, [eax + esi] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 455ceb: xor eax, eax */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40116u))) & 0xff) << 0);	/* 455ced: mov dl, byte ptr [ebp + ecx*4 + 0x40116] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40115u))) & 0xff) << 0);	/* 455cf4: mov al, byte ptr [ebp + ecx*4 + 0x40115] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 455cfb: add edx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 455cfd: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40114u))) & 0xff) << 0);	/* 455cff: mov al, byte ptr [ebp + ecx*4 + 0x40114] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 455d06: add edx, eax */
	m->eax = 0x55555556u;	/* 455d08: mov eax, 0x55555556 */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 455d0d: imul edx */
	m->eax = m->edx;	/* 455d0f: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 455d11: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 455d14: add edx, eax */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 455d16: inc esi */
	M8((DWORD)(m->ebp + m->ecx*4 + 0x117u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 455d17: mov byte ptr [ebp + ecx*4 + 0x117], dl */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455d1e: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455d24: cmp esi, eax */
	if (m->sf != m->of) goto L_455ce3;	/* 455d26: jl 0x455ce3 */
L_455d28:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455d28: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 455d2e: inc edi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455d2f: cmp edi, eax */
	if (m->sf != m->of) goto L_455cd7;	/* 455d31: jl 0x455cd7 */
	goto L_455d71;	/* 455d33: jmp 0x455d71 */
L_455d35:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455d35: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 455d3b: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455d3d: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_455d71;	/* 455d3f: jle 0x455d71 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0xffu) & 0xff) << 0);	/* 455d41: mov bl, 0xff */
L_455d43:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455d43: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455d49: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455d4b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_455d66;	/* 455d4d: jle 0x455d66 */
L_455d4f:
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 455d4f: imul eax, edx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 455d52: add eax, ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 455d54: inc ecx */
	M8((DWORD)(m->ebp + m->eax*4 + 0x117u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 455d55: mov byte ptr [ebp + eax*4 + 0x117], bl */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455d5c: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455d62: cmp ecx, eax */
	if (m->sf != m->of) goto L_455d4f;	/* 455d64: jl 0x455d4f */
L_455d66:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455d66: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 455d6c: inc edx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455d6d: cmp edx, eax */
	if (m->sf != m->of) goto L_455d43;	/* 455d6f: jl 0x455d43 */
L_455d71:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 455d71: mov cl, byte ptr [ebp + 8] */
	m->eax = (DWORD)(m->ebp + 0x8u);	/* 455d74: lea eax, [ebp + 8] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 455d77: test cl, cl */
	if (m->zf) goto L_455d98;	/* 455d79: je 0x455d98 */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 455d7b: lea ecx, [esp + 0x1ac] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 455d82: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455d86: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455d87: push eax */
	{ DWORD v_ = 0x4b40d4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455d88: push 0x4b40d4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455d8d: push edx */
	m->esp -= 4; M32(m->esp) = 0x455d93u; native_call(m, 0x49e9ddu);	/* 455d8e: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455d93: add esp, 0x10 */
	goto L_455db2;	/* 455d96: jmp 0x455db2 */
L_455d98:
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 455d98: lea eax, [esp + 0x1ac] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 455d9f: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455da3: push eax */
	{ DWORD v_ = 0x4b40c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455da4: push 0x4b40c4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455da9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455dafu; native_call(m, 0x49e9ddu);	/* 455daa: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455daf: add esp, 0xc */
L_455db2:
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 455db2: lea edx, [esp + 0x1c] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 455db6: push 0x4ad170 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455dbb: push edx */
	m->esp -= 4; M32(m->esp) = 0x455dc1u; native_call(m, 0x49e9cau);	/* 455dbc: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455dc1: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455dc4: test eax, eax */
	if (m->zf) goto L_455e26;	/* 455dc6: je 0x455e26 */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 455dc8: lea ecx, [esp + 0x10] */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 455dcc: lea edx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455dd0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455dd1: push edx */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 455dd2: lea ecx, [esp + 0x20] */
	m->edx = (DWORD)(m->ebp + 0x80114u);	/* 455dd6: lea edx, [ebp + 0x80114] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455ddc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455ddd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455dde: push eax */
	m->esp -= 4; M32(m->esp) = 0x455de4u; native_call(m, 0x46ed80u);	/* 455ddf: call 0x46ed80 */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455de4: mov eax, dword ptr [ebp + 0xc0118] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 455dea: mov ecx, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 455dee: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455df2: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455df5: cmp eax, ecx */
	if (!m->zf) goto L_455e05;	/* 455df7: jne 0x455e05 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xc011cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455df9: cmp dword ptr [ebp + 0xc011c], edx */
	if (m->zf) goto L_45640a;	/* 455dff: je 0x45640a */
L_455e05:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455e05: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455e06: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0xc011cu));	/* 455e07: mov ecx, dword ptr [ebp + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455e0d: push ecx */
L_455e0e:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455e0e: push eax */
	{ DWORD v_ = 0x4b4104u; m->esp -= 4; M32(m->esp) = v_; }	/* 455e0f: push 0x4b4104 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455e14: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x455e1eu; native_call(m, 0x46c710u);	/* 455e19: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455e1e: add esp, 0x18 */
	goto L_45640a;	/* 455e21: jmp 0x45640a */
L_455e26:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455e26: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 455e2c: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455e2e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45640a;	/* 455e30: jle 0x45640a */
L_455e36:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455e36: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 455e3c: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455e3e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_455e5f;	/* 455e40: jle 0x455e5f */
L_455e42:
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 455e42: imul eax, edx */
	m->esi = M32((DWORD)(0xa1f238u));	/* 455e45: mov esi, dword ptr [0xa1f238] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 455e4b: add eax, ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 455e4d: inc ecx */
	M32((DWORD)(m->ebp + m->eax*4 + 0x80114u)) = m->esi;	/* 455e4e: mov dword ptr [ebp + eax*4 + 0x80114], esi */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455e55: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455e5b: cmp ecx, eax */
	if (m->sf != m->of) goto L_455e42;	/* 455e5d: jl 0x455e42 */
L_455e5f:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455e5f: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 455e65: inc edx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455e66: cmp edx, eax */
	if (m->sf != m->of) goto L_455e36;	/* 455e68: jl 0x455e36 */
	goto L_45640a;	/* 455e6a: jmp 0x45640a */
L_455e6f:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 455e6f: mov al, byte ptr [ebp + 8] */
	m->esi = (DWORD)(m->ebp + 0x8u);	/* 455e72: lea esi, [ebp + 8] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 455e75: test al, al */
	if (m->zf) goto L_455e96;	/* 455e77: je 0x455e96 */
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 455e79: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 455e80: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455e84: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455e85: push esi */
	{ DWORD v_ = 0x4b3fecu; m->esp -= 4; M32(m->esp) = v_; }	/* 455e86: push 0x4b3fec */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455e8b: push eax */
	m->esp -= 4; M32(m->esp) = 0x455e91u; native_call(m, 0x49e9ddu);	/* 455e8c: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455e91: add esp, 0x10 */
	goto L_455eb0;	/* 455e94: jmp 0x455eb0 */
L_455e96:
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 455e96: lea ecx, [esp + 0x1ac] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 455e9d: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455ea1: push ecx */
	{ DWORD v_ = 0x4b3fe4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455ea2: push 0x4b3fe4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455ea7: push edx */
	m->esp -= 4; M32(m->esp) = 0x455eadu; native_call(m, 0x49e9ddu);	/* 455ea8: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455ead: add esp, 0xc */
L_455eb0:
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 455eb0: lea eax, [esp + 0x1c] */
	m->ecx = (DWORD)(m->esp + 0x2acu);	/* 455eb4: lea ecx, [esp + 0x2ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455ebb: push eax */
	m->esp -= 4; M32(m->esp) = 0x455ec1u; native_call(m, 0x46cd00u);	/* 455ebc: call 0x46cd00 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455ec1: test eax, eax */
	if (!m->zf) goto L_455edc;	/* 455ec3: jne 0x455edc */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 455ec5: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455ec9: push ecx */
	{ DWORD v_ = 0x4b40a8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455eca: push 0x4b40a8 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455ecf: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x455ed9u; native_call(m, 0x46c710u);	/* 455ed4: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455ed9: add esp, 0xc */
L_455edc:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455edc: mov eax, dword ptr [ebp + 0xc011c] */
	m->ecx = M32((DWORD)(m->ebp + 0xc0118u));	/* 455ee2: mov ecx, dword ptr [ebp + 0xc0118] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455ee8: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455ee9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455eea: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455eeb: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455eec: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455eed: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455eee: push ebx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455eef: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455ef1: push eax */
	m->edx = (DWORD)(m->ebp + 0x114u);	/* 455ef2: lea edx, [ebp + 0x114] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455ef8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455ef9: push edx */
	m->ecx = (DWORD)(m->esp + 0x2d8u);	/* 455efa: lea ecx, [esp + 0x2d8] */
	m->esp -= 4; M32(m->esp) = 0x455f06u; native_call(m, 0x46ce80u);	/* 455f01: call 0x46ce80 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x0u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 455f06: cmp byte ptr [esi], 0 */
	if (m->zf) goto L_455f28;	/* 455f09: je 0x455f28 */
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 455f0b: lea eax, [esp + 0x1ac] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 455f12: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455f16: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455f17: push esi */
	{ DWORD v_ = 0x4b4098u; m->esp -= 4; M32(m->esp) = v_; }	/* 455f18: push 0x4b4098 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f1d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455f23u; native_call(m, 0x49e9ddu);	/* 455f1e: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455f23: add esp, 0x10 */
	goto L_455f42;	/* 455f26: jmp 0x455f42 */
L_455f28:
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 455f28: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 455f2f: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f33: push edx */
	{ DWORD v_ = 0x4b4088u; m->esp -= 4; M32(m->esp) = v_; }	/* 455f34: push 0x4b4088 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455f39: push eax */
	m->esp -= 4; M32(m->esp) = 0x455f3fu; native_call(m, 0x49e9ddu);	/* 455f3a: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455f3f: add esp, 0xc */
L_455f42:
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 455f42: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f46: push ecx */
	m->ecx = (DWORD)(m->esp + 0x168u);	/* 455f47: lea ecx, [esp + 0x168] */
	m->esp -= 4; M32(m->esp) = 0x455f53u; native_call(m, 0x46cd00u);	/* 455f4e: call 0x46cd00 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455f53: test eax, eax */
	if (m->zf) goto L_455ffb;	/* 455f55: je 0x455ffb */
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455f5b: mov eax, dword ptr [ebp + 0xc011c] */
	m->ecx = M32((DWORD)(m->ebp + 0xc0118u));	/* 455f61: mov ecx, dword ptr [ebp + 0xc0118] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f67: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455f68: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f69: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f6a: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f6b: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f6c: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f6d: push ebx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 455f6e: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455f70: push eax */
	m->edx = (DWORD)(m->ebp + 0x40114u);	/* 455f71: lea edx, [ebp + 0x40114] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f77: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455f78: push edx */
	m->ecx = (DWORD)(m->esp + 0x190u);	/* 455f79: lea ecx, [esp + 0x190] */
	m->esp -= 4; M32(m->esp) = 0x455f85u; native_call(m, 0x46ce80u);	/* 455f80: call 0x46ce80 */
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455f85: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 455f8b: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455f8d: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_455fed;	/* 455f8f: jle 0x455fed */
L_455f91:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455f91: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 455f97: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455f99: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_455fe2;	/* 455f9b: jle 0x455fe2 */
L_455f9d:
	{ long long p_ = (long long)(int)m->eax * (int)m->edi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 455f9d: imul eax, edi */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 455fa0: xor edx, edx */
	m->ecx = (DWORD)(m->eax + m->esi*1 + 0x0u);	/* 455fa2: lea ecx, [eax + esi] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 455fa5: xor eax, eax */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40116u))) & 0xff) << 0);	/* 455fa7: mov dl, byte ptr [ebp + ecx*4 + 0x40116] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40115u))) & 0xff) << 0);	/* 455fae: mov al, byte ptr [ebp + ecx*4 + 0x40115] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 455fb5: add edx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 455fb7: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40114u))) & 0xff) << 0);	/* 455fb9: mov al, byte ptr [ebp + ecx*4 + 0x40114] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 455fc0: add edx, eax */
	m->eax = 0x55555556u;	/* 455fc2: mov eax, 0x55555556 */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 455fc7: imul edx */
	m->eax = m->edx;	/* 455fc9: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 455fcb: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 455fce: add edx, eax */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 455fd0: inc esi */
	M8((DWORD)(m->ebp + m->ecx*4 + 0x117u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 455fd1: mov byte ptr [ebp + ecx*4 + 0x117], dl */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 455fd8: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455fde: cmp esi, eax */
	if (m->sf != m->of) goto L_455f9d;	/* 455fe0: jl 0x455f9d */
L_455fe2:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455fe2: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 455fe8: inc edi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455fe9: cmp edi, eax */
	if (m->sf != m->of) goto L_455f91;	/* 455feb: jl 0x455f91 */
L_455fed:
	m->ecx = (DWORD)(m->esp + 0x164u);	/* 455fed: lea ecx, [esp + 0x164] */
	m->esp -= 4; M32(m->esp) = 0x455ff9u; native_call(m, 0x46ce50u);	/* 455ff4: call 0x46ce50 */
	goto L_456037;	/* 455ff9: jmp 0x456037 */
L_455ffb:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455ffb: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 456001: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456003: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_456037;	/* 456005: jle 0x456037 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0xffu) & 0xff) << 0);	/* 456007: mov bl, 0xff */
L_456009:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 456009: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45600f: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456011: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45602c;	/* 456013: jle 0x45602c */
L_456015:
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 456015: imul eax, edx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 456018: add eax, ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45601a: inc ecx */
	M8((DWORD)(m->ebp + m->eax*4 + 0x117u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 45601b: mov byte ptr [ebp + eax*4 + 0x117], bl */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 456022: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456028: cmp ecx, eax */
	if (m->sf != m->of) goto L_456015;	/* 45602a: jl 0x456015 */
L_45602c:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 45602c: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 456032: inc edx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456033: cmp edx, eax */
	if (m->sf != m->of) goto L_456009;	/* 456035: jl 0x456009 */
L_456037:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 456037: mov cl, byte ptr [ebp + 8] */
	m->eax = (DWORD)(m->ebp + 0x8u);	/* 45603a: lea eax, [ebp + 8] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45603d: test cl, cl */
	if (m->zf) goto L_45605e;	/* 45603f: je 0x45605e */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 456041: lea ecx, [esp + 0x1ac] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 456048: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45604c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45604d: push eax */
	{ DWORD v_ = 0x4b4078u; m->esp -= 4; M32(m->esp) = v_; }	/* 45604e: push 0x4b4078 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456053: push edx */
	m->esp -= 4; M32(m->esp) = 0x456059u; native_call(m, 0x49e9ddu);	/* 456054: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456059: add esp, 0x10 */
	goto L_456078;	/* 45605c: jmp 0x456078 */
L_45605e:
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 45605e: lea eax, [esp + 0x1ac] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 456065: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456069: push eax */
	{ DWORD v_ = 0x4b4068u; m->esp -= 4; M32(m->esp) = v_; }	/* 45606a: push 0x4b4068 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45606f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x456075u; native_call(m, 0x49e9ddu);	/* 456070: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456075: add esp, 0xc */
L_456078:
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 456078: lea edx, [esp + 0x1c] */
	m->ecx = (DWORD)(m->esp + 0x11cu);	/* 45607c: lea ecx, [esp + 0x11c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456083: push edx */
	m->esp -= 4; M32(m->esp) = 0x456089u; native_call(m, 0x46cd00u);	/* 456084: call 0x46cd00 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456089: test eax, eax */
	if (m->zf) goto L_4560cd;	/* 45608b: je 0x4560cd */
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 45608d: mov eax, dword ptr [ebp + 0xc011c] */
	m->ecx = M32((DWORD)(m->ebp + 0xc0118u));	/* 456093: mov ecx, dword ptr [ebp + 0xc0118] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 456099: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45609b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45609c: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45609d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45609f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4560a1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4560a3: push 0 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4560a5: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4560a7: push eax */
	{ DWORD a_ = m->ebp, b_ = 0x80114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4560a8: add ebp, 0x80114 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4560ae: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4560af: push ebp */
	m->ecx = (DWORD)(m->esp + 0x148u);	/* 4560b0: lea ecx, [esp + 0x148] */
	m->esp -= 4; M32(m->esp) = 0x4560bcu; native_call(m, 0x46ce80u);	/* 4560b7: call 0x46ce80 */
	m->ecx = (DWORD)(m->esp + 0x11cu);	/* 4560bc: lea ecx, [esp + 0x11c] */
	m->esp -= 4; M32(m->esp) = 0x4560c8u; native_call(m, 0x46ce50u);	/* 4560c3: call 0x46ce50 */
	goto L_45640a;	/* 4560c8: jmp 0x45640a */
L_4560cd:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 4560cd: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4560d3: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4560d5: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45640a;	/* 4560d7: jle 0x45640a */
L_4560dd:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 4560dd: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4560e3: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4560e5: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_456106;	/* 4560e7: jle 0x456106 */
L_4560e9:
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 4560e9: imul eax, edx */
	m->esi = M32((DWORD)(0xa1f238u));	/* 4560ec: mov esi, dword ptr [0xa1f238] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4560f2: add eax, ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4560f4: inc ecx */
	M32((DWORD)(m->ebp + m->eax*4 + 0x80114u)) = m->esi;	/* 4560f5: mov dword ptr [ebp + eax*4 + 0x80114], esi */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 4560fc: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456102: cmp ecx, eax */
	if (m->sf != m->of) goto L_4560e9;	/* 456104: jl 0x4560e9 */
L_456106:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 456106: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 45610c: inc edx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45610d: cmp edx, eax */
	if (m->sf != m->of) goto L_4560dd;	/* 45610f: jl 0x4560dd */
	goto L_45640a;	/* 456111: jmp 0x45640a */
L_456116:
	{ DWORD a_ = M32((DWORD)(0xa0e00cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456116: cmp dword ptr [0xa0e00c], ebx */
	if (!m->zf) goto L_456129;	/* 45611c: jne 0x456129 */
	m->esp -= 4; M32(m->esp) = 0x456123u; native_call(m, 0x46ea00u);	/* 45611e: call 0x46ea00 */
	M32((DWORD)(0xa0e00cu)) = m->esi;	/* 456123: mov dword ptr [0xa0e00c], esi */
L_456129:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 456129: mov al, byte ptr [ebp + 8] */
	m->esi = (DWORD)(m->ebp + 0x8u);	/* 45612c: lea esi, [ebp + 8] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45612f: test al, al */
	if (m->zf) goto L_456150;	/* 456131: je 0x456150 */
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 456133: lea eax, [esp + 0x1ac] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 45613a: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45613e: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45613f: push esi */
	{ DWORD v_ = 0x4b3fdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 456140: push 0x4b3fdc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456145: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45614bu; native_call(m, 0x49e9ddu);	/* 456146: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45614b: add esp, 0x10 */
	goto L_45616a;	/* 45614e: jmp 0x45616a */
L_456150:
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 456150: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 456157: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45615b: push edx */
	{ DWORD v_ = 0x4b3fd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45615c: push 0x4b3fd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456161: push eax */
	m->esp -= 4; M32(m->esp) = 0x456167u; native_call(m, 0x49e9ddu);	/* 456162: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456167: add esp, 0xc */
L_45616a:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 45616a: lea ecx, [esp + 0x10] */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 45616e: lea edx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456172: push ecx */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 456173: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456177: push edx */
	m->ecx = (DWORD)(m->ebp + 0x114u);	/* 456178: lea ecx, [ebp + 0x114] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45617e: push eax */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 45617f: lea edx, [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456183: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456184: push edx */
	m->ecx = m->ebp;	/* 456185: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x45618cu; native_call(m, 0x455550u);	/* 456187: call 0x455550 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45618c: push eax */
	m->esp -= 4; M32(m->esp) = 0x456192u; native_call(m, 0x46ed80u);	/* 45618d: call 0x46ed80 */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 456192: mov eax, dword ptr [ebp + 0xc0118] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 456198: mov ecx, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 45619c: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4561a0: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4561a3: cmp eax, ecx */
	if (!m->zf) goto L_4561af;	/* 4561a5: jne 0x4561af */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xc011cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4561a7: cmp dword ptr [ebp + 0xc011c], edx */
	if (m->zf) goto L_4561cb;	/* 4561ad: je 0x4561cb */
L_4561af:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4561af: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4561b0: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0xc011cu));	/* 4561b1: mov ecx, dword ptr [ebp + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4561b7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4561b8: push eax */
	{ DWORD v_ = 0x4b4104u; m->esp -= 4; M32(m->esp) = v_; }	/* 4561b9: push 0x4b4104 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4561be: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x4561c8u; native_call(m, 0x46c710u);	/* 4561c3: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4561c8: add esp, 0x18 */
L_4561cb:
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x0u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4561cb: cmp byte ptr [esi], 0 */
	if (m->zf) goto L_4561ed;	/* 4561ce: je 0x4561ed */
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 4561d0: lea edx, [esp + 0x1ac] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 4561d7: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4561db: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4561dc: push esi */
	{ DWORD v_ = 0x4b405cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4561dd: push 0x4b405c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4561e2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4561e8u; native_call(m, 0x49e9ddu);	/* 4561e3: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4561e8: add esp, 0x10 */
	goto L_456207;	/* 4561eb: jmp 0x456207 */
L_4561ed:
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 4561ed: lea ecx, [esp + 0x1ac] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 4561f4: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4561f8: push ecx */
	{ DWORD v_ = 0x4b4050u; m->esp -= 4; M32(m->esp) = v_; }	/* 4561f9: push 0x4b4050 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4561fe: push edx */
	m->esp -= 4; M32(m->esp) = 0x456204u; native_call(m, 0x49e9ddu);	/* 4561ff: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456204: add esp, 0xc */
L_456207:
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 456207: lea eax, [esp + 0x1c] */
	m->ecx = m->ebp;	/* 45620b: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45620d: push eax */
	m->esp -= 4; M32(m->esp) = 0x456213u; native_call(m, 0x4554c0u);	/* 45620e: call 0x4554c0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456213: test eax, eax */
	if (m->sf != m->of) goto L_4562ea;	/* 456215: jl 0x4562ea */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 45621b: lea ecx, [esp + 0x10] */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 45621f: lea edx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456223: push ecx */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 456224: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456228: push edx */
	m->ecx = (DWORD)(m->ebp + 0x40114u);	/* 456229: lea ecx, [ebp + 0x40114] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45622f: push eax */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 456230: lea edx, [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456234: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456235: push edx */
	m->ecx = m->ebp;	/* 456236: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x45623du; native_call(m, 0x455550u);	/* 456238: call 0x455550 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45623d: push eax */
	m->esp -= 4; M32(m->esp) = 0x456243u; native_call(m, 0x46ed80u);	/* 45623e: call 0x46ed80 */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 456243: mov eax, dword ptr [ebp + 0xc0118] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 456249: mov ecx, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 45624d: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456251: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456254: cmp eax, ecx */
	if (!m->zf) goto L_456260;	/* 456256: jne 0x456260 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xc011cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456258: cmp dword ptr [ebp + 0xc011c], edx */
	if (m->zf) goto L_45627c;	/* 45625e: je 0x45627c */
L_456260:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456260: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456261: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0xc011cu));	/* 456262: mov ecx, dword ptr [ebp + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456268: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456269: push eax */
	{ DWORD v_ = 0x4b4104u; m->esp -= 4; M32(m->esp) = v_; }	/* 45626a: push 0x4b4104 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45626f: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x456279u; native_call(m, 0x46c710u);	/* 456274: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456279: add esp, 0x18 */
L_45627c:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 45627c: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 456282: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456284: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_456326;	/* 456286: jle 0x456326 */
L_45628c:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 45628c: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 456292: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456294: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_4562dd;	/* 456296: jle 0x4562dd */
L_456298:
	{ long long p_ = (long long)(int)m->eax * (int)m->edi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 456298: imul eax, edi */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45629b: xor edx, edx */
	m->ecx = (DWORD)(m->eax + m->esi*1 + 0x0u);	/* 45629d: lea ecx, [eax + esi] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4562a0: xor eax, eax */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40116u))) & 0xff) << 0);	/* 4562a2: mov dl, byte ptr [ebp + ecx*4 + 0x40116] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40115u))) & 0xff) << 0);	/* 4562a9: mov al, byte ptr [ebp + ecx*4 + 0x40115] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4562b0: add edx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4562b2: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*4 + 0x40114u))) & 0xff) << 0);	/* 4562b4: mov al, byte ptr [ebp + ecx*4 + 0x40114] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4562bb: add edx, eax */
	m->eax = 0x55555556u;	/* 4562bd: mov eax, 0x55555556 */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 4562c2: imul edx */
	m->eax = m->edx;	/* 4562c4: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4562c6: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4562c9: add edx, eax */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4562cb: inc esi */
	M8((DWORD)(m->ebp + m->ecx*4 + 0x117u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4562cc: mov byte ptr [ebp + ecx*4 + 0x117], dl */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 4562d3: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4562d9: cmp esi, eax */
	if (m->sf != m->of) goto L_456298;	/* 4562db: jl 0x456298 */
L_4562dd:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 4562dd: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 4562e3: inc edi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4562e4: cmp edi, eax */
	if (m->sf != m->of) goto L_45628c;	/* 4562e6: jl 0x45628c */
	goto L_456326;	/* 4562e8: jmp 0x456326 */
L_4562ea:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 4562ea: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4562f0: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4562f2: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_456326;	/* 4562f4: jle 0x456326 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0xffu) & 0xff) << 0);	/* 4562f6: mov bl, 0xff */
L_4562f8:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 4562f8: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4562fe: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456300: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45631b;	/* 456302: jle 0x45631b */
L_456304:
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 456304: imul eax, edx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 456307: add eax, ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 456309: inc ecx */
	M8((DWORD)(m->ebp + m->eax*4 + 0x117u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 45630a: mov byte ptr [ebp + eax*4 + 0x117], bl */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 456311: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456317: cmp ecx, eax */
	if (m->sf != m->of) goto L_456304;	/* 456319: jl 0x456304 */
L_45631b:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 45631b: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 456321: inc edx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456322: cmp edx, eax */
	if (m->sf != m->of) goto L_4562f8;	/* 456324: jl 0x4562f8 */
L_456326:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x8u))) & 0xff) << 0);	/* 456326: mov cl, byte ptr [ebp + 8] */
	m->eax = (DWORD)(m->ebp + 0x8u);	/* 456329: lea eax, [ebp + 8] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45632c: test cl, cl */
	if (m->zf) goto L_45634d;	/* 45632e: je 0x45634d */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 456330: lea ecx, [esp + 0x1ac] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 456337: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45633b: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45633c: push eax */
	{ DWORD v_ = 0x4b4044u; m->esp -= 4; M32(m->esp) = v_; }	/* 45633d: push 0x4b4044 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456342: push edx */
	m->esp -= 4; M32(m->esp) = 0x456348u; native_call(m, 0x49e9ddu);	/* 456343: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456348: add esp, 0x10 */
	goto L_456367;	/* 45634b: jmp 0x456367 */
L_45634d:
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 45634d: lea eax, [esp + 0x1ac] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 456354: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456358: push eax */
	{ DWORD v_ = 0x4b4038u; m->esp -= 4; M32(m->esp) = v_; }	/* 456359: push 0x4b4038 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45635e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x456364u; native_call(m, 0x49e9ddu);	/* 45635f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456364: add esp, 0xc */
L_456367:
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 456367: lea edx, [esp + 0x1c] */
	m->ecx = m->ebp;	/* 45636b: mov ecx, ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45636d: push edx */
	m->esp -= 4; M32(m->esp) = 0x456373u; native_call(m, 0x456373u + M32(0x45636fu));	/* 0x4554c0 unless the patch DLL retargets it */	/* 45636e: call 0x4554c0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456373: test eax, eax */
	if (m->sf != m->of) goto L_4563ca;	/* 456375: jl 0x4563ca */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 456377: lea eax, [esp + 0x10] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 45637b: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45637f: push eax */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 456380: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456384: push ecx */
	m->eax = (DWORD)(m->ebp + 0x80114u);	/* 456385: lea eax, [ebp + 0x80114] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45638b: push edx */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 45638c: lea ecx, [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456390: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456391: push ecx */
	m->ecx = m->ebp;	/* 456392: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x456399u; native_call(m, 0x455550u);	/* 456394: call 0x455550 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456399: push eax */
	m->esp -= 4; M32(m->esp) = 0x45639fu; native_call(m, 0x46ed80u);	/* 45639a: call 0x46ed80 */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 45639f: mov eax, dword ptr [ebp + 0xc0118] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4563a5: mov ecx, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4563a9: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4563ad: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4563b0: cmp eax, ecx */
	if (!m->zf) goto L_4563bc;	/* 4563b2: jne 0x4563bc */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xc011cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4563b4: cmp dword ptr [ebp + 0xc011c], edx */
	if (m->zf) goto L_45640a;	/* 4563ba: je 0x45640a */
L_4563bc:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4563bc: push edx */
	m->edx = M32((DWORD)(m->ebp + 0xc011cu));	/* 4563bd: mov edx, dword ptr [ebp + 0xc011c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4563c3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4563c4: push edx */
	goto L_455e0e;	/* 4563c5: jmp 0x455e0e */
L_4563ca:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 4563ca: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4563d0: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4563d2: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45640a;	/* 4563d4: jle 0x45640a */
L_4563d6:
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 4563d6: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4563dc: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4563de: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4563ff;	/* 4563e0: jle 0x4563ff */
L_4563e2:
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 4563e2: imul eax, edx */
	m->esi = M32((DWORD)(0xa1f238u));	/* 4563e5: mov esi, dword ptr [0xa1f238] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4563eb: add eax, ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4563ed: inc ecx */
	M32((DWORD)(m->ebp + m->eax*4 + 0x80114u)) = m->esi;	/* 4563ee: mov dword ptr [ebp + eax*4 + 0x80114], esi */
	m->eax = M32((DWORD)(m->ebp + 0xc0118u));	/* 4563f5: mov eax, dword ptr [ebp + 0xc0118] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4563fb: cmp ecx, eax */
	if (m->sf != m->of) goto L_4563e2;	/* 4563fd: jl 0x4563e2 */
L_4563ff:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 4563ff: mov eax, dword ptr [ebp + 0xc011c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 456405: inc edx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456406: cmp edx, eax */
	if (m->sf != m->of) goto L_4563d6;	/* 456408: jl 0x4563d6 */
L_45640a:
	m->ecx = (DWORD)(m->esp + 0x11cu);	/* 45640a: lea ecx, [esp + 0x11c] */
	M8((DWORD)(m->esp + 0x2fcu)) = (BYTE)(0x1u);	/* 456411: mov byte ptr [esp + 0x2fc], 1 */
	m->esp -= 4; M32(m->esp) = 0x45641eu; native_call(m, 0x46ce60u);	/* 456419: call 0x46ce60 */
	m->ecx = (DWORD)(m->esp + 0x164u);	/* 45641e: lea ecx, [esp + 0x164] */
	M8((DWORD)(m->esp + 0x2fcu)) = (BYTE)(0x0u);	/* 456425: mov byte ptr [esp + 0x2fc], 0 */
	m->esp -= 4; M32(m->esp) = 0x456432u; native_call(m, 0x46ce60u);	/* 45642d: call 0x46ce60 */
	m->ecx = (DWORD)(m->esp + 0x2acu);	/* 456432: lea ecx, [esp + 0x2ac] */
	M32((DWORD)(m->esp + 0x2fcu)) = 0xffffffffu;	/* 456439: mov dword ptr [esp + 0x2fc], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x456449u; native_call(m, 0x46ce60u);	/* 456444: call 0x46ce60 */
	m->ecx = M32((DWORD)(m->esp + 0x2f4u));	/* 456449: mov ecx, dword ptr [esp + 0x2f4] */
	m->edi = M32(m->esp); m->esp += 4;	/* 456450: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 456451: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 456452: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 456453: pop ebx */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 456454: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x2f0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45645b: add esp, 0x2f0 */
	m->esp += 4 + 4; return;	/* 456461: ret 4 */
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
