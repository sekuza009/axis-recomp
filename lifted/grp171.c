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

static void lift_4913a0(X86 *m);

/* hud_drawPlayerMarkers (0x4913a0), lifted by tools/lift.py */
static void lift_4913a0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4913a0: sub esp, 0x128 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4913a6: push ebx */
	m->ebx = M32((DWORD)(0x4a920cu));	/* 4913a7: mov ebx, dword ptr [0x4a920c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4913ad: push ebp */
	m->ebp = M32((DWORD)(0x4a91f4u));	/* 4913ae: mov ebp, dword ptr [0x4a91f4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4913b4: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4913b5: xor eax, eax */
	m->edx = (DWORD)(m->ecx + 0x2342936u);	/* 4913b7: lea edx, [ecx + 0x2342936] */
	m->esi = (DWORD)(m->ecx + 0x1ed5250u);	/* 4913bd: lea esi, [ecx + 0x1ed5250] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4913c3: push edi */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 4913c4: mov dword ptr [esp + 0x1c], ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 4913c8: mov dword ptr [esp + 0x30], eax */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 4913cc: mov dword ptr [esp + 0x34], edx */
	M32((DWORD)(m->esp + 0x2cu)) = m->esi;	/* 4913d0: mov dword ptr [esp + 0x2c], esi */
L_4913d4:
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ecx + 0x234240du)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4913d4: cmp eax, dword ptr [ecx + 0x234240d] */
	if (m->zf) goto L_491f12;	/* 4913da: je 0x491f12 */
	m->edx = M32((DWORD)(m->esi + 0xffff796cu));	/* 4913e0: mov edx, dword ptr [esi - 0x8694] */
	m->eax = 0x1u;	/* 4913e6: mov eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4913eb: cmp edx, eax */
	if (!m->zf) goto L_491f12;	/* 4913ed: jne 0x491f12 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x0u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4913f3: cmp dword ptr [esi], eax */
	if (!m->zf) goto L_491f12;	/* 4913f5: jne 0x491f12 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xffff7cf8u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4913fb: cmp dword ptr [esi - 0x8308], eax */
	if (!m->zf) goto L_49156c;	/* 491401: jne 0x49156c */
	m->esp -= 4; M32(m->esp) = 0x49140cu; native_call(m, 0x4685b0u);	/* 491407: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 49140c: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491410: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 491414: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 49141a: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491420: call 0x49ec14 */
	m->edi = m->eax;	/* 491425: mov edi, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 491427: mov dword ptr [esp + 0x14], edi */
	m->esp -= 4; M32(m->esp) = 0x491430u; native_call(m, 0x4685c0u);	/* 49142b: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 491430: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491434: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 491438: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 49143e: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491444: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffdcu)));	/* 491449: fld dword ptr [esi - 0x24] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 49144c: mov dword ptr [esp + 0x18], eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491450: call 0x49ec14 */
	m->ecx = m->eax;	/* 491455: mov ecx, eax */
	m->eax = m->edi;	/* 491457: mov eax, edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 491459: cdq  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffecu)));	/* 49145a: fld dword ptr [esi - 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49145d: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49145f: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 491461: sub ecx, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 491463: mov dword ptr [esp + 0x20], ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491467: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 49146c: mov ecx, dword ptr [esp + 0x18] */
	m->edi = m->eax;	/* 491470: mov edi, eax */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 491472: push 0xde1 */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 491477: sub edi, ecx */
	m->esp -= 4; M32(m->esp) = 0x49147fu; native_call(m, M32(0x4a9224u));	/* 491479: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 49147f: mov eax, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->eax + 0xbc06acu));	/* 491483: mov eax, dword ptr [eax + 0xbc06ac] */
	m->ecx = m->eax;	/* 491489: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49148b: and ecx, 0x800001ff */
	if (!m->sf) goto L_49149b;	/* 491491: jns 0x49149b */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 491493: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491494: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49149a: inc ecx */
L_49149b:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49149b: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49149c: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4914a2: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4914a3: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4914a5: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4914ab: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4914ae: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4914b7u; native_call(m, 0x4566c0u);	/* 4914b2: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914b7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914bc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914c1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914c6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4914d1u; native_call(m, M32(0x4a9228u));	/* 4914cb: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914d1: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4914d9u; native_call(m, M32(0x4a921cu));	/* 4914d3: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914d9: push 0x3f400000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914de: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4914e2u; native_call(m, m->ebx);	/* 4914e0: call ebx */
	m->esp -= 4; M32(m->esp) = 0x4914e7u; native_call(m, 0x4685c0u);	/* 4914e2: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4914e7: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4914e9: push eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4914ea: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4914ee: push eax */
	m->esp -= 4; M32(m->esp) = 0x4914f1u; native_call(m, m->ebp);	/* 4914ef: call ebp */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914f1: push 0x3f400000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4914f6: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x4914fdu; native_call(m, m->ebx);	/* 4914fb: call ebx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4914fd: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 491501: mov edx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 491505: add ecx, edx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 491507: mov dword ptr [esp + 0x14], ecx */
	m->esp -= 4; M32(m->esp) = 0x491510u; native_call(m, 0x4685c0u);	/* 49150b: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491510: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491512: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 491513: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491517: push eax */
	m->esp -= 4; M32(m->esp) = 0x49151au; native_call(m, m->ebp);	/* 491518: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49151a: push 0x3f800000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49151f: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x491526u; native_call(m, m->ebx);	/* 491524: call ebx */
	m->esp -= 4; M32(m->esp) = 0x49152bu; native_call(m, 0x4685c0u);	/* 491526: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49152b: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49152f: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491533: sub eax, edi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491535: sub eax, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491537: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491538: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49153bu; native_call(m, m->ebp);	/* 491539: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49153b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491540: push 0 */
	m->esp -= 4; M32(m->esp) = 0x491544u; native_call(m, m->ebx);	/* 491542: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491549u; native_call(m, 0x4685c0u);	/* 491544: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 491549: mov edx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49154d: sub eax, edi */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esp + 0x18u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49154f: sub eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491553: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491554: push edx */
	m->esp -= 4; M32(m->esp) = 0x491557u; native_call(m, m->ebp);	/* 491555: call ebp */
	m->esp -= 4; M32(m->esp) = 0x49155du; native_call(m, M32(0x4a9220u));	/* 491557: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49155d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x491568u; native_call(m, M32(0x4a922cu));	/* 491562: call dword ptr [0x4a922c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 491568: mov ecx, dword ptr [esp + 0x1c] */
L_49156c:
	{ DWORD a_ = M32((DWORD)(m->esi + 0xffff7cfcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49156c: cmp dword ptr [esi - 0x8304], 1 */
	if (!m->zf) goto L_491744;	/* 491573: jne 0x491744 */
	m->esp -= 4; M32(m->esp) = 0x49157eu; native_call(m, 0x4685b0u);	/* 491579: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 49157e: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491582: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 491586: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 49158c: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491592: call 0x49ec14 */
	m->edi = m->eax;	/* 491597: mov edi, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 491599: mov dword ptr [esp + 0x14], edi */
	m->esp -= 4; M32(m->esp) = 0x4915a2u; native_call(m, 0x4685c0u);	/* 49159d: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4915a2: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4915a6: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 4915aa: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 4915b0: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4915b6: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffdcu)));	/* 4915bb: fld dword ptr [esi - 0x24] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4915be: mov dword ptr [esp + 0x18], eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4915c2: call 0x49ec14 */
	m->ecx = m->eax;	/* 4915c7: mov ecx, eax */
	m->eax = m->edi;	/* 4915c9: mov eax, edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4915cb: cdq  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffecu)));	/* 4915cc: fld dword ptr [esi - 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4915cf: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4915d1: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4915d3: sub ecx, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 4915d5: mov dword ptr [esp + 0x20], ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4915d9: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4915de: mov ecx, dword ptr [esp + 0x18] */
	m->edi = m->eax;	/* 4915e2: mov edi, eax */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4915e4: push 0xde1 */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4915e9: sub edi, ecx */
	m->esp -= 4; M32(m->esp) = 0x4915f1u; native_call(m, M32(0x4a9224u));	/* 4915eb: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4915f1: mov eax, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->eax + 0xbc06acu));	/* 4915f5: mov eax, dword ptr [eax + 0xbc06ac] */
	m->ecx = m->eax;	/* 4915fb: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4915fd: and ecx, 0x800001ff */
	if (!m->sf) goto L_49160d;	/* 491603: jns 0x49160d */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 491605: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491606: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49160c: inc ecx */
L_49160d:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49160d: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49160e: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491614: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491615: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 491617: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49161d: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 491620: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x491629u; native_call(m, 0x4566c0u);	/* 491624: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491629: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49162e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491633: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491638: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x491643u; native_call(m, M32(0x4a9228u));	/* 49163d: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 491643: push 7 */
	m->esp -= 4; M32(m->esp) = 0x49164bu; native_call(m, M32(0x4a921cu));	/* 491645: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(m->esi + 0xffff7938u));	/* 49164b: mov eax, dword ptr [esi - 0x86c8] */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491651: push 0x3f400000 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 491656: inc eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491657: push ecx */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 491658: shl eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 49165b: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 49165f: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 491663: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 491669: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x49166eu; native_call(m, m->ebx);	/* 49166c: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491673u; native_call(m, 0x4685c0u);	/* 49166e: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 491673: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491677: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491679: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49167a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49167du; native_call(m, m->ebp);	/* 49167b: call ebp */
	m->edx = M32((DWORD)(m->esi + 0xffff7938u));	/* 49167d: mov edx, dword ptr [esi - 0x86c8] */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491683: push 0x3f400000 */
	{ DWORD a_ = m->edx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 491688: add edx, 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49168b: push ecx */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49168c: shl edx, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 49168f: mov dword ptr [esp + 0x18], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 491693: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 491697: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 49169d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4916a2u; native_call(m, m->ebx);	/* 4916a0: call ebx */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4916a2: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4916a6: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4916aa: add eax, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4916ac: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x4916b5u; native_call(m, 0x4685c0u);	/* 4916b0: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4916b5: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4916b9: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4916bb: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4916bc: push edx */
	m->esp -= 4; M32(m->esp) = 0x4916bfu; native_call(m, m->ebp);	/* 4916bd: call ebp */
	m->eax = M32((DWORD)(m->esi + 0xffff7938u));	/* 4916bf: mov eax, dword ptr [esi - 0x86c8] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4916c5: push 0x3f800000 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4916ca: add eax, 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4916cd: push ecx */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4916ce: shl eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4916d1: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 4916d5: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4916d9: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4916df: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4916e4u; native_call(m, m->ebx);	/* 4916e2: call ebx */
	m->esp -= 4; M32(m->esp) = 0x4916e9u; native_call(m, 0x4685c0u);	/* 4916e4: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4916e9: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4916ed: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4916f1: sub eax, edi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4916f3: sub eax, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4916f5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4916f6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4916f9u; native_call(m, m->ebp);	/* 4916f7: call ebp */
	m->edx = M32((DWORD)(m->esi + 0xffff7938u));	/* 4916f9: mov edx, dword ptr [esi - 0x86c8] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4916ff: push 0x3f800000 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 491704: inc edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491705: push ecx */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 491706: shl edx, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 491709: mov dword ptr [esp + 0x18], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 49170d: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 491711: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 491717: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x49171cu; native_call(m, m->ebx);	/* 49171a: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491721u; native_call(m, 0x4685c0u);	/* 49171c: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491721: sub eax, edi */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esp + 0x18u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491723: sub eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491727: push eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 491728: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49172c: push eax */
	m->esp -= 4; M32(m->esp) = 0x49172fu; native_call(m, m->ebp);	/* 49172d: call ebp */
	m->esp -= 4; M32(m->esp) = 0x491735u; native_call(m, M32(0x4a9220u));	/* 49172f: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 491735: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x491740u; native_call(m, M32(0x4a922cu));	/* 49173a: call dword ptr [0x4a922c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 491740: mov ecx, dword ptr [esp + 0x1c] */
L_491744:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 491744: fld dword ptr [esi + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 491747: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49174d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49174f: test ah, 0x41 */
	if (m->zf) goto L_491768;	/* 491752: je 0x491768 */
	m->eax = M32((DWORD)(m->ecx + 0x233c9fcu));	/* 491754: mov eax, dword ptr [ecx + 0x233c9fc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49175a: test eax, eax */
	if (m->zf) goto L_491787;	/* 49175c: je 0x491787 */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x8u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49175e: cmp dword ptr [ecx + 8], 3 */
	if (!m->zf) goto L_491d39;	/* 491762: jne 0x491d39 */
L_491768:
	m->eax = M32((DWORD)(m->ecx + 0x233c9fcu));	/* 491768: mov eax, dword ptr [ecx + 0x233c9fc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49176e: test eax, eax */
	if (m->zf) goto L_491787;	/* 491770: je 0x491787 */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x8u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491772: cmp dword ptr [ecx + 8], 3 */
	if (m->zf) goto L_491787;	/* 491776: je 0x491787 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 491778: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9438u));	/* 49177b: fmul dword ptr [0x4a9438] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 491781: fstp dword ptr [esp + 0x28] */
	goto L_49178f;	/* 491785: jmp 0x49178f */
L_491787:
	M32((DWORD)(m->esp + 0x28u)) = 0x3f800000u;	/* 491787: mov dword ptr [esp + 0x28], 0x3f800000 */
L_49178f:
	m->eax = M32((DWORD)(m->ecx + 0x234240du));	/* 49178f: mov eax, dword ptr [ecx + 0x234240d] */
	m->edx = m->eax;	/* 491795: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 491797: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49179a: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49179c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49179f: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4917a1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4917a4: add edx, eax */
	m->eax = M32((DWORD)(m->esi + 0xffff7938u));	/* 4917a6: mov eax, dword ptr [esi - 0x86c8] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ecx + m->edx*8 + 0x1eccb88u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4917ac: cmp eax, dword ptr [ecx + edx*8 + 0x1eccb88] */
	if (!m->zf) goto L_491962;	/* 4917b3: jne 0x491962 */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x8u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4917b9: cmp dword ptr [ecx + 8], 3 */
	if (m->zf) goto L_491962;	/* 4917bd: je 0x491962 */
	m->eax = M32((DWORD)(m->ecx + 0x22e719cu));	/* 4917c3: mov eax, dword ptr [ecx + 0x22e719c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4917c9: test eax, eax */
	if (!m->zf) goto L_491962;	/* 4917cb: jne 0x491962 */
	m->esp -= 4; M32(m->esp) = 0x4917d6u; native_call(m, 0x4685b0u);	/* 4917d1: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4917d6: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4917da: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 4917de: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4a8u));	/* 4917e4: fdivr dword ptr [0x4aa4a8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4917ea: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4917ef: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x4917f8u; native_call(m, 0x4685c0u);	/* 4917f3: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4917f8: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4917fc: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 491800: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4a8u));	/* 491806: fdivr dword ptr [0x4aa4a8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49180c: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 491811: mov dword ptr [esp + 0x18], eax */
	m->esp -= 4; M32(m->esp) = 0x49181au; native_call(m, 0x4685c0u);	/* 491815: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 49181a: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 49181e: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 491822: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa43cu));	/* 491828: fdivr dword ptr [0x4aa43c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49182e: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffecu)));	/* 491833: fld dword ptr [esi - 0x14] */
	m->edi = m->eax;	/* 491836: mov edi, eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491838: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffdcu)));	/* 49183d: fld dword ptr [esi - 0x24] */
	m->ecx = m->edi;	/* 491840: mov ecx, edi */
	m->edi = m->eax;	/* 491842: mov edi, eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 491844: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 491848: sub edi, ecx */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49184a: sub edi, eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49184c: call 0x49ec14 */
	m->ecx = m->eax;	/* 491851: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 491853: mov eax, dword ptr [esp + 0x14] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 491857: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491858: sub eax, edx */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49185a: push 0xde1 */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49185f: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 491861: sub ecx, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 491863: mov dword ptr [esp + 0x24], ecx */
	m->esp -= 4; M32(m->esp) = 0x49186du; native_call(m, M32(0x4a9224u));	/* 491867: call dword ptr [0x4a9224] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 49186d: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->edx + 0xbc06a0u));	/* 491871: mov eax, dword ptr [edx + 0xbc06a0] */
	m->ecx = m->eax;	/* 491877: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491879: and ecx, 0x800001ff */
	if (!m->sf) goto L_491889;	/* 49187f: jns 0x491889 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 491881: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491882: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 491888: inc ecx */
L_491889:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 491889: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49188a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491890: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491891: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 491893: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 491899: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 49189c: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4918a5u; native_call(m, 0x4566c0u);	/* 4918a0: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 4918a5: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4918a9: push eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4918aa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4918af: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4918b4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4918bfu; native_call(m, M32(0x4a9228u));	/* 4918b9: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4918bf: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4918c7u; native_call(m, M32(0x4a921cu));	/* 4918c1: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4918c7: push 0x3f200000 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4918cc: push 0x3e000000 */
	m->esp -= 4; M32(m->esp) = 0x4918d3u; native_call(m, m->ebx);	/* 4918d1: call ebx */
	m->esp -= 4; M32(m->esp) = 0x4918d8u; native_call(m, 0x4685c0u);	/* 4918d3: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4918d8: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4918dc: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4918de: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4918df: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4918e2u; native_call(m, m->ebp);	/* 4918e0: call ebp */
	{ DWORD v_ = 0x3f200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4918e2: push 0x3f200000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4918e7: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x4918eeu; native_call(m, m->ebx);	/* 4918ec: call ebx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4918ee: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4918f2: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4918f6: add edx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 4918f8: mov dword ptr [esp + 0x14], edx */
	m->esp -= 4; M32(m->esp) = 0x491901u; native_call(m, 0x4685c0u);	/* 4918fc: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 491901: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491905: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491907: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491908: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49190bu; native_call(m, m->ebp);	/* 491909: call ebp */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49190b: push 0x3f400000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491910: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x491917u; native_call(m, m->ebx);	/* 491915: call ebx */
	m->esp -= 4; M32(m->esp) = 0x49191cu; native_call(m, 0x4685c0u);	/* 491917: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 49191c: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 491920: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491924: sub eax, edi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491926: sub eax, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491928: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491929: push edx */
	m->esp -= 4; M32(m->esp) = 0x49192cu; native_call(m, m->ebp);	/* 49192a: call ebp */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49192c: push 0x3f400000 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491931: push 0x3e000000 */
	m->esp -= 4; M32(m->esp) = 0x491938u; native_call(m, m->ebx);	/* 491936: call ebx */
	m->esp -= 4; M32(m->esp) = 0x49193du; native_call(m, 0x4685c0u);	/* 491938: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49193d: sub eax, edi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 49193f: mov edi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491943: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491945: push eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 491946: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49194a: push eax */
	m->esp -= 4; M32(m->esp) = 0x49194du; native_call(m, m->ebp);	/* 49194b: call ebp */
	m->esp -= 4; M32(m->esp) = 0x491953u; native_call(m, M32(0x4a9220u));	/* 49194d: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 491953: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x49195eu; native_call(m, M32(0x4a922cu));	/* 491958: call dword ptr [0x4a922c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 49195e: mov ecx, dword ptr [esp + 0x1c] */
L_491962:
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 491962: mov edx, dword ptr [esp + 0x34] */
	{ DWORD a_ = M32((DWORD)(m->edx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491966: cmp dword ptr [edx], 1 */
	if (!m->zf) goto L_491b00;	/* 491969: jne 0x491b00 */
	m->eax = M32((DWORD)(m->ecx + 0x22e719cu));	/* 49196f: mov eax, dword ptr [ecx + 0x22e719c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 491975: test eax, eax */
	if (!m->zf) goto L_491b00;	/* 491977: jne 0x491b00 */
	m->eax = M32((DWORD)(m->ecx + 0x22e71a0u));	/* 49197d: mov eax, dword ptr [ecx + 0x22e71a0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 491983: test eax, eax */
	if (!m->zf) goto L_491b00;	/* 491985: jne 0x491b00 */
	m->eax = M32((DWORD)(m->esi + 0xffff7904u));	/* 49198b: mov eax, dword ptr [esi - 0x86fc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 491991: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_491b00;	/* 491993: jle 0x491b00 */
	m->esp -= 4; M32(m->esp) = 0x49199eu; native_call(m, 0x4685b0u);	/* 491999: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 49199e: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4919a2: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 4919a6: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 4919ac: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4919b2: call 0x49ec14 */
	m->edi = m->eax;	/* 4919b7: mov edi, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 4919b9: mov dword ptr [esp + 0x14], edi */
	m->esp -= 4; M32(m->esp) = 0x4919c2u; native_call(m, 0x4685c0u);	/* 4919bd: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4919c2: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4919c6: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 4919ca: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 4919d0: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4919d6: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffdcu)));	/* 4919db: fld dword ptr [esi - 0x24] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4919de: mov dword ptr [esp + 0x18], eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4919e2: call 0x49ec14 */
	m->ecx = m->eax;	/* 4919e7: mov ecx, eax */
	m->eax = m->edi;	/* 4919e9: mov eax, edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4919eb: cdq  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffecu)));	/* 4919ec: fld dword ptr [esi - 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4919ef: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4919f1: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4919f3: sub ecx, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 4919f5: mov dword ptr [esp + 0x20], ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4919f9: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4919fe: mov ecx, dword ptr [esp + 0x18] */
	m->edi = m->eax;	/* 491a02: mov edi, eax */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a04: push 0xde1 */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 491a09: sub edi, ecx */
	m->esp -= 4; M32(m->esp) = 0x491a11u; native_call(m, M32(0x4a9224u));	/* 491a0b: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 491a11: mov eax, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->eax + 0xbc06a0u));	/* 491a15: mov eax, dword ptr [eax + 0xbc06a0] */
	m->ecx = m->eax;	/* 491a1b: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491a1d: and ecx, 0x800001ff */
	if (!m->sf) goto L_491a2d;	/* 491a23: jns 0x491a2d */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 491a25: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491a26: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 491a2c: inc ecx */
L_491a2d:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 491a2d: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 491a2e: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491a34: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491a35: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 491a37: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 491a3d: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 491a40: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x491a49u; native_call(m, 0x4566c0u);	/* 491a44: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 491a49: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491a4d: push eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a4e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a53: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a58: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x491a63u; native_call(m, M32(0x4a9228u));	/* 491a5d: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a63: push 7 */
	m->esp -= 4; M32(m->esp) = 0x491a6bu; native_call(m, M32(0x4a921cu));	/* 491a65: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a6b: push 0x3f400000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a70: push 0 */
	m->esp -= 4; M32(m->esp) = 0x491a74u; native_call(m, m->ebx);	/* 491a72: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491a79u; native_call(m, 0x4685c0u);	/* 491a74: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 491a79: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491a7d: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491a7f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491a80: push ecx */
	m->esp -= 4; M32(m->esp) = 0x491a83u; native_call(m, m->ebp);	/* 491a81: call ebp */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a83: push 0x3f400000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491a88: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x491a8fu; native_call(m, m->ebx);	/* 491a8d: call ebx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 491a8f: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 491a93: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 491a97: add edx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 491a99: mov dword ptr [esp + 0x14], edx */
	m->esp -= 4; M32(m->esp) = 0x491aa2u; native_call(m, 0x4685c0u);	/* 491a9d: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 491aa2: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491aa6: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491aa8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491aa9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x491aacu; native_call(m, m->ebp);	/* 491aaa: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491aac: push 0x3f800000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491ab1: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x491ab8u; native_call(m, m->ebx);	/* 491ab6: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491abdu; native_call(m, 0x4685c0u);	/* 491ab8: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 491abd: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 491ac1: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491ac5: sub eax, edi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491ac7: sub eax, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491ac9: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491aca: push edx */
	m->esp -= 4; M32(m->esp) = 0x491acdu; native_call(m, m->ebp);	/* 491acb: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491acd: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491ad2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x491ad6u; native_call(m, m->ebx);	/* 491ad4: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491adbu; native_call(m, 0x4685c0u);	/* 491ad6: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491adb: sub eax, edi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 491add: mov edi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491ae1: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491ae3: push eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 491ae4: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491ae8: push eax */
	m->esp -= 4; M32(m->esp) = 0x491aebu; native_call(m, m->ebp);	/* 491ae9: call ebp */
	m->esp -= 4; M32(m->esp) = 0x491af1u; native_call(m, M32(0x4a9220u));	/* 491aeb: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 491af1: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x491afcu; native_call(m, M32(0x4a922cu));	/* 491af6: call dword ptr [0x4a922c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 491afc: mov ecx, dword ptr [esp + 0x1c] */
L_491b00:
	m->eax = M32((DWORD)(m->ecx + 0x233c9fcu));	/* 491b00: mov eax, dword ptr [ecx + 0x233c9fc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 491b06: test eax, eax */
	if (!m->zf) goto L_491b26;	/* 491b08: jne 0x491b26 */
	m->eax = M32((DWORD)(m->ecx + 0x23424f2u));	/* 491b0a: mov eax, dword ptr [ecx + 0x23424f2] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 491b10: test eax, eax */
	if (m->sf != m->of) goto L_491b26;	/* 491b12: jl 0x491b26 */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 491b14: mov edx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->ecx + 0x2340c64u));	/* 491b18: mov eax, dword ptr [ecx + 0x2340c64] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491b1e: cmp edx, eax */
	if (m->zf) goto L_491d39;	/* 491b20: je 0x491d39 */
L_491b26:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x8u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491b26: cmp dword ptr [ecx + 8], 3 */
	if (!m->zf) goto L_491b3e;	/* 491b2a: jne 0x491b3e */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 491b2c: mov eax, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->ecx + 0x2340c64u));	/* 491b30: mov edx, dword ptr [ecx + 0x2340c64] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491b36: cmp eax, edx */
	if (m->zf) goto L_491d39;	/* 491b38: je 0x491d39 */
L_491b3e:
	m->eax = M32((DWORD)(m->ecx + 0x22e7184u));	/* 491b3e: mov eax, dword ptr [ecx + 0x22e7184] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 491b44: test eax, eax */
	if (!m->zf) goto L_491b59;	/* 491b46: jne 0x491b59 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 491b48: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491b4c: push ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b4d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b52: push 0x3f800000 */
	goto L_491b97;	/* 491b57: jmp 0x491b97 */
L_491b59:
	m->edx = M32((DWORD)(m->esi + 0xffff7938u));	/* 491b59: mov edx, dword ptr [esi - 0x86c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491b5f: push edx */
	m->esp -= 4; M32(m->esp) = 0x491b65u; native_call(m, 0x463740u);	/* 491b60: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491b65: sub eax, 0 */
	if (m->zf) goto L_491b8e;	/* 491b68: je 0x491b8e */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 491b6a: dec eax */
	if (m->zf) goto L_491b7e;	/* 491b6b: je 0x491b7e */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 491b6d: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491b71: push eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b72: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b77: push 0x3f800000 */
	goto L_491b97;	/* 491b7c: jmp 0x491b97 */
L_491b7e:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 491b7e: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491b82: push ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b83: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b88: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b8a: push 0 */
	goto L_491b9c;	/* 491b8c: jmp 0x491b9c */
L_491b8e:
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 491b8e: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491b92: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b93: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b95: push 0 */
L_491b97:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491b97: push 0x3f800000 */
L_491b9c:
	m->esp -= 4; M32(m->esp) = 0x491ba1u; native_call(m, 0x44ad30u);	/* 491b9c: call 0x44ad30 */
	m->edi = (DWORD)(m->esi + 0xffff78b8u);	/* 491ba1: lea edi, [esi - 0x8748] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491ba7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 491baa: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 491bac: add esp, 0x10 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 491baf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 491bb1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 491bb3: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 491bb5: lea edx, [esp + 0x38] */
	m->eax = m->ecx;	/* 491bb9: mov eax, ecx */
	m->esi = m->edi;	/* 491bbb: mov esi, edi */
	m->edi = m->edx;	/* 491bbd: mov edi, edx */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 491bbf: push 8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 491bc1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 491bc4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 491bc6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491bc8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 491bcb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 491bcd: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491bd1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x491bd7u; native_call(m, 0x4685b0u);	/* 491bd2: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 491bd7: mov dword ptr [esp + 0x18], eax */
	m->esi = M32((DWORD)(m->esp + 0x34u));	/* 491bdb: mov esi, dword ptr [esp + 0x34] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 491bdf: fild dword ptr [esp + 0x18] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 491be3: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffdcu));	/* 491be9: fmul dword ptr [esi - 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491bec: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491bf1: push eax */
	m->esp -= 4; M32(m->esp) = 0x491bf7u; native_call(m, 0x4685c0u);	/* 491bf2: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 491bf7: mov dword ptr [esp + 0x1c], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 491bfb: fild dword ptr [esp + 0x1c] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 491bff: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffecu));	/* 491c05: fmul dword ptr [esi - 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491c08: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491c0d: sub eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491c10: push eax */
	m->esp -= 4; M32(m->esp) = 0x491c16u; native_call(m, 0x4685b0u);	/* 491c11: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 491c16: mov dword ptr [esp + 0x20], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 491c1a: fild dword ptr [esp + 0x20] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 491c1e: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffdcu));	/* 491c24: fmul dword ptr [esi - 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491c27: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491c2c: push eax */
	m->esp -= 4; M32(m->esp) = 0x491c32u; native_call(m, 0x491c32u + M32(0x491c2eu));	/* 0x44ae10 unless the patch DLL retargets it */	/* 491c2d: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 491c32: add esp, 0x14 */
	m->esp -= 4; M32(m->esp) = 0x491c3au; native_call(m, 0x4685b0u);	/* 491c35: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 491c3a: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491c3e: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 491c42: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffdcu));	/* 491c48: fmul dword ptr [esi - 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491c4b: call 0x49ec14 */
	m->edx = m->eax;	/* 491c50: mov edx, eax */
	if (M8(0x491c52u) == 0x52 && M8(0x491c53u) == 0x8d && M8(0x491c54u) == 0x44 && M8(0x491c55u) == 0x24 && M8(0x491c56u) == 0x3c && M8(0x491c57u) == 0x50 && M8(0x491c58u) == 0xe8 && M8(0x491c5du) == 0x59 && M8(0x491c5eu) == 0x5a && M8(0x491c5fu) == 0x2b && M8(0x491c60u) == 0xd0 && M8(0x491c61u) == 0x90 && M8(0x491c62u) == 0x90 && M8(0x491c63u) == 0x90 && M8(0x491c64u) == 0x90 && M8(0x491c65u) == 0x90 && M8(0x491c66u) == 0x90) {	/* the patch DLL's block (21 bytes) */
		{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* patched 491c52: push edx */
		m->eax = (DWORD)(m->esp + 0x3cu);	/* patched 491c53: lea eax, [esp + 0x3c] */
		{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* patched 491c57: push eax */
		m->esp -= 4; M32(m->esp) = 0x491c5du; native_call(m, 0x491c5du + M32(0x491c59u));	/* 0x491c5d unless the patch DLL retargets it */	/* patched 491c58: call 0x491c5d */
		m->ecx = M32(m->esp); m->esp += 4;	/* patched 491c5d: pop ecx */
		m->edx = M32(m->esp); m->esp += 4;	/* patched 491c5e: pop edx */
		{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* patched 491c5f: sub edx, eax */
		;	/* patched 491c61: nop  */
		;	/* patched 491c62: nop  */
		;	/* patched 491c63: nop  */
		;	/* patched 491c64: nop  */
		;	/* patched 491c65: nop  */
		;	/* patched 491c66: nop  */
		goto L_491c67;
	}
	m->edi = (DWORD)(m->esp + 0x38u);	/* 491c52: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491c56: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 491c59: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 491c5b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 491c5d: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 491c5f: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 491c60: shr ecx, 1 */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 491c62: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 491c65: sub edx, ecx */
L_491c67:
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 491c67: mov dword ptr [esp + 0x14], edx */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 491c6b: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491c6f: push edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491c70: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491c75: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491c7a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x491c85u; native_call(m, M32(0x4a9228u));	/* 491c7f: call dword ptr [0x4a9228] */
	m->edi = M32((DWORD)(m->esp + 0x1cu));	/* 491c85: mov edi, dword ptr [esp + 0x1c] */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x233c9f0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491c89: cmp dword ptr [edi + 0x233c9f0], 1 */
	if (!m->zf) goto L_491cc9;	/* 491c90: jne 0x491cc9 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x14u)), b_ = 0x18u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esp + 0x14u)) = r_; }	/* 491c92: sub dword ptr [esp + 0x14], 0x18 */
	m->esp -= 4; M32(m->esp) = 0x491c9cu; native_call(m, 0x4685c0u);	/* 491c97: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 491c9c: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491ca0: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 491ca4: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffecu));	/* 491caa: fmul dword ptr [esi - 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491cad: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esi + 0xffff78fcu));	/* 491cb2: mov ecx, dword ptr [esi - 0x8704] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491cb8: sub eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491cbb: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 491cbc: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491cc0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491cc1: push ecx */
	m->ecx = m->edi;	/* 491cc2: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x491cc9u; native_call(m, 0x4922c0u);	/* 491cc4: call 0x4922c0 */
L_491cc9:
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 491cc9: mov eax, dword ptr [edi + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 491ccc: test eax, eax */
	if (!m->zf) goto L_491cdc;	/* 491cce: jne 0x491cdc */
	m->ecx = M32((DWORD)(m->esi + 0xffff792cu));	/* 491cd0: mov ecx, dword ptr [esi - 0x86d4] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 491cd6: mov dword ptr [esp + 0x18], ecx */
	goto L_491ce6;	/* 491cda: jmp 0x491ce6 */
L_491cdc:
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 491cdc: mov edx, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 491ce0: mov dword ptr [esp + 0x18], edx */
	m->ecx = m->edx;	/* 491ce4: mov ecx, edx */
L_491ce6:
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 491ce6: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 491ce9: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491cec: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 491cee: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 491cf1: lea ecx, [ecx + eax*8] */
	{ DWORD a_ = M32((DWORD)(m->edi + m->ecx*2 + 0x179d1f6u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491cf4: cmp dword ptr [edi + ecx*2 + 0x179d1f6], 1 */
	if (!m->zf) goto L_491d31;	/* 491cfc: jne 0x491d31 */
	m->esp -= 4; M32(m->esp) = 0x491d03u; native_call(m, 0x4685c0u);	/* 491cfe: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 491d03: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491d07: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 491d0b: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffecu));	/* 491d11: fmul dword ptr [esi - 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491d14: call 0x49ec14 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 491d19: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491d1d: sub eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491d20: push eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 491d21: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->edx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 491d25: add edx, -0x18 */
	m->ecx = m->edi;	/* 491d28: mov ecx, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491d2a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491d2b: push eax */
	m->esp -= 4; M32(m->esp) = 0x491d31u; native_call(m, 0x4924d0u);	/* 491d2c: call 0x4924d0 */
L_491d31:
	m->esi = M32((DWORD)(m->esp + 0x2cu));	/* 491d31: mov esi, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 491d35: mov ecx, dword ptr [esp + 0x1c] */
L_491d39:
	m->eax = M32((DWORD)(m->esi + 0xffff7c0cu));	/* 491d39: mov eax, dword ptr [esi - 0x83f4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 491d3f: test eax, eax */
	if (m->zf) goto L_491f12;	/* 491d41: je 0x491f12 */
	m->esp -= 4; M32(m->esp) = 0x491d4cu; native_call(m, 0x4685b0u);	/* 491d47: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 491d4c: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491d50: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 491d54: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 491d5a: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491d60: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 491d65: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x491d6eu; native_call(m, 0x4685c0u);	/* 491d69: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 491d6e: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491d72: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 491d76: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 491d7c: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491d82: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 491d87: mov dword ptr [esp + 0x18], eax */
	m->esp -= 4; M32(m->esp) = 0x491d90u; native_call(m, 0x4685c0u);	/* 491d8b: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 491d90: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491d94: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 491d98: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa43cu));	/* 491d9e: fdivr dword ptr [0x4aa43c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491da4: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffecu)));	/* 491da9: fld dword ptr [esi - 0x14] */
	m->edi = m->eax;	/* 491dac: mov edi, eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491dae: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffdcu)));	/* 491db3: fld dword ptr [esi - 0x24] */
	m->ecx = m->edi;	/* 491db6: mov ecx, edi */
	m->edi = m->eax;	/* 491db8: mov edi, eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 491dba: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 491dbe: sub edi, ecx */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 491dc0: sub edi, eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 491dc2: call 0x49ec14 */
	m->ecx = m->eax;	/* 491dc7: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 491dc9: mov eax, dword ptr [esp + 0x14] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 491dcd: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491dce: sub eax, edx */
	M32((DWORD)(m->esp + 0x2cu)) = 0xa0u;	/* 491dd0: mov dword ptr [esp + 0x2c], 0xa0 */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 491dd8: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 491dda: sub ecx, eax */
	m->eax = M32((DWORD)(m->esi + 0xffff7c0cu));	/* 491ddc: mov eax, dword ptr [esi - 0x83f4] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 491de2: dec eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 491de3: mov dword ptr [esp + 0x20], ecx */
	if (!m->zf) goto L_491df1;	/* 491de7: jne 0x491df1 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x80u;	/* 491de9: mov dword ptr [esp + 0x2c], 0x80 */
L_491df1:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 491df1: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x491dfcu; native_call(m, M32(0x4a9224u));	/* 491df6: call dword ptr [0x4a9224] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 491dfc: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->edx + 0xbc06a0u));	/* 491e00: mov eax, dword ptr [edx + 0xbc06a0] */
	m->ecx = m->eax;	/* 491e06: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491e08: and ecx, 0x800001ff */
	if (!m->sf) goto L_491e18;	/* 491e0e: jns 0x491e18 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 491e10: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 491e11: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 491e17: inc ecx */
L_491e18:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 491e18: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 491e19: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491e1f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491e20: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 491e22: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 491e28: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 491e2b: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x491e34u; native_call(m, 0x4566c0u);	/* 491e2f: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491e34: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491e39: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491e3e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491e43: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x491e4eu; native_call(m, M32(0x4a9228u));	/* 491e48: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 491e4e: push 7 */
	m->esp -= 4; M32(m->esp) = 0x491e56u; native_call(m, M32(0x4a921cu));	/* 491e50: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 491e56: fild dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 491e5a: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 491e60: fstp dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 491e64: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491e68: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491e69: push 0 */
	m->esp -= 4; M32(m->esp) = 0x491e6du; native_call(m, m->ebx);	/* 491e6b: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491e72u; native_call(m, 0x4685c0u);	/* 491e6d: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 491e72: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491e76: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491e78: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491e79: push ecx */
	m->esp -= 4; M32(m->esp) = 0x491e7cu; native_call(m, m->ebp);	/* 491e7a: call ebp */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 491e7c: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491e80: push edx */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491e81: push 0x3e000000 */
	m->esp -= 4; M32(m->esp) = 0x491e88u; native_call(m, m->ebx);	/* 491e86: call ebx */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 491e88: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 491e8c: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491e90: add eax, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 491e92: mov dword ptr [esp + 0x14], eax */
	m->esp -= 4; M32(m->esp) = 0x491e9bu; native_call(m, 0x4685c0u);	/* 491e96: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 491e9b: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491e9f: sub eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491ea1: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491ea2: push edx */
	m->esp -= 4; M32(m->esp) = 0x491ea5u; native_call(m, m->ebp);	/* 491ea3: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 491ea5: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491ea9: add eax, 0x20 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 491eac: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 491eb0: fild dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 491eb4: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 491eba: fstp dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 491ebe: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491ec2: push ecx */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 491ec3: push 0x3e000000 */
	m->esp -= 4; M32(m->esp) = 0x491ecau; native_call(m, m->ebx);	/* 491ec8: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491ecfu; native_call(m, 0x4685c0u);	/* 491eca: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 491ecf: mov edx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491ed3: sub eax, edi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491ed5: sub eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 491ed7: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491edb: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 491edc: push edx */
	m->esp -= 4; M32(m->esp) = 0x491edfu; native_call(m, m->ebp);	/* 491edd: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 491edf: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491ee3: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 491ee4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x491ee8u; native_call(m, m->ebx);	/* 491ee6: call ebx */
	m->esp -= 4; M32(m->esp) = 0x491eedu; native_call(m, 0x4685c0u);	/* 491ee8: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 491eed: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491ef1: sub eax, edi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 491ef3: sub eax, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 491ef5: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 491ef9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 491efa: push ecx */
	m->esp -= 4; M32(m->esp) = 0x491efdu; native_call(m, m->ebp);	/* 491efb: call ebp */
	m->esp -= 4; M32(m->esp) = 0x491f03u; native_call(m, M32(0x4a9220u));	/* 491efd: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 491f03: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x491f0eu; native_call(m, M32(0x4a922cu));	/* 491f08: call dword ptr [0x4a922c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 491f0e: mov ecx, dword ptr [esp + 0x1c] */
L_491f12:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 491f12: mov eax, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 491f16: mov edx, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 491f1a: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 491f1b: add edx, 4 */
	{ DWORD a_ = m->esi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 491f1e: add esi, 0x8888 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491f24: cmp eax, 0x10 */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 491f27: mov dword ptr [esp + 0x30], eax */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 491f2b: mov dword ptr [esp + 0x34], edx */
	M32((DWORD)(m->esp + 0x2cu)) = m->esi;	/* 491f2f: mov dword ptr [esp + 0x2c], esi */
	if (m->sf != m->of) goto L_4913d4;	/* 491f33: jl 0x4913d4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 491f39: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 491f3a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 491f3b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 491f3c: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 491f3d: add esp, 0x128 */
	m->esp += 4 + 0; return;	/* 491f43: ret  */
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
