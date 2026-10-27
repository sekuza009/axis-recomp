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

static void lift_429d70(X86 *m);

/* menu_drawBackground3D (0x429d70), lifted by tools/lift.py */
static void lift_429d70(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429d70: sub esp, 0x20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 429d73: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 429d74: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 429d75: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 429d76: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429d77: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429d7c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429d81: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429d86: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x429d91u; native_call(m, M32(0x4a9228u));	/* 429d8b: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 429d91: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x429d9cu; native_call(m, M32(0x4a9224u));	/* 429d96: call dword ptr [0x4a9224] */
	m->esi = M32((DWORD)(m->esp + 0x34u));	/* 429d9c: mov esi, dword ptr [esp + 0x34] */
	m->ebp = 0x1u;	/* 429da0: mov ebp, 1 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 429da5: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 429dad: mov dword ptr [esp + 0x10], esi */
	m->eax = M32((DWORD)(m->esi + 0x3534u));	/* 429db1: mov eax, dword ptr [esi + 0x3534] */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 429db7: mov dword ptr [esp + 0x14], ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 429dbb: test eax, eax */
	if (m->zf) goto L_429dd4;	/* 429dbd: je 0x429dd4 */
L_429dbf:
	m->esi = m->eax;	/* 429dbf: mov esi, eax */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 429dc1: inc ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 429dc2: mov dword ptr [esp + 0x10], esi */
	m->eax = M32((DWORD)(m->esi + 0x3534u));	/* 429dc6: mov eax, dword ptr [esi + 0x3534] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 429dcc: test eax, eax */
	if (!m->zf) goto L_429dbf;	/* 429dce: jne 0x429dbf */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 429dd0: mov dword ptr [esp + 0x14], ebp */
L_429dd4:
	m->eax = M32((DWORD)(0x9da494u));	/* 429dd4: mov eax, dword ptr [0x9da494] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 429dd9: test eax, eax */
	if (!m->zf) goto L_429e10;	/* 429ddb: jne 0x429e10 */
	m->eax = M32((DWORD)(0x4e186cu));	/* 429ddd: mov eax, dword ptr [0x4e186c] */
	m->ecx = m->eax;	/* 429de2: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 429de4: and ecx, 0x800001ff */
	if (!m->sf) goto L_429df4;	/* 429dea: jns 0x429df4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 429dec: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 429ded: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 429df3: inc ecx */
L_429df4:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 429df4: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429df5: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429dfb: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429dfc: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 429dfe: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429e04: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 429e07: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x429e10u; native_call(m, 0x4566c0u);	/* 429e0b: call 0x4566c0 */
L_429e10:
	m->edi = M32((DWORD)(0x4a920cu));	/* 429e10: mov edi, dword ptr [0x4a920c] */
	m->ebx = M32((DWORD)(0x4a9210u));	/* 429e16: mov ebx, dword ptr [0x4a9210] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 429e1c: test ebp, ebp */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 429e1e: mov dword ptr [esp + 0x18], 0 */
	if (m->zf) goto L_42a060;	/* 429e26: je 0x42a060 */
L_429e2c:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429e2c: cmp dword ptr [esp + 0x18], 2 */
	if (m->sf == m->of) goto L_42a053;	/* 429e31: jge 0x42a053 */
	m->esp -= 4; M32(m->esp) = 0x429e3cu; native_call(m, 0x41f050u);	/* 429e37: call 0x41f050 */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 429e3c: mov eax, dword ptr [esi + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429e3f: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429e40: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429e42: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429e4au; native_call(m, M32(0x4a9214u));	/* 429e44: call dword ptr [0x4a9214] */
	m->ecx = M32((DWORD)(m->esi + 0x1930u));	/* 429e4a: mov ecx, dword ptr [esi + 0x1930] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429e50: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429e51: push 0 */
	{ DWORD v_ = 0x43340000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429e53: push 0x43340000 */
	m->esp -= 4; M32(m->esp) = 0x429e5du; native_call(m, 0x41ef20u);	/* 429e58: call 0x41ef20 */
	m->eax = M32((DWORD)(0x9da494u));	/* 429e5d: mov eax, dword ptr [0x9da494] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429e62: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 429e65: test eax, eax */
	if (!m->zf) goto L_429fd2;	/* 429e67: jne 0x429fd2 */
	FPUSH((long double)(int)M32((DWORD)(m->esi + 0x3528u)));	/* 429e6d: fild dword ptr [esi + 0x3528] */
	m->edx = M32((DWORD)(0x4b06fcu));	/* 429e73: mov edx, dword ptr [0x4b06fc] */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 429e79: push 0x3f4ccccd */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429e7e: push ecx */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 429e7f: fdivr dword ptr [0x4a93d0] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 429e85: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 429e89: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b06fcu));	/* 429e8f: fsub dword ptr [0x4b06fc] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 429e95: fstp dword ptr [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429e98: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429e99: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429ea1u; native_call(m, M32(0x4a9228u));	/* 429e9b: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429ea1: push 7 */
	m->esp -= 4; M32(m->esp) = 0x429ea9u; native_call(m, M32(0x4a921cu));	/* 429ea3: call dword ptr [0x4a921c] */
	m->ecx = M32((DWORD)(m->esi + 0x3528u));	/* 429ea9: mov ecx, dword ptr [esi + 0x3528] */
	m->eax = 0x66666667u;	/* 429eaf: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 429eb4: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 429eb6: sar edx, 1 */
	m->eax = m->edx;	/* 429eb8: mov eax, edx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 429eba: xor ebp, ebp */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429ebc: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 429ebf: add edx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 429ec1: test ecx, ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 429ec3: mov dword ptr [esp + 0x2c], edx */
	if (m->zf || m->sf != m->of) goto L_429fc8;	/* 429ec7: jle 0x429fc8 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 429ecd: mov ecx, dword ptr [esp + 0x10] */
	m->esi = (DWORD)(m->ecx + 0x14u);	/* 429ed1: lea esi, [ecx + 0x14] */
L_429ed4:
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 429ed4: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429ed8: cmp ebp, eax */
	if (m->sf == m->of) goto L_429ee2;	/* 429eda: jge 0x429ee2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebp;	/* 429edc: mov dword ptr [esp + 0x1c], ebp */
	goto L_429f1d;	/* 429ee0: jmp 0x429f1d */
L_429ee2:
	m->edx = (DWORD)(m->eax + m->eax*1 + 0x0u);	/* 429ee2: lea edx, [eax + eax] */
	{ DWORD a_ = m->ebp, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429ee5: cmp ebp, edx */
	if (m->sf == m->of) goto L_429ef3;	/* 429ee7: jge 0x429ef3 */
	m->edx = m->ebp;	/* 429ee9: mov edx, ebp */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 429eeb: sub edx, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 429eed: mov dword ptr [esp + 0x1c], edx */
	goto L_429f1d;	/* 429ef1: jmp 0x429f1d */
L_429ef3:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 429ef3: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429ef6: cmp ebp, ecx */
	if (m->sf == m->of) goto L_429f04;	/* 429ef8: jge 0x429f04 */
	m->eax = m->ebp;	/* 429efa: mov eax, ebp */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429efc: sub eax, edx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 429efe: mov dword ptr [esp + 0x1c], eax */
	goto L_429f1d;	/* 429f02: jmp 0x429f1d */
L_429f04:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429f04: shl eax, 2 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429f07: cmp ebp, eax */
	if (m->sf == m->of) goto L_429f15;	/* 429f09: jge 0x429f15 */
	m->edx = m->ebp;	/* 429f0b: mov edx, ebp */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 429f0d: sub edx, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 429f0f: mov dword ptr [esp + 0x1c], edx */
	goto L_429f1d;	/* 429f13: jmp 0x429f1d */
L_429f15:
	m->ecx = m->ebp;	/* 429f15: mov ecx, ebp */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 429f17: sub ecx, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 429f19: mov dword ptr [esp + 0x1c], ecx */
L_429f1d:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 429f1d: fild dword ptr [esp + 0x1c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429f21: push 0 */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 429f23: fst dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 429f27: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 429f2b: fstp dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 429f2f: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f33: push edx */
	m->esp -= 4; M32(m->esp) = 0x429f36u; native_call(m, m->edi);	/* 429f34: call edi */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 429f36: mov eax, dword ptr [esi + 4] */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 429f39: mov ecx, dword ptr [esi] */
	m->edx = M32((DWORD)(m->esi + 0xfffffffcu));	/* 429f3b: mov edx, dword ptr [esi - 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429f3e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f3f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f40: push edx */
	m->esp -= 4; M32(m->esp) = 0x429f43u; native_call(m, m->ebx);	/* 429f41: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 429f43: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 429f47: fadd dword ptr [0x4a9424] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429f4d: push 0 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 429f4f: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 429f53: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 429f57: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429f5b: push eax */
	m->esp -= 4; M32(m->esp) = 0x429f5eu; native_call(m, m->edi);	/* 429f5c: call edi */
	m->ecx = M32((DWORD)(m->esi + 0x14u));	/* 429f5e: mov ecx, dword ptr [esi + 0x14] */
	m->edx = M32((DWORD)(m->esi + 0x10u));	/* 429f61: mov edx, dword ptr [esi + 0x10] */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 429f64: mov eax, dword ptr [esi + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f67: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f68: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429f69: push eax */
	m->esp -= 4; M32(m->esp) = 0x429f6cu; native_call(m, m->ebx);	/* 429f6a: call ebx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 429f6c: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = 0x41a00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429f70: push 0x41a00000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f75: push ecx */
	m->esp -= 4; M32(m->esp) = 0x429f78u; native_call(m, m->edi);	/* 429f76: call edi */
	m->edx = M32((DWORD)(m->esi + 0xca4u));	/* 429f78: mov edx, dword ptr [esi + 0xca4] */
	m->eax = M32((DWORD)(m->esi + 0xca0u));	/* 429f7e: mov eax, dword ptr [esi + 0xca0] */
	m->ecx = M32((DWORD)(m->esi + 0xc9cu));	/* 429f84: mov ecx, dword ptr [esi + 0xc9c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f8a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429f8b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f8c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x429f8fu; native_call(m, m->ebx);	/* 429f8d: call ebx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 429f8f: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x41a00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429f93: push 0x41a00000 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429f98: push edx */
	m->esp -= 4; M32(m->esp) = 0x429f9bu; native_call(m, m->edi);	/* 429f99: call edi */
	m->eax = M32((DWORD)(m->esi + 0xc94u));	/* 429f9b: mov eax, dword ptr [esi + 0xc94] */
	m->ecx = M32((DWORD)(m->esi + 0xc90u));	/* 429fa1: mov ecx, dword ptr [esi + 0xc90] */
	m->edx = M32((DWORD)(m->esi + 0xc8cu));	/* 429fa7: mov edx, dword ptr [esi + 0xc8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429fad: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429fae: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429faf: push edx */
	m->esp -= 4; M32(m->esp) = 0x429fb2u; native_call(m, m->ebx);	/* 429fb0: call ebx */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 429fb2: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 429fb6: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 429fb7: add esi, 0x10 */
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->eax + 0x3528u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429fba: cmp ebp, dword ptr [eax + 0x3528] */
	if (m->sf != m->of) goto L_429ed4;	/* 429fc0: jl 0x429ed4 */
	m->esi = m->eax;	/* 429fc6: mov esi, eax */
L_429fc8:
	m->esp -= 4; M32(m->esp) = 0x429fceu; native_call(m, M32(0x4a9220u));	/* 429fc8: call dword ptr [0x4a9220] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 429fce: mov ebp, dword ptr [esp + 0x14] */
L_429fd2:
	m->eax = M32((DWORD)(0x680370u));	/* 429fd2: mov eax, dword ptr [0x680370] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429fd7: cmp eax, 1 */
	if (m->zf) goto L_429fef;	/* 429fda: je 0x429fef */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429fdc: cmp eax, 3 */
	if (m->zf) goto L_429fef;	/* 429fdf: je 0x429fef */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 429fe1: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x1934u));	/* 429fe7: fmul dword ptr [esi + 0x1934] */
	goto L_42a001;	/* 429fed: jmp 0x42a001 */
L_429fef:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 429fef: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x1934u));	/* 429ff5: fmul dword ptr [esi + 0x1934] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 429ffb: fmul dword ptr [0x4a93d0] */
L_42a001:
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x1930u));	/* 42a001: fadd dword ptr [esi + 0x1930] */
	MF((DWORD)(m->esi + 0x1930u)) = (float)ST(0); FPOP();	/* 42a007: fstp dword ptr [esi + 0x1930] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1930u)));	/* 42a00d: fld dword ptr [esi + 0x1930] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9460u)); FPOP();	/* 42a013: fcomp dword ptr [0x4a9460] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a019: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a01b: test ah, 1 */
	if (!m->zf) goto L_42a02a;	/* 42a01e: jne 0x42a02a */
	M32((DWORD)(m->esi + 0x1930u)) = 0xc3b40000u;	/* 42a020: mov dword ptr [esi + 0x1930], 0xc3b40000 */
L_42a02a:
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 42a02a: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 42a02e: mov ecx, dword ptr [esp + 0x28] */
	m->esi = M32((DWORD)(m->esi + 0x3530u));	/* 42a032: mov esi, dword ptr [esi + 0x3530] */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 42a038: dec ebp */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 42a039: inc edx */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 42a03a: inc ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a03b: test ebp, ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 42a03d: mov dword ptr [esp + 0x10], esi */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 42a041: mov dword ptr [esp + 0x14], ebp */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 42a045: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 42a049: mov dword ptr [esp + 0x28], ecx */
	if (!m->zf) goto L_429e2c;	/* 42a04d: jne 0x429e2c */
L_42a053:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x28u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a053: cmp dword ptr [esp + 0x28], 2 */
	if (!m->zf) goto L_42a060;	/* 42a058: jne 0x42a060 */
	m->esp -= 4; M32(m->esp) = 0x42a060u; native_call(m, M32(0x4a9258u));	/* 42a05a: call dword ptr [0x4a9258] */
L_42a060:
	m->esi = M32((DWORD)(m->esp + 0x34u));	/* 42a060: mov esi, dword ptr [esp + 0x34] */
	m->ebp = 0x1u;	/* 42a064: mov ebp, 1 */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 42a069: mov dword ptr [esp + 0x10], esi */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 42a06d: mov dword ptr [esp + 0x14], ebp */
	m->eax = M32((DWORD)(m->esi + 0x3534u));	/* 42a071: mov eax, dword ptr [esi + 0x3534] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a077: test eax, eax */
	if (m->zf) goto L_42a090;	/* 42a079: je 0x42a090 */
L_42a07b:
	m->esi = m->eax;	/* 42a07b: mov esi, eax */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 42a07d: inc ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 42a07e: mov dword ptr [esp + 0x10], esi */
	m->eax = M32((DWORD)(m->esi + 0x3534u));	/* 42a082: mov eax, dword ptr [esi + 0x3534] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a088: test eax, eax */
	if (!m->zf) goto L_42a07b;	/* 42a08a: jne 0x42a07b */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 42a08c: mov dword ptr [esp + 0x14], ebp */
L_42a090:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a090: test ebp, ebp */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 42a092: mov dword ptr [esp + 0x18], 0 */
	if (m->zf) goto L_42a2cf;	/* 42a09a: je 0x42a2cf */
L_42a0a0:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a0a0: cmp dword ptr [esp + 0x18], 2 */
	if (m->sf == m->of) goto L_42a2cf;	/* 42a0a5: jge 0x42a2cf */
	m->esp -= 4; M32(m->esp) = 0x42a0b0u; native_call(m, 0x41f050u);	/* 42a0ab: call 0x41f050 */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 42a0b0: mov ecx, dword ptr [esi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0b3: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0b4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0b6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a0beu; native_call(m, M32(0x4a9214u));	/* 42a0b8: call dword ptr [0x4a9214] */
	m->edx = M32((DWORD)(m->esi + 0x3264u));	/* 42a0be: mov edx, dword ptr [esi + 0x3264] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0c4: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0c5: push 0 */
	{ DWORD v_ = 0x43340000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0c7: push 0x43340000 */
	m->esp -= 4; M32(m->esp) = 0x42a0d1u; native_call(m, 0x41ef20u);	/* 42a0cc: call 0x41ef20 */
	m->eax = M32((DWORD)(0x9da494u));	/* 42a0d1: mov eax, dword ptr [0x9da494] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42a0d6: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a0d9: test eax, eax */
	if (!m->zf) goto L_42a24b;	/* 42a0db: jne 0x42a24b */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 42a0e1: mov esi, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(0x4b06fcu));	/* 42a0e5: mov eax, dword ptr [0x4b06fc] */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0ea: push 0x3f19999a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0ef: push eax */
	FPUSH((long double)(int)M32((DWORD)(m->esi + 0x3528u)));	/* 42a0f0: fild dword ptr [esi + 0x3528] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0f6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a0f7: push ecx */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 42a0f8: fdivr dword ptr [0x4a93d0] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 42a0fe: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 42a102: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b06fcu));	/* 42a108: fsub dword ptr [0x4b06fc] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42a10e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x42a117u; native_call(m, M32(0x4a9228u));	/* 42a111: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a117: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42a11fu; native_call(m, M32(0x4a921cu));	/* 42a119: call dword ptr [0x4a921c] */
	m->ecx = M32((DWORD)(m->esi + 0x3528u));	/* 42a11f: mov ecx, dword ptr [esi + 0x3528] */
	m->eax = 0x66666667u;	/* 42a125: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 42a12a: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 42a12c: sar edx, 1 */
	m->eax = m->edx;	/* 42a12e: mov eax, edx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 42a130: xor ebp, ebp */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42a132: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42a135: add edx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a137: test ecx, ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 42a139: mov dword ptr [esp + 0x2c], edx */
	if (m->zf || m->sf != m->of) goto L_42a23d;	/* 42a13d: jle 0x42a23d */
	m->ecx = m->esi;	/* 42a143: mov ecx, esi */
	m->esi = (DWORD)(m->ecx + 0x1948u);	/* 42a145: lea esi, [ecx + 0x1948] */
L_42a14b:
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 42a14b: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a14f: cmp ebp, eax */
	if (m->sf == m->of) goto L_42a159;	/* 42a151: jge 0x42a159 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebp;	/* 42a153: mov dword ptr [esp + 0x1c], ebp */
	goto L_42a194;	/* 42a157: jmp 0x42a194 */
L_42a159:
	m->edx = (DWORD)(m->eax + m->eax*1 + 0x0u);	/* 42a159: lea edx, [eax + eax] */
	{ DWORD a_ = m->ebp, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a15c: cmp ebp, edx */
	if (m->sf == m->of) goto L_42a16a;	/* 42a15e: jge 0x42a16a */
	m->edx = m->ebp;	/* 42a160: mov edx, ebp */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42a162: sub edx, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 42a164: mov dword ptr [esp + 0x1c], edx */
	goto L_42a194;	/* 42a168: jmp 0x42a194 */
L_42a16a:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 42a16a: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a16d: cmp ebp, ecx */
	if (m->sf == m->of) goto L_42a17b;	/* 42a16f: jge 0x42a17b */
	m->eax = m->ebp;	/* 42a171: mov eax, ebp */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42a173: sub eax, edx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 42a175: mov dword ptr [esp + 0x1c], eax */
	goto L_42a194;	/* 42a179: jmp 0x42a194 */
L_42a17b:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42a17b: shl eax, 2 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a17e: cmp ebp, eax */
	if (m->sf == m->of) goto L_42a18c;	/* 42a180: jge 0x42a18c */
	m->edx = m->ebp;	/* 42a182: mov edx, ebp */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42a184: sub edx, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 42a186: mov dword ptr [esp + 0x1c], edx */
	goto L_42a194;	/* 42a18a: jmp 0x42a194 */
L_42a18c:
	m->ecx = m->ebp;	/* 42a18c: mov ecx, ebp */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42a18e: sub ecx, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 42a190: mov dword ptr [esp + 0x1c], ecx */
L_42a194:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 42a194: fild dword ptr [esp + 0x1c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a198: push 0 */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 42a19a: fst dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 42a19e: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 42a1a2: fstp dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 42a1a6: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1aa: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a1adu; native_call(m, m->edi);	/* 42a1ab: call edi */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 42a1ad: mov eax, dword ptr [esi + 4] */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 42a1b0: mov ecx, dword ptr [esi] */
	m->edx = M32((DWORD)(m->esi + 0xfffffffcu));	/* 42a1b2: mov edx, dword ptr [esi - 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1b5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1b6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1b7: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a1bau; native_call(m, m->ebx);	/* 42a1b8: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 42a1ba: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 42a1be: fadd dword ptr [0x4a9424] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1c4: push 0 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 42a1c6: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 42a1ca: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 42a1ce: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1d2: push eax */
	m->esp -= 4; M32(m->esp) = 0x42a1d5u; native_call(m, m->edi);	/* 42a1d3: call edi */
	m->ecx = M32((DWORD)(m->esi + 0x14u));	/* 42a1d5: mov ecx, dword ptr [esi + 0x14] */
	m->edx = M32((DWORD)(m->esi + 0x10u));	/* 42a1d8: mov edx, dword ptr [esi + 0x10] */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 42a1db: mov eax, dword ptr [esi + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1de: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1df: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1e0: push eax */
	m->esp -= 4; M32(m->esp) = 0x42a1e3u; native_call(m, m->ebx);	/* 42a1e1: call ebx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 42a1e3: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = 0x41a00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1e7: push 0x41a00000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a1ec: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42a1efu; native_call(m, m->edi);	/* 42a1ed: call edi */
	m->edx = M32((DWORD)(m->esi + 0xca4u));	/* 42a1ef: mov edx, dword ptr [esi + 0xca4] */
	m->eax = M32((DWORD)(m->esi + 0xca0u));	/* 42a1f5: mov eax, dword ptr [esi + 0xca0] */
	m->ecx = M32((DWORD)(m->esi + 0xc9cu));	/* 42a1fb: mov ecx, dword ptr [esi + 0xc9c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a201: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a202: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a203: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42a206u; native_call(m, m->ebx);	/* 42a204: call ebx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 42a206: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x41a00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a20a: push 0x41a00000 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a20f: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a212u; native_call(m, m->edi);	/* 42a210: call edi */
	m->eax = M32((DWORD)(m->esi + 0xc94u));	/* 42a212: mov eax, dword ptr [esi + 0xc94] */
	m->ecx = M32((DWORD)(m->esi + 0xc90u));	/* 42a218: mov ecx, dword ptr [esi + 0xc90] */
	m->edx = M32((DWORD)(m->esi + 0xc8cu));	/* 42a21e: mov edx, dword ptr [esi + 0xc8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a224: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a225: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a226: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a229u; native_call(m, m->ebx);	/* 42a227: call ebx */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 42a229: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 42a22d: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42a22e: add esi, 0x10 */
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->eax + 0x3528u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a231: cmp ebp, dword ptr [eax + 0x3528] */
	if (m->sf != m->of) goto L_42a14b;	/* 42a237: jl 0x42a14b */
L_42a23d:
	m->esp -= 4; M32(m->esp) = 0x42a243u; native_call(m, M32(0x4a9220u));	/* 42a23d: call dword ptr [0x4a9220] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 42a243: mov ebp, dword ptr [esp + 0x14] */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 42a247: mov esi, dword ptr [esp + 0x10] */
L_42a24b:
	m->eax = M32((DWORD)(0x680370u));	/* 42a24b: mov eax, dword ptr [0x680370] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a250: cmp eax, 1 */
	if (m->zf) goto L_42a274;	/* 42a253: je 0x42a274 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a255: cmp eax, 3 */
	if (m->zf) goto L_42a274;	/* 42a258: je 0x42a274 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42a25a: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x3268u));	/* 42a260: fmul dword ptr [esi + 0x3268] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x3264u));	/* 42a266: fadd dword ptr [esi + 0x3264] */
	MF((DWORD)(m->esi + 0x3264u)) = (float)ST(0); FPOP();	/* 42a26c: fstp dword ptr [esi + 0x3264] */
	goto L_42a292;	/* 42a272: jmp 0x42a292 */
L_42a274:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42a274: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x1934u));	/* 42a27a: fmul dword ptr [esi + 0x1934] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 42a280: fmul dword ptr [0x4a93d0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x1930u));	/* 42a286: fadd dword ptr [esi + 0x1930] */
	MF((DWORD)(m->esi + 0x1930u)) = (float)ST(0); FPOP();	/* 42a28c: fstp dword ptr [esi + 0x1930] */
L_42a292:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3264u)));	/* 42a292: fld dword ptr [esi + 0x3264] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9460u)); FPOP();	/* 42a298: fcomp dword ptr [0x4a9460] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a29e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a2a0: test ah, 1 */
	if (!m->zf) goto L_42a2af;	/* 42a2a3: jne 0x42a2af */
	M32((DWORD)(m->esi + 0x3264u)) = 0xc3b40000u;	/* 42a2a5: mov dword ptr [esi + 0x3264], 0xc3b40000 */
L_42a2af:
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 42a2af: mov ecx, dword ptr [esp + 0x18] */
	m->esi = M32((DWORD)(m->esi + 0x3530u));	/* 42a2b3: mov esi, dword ptr [esi + 0x3530] */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 42a2b9: dec ebp */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 42a2ba: inc ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a2bb: test ebp, ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 42a2bd: mov dword ptr [esp + 0x10], esi */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 42a2c1: mov dword ptr [esp + 0x14], ebp */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 42a2c5: mov dword ptr [esp + 0x18], ecx */
	if (!m->zf) goto L_42a0a0;	/* 42a2c9: jne 0x42a0a0 */
L_42a2cf:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0700u)));	/* 42a2cf: fld dword ptr [0x4b0700] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 42a2d5: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b06fcu));	/* 42a2db: fadd dword ptr [0x4b06fc] */
	MF((DWORD)(0x4b06fcu)) = (float)ST(0);	/* 42a2e1: fst dword ptr [0x4b06fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a953cu)); FPOP();	/* 42a2e7: fcomp dword ptr [0x4a953c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a2ed: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a2ef: test ah, 1 */
	if (!m->zf) goto L_42a30a;	/* 42a2f2: jne 0x42a30a */
	M32((DWORD)(0x4b06fcu)) = 0x3f733333u;	/* 42a2f4: mov dword ptr [0x4b06fc], 0x3f733333 */
	M32((DWORD)(0x4b0700u)) = 0xbc23d70au;	/* 42a2fe: mov dword ptr [0x4b0700], 0xbc23d70a */
	goto L_42a331;	/* 42a308: jmp 0x42a331 */
L_42a30a:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b06fcu)));	/* 42a30a: fld dword ptr [0x4b06fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9468u)); FPOP();	/* 42a310: fcomp dword ptr [0x4a9468] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a316: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a318: test ah, 0x41 */
	if (m->zf) goto L_42a331;	/* 42a31b: je 0x42a331 */
	M32((DWORD)(0x4b06fcu)) = 0x3d4ccccdu;	/* 42a31d: mov dword ptr [0x4b06fc], 0x3d4ccccd */
	M32((DWORD)(0x4b0700u)) = 0x3c23d70au;	/* 42a327: mov dword ptr [0x4b0700], 0x3c23d70a */
L_42a331:
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 42a331: mov eax, dword ptr [esp + 0x34] */
	m->ecx = 0x1u;	/* 42a335: mov ecx, 1 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 42a33a: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 42a33e: mov dword ptr [esp + 0x14], ecx */
	m->eax = M32((DWORD)(m->eax + 0x3534u));	/* 42a342: mov eax, dword ptr [eax + 0x3534] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a348: test eax, eax */
	if (m->zf) goto L_42a35f;	/* 42a34a: je 0x42a35f */
L_42a34c:
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 42a34c: mov dword ptr [esp + 0x10], eax */
	m->eax = M32((DWORD)(m->eax + 0x3534u));	/* 42a350: mov eax, dword ptr [eax + 0x3534] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 42a356: inc ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a357: test eax, eax */
	if (!m->zf) goto L_42a34c;	/* 42a359: jne 0x42a34c */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 42a35b: mov dword ptr [esp + 0x14], ecx */
L_42a35f:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a35f: test ecx, ecx */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 42a361: mov dword ptr [esp + 0x18], 0 */
	if (m->zf) goto L_42a628;	/* 42a369: je 0x42a628 */
L_42a36f:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a36f: cmp dword ptr [esp + 0x18], 2 */
	if (m->sf == m->of) goto L_42a628;	/* 42a374: jge 0x42a628 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 42a37a: xor ebp, ebp */
L_42a37c:
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 42a37c: mov esi, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esi + 0x3520u));	/* 42a380: mov ecx, dword ptr [esi + 0x3520] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a386: push ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a387: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a38c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a391: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a39cu; native_call(m, M32(0x4a9228u));	/* 42a396: call dword ptr [0x4a9228] */
	m->esp -= 4; M32(m->esp) = 0x42a3a1u; native_call(m, 0x41f050u);	/* 42a39c: call 0x41f050 */
	m->eax = M32((DWORD)(0x9da494u));	/* 42a3a1: mov eax, dword ptr [0x9da494] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a3a6: test eax, eax */
	if (!m->zf) goto L_42a3e8;	/* 42a3a8: jne 0x42a3e8 */
	m->edx = (DWORD)(m->ebp*4 + 0x0u);	/* 42a3aa: lea edx, [ebp*4] */
	m->eax = 0x9da470u;	/* 42a3b1: mov eax, 0x9da470 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42a3b6: sub eax, edx */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 42a3b8: mov eax, dword ptr [eax] */
	m->ecx = m->eax;	/* 42a3ba: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42a3bc: and ecx, 0x800001ff */
	if (!m->sf) goto L_42a3cc;	/* 42a3c2: jns 0x42a3cc */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42a3c4: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42a3c5: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 42a3cb: inc ecx */
L_42a3cc:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 42a3cc: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42a3cd: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a3d3: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42a3d4: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 42a3d6: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42a3dc: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 42a3df: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x42a3e8u; native_call(m, 0x4566c0u);	/* 42a3e3: call 0x4566c0 */
L_42a3e8:
	{ DWORD a_ = m->ebp, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a3e8: cmp ebp, 2 */
	if (!m->zf) goto L_42a455;	/* 42a3eb: jne 0x42a455 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0708u)));	/* 42a3ed: fld dword ptr [0x4b0708] */
	ST(0) = -ST(0);	/* 42a3f3: fchs  */
	MF((DWORD)(m->esi + 0x33c0u)) = (float)ST(0); FPOP();	/* 42a3f5: fstp dword ptr [esi + 0x33c0] */
	m->eax = M32((DWORD)(0x4b0708u));	/* 42a3fb: mov eax, dword ptr [0x4b0708] */
	M32((DWORD)(m->esi + 0x33c4u)) = m->eax;	/* 42a400: mov dword ptr [esi + 0x33c4], eax */
	m->ecx = M32((DWORD)(0x4b0708u));	/* 42a406: mov ecx, dword ptr [0x4b0708] */
	M32((DWORD)(m->esi + 0x33d0u)) = m->ecx;	/* 42a40c: mov dword ptr [esi + 0x33d0], ecx */
	m->edx = M32((DWORD)(0x4b0708u));	/* 42a412: mov edx, dword ptr [0x4b0708] */
	M32((DWORD)(m->esi + 0x33d4u)) = m->edx;	/* 42a418: mov dword ptr [esi + 0x33d4], edx */
	m->eax = M32((DWORD)(0x4b0708u));	/* 42a41e: mov eax, dword ptr [0x4b0708] */
	M32((DWORD)(m->esi + 0x33e0u)) = m->eax;	/* 42a423: mov dword ptr [esi + 0x33e0], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0708u)));	/* 42a429: fld dword ptr [0x4b0708] */
	ST(0) = -ST(0);	/* 42a42f: fchs  */
	MF((DWORD)(m->esi + 0x33e4u)) = (float)ST(0); FPOP();	/* 42a431: fstp dword ptr [esi + 0x33e4] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0708u)));	/* 42a437: fld dword ptr [0x4b0708] */
	ST(0) = -ST(0);	/* 42a43d: fchs  */
	MF((DWORD)(m->esi + 0x33f0u)) = (float)ST(0); FPOP();	/* 42a43f: fstp dword ptr [esi + 0x33f0] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0708u)));	/* 42a445: fld dword ptr [0x4b0708] */
	ST(0) = -ST(0);	/* 42a44b: fchs  */
	MF((DWORD)(m->esi + 0x33f4u)) = (float)ST(0); FPOP();	/* 42a44d: fstp dword ptr [esi + 0x33f4] */
	goto L_42a4c1;	/* 42a453: jmp 0x42a4c1 */
L_42a455:
	{ DWORD a_ = m->ebp, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a455: cmp ebp, 3 */
	if (!m->zf) goto L_42a4c1;	/* 42a458: jne 0x42a4c1 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0704u)));	/* 42a45a: fld dword ptr [0x4b0704] */
	ST(0) = -ST(0);	/* 42a460: fchs  */
	MF((DWORD)(m->esi + 0x3418u)) = (float)ST(0); FPOP();	/* 42a462: fstp dword ptr [esi + 0x3418] */
	m->ecx = M32((DWORD)(0x4b0704u));	/* 42a468: mov ecx, dword ptr [0x4b0704] */
	M32((DWORD)(m->esi + 0x341cu)) = m->ecx;	/* 42a46e: mov dword ptr [esi + 0x341c], ecx */
	m->edx = M32((DWORD)(0x4b0704u));	/* 42a474: mov edx, dword ptr [0x4b0704] */
	M32((DWORD)(m->esi + 0x3428u)) = m->edx;	/* 42a47a: mov dword ptr [esi + 0x3428], edx */
	m->eax = M32((DWORD)(0x4b0704u));	/* 42a480: mov eax, dword ptr [0x4b0704] */
	M32((DWORD)(m->esi + 0x342cu)) = m->eax;	/* 42a485: mov dword ptr [esi + 0x342c], eax */
	m->ecx = M32((DWORD)(0x4b0704u));	/* 42a48b: mov ecx, dword ptr [0x4b0704] */
	M32((DWORD)(m->esi + 0x3438u)) = m->ecx;	/* 42a491: mov dword ptr [esi + 0x3438], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0704u)));	/* 42a497: fld dword ptr [0x4b0704] */
	ST(0) = -ST(0);	/* 42a49d: fchs  */
	MF((DWORD)(m->esi + 0x343cu)) = (float)ST(0); FPOP();	/* 42a49f: fstp dword ptr [esi + 0x343c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0704u)));	/* 42a4a5: fld dword ptr [0x4b0704] */
	ST(0) = -ST(0);	/* 42a4ab: fchs  */
	MF((DWORD)(m->esi + 0x3448u)) = (float)ST(0); FPOP();	/* 42a4ad: fstp dword ptr [esi + 0x3448] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0704u)));	/* 42a4b3: fld dword ptr [0x4b0704] */
	ST(0) = -ST(0);	/* 42a4b9: fchs  */
	MF((DWORD)(m->esi + 0x344cu)) = (float)ST(0); FPOP();	/* 42a4bb: fstp dword ptr [esi + 0x344c] */
L_42a4c1:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 42a4c1: mov ecx, dword ptr [esp + 0x10] */
	m->edx = (DWORD)(m->ebp + m->ebp*4 + 0x0u);	/* 42a4c5: lea edx, [ebp + ebp*4] */
	m->eax = (DWORD)(m->ebp + m->edx*2 + 0x0u);	/* 42a4c9: lea eax, [ebp + edx*2] */
	m->edx = M32((DWORD)(m->ecx + m->eax*8 + 0x3358u));	/* 42a4cd: mov edx, dword ptr [ecx + eax*8 + 0x3358] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a4d4: push edx */
	m->esi = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 42a4d5: lea esi, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->ecx + m->eax*8 + 0x3354u));	/* 42a4d8: mov eax, dword ptr [ecx + eax*8 + 0x3354] */
	m->ecx = M32((DWORD)(m->esi + 0x3350u));	/* 42a4df: mov ecx, dword ptr [esi + 0x3350] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a4e5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a4e6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42a4edu; native_call(m, M32(0x4a9214u));	/* 42a4e7: call dword ptr [0x4a9214] */
	m->edx = M32((DWORD)(m->esi + 0x3360u));	/* 42a4ed: mov edx, dword ptr [esi + 0x3360] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a4f3: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a4f4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a4f6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a4fdu; native_call(m, 0x41ef20u);	/* 42a4f8: call 0x41ef20 */
	m->eax = M32((DWORD)(0x9da494u));	/* 42a4fd: mov eax, dword ptr [0x9da494] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42a502: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a505: test eax, eax */
	if (!m->zf) goto L_42a5aa;	/* 42a507: jne 0x42a5aa */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a50d: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42a515u; native_call(m, M32(0x4a921cu));	/* 42a50f: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a515: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a51a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a51eu; native_call(m, m->edi);	/* 42a51c: call edi */
	m->eax = M32((DWORD)(m->esi + 0x3318u));	/* 42a51e: mov eax, dword ptr [esi + 0x3318] */
	m->ecx = M32((DWORD)(m->esi + 0x3314u));	/* 42a524: mov ecx, dword ptr [esi + 0x3314] */
	m->edx = M32((DWORD)(m->esi + 0x3310u));	/* 42a52a: mov edx, dword ptr [esi + 0x3310] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a530: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a531: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a532: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a535u; native_call(m, m->ebx);	/* 42a533: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a535: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a53a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a541u; native_call(m, m->edi);	/* 42a53f: call edi */
	m->eax = M32((DWORD)(m->esi + 0x3328u));	/* 42a541: mov eax, dword ptr [esi + 0x3328] */
	m->ecx = M32((DWORD)(m->esi + 0x3324u));	/* 42a547: mov ecx, dword ptr [esi + 0x3324] */
	m->edx = M32((DWORD)(m->esi + 0x3320u));	/* 42a54d: mov edx, dword ptr [esi + 0x3320] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a553: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a554: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a555: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a558u; native_call(m, m->ebx);	/* 42a556: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a558: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a55a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a561u; native_call(m, m->edi);	/* 42a55f: call edi */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 42a561: mov edx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebp + m->ebp*4 + 0x2e9u);	/* 42a565: lea eax, [ebp + ebp*4 + 0x2e9] */
	m->ecx = (DWORD)(m->ebp + m->eax*2 + 0x95u);	/* 42a56c: lea ecx, [ebp + eax*2 + 0x95] */
	m->eax = M32((DWORD)(m->edx + m->ecx*8 + 0x0u));	/* 42a573: mov eax, dword ptr [edx + ecx*8] */
	m->ecx = M32((DWORD)(m->esi + 0x3334u));	/* 42a576: mov ecx, dword ptr [esi + 0x3334] */
	m->edx = M32((DWORD)(m->esi + 0x3330u));	/* 42a57c: mov edx, dword ptr [esi + 0x3330] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a582: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a583: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a584: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a587u; native_call(m, m->ebx);	/* 42a585: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a587: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a589: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a58du; native_call(m, m->edi);	/* 42a58b: call edi */
	m->eax = M32((DWORD)(m->esi + 0x3348u));	/* 42a58d: mov eax, dword ptr [esi + 0x3348] */
	m->ecx = M32((DWORD)(m->esi + 0x3344u));	/* 42a593: mov ecx, dword ptr [esi + 0x3344] */
	m->edx = M32((DWORD)(m->esi + 0x3340u));	/* 42a599: mov edx, dword ptr [esi + 0x3340] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a59f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a5a0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a5a1: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a5a4u; native_call(m, m->ebx);	/* 42a5a2: call ebx */
	m->esp -= 4; M32(m->esp) = 0x42a5aau; native_call(m, M32(0x4a9220u));	/* 42a5a4: call dword ptr [0x4a9220] */
L_42a5aa:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42a5aa: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x3364u));	/* 42a5b0: fmul dword ptr [esi + 0x3364] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x3360u));	/* 42a5b6: fadd dword ptr [esi + 0x3360] */
	MF((DWORD)(m->esi + 0x3360u)) = (float)ST(0);	/* 42a5bc: fst dword ptr [esi + 0x3360] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9460u)); FPOP();	/* 42a5c2: fcomp dword ptr [0x4a9460] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a5c8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a5ca: test ah, 0x41 */
	if (!m->zf) goto L_42a5d9;	/* 42a5cd: jne 0x42a5d9 */
	M32((DWORD)(m->esi + 0x3360u)) = 0xc3b40000u;	/* 42a5cf: mov dword ptr [esi + 0x3360], 0xc3b40000 */
L_42a5d9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3360u)));	/* 42a5d9: fld dword ptr [esi + 0x3360] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94b0u)); FPOP();	/* 42a5df: fcomp dword ptr [0x4a94b0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a5e5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a5e7: test ah, 1 */
	if (m->zf) goto L_42a5f6;	/* 42a5ea: je 0x42a5f6 */
	M32((DWORD)(m->esi + 0x3360u)) = 0x43b40000u;	/* 42a5ec: mov dword ptr [esi + 0x3360], 0x43b40000 */
L_42a5f6:
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 42a5f6: inc ebp */
	{ DWORD a_ = m->ebp, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a5f7: cmp ebp, 6 */
	if (m->sf != m->of) goto L_42a37c;	/* 42a5fa: jl 0x42a37c */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 42a600: mov eax, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 42a604: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->eax + 0x3530u));	/* 42a608: mov ecx, dword ptr [eax + 0x3530] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42a60e: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42a612: dec eax */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 42a613: inc edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a614: test eax, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 42a616: mov dword ptr [esp + 0x10], ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 42a61a: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 42a61e: mov dword ptr [esp + 0x18], edx */
	if (!m->zf) goto L_42a36f;	/* 42a622: jne 0x42a36f */
L_42a628:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b070cu)));	/* 42a628: fld dword ptr [0x4b070c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b0704u));	/* 42a62e: fadd dword ptr [0x4b0704] */
	MF((DWORD)(0x4b0704u)) = (float)ST(0);	/* 42a634: fst dword ptr [0x4b0704] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9514u)); FPOP();	/* 42a63a: fcomp dword ptr [0x4a9514] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a640: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a642: test ah, 1 */
	if (!m->zf) goto L_42a659;	/* 42a645: jne 0x42a659 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42a647: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9538u));	/* 42a64d: fmul dword ptr [0x4a9538] */
	MF((DWORD)(0x4b070cu)) = (float)ST(0); FPOP();	/* 42a653: fstp dword ptr [0x4b070c] */
L_42a659:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0704u)));	/* 42a659: fld dword ptr [0x4b0704] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 42a65f: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a665: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a667: test ah, 0x41 */
	if (m->zf) goto L_42a67e;	/* 42a66a: je 0x42a67e */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42a66c: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 42a672: fmul dword ptr [0x4a94f8] */
	MF((DWORD)(0x4b070cu)) = (float)ST(0); FPOP();	/* 42a678: fstp dword ptr [0x4b070c] */
L_42a67e:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0710u)));	/* 42a67e: fld dword ptr [0x4b0710] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b0708u));	/* 42a684: fadd dword ptr [0x4b0708] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9514u));	/* 42a68a: fcom dword ptr [0x4a9514] */
	MF((DWORD)(0x4b0708u)) = (float)ST(0);	/* 42a690: fst dword ptr [0x4b0708] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a696: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a698: test ah, 1 */
	if (!m->zf) goto L_42a6af;	/* 42a69b: jne 0x42a6af */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42a69d: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9538u));	/* 42a6a3: fmul dword ptr [0x4a9538] */
	MF((DWORD)(0x4b0710u)) = (float)ST(0); FPOP();	/* 42a6a9: fstp dword ptr [0x4b0710] */
L_42a6af:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 42a6af: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a6b5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a6b7: test ah, 0x41 */
	if (m->zf) goto L_42a6ce;	/* 42a6ba: je 0x42a6ce */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42a6bc: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 42a6c2: fmul dword ptr [0x4a94f8] */
	MF((DWORD)(0x4b0710u)) = (float)ST(0); FPOP();	/* 42a6c8: fstp dword ptr [0x4b0710] */
L_42a6ce:
	m->esi = M32((DWORD)(m->esp + 0x34u));	/* 42a6ce: mov esi, dword ptr [esp + 0x34] */
	m->ebp = 0x1u;	/* 42a6d2: mov ebp, 1 */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 42a6d7: mov dword ptr [esp + 0x14], ebp */
	m->eax = M32((DWORD)(m->esi + 0x3534u));	/* 42a6db: mov eax, dword ptr [esi + 0x3534] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a6e1: test eax, eax */
	if (m->zf) goto L_42a6f6;	/* 42a6e3: je 0x42a6f6 */
L_42a6e5:
	m->esi = m->eax;	/* 42a6e5: mov esi, eax */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 42a6e7: inc ebp */
	m->eax = M32((DWORD)(m->esi + 0x3534u));	/* 42a6e8: mov eax, dword ptr [esi + 0x3534] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a6ee: test eax, eax */
	if (!m->zf) goto L_42a6e5;	/* 42a6f0: jne 0x42a6e5 */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 42a6f2: mov dword ptr [esp + 0x14], ebp */
L_42a6f6:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a6f6: test ebp, ebp */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 42a6f8: mov dword ptr [esp + 0x18], 0 */
	if (m->zf) goto L_42aa1b;	/* 42a700: je 0x42aa1b */
L_42a706:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42a706: cmp dword ptr [esp + 0x18], 2 */
	if (m->sf == m->of) goto L_42aa1b;	/* 42a70b: jge 0x42aa1b */
	m->esp -= 4; M32(m->esp) = 0x42a716u; native_call(m, 0x41f050u);	/* 42a711: call 0x41f050 */
	m->edx = M32((DWORD)(m->esi + 0x3300u));	/* 42a716: mov edx, dword ptr [esi + 0x3300] */
	m->eax = M32((DWORD)(m->esi + 0x32fcu));	/* 42a71c: mov eax, dword ptr [esi + 0x32fc] */
	m->ecx = M32((DWORD)(m->esi + 0x32f8u));	/* 42a722: mov ecx, dword ptr [esi + 0x32f8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a728: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a729: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a72a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42a731u; native_call(m, M32(0x4a9214u));	/* 42a72b: call dword ptr [0x4a9214] */
	m->edx = M32((DWORD)(m->esi + 0x3308u));	/* 42a731: mov edx, dword ptr [esi + 0x3308] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a737: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a738: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a73a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a741u; native_call(m, 0x41ef20u);	/* 42a73c: call 0x41ef20 */
	m->eax = M32((DWORD)(0x9da494u));	/* 42a741: mov eax, dword ptr [0x9da494] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42a746: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42a749: test eax, eax */
	if (!m->zf) goto L_42a9d0;	/* 42a74b: jne 0x42a9d0 */
	m->eax = M32((DWORD)(0x76d36cu));	/* 42a751: mov eax, dword ptr [0x76d36c] */
	m->ecx = m->eax;	/* 42a756: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42a758: and ecx, 0x800001ff */
	if (!m->sf) goto L_42a768;	/* 42a75e: jns 0x42a768 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42a760: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42a761: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 42a767: inc ecx */
L_42a768:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 42a768: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42a769: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a76f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42a770: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 42a772: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42a778: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 42a77b: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x42a784u; native_call(m, 0x4566c0u);	/* 42a77f: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a784: push 0x3f800000 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 42a789: push 0x3e99999a */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 42a78e: push 0x3e99999a */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 42a793: push 0x3e99999a */
	m->esp -= 4; M32(m->esp) = 0x42a79eu; native_call(m, M32(0x4a9228u));	/* 42a798: call dword ptr [0x4a9228] */
	m->ebp = M32((DWORD)(0x4a921cu));	/* 42a79e: mov ebp, dword ptr [0x4a921c] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7a4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42a7a8u; native_call(m, m->ebp);	/* 42a7a6: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7a8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7ad: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a7b1u; native_call(m, m->edi);	/* 42a7af: call edi */
	m->eax = M32((DWORD)(m->esi + 0x3280u));	/* 42a7b1: mov eax, dword ptr [esi + 0x3280] */
	m->ecx = M32((DWORD)(m->esi + 0x327cu));	/* 42a7b7: mov ecx, dword ptr [esi + 0x327c] */
	m->edx = M32((DWORD)(m->esi + 0x3278u));	/* 42a7bd: mov edx, dword ptr [esi + 0x3278] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7c3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7c4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7c5: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a7c8u; native_call(m, m->ebx);	/* 42a7c6: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7c8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7cd: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a7d4u; native_call(m, m->edi);	/* 42a7d2: call edi */
	m->eax = M32((DWORD)(m->esi + 0x3290u));	/* 42a7d4: mov eax, dword ptr [esi + 0x3290] */
	m->ecx = M32((DWORD)(m->esi + 0x328cu));	/* 42a7da: mov ecx, dword ptr [esi + 0x328c] */
	m->edx = M32((DWORD)(m->esi + 0x3288u));	/* 42a7e0: mov edx, dword ptr [esi + 0x3288] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7e6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7e7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7e8: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a7ebu; native_call(m, m->ebx);	/* 42a7e9: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7eb: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a7ed: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a7f4u; native_call(m, m->edi);	/* 42a7f2: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32d0u));	/* 42a7f4: mov eax, dword ptr [esi + 0x32d0] */
	m->ecx = M32((DWORD)(m->esi + 0x32ccu));	/* 42a7fa: mov ecx, dword ptr [esi + 0x32cc] */
	m->edx = M32((DWORD)(m->esi + 0x32c8u));	/* 42a800: mov edx, dword ptr [esi + 0x32c8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a806: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a807: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a808: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a80bu; native_call(m, m->ebx);	/* 42a809: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a80b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a80d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a811u; native_call(m, m->edi);	/* 42a80f: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32c0u));	/* 42a811: mov eax, dword ptr [esi + 0x32c0] */
	m->ecx = M32((DWORD)(m->esi + 0x32bcu));	/* 42a817: mov ecx, dword ptr [esi + 0x32bc] */
	m->edx = M32((DWORD)(m->esi + 0x32b8u));	/* 42a81d: mov edx, dword ptr [esi + 0x32b8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a823: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a824: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a825: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a828u; native_call(m, m->ebx);	/* 42a826: call ebx */
	m->esp -= 4; M32(m->esp) = 0x42a82eu; native_call(m, M32(0x4a9220u));	/* 42a828: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a82e: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42a832u; native_call(m, m->ebp);	/* 42a830: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a832: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a837: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a83bu; native_call(m, m->edi);	/* 42a839: call edi */
	m->eax = M32((DWORD)(m->esi + 0x3290u));	/* 42a83b: mov eax, dword ptr [esi + 0x3290] */
	m->ecx = M32((DWORD)(m->esi + 0x328cu));	/* 42a841: mov ecx, dword ptr [esi + 0x328c] */
	m->edx = M32((DWORD)(m->esi + 0x3288u));	/* 42a847: mov edx, dword ptr [esi + 0x3288] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a84d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a84e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a84f: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a852u; native_call(m, m->ebx);	/* 42a850: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a852: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a857: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a85eu; native_call(m, m->edi);	/* 42a85c: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32a0u));	/* 42a85e: mov eax, dword ptr [esi + 0x32a0] */
	m->ecx = M32((DWORD)(m->esi + 0x329cu));	/* 42a864: mov ecx, dword ptr [esi + 0x329c] */
	m->edx = M32((DWORD)(m->esi + 0x3298u));	/* 42a86a: mov edx, dword ptr [esi + 0x3298] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a870: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a871: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a872: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a875u; native_call(m, m->ebx);	/* 42a873: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a875: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a877: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a87eu; native_call(m, m->edi);	/* 42a87c: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32e0u));	/* 42a87e: mov eax, dword ptr [esi + 0x32e0] */
	m->ecx = M32((DWORD)(m->esi + 0x32dcu));	/* 42a884: mov ecx, dword ptr [esi + 0x32dc] */
	m->edx = M32((DWORD)(m->esi + 0x32d8u));	/* 42a88a: mov edx, dword ptr [esi + 0x32d8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a890: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a891: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a892: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a895u; native_call(m, m->ebx);	/* 42a893: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a895: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a897: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a89bu; native_call(m, m->edi);	/* 42a899: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32d0u));	/* 42a89b: mov eax, dword ptr [esi + 0x32d0] */
	m->ecx = M32((DWORD)(m->esi + 0x32ccu));	/* 42a8a1: mov ecx, dword ptr [esi + 0x32cc] */
	m->edx = M32((DWORD)(m->esi + 0x32c8u));	/* 42a8a7: mov edx, dword ptr [esi + 0x32c8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8ad: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8ae: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8af: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a8b2u; native_call(m, m->ebx);	/* 42a8b0: call ebx */
	m->esp -= 4; M32(m->esp) = 0x42a8b8u; native_call(m, M32(0x4a9220u));	/* 42a8b2: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8b8: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42a8bcu; native_call(m, m->ebp);	/* 42a8ba: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8bc: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8c1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a8c5u; native_call(m, m->edi);	/* 42a8c3: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32a0u));	/* 42a8c5: mov eax, dword ptr [esi + 0x32a0] */
	m->ecx = M32((DWORD)(m->esi + 0x329cu));	/* 42a8cb: mov ecx, dword ptr [esi + 0x329c] */
	m->edx = M32((DWORD)(m->esi + 0x3298u));	/* 42a8d1: mov edx, dword ptr [esi + 0x3298] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8d7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8d8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8d9: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a8dcu; native_call(m, m->ebx);	/* 42a8da: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8dc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8e1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a8e8u; native_call(m, m->edi);	/* 42a8e6: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32b0u));	/* 42a8e8: mov eax, dword ptr [esi + 0x32b0] */
	m->ecx = M32((DWORD)(m->esi + 0x32acu));	/* 42a8ee: mov ecx, dword ptr [esi + 0x32ac] */
	m->edx = M32((DWORD)(m->esi + 0x32a8u));	/* 42a8f4: mov edx, dword ptr [esi + 0x32a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8fa: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8fb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8fc: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a8ffu; native_call(m, m->ebx);	/* 42a8fd: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a8ff: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a901: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a908u; native_call(m, m->edi);	/* 42a906: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32f0u));	/* 42a908: mov eax, dword ptr [esi + 0x32f0] */
	m->ecx = M32((DWORD)(m->esi + 0x32ecu));	/* 42a90e: mov ecx, dword ptr [esi + 0x32ec] */
	m->edx = M32((DWORD)(m->esi + 0x32e8u));	/* 42a914: mov edx, dword ptr [esi + 0x32e8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a91a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a91b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a91c: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a91fu; native_call(m, m->ebx);	/* 42a91d: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a91f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a921: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a925u; native_call(m, m->edi);	/* 42a923: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32e0u));	/* 42a925: mov eax, dword ptr [esi + 0x32e0] */
	m->ecx = M32((DWORD)(m->esi + 0x32dcu));	/* 42a92b: mov ecx, dword ptr [esi + 0x32dc] */
	m->edx = M32((DWORD)(m->esi + 0x32d8u));	/* 42a931: mov edx, dword ptr [esi + 0x32d8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a937: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a938: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a939: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a93cu; native_call(m, m->ebx);	/* 42a93a: call ebx */
	m->esp -= 4; M32(m->esp) = 0x42a942u; native_call(m, M32(0x4a9220u));	/* 42a93c: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a942: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42a946u; native_call(m, m->ebp);	/* 42a944: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a946: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a94b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a94fu; native_call(m, m->edi);	/* 42a94d: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32b0u));	/* 42a94f: mov eax, dword ptr [esi + 0x32b0] */
	m->ecx = M32((DWORD)(m->esi + 0x32acu));	/* 42a955: mov ecx, dword ptr [esi + 0x32ac] */
	m->edx = M32((DWORD)(m->esi + 0x32a8u));	/* 42a95b: mov edx, dword ptr [esi + 0x32a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a961: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a962: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a963: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a966u; native_call(m, m->ebx);	/* 42a964: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a966: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a96b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a972u; native_call(m, m->edi);	/* 42a970: call edi */
	m->eax = M32((DWORD)(m->esi + 0x3280u));	/* 42a972: mov eax, dword ptr [esi + 0x3280] */
	m->ecx = M32((DWORD)(m->esi + 0x327cu));	/* 42a978: mov ecx, dword ptr [esi + 0x327c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a97e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a97f: push ecx */
	m->edx = M32((DWORD)(m->esi + 0x3278u));	/* 42a980: mov edx, dword ptr [esi + 0x3278] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a986: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a989u; native_call(m, m->ebx);	/* 42a987: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a989: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a98b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42a992u; native_call(m, m->edi);	/* 42a990: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32c0u));	/* 42a992: mov eax, dword ptr [esi + 0x32c0] */
	m->ecx = M32((DWORD)(m->esi + 0x32bcu));	/* 42a998: mov ecx, dword ptr [esi + 0x32bc] */
	m->edx = M32((DWORD)(m->esi + 0x32b8u));	/* 42a99e: mov edx, dword ptr [esi + 0x32b8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a9a4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a9a5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a9a6: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a9a9u; native_call(m, m->ebx);	/* 42a9a7: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a9a9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42a9ab: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42a9afu; native_call(m, m->edi);	/* 42a9ad: call edi */
	m->eax = M32((DWORD)(m->esi + 0x32f0u));	/* 42a9af: mov eax, dword ptr [esi + 0x32f0] */
	m->ecx = M32((DWORD)(m->esi + 0x32ecu));	/* 42a9b5: mov ecx, dword ptr [esi + 0x32ec] */
	m->edx = M32((DWORD)(m->esi + 0x32e8u));	/* 42a9bb: mov edx, dword ptr [esi + 0x32e8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42a9c1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a9c2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42a9c3: push edx */
	m->esp -= 4; M32(m->esp) = 0x42a9c6u; native_call(m, m->ebx);	/* 42a9c4: call ebx */
	m->esp -= 4; M32(m->esp) = 0x42a9ccu; native_call(m, M32(0x4a9220u));	/* 42a9c6: call dword ptr [0x4a9220] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 42a9cc: mov ebp, dword ptr [esp + 0x14] */
L_42a9d0:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 42a9d0: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x330cu));	/* 42a9d6: fmul dword ptr [esi + 0x330c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x3308u));	/* 42a9dc: fadd dword ptr [esi + 0x3308] */
	MF((DWORD)(m->esi + 0x3308u)) = (float)ST(0);	/* 42a9e2: fst dword ptr [esi + 0x3308] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9460u)); FPOP();	/* 42a9e8: fcomp dword ptr [0x4a9460] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42a9ee: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42a9f0: test ah, 1 */
	if (!m->zf) goto L_42a9ff;	/* 42a9f3: jne 0x42a9ff */
	M32((DWORD)(m->esi + 0x3308u)) = 0xc3b40000u;	/* 42a9f5: mov dword ptr [esi + 0x3308], 0xc3b40000 */
L_42a9ff:
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 42a9ff: mov ecx, dword ptr [esp + 0x18] */
	m->esi = M32((DWORD)(m->esi + 0x3530u));	/* 42aa03: mov esi, dword ptr [esi + 0x3530] */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 42aa09: dec ebp */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 42aa0a: inc ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42aa0b: test ebp, ebp */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 42aa0d: mov dword ptr [esp + 0x14], ebp */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 42aa11: mov dword ptr [esp + 0x18], ecx */
	if (!m->zf) goto L_42a706;	/* 42aa15: jne 0x42a706 */
L_42aa1b:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42aa1b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x42aa26u; native_call(m, M32(0x4a922cu));	/* 42aa20: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 42aa26: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42aa27: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42aa28: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42aa29: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42aa2a: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 42aa2d: ret  */
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
