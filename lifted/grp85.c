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

static void lift_419160(X86 *m);

/* armc_419160 (0x419160), lifted by tools/lift.py */
static void lift_419160(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419160: push ebp */
	m->ebp = m->esp;	/* 419161: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 419163: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419166: sub esp, 0x50 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 419169: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 41916e: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419174: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419175: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 419176: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 419177: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419178: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419179: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41917fu; native_call(m, 0x40e490u);	/* 41917a: call 0x40e490 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41917f: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 419182: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 419184: mov dword ptr [esp + 0x14], eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 419188: xor esi, esi */
	m->edi = 0x7517a4u;	/* 41918a: mov edi, 0x7517a4 */
L_41918f:
	m->ebp = M32((DWORD)(0x4a9224u));	/* 41918f: mov ebp, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 419195: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41919cu; native_call(m, m->ebp);	/* 41919a: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 41919c: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 4191a1: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4191a3: and edx, 0x800001ff */
	if (!m->sf) goto L_4191b3;	/* 4191a9: jns 0x4191b3 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4191ab: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4191ac: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4191b2: inc edx */
L_4191b3:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4191b3: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4191b4: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4191ba: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4191bb: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4191c1: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4191c3: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4191c6: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4191cfu; native_call(m, 0x4566c0u);	/* 4191ca: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4191cf: mov eax, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->ebx + 0x3u);	/* 4191d3: lea edx, [ebx + 3] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4191d6: cmp eax, edx */
	if (!m->zf) goto L_419231;	/* 4191d8: jne 0x419231 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4191da: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4191df: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4191e4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4191e9: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4191f4u; native_call(m, M32(0x4a9228u));	/* 4191ee: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 4191f4: mov eax, dword ptr [0x4dcc90] */
	m->ecx = M32((DWORD)(0x4dcc9cu));	/* 4191f9: mov ecx, dword ptr [0x4dcc9c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4191ff: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419201: push ecx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x70u);	/* 419202: lea edx, [esi + eax + 0x70] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 419206: add ecx, -0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419209: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x10u);	/* 41920a: lea eax, [esi + eax + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41920e: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41920f: push eax */
	m->esp -= 4; M32(m->esp) = 0x419215u; native_call(m, 0x4282f0u);	/* 419210: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dbc64u));	/* 419215: mov ecx, dword ptr [0x4dbc64] */
	m->edx = M32((DWORD)(0x4dbc60u));	/* 41921b: mov edx, dword ptr [0x4dbc60] */
	m->eax = M32((DWORD)(0x4dbc5cu));	/* 419221: mov eax, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419226: push ecx */
	m->ecx = M32((DWORD)(0x4dbc58u));	/* 419227: mov ecx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41922d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41922e: push eax */
	goto L_419286;	/* 41922f: jmp 0x419286 */
L_419231:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 419231: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419236: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41923b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419240: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41924bu; native_call(m, M32(0x4a9228u));	/* 419245: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 41924b: mov eax, dword ptr [0x4dcc90] */
	m->ecx = M32((DWORD)(0x4dcc9cu));	/* 419250: mov ecx, dword ptr [0x4dcc9c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 419256: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419258: push ecx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x70u);	/* 419259: lea edx, [esi + eax + 0x70] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41925d: add ecx, -0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419260: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x10u);	/* 419261: lea eax, [esi + eax + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419265: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419266: push eax */
	m->esp -= 4; M32(m->esp) = 0x41926cu; native_call(m, 0x4282f0u);	/* 419267: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dc1dcu));	/* 41926c: mov ecx, dword ptr [0x4dc1dc] */
	m->edx = M32((DWORD)(0x4dc1d8u));	/* 419272: mov edx, dword ptr [0x4dc1d8] */
	m->eax = M32((DWORD)(0x4dc1d4u));	/* 419278: mov eax, dword ptr [0x4dc1d4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41927d: push ecx */
	m->ecx = M32((DWORD)(0x4dc1d0u));	/* 41927e: mov ecx, dword ptr [0x4dc1d0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419284: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419285: push eax */
L_419286:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419286: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419287: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419291u; native_call(m, 0x41f0e0u);	/* 41928c: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 419291: mov eax, dword ptr [0x4dcc90] */
	m->ecx = M32((DWORD)(0x4dcc9cu));	/* 419296: mov ecx, dword ptr [0x4dcc9c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41929c: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41929f: add ecx, -0x18 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x70u);	/* 4192a2: lea edx, [esi + eax + 0x70] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4192a6: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4192a7: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x10u);	/* 4192a8: lea edx, [esi + eax + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4192ac: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4192ad: push edx */
	m->esp -= 4; M32(m->esp) = 0x4192b3u; native_call(m, 0x4029d0u);	/* 4192ae: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4192b3: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4192b6: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4192bc: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4192bd: add esi, 0x64 */
	{ DWORD a_ = m->edi, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4192c0: cmp edi, 0x7518a4 */
	if (m->sf != m->of) goto L_41918f;	/* 4192c6: jl 0x41918f */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4192cc: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4192d3u; native_call(m, m->ebp);	/* 4192d1: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 4192d3: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 4192d8: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4192da: and ecx, 0x800001ff */
	if (!m->sf) goto L_4192ea;	/* 4192e0: jns 0x4192ea */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4192e2: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4192e3: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4192e9: inc ecx */
L_4192ea:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4192ea: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4192eb: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4192f1: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4192f2: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4192f4: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4192fa: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4192fd: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x419306u; native_call(m, 0x4566c0u);	/* 419301: call 0x4566c0 */
	m->edi = M32((DWORD)(0x4a9228u));	/* 419306: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41930c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419311: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419316: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41931b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x419322u; native_call(m, m->edi);	/* 419320: call edi */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 419322: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 419324: xor esi, esi */
L_419326:
	{ DWORD a_ = M32((DWORD)(0x4dbe48u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419326: cmp dword ptr [0x4dbe48], ebx */
	if (!m->zf) goto L_419335;	/* 41932c: jne 0x419335 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41932e: push 0x3f800000 */
	goto L_41933a;	/* 419333: jmp 0x41933a */
L_419335:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 419335: push 0x3ecccccd */
L_41933a:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41933a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41933f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419344: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41934bu; native_call(m, m->edi);	/* 419349: call edi */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 41934b: mov eax, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 419350: push 1 */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x54u);	/* 419352: lea ecx, [esi + eax + 0x54] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x28u);	/* 419356: lea eax, [esi + eax + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41935a: push ecx */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 41935b: mov ecx, dword ptr [0x4dcc90] */
	m->edx = (DWORD)(m->ecx + 0xa0u);	/* 419361: lea edx, [ecx + 0xa0] */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 419367: add ecx, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41936a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41936b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41936c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x419372u; native_call(m, 0x4282f0u);	/* 41936d: call 0x4282f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419372: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x3fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 419375: add esi, 0x3f */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 419378: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x17au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419379: cmp esi, 0x17a */
	if (m->sf != m->of) goto L_419326;	/* 41937f: jl 0x419326 */
	m->eax = M32((DWORD)(0x4dcc64u));	/* 419381: mov eax, dword ptr [0x4dcc64] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 419386: test eax, eax */
	if (m->zf) goto L_419399;	/* 419388: je 0x419399 */
	m->ecx = M32((DWORD)(0x4dbe48u));	/* 41938a: mov ecx, dword ptr [0x4dbe48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419390: push ecx */
	m->esp -= 4; M32(m->esp) = 0x419396u; native_call(m, 0x419000u);	/* 419391: call 0x419000 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419396: add esp, 4 */
L_419399:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 419399: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4193a0u; native_call(m, m->ebp);	/* 41939e: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4193a0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4193a5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4193aa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4193af: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4193b6u; native_call(m, m->edi);	/* 4193b4: call edi */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4193b6: mov esi, dword ptr [0x4a920c] */
	m->edx = 0x4dbe50u;	/* 4193bc: mov edx, 0x4dbe50 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4193c1: xor ebx, ebx */
	m->ebp = 0x4dcc70u;	/* 4193c3: mov ebp, 0x4dcc70 */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 4193c8: mov dword ptr [esp + 0x10], edx */
L_4193cc:
	m->edi = m->edx;	/* 4193cc: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4193ce: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4193d1: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4193d3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4193d5: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4193d7: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4193d8: cmp ecx, 1 */
	if (m->cf || m->zf) goto L_4194c2;	/* 4193db: jbe 0x4194c2 */
	m->eax = M32((DWORD)(m->ebp + 0x0u));	/* 4193e1: mov eax, dword ptr [ebp] */
	m->edx = m->eax;	/* 4193e4: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4193e6: and edx, 0x800001ff */
	if (!m->sf) goto L_4193f6;	/* 4193ec: jns 0x4193f6 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4193ee: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4193ef: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4193f5: inc edx */
L_4193f6:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4193f6: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4193f7: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4193fd: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4193fe: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 419404: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 419406: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 419409: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x419412u; native_call(m, 0x4566c0u);	/* 41940d: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 419412: push 7 */
	m->esp -= 4; M32(m->esp) = 0x41941au; native_call(m, M32(0x4a921cu));	/* 419414: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41941a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41941c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x419420u; native_call(m, m->esi);	/* 41941e: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 419420: mov edx, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 419426: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->ecx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41942c: add ecx, 0x40 */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x2au);	/* 41942f: lea eax, [ebx + edx + 0x2a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419433: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419434: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41943au; native_call(m, 0x41ef60u);	/* 419435: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41943a: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41943d: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41943f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x419446u; native_call(m, m->esi);	/* 419444: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 419446: mov edx, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 41944c: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->ecx, b_ = 0x9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 419452: add ecx, 0x9c */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x2au);	/* 419458: lea eax, [ebx + edx + 0x2a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41945c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41945d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x419463u; native_call(m, 0x41ef60u);	/* 41945e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419463: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419466: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41946b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x419472u; native_call(m, m->esi);	/* 419470: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 419472: mov edx, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 419478: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->ecx, b_ = 0x9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41947e: add ecx, 0x9c */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x4eu);	/* 419484: lea eax, [ebx + edx + 0x4e] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419488: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419489: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41948fu; native_call(m, 0x41ef60u);	/* 41948a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41948f: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419492: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419497: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41949bu; native_call(m, m->esi);	/* 419499: call esi */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41949b: mov edx, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 4194a1: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD a_ = m->ecx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4194a7: add ecx, 0x40 */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x4eu);	/* 4194aa: lea eax, [ebx + edx + 0x4e] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4194ae: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4194af: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4194b5u; native_call(m, 0x41ef60u);	/* 4194b0: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4194b5: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4194beu; native_call(m, M32(0x4a9220u));	/* 4194b8: call dword ptr [0x4a9220] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4194be: mov edx, dword ptr [esp + 0x10] */
L_4194c2:
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4194c2: add edx, 0x80 */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4194c8: add ebp, 4 */
	{ DWORD a_ = m->ebx, b_ = 0x3fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4194cb: add ebx, 0x3f */
	{ DWORD a_ = m->edx, b_ = 0x4dc150u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4194ce: cmp edx, 0x4dc150 */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 4194d4: mov dword ptr [esp + 0x10], edx */
	if (m->sf != m->of) goto L_4193cc;	/* 4194d8: jl 0x4193cc */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4194de: xor ebx, ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4194e0: xor ebp, ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->ebp;	/* 4194e2: mov dword ptr [esp + 0x10], ebp */
	goto L_4194ec;	/* 4194e6: jmp 0x4194ec */
L_4194e8:
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 4194e8: mov ebp, dword ptr [esp + 0x10] */
L_4194ec:
	m->edx = M32((DWORD)(0x4dbc64u));	/* 4194ec: mov edx, dword ptr [0x4dbc64] */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 4194f2: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 4194f7: mov ecx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4194fd: push edx */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 4194fe: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419504: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419505: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419506: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419507: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419511u; native_call(m, 0x41f0e0u);	/* 41950c: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 419511: mov ecx, dword ptr [0x4dcc94] */
	m->eax = (DWORD)(m->ebp + 0x756fa4u);	/* 419517: lea eax, [ebp + 0x756fa4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41951d: push eax */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 41951e: mov eax, dword ptr [0x4dcc90] */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x19u);	/* 419523: lea edx, [ebx + ecx + 0x19] */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 419527: add eax, 0x14 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41952a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41952b: push eax */
	m->esp -= 4; M32(m->esp) = 0x419531u; native_call(m, 0x402620u);	/* 41952c: call 0x402620 */
	m->ebp = (DWORD)(m->ebp + 0x4dbe50u);	/* 419531: lea ebp, [ebp + 0x4dbe50] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419537: or ecx, 0xffffffff */
	m->edi = m->ebp;	/* 41953a: mov edi, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41953c: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41953e: add esp, 0x20 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419541: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419543: not ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419545: push 0x3f800000 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41954a: dec ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41954b: push eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41954c: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419551: cmp ecx, 1 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419554: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419559: push 0x76d438 */
	if (!m->cf && !m->zf) goto L_41958f;	/* 41955e: ja 0x41958f */
	m->esp -= 4; M32(m->esp) = 0x419565u; native_call(m, 0x41f0e0u);	/* 419560: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 419565: mov eax, dword ptr [0x4dcc90] */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41956a: mov edx, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x757da4u; m->esp -= 4; M32(m->esp) = v_; }	/* 419570: push 0x757da4 */
	m->ecx = (DWORD)(m->eax + 0xa0u);	/* 419575: lea ecx, [eax + 0xa0] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41957b: add eax, 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41957e: push ecx */
	m->ecx = (DWORD)(m->ebx + m->edx*1 + 0x36u);	/* 41957f: lea ecx, [ebx + edx + 0x36] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419583: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419584: push eax */
	m->esp -= 4; M32(m->esp) = 0x41958au; native_call(m, 0x402740u);	/* 419585: call 0x402740 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41958a: add esp, 0x24 */
	goto L_4195b2;	/* 41958d: jmp 0x4195b2 */
L_41958f:
	m->esp -= 4; M32(m->esp) = 0x419594u; native_call(m, 0x41f0e0u);	/* 41958f: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 419594: mov edx, dword ptr [0x4dcc94] */
	m->ecx = M32((DWORD)(0x4dcc90u));	/* 41959a: mov ecx, dword ptr [0x4dcc90] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4195a0: push ebp */
	{ DWORD a_ = m->ecx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4195a1: add ecx, 0x18 */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x2du);	/* 4195a4: lea eax, [ebx + edx + 0x2d] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4195a8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4195a9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4195afu; native_call(m, 0x403170u);	/* 4195aa: call 0x403170 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4195af: add esp, 0x20 */
L_4195b2:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4195b2: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebx, b_ = 0x3fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4195b6: add ebx, 0x3f */
	{ DWORD a_ = m->eax, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4195b9: add eax, 0x80 */
	{ DWORD a_ = m->eax, b_ = 0x300u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4195be: cmp eax, 0x300 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4195c3: mov dword ptr [esp + 0x10], eax */
	if (m->sf != m->of) goto L_4194e8;	/* 4195c7: jl 0x4194e8 */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 4195cd: mov edx, dword ptr [0x4dcc98] */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 4195d3: mov eax, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4195d8: push 0xde1 */
	m->ebx = (DWORD)(m->edx + 0xffffff3eu);	/* 4195dd: lea ebx, [edx - 0xc2] */
	m->ebp = (DWORD)(m->eax + 0x28u);	/* 4195e3: lea ebp, [eax + 0x28] */
	m->esp -= 4; M32(m->esp) = 0x4195ecu; native_call(m, M32(0x4a922cu));	/* 4195e6: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4195ec: push 0x3f333333 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4195f1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4195f3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4195f5: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4195f7: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x419601u; native_call(m, 0x41f0e0u);	/* 4195fc: call 0x41f0e0 */
	m->edi = (DWORD)(m->ebp + 0x17cu);	/* 419601: lea edi, [ebp + 0x17c] */
	m->eax = (DWORD)(m->ebx + 0xa0u);	/* 419607: lea eax, [ebx + 0xa0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41960d: push 1 */
	m->ecx = (DWORD)(m->ebp + 0x118u);	/* 41960f: lea ecx, [ebp + 0x118] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 419615: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419616: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419617: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419618: push ebx */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 419619: mov dword ptr [esp + 0x38], eax */
	m->esp -= 4; M32(m->esp) = 0x419622u; native_call(m, 0x427970u);	/* 41961d: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419622: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419627: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41962c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419631: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 419633: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x41963du; native_call(m, 0x41f0e0u);	/* 419638: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 41963d: mov ecx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419641: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 419643: push edi */
	m->eax = (DWORD)(m->ebp + 0x118u);	/* 419644: lea eax, [ebp + 0x118] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41964a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41964b: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41964c: push ebx */
	m->esp -= 4; M32(m->esp) = 0x419652u; native_call(m, 0x427970u);	/* 41964d: call 0x427970 */
	m->edi = 0x4dc150u;	/* 419652: mov edi, 0x4dc150 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419657: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41965a: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41965c: add esp, 0x50 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41965f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419661: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 419663: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419664: cmp ecx, 1 */
	if (!m->cf && !m->zf) goto L_4196a2;	/* 419667: ja 0x4196a2 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419669: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41966e: push eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41966f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419674: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419679: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419683u; native_call(m, 0x41f0e0u);	/* 41967e: call 0x41f0e0 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 419683: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = 0x757e24u; m->esp -= 4; M32(m->esp) = v_; }	/* 419687: push 0x757e24 */
	m->eax = (DWORD)(m->ebp + 0x142u);	/* 41968c: lea eax, [ebp + 0x142] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419692: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419693: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419694: push ebx */
	m->esp -= 4; M32(m->esp) = 0x41969au; native_call(m, 0x402740u);	/* 419695: call 0x402740 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41969a: add esp, 0x24 */
	goto L_4197ff;	/* 41969d: jmp 0x4197ff */
L_4196a2:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4196a2: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4196adu; native_call(m, M32(0x4a9224u));	/* 4196a7: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4196ad: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4196b2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4196b7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4196bc: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4196c7u; native_call(m, M32(0x4a9228u));	/* 4196c1: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x4dcc88u));	/* 4196c7: mov eax, dword ptr [0x4dcc88] */
	m->ecx = m->eax;	/* 4196cc: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4196ce: and ecx, 0x800001ff */
	if (!m->sf) goto L_4196de;	/* 4196d4: jns 0x4196de */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4196d6: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4196d7: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4196dd: inc ecx */
L_4196de:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4196de: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4196df: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4196e5: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4196e6: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4196e8: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4196ee: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4196f1: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4196fau; native_call(m, 0x4566c0u);	/* 4196f5: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4196fa: push 7 */
	m->esp -= 4; M32(m->esp) = 0x419702u; native_call(m, M32(0x4a921cu));	/* 4196fc: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419702: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419704: push 0 */
	m->esp -= 4; M32(m->esp) = 0x419708u; native_call(m, m->esi);	/* 419706: call esi */
	m->edi = (DWORD)(m->ebp + 0x11cu);	/* 419708: lea edi, [ebp + 0x11c] */
	m->eax = (DWORD)(m->ebx + 0x10u);	/* 41970e: lea eax, [ebx + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 419711: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419712: push eax */
	m->esp -= 4; M32(m->esp) = 0x419718u; native_call(m, 0x41ef60u);	/* 419713: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419718: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41971b: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41971d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x419724u; native_call(m, m->esi);	/* 419722: call esi */
	m->eax = (DWORD)(m->ebx + 0x90u);	/* 419724: lea eax, [ebx + 0x90] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41972a: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41972b: push eax */
	m->esp -= 4; M32(m->esp) = 0x419731u; native_call(m, 0x41ef60u);	/* 41972c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419731: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419734: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419739: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x419740u; native_call(m, m->esi);	/* 41973e: call esi */
	m->edi = (DWORD)(m->ebp + 0x158u);	/* 419740: lea edi, [ebp + 0x158] */
	m->eax = (DWORD)(m->ebx + 0x90u);	/* 419746: lea eax, [ebx + 0x90] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41974c: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41974d: push eax */
	m->esp -= 4; M32(m->esp) = 0x419753u; native_call(m, 0x41ef60u);	/* 41974e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419753: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419756: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41975b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41975fu; native_call(m, m->esi);	/* 41975d: call esi */
	m->eax = (DWORD)(m->ebx + 0x10u);	/* 41975f: lea eax, [ebx + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 419762: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419763: push eax */
	m->esp -= 4; M32(m->esp) = 0x419769u; native_call(m, 0x41ef60u);	/* 419764: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419769: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x419772u; native_call(m, M32(0x4a9220u));	/* 41976c: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419772: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419777: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41977c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419781: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419786: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419790u; native_call(m, 0x41f0e0u);	/* 41978b: call 0x41f0e0 */
	m->esi = (DWORD)(m->ebx + 0x5u);	/* 419790: lea esi, [ebx + 5] */
	{ DWORD v_ = 0x4dc150u; m->esp -= 4; M32(m->esp) = v_; }	/* 419793: push 0x4dc150 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 419798: push edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 419799: push esi */
	m->esp -= 4; M32(m->esp) = 0x41979fu; native_call(m, 0x4125c0u);	/* 41979a: call 0x4125c0 */
	m->eax = M32((DWORD)(0x4dbe48u));	/* 41979f: mov eax, dword ptr [0x4dbe48] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4197a4: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4197a7: cmp eax, 3 */
	if (!m->zf && m->sf == m->of) goto L_4197ba;	/* 4197aa: jg 0x4197ba */
	m->eax = M32((DWORD)(0x4dc77cu));	/* 4197ac: mov eax, dword ptr [0x4dc77c] */
	m->edi = M32((DWORD)(m->eax*4 + 0x4dc79cu));	/* 4197b1: mov edi, dword ptr [eax*4 + 0x4dc79c] */
	goto L_4197c7;	/* 4197b8: jmp 0x4197c7 */
L_4197ba:
	m->ecx = M32((DWORD)(0x4dc77cu));	/* 4197ba: mov ecx, dword ptr [0x4dc77c] */
	m->edi = M32((DWORD)(m->ecx*4 + 0x4dcca4u));	/* 4197c0: mov edi, dword ptr [ecx*4 + 0x4dcca4] */
L_4197c7:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4197c7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4197cc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4197d1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4197d6: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4197db: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4197e5u; native_call(m, 0x41f0e0u);	/* 4197e0: call 0x41f0e0 */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4197e5: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x7641a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4197e8: add edi, 0x7641a4 */
	m->edx = (DWORD)(m->ebp + 0x16au);	/* 4197ee: lea edx, [ebp + 0x16a] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4197f4: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4197f5: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4197f6: push esi */
	m->esp -= 4; M32(m->esp) = 0x4197fcu; native_call(m, 0x4125c0u);	/* 4197f7: call 0x4125c0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4197fc: add esp, 0x20 */
L_4197ff:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4197ff: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41980au; native_call(m, M32(0x4a9224u));	/* 419804: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 41980a: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 41980f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419811: and ecx, 0x800001ff */
	if (!m->sf) goto L_419821;	/* 419817: jns 0x419821 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 419819: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41981a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 419820: inc ecx */
L_419821:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 419821: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 419822: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419828: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 419829: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 41982b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 419831: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 419834: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x41983du; native_call(m, 0x4566c0u);	/* 419838: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41983d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419842: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419847: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41984c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x419857u; native_call(m, M32(0x4a9228u));	/* 419851: call dword ptr [0x4a9228] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 419857: mov edi, dword ptr [esp + 0x14] */
	m->esi = (DWORD)(m->ebp + 0x15au);	/* 41985b: lea esi, [ebp + 0x15a] */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419861: cmp edi, 0xc */
	if (!m->zf) goto L_419acf;	/* 419864: jne 0x419acf */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41986a: push 1 */
	{ DWORD a_ = m->ebp, b_ = 0x13au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 41986c: add ebp, 0x13a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 419872: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419873: push ebx */
	m->eax = (DWORD)(m->ebx + 0xffffffd8u);	/* 419874: lea eax, [ebx - 0x28] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419877: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419878: push eax */
	m->esp -= 4; M32(m->esp) = 0x41987eu; native_call(m, 0x4284d0u);	/* 419879: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41987e: add esp, 0x14 */
L_419881:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 419881: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419885: push 0 */
	{ DWORD a_ = m->ebx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 419887: add ebx, 0xc8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41988d: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41988e: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41988f: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419890: push eax */
L_419891:
	m->esp -= 4; M32(m->esp) = 0x419896u; native_call(m, 0x4285c0u);	/* 419891: call 0x4285c0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419896: add esp, 0x14 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 419899: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41989e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4198a3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4198a8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4198b3u; native_call(m, M32(0x4a9228u));	/* 4198ad: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x4dcc9cu));	/* 4198b3: mov eax, dword ptr [0x4dcc9c] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 4198b8: mov ecx, dword ptr [0x4dcc98] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4198be: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4198c0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4198c1: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4198c2: add eax, -0x20 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4198c5: add ecx, 0xffffff60 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4198cb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4198cc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4198d2u; native_call(m, 0x4282f0u);	/* 4198cd: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dbc64u));	/* 4198d2: mov ecx, dword ptr [0x4dbc64] */
	m->edx = M32((DWORD)(0x4dbc60u));	/* 4198d8: mov edx, dword ptr [0x4dbc60] */
	m->eax = M32((DWORD)(0x4dbc5cu));	/* 4198de: mov eax, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4198e3: push ecx */
	m->ecx = M32((DWORD)(0x4dbc58u));	/* 4198e4: mov ecx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4198ea: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4198eb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4198ec: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4198ed: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4198f7u; native_call(m, 0x41f0e0u);	/* 4198f2: call 0x41f0e0 */
	m->ecx = 0xcu;	/* 4198f7: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4198fc: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x54u);	/* 4198fe: lea edi, [esp + 0x54] */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 419902: lea edx, [esp + 0x54] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419906: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419908: stosw word ptr es:[edi], ax */
	m->edi = 0x756da4u;	/* 41990a: mov edi, 0x756da4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41990f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419912: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419914: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419916: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419918: sub edi, ecx */
	m->eax = m->ecx;	/* 41991a: mov eax, ecx */
	m->esi = m->edi;	/* 41991c: mov esi, edi */
	m->edi = m->edx;	/* 41991e: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 419920: lea edx, [esp + 0x54] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419924: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419927: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 419929: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41992b: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41992d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419930: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b035cu;	/* 419932: mov edi, 0x4b035c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419937: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41993a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41993c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41993e: sub edi, ecx */
	m->esi = m->edi;	/* 419940: mov esi, edi */
	m->ebx = m->ecx;	/* 419942: mov ebx, ecx */
	m->edi = m->edx;	/* 419944: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419946: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419949: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 41994b: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41994d: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41994e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419951: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 419953: mov ecx, ebx */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 419955: lea edx, [esp + 0x54] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419959: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41995c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32((DWORD)(0x4dceacu));	/* 41995e: mov edi, dword ptr [0x4dceac] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419964: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 419967: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x751924u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41996a: add edi, 0x751924 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419970: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419972: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419974: sub edi, ecx */
	m->esi = m->edi;	/* 419976: mov esi, edi */
	m->ebx = m->ecx;	/* 419978: mov ebx, ecx */
	m->edi = m->edx;	/* 41997a: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41997c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41997f: repne scasb al, byte ptr es:[edi] */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 419981: dec edi */
	m->ecx = m->ebx;	/* 419982: mov ecx, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419984: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419987: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 419989: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x54u);	/* 41998b: lea eax, [esp + 0x54] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41998f: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419992: push eax */
	m->eax = M32((DWORD)(0x4dcc98u));	/* 419993: mov eax, dword ptr [0x4dcc98] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419998: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dcc9cu));	/* 41999a: mov ecx, dword ptr [0x4dcc9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4199a0: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4199a1: add ecx, -0x18 */
	{ DWORD a_ = m->eax, b_ = 0xffffff60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4199a4: add eax, 0xffffff60 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4199a9: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4199aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4199b0u; native_call(m, 0x4029d0u);	/* 4199ab: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4199b0: add esp, 0x38 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4199b3: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4199beu; native_call(m, M32(0x4a922cu));	/* 4199b8: call dword ptr [0x4a922c] */
	m->edx = M32((DWORD)(0x4dcc98u));	/* 4199be: mov edx, dword ptr [0x4dcc98] */
	m->eax = M32((DWORD)(0x4dcc94u));	/* 4199c4: mov eax, dword ptr [0x4dcc94] */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4199c9: push 0x3f333333 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4199ce: push 0x3f000000 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4199d3: push 0x3e4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4199d8: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4199dd: push 0x9da480 */
	m->ebp = (DWORD)(m->edx + 0xffffff3eu);	/* 4199e2: lea ebp, [edx - 0xc2] */
	m->ebx = (DWORD)(m->eax + 0x28u);	/* 4199e8: lea ebx, [eax + 0x28] */
	m->esp -= 4; M32(m->esp) = 0x4199f0u; native_call(m, 0x41f0e0u);	/* 4199eb: call 0x41f0e0 */
	m->ecx = (DWORD)(m->ebx + 0x10eu);	/* 4199f0: lea ecx, [ebx + 0x10e] */
	m->edi = (DWORD)(m->ebp + 0xc8u);	/* 4199f6: lea edi, [ebp + 0xc8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4199fc: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4199fe: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4199ff: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419a00: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419a01: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419a07u; native_call(m, 0x427970u);	/* 419a02: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a07: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a0c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a11: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a16: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a18: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x419a22u; native_call(m, 0x41f0e0u);	/* 419a1d: call 0x41f0e0 */
	m->edx = (DWORD)(m->ebx + 0x10au);	/* 419a22: lea edx, [ebx + 0x10a] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a28: push 0 */
	m->eax = (DWORD)(m->ebp + 0xc4u);	/* 419a2a: lea eax, [ebp + 0xc4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419a30: push edx */
	m->ecx = (DWORD)(m->ebx + 0x4u);	/* 419a31: lea ecx, [ebx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419a34: push eax */
	m->edx = (DWORD)(m->ebp + 0x4u);	/* 419a35: lea edx, [ebp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419a38: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419a39: push edx */
	m->esp -= 4; M32(m->esp) = 0x419a3fu; native_call(m, 0x427970u);	/* 419a3a: call 0x427970 */
	m->ecx = M32((DWORD)(0x4dc190u));	/* 419a3f: mov ecx, dword ptr [0x4dc190] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419a45: or eax, 0xffffffff */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419a48: add esp, 0x50 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419a4b: cmp ecx, eax */
	if (m->zf) goto L_41a239;	/* 419a4d: je 0x41a239 */
	{ DWORD a_ = M32((DWORD)(0x4dc194u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419a53: cmp dword ptr [0x4dc194], eax */
	if (!m->zf) goto L_419b04;	/* 419a59: jne 0x419b04 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a5f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a64: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a66: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a6b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a70: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419a7au; native_call(m, 0x41f0e0u);	/* 419a75: call 0x41f0e0 */
	m->eax = (DWORD)(m->ebx + 0x10u);	/* 419a7a: lea eax, [ebx + 0x10] */
	{ DWORD a_ = m->ebp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 419a7d: add ebp, 8 */
	{ DWORD v_ = 0x765fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a80: push 0x765fa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419a85: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419a86: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419a8cu; native_call(m, 0x402620u);	/* 419a87: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a8c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a91: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a96: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419a9b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419aa0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419aaau; native_call(m, 0x41f0e0u);	/* 419aa5: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dc198u));	/* 419aaa: mov ecx, dword ptr [0x4dc198] */
	{ DWORD a_ = m->ebx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 419ab0: add ebx, 0x28 */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419ab3: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x7652a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 419ab6: add ecx, 0x7652a4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419abc: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419abd: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419abe: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419ac4u; native_call(m, 0x4125c0u);	/* 419abf: call 0x4125c0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419ac4: add esp, 0x40 */
	m->edi = M32(m->esp); m->esp += 4;	/* 419ac7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 419ac8: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 419ac9: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 419aca: pop ebx */
	m->esp = m->ebp;	/* 419acb: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 419acd: pop ebp */
	m->esp += 4 + 0; return;	/* 419ace: ret  */
L_419acf:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419acf: push 0 */
	{ DWORD a_ = m->ebp, b_ = 0x13au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 419ad1: add ebp, 0x13a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 419ad7: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419ad8: push ebx */
	m->ecx = (DWORD)(m->ebx + 0xffffffd8u);	/* 419ad9: lea ecx, [ebx - 0x28] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419adc: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419add: push ecx */
	m->esp -= 4; M32(m->esp) = 0x419ae3u; native_call(m, 0x4284d0u);	/* 419ade: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419ae3: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419ae6: cmp edi, 0xd */
	if (!m->zf) goto L_419881;	/* 419ae9: jne 0x419881 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 419aef: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 419af3: push 1 */
	{ DWORD a_ = m->ebx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 419af5: add ebx, 0xc8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 419afb: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 419afc: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419afd: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419afe: push edx */
	goto L_419891;	/* 419aff: jmp 0x419891 */
L_419b04:
	m->edx = M32((DWORD)(0x4dbc64u));	/* 419b04: mov edx, dword ptr [0x4dbc64] */
	m->eax = M32((DWORD)(0x4dbc60u));	/* 419b0a: mov eax, dword ptr [0x4dbc60] */
	m->ecx = M32((DWORD)(0x4dbc5cu));	/* 419b0f: mov ecx, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419b15: push edx */
	m->edx = M32((DWORD)(0x4dbc58u));	/* 419b16: mov edx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419b1c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419b1d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419b1e: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b1f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419b29u; native_call(m, 0x41f0e0u);	/* 419b24: call 0x41f0e0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b29: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b2e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b33: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b38: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b3d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419b47u; native_call(m, 0x41f0e0u);	/* 419b42: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419b47: add esp, 0x28 */
	m->edi = 0x7574a4u;	/* 419b4a: mov edi, 0x7574a4 */
	m->esi = (DWORD)(m->ebx + 0x8u);	/* 419b4f: lea esi, [ebx + 8] */
L_419b52:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 419b52: push edi */
	m->eax = (DWORD)(m->ebp + 0x8u);	/* 419b53: lea eax, [ebp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 419b56: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419b57: push eax */
	m->esp -= 4; M32(m->esp) = 0x419b5du; native_call(m, 0x4125c0u);	/* 419b58: call 0x4125c0 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419b5d: add edi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419b63: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 419b66: add esi, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x757ca4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419b69: cmp edi, 0x757ca4 */
	if (m->sf != m->of) goto L_419b52;	/* 419b6f: jl 0x419b52 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b71: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b76: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b7b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b80: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 419b82: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x419b8cu; native_call(m, 0x41f0e0u);	/* 419b87: call 0x41f0e0 */
	m->ecx = 0xcu;	/* 419b8c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419b91: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 419b93: lea edi, [esp + 0x40] */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 419b97: lea edx, [esp + 0x40] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419b9b: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419b9d: stosw word ptr es:[edi], ax */
	m->edi = M32((DWORD)(0x4dc190u));	/* 419b9f: mov edi, dword ptr [0x4dc190] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419ba5: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 419ba8: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x757ea4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419bab: add edi, 0x757ea4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419bb1: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419bb3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419bb5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419bb7: sub edi, ecx */
	{ DWORD a_ = m->ebp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 419bb9: add ebp, 0xc0 */
	m->eax = m->ecx;	/* 419bbf: mov eax, ecx */
	m->esi = m->edi;	/* 419bc1: mov esi, edi */
	m->edi = m->edx;	/* 419bc3: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419bc5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419bc8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 419bca: mov ecx, eax */
	m->eax = (DWORD)(m->ebx + 0x8u);	/* 419bcc: lea eax, [ebx + 8] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419bcf: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419bd2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x40u);	/* 419bd4: lea ecx, [esp + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419bd8: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419bd9: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419bda: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419be0u; native_call(m, 0x4125f0u);	/* 419bdb: call 0x4125f0 */
	m->ecx = 0xcu;	/* 419be0: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419be5: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x4cu);	/* 419be7: lea edi, [esp + 0x4c] */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 419beb: lea edx, [esp + 0x4c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419bef: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419bf1: stosw word ptr es:[edi], ax */
	m->edi = M32((DWORD)(0x4dc194u));	/* 419bf3: mov edi, dword ptr [0x4dc194] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419bf9: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 419bfc: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x757fa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419bff: add edi, 0x757fa4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419c05: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419c07: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419c09: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419c0b: sub edi, ecx */
	m->eax = m->ecx;	/* 419c0d: mov eax, ecx */
	m->esi = m->edi;	/* 419c0f: mov esi, edi */
	m->edi = m->edx;	/* 419c11: mov edi, edx */
	m->edx = (DWORD)(m->ebx + 0x18u);	/* 419c13: lea edx, [ebx + 0x18] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419c16: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419c19: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 419c1b: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419c1d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419c20: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 419c22: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419c26: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419c27: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419c28: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419c2eu; native_call(m, 0x4125f0u);	/* 419c29: call 0x4125f0 */
	m->ecx = 0xcu;	/* 419c2e: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419c33: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x58u);	/* 419c35: lea edi, [esp + 0x58] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 419c39: push 0xa */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419c3b: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dc198u));	/* 419c3d: mov ecx, dword ptr [0x4dc198] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419c43: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 419c45: lea eax, [esp + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419c49: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419c4a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x419c50u; native_call(m, 0x49fb53u);	/* 419c4b: call 0x49fb53 */
	m->edi = 0x765824u;	/* 419c50: mov edi, 0x765824 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419c55: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419c58: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x64u);	/* 419c5a: lea edx, [esp + 0x64] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419c5e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419c60: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419c62: sub edi, ecx */
	m->esi = m->edi;	/* 419c64: mov esi, edi */
	m->edi = m->edx;	/* 419c66: mov edi, edx */
	m->edx = m->ecx;	/* 419c68: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419c6a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419c6d: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 419c6f: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 419c71: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419c72: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419c75: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 419c77: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x64u);	/* 419c79: lea eax, [esp + 0x64] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419c7d: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419c80: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419c81: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0x28u);	/* 419c83: lea ecx, [ebx + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419c86: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419c87: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419c8du; native_call(m, 0x4125f0u);	/* 419c88: call 0x4125f0 */
	m->ecx = 0xcu;	/* 419c8d: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419c92: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x70u);	/* 419c94: lea edi, [esp + 0x70] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419c98: add esp, 0x44 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419c9b: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419c9d: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc19cu));	/* 419c9f: mov eax, dword ptr [0x4dc19c] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 419ca4: lea edx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 419ca8: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419caa: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419cab: push eax */
	m->esp -= 4; M32(m->esp) = 0x419cb1u; native_call(m, 0x49fb53u);	/* 419cac: call 0x49fb53 */
	m->edi = 0x765924u;	/* 419cb1: mov edi, 0x765924 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419cb6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419cb9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 419cbb: lea edx, [esp + 0x38] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419cbf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419cc1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419cc3: sub edi, ecx */
	m->esi = m->edi;	/* 419cc5: mov esi, edi */
	m->edi = m->edx;	/* 419cc7: mov edi, edx */
	m->edx = m->ecx;	/* 419cc9: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419ccb: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419cce: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 419cd0: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 419cd2: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419cd3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419cd6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 419cd8: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 419cda: lea eax, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419cde: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419ce1: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419ce2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0x38u);	/* 419ce4: lea ecx, [ebx + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419ce7: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419ce8: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419ceeu; native_call(m, 0x4125f0u);	/* 419ce9: call 0x4125f0 */
	m->ecx = 0xcu;	/* 419cee: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419cf3: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x44u);	/* 419cf5: lea edi, [esp + 0x44] */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 419cf9: lea edx, [esp + 0x44] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419cfd: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419cff: stosw word ptr es:[edi], ax */
	m->edi = M32((DWORD)(0x4dc1a0u));	/* 419d01: mov edi, dword ptr [0x4dc1a0] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419d07: or ecx, 0xffffffff */
	{ DWORD a_ = m->edi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 419d0a: shl edi, 7 */
	{ DWORD a_ = m->edi, b_ = 0x7581a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419d0d: add edi, 0x7581a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419d13: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419d15: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419d17: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419d19: sub edi, ecx */
	m->eax = m->ecx;	/* 419d1b: mov eax, ecx */
	m->esi = m->edi;	/* 419d1d: mov esi, edi */
	m->edi = m->edx;	/* 419d1f: mov edi, edx */
	m->edx = (DWORD)(m->ebx + 0x48u);	/* 419d21: lea edx, [ebx + 0x48] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419d24: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419d27: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 419d29: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419d2b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419d2e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 419d30: lea ecx, [esp + 0x44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419d34: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419d35: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419d36: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419d3cu; native_call(m, 0x4125f0u);	/* 419d37: call 0x4125f0 */
	m->ecx = 0xcu;	/* 419d3c: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419d41: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x50u);	/* 419d43: lea edi, [esp + 0x50] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 419d47: push 0xa */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419d49: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4dc1a4u));	/* 419d4b: mov ecx, dword ptr [0x4dc1a4] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419d51: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x54u);	/* 419d53: lea eax, [esp + 0x54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419d57: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419d58: push ecx */
	m->esp -= 4; M32(m->esp) = 0x419d5eu; native_call(m, 0x49fb53u);	/* 419d59: call 0x49fb53 */
	m->eax = M32((DWORD)(0x4dc194u));	/* 419d5e: mov eax, dword ptr [0x4dc194] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419d63: add esp, 0x30 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 419d66: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_419dae;	/* 419d69: ja 0x419dae */
	switch (m->eax) { case 0: goto L_419d72; case 1: goto L_419d72; case 2: goto L_419d86; case 3: goto L_419d9a; default: abort(); }	/* 419d6b: jmp dword ptr [eax*4 + 0x41a270] */
L_419d72:
	m->eax = M32((DWORD)(0x9f1818u));	/* 419d72: mov eax, dword ptr [0x9f1818] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 419d77: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 419d7a: lea eax, [eax + edx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->eax*4 + 0x9f9068u)));	/* 419d7d: fild dword ptr [eax*4 + 0x9f9068] */
	goto L_419dc0;	/* 419d84: jmp 0x419dc0 */
L_419d86:
	m->eax = M32((DWORD)(0x9f1818u));	/* 419d86: mov eax, dword ptr [0x9f1818] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 419d8b: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 419d8e: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f906cu)));	/* 419d91: fild dword ptr [edx*4 + 0x9f906c] */
	goto L_419dc0;	/* 419d98: jmp 0x419dc0 */
L_419d9a:
	m->eax = M32((DWORD)(0x9f1818u));	/* 419d9a: mov eax, dword ptr [0x9f1818] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 419d9f: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 419da2: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9070u)));	/* 419da5: fild dword ptr [edx*4 + 0x9f9070] */
	goto L_419dc0;	/* 419dac: jmp 0x419dc0 */
L_419dae:
	m->eax = M32((DWORD)(0x9f1818u));	/* 419dae: mov eax, dword ptr [0x9f1818] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 419db3: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 419db6: lea edx, [eax + ecx*2] */
	FPUSH((long double)(int)M32((DWORD)(m->edx*4 + 0x9f9074u)));	/* 419db9: fild dword ptr [edx*4 + 0x9f9074] */
L_419dc0:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 419dc0: fmul dword ptr [0x4a9420] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x4dc1a4u));	/* 419dc6: fimul dword ptr [0x4dc1a4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 419dcc: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 419dd2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 419dd4: test ah, 1 */
	if (m->zf) goto L_419deb;	/* 419dd7: je 0x419deb */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 419dd9: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419dde: push eax */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 419ddf: lea eax, [esp + 0x1c] */
	{ DWORD v_ = 0x4b02f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 419de3: push 0x4b02f8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419de8: push eax */
	goto L_419dfb;	/* 419de9: jmp 0x419dfb */
L_419deb:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 419deb: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419df0: push eax */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 419df1: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = 0x4b02f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 419df5: push 0x4b02f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419dfa: push ecx */
L_419dfb:
	m->esp -= 4; M32(m->esp) = 0x419e00u; native_call(m, 0x49e9ddu);	/* 419dfb: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x24u);	/* 419e00: lea edi, [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419e04: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419e07: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419e09: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419e0c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419e0e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419e10: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 419e12: lea edx, [esp + 0x2c] */
	m->esi = m->edi;	/* 419e16: mov esi, edi */
	m->edi = m->edx;	/* 419e18: mov edi, edx */
	m->edx = m->ecx;	/* 419e1a: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419e1c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419e1f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 419e21: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 419e23: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419e24: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419e27: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 419e29: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 419e2b: lea eax, [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419e2f: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419e32: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419e33: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0x58u);	/* 419e35: lea ecx, [ebx + 0x58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419e38: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419e39: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419e3fu; native_call(m, 0x4125f0u);	/* 419e3a: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1a8u)));	/* 419e3f: fld dword ptr [0x4dc1a8] */
	m->ecx = 0xcu;	/* 419e45: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419e4a: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x4u)) = (double)ST(0); FPOP();	/* 419e4c: fstp qword ptr [esp + 4] */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 419e50: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419e54: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419e57: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 419e59: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 419e5d: push 0x4b0354 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419e62: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419e63: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x419e6au; native_call(m, 0x49e9ddu);	/* 419e65: call 0x49e9dd */
	m->edi = 0x7655a4u;	/* 419e6a: mov edi, 0x7655a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419e6f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419e72: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 419e74: lea edx, [esp + 0x3c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419e78: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419e7a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419e7c: sub edi, ecx */
	m->esi = m->edi;	/* 419e7e: mov esi, edi */
	m->edi = m->edx;	/* 419e80: mov edi, edx */
	m->edx = m->ecx;	/* 419e82: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419e84: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419e87: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 419e89: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 419e8b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419e8c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419e8f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 419e91: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 419e93: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419e97: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419e9a: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419e9b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0x68u);	/* 419e9d: lea ecx, [ebx + 0x68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419ea0: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419ea1: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419ea7u; native_call(m, 0x4125f0u);	/* 419ea2: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1acu)));	/* 419ea7: fld dword ptr [0x4dc1ac] */
	m->ecx = 0xcu;	/* 419ead: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419eb2: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x14u)) = (double)ST(0); FPOP();	/* 419eb4: fstp qword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 419eb8: lea edi, [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419ebc: add esp, 0x14 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419ebf: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 419ec1: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 419ec5: push 0x4b0354 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419eca: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419ecb: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x419ed2u; native_call(m, 0x49e9ddu);	/* 419ecd: call 0x49e9dd */
	m->edi = 0x7659a4u;	/* 419ed2: mov edi, 0x7659a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419ed7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419eda: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 419edc: lea edx, [esp + 0x3c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419ee0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419ee2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419ee4: sub edi, ecx */
	m->esi = m->edi;	/* 419ee6: mov esi, edi */
	m->edi = m->edx;	/* 419ee8: mov edi, edx */
	m->edx = m->ecx;	/* 419eea: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419eec: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419eef: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 419ef1: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 419ef3: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419ef4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419ef7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 419ef9: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 419efb: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419eff: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419f02: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419f03: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0x78u);	/* 419f05: lea ecx, [ebx + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419f08: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419f09: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419f0fu; native_call(m, 0x4125f0u);	/* 419f0a: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1b0u)));	/* 419f0f: fld dword ptr [0x4dc1b0] */
	m->ecx = 0xcu;	/* 419f15: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419f1a: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x14u)) = (double)ST(0); FPOP();	/* 419f1c: fstp qword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 419f20: lea edi, [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419f24: add esp, 0x14 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419f27: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 419f29: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 419f2d: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419f32: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419f33: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x419f3au; native_call(m, 0x49e9ddu);	/* 419f35: call 0x49e9dd */
	m->edi = 0x765624u;	/* 419f3a: mov edi, 0x765624 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419f3f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419f42: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 419f44: lea edx, [esp + 0x3c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419f48: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419f4a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419f4c: sub edi, ecx */
	m->esi = m->edi;	/* 419f4e: mov esi, edi */
	m->edi = m->edx;	/* 419f50: mov edi, edx */
	m->edx = m->ecx;	/* 419f52: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419f54: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419f57: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 419f59: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 419f5b: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419f5c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419f5f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 419f61: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 419f63: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419f67: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419f6a: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419f6b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0x88u);	/* 419f6d: lea ecx, [ebx + 0x88] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419f73: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419f74: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419f7au; native_call(m, 0x4125f0u);	/* 419f75: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1b4u)));	/* 419f7a: fld dword ptr [0x4dc1b4] */
	m->ecx = 0xcu;	/* 419f80: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419f85: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x14u)) = (double)ST(0); FPOP();	/* 419f87: fstp qword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 419f8b: lea edi, [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419f8f: add esp, 0x14 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419f92: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 419f94: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 419f98: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 419f9d: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 419f9e: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x419fa5u; native_call(m, 0x49e9ddu);	/* 419fa0: call 0x49e9dd */
	m->edi = 0x7655a4u;	/* 419fa5: mov edi, 0x7655a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419faa: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419fad: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 419faf: lea edx, [esp + 0x3c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419fb3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 419fb5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 419fb7: sub edi, ecx */
	m->esi = m->edi;	/* 419fb9: mov esi, edi */
	m->edi = m->edx;	/* 419fbb: mov edi, edx */
	m->edx = m->ecx;	/* 419fbd: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419fbf: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 419fc2: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 419fc4: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 419fc6: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 419fc7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 419fca: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 419fcc: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 419fce: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 419fd2: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 419fd5: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 419fd6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0x98u);	/* 419fd8: lea ecx, [ebx + 0x98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 419fde: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 419fdf: push ebp */
	m->esp -= 4; M32(m->esp) = 0x419fe5u; native_call(m, 0x4125f0u);	/* 419fe0: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1b8u)));	/* 419fe5: fld dword ptr [0x4dc1b8] */
	m->ecx = 0xcu;	/* 419feb: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 419ff0: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x14u)) = (double)ST(0); FPOP();	/* 419ff2: fstp qword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 419ff6: lea edi, [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 419ffa: add esp, 0x14 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 419ffd: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 419fff: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a003: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a008: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a009: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x41a010u; native_call(m, 0x49e9ddu);	/* 41a00b: call 0x49e9dd */
	m->edi = 0x7655a4u;	/* 41a010: mov edi, 0x7655a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a015: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a018: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41a01a: lea edx, [esp + 0x3c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a01e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a020: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a022: sub edi, ecx */
	m->esi = m->edi;	/* 41a024: mov esi, edi */
	m->edi = m->edx;	/* 41a026: mov edi, edx */
	m->edx = m->ecx;	/* 41a028: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a02a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a02d: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41a02f: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a031: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a032: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a035: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41a037: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41a039: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a03d: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a040: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a041: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0xa8u);	/* 41a043: lea ecx, [ebx + 0xa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a049: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41a04a: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41a050u; native_call(m, 0x4125f0u);	/* 41a04b: call 0x4125f0 */
	m->ecx = 0xcu;	/* 41a050: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a055: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 41a057: lea edi, [esp + 0x48] */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 41a05b: lea edx, [esp + 0x48] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a05f: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a061: stosw word ptr es:[edi], ax */
	m->eax = M32((DWORD)(0x4dc1bcu));	/* 41a063: mov eax, dword ptr [0x4dc1bc] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 41a068: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a06a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a06b: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a071u; native_call(m, 0x49fb53u);	/* 41a06c: call 0x49fb53 */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 41a071: lea ecx, [esp + 0x54] */
	m->edx = (DWORD)(m->ebx + 0xb8u);	/* 41a075: lea edx, [ebx + 0xb8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a07b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a07c: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41a07d: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41a083u; native_call(m, 0x4125f0u);	/* 41a07e: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1c0u)));	/* 41a083: fld dword ptr [0x4dc1c0] */
	m->ecx = 0xcu;	/* 41a089: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a08e: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x60u);	/* 41a090: lea edi, [esp + 0x60] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a094: add esp, 0x2c */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a097: rep stosd dword ptr es:[edi], eax */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41a099: fstp qword ptr [esp] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a09c: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 41a09e: lea eax, [esp + 0x34] */
	{ DWORD v_ = 0x4b0354u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a0a2: push 0x4b0354 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a0a7: push eax */
	m->esp -= 4; M32(m->esp) = 0x41a0adu; native_call(m, 0x49e9ddu);	/* 41a0a8: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41a0ad: lea edx, [esp + 0x3c] */
	m->edi = 0x765724u;	/* 41a0b1: mov edi, 0x765724 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a0b6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a0b9: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a0bb: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a0bd: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a0bf: sub edi, ecx */
	m->esi = m->edi;	/* 41a0c1: mov esi, edi */
	m->edi = m->edx;	/* 41a0c3: mov edi, edx */
	m->edx = m->ecx;	/* 41a0c5: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a0c7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a0ca: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41a0cc: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a0ce: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a0cf: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a0d2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41a0d4: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41a0d6: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a0da: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a0dd: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a0de: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0xc8u);	/* 41a0e0: lea ecx, [ebx + 0xc8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a0e6: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41a0e7: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41a0edu; native_call(m, 0x4125f0u);	/* 41a0e8: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1c4u)));	/* 41a0ed: fld dword ptr [0x4dc1c4] */
	m->ecx = 0xcu;	/* 41a0f3: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a0f8: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x14u)) = (double)ST(0); FPOP();	/* 41a0fa: fstp qword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 41a0fe: lea edi, [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a102: add esp, 0x14 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a105: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41a107: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a10b: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a110: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a111: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x41a118u; native_call(m, 0x49e9ddu);	/* 41a113: call 0x49e9dd */
	m->edi = 0x765624u;	/* 41a118: mov edi, 0x765624 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a11d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a120: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41a122: lea edx, [esp + 0x3c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a126: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a128: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a12a: sub edi, ecx */
	m->esi = m->edi;	/* 41a12c: mov esi, edi */
	m->edi = m->edx;	/* 41a12e: mov edi, edx */
	m->edx = m->ecx;	/* 41a130: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a132: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a135: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41a137: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a139: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a13a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a13d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41a13f: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41a141: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a145: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a148: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a149: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0xd8u);	/* 41a14b: lea ecx, [ebx + 0xd8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a151: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41a152: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41a158u; native_call(m, 0x4125f0u);	/* 41a153: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1c8u)));	/* 41a158: fld dword ptr [0x4dc1c8] */
	m->ecx = 0xcu;	/* 41a15e: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a163: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x14u)) = (double)ST(0); FPOP();	/* 41a165: fstp qword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 41a169: lea edi, [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a16d: add esp, 0x14 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a170: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41a172: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a176: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a17b: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a17c: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x41a183u; native_call(m, 0x49e9ddu);	/* 41a17e: call 0x49e9dd */
	m->edi = 0x765724u;	/* 41a183: mov edi, 0x765724 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a188: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a18b: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41a18d: lea edx, [esp + 0x3c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a191: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a193: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a195: sub edi, ecx */
	m->esi = m->edi;	/* 41a197: mov esi, edi */
	m->edi = m->edx;	/* 41a199: mov edi, edx */
	m->edx = m->ecx;	/* 41a19b: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a19d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a1a0: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41a1a2: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a1a4: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a1a5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a1a8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41a1aa: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41a1ac: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a1b0: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a1b3: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a1b4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->ebx + 0xe8u);	/* 41a1b6: lea ecx, [ebx + 0xe8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a1bc: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41a1bd: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41a1c3u; native_call(m, 0x4125f0u);	/* 41a1be: call 0x4125f0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dc1ccu)));	/* 41a1c3: fld dword ptr [0x4dc1cc] */
	m->ecx = 0xcu;	/* 41a1c9: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a1ce: xor eax, eax */
	MDBL((DWORD)(m->esp + 0x14u)) = (double)ST(0); FPOP();	/* 41a1d0: fstp qword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->esp + 0x48u);	/* 41a1d4: lea edi, [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a1d8: add esp, 0x14 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41a1db: rep stosd dword ptr es:[edi], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 41a1dd: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4b0334u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a1e1: push 0x4b0334 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a1e6: push edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 41a1e7: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x41a1eeu; native_call(m, 0x49e9ddu);	/* 41a1e9: call 0x49e9dd */
	m->edi = 0x7657a4u;	/* 41a1ee: mov edi, 0x7657a4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a1f3: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41a1f6: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 41a1f8: lea edx, [esp + 0x3c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a1fc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41a1fe: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41a200: sub edi, ecx */
	{ DWORD a_ = m->ebx, b_ = 0xf8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 41a202: add ebx, 0xf8 */
	m->esi = m->edi;	/* 41a208: mov esi, edi */
	m->edi = m->edx;	/* 41a20a: mov edi, edx */
	m->edx = m->ecx;	/* 41a20c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a20e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41a211: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 41a213: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 41a215: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41a216: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41a219: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41a21b: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 41a21d: lea eax, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41a221: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41a224: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a225: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41a226: push ebp */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41a227: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x41a22eu; native_call(m, 0x4125f0u);	/* 41a229: call 0x4125f0 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a22e: add esp, 0x1c */
	m->edi = M32(m->esp); m->esp += 4;	/* 41a231: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41a232: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41a233: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41a234: pop ebx */
	m->esp = m->ebp;	/* 41a235: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41a237: pop ebp */
	m->esp += 4 + 0; return;	/* 41a238: ret  */
L_41a239:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a239: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a23e: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a240: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a245: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a24a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41a254u; native_call(m, 0x41f0e0u);	/* 41a24f: call 0x41f0e0 */
	{ DWORD v_ = 0x757da4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41a254: push 0x757da4 */
	{ DWORD a_ = m->ebx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 41a259: add ebx, 0x40 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41a25c: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41a25d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41a25e: push ebp */
	m->esp -= 4; M32(m->esp) = 0x41a264u; native_call(m, 0x4029d0u);	/* 41a25f: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41a264: add esp, 0x24 */
	m->edi = M32(m->esp); m->esp += 4;	/* 41a267: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41a268: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41a269: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41a26a: pop ebx */
	m->esp = m->ebp;	/* 41a26b: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41a26d: pop ebp */
	m->esp += 4 + 0; return;	/* 41a26e: ret  */
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
