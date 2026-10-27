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

static void lift_464bf0(X86 *m);

/* model_loadFrom (0x464bf0), lifted by tools/lift.py */
static void lift_464bf0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464bf0: sub esp, 0x10c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 464bf6: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x114u));	/* 464bf7: mov ebp, dword ptr [esp + 0x114] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464bfe: push esi */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 464bff: push 0x4ad170 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 464c04: mov dword ptr [esp + 0x14], ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 464c08: push ebp */
	m->esp -= 4; M32(m->esp) = 0x464c0eu; native_call(m, 0x49e9cau);	/* 464c09: call 0x49e9ca */
	m->esi = m->eax;	/* 464c0e: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464c10: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464c13: test esi, esi */
	M32((DWORD)(m->esp + 0xcu)) = m->esi;	/* 464c15: mov dword ptr [esp + 0xc], esi */
	if (!m->zf) goto L_464c2e;	/* 464c19: jne 0x464c2e */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 464c1b: push ebp */
	{ DWORD v_ = 0x4c4ae4u; m->esp -= 4; M32(m->esp) = v_; }	/* 464c1c: push 0x4c4ae4 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 464c21: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x464c2bu; native_call(m, 0x46c710u);	/* 464c26: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464c2b: add esp, 0xc */
L_464c2e:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 464c2e: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 464c2f: push edi */
	m->edi = m->ebp;	/* 464c30: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464c32: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464c35: xor eax, eax */
	M32((DWORD)(m->esp + 0x10u)) = 0xffffffffu;	/* 464c37: mov dword ptr [esp + 0x10], 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 464c3f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 464c41: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 464c43: dec ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 464c44: dec ecx */
	if (m->sf) goto L_464d12;	/* 464c45: js 0x464d12 */
L_464c4b:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + m->ebp*1 + 0x0u))) & 0xff) << 0);	/* 464c4b: mov al, byte ptr [ecx + ebp] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2eu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464c4e: cmp al, 0x2e */
	if (m->zf) goto L_464c6a;	/* 464c50: je 0x464c6a */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x5cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464c52: cmp al, 0x5c */
	if (m->zf) goto L_464d12;	/* 464c54: je 0x464d12 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2fu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 464c5a: cmp al, 0x2f */
	if (m->zf) goto L_464d12;	/* 464c5c: je 0x464d12 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 464c62: dec ecx */
	if (!m->sf) goto L_464c4b;	/* 464c63: jns 0x464c4b */
	goto L_464d12;	/* 464c65: jmp 0x464d12 */
L_464c6a:
	m->edi = (DWORD)(m->ecx + m->ebp*1 + 0x1u);	/* 464c6a: lea edi, [ecx + ebp + 1] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464c6e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464c71: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 464c73: lea edx, [esp + 0x1c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 464c77: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 464c79: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 464c7b: sub edi, ecx */
	m->eax = m->ecx;	/* 464c7d: mov eax, ecx */
	m->esi = m->edi;	/* 464c7f: mov esi, edi */
	m->edi = m->edx;	/* 464c81: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 464c83: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 464c86: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 464c88: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464c8a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 464c8d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x1cu)));	/* 464c8f: movsx esi, byte ptr [esp + 0x1c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464c94: push esi */
	m->esp -= 4; M32(m->esp) = 0x464c9au; native_call(m, 0x49fdafu);	/* 464c95: call 0x49fdaf */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x21u))) & 0xff) << 0);	/* 464c9a: mov bl, byte ptr [esp + 0x21] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464c9e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x73u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464ca1: cmp eax, 0x73 */
	if (!m->zf) goto L_464cd4;	/* 464ca4: jne 0x464cd4 */
	m->ecx = (DWORD)(int)(signed char)(((m->ebx >> 0) & 0xff));	/* 464ca6: movsx ecx, bl */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 464ca9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x464cafu; native_call(m, 0x49fdafu);	/* 464caa: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464caf: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x68u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464cb2: cmp eax, 0x68 */
	if (!m->zf) goto L_464cd4;	/* 464cb5: jne 0x464cd4 */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x1eu)));	/* 464cb7: movsx edx, byte ptr [esp + 0x1e] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 464cbc: push edx */
	m->esp -= 4; M32(m->esp) = 0x464cc2u; native_call(m, 0x49fdafu);	/* 464cbd: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464cc2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x70u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464cc5: cmp eax, 0x70 */
	if (!m->zf) goto L_464cd4;	/* 464cc8: jne 0x464cd4 */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 464cca: mov dword ptr [esp + 0x10], 0 */
	goto L_464d0e;	/* 464cd2: jmp 0x464d0e */
L_464cd4:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464cd4: push esi */
	m->esp -= 4; M32(m->esp) = 0x464cdau; native_call(m, 0x49fdafu);	/* 464cd5: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464cda: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x6fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464cdd: cmp eax, 0x6f */
	if (!m->zf) goto L_464d0e;	/* 464ce0: jne 0x464d0e */
	m->eax = (DWORD)(int)(signed char)(((m->ebx >> 0) & 0xff));	/* 464ce2: movsx eax, bl */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 464ce5: push eax */
	m->esp -= 4; M32(m->esp) = 0x464cebu; native_call(m, 0x49fdafu);	/* 464ce6: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464ceb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x62u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464cee: cmp eax, 0x62 */
	if (!m->zf) goto L_464d0e;	/* 464cf1: jne 0x464d0e */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x1eu)));	/* 464cf3: movsx ecx, byte ptr [esp + 0x1e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 464cf8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x464cfeu; native_call(m, 0x49fdafu);	/* 464cf9: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464cfe: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x6au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464d01: cmp eax, 0x6a */
	if (!m->zf) goto L_464d0e;	/* 464d04: jne 0x464d0e */
	M32((DWORD)(m->esp + 0x10u)) = 0x1u;	/* 464d06: mov dword ptr [esp + 0x10], 1 */
L_464d0e:
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 464d0e: mov esi, dword ptr [esp + 0x14] */
L_464d12:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 464d12: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32(m->esp); m->esp += 4;	/* 464d16: pop edi */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 464d17: sub eax, 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 464d1a: pop ebx */
	if (m->zf) goto L_464d75;	/* 464d1b: je 0x464d75 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 464d1d: dec eax */
	if (m->zf) goto L_464d47;	/* 464d1e: je 0x464d47 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 464d20: push ebp */
	{ DWORD v_ = 0x4c4aa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 464d21: push 0x4c4aa4 */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 464d26: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x464d30u; native_call(m, 0x46c710u);	/* 464d2b: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464d30: add esp, 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464d33: push esi */
	m->esp -= 4; M32(m->esp) = 0x464d39u; native_call(m, 0x49e7e0u);	/* 464d34: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464d39: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 464d3c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 464d3d: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464d3e: add esp, 0x10c */
	m->esp += 4 + 12; return;	/* 464d44: ret 0xc */
L_464d47:
	m->edx = M32((DWORD)(m->esp + 0x120u));	/* 464d47: mov edx, dword ptr [esp + 0x120] */
	m->eax = M32((DWORD)(m->esp + 0x11cu));	/* 464d4e: mov eax, dword ptr [esp + 0x11c] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 464d55: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 464d59: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 464d5a: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464d5b: push esi */
	m->esp -= 4; M32(m->esp) = 0x464d61u; native_call(m, 0x464db0u);	/* 464d5c: call 0x464db0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464d61: push esi */
	m->esp -= 4; M32(m->esp) = 0x464d67u; native_call(m, 0x49e7e0u);	/* 464d62: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464d67: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 464d6a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 464d6b: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464d6c: add esp, 0x10c */
	m->esp += 4 + 12; return;	/* 464d72: ret 0xc */
L_464d75:
	m->ecx = M32((DWORD)(m->esp + 0x120u));	/* 464d75: mov ecx, dword ptr [esp + 0x120] */
	m->edx = M32((DWORD)(m->esp + 0x11cu));	/* 464d7c: mov edx, dword ptr [esp + 0x11c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 464d83: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 464d84: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 464d88: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464d89: push esi */
	m->esp -= 4; M32(m->esp) = 0x464d8fu; native_call(m, 0x466120u);	/* 464d8a: call 0x466120 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 464d8f: push esi */
	m->esp -= 4; M32(m->esp) = 0x464d95u; native_call(m, 0x49e7e0u);	/* 464d90: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464d95: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 464d98: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 464d99: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464d9a: add esp, 0x10c */
	m->esp += 4 + 12; return;	/* 464da0: ret 0xc */
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
