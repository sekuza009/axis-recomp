/* ---- emulated machine for lifted functions (tools/lift.py) ---- */
#if 0 /* X86 comes from the earlier lifted file */
typedef struct { DWORD eax, ecx, edx, ebx, esp, ebp, esi, edi; int zf, sf, cf, of; long double fs[8]; int ft; DWORD fsw; } X86;
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

static void lift_46cc30(X86 *m);
static void lift_46cdc0(X86 *m);
static void lift_42c650(X86 *m);
static void lift_42c910(X86 *m);
static void lift_41e7c0(X86 *m);
static void lift_41e260(X86 *m);
static void lift_445f70(X86 *m);
static void lift_447320(X86 *m);
static void lift_443af0(X86 *m);
static void lift_43f160(X86 *m);
static void lift_4435f0(X86 *m);
static void lift_42d7f0(X86 *m);
static void lift_40d4e0(X86 *m);
static void lift_42cba0(X86 *m);
static void lift_46cbe0(X86 *m);

/* FUN_0046cbe0 (0x46cbe0), lifted by tools/lift.py */
static void lift_46cbe0(X86 *m)
{
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46cbe0: mov edx, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 46cbe4: mov ecx, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 46cbe8: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46cbec: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 46cbed: mov esi, dword ptr [esp + 8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46cbf1: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cbf2: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cbf3: push ecx */
	m->edi = m->eax;	/* 46cbf4: mov edi, eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cbf6: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46cbf7: push esi */
	{ long long p_ = (long long)(int)m->edi * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 46cbf8: imul edi, ecx */
	m->esp -= 4; M32(m->esp) = 0x46cc00u; native_call(m, 0x49e836u);	/* 46cbfb: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cc00: add esp, 0x10 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46cc03: xor edx, edx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cc05: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46cc28;	/* 46cc07: jle 0x46cc28 */
L_46cc09:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + m->esi*1 + 0x0u))) & 0xff) << 0);	/* 46cc09: mov cl, byte ptr [edx + esi] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x59u & 0xffu, r_ = a_ ^ b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 46cc0c: xor cl, 0x59 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46cc0f: test cl, 0x80 */
	M8((DWORD)(m->edx + m->esi*1 + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 46cc12: mov byte ptr [edx + esi], cl */
	if (m->zf) goto L_46cc1e;	/* 46cc15: je 0x46cc1e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 46cc17: shl cl, 1 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 46cc19: or cl, 1 */
	goto L_46cc20;	/* 46cc1c: jmp 0x46cc20 */
L_46cc1e:
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 46cc1e: shl cl, 1 */
L_46cc20:
	M8((DWORD)(m->edx + m->esi*1 + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 46cc20: mov byte ptr [edx + esi], cl */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 46cc23: inc edx */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cc24: cmp edx, edi */
	if (m->sf != m->of) goto L_46cc09;	/* 46cc26: jl 0x46cc09 */
L_46cc28:
	m->edi = M32(m->esp); m->esp += 4;	/* 46cc28: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46cc29: pop esi */
	m->esp += 4 + 0; return;	/* 46cc2a: ret  */
}

/* FUN_0046cc30 (0x46cc30), lifted by tools/lift.py */
static void lift_46cc30(X86 *m)
{
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 46cc30: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cc34: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 46cc35: mov ebx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46cc39: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46cc3a: push edi */
	m->edi = m->edx;	/* 46cc3b: mov edi, edx */
	{ long long p_ = (long long)(int)m->edi * (int)m->ebx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 46cc3d: imul edi, ebx */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 46cc40: mov esi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46cc44: xor ecx, ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cc46: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46cc66;	/* 46cc48: jle 0x46cc66 */
L_46cc4a:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + m->esi*1 + 0x0u))) & 0xff) << 0);	/* 46cc4a: mov al, byte ptr [ecx + esi] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46cc4d: test al, 1 */
	if (m->zf) goto L_46cc57;	/* 46cc4f: je 0x46cc57 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 8); m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 46cc51: shr al, 1 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 46cc53: or al, 0x80 */
	goto L_46cc59;	/* 46cc55: jmp 0x46cc59 */
L_46cc57:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 8); m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 46cc57: shr al, 1 */
L_46cc59:
	M8((DWORD)(m->ecx + m->esi*1 + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 46cc59: mov byte ptr [ecx + esi], al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x59u & 0xffu, r_ = a_ ^ b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 46cc5c: xor al, 0x59 */
	M8((DWORD)(m->ecx + m->esi*1 + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 46cc5e: mov byte ptr [ecx + esi], al */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 46cc61: inc ecx */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cc62: cmp ecx, edi */
	if (m->sf != m->of) goto L_46cc4a;	/* 46cc64: jl 0x46cc4a */
L_46cc66:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 46cc66: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cc6a: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cc6b: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cc6c: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46cc6d: push esi */
	m->esp -= 4; M32(m->esp) = 0x46cc73u; native_call(m, 0x49f58au);	/* 46cc6e: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cc73: add esp, 0x10 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46cc76: xor edx, edx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cc78: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_46cc9b;	/* 46cc7a: jle 0x46cc9b */
L_46cc7c:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + m->esi*1 + 0x0u))) & 0xff) << 0);	/* 46cc7c: mov cl, byte ptr [edx + esi] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x59u & 0xffu, r_ = a_ ^ b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 46cc7f: xor cl, 0x59 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46cc82: test cl, 0x80 */
	M8((DWORD)(m->edx + m->esi*1 + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 46cc85: mov byte ptr [edx + esi], cl */
	if (m->zf) goto L_46cc91;	/* 46cc88: je 0x46cc91 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 46cc8a: shl cl, 1 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 46cc8c: or cl, 1 */
	goto L_46cc93;	/* 46cc8f: jmp 0x46cc93 */
L_46cc91:
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 46cc91: shl cl, 1 */
L_46cc93:
	M8((DWORD)(m->edx + m->esi*1 + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 46cc93: mov byte ptr [edx + esi], cl */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 46cc96: inc edx */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cc97: cmp edx, edi */
	if (m->sf != m->of) goto L_46cc7c;	/* 46cc99: jl 0x46cc7c */
L_46cc9b:
	m->edi = M32(m->esp); m->esp += 4;	/* 46cc9b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46cc9c: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46cc9d: pop ebx */
	m->esp += 4 + 0; return;	/* 46cc9e: ret  */
}

/* match_46cdc0 (0x46cdc0), lifted by tools/lift.py */
static void lift_46cdc0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46cdc0: push esi */
	m->esi = m->ecx;	/* 46cdc1: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 46cdc3: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cdc6: test eax, eax */
	if (m->zf) goto L_46cdd3;	/* 46cdc8: je 0x46cdd3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cdca: push eax */
	m->esp -= 4; M32(m->esp) = 0x46cdd0u; native_call(m, 0x49e7e0u);	/* 46cdcb: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cdd0: add esp, 4 */
L_46cdd3:
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 46cdd3: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cdd7: push 0x4ad170 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cddc: push eax */
	m->esp -= 4; M32(m->esp) = 0x46cde2u; native_call(m, 0x49e9cau);	/* 46cddd: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cde2: add esp, 8 */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 46cde5: mov dword ptr [esi + 4], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cde8: test eax, eax */
	if (m->zf) goto L_46ce3c;	/* 46cdea: je 0x46ce3c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cdec: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cded: push 1 */
	m->ecx = (DWORD)(m->esi + 0x8u);	/* 46cdef: lea ecx, [esi + 8] */
	{ DWORD v_ = 0xeu; m->esp -= 4; M32(m->esp) = v_; }	/* 46cdf2: push 0xe */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cdf4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46cdfau; native_call(m, 0x49e836u);	/* 46cdf5: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cdfa: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cdfd: cmp eax, 1 */
	if (m->cf) goto L_46ce3c;	/* 46ce00: jb 0x46ce3c */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 46ce02: mov edx, dword ptr [esi + 4] */
	m->eax = (DWORD)(m->esi + 0x16u);	/* 46ce05: lea eax, [esi + 0x16] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ce08: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ce09: push 1 */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ce0b: push 0x28 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ce0d: push eax */
	m->esp -= 4; M32(m->esp) = 0x46ce13u; native_call(m, 0x49e836u);	/* 46ce0e: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ce13: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ce16: cmp eax, 1 */
	if (m->cf) goto L_46ce3c;	/* 46ce19: jb 0x46ce3c */
	{ DWORD a_ = M16((DWORD)(m->esi + 0x24u)), b_ = 0x18u & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 46ce1b: cmp word ptr [esi + 0x24], 0x18 */
	if (!m->zf) goto L_46ce3c;	/* 46ce20: jne 0x46ce3c */
	m->eax = M32((DWORD)(m->esi + 0x26u));	/* 46ce22: mov eax, dword ptr [esi + 0x26] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46ce25: test eax, eax */
	if (!m->zf) goto L_46ce3c;	/* 46ce27: jne 0x46ce3c */
	m->ecx = M32((DWORD)(m->esi + 0x1au));	/* 46ce29: mov ecx, dword ptr [esi + 0x1a] */
	m->edx = M32((DWORD)(m->esi + 0x1eu));	/* 46ce2c: mov edx, dword ptr [esi + 0x1e] */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 46ce2f: mov eax, dword ptr [esi + 4] */
	M32((DWORD)(m->esi + 0x3eu)) = m->ecx;	/* 46ce32: mov dword ptr [esi + 0x3e], ecx */
	M32((DWORD)(m->esi + 0x42u)) = m->edx;	/* 46ce35: mov dword ptr [esi + 0x42], edx */
	m->esi = M32(m->esp); m->esp += 4;	/* 46ce38: pop esi */
	m->esp += 4 + 4; return;	/* 46ce39: ret 4 */
L_46ce3c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46ce3c: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 46ce3e: pop esi */
	m->esp += 4 + 4; return;	/* 46ce3f: ret 4 */
}

/* cfg_parsePlayer (0x42c650), lifted by tools/lift.py */
static void lift_42c650(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c650: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 42c651: mov esi, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c655: push esi */
	{ DWORD v_ = 0x4b1830u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c656: push 0x4b1830 */
	m->esp -= 4; M32(m->esp) = 0x42c660u; native_call(m, 0x49f167u);	/* 42c65b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c660: push esi */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c661: push 0x4dedb0 */
	m->esp -= 4; M32(m->esp) = 0x42c66bu; native_call(m, 0x49f167u);	/* 42c666: call 0x49f167 */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c66b: push 0x4b182c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c670: push esi */
	m->esp -= 4; M32(m->esp) = 0x42c676u; native_call(m, 0x49f135u);	/* 42c671: call 0x49f135 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c676: push esi */
	{ DWORD v_ = 0x4b1818u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c677: push 0x4b1818 */
	m->esp -= 4; M32(m->esp) = 0x42c681u; native_call(m, 0x49f167u);	/* 42c67c: call 0x49f167 */
	m->eax = M32((DWORD)(0x4dedd0u));	/* 42c681: mov eax, dword ptr [0x4dedd0] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c686: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42c689: sub eax, 0 */
	if (m->zf) goto L_42c6a4;	/* 42c68c: je 0x42c6a4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42c68e: dec eax */
	if (m->zf) goto L_42c69c;	/* 42c68f: je 0x42c69c */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42c691: dec eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c692: push esi */
	if (!m->zf) goto L_42c6a5;	/* 42c693: jne 0x42c6a5 */
	{ DWORD v_ = 0x4b1810u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c695: push 0x4b1810 */
	goto L_42c6aa;	/* 42c69a: jmp 0x42c6aa */
L_42c69c:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c69c: push esi */
	{ DWORD v_ = 0x4b1808u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c69d: push 0x4b1808 */
	goto L_42c6aa;	/* 42c6a2: jmp 0x42c6aa */
L_42c6a4:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6a4: push esi */
L_42c6a5:
	{ DWORD v_ = 0x4b1800u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6a5: push 0x4b1800 */
L_42c6aa:
	m->esp -= 4; M32(m->esp) = 0x42c6afu; native_call(m, 0x49f167u);	/* 42c6aa: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c6af: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6b2: push esi */
	{ DWORD v_ = 0x4b17e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6b3: push 0x4b17e8 */
	m->esp -= 4; M32(m->esp) = 0x42c6bdu; native_call(m, 0x49f167u);	/* 42c6b8: call 0x49f167 */
	m->eax = M32((DWORD)(0x4dedd4u));	/* 42c6bd: mov eax, dword ptr [0x4dedd4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c6c2: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42c6c5: cmp eax, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6c8: push esi */
	if (!m->zf) goto L_42c6d2;	/* 42c6c9: jne 0x42c6d2 */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6cb: push 0x4b17e4 */
	goto L_42c6d7;	/* 42c6d0: jmp 0x42c6d7 */
L_42c6d2:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6d2: push 0x4b17dc */
L_42c6d7:
	m->esp -= 4; M32(m->esp) = 0x42c6dcu; native_call(m, 0x49f167u);	/* 42c6d7: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c6dc: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6df: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6e0: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42c6eau; native_call(m, 0x49f167u);	/* 42c6e5: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c6ea: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42c6ed: pop esi */
	m->esp += 4 + 0; return;	/* 42c6ee: ret  */
}

/* cfg_parseSound (0x42c910), lifted by tools/lift.py */
static void lift_42c910(X86 *m)
{
	m->ecx = M32((DWORD)(0x4e0c90u));	/* 42c910: mov ecx, dword ptr [0x4e0c90] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c916: sub esp, 0xc */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 42c919: lea eax, [esp] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c91d: push esi */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 42c91e: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c920: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c921: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c927u; native_call(m, 0x49fb53u);	/* 42c922: call 0x49fb53 */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 42c927: mov esi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c92b: push esi */
	{ DWORD v_ = 0x4b1a4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c92c: push 0x4b1a4c */
	m->esp -= 4; M32(m->esp) = 0x42c936u; native_call(m, 0x49f167u);	/* 42c931: call 0x49f167 */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 42c936: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c93a: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c93b: push edx */
	m->esp -= 4; M32(m->esp) = 0x42c941u; native_call(m, 0x49f167u);	/* 42c93c: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c941: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c942: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42c94cu; native_call(m, 0x49f167u);	/* 42c947: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4e0c94u));	/* 42c94c: mov ecx, dword ptr [0x4e0c94] */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 42c952: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 42c956: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c958: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c959: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c95fu; native_call(m, 0x49fb53u);	/* 42c95a: call 0x49fb53 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c95f: push esi */
	{ DWORD v_ = 0x4b1a34u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c960: push 0x4b1a34 */
	m->esp -= 4; M32(m->esp) = 0x42c96au; native_call(m, 0x49f167u);	/* 42c965: call 0x49f167 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 42c96a: lea edx, [esp + 0x3c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c96e: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c96f: push edx */
	m->esp -= 4; M32(m->esp) = 0x42c975u; native_call(m, 0x49f167u);	/* 42c970: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c975: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c978: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c979: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42c983u; native_call(m, 0x49f167u);	/* 42c97e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c983: push esi */
	{ DWORD v_ = 0x4b1a20u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c984: push 0x4b1a20 */
	m->esp -= 4; M32(m->esp) = 0x42c98eu; native_call(m, 0x49f167u);	/* 42c989: call 0x49f167 */
	m->eax = M32((DWORD)(0x4e0c98u));	/* 42c98e: mov eax, dword ptr [0x4e0c98] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c993: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42c996: cmp eax, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c999: push esi */
	if (!m->zf) goto L_42c9a3;	/* 42c99a: jne 0x42c9a3 */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c99c: push 0x4b17e4 */
	goto L_42c9a8;	/* 42c9a1: jmp 0x42c9a8 */
L_42c9a3:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9a3: push 0x4b17dc */
L_42c9a8:
	m->esp -= 4; M32(m->esp) = 0x42c9adu; native_call(m, 0x49f167u);	/* 42c9a8: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c9ad: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9b0: push esi */
	{ DWORD v_ = 0x4b1a04u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9b1: push 0x4b1a04 */
	m->esp -= 4; M32(m->esp) = 0x42c9bbu; native_call(m, 0x49f167u);	/* 42c9b6: call 0x49f167 */
	m->eax = M32((DWORD)(0x4e0c9cu));	/* 42c9bb: mov eax, dword ptr [0x4e0c9c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c9c0: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42c9c3: cmp eax, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9c6: push esi */
	if (!m->zf) goto L_42c9d0;	/* 42c9c7: jne 0x42c9d0 */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9c9: push 0x4b17e4 */
	goto L_42c9d5;	/* 42c9ce: jmp 0x42c9d5 */
L_42c9d0:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9d0: push 0x4b17dc */
L_42c9d5:
	m->esp -= 4; M32(m->esp) = 0x42c9dau; native_call(m, 0x49f167u);	/* 42c9d5: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c9da: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9dd: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9de: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42c9e8u; native_call(m, 0x49f167u);	/* 42c9e3: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c9e8: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42c9eb: pop esi */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c9ec: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 42c9ef: ret  */
}

/* console_loadFile (0x41e7c0), lifted by tools/lift.py */
static void lift_41e7c0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 41e7c0: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->esp, b_ = 0x400u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e7c4: sub esp, 0x400 */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41e7ca: shl eax, 5 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e7cd: push edi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e7ce: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->eax + 0x907b30u);	/* 41e7d1: lea edx, [eax + 0x907b30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41e7d7: xor eax, eax */
	m->edi = m->edx;	/* 41e7d9: mov edi, edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41e7db: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41e7dd: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41e7df: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e7e0: cmp ecx, 1 */
	if (!m->cf && !m->zf) goto L_41e7ed;	/* 41e7e3: ja 0x41e7ed */
	m->edi = M32(m->esp); m->esp += 4;	/* 41e7e5: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x400u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e7e6: add esp, 0x400 */
	m->esp += 4 + 0; return;	/* 41e7ec: ret  */
L_41e7ed:
	m->ecx = 0x100u;	/* 41e7ed: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41e7f2: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x4u);	/* 41e7f4: lea edi, [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e7f8: push ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41e7f9: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e7fb: or ecx, 0xffffffff */
	m->edi = 0x4b0434u;	/* 41e7fe: mov edi, 0x4b0434 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41e803: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41e805: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41e807: sub edi, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e809: push esi */
	m->ebx = (DWORD)(m->esp + 0xcu);	/* 41e80a: lea ebx, [esp + 0xc] */
	m->eax = m->ecx;	/* 41e80e: mov eax, ecx */
	m->esi = m->edi;	/* 41e810: mov esi, edi */
	m->edi = m->ebx;	/* 41e812: mov edi, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41e814: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41e817: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41e819: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41e81b: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e81d: and ecx, 3 */
	m->ebx = (DWORD)(m->esp + 0xcu);	/* 41e820: lea ebx, [esp + 0xc] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41e824: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = m->edx;	/* 41e826: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e828: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41e82b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41e82d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41e82f: sub edi, ecx */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e831: push 0x4ad170 */
	m->esi = m->edi;	/* 41e836: mov esi, edi */
	m->edx = m->ecx;	/* 41e838: mov edx, ecx */
	m->edi = m->ebx;	/* 41e83a: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e83c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41e83f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41e841: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41e843: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41e844: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41e847: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41e849: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 41e84b: lea edx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e84f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41e852: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b042cu;	/* 41e854: mov edi, 0x4b042c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e859: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41e85c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41e85e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41e860: sub edi, ecx */
	m->esi = m->edi;	/* 41e862: mov esi, edi */
	m->ebx = m->ecx;	/* 41e864: mov ebx, ecx */
	m->edi = m->edx;	/* 41e866: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e868: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41e86b: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 41e86d: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41e86f: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41e870: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41e873: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 41e875: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 41e877: lea eax, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41e87b: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41e87e: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41e87f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x41e886u; native_call(m, 0x49e9cau);	/* 41e881: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e886: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e889: test eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 41e88b: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41e88c: pop ebx */
	if (!m->zf) goto L_41e897;	/* 41e88d: jne 0x41e897 */
	m->edi = M32(m->esp); m->esp += 4;	/* 41e88f: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x400u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e890: add esp, 0x400 */
	m->esp += 4 + 0; return;	/* 41e896: ret  */
L_41e897:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41e897: push eax */
	m->esp -= 4; M32(m->esp) = 0x41e89du; native_call(m, 0x49e7e0u);	/* 41e898: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e89d: add esp, 4 */
	m->eax = 0x1u;	/* 41e8a0: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 41e8a5: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x400u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e8a6: add esp, 0x400 */
	m->esp += 4 + 0; return;	/* 41e8ac: ret  */
}

/* app_checkLauncherRunning (0x41e260), lifted by tools/lift.py */
static void lift_41e260(X86 *m)
{
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41e260: xor eax, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e262: push esi */
	M32((DWORD)(0x4dd988u)) = m->eax;	/* 41e263: mov dword ptr [0x4dd988], eax */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e268: push 0x4ad170 */
	M32((DWORD)(0x4dd98cu)) = m->eax;	/* 41e26d: mov dword ptr [0x4dd98c], eax */
	{ DWORD v_ = 0x4b03b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e272: push 0x4b03b4 */
	M32((DWORD)(0x4dd990u)) = m->eax;	/* 41e277: mov dword ptr [0x4dd990], eax */
	m->esp -= 4; M32(m->esp) = 0x41e281u; native_call(m, 0x49e9cau);	/* 41e27c: call 0x49e9ca */
	m->esi = m->eax;	/* 41e281: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e283: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e286: test esi, esi */
	if (!m->zf) goto L_41e28c;	/* 41e288: jne 0x41e28c */
	m->esi = M32(m->esp); m->esp += 4;	/* 41e28a: pop esi */
	m->esp += 4 + 0; return;	/* 41e28b: ret  */
L_41e28c:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e28c: push 0 */
	{ DWORD v_ = 0x1a2bu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e28e: push 0x1a2b */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e293: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e299u; native_call(m, 0x49e91eu);	/* 41e294: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e299: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e29a: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e29c: push 1 */
	{ DWORD v_ = 0x4dd988u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e29e: push 0x4dd988 */
	m->esp -= 4; M32(m->esp) = 0x41e2a8u; native_call(m, 0x49e836u);	/* 41e2a3: call 0x49e836 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2a8: push 0 */
	{ DWORD v_ = 0x1a2cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2aa: push 0x1a2c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2af: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e2b5u; native_call(m, 0x49e91eu);	/* 41e2b0: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2b5: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2b6: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2b8: push 1 */
	{ DWORD v_ = 0x4dd989u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2ba: push 0x4dd989 */
	m->esp -= 4; M32(m->esp) = 0x41e2c4u; native_call(m, 0x49e836u);	/* 41e2bf: call 0x49e836 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2c4: push 0 */
	{ DWORD v_ = 0x2dbfu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2c6: push 0x2dbf */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2cb: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e2d1u; native_call(m, 0x49e91eu);	/* 41e2cc: call 0x49e91e */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e2d1: add esp, 0x44 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2d4: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2d5: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2d7: push 1 */
	{ DWORD v_ = 0x4dd98au; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2d9: push 0x4dd98a */
	m->esp -= 4; M32(m->esp) = 0x41e2e3u; native_call(m, 0x49e836u);	/* 41e2de: call 0x49e836 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2e3: push 0 */
	{ DWORD v_ = 0x2dc0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2e5: push 0x2dc0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2ea: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e2f0u; native_call(m, 0x49e91eu);	/* 41e2eb: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2f0: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2f1: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2f3: push 1 */
	{ DWORD v_ = 0x4dd98bu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2f5: push 0x4dd98b */
	m->esp -= 4; M32(m->esp) = 0x41e2ffu; native_call(m, 0x49e836u);	/* 41e2fa: call 0x49e836 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e2ff: push 0 */
	{ DWORD v_ = 0x38a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e301: push 0x38a4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e306: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e30cu; native_call(m, 0x49e91eu);	/* 41e307: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e30c: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e30d: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e30f: push 1 */
	{ DWORD v_ = 0x4dd98cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e311: push 0x4dd98c */
	m->esp -= 4; M32(m->esp) = 0x41e31bu; native_call(m, 0x49e836u);	/* 41e316: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e31b: add esp, 0x48 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e31e: push 0 */
	{ DWORD v_ = 0x38a5u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e320: push 0x38a5 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e325: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e32bu; native_call(m, 0x49e91eu);	/* 41e326: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e32b: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e32c: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e32e: push 1 */
	{ DWORD v_ = 0x4dd98du; m->esp -= 4; M32(m->esp) = v_; }	/* 41e330: push 0x4dd98d */
	m->esp -= 4; M32(m->esp) = 0x41e33au; native_call(m, 0x49e836u);	/* 41e335: call 0x49e836 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e33a: push 0 */
	{ DWORD v_ = 0x55f1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e33c: push 0x55f1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e341: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e347u; native_call(m, 0x49e91eu);	/* 41e342: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e347: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e348: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e34a: push 1 */
	{ DWORD v_ = 0x4dd98eu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e34c: push 0x4dd98e */
	m->esp -= 4; M32(m->esp) = 0x41e356u; native_call(m, 0x49e836u);	/* 41e351: call 0x49e836 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e356: push 0 */
	{ DWORD v_ = 0x55f2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e358: push 0x55f2 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e35d: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e363u; native_call(m, 0x49e91eu);	/* 41e35e: call 0x49e91e */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e363: add esp, 0x44 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e366: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e367: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e369: push 1 */
	{ DWORD v_ = 0x4dd98fu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e36b: push 0x4dd98f */
	m->esp -= 4; M32(m->esp) = 0x41e375u; native_call(m, 0x49e836u);	/* 41e370: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e375: push esi */
	m->esp -= 4; M32(m->esp) = 0x41e37bu; native_call(m, 0x49e7e0u);	/* 41e376: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e37b: add esp, 0x14 */
	m->eax = 0x1u;	/* 41e37e: mov eax, 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41e383: pop esi */
	m->esp += 4 + 0; return;	/* 41e384: ret  */
}

/* profile_loadList (0x445f70), lifted by tools/lift.py */
static void lift_445f70(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445f70: sub esp, 0x188 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 445f76: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 445f79: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 445f7b: lea edx, [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 445f7f: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 445f80: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 445f81: push edi */
	m->edi = 0x9dae7cu;	/* 445f82: mov edi, 0x9dae7c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 445f87: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 445f89: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 445f8b: sub edi, ecx */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 445f8d: push 0x4b2ab0 */
	m->eax = m->ecx;	/* 445f92: mov eax, ecx */
	m->esi = m->edi;	/* 445f94: mov esi, edi */
	m->edi = m->edx;	/* 445f96: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 445f98: lea edx, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 445f9c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 445f9f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 445fa1: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 445fa3: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 445fa5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 445fa8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2ab4u;	/* 445faa: mov edi, 0x4b2ab4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 445faf: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 445fb2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 445fb4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 445fb6: sub edi, ecx */
	m->esi = m->edi;	/* 445fb8: mov esi, edi */
	m->ebx = m->ecx;	/* 445fba: mov ebx, ecx */
	m->edi = m->edx;	/* 445fbc: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 445fbe: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 445fc1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 445fc3: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 445fc5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 445fc6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 445fc9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 445fcb: mov eax, dword ptr [0x9f8d74] */
	m->ecx = m->ebx;	/* 445fd0: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 445fd2: and ecx, 3 */
	M32((DWORD)(0x9f8c58u)) = m->eax;	/* 445fd5: mov dword ptr [0x9f8c58], eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 445fda: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 445fdc: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445fe0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x445fe6u; native_call(m, 0x49e9cau);	/* 445fe1: call 0x49e9ca */
	m->esi = m->eax;	/* 445fe6: mov esi, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 445fe8: xor edi, edi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445fea: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445fed: cmp esi, edi */
	if (!m->zf) goto L_446001;	/* 445fef: jne 0x446001 */
	M32((DWORD)(0x9f9008u)) = m->edi;	/* 445ff1: mov dword ptr [0x9f9008], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 445ff7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 445ff8: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 445ff9: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445ffa: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 446000: ret  */
L_446001:
	m->edx = M32((DWORD)(m->esp + 0x198u));	/* 446001: mov edx, dword ptr [esp + 0x198] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446008: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446009: push 1 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 44600b: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44600f: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 446011: push eax */
	M32((DWORD)(m->esp + 0x1cu)) = 0xfefefef7u;	/* 446012: mov dword ptr [esp + 0x1c], 0xfefefef7 */
	M32((DWORD)(0x9f9008u)) = m->edx;	/* 44601a: mov dword ptr [0x9f9008], edx */
	M32((DWORD)(0x9f8c58u)) = m->edi;	/* 446020: mov dword ptr [0x9f8c58], edi */
	M32((DWORD)(0x9f8c4cu)) = m->edi;	/* 446026: mov dword ptr [0x9f8c4c], edi */
	M32((DWORD)(0x9f8c5cu)) = m->edi;	/* 44602c: mov dword ptr [0x9f8c5c], edi */
	m->esp -= 4; M32(m->esp) = 0x446037u; native_call(m, 0x49f58au);	/* 446032: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446037: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446038: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44603a: push 4 */
	{ DWORD v_ = 0x9f9008u; m->esp -= 4; M32(m->esp) = v_; }	/* 44603c: push 0x9f9008 */
	m->esp -= 4; M32(m->esp) = 0x446046u; native_call(m, 0x49f58au);	/* 446041: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446046: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446047: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446049: push 4 */
	{ DWORD v_ = 0x9f8c58u; m->esp -= 4; M32(m->esp) = v_; }	/* 44604b: push 0x9f8c58 */
	m->esp -= 4; M32(m->esp) = 0x446055u; native_call(m, 0x49f58au);	/* 446050: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446055: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446056: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446058: push 4 */
	{ DWORD v_ = 0x9f8c4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44605a: push 0x9f8c4c */
	m->esp -= 4; M32(m->esp) = 0x446064u; native_call(m, 0x49f58au);	/* 44605f: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446064: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446067: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446068: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44606a: push 4 */
	{ DWORD v_ = 0x9f8c5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44606c: push 0x9f8c5c */
	m->esp -= 4; M32(m->esp) = 0x446076u; native_call(m, 0x49f58au);	/* 446071: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446076: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446077: push 1 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 446079: push 0x20 */
	{ DWORD v_ = 0x9f8fe8u; m->esp -= 4; M32(m->esp) = v_; }	/* 44607b: push 0x9f8fe8 */
	m->esp -= 4; M32(m->esp) = 0x446085u; native_call(m, 0x49f58au);	/* 446080: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 446085: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44608a: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44608d: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_4460b1;	/* 44608f: jle 0x4460b1 */
	m->ebx = 0x9f6848u;	/* 446091: mov ebx, 0x9f6848 */
L_446096:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446096: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446097: push 1 */
	{ DWORD v_ = 0x48u; m->esp -= 4; M32(m->esp) = v_; }	/* 446099: push 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44609b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4460a1u; native_call(m, 0x49f58au);	/* 44609c: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 4460a1: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4460a6: add esp, 0x10 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 4460a9: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4460aa: add ebx, 0x48 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4460ad: cmp edi, eax */
	if (m->sf != m->of) goto L_446096;	/* 4460af: jl 0x446096 */
L_4460b1:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4460b1: push esi */
	m->esp -= 4; M32(m->esp) = 0x4460b7u; native_call(m, 0x49e7e0u);	/* 4460b2: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4460b7: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4460ba: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4460bb: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4460bc: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4460bd: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 4460c3: ret  */
}

/* profile_delete (0x447320), lifted by tools/lift.py */
static void lift_447320(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447320: sub esp, 0x188 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447326: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 447329: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 44732b: lea edx, [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44732f: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 447330: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 447331: push edi */
	m->edi = 0x9dae7cu;	/* 447332: mov edi, 0x9dae7c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 447337: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 447339: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44733b: sub edi, ecx */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44733d: push 0x4b2ab0 */
	m->eax = m->ecx;	/* 447342: mov eax, ecx */
	m->esi = m->edi;	/* 447344: mov esi, edi */
	m->edi = m->edx;	/* 447346: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 447348: lea edx, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44734c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44734f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 447351: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 447353: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447355: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 447358: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2ab4u;	/* 44735a: mov edi, 0x4b2ab4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44735f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 447362: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 447364: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 447366: sub edi, ecx */
	m->esi = m->edi;	/* 447368: mov esi, edi */
	m->ebx = m->ecx;	/* 44736a: mov ebx, ecx */
	m->edi = m->edx;	/* 44736c: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44736e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 447371: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 447373: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 447375: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 447376: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 447379: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9f8d74u));	/* 44737b: mov eax, dword ptr [0x9f8d74] */
	m->ecx = m->ebx;	/* 447380: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 447382: and ecx, 3 */
	M32((DWORD)(0x9f8c58u)) = m->eax;	/* 447385: mov dword ptr [0x9f8c58], eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44738a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 44738c: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 447390: push ecx */
	m->esp -= 4; M32(m->esp) = 0x447396u; native_call(m, 0x49e9cau);	/* 447391: call 0x49e9ca */
	m->ebx = m->eax;	/* 447396: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447398: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44739b: test ebx, ebx */
	if (!m->zf) goto L_4473ae;	/* 44739d: jne 0x4473ae */
	m->edi = M32(m->esp); m->esp += 4;	/* 44739f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4473a0: pop esi */
	M32((DWORD)(0x9f9008u)) = m->eax;	/* 4473a1: mov dword ptr [0x9f9008], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4473a6: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4473a7: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 4473ad: ret  */
L_4473ae:
	m->ecx = 0x8u;	/* 4473ae: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4473b3: xor eax, eax */
	m->edi = 0x9f8fe8u;	/* 4473b5: mov edi, 0x9f8fe8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4473ba: push ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4473bb: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9f8c58u));	/* 4473bd: mov eax, dword ptr [0x9f8c58] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4473c2: or ecx, 0xffffffff */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4473c5: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4473c7: push 4 */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4473c9: lea edx, [eax + eax*8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4473cc: xor eax, eax */
	M32((DWORD)(m->esp + 0x18u)) = 0xfefefef7u;	/* 4473ce: mov dword ptr [esp + 0x18], 0xfefefef7 */
	m->edi = (DWORD)(m->edx*8 + 0x9f684cu);	/* 4473d6: lea edi, [edx*8 + 0x9f684c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4473dd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4473df: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4473e1: sub edi, ecx */
	m->eax = m->ecx;	/* 4473e3: mov eax, ecx */
	m->esi = m->edi;	/* 4473e5: mov esi, edi */
	m->edi = 0x9f8fe8u;	/* 4473e7: mov edi, 0x9f8fe8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4473ec: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4473ef: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4473f1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4473f3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4473f6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 4473f8: lea ecx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4473fc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x447402u; native_call(m, 0x49f58au);	/* 4473fd: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447402: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447403: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 447405: push 4 */
	{ DWORD v_ = 0x9f9008u; m->esp -= 4; M32(m->esp) = v_; }	/* 447407: push 0x9f9008 */
	m->esp -= 4; M32(m->esp) = 0x447411u; native_call(m, 0x49f58au);	/* 44740c: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447411: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447412: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 447414: push 4 */
	{ DWORD v_ = 0x9f8c58u; m->esp -= 4; M32(m->esp) = v_; }	/* 447416: push 0x9f8c58 */
	m->esp -= 4; M32(m->esp) = 0x447420u; native_call(m, 0x49f58au);	/* 44741b: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447420: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447421: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 447423: push 4 */
	{ DWORD v_ = 0x9f8c4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 447425: push 0x9f8c4c */
	m->esp -= 4; M32(m->esp) = 0x44742fu; native_call(m, 0x49f58au);	/* 44742a: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44742f: add esp, 0x40 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447432: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447433: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 447435: push 4 */
	{ DWORD v_ = 0x9f8c5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 447437: push 0x9f8c5c */
	m->esp -= 4; M32(m->esp) = 0x447441u; native_call(m, 0x49f58au);	/* 44743c: call 0x49f58a */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447441: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447442: push 1 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 447444: push 0x20 */
	{ DWORD v_ = 0x9f8fe8u; m->esp -= 4; M32(m->esp) = v_; }	/* 447446: push 0x9f8fe8 */
	m->esp -= 4; M32(m->esp) = 0x447450u; native_call(m, 0x49f58au);	/* 44744b: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 447450: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447455: add esp, 0x20 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 447458: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44745a: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_44747e;	/* 44745c: jle 0x44747e */
	m->edi = 0x9f6848u;	/* 44745e: mov edi, 0x9f6848 */
L_447463:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 447463: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 447464: push 1 */
	{ DWORD v_ = 0x48u; m->esp -= 4; M32(m->esp) = v_; }	/* 447466: push 0x48 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 447468: push edi */
	m->esp -= 4; M32(m->esp) = 0x44746eu; native_call(m, 0x49f58au);	/* 447469: call 0x49f58a */
	m->eax = M32((DWORD)(0x9f9008u));	/* 44746e: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447473: add esp, 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 447476: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 447477: add edi, 0x48 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44747a: cmp esi, eax */
	if (m->sf != m->of) goto L_447463;	/* 44747c: jl 0x447463 */
L_44747e:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44747e: push ebx */
	m->esp -= 4; M32(m->esp) = 0x447484u; native_call(m, 0x49e7e0u);	/* 44747f: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447484: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 447487: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 447488: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 447489: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x188u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44748a: add esp, 0x188 */
	m->esp += 4 + 0; return;	/* 447490: ret  */
}

/* mission_saveAxisMis (0x443af0), lifted by tools/lift.py */
static void lift_443af0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x184u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443af0: sub esp, 0x184 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443af6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 443af9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 443afb: lea edx, [esp] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 443aff: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 443b00: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 443b01: push edi */
	m->edi = 0x9dae7cu;	/* 443b02: mov edi, 0x9dae7c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 443b07: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 443b09: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 443b0b: sub edi, ecx */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 443b0d: push 0x4ad170 */
	m->eax = m->ecx;	/* 443b12: mov eax, ecx */
	m->esi = m->edi;	/* 443b14: mov esi, edi */
	m->edi = m->edx;	/* 443b16: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 443b18: lea edx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 443b1c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 443b1f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 443b21: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 443b23: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443b25: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 443b28: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2aa4u;	/* 443b2a: mov edi, 0x4b2aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443b2f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 443b32: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 443b34: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 443b36: sub edi, ecx */
	m->esi = m->edi;	/* 443b38: mov esi, edi */
	m->ebx = m->ecx;	/* 443b3a: mov ebx, ecx */
	m->edi = m->edx;	/* 443b3c: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443b3e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 443b41: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 443b43: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 443b45: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 443b46: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 443b49: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 443b4b: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 443b4d: lea eax, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443b51: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443b54: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 443b55: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x443b5cu; native_call(m, 0x49e9cau);	/* 443b57: call 0x49e9ca */
	m->edi = m->eax;	/* 443b5c: mov edi, eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 443b5e: xor ebx, ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443b60: add esp, 8 */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443b63: cmp edi, ebx */
	if (m->zf) goto L_443c61;	/* 443b65: je 0x443c61 */
	m->esi = M32((DWORD)(m->esp + 0x194u));	/* 443b6b: mov esi, dword ptr [esp + 0x194] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 443b72: xor eax, eax */
	{ DWORD a_ = m->esi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443b74: cmp esi, ebx */
	if (m->zf || m->sf != m->of) goto L_443b8e;	/* 443b76: jle 0x443b8e */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 443b78: push ebp */
	m->ecx = 0x9ef3c4u;	/* 443b79: mov ecx, 0x9ef3c4 */
	m->edx = m->esi;	/* 443b7e: mov edx, esi */
L_443b80:
	m->ebp = M32((DWORD)(m->ecx + 0x0u));	/* 443b80: mov ebp, dword ptr [ecx] */
	{ DWORD a_ = m->ecx, b_ = 0xfcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 443b82: add ecx, 0xfc */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 443b88: add eax, ebp */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 443b8a: dec edx */
	if (!m->zf) goto L_443b80;	/* 443b8b: jne 0x443b80 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 443b8d: pop ebp */
L_443b8e:
	m->ecx = M32((DWORD)(0x9ef2c0u));	/* 443b8e: mov ecx, dword ptr [0x9ef2c0] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 443b94: push ebx */
	m->edx = m->ecx;	/* 443b95: mov edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 443b97: shl edx, 5 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 443b9a: sub edx, ecx */
	m->eax = (DWORD)(m->eax + m->edx*8 + 0x1au);	/* 443b9c: lea eax, [eax + edx*8 + 0x1a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443ba0: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 443ba1: push edi */
	m->esp -= 4; M32(m->esp) = 0x443ba7u; native_call(m, 0x49e91eu);	/* 443ba2: call 0x49e91e */
	m->eax = M32((DWORD)(0x9ef1ecu));	/* 443ba7: mov eax, dword ptr [0x9ef1ec] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443bac: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443baf: cmp eax, ebx */
	if (m->zf) goto L_443bbc;	/* 443bb1: je 0x443bbc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443bb3: push eax */
	m->esp -= 4; M32(m->esp) = 0x443bb9u; native_call(m, 0x49ee81u);	/* 443bb4: call 0x49ee81 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443bb9: add esp, 4 */
L_443bbc:
	m->ecx = m->esi;	/* 443bbc: mov ecx, esi */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 443bbe: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 443bc1: sub ecx, esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x9ef3c4u));	/* 443bc3: mov edx, dword ptr [ecx*4 + 0x9ef3c4] */
	m->esi = (DWORD)(m->ecx*4 + 0x9ef3c4u);	/* 443bca: lea esi, [ecx*4 + 0x9ef3c4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443bd1: push edx */
	m->esp -= 4; M32(m->esp) = 0x443bd7u; native_call(m, 0x49eeb0u);	/* 443bd2: call 0x49eeb0 */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 443bd7: mov ecx, dword ptr [esi] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 443bd9: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443bda: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443bdc: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443bdd: push eax */
	M32((DWORD)(0x9ef1ecu)) = m->eax;	/* 443bde: mov dword ptr [0x9ef1ec], eax */
	m->esp -= 4; M32(m->esp) = 0x443be8u; native_call(m, 0x49e836u);	/* 443be3: call 0x49e836 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 443be8: push edi */
	m->esp -= 4; M32(m->esp) = 0x443beeu; native_call(m, 0x49e7e0u);	/* 443be9: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443bee: add esp, 0x18 */
	m->ecx = 0x32u;	/* 443bf1: mov ecx, 0x32 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 443bf6: xor eax, eax */
	m->edi = 0x9eeadcu;	/* 443bf8: mov edi, 0x9eeadc */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 443bfd: rep stosd dword ptr es:[edi], eax */
	m->edx = M32((DWORD)(m->esi + 0x0u));	/* 443bff: mov edx, dword ptr [esi] */
	m->ecx = 0x190u;	/* 443c01: mov ecx, 0x190 */
	m->edi = 0x9f1064u;	/* 443c06: mov edi, 0x9f1064 */
	M32((DWORD)(0x9ef218u)) = m->ebx;	/* 443c0b: mov dword ptr [0x9ef218], ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 443c11: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x190u;	/* 443c13: mov ecx, 0x190 */
	m->edi = 0x9eebacu;	/* 443c18: mov edi, 0x9eebac */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 443c1d: rep stosd dword ptr es:[edi], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 443c1f: pop edi */
	M32((DWORD)(0x9ef1f4u)) = m->ebx;	/* 443c20: mov dword ptr [0x9ef1f4], ebx */
	M32((DWORD)(0x9f105cu)) = m->ebx;	/* 443c26: mov dword ptr [0x9f105c], ebx */
	M32((DWORD)(0x9eeba4u)) = m->ebx;	/* 443c2c: mov dword ptr [0x9eeba4], ebx */
	M32((DWORD)(0x4d7348u)) = m->ebx;	/* 443c32: mov dword ptr [0x4d7348], ebx */
	M32((DWORD)(0x9f1060u)) = m->ebx;	/* 443c38: mov dword ptr [0x9f1060], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 443c3e: pop esi */
	M32((DWORD)(0x9ef1f8u)) = 0x14u;	/* 443c3f: mov dword ptr [0x9ef1f8], 0x14 */
	M32((DWORD)(0x9ef200u)) = m->edx;	/* 443c49: mov dword ptr [0x9ef200], edx */
	M32((DWORD)(0x9f16b8u)) = 0x0u;	/* 443c4f: mov dword ptr [0x9f16b8], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 443c59: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443c5a: add esp, 0x184 */
	m->esp += 4 + 0; return;	/* 443c60: ret  */
L_443c61:
	{ DWORD v_ = 0xbu; m->esp -= 4; M32(m->esp) = v_; }	/* 443c61: push 0xb */
	m->esp -= 4; M32(m->esp) = 0x443c68u; native_call(m, 0x41ee40u);	/* 443c63: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443c68: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 443c6b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 443c6c: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 443c6d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443c6e: add esp, 0x184 */
	m->esp += 4 + 0; return;	/* 443c74: ret  */
}

/* arena_readLaunchFile (0x43f160), lifted by tools/lift.py */
static void lift_43f160(X86 *m)
{
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 43f160: mov edx, dword ptr [esp + 4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f164: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f165: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f166: push edi */
	m->edi = m->edx;	/* 43f167: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f169: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f16c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43f16e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43f170: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43f172: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x400u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f173: cmp ecx, 0x400 */
	if (m->cf || m->zf) goto L_43f193;	/* 43f179: jbe 0x43f193 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 43f17b: xor ebx, ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 43f17d: pop edi */
	M32((DWORD)(0x9dd88cu)) = m->ebx;	/* 43f17e: mov dword ptr [0x9dd88c], ebx */
	M32((DWORD)(0x76d410u)) = m->ebx;	/* 43f184: mov dword ptr [0x76d410], ebx */
	M32((DWORD)(0x76d364u)) = m->ebx;	/* 43f18a: mov dword ptr [0x76d364], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43f190: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43f191: pop ebx */
	m->esp += 4 + 0; return;	/* 43f192: ret  */
L_43f193:
	m->edi = m->edx;	/* 43f193: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f195: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f198: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43f19a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43f19c: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43f19e: dec ecx */
	m->edi = 0x1u;	/* 43f19f: mov edi, 1 */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f1a4: cmp ecx, edi */
	if (!m->cf && !m->zf) goto L_43f1c0;	/* 43f1a6: ja 0x43f1c0 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 43f1a8: xor ebx, ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 43f1aa: pop edi */
	M32((DWORD)(0x9dd88cu)) = m->ebx;	/* 43f1ab: mov dword ptr [0x9dd88c], ebx */
	M32((DWORD)(0x76d410u)) = m->ebx;	/* 43f1b1: mov dword ptr [0x76d410], ebx */
	M32((DWORD)(0x76d364u)) = m->ebx;	/* 43f1b7: mov dword ptr [0x76d364], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43f1bd: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43f1be: pop ebx */
	m->esp += 4 + 0; return;	/* 43f1bf: ret  */
L_43f1c0:
	{ DWORD v_ = 0x4b035cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f1c0: push 0x4b035c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f1c5: push edx */
	m->esp -= 4; M32(m->esp) = 0x43f1cbu; native_call(m, 0x49ec3bu);	/* 43f1c6: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f1cb: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 43f1ce: xor ebx, ebx */
	M32((DWORD)(0x9dd88cu)) = m->ebx;	/* 43f1d0: mov dword ptr [0x9dd88c], ebx */
	m->esi = 0x9dd890u;	/* 43f1d6: mov esi, 0x9dd890 */
L_43f1db:
	m->edx = M32((DWORD)(0x9dd88cu));	/* 43f1db: mov edx, dword ptr [0x9dd88c] */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 43f1e1: mov dword ptr [esi], eax */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43f1e3: add esi, 4 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 43f1e6: inc edx */
	{ DWORD v_ = 0x4b035cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f1e7: push 0x4b035c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f1ec: push ebx */
	M32((DWORD)(0x9dd88cu)) = m->edx;	/* 43f1ed: mov dword ptr [0x9dd88c], edx */
	m->esp -= 4; M32(m->esp) = 0x43f1f8u; native_call(m, 0x49ec3bu);	/* 43f1f3: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f1f8: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f1fb: cmp eax, ebx */
	if (!m->zf) goto L_43f1db;	/* 43f1fd: jne 0x43f1db */
	m->eax = M32((DWORD)(0x9dd88cu));	/* 43f1ff: mov eax, dword ptr [0x9dd88c] */
	M32((DWORD)(0x76d410u)) = m->ebx;	/* 43f204: mov dword ptr [0x76d410], ebx */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f20a: cmp eax, edi */
	M32((DWORD)(0x76d364u)) = m->ebx;	/* 43f20c: mov dword ptr [0x76d364], ebx */
	if (!m->zf) goto L_43f27a;	/* 43f212: jne 0x43f27a */
	m->eax = M32((DWORD)(0x9dd890u));	/* 43f214: mov eax, dword ptr [0x9dd890] */
	m->esi = 0x4b2880u;	/* 43f219: mov esi, 0x4b2880 */
L_43f21e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 43f21e: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43f220: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43f222: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_43f242;	/* 43f224: jne 0x43f242 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43f226: cmp cl, bl */
	if (m->zf) goto L_43f23e;	/* 43f228: je 0x43f23e */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 43f22a: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43f22d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43f22f: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_43f242;	/* 43f232: jne 0x43f242 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43f234: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43f237: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43f23a: cmp cl, bl */
	if (!m->zf) goto L_43f21e;	/* 43f23c: jne 0x43f21e */
L_43f23e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f23e: xor eax, eax */
	goto L_43f247;	/* 43f240: jmp 0x43f247 */
L_43f242:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43f242: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43f244: sbb eax, -1 */
L_43f247:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f247: cmp eax, ebx */
	if (!m->zf) goto L_43f2f8;	/* 43f249: jne 0x43f2f8 */
	{ DWORD v_ = 0x4ad5e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f24f: push 0x4ad5e0 */
	{ DWORD v_ = 0x4ad5e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f254: push 0x4ad5e4 */
	m->esp -= 4; M32(m->esp) = 0x43f25eu; native_call(m, 0x49e9cau);	/* 43f259: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f25e: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f261: cmp eax, ebx */
	if (m->zf) goto L_43f27a;	/* 43f263: je 0x43f27a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f265: push eax */
	M32((DWORD)(0x76d410u)) = m->edi;	/* 43f266: mov dword ptr [0x76d410], edi */
	M32((DWORD)(0x76d364u)) = m->edi;	/* 43f26c: mov dword ptr [0x76d364], edi */
	m->esp -= 4; M32(m->esp) = 0x43f277u; native_call(m, 0x49e7e0u);	/* 43f272: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f277: add esp, 4 */
L_43f27a:
	{ DWORD a_ = M32((DWORD)(0x9dd88cu)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f27a: cmp dword ptr [0x9dd88c], 3 */
	if (!m->zf) goto L_43f2f8;	/* 43f281: jne 0x43f2f8 */
	m->eax = M32((DWORD)(0x9dd894u));	/* 43f283: mov eax, dword ptr [0x9dd894] */
	m->esi = 0x4b287cu;	/* 43f288: mov esi, 0x4b287c */
L_43f28d:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 43f28d: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43f28f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43f291: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_43f2b1;	/* 43f293: jne 0x43f2b1 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43f295: cmp cl, bl */
	if (m->zf) goto L_43f2ad;	/* 43f297: je 0x43f2ad */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 43f299: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43f29c: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43f29e: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_43f2b1;	/* 43f2a1: jne 0x43f2b1 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43f2a3: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43f2a6: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43f2a9: cmp cl, bl */
	if (!m->zf) goto L_43f28d;	/* 43f2ab: jne 0x43f28d */
L_43f2ad:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f2ad: xor eax, eax */
	goto L_43f2b6;	/* 43f2af: jmp 0x43f2b6 */
L_43f2b1:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43f2b1: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43f2b3: sbb eax, -1 */
L_43f2b6:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f2b6: cmp eax, ebx */
	if (!m->zf) goto L_43f2f8;	/* 43f2b8: jne 0x43f2f8 */
	M32((DWORD)(0x76d410u)) = m->edi;	/* 43f2ba: mov dword ptr [0x76d410], edi */
	m->ecx = 0x100u;	/* 43f2c0: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f2c5: xor eax, eax */
	m->edi = 0x4de748u;	/* 43f2c7: mov edi, 0x4de748 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43f2cc: rep stosd dword ptr es:[edi], eax */
	m->edi = M32((DWORD)(0x9dd898u));	/* 43f2ce: mov edi, dword ptr [0x9dd898] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f2d4: or ecx, 0xffffffff */
	M32((DWORD)(0x76d364u)) = m->ebx;	/* 43f2d7: mov dword ptr [0x76d364], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43f2dd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43f2df: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43f2e1: sub edi, ecx */
	m->eax = m->ecx;	/* 43f2e3: mov eax, ecx */
	m->esi = m->edi;	/* 43f2e5: mov esi, edi */
	m->edi = 0x4de748u;	/* 43f2e7: mov edi, 0x4de748 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43f2ec: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43f2ef: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43f2f1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f2f3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43f2f6: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_43f2f8:
	m->edi = M32(m->esp); m->esp += 4;	/* 43f2f8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43f2f9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43f2fa: pop ebx */
	m->esp += 4 + 0; return;	/* 43f2fb: ret  */
}

/* mission_loadAxisMis (0x4435f0), lifted by tools/lift.py */
static void lift_4435f0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x184u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4435f0: sub esp, 0x184 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4435f6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4435f9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 4435fb: lea edx, [esp] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4435ff: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 443600: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 443601: push edi */
	m->edi = 0x9dae7cu;	/* 443602: mov edi, 0x9dae7c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 443607: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 443609: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44360b: sub edi, ecx */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 44360d: push 0x4ad170 */
	m->eax = m->ecx;	/* 443612: mov eax, ecx */
	m->esi = m->edi;	/* 443614: mov esi, edi */
	m->edi = m->edx;	/* 443616: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 443618: lea edx, [esp + 0x10] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44361c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44361f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 443621: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 443623: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443625: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 443628: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2aa4u;	/* 44362a: mov edi, 0x4b2aa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44362f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 443632: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 443634: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 443636: sub edi, ecx */
	m->esi = m->edi;	/* 443638: mov esi, edi */
	m->ebx = m->ecx;	/* 44363a: mov ebx, ecx */
	m->edi = m->edx;	/* 44363c: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44363e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 443641: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 443643: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 443645: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 443646: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 443649: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 44364b: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 44364d: lea eax, [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443651: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443654: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 443655: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x44365cu; native_call(m, 0x49e9cau);	/* 443657: call 0x49e9ca */
	m->esi = m->eax;	/* 44365c: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44365e: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 443661: test esi, esi */
	if (m->zf) goto L_443793;	/* 443663: je 0x443793 */
	m->esp -= 4; M32(m->esp) = 0x44366eu; native_call(m, 0x443570u);	/* 443669: call 0x443570 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44366e: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44366f: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443671: push 4 */
	{ DWORD v_ = 0x9ef2c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 443673: push 0x9ef2c0 */
	m->esp -= 4; M32(m->esp) = 0x44367du; native_call(m, 0x49e836u);	/* 443678: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44367d: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44367e: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443680: push 4 */
	{ DWORD v_ = 0x9ef2c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443682: push 0x9ef2c4 */
	m->esp -= 4; M32(m->esp) = 0x44368cu; native_call(m, 0x49e836u);	/* 443687: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44368c: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44368d: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44368f: push 4 */
	{ DWORD v_ = 0x9ef2c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 443691: push 0x9ef2c8 */
	m->esp -= 4; M32(m->esp) = 0x44369bu; native_call(m, 0x49e836u);	/* 443696: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44369b: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44369c: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44369e: push 4 */
	{ DWORD v_ = 0x9ef2ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 4436a0: push 0x9ef2cc */
	m->esp -= 4; M32(m->esp) = 0x4436aau; native_call(m, 0x49e836u);	/* 4436a5: call 0x49e836 */
	m->eax = M32((DWORD)(0x9ef2c0u));	/* 4436aa: mov eax, dword ptr [0x9ef2c0] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4436af: add esp, 0x40 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4436b2: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4436b4: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_443757;	/* 4436b6: jle 0x443757 */
	m->edi = 0x9ef2d4u;	/* 4436bc: mov edi, 0x9ef2d4 */
L_4436c1:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4436c1: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4436c2: push 1 */
	m->ecx = (DWORD)(m->edi + 0xfffffffcu);	/* 4436c4: lea ecx, [edi - 4] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4436c7: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4436c9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4436cfu; native_call(m, 0x49e836u);	/* 4436ca: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4436cf: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4436d0: push 1 */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 4436d2: push 0x40 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4436d4: push edi */
	m->esp -= 4; M32(m->esp) = 0x4436dau; native_call(m, 0x49e836u);	/* 4436d5: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4436da: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4436db: push 1 */
	m->edx = (DWORD)(m->edi + 0x40u);	/* 4436dd: lea edx, [edi + 0x40] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4436e0: push 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4436e2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4436e8u; native_call(m, 0x49e836u);	/* 4436e3: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4436e8: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4436e9: push 1 */
	m->eax = (DWORD)(m->edi + 0x60u);	/* 4436eb: lea eax, [edi + 0x60] */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 4436ee: push 0x80 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4436f3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4436f9u; native_call(m, 0x49e836u);	/* 4436f4: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4436f9: add esp, 0x40 */
	m->ecx = (DWORD)(m->edi + 0xe0u);	/* 4436fc: lea ecx, [edi + 0xe0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 443702: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443703: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443705: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443707: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44370du; native_call(m, 0x49e836u);	/* 443708: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44370d: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44370e: push 1 */
	m->edx = (DWORD)(m->edi + 0xe4u);	/* 443710: lea edx, [edi + 0xe4] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443716: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443718: push edx */
	m->esp -= 4; M32(m->esp) = 0x44371eu; native_call(m, 0x49e836u);	/* 443719: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44371e: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44371f: push 1 */
	m->eax = (DWORD)(m->edi + 0xe8u);	/* 443721: lea eax, [edi + 0xe8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443727: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443729: push eax */
	m->esp -= 4; M32(m->esp) = 0x44372fu; native_call(m, 0x49e836u);	/* 44372a: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44372f: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443730: push 1 */
	m->ecx = (DWORD)(m->edi + 0xecu);	/* 443732: lea ecx, [edi + 0xec] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443738: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44373a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443740u; native_call(m, 0x49e836u);	/* 44373b: call 0x49e836 */
	m->eax = M32((DWORD)(0x9ef2c0u));	/* 443740: mov eax, dword ptr [0x9ef2c0] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443745: add esp, 0x40 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 443748: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0xfcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 443749: add edi, 0xfc */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44374f: cmp ebx, eax */
	if (m->sf != m->of) goto L_4436c1;	/* 443751: jl 0x4436c1 */
L_443757:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 443757: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 443759: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_443780;	/* 44375b: jle 0x443780 */
	m->ebx = 0x9ef3c4u;	/* 44375d: mov ebx, 0x9ef3c4 */
L_443762:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 443762: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443763: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443765: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 443767: push ebx */
	m->esp -= 4; M32(m->esp) = 0x44376du; native_call(m, 0x49e836u);	/* 443768: call 0x49e836 */
	m->eax = M32((DWORD)(0x9ef2c0u));	/* 44376d: mov eax, dword ptr [0x9ef2c0] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443772: add esp, 0x10 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 443775: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0xfcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 443776: add ebx, 0xfc */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44377c: cmp edi, eax */
	if (m->sf != m->of) goto L_443762;	/* 44377e: jl 0x443762 */
L_443780:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 443780: push esi */
	m->esp -= 4; M32(m->esp) = 0x443786u; native_call(m, 0x49e7e0u);	/* 443781: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443786: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 443789: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44378a: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44378b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44378c: add esp, 0x184 */
	m->esp += 4 + 0; return;	/* 443792: ret  */
L_443793:
	{ DWORD v_ = 0xbu; m->esp -= 4; M32(m->esp) = v_; }	/* 443793: push 0xb */
	m->esp -= 4; M32(m->esp) = 0x44379au; native_call(m, 0x41ee40u);	/* 443795: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44379a: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44379d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44379e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44379f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4437a0: add esp, 0x184 */
	m->esp += 4 + 0; return;	/* 4437a6: ret  */
}

/* cfg_readLines (0x42d7f0), lifted by tools/lift.py */
static void lift_42d7f0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d7f0: sub esp, 0x108 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7f6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7f7: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7f8: push esi */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 42d7f9: xor ebx, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d7fb: push edi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 42d7fc: xor ebp, ebp */
L_42d7fe:
	m->eax = M32((DWORD)(m->esp + 0x11cu));	/* 42d7fe: mov eax, dword ptr [esp + 0x11c] */
	m->ecx = (DWORD)(m->esp + 0x94u);	/* 42d805: lea ecx, [esp + 0x94] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d80c: push eax */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d80d: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d80f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d815u; native_call(m, 0x49ecd7u);	/* 42d810: call 0x49ecd7 */
	m->edi = (DWORD)(m->esp + 0xa0u);	/* 42d815: lea edi, [esp + 0xa0] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d81c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d81f: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0xa0u);	/* 42d821: lea edx, [esp + 0xa0] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42d828: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42d82a: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42d82c: dec ecx */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d82d: push 0x4ad5dc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d832: push edx */
	M8((DWORD)(m->esp + m->ecx*1 + 0xa7u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 42d833: mov byte ptr [esp + ecx + 0xa7], bl */
	m->esp -= 4; M32(m->esp) = 0x42d83fu; native_call(m, 0x49ec3bu);	/* 42d83a: call 0x49ec3b */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d83f: push 0x4ad5dc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d844: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42d84au; native_call(m, 0x49ec3bu);	/* 42d845: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d84a: add esp, 0x1c */
	m->ecx = 0x21u;	/* 42d84d: mov ecx, 0x21 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d852: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 42d854: lea edi, [esp + 0x10] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42d858: rep stosd dword ptr es:[edi], eax */
L_42d85a:
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d85a: push 0x4ad5dc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d85f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42d865u; native_call(m, 0x49ec3bu);	/* 42d860: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d865: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42d868: cmp eax, ebx */
	if (m->zf) goto L_42d8c9;	/* 42d86a: je 0x42d8c9 */
	m->edi = m->eax;	/* 42d86c: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d86e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d871: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42d873: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42d877: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42d879: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42d87b: sub edi, ecx */
	m->esi = m->edi;	/* 42d87d: mov esi, edi */
	m->edi = m->edx;	/* 42d87f: mov edi, edx */
	m->edx = m->ecx;	/* 42d881: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d883: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42d886: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 42d888: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42d88a: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42d88b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42d88e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42d890: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d892: and ecx, 3 */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42d895: cmp ebp, ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42d897: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_42d85a;	/* 42d899: jne 0x42d85a */
	m->edi = 0x4b035cu;	/* 42d89b: mov edi, 0x4b035c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d8a0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42d8a3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42d8a5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42d8a7: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42d8a9: lea edx, [esp + 0x10] */
	m->esi = m->edi;	/* 42d8ad: mov esi, edi */
	m->edi = m->edx;	/* 42d8af: mov edi, edx */
	m->edx = m->ecx;	/* 42d8b1: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d8b3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42d8b6: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 42d8b8: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42d8ba: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42d8bb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42d8be: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42d8c0: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d8c2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42d8c5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42d85a;	/* 42d8c7: jmp 0x42d85a */
L_42d8c9:
	m->eax = m->ebp;	/* 42d8c9: mov eax, ebp */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42d8cb: sub eax, ebx */
	if (m->zf) goto L_42da07;	/* 42d8cd: je 0x42da07 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42d8d3: dec eax */
	if (m->zf) goto L_42d931;	/* 42d8d4: je 0x42d931 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42d8d6: dec eax */
	if (!m->zf) goto L_42da38;	/* 42d8d7: jne 0x42da38 */
	m->esi = 0x4b21bcu;	/* 42d8dd: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42d8e2: lea eax, [esp + 0x10] */
L_42d8e6:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42d8e6: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42d8e8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d8ea: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42d91a;	/* 42d8ec: jne 0x42d91a */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d8ee: cmp cl, bl */
	if (m->zf) goto L_42d906;	/* 42d8f0: je 0x42d906 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42d8f2: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42d8f5: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d8f7: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42d91a;	/* 42d8fa: jne 0x42d91a */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42d8fc: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42d8ff: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d902: cmp cl, bl */
	if (!m->zf) goto L_42d8e6;	/* 42d904: jne 0x42d8e6 */
L_42d906:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d906: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d908: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42d90a: cmp eax, ebx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42d90c: sete cl */
	M32((DWORD)(0x4dedd4u)) = m->ecx;	/* 42d90f: mov dword ptr [0x4dedd4], ecx */
	goto L_42da38;	/* 42d915: jmp 0x42da38 */
L_42d91a:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d91a: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d91c: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42d91f: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42d921: cmp eax, ebx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42d923: sete cl */
	M32((DWORD)(0x4dedd4u)) = m->ecx;	/* 42d926: mov dword ptr [0x4dedd4], ecx */
	goto L_42da38;	/* 42d92c: jmp 0x42da38 */
L_42d931:
	m->esi = 0x4b21b8u;	/* 42d931: mov esi, 0x4b21b8 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42d936: lea eax, [esp + 0x10] */
L_42d93a:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42d93a: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42d93c: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d93e: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42d95e;	/* 42d940: jne 0x42d95e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d942: cmp cl, bl */
	if (m->zf) goto L_42d95a;	/* 42d944: je 0x42d95a */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42d946: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42d949: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d94b: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42d95e;	/* 42d94e: jne 0x42d95e */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42d950: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42d953: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d956: cmp cl, bl */
	if (!m->zf) goto L_42d93a;	/* 42d958: jne 0x42d93a */
L_42d95a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d95a: xor eax, eax */
	goto L_42d963;	/* 42d95c: jmp 0x42d963 */
L_42d95e:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d95e: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d960: sbb eax, -1 */
L_42d963:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42d963: cmp eax, ebx */
	if (!m->zf) goto L_42d972;	/* 42d965: jne 0x42d972 */
	M32((DWORD)(0x4dedd0u)) = m->ebx;	/* 42d967: mov dword ptr [0x4dedd0], ebx */
	goto L_42da38;	/* 42d96d: jmp 0x42da38 */
L_42d972:
	m->esi = 0x4b21b0u;	/* 42d972: mov esi, 0x4b21b0 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42d977: lea eax, [esp + 0x10] */
L_42d97b:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42d97b: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42d97d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d97f: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42d99f;	/* 42d981: jne 0x42d99f */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d983: cmp cl, bl */
	if (m->zf) goto L_42d99b;	/* 42d985: je 0x42d99b */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42d987: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42d98a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d98c: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42d99f;	/* 42d98f: jne 0x42d99f */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42d991: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42d994: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d997: cmp cl, bl */
	if (!m->zf) goto L_42d97b;	/* 42d999: jne 0x42d97b */
L_42d99b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d99b: xor eax, eax */
	goto L_42d9a4;	/* 42d99d: jmp 0x42d9a4 */
L_42d99f:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d99f: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d9a1: sbb eax, -1 */
L_42d9a4:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42d9a4: cmp eax, ebx */
	if (!m->zf) goto L_42d9b7;	/* 42d9a6: jne 0x42d9b7 */
	M32((DWORD)(0x4dedd0u)) = 0x1u;	/* 42d9a8: mov dword ptr [0x4dedd0], 1 */
	goto L_42da38;	/* 42d9b2: jmp 0x42da38 */
L_42d9b7:
	m->esi = 0x4b21a8u;	/* 42d9b7: mov esi, 0x4b21a8 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42d9bc: lea eax, [esp + 0x10] */
L_42d9c0:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42d9c0: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42d9c2: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d9c4: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42d9f2;	/* 42d9c6: jne 0x42d9f2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d9c8: cmp cl, bl */
	if (m->zf) goto L_42d9e0;	/* 42d9ca: je 0x42d9e0 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42d9cc: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42d9cf: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d9d1: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42d9f2;	/* 42d9d4: jne 0x42d9f2 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42d9d6: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42d9d9: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42d9dc: cmp cl, bl */
	if (!m->zf) goto L_42d9c0;	/* 42d9de: jne 0x42d9c0 */
L_42d9e0:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42d9e0: xor eax, eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 42d9e2: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d9e4: sbb eax, eax */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xfeu & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 42d9e6: and al, 0xfe */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42d9e8: add eax, 2 */
	M32((DWORD)(0x4dedd0u)) = m->eax;	/* 42d9eb: mov dword ptr [0x4dedd0], eax */
	goto L_42da38;	/* 42d9f0: jmp 0x42da38 */
L_42d9f2:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d9f2: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d9f4: sbb eax, -1 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 42d9f7: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42d9f9: sbb eax, eax */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xfeu & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 42d9fb: and al, 0xfe */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42d9fd: add eax, 2 */
	M32((DWORD)(0x4dedd0u)) = m->eax;	/* 42da00: mov dword ptr [0x4dedd0], eax */
	goto L_42da38;	/* 42da05: jmp 0x42da38 */
L_42da07:
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42da07: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42da0b: push eax */
	m->esp -= 4; M32(m->esp) = 0x42da11u; native_call(m, 0x44ac70u);	/* 42da0c: call 0x44ac70 */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 42da11: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42da15: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42da18: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42da1a: add esp, 4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42da1d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42da1f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42da21: sub edi, ecx */
	m->edx = m->ecx;	/* 42da23: mov edx, ecx */
	m->esi = m->edi;	/* 42da25: mov esi, edi */
	m->edi = 0x4dedb0u;	/* 42da27: mov edi, 0x4dedb0 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42da2c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42da2f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42da31: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42da33: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42da36: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_42da38:
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 42da38: inc ebp */
	{ DWORD a_ = m->ebp, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42da39: cmp ebp, 3 */
	if (m->sf != m->of) goto L_42d7fe;	/* 42da3c: jl 0x42d7fe */
	m->eax = M32((DWORD)(m->esp + 0x11cu));	/* 42da42: mov eax, dword ptr [esp + 0x11c] */
	m->ecx = (DWORD)(m->esp + 0x94u);	/* 42da49: lea ecx, [esp + 0x94] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42da50: push eax */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42da51: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42da53: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42da59u; native_call(m, 0x49ecd7u);	/* 42da54: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42da59: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 42da5c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42da5d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42da5e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42da5f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42da60: add esp, 0x108 */
	m->esp += 4 + 0; return;	/* 42da66: ret  */
}

/* arena_loadSettings (0x40d4e0), lifted by tools/lift.py */
static void lift_40d4e0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 40d4e0: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d4e4: sub esp, 0x50 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d4e7: push ebx */
	{ DWORD v_ = 0x4ad5e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40d4e8: push 0x4ad5e0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d4ed: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d4f3u; native_call(m, 0x49e9cau);	/* 40d4ee: call 0x49e9ca */
	m->ebx = m->eax;	/* 40d4f3: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d4f5: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d4f8: test ebx, ebx */
	if (!m->zf) goto L_40d501;	/* 40d4fa: jne 0x40d501 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40d4fc: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d4fd: add esp, 0x50 */
	m->esp += 4 + 0; return;	/* 40d500: ret  */
L_40d501:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40d501: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40d502: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40d503: push edi */
L_40d504:
	m->ecx = 0x14u;	/* 40d504: mov ecx, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d509: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 40d50b: lea edi, [esp + 0x10] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d50f: push ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40d510: rep stosd dword ptr es:[edi], eax */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 40d512: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 40d516: push 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d518: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40d51eu; native_call(m, 0x49ecd7u);	/* 40d519: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d51e: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d521: test eax, eax */
	if (m->zf) goto L_40d823;	/* 40d523: je 0x40d823 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x10u)), b_ = 0x2fu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d529: cmp byte ptr [esp + 0x10], 0x2f */
	if (!m->zf) goto L_40d537;	/* 40d52e: jne 0x40d537 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x11u)), b_ = 0x2fu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d530: cmp byte ptr [esp + 0x11], 0x2f */
	if (m->zf) goto L_40d504;	/* 40d535: je 0x40d504 */
L_40d537:
	m->edx = (DWORD)(m->esp + 0x10u);	/* 40d537: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d53b: push 0x4ad5dc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d540: push edx */
	m->esp -= 4; M32(m->esp) = 0x40d546u; native_call(m, 0x49ec3bu);	/* 40d541: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d546: add esp, 8 */
	m->ebp = m->eax;	/* 40d549: mov ebp, eax */
L_40d54b:
	m->esi = 0x4ad5d0u;	/* 40d54b: mov esi, 0x4ad5d0 */
	m->eax = m->ebp;	/* 40d550: mov eax, ebp */
L_40d552:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d552: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d554: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d556: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d576;	/* 40d558: jne 0x40d576 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d55a: test cl, cl */
	if (m->zf) goto L_40d572;	/* 40d55c: je 0x40d572 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d55e: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d561: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d563: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d576;	/* 40d566: jne 0x40d576 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d568: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d56b: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d56e: test cl, cl */
	if (!m->zf) goto L_40d552;	/* 40d570: jne 0x40d552 */
L_40d572:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d572: xor eax, eax */
	goto L_40d57b;	/* 40d574: jmp 0x40d57b */
L_40d576:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d576: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d578: sbb eax, -1 */
L_40d57b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d57b: test eax, eax */
	if (!m->zf) goto L_40d5bd;	/* 40d57d: jne 0x40d5bd */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d57f: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d584: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d58au; native_call(m, 0x49ec3bu);	/* 40d585: call 0x49ec3b */
	m->ebp = m->eax;	/* 40d58a: mov ebp, eax */
	m->ecx = 0x8u;	/* 40d58c: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d591: xor eax, eax */
	m->edi = 0x5b191cu;	/* 40d593: mov edi, 0x5b191c */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40d598: rep stosd dword ptr es:[edi], eax */
	m->edi = m->ebp;	/* 40d59a: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d59c: or ecx, 0xffffffff */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d59f: add esp, 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40d5a2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40d5a4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40d5a6: sub edi, ecx */
	m->eax = m->ecx;	/* 40d5a8: mov eax, ecx */
	m->esi = m->edi;	/* 40d5aa: mov esi, edi */
	m->edi = 0x5b191cu;	/* 40d5ac: mov edi, 0x5b191c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40d5b1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40d5b4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 40d5b6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d5b8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40d5bb: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_40d5bd:
	m->esi = 0x4ad5c8u;	/* 40d5bd: mov esi, 0x4ad5c8 */
	m->eax = m->ebp;	/* 40d5c2: mov eax, ebp */
L_40d5c4:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d5c4: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d5c6: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d5c8: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d5e8;	/* 40d5ca: jne 0x40d5e8 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d5cc: test cl, cl */
	if (m->zf) goto L_40d5e4;	/* 40d5ce: je 0x40d5e4 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d5d0: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d5d3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d5d5: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d5e8;	/* 40d5d8: jne 0x40d5e8 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d5da: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d5dd: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d5e0: test cl, cl */
	if (!m->zf) goto L_40d5c4;	/* 40d5e2: jne 0x40d5c4 */
L_40d5e4:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d5e4: xor eax, eax */
	goto L_40d5ed;	/* 40d5e6: jmp 0x40d5ed */
L_40d5e8:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d5e8: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d5ea: sbb eax, -1 */
L_40d5ed:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d5ed: test eax, eax */
	if (!m->zf) goto L_40d60c;	/* 40d5ef: jne 0x40d60c */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d5f1: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d5f6: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d5fcu; native_call(m, 0x49ec3bu);	/* 40d5f7: call 0x49ec3b */
	m->ebp = m->eax;	/* 40d5fc: mov ebp, eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40d5fe: push ebp */
	m->esp -= 4; M32(m->esp) = 0x40d604u; native_call(m, 0x49ec09u);	/* 40d5ff: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d604: add esp, 0xc */
	M32((DWORD)(0x5b1958u)) = m->eax;	/* 40d607: mov dword ptr [0x5b1958], eax */
L_40d60c:
	m->esi = 0x4ad5bcu;	/* 40d60c: mov esi, 0x4ad5bc */
	m->eax = m->ebp;	/* 40d611: mov eax, ebp */
L_40d613:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d613: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d615: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d617: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d637;	/* 40d619: jne 0x40d637 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d61b: test cl, cl */
	if (m->zf) goto L_40d633;	/* 40d61d: je 0x40d633 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d61f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d622: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d624: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d637;	/* 40d627: jne 0x40d637 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d629: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d62c: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d62f: test cl, cl */
	if (!m->zf) goto L_40d613;	/* 40d631: jne 0x40d613 */
L_40d633:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d633: xor eax, eax */
	goto L_40d63c;	/* 40d635: jmp 0x40d63c */
L_40d637:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d637: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d639: sbb eax, -1 */
L_40d63c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d63c: test eax, eax */
	if (!m->zf) goto L_40d67c;	/* 40d63e: jne 0x40d67c */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d640: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d645: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d64bu; native_call(m, 0x49ec3bu);	/* 40d646: call 0x49ec3b */
	m->ebp = m->eax;	/* 40d64b: mov ebp, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d64d: xor eax, eax */
	M32((DWORD)(0x5b193cu)) = m->eax;	/* 40d64f: mov dword ptr [0x5b193c], eax */
	m->edi = m->ebp;	/* 40d654: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d656: or ecx, 0xffffffff */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d659: add esp, 8 */
	M32((DWORD)(0x5b1940u)) = m->eax;	/* 40d65c: mov dword ptr [0x5b1940], eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40d661: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40d663: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40d665: sub edi, ecx */
	m->edx = m->ecx;	/* 40d667: mov edx, ecx */
	m->esi = m->edi;	/* 40d669: mov esi, edi */
	m->edi = 0x5b193cu;	/* 40d66b: mov edi, 0x5b193c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40d670: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40d673: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 40d675: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40d677: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40d67a: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_40d67c:
	m->esi = 0x4ad5b0u;	/* 40d67c: mov esi, 0x4ad5b0 */
	m->eax = m->ebp;	/* 40d681: mov eax, ebp */
L_40d683:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d683: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d685: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d687: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d6a7;	/* 40d689: jne 0x40d6a7 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d68b: test cl, cl */
	if (m->zf) goto L_40d6a3;	/* 40d68d: je 0x40d6a3 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d68f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d692: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d694: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d6a7;	/* 40d697: jne 0x40d6a7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d699: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d69c: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d69f: test cl, cl */
	if (!m->zf) goto L_40d683;	/* 40d6a1: jne 0x40d683 */
L_40d6a3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d6a3: xor eax, eax */
	goto L_40d6ac;	/* 40d6a5: jmp 0x40d6ac */
L_40d6a7:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d6a7: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d6a9: sbb eax, -1 */
L_40d6ac:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d6ac: test eax, eax */
	if (!m->zf) goto L_40d6cb;	/* 40d6ae: jne 0x40d6cb */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d6b0: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d6b5: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d6bbu; native_call(m, 0x49ec3bu);	/* 40d6b6: call 0x49ec3b */
	m->ebp = m->eax;	/* 40d6bb: mov ebp, eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40d6bd: push ebp */
	m->esp -= 4; M32(m->esp) = 0x40d6c3u; native_call(m, 0x49ec09u);	/* 40d6be: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d6c3: add esp, 0xc */
	M32((DWORD)(0x5b194cu)) = m->eax;	/* 40d6c6: mov dword ptr [0x5b194c], eax */
L_40d6cb:
	m->esi = 0x4ad5a4u;	/* 40d6cb: mov esi, 0x4ad5a4 */
	m->eax = m->ebp;	/* 40d6d0: mov eax, ebp */
L_40d6d2:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d6d2: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d6d4: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d6d6: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d6f6;	/* 40d6d8: jne 0x40d6f6 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d6da: test cl, cl */
	if (m->zf) goto L_40d6f2;	/* 40d6dc: je 0x40d6f2 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d6de: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d6e1: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d6e3: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d6f6;	/* 40d6e6: jne 0x40d6f6 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d6e8: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d6eb: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d6ee: test cl, cl */
	if (!m->zf) goto L_40d6d2;	/* 40d6f0: jne 0x40d6d2 */
L_40d6f2:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d6f2: xor eax, eax */
	goto L_40d6fb;	/* 40d6f4: jmp 0x40d6fb */
L_40d6f6:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d6f6: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d6f8: sbb eax, -1 */
L_40d6fb:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d6fb: test eax, eax */
	if (!m->zf) goto L_40d71a;	/* 40d6fd: jne 0x40d71a */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d6ff: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d704: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d70au; native_call(m, 0x49ec3bu);	/* 40d705: call 0x49ec3b */
	m->ebp = m->eax;	/* 40d70a: mov ebp, eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40d70c: push ebp */
	m->esp -= 4; M32(m->esp) = 0x40d712u; native_call(m, 0x49ec09u);	/* 40d70d: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d712: add esp, 0xc */
	M32((DWORD)(0x5b1948u)) = m->eax;	/* 40d715: mov dword ptr [0x5b1948], eax */
L_40d71a:
	m->esi = 0x4ad5a0u;	/* 40d71a: mov esi, 0x4ad5a0 */
	m->eax = m->ebp;	/* 40d71f: mov eax, ebp */
L_40d721:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d721: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d723: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d725: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d745;	/* 40d727: jne 0x40d745 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d729: test cl, cl */
	if (m->zf) goto L_40d741;	/* 40d72b: je 0x40d741 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d72d: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d730: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d732: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d745;	/* 40d735: jne 0x40d745 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d737: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d73a: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d73d: test cl, cl */
	if (!m->zf) goto L_40d721;	/* 40d73f: jne 0x40d721 */
L_40d741:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d741: xor eax, eax */
	goto L_40d74a;	/* 40d743: jmp 0x40d74a */
L_40d745:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d745: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d747: sbb eax, -1 */
L_40d74a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d74a: test eax, eax */
	if (!m->zf) goto L_40d769;	/* 40d74c: jne 0x40d769 */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d74e: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d753: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d759u; native_call(m, 0x49ec3bu);	/* 40d754: call 0x49ec3b */
	m->ebp = m->eax;	/* 40d759: mov ebp, eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40d75b: push ebp */
	m->esp -= 4; M32(m->esp) = 0x40d761u; native_call(m, 0x49ec09u);	/* 40d75c: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d761: add esp, 0xc */
	M32((DWORD)(0x5b1944u)) = m->eax;	/* 40d764: mov dword ptr [0x5b1944], eax */
L_40d769:
	m->esi = 0x4ad594u;	/* 40d769: mov esi, 0x4ad594 */
	m->eax = m->ebp;	/* 40d76e: mov eax, ebp */
L_40d770:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d770: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d772: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d774: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d794;	/* 40d776: jne 0x40d794 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d778: test cl, cl */
	if (m->zf) goto L_40d790;	/* 40d77a: je 0x40d790 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d77c: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d77f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d781: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d794;	/* 40d784: jne 0x40d794 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d786: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d789: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d78c: test cl, cl */
	if (!m->zf) goto L_40d770;	/* 40d78e: jne 0x40d770 */
L_40d790:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d790: xor eax, eax */
	goto L_40d799;	/* 40d792: jmp 0x40d799 */
L_40d794:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d794: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d796: sbb eax, -1 */
L_40d799:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d799: test eax, eax */
	if (!m->zf) goto L_40d7b8;	/* 40d79b: jne 0x40d7b8 */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d79d: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d7a2: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d7a8u; native_call(m, 0x49ec3bu);	/* 40d7a3: call 0x49ec3b */
	m->ebp = m->eax;	/* 40d7a8: mov ebp, eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40d7aa: push ebp */
	m->esp -= 4; M32(m->esp) = 0x40d7b0u; native_call(m, 0x49ec09u);	/* 40d7ab: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d7b0: add esp, 0xc */
	M32((DWORD)(0x5b1950u)) = m->eax;	/* 40d7b3: mov dword ptr [0x5b1950], eax */
L_40d7b8:
	m->esi = 0x4ad588u;	/* 40d7b8: mov esi, 0x4ad588 */
	m->eax = m->ebp;	/* 40d7bd: mov eax, ebp */
L_40d7bf:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40d7bf: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d7c1: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d7c3: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_40d7e3;	/* 40d7c5: jne 0x40d7e3 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d7c7: test cl, cl */
	if (m->zf) goto L_40d7df;	/* 40d7c9: je 0x40d7df */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 40d7cb: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 40d7ce: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d7d0: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_40d7e3;	/* 40d7d3: jne 0x40d7e3 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40d7d5: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40d7d8: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d7db: test cl, cl */
	if (!m->zf) goto L_40d7bf;	/* 40d7dd: jne 0x40d7bf */
L_40d7df:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40d7df: xor eax, eax */
	goto L_40d7e8;	/* 40d7e1: jmp 0x40d7e8 */
L_40d7e3:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d7e3: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40d7e5: sbb eax, -1 */
L_40d7e8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d7e8: test eax, eax */
	if (!m->zf) goto L_40d805;	/* 40d7ea: jne 0x40d805 */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d7ec: push 0x4ad5dc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d7f1: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d7f7u; native_call(m, 0x49ec3bu);	/* 40d7f2: call 0x49ec3b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d7f7: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d7fdu; native_call(m, 0x49ec09u);	/* 40d7f8: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d7fd: add esp, 0xc */
	M32((DWORD)(0x5b1954u)) = m->eax;	/* 40d800: mov dword ptr [0x5b1954], eax */
L_40d805:
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40d805: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40d80a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40d811u; native_call(m, 0x49ec3bu);	/* 40d80c: call 0x49ec3b */
	m->ebp = m->eax;	/* 40d811: mov ebp, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d813: add esp, 8 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d816: test ebp, ebp */
	if (!m->zf) goto L_40d54b;	/* 40d818: jne 0x40d54b */
	goto L_40d504;	/* 40d81e: jmp 0x40d504 */
L_40d823:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d823: push ebx */
	m->esp -= 4; M32(m->esp) = 0x40d829u; native_call(m, 0x49e7e0u);	/* 40d824: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d829: add esp, 4 */
	m->eax = 0x1u;	/* 40d82c: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40d831: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40d832: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40d833: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40d834: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d835: add esp, 0x50 */
	m->esp += 4 + 0; return;	/* 40d838: ret  */
}

/* cfg_keyBindings (0x42cba0), lifted by tools/lift.py */
static void lift_42cba0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cba0: sub esp, 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cba3: push esi */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 42cba4: mov esi, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cba8: push esi */
	{ DWORD v_ = 0x4b2184u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cba9: push 0x4b2184 */
	m->esp -= 4; M32(m->esp) = 0x42cbb3u; native_call(m, 0x49f167u);	/* 42cbae: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def00u));	/* 42cbb3: mov eax, dword ptr [0x4def00] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbb8: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42cbb9: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbc0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42cbc6u; native_call(m, 0x49f167u);	/* 42cbc1: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbc6: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbc7: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cbd1u; native_call(m, 0x49f167u);	/* 42cbcc: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbd1: push esi */
	{ DWORD v_ = 0x4b2170u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbd2: push 0x4b2170 */
	m->esp -= 4; M32(m->esp) = 0x42cbdcu; native_call(m, 0x49f167u);	/* 42cbd7: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def04u));	/* 42cbdc: mov edx, dword ptr [0x4def04] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbe2: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42cbe3: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbea: push eax */
	m->esp -= 4; M32(m->esp) = 0x42cbf0u; native_call(m, 0x49f167u);	/* 42cbeb: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbf0: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbf1: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cbfbu; native_call(m, 0x49f167u);	/* 42cbf6: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbfb: push esi */
	{ DWORD v_ = 0x4b215cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cbfc: push 0x4b215c */
	m->esp -= 4; M32(m->esp) = 0x42cc06u; native_call(m, 0x49f167u);	/* 42cc01: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def08u));	/* 42cc06: mov ecx, dword ptr [0x4def08] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc0c: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42cc0d: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc14: push edx */
	m->esp -= 4; M32(m->esp) = 0x42cc1au; native_call(m, 0x49f167u);	/* 42cc15: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cc1a: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc1d: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc1e: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cc28u; native_call(m, 0x49f167u);	/* 42cc23: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc28: push esi */
	{ DWORD v_ = 0x4b2148u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc29: push 0x4b2148 */
	m->esp -= 4; M32(m->esp) = 0x42cc33u; native_call(m, 0x49f167u);	/* 42cc2e: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def0cu));	/* 42cc33: mov eax, dword ptr [0x4def0c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc38: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42cc39: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc40: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42cc46u; native_call(m, 0x49f167u);	/* 42cc41: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc46: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc47: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cc51u; native_call(m, 0x49f167u);	/* 42cc4c: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc51: push esi */
	{ DWORD v_ = 0x4b2134u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc52: push 0x4b2134 */
	m->esp -= 4; M32(m->esp) = 0x42cc5cu; native_call(m, 0x49f167u);	/* 42cc57: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def10u));	/* 42cc5c: mov edx, dword ptr [0x4def10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc62: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42cc63: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc6a: push eax */
	m->esp -= 4; M32(m->esp) = 0x42cc70u; native_call(m, 0x49f167u);	/* 42cc6b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc70: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc71: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cc7bu; native_call(m, 0x49f167u);	/* 42cc76: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc7b: push esi */
	{ DWORD v_ = 0x4b2120u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc7c: push 0x4b2120 */
	m->esp -= 4; M32(m->esp) = 0x42cc86u; native_call(m, 0x49f167u);	/* 42cc81: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def14u));	/* 42cc86: mov ecx, dword ptr [0x4def14] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cc8c: add esp, 0x40 */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42cc8f: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc96: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc97: push edx */
	m->esp -= 4; M32(m->esp) = 0x42cc9du; native_call(m, 0x49f167u);	/* 42cc98: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc9d: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cc9e: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cca8u; native_call(m, 0x49f167u);	/* 42cca3: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cca8: push esi */
	{ DWORD v_ = 0x4b2108u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cca9: push 0x4b2108 */
	m->esp -= 4; M32(m->esp) = 0x42ccb3u; native_call(m, 0x49f167u);	/* 42ccae: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def18u));	/* 42ccb3: mov eax, dword ptr [0x4def18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccb8: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42ccb9: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccc0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42ccc6u; native_call(m, 0x49f167u);	/* 42ccc1: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccc6: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccc7: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42ccd1u; native_call(m, 0x49f167u);	/* 42cccc: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccd1: push esi */
	{ DWORD v_ = 0x4b20f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccd2: push 0x4b20f0 */
	m->esp -= 4; M32(m->esp) = 0x42ccdcu; native_call(m, 0x49f167u);	/* 42ccd7: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def1cu));	/* 42ccdc: mov edx, dword ptr [0x4def1c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cce2: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42cce3: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccea: push eax */
	m->esp -= 4; M32(m->esp) = 0x42ccf0u; native_call(m, 0x49f167u);	/* 42cceb: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccf0: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccf1: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42ccfbu; native_call(m, 0x49f167u);	/* 42ccf6: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ccfb: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccfe: push esi */
	{ DWORD v_ = 0x4b20dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ccff: push 0x4b20dc */
	m->esp -= 4; M32(m->esp) = 0x42cd09u; native_call(m, 0x49f167u);	/* 42cd04: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def20u));	/* 42cd09: mov ecx, dword ptr [0x4def20] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd0f: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42cd10: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd17: push edx */
	m->esp -= 4; M32(m->esp) = 0x42cd1du; native_call(m, 0x49f167u);	/* 42cd18: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd1d: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd1e: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cd28u; native_call(m, 0x49f167u);	/* 42cd23: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd28: push esi */
	{ DWORD v_ = 0x4b20c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd29: push 0x4b20c8 */
	m->esp -= 4; M32(m->esp) = 0x42cd33u; native_call(m, 0x49f167u);	/* 42cd2e: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def24u));	/* 42cd33: mov eax, dword ptr [0x4def24] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd38: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42cd39: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd40: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42cd46u; native_call(m, 0x49f167u);	/* 42cd41: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd46: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd47: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cd51u; native_call(m, 0x49f167u);	/* 42cd4c: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd51: push esi */
	{ DWORD v_ = 0x4b20b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd52: push 0x4b20b0 */
	m->esp -= 4; M32(m->esp) = 0x42cd5cu; native_call(m, 0x49f167u);	/* 42cd57: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def28u));	/* 42cd5c: mov edx, dword ptr [0x4def28] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd62: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42cd63: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd6a: push eax */
	m->esp -= 4; M32(m->esp) = 0x42cd70u; native_call(m, 0x49f167u);	/* 42cd6b: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cd70: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd73: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd74: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cd7eu; native_call(m, 0x49f167u);	/* 42cd79: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd7e: push esi */
	{ DWORD v_ = 0x4b2098u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd7f: push 0x4b2098 */
	m->esp -= 4; M32(m->esp) = 0x42cd89u; native_call(m, 0x49f167u);	/* 42cd84: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def2cu));	/* 42cd89: mov ecx, dword ptr [0x4def2c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd8f: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42cd90: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd97: push edx */
	m->esp -= 4; M32(m->esp) = 0x42cd9du; native_call(m, 0x49f167u);	/* 42cd98: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd9d: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cd9e: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cda8u; native_call(m, 0x49f167u);	/* 42cda3: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cda8: push esi */
	{ DWORD v_ = 0x4b207cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cda9: push 0x4b207c */
	m->esp -= 4; M32(m->esp) = 0x42cdb3u; native_call(m, 0x49f167u);	/* 42cdae: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def30u));	/* 42cdb3: mov eax, dword ptr [0x4def30] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdb8: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42cdb9: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdc0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42cdc6u; native_call(m, 0x49f167u);	/* 42cdc1: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdc6: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdc7: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cdd1u; native_call(m, 0x49f167u);	/* 42cdcc: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdd1: push esi */
	{ DWORD v_ = 0x4b2060u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdd2: push 0x4b2060 */
	m->esp -= 4; M32(m->esp) = 0x42cddcu; native_call(m, 0x49f167u);	/* 42cdd7: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def34u));	/* 42cddc: mov edx, dword ptr [0x4def34] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cde2: add esp, 0x40 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42cde5: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdec: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42cded: push eax */
	m->esp -= 4; M32(m->esp) = 0x42cdf3u; native_call(m, 0x49f167u);	/* 42cdee: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdf3: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdf4: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cdfeu; native_call(m, 0x49f167u);	/* 42cdf9: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdfe: push esi */
	{ DWORD v_ = 0x4b204cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cdff: push 0x4b204c */
	m->esp -= 4; M32(m->esp) = 0x42ce09u; native_call(m, 0x49f167u);	/* 42ce04: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def38u));	/* 42ce09: mov ecx, dword ptr [0x4def38] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce0f: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42ce10: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce17: push edx */
	m->esp -= 4; M32(m->esp) = 0x42ce1du; native_call(m, 0x49f167u);	/* 42ce18: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce1d: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce1e: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42ce28u; native_call(m, 0x49f167u);	/* 42ce23: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce28: push esi */
	{ DWORD v_ = 0x4b2038u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce29: push 0x4b2038 */
	m->esp -= 4; M32(m->esp) = 0x42ce33u; native_call(m, 0x49f167u);	/* 42ce2e: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def3cu));	/* 42ce33: mov eax, dword ptr [0x4def3c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce38: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42ce39: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce40: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42ce46u; native_call(m, 0x49f167u);	/* 42ce41: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce46: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce47: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42ce51u; native_call(m, 0x49f167u);	/* 42ce4c: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ce51: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce54: push esi */
	{ DWORD v_ = 0x4b2024u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce55: push 0x4b2024 */
	m->esp -= 4; M32(m->esp) = 0x42ce5fu; native_call(m, 0x49f167u);	/* 42ce5a: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def40u));	/* 42ce5f: mov edx, dword ptr [0x4def40] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce65: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42ce66: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce6d: push eax */
	m->esp -= 4; M32(m->esp) = 0x42ce73u; native_call(m, 0x49f167u);	/* 42ce6e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce73: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce74: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42ce7eu; native_call(m, 0x49f167u);	/* 42ce79: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce7e: push esi */
	{ DWORD v_ = 0x4b2010u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce7f: push 0x4b2010 */
	m->esp -= 4; M32(m->esp) = 0x42ce89u; native_call(m, 0x49f167u);	/* 42ce84: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def44u));	/* 42ce89: mov ecx, dword ptr [0x4def44] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce8f: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42ce90: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce97: push edx */
	m->esp -= 4; M32(m->esp) = 0x42ce9du; native_call(m, 0x49f167u);	/* 42ce98: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce9d: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ce9e: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cea8u; native_call(m, 0x49f167u);	/* 42cea3: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cea8: push esi */
	{ DWORD v_ = 0x4b1ffcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cea9: push 0x4b1ffc */
	m->esp -= 4; M32(m->esp) = 0x42ceb3u; native_call(m, 0x49f167u);	/* 42ceae: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def48u));	/* 42ceb3: mov eax, dword ptr [0x4def48] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ceb8: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42ceb9: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cec0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42cec6u; native_call(m, 0x49f167u);	/* 42cec1: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cec6: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cec9: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ceca: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42ced4u; native_call(m, 0x49f167u);	/* 42cecf: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ced4: push esi */
	{ DWORD v_ = 0x4b1fe8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ced5: push 0x4b1fe8 */
	m->esp -= 4; M32(m->esp) = 0x42cedfu; native_call(m, 0x49f167u);	/* 42ceda: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def4cu));	/* 42cedf: mov edx, dword ptr [0x4def4c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cee5: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42cee6: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42ceed: push eax */
	m->esp -= 4; M32(m->esp) = 0x42cef3u; native_call(m, 0x49f167u);	/* 42ceee: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cef3: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cef4: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cefeu; native_call(m, 0x49f167u);	/* 42cef9: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cefe: push esi */
	{ DWORD v_ = 0x4b1fd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ceff: push 0x4b1fd8 */
	m->esp -= 4; M32(m->esp) = 0x42cf09u; native_call(m, 0x49f167u);	/* 42cf04: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def50u));	/* 42cf09: mov ecx, dword ptr [0x4def50] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf0f: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42cf10: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf17: push edx */
	m->esp -= 4; M32(m->esp) = 0x42cf1du; native_call(m, 0x49f167u);	/* 42cf18: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf1d: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf1e: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cf28u; native_call(m, 0x49f167u);	/* 42cf23: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf28: push esi */
	{ DWORD v_ = 0x4b1fc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf29: push 0x4b1fc8 */
	m->esp -= 4; M32(m->esp) = 0x42cf33u; native_call(m, 0x49f167u);	/* 42cf2e: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def54u));	/* 42cf33: mov eax, dword ptr [0x4def54] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cf38: add esp, 0x40 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42cf3b: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf42: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf43: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42cf49u; native_call(m, 0x49f167u);	/* 42cf44: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf49: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf4a: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cf54u; native_call(m, 0x49f167u);	/* 42cf4f: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf54: push esi */
	{ DWORD v_ = 0x4b1fb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf55: push 0x4b1fb0 */
	m->esp -= 4; M32(m->esp) = 0x42cf5fu; native_call(m, 0x49f167u);	/* 42cf5a: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def58u));	/* 42cf5f: mov edx, dword ptr [0x4def58] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf65: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42cf66: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf6d: push eax */
	m->esp -= 4; M32(m->esp) = 0x42cf73u; native_call(m, 0x49f167u);	/* 42cf6e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf73: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf74: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cf7eu; native_call(m, 0x49f167u);	/* 42cf79: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf7e: push esi */
	{ DWORD v_ = 0x4b1f98u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf7f: push 0x4b1f98 */
	m->esp -= 4; M32(m->esp) = 0x42cf89u; native_call(m, 0x49f167u);	/* 42cf84: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def5cu));	/* 42cf89: mov ecx, dword ptr [0x4def5c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf8f: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42cf90: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf97: push edx */
	m->esp -= 4; M32(m->esp) = 0x42cf9du; native_call(m, 0x49f167u);	/* 42cf98: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf9d: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cf9e: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cfa8u; native_call(m, 0x49f167u);	/* 42cfa3: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cfa8: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfab: push esi */
	{ DWORD v_ = 0x4b1f80u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfac: push 0x4b1f80 */
	m->esp -= 4; M32(m->esp) = 0x42cfb6u; native_call(m, 0x49f167u);	/* 42cfb1: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def60u));	/* 42cfb6: mov eax, dword ptr [0x4def60] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfbb: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42cfbc: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfc3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42cfc9u; native_call(m, 0x49f167u);	/* 42cfc4: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfc9: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfca: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cfd4u; native_call(m, 0x49f167u);	/* 42cfcf: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfd4: push esi */
	{ DWORD v_ = 0x4b1f68u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfd5: push 0x4b1f68 */
	m->esp -= 4; M32(m->esp) = 0x42cfdfu; native_call(m, 0x49f167u);	/* 42cfda: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def64u));	/* 42cfdf: mov edx, dword ptr [0x4def64] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfe5: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42cfe6: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfed: push eax */
	m->esp -= 4; M32(m->esp) = 0x42cff3u; native_call(m, 0x49f167u);	/* 42cfee: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cff3: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cff4: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cffeu; native_call(m, 0x49f167u);	/* 42cff9: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cffe: push esi */
	{ DWORD v_ = 0x4b1f4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cfff: push 0x4b1f4c */
	m->esp -= 4; M32(m->esp) = 0x42d009u; native_call(m, 0x49f167u);	/* 42d004: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def78u));	/* 42d009: mov ecx, dword ptr [0x4def78] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d00f: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d010: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d017: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d01du; native_call(m, 0x49f167u);	/* 42d018: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d01d: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d020: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d021: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d02bu; native_call(m, 0x49f167u);	/* 42d026: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d02b: push esi */
	{ DWORD v_ = 0x4b1f30u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d02c: push 0x4b1f30 */
	m->esp -= 4; M32(m->esp) = 0x42d036u; native_call(m, 0x49f167u);	/* 42d031: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def7cu));	/* 42d036: mov eax, dword ptr [0x4def7c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d03b: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d03c: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d043: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d049u; native_call(m, 0x49f167u);	/* 42d044: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d049: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d04a: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d054u; native_call(m, 0x49f167u);	/* 42d04f: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d054: push esi */
	{ DWORD v_ = 0x4b1f14u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d055: push 0x4b1f14 */
	m->esp -= 4; M32(m->esp) = 0x42d05fu; native_call(m, 0x49f167u);	/* 42d05a: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def80u));	/* 42d05f: mov edx, dword ptr [0x4def80] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d065: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d066: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d06d: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d073u; native_call(m, 0x49f167u);	/* 42d06e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d073: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d074: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d07eu; native_call(m, 0x49f167u);	/* 42d079: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d07e: push esi */
	{ DWORD v_ = 0x4b1ef8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d07f: push 0x4b1ef8 */
	m->esp -= 4; M32(m->esp) = 0x42d089u; native_call(m, 0x49f167u);	/* 42d084: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def84u));	/* 42d089: mov ecx, dword ptr [0x4def84] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d08f: add esp, 0x40 */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d092: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d099: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d09a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d0a0u; native_call(m, 0x49f167u);	/* 42d09b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0a0: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0a1: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d0abu; native_call(m, 0x49f167u);	/* 42d0a6: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0ab: push esi */
	{ DWORD v_ = 0x4b1edcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0ac: push 0x4b1edc */
	m->esp -= 4; M32(m->esp) = 0x42d0b6u; native_call(m, 0x49f167u);	/* 42d0b1: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def88u));	/* 42d0b6: mov eax, dword ptr [0x4def88] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0bb: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d0bc: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0c3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d0c9u; native_call(m, 0x49f167u);	/* 42d0c4: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0c9: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0ca: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d0d4u; native_call(m, 0x49f167u);	/* 42d0cf: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0d4: push esi */
	{ DWORD v_ = 0x4b1ec0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0d5: push 0x4b1ec0 */
	m->esp -= 4; M32(m->esp) = 0x42d0dfu; native_call(m, 0x49f167u);	/* 42d0da: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def8cu));	/* 42d0df: mov edx, dword ptr [0x4def8c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0e5: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d0e6: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0ed: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d0f3u; native_call(m, 0x49f167u);	/* 42d0ee: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0f3: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d0f4: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d0feu; native_call(m, 0x49f167u);	/* 42d0f9: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d0fe: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d101: push esi */
	{ DWORD v_ = 0x4b1ea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d102: push 0x4b1ea4 */
	m->esp -= 4; M32(m->esp) = 0x42d10cu; native_call(m, 0x49f167u);	/* 42d107: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def90u));	/* 42d10c: mov ecx, dword ptr [0x4def90] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d112: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d113: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d11a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d120u; native_call(m, 0x49f167u);	/* 42d11b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d120: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d121: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d12bu; native_call(m, 0x49f167u);	/* 42d126: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d12b: push esi */
	{ DWORD v_ = 0x4b1e88u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d12c: push 0x4b1e88 */
	m->esp -= 4; M32(m->esp) = 0x42d136u; native_call(m, 0x49f167u);	/* 42d131: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def94u));	/* 42d136: mov eax, dword ptr [0x4def94] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d13b: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d13c: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d143: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d149u; native_call(m, 0x49f167u);	/* 42d144: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d149: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d14a: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d154u; native_call(m, 0x49f167u);	/* 42d14f: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d154: push esi */
	{ DWORD v_ = 0x4b1e68u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d155: push 0x4b1e68 */
	m->esp -= 4; M32(m->esp) = 0x42d15fu; native_call(m, 0x49f167u);	/* 42d15a: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def68u));	/* 42d15f: mov edx, dword ptr [0x4def68] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d165: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d166: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d16d: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d173u; native_call(m, 0x49f167u);	/* 42d16e: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d173: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d176: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d177: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d181u; native_call(m, 0x49f167u);	/* 42d17c: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d181: push esi */
	{ DWORD v_ = 0x4b1e48u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d182: push 0x4b1e48 */
	m->esp -= 4; M32(m->esp) = 0x42d18cu; native_call(m, 0x49f167u);	/* 42d187: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d18c: push esi */
	m->ecx = M32((DWORD)(0x4def6cu));	/* 42d18d: mov ecx, dword ptr [0x4def6c] */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d193: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d19a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d1a0u; native_call(m, 0x49f167u);	/* 42d19b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1a0: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1a1: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d1abu; native_call(m, 0x49f167u);	/* 42d1a6: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1ab: push esi */
	{ DWORD v_ = 0x4b1e28u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1ac: push 0x4b1e28 */
	m->esp -= 4; M32(m->esp) = 0x42d1b6u; native_call(m, 0x49f167u);	/* 42d1b1: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def70u));	/* 42d1b6: mov eax, dword ptr [0x4def70] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1bb: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d1bc: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1c3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d1c9u; native_call(m, 0x49f167u);	/* 42d1c4: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1c9: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1ca: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d1d4u; native_call(m, 0x49f167u);	/* 42d1cf: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1d4: push esi */
	{ DWORD v_ = 0x4b1e08u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1d5: push 0x4b1e08 */
	m->esp -= 4; M32(m->esp) = 0x42d1dfu; native_call(m, 0x49f167u);	/* 42d1da: call 0x49f167 */
	m->edx = M32((DWORD)(0x4def74u));	/* 42d1df: mov edx, dword ptr [0x4def74] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d1e5: add esp, 0x40 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d1e8: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1ef: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1f0: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d1f6u; native_call(m, 0x49f167u);	/* 42d1f1: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1f6: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d1f7: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d201u; native_call(m, 0x49f167u);	/* 42d1fc: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d201: push esi */
	{ DWORD v_ = 0x4b1df8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d202: push 0x4b1df8 */
	m->esp -= 4; M32(m->esp) = 0x42d20cu; native_call(m, 0x49f167u);	/* 42d207: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4def98u));	/* 42d20c: mov ecx, dword ptr [0x4def98] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d212: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d213: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d21a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d220u; native_call(m, 0x49f167u);	/* 42d21b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d220: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d221: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d22bu; native_call(m, 0x49f167u);	/* 42d226: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d22b: push esi */
	{ DWORD v_ = 0x4b1de8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d22c: push 0x4b1de8 */
	m->esp -= 4; M32(m->esp) = 0x42d236u; native_call(m, 0x49f167u);	/* 42d231: call 0x49f167 */
	m->eax = M32((DWORD)(0x4def9cu));	/* 42d236: mov eax, dword ptr [0x4def9c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d23b: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d23c: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d243: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d249u; native_call(m, 0x49f167u);	/* 42d244: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d249: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d24a: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d254u; native_call(m, 0x49f167u);	/* 42d24f: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d254: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d257: push esi */
	{ DWORD v_ = 0x4b1dd4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d258: push 0x4b1dd4 */
	m->esp -= 4; M32(m->esp) = 0x42d262u; native_call(m, 0x49f167u);	/* 42d25d: call 0x49f167 */
	m->edx = M32((DWORD)(0x4defa0u));	/* 42d262: mov edx, dword ptr [0x4defa0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d268: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d269: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d270: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d276u; native_call(m, 0x49f167u);	/* 42d271: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d276: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d277: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d281u; native_call(m, 0x49f167u);	/* 42d27c: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d281: push esi */
	{ DWORD v_ = 0x4b1dc0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d282: push 0x4b1dc0 */
	m->esp -= 4; M32(m->esp) = 0x42d28cu; native_call(m, 0x49f167u);	/* 42d287: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4defa4u));	/* 42d28c: mov ecx, dword ptr [0x4defa4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d292: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d293: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d29a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d2a0u; native_call(m, 0x49f167u);	/* 42d29b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2a0: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2a1: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d2abu; native_call(m, 0x49f167u);	/* 42d2a6: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2ab: push esi */
	{ DWORD v_ = 0x4b1db0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2ac: push 0x4b1db0 */
	m->esp -= 4; M32(m->esp) = 0x42d2b6u; native_call(m, 0x49f167u);	/* 42d2b1: call 0x49f167 */
	m->eax = M32((DWORD)(0x4defa8u));	/* 42d2b6: mov eax, dword ptr [0x4defa8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2bb: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d2bc: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2c3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d2c9u; native_call(m, 0x49f167u);	/* 42d2c4: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d2c9: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2cc: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2cd: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d2d7u; native_call(m, 0x49f167u);	/* 42d2d2: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2d7: push esi */
	{ DWORD v_ = 0x4b1da0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2d8: push 0x4b1da0 */
	m->esp -= 4; M32(m->esp) = 0x42d2e2u; native_call(m, 0x49f167u);	/* 42d2dd: call 0x49f167 */
	m->edx = M32((DWORD)(0x4defacu));	/* 42d2e2: mov edx, dword ptr [0x4defac] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2e8: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d2e9: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2f0: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d2f6u; native_call(m, 0x49f167u);	/* 42d2f1: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2f6: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d2f7: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d301u; native_call(m, 0x49f167u);	/* 42d2fc: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d301: push esi */
	{ DWORD v_ = 0x4b1d8cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d302: push 0x4b1d8c */
	m->esp -= 4; M32(m->esp) = 0x42d30cu; native_call(m, 0x49f167u);	/* 42d307: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4defb0u));	/* 42d30c: mov ecx, dword ptr [0x4defb0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d312: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d313: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d31a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d320u; native_call(m, 0x49f167u);	/* 42d31b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d320: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d321: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d32bu; native_call(m, 0x49f167u);	/* 42d326: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d32b: push esi */
	{ DWORD v_ = 0x4b1d78u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d32c: push 0x4b1d78 */
	m->esp -= 4; M32(m->esp) = 0x42d336u; native_call(m, 0x49f167u);	/* 42d331: call 0x49f167 */
	m->eax = M32((DWORD)(0x4defb4u));	/* 42d336: mov eax, dword ptr [0x4defb4] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d33b: add esp, 0x40 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d33e: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d345: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d346: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d34cu; native_call(m, 0x49f167u);	/* 42d347: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d34c: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d34d: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d357u; native_call(m, 0x49f167u);	/* 42d352: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d357: push esi */
	{ DWORD v_ = 0x4b1d64u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d358: push 0x4b1d64 */
	m->esp -= 4; M32(m->esp) = 0x42d362u; native_call(m, 0x49f167u);	/* 42d35d: call 0x49f167 */
	m->edx = M32((DWORD)(0x4defb8u));	/* 42d362: mov edx, dword ptr [0x4defb8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d368: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d369: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d370: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d376u; native_call(m, 0x49f167u);	/* 42d371: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d376: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d377: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d381u; native_call(m, 0x49f167u);	/* 42d37c: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d381: push esi */
	{ DWORD v_ = 0x4b1d50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d382: push 0x4b1d50 */
	m->esp -= 4; M32(m->esp) = 0x42d38cu; native_call(m, 0x49f167u);	/* 42d387: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4defbcu));	/* 42d38c: mov ecx, dword ptr [0x4defbc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d392: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d393: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d39a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d3a0u; native_call(m, 0x49f167u);	/* 42d39b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3a0: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3a1: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d3abu; native_call(m, 0x49f167u);	/* 42d3a6: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d3ab: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3ae: push esi */
	{ DWORD v_ = 0x4b1d3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3af: push 0x4b1d3c */
	m->esp -= 4; M32(m->esp) = 0x42d3b9u; native_call(m, 0x49f167u);	/* 42d3b4: call 0x49f167 */
	m->eax = M32((DWORD)(0x4defc0u));	/* 42d3b9: mov eax, dword ptr [0x4defc0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3be: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d3bf: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3c6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d3ccu; native_call(m, 0x49f167u);	/* 42d3c7: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3cc: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3cd: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d3d7u; native_call(m, 0x49f167u);	/* 42d3d2: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3d7: push esi */
	{ DWORD v_ = 0x4b1d28u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3d8: push 0x4b1d28 */
	m->esp -= 4; M32(m->esp) = 0x42d3e2u; native_call(m, 0x49f167u);	/* 42d3dd: call 0x49f167 */
	m->edx = M32((DWORD)(0x4defc4u));	/* 42d3e2: mov edx, dword ptr [0x4defc4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3e8: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d3e9: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3f0: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d3f6u; native_call(m, 0x49f167u);	/* 42d3f1: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3f6: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d3f7: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d401u; native_call(m, 0x49f167u);	/* 42d3fc: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d401: push esi */
	{ DWORD v_ = 0x4b1d14u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d402: push 0x4b1d14 */
	m->esp -= 4; M32(m->esp) = 0x42d40cu; native_call(m, 0x49f167u);	/* 42d407: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4defc8u));	/* 42d40c: mov ecx, dword ptr [0x4defc8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d412: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d413: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d41a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d420u; native_call(m, 0x49f167u);	/* 42d41b: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d420: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d423: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d424: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d42eu; native_call(m, 0x49f167u);	/* 42d429: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d42e: push esi */
	{ DWORD v_ = 0x4b1d00u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d42f: push 0x4b1d00 */
	m->esp -= 4; M32(m->esp) = 0x42d439u; native_call(m, 0x49f167u);	/* 42d434: call 0x49f167 */
	m->eax = M32((DWORD)(0x4defccu));	/* 42d439: mov eax, dword ptr [0x4defcc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d43e: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d43f: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d446: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d44cu; native_call(m, 0x49f167u);	/* 42d447: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d44c: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d44d: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d457u; native_call(m, 0x49f167u);	/* 42d452: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d457: push esi */
	{ DWORD v_ = 0x4b1ce8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d458: push 0x4b1ce8 */
	m->esp -= 4; M32(m->esp) = 0x42d462u; native_call(m, 0x49f167u);	/* 42d45d: call 0x49f167 */
	m->edx = M32((DWORD)(0x4defd0u));	/* 42d462: mov edx, dword ptr [0x4defd0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d468: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d469: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d470: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d476u; native_call(m, 0x49f167u);	/* 42d471: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d476: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d477: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d481u; native_call(m, 0x49f167u);	/* 42d47c: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d481: push esi */
	{ DWORD v_ = 0x4b1cd0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d482: push 0x4b1cd0 */
	m->esp -= 4; M32(m->esp) = 0x42d48cu; native_call(m, 0x49f167u);	/* 42d487: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4defd4u));	/* 42d48c: mov ecx, dword ptr [0x4defd4] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d492: add esp, 0x40 */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d495: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d49c: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d49d: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d4a3u; native_call(m, 0x49f167u);	/* 42d49e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4a3: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4a4: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d4aeu; native_call(m, 0x49f167u);	/* 42d4a9: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4ae: push esi */
	{ DWORD v_ = 0x4b1cb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4af: push 0x4b1cb8 */
	m->esp -= 4; M32(m->esp) = 0x42d4b9u; native_call(m, 0x49f167u);	/* 42d4b4: call 0x49f167 */
	m->eax = M32((DWORD)(0x4defd8u));	/* 42d4b9: mov eax, dword ptr [0x4defd8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4be: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d4bf: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4c6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d4ccu; native_call(m, 0x49f167u);	/* 42d4c7: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4cc: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4cd: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d4d7u; native_call(m, 0x49f167u);	/* 42d4d2: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4d7: push esi */
	{ DWORD v_ = 0x4b1ca0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4d8: push 0x4b1ca0 */
	m->esp -= 4; M32(m->esp) = 0x42d4e2u; native_call(m, 0x49f167u);	/* 42d4dd: call 0x49f167 */
	m->edx = M32((DWORD)(0x4defdcu));	/* 42d4e2: mov edx, dword ptr [0x4defdc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4e8: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d4e9: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4f0: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d4f6u; native_call(m, 0x49f167u);	/* 42d4f1: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4f6: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d4f7: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d501u; native_call(m, 0x49f167u);	/* 42d4fc: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d501: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d504: push esi */
	{ DWORD v_ = 0x4b1c90u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d505: push 0x4b1c90 */
	m->esp -= 4; M32(m->esp) = 0x42d50fu; native_call(m, 0x49f167u);	/* 42d50a: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4defe0u));	/* 42d50f: mov ecx, dword ptr [0x4defe0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d515: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d516: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d51d: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d523u; native_call(m, 0x49f167u);	/* 42d51e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d523: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d524: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d52eu; native_call(m, 0x49f167u);	/* 42d529: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d52e: push esi */
	{ DWORD v_ = 0x4b1c80u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d52f: push 0x4b1c80 */
	m->esp -= 4; M32(m->esp) = 0x42d539u; native_call(m, 0x49f167u);	/* 42d534: call 0x49f167 */
	m->eax = M32((DWORD)(0x4defe4u));	/* 42d539: mov eax, dword ptr [0x4defe4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d53e: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d53f: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d546: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d54cu; native_call(m, 0x49f167u);	/* 42d547: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d54c: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d54d: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d557u; native_call(m, 0x49f167u);	/* 42d552: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d557: push esi */
	{ DWORD v_ = 0x4b1c64u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d558: push 0x4b1c64 */
	m->esp -= 4; M32(m->esp) = 0x42d562u; native_call(m, 0x49f167u);	/* 42d55d: call 0x49f167 */
	m->edx = M32((DWORD)(0x4defe8u));	/* 42d562: mov edx, dword ptr [0x4defe8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d568: push esi */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d569: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d570: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d576u; native_call(m, 0x49f167u);	/* 42d571: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d576: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d579: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d57a: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d584u; native_call(m, 0x49f167u);	/* 42d57f: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d584: push esi */
	{ DWORD v_ = 0x4b1c48u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d585: push 0x4b1c48 */
	m->esp -= 4; M32(m->esp) = 0x42d58fu; native_call(m, 0x49f167u);	/* 42d58a: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4defecu));	/* 42d58f: mov ecx, dword ptr [0x4defec] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d595: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d596: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d59d: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d5a3u; native_call(m, 0x49f167u);	/* 42d59e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5a3: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5a4: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d5aeu; native_call(m, 0x49f167u);	/* 42d5a9: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5ae: push esi */
	{ DWORD v_ = 0x4b1c2cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5af: push 0x4b1c2c */
	m->esp -= 4; M32(m->esp) = 0x42d5b9u; native_call(m, 0x49f167u);	/* 42d5b4: call 0x49f167 */
	m->eax = M32((DWORD)(0x4deff0u));	/* 42d5b9: mov eax, dword ptr [0x4deff0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5be: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d5bf: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5c6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d5ccu; native_call(m, 0x49f167u);	/* 42d5c7: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5cc: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5cd: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d5d7u; native_call(m, 0x49f167u);	/* 42d5d2: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5d7: push esi */
	{ DWORD v_ = 0x4b1c10u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5d8: push 0x4b1c10 */
	m->esp -= 4; M32(m->esp) = 0x42d5e2u; native_call(m, 0x49f167u);	/* 42d5dd: call 0x49f167 */
	m->edx = M32((DWORD)(0x4deff4u));	/* 42d5e2: mov edx, dword ptr [0x4deff4] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d5e8: add esp, 0x40 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b0750u));	/* 42d5eb: mov eax, dword ptr [edx*4 + 0x4b0750] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5f2: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5f3: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d5f9u; native_call(m, 0x49f167u);	/* 42d5f4: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5f9: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d5fa: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d604u; native_call(m, 0x49f167u);	/* 42d5ff: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d604: push esi */
	{ DWORD v_ = 0x4b1c00u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d605: push 0x4b1c00 */
	m->esp -= 4; M32(m->esp) = 0x42d60fu; native_call(m, 0x49f167u);	/* 42d60a: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4deff8u));	/* 42d60f: mov ecx, dword ptr [0x4deff8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d615: push esi */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b0750u));	/* 42d616: mov edx, dword ptr [ecx*4 + 0x4b0750] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d61d: push edx */
	m->esp -= 4; M32(m->esp) = 0x42d623u; native_call(m, 0x49f167u);	/* 42d61e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d623: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d624: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d62eu; native_call(m, 0x49f167u);	/* 42d629: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d62e: push esi */
	{ DWORD v_ = 0x4b1bf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d62f: push 0x4b1bf0 */
	m->esp -= 4; M32(m->esp) = 0x42d639u; native_call(m, 0x49f167u);	/* 42d634: call 0x49f167 */
	m->eax = M32((DWORD)(0x4deffcu));	/* 42d639: mov eax, dword ptr [0x4deffc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d63e: push esi */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42d63f: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d646: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d64cu; native_call(m, 0x49f167u);	/* 42d647: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d64c: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d64d: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d657u; native_call(m, 0x49f167u);	/* 42d652: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d657: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d65a: push esi */
	{ DWORD v_ = 0x4b1bd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d65b: push 0x4b1bd8 */
	m->esp -= 4; M32(m->esp) = 0x42d665u; native_call(m, 0x49f167u);	/* 42d660: call 0x49f167 */
	m->eax = M32((DWORD)(0x4df000u));	/* 42d665: mov eax, dword ptr [0x4df000] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d66a: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42d66d: cmp eax, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d670: push esi */
	if (!m->zf) goto L_42d67a;	/* 42d671: jne 0x42d67a */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d673: push 0x4b17e4 */
	goto L_42d67f;	/* 42d678: jmp 0x42d67f */
L_42d67a:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d67a: push 0x4b17dc */
L_42d67f:
	m->esp -= 4; M32(m->esp) = 0x42d684u; native_call(m, 0x49f167u);	/* 42d67f: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d684: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d687: push esi */
	{ DWORD v_ = 0x4b1bc0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d688: push 0x4b1bc0 */
	m->esp -= 4; M32(m->esp) = 0x42d692u; native_call(m, 0x49f167u);	/* 42d68d: call 0x49f167 */
	m->eax = M32((DWORD)(0x4df004u));	/* 42d692: mov eax, dword ptr [0x4df004] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d697: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42d69a: cmp eax, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d69d: push esi */
	if (!m->zf) goto L_42d6a7;	/* 42d69e: jne 0x42d6a7 */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6a0: push 0x4b17e4 */
	goto L_42d6ac;	/* 42d6a5: jmp 0x42d6ac */
L_42d6a7:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6a7: push 0x4b17dc */
L_42d6ac:
	m->esp -= 4; M32(m->esp) = 0x42d6b1u; native_call(m, 0x49f167u);	/* 42d6ac: call 0x49f167 */
	m->eax = M32((DWORD)(0x4df008u));	/* 42d6b1: mov eax, dword ptr [0x4df008] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d6b6: add esp, 8 */
	m->edx = (DWORD)(m->esp + 0x4u);	/* 42d6b9: lea edx, [esp + 4] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6bd: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6bf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6c0: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d6c6u; native_call(m, 0x49fb53u);	/* 42d6c1: call 0x49fb53 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6c6: push esi */
	{ DWORD v_ = 0x4b1ba8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6c7: push 0x4b1ba8 */
	m->esp -= 4; M32(m->esp) = 0x42d6d1u; native_call(m, 0x49f167u);	/* 42d6cc: call 0x49f167 */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 42d6d1: lea ecx, [esp + 0x18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6d5: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6d6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d6dcu; native_call(m, 0x49f167u);	/* 42d6d7: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6dc: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6dd: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d6e7u; native_call(m, 0x49f167u);	/* 42d6e2: call 0x49f167 */
	m->eax = M32((DWORD)(0x4df00cu));	/* 42d6e7: mov eax, dword ptr [0x4df00c] */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 42d6ec: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6f0: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6f2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6f3: push eax */
	m->esp -= 4; M32(m->esp) = 0x42d6f9u; native_call(m, 0x49fb53u);	/* 42d6f4: call 0x49fb53 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6f9: push esi */
	{ DWORD v_ = 0x4b1b90u; m->esp -= 4; M32(m->esp) = v_; }	/* 42d6fa: push 0x4b1b90 */
	m->esp -= 4; M32(m->esp) = 0x42d704u; native_call(m, 0x49f167u);	/* 42d6ff: call 0x49f167 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 42d704: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d708: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42d709: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42d70fu; native_call(m, 0x49f167u);	/* 42d70a: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d70f: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42d712: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42d713: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42d71du; native_call(m, 0x49f167u);	/* 42d718: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d71d: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42d720: pop esi */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42d721: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 42d724: ret  */
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
