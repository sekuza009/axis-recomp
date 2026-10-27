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

static void lift_464db0(X86 *m);

/* model_loadObjFormatFrom (0x464db0), lifted by tools/lift.py */
static void lift_464db0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x2d4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464db0: sub esp, 0x2d4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 464db6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 464db7: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464db8: push esi */
	m->esi = m->ecx;	/* 464db9: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 464dbb: push edi */
	M32((DWORD)(m->esp + 0x40u)) = m->esi;	/* 464dbc: mov dword ptr [esp + 0x40], esi */
	m->esp -= 4; M32(m->esp) = 0x464dc5u; native_call(m, 0x464bc0u);	/* 464dc0: call 0x464bc0 */
	m->eax = M32((DWORD)(m->esp + 0x2e8u));	/* 464dc5: mov eax, dword ptr [esp + 0x2e8] */
	m->ecx = (DWORD)(m->esp + 0x6cu);	/* 464dcc: lea ecx, [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 464dd0: push eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 464dd1: xor edi, edi */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 464dd3: push 0x100 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 464dd8: push ecx */
	M32((DWORD)(m->esi + 0x10u)) = m->edi;	/* 464dd9: mov dword ptr [esi + 0x10], edi */
	M32((DWORD)(m->esp + 0x2cu)) = m->edi;	/* 464ddc: mov dword ptr [esp + 0x2c], edi */
	M32((DWORD)(m->esp + 0x38u)) = m->edi;	/* 464de0: mov dword ptr [esp + 0x38], edi */
	M32((DWORD)(m->esp + 0x30u)) = m->edi;	/* 464de4: mov dword ptr [esp + 0x30], edi */
	m->esp -= 4; M32(m->esp) = 0x464dedu; native_call(m, 0x49ecd7u);	/* 464de8: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464ded: add esp, 0xc */
	m->ebx = 0x2u;	/* 464df0: mov ebx, 2 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464df5: test eax, eax */
	if (m->zf) goto L_465068;	/* 464df7: je 0x465068 */
L_464dfd:
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 464dfd: lea edx, [esp + 0x6c] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 464e01: push 0x4ad5dc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 464e06: push edx */
	m->esp -= 4; M32(m->esp) = 0x464e0cu; native_call(m, 0x49ec3bu);	/* 464e07: call 0x49ec3b */
	m->edi = m->eax;	/* 464e0c: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464e0e: add esp, 8 */
	m->ebp = 0x4c4c64u;	/* 464e11: mov ebp, 0x4c4c64 */
	m->ecx = m->edi;	/* 464e16: mov ecx, edi */
L_464e18:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 464e18: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464e1a: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464e1c: cmp al, byte ptr [ebp] */
	if (!m->zf) goto L_464e3b;	/* 464e1f: jne 0x464e3b */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464e21: test dl, dl */
	if (m->zf) goto L_464e37;	/* 464e23: je 0x464e37 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 464e25: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464e28: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464e2a: cmp al, byte ptr [ebp + 1] */
	if (!m->zf) goto L_464e3b;	/* 464e2d: jne 0x464e3b */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 464e2f: add ecx, ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 464e31: add ebp, ebx */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464e33: test dl, dl */
	if (!m->zf) goto L_464e18;	/* 464e35: jne 0x464e18 */
L_464e37:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464e37: xor ecx, ecx */
	goto L_464e40;	/* 464e39: jmp 0x464e40 */
L_464e3b:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464e3b: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464e3d: sbb ecx, -1 */
L_464e40:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464e40: test ecx, ecx */
	if (!m->zf) goto L_464e4c;	/* 464e42: jne 0x464e4c */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x10u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x10u)) = r_; }	/* 464e44: inc dword ptr [esi + 0x10] */
	goto L_465044;	/* 464e47: jmp 0x465044 */
L_464e4c:
	m->ebp = 0x4c4c60u;	/* 464e4c: mov ebp, 0x4c4c60 */
	m->ecx = m->edi;	/* 464e51: mov ecx, edi */
L_464e53:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 464e53: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464e55: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464e57: cmp al, byte ptr [ebp] */
	if (!m->zf) goto L_464e76;	/* 464e5a: jne 0x464e76 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464e5c: test dl, dl */
	if (m->zf) goto L_464e72;	/* 464e5e: je 0x464e72 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 464e60: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464e63: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464e65: cmp al, byte ptr [ebp + 1] */
	if (!m->zf) goto L_464e76;	/* 464e68: jne 0x464e76 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 464e6a: add ecx, ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 464e6c: add ebp, ebx */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464e6e: test dl, dl */
	if (!m->zf) goto L_464e53;	/* 464e70: jne 0x464e53 */
L_464e72:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464e72: xor ecx, ecx */
	goto L_464e7b;	/* 464e74: jmp 0x464e7b */
L_464e76:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464e76: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464e78: sbb ecx, -1 */
L_464e7b:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464e7b: test ecx, ecx */
	if (!m->zf) goto L_464e88;	/* 464e7d: jne 0x464e88 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x24u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esp + 0x24u)) = r_; }	/* 464e7f: inc dword ptr [esp + 0x24] */
	goto L_465044;	/* 464e83: jmp 0x465044 */
L_464e88:
	m->ebp = 0x4c4c5cu;	/* 464e88: mov ebp, 0x4c4c5c */
	m->ecx = m->edi;	/* 464e8d: mov ecx, edi */
L_464e8f:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 464e8f: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464e91: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464e93: cmp al, byte ptr [ebp] */
	if (!m->zf) goto L_464eb2;	/* 464e96: jne 0x464eb2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464e98: test dl, dl */
	if (m->zf) goto L_464eae;	/* 464e9a: je 0x464eae */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 464e9c: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464e9f: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464ea1: cmp al, byte ptr [ebp + 1] */
	if (!m->zf) goto L_464eb2;	/* 464ea4: jne 0x464eb2 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 464ea6: add ecx, ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 464ea8: add ebp, ebx */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464eaa: test dl, dl */
	if (!m->zf) goto L_464e8f;	/* 464eac: jne 0x464e8f */
L_464eae:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464eae: xor ecx, ecx */
	goto L_464eb7;	/* 464eb0: jmp 0x464eb7 */
L_464eb2:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464eb2: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464eb4: sbb ecx, -1 */
L_464eb7:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464eb7: test ecx, ecx */
	if (!m->zf) goto L_464ec4;	/* 464eb9: jne 0x464ec4 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x2cu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esp + 0x2cu)) = r_; }	/* 464ebb: inc dword ptr [esp + 0x2c] */
	goto L_465044;	/* 464ebf: jmp 0x465044 */
L_464ec4:
	m->ebp = 0x4c4c58u;	/* 464ec4: mov ebp, 0x4c4c58 */
	m->ecx = m->edi;	/* 464ec9: mov ecx, edi */
L_464ecb:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 464ecb: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464ecd: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464ecf: cmp al, byte ptr [ebp] */
	if (!m->zf) goto L_464eee;	/* 464ed2: jne 0x464eee */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464ed4: test dl, dl */
	if (m->zf) goto L_464eea;	/* 464ed6: je 0x464eea */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 464ed8: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464edb: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464edd: cmp al, byte ptr [ebp + 1] */
	if (!m->zf) goto L_464eee;	/* 464ee0: jne 0x464eee */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 464ee2: add ecx, ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 464ee4: add ebp, ebx */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464ee6: test dl, dl */
	if (!m->zf) goto L_464ecb;	/* 464ee8: jne 0x464ecb */
L_464eea:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464eea: xor ecx, ecx */
	goto L_464ef3;	/* 464eec: jmp 0x464ef3 */
L_464eee:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464eee: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464ef0: sbb ecx, -1 */
L_464ef3:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464ef3: test ecx, ecx */
	if (!m->zf) goto L_464f00;	/* 464ef5: jne 0x464f00 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esp + 0x20u)) = r_; }	/* 464ef7: inc dword ptr [esp + 0x20] */
	goto L_465044;	/* 464efb: jmp 0x465044 */
L_464f00:
	m->ebp = 0x4c4c54u;	/* 464f00: mov ebp, 0x4c4c54 */
	m->eax = m->edi;	/* 464f05: mov eax, edi */
L_464f07:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 464f07: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 464f09: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464f0b: cmp dl, byte ptr [ebp] */
	if (!m->zf) goto L_464f2a;	/* 464f0e: jne 0x464f2a */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464f10: test cl, cl */
	if (m->zf) goto L_464f26;	/* 464f12: je 0x464f26 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 464f14: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 464f17: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464f19: cmp dl, byte ptr [ebp + 1] */
	if (!m->zf) goto L_464f2a;	/* 464f1c: jne 0x464f2a */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 464f1e: add eax, ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 464f20: add ebp, ebx */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464f22: test cl, cl */
	if (!m->zf) goto L_464f07;	/* 464f24: jne 0x464f07 */
L_464f26:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464f26: xor eax, eax */
	goto L_464f2f;	/* 464f28: jmp 0x464f2f */
L_464f2a:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 464f2a: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 464f2c: sbb eax, -1 */
L_464f2f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464f2f: test eax, eax */
	if (!m->zf) goto L_465044;	/* 464f31: jne 0x465044 */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 464f37: push 0x4b4310 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 464f3c: push eax */
	m->esp -= 4; M32(m->esp) = 0x464f42u; native_call(m, 0x49ec3bu);	/* 464f3d: call 0x49ec3b */
	m->edi = m->eax;	/* 464f42: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464f44: add esp, 8 */
	m->ebp = 0x4b1328u;	/* 464f47: mov ebp, 0x4b1328 */
	m->ecx = m->edi;	/* 464f4c: mov ecx, edi */
L_464f4e:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 464f4e: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464f50: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464f52: cmp al, byte ptr [ebp] */
	if (!m->zf) goto L_464f71;	/* 464f55: jne 0x464f71 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464f57: test dl, dl */
	if (m->zf) goto L_464f6d;	/* 464f59: je 0x464f6d */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 464f5b: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 464f5e: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464f60: cmp al, byte ptr [ebp + 1] */
	if (!m->zf) goto L_464f71;	/* 464f63: jne 0x464f71 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 464f65: add ecx, ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 464f67: add ebp, ebx */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 464f69: test dl, dl */
	if (!m->zf) goto L_464f4e;	/* 464f6b: jne 0x464f4e */
L_464f6d:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464f6d: xor ecx, ecx */
	goto L_464f76;	/* 464f6f: jmp 0x464f76 */
L_464f71:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464f71: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 464f73: sbb ecx, -1 */
L_464f76:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464f76: test ecx, ecx */
	if (!m->zf) goto L_464fa5;	/* 464f78: jne 0x464fa5 */
	m->ecx = M32((DWORD)(m->esp + 0x2e8u));	/* 464f7a: mov ecx, dword ptr [esp + 0x2e8] */
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 464f81: lea edx, [esp + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 464f85: push ecx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 464f86: push 0x100 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 464f8b: push edx */
	m->esp -= 4; M32(m->esp) = 0x464f91u; native_call(m, 0x49ecd7u);	/* 464f8c: call 0x49ecd7 */
	m->eax = (DWORD)(m->esp + 0x78u);	/* 464f91: lea eax, [esp + 0x78] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 464f95: push 0x4b4310 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 464f9a: push eax */
	m->esp -= 4; M32(m->esp) = 0x464fa0u; native_call(m, 0x49ec3bu);	/* 464f9b: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464fa0: add esp, 0x14 */
	m->edi = m->eax;	/* 464fa3: mov edi, eax */
L_464fa5:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464fa5: test edi, edi */
	if (!m->zf) goto L_464fc0;	/* 464fa7: jne 0x464fc0 */
	m->ecx = (DWORD)(m->esp + 0x6cu);	/* 464fa9: lea ecx, [esp + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 464fad: push ecx */
	{ DWORD v_ = 0x4c4c20u; m->esp -= 4; M32(m->esp) = v_; }	/* 464fae: push 0x4c4c20 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 464fb3: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x464fbdu; native_call(m, 0x46c710u);	/* 464fb8: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464fbd: add esp, 0xc */
L_464fc0:
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 464fc0: push 0x4b4310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 464fc5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x464fccu; native_call(m, 0x49ec3bu);	/* 464fc7: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464fcc: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464fcf: test eax, eax */
	if (!m->zf) goto L_464fea;	/* 464fd1: jne 0x464fea */
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 464fd3: lea edx, [esp + 0x6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 464fd7: push edx */
	{ DWORD v_ = 0x4c4c20u; m->esp -= 4; M32(m->esp) = v_; }	/* 464fd8: push 0x4c4c20 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 464fdd: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x464fe7u; native_call(m, 0x46c710u);	/* 464fe2: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464fe7: add esp, 0xc */
L_464fea:
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 464fea: push 0x4b4310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 464fef: push 0 */
	m->esp -= 4; M32(m->esp) = 0x464ff6u; native_call(m, 0x49ec3bu);	/* 464ff1: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464ff6: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464ff9: test eax, eax */
	if (!m->zf) goto L_465014;	/* 464ffb: jne 0x465014 */
	m->eax = (DWORD)(m->esp + 0x6cu);	/* 464ffd: lea eax, [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465001: push eax */
	{ DWORD v_ = 0x4c4c20u; m->esp -= 4; M32(m->esp) = v_; }	/* 465002: push 0x4c4c20 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 465007: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x465011u; native_call(m, 0x46c710u);	/* 46500c: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465011: add esp, 0xc */
L_465014:
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 465014: push 0x4b4310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465019: push 0 */
	m->esp -= 4; M32(m->esp) = 0x465020u; native_call(m, 0x49ec3bu);	/* 46501b: call 0x49ec3b */
	m->ecx = M32((DWORD)(m->esi + 0x18u));	/* 465020: mov ecx, dword ptr [esi + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465023: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465026: test eax, eax */
	if (!m->zf) goto L_465036;	/* 465028: jne 0x465036 */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 46502a: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46502d: add ecx, 3 */
	M32((DWORD)(m->esi + 0x18u)) = m->ecx;	/* 465030: mov dword ptr [esi + 0x18], ecx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 465033: inc eax */
	goto L_465041;	/* 465034: jmp 0x465041 */
L_465036:
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 465036: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = 0x6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465039: add ecx, 6 */
	M32((DWORD)(m->esi + 0x18u)) = m->ecx;	/* 46503c: mov dword ptr [esi + 0x18], ecx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46503f: add eax, ebx */
L_465041:
	M32((DWORD)(m->esi + 0x1cu)) = m->eax;	/* 465041: mov dword ptr [esi + 0x1c], eax */
L_465044:
	m->ecx = M32((DWORD)(m->esp + 0x2e8u));	/* 465044: mov ecx, dword ptr [esp + 0x2e8] */
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 46504b: lea edx, [esp + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46504f: push ecx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 465050: push 0x100 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 465055: push edx */
	m->esp -= 4; M32(m->esp) = 0x46505bu; native_call(m, 0x49ecd7u);	/* 465056: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46505b: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46505e: test eax, eax */
	if (!m->zf) goto L_464dfd;	/* 465060: jne 0x464dfd */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 465066: xor edi, edi */
L_465068:
	m->ecx = M32((DWORD)(m->esi + 0x10u));	/* 465068: mov ecx, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46506b: cmp ecx, edi */
	if (m->zf || m->sf != m->of) goto L_466112;	/* 46506d: jle 0x466112 */
	m->eax = M32((DWORD)(m->esi + 0x18u));	/* 465073: mov eax, dword ptr [esi + 0x18] */
	m->ebx = M32((DWORD)(m->esi + 0x1cu));	/* 465076: mov ebx, dword ptr [esi + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 465079: mov edx, dword ptr [esp + 0x24] */
	m->ebp = M32((DWORD)(m->esp + 0x2ecu));	/* 46507d: mov ebp, dword ptr [esp + 0x2ec] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465084: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465087: add eax, ebx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465089: add eax, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46508b: shl ecx, 7 */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 46508e: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 465091: lea ecx, [ecx + eax*4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 465094: mov eax, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esi + 0x4u)) = m->ecx;	/* 465098: mov dword ptr [esi + 4], ecx */
	m->ebx = (DWORD)(m->eax + m->edx*1 + 0x0u);	/* 46509b: lea ebx, [eax + edx] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 46509e: mov eax, dword ptr [esp + 0x20] */
	m->ebx = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 4650a2: lea ebx, [ebx + ebx*2] */
	m->edi = (DWORD)(m->eax*8 + 0x0u);	/* 4650a5: lea edi, [eax*8] */
	{ DWORD a_ = m->ebx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 4650ac: shl ebx, 2 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4650af: test ebp, ebp */
	m->eax = (DWORD)(m->edi + m->ebx*1 + 0x0u);	/* 4650b1: lea eax, [edi + ebx] */
	if (!m->zf) goto L_4651a8;	/* 4650b4: jne 0x4651a8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4650ba: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4650c0u; native_call(m, 0x49f1aau);	/* 4650bb: call 0x49f1aa */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4650c0: xor ebx, ebx */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4650c2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4650c5: cmp eax, ebx */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 4650c7: mov dword ptr [esi + 8], eax */
	if (!m->zf) goto L_4650e2;	/* 4650ca: jne 0x4650e2 */
	m->ecx = M32((DWORD)(m->esi + 0x4u));	/* 4650cc: mov ecx, dword ptr [esi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4650cf: push ecx */
	{ DWORD v_ = 0x4c4becu; m->esp -= 4; M32(m->esp) = v_; }	/* 4650d0: push 0x4c4bec */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 4650d5: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x4650dfu; native_call(m, 0x46c710u);	/* 4650da: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4650df: add esp, 0xc */
L_4650e2:
	m->ebp = M32((DWORD)(m->esp + 0x24u));	/* 4650e2: mov ebp, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esi + 0xcu)) = 0x1u;	/* 4650e6: mov dword ptr [esi + 0xc], 1 */
	m->edx = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 4650ed: lea edx, [ebp + ebp*2] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4650f1: shl edx, 2 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4650f4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4650fau; native_call(m, 0x49f1aau);	/* 4650f5: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4650fa: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4650fd: cmp eax, ebx */
	if (m->zf) goto L_46510a;	/* 4650ff: je 0x46510a */
	m->ecx = (DWORD)(m->ebp + 0xffffffffu);	/* 465101: lea ecx, [ebp - 1] */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 465104: mov dword ptr [esp + 0x30], ecx */
	goto L_46510c;	/* 465108: jmp 0x46510c */
L_46510a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46510a: xor eax, eax */
L_46510c:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46510c: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 46510e: mov dword ptr [esp + 0x1c], eax */
	if (!m->zf) goto L_465127;	/* 465112: jne 0x465127 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 465114: push ebp */
	{ DWORD v_ = 0x4c4bb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 465115: push 0x4c4bb4 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 46511a: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x465124u; native_call(m, 0x46c710u);	/* 46511f: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465124: add esp, 0xc */
L_465127:
	m->ebp = M32((DWORD)(m->esp + 0x2cu));	/* 465127: mov ebp, dword ptr [esp + 0x2c] */
	m->edx = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 46512b: lea edx, [ebp + ebp*2] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46512f: shl edx, 2 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 465132: push edx */
	m->esp -= 4; M32(m->esp) = 0x465138u; native_call(m, 0x49f1aau);	/* 465133: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465138: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46513b: cmp eax, ebx */
	if (m->zf) goto L_465148;	/* 46513d: je 0x465148 */
	m->ecx = (DWORD)(m->ebp + 0xffffffffu);	/* 46513f: lea ecx, [ebp - 1] */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 465142: mov dword ptr [esp + 0x30], ecx */
	goto L_46514a;	/* 465146: jmp 0x46514a */
L_465148:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 465148: xor eax, eax */
L_46514a:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46514a: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 46514c: mov dword ptr [esp + 0x18], eax */
	if (!m->zf) goto L_465165;	/* 465150: jne 0x465165 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 465152: push ebp */
	{ DWORD v_ = 0x4c4b78u; m->esp -= 4; M32(m->esp) = v_; }	/* 465153: push 0x4c4b78 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 465158: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x465162u; native_call(m, 0x46c710u);	/* 46515d: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465162: add esp, 0xc */
L_465165:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 465165: push edi */
	m->esp -= 4; M32(m->esp) = 0x46516bu; native_call(m, 0x49f1aau);	/* 465166: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46516b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46516e: cmp eax, ebx */
	if (m->zf) goto L_46517d;	/* 465170: je 0x46517d */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 465172: mov edx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 465176: dec edx */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 465177: mov dword ptr [esp + 0x30], edx */
	goto L_46517f;	/* 46517b: jmp 0x46517f */
L_46517d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46517d: xor eax, eax */
L_46517f:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46517f: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 465181: mov dword ptr [esp + 0x28], eax */
	if (!m->zf) goto L_46519e;	/* 465185: jne 0x46519e */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 465187: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46518b: push eax */
	{ DWORD v_ = 0x4c4b38u; m->esp -= 4; M32(m->esp) = v_; }	/* 46518c: push 0x4c4b38 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 465191: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x46519bu; native_call(m, 0x46c710u);	/* 465196: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46519b: add esp, 0xc */
L_46519e:
	M32((DWORD)(m->esp + 0x30u)) = 0x1u;	/* 46519e: mov dword ptr [esp + 0x30], 1 */
	goto L_4651f9;	/* 4651a6: jmp 0x4651f9 */
L_4651a8:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4651a8: add eax, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x2f0u));	/* 4651aa: mov ecx, dword ptr [esp + 0x2f0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4651b1: cmp ecx, eax */
	if (m->sf == m->of) goto L_4651cd;	/* 4651b3: jge 0x4651cd */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4651b5: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4651b6: push eax */
	{ DWORD v_ = 0x4c4b08u; m->esp -= 4; M32(m->esp) = v_; }	/* 4651b7: push 0x4c4b08 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 4651bc: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x4651c6u; native_call(m, 0x46c710u);	/* 4651c1: call 0x46c710 */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 4651c6: mov edx, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4651ca: add esp, 0x10 */
L_4651cd:
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 4651cd: mov eax, dword ptr [esi + 4] */
	m->edx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 4651d0: lea edx, [edx + edx*2] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4651d3: xor edi, edi */
	M32((DWORD)(m->esi + 0x8u)) = m->ebp;	/* 4651d5: mov dword ptr [esi + 8], ebp */
	m->ecx = (DWORD)(m->eax + m->ebp*1 + 0x0u);	/* 4651d8: lea ecx, [eax + ebp] */
	M32((DWORD)(m->esi + 0xcu)) = m->edi;	/* 4651db: mov dword ptr [esi + 0xc], edi */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 4651de: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 4651e2: lea ecx, [eax + edx*4] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4651e5: add eax, ebx */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4651e7: add ecx, ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4651e9: add eax, ebp */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 4651eb: mov dword ptr [esp + 0x18], ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4651ef: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esp + 0x30u)) = m->edi;	/* 4651f3: mov dword ptr [esp + 0x30], edi */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4651f7: xor ebx, ebx */
L_4651f9:
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 4651f9: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4651fc: xor ecx, ecx */
	M32((DWORD)(m->esi + 0x14u)) = m->eax;	/* 4651fe: mov dword ptr [esi + 0x14], eax */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 465201: mov eax, dword ptr [esi + 0x10] */
	m->edi = m->eax;	/* 465204: mov edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 465206: shl edi, 7 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 465209: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 46520b: mov dword ptr [esp + 0x10], edi */
	if (m->zf || m->sf != m->of) goto L_46523f;	/* 46520f: jle 0x46523f */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 465211: xor edx, edx */
L_465213:
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 465213: mov eax, dword ptr [esi + 0x14] */
	M32((DWORD)(m->eax + m->edx*1 + 0x0u)) = m->ebx;	/* 465216: mov dword ptr [eax + edx], ebx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465219: add eax, edx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 46521b: inc ecx */
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46521c: add edx, 0x80 */
	M32((DWORD)(m->eax + 0x44u)) = m->ebx;	/* 465222: mov dword ptr [eax + 0x44], ebx */
	M32((DWORD)(m->eax + 0x4cu)) = m->ebx;	/* 465225: mov dword ptr [eax + 0x4c], ebx */
	M32((DWORD)(m->eax + 0x50u)) = m->ebx;	/* 465228: mov dword ptr [eax + 0x50], ebx */
	M32((DWORD)(m->eax + 0x54u)) = m->ebx;	/* 46522b: mov dword ptr [eax + 0x54], ebx */
	M32((DWORD)(m->eax + 0x58u)) = m->ebx;	/* 46522e: mov dword ptr [eax + 0x58], ebx */
	M32((DWORD)(m->eax + 0x5cu)) = m->ebx;	/* 465231: mov dword ptr [eax + 0x5c], ebx */
	M32((DWORD)(m->eax + 0x60u)) = m->ebx;	/* 465234: mov dword ptr [eax + 0x60], ebx */
	M32((DWORD)(m->eax + 0x64u)) = m->ebx;	/* 465237: mov dword ptr [eax + 0x64], ebx */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->esi + 0x10u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46523a: cmp ecx, dword ptr [esi + 0x10] */
	if (m->sf != m->of) goto L_465213;	/* 46523d: jl 0x465213 */
L_46523f:
	m->ebp = M32((DWORD)(m->esp + 0x2e8u));	/* 46523f: mov ebp, dword ptr [esp + 0x2e8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 465246: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 465247: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 465248: push ebp */
	m->esp -= 4; M32(m->esp) = 0x46524eu; native_call(m, 0x49e91eu);	/* 465249: call 0x49e91e */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46524e: push ebp */
	m->ecx = (DWORD)(m->esp + 0x7cu);	/* 46524f: lea ecx, [esp + 0x7c] */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 465253: push 0x100 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 465258: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46525eu; native_call(m, 0x49ecd7u);	/* 465259: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46525e: add esp, 0x18 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465261: test eax, eax */
	if (m->zf) goto L_46544b;	/* 465263: je 0x46544b */
	M32((DWORD)(m->esp + 0x14u)) = 0xffffff80u;	/* 465269: mov dword ptr [esp + 0x14], 0xffffff80 */
L_465271:
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 465271: lea edx, [esp + 0x6c] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 465275: push 0x4ad5dc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46527a: push edx */
	m->esp -= 4; M32(m->esp) = 0x465280u; native_call(m, 0x49ec3bu);	/* 46527b: call 0x49ec3b */
	m->edi = m->eax;	/* 465280: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465282: add esp, 8 */
	m->ebp = 0x4c4c64u;	/* 465285: mov ebp, 0x4c4c64 */
	m->ecx = m->edi;	/* 46528a: mov ecx, edi */
L_46528c:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 46528c: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 46528e: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465290: cmp al, byte ptr [ebp] */
	if (!m->zf) goto L_4652b1;	/* 465293: jne 0x4652b1 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465295: test dl, dl */
	if (m->zf) goto L_4652ad;	/* 465297: je 0x4652ad */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 465299: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 46529c: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46529e: cmp al, byte ptr [ebp + 1] */
	if (!m->zf) goto L_4652b1;	/* 4652a1: jne 0x4652b1 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4652a3: add ecx, 2 */
	{ DWORD a_ = m->ebp, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4652a6: add ebp, 2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4652a9: test dl, dl */
	if (!m->zf) goto L_46528c;	/* 4652ab: jne 0x46528c */
L_4652ad:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4652ad: xor ecx, ecx */
	goto L_4652b6;	/* 4652af: jmp 0x4652b6 */
L_4652b1:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 4652b1: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 4652b3: sbb ecx, -1 */
L_4652b6:
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4652b6: cmp ecx, ebx */
	if (!m->zf) goto L_4652d7;	/* 4652b8: jne 0x4652d7 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4652ba: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esi + 0x14u));	/* 4652be: mov ecx, dword ptr [esi + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4652c1: add eax, 0x80 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4652c6: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->ecx + m->eax*1 + 0x60u)) = 0x1u;	/* 4652ca: mov dword ptr [ecx + eax + 0x60], 1 */
	goto L_465425;	/* 4652d2: jmp 0x465425 */
L_4652d7:
	m->ebp = 0x4c4c54u;	/* 4652d7: mov ebp, 0x4c4c54 */
	m->eax = m->edi;	/* 4652dc: mov eax, edi */
L_4652de:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4652de: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4652e0: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4652e2: cmp dl, byte ptr [ebp] */
	if (!m->zf) goto L_465303;	/* 4652e5: jne 0x465303 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4652e7: test cl, cl */
	if (m->zf) goto L_4652ff;	/* 4652e9: je 0x4652ff */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4652eb: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4652ee: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4652f0: cmp dl, byte ptr [ebp + 1] */
	if (!m->zf) goto L_465303;	/* 4652f3: jne 0x465303 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4652f5: add eax, 2 */
	{ DWORD a_ = m->ebp, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4652f8: add ebp, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4652fb: test cl, cl */
	if (!m->zf) goto L_4652de;	/* 4652fd: jne 0x4652de */
L_4652ff:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4652ff: xor eax, eax */
	goto L_465308;	/* 465301: jmp 0x465308 */
L_465303:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 465303: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 465305: sbb eax, -1 */
L_465308:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 465308: cmp eax, ebx */
	if (!m->zf) goto L_465425;	/* 46530a: jne 0x465425 */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 465310: push 0x4b4310 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 465315: push ebx */
	m->esp -= 4; M32(m->esp) = 0x46531bu; native_call(m, 0x49ec3bu);	/* 465316: call 0x49ec3b */
	m->edi = m->eax;	/* 46531b: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46531d: add esp, 8 */
	m->ebp = 0x4b1328u;	/* 465320: mov ebp, 0x4b1328 */
	m->ecx = m->edi;	/* 465325: mov ecx, edi */
L_465327:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 465327: mov al, byte ptr [ecx] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 465329: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46532b: cmp al, byte ptr [ebp] */
	if (!m->zf) goto L_46534c;	/* 46532e: jne 0x46534c */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465330: test dl, dl */
	if (m->zf) goto L_465348;	/* 465332: je 0x465348 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 465334: mov al, byte ptr [ecx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 465337: mov dl, al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = M8((DWORD)(m->ebp + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465339: cmp al, byte ptr [ebp + 1] */
	if (!m->zf) goto L_46534c;	/* 46533c: jne 0x46534c */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46533e: add ecx, 2 */
	{ DWORD a_ = m->ebp, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 465341: add ebp, 2 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465344: test dl, dl */
	if (!m->zf) goto L_465327;	/* 465346: jne 0x465327 */
L_465348:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465348: xor ecx, ecx */
	goto L_465351;	/* 46534a: jmp 0x465351 */
L_46534c:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46534c: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46534e: sbb ecx, -1 */
L_465351:
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 465351: cmp ecx, ebx */
	if (!m->zf) goto L_465380;	/* 465353: jne 0x465380 */
	m->ecx = M32((DWORD)(m->esp + 0x2e8u));	/* 465355: mov ecx, dword ptr [esp + 0x2e8] */
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 46535c: lea edx, [esp + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 465360: push ecx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 465361: push 0x100 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 465366: push edx */
	m->esp -= 4; M32(m->esp) = 0x46536cu; native_call(m, 0x49ecd7u);	/* 465367: call 0x49ecd7 */
	m->eax = (DWORD)(m->esp + 0x78u);	/* 46536c: lea eax, [esp + 0x78] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 465370: push 0x4b4310 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465375: push eax */
	m->esp -= 4; M32(m->esp) = 0x46537bu; native_call(m, 0x49ec3bu);	/* 465376: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46537b: add esp, 0x14 */
	m->edi = m->eax;	/* 46537e: mov edi, eax */
L_465380:
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 465380: cmp edi, ebx */
	if (!m->zf) goto L_46539b;	/* 465382: jne 0x46539b */
	m->ecx = (DWORD)(m->esp + 0x6cu);	/* 465384: lea ecx, [esp + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 465388: push ecx */
	{ DWORD v_ = 0x4c4c20u; m->esp -= 4; M32(m->esp) = v_; }	/* 465389: push 0x4c4c20 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 46538e: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x465398u; native_call(m, 0x46c710u);	/* 465393: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465398: add esp, 0xc */
L_46539b:
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 46539b: push 0x4b4310 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4653a0: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4653a6u; native_call(m, 0x49ec3bu);	/* 4653a1: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4653a6: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4653a9: test eax, eax */
	if (!m->zf) goto L_4653c4;	/* 4653ab: jne 0x4653c4 */
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 4653ad: lea edx, [esp + 0x6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4653b1: push edx */
	{ DWORD v_ = 0x4c4c20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4653b2: push 0x4c4c20 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 4653b7: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x4653c1u; native_call(m, 0x46c710u);	/* 4653bc: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4653c1: add esp, 0xc */
L_4653c4:
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 4653c4: push 0x4b4310 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4653c9: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4653cfu; native_call(m, 0x49ec3bu);	/* 4653ca: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4653cf: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4653d2: test eax, eax */
	if (!m->zf) goto L_4653ed;	/* 4653d4: jne 0x4653ed */
	m->eax = (DWORD)(m->esp + 0x6cu);	/* 4653d6: lea eax, [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4653da: push eax */
	{ DWORD v_ = 0x4c4c20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4653db: push 0x4c4c20 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 4653e0: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x4653eau; native_call(m, 0x46c710u);	/* 4653e5: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4653ea: add esp, 0xc */
L_4653ed:
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 4653ed: push 0x4b4310 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4653f2: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4653f8u; native_call(m, 0x49ec3bu);	/* 4653f3: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4653f8: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4653fb: test eax, eax */
	if (!m->zf) goto L_465413;	/* 4653fd: jne 0x465413 */
	m->ecx = M32((DWORD)(m->esi + 0x14u));	/* 4653ff: mov ecx, dword ptr [esi + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 465402: mov edx, dword ptr [esp + 0x14] */
	m->eax = (DWORD)(m->ecx + m->edx*1 + 0x4cu);	/* 465406: lea eax, [ecx + edx + 0x4c] */
	m->ecx = M32((DWORD)(m->ecx + m->edx*1 + 0x4cu));	/* 46540a: mov ecx, dword ptr [ecx + edx + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46540e: add ecx, 3 */
	goto L_465423;	/* 465411: jmp 0x465423 */
L_465413:
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 465413: mov eax, dword ptr [esi + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 465416: mov ecx, dword ptr [esp + 0x14] */
	m->eax = (DWORD)(m->eax + m->ecx*1 + 0x4cu);	/* 46541a: lea eax, [eax + ecx + 0x4c] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 46541e: mov ecx, dword ptr [eax] */
	{ DWORD a_ = m->ecx, b_ = 0x6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465420: add ecx, 6 */
L_465423:
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 465423: mov dword ptr [eax], ecx */
L_465425:
	m->edx = M32((DWORD)(m->esp + 0x2e8u));	/* 465425: mov edx, dword ptr [esp + 0x2e8] */
	m->eax = (DWORD)(m->esp + 0x6cu);	/* 46542c: lea eax, [esp + 0x6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 465430: push edx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 465431: push 0x100 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465436: push eax */
	m->esp -= 4; M32(m->esp) = 0x46543cu; native_call(m, 0x49ecd7u);	/* 465437: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46543c: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46543f: test eax, eax */
	if (!m->zf) goto L_465271;	/* 465441: jne 0x465271 */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 465447: mov edi, dword ptr [esp + 0x10] */
L_46544b:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46544b: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 46544e: xor ebp, ebp */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 465450: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465452: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_465501;	/* 465454: jle 0x465501 */
	M32((DWORD)(m->esp + 0x14u)) = m->ebx;	/* 46545a: mov dword ptr [esp + 0x14], ebx */
	goto L_465464;	/* 46545e: jmp 0x465464 */
L_465460:
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 465460: mov edi, dword ptr [esp + 0x10] */
L_465464:
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 465464: mov eax, dword ptr [esi + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 465467: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esi + 0x8u));	/* 46546b: mov edx, dword ptr [esi + 8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46546e: add eax, ecx */
	m->ecx = m->edi;	/* 465470: mov ecx, edi */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465472: add ecx, edx */
	M32((DWORD)(m->eax + 0x50u)) = m->ecx;	/* 465474: mov dword ptr [eax + 0x50], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4cu));	/* 465477: mov ecx, dword ptr [eax + 0x4c] */
	m->edx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 46547a: lea edx, [ecx + ecx*2] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46547d: shl edx, 2 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 465480: add edi, edx */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 465482: mov dword ptr [esp + 0x10], edi */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->esi + 0x8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 465486: add edi, dword ptr [esi + 8] */
	M32((DWORD)(m->eax + 0x54u)) = m->edi;	/* 465489: mov dword ptr [eax + 0x54], edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 46548c: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 465490: add edi, edx */
	m->edx = m->edi;	/* 465492: mov edx, edi */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esi + 0x8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465494: add edx, dword ptr [esi + 8] */
	M32((DWORD)(m->eax + 0x58u)) = m->edx;	/* 465497: mov dword ptr [eax + 0x58], edx */
	m->edx = (DWORD)(m->edi + m->ecx*4 + 0x0u);	/* 46549a: lea edx, [edi + ecx*4] */
	m->edi = m->edx;	/* 46549d: mov edi, edx */
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(m->esi + 0x8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46549f: add edi, dword ptr [esi + 8] */
	m->edx = (DWORD)(m->edx + m->ecx*8 + 0x0u);	/* 4654a2: lea edx, [edx + ecx*8] */
	M32((DWORD)(m->eax + 0x48u)) = m->ebp;	/* 4654a5: mov dword ptr [eax + 0x48], ebp */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4654a8: add ebp, ecx */
	M32((DWORD)(m->eax + 0x5cu)) = m->edi;	/* 4654aa: mov dword ptr [eax + 0x5c], edi */
	M32((DWORD)(m->eax + 0x60u)) = 0x1u;	/* 4654ad: mov dword ptr [eax + 0x60], 1 */
	m->edi = M32((DWORD)(m->esi + 0x8u));	/* 4654b4: mov edi, dword ptr [esi + 8] */
	m->ecx = m->edx;	/* 4654b7: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4654b9: add ecx, edi */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4654bb: add edx, 0xc */
	M32((DWORD)(m->eax + 0x64u)) = m->ecx;	/* 4654be: mov dword ptr [eax + 0x64], ecx */
	M32((DWORD)(m->ecx + 0x0u)) = 0x4u;	/* 4654c1: mov dword ptr [ecx], 4 */
	m->ecx = M32((DWORD)(m->eax + 0x64u));	/* 4654c7: mov ecx, dword ptr [eax + 0x64] */
	m->edi = M32((DWORD)(m->eax + 0x4cu));	/* 4654ca: mov edi, dword ptr [eax + 0x4c] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 4654cd: mov dword ptr [ecx + 4], edi */
	m->edi = M32((DWORD)(m->esi + 0x8u));	/* 4654d0: mov edi, dword ptr [esi + 8] */
	m->ecx = m->edx;	/* 4654d3: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4654d5: add ecx, edi */
	m->edi = M32((DWORD)(m->eax + 0x64u));	/* 4654d7: mov edi, dword ptr [eax + 0x64] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4654da: inc ebx */
	M32((DWORD)(m->edi + 0x8u)) = m->ecx;	/* 4654db: mov dword ptr [edi + 8], ecx */
	m->eax = M32((DWORD)(m->eax + 0x4cu));	/* 4654de: mov eax, dword ptr [eax + 0x4c] */
	m->ecx = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 4654e1: lea ecx, [edx + eax*4] */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 4654e4: mov eax, dword ptr [esi + 0x10] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 4654e7: mov dword ptr [esp + 0x10], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4654eb: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4654ef: add ecx, 0x80 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4654f5: cmp ebx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 4654f7: mov dword ptr [esp + 0x14], ecx */
	if (m->sf != m->of) goto L_465460;	/* 4654fb: jl 0x465460 */
L_465501:
	m->edi = M32((DWORD)(m->esp + 0x2e8u));	/* 465501: mov edi, dword ptr [esp + 0x2e8] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 465508: xor ebx, ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46550a: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46550b: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46550c: push edi */
	m->esp -= 4; M32(m->esp) = 0x465512u; native_call(m, 0x49e91eu);	/* 46550d: call 0x49e91e */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 465512: push edi */
	m->edx = (DWORD)(m->esp + 0x7cu);	/* 465513: lea edx, [esp + 0x7c] */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 465517: push 0x100 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46551c: push edx */
	M32((DWORD)(m->esp + 0x50u)) = m->ebx;	/* 46551d: mov dword ptr [esp + 0x50], ebx */
	m->esp -= 4; M32(m->esp) = 0x465526u; native_call(m, 0x49ecd7u);	/* 465521: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465526: add esp, 0x18 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465529: test eax, eax */
	if (m->zf) goto L_465f1b;	/* 46552b: je 0x465f1b */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 465531: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 465535: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 465539: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46553d: add ecx, 8 */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465540: add edx, 8 */
	M32((DWORD)(m->esp + 0x34u)) = m->ebx;	/* 465543: mov dword ptr [esp + 0x34], ebx */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 465547: mov dword ptr [esp + 0x44], eax */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 46554b: mov dword ptr [esp + 0x48], ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 46554f: mov dword ptr [esp + 0x3c], edx */
L_465553:
	{ DWORD a_ = M8((DWORD)(m->esp + 0x6cu)), b_ = 0x23u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465553: cmp byte ptr [esp + 0x6c], 0x23 */
	if (!m->zf) goto L_46559d;	/* 465558: jne 0x46559d */
	m->eax = (DWORD)(m->esp + 0x6eu);	/* 46555a: lea eax, [esp + 0x6e] */
L_46555e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xffffffffu))) & 0xff) << 0);	/* 46555e: mov dl, byte ptr [eax - 1] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465561: test dl, dl */
	if (m->zf) goto L_465ef5;	/* 465563: je 0x465ef5 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 465569: mov cl, byte ptr [eax] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46556b: test cl, cl */
	if (m->zf) goto L_465ef5;	/* 46556d: je 0x465ef5 */
	{ DWORD a_ = M8((DWORD)(m->eax + 0xfffffffeu)), b_ = 0x33u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465573: cmp byte ptr [eax - 2], 0x33 */
	if (!m->zf) goto L_465583;	/* 465577: jne 0x465583 */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = 0x44u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465579: cmp dl, 0x44 */
	if (!m->zf) goto L_465583;	/* 46557c: jne 0x465583 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x53u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46557e: cmp cl, 0x53 */
	if (m->zf) goto L_465590;	/* 465581: je 0x465590 */
L_465583:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xffffffffu))) & 0xff) << 0);	/* 465583: mov cl, byte ptr [eax - 1] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 465586: inc eax */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465587: test cl, cl */
	if (!m->zf) goto L_46555e;	/* 465589: jne 0x46555e */
	goto L_465ef5;	/* 46558b: jmp 0x465ef5 */
L_465590:
	M32((DWORD)(m->esp + 0x38u)) = 0x1u;	/* 465590: mov dword ptr [esp + 0x38], 1 */
	goto L_465ef5;	/* 465598: jmp 0x465ef5 */
L_46559d:
	m->eax = (DWORD)(m->esp + 0x6cu);	/* 46559d: lea eax, [esp + 0x6c] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4655a1: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4655a6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4655acu; native_call(m, 0x49ec3bu);	/* 4655a7: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4655ac: add esp, 8 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4655af: mov dword ptr [esp + 0x14], eax */
	m->ecx = 0x4c4c60u;	/* 4655b3: mov ecx, 0x4c4c60 */
	m->edi = m->eax;	/* 4655b8: mov edi, eax */
L_4655ba:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 4655ba: mov dl, byte ptr [edi] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4655bc: mov al, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4655be: cmp dl, byte ptr [ecx] */
	if (!m->zf) goto L_4655de;	/* 4655c0: jne 0x4655de */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4655c2: test al, al */
	if (m->zf) goto L_4655da;	/* 4655c4: je 0x4655da */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 4655c6: mov dl, byte ptr [edi + 1] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4655c9: mov al, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->ecx + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4655cb: cmp dl, byte ptr [ecx + 1] */
	if (!m->zf) goto L_4655de;	/* 4655ce: jne 0x4655de */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4655d0: add edi, 2 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4655d3: add ecx, 2 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4655d6: test al, al */
	if (!m->zf) goto L_4655ba;	/* 4655d8: jne 0x4655ba */
L_4655da:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4655da: xor eax, eax */
	goto L_4655e3;	/* 4655dc: jmp 0x4655e3 */
L_4655de:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4655de: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4655e0: sbb eax, -1 */
L_4655e3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4655e3: test eax, eax */
	if (!m->zf) goto L_465637;	/* 4655e5: jne 0x465637 */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4655e7: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4655ec: push eax */
	m->esp -= 4; M32(m->esp) = 0x4655f2u; native_call(m, 0x49ec3bu);	/* 4655ed: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4655f2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4655f8u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 4655f3: call 0x49fe7a */
	m->esi = M32((DWORD)(m->esp + 0x48u));	/* 4655f8: mov esi, dword ptr [esp + 0x48] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4655fc: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465601: push 0 */
	MF((DWORD)(m->esi + 0xfffffff8u)) = (float)ST(0); FPOP();	/* 465603: fstp dword ptr [esi - 8] */
	m->esp -= 4; M32(m->esp) = 0x46560bu; native_call(m, 0x49ec3bu);	/* 465606: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46560b: push eax */
	m->esp -= 4; M32(m->esp) = 0x465611u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 46560c: call 0x49fe7a */
	MF((DWORD)(m->esi + 0xfffffffcu)) = (float)ST(0); FPOP();	/* 465611: fstp dword ptr [esi - 4] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 465614: push 0x4b4310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465619: push 0 */
	m->esp -= 4; M32(m->esp) = 0x465620u; native_call(m, 0x49ec3bu);	/* 46561b: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465620: push eax */
	m->esp -= 4; M32(m->esp) = 0x465626u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 465621: call 0x49fe7a */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 465626: fstp dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465628: add esp, 0x24 */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46562b: add esi, 0xc */
	M32((DWORD)(m->esp + 0x3cu)) = m->esi;	/* 46562e: mov dword ptr [esp + 0x3c], esi */
	goto L_465ef5;	/* 465632: jmp 0x465ef5 */
L_465637:
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 465637: mov edi, dword ptr [esp + 0x14] */
	m->eax = 0x4c4c5cu;	/* 46563b: mov eax, 0x4c4c5c */
L_465640:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 465640: mov dl, byte ptr [edi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 465642: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->eax + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465644: cmp dl, byte ptr [eax] */
	if (!m->zf) goto L_465664;	/* 465646: jne 0x465664 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465648: test cl, cl */
	if (m->zf) goto L_465660;	/* 46564a: je 0x465660 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 46564c: mov dl, byte ptr [edi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46564f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->eax + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465651: cmp dl, byte ptr [eax + 1] */
	if (!m->zf) goto L_465664;	/* 465654: jne 0x465664 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 465656: add edi, 2 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465659: add eax, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46565c: test cl, cl */
	if (!m->zf) goto L_465640;	/* 46565e: jne 0x465640 */
L_465660:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 465660: xor eax, eax */
	goto L_465669;	/* 465662: jmp 0x465669 */
L_465664:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 465664: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 465666: sbb eax, -1 */
L_465669:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465669: test eax, eax */
	if (!m->zf) goto L_4656bd;	/* 46566b: jne 0x4656bd */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46566d: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465672: push eax */
	m->esp -= 4; M32(m->esp) = 0x465678u; native_call(m, 0x49ec3bu);	/* 465673: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465678: push eax */
	m->esp -= 4; M32(m->esp) = 0x46567eu; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 465679: call 0x49fe7a */
	m->esi = M32((DWORD)(m->esp + 0x54u));	/* 46567e: mov esi, dword ptr [esp + 0x54] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 465682: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465687: push 0 */
	MF((DWORD)(m->esi + 0xfffffff8u)) = (float)ST(0); FPOP();	/* 465689: fstp dword ptr [esi - 8] */
	m->esp -= 4; M32(m->esp) = 0x465691u; native_call(m, 0x49ec3bu);	/* 46568c: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465691: push eax */
	m->esp -= 4; M32(m->esp) = 0x465697u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 465692: call 0x49fe7a */
	MF((DWORD)(m->esi + 0xfffffffcu)) = (float)ST(0); FPOP();	/* 465697: fstp dword ptr [esi - 4] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 46569a: push 0x4b4310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46569f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4656a6u; native_call(m, 0x49ec3bu);	/* 4656a1: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4656a6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4656acu; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 4656a7: call 0x49fe7a */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 4656ac: fstp dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4656ae: add esp, 0x24 */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4656b1: add esi, 0xc */
	M32((DWORD)(m->esp + 0x48u)) = m->esi;	/* 4656b4: mov dword ptr [esp + 0x48], esi */
	goto L_465ef5;	/* 4656b8: jmp 0x465ef5 */
L_4656bd:
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 4656bd: mov edi, dword ptr [esp + 0x14] */
	m->eax = 0x4c4c58u;	/* 4656c1: mov eax, 0x4c4c58 */
L_4656c6:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 4656c6: mov dl, byte ptr [edi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4656c8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->eax + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4656ca: cmp dl, byte ptr [eax] */
	if (!m->zf) goto L_4656ea;	/* 4656cc: jne 0x4656ea */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4656ce: test cl, cl */
	if (m->zf) goto L_4656e6;	/* 4656d0: je 0x4656e6 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 4656d2: mov dl, byte ptr [edi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4656d5: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->eax + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4656d7: cmp dl, byte ptr [eax + 1] */
	if (!m->zf) goto L_4656ea;	/* 4656da: jne 0x4656ea */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4656dc: add edi, 2 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4656df: add eax, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4656e2: test cl, cl */
	if (!m->zf) goto L_4656c6;	/* 4656e4: jne 0x4656c6 */
L_4656e6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4656e6: xor eax, eax */
	goto L_4656ef;	/* 4656e8: jmp 0x4656ef */
L_4656ea:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4656ea: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4656ec: sbb eax, -1 */
L_4656ef:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4656ef: test eax, eax */
	if (!m->zf) goto L_46572e;	/* 4656f1: jne 0x46572e */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4656f3: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4656f8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4656feu; native_call(m, 0x49ec3bu);	/* 4656f9: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4656fe: push eax */
	m->esp -= 4; M32(m->esp) = 0x465704u; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 4656ff: call 0x49fe7a */
	m->esi = M32((DWORD)(m->esp + 0x50u));	/* 465704: mov esi, dword ptr [esp + 0x50] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 465708: push 0x4b4310 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46570d: push 0 */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 46570f: fstp dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x465716u; native_call(m, 0x49ec3bu);	/* 465711: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465716: push eax */
	m->esp -= 4; M32(m->esp) = 0x46571cu; { long double r_ = native_call_fp(m, 0x49fe7au); FPUSH(r_); }	/* 465717: call 0x49fe7a */
	MF((DWORD)(m->esi + 0x4u)) = (float)ST(0); FPOP();	/* 46571c: fstp dword ptr [esi + 4] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46571f: add esp, 0x18 */
	{ DWORD a_ = m->esi, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 465722: add esi, 8 */
	M32((DWORD)(m->esp + 0x44u)) = m->esi;	/* 465725: mov dword ptr [esp + 0x44], esi */
	goto L_465ef5;	/* 465729: jmp 0x465ef5 */
L_46572e:
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 46572e: mov edi, dword ptr [esp + 0x14] */
	m->eax = 0x4c4c64u;	/* 465732: mov eax, 0x4c4c64 */
L_465737:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 465737: mov dl, byte ptr [edi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 465739: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->eax + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46573b: cmp dl, byte ptr [eax] */
	if (!m->zf) goto L_46575b;	/* 46573d: jne 0x46575b */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46573f: test cl, cl */
	if (m->zf) goto L_465757;	/* 465741: je 0x465757 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 465743: mov dl, byte ptr [edi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 465746: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->eax + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465748: cmp dl, byte ptr [eax + 1] */
	if (!m->zf) goto L_46575b;	/* 46574b: jne 0x46575b */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46574d: add edi, 2 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465750: add eax, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465753: test cl, cl */
	if (!m->zf) goto L_465737;	/* 465755: jne 0x465737 */
L_465757:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 465757: xor eax, eax */
	goto L_465760;	/* 465759: jmp 0x465760 */
L_46575b:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46575b: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 46575d: sbb eax, -1 */
L_465760:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465760: test eax, eax */
	if (!m->zf) goto L_465822;	/* 465762: jne 0x465822 */
	m->ebx = M32((DWORD)(m->esi + 0x14u));	/* 465768: mov ebx, dword ptr [esi + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 46576b: mov eax, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46576f: add ebx, eax */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 465771: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465773: add eax, 0x80 */
	{ DWORD v_ = 0x4c4b04u; m->esp -= 4; M32(m->esp) = v_; }	/* 465778: push 0x4c4b04 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46577d: push ebp */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 46577e: mov dword ptr [esp + 0x3c], eax */
	m->esp -= 4; M32(m->esp) = 0x465787u; native_call(m, 0x49ec3bu);	/* 465782: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465787: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46578a: test eax, eax */
	if (m->zf) goto L_4657c7;	/* 46578c: je 0x4657c7 */
L_46578e:
	m->edi = m->eax;	/* 46578e: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465790: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 465793: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x1e4u);	/* 465795: lea edx, [esp + 0x1e4] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46579c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46579e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4657a0: sub edi, ecx */
	{ DWORD v_ = 0x4c4b04u; m->esp -= 4; M32(m->esp) = v_; }	/* 4657a2: push 0x4c4b04 */
	m->eax = m->ecx;	/* 4657a7: mov eax, ecx */
	m->esi = m->edi;	/* 4657a9: mov esi, edi */
	m->edi = m->edx;	/* 4657ab: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4657ad: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4657af: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4657b2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4657b4: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4657b6: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4657b9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4657c0u; native_call(m, 0x49ec3bu);	/* 4657bb: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4657c0: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4657c3: test eax, eax */
	if (!m->zf) goto L_46578e;	/* 4657c5: jne 0x46578e */
L_4657c7:
	m->ecx = (DWORD)(m->esp + 0x1e4u);	/* 4657c7: lea ecx, [esp + 0x1e4] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 4657ce: push 0x4b4310 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4657d3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4657d9u; native_call(m, 0x49ec3bu);	/* 4657d4: call 0x49ec3b */
	m->edx = m->eax;	/* 4657d9: mov edx, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4657db: or ecx, 0xffffffff */
	m->edi = m->edx;	/* 4657de: mov edi, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4657e0: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4657e2: add esp, 8 */
	m->esi = (DWORD)(m->ebx + 0x4u);	/* 4657e5: lea esi, [ebx + 4] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4657e8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4657ea: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4657ec: sub edi, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 4657ee: mov dword ptr [esp + 0x14], esi */
	m->eax = m->ecx;	/* 4657f2: mov eax, ecx */
	m->esi = m->edi;	/* 4657f4: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 4657f6: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4657fa: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4657fd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4657ff: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 465801: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465803: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 465806: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 465808: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46580a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46580d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46580f: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 465811: dec ecx */
	M8((DWORD)(m->ecx + m->ebx*1 + 0x3u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 465812: mov byte ptr [ecx + ebx + 3], al */
	M32((DWORD)(m->ebx + 0x44u)) = 0xffffffffu;	/* 465816: mov dword ptr [ebx + 0x44], 0xffffffff */
	goto L_465ef5;	/* 46581d: jmp 0x465ef5 */
L_465822:
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 465822: mov esi, dword ptr [esp + 0x14] */
	m->edi = 0x4c4c54u;	/* 465826: mov edi, 0x4c4c54 */
L_46582b:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 46582b: mov cl, byte ptr [esi] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 46582d: mov dl, byte ptr [edi] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((((m->ecx >> 0) & 0xff)) & 0xff) << 0);	/* 46582f: mov al, cl */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465831: cmp cl, dl */
	if (!m->zf) goto L_465853;	/* 465833: jne 0x465853 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465835: test al, al */
	if (m->zf) goto L_46584f;	/* 465837: je 0x46584f */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 465839: mov dl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 46583c: mov cl, byte ptr [edi + 1] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 46583f: mov al, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465841: cmp dl, cl */
	if (!m->zf) goto L_465853;	/* 465843: jne 0x465853 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 465845: add esi, 2 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 465848: add edi, 2 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46584b: test al, al */
	if (!m->zf) goto L_46582b;	/* 46584d: jne 0x46582b */
L_46584f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46584f: xor eax, eax */
	goto L_465858;	/* 465851: jmp 0x465858 */
L_465853:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 465853: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 465855: sbb eax, -1 */
L_465858:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465858: test eax, eax */
	if (!m->zf) goto L_465ef5;	/* 46585a: jne 0x465ef5 */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 465860: push 0x4b4310 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465865: push eax */
	m->esp -= 4; M32(m->esp) = 0x46586bu; native_call(m, 0x49ec3bu);	/* 465866: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46586b: add esp, 8 */
	m->edi = 0x4b1328u;	/* 46586e: mov edi, 0x4b1328 */
	m->esi = m->eax;	/* 465873: mov esi, eax */
L_465875:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 465875: mov dl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 465877: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->edi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465879: cmp dl, byte ptr [edi] */
	if (!m->zf) goto L_465899;	/* 46587b: jne 0x465899 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46587d: test cl, cl */
	if (m->zf) goto L_465895;	/* 46587f: je 0x465895 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 465881: mov dl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 465884: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->edi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 465886: cmp dl, byte ptr [edi + 1] */
	if (!m->zf) goto L_465899;	/* 465889: jne 0x465899 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46588b: add esi, 2 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46588e: add edi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465891: test cl, cl */
	if (!m->zf) goto L_465875;	/* 465893: jne 0x465875 */
L_465895:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465895: xor ecx, ecx */
	goto L_46589e;	/* 465897: jmp 0x46589e */
L_465899:
	{ DWORD a_ = m->ecx, b_ = m->ecx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 465899: sbb ecx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ecx = r_; }	/* 46589b: sbb ecx, -1 */
L_46589e:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46589e: test ecx, ecx */
	if (!m->zf) goto L_4658cb;	/* 4658a0: jne 0x4658cb */
	m->eax = M32((DWORD)(m->esp + 0x2e8u));	/* 4658a2: mov eax, dword ptr [esp + 0x2e8] */
	m->ecx = (DWORD)(m->esp + 0x6cu);	/* 4658a9: lea ecx, [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4658ad: push eax */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 4658ae: push 0x100 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4658b3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4658b9u; native_call(m, 0x49ecd7u);	/* 4658b4: call 0x49ecd7 */
	m->edx = (DWORD)(m->esp + 0x78u);	/* 4658b9: lea edx, [esp + 0x78] */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 4658bd: push 0x4b4310 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4658c2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4658c8u; native_call(m, 0x49ec3bu);	/* 4658c3: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4658c8: add esp, 0x14 */
L_4658cb:
	m->edi = m->eax;	/* 4658cb: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4658cd: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4658d0: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x1c4u);	/* 4658d2: lea edx, [esp + 0x1c4] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4658d9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4658db: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4658dd: sub edi, ecx */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 4658df: push 0x4b4310 */
	m->eax = m->ecx;	/* 4658e4: mov eax, ecx */
	m->esi = m->edi;	/* 4658e6: mov esi, edi */
	m->edi = m->edx;	/* 4658e8: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4658ea: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4658ec: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4658ef: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4658f1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4658f3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4658f6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4658fdu; native_call(m, 0x49ec3bu);	/* 4658f8: call 0x49ec3b */
	m->edi = m->eax;	/* 4658fd: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4658ff: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 465902: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x1acu);	/* 465904: lea edx, [esp + 0x1ac] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46590b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46590d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46590f: sub edi, ecx */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 465911: push 0x4b4310 */
	m->eax = m->ecx;	/* 465916: mov eax, ecx */
	m->esi = m->edi;	/* 465918: mov esi, edi */
	m->edi = m->edx;	/* 46591a: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46591c: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46591e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 465921: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 465923: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465925: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 465928: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x46592fu; native_call(m, 0x49ec3bu);	/* 46592a: call 0x49ec3b */
	m->edi = m->eax;	/* 46592f: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465931: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 465934: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x194u);	/* 465936: lea edx, [esp + 0x194] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46593d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46593f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 465941: sub edi, ecx */
	{ DWORD v_ = 0x4b4310u; m->esp -= 4; M32(m->esp) = v_; }	/* 465943: push 0x4b4310 */
	m->eax = m->ecx;	/* 465948: mov eax, ecx */
	m->esi = m->edi;	/* 46594a: mov esi, edi */
	m->edi = m->edx;	/* 46594c: mov edi, edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46594e: push 0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 465950: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 465953: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 465955: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465957: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46595a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x465961u; native_call(m, 0x49ec3bu);	/* 46595c: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465961: add esp, 0x18 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465964: test eax, eax */
	if (!m->zf) goto L_46596e;	/* 465966: jne 0x46596e */
	M8((DWORD)(m->esp + 0x4cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 465968: mov byte ptr [esp + 0x4c], al */
	goto L_465991;	/* 46596c: jmp 0x465991 */
L_46596e:
	m->edi = m->eax;	/* 46596e: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465970: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 465973: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 465975: lea edx, [esp + 0x4c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 465979: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46597b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46597d: sub edi, ecx */
	m->eax = m->ecx;	/* 46597f: mov eax, ecx */
	m->esi = m->edi;	/* 465981: mov esi, edi */
	m->edi = m->edx;	/* 465983: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 465985: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 465988: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46598a: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46598c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46598f: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_465991:
	m->ecx = (DWORD)(m->esp + 0x1c4u);	/* 465991: lea ecx, [esp + 0x1c4] */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465998: push 0x4ad564 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46599d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4659a3u; native_call(m, 0x49ec3bu);	/* 46599e: call 0x49ec3b */
	m->esi = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 4659a3: lea esi, [ebp + ebp*2] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4659a7: push eax */
	{ DWORD a_ = m->esi, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4659a8: shl esi, 2 */
	m->esp -= 4; M32(m->esp) = 0x4659b0u; native_call(m, 0x49ec09u);	/* 4659ab: call 0x49ec09 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4659b0: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 4659b3: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 4659b7: push 0x4ad564 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4659bc: push 0 */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0xfffffff4u);	/* 4659be: lea ecx, [eax + edx*4 - 0xc] */
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 4659c2: mov edx, dword ptr [ebx + 0x50] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4659c5: add edx, esi */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 4659c7: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 4659c9: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 4659cb: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 4659ce: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 4659d1: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 4659d4: mov dword ptr [edx + 8], ecx */
	m->esp -= 4; M32(m->esp) = 0x4659dcu; native_call(m, 0x49ec3bu);	/* 4659d7: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4659dc: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4659df: test eax, eax */
	if (m->zf) goto L_465a7e;	/* 4659e1: je 0x465a7e */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4659e7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4659edu; native_call(m, 0x49ec09u);	/* 4659e8: call 0x49ec09 */
	m->edi = m->eax;	/* 4659ed: mov edi, eax */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 4659ef: push 0x4ad564 */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4659f4: dec edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4659f5: push 0 */
	M32((DWORD)(m->esp + 0x1cu)) = m->edi;	/* 4659f7: mov dword ptr [esp + 0x1c], edi */
	m->esp -= 4; M32(m->esp) = 0x465a00u; native_call(m, 0x49ec3bu);	/* 4659fb: call 0x49ec3b */
	m->edx = M32((DWORD)(m->ebx + 0x5cu));	/* 465a00: mov edx, dword ptr [ebx + 0x5c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465a03: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465a06: test eax, eax */
	if (m->zf) goto L_465a4f;	/* 465a08: je 0x465a4f */
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 465a0a: mov edi, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 465a0e: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465a12: push eax */
	m->ecx = M32((DWORD)(m->edi + m->ecx*8 + 0x0u));	/* 465a13: mov ecx, dword ptr [edi + ecx*8] */
	M32((DWORD)(m->edx + m->ebp*8 + 0x0u)) = m->ecx;	/* 465a16: mov dword ptr [edx + ebp*8], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 465a19: mov ecx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->edi + m->ecx*8 + 0x4u));	/* 465a1d: mov ecx, dword ptr [edi + ecx*8 + 4] */
	M32((DWORD)(m->edx + m->ebp*8 + 0x4u)) = m->ecx;	/* 465a21: mov dword ptr [edx + ebp*8 + 4], ecx */
	m->esp -= 4; M32(m->esp) = 0x465a2au; native_call(m, 0x49ec09u);	/* 465a25: call 0x49ec09 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465a2a: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 465a2d: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465a31: add esp, 4 */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0xfffffff4u);	/* 465a34: lea ecx, [eax + edx*4 - 0xc] */
	m->edx = M32((DWORD)(m->ebx + 0x54u));	/* 465a38: mov edx, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465a3b: add edx, esi */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 465a3d: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 465a3f: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 465a41: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 465a44: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 465a47: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 465a4a: mov dword ptr [edx + 8], ecx */
	goto L_465a82;	/* 465a4d: jmp 0x465a82 */
L_465a4f:
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 465a4f: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->edx + m->ebp*8 + 0x0u);	/* 465a53: lea eax, [edx + ebp*8] */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 465a56: mov dword ptr [eax], 0 */
	M32((DWORD)(m->eax + 0x4u)) = 0x0u;	/* 465a5c: mov dword ptr [eax + 4], 0 */
	m->eax = (DWORD)(m->edi + m->edi*2 + 0x0u);	/* 465a63: lea eax, [edi + edi*2] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 465a66: lea edx, [ecx + eax*4] */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 465a69: mov eax, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465a6c: add eax, esi */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 465a6e: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 465a70: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 465a72: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 465a75: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 465a78: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 465a7b: mov dword ptr [eax + 8], edx */
L_465a7e:
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 465a7e: mov edi, dword ptr [esp + 0x28] */
L_465a82:
	m->eax = (DWORD)(m->esp + 0x1a4u);	/* 465a82: lea eax, [esp + 0x1a4] */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465a89: push 0x4ad564 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465a8e: push eax */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 465a8f: inc ebp */
	m->esp -= 4; M32(m->esp) = 0x465a95u; native_call(m, 0x49ec3bu);	/* 465a90: call 0x49ec3b */
	m->esi = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 465a95: lea esi, [ebp + ebp*2] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465a99: push eax */
	{ DWORD a_ = m->esi, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 465a9a: shl esi, 2 */
	m->esp -= 4; M32(m->esp) = 0x465aa2u; native_call(m, 0x49ec09u);	/* 465a9d: call 0x49ec09 */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 465aa2: mov edx, dword ptr [esp + 0x28] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465aa6: lea ecx, [eax + eax*2] */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465aa9: push 0x4ad564 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465aae: push 0 */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0xfffffff4u);	/* 465ab0: lea eax, [edx + ecx*4 - 0xc] */
	m->ecx = M32((DWORD)(m->ebx + 0x50u));	/* 465ab4: mov ecx, dword ptr [ebx + 0x50] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465ab7: add ecx, esi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 465ab9: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 465abb: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 465abd: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 465ac0: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 465ac3: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 465ac6: mov dword ptr [ecx + 8], eax */
	m->esp -= 4; M32(m->esp) = 0x465aceu; native_call(m, 0x49ec3bu);	/* 465ac9: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465ace: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465ad1: test eax, eax */
	if (m->zf) goto L_465b73;	/* 465ad3: je 0x465b73 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465ad9: push eax */
	m->esp -= 4; M32(m->esp) = 0x465adfu; native_call(m, 0x49ec09u);	/* 465ada: call 0x49ec09 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 465adf: dec eax */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465ae0: push 0x4ad564 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465ae5: push 0 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 465ae7: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x465af0u; native_call(m, 0x49ec3bu);	/* 465aeb: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465af0: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465af3: test eax, eax */
	if (m->zf) goto L_465b3b;	/* 465af5: je 0x465b3b */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 465af7: mov edx, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->ebx + 0x5cu));	/* 465afb: mov ecx, dword ptr [ebx + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465afe: push eax */
	m->edx = M32((DWORD)(m->edi + m->edx*8 + 0x0u));	/* 465aff: mov edx, dword ptr [edi + edx*8] */
	M32((DWORD)(m->ecx + m->ebp*8 + 0x0u)) = m->edx;	/* 465b02: mov dword ptr [ecx + ebp*8], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 465b05: mov edx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->edi + m->edx*8 + 0x4u));	/* 465b09: mov edx, dword ptr [edi + edx*8 + 4] */
	M32((DWORD)(m->ecx + m->ebp*8 + 0x4u)) = m->edx;	/* 465b0d: mov dword ptr [ecx + ebp*8 + 4], edx */
	m->esp -= 4; M32(m->esp) = 0x465b16u; native_call(m, 0x49ec09u);	/* 465b11: call 0x49ec09 */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 465b16: mov ecx, dword ptr [esp + 0x1c] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465b1a: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465b1d: add esp, 4 */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0xfffffff4u);	/* 465b20: lea edx, [ecx + eax*4 - 0xc] */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 465b24: mov eax, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465b27: add eax, esi */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 465b29: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 465b2b: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 465b2d: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 465b30: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 465b33: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 465b36: mov dword ptr [eax + 8], edx */
	goto L_465b73;	/* 465b39: jmp 0x465b73 */
L_465b3b:
	m->eax = M32((DWORD)(m->ebx + 0x5cu));	/* 465b3b: mov eax, dword ptr [ebx + 0x5c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 465b3e: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + m->ebp*8 + 0x0u)) = 0x0u;	/* 465b42: mov dword ptr [eax + ebp*8], 0 */
	M32((DWORD)(m->eax + m->ebp*8 + 0x4u)) = 0x0u;	/* 465b49: mov dword ptr [eax + ebp*8 + 4], 0 */
	m->eax = (DWORD)(m->eax + m->ebp*8 + 0x0u);	/* 465b51: lea eax, [eax + ebp*8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 465b54: mov eax, dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465b58: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 465b5b: lea eax, [edx + ecx*4] */
	m->ecx = M32((DWORD)(m->ebx + 0x54u));	/* 465b5e: mov ecx, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465b61: add ecx, esi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 465b63: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 465b65: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 465b67: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 465b6a: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 465b6d: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 465b70: mov dword ptr [ecx + 8], eax */
L_465b73:
	m->ecx = (DWORD)(m->esp + 0x184u);	/* 465b73: lea ecx, [esp + 0x184] */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465b7a: push 0x4ad564 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 465b7f: push ecx */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 465b80: inc ebp */
	m->esp -= 4; M32(m->esp) = 0x465b86u; native_call(m, 0x49ec3bu);	/* 465b81: call 0x49ec3b */
	m->esi = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 465b86: lea esi, [ebp + ebp*2] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465b8a: push eax */
	{ DWORD a_ = m->esi, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 465b8b: shl esi, 2 */
	m->esp -= 4; M32(m->esp) = 0x465b93u; native_call(m, 0x49ec09u);	/* 465b8e: call 0x49ec09 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465b93: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 465b96: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465b9a: push 0x4ad564 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465b9f: push 0 */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0xfffffff4u);	/* 465ba1: lea ecx, [eax + edx*4 - 0xc] */
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 465ba5: mov edx, dword ptr [ebx + 0x50] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465ba8: add edx, esi */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 465baa: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 465bac: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 465bae: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 465bb1: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 465bb4: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 465bb7: mov dword ptr [edx + 8], ecx */
	m->esp -= 4; M32(m->esp) = 0x465bbfu; native_call(m, 0x49ec3bu);	/* 465bba: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465bbf: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465bc2: test eax, eax */
	if (m->zf) goto L_465c64;	/* 465bc4: je 0x465c64 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465bca: push eax */
	m->esp -= 4; M32(m->esp) = 0x465bd0u; native_call(m, 0x49ec09u);	/* 465bcb: call 0x49ec09 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 465bd0: dec eax */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465bd1: push 0x4ad564 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465bd6: push 0 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 465bd8: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x465be1u; native_call(m, 0x49ec3bu);	/* 465bdc: call 0x49ec3b */
	m->edx = M32((DWORD)(m->ebx + 0x5cu));	/* 465be1: mov edx, dword ptr [ebx + 0x5c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465be4: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465be7: test eax, eax */
	if (m->zf) goto L_465c2f;	/* 465be9: je 0x465c2f */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 465beb: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465bef: push eax */
	m->ecx = M32((DWORD)(m->edi + m->ecx*8 + 0x0u));	/* 465bf0: mov ecx, dword ptr [edi + ecx*8] */
	M32((DWORD)(m->edx + m->ebp*8 + 0x0u)) = m->ecx;	/* 465bf3: mov dword ptr [edx + ebp*8], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 465bf6: mov ecx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->edi + m->ecx*8 + 0x4u));	/* 465bfa: mov ecx, dword ptr [edi + ecx*8 + 4] */
	M32((DWORD)(m->edx + m->ebp*8 + 0x4u)) = m->ecx;	/* 465bfe: mov dword ptr [edx + ebp*8 + 4], ecx */
	m->esp -= 4; M32(m->esp) = 0x465c07u; native_call(m, 0x49ec09u);	/* 465c02: call 0x49ec09 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465c07: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 465c0a: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465c0e: add esp, 4 */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0xfffffff4u);	/* 465c11: lea ecx, [eax + edx*4 - 0xc] */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 465c15: mov eax, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 465c18: add esi, eax */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 465c1a: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esi + 0x0u)) = m->edx;	/* 465c1c: mov dword ptr [esi], edx */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 465c1e: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 465c21: mov dword ptr [esi + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 465c24: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esi + 0x8u)) = m->ecx;	/* 465c27: mov dword ptr [esi + 8], ecx */
	goto L_465cdb;	/* 465c2a: jmp 0x465cdb */
L_465c2f:
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 465c2f: mov ecx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->edx + m->ebp*8 + 0x0u);	/* 465c33: lea eax, [edx + ebp*8] */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 465c36: mov dword ptr [eax], 0 */
	M32((DWORD)(m->eax + 0x4u)) = 0x0u;	/* 465c3c: mov dword ptr [eax + 4], 0 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 465c43: mov eax, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465c47: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 465c4a: lea edx, [ecx + eax*4] */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 465c4d: mov eax, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 465c50: add esi, eax */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 465c52: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 465c54: mov dword ptr [esi], eax */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 465c56: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->esi + 0x4u)) = m->ecx;	/* 465c59: mov dword ptr [esi + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 465c5c: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esi + 0x8u)) = m->edx;	/* 465c5f: mov dword ptr [esi + 8], edx */
	goto L_465cdb;	/* 465c62: jmp 0x465cdb */
L_465c64:
	m->ecx = M32((DWORD)(m->ebx + 0x50u));	/* 465c64: mov ecx, dword ptr [ebx + 0x50] */
	m->eax = (DWORD)(m->ebp + m->ebp*2 + 0xfffffffau);	/* 465c67: lea eax, [ebp + ebp*2 - 6] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 465c6b: shl eax, 2 */
	m->edx = (DWORD)(m->ecx + m->esi*1 + 0x0u);	/* 465c6e: lea edx, [ecx + esi] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 465c71: mov dword ptr [esp + 0x14], eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 465c75: push edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffff4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465c76: add edx, -0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465c79: add eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 465c7b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465c7c: push eax */
	m->eax = (DWORD)(m->esp + 0x184u);	/* 465c7d: lea eax, [esp + 0x184] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465c84: push eax */
	m->esp -= 4; M32(m->esp) = 0x465c8au; native_call(m, 0x4679a0u);	/* 465c85: call 0x4679a0 */
	m->edx = M32((DWORD)(m->ebx + 0x54u));	/* 465c8a: mov edx, dword ptr [ebx + 0x54] */
	m->ecx = m->esi;	/* 465c8d: mov ecx, esi */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465c8f: add ecx, edx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 465c91: mov edx, dword ptr [eax] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465c93: add esp, 0x10 */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 465c96: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 465c98: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 465c9b: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 465c9e: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 465ca1: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->ebx + 0x54u));	/* 465ca4: mov ecx, dword ptr [ebx + 0x54] */
	m->eax = (DWORD)(m->esi + m->ecx*1 + 0x0u);	/* 465ca7: lea eax, [esi + ecx] */
	m->ecx = M32((DWORD)(m->esi + m->ecx*1 + 0x0u));	/* 465caa: mov ecx, dword ptr [esi + ecx] */
	m->edx = (DWORD)(m->eax + 0xfffffff4u);	/* 465cad: lea edx, [eax - 0xc] */
	M32((DWORD)(m->eax + 0xfffffff4u)) = m->ecx;	/* 465cb0: mov dword ptr [eax - 0xc], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 465cb3: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 465cb6: mov dword ptr [edx + 4], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 465cb9: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 465cbc: mov dword ptr [edx + 8], eax */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 465cbf: mov eax, dword ptr [ebx + 0x54] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 465cc2: mov edx, dword ptr [esp + 0x14] */
	m->ecx = (DWORD)(m->eax + m->esi*1 + 0x0u);	/* 465cc6: lea ecx, [eax + esi] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465cc9: add edx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 465ccb: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 465ccd: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 465ccf: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 465cd2: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 465cd5: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 465cd8: mov dword ptr [edx + 8], ecx */
L_465cdb:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x4cu))) & 0xff) << 0);	/* 465cdb: mov al, byte ptr [esp + 0x4c] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 465cdf: inc ebp */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 465ce0: test al, al */
	if (m->zf) goto L_465ef5;	/* 465ce2: je 0x465ef5 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 465ce8: mov edx, dword ptr [esp + 0x1c] */
	m->eax = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 465cec: lea eax, [ebp + ebp*2] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 465cf0: shl eax, 2 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 465cf3: mov dword ptr [esp + 0x10], eax */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465cf7: push 0x4ad564 */
	m->ecx = (DWORD)(m->eax + m->edx*1 + 0x0u);	/* 465cfc: lea ecx, [eax + edx] */
	m->edx = (DWORD)(m->ecx + 0xfffffff4u);	/* 465cff: lea edx, [ecx - 0xc] */
	m->esi = M32((DWORD)(m->ecx + 0xfffffff4u));	/* 465d02: mov esi, dword ptr [ecx - 0xc] */
	M32((DWORD)(m->ecx + 0x0u)) = m->esi;	/* 465d05: mov dword ptr [ecx], esi */
	m->esi = M32((DWORD)(m->edx + 0x4u));	/* 465d07: mov esi, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->esi;	/* 465d0a: mov dword ptr [ecx + 4], esi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 465d0d: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 465d10: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 465d13: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465d17: add eax, ecx */
	m->edx = (DWORD)(m->eax + 0xfffffff4u);	/* 465d19: lea edx, [eax - 0xc] */
	m->ecx = M32((DWORD)(m->eax + 0xfffffff4u));	/* 465d1c: mov ecx, dword ptr [eax - 0xc] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 465d1f: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 465d21: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 465d24: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 465d27: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 465d2a: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->edi + m->ebp*8 + 0xfffffff8u));	/* 465d2d: mov eax, dword ptr [edi + ebp*8 - 8] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 465d31: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->edi + m->ebp*8 + 0x0u)) = m->eax;	/* 465d35: mov dword ptr [edi + ebp*8], eax */
	m->ecx = M32((DWORD)(m->edi + m->ebp*8 + 0xfffffffcu));	/* 465d38: mov ecx, dword ptr [edi + ebp*8 - 4] */
	m->eax = (DWORD)(m->ebp + m->ebp*2 + 0xfffffff7u);	/* 465d3c: lea eax, [ebp + ebp*2 - 9] */
	M32((DWORD)(m->edi + m->ebp*8 + 0x4u)) = m->ecx;	/* 465d40: mov dword ptr [edi + ebp*8 + 4], ecx */
	m->ecx = (DWORD)(m->ebp + m->ebp*2 + 0x6u);	/* 465d44: lea ecx, [ebp + ebp*2 + 6] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 465d48: shl eax, 2 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 465d4b: shl ecx, 2 */
	m->esi = (DWORD)(m->eax + m->edx*1 + 0x0u);	/* 465d4e: lea esi, [eax + edx] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 465d51: mov dword ptr [esp + 0x18], ecx */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465d55: add ecx, edx */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 465d57: mov edx, dword ptr [esi] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 465d59: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 465d5b: mov edx, dword ptr [esi + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 465d5e: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esi + 0x8u));	/* 465d61: mov edx, dword ptr [esi + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 465d64: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 465d67: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 465d6b: mov edx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465d6f: add eax, ecx */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465d71: add edx, ecx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 465d73: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 465d75: mov dword ptr [edx], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 465d77: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 465d7a: mov dword ptr [edx + 4], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 465d7d: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 465d80: mov dword ptr [edx + 8], eax */
	m->ecx = M32((DWORD)(m->edi + m->ebp*8 + 0xffffffe8u));	/* 465d83: mov ecx, dword ptr [edi + ebp*8 - 0x18] */
	M32((DWORD)(m->edi + m->ebp*8 + 0x10u)) = m->ecx;	/* 465d87: mov dword ptr [edi + ebp*8 + 0x10], ecx */
	m->edx = M32((DWORD)(m->edi + m->ebp*8 + 0xffffffecu));	/* 465d8b: mov edx, dword ptr [edi + ebp*8 - 0x14] */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 465d8f: lea eax, [esp + 0x50] */
	M32((DWORD)(m->edi + m->ebp*8 + 0x14u)) = m->edx;	/* 465d93: mov dword ptr [edi + ebp*8 + 0x14], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465d97: push eax */
	m->esp -= 4; M32(m->esp) = 0x465d9du; native_call(m, 0x49ec3bu);	/* 465d98: call 0x49ec3b */
	m->esi = (DWORD)(m->ebp + m->ebp*2 + 0x3u);	/* 465d9d: lea esi, [ebp + ebp*2 + 3] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465da1: push eax */
	{ DWORD a_ = m->esi, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 465da2: shl esi, 2 */
	m->esp -= 4; M32(m->esp) = 0x465daau; native_call(m, 0x49ec09u);	/* 465da5: call 0x49ec09 */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 465daa: mov edx, dword ptr [esp + 0x28] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465dae: lea ecx, [eax + eax*2] */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465db1: push 0x4ad564 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465db6: push 0 */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0xfffffff4u);	/* 465db8: lea eax, [edx + ecx*4 - 0xc] */
	m->ecx = M32((DWORD)(m->ebx + 0x50u));	/* 465dbc: mov ecx, dword ptr [ebx + 0x50] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465dbf: add ecx, esi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 465dc1: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 465dc3: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 465dc5: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 465dc8: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 465dcb: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 465dce: mov dword ptr [ecx + 8], eax */
	m->esp -= 4; M32(m->esp) = 0x465dd6u; native_call(m, 0x49ec3bu);	/* 465dd1: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465dd6: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465dd9: test eax, eax */
	if (m->zf) goto L_465e83;	/* 465ddb: je 0x465e83 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465de1: push eax */
	m->esp -= 4; M32(m->esp) = 0x465de7u; native_call(m, 0x49ec09u);	/* 465de2: call 0x49ec09 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 465de7: dec eax */
	{ DWORD v_ = 0x4ad564u; m->esp -= 4; M32(m->esp) = v_; }	/* 465de8: push 0x4ad564 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 465ded: push 0 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 465def: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x465df8u; native_call(m, 0x49ec3bu);	/* 465df3: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465df8: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465dfb: test eax, eax */
	if (m->zf) goto L_465e47;	/* 465dfd: je 0x465e47 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 465dff: mov edx, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->ebx + 0x5cu));	/* 465e03: mov ecx, dword ptr [ebx + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465e06: push eax */
	m->edx = M32((DWORD)(m->edi + m->edx*8 + 0x0u));	/* 465e07: mov edx, dword ptr [edi + edx*8] */
	M32((DWORD)(m->ecx + m->ebp*8 + 0x8u)) = m->edx;	/* 465e0a: mov dword ptr [ecx + ebp*8 + 8], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 465e0e: mov edx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->edi + m->edx*8 + 0x4u));	/* 465e12: mov edx, dword ptr [edi + edx*8 + 4] */
	M32((DWORD)(m->ecx + m->ebp*8 + 0xcu)) = m->edx;	/* 465e16: mov dword ptr [ecx + ebp*8 + 0xc], edx */
	m->esp -= 4; M32(m->esp) = 0x465e1fu; native_call(m, 0x49ec09u);	/* 465e1a: call 0x49ec09 */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 465e1f: mov ecx, dword ptr [esp + 0x1c] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465e23: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465e26: add esp, 4 */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0xfffffff4u);	/* 465e29: lea edx, [ecx + eax*4 - 0xc] */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 465e2d: mov eax, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 465e30: add esi, eax */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 465e32: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 465e34: mov dword ptr [esi], eax */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 465e36: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->esi + 0x4u)) = m->ecx;	/* 465e39: mov dword ptr [esi + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 465e3c: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esi + 0x8u)) = m->edx;	/* 465e3f: mov dword ptr [esi + 8], edx */
	goto L_465ef2;	/* 465e42: jmp 0x465ef2 */
L_465e47:
	m->eax = M32((DWORD)(m->ebx + 0x5cu));	/* 465e47: mov eax, dword ptr [ebx + 0x5c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 465e4a: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + m->ebp*8 + 0x8u)) = 0x0u;	/* 465e4e: mov dword ptr [eax + ebp*8 + 8], 0 */
	M32((DWORD)(m->eax + m->ebp*8 + 0xcu)) = 0x0u;	/* 465e56: mov dword ptr [eax + ebp*8 + 0xc], 0 */
	m->eax = (DWORD)(m->eax + m->ebp*8 + 0x8u);	/* 465e5e: lea eax, [eax + ebp*8 + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 465e62: mov eax, dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 465e66: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 465e69: lea eax, [edx + ecx*4] */
	m->ecx = M32((DWORD)(m->ebx + 0x54u));	/* 465e6c: mov ecx, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 465e6f: add esi, ecx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 465e71: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esi + 0x0u)) = m->ecx;	/* 465e73: mov dword ptr [esi], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 465e75: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esi + 0x4u)) = m->edx;	/* 465e78: mov dword ptr [esi + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 465e7b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 465e7e: mov dword ptr [esi + 8], eax */
	goto L_465ef2;	/* 465e81: jmp 0x465ef2 */
L_465e83:
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 465e83: mov eax, dword ptr [ebx + 0x50] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 465e86: mov ecx, dword ptr [esp + 0x14] */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 465e8a: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465e8e: add ecx, eax */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x0u);	/* 465e90: lea edx, [esi + eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 465e93: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465e94: add eax, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 465e96: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465e97: push eax */
	m->eax = (DWORD)(m->esp + 0x178u);	/* 465e98: lea eax, [esp + 0x178] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 465e9f: push eax */
	m->esp -= 4; M32(m->esp) = 0x465ea5u; native_call(m, 0x4679a0u);	/* 465ea0: call 0x4679a0 */
	m->edx = M32((DWORD)(m->ebx + 0x54u));	/* 465ea5: mov edx, dword ptr [ebx + 0x54] */
	m->ecx = m->esi;	/* 465ea8: mov ecx, esi */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 465eaa: add ecx, edx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 465eac: mov edx, dword ptr [eax] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465eae: add esp, 0x10 */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 465eb1: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 465eb3: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 465eb6: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 465eb9: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 465ebc: mov dword ptr [ecx + 8], eax */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 465ebf: mov eax, dword ptr [ebx + 0x54] */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x0u);	/* 465ec2: lea ecx, [esi + eax] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465ec5: add eax, edi */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 465ec7: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 465ec9: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 465ecb: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 465ece: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 465ed1: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 465ed5: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 465ed8: mov dword ptr [eax + 8], ecx */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 465edb: mov eax, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 465ede: add esi, eax */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465ee0: add edx, eax */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 465ee2: mov eax, dword ptr [esi] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 465ee4: mov dword ptr [edx], eax */
	m->ecx = M32((DWORD)(m->esi + 0x4u));	/* 465ee6: mov ecx, dword ptr [esi + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 465ee9: mov dword ptr [edx + 4], ecx */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 465eec: mov eax, dword ptr [esi + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 465eef: mov dword ptr [edx + 8], eax */
L_465ef2:
	{ DWORD a_ = m->ebp, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 465ef2: add ebp, 3 */
L_465ef5:
	m->ecx = M32((DWORD)(m->esp + 0x2e8u));	/* 465ef5: mov ecx, dword ptr [esp + 0x2e8] */
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 465efc: lea edx, [esp + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 465f00: push ecx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 465f01: push 0x100 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 465f06: push edx */
	m->esp -= 4; M32(m->esp) = 0x465f0cu; native_call(m, 0x49ecd7u);	/* 465f07: call 0x49ecd7 */
	m->esi = M32((DWORD)(m->esp + 0x4cu));	/* 465f0c: mov esi, dword ptr [esp + 0x4c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 465f10: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465f13: test eax, eax */
	if (!m->zf) goto L_465553;	/* 465f15: jne 0x465553 */
L_465f1b:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 465f1b: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 465f1e: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465f20: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_465f53;	/* 465f22: jle 0x465f53 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 465f24: xor edx, edx */
L_465f26:
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 465f26: mov eax, dword ptr [esi + 0x14] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465f29: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465f2b: add eax, edx */
	m->ebx = M32((DWORD)(m->eax + 0x4cu));	/* 465f2d: mov ebx, dword ptr [eax + 0x4c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465f30: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_465f45;	/* 465f32: jle 0x465f45 */
L_465f34:
	m->ebx = M32((DWORD)(m->eax + 0x64u));	/* 465f34: mov ebx, dword ptr [eax + 0x64] */
	m->ebx = M32((DWORD)(m->ebx + 0x8u));	/* 465f37: mov ebx, dword ptr [ebx + 8] */
	M32((DWORD)(m->ebx + m->ecx*4 + 0x0u)) = m->ecx;	/* 465f3a: mov dword ptr [ebx + ecx*4], ecx */
	m->ebx = M32((DWORD)(m->eax + 0x4cu));	/* 465f3d: mov ebx, dword ptr [eax + 0x4c] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 465f40: inc ecx */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 465f41: cmp ecx, ebx */
	if (m->sf != m->of) goto L_465f34;	/* 465f43: jl 0x465f34 */
L_465f45:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 465f45: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 465f48: inc edi */
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 465f49: add edx, 0x80 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 465f4f: cmp edi, eax */
	if (m->sf != m->of) goto L_465f26;	/* 465f51: jl 0x465f26 */
L_465f53:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x38u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 465f53: cmp dword ptr [esp + 0x38], 1 */
	if (!m->zf) goto L_465fd7;	/* 465f58: jne 0x465fd7 */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 465f5a: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 465f5d: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465f5f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_465fd7;	/* 465f61: jle 0x465fd7 */
L_465f63:
	m->edi = M32((DWORD)(m->esi + 0x14u));	/* 465f63: mov edi, dword ptr [esi + 0x14] */
	m->eax = m->edx;	/* 465f66: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 465f68: shl eax, 7 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465f6b: add eax, edi */
	m->ecx = M32((DWORD)(m->eax + 0x4cu));	/* 465f6d: mov ecx, dword ptr [eax + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465f70: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_465fcf;	/* 465f72: jle 0x465fcf */
L_465f74:
	m->ecx = M32((DWORD)(m->eax + 0x50u));	/* 465f74: mov ecx, dword ptr [eax + 0x50] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 465f77: inc edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 465f78: fld dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 465f7b: fld dword ptr [ecx + 4] */
	ST(0) = -ST(0);	/* 465f7e: fchs  */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 465f80: fstp dword ptr [ecx + 8] */
	m->ecx = M32((DWORD)(m->eax + 0x50u));	/* 465f83: mov ecx, dword ptr [eax + 0x50] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 465f86: fstp dword ptr [ecx + 4] */
	m->ecx = M32((DWORD)(m->eax + 0x54u));	/* 465f89: mov ecx, dword ptr [eax + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 465f8c: fld dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 465f8f: fld dword ptr [ecx + 4] */
	ST(0) = -ST(0);	/* 465f92: fchs  */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 465f94: fstp dword ptr [ecx + 8] */
	m->ecx = M32((DWORD)(m->eax + 0x54u));	/* 465f97: mov ecx, dword ptr [eax + 0x54] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 465f9a: fstp dword ptr [ecx + 4] */
	m->ecx = M32((DWORD)(m->eax + 0x54u));	/* 465f9d: mov ecx, dword ptr [eax + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 465fa0: fld dword ptr [ecx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9474u));	/* 465fa2: fmul dword ptr [0x4a9474] */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 465fa8: fstp dword ptr [ecx] */
	m->ecx = M32((DWORD)(m->eax + 0x54u));	/* 465faa: mov ecx, dword ptr [eax + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 465fad: fld dword ptr [ecx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9474u));	/* 465fb0: fmul dword ptr [0x4a9474] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 465fb6: fstp dword ptr [ecx + 4] */
	m->ecx = M32((DWORD)(m->eax + 0x54u));	/* 465fb9: mov ecx, dword ptr [eax + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 465fbc: fld dword ptr [ecx + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9474u));	/* 465fbf: fmul dword ptr [0x4a9474] */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 465fc5: fstp dword ptr [ecx + 8] */
	m->ecx = M32((DWORD)(m->eax + 0x4cu));	/* 465fc8: mov ecx, dword ptr [eax + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465fcb: test ecx, ecx */
	if (!m->zf && m->sf == m->of) goto L_465f74;	/* 465fcd: jg 0x465f74 */
L_465fcf:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 465fcf: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 465fd2: inc edx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 465fd3: cmp edx, eax */
	if (m->sf != m->of) goto L_465f63;	/* 465fd5: jl 0x465f63 */
L_465fd7:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 465fd7: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 465fda: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465fdc: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_466012;	/* 465fde: jle 0x466012 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 465fe0: xor edx, edx */
L_465fe2:
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 465fe2: mov eax, dword ptr [esi + 0x14] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 465fe5: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 465fe7: add eax, edx */
	m->edi = M32((DWORD)(m->eax + 0x4cu));	/* 465fe9: mov edi, dword ptr [eax + 0x4c] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 465fec: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_466004;	/* 465fee: jle 0x466004 */
L_465ff0:
	m->edi = M32((DWORD)(m->eax + 0x58u));	/* 465ff0: mov edi, dword ptr [eax + 0x58] */
	m->ebp = M32((DWORD)(0xa1f23cu));	/* 465ff3: mov ebp, dword ptr [0xa1f23c] */
	M32((DWORD)(m->edi + m->ecx*4 + 0x0u)) = m->ebp;	/* 465ff9: mov dword ptr [edi + ecx*4], ebp */
	m->edi = M32((DWORD)(m->eax + 0x4cu));	/* 465ffc: mov edi, dword ptr [eax + 0x4c] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 465fff: inc ecx */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466000: cmp ecx, edi */
	if (m->sf != m->of) goto L_465ff0;	/* 466002: jl 0x465ff0 */
L_466004:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 466004: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 466007: inc ebx */
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 466008: add edx, 0x80 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46600e: cmp ebx, eax */
	if (m->sf != m->of) goto L_465fe2;	/* 466010: jl 0x465fe2 */
L_466012:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x30u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466012: cmp dword ptr [esp + 0x30], 1 */
	if (!m->zf) goto L_466058;	/* 466017: jne 0x466058 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 466019: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46601d: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46602e;	/* 46601f: jle 0x46602e */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 466021: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466025: push edx */
	m->esp -= 4; M32(m->esp) = 0x46602bu; native_call(m, 0x49ef24u);	/* 466026: call 0x49ef24 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46602b: add esp, 4 */
L_46602e:
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 46602e: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466032: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_466043;	/* 466034: jle 0x466043 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 466036: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46603a: push eax */
	m->esp -= 4; M32(m->esp) = 0x466040u; native_call(m, 0x49ef24u);	/* 46603b: call 0x49ef24 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466040: add esp, 4 */
L_466043:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 466043: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466047: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_466058;	/* 466049: jle 0x466058 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 46604b: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46604f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x466055u; native_call(m, 0x49ef24u);	/* 466050: call 0x49ef24 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466055: add esp, 4 */
L_466058:
	m->ecx = m->esi;	/* 466058: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x46605fu; native_call(m, 0x4666d0u);	/* 46605a: call 0x4666d0 */
	m->eax = (DWORD)(m->esi + 0x20u);	/* 46605f: lea eax, [esi + 0x20] */
	m->edx = (DWORD)(m->esi + 0x34u);	/* 466062: lea edx, [esi + 0x34] */
	m->ecx = m->eax;	/* 466065: mov ecx, eax */
	m->edi = m->edx;	/* 466067: mov edi, edx */
	m->ebx = M32((DWORD)(m->ecx + 0x0u));	/* 466069: mov ebx, dword ptr [ecx] */
	M32((DWORD)(m->edi + 0x0u)) = m->ebx;	/* 46606b: mov dword ptr [edi], ebx */
	m->ebx = M32((DWORD)(m->ecx + 0x4u));	/* 46606d: mov ebx, dword ptr [ecx + 4] */
	M32((DWORD)(m->edi + 0x4u)) = m->ebx;	/* 466070: mov dword ptr [edi + 4], ebx */
	m->ebx = M32((DWORD)(m->eax + 0x0u));	/* 466073: mov ebx, dword ptr [eax] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 466075: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edi + 0x8u)) = m->ecx;	/* 466078: mov dword ptr [edi + 8], ecx */
	m->edi = (DWORD)(m->esi + 0x40u);	/* 46607b: lea edi, [esi + 0x40] */
	m->ecx = m->edi;	/* 46607e: mov ecx, edi */
	M32((DWORD)(m->ecx + 0x0u)) = m->ebx;	/* 466080: mov dword ptr [ecx], ebx */
	m->ebx = M32((DWORD)(m->eax + 0x4u));	/* 466082: mov ebx, dword ptr [eax + 4] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 466085: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x4u)) = m->ebx;	/* 466088: mov dword ptr [ecx + 4], ebx */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 46608b: mov dword ptr [ecx + 8], eax */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46608e: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466091: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_466112;	/* 466093: jle 0x466112 */
	m->ecx = M32((DWORD)(m->esi + 0x14u));	/* 466095: mov ecx, dword ptr [esi + 0x14] */
	m->ebx = m->eax;	/* 466098: mov ebx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46609a: add ecx, 0x6c */
L_46609d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 46609d: fld dword ptr [edx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0xfffffffcu)); FPOP();	/* 46609f: fcomp dword ptr [ecx - 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4660a2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4660a4: test ah, 0x41 */
	if (!m->zf) goto L_4660ae;	/* 4660a7: jne 0x4660ae */
	m->eax = M32((DWORD)(m->ecx + 0xfffffffcu));	/* 4660a9: mov eax, dword ptr [ecx - 4] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 4660ac: mov dword ptr [edx], eax */
L_4660ae:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x38u)));	/* 4660ae: fld dword ptr [esi + 0x38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x0u)); FPOP();	/* 4660b1: fcomp dword ptr [ecx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4660b3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4660b5: test ah, 0x41 */
	if (!m->zf) goto L_4660bf;	/* 4660b8: jne 0x4660bf */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 4660ba: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->esi + 0x38u)) = m->eax;	/* 4660bc: mov dword ptr [esi + 0x38], eax */
L_4660bf:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3cu)));	/* 4660bf: fld dword ptr [esi + 0x3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x4u)); FPOP();	/* 4660c2: fcomp dword ptr [ecx + 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4660c5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4660c7: test ah, 0x41 */
	if (!m->zf) goto L_4660d2;	/* 4660ca: jne 0x4660d2 */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 4660cc: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->esi + 0x3cu)) = m->eax;	/* 4660cf: mov dword ptr [esi + 0x3c], eax */
L_4660d2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 4660d2: fld dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x8u)); FPOP();	/* 4660d4: fcomp dword ptr [ecx + 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4660d7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4660d9: test ah, 1 */
	if (m->zf) goto L_4660e3;	/* 4660dc: je 0x4660e3 */
	m->eax = M32((DWORD)(m->ecx + 0x8u));	/* 4660de: mov eax, dword ptr [ecx + 8] */
	M32((DWORD)(m->edi + 0x0u)) = m->eax;	/* 4660e1: mov dword ptr [edi], eax */
L_4660e3:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 4660e3: fld dword ptr [esi + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0xcu)); FPOP();	/* 4660e6: fcomp dword ptr [ecx + 0xc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4660e9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4660eb: test ah, 1 */
	if (m->zf) goto L_4660f6;	/* 4660ee: je 0x4660f6 */
	m->eax = M32((DWORD)(m->ecx + 0xcu));	/* 4660f0: mov eax, dword ptr [ecx + 0xc] */
	M32((DWORD)(m->esi + 0x44u)) = m->eax;	/* 4660f3: mov dword ptr [esi + 0x44], eax */
L_4660f6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x48u)));	/* 4660f6: fld dword ptr [esi + 0x48] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x10u)); FPOP();	/* 4660f9: fcomp dword ptr [ecx + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4660fc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4660fe: test ah, 1 */
	if (m->zf) goto L_466109;	/* 466101: je 0x466109 */
	m->eax = M32((DWORD)(m->ecx + 0x10u));	/* 466103: mov eax, dword ptr [ecx + 0x10] */
	M32((DWORD)(m->esi + 0x48u)) = m->eax;	/* 466106: mov dword ptr [esi + 0x48], eax */
L_466109:
	{ DWORD a_ = m->ecx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 466109: add ecx, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 46610f: dec ebx */
	if (!m->zf) goto L_46609d;	/* 466110: jne 0x46609d */
L_466112:
	m->edi = M32(m->esp); m->esp += 4;	/* 466112: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 466113: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 466114: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 466115: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x2d4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466116: add esp, 0x2d4 */
	m->esp += 4 + 12; return;	/* 46611c: ret 0xc */
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
