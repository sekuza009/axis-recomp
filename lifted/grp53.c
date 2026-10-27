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

static void lift_495ed0(X86 *m);

/* hud_495ed0 (0x495ed0), lifted by tools/lift.py */
static void lift_495ed0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xa0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495ed0: sub esp, 0xa0 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xa4u)));	/* 495ed6: fild dword ptr [esp + 0xa4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495edd: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 495ede: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 495edf: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495ee0: push edi */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 495ee1: fstp dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 495ee5: mov dword ptr [esp + 0x18], ecx */
	m->esp -= 4; M32(m->esp) = 0x495eeeu; native_call(m, 0x4685b0u);	/* 495ee9: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 495eee: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 495ef2: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 495ef6: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 495efc: fdivr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 495f00: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xb8u)));	/* 495f05: fild dword ptr [esp + 0xb8] */
	m->ebx = m->eax;	/* 495f0c: mov ebx, eax */
	M32((DWORD)(m->esp + 0xb4u)) = m->ebx;	/* 495f0e: mov dword ptr [esp + 0xb4], ebx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 495f15: fstp dword ptr [esp + 0x14] */
	m->esp -= 4; M32(m->esp) = 0x495f1eu; native_call(m, 0x4685c0u);	/* 495f19: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 495f1e: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 495f22: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 495f26: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 495f2c: fdivr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 495f30: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xbcu)));	/* 495f35: fild dword ptr [esp + 0xbc] */
	m->ebp = m->eax;	/* 495f3c: mov ebp, eax */
	M32((DWORD)(m->esp + 0xb8u)) = m->ebp;	/* 495f3e: mov dword ptr [esp + 0xb8], ebp */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 495f45: fstp dword ptr [esp + 0x14] */
	m->esp -= 4; M32(m->esp) = 0x495f4eu; native_call(m, 0x4685b0u);	/* 495f49: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 495f4e: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 495f52: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 495f56: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 495f5c: fdivr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 495f60: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xc0u)));	/* 495f65: fild dword ptr [esp + 0xc0] */
	M32((DWORD)(m->esp + 0xbcu)) = m->eax;	/* 495f6c: mov dword ptr [esp + 0xbc], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 495f73: fstp dword ptr [esp + 0x14] */
	m->esp -= 4; M32(m->esp) = 0x495f7cu; native_call(m, 0x4685c0u);	/* 495f77: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 495f7c: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 495f80: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 495f84: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 495f8a: fdivr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 495f8e: call 0x49ec14 */
	M32((DWORD)(m->esp + 0xc0u)) = m->eax;	/* 495f93: mov dword ptr [esp + 0xc0], eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 495f9a: xor edi, edi */
	m->esi = (DWORD)(m->esp + 0x28u);	/* 495f9c: lea esi, [esp + 0x28] */
L_495fa0:
	m->eax = m->edi;	/* 495fa0: mov eax, edi */
	m->ecx = 0x3u;	/* 495fa2: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 495fa7: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 495fa8: idiv ecx */
	{ DWORD a_ = m->edx, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 495faa: sub edx, 0 */
	if (m->zf) goto L_495ff6;	/* 495fad: je 0x495ff6 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 495faf: dec edx */
	if (m->zf) goto L_495fe8;	/* 495fb0: je 0x495fe8 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 495fb2: dec edx */
	if (!m->zf) goto L_496028;	/* 495fb3: jne 0x496028 */
	m->edx = M32((DWORD)(m->esp + 0xbcu));	/* 495fb5: mov edx, dword ptr [esp + 0xbc] */
	M32((DWORD)(m->esi + 0xfffffff8u)) = m->edx;	/* 495fbc: mov dword ptr [esi - 8], edx */
	m->esp -= 4; M32(m->esp) = 0x495fc4u; native_call(m, 0x4685b0u);	/* 495fbf: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 495fc4: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 495fc8: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 495fcc: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4a8u));	/* 495fd2: fdivr dword ptr [0x4aa4a8] */
	ST(0) = ST(0) + (long double)(int)M32((DWORD)(m->esp + 0xbcu));	/* 495fd8: fiadd dword ptr [esp + 0xbc] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 495fdf: call 0x49ec14 */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 495fe4: mov dword ptr [esi], eax */
	goto L_496028;	/* 495fe6: jmp 0x496028 */
L_495fe8:
	m->eax = M32((DWORD)(m->esp + 0xbcu));	/* 495fe8: mov eax, dword ptr [esp + 0xbc] */
	M32((DWORD)(m->esi + 0xfffffff8u)) = m->ebx;	/* 495fef: mov dword ptr [esi - 8], ebx */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 495ff2: mov dword ptr [esi], eax */
	goto L_496028;	/* 495ff4: jmp 0x496028 */
L_495ff6:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xb4u)));	/* 495ff6: fild dword ptr [esp + 0xb4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 495ffd: fstp dword ptr [esp + 0x14] */
	m->esp -= 4; M32(m->esp) = 0x496006u; native_call(m, 0x4685b0u);	/* 496001: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 496006: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 49600a: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 49600e: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4a8u));	/* 496014: fdivr dword ptr [0x4aa4a8] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 49601a: fsubr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49601e: call 0x49ec14 */
	M32((DWORD)(m->esi + 0xfffffff8u)) = m->eax;	/* 496023: mov dword ptr [esi - 8], eax */
	M32((DWORD)(m->esi + 0x0u)) = m->ebx;	/* 496026: mov dword ptr [esi], ebx */
L_496028:
	m->eax = 0x55555556u;	/* 496028: mov eax, 0x55555556 */
	{ long long p_ = (long long)(int)m->eax * (int)m->edi; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 49602d: imul edi */
	m->ecx = m->edx;	/* 49602f: mov ecx, edx */
	{ DWORD a_ = m->ecx, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 496031: shr ecx, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496034: add edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496036: sub edx, 0 */
	if (m->zf) goto L_496084;	/* 496039: je 0x496084 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 49603b: dec edx */
	if (m->zf) goto L_496075;	/* 49603c: je 0x496075 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 49603e: dec edx */
	if (!m->zf) goto L_4960b7;	/* 49603f: jne 0x4960b7 */
	m->edx = M32((DWORD)(m->esp + 0xc0u));	/* 496041: mov edx, dword ptr [esp + 0xc0] */
	M32((DWORD)(m->esi + 0xfffffffcu)) = m->edx;	/* 496048: mov dword ptr [esi - 4], edx */
	m->esp -= 4; M32(m->esp) = 0x496050u; native_call(m, 0x4685c0u);	/* 49604b: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 496050: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 496054: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 496058: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4a8u));	/* 49605e: fdivr dword ptr [0x4aa4a8] */
	ST(0) = ST(0) + (long double)(int)M32((DWORD)(m->esp + 0xc0u));	/* 496064: fiadd dword ptr [esp + 0xc0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49606b: call 0x49ec14 */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 496070: mov dword ptr [esi + 4], eax */
	goto L_4960b7;	/* 496073: jmp 0x4960b7 */
L_496075:
	m->eax = M32((DWORD)(m->esp + 0xc0u));	/* 496075: mov eax, dword ptr [esp + 0xc0] */
	M32((DWORD)(m->esi + 0xfffffffcu)) = m->ebp;	/* 49607c: mov dword ptr [esi - 4], ebp */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 49607f: mov dword ptr [esi + 4], eax */
	goto L_4960b7;	/* 496082: jmp 0x4960b7 */
L_496084:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xb8u)));	/* 496084: fild dword ptr [esp + 0xb8] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49608b: fstp dword ptr [esp + 0x14] */
	m->esp -= 4; M32(m->esp) = 0x496094u; native_call(m, 0x4685c0u);	/* 49608f: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 496094: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 496098: fild dword ptr [esp + 0x10] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 49609c: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4a8u));	/* 4960a2: fdivr dword ptr [0x4aa4a8] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 4960a8: fsubr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4960ac: call 0x49ec14 */
	M32((DWORD)(m->esi + 0xfffffffcu)) = m->eax;	/* 4960b1: mov dword ptr [esi - 4], eax */
	M32((DWORD)(m->esi + 0x4u)) = m->ebp;	/* 4960b4: mov dword ptr [esi + 4], ebp */
L_4960b7:
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 4960b7: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4960b8: add esi, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4960bb: cmp edi, 9 */
	if (m->sf != m->of) goto L_495fa0;	/* 4960be: jl 0x495fa0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4960c4: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4960cfu; native_call(m, M32(0x4a9224u));	/* 4960c9: call dword ptr [0x4a9224] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4960cf: mov ecx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->ecx + 0xbc06b4u));	/* 4960d3: mov eax, dword ptr [ecx + 0xbc06b4] */
	m->edx = m->eax;	/* 4960d9: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4960db: and edx, 0x800001ff */
	if (!m->sf) goto L_4960eb;	/* 4960e1: jns 0x4960eb */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4960e3: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4960e4: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4960ea: inc edx */
L_4960eb:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4960eb: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4960ec: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4960f2: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4960f3: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4960f9: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4960fb: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4960fe: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x496107u; native_call(m, 0x4566c0u);	/* 496102: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 496107: push 7 */
	m->esp -= 4; M32(m->esp) = 0x49610fu; native_call(m, M32(0x4a921cu));	/* 496109: call dword ptr [0x4a921c] */
	m->ebx = M32((DWORD)(0x4a920cu));	/* 49610f: mov ebx, dword ptr [0x4a920c] */
	m->ebp = M32((DWORD)(0x4a91f4u));	/* 496115: mov ebp, dword ptr [0x4a91f4] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 49611b: xor edi, edi */
	m->esi = (DWORD)(m->esp + 0x28u);	/* 49611d: lea esi, [esp + 0x28] */
L_496121:
	m->eax = 0x55555556u;	/* 496121: mov eax, 0x55555556 */
	m->ecx = 0x3u;	/* 496126: mov ecx, 3 */
	{ long long p_ = (long long)(int)m->eax * (int)m->edi; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 49612b: imul edi */
	m->eax = m->edx;	/* 49612d: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49612f: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496132: add edx, eax */
	m->eax = m->edi;	/* 496134: mov eax, edi */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 496136: mov dword ptr [esp + 0x1c], edx */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49613a: shl edx, 5 */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 49613d: mov dword ptr [esp + 0x10], edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 496141: cdq  */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 496142: fild dword ptr [esp + 0x10] */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 496146: idiv ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 496148: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49614e: fstp dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 496152: mov dword ptr [esp + 0x14], edx */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 496156: shl edx, 5 */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 496159: mov dword ptr [esp + 0x10], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49615d: mov edx, dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 496161: fild dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496165: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 496166: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49616c: fstp dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 496170: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496174: push eax */
	m->esp -= 4; M32(m->esp) = 0x496177u; native_call(m, m->ebx);	/* 496175: call ebx */
	m->esp -= 4; M32(m->esp) = 0x49617cu; native_call(m, 0x4685c0u);	/* 496177: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + 0xfffffffcu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49617c: sub eax, dword ptr [esi - 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49617f: push eax */
	m->eax = M32((DWORD)(m->esi + 0xfffffff8u));	/* 496180: mov eax, dword ptr [esi - 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496183: push eax */
	m->esp -= 4; M32(m->esp) = 0x496186u; native_call(m, m->ebp);	/* 496184: call ebp */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 496186: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49618a: mov edx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49618e: inc ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49618f: push edx */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 496190: shl ecx, 5 */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 496193: mov dword ptr [esp + 0x18], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 496197: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 49619b: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4961a1: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4961a5: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4961a9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4961acu; native_call(m, m->ebx);	/* 4961aa: call ebx */
	m->esp -= 4; M32(m->esp) = 0x4961b1u; native_call(m, 0x4685c0u);	/* 4961ac: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + 0xfffffffcu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4961b1: sub eax, dword ptr [esi - 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4961b4: push eax */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 4961b5: mov eax, dword ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4961b7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4961bau; native_call(m, m->ebp);	/* 4961b8: call ebp */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4961ba: mov ecx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4961be: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4961c2: inc ecx */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4961c3: shl ecx, 5 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 4961c6: mov dword ptr [esp + 0x1c], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 4961ca: fild dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4961ce: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4961d4: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4961d8: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4961dc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4961dd: push eax */
	m->esp -= 4; M32(m->esp) = 0x4961e0u; native_call(m, m->ebx);	/* 4961de: call ebx */
	m->esp -= 4; M32(m->esp) = 0x4961e5u; native_call(m, 0x4685c0u);	/* 4961e0: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + 0x4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4961e5: sub eax, dword ptr [esi + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4961e8: push eax */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 4961e9: mov eax, dword ptr [esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4961eb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4961eeu; native_call(m, m->ebp);	/* 4961ec: call ebp */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4961ee: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4961f2: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4961f6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4961f7: push edx */
	m->esp -= 4; M32(m->esp) = 0x4961fau; native_call(m, m->ebx);	/* 4961f8: call ebx */
	m->esp -= 4; M32(m->esp) = 0x4961ffu; native_call(m, 0x4685c0u);	/* 4961fa: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + 0x4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4961ff: sub eax, dword ptr [esi + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496202: push eax */
	m->eax = M32((DWORD)(m->esi + 0xfffffff8u));	/* 496203: mov eax, dword ptr [esi - 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496206: push eax */
	m->esp -= 4; M32(m->esp) = 0x496209u; native_call(m, m->ebp);	/* 496207: call ebp */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 496209: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 49620a: add esi, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49620d: cmp edi, 9 */
	if (m->sf != m->of) goto L_496121;	/* 496210: jl 0x496121 */
	m->esp -= 4; M32(m->esp) = 0x49621cu; native_call(m, M32(0x4a9220u));	/* 496216: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49621c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x496227u; native_call(m, M32(0x4a922cu));	/* 496221: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 496227: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 496228: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 496229: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49622a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49622b: add esp, 0xa0 */
	m->esp += 4 + 16; return;	/* 496231: ret 0x10 */
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
