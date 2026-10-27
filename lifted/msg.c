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

static void lift_462e30(X86 *m);
static void lift_4630c0(X86 *m);
static void lift_462d30(X86 *m);

/* msg_playerJoinedTeam (0x462d30), lifted by tools/lift.py */
static void lift_462d30(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462d30: push esi */
	m->esi = m->ecx;	/* 462d31: mov esi, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 462d33: mov ecx, dword ptr [esp + 8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 462d37: push edi */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 462d38: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462d3b: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462d3e: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 462d40: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 462d43: lea ecx, [ecx + eax*8] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + m->ecx*2 + 0x1755234u))) & 0xff) << 0);	/* 462d46: mov al, byte ptr [esi + ecx*2 + 0x1755234] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 462d4d: test al, al */
	m->edi = (DWORD)(m->esi + m->ecx*2 + 0x1755234u);	/* 462d4f: lea edi, [esi + ecx*2 + 0x1755234] */
	if (m->zf) goto L_462e24;	/* 462d56: je 0x462e24 */
	m->eax = M32((DWORD)(0x9dae74u));	/* 462d5c: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462d61: dec eax */
	if (m->zf) goto L_462dca;	/* 462d62: je 0x462dca */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462d64: dec eax */
	if (!m->zf) goto L_462e24;	/* 462d65: jne 0x462e24 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462d6b: cmp dword ptr [esi + 0x22e7184], 1 */
	if (!m->zf) goto L_462d9f;	/* 462d72: jne 0x462d9f */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 462d74: mov edx, dword ptr [esp + 0x10] */
	m->ecx = m->esi;	/* 462d78: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462d7a: push edx */
	m->esp -= 4; M32(m->esp) = 0x462d80u; native_call(m, 0x463740u);	/* 462d7b: call 0x463740 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462d80: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x4a97acu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462d83: add eax, 0x4a97ac */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462d88: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 462d89: push edi */
	{ DWORD v_ = 0x4c471cu; m->esp -= 4; M32(m->esp) = v_; }	/* 462d8a: push 0x4c471c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462d8f: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462d91: push esi */
	m->esp -= 4; M32(m->esp) = 0x462d97u; native_call(m, 0x4629f0u);	/* 462d92: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462d97: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 462d9a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 462d9b: pop esi */
	m->esp += 4 + 8; return;	/* 462d9c: ret 8 */
L_462d9f:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 462d9f: mov eax, dword ptr [esp + 0x10] */
	m->ecx = m->esi;	/* 462da3: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462da5: push eax */
	m->esp -= 4; M32(m->esp) = 0x462dabu; native_call(m, 0x463740u);	/* 462da6: call 0x463740 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462dab: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x4a97acu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462dae: add eax, 0x4a97ac */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462db3: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 462db4: push edi */
	{ DWORD v_ = 0x4c4700u; m->esp -= 4; M32(m->esp) = v_; }	/* 462db5: push 0x4c4700 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462dba: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462dbc: push esi */
	m->esp -= 4; M32(m->esp) = 0x462dc2u; native_call(m, 0x4629f0u);	/* 462dbd: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462dc2: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 462dc5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 462dc6: pop esi */
	m->esp += 4 + 8; return;	/* 462dc7: ret 8 */
L_462dca:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462dca: cmp dword ptr [esi + 0x22e7184], 1 */
	if (!m->zf) goto L_462dfe;	/* 462dd1: jne 0x462dfe */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 462dd3: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 462dd7: push ecx */
	m->ecx = m->esi;	/* 462dd8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x462ddfu; native_call(m, 0x463740u);	/* 462dda: call 0x463740 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462ddf: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x4a975cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462de2: add eax, 0x4a975c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462de7: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 462de8: push edi */
	{ DWORD v_ = 0x4c46e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 462de9: push 0x4c46e4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462dee: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462df0: push esi */
	m->esp -= 4; M32(m->esp) = 0x462df6u; native_call(m, 0x4629f0u);	/* 462df1: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462df6: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 462df9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 462dfa: pop esi */
	m->esp += 4 + 8; return;	/* 462dfb: ret 8 */
L_462dfe:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 462dfe: mov edx, dword ptr [esp + 0x10] */
	m->ecx = m->esi;	/* 462e02: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462e04: push edx */
	m->esp -= 4; M32(m->esp) = 0x462e0au; native_call(m, 0x463740u);	/* 462e05: call 0x463740 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462e0a: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x4a975cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462e0d: add eax, 0x4a975c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462e12: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 462e13: push edi */
	{ DWORD v_ = 0x4c46c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 462e14: push 0x4c46c8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462e19: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462e1b: push esi */
	m->esp -= 4; M32(m->esp) = 0x462e21u; native_call(m, 0x4629f0u);	/* 462e1c: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462e21: add esp, 0x14 */
L_462e24:
	m->edi = M32(m->esp); m->esp += 4;	/* 462e24: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 462e25: pop esi */
	m->esp += 4 + 8; return;	/* 462e26: ret 8 */
}

/* msg_playerChangedTeam (0x462e30), lifted by tools/lift.py */
static void lift_462e30(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 462e30: mov eax, dword ptr [0x9dae74] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462e35: push esi */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462e36: dec eax */
	m->esi = m->ecx;	/* 462e37: mov esi, ecx */
	if (m->zf) goto L_462eb5;	/* 462e39: je 0x462eb5 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462e3b: dec eax */
	if (!m->zf) goto L_462f26;	/* 462e3c: jne 0x462f26 */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 462e42: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 462e46: test eax, eax */
	if (m->sf != m->of) goto L_462e87;	/* 462e48: jl 0x462e87 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462e4a: push eax */
	m->esp -= 4; M32(m->esp) = 0x462e50u; native_call(m, 0x463740u);	/* 462e4b: call 0x463740 */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 462e50: mov ecx, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462e54: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x4a97acu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462e57: add eax, 0x4a97ac */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462e5c: push eax */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 462e5d: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462e60: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462e63: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 462e65: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 462e68: lea ecx, [ecx + eax*8] */
	m->edx = (DWORD)(m->esi + m->ecx*2 + 0x1755234u);	/* 462e6b: lea edx, [esi + ecx*2 + 0x1755234] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462e72: push edx */
	{ DWORD v_ = 0x4c4790u; m->esp -= 4; M32(m->esp) = v_; }	/* 462e73: push 0x4c4790 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462e78: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462e7a: push esi */
	m->esp -= 4; M32(m->esp) = 0x462e80u; native_call(m, 0x4629f0u);	/* 462e7b: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462e80: add esp, 0x14 */
	m->esi = M32(m->esp); m->esp += 4;	/* 462e83: pop esi */
	m->esp += 4 + 8; return;	/* 462e84: ret 8 */
L_462e87:
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 462e87: mov ecx, dword ptr [esp + 8] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 462e8b: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462e8e: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462e91: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 462e93: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 462e96: lea ecx, [ecx + eax*8] */
	m->edx = (DWORD)(m->esi + m->ecx*2 + 0x1755234u);	/* 462e99: lea edx, [esi + ecx*2 + 0x1755234] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462ea0: push edx */
	{ DWORD v_ = 0x4c4778u; m->esp -= 4; M32(m->esp) = v_; }	/* 462ea1: push 0x4c4778 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462ea6: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462ea8: push esi */
	m->esp -= 4; M32(m->esp) = 0x462eaeu; native_call(m, 0x4629f0u);	/* 462ea9: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462eae: add esp, 0x10 */
	m->esi = M32(m->esp); m->esp += 4;	/* 462eb1: pop esi */
	m->esp += 4 + 8; return;	/* 462eb2: ret 8 */
L_462eb5:
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 462eb5: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 462eb9: test eax, eax */
	if (m->sf != m->of) goto L_462efc;	/* 462ebb: jl 0x462efc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462ebd: push eax */
	m->ecx = m->esi;	/* 462ebe: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x462ec5u; native_call(m, 0x463740u);	/* 462ec0: call 0x463740 */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 462ec5: mov ecx, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462ec9: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x4a975cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462ecc: add eax, 0x4a975c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462ed1: push eax */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 462ed2: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462ed5: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462ed8: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 462eda: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 462edd: lea ecx, [ecx + eax*8] */
	m->edx = (DWORD)(m->esi + m->ecx*2 + 0x1755234u);	/* 462ee0: lea edx, [esi + ecx*2 + 0x1755234] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462ee7: push edx */
	{ DWORD v_ = 0x4c4754u; m->esp -= 4; M32(m->esp) = v_; }	/* 462ee8: push 0x4c4754 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462eed: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462eef: push esi */
	m->esp -= 4; M32(m->esp) = 0x462ef5u; native_call(m, 0x4629f0u);	/* 462ef0: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462ef5: add esp, 0x14 */
	m->esi = M32(m->esp); m->esp += 4;	/* 462ef8: pop esi */
	m->esp += 4 + 8; return;	/* 462ef9: ret 8 */
L_462efc:
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 462efc: mov ecx, dword ptr [esp + 8] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 462f00: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 462f03: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462f06: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 462f08: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 462f0b: lea ecx, [ecx + eax*8] */
	m->edx = (DWORD)(m->esi + m->ecx*2 + 0x1755234u);	/* 462f0e: lea edx, [esi + ecx*2 + 0x1755234] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462f15: push edx */
	{ DWORD v_ = 0x4c4734u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f16: push 0x4c4734 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f1b: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462f1d: push esi */
	m->esp -= 4; M32(m->esp) = 0x462f23u; native_call(m, 0x4629f0u);	/* 462f1e: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462f23: add esp, 0x10 */
L_462f26:
	m->esi = M32(m->esp); m->esp += 4;	/* 462f26: pop esi */
	m->esp += 4 + 8; return;	/* 462f27: ret 8 */
}

/* msg_kill (0x4630c0), lifted by tools/lift.py */
static void lift_4630c0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4630c0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4630c4: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4630c5: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4630c7: push edi */
	if (m->sf != m->of) goto L_46337d;	/* 4630c8: jl 0x46337d */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4630ce: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4630d2: test edx, edx */
	if (m->sf != m->of) goto L_46337d;	/* 4630d4: jl 0x46337d */
	m->esi = M32((DWORD)(0x9dae74u));	/* 4630da: mov esi, dword ptr [0x9dae74] */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 4630e0: dec esi */
	if (m->zf) goto L_463238;	/* 4630e1: je 0x463238 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 4630e7: dec esi */
	if (!m->zf) goto L_46337d;	/* 4630e8: jne 0x46337d */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4630ee: cmp eax, edx */
	if (!m->zf) goto L_463156;	/* 4630f0: jne 0x463156 */
	m->edx = M32((DWORD)(m->ecx + 0x234240du));	/* 4630f2: mov edx, dword ptr [ecx + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4630f8: cmp eax, edx */
	m->edx = m->eax;	/* 4630fa: mov edx, eax */
	if (!m->zf) goto L_46312a;	/* 4630fc: jne 0x46312a */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4630fe: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463101: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463103: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463106: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463108: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46310b: add edx, eax */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x1eccb08u);	/* 46310d: lea eax, [ecx + edx*8 + 0x1eccb08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 463114: push eax */
	{ DWORD v_ = 0x4c4924u; m->esp -= 4; M32(m->esp) = v_; }	/* 463115: push 0x4c4924 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46311a: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46311c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x463122u; native_call(m, 0x4629f0u);	/* 46311d: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463122: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 463125: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 463126: pop esi */
	m->esp += 4 + 8; return;	/* 463127: ret 8 */
L_46312a:
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46312a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46312d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46312f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463132: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463134: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463137: add edx, eax */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x1eccb08u);	/* 463139: lea eax, [ecx + edx*8 + 0x1eccb08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 463140: push eax */
	{ DWORD v_ = 0x4c4924u; m->esp -= 4; M32(m->esp) = v_; }	/* 463141: push 0x4c4924 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 463146: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 463148: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46314eu; native_call(m, 0x4629f0u);	/* 463149: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46314e: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 463151: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 463152: pop esi */
	m->esp += 4 + 8; return;	/* 463153: ret 8 */
L_463156:
	m->esi = M32((DWORD)(m->ecx + 0x234240du));	/* 463156: mov esi, dword ptr [ecx + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46315c: cmp eax, esi */
	if (m->zf) goto L_4631ce;	/* 46315e: je 0x4631ce */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463160: cmp edx, esi */
	if (m->zf) goto L_4631ce;	/* 463162: je 0x4631ce */
	m->esi = m->eax;	/* 463164: mov esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 463166: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 463169: add esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46316b: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46316e: add esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 463170: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 463173: add esi, eax */
	m->edi = (DWORD)(m->ecx + m->esi*8 + 0x0u);	/* 463175: lea edi, [ecx + esi*8] */
	m->esi = M32((DWORD)(m->ecx + m->esi*8 + 0x1eccf34u));	/* 463178: mov esi, dword ptr [ecx + esi*8 + 0x1eccf34] */
	{ DWORD a_ = m->edi, b_ = 0x1eccb08u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46317f: add edi, 0x1eccb08 */
	m->eax = m->esi;	/* 463185: mov eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 463187: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46318a: sub eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46318c: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46318f: sub eax, esi */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 463191: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 463194: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->eax*8 + 0x16c5181u);	/* 463197: lea eax, [ecx + eax*8 + 0x16c5181] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46319e: push eax */
	m->eax = m->edx;	/* 46319f: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4631a1: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4631a4: add eax, edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4631a6: push edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4631a7: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4631aa: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4631ac: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4631af: add eax, edx */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x1eccb08u);	/* 4631b1: lea edx, [ecx + eax*8 + 0x1eccb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4631b8: push edx */
	{ DWORD v_ = 0x4c490cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4631b9: push 0x4c490c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4631be: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4631c0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4631c6u; native_call(m, 0x4629f0u);	/* 4631c1: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4631c6: add esp, 0x18 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4631c9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4631ca: pop esi */
	m->esp += 4 + 8; return;	/* 4631cb: ret 8 */
L_4631ce:
	m->esi = m->eax;	/* 4631ce: mov esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4631d0: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4631d3: add esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4631d5: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4631d8: add esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4631da: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4631dd: add esi, eax */
	m->edi = (DWORD)(m->ecx + m->esi*8 + 0x0u);	/* 4631df: lea edi, [ecx + esi*8] */
	m->esi = M32((DWORD)(m->ecx + m->esi*8 + 0x1eccf34u));	/* 4631e2: mov esi, dword ptr [ecx + esi*8 + 0x1eccf34] */
	{ DWORD a_ = m->edi, b_ = 0x1eccb08u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4631e9: add edi, 0x1eccb08 */
	m->eax = m->esi;	/* 4631ef: mov eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4631f1: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4631f4: sub eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4631f6: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4631f9: sub eax, esi */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4631fb: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4631fe: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->eax*8 + 0x16c5181u);	/* 463201: lea eax, [ecx + eax*8 + 0x16c5181] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 463208: push eax */
	m->eax = m->edx;	/* 463209: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46320b: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46320e: add eax, edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 463210: push edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 463211: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 463214: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 463216: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 463219: add eax, edx */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x1eccb08u);	/* 46321b: lea edx, [ecx + eax*8 + 0x1eccb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 463222: push edx */
	{ DWORD v_ = 0x4c490cu; m->esp -= 4; M32(m->esp) = v_; }	/* 463223: push 0x4c490c */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 463228: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46322a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x463230u; native_call(m, 0x4629f0u);	/* 46322b: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463230: add esp, 0x18 */
	m->edi = M32(m->esp); m->esp += 4;	/* 463233: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 463234: pop esi */
	m->esp += 4 + 8; return;	/* 463235: ret 8 */
L_463238:
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463238: cmp eax, edx */
	if (!m->zf) goto L_4632a0;	/* 46323a: jne 0x4632a0 */
	m->edx = M32((DWORD)(m->ecx + 0x234240du));	/* 46323c: mov edx, dword ptr [ecx + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463242: cmp eax, edx */
	m->edx = m->eax;	/* 463244: mov edx, eax */
	if (!m->zf) goto L_463274;	/* 463246: jne 0x463274 */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463248: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46324b: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46324d: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463250: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463252: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463255: add edx, eax */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x1eccb08u);	/* 463257: lea eax, [ecx + edx*8 + 0x1eccb08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46325e: push eax */
	{ DWORD v_ = 0x4c48f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46325f: push 0x4c48f4 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 463264: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 463266: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46326cu; native_call(m, 0x4629f0u);	/* 463267: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46326c: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46326f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 463270: pop esi */
	m->esp += 4 + 8; return;	/* 463271: ret 8 */
L_463274:
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463274: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463277: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463279: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46327c: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46327e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463281: add edx, eax */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x1eccb08u);	/* 463283: lea eax, [ecx + edx*8 + 0x1eccb08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46328a: push eax */
	{ DWORD v_ = 0x4c48f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46328b: push 0x4c48f4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 463290: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 463292: push ecx */
	m->esp -= 4; M32(m->esp) = 0x463298u; native_call(m, 0x4629f0u);	/* 463293: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463298: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46329b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46329c: pop esi */
	m->esp += 4 + 8; return;	/* 46329d: ret 8 */
L_4632a0:
	m->esi = M32((DWORD)(m->ecx + 0x234240du));	/* 4632a0: mov esi, dword ptr [ecx + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4632a6: cmp eax, esi */
	if (m->zf) goto L_463318;	/* 4632a8: je 0x463318 */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4632aa: cmp edx, esi */
	if (m->zf) goto L_463318;	/* 4632ac: je 0x463318 */
	m->esi = m->eax;	/* 4632ae: mov esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4632b0: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4632b3: add esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4632b5: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4632b8: add esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4632ba: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4632bd: add esi, eax */
	m->edi = (DWORD)(m->ecx + m->esi*8 + 0x0u);	/* 4632bf: lea edi, [ecx + esi*8] */
	m->esi = M32((DWORD)(m->ecx + m->esi*8 + 0x1eccf34u));	/* 4632c2: mov esi, dword ptr [ecx + esi*8 + 0x1eccf34] */
	{ DWORD a_ = m->edi, b_ = 0x1eccb08u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4632c9: add edi, 0x1eccb08 */
	m->eax = m->esi;	/* 4632cf: mov eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4632d1: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4632d4: sub eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4632d6: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4632d9: sub eax, esi */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4632db: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4632de: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->eax*8 + 0x16c5181u);	/* 4632e1: lea eax, [ecx + eax*8 + 0x16c5181] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4632e8: push eax */
	m->eax = m->edx;	/* 4632e9: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4632eb: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4632ee: add eax, edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4632f0: push edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4632f1: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4632f4: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4632f6: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4632f9: add eax, edx */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x1eccb08u);	/* 4632fb: lea edx, [ecx + eax*8 + 0x1eccb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 463302: push edx */
	{ DWORD v_ = 0x4c48d4u; m->esp -= 4; M32(m->esp) = v_; }	/* 463303: push 0x4c48d4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 463308: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46330a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x463310u; native_call(m, 0x4629f0u);	/* 46330b: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463310: add esp, 0x18 */
	m->edi = M32(m->esp); m->esp += 4;	/* 463313: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 463314: pop esi */
	m->esp += 4 + 8; return;	/* 463315: ret 8 */
L_463318:
	m->esi = m->eax;	/* 463318: mov esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46331a: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46331d: add esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46331f: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 463322: add esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 463324: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 463327: add esi, eax */
	m->edi = (DWORD)(m->ecx + m->esi*8 + 0x0u);	/* 463329: lea edi, [ecx + esi*8] */
	m->esi = M32((DWORD)(m->ecx + m->esi*8 + 0x1eccf34u));	/* 46332c: mov esi, dword ptr [ecx + esi*8 + 0x1eccf34] */
	{ DWORD a_ = m->edi, b_ = 0x1eccb08u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 463333: add edi, 0x1eccb08 */
	m->eax = m->esi;	/* 463339: mov eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46333b: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46333e: sub eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 463340: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 463343: sub eax, esi */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 463345: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 463348: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->eax*8 + 0x16c5181u);	/* 46334b: lea eax, [ecx + eax*8 + 0x16c5181] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 463352: push eax */
	m->eax = m->edx;	/* 463353: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 463355: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 463358: add eax, edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46335a: push edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46335b: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46335e: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 463360: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 463363: add eax, edx */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x1eccb08u);	/* 463365: lea edx, [ecx + eax*8 + 0x1eccb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46336c: push edx */
	{ DWORD v_ = 0x4c48d4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46336d: push 0x4c48d4 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 463372: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 463374: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46337au; native_call(m, 0x4629f0u);	/* 463375: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46337a: add esp, 0x18 */
L_46337d:
	m->edi = M32(m->esp); m->esp += 4;	/* 46337d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46337e: pop esi */
	m->esp += 4 + 8; return;	/* 46337f: ret 8 */
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
