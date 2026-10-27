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

static void lift_469b90(X86 *m);

/* skel_loadAseFrom (0x469b90), lifted by tools/lift.py */
static void lift_469b90(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x370u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469b90: sub esp, 0x370 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 469b96: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 469b97: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469b98: push esi */
	m->ebx = m->ecx;	/* 469b99: mov ebx, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 469b9b: push edi */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 469b9c: mov dword ptr [esp + 0x10], ebx */
	m->esp -= 4; M32(m->esp) = 0x469ba5u; native_call(m, 0x4699a0u);	/* 469ba0: call 0x4699a0 */
	m->eax = M32((DWORD)(m->esp + 0x384u));	/* 469ba5: mov eax, dword ptr [esp + 0x384] */
	m->ecx = (DWORD)(m->esp + 0x140u);	/* 469bac: lea ecx, [esp + 0x140] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469bb3: push eax */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 469bb4: xor ebp, ebp */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 469bb6: push 0x100 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469bbb: push ecx */
	M32((DWORD)(m->ebx + 0x10u)) = m->ebp;	/* 469bbc: mov dword ptr [ebx + 0x10], ebp */
	M32((DWORD)(m->ebx + 0x1cu)) = m->ebp;	/* 469bbf: mov dword ptr [ebx + 0x1c], ebp */
	M32((DWORD)(m->ebx + 0x18u)) = m->ebp;	/* 469bc2: mov dword ptr [ebx + 0x18], ebp */
	m->esp -= 4; M32(m->esp) = 0x469bcau; native_call(m, 0x49ecd7u);	/* 469bc5: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469bca: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469bcd: test eax, eax */
	if (m->zf) goto L_469cf1;	/* 469bcf: je 0x469cf1 */
L_469bd5:
	m->edx = (DWORD)(m->esp + 0x140u);	/* 469bd5: lea edx, [esp + 0x140] */
	{ DWORD v_ = 0x4c5498u; m->esp -= 4; M32(m->esp) = v_; }	/* 469bdc: push 0x4c5498 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469be1: push edx */
	m->esp -= 4; M32(m->esp) = 0x469be7u; native_call(m, 0x49ec3bu);	/* 469be2: call 0x49ec3b */
	m->edi = m->eax;	/* 469be7: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469be9: add esp, 8 */
	m->esi = 0x4c548cu;	/* 469bec: mov esi, 0x4c548c */
	m->ecx = m->edi;	/* 469bf1: mov ecx, edi */
L_469bf3:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 469bf3: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 469bf5: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469bf7: cmp al, byte ptr [esi] */
	if (!m->zf) goto L_469c17;	/* 469bf9: jne 0x469c17 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469bfb: test dl, dl */
	if (m->zf) goto L_469c13;	/* 469bfd: je 0x469c13 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 469bff: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 469c02: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469c04: cmp al, byte ptr [esi + 1] */
	if (!m->zf) goto L_469c17;	/* 469c07: jne 0x469c17 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 469c09: add ecx, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469c0c: add esi, 2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469c0f: test dl, dl */
	if (!m->zf) goto L_469bf3;	/* 469c11: jne 0x469bf3 */
L_469c13:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469c13: xor ecx, ecx */
	goto L_469c1c;	/* 469c15: jmp 0x469c1c */
L_469c17:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 469c17: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 469c19: sbb ecx, -1 */
L_469c1c:
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469c1c: cmp ecx, ebp */
	if (!m->zf) goto L_469c28;	/* 469c1e: jne 0x469c28 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x10u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebx + 0x10u)) = r_; }	/* 469c20: inc dword ptr [ebx + 0x10] */
	goto L_469ccc;	/* 469c23: jmp 0x469ccc */
L_469c28:
	m->esi = 0x4c5478u;	/* 469c28: mov esi, 0x4c5478 */
	m->ecx = m->edi;	/* 469c2d: mov ecx, edi */
L_469c2f:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 469c2f: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 469c31: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469c33: cmp al, byte ptr [esi] */
	if (!m->zf) goto L_469c53;	/* 469c35: jne 0x469c53 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469c37: test dl, dl */
	if (m->zf) goto L_469c4f;	/* 469c39: je 0x469c4f */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 469c3b: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 469c3e: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469c40: cmp al, byte ptr [esi + 1] */
	if (!m->zf) goto L_469c53;	/* 469c43: jne 0x469c53 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 469c45: add ecx, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469c48: add esi, 2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469c4b: test dl, dl */
	if (!m->zf) goto L_469c2f;	/* 469c4d: jne 0x469c2f */
L_469c4f:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469c4f: xor ecx, ecx */
	goto L_469c58;	/* 469c51: jmp 0x469c58 */
L_469c53:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 469c53: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 469c55: sbb ecx, -1 */
L_469c58:
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469c58: cmp ecx, ebp */
	if (m->zf) goto L_469cc9;	/* 469c5a: je 0x469cc9 */
	m->esi = 0x4c5460u;	/* 469c5c: mov esi, 0x4c5460 */
	m->ecx = m->edi;	/* 469c61: mov ecx, edi */
L_469c63:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 469c63: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 469c65: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469c67: cmp al, byte ptr [esi] */
	if (!m->zf) goto L_469c87;	/* 469c69: jne 0x469c87 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469c6b: test dl, dl */
	if (m->zf) goto L_469c83;	/* 469c6d: je 0x469c83 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 469c6f: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 469c72: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469c74: cmp al, byte ptr [esi + 1] */
	if (!m->zf) goto L_469c87;	/* 469c77: jne 0x469c87 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 469c79: add ecx, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469c7c: add esi, 2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469c7f: test dl, dl */
	if (!m->zf) goto L_469c63;	/* 469c81: jne 0x469c63 */
L_469c83:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469c83: xor ecx, ecx */
	goto L_469c8c;	/* 469c85: jmp 0x469c8c */
L_469c87:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 469c87: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 469c89: sbb ecx, -1 */
L_469c8c:
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469c8c: cmp ecx, ebp */
	if (m->zf) goto L_469cc9;	/* 469c8e: je 0x469cc9 */
	m->esi = 0x4c544cu;	/* 469c90: mov esi, 0x4c544c */
	m->eax = m->edi;	/* 469c95: mov eax, edi */
L_469c97:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 469c97: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469c99: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469c9b: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_469cbb;	/* 469c9d: jne 0x469cbb */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469c9f: test cl, cl */
	if (m->zf) goto L_469cb7;	/* 469ca1: je 0x469cb7 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 469ca3: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469ca6: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469ca8: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_469cbb;	/* 469cab: jne 0x469cbb */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469cad: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469cb0: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469cb3: test cl, cl */
	if (!m->zf) goto L_469c97;	/* 469cb5: jne 0x469c97 */
L_469cb7:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469cb7: xor eax, eax */
	goto L_469cc0;	/* 469cb9: jmp 0x469cc0 */
L_469cbb:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469cbb: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469cbd: sbb eax, -1 */
L_469cc0:
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469cc0: cmp eax, ebp */
	if (!m->zf) goto L_469ccc;	/* 469cc2: jne 0x469ccc */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x1cu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebx + 0x1cu)) = r_; }	/* 469cc4: inc dword ptr [ebx + 0x1c] */
	goto L_469ccc;	/* 469cc7: jmp 0x469ccc */
L_469cc9:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x18u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebx + 0x18u)) = r_; }	/* 469cc9: inc dword ptr [ebx + 0x18] */
L_469ccc:
	m->eax = M32((DWORD)(m->esp + 0x384u));	/* 469ccc: mov eax, dword ptr [esp + 0x384] */
	m->ecx = (DWORD)(m->esp + 0x140u);	/* 469cd3: lea ecx, [esp + 0x140] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469cda: push eax */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 469cdb: push 0x100 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469ce0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x469ce6u; native_call(m, 0x49ecd7u);	/* 469ce1: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469ce6: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469ce9: test eax, eax */
	if (!m->zf) goto L_469bd5;	/* 469ceb: jne 0x469bd5 */
L_469cf1:
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 469cf1: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469cf4: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_46a9fa;	/* 469cf6: jle 0x46a9fa */
	m->edx = (DWORD)(m->eax*8 + 0x0u);	/* 469cfc: lea edx, [eax*8] */
	m->esi = M32((DWORD)(m->esp + 0x388u));	/* 469d03: mov esi, dword ptr [esp + 0x388] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 469d0a: sub edx, eax */
	m->eax = M32((DWORD)(m->ebx + 0x1cu));	/* 469d0c: mov eax, dword ptr [ebx + 0x1c] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 469d0f: shl edx, 4 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 469d12: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->edx + m->eax*8 + 0x0u);	/* 469d15: lea ecx, [edx + eax*8] */
	m->edx = M32((DWORD)(m->ebx + 0x18u));	/* 469d18: mov edx, dword ptr [ebx + 0x18] */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 469d1b: shl edx, 5 */
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469d1e: cmp esi, ebp */
	m->eax = (DWORD)(m->ecx + m->edx*1 + 0x0u);	/* 469d20: lea eax, [ecx + edx] */
	M32((DWORD)(m->ebx + 0x4u)) = m->eax;	/* 469d23: mov dword ptr [ebx + 4], eax */
	if (!m->zf) goto L_469d57;	/* 469d26: jne 0x469d57 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469d28: push eax */
	m->esp -= 4; M32(m->esp) = 0x469d2eu; native_call(m, 0x49f1aau);	/* 469d29: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469d2e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469d31: cmp eax, ebp */
	M32((DWORD)(m->ebx + 0x8u)) = m->eax;	/* 469d33: mov dword ptr [ebx + 8], eax */
	if (!m->zf) goto L_469d4e;	/* 469d36: jne 0x469d4e */
	m->eax = M32((DWORD)(m->ebx + 0x4u));	/* 469d38: mov eax, dword ptr [ebx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469d3b: push eax */
	{ DWORD v_ = 0x4c4becu; m->esp -= 4; M32(m->esp) = v_; }	/* 469d3c: push 0x4c4bec */
	{ DWORD v_ = 0xa0eaa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 469d41: push 0xa0eaa8 */
	m->esp -= 4; M32(m->esp) = 0x469d4bu; native_call(m, 0x46c710u);	/* 469d46: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469d4b: add esp, 0xc */
L_469d4e:
	M32((DWORD)(m->ebx + 0xcu)) = 0x1u;	/* 469d4e: mov dword ptr [ebx + 0xc], 1 */
	goto L_469d7c;	/* 469d55: jmp 0x469d7c */
L_469d57:
	m->ecx = M32((DWORD)(m->esp + 0x38cu));	/* 469d57: mov ecx, dword ptr [esp + 0x38c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469d5e: cmp ecx, eax */
	if (m->sf == m->of) goto L_469d76;	/* 469d60: jge 0x469d76 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469d62: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469d63: push eax */
	{ DWORD v_ = 0x4c4b08u; m->esp -= 4; M32(m->esp) = v_; }	/* 469d64: push 0x4c4b08 */
	{ DWORD v_ = 0xa0eaa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 469d69: push 0xa0eaa8 */
	m->esp -= 4; M32(m->esp) = 0x469d73u; native_call(m, 0x46c710u);	/* 469d6e: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469d73: add esp, 0x10 */
L_469d76:
	M32((DWORD)(m->ebx + 0x8u)) = m->esi;	/* 469d76: mov dword ptr [ebx + 8], esi */
	M32((DWORD)(m->ebx + 0xcu)) = m->ebp;	/* 469d79: mov dword ptr [ebx + 0xc], ebp */
L_469d7c:
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 469d7c: mov esi, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->esp + 0x384u));	/* 469d80: mov edi, dword ptr [esp + 0x384] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 469d87: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 469d88: push ebp */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 469d89: mov ecx, dword ptr [esi + 8] */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 469d8c: mov eax, dword ptr [esi + 0x10] */
	M32((DWORD)(m->esi + 0x14u)) = m->ecx;	/* 469d8f: mov dword ptr [esi + 0x14], ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 469d92: push edi */
	m->ecx = (DWORD)(m->eax*8 + 0x0u);	/* 469d93: lea ecx, [eax*8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 469d9a: sub ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 469d9c: shl ecx, 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 469d9f: mov dword ptr [esp + 0x24], ecx */
	m->esp -= 4; M32(m->esp) = 0x469da8u; native_call(m, 0x49e91eu);	/* 469da3: call 0x49e91e */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 469da8: push edi */
	m->edx = (DWORD)(m->esp + 0x150u);	/* 469da9: lea edx, [esp + 0x150] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469db0: or eax, 0xffffffff */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 469db3: push 0x100 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469db8: push edx */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 469db9: mov dword ptr [esp + 0x44], eax */
	M32((DWORD)(m->esp + 0x34u)) = m->ebp;	/* 469dbd: mov dword ptr [esp + 0x34], ebp */
	M32((DWORD)(m->esp + 0x2cu)) = 0x21u;	/* 469dc1: mov dword ptr [esp + 0x2c], 0x21 */
	M32((DWORD)(m->esp + 0x40u)) = 0xa0u;	/* 469dc9: mov dword ptr [esp + 0x40], 0xa0 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 469dd1: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 469dd3: mov dword ptr [esp + 0x3c], eax */
	m->esp -= 4; M32(m->esp) = 0x469ddcu; native_call(m, 0x49ecd7u);	/* 469dd7: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469ddc: add esp, 0x18 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469ddf: test eax, eax */
	if (m->zf) goto L_46a63f;	/* 469de1: je 0x46a63f */
	M32((DWORD)(m->esp + 0x20u)) = 0xffffff90u;	/* 469de7: mov dword ptr [esp + 0x20], 0xffffff90 */
L_469def:
	m->eax = (DWORD)(m->esp + 0x140u);	/* 469def: lea eax, [esp + 0x140] */
	{ DWORD v_ = 0x4c5498u; m->esp -= 4; M32(m->esp) = v_; }	/* 469df6: push 0x4c5498 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469dfb: push eax */
	m->esp -= 4; M32(m->esp) = 0x469e01u; native_call(m, 0x49ec3bu);	/* 469dfc: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469e01: add esp, 8 */
	m->edi = m->eax;	/* 469e04: mov edi, eax */
	m->esi = 0x4c543cu;	/* 469e06: mov esi, 0x4c543c */
L_469e0b:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 469e0b: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469e0d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469e0f: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_469e2f;	/* 469e11: jne 0x469e2f */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469e13: test cl, cl */
	if (m->zf) goto L_469e2b;	/* 469e15: je 0x469e2b */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 469e17: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469e1a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469e1c: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_469e2f;	/* 469e1f: jne 0x469e2f */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469e21: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469e24: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469e27: test cl, cl */
	if (!m->zf) goto L_469e0b;	/* 469e29: jne 0x469e0b */
L_469e2b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469e2b: xor eax, eax */
	goto L_469e34;	/* 469e2d: jmp 0x469e34 */
L_469e2f:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469e2f: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469e31: sbb eax, -1 */
L_469e34:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469e34: test eax, eax */
	if (!m->zf) goto L_469e92;	/* 469e36: jne 0x469e92 */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 469e38: push 0x4b4310 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469e3d: push eax */
	m->esp -= 4; M32(m->esp) = 0x469e43u; native_call(m, 0x49ec3bu);	/* 469e3e: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469e43: push eax */
	m->esp -= 4; M32(m->esp) = 0x469e49u; native_call(m, 0x49ec09u);	/* 469e44: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469e49: add esp, 0xc */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 469e4c: mov dword ptr [esp + 0x1c], eax */
L_469e50:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 469e50: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469e54: test eax, eax */
	if (!m->zf) goto L_46a616;	/* 469e56: jne 0x46a616 */
L_469e5c:
	m->esi = 0x4c5430u;	/* 469e5c: mov esi, 0x4c5430 */
	m->eax = m->edi;	/* 469e61: mov eax, edi */
L_469e63:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 469e63: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469e65: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469e67: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a000;	/* 469e69: jne 0x46a000 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469e6f: test cl, cl */
	if (m->zf) goto L_469e8b;	/* 469e71: je 0x469e8b */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 469e73: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469e76: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469e78: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a000;	/* 469e7b: jne 0x46a000 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469e81: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469e84: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469e87: test cl, cl */
	if (!m->zf) goto L_469e63;	/* 469e89: jne 0x469e63 */
L_469e8b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469e8b: xor eax, eax */
	goto L_46a005;	/* 469e8d: jmp 0x46a005 */
L_469e92:
	m->esi = 0x4c541cu;	/* 469e92: mov esi, 0x4c541c */
	m->eax = m->edi;	/* 469e97: mov eax, edi */
L_469e99:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 469e99: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469e9b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469e9d: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_469ebd;	/* 469e9f: jne 0x469ebd */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469ea1: test cl, cl */
	if (m->zf) goto L_469eb9;	/* 469ea3: je 0x469eb9 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 469ea5: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469ea8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469eaa: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_469ebd;	/* 469ead: jne 0x469ebd */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469eaf: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469eb2: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469eb5: test cl, cl */
	if (!m->zf) goto L_469e99;	/* 469eb7: jne 0x469e99 */
L_469eb9:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469eb9: xor eax, eax */
	goto L_469ec2;	/* 469ebb: jmp 0x469ec2 */
L_469ebd:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469ebd: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469ebf: sbb eax, -1 */
L_469ec2:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469ec2: test eax, eax */
	if (!m->zf) goto L_469ef9;	/* 469ec4: jne 0x469ef9 */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 469ec6: push 0x4b4310 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469ecb: push eax */
	m->esp -= 4; M32(m->esp) = 0x469ed1u; native_call(m, 0x49ec3bu);	/* 469ecc: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469ed1: push eax */
	m->esp -= 4; M32(m->esp) = 0x469ed7u; native_call(m, 0x49ec09u);	/* 469ed2: call 0x49ec09 */
	m->ecx = m->eax;	/* 469ed7: mov ecx, eax */
	m->eax = 0x3e8u;	/* 469ed9: mov eax, 0x3e8 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 469ede: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 469edf: idiv ecx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469ee1: add esp, 0xc */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 469ee4: mov edx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 469ee8: mov dword ptr [esp + 0x14], eax */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 469eec: imul eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->edx + 0x20u)) = m->eax;	/* 469ef1: mov dword ptr [edx + 0x20], eax */
	goto L_469e50;	/* 469ef4: jmp 0x469e50 */
L_469ef9:
	m->esi = 0x4c5408u;	/* 469ef9: mov esi, 0x4c5408 */
	m->eax = m->edi;	/* 469efe: mov eax, edi */
L_469f00:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 469f00: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469f02: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469f04: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_469f24;	/* 469f06: jne 0x469f24 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469f08: test cl, cl */
	if (m->zf) goto L_469f20;	/* 469f0a: je 0x469f20 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 469f0c: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469f0f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469f11: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_469f24;	/* 469f14: jne 0x469f24 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469f16: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469f19: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469f1c: test cl, cl */
	if (!m->zf) goto L_469f00;	/* 469f1e: jne 0x469f00 */
L_469f20:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469f20: xor eax, eax */
	goto L_469f29;	/* 469f22: jmp 0x469f29 */
L_469f24:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469f24: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469f26: sbb eax, -1 */
L_469f29:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469f29: test eax, eax */
	if (!m->zf) goto L_469f4a;	/* 469f2b: jne 0x469f4a */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 469f2d: push 0x4b4310 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469f32: push eax */
	m->esp -= 4; M32(m->esp) = 0x469f38u; native_call(m, 0x49ec3bu);	/* 469f33: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469f38: push eax */
	m->esp -= 4; M32(m->esp) = 0x469f3eu; native_call(m, 0x49ec09u);	/* 469f39: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469f3e: add esp, 0xc */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 469f41: mov dword ptr [esp + 0x28], eax */
	goto L_469e50;	/* 469f45: jmp 0x469e50 */
L_469f4a:
	m->esi = 0x4c548cu;	/* 469f4a: mov esi, 0x4c548c */
	m->eax = m->edi;	/* 469f4f: mov eax, edi */
L_469f51:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 469f51: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469f53: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469f55: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_469f77;	/* 469f57: jne 0x469f77 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469f59: test cl, cl */
	if (m->zf) goto L_469f71;	/* 469f5b: je 0x469f71 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 469f5d: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469f60: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469f62: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_469f77;	/* 469f65: jne 0x469f77 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469f67: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469f6a: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469f6d: test cl, cl */
	if (!m->zf) goto L_469f51;	/* 469f6f: jne 0x469f51 */
L_469f71:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469f71: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469f73: xor eax, eax */
	goto L_469f7e;	/* 469f75: jmp 0x469f7e */
L_469f77:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469f77: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469f79: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469f7c: xor ecx, ecx */
L_469f7e:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469f7e: cmp eax, ecx */
	if (!m->zf) goto L_469fbb;	/* 469f80: jne 0x469fbb */
	m->ebx = M32((DWORD)(m->esp + 0x2cu));	/* 469f82: mov ebx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 469f86: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 469f8a: inc ebx */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 469f8b: mov dword ptr [esp + 0x24], ecx */
	m->edx = M32((DWORD)(m->eax + 0x14u));	/* 469f8f: mov edx, dword ptr [eax + 0x14] */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebx;	/* 469f92: mov dword ptr [esp + 0x2c], ebx */
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 469f96: mov ebx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ebx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 469f9a: add ebx, 0x70 */
	M32((DWORD)(m->esp + 0x20u)) = m->ebx;	/* 469f9d: mov dword ptr [esp + 0x20], ebx */
	{ DWORD a_ = m->ebx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 469fa1: add ebx, edx */
	M32((DWORD)(m->ebx + 0x40u)) = 0xffffffffu;	/* 469fa3: mov dword ptr [ebx + 0x40], 0xffffffff */
	M32((DWORD)(m->ebx + 0x60u)) = m->ecx;	/* 469faa: mov dword ptr [ebx + 0x60], ecx */
	M32((DWORD)(m->ebx + 0x64u)) = m->ecx;	/* 469fad: mov dword ptr [ebx + 0x64], ecx */
	M32((DWORD)(m->ebx + 0x68u)) = m->ecx;	/* 469fb0: mov dword ptr [ebx + 0x68], ecx */
	M32((DWORD)(m->ebx + 0x6cu)) = m->ecx;	/* 469fb3: mov dword ptr [ebx + 0x6c], ecx */
	goto L_469e5c;	/* 469fb6: jmp 0x469e5c */
L_469fbb:
	m->esi = 0x4c53f8u;	/* 469fbb: mov esi, 0x4c53f8 */
	m->eax = m->edi;	/* 469fc0: mov eax, edi */
L_469fc2:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 469fc2: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469fc4: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469fc6: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_469fe6;	/* 469fc8: jne 0x469fe6 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469fca: test cl, cl */
	if (m->zf) goto L_469fe2;	/* 469fcc: je 0x469fe2 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 469fce: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 469fd1: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469fd3: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_469fe6;	/* 469fd6: jne 0x469fe6 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469fd8: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469fdb: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469fde: test cl, cl */
	if (!m->zf) goto L_469fc2;	/* 469fe0: jne 0x469fc2 */
L_469fe2:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469fe2: xor eax, eax */
	goto L_469feb;	/* 469fe4: jmp 0x469feb */
L_469fe6:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469fe6: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 469fe8: sbb eax, -1 */
L_469feb:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469feb: test eax, eax */
	if (!m->zf) goto L_469e50;	/* 469fed: jne 0x469e50 */
	M32((DWORD)(m->esp + 0x24u)) = 0x1u;	/* 469ff3: mov dword ptr [esp + 0x24], 1 */
	goto L_46a616;	/* 469ffb: jmp 0x46a616 */
L_46a000:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a000: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a002: sbb eax, -1 */
L_46a005:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a005: test eax, eax */
	if (!m->zf) goto L_46a03b;	/* 46a007: jne 0x46a03b */
	{ DWORD v_ = 0x4c53f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a009: push 0x4c53f4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a00e: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a014u; native_call(m, 0x49ec3bu);	/* 46a00f: call 0x49ec3b */
	m->edi = m->eax;	/* 46a014: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46a016: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a019: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a01b: add esp, 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46a01e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46a020: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46a022: sub edi, ecx */
	m->eax = m->ecx;	/* 46a024: mov eax, ecx */
	m->esi = m->edi;	/* 46a026: mov esi, edi */
	m->edi = m->ebx;	/* 46a028: mov edi, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46a02a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46a02d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46a02f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46a031: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46a034: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_46a616;	/* 46a036: jmp 0x46a616 */
L_46a03b:
	m->esi = 0x4c53e8u;	/* 46a03b: mov esi, 0x4c53e8 */
	m->eax = m->edi;	/* 46a040: mov eax, edi */
L_46a042:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46a042: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a044: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a046: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a066;	/* 46a048: jne 0x46a066 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a04a: test cl, cl */
	if (m->zf) goto L_46a062;	/* 46a04c: je 0x46a062 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46a04e: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a051: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a053: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a066;	/* 46a056: jne 0x46a066 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a058: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a05b: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a05e: test cl, cl */
	if (!m->zf) goto L_46a042;	/* 46a060: jne 0x46a042 */
L_46a062:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a062: xor eax, eax */
	goto L_46a06b;	/* 46a064: jmp 0x46a06b */
L_46a066:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a066: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a068: sbb eax, -1 */
L_46a06b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a06b: test eax, eax */
	if (!m->zf) goto L_46a129;	/* 46a06d: jne 0x46a129 */
	{ DWORD v_ = 0x4c53f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a073: push 0x4c53f4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a078: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a07eu; native_call(m, 0x49ec3bu);	/* 46a079: call 0x49ec3b */
	m->edi = m->eax;	/* 46a07e: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46a080: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a083: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a085: add esp, 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46a088: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46a08a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46a08c: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x100u);	/* 46a08e: lea edx, [esp + 0x100] */
	m->eax = m->ecx;	/* 46a095: mov eax, ecx */
	m->esi = m->edi;	/* 46a097: mov esi, edi */
	m->edi = m->edx;	/* 46a099: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46a09b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46a09e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46a0a0: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 46a0a2: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46a0a6: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46a0a9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46a0ab: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a0ad: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46a0ff;	/* 46a0af: jle 0x46a0ff */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46a0b1: mov ecx, dword ptr [esp + 0x10] */
	m->ebp = M32((DWORD)(m->ecx + 0x14u));	/* 46a0b5: mov ebp, dword ptr [ecx + 0x14] */
L_46a0b8:
	m->esi = (DWORD)(m->esp + 0x100u);	/* 46a0b8: lea esi, [esp + 0x100] */
	m->eax = m->ebp;	/* 46a0bf: mov eax, ebp */
L_46a0c1:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46a0c1: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a0c3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a0c5: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a0e5;	/* 46a0c7: jne 0x46a0e5 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a0c9: test cl, cl */
	if (m->zf) goto L_46a0e1;	/* 46a0cb: je 0x46a0e1 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46a0cd: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a0d0: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a0d2: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a0e5;	/* 46a0d5: jne 0x46a0e5 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a0d7: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a0da: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a0dd: test cl, cl */
	if (!m->zf) goto L_46a0c1;	/* 46a0df: jne 0x46a0c1 */
L_46a0e1:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a0e1: xor eax, eax */
	goto L_46a0ea;	/* 46a0e3: jmp 0x46a0ea */
L_46a0e5:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a0e5: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a0e7: sbb eax, -1 */
L_46a0ea:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a0ea: test eax, eax */
	if (m->zf) goto L_46a0fc;	/* 46a0ec: je 0x46a0fc */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 46a0ee: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 46a0f2: inc edi */
	{ DWORD a_ = m->ebp, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46a0f3: add ebp, 0x70 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46a0f6: cmp edi, eax */
	if (m->sf != m->of) goto L_46a0b8;	/* 46a0f8: jl 0x46a0b8 */
	goto L_46a0ff;	/* 46a0fa: jmp 0x46a0ff */
L_46a0fc:
	M32((DWORD)(m->ebx + 0x40u)) = m->edi;	/* 46a0fc: mov dword ptr [ebx + 0x40], edi */
L_46a0ff:
	m->eax = M32((DWORD)(m->ebx + 0x40u));	/* 46a0ff: mov eax, dword ptr [ebx + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a102: test eax, eax */
	if (m->sf == m->of) goto L_46a616;	/* 46a104: jge 0x46a616 */
	m->eax = (DWORD)(m->esp + 0x100u);	/* 46a10a: lea eax, [esp + 0x100] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a111: push eax */
	{ DWORD v_ = 0x4c53b8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a112: push 0x4c53b8 */
	{ DWORD v_ = 0xa0eaa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a117: push 0xa0eaa8 */
	m->esp -= 4; M32(m->esp) = 0x46a121u; native_call(m, 0x46c710u);	/* 46a11c: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a121: add esp, 0xc */
	goto L_46a616;	/* 46a124: jmp 0x46a616 */
L_46a129:
	m->esi = 0x4c53b0u;	/* 46a129: mov esi, 0x4c53b0 */
	m->eax = m->edi;	/* 46a12e: mov eax, edi */
L_46a130:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46a130: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a132: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a134: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a154;	/* 46a136: jne 0x46a154 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a138: test cl, cl */
	if (m->zf) goto L_46a150;	/* 46a13a: je 0x46a150 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46a13c: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a13f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a141: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a154;	/* 46a144: jne 0x46a154 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a146: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a149: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a14c: test cl, cl */
	if (!m->zf) goto L_46a130;	/* 46a14e: jne 0x46a130 */
L_46a150:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a150: xor eax, eax */
	goto L_46a159;	/* 46a152: jmp 0x46a159 */
L_46a154:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a154: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a156: sbb eax, -1 */
L_46a159:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a159: test eax, eax */
	if (!m->zf) goto L_46a1a5;	/* 46a15b: jne 0x46a1a5 */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a15d: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a162: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a168u; native_call(m, 0x49ec3bu);	/* 46a163: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a168: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a16eu; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a169: call 0x49fe7a */
	MF((DWORD)(m->ebx + 0x44u)) = (float)ST(0); FPOP();	/* 46a16e: fstp dword ptr [ebx + 0x44] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a171: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a176: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46a17du; native_call(m, 0x49ec3bu);	/* 46a178: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a17d: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a183u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a17e: call 0x49fe7a */
	ST(0) = -ST(0);	/* 46a183: fchs  */
	MF((DWORD)(m->ebx + 0x4cu)) = (float)ST(0); FPOP();	/* 46a185: fstp dword ptr [ebx + 0x4c] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a188: push 0x4b4310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a18d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46a194u; native_call(m, 0x49ec3bu);	/* 46a18f: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a194: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a19au; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a195: call 0x49fe7a */
	MF((DWORD)(m->ebx + 0x48u)) = (float)ST(0); FPOP();	/* 46a19a: fstp dword ptr [ebx + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a19d: add esp, 0x24 */
	goto L_46a616;	/* 46a1a0: jmp 0x46a616 */
L_46a1a5:
	m->esi = 0x4c53a4u;	/* 46a1a5: mov esi, 0x4c53a4 */
	m->eax = m->edi;	/* 46a1aa: mov eax, edi */
L_46a1ac:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46a1ac: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a1ae: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a1b0: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a1d0;	/* 46a1b2: jne 0x46a1d0 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a1b4: test cl, cl */
	if (m->zf) goto L_46a1cc;	/* 46a1b6: je 0x46a1cc */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46a1b8: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a1bb: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a1bd: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a1d0;	/* 46a1c0: jne 0x46a1d0 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a1c2: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a1c5: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a1c8: test cl, cl */
	if (!m->zf) goto L_46a1ac;	/* 46a1ca: jne 0x46a1ac */
L_46a1cc:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a1cc: xor eax, eax */
	goto L_46a1d5;	/* 46a1ce: jmp 0x46a1d5 */
L_46a1d0:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a1d0: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a1d2: sbb eax, -1 */
L_46a1d5:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a1d5: test eax, eax */
	if (!m->zf) goto L_46a221;	/* 46a1d7: jne 0x46a221 */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a1d9: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a1de: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a1e4u; native_call(m, 0x49ec3bu);	/* 46a1df: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a1e4: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a1eau; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a1e5: call 0x49fe7a */
	MF((DWORD)(m->ebx + 0x54u)) = (float)ST(0); FPOP();	/* 46a1ea: fstp dword ptr [ebx + 0x54] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a1ed: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a1f2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46a1f9u; native_call(m, 0x49ec3bu);	/* 46a1f4: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a1f9: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a1ffu; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a1fa: call 0x49fe7a */
	ST(0) = -ST(0);	/* 46a1ff: fchs  */
	MF((DWORD)(m->ebx + 0x5cu)) = (float)ST(0); FPOP();	/* 46a201: fstp dword ptr [ebx + 0x5c] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a204: push 0x4b4310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a209: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46a210u; native_call(m, 0x49ec3bu);	/* 46a20b: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a210: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a216u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a211: call 0x49fe7a */
	MF((DWORD)(m->ebx + 0x58u)) = (float)ST(0); FPOP();	/* 46a216: fstp dword ptr [ebx + 0x58] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a219: add esp, 0x24 */
	goto L_46a616;	/* 46a21c: jmp 0x46a616 */
L_46a221:
	m->esi = 0x4c5398u;	/* 46a221: mov esi, 0x4c5398 */
	m->eax = m->edi;	/* 46a226: mov eax, edi */
L_46a228:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46a228: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a22a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a22c: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a24c;	/* 46a22e: jne 0x46a24c */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a230: test cl, cl */
	if (m->zf) goto L_46a248;	/* 46a232: je 0x46a248 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46a234: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a237: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a239: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a24c;	/* 46a23c: jne 0x46a24c */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a23e: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a241: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a244: test cl, cl */
	if (!m->zf) goto L_46a228;	/* 46a246: jne 0x46a228 */
L_46a248:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a248: xor eax, eax */
	goto L_46a251;	/* 46a24a: jmp 0x46a251 */
L_46a24c:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a24c: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a24e: sbb eax, -1 */
L_46a251:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a251: test eax, eax */
	if (!m->zf) goto L_46a273;	/* 46a253: jne 0x46a273 */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a255: push 0x4b4310 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a25a: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a260u; native_call(m, 0x49ec3bu);	/* 46a25b: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a260: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a266u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a261: call 0x49fe7a */
	ST(0) = -ST(0);	/* 46a266: fchs  */
	MF((DWORD)(m->ebx + 0x50u)) = (float)ST(0); FPOP();	/* 46a268: fstp dword ptr [ebx + 0x50] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a26b: add esp, 0xc */
	goto L_46a616;	/* 46a26e: jmp 0x46a616 */
L_46a273:
	m->esi = 0x4c5388u;	/* 46a273: mov esi, 0x4c5388 */
	m->eax = m->edi;	/* 46a278: mov eax, edi */
L_46a27a:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46a27a: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a27c: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a27e: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a29e;	/* 46a280: jne 0x46a29e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a282: test cl, cl */
	if (m->zf) goto L_46a29a;	/* 46a284: je 0x46a29a */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46a286: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a289: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a28b: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a29e;	/* 46a28e: jne 0x46a29e */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a290: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a293: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a296: test cl, cl */
	if (!m->zf) goto L_46a27a;	/* 46a298: jne 0x46a27a */
L_46a29a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a29a: xor eax, eax */
	goto L_46a2a3;	/* 46a29c: jmp 0x46a2a3 */
L_46a29e:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a29e: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a2a0: sbb eax, -1 */
L_46a2a3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a2a3: test eax, eax */
	if (m->zf) goto L_46a4aa;	/* 46a2a5: je 0x46a4aa */
	m->esi = 0x4c5374u;	/* 46a2ab: mov esi, 0x4c5374 */
	m->eax = m->edi;	/* 46a2b0: mov eax, edi */
L_46a2b2:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46a2b2: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a2b4: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a2b6: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a2d6;	/* 46a2b8: jne 0x46a2d6 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a2ba: test cl, cl */
	if (m->zf) goto L_46a2d2;	/* 46a2bc: je 0x46a2d2 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46a2be: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a2c1: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a2c3: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a2d6;	/* 46a2c6: jne 0x46a2d6 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a2c8: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a2cb: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a2ce: test cl, cl */
	if (!m->zf) goto L_46a2b2;	/* 46a2d0: jne 0x46a2b2 */
L_46a2d2:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a2d2: xor eax, eax */
	goto L_46a2db;	/* 46a2d4: jmp 0x46a2db */
L_46a2d6:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a2d6: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a2d8: sbb eax, -1 */
L_46a2db:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a2db: test eax, eax */
	if (m->zf) goto L_46a4aa;	/* 46a2dd: je 0x46a4aa */
	m->esi = 0x4c5364u;	/* 46a2e3: mov esi, 0x4c5364 */
	m->eax = m->edi;	/* 46a2e8: mov eax, edi */
L_46a2ea:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46a2ea: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a2ec: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a2ee: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_46a30e;	/* 46a2f0: jne 0x46a30e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a2f2: test cl, cl */
	if (m->zf) goto L_46a30a;	/* 46a2f4: je 0x46a30a */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 46a2f6: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46a2f9: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a2fb: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a30e;	/* 46a2fe: jne 0x46a30e */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a300: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a303: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a306: test cl, cl */
	if (!m->zf) goto L_46a2ea;	/* 46a308: jne 0x46a2ea */
L_46a30a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46a30a: xor eax, eax */
	goto L_46a313;	/* 46a30c: jmp 0x46a313 */
L_46a30e:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a30e: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46a310: sbb eax, -1 */
L_46a313:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a313: test eax, eax */
	if (!m->zf) goto L_46a616;	/* 46a315: jne 0x46a616 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46a31b: mov ecx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 46a31f: mov eax, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->ecx + 0x8u));	/* 46a323: mov edx, dword ptr [ecx + 8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a326: add eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x384u));	/* 46a328: mov edx, dword ptr [esp + 0x384] */
	M32((DWORD)(m->ebx + 0x6cu)) = m->eax;	/* 46a32f: mov dword ptr [ebx + 0x6c], eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a332: push edx */
	m->eax = (DWORD)(m->esp + 0x144u);	/* 46a333: lea eax, [esp + 0x144] */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a33a: push 0x100 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a33f: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a345u; native_call(m, 0x49ecd7u);	/* 46a340: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a345: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a348: test eax, eax */
	if (m->zf) goto L_46a494;	/* 46a34a: je 0x46a494 */
L_46a350:
	m->ecx = (DWORD)(m->esp + 0x140u);	/* 46a350: lea ecx, [esp + 0x140] */
	{ DWORD v_ = 0x4c535cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a357: push 0x4c535c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a35c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a362u; native_call(m, 0x49ec3bu);	/* 46a35d: call 0x49ec3b */
	m->edi = m->eax;	/* 46a362: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a364: add esp, 8 */
	m->esi = 0x4c544cu;	/* 46a367: mov esi, 0x4c544c */
	m->ecx = m->edi;	/* 46a36c: mov ecx, edi */
L_46a36e:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 46a36e: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 46a370: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a372: cmp al, byte ptr [esi] */
	if (!m->zf) goto L_46a392;	/* 46a374: jne 0x46a392 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a376: test dl, dl */
	if (m->zf) goto L_46a38e;	/* 46a378: je 0x46a38e */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 46a37a: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 46a37d: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a37f: cmp al, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a392;	/* 46a382: jne 0x46a392 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46a384: add ecx, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a387: add esi, 2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a38a: test dl, dl */
	if (!m->zf) goto L_46a36e;	/* 46a38c: jne 0x46a36e */
L_46a38e:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46a38e: xor ecx, ecx */
	goto L_46a397;	/* 46a390: jmp 0x46a397 */
L_46a392:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46a392: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46a394: sbb ecx, -1 */
L_46a397:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a397: test ecx, ecx */
	if (!m->zf) goto L_46a466;	/* 46a399: jne 0x46a466 */
	m->eax = M32((DWORD)(m->ebx + 0x68u));	/* 46a39f: mov eax, dword ptr [ebx + 0x68] */
	m->edx = M32((DWORD)(m->ebx + 0x6cu));	/* 46a3a2: mov edx, dword ptr [ebx + 0x6c] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3a5: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3aa: push 0 */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46a3ac: lea ecx, [eax + eax*4] */
	m->esi = (DWORD)(m->edx + m->ecx*8 + 0x0u);	/* 46a3af: lea esi, [edx + ecx*8] */
	m->esp -= 4; M32(m->esp) = 0x46a3b7u; native_call(m, 0x49ec3bu);	/* 46a3b2: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3b7: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a3bdu; native_call(m, 0x49ec09u);	/* 46a3b8: call 0x49ec09 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46a3bd: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esp + 0x34u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46a3be: idiv dword ptr [esp + 0x34] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3c2: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3c7: push 0 */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x28u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46a3c9: imul eax, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 46a3ce: mov dword ptr [esi], eax */
	m->esp -= 4; M32(m->esp) = 0x46a3d5u; native_call(m, 0x49ec3bu);	/* 46a3d0: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3d5: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a3dbu; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a3d6: call 0x49fe7a */
	MF((DWORD)(m->esi + 0xcu)) = (float)ST(0); FPOP();	/* 46a3db: fstp dword ptr [esi + 0xc] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3de: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3e3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46a3eau; native_call(m, 0x49ec3bu);	/* 46a3e5: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3ea: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a3f0u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a3eb: call 0x49fe7a */
	ST(0) = -ST(0);	/* 46a3f0: fchs  */
	MF((DWORD)(m->esi + 0x14u)) = (float)ST(0); FPOP();	/* 46a3f2: fstp dword ptr [esi + 0x14] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3f5: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a3fa: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46a401u; native_call(m, 0x49ec3bu);	/* 46a3fc: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a401: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a407u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a402: call 0x49fe7a */
	MF((DWORD)(m->esi + 0x10u)) = (float)ST(0); FPOP();	/* 46a407: fstp dword ptr [esi + 0x10] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a40a: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a40f: push 0 */
	{ DWORD a_ = m->esi, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a411: add esi, 8 */
	m->esp -= 4; M32(m->esp) = 0x46a419u; native_call(m, 0x49ec3bu);	/* 46a414: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a419: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a41fu; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a41a: call 0x49fe7a */
	ST(0) = -ST(0);	/* 46a41f: fchs  */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 46a421: fstp dword ptr [esi] */
	m->eax = M32((DWORD)(m->ebx + 0x68u));	/* 46a423: mov eax, dword ptr [ebx + 0x68] */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a426: add esp, 0x3c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a429: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46a461;	/* 46a42b: jle 0x46a461 */
	m->ecx = M32((DWORD)(m->ebx + 0x6cu));	/* 46a42d: mov ecx, dword ptr [ebx + 0x6c] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46a430: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0xffffffe0u);	/* 46a433: lea edx, [ecx + eax*8 - 0x20] */
	m->eax = (DWORD)(m->esp + 0x70u);	/* 46a437: lea eax, [esp + 0x70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a43b: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46a43c: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a43d: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a443u; native_call(m, 0x47d320u);	/* 46a43e: call 0x47d320 */
	m->ecx = M32((DWORD)(m->esp + 0x7cu));	/* 46a443: mov ecx, dword ptr [esp + 0x7c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a447: add esp, 0xc */
	M32((DWORD)(m->esi + 0x0u)) = m->ecx;	/* 46a44a: mov dword ptr [esi], ecx */
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 46a44c: mov edx, dword ptr [esp + 0x74] */
	M32((DWORD)(m->esi + 0x4u)) = m->edx;	/* 46a450: mov dword ptr [esi + 4], edx */
	m->eax = M32((DWORD)(m->esp + 0x78u));	/* 46a453: mov eax, dword ptr [esp + 0x78] */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 46a457: mov dword ptr [esi + 8], eax */
	m->ecx = M32((DWORD)(m->esp + 0x7cu));	/* 46a45a: mov ecx, dword ptr [esp + 0x7c] */
	M32((DWORD)(m->esi + 0xcu)) = m->ecx;	/* 46a45e: mov dword ptr [esi + 0xc], ecx */
L_46a461:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x68u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebx + 0x68u)) = r_; }	/* 46a461: inc dword ptr [ebx + 0x68] */
	goto L_46a46f;	/* 46a464: jmp 0x46a46f */
L_46a466:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a466: test edi, edi */
	if (m->zf) goto L_46a46f;	/* 46a468: je 0x46a46f */
	{ DWORD a_ = M8((DWORD)(m->edi + 0x0u)), b_ = 0x7du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a46a: cmp byte ptr [edi], 0x7d */
	if (m->zf) goto L_46a494;	/* 46a46d: je 0x46a494 */
L_46a46f:
	m->edx = M32((DWORD)(m->esp + 0x384u));	/* 46a46f: mov edx, dword ptr [esp + 0x384] */
	m->eax = (DWORD)(m->esp + 0x140u);	/* 46a476: lea eax, [esp + 0x140] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a47d: push edx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a47e: push 0x100 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a483: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a489u; native_call(m, 0x49ecd7u);	/* 46a484: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a489: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a48c: test eax, eax */
	if (!m->zf) goto L_46a350;	/* 46a48e: jne 0x46a350 */
L_46a494:
	m->eax = M32((DWORD)(m->ebx + 0x68u));	/* 46a494: mov eax, dword ptr [ebx + 0x68] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 46a497: mov edx, dword ptr [esp + 0x18] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46a49b: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*8 + 0x0u);	/* 46a49e: lea eax, [edx + ecx*8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 46a4a1: mov dword ptr [esp + 0x18], eax */
	goto L_46a616;	/* 46a4a5: jmp 0x46a616 */
L_46a4aa:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46a4aa: mov edx, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 46a4ae: mov ecx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->edx + 0x8u));	/* 46a4b2: mov eax, dword ptr [edx + 8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46a4b5: add ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x384u));	/* 46a4b7: mov eax, dword ptr [esp + 0x384] */
	M32((DWORD)(m->ebx + 0x64u)) = m->ecx;	/* 46a4be: mov dword ptr [ebx + 0x64], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a4c1: push eax */
	m->ecx = (DWORD)(m->esp + 0x144u);	/* 46a4c2: lea ecx, [esp + 0x144] */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a4c9: push 0x100 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a4ce: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a4d4u; native_call(m, 0x49ecd7u);	/* 46a4cf: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a4d4: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a4d7: test eax, eax */
	if (m->zf) goto L_46a606;	/* 46a4d9: je 0x46a606 */
L_46a4df:
	m->edx = (DWORD)(m->esp + 0x140u);	/* 46a4df: lea edx, [esp + 0x140] */
	{ DWORD v_ = 0x4c535cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a4e6: push 0x4c535c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a4eb: push edx */
	m->esp -= 4; M32(m->esp) = 0x46a4f1u; native_call(m, 0x49ec3bu);	/* 46a4ec: call 0x49ec3b */
	m->edi = m->eax;	/* 46a4f1: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a4f3: add esp, 8 */
	m->esi = 0x4c5478u;	/* 46a4f6: mov esi, 0x4c5478 */
	m->ecx = m->edi;	/* 46a4fb: mov ecx, edi */
L_46a4fd:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 46a4fd: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 46a4ff: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a501: cmp al, byte ptr [esi] */
	if (!m->zf) goto L_46a521;	/* 46a503: jne 0x46a521 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a505: test dl, dl */
	if (m->zf) goto L_46a51d;	/* 46a507: je 0x46a51d */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 46a509: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 46a50c: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a50e: cmp al, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a521;	/* 46a511: jne 0x46a521 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46a513: add ecx, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a516: add esi, 2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a519: test dl, dl */
	if (!m->zf) goto L_46a4fd;	/* 46a51b: jne 0x46a4fd */
L_46a51d:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46a51d: xor ecx, ecx */
	goto L_46a526;	/* 46a51f: jmp 0x46a526 */
L_46a521:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46a521: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46a523: sbb ecx, -1 */
L_46a526:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a526: test ecx, ecx */
	if (m->zf) goto L_46a56d;	/* 46a528: je 0x46a56d */
	m->esi = 0x4c5460u;	/* 46a52a: mov esi, 0x4c5460 */
	m->ecx = m->edi;	/* 46a52f: mov ecx, edi */
L_46a531:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 46a531: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 46a533: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a535: cmp al, byte ptr [esi] */
	if (!m->zf) goto L_46a555;	/* 46a537: jne 0x46a555 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a539: test dl, dl */
	if (m->zf) goto L_46a551;	/* 46a53b: je 0x46a551 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 46a53d: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 46a540: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a542: cmp al, byte ptr [esi + 1] */
	if (!m->zf) goto L_46a555;	/* 46a545: jne 0x46a555 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46a547: add ecx, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a54a: add esi, 2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46a54d: test dl, dl */
	if (!m->zf) goto L_46a531;	/* 46a54f: jne 0x46a531 */
L_46a551:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46a551: xor ecx, ecx */
	goto L_46a55a;	/* 46a553: jmp 0x46a55a */
L_46a555:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46a555: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46a557: sbb ecx, -1 */
L_46a55a:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a55a: test ecx, ecx */
	if (m->zf) goto L_46a56d;	/* 46a55c: je 0x46a56d */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a55e: test edi, edi */
	if (m->zf) goto L_46a5e1;	/* 46a560: je 0x46a5e1 */
	{ DWORD a_ = M8((DWORD)(m->edi + 0x0u)), b_ = 0x7du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46a562: cmp byte ptr [edi], 0x7d */
	if (m->zf) goto L_46a606;	/* 46a565: je 0x46a606 */
	goto L_46a5e1;	/* 46a56b: jmp 0x46a5e1 */
L_46a56d:
	m->esi = M32((DWORD)(m->ebx + 0x60u));	/* 46a56d: mov esi, dword ptr [ebx + 0x60] */
	m->ecx = M32((DWORD)(m->ebx + 0x64u));	/* 46a570: mov ecx, dword ptr [ebx + 0x64] */
	{ DWORD a_ = m->esi, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46a573: shl esi, 5 */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a576: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a57b: push 0 */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a57d: add esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x46a584u; native_call(m, 0x49ec3bu);	/* 46a57f: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a584: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a58au; native_call(m, 0x49ec09u);	/* 46a585: call 0x49ec09 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46a58a: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esp + 0x34u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46a58b: idiv dword ptr [esp + 0x34] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a58f: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a594: push 0 */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x28u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46a596: imul eax, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 46a59b: mov dword ptr [esi], eax */
	m->esp -= 4; M32(m->esp) = 0x46a5a2u; native_call(m, 0x49ec3bu);	/* 46a59d: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5a2: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a5a8u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a5a3: call 0x49fe7a */
	MF((DWORD)(m->esi + 0x8u)) = (float)ST(0); FPOP();	/* 46a5a8: fstp dword ptr [esi + 8] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5ab: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5b0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46a5b7u; native_call(m, 0x49ec3bu);	/* 46a5b2: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5b7: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a5bdu; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a5b8: call 0x49fe7a */
	ST(0) = -ST(0);	/* 46a5bd: fchs  */
	MF((DWORD)(m->esi + 0x10u)) = (float)ST(0); FPOP();	/* 46a5bf: fstp dword ptr [esi + 0x10] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5c2: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5c7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46a5ceu; native_call(m, 0x49ec3bu);	/* 46a5c9: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5ce: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a5d4u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46a5cf: call 0x49fe7a */
	MF((DWORD)(m->esi + 0xcu)) = (float)ST(0); FPOP();	/* 46a5d4: fstp dword ptr [esi + 0xc] */
	m->eax = M32((DWORD)(m->ebx + 0x60u));	/* 46a5d7: mov eax, dword ptr [ebx + 0x60] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a5da: add esp, 0x30 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46a5dd: inc eax */
	M32((DWORD)(m->ebx + 0x60u)) = m->eax;	/* 46a5de: mov dword ptr [ebx + 0x60], eax */
L_46a5e1:
	m->ecx = M32((DWORD)(m->esp + 0x384u));	/* 46a5e1: mov ecx, dword ptr [esp + 0x384] */
	m->edx = (DWORD)(m->esp + 0x140u);	/* 46a5e8: lea edx, [esp + 0x140] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5ef: push ecx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5f0: push 0x100 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a5f5: push edx */
	m->esp -= 4; M32(m->esp) = 0x46a5fbu; native_call(m, 0x49ecd7u);	/* 46a5f6: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a5fb: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a5fe: test eax, eax */
	if (!m->zf) goto L_46a4df;	/* 46a600: jne 0x46a4df */
L_46a606:
	m->eax = M32((DWORD)(m->ebx + 0x60u));	/* 46a606: mov eax, dword ptr [ebx + 0x60] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 46a609: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46a60d: shl eax, 5 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46a610: add ecx, eax */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 46a612: mov dword ptr [esp + 0x18], ecx */
L_46a616:
	m->ecx = M32((DWORD)(m->esp + 0x384u));	/* 46a616: mov ecx, dword ptr [esp + 0x384] */
	m->edx = (DWORD)(m->esp + 0x140u);	/* 46a61d: lea edx, [esp + 0x140] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a624: push ecx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 46a625: push 0x100 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a62a: push edx */
	m->esp -= 4; M32(m->esp) = 0x46a630u; native_call(m, 0x49ecd7u);	/* 46a62b: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a630: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a633: test eax, eax */
	if (!m->zf) goto L_469def;	/* 46a635: jne 0x469def */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 46a63b: mov esi, dword ptr [esp + 0x10] */
L_46a63f:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46a63f: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46a642: dec eax */
	if (m->sf) goto L_46a87f;	/* 46a643: js 0x46a87f */
	m->ebp = (DWORD)(m->eax*8 + 0x0u);	/* 46a649: lea ebp, [eax*8] */
	m->ebx = (DWORD)(m->eax + 0x1u);	/* 46a650: lea ebx, [eax + 1] */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46a653: sub ebp, eax */
	{ DWORD a_ = m->ebp, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 46a655: shl ebp, 4 */
L_46a658:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46a658: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->eax + 0x14u));	/* 46a65c: mov edi, dword ptr [eax + 0x14] */
	m->eax = M32((DWORD)(m->edi + m->ebp*1 + 0x40u));	/* 46a65f: mov eax, dword ptr [edi + ebp + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a663: test eax, eax */
	if (m->sf != m->of) goto L_46a875;	/* 46a665: jl 0x46a875 */
	m->ecx = (DWORD)(m->eax*8 + 0x0u);	/* 46a66b: lea ecx, [eax*8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46a672: sub ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46a674: shl ecx, 4 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->edi*1 + 0x4cu)));	/* 46a677: fld dword ptr [ecx + edi + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->edi*1 + 0x48u)));	/* 46a67b: fld dword ptr [ecx + edi + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->edi*1 + 0x44u)));	/* 46a67f: fld dword ptr [ecx + edi + 0x44] */
	m->eax = (DWORD)(m->ecx + m->edi*1 + 0x44u);	/* 46a683: lea eax, [ecx + edi + 0x44] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f800000u;	/* 46a687: mov dword ptr [esp + 0x30], 0x3f800000 */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 46a68f: fstp dword ptr [esp + 0x60] */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 46a693: mov dword ptr [esp + 0x40], 0 */
	M32((DWORD)(m->esp + 0x50u)) = 0x0u;	/* 46a69b: mov dword ptr [esp + 0x50], 0 */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 46a6a3: fstp dword ptr [esp + 0x64] */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 46a6a7: mov dword ptr [esp + 0x34], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f800000u;	/* 46a6af: mov dword ptr [esp + 0x44], 0x3f800000 */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 46a6b7: fstp dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 46a6bb: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x38u)) = 0x0u;	/* 46a6c3: mov dword ptr [esp + 0x38], 0 */
	M32((DWORD)(m->esp + 0x48u)) = 0x0u;	/* 46a6cb: mov dword ptr [esp + 0x48], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x3f800000u;	/* 46a6d3: mov dword ptr [esp + 0x58], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x0u;	/* 46a6db: mov dword ptr [esp + 0x3c], 0 */
	M32((DWORD)(m->esp + 0x4cu)) = 0x0u;	/* 46a6e3: mov dword ptr [esp + 0x4c], 0 */
	M32((DWORD)(m->esp + 0x5cu)) = 0x0u;	/* 46a6eb: mov dword ptr [esp + 0x5c], 0 */
	M32((DWORD)(m->esp + 0x6cu)) = 0x3f800000u;	/* 46a6f3: mov dword ptr [esp + 0x6c], 0x3f800000 */
	m->eax = M32((DWORD)(m->edi + m->ebp*1 + 0x40u));	/* 46a6fb: mov eax, dword ptr [edi + ebp + 0x40] */
	m->ecx = (DWORD)(m->esp + 0x80u);	/* 46a6ff: lea ecx, [esp + 0x80] */
	m->edx = (DWORD)(m->eax*8 + 0x0u);	/* 46a706: lea edx, [eax*8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46a70d: sub edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46a70f: shl edx, 4 */
	m->eax = (DWORD)(m->edx + m->edi*1 + 0x50u);	/* 46a712: lea eax, [edx + edi + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a716: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a717: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a71du; native_call(m, 0x47d9a0u);	/* 46a718: call 0x47d9a0 */
	m->edx = (DWORD)(m->esp + 0x88u);	/* 46a71d: lea edx, [esp + 0x88] */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 46a724: lea eax, [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a728: push edx */
	m->ecx = (DWORD)(m->esp + 0x24cu);	/* 46a729: lea ecx, [esp + 0x24c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a730: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a731: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a737u; native_call(m, 0x47d380u);	/* 46a732: call 0x47d380 */
	m->edx = (DWORD)(m->esp + 0x254u);	/* 46a737: lea edx, [esp + 0x254] */
	m->eax = (DWORD)(m->esp + 0x314u);	/* 46a73e: lea eax, [esp + 0x314] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a745: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a746: push eax */
	m->esp -= 4; M32(m->esp) = 0x46a74cu; native_call(m, 0x47d740u);	/* 46a747: call 0x47d740 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + m->ebp*1 + 0x4cu)));	/* 46a74c: fld dword ptr [edi + ebp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + m->ebp*1 + 0x48u)));	/* 46a750: fld dword ptr [edi + ebp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + m->ebp*1 + 0x44u)));	/* 46a754: fld dword ptr [edi + ebp + 0x44] */
	m->esi = (DWORD)(m->edi + m->ebp*1 + 0x44u);	/* 46a758: lea esi, [edi + ebp + 0x44] */
	m->edi = (DWORD)(m->edi + m->ebp*1 + 0x50u);	/* 46a75c: lea edi, [edi + ebp + 0x50] */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0); FPOP();	/* 46a760: fstp dword ptr [esp + 0x7c] */
	m->ecx = (DWORD)(m->esp + 0x9cu);	/* 46a764: lea ecx, [esp + 0x9c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46a76b: push edi */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 46a76c: fstp dword ptr [esp + 0x84] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a773: push ecx */
	M32((DWORD)(m->esp + 0x54u)) = 0x3f800000u;	/* 46a774: mov dword ptr [esp + 0x54], 0x3f800000 */
	MF((DWORD)(m->esp + 0x8cu)) = (float)ST(0); FPOP();	/* 46a77c: fstp dword ptr [esp + 0x8c] */
	M32((DWORD)(m->esp + 0x64u)) = 0x0u;	/* 46a783: mov dword ptr [esp + 0x64], 0 */
	M32((DWORD)(m->esp + 0x74u)) = 0x0u;	/* 46a78b: mov dword ptr [esp + 0x74], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x0u;	/* 46a793: mov dword ptr [esp + 0x58], 0 */
	M32((DWORD)(m->esp + 0x68u)) = 0x3f800000u;	/* 46a79b: mov dword ptr [esp + 0x68], 0x3f800000 */
	M32((DWORD)(m->esp + 0x78u)) = 0x0u;	/* 46a7a3: mov dword ptr [esp + 0x78], 0 */
	M32((DWORD)(m->esp + 0x5cu)) = 0x0u;	/* 46a7ab: mov dword ptr [esp + 0x5c], 0 */
	M32((DWORD)(m->esp + 0x6cu)) = 0x0u;	/* 46a7b3: mov dword ptr [esp + 0x6c], 0 */
	M32((DWORD)(m->esp + 0x7cu)) = 0x3f800000u;	/* 46a7bb: mov dword ptr [esp + 0x7c], 0x3f800000 */
	M32((DWORD)(m->esp + 0x60u)) = 0x0u;	/* 46a7c3: mov dword ptr [esp + 0x60], 0 */
	M32((DWORD)(m->esp + 0x70u)) = 0x0u;	/* 46a7cb: mov dword ptr [esp + 0x70], 0 */
	M32((DWORD)(m->esp + 0x80u)) = 0x0u;	/* 46a7d3: mov dword ptr [esp + 0x80], 0 */
	M32((DWORD)(m->esp + 0x90u)) = 0x3f800000u;	/* 46a7de: mov dword ptr [esp + 0x90], 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x46a7eeu; native_call(m, 0x47d9a0u);	/* 46a7e9: call 0x47d9a0 */
	m->edx = (DWORD)(m->esp + 0xa4u);	/* 46a7ee: lea edx, [esp + 0xa4] */
	m->eax = (DWORD)(m->esp + 0x54u);	/* 46a7f5: lea eax, [esp + 0x54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a7f9: push edx */
	m->ecx = (DWORD)(m->esp + 0x368u);	/* 46a7fa: lea ecx, [esp + 0x368] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a801: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a802: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a808u; native_call(m, 0x47d380u);	/* 46a803: call 0x47d380 */
	m->edx = (DWORD)(m->esp + 0x370u);	/* 46a808: lea edx, [esp + 0x370] */
	m->eax = (DWORD)(m->esp + 0x330u);	/* 46a80f: lea eax, [esp + 0x330] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a816: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a817: push eax */
	m->ecx = (DWORD)(m->esp + 0xf8u);	/* 46a818: lea ecx, [esp + 0xf8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a81f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a825u; native_call(m, 0x47d380u);	/* 46a820: call 0x47d380 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x134u)));	/* 46a825: fld dword ptr [esp + 0x134] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x130u)));	/* 46a82c: fld dword ptr [esp + 0x130] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x12cu)));	/* 46a833: fld dword ptr [esp + 0x12c] */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 46a83a: fstp dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a83c: add esp, 0x3c */
	m->edx = (DWORD)(m->esp + 0xc0u);	/* 46a83f: lea edx, [esp + 0xc0] */
	MF((DWORD)(m->esi + 0x4u)) = (float)ST(0); FPOP();	/* 46a846: fstp dword ptr [esi + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a849: push edx */
	m->ecx = m->edi;	/* 46a84a: mov ecx, edi */
	MF((DWORD)(m->esi + 0x8u)) = (float)ST(0); FPOP();	/* 46a84c: fstp dword ptr [esi + 8] */
	M32((DWORD)(m->esp + 0xfcu)) = 0x0u;	/* 46a84f: mov dword ptr [esp + 0xfc], 0 */
	M32((DWORD)(m->esp + 0xf8u)) = 0x0u;	/* 46a85a: mov dword ptr [esp + 0xf8], 0 */
	M32((DWORD)(m->esp + 0xf4u)) = 0x0u;	/* 46a865: mov dword ptr [esp + 0xf4], 0 */
	m->esp -= 4; M32(m->esp) = 0x46a875u; native_call(m, 0x47d2f0u);	/* 46a870: call 0x47d2f0 */
L_46a875:
	{ DWORD a_ = m->ebp, b_ = 0x70u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46a875: sub ebp, 0x70 */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 46a878: dec ebx */
	if (!m->zf) goto L_46a658;	/* 46a879: jne 0x46a658 */
L_46a87f:
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 46a87f: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46a883: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebx;	/* 46a885: mov dword ptr [esp + 0x1c], ebx */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x10u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46a889: cmp dword ptr [edi + 0x10], ebx */
	if (m->zf || m->sf != m->of) goto L_46a9fa;	/* 46a88c: jle 0x46a9fa */
	M32((DWORD)(m->esp + 0x14u)) = m->ebx;	/* 46a892: mov dword ptr [esp + 0x14], ebx */
L_46a896:
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 46a896: mov esi, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x14u));	/* 46a89a: mov eax, dword ptr [edi + 0x14] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46a89d: add esi, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46a89f: xor edx, edx */
	m->eax = M32((DWORD)(m->esi + 0x60u));	/* 46a8a1: mov eax, dword ptr [esi + 0x60] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46a8a4: dec eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a8a5: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46a8e5;	/* 46a8a7: jle 0x46a8e5 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46a8a9: xor ecx, ecx */
L_46a8ab:
	m->eax = M32((DWORD)(m->esi + 0x64u));	/* 46a8ab: mov eax, dword ptr [esi + 0x64] */
	m->ebp = M32((DWORD)(m->ecx + m->eax*1 + 0x20u));	/* 46a8ae: mov ebp, dword ptr [ecx + eax + 0x20] */
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ecx + m->eax*1 + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46a8b2: sub ebp, dword ptr [ecx + eax] */
	M32((DWORD)(m->ecx + m->eax*1 + 0x4u)) = m->ebp;	/* 46a8b5: mov dword ptr [ecx + eax + 4], ebp */
	m->eax = M32((DWORD)(m->esi + 0x64u));	/* 46a8b9: mov eax, dword ptr [esi + 0x64] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46a8bc: add eax, ecx */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 46a8be: inc edx */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46a8bf: add ecx, 0x20 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x30u)));	/* 46a8c2: fld dword ptr [eax + 0x30] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 46a8c5: fsub dword ptr [eax + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x2cu)));	/* 46a8c8: fld dword ptr [eax + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0xcu));	/* 46a8cb: fsub dword ptr [eax + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x28u)));	/* 46a8ce: fld dword ptr [eax + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 46a8d1: fsub dword ptr [eax + 8] */
	MF((DWORD)(m->eax + 0x14u)) = (float)ST(0); FPOP();	/* 46a8d4: fstp dword ptr [eax + 0x14] */
	MF((DWORD)(m->eax + 0x18u)) = (float)ST(0); FPOP();	/* 46a8d7: fstp dword ptr [eax + 0x18] */
	MF((DWORD)(m->eax + 0x1cu)) = (float)ST(0); FPOP();	/* 46a8da: fstp dword ptr [eax + 0x1c] */
	m->eax = M32((DWORD)(m->esi + 0x60u));	/* 46a8dd: mov eax, dword ptr [esi + 0x60] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46a8e0: dec eax */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46a8e1: cmp edx, eax */
	if (m->sf != m->of) goto L_46a8ab;	/* 46a8e3: jl 0x46a8ab */
L_46a8e5:
	m->eax = M32((DWORD)(m->esi + 0x60u));	/* 46a8e5: mov eax, dword ptr [esi + 0x60] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46a8e8: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_46a90b;	/* 46a8ea: jle 0x46a90b */
	m->ecx = M32((DWORD)(m->esi + 0x64u));	/* 46a8ec: mov ecx, dword ptr [esi + 0x64] */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46a8ef: shl eax, 5 */
	M32((DWORD)(m->eax + m->ecx*1 + 0xffffffe4u)) = m->ebx;	/* 46a8f2: mov dword ptr [eax + ecx - 0x1c], ebx */
	m->edx = M32((DWORD)(m->esi + 0x60u));	/* 46a8f6: mov edx, dword ptr [esi + 0x60] */
	m->eax = M32((DWORD)(m->esi + 0x64u));	/* 46a8f9: mov eax, dword ptr [esi + 0x64] */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46a8fc: shl edx, 5 */
	m->eax = (DWORD)(m->edx + m->eax*1 + 0xfffffff4u);	/* 46a8ff: lea eax, [edx + eax - 0xc] */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 46a903: mov dword ptr [eax], ebx */
	M32((DWORD)(m->eax + 0x4u)) = m->ebx;	/* 46a905: mov dword ptr [eax + 4], ebx */
	M32((DWORD)(m->eax + 0x8u)) = m->ebx;	/* 46a908: mov dword ptr [eax + 8], ebx */
L_46a90b:
	m->ecx = M32((DWORD)(m->esi + 0x68u));	/* 46a90b: mov ecx, dword ptr [esi + 0x68] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 46a90e: xor ebp, ebp */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46a910: dec ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46a911: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_46a9b2;	/* 46a913: jle 0x46a9b2 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46a919: xor edi, edi */
L_46a91b:
	m->eax = M32((DWORD)(m->esi + 0x6cu));	/* 46a91b: mov eax, dword ptr [esi + 0x6c] */
	m->edx = M32((DWORD)(m->eax + m->edi*1 + 0x28u));	/* 46a91e: mov edx, dword ptr [eax + edi + 0x28] */
	m->ecx = M32((DWORD)(m->eax + m->edi*1 + 0x0u));	/* 46a922: mov ecx, dword ptr [eax + edi] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46a925: sub edx, ecx */
	M32((DWORD)(m->eax + m->edi*1 + 0x4u)) = m->edx;	/* 46a927: mov dword ptr [eax + edi + 4], edx */
	m->eax = M32((DWORD)(m->esi + 0x6cu));	/* 46a92b: mov eax, dword ptr [esi + 0x6c] */
	m->edx = (DWORD)(m->esp + 0x80u);	/* 46a92e: lea edx, [esp + 0x80] */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x8u);	/* 46a935: lea ecx, [edi + eax + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a939: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a93a: push edx */
	m->esp -= 4; M32(m->esp) = 0x46a940u; native_call(m, 0x47d9a0u);	/* 46a93b: call 0x47d9a0 */
	m->eax = (DWORD)(m->esp + 0x88u);	/* 46a940: lea eax, [esp + 0x88] */
	m->ecx = (DWORD)(m->esp + 0x288u);	/* 46a947: lea ecx, [esp + 0x288] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a94e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a94f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a955u; native_call(m, 0x47d830u);	/* 46a950: call 0x47d830 */
	m->edx = M32((DWORD)(m->esi + 0x6cu));	/* 46a955: mov edx, dword ptr [esi + 0x6c] */
	m->ecx = (DWORD)(m->esp + 0x90u);	/* 46a958: lea ecx, [esp + 0x90] */
	m->eax = (DWORD)(m->edi + m->edx*1 + 0x30u);	/* 46a95f: lea eax, [edi + edx + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a963: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a964: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a96au; native_call(m, 0x47d9a0u);	/* 46a965: call 0x47d9a0 */
	m->edx = (DWORD)(m->esp + 0x98u);	/* 46a96a: lea edx, [esp + 0x98] */
	m->eax = (DWORD)(m->esp + 0x298u);	/* 46a971: lea eax, [esp + 0x298] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a978: push edx */
	m->ecx = (DWORD)(m->esp + 0x2dcu);	/* 46a979: lea ecx, [esp + 0x2dc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46a980: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a981: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46a987u; native_call(m, 0x47d380u);	/* 46a982: call 0x47d380 */
	m->eax = M32((DWORD)(m->esi + 0x6cu));	/* 46a987: mov eax, dword ptr [esi + 0x6c] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a98a: add esp, 0x24 */
	m->edx = (DWORD)(m->esp + 0x2c0u);	/* 46a98d: lea edx, [esp + 0x2c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46a994: push edx */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x18u);	/* 46a995: lea ecx, [edi + eax + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x46a99eu; native_call(m, 0x47d2f0u);	/* 46a999: call 0x47d2f0 */
	m->ecx = M32((DWORD)(m->esi + 0x68u));	/* 46a99e: mov ecx, dword ptr [esi + 0x68] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 46a9a1: inc ebp */
	{ DWORD a_ = m->edi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46a9a2: add edi, 0x28 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46a9a5: dec ecx */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46a9a6: cmp ebp, ecx */
	if (m->sf != m->of) goto L_46a91b;	/* 46a9a8: jl 0x46a91b */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 46a9ae: mov edi, dword ptr [esp + 0x10] */
L_46a9b2:
	m->eax = M32((DWORD)(m->esi + 0x68u));	/* 46a9b2: mov eax, dword ptr [esi + 0x68] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46a9b5: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_46a9db;	/* 46a9b7: jle 0x46a9db */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46a9b9: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->esi + 0x6cu));	/* 46a9bc: mov eax, dword ptr [esi + 0x6c] */
	M32((DWORD)(m->eax + m->edx*8 + 0xffffffdcu)) = m->ebx;	/* 46a9bf: mov dword ptr [eax + edx*8 - 0x24], ebx */
	m->eax = M32((DWORD)(m->esi + 0x68u));	/* 46a9c3: mov eax, dword ptr [esi + 0x68] */
	m->edx = M32((DWORD)(m->esi + 0x6cu));	/* 46a9c6: mov edx, dword ptr [esi + 0x6c] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46a9c9: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*8 + 0xfffffff0u);	/* 46a9cc: lea eax, [edx + ecx*8 - 0x10] */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 46a9d0: mov dword ptr [eax], ebx */
	M32((DWORD)(m->eax + 0x4u)) = m->ebx;	/* 46a9d2: mov dword ptr [eax + 4], ebx */
	M32((DWORD)(m->eax + 0x8u)) = m->ebx;	/* 46a9d5: mov dword ptr [eax + 8], ebx */
	M32((DWORD)(m->eax + 0xcu)) = m->ebx;	/* 46a9d8: mov dword ptr [eax + 0xc], ebx */
L_46a9db:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 46a9db: mov eax, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46a9df: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->edi + 0x10u));	/* 46a9e3: mov ecx, dword ptr [edi + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46a9e6: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46a9e7: add edx, 0x70 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46a9ea: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 46a9ec: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 46a9f0: mov dword ptr [esp + 0x14], edx */
	if (m->sf != m->of) goto L_46a896;	/* 46a9f4: jl 0x46a896 */
L_46a9fa:
	m->edi = M32(m->esp); m->esp += 4;	/* 46a9fa: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46a9fb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46a9fc: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46a9fd: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x370u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46a9fe: add esp, 0x370 */
	m->esp += 4 + 12; return;	/* 46aa04: ret 0xc */
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
