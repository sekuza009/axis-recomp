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

static void lift_41b400(X86 *m);

/* armc_41b400 (0x41b400), lifted by tools/lift.py */
static void lift_41b400(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b400: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b401: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41b402: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41b403: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41b404: push edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b405: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41b410u; native_call(m, M32(0x4a9224u));	/* 41b40a: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a920cu));	/* 41b410: mov ebx, dword ptr [0x4a920c] */
	m->ebp = M32((DWORD)(0x4a9210u));	/* 41b416: mov ebp, dword ptr [0x4a9210] */
	m->edi = 0x1u;	/* 41b41c: mov edi, 1 */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 41b421: mov dword ptr [esp + 0x10], edi */
L_41b425:
	m->esp -= 4; M32(m->esp) = 0x41b42au; native_call(m, 0x41f050u);	/* 41b425: call 0x41f050 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41b42a: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41b42f: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41b434: push 0x3f4ccccd */
	m->esp -= 4; M32(m->esp) = 0x41b43fu; native_call(m, M32(0x4a9200u));	/* 41b439: call dword ptr [0x4a9200] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b43f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b444: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b449: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b44e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41b459u; native_call(m, M32(0x4a9228u));	/* 41b453: call dword ptr [0x4a9228] */
	m->eax = (DWORD)(m->edi*4 + 0x0u);	/* 41b459: lea eax, [edi*4] */
	m->ecx = 0x9da470u;	/* 41b460: mov ecx, 0x9da470 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 41b465: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 41b467: mov eax, dword ptr [ecx] */
	m->edx = m->eax;	/* 41b469: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41b46b: and edx, 0x800001ff */
	if (!m->sf) goto L_41b47b;	/* 41b471: jns 0x41b47b */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 41b473: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41b474: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 41b47a: inc edx */
L_41b47b:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b47b: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 41b47c: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 41b482: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41b483: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41b489: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41b48b: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 41b48e: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x41b497u; native_call(m, 0x4566c0u);	/* 41b492: call 0x4566c0 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b497: cmp edi, 2 */
	if (!m->zf) goto L_41b4df;	/* 41b49a: jne 0x41b4df */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0708u)));	/* 41b49c: fld dword ptr [0x4b0708] */
	m->edx = M32((DWORD)(0x4b0708u));	/* 41b4a2: mov edx, dword ptr [0x4b0708] */
	ST(0) = -ST(0);	/* 41b4a8: fchs  */
	MF((DWORD)(0x4dc600u)) = (float)ST(0);	/* 41b4aa: fst dword ptr [0x4dc600] */
	MF((DWORD)(0x4dc628u)) = (float)ST(0);	/* 41b4b0: fst dword ptr [0x4dc628] */
	MF((DWORD)(0x4dc630u)) = (float)ST(0);	/* 41b4b6: fst dword ptr [0x4dc630] */
	MF((DWORD)(0x4dc638u)) = (float)ST(0); FPOP();	/* 41b4bc: fstp dword ptr [0x4dc638] */
	m->eax = m->edx;	/* 41b4c2: mov eax, edx */
	m->ecx = m->edx;	/* 41b4c4: mov ecx, edx */
	M32((DWORD)(0x4dc608u)) = m->edx;	/* 41b4c6: mov dword ptr [0x4dc608], edx */
	M32((DWORD)(0x4dc610u)) = m->eax;	/* 41b4cc: mov dword ptr [0x4dc610], eax */
	M32((DWORD)(0x4dc618u)) = m->ecx;	/* 41b4d1: mov dword ptr [0x4dc618], ecx */
	M32((DWORD)(0x4dc620u)) = m->edx;	/* 41b4d7: mov dword ptr [0x4dc620], edx */
	goto L_41b523;	/* 41b4dd: jmp 0x41b523 */
L_41b4df:
	{ DWORD a_ = m->edi, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b4df: cmp edi, 3 */
	if (!m->zf) goto L_41b523;	/* 41b4e2: jne 0x41b523 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0704u)));	/* 41b4e4: fld dword ptr [0x4b0704] */
	m->eax = M32((DWORD)(0x4b0704u));	/* 41b4ea: mov eax, dword ptr [0x4b0704] */
	ST(0) = -ST(0);	/* 41b4ef: fchs  */
	MF((DWORD)(0x4dc658u)) = (float)ST(0);	/* 41b4f1: fst dword ptr [0x4dc658] */
	MF((DWORD)(0x4dc680u)) = (float)ST(0);	/* 41b4f7: fst dword ptr [0x4dc680] */
	MF((DWORD)(0x4dc688u)) = (float)ST(0);	/* 41b4fd: fst dword ptr [0x4dc688] */
	MF((DWORD)(0x4dc690u)) = (float)ST(0); FPOP();	/* 41b503: fstp dword ptr [0x4dc690] */
	m->ecx = m->eax;	/* 41b509: mov ecx, eax */
	m->edx = m->eax;	/* 41b50b: mov edx, eax */
	M32((DWORD)(0x4dc660u)) = m->eax;	/* 41b50d: mov dword ptr [0x4dc660], eax */
	M32((DWORD)(0x4dc668u)) = m->ecx;	/* 41b512: mov dword ptr [0x4dc668], ecx */
	M32((DWORD)(0x4dc670u)) = m->edx;	/* 41b518: mov dword ptr [0x4dc670], edx */
	M32((DWORD)(0x4dc678u)) = m->eax;	/* 41b51e: mov dword ptr [0x4dc678], eax */
L_41b523:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 41b523: fild dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(0x4dcfc8u));	/* 41b527: mov edx, dword ptr [0x4dcfc8] */
	m->ecx = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 41b52d: lea ecx, [edi + edi*4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b530: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b531: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 41b532: fmul dword ptr [0x4a93d0] */
	m->esi = (DWORD)(m->edi + m->ecx*2 + 0x0u);	/* 41b538: lea esi, [edi + ecx*2] */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 41b53b: shl esi, 3 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dcfc4u));	/* 41b53e: fadd dword ptr [0x4dcfc4] */
	m->eax = M32((DWORD)(m->esi + 0x4dc590u));	/* 41b544: mov eax, dword ptr [esi + 0x4dc590] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 41b54a: fadd dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94b4u));	/* 41b550: fsub dword ptr [0x4a94b4] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41b556: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b559: push eax */
	m->esp -= 4; M32(m->esp) = 0x41b560u; native_call(m, M32(0x4a9214u));	/* 41b55a: call dword ptr [0x4a9214] */
	m->esp -= 4; M32(m->esp) = 0x41b566u; native_call(m, M32(0x4a9204u));	/* 41b560: call dword ptr [0x4a9204] */
	m->ecx = M32((DWORD)(m->esi + 0x4dc5a0u));	/* 41b566: mov ecx, dword ptr [esi + 0x4dc5a0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b56c: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b56e: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b56f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41b576u; native_call(m, 0x41ef20u);	/* 41b571: call 0x41ef20 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b576: add esp, 0xc */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b579: push 7 */
	m->esp -= 4; M32(m->esp) = 0x41b581u; native_call(m, M32(0x4a921cu));	/* 41b57b: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b581: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b586: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41b58au; native_call(m, m->ebx);	/* 41b588: call ebx */
	m->edx = M32((DWORD)(m->esi + 0x4dc558u));	/* 41b58a: mov edx, dword ptr [esi + 0x4dc558] */
	m->eax = M32((DWORD)(m->esi + 0x4dc554u));	/* 41b590: mov eax, dword ptr [esi + 0x4dc554] */
	m->ecx = M32((DWORD)(m->esi + 0x4dc550u));	/* 41b596: mov ecx, dword ptr [esi + 0x4dc550] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b59c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b59d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b59e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41b5a1u; native_call(m, m->ebp);	/* 41b59f: call ebp */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5a1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5a6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41b5adu; native_call(m, m->ebx);	/* 41b5ab: call ebx */
	m->edx = M32((DWORD)(m->esi + 0x4dc568u));	/* 41b5ad: mov edx, dword ptr [esi + 0x4dc568] */
	m->eax = M32((DWORD)(m->esi + 0x4dc564u));	/* 41b5b3: mov eax, dword ptr [esi + 0x4dc564] */
	m->ecx = M32((DWORD)(m->esi + 0x4dc560u));	/* 41b5b9: mov ecx, dword ptr [esi + 0x4dc560] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5bf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5c0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5c1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41b5c4u; native_call(m, m->ebp);	/* 41b5c2: call ebp */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5c4: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5c6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41b5cdu; native_call(m, m->ebx);	/* 41b5cb: call ebx */
	m->edx = M32((DWORD)(m->esi + 0x4dc578u));	/* 41b5cd: mov edx, dword ptr [esi + 0x4dc578] */
	m->eax = M32((DWORD)(m->esi + 0x4dc574u));	/* 41b5d3: mov eax, dword ptr [esi + 0x4dc574] */
	m->ecx = M32((DWORD)(m->esi + 0x4dc570u));	/* 41b5d9: mov ecx, dword ptr [esi + 0x4dc570] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5df: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5e0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5e1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41b5e4u; native_call(m, m->ebp);	/* 41b5e2: call ebp */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5e4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5e6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41b5eau; native_call(m, m->ebx);	/* 41b5e8: call ebx */
	m->edx = M32((DWORD)(m->esi + 0x4dc588u));	/* 41b5ea: mov edx, dword ptr [esi + 0x4dc588] */
	m->eax = M32((DWORD)(m->esi + 0x4dc584u));	/* 41b5f0: mov eax, dword ptr [esi + 0x4dc584] */
	m->ecx = M32((DWORD)(m->esi + 0x4dc580u));	/* 41b5f6: mov ecx, dword ptr [esi + 0x4dc580] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5fc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5fd: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41b5fe: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41b601u; native_call(m, m->ebp);	/* 41b5ff: call ebp */
	m->esp -= 4; M32(m->esp) = 0x41b607u; native_call(m, M32(0x4a9220u));	/* 41b601: call dword ptr [0x4a9220] */
	m->esp -= 4; M32(m->esp) = 0x41b60du; native_call(m, M32(0x4a9258u));	/* 41b607: call dword ptr [0x4a9258] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41b60d: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4dc5a4u));	/* 41b613: fmul dword ptr [esi + 0x4dc5a4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4dc5a0u));	/* 41b619: fadd dword ptr [esi + 0x4dc5a0] */
	MF((DWORD)(m->esi + 0x4dc5a0u)) = (float)ST(0);	/* 41b61f: fst dword ptr [esi + 0x4dc5a0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9460u)); FPOP();	/* 41b625: fcomp dword ptr [0x4a9460] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41b62b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41b62d: test ah, 0x41 */
	if (!m->zf) goto L_41b63c;	/* 41b630: jne 0x41b63c */
	M32((DWORD)(m->esi + 0x4dc5a0u)) = 0xc3b40000u;	/* 41b632: mov dword ptr [esi + 0x4dc5a0], 0xc3b40000 */
L_41b63c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4dc5a0u)));	/* 41b63c: fld dword ptr [esi + 0x4dc5a0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94b0u)); FPOP();	/* 41b642: fcomp dword ptr [0x4a94b0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41b648: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41b64a: test ah, 1 */
	if (m->zf) goto L_41b659;	/* 41b64d: je 0x41b659 */
	M32((DWORD)(m->esi + 0x4dc5a0u)) = 0x43b40000u;	/* 41b64f: mov dword ptr [esi + 0x4dc5a0], 0x43b40000 */
L_41b659:
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 41b659: inc edi */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b65a: cmp edi, 6 */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 41b65d: mov dword ptr [esp + 0x10], edi */
	if (m->sf != m->of) goto L_41b425;	/* 41b661: jl 0x41b425 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b070cu)));	/* 41b667: fld dword ptr [0x4b070c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b0704u));	/* 41b66d: fadd dword ptr [0x4b0704] */
	m->edi = M32(m->esp); m->esp += 4;	/* 41b673: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41b674: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41b675: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41b676: pop ebx */
	MF((DWORD)(0x4b0704u)) = (float)ST(0);	/* 41b677: fst dword ptr [0x4b0704] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94acu)); FPOP();	/* 41b67d: fcomp dword ptr [0x4a94ac] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41b683: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41b685: test ah, 1 */
	if (!m->zf) goto L_41b69c;	/* 41b688: jne 0x41b69c */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41b68a: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94a8u));	/* 41b690: fmul dword ptr [0x4a94a8] */
	MF((DWORD)(0x4b070cu)) = (float)ST(0); FPOP();	/* 41b696: fstp dword ptr [0x4b070c] */
L_41b69c:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0704u)));	/* 41b69c: fld dword ptr [0x4b0704] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 41b6a2: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41b6a8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41b6aa: test ah, 0x41 */
	if (m->zf) goto L_41b6bd;	/* 41b6ad: je 0x41b6bd */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41b6af: fld dword ptr [0x4b071c] */
	ST(0) = ST(0) + ST(0);	/* 41b6b5: fadd st(0), st(0) */
	MF((DWORD)(0x4b070cu)) = (float)ST(0); FPOP();	/* 41b6b7: fstp dword ptr [0x4b070c] */
L_41b6bd:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b0710u)));	/* 41b6bd: fld dword ptr [0x4b0710] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b0708u));	/* 41b6c3: fadd dword ptr [0x4b0708] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94acu));	/* 41b6c9: fcom dword ptr [0x4a94ac] */
	MF((DWORD)(0x4b0708u)) = (float)ST(0);	/* 41b6cf: fst dword ptr [0x4b0708] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41b6d5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41b6d7: test ah, 1 */
	if (!m->zf) goto L_41b6ee;	/* 41b6da: jne 0x41b6ee */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41b6dc: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94a8u));	/* 41b6e2: fmul dword ptr [0x4a94a8] */
	MF((DWORD)(0x4b0710u)) = (float)ST(0); FPOP();	/* 41b6e8: fstp dword ptr [0x4b0710] */
L_41b6ee:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 41b6ee: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41b6f4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41b6f6: test ah, 0x41 */
	if (m->zf) goto L_41b709;	/* 41b6f9: je 0x41b709 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41b6fb: fld dword ptr [0x4b071c] */
	ST(0) = ST(0) + ST(0);	/* 41b701: fadd st(0), st(0) */
	MF((DWORD)(0x4b0710u)) = (float)ST(0); FPOP();	/* 41b703: fstp dword ptr [0x4b0710] */
L_41b709:
	m->ecx = M32(m->esp); m->esp += 4;	/* 41b709: pop ecx */
	m->esp += 4 + 0; return;	/* 41b70a: ret  */
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
