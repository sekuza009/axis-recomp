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

static void lift_4924d0(X86 *m);
static void lift_496820(X86 *m);
static void lift_46bdc0(X86 *m);
static void lift_4922c0(X86 *m);

/* hud_drawNameIcon (0x4922c0), lifted by tools/lift.py */
static void lift_4922c0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4922c0: sub esp, 0xc */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4922c3: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4922c4: push edi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 4922c5: mov edi, dword ptr [esp + 0x18] */
	m->ebp = m->ecx;	/* 4922c9: mov ebp, ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4922cb: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_4924c5;	/* 4922cd: jle 0x4924c5 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 4922d3: fild dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4922d7: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4922d8: push esi */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4922d9: dec edi */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4922da: fstp dword ptr [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x4922e3u; native_call(m, 0x4685b0u);	/* 4922de: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4922e3: mov dword ptr [esp + 0x20], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4922e7: fild dword ptr [esp + 0x20] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 4922eb: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 4922f1: fdivr dword ptr [esp + 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4922f5: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4922fa: fild dword ptr [esp + 0x28] */
	m->ebx = m->eax;	/* 4922fe: mov ebx, eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 492300: fstp dword ptr [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x492309u; native_call(m, 0x4685c0u);	/* 492304: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 492309: mov dword ptr [esp + 0x20], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 49230d: fild dword ptr [esp + 0x20] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 492311: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 492317: fdivr dword ptr [esp + 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49231b: call 0x49ec14 */
	m->esi = m->eax;	/* 492320: mov esi, eax */
	m->esp -= 4; M32(m->esp) = 0x492327u; native_call(m, 0x4685b0u);	/* 492322: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 492327: mov dword ptr [esp + 0x20], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 49232b: fild dword ptr [esp + 0x20] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 49232f: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4b0u));	/* 492335: fdivr dword ptr [0x4aa4b0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49233b: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 492340: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x492349u; native_call(m, 0x4685c0u);	/* 492344: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 492349: mov dword ptr [esp + 0x20], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 49234d: fild dword ptr [esp + 0x20] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 492351: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa43cu));	/* 492357: fdivr dword ptr [0x4aa43c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49235d: call 0x49ec14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 492362: push 0xde1 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 492367: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x492371u; native_call(m, M32(0x4a9224u));	/* 49236b: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->ebp + 0xbc06b0u));	/* 492371: mov eax, dword ptr [ebp + 0xbc06b0] */
	m->ecx = m->eax;	/* 492377: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 492379: and ecx, 0x800001ff */
	if (!m->sf) goto L_492389;	/* 49237f: jns 0x492389 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 492381: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 492382: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 492388: inc ecx */
L_492389:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 492389: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49238a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 492390: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492391: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 492393: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 492399: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 49239c: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4923a5u; native_call(m, 0x4566c0u);	/* 4923a0: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4923a5: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4923adu; native_call(m, M32(0x4a921cu));	/* 4923a7: call dword ptr [0x4a921c] */
	m->eax = 0x66666667u;	/* 4923ad: mov eax, 0x66666667 */
	m->ecx = 0xau;	/* 4923b2: mov ecx, 0xa */
	{ long long p_ = (long long)(int)m->eax * (int)m->edi; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 4923b7: imul edi */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4923b9: sar edx, 2 */
	m->eax = m->edx;	/* 4923bc: mov eax, edx */
	m->ebp = M32((DWORD)(0x4a920cu));	/* 4923be: mov ebp, dword ptr [0x4a920c] */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4923c4: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4923c7: add edx, eax */
	m->eax = m->edi;	/* 4923c9: mov eax, edi */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 4923cb: mov dword ptr [esp + 0x18], edx */
	{ DWORD a_ = m->edx, b_ = 0xeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4923cf: add edx, 0xe */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4923d2: shl edx, 4 */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 4923d5: mov dword ptr [esp + 0x20], edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4923d9: cdq  */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4923da: fild dword ptr [esp + 0x20] */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4923de: idiv ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4923e0: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4923e6: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4923ea: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4923ee: push eax */
	m->edi = m->edx;	/* 4923ef: mov edi, edx */
	m->edx = (DWORD)(m->edi + m->edi*2 + 0x0u);	/* 4923f1: lea edx, [edi + edi*2] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4923f4: shl edx, 3 */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 4923f7: mov dword ptr [esp + 0x28], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4923fb: fild dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4923ff: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 492405: fstp dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 492409: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49240d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x492410u; native_call(m, m->ebp);	/* 49240e: call ebp */
	m->esp -= 4; M32(m->esp) = 0x492415u; native_call(m, 0x4685c0u);	/* 492410: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492415: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492417: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 492418: push ebx */
	m->esp -= 4; M32(m->esp) = 0x49241fu; native_call(m, M32(0x4a91f4u));	/* 492419: call dword ptr [0x4a91f4] */
	m->edx = (DWORD)(m->edi + m->edi*2 + 0x3u);	/* 49241f: lea edx, [edi + edi*2 + 3] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 492423: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 492427: shl edx, 3 */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49242a: mov dword ptr [esp + 0x24], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49242e: push eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 49242f: fild dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 492433: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 492439: fstp dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 49243d: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 492441: push ecx */
	m->esp -= 4; M32(m->esp) = 0x492444u; native_call(m, m->ebp);	/* 492442: call ebp */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 492444: mov edx, dword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->edx + m->ebx*1 + 0x0u);	/* 492448: lea edi, [edx + ebx] */
	m->esp -= 4; M32(m->esp) = 0x492450u; native_call(m, 0x4685c0u);	/* 49244b: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492450: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492452: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 492453: push edi */
	m->esp -= 4; M32(m->esp) = 0x49245au; native_call(m, M32(0x4a91f4u));	/* 492454: call dword ptr [0x4a91f4] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49245a: mov eax, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 49245e: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492462: add eax, 0xf */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 492465: shl eax, 4 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 492468: mov dword ptr [esp + 0x20], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 49246c: fild dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 492470: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 492476: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 49247a: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49247e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49247f: push edx */
	m->esp -= 4; M32(m->esp) = 0x492482u; native_call(m, m->ebp);	/* 492480: call ebp */
	m->esp -= 4; M32(m->esp) = 0x492487u; native_call(m, 0x4685c0u);	/* 492482: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esp + 0x10u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492487: sub eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49248b: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49248d: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49248e: push edi */
	m->edi = M32((DWORD)(0x4a91f4u));	/* 49248f: mov edi, dword ptr [0x4a91f4] */
	m->esp -= 4; M32(m->esp) = 0x492497u; native_call(m, m->edi);	/* 492495: call edi */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 492497: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 49249b: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49249f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4924a0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4924a3u; native_call(m, m->ebp);	/* 4924a1: call ebp */
	m->esp -= 4; M32(m->esp) = 0x4924a8u; native_call(m, 0x4685c0u);	/* 4924a3: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esp + 0x10u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4924a8: sub eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4924ac: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4924ae: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4924af: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4924b2u; native_call(m, m->edi);	/* 4924b0: call edi */
	m->esp -= 4; M32(m->esp) = 0x4924b8u; native_call(m, M32(0x4a9220u));	/* 4924b2: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4924b8: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4924c3u; native_call(m, M32(0x4a922cu));	/* 4924bd: call dword ptr [0x4a922c] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4924c3: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4924c4: pop ebx */
L_4924c5:
	m->edi = M32(m->esp); m->esp += 4;	/* 4924c5: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4924c6: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4924c7: add esp, 0xc */
	m->esp += 4 + 12; return;	/* 4924ca: ret 0xc */
}

/* hud_drawLeaderIcon (0x4924d0), lifted by tools/lift.py */
static void lift_4924d0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4924d0: sub esp, 0xc */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4924d3: fild dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4924d7: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4924d8: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4924d9: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4924da: push edi */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 4924db: fstp dword ptr [esp + 0x14] */
	m->esi = m->ecx;	/* 4924df: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x4924e6u; native_call(m, 0x4685b0u);	/* 4924e1: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4924e6: mov dword ptr [esp + 0x24], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 4924ea: fild dword ptr [esp + 0x24] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 4924ee: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 4924f4: fdivr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4924f8: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4924fd: fild dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 492501: mov dword ptr [esp + 0x24], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 492505: fstp dword ptr [esp + 0x14] */
	m->esp -= 4; M32(m->esp) = 0x49250eu; native_call(m, 0x4685c0u);	/* 492509: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 49250e: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 492512: fild dword ptr [esp + 0x28] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 492516: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 49251c: fdivr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 492520: call 0x49ec14 */
	m->edi = m->eax;	/* 492525: mov edi, eax */
	m->esp -= 4; M32(m->esp) = 0x49252cu; native_call(m, 0x4685b0u);	/* 492527: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 49252c: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 492530: fild dword ptr [esp + 0x28] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 492534: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4b0u));	/* 49253a: fdivr dword ptr [0x4aa4b0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 492540: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 492545: mov dword ptr [esp + 0x18], eax */
	m->esp -= 4; M32(m->esp) = 0x49254eu; native_call(m, 0x4685c0u);	/* 492549: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 49254e: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 492552: fild dword ptr [esp + 0x28] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 492556: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa43cu));	/* 49255c: fdivr dword ptr [0x4aa43c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 492562: call 0x49ec14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 492567: push 0xde1 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 49256c: mov dword ptr [esp + 0x18], eax */
	m->esp -= 4; M32(m->esp) = 0x492576u; native_call(m, M32(0x4a9224u));	/* 492570: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 492576: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 492579: test eax, eax */
	if (!m->zf) goto L_4925b3;	/* 49257b: jne 0x4925b3 */
	m->eax = M32((DWORD)(m->esi + 0x22f86acu));	/* 49257d: mov eax, dword ptr [esi + 0x22f86ac] */
	m->ecx = m->eax;	/* 492583: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 492585: and ecx, 0x800001ff */
	if (!m->sf) goto L_492595;	/* 49258b: jns 0x492595 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 49258d: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49258e: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 492594: inc ecx */
L_492595:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 492595: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 492596: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49259c: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49259d: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 49259f: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4925a5: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4925a8: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4925b1u; native_call(m, 0x4566c0u);	/* 4925ac: call 0x4566c0 */
	goto L_4925c5;	/* 4925b1: jmp 0x4925c5 */
L_4925b3:
	m->eax = M32((DWORD)(m->esi + 0x22f06a8u));	/* 4925b3: mov eax, dword ptr [esi + 0x22f06a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4925b9: push eax */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4925ba: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4925c5u; native_call(m, M32(0x4a9264u));	/* 4925bf: call dword ptr [0x4a9264] */
L_4925c5:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4925c5: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4925cdu; native_call(m, M32(0x4a921cu));	/* 4925c7: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 4925cd: mov esi, dword ptr [esp + 0x20] */
	m->eax = m->esi;	/* 4925d1: mov eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4925d3: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4925d4: and edx, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4925d7: add eax, edx */
	m->ebx = m->eax;	/* 4925d9: mov ebx, eax */
	{ DWORD a_ = m->ebx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 4925db: sar ebx, 2 */
	m->ecx = m->ebx;	/* 4925de: mov ecx, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4925e0: shl ecx, 4 */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 4925e3: mov dword ptr [esp + 0x28], ecx */
	{ DWORD a_ = m->esi, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4925e7: and esi, 0x80000003 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4925ed: fild dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4b4u));	/* 4925f1: fmul dword ptr [0x4aa4b4] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4925f7: fstp dword ptr [esp + 0x28] */
	if (!m->sf) goto L_492602;	/* 4925fb: jns 0x492602 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 4925fd: dec esi */
	{ DWORD a_ = m->esi, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4925fe: or esi, 0xfffffffc */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 492601: inc esi */
L_492602:
	m->edx = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 492602: lea edx, [esi + esi*2] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 492605: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 492609: shl edx, 3 */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 49260c: mov dword ptr [esp + 0x20], edx */
	m->ebp = M32((DWORD)(0x4a920cu));	/* 492610: mov ebp, dword ptr [0x4a920c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 492616: fild dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49261a: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa420u));	/* 49261b: fmul dword ptr [0x4aa420] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 492621: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 492625: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 492629: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49262cu; native_call(m, m->ebp);	/* 49262a: call ebp */
	m->esp -= 4; M32(m->esp) = 0x492631u; native_call(m, 0x4685c0u);	/* 49262c: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 492631: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492635: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492637: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 492638: push edx */
	m->esp -= 4; M32(m->esp) = 0x49263fu; native_call(m, M32(0x4a91f4u));	/* 492639: call dword ptr [0x4a91f4] */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x3u);	/* 49263f: lea eax, [esi + esi*2 + 3] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 492643: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 492647: shl eax, 3 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 49264a: mov dword ptr [esp + 0x20], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49264e: push ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 49264f: fild dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa420u));	/* 492653: fmul dword ptr [0x4aa420] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 492659: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 49265d: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 492661: push edx */
	m->esp -= 4; M32(m->esp) = 0x492664u; native_call(m, m->ebp);	/* 492662: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 492664: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 492668: mov ecx, dword ptr [esp + 0x24] */
	m->esi = (DWORD)(m->eax + m->ecx*1 + 0x0u);	/* 49266c: lea esi, [eax + ecx] */
	m->esp -= 4; M32(m->esp) = 0x492674u; native_call(m, 0x4685c0u);	/* 49266f: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492674: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492676: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 492677: push esi */
	m->esp -= 4; M32(m->esp) = 0x49267eu; native_call(m, M32(0x4a91f4u));	/* 492678: call dword ptr [0x4a91f4] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 49267e: inc ebx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 49267f: mov edx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ebx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 492683: shl ebx, 4 */
	M32((DWORD)(m->esp + 0x28u)) = m->ebx;	/* 492686: mov dword ptr [esp + 0x28], ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 49268a: fild dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4b4u));	/* 49268e: fmul dword ptr [0x4aa4b4] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 492694: fstp dword ptr [esp + 0x28] */
	m->ebx = M32((DWORD)(m->esp + 0x28u));	/* 492698: mov ebx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49269c: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49269d: push edx */
	m->esp -= 4; M32(m->esp) = 0x4926a0u; native_call(m, m->ebp);	/* 49269e: call ebp */
	m->esp -= 4; M32(m->esp) = 0x4926a5u; native_call(m, 0x4685c0u);	/* 4926a0: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esp + 0x14u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4926a5: sub eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4926a9: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4926ab: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4926ac: push esi */
	m->esi = M32((DWORD)(0x4a91f4u));	/* 4926ad: mov esi, dword ptr [0x4a91f4] */
	m->esp -= 4; M32(m->esp) = 0x4926b5u; native_call(m, m->esi);	/* 4926b3: call esi */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4926b5: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4926b9: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4926ba: push eax */
	m->esp -= 4; M32(m->esp) = 0x4926bdu; native_call(m, m->ebp);	/* 4926bb: call ebp */
	m->esp -= 4; M32(m->esp) = 0x4926c2u; native_call(m, 0x4685c0u);	/* 4926bd: call 0x4685c0 */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 4926c2: mov ebp, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4926c6: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4926ca: sub eax, ebp */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4926cc: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4926ce: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4926cf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4926d2u; native_call(m, m->esi);	/* 4926d0: call esi */
	m->esp -= 4; M32(m->esp) = 0x4926d8u; native_call(m, M32(0x4a9220u));	/* 4926d2: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4926d8: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4926e3u; native_call(m, M32(0x4a922cu));	/* 4926dd: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4926e3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4926e4: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4926e5: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4926e6: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4926e7: add esp, 0xc */
	m->esp += 4 + 12; return;	/* 4926ea: ret 0xc */
}

/* replay_drawIcon (0x496820), lifted by tools/lift.py */
static void lift_496820(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 496820: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496824: sub esp, 0xc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 496827: push ebx */
	m->ebx = m->ecx;	/* 496828: mov ebx, ecx */
	m->ecx = m->eax;	/* 49682a: mov ecx, eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49682c: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49682d: push esi */
	{ DWORD a_ = m->ecx, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49682e: and ecx, 0x80000007 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496834: push edi */
	if (!m->sf) goto L_49683c;	/* 496835: jns 0x49683c */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 496837: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 496838: or ecx, 0xfffffff8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49683b: inc ecx */
L_49683c:
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49683c: shl ecx, 5 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49683f: cdq  */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 496840: mov dword ptr [esp + 0x28], ecx */
	{ DWORD a_ = m->edx, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 496844: and edx, 7 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 496847: fild dword ptr [esp + 0x28] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49684b: add eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 49684d: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 496851: sar eax, 3 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 496854: fmul dword ptr [0x4a957c] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49685a: add eax, 3 */
	{ DWORD a_ = m->edx, b_ = 0xfffffff8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49685d: add edx, -8 */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 496860: shl eax, 5 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 496863: mov dword ptr [esp + 0x28], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 496867: fstp dword ptr [esp + 0x14] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 49686b: fild dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 49686f: mov dword ptr [esp + 0x28], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 496873: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 496879: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 49687d: fild dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 496881: fstp dword ptr [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x49688au; native_call(m, 0x4685c0u);	/* 496885: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 49688a: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 49688e: fild dword ptr [esp + 0x28] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 496892: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 496898: fdivr dword ptr [esp + 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49689c: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4968a1: fild dword ptr [esp + 0x20] */
	m->esi = m->eax;	/* 4968a5: mov esi, eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4968a7: fstp dword ptr [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x4968b0u; native_call(m, 0x4685b0u);	/* 4968ab: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4968b0: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4968b4: fild dword ptr [esp + 0x28] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 4968b8: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 4968be: fdivr dword ptr [esp + 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4968c2: call 0x49ec14 */
	m->edi = m->eax;	/* 4968c7: mov edi, eax */
	m->esp -= 4; M32(m->esp) = 0x4968ceu; native_call(m, 0x4685b0u);	/* 4968c9: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4968ce: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4968d2: fild dword ptr [esp + 0x28] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 4968d6: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4a8u));	/* 4968dc: fdivr dword ptr [0x4aa4a8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4968e2: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4968e7: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x4968f0u; native_call(m, 0x4685c0u);	/* 4968eb: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4968f0: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4968f4: fild dword ptr [esp + 0x28] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 4968f8: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4a8u));	/* 4968fe: fdivr dword ptr [0x4aa4a8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 496904: call 0x49ec14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 496909: push 0xde1 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 49690e: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x496918u; native_call(m, M32(0x4a9224u));	/* 496912: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->ebx + 0xbc06b0u));	/* 496918: mov eax, dword ptr [ebx + 0xbc06b0] */
	m->ecx = m->eax;	/* 49691e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 496920: and ecx, 0x800001ff */
	if (!m->sf) goto L_496930;	/* 496926: jns 0x496930 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 496928: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 496929: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49692f: inc ecx */
L_496930:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 496930: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 496931: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496937: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 496938: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 49693a: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 496940: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 496943: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x49694cu; native_call(m, 0x4566c0u);	/* 496947: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49694c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496951: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496956: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49695b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496966u; native_call(m, M32(0x4a9228u));	/* 496960: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 496966: push 7 */
	m->esp -= 4; M32(m->esp) = 0x49696eu; native_call(m, M32(0x4a921cu));	/* 496968: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49696e: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 496972: mov ecx, dword ptr [esp + 0x14] */
	m->ebx = M32((DWORD)(0x4a920cu));	/* 496976: mov ebx, dword ptr [0x4a920c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49697c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49697d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x496980u; native_call(m, m->ebx);	/* 49697e: call ebx */
	m->esp -= 4; M32(m->esp) = 0x496985u; native_call(m, 0x4685c0u);	/* 496980: call 0x4685c0 */
	m->ebp = M32((DWORD)(0x4a91f4u));	/* 496985: mov ebp, dword ptr [0x4a91f4] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49698b: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49698d: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49698e: push edi */
	m->esp -= 4; M32(m->esp) = 0x496991u; native_call(m, m->ebp);	/* 49698f: call ebp */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 496991: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 496995: fadd dword ptr [0x4aa274] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49699b: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49699f: push edx */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4969a0: fstp dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4969a4: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4969a8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4969abu; native_call(m, m->ebx);	/* 4969a9: call ebx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4969ab: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4969af: add ecx, edi */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 4969b1: mov dword ptr [esp + 0x24], ecx */
	m->esp -= 4; M32(m->esp) = 0x4969bau; native_call(m, 0x4685c0u);	/* 4969b5: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4969ba: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4969be: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4969c0: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4969c1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4969c4u; native_call(m, m->ebp);	/* 4969c2: call ebp */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4969c4: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 4969c8: fadd dword ptr [0x4aa274] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4969ce: mov ecx, dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4969d2: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4969d6: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4969da: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4969db: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4969deu; native_call(m, m->ebx);	/* 4969dc: call ebx */
	m->esp -= 4; M32(m->esp) = 0x4969e3u; native_call(m, 0x4685c0u);	/* 4969de: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4969e3: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4969e7: sub eax, esi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4969e9: sub eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4969eb: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4969ef: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4969f0: push edx */
	m->esp -= 4; M32(m->esp) = 0x4969f3u; native_call(m, m->ebp);	/* 4969f1: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4969f3: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4969f7: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4969fb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4969fc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4969ffu; native_call(m, m->ebx);	/* 4969fd: call ebx */
	m->esp -= 4; M32(m->esp) = 0x496a04u; native_call(m, 0x4685c0u);	/* 4969ff: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 496a04: sub eax, esi */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 496a06: mov esi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 496a0a: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496a0c: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496a0d: push edi */
	m->esp -= 4; M32(m->esp) = 0x496a10u; native_call(m, m->ebp);	/* 496a0e: call ebp */
	m->esp -= 4; M32(m->esp) = 0x496a16u; native_call(m, M32(0x4a9220u));	/* 496a10: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 496a16: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x496a21u; native_call(m, M32(0x4a922cu));	/* 496a1b: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 496a21: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 496a22: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 496a23: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 496a24: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496a25: add esp, 0xc */
	m->esp += 4 + 12; return;	/* 496a28: ret 0xc */
}

/* hud_drawDigits (0x46bdc0), lifted by tools/lift.py */
static void lift_46bdc0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46bdc0: sub esp, 0x24 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 46bdc3: fld dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa280u));	/* 46bdc7: fmul dword ptr [0x4aa280] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46bdcd: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46bdce: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46bdcf: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46bdd0: push edi */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 46bdd1: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 46bdd6: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa27cu));	/* 46bdda: fmul dword ptr [0x4aa27c] */
	m->esi = m->eax;	/* 46bde0: mov esi, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->esi;	/* 46bde2: mov dword ptr [esp + 0x1c], esi */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 46bde6: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 46bdeb: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 46bdef: fmul dword ptr [0x4a9534] */
	m->ebx = m->eax;	/* 46bdf5: mov ebx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ebx;	/* 46bdf7: mov dword ptr [esp + 0x14], ebx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 46bdfb: call 0x49ec14 */
	m->ebp = M32((DWORD)(m->esp + 0x48u));	/* 46be00: mov ebp, dword ptr [esp + 0x48] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 46be04: mov dword ptr [esp + 0x10], eax */
	m->eax = m->esi;	/* 46be08: mov eax, esi */
	m->esi = M32((DWORD)(m->esp + 0x3cu));	/* 46be0a: mov esi, dword ptr [esp + 0x3c] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46be0e: imul eax, ebp */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46be11: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46be12: sub eax, edx */
	m->edi = m->eax;	/* 46be14: mov edi, eax */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 46be16: mov eax, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->edi, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 46be1a: sar edi, 1 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46be1c: add edi, eax */
	m->eax = m->ebx;	/* 46be1e: mov eax, ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46be20: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46be21: sub eax, edx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46be23: xor ebx, ebx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46be25: sar eax, 1 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46be27: sub esi, eax */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 46be29: mov eax, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46be2d: cmp eax, ebx */
	if (m->sf == m->of) goto L_46be41;	/* 46be2f: jge 0x46be41 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 46be31: neg eax */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 46be33: mov dword ptr [esp + 0x44], eax */
	M32((DWORD)(m->esp + 0x2cu)) = 0x1u;	/* 46be37: mov dword ptr [esp + 0x2c], 1 */
	goto L_46be45;	/* 46be3f: jmp 0x46be45 */
L_46be41:
	M32((DWORD)(m->esp + 0x2cu)) = m->ebx;	/* 46be41: mov dword ptr [esp + 0x2c], ebx */
L_46be45:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46be45: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x46be50u; native_call(m, M32(0x4a9224u));	/* 46be4a: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0xa106acu));	/* 46be50: mov eax, dword ptr [0xa106ac] */
	m->ecx = m->eax;	/* 46be55: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46be57: and ecx, 0x800001ff */
	if (!m->sf) goto L_46be67;	/* 46be5d: jns 0x46be67 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46be5f: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46be60: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 46be66: inc ecx */
L_46be67:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46be67: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46be68: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46be6e: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46be6f: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 46be71: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46be77: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 46be7a: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x46be83u; native_call(m, 0x4566c0u);	/* 46be7e: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 46be83: push 7 */
	m->esp -= 4; M32(m->esp) = 0x46be8bu; native_call(m, M32(0x4a921cu));	/* 46be85: call dword ptr [0x4a921c] */
	m->ecx = 0xau;	/* 46be8b: mov ecx, 0xa */
	M32((DWORD)(m->esp + 0x18u)) = m->ebx;	/* 46be90: mov dword ptr [esp + 0x18], ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46be94: cmp ebp, ebx */
	m->ebx = M32((DWORD)(0x4a920cu));	/* 46be96: mov ebx, dword ptr [0x4a920c] */
	m->ebp = M32((DWORD)(0x4a91f4u));	/* 46be9c: mov ebp, dword ptr [0x4a91f4] */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 46bea2: mov dword ptr [esp + 0x3c], ecx */
	if (m->zf || m->sf != m->of) goto L_46c050;	/* 46bea6: jle 0x46c050 */
	goto L_46beb2;	/* 46beac: jmp 0x46beb2 */
L_46beae:
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 46beae: mov ecx, dword ptr [esp + 0x3c] */
L_46beb2:
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 46beb2: mov edx, dword ptr [esp + 0x1c] */
	m->eax = 0x66666667u;	/* 46beb6: mov eax, 0x66666667 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46bebb: sub edi, edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 46bebd: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46bebf: sar edx, 2 */
	m->eax = m->edx;	/* 46bec2: mov eax, edx */
	M32((DWORD)(m->esp + 0x38u)) = m->edi;	/* 46bec4: mov dword ptr [esp + 0x38], edi */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46bec8: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46becb: add edx, eax */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 46becd: mov eax, dword ptr [esp + 0x44] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 46bed1: mov dword ptr [esp + 0x40], edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46bed5: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46bed6: idiv ecx */
	m->eax = m->edx;	/* 46bed8: mov eax, edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46beda: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->esp + 0x40u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46bedb: idiv dword ptr [esp + 0x40] */
	m->ecx = m->eax;	/* 46bedf: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 46bee1: mov eax, dword ptr [esp + 0x4c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46bee5: test eax, eax */
	if (!m->zf) goto L_46bf01;	/* 46bee7: jne 0x46bf01 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 46bee9: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46beed: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46bf01;	/* 46beef: jle 0x46bf01 */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 46bef1: mov edx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 46bef5: mov eax, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46bef9: cmp eax, edx */
	if (m->sf != m->of) goto L_46c050;	/* 46befb: jl 0x46c050 */
L_46bf01:
	m->eax = 0x66666667u;	/* 46bf01: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 46bf06: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46bf08: sar edx, 1 */
	m->eax = m->edx;	/* 46bf0a: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46bf0c: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46bf0f: add edx, eax */
	m->eax = m->ecx;	/* 46bf11: mov eax, ecx */
	m->ecx = 0x5u;	/* 46bf13: mov ecx, 5 */
	m->edi = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 46bf18: lea edi, [edx + edx*2] */
	m->edx = (DWORD)(m->edi + m->edi*8 + 0x70u);	/* 46bf1b: lea edx, [edi + edi*8 + 0x70] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 46bf1f: mov dword ptr [esp + 0x40], edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46bf23: cdq  */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x40u)));	/* 46bf24: fild dword ptr [esp + 0x40] */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 46bf28: idiv ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46bf2a: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 46bf30: fstp dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 46bf34: mov dword ptr [esp + 0x24], edx */
	m->eax = (DWORD)(m->edx*8 + 0x0u);	/* 46bf38: lea eax, [edx*8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bf3f: sub eax, edx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46bf41: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 46bf44: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 46bf48: mov dword ptr [esp + 0x40], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bf4c: push eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x44u)));	/* 46bf4d: fild dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46bf51: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 46bf57: fstp dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 46bf5b: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46bf5f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46bf62u; native_call(m, m->ebx);	/* 46bf60: call ebx */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 46bf62: mov eax, dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 46bf66: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bf6a: sub eax, ecx */
	M32((DWORD)(m->esp + 0x40u)) = m->eax;	/* 46bf6c: mov dword ptr [esp + 0x40], eax */
	m->esp -= 4; M32(m->esp) = 0x46bf75u; native_call(m, 0x4685c0u);	/* 46bf70: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 46bf75: mov edx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bf79: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bf7b: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46bf7c: push edx */
	m->esp -= 4; M32(m->esp) = 0x46bf7fu; native_call(m, m->ebp);	/* 46bf7d: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 46bf7f: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 46bf83: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46bf87: push edx */
	m->ecx = (DWORD)(m->eax + 0x1u);	/* 46bf88: lea ecx, [eax + 1] */
	m->eax = (DWORD)(m->ecx*8 + 0x0u);	/* 46bf8b: lea eax, [ecx*8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bf92: sub eax, ecx */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46bf94: lea ecx, [eax + eax*4] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 46bf97: mov dword ptr [esp + 0x28], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 46bf9b: fild dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46bf9f: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 46bfa5: fstp dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 46bfa9: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bfad: push eax */
	m->esp -= 4; M32(m->esp) = 0x46bfb0u; native_call(m, m->ebx);	/* 46bfae: call ebx */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 46bfb0: mov ecx, dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46bfb4: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 46bfb8: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46bfbc: add ecx, edx */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46bfbe: add ecx, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 46bfc0: mov dword ptr [esp + 0x20], ecx */
	m->esp -= 4; M32(m->esp) = 0x46bfc9u; native_call(m, 0x4685c0u);	/* 46bfc4: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 46bfc9: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46bfcd: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bfcf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46bfd0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46bfd3u; native_call(m, m->ebp);	/* 46bfd1: call ebp */
	m->edx = (DWORD)(m->edi + m->edi*8 + 0x8bu);	/* 46bfd3: lea edx, [edi + edi*8 + 0x8b] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 46bfda: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 46bfde: mov dword ptr [esp + 0x30], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 46bfe2: fild dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46bfe6: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 46bfec: fstp dword ptr [esp + 0x30] */
	m->edi = M32((DWORD)(m->esp + 0x30u));	/* 46bff0: mov edi, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46bff4: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46bff5: push eax */
	m->esp -= 4; M32(m->esp) = 0x46bff8u; native_call(m, m->ebx);	/* 46bff6: call ebx */
	m->esp -= 4; M32(m->esp) = 0x46bffdu; native_call(m, 0x4685c0u);	/* 46bff8: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46bffd: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 46c001: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c005: sub eax, esi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c007: sub eax, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c009: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c00a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46c00du; native_call(m, m->ebp);	/* 46c00b: call ebp */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 46c00d: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c011: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c012: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c015u; native_call(m, m->ebx);	/* 46c013: call ebx */
	m->esp -= 4; M32(m->esp) = 0x46c01au; native_call(m, 0x4685c0u);	/* 46c015: call 0x4685c0 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 46c01a: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c01e: sub eax, esi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c020: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c022: push eax */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 46c023: mov eax, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c027: push eax */
	m->esp -= 4; M32(m->esp) = 0x46c02au; native_call(m, m->ebp);	/* 46c028: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 46c02a: mov eax, dword ptr [esp + 0x3c] */
	m->edi = M32((DWORD)(m->esp + 0x38u));	/* 46c02e: mov edi, dword ptr [esp + 0x38] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46c032: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 46c035: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46c039: shl ecx, 1 */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 46c03b: mov dword ptr [esp + 0x3c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x48u));	/* 46c03f: mov ecx, dword ptr [esp + 0x48] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46c043: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c044: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 46c046: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_46beae;	/* 46c04a: jl 0x46beae */
L_46c050:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x2cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c050: cmp dword ptr [esp + 0x2c], 1 */
	if (!m->zf) goto L_46c0e3;	/* 46c055: jne 0x46c0e3 */
	{ DWORD v_ = 0x3ee00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c05b: push 0x3ee00000 */
	{ DWORD v_ = 0x3f2f0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c060: push 0x3f2f0000 */
	m->esp -= 4; M32(m->esp) = 0x46c067u; native_call(m, m->ebx);	/* 46c065: call ebx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 46c067: mov edx, dword ptr [esp + 0x10] */
	m->eax = m->edi;	/* 46c06b: mov eax, edi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c06d: sub eax, edx */
	M32((DWORD)(m->esp + 0x40u)) = m->eax;	/* 46c06f: mov dword ptr [esp + 0x40], eax */
	m->esp -= 4; M32(m->esp) = 0x46c078u; native_call(m, 0x4685c0u);	/* 46c073: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 46c078: mov edx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c07c: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c07e: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c07f: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c082u; native_call(m, m->ebp);	/* 46c080: call ebp */
	{ DWORD v_ = 0x3ee00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c082: push 0x3ee00000 */
	{ DWORD v_ = 0x3f520000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c087: push 0x3f520000 */
	m->esp -= 4; M32(m->esp) = 0x46c08eu; native_call(m, m->ebx);	/* 46c08c: call ebx */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46c08e: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 46c092: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46c096: add edi, eax */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46c098: add edi, ecx */
	m->esp -= 4; M32(m->esp) = 0x46c09fu; native_call(m, 0x4685c0u);	/* 46c09a: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c09f: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0a1: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0a2: push edi */
	m->esp -= 4; M32(m->esp) = 0x46c0a5u; native_call(m, m->ebp);	/* 46c0a3: call ebp */
	{ DWORD v_ = 0x3f0b0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0a5: push 0x3f0b0000 */
	{ DWORD v_ = 0x3f520000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0aa: push 0x3f520000 */
	m->esp -= 4; M32(m->esp) = 0x46c0b1u; native_call(m, m->ebx);	/* 46c0af: call ebx */
	m->esp -= 4; M32(m->esp) = 0x46c0b6u; native_call(m, 0x4685c0u);	/* 46c0b1: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46c0b6: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c0ba: sub eax, esi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c0bc: sub eax, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0be: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0bf: push edi */
	m->esp -= 4; M32(m->esp) = 0x46c0c2u; native_call(m, m->ebp);	/* 46c0c0: call ebp */
	{ DWORD v_ = 0x3f0b0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0c2: push 0x3f0b0000 */
	{ DWORD v_ = 0x3f2f0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0c7: push 0x3f2f0000 */
	m->esp -= 4; M32(m->esp) = 0x46c0ceu; native_call(m, m->ebx);	/* 46c0cc: call ebx */
	m->esp -= 4; M32(m->esp) = 0x46c0d3u; native_call(m, 0x4685c0u);	/* 46c0ce: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46c0d3: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c0d7: sub eax, esi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c0d9: sub eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 46c0db: mov edx, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0df: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0e0: push edx */
	m->esp -= 4; M32(m->esp) = 0x46c0e3u; native_call(m, m->ebp);	/* 46c0e1: call ebp */
L_46c0e3:
	m->esp -= 4; M32(m->esp) = 0x46c0e9u; native_call(m, M32(0x4a9220u));	/* 46c0e3: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c0e9: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x46c0f4u; native_call(m, M32(0x4a922cu));	/* 46c0ee: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46c0f4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46c0f5: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46c0f6: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46c0f7: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c0f8: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 46c0fb: ret  */
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
