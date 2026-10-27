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

static void lift_469320(X86 *m);

/* loading_draw (0x469320), lifted by tools/lift.py */
static void lift_469320(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x120u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469320: sub esp, 0x120 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 469326: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 469327: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469328: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 469329: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46932a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46932f: push 0x3f800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 469334: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 469339: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x469344u; native_call(m, M32(0x4a91e0u));	/* 46933e: call dword ptr [0x4a91e0] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 469344: xor esi, esi */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 469346: push 0x3ff00000 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46934b: push esi */
	m->esp -= 4; M32(m->esp) = 0x469352u; native_call(m, M32(0x4a91dcu));	/* 46934c: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x4100u; m->esp -= 4; M32(m->esp) = v_; }	/* 469352: push 0x4100 */
	m->esp -= 4; M32(m->esp) = 0x46935du; native_call(m, M32(0x4a91e8u));	/* 469357: call dword ptr [0x4a91e8] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46935d: push 0x3f800000 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 469362: push 1 */
	m->esp -= 4; M32(m->esp) = 0x469369u; native_call(m, 0x4685f0u);	/* 469364: call 0x4685f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469369: add esp, 8 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46936c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x469377u; native_call(m, M32(0x4a9224u));	/* 469371: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0xa0e980u));	/* 469377: mov eax, dword ptr [0xa0e980] */
	m->ecx = m->eax;	/* 46937c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46937e: and ecx, 0x800001ff */
	if (!m->sf) goto L_46938e;	/* 469384: jns 0x46938e */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 469386: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469387: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 46938d: inc ecx */
L_46938e:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46938e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46938f: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469395: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469396: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 469398: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46939e: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4693a1: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4693aau; native_call(m, 0x4566c0u);	/* 4693a5: call 0x4566c0 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4693aa: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4693af: push 0x3f800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4693b4: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4693b9: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x4693c4u; native_call(m, M32(0x4a9228u));	/* 4693be: call dword ptr [0x4a9228] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x134u)));	/* 4693c4: fld dword ptr [esp + 0x134] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4693cb: fadd dword ptr [0x4a9418] */
	m->edi = M32((DWORD)(0x4a920cu));	/* 4693d1: mov edi, dword ptr [0x4a920c] */
	m->ebx = M32((DWORD)(0x4a9290u));	/* 4693d7: mov ebx, dword ptr [0x4a9290] */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 4693dd: mov dword ptr [esp + 0x10], esi */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4693e1: fstp dword ptr [esp + 0x28] */
L_4693e5:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4693e5: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4693edu; native_call(m, M32(0x4a921cu));	/* 4693e7: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4693ed: fild dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x134u));	/* 4693f1: mov eax, dword ptr [esp + 0x134] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4693f8: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa26cu));	/* 4693f9: fmul dword ptr [0x4aa26c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4693ff: fstp dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 469403: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469407: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46940au; native_call(m, m->edi);	/* 469408: call edi */
	m->eax = 0x38e38e39u;	/* 46940a: mov eax, 0x38e38e39 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 46940f: lea ecx, [esp + 0x14] */
	{ long long p_ = (long long)(int)m->eax * (int)m->esi; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 469413: imul esi */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 469415: sar edx, 2 */
	m->eax = m->edx;	/* 469418: mov eax, edx */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 46941a: mov dword ptr [esp + 0x14], 0 */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 469422: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 469425: add edx, eax */
	M32((DWORD)(m->esp + 0x18u)) = 0x43c80000u;	/* 469427: mov dword ptr [esp + 0x18], 0x43c80000 */
	m->ebp = m->edx;	/* 46942f: mov ebp, edx */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 469431: mov dword ptr [esp + 0x1c], 0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 469439: push ebp */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46943a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x469441u; native_call(m, 0x4677c0u);	/* 46943c: call 0x4677c0 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 469441: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469445: push ecx */
	m->esp -= 4; M32(m->esp) = 0x469448u; native_call(m, m->ebx);	/* 469446: call ebx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 469448: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x134u));	/* 46944c: mov eax, dword ptr [esp + 0x134] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 469453: inc edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469454: push eax */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 469455: mov dword ptr [esp + 0x24], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 469459: fild dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa26cu));	/* 46945d: fmul dword ptr [0x4aa26c] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 469463: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 469467: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46946b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46946eu; native_call(m, m->edi);	/* 46946c: call edi */
	m->ecx = (DWORD)(m->esi + 0xe10u);	/* 46946e: lea ecx, [esi + 0xe10] */
	m->eax = 0x38e38e39u;	/* 469474: mov eax, 0x38e38e39 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 469479: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46947b: sar edx, 2 */
	m->eax = m->edx;	/* 46947e: mov eax, edx */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 469480: lea ecx, [esp + 0x14] */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 469484: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 469487: add edx, eax */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 469489: mov dword ptr [esp + 0x14], 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469491: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 469492: push 0 */
	M32((DWORD)(m->esp + 0x20u)) = 0x43c80000u;	/* 469494: mov dword ptr [esp + 0x20], 0x43c80000 */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 46949c: mov dword ptr [esp + 0x24], 0 */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 4694a4: mov dword ptr [esp + 0x34], edx */
	m->esp -= 4; M32(m->esp) = 0x4694adu; native_call(m, 0x4677c0u);	/* 4694a8: call 0x4677c0 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 4694ad: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4694b1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4694b4u; native_call(m, m->ebx);	/* 4694b2: call ebx */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 4694b4: mov edx, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4694b8: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4694bc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4694bd: push eax */
	m->esp -= 4; M32(m->esp) = 0x4694c0u; native_call(m, m->edi);	/* 4694be: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4694c0: mov ecx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 4694c4: mov dword ptr [esp + 0x14], 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4694cc: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4694cd: push 0 */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 4694cf: lea ecx, [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x20u)) = 0x43c80000u;	/* 4694d3: mov dword ptr [esp + 0x20], 0x43c80000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc6c4597cu;	/* 4694db: mov dword ptr [esp + 0x24], 0xc6c4597c */
	m->esp -= 4; M32(m->esp) = 0x4694e8u; native_call(m, 0x4677c0u);	/* 4694e3: call 0x4677c0 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 4694e8: lea edx, [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4694ec: push edx */
	m->esp -= 4; M32(m->esp) = 0x4694efu; native_call(m, m->ebx);	/* 4694ed: call ebx */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 4694ef: mov eax, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4694f3: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4694f7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4694f8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4694fbu; native_call(m, m->edi);	/* 4694f9: call edi */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 4694fb: mov dword ptr [esp + 0x14], 0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x43c80000u;	/* 469503: mov dword ptr [esp + 0x18], 0x43c80000 */
	M32((DWORD)(m->esp + 0x1cu)) = 0xc6c4597cu;	/* 46950b: mov dword ptr [esp + 0x1c], 0xc6c4597c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 469513: push ebp */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 469514: push 0 */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 469516: lea ecx, [esp + 0x1c] */
	m->esp -= 4; M32(m->esp) = 0x46951fu; native_call(m, 0x4677c0u);	/* 46951a: call 0x4677c0 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 46951f: lea edx, [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469523: push edx */
	m->esp -= 4; M32(m->esp) = 0x469526u; native_call(m, m->ebx);	/* 469524: call ebx */
	m->esp -= 4; M32(m->esp) = 0x46952cu; native_call(m, M32(0x4a9220u));	/* 469526: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 46952c: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esi, b_ = 0xe10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469530: add esi, 0xe10 */
	{ DWORD a_ = m->esi, b_ = 0xfd20u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469536: cmp esi, 0xfd20 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 46953c: mov dword ptr [esp + 0x10], eax */
	if (m->sf != m->of) goto L_4693e5;	/* 469540: jl 0x4693e5 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 469546: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x469551u; native_call(m, M32(0x4a922cu));	/* 46954b: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 469551: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 469556: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46955du; native_call(m, 0x4685f0u);	/* 469558: call 0x4685f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46955d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 469562: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 469564: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 469569: push 0x3f800000 */
	m->esi = 0x2u;	/* 46956e: mov esi, 2 */
	m->esp -= 4; M32(m->esp) = 0x469578u; native_call(m, 0x44ad30u);	/* 469573: call 0x44ad30 */
	m->ecx = M32((DWORD)(0xa0ea8cu));	/* 469578: mov ecx, dword ptr [0xa0ea8c] */
	m->edi = 0x1u;	/* 46957e: mov edi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469583: add esp, 0x18 */
	m->eax = M32((DWORD)(m->ecx + 0x8u));	/* 469586: mov eax, dword ptr [ecx + 8] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469589: cmp eax, edi */
	if (m->zf) goto L_469592;	/* 46958b: je 0x469592 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46958d: cmp eax, 3 */
	if (!m->zf) goto L_4695c1;	/* 469590: jne 0x4695c1 */
L_469592:
	{ DWORD v_ = 0x67fb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 469592: push 0x67fb44 */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 469597: lea edx, [esp + 0x34] */
	{ DWORD v_ = 0x4c5330u; m->esp -= 4; M32(m->esp) = v_; }	/* 46959b: push 0x4c5330 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4695a0: push edx */
	m->esp -= 4; M32(m->esp) = 0x4695a6u; native_call(m, 0x49e9ddu);	/* 4695a1: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4695a6: lea eax, [esp + 0x3c] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4695aa: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4695ac: push eax */
	{ DWORD v_ = 0x66u; m->esp -= 4; M32(m->esp) = v_; }	/* 4695ad: push 0x66 */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 4695af: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x4695b9u; native_call(m, 0x44ad60u);	/* 4695b4: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4695b9: add esp, 0x1c */
	m->esi = 0x4u;	/* 4695bc: mov esi, 4 */
L_4695c1:
	m->ecx = M32((DWORD)(0xa0ea8cu));	/* 4695c1: mov ecx, dword ptr [0xa0ea8c] */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x1f1cb0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4695c7: cmp dword ptr [ecx + 0x1f1cb0], edi */
	if (!m->zf) goto L_4695e3;	/* 4695cd: jne 0x4695e3 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 4695cf: lea edx, [esp + 0x30] */
	{ DWORD v_ = 0x4c531cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4695d3: push 0x4c531c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4695d8: push edx */
	m->esp -= 4; M32(m->esp) = 0x4695deu; native_call(m, 0x49e9ddu);	/* 4695d9: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4695de: add esp, 8 */
	goto L_469603;	/* 4695e1: jmp 0x469603 */
L_4695e3:
	m->eax = M32((DWORD)(0x9dad94u));	/* 4695e3: mov eax, dword ptr [0x9dad94] */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 4695e8: lea ecx, [esp + 0x30] */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4695ec: shl eax, 5 */
	{ DWORD a_ = m->eax, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4695ef: add eax, 0x907b30 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4695f4: push eax */
	{ DWORD v_ = 0x4c5310u; m->esp -= 4; M32(m->esp) = v_; }	/* 4695f5: push 0x4c5310 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4695fa: push ecx */
	m->esp -= 4; M32(m->esp) = 0x469600u; native_call(m, 0x49e9ddu);	/* 4695fb: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469600: add esp, 0xc */
L_469603:
	m->eax = m->esi;	/* 469603: mov eax, esi */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 469605: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 469609: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46960c: add eax, 0x46 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46960f: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469611: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469612: push eax */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 469613: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x46961du; native_call(m, 0x44ad60u);	/* 469618: call 0x44ad60 */
	m->eax = M32((DWORD)(0xa0ea8cu));	/* 46961d: mov eax, dword ptr [0xa0ea8c] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469622: add esp, 0x10 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469625: add esi, 2 */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x1f1cb0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469628: cmp dword ptr [eax + 0x1f1cb0], edi */
	if (!m->zf) goto L_469644;	/* 46962e: jne 0x469644 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 469630: lea eax, [esp + 0x30] */
	{ DWORD v_ = 0x4c52f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 469634: push 0x4c52f8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469639: push eax */
	m->esp -= 4; M32(m->esp) = 0x46963fu; native_call(m, 0x49e9ddu);	/* 46963a: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46963f: add esp, 8 */
	goto L_469666;	/* 469642: jmp 0x469666 */
L_469644:
	m->ecx = M32((DWORD)(m->eax + 0x22e7180u));	/* 469644: mov ecx, dword ptr [eax + 0x22e7180] */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 46964a: lea edx, [esp + 0x30] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46964e: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = 0x4c7030u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 469651: add ecx, 0x4c7030 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469657: push ecx */
	{ DWORD v_ = 0x4c52e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 469658: push 0x4c52e8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46965d: push edx */
	m->esp -= 4; M32(m->esp) = 0x469663u; native_call(m, 0x49e9ddu);	/* 46965e: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469663: add esp, 0xc */
L_469666:
	m->eax = m->esi;	/* 469666: mov eax, esi */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 469668: lea ecx, [esp + 0x30] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46966c: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46966f: add eax, 0x46 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 469672: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469674: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469675: push eax */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 469676: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x469680u; native_call(m, 0x44ad60u);	/* 46967b: call 0x44ad60 */
	m->edx = M32((DWORD)(0x4df8e8u));	/* 469680: mov edx, dword ptr [0x4df8e8] */
	m->eax = (DWORD)(m->esp + 0x40u);	/* 469686: lea eax, [esp + 0x40] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46968a: push edx */
	{ DWORD v_ = 0x4c52d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46968b: push 0x4c52d8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469690: push eax */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469691: add esi, 2 */
	m->esp -= 4; M32(m->esp) = 0x469699u; native_call(m, 0x49e9ddu);	/* 469694: call 0x49e9dd */
	m->eax = m->esi;	/* 469699: mov eax, esi */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 46969b: lea ecx, [esp + 0x4c] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46969f: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4696a2: add eax, 0x46 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696a5: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4696a7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4696a8: push eax */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696a9: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x4696b3u; native_call(m, 0x44ad60u);	/* 4696ae: call 0x44ad60 */
	m->edx = M32((DWORD)(0x76d408u));	/* 4696b3: mov edx, dword ptr [0x76d408] */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 4696b9: lea eax, [esp + 0x5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4696bd: push edx */
	{ DWORD v_ = 0x4c52c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696be: push 0x4c52c8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4696c3: push eax */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4696c4: add esi, 2 */
	m->esp -= 4; M32(m->esp) = 0x4696ccu; native_call(m, 0x49e9ddu);	/* 4696c7: call 0x49e9dd */
	m->eax = m->esi;	/* 4696cc: mov eax, esi */
	m->ecx = (DWORD)(m->esp + 0x68u);	/* 4696ce: lea ecx, [esp + 0x68] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4696d2: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4696d5: add eax, 0x46 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696d8: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4696da: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4696db: push eax */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696dc: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x4696e6u; native_call(m, 0x44ad60u);	/* 4696e1: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4696e6: add esp, 0x48 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696e9: push 0x3f800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696ee: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696f3: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4696f8: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x469702u; native_call(m, 0x44ad30u);	/* 4696fd: call 0x44ad30 */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 469702: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = 0x76u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 469705: add esi, 0x76 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 469708: push 0x10 */
	{ DWORD v_ = 0xa0e988u; m->esp -= 4; M32(m->esp) = v_; }	/* 46970a: push 0xa0e988 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46970f: push esi */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 469710: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x46971au; native_call(m, 0x44ad60u);	/* 469715: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46971a: add esp, 0x20 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46971d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46971e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46971f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 469720: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x120u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469721: add esp, 0x120 */
	m->esp += 4 + 0; return;	/* 469727: ret  */
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
