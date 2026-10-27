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

static void lift_4445a0(X86 *m);
static void lift_411ab0(X86 *m);
static void lift_4388e0(X86 *m);
static void lift_4091b0(X86 *m);
static void lift_411110(X86 *m);

/* armc_411110 (0x411110), lifted by tools/lift.py */
static void lift_411110(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 411110: sub esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 411113: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 411114: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 411115: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 411116: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 411117: push 1 */
	M32((DWORD)(m->esp + 0x50u)) = 0xc2200000u;	/* 411119: mov dword ptr [esp + 0x50], 0xc2200000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 411121: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x42200000u;	/* 411129: mov dword ptr [esp + 0x58], 0x42200000 */
	m->esp -= 4; M32(m->esp) = 0x411136u; native_call(m, 0x41ef90u);	/* 411131: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 411136: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 411139: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x411144u; native_call(m, M32(0x4a9224u));	/* 41113e: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 411144: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 41114a: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 411150: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 411156: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41115c: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 41115e: mov dword ptr [esp + 0x1c], eax */
	goto L_411168;	/* 411162: jmp 0x411168 */
L_411164:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 411164: mov eax, dword ptr [esp + 0x1c] */
L_411168:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411168: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 41116b: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 411173: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 41117b: mov dword ptr [esp + 0x40], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3e800000u;	/* 411183: mov dword ptr [esp + 0x44], 0x3e800000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f000000u;	/* 41118b: mov dword ptr [esp + 0x38], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_4111bd;	/* 411193: jle 0x4111bd */
	M32((DWORD)(m->esp + 0x28u)) = 0x3f000000u;	/* 411195: mov dword ptr [esp + 0x28], 0x3f000000 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 41119d: mov dword ptr [esp + 0x30], 0 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3ef00000u;	/* 4111a5: mov dword ptr [esp + 0x40], 0x3ef00000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f200000u;	/* 4111ad: mov dword ptr [esp + 0x44], 0x3f200000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 4111b5: mov dword ptr [esp + 0x38], 0x3f800000 */
L_4111bd:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4111bd: cmp eax, 2 */
	if (m->sf == m->of) goto L_4111f2;	/* 4111c0: jge 0x4111f2 */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 4111c2: mov eax, dword ptr [0x4e0cd0] */
	m->ecx = m->eax;	/* 4111c7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4111c9: and ecx, 0x800001ff */
	if (!m->sf) goto L_4111d9;	/* 4111cf: jns 0x4111d9 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4111d1: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4111d2: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4111d8: inc ecx */
L_4111d9:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4111d9: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4111da: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4111e0: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4111e1: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4111e3: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4111e9: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4111ec: mov ecx, dword ptr [edx + eax*4 + 4] */
	goto L_411227;	/* 4111f0: jmp 0x411227 */
L_4111f2:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4111f2: shl eax, 2 */
	m->ecx = 0x76d484u;	/* 4111f5: mov ecx, 0x76d484 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4111fa: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 4111fc: mov eax, dword ptr [ecx] */
	m->edx = m->eax;	/* 4111fe: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 411200: and edx, 0x800001ff */
	if (!m->sf) goto L_411210;	/* 411206: jns 0x411210 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 411208: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 411209: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 41120f: inc edx */
L_411210:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411210: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 411211: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 411217: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 411218: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41121e: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 411220: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 411223: mov ecx, dword ptr [ecx + eax*4 + 4] */
L_411227:
	m->esp -= 4; M32(m->esp) = 0x41122cu; native_call(m, 0x4566c0u);	/* 411227: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 41122c: mov dword ptr [esp + 0x18], 0 */
L_411234:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 411234: mov eax, dword ptr [esp + 0x18] */
	m->ecx = 0x3u;	/* 411238: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 41123d: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 41123e: idiv ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 411240: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x411249u; native_call(m, 0x41f050u);	/* 411244: call 0x41f050 */
	{ DWORD v_ = 0xc4098000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411249: push 0xc4098000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41124e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411250: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411258u; native_call(m, M32(0x4a9214u));	/* 411252: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411258: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_41126a;	/* 41125d: jge 0x41126a */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 41125f: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + m->edx*4 + 0x4cu));	/* 411263: mov eax, dword ptr [esp + edx*4 + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411267: push eax */
	goto L_411278;	/* 411268: jmp 0x411278 */
L_41126a:
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 41126a: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41126e: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->ecx*4 + 0x50u)));	/* 41126f: fld dword ptr [esp + ecx*4 + 0x50] */
	ST(0) = -ST(0);	/* 411273: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411275: fstp dword ptr [esp] */
L_411278:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411278: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41127a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411281u; native_call(m, 0x41ef20u);	/* 41127c: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 411281: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 411285: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411288: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_411409;	/* 41128b: ja 0x411409 */
	switch (m->eax) { case 0: goto L_411298; case 1: goto L_4112c8; case 2: goto L_411964; case 3: goto L_4112e7; default: abort(); }	/* 411291: jmp dword ptr [eax*4 + 0x411a98] */
L_411298:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 411298: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 41129e: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4112a4: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4112a5: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4112ab: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112ae: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112b3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112b8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4112c3u; native_call(m, M32(0x4a9228u));	/* 4112bd: call dword ptr [0x4a9228] */
	goto L_4116e3;	/* 4112c3: jmp 0x4116e3 */
L_4112c8:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4112c8: push 0x3ecccccd */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112cd: push 0x41200000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112d2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112d7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4112e2u; native_call(m, M32(0x4a9228u));	/* 4112dc: call dword ptr [0x4a9228] */
	goto L_411412;	/* 4112e2: jmp 0x411412 */
L_4112e7:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112e7: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112ec: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112f1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4112f6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411301u; native_call(m, M32(0x4a9228u));	/* 4112fb: call dword ptr [0x4a9228] */
L_411301:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 411301: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 411305: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411307: cmp eax, 3 */
	if (m->sf == m->of) goto L_411864;	/* 41130a: jge 0x411864 */
	m->esp -= 4; M32(m->esp) = 0x411312u; native_call(m, m->ebx);	/* 411310: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 411312: fild dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 411316: fst dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 41131a: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 411320: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 411324: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411328: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411329: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41132du; native_call(m, m->esi);	/* 41132b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 41132d: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 411331: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 411337: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 41133b: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 411341: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 411345: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 411349: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 41134f: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 411353: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411357: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 411358: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 41135c: fild dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 411360: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411364: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 411365: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 41136b: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 411371: fstp dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 411375: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411379: push eax */
	m->esp -= 4; M32(m->esp) = 0x41137cu; native_call(m, m->edi);	/* 41137a: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 41137c: mov ecx, dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 411380: mov edx, dword ptr [esp + 0x20] */
	m->eax = m->ecx;	/* 411384: mov eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411386: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411387: push eax */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 411388: mov dword ptr [esp + 0x44], ecx */
	m->esp -= 4; M32(m->esp) = 0x41138eu; native_call(m, m->esi);	/* 41138c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41138e: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411392: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 411398: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 41139c: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4113a0: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4113a4: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4113a8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4113a9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4113aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4113adu; native_call(m, m->edi);	/* 4113ab: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 4113ad: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4113b1: fadd dword ptr [0x4a9424] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 4113b7: mov edx, dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 4113bb: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 4113c1: fstp dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 4113c5: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4113c9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4113ca: push edx */
	m->esp -= 4; M32(m->esp) = 0x4113cdu; native_call(m, m->esi);	/* 4113cb: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4113cd: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4113d1: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4113d7: mov eax, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 4113db: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4113df: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4113e0: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4113e4: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4113e8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4113e9: push edx */
	m->esp -= 4; M32(m->esp) = 0x4113ecu; native_call(m, m->edi);	/* 4113ea: call edi */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 4113ec: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4113f0: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4113f1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4113f5u; native_call(m, m->esi);	/* 4113f3: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4113f5: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4113f9: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4113fd: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411401: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411402: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411403: push eax */
	goto L_411960;	/* 411404: jmp 0x411960 */
L_411409:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411409: cmp eax, 1 */
	if (!m->zf) goto L_4116db;	/* 41140c: jne 0x4116db */
L_411412:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 411412: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 411416: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411418: cmp eax, 3 */
	if (m->sf == m->of) goto L_41158a;	/* 41141b: jge 0x41158a */
	m->esp -= 4; M32(m->esp) = 0x411423u; native_call(m, m->ebx);	/* 411421: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411423: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411425: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411429u; native_call(m, m->esi);	/* 411427: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411429: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 41142f: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411435: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411436: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41143c: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41143f: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411444: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x41144bu; native_call(m, m->edi);	/* 411449: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 41144b: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411451: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411457: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411459: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 41145a: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411460: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411465u; native_call(m, m->esi);	/* 411463: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411465: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41146a: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 41146f: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411476u; native_call(m, m->edi);	/* 411474: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411476: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 41147c: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411482: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411487: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 411488: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41148e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411493u; native_call(m, m->esi);	/* 411491: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411493: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411498: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 41149d: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4114a4u; native_call(m, m->edi);	/* 4114a2: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114a4: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114a9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4114adu; native_call(m, m->esi);	/* 4114ab: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4114ad: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4114b3: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4114b9: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4114ba: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4114c0: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114c3: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114c8: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4114cfu; native_call(m, m->edi);	/* 4114cd: call edi */
	m->esp -= 4; M32(m->esp) = 0x4114d1u; native_call(m, m->ebp);	/* 4114cf: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114d1: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4114d5u; native_call(m, m->ebx);	/* 4114d3: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4114d5: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4114db: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114e1: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4114e3: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4114e4: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4114ea: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4114efu; native_call(m, m->esi);	/* 4114ed: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114ef: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114f4: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4114f9: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411500u; native_call(m, m->edi);	/* 4114fe: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411500: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411502: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411509u; native_call(m, m->esi);	/* 411507: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411509: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 41150f: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411515: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411516: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41151c: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41151f: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411524: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x41152bu; native_call(m, m->edi);	/* 411529: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41152b: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411530: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411537u; native_call(m, m->esi);	/* 411535: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411537: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 41153d: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411543: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411544: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41154a: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41154d: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411552: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411559u; native_call(m, m->edi);	/* 411557: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411559: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 41155f: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411565: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41156a: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 41156b: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411571: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411576u; native_call(m, m->esi);	/* 411574: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411576: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41157b: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411580: push 0xc1ef3333 */
	goto L_411960;	/* 411585: jmp 0x411960 */
L_41158a:
	m->esp -= 4; M32(m->esp) = 0x41158cu; native_call(m, m->ebx);	/* 41158a: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 41158c: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411592: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411598: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41159a: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41159b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4115a0u; native_call(m, m->esi);	/* 41159e: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115a0: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115a5: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115aa: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4115b1u; native_call(m, m->edi);	/* 4115af: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115b1: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115b3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4115bau; native_call(m, m->esi);	/* 4115b8: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4115ba: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4115c0: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4115c6: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4115c7: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4115cd: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115d0: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115d5: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4115dcu; native_call(m, m->edi);	/* 4115da: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115dc: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115e1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4115e8u; native_call(m, m->esi);	/* 4115e6: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4115e8: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4115ee: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4115f4: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4115f5: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4115fb: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4115fe: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411603: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x41160au; native_call(m, m->edi);	/* 411608: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 41160a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411610: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411616: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41161b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41161c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411621u; native_call(m, m->esi);	/* 41161f: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411621: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411626: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 41162b: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411632u; native_call(m, m->edi);	/* 411630: call edi */
	m->esp -= 4; M32(m->esp) = 0x411634u; native_call(m, m->ebp);	/* 411632: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 411634: push 7 */
	m->esp -= 4; M32(m->esp) = 0x411638u; native_call(m, m->ebx);	/* 411636: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411638: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41163a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41163eu; native_call(m, m->esi);	/* 41163c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 41163e: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 411644: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41164a: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 41164b: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411651: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411654: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411659: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411660u; native_call(m, m->edi);	/* 41165e: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411660: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411666: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41166c: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41166e: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41166f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411674u; native_call(m, m->esi);	/* 411672: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411674: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411679: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 41167e: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411685u; native_call(m, m->edi);	/* 411683: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411685: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 41168b: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411691: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411696: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411697: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x41169cu; native_call(m, m->esi);	/* 41169a: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41169c: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116a1: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116a6: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4116adu; native_call(m, m->edi);	/* 4116ab: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116ad: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116b2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4116b6u; native_call(m, m->esi);	/* 4116b4: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4116b6: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4116bc: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4116c2: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4116c3: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4116c9: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116cc: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116d1: push 0x41ef3333 */
	goto L_411960;	/* 4116d6: jmp 0x411960 */
L_4116db:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4116db: test eax, eax */
	if (!m->zf) goto L_411301;	/* 4116dd: jne 0x411301 */
L_4116e3:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4116e3: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116e7: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4116e9: cmp eax, 3 */
	if (m->sf == m->of) goto L_4117ab;	/* 4116ec: jge 0x4117ab */
	m->esp -= 4; M32(m->esp) = 0x4116f4u; native_call(m, m->ebx);	/* 4116f2: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116f4: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4116f9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4116fdu; native_call(m, m->esi);	/* 4116fb: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4116fd: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 411701: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 411707: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 41170b: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 411711: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 411715: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 411719: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 41171f: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 411723: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411727: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 411728: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 41172c: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411730: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411731: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x411738u; native_call(m, m->edi);	/* 411736: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411738: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41173d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411744u; native_call(m, m->esi);	/* 411742: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 411744: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411748: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 41174e: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 411752: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 411756: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41175a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41175b: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41175c: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x411763u; native_call(m, m->edi);	/* 411761: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411763: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411768: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41176fu; native_call(m, m->esi);	/* 41176d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41176f: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 411773: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 411779: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41177d: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 41177e: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 411782: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411786: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411787: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x41178eu; native_call(m, m->edi);	/* 41178c: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41178e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411793: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411797u; native_call(m, m->esi);	/* 411795: call esi */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 411797: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 41179b: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41179f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4117a0: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4117a1: push 0xc1f00000 */
	goto L_411960;	/* 4117a6: jmp 0x411960 */
L_4117ab:
	m->esp -= 4; M32(m->esp) = 0x4117adu; native_call(m, m->ebx);	/* 4117ab: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4117ad: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4117b2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4117b9u; native_call(m, m->esi);	/* 4117b7: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4117b9: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4117bd: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4117c3: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 4117c7: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4117cd: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4117d1: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4117d5: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4117db: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4117df: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4117e3: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4117e4: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4117e8: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4117ec: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4117ed: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4117f4u; native_call(m, m->edi);	/* 4117f2: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4117f4: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4117f9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4117fdu; native_call(m, m->esi);	/* 4117fb: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4117fd: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411801: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 411807: mov ecx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 41180b: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 41180f: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411813: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411814: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411815: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x41181cu; native_call(m, m->edi);	/* 41181a: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41181c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411821: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411825u; native_call(m, m->esi);	/* 411823: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 411825: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 411829: fsub dword ptr [0x4a9418] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 41182f: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411833: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 411834: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 411838: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41183c: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41183d: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x411844u; native_call(m, m->edi);	/* 411842: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411844: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411849: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411850u; native_call(m, m->esi);	/* 41184e: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 411850: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 411854: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411858: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411859: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41185a: push 0x41f00000 */
	goto L_411960;	/* 41185f: jmp 0x411960 */
L_411864:
	m->esp -= 4; M32(m->esp) = 0x411866u; native_call(m, m->ebx);	/* 411864: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 411866: fild dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 41186a: mov edx, dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 41186e: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 411874: fst dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 411878: fadd dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 41187c: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 411880: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411884: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411885: push edx */
	m->esp -= 4; M32(m->esp) = 0x411888u; native_call(m, m->esi);	/* 411886: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 411888: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 41188c: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 411892: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 411896: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 41189c: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4118a0: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4118a4: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4118aa: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4118ae: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4118b2: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4118b3: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4118b7: fild dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4118bb: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4118bf: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 4118c0: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 4118c6: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4118cc: fstp dword ptr [esp + 0x3c] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 4118d0: mov edx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4118d4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4118d7u; native_call(m, m->edi);	/* 4118d5: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4118d7: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 4118db: fadd dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4118df: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4118e3: push eax */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4118e4: fstp dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 4118e8: mov ecx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4118ec: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4118efu; native_call(m, m->esi);	/* 4118ed: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4118ef: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4118f3: fadd dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4118f9: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 4118fd: mov ecx, dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 411901: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 411905: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411909: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41190a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41190b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41190eu; native_call(m, m->edi);	/* 41190c: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 41190e: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 411912: fadd dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 411916: mov eax, dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 41191a: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 41191e: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411922: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411923: push eax */
	m->esp -= 4; M32(m->esp) = 0x411926u; native_call(m, m->esi);	/* 411924: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 411926: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 41192a: fsub dword ptr [0x4a9418] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 411930: mov ecx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 411934: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411938: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 411939: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 41193d: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411941: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411942: push eax */
	m->esp -= 4; M32(m->esp) = 0x411945u; native_call(m, m->edi);	/* 411943: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 411945: mov ecx, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 411949: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41194d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41194e: push edx */
	m->esp -= 4; M32(m->esp) = 0x411951u; native_call(m, m->esi);	/* 41194f: call esi */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 411951: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 411955: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 411959: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41195d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41195e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41195f: push edx */
L_411960:
	m->esp -= 4; M32(m->esp) = 0x411962u; native_call(m, m->edi);	/* 411960: call edi */
	m->esp -= 4; M32(m->esp) = 0x411964u; native_call(m, m->ebp);	/* 411962: call ebp */
L_411964:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 411964: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 411968: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411969: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 41196c: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_411234;	/* 411970: jl 0x411234 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 411976: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 41197a: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41197b: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 41197e: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_411164;	/* 411982: jl 0x411164 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 411988: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x411993u; native_call(m, M32(0x4a922cu));	/* 41198d: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 411993: mov eax, dword ptr [0x680398] */
	m->edi = M32(m->esp); m->esp += 4;	/* 411998: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 411999: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41199a: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41199b: test eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41199d: pop ebx */
	if (m->zf) goto L_411a02;	/* 41199e: je 0x411a02 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 4119a0: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 4119a6: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 4119ac: fadd dword ptr [0x680ccc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 4119b2: fst dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 4119b8: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4119be: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4119c0: test ah, 0x41 */
	if (m->zf) goto L_4119db;	/* 4119c3: je 0x4119db */
	M32((DWORD)(0x680cccu)) = 0x40000000u;	/* 4119c5: mov dword ptr [0x680ccc], 0x40000000 */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 4119cf: mov dword ptr [0x4df454], 0x3f800000 */
	goto L_411a02;	/* 4119d9: jmp 0x411a02 */
L_4119db:
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 4119db: fld dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 4119e1: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4119e7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4119e9: test ah, 1 */
	if (!m->zf) goto L_411a02;	/* 4119ec: jne 0x411a02 */
	M32((DWORD)(0x680cccu)) = 0x42180000u;	/* 4119ee: mov dword ptr [0x680ccc], 0x42180000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 4119f8: mov dword ptr [0x4df454], 0xbf800000 */
L_411a02:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 411a02: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 411a08: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 411a0e: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 411a14: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 411a1a: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 411a20: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 411a22: test ah, 0x41 */
	if (m->zf) goto L_411a3d;	/* 411a25: je 0x411a3d */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 411a27: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 411a31: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_411a64;	/* 411a3b: jmp 0x411a64 */
L_411a3d:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 411a3d: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 411a43: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 411a49: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 411a4b: test ah, 1 */
	if (!m->zf) goto L_411a64;	/* 411a4e: jne 0x411a64 */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 411a50: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 411a5a: mov dword ptr [0x4df010], 0xbf800000 */
L_411a64:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 411a64: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 411a6a: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 411a70: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 411a76: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 411a7c: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 411a82: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 411a84: test ah, 1 */
	if (!m->zf) goto L_411a93;	/* 411a87: jne 0x411a93 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 411a89: mov dword ptr [0x4e14fc], 0 */
L_411a93:
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 411a93: add esp, 0x48 */
	m->esp += 4 + 0; return;	/* 411a96: ret  */
}

/* skirmish_4445a0 (0x4445a0), lifted by tools/lift.py */
static void lift_4445a0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4445a0: sub esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4445a3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4445a4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4445a5: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4445a6: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4445a7: push 1 */
	M32((DWORD)(m->esp + 0x50u)) = 0xc2200000u;	/* 4445a9: mov dword ptr [esp + 0x50], 0xc2200000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 4445b1: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x42200000u;	/* 4445b9: mov dword ptr [esp + 0x58], 0x42200000 */
	m->esp -= 4; M32(m->esp) = 0x4445c6u; native_call(m, 0x41ef90u);	/* 4445c1: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4445c6: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4445c9: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4445d4u; native_call(m, M32(0x4a9224u));	/* 4445ce: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 4445d4: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4445da: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 4445e0: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 4445e6: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4445ec: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4445ee: mov dword ptr [esp + 0x1c], eax */
	goto L_4445f8;	/* 4445f2: jmp 0x4445f8 */
L_4445f4:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4445f4: mov eax, dword ptr [esp + 0x1c] */
L_4445f8:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4445f8: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 4445fb: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 444603: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 44460b: mov dword ptr [esp + 0x40], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3e800000u;	/* 444613: mov dword ptr [esp + 0x44], 0x3e800000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f000000u;	/* 44461b: mov dword ptr [esp + 0x38], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_44464d;	/* 444623: jle 0x44464d */
	M32((DWORD)(m->esp + 0x28u)) = 0x3f000000u;	/* 444625: mov dword ptr [esp + 0x28], 0x3f000000 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 44462d: mov dword ptr [esp + 0x30], 0 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3ef00000u;	/* 444635: mov dword ptr [esp + 0x40], 0x3ef00000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f200000u;	/* 44463d: mov dword ptr [esp + 0x44], 0x3f200000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 444645: mov dword ptr [esp + 0x38], 0x3f800000 */
L_44464d:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44464d: cmp eax, 2 */
	if (m->sf == m->of) goto L_444682;	/* 444650: jge 0x444682 */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 444652: mov eax, dword ptr [0x4e0cd0] */
	m->ecx = m->eax;	/* 444657: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 444659: and ecx, 0x800001ff */
	if (!m->sf) goto L_444669;	/* 44465f: jns 0x444669 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 444661: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 444662: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 444668: inc ecx */
L_444669:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 444669: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44466a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444670: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 444671: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 444673: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 444679: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44467c: mov ecx, dword ptr [edx + eax*4 + 4] */
	goto L_4446b7;	/* 444680: jmp 0x4446b7 */
L_444682:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 444682: shl eax, 2 */
	m->ecx = 0x76d484u;	/* 444685: mov ecx, 0x76d484 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44468a: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 44468c: mov eax, dword ptr [ecx] */
	m->edx = m->eax;	/* 44468e: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 444690: and edx, 0x800001ff */
	if (!m->sf) goto L_4446a0;	/* 444696: jns 0x4446a0 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 444698: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 444699: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44469f: inc edx */
L_4446a0:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4446a0: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4446a1: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4446a7: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4446a8: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4446ae: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4446b0: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4446b3: mov ecx, dword ptr [ecx + eax*4 + 4] */
L_4446b7:
	m->esp -= 4; M32(m->esp) = 0x4446bcu; native_call(m, 0x4566c0u);	/* 4446b7: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 4446bc: mov dword ptr [esp + 0x18], 0 */
L_4446c4:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4446c4: mov eax, dword ptr [esp + 0x18] */
	m->ecx = 0x3u;	/* 4446c8: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4446cd: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4446ce: idiv ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 4446d0: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x4446d9u; native_call(m, 0x41f050u);	/* 4446d4: call 0x41f050 */
	{ DWORD v_ = 0xc4098000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4446d9: push 0xc4098000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4446de: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4446e0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4446e8u; native_call(m, M32(0x4a9214u));	/* 4446e2: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4446e8: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_4446fa;	/* 4446ed: jge 0x4446fa */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 4446ef: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + m->edx*4 + 0x4cu));	/* 4446f3: mov eax, dword ptr [esp + edx*4 + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4446f7: push eax */
	goto L_444708;	/* 4446f8: jmp 0x444708 */
L_4446fa:
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4446fa: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4446fe: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->ecx*4 + 0x50u)));	/* 4446ff: fld dword ptr [esp + ecx*4 + 0x50] */
	ST(0) = -ST(0);	/* 444703: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444705: fstp dword ptr [esp] */
L_444708:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444708: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44470a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x444711u; native_call(m, 0x41ef20u);	/* 44470c: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 444711: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 444715: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444718: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_444899;	/* 44471b: ja 0x444899 */
	switch (m->eax) { case 0: goto L_444728; case 1: goto L_444758; case 2: goto L_444df4; case 3: goto L_444777; default: abort(); }	/* 444721: jmp dword ptr [eax*4 + 0x444f28] */
L_444728:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 444728: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 44472e: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444734: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 444735: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44473b: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44473e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444743: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444748: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444753u; native_call(m, M32(0x4a9228u));	/* 44474d: call dword ptr [0x4a9228] */
	goto L_444b73;	/* 444753: jmp 0x444b73 */
L_444758:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 444758: push 0x3ecccccd */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44475d: push 0x41200000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444762: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444767: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444772u; native_call(m, M32(0x4a9228u));	/* 44476c: call dword ptr [0x4a9228] */
	goto L_4448a2;	/* 444772: jmp 0x4448a2 */
L_444777:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444777: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44477c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444781: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444786: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444791u; native_call(m, M32(0x4a9228u));	/* 44478b: call dword ptr [0x4a9228] */
L_444791:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 444791: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 444795: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444797: cmp eax, 3 */
	if (m->sf == m->of) goto L_444cf4;	/* 44479a: jge 0x444cf4 */
	m->esp -= 4; M32(m->esp) = 0x4447a2u; native_call(m, m->ebx);	/* 4447a0: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 4447a2: fild dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 4447a6: fst dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 4447aa: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4447b0: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4447b4: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4447b8: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4447b9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4447bdu; native_call(m, m->esi);	/* 4447bb: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4447bd: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4447c1: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4447c7: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 4447cb: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4447d1: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4447d5: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4447d9: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4447df: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4447e3: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4447e7: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4447e8: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4447ec: fild dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4447f0: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4447f4: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 4447f5: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 4447fb: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 444801: fstp dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 444805: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444809: push eax */
	m->esp -= 4; M32(m->esp) = 0x44480cu; native_call(m, m->edi);	/* 44480a: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 44480c: mov ecx, dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 444810: mov edx, dword ptr [esp + 0x20] */
	m->eax = m->ecx;	/* 444814: mov eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444816: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444817: push eax */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 444818: mov dword ptr [esp + 0x44], ecx */
	m->esp -= 4; M32(m->esp) = 0x44481eu; native_call(m, m->esi);	/* 44481c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 44481e: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 444822: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 444828: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 44482c: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 444830: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 444834: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444838: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444839: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44483a: push eax */
	m->esp -= 4; M32(m->esp) = 0x44483du; native_call(m, m->edi);	/* 44483b: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 44483d: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 444841: fadd dword ptr [0x4a9424] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 444847: mov edx, dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 44484b: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 444851: fstp dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 444855: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444859: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44485a: push edx */
	m->esp -= 4; M32(m->esp) = 0x44485du; native_call(m, m->esi);	/* 44485b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 44485d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 444861: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 444867: mov eax, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 44486b: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44486f: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 444870: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 444874: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444878: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444879: push edx */
	m->esp -= 4; M32(m->esp) = 0x44487cu; native_call(m, m->edi);	/* 44487a: call edi */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 44487c: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444880: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444881: push 0 */
	m->esp -= 4; M32(m->esp) = 0x444885u; native_call(m, m->esi);	/* 444883: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 444885: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 444889: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 44488d: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444891: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444892: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444893: push eax */
	goto L_444df0;	/* 444894: jmp 0x444df0 */
L_444899:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444899: cmp eax, 1 */
	if (!m->zf) goto L_444b6b;	/* 44489c: jne 0x444b6b */
L_4448a2:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4448a2: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448a6: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4448a8: cmp eax, 3 */
	if (m->sf == m->of) goto L_444a1a;	/* 4448ab: jge 0x444a1a */
	m->esp -= 4; M32(m->esp) = 0x4448b3u; native_call(m, m->ebx);	/* 4448b1: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448b3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448b5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4448b9u; native_call(m, m->esi);	/* 4448b7: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4448b9: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4448bf: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4448c5: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4448c6: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4448cc: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448cf: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448d4: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4448dbu; native_call(m, m->edi);	/* 4448d9: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4448db: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4448e1: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448e7: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4448e9: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4448ea: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4448f0: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4448f5u; native_call(m, m->esi);	/* 4448f3: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448f5: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448fa: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4448ff: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444906u; native_call(m, m->edi);	/* 444904: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444906: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 44490c: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444912: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444917: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 444918: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44491e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x444923u; native_call(m, m->esi);	/* 444921: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444923: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444928: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44492d: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444934u; native_call(m, m->edi);	/* 444932: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444934: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444939: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44493du; native_call(m, m->esi);	/* 44493b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 44493d: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 444943: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444949: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 44494a: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444950: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444953: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444958: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x44495fu; native_call(m, m->edi);	/* 44495d: call edi */
	m->esp -= 4; M32(m->esp) = 0x444961u; native_call(m, m->ebp);	/* 44495f: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 444961: push 7 */
	m->esp -= 4; M32(m->esp) = 0x444965u; native_call(m, m->ebx);	/* 444963: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444965: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 44496b: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444971: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444973: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 444974: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44497a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x44497fu; native_call(m, m->esi);	/* 44497d: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44497f: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444984: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444989: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444990u; native_call(m, m->edi);	/* 44498e: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444990: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444992: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444999u; native_call(m, m->esi);	/* 444997: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444999: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 44499f: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4449a5: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4449a6: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4449ac: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4449af: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4449b4: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4449bbu; native_call(m, m->edi);	/* 4449b9: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4449bb: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4449c0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4449c7u; native_call(m, m->esi);	/* 4449c5: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4449c7: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4449cd: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4449d3: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4449d4: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4449da: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4449dd: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4449e2: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4449e9u; native_call(m, m->edi);	/* 4449e7: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4449e9: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4449ef: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4449f5: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4449fa: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4449fb: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444a01: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x444a06u; native_call(m, m->esi);	/* 444a04: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a06: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a0b: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a10: push 0xc1ef3333 */
	goto L_444df0;	/* 444a15: jmp 0x444df0 */
L_444a1a:
	m->esp -= 4; M32(m->esp) = 0x444a1cu; native_call(m, m->ebx);	/* 444a1a: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444a1c: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 444a22: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a28: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444a2a: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444a2b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x444a30u; native_call(m, m->esi);	/* 444a2e: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a30: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a35: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a3a: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444a41u; native_call(m, m->edi);	/* 444a3f: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a41: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a43: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444a4au; native_call(m, m->esi);	/* 444a48: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444a4a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 444a50: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444a56: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 444a57: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444a5d: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a60: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a65: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444a6cu; native_call(m, m->edi);	/* 444a6a: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a6c: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a71: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444a78u; native_call(m, m->esi);	/* 444a76: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444a78: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 444a7e: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444a84: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 444a85: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444a8b: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a8e: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444a93: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444a9au; native_call(m, m->edi);	/* 444a98: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444a9a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 444aa0: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444aa6: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444aab: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444aac: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x444ab1u; native_call(m, m->esi);	/* 444aaf: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ab1: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ab6: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444abb: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444ac2u; native_call(m, m->edi);	/* 444ac0: call edi */
	m->esp -= 4; M32(m->esp) = 0x444ac4u; native_call(m, m->ebp);	/* 444ac2: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ac4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x444ac8u; native_call(m, m->ebx);	/* 444ac6: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ac8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444aca: push 0 */
	m->esp -= 4; M32(m->esp) = 0x444aceu; native_call(m, m->esi);	/* 444acc: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444ace: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 444ad4: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444ada: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 444adb: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444ae1: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ae4: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ae9: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444af0u; native_call(m, m->edi);	/* 444aee: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444af0: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 444af6: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444afc: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444afe: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444aff: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x444b04u; native_call(m, m->esi);	/* 444b02: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b04: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b09: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b0e: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444b15u; native_call(m, m->edi);	/* 444b13: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444b15: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 444b1b: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b21: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444b26: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444b27: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x444b2cu; native_call(m, m->esi);	/* 444b2a: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b2c: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b31: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b36: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x444b3du; native_call(m, m->edi);	/* 444b3b: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b3d: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b42: push 0 */
	m->esp -= 4; M32(m->esp) = 0x444b46u; native_call(m, m->esi);	/* 444b44: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 444b46: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 444b4c: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444b52: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 444b53: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 444b59: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b5c: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b61: push 0x41ef3333 */
	goto L_444df0;	/* 444b66: jmp 0x444df0 */
L_444b6b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 444b6b: test eax, eax */
	if (!m->zf) goto L_444791;	/* 444b6d: jne 0x444791 */
L_444b73:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 444b73: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b77: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444b79: cmp eax, 3 */
	if (m->sf == m->of) goto L_444c3b;	/* 444b7c: jge 0x444c3b */
	m->esp -= 4; M32(m->esp) = 0x444b84u; native_call(m, m->ebx);	/* 444b82: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b84: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444b89: push 0 */
	m->esp -= 4; M32(m->esp) = 0x444b8du; native_call(m, m->esi);	/* 444b8b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 444b8d: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 444b91: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 444b97: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 444b9b: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 444ba1: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 444ba5: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 444ba9: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 444baf: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 444bb3: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444bb7: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 444bb8: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 444bbc: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444bc0: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444bc1: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x444bc8u; native_call(m, m->edi);	/* 444bc6: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444bc8: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444bcd: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444bd4u; native_call(m, m->esi);	/* 444bd2: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 444bd4: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 444bd8: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 444bde: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 444be2: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 444be6: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444bea: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444beb: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444bec: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x444bf3u; native_call(m, m->edi);	/* 444bf1: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444bf3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444bf8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444bffu; native_call(m, m->esi);	/* 444bfd: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 444bff: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 444c03: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 444c09: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444c0d: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 444c0e: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 444c12: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444c16: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c17: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x444c1eu; native_call(m, m->edi);	/* 444c1c: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c1e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c23: push 0 */
	m->esp -= 4; M32(m->esp) = 0x444c27u; native_call(m, m->esi);	/* 444c25: call esi */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 444c27: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 444c2b: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444c2f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444c30: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c31: push 0xc1f00000 */
	goto L_444df0;	/* 444c36: jmp 0x444df0 */
L_444c3b:
	m->esp -= 4; M32(m->esp) = 0x444c3du; native_call(m, m->ebx);	/* 444c3b: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c3d: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c42: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444c49u; native_call(m, m->esi);	/* 444c47: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 444c49: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 444c4d: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 444c53: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 444c57: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 444c5d: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 444c61: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 444c65: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 444c6b: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 444c6f: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444c73: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 444c74: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 444c78: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444c7c: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c7d: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x444c84u; native_call(m, m->edi);	/* 444c82: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c84: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444c89: push 0 */
	m->esp -= 4; M32(m->esp) = 0x444c8du; native_call(m, m->esi);	/* 444c8b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 444c8d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 444c91: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 444c97: mov ecx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 444c9b: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 444c9f: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444ca3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444ca4: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ca5: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x444cacu; native_call(m, m->edi);	/* 444caa: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444cac: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444cb1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x444cb5u; native_call(m, m->esi);	/* 444cb3: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 444cb5: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 444cb9: fsub dword ptr [0x4a9418] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 444cbf: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444cc3: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 444cc4: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 444cc8: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444ccc: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ccd: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x444cd4u; native_call(m, m->edi);	/* 444cd2: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444cd4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444cd9: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x444ce0u; native_call(m, m->esi);	/* 444cde: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 444ce0: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 444ce4: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444ce8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444ce9: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444cea: push 0x41f00000 */
	goto L_444df0;	/* 444cef: jmp 0x444df0 */
L_444cf4:
	m->esp -= 4; M32(m->esp) = 0x444cf6u; native_call(m, m->ebx);	/* 444cf4: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 444cf6: fild dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 444cfa: mov edx, dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 444cfe: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 444d04: fst dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 444d08: fadd dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 444d0c: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 444d10: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444d14: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444d15: push edx */
	m->esp -= 4; M32(m->esp) = 0x444d18u; native_call(m, m->esi);	/* 444d16: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 444d18: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 444d1c: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 444d22: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 444d26: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 444d2c: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 444d30: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 444d34: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 444d3a: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 444d3e: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444d42: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 444d43: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 444d47: fild dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 444d4b: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444d4f: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 444d50: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 444d56: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 444d5c: fstp dword ptr [esp + 0x3c] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 444d60: mov edx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444d64: push edx */
	m->esp -= 4; M32(m->esp) = 0x444d67u; native_call(m, m->edi);	/* 444d65: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 444d67: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 444d6b: fadd dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 444d6f: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444d73: push eax */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 444d74: fstp dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 444d78: mov ecx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444d7c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x444d7fu; native_call(m, m->esi);	/* 444d7d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 444d7f: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 444d83: fadd dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 444d89: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 444d8d: mov ecx, dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 444d91: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 444d95: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444d99: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444d9a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444d9b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x444d9eu; native_call(m, m->edi);	/* 444d9c: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 444d9e: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 444da2: fadd dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 444da6: mov eax, dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 444daa: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 444dae: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444db2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444db3: push eax */
	m->esp -= 4; M32(m->esp) = 0x444db6u; native_call(m, m->esi);	/* 444db4: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 444db6: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 444dba: fsub dword ptr [0x4a9418] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 444dc0: mov ecx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 444dc4: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444dc8: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 444dc9: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 444dcd: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444dd1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444dd2: push eax */
	m->esp -= 4; M32(m->esp) = 0x444dd5u; native_call(m, m->edi);	/* 444dd3: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 444dd5: mov ecx, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 444dd9: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444ddd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444dde: push edx */
	m->esp -= 4; M32(m->esp) = 0x444de1u; native_call(m, m->esi);	/* 444ddf: call esi */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 444de1: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 444de5: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 444de9: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444ded: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444dee: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444def: push edx */
L_444df0:
	m->esp -= 4; M32(m->esp) = 0x444df2u; native_call(m, m->edi);	/* 444df0: call edi */
	m->esp -= 4; M32(m->esp) = 0x444df4u; native_call(m, m->ebp);	/* 444df2: call ebp */
L_444df4:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 444df4: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 444df8: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444df9: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 444dfc: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_4446c4;	/* 444e00: jl 0x4446c4 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 444e06: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 444e0a: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444e0b: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 444e0e: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_4445f4;	/* 444e12: jl 0x4445f4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 444e18: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x444e23u; native_call(m, M32(0x4a922cu));	/* 444e1d: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 444e23: mov eax, dword ptr [0x680398] */
	m->edi = M32(m->esp); m->esp += 4;	/* 444e28: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 444e29: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 444e2a: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 444e2b: test eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 444e2d: pop ebx */
	if (m->zf) goto L_444e92;	/* 444e2e: je 0x444e92 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 444e30: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 444e36: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 444e3c: fadd dword ptr [0x680ccc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 444e42: fst dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 444e48: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 444e4e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 444e50: test ah, 0x41 */
	if (m->zf) goto L_444e6b;	/* 444e53: je 0x444e6b */
	M32((DWORD)(0x680cccu)) = 0x40000000u;	/* 444e55: mov dword ptr [0x680ccc], 0x40000000 */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 444e5f: mov dword ptr [0x4df454], 0x3f800000 */
	goto L_444e92;	/* 444e69: jmp 0x444e92 */
L_444e6b:
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 444e6b: fld dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 444e71: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 444e77: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 444e79: test ah, 1 */
	if (!m->zf) goto L_444e92;	/* 444e7c: jne 0x444e92 */
	M32((DWORD)(0x680cccu)) = 0x42180000u;	/* 444e7e: mov dword ptr [0x680ccc], 0x42180000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 444e88: mov dword ptr [0x4df454], 0xbf800000 */
L_444e92:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 444e92: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 444e98: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 444e9e: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 444ea4: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 444eaa: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 444eb0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 444eb2: test ah, 0x41 */
	if (m->zf) goto L_444ecd;	/* 444eb5: je 0x444ecd */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 444eb7: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 444ec1: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_444ef4;	/* 444ecb: jmp 0x444ef4 */
L_444ecd:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 444ecd: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 444ed3: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 444ed9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 444edb: test ah, 1 */
	if (!m->zf) goto L_444ef4;	/* 444ede: jne 0x444ef4 */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 444ee0: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 444eea: mov dword ptr [0x4df010], 0xbf800000 */
L_444ef4:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 444ef4: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 444efa: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 444f00: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 444f06: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 444f0c: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 444f12: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 444f14: test ah, 1 */
	if (!m->zf) goto L_444f23;	/* 444f17: jne 0x444f23 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 444f19: mov dword ptr [0x4e14fc], 0 */
L_444f23:
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 444f23: add esp, 0x48 */
	m->esp += 4 + 0; return;	/* 444f26: ret  */
}

/* armc_411ab0 (0x411ab0), lifted by tools/lift.py */
static void lift_411ab0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 411ab0: sub esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 411ab3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 411ab4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 411ab5: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 411ab6: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ab7: push 1 */
	M32((DWORD)(m->esp + 0x50u)) = 0xc2200000u;	/* 411ab9: mov dword ptr [esp + 0x50], 0xc2200000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 411ac1: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x42200000u;	/* 411ac9: mov dword ptr [esp + 0x58], 0x42200000 */
	m->esp -= 4; M32(m->esp) = 0x411ad6u; native_call(m, 0x41ef90u);	/* 411ad1: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 411ad6: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ad9: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x411ae4u; native_call(m, M32(0x4a9224u));	/* 411ade: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 411ae4: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 411aea: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 411af0: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 411af6: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 411afc: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 411afe: mov dword ptr [esp + 0x1c], eax */
	goto L_411b08;	/* 411b02: jmp 0x411b08 */
L_411b04:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 411b04: mov eax, dword ptr [esp + 0x1c] */
L_411b08:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411b08: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 411b0b: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 411b13: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 411b1b: mov dword ptr [esp + 0x40], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3e800000u;	/* 411b23: mov dword ptr [esp + 0x44], 0x3e800000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f000000u;	/* 411b2b: mov dword ptr [esp + 0x38], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_411b5d;	/* 411b33: jle 0x411b5d */
	M32((DWORD)(m->esp + 0x28u)) = 0x3f000000u;	/* 411b35: mov dword ptr [esp + 0x28], 0x3f000000 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 411b3d: mov dword ptr [esp + 0x30], 0 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3ef00000u;	/* 411b45: mov dword ptr [esp + 0x40], 0x3ef00000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f200000u;	/* 411b4d: mov dword ptr [esp + 0x44], 0x3f200000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 411b55: mov dword ptr [esp + 0x38], 0x3f800000 */
L_411b5d:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411b5d: cmp eax, 2 */
	if (m->sf == m->of) goto L_411b92;	/* 411b60: jge 0x411b92 */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 411b62: mov eax, dword ptr [0x4e0cd0] */
	m->ecx = m->eax;	/* 411b67: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 411b69: and ecx, 0x800001ff */
	if (!m->sf) goto L_411b79;	/* 411b6f: jns 0x411b79 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 411b71: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 411b72: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 411b78: inc ecx */
L_411b79:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 411b79: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 411b7a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411b80: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 411b81: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 411b83: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 411b89: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 411b8c: mov ecx, dword ptr [edx + eax*4 + 4] */
	goto L_411bc7;	/* 411b90: jmp 0x411bc7 */
L_411b92:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 411b92: shl eax, 2 */
	m->ecx = 0x4df910u;	/* 411b95: mov ecx, 0x4df910 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 411b9a: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 411b9c: mov eax, dword ptr [ecx] */
	m->edx = m->eax;	/* 411b9e: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 411ba0: and edx, 0x800001ff */
	if (!m->sf) goto L_411bb0;	/* 411ba6: jns 0x411bb0 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 411ba8: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 411ba9: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 411baf: inc edx */
L_411bb0:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411bb0: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 411bb1: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 411bb7: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 411bb8: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 411bbe: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 411bc0: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 411bc3: mov ecx, dword ptr [ecx + eax*4 + 4] */
L_411bc7:
	m->esp -= 4; M32(m->esp) = 0x411bccu; native_call(m, 0x4566c0u);	/* 411bc7: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 411bcc: mov dword ptr [esp + 0x18], 0 */
L_411bd4:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 411bd4: mov eax, dword ptr [esp + 0x18] */
	m->ecx = 0x3u;	/* 411bd8: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 411bdd: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 411bde: idiv ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 411be0: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x411be9u; native_call(m, 0x41f050u);	/* 411be4: call 0x41f050 */
	{ DWORD v_ = 0xc4ce4000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411be9: push 0xc4ce4000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411bee: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411bf0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411bf8u; native_call(m, M32(0x4a9214u));	/* 411bf2: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411bf8: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_411c0a;	/* 411bfd: jge 0x411c0a */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 411bff: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + m->edx*4 + 0x4cu));	/* 411c03: mov eax, dword ptr [esp + edx*4 + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411c07: push eax */
	goto L_411c18;	/* 411c08: jmp 0x411c18 */
L_411c0a:
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 411c0a: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411c0e: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->ecx*4 + 0x50u)));	/* 411c0f: fld dword ptr [esp + ecx*4 + 0x50] */
	ST(0) = -ST(0);	/* 411c13: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411c15: fstp dword ptr [esp] */
L_411c18:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411c18: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411c1a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411c21u; native_call(m, 0x41ef20u);	/* 411c1c: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 411c21: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 411c25: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411c28: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_411de5;	/* 411c2b: ja 0x411de5 */
	switch (m->eax) { case 0: goto L_411c38; case 1: goto L_411c65; case 2: goto L_411c84; case 3: goto L_411dcc; default: abort(); }	/* 411c31: jmp dword ptr [eax*4 + 0x412440] */
L_411c38:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 411c38: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 411c3e: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411c44: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 411c45: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411c4b: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411c4e: push 0x3f333333 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411c53: push 0 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411c55: push 0x3f333333 */
	m->esp -= 4; M32(m->esp) = 0x411c60u; native_call(m, M32(0x4a9228u));	/* 411c5a: call dword ptr [0x4a9228] */
	goto L_4120bf;	/* 411c60: jmp 0x4120bf */
L_411c65:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411c65: push 0x3f333333 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 411c6a: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 411c6f: push 0x3dcccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411c74: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411c7fu; native_call(m, M32(0x4a9228u));	/* 411c79: call dword ptr [0x4a9228] */
	goto L_411dee;	/* 411c7f: jmp 0x411dee */
L_411c84:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411c84: cmp dword ptr [esp + 0x18], -1 */
	if (!m->zf) goto L_411cb8;	/* 411c89: jne 0x411cb8 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 411c8b: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9428u));	/* 411c91: fmul dword ptr [0x4a9428] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411c97: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 411c98: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411c9e: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ca1: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 411ca6: push 0x3dcccccd */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411cab: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x411cb6u; native_call(m, M32(0x4a9228u));	/* 411cb0: call dword ptr [0x4a9228] */
	goto L_411cd1;	/* 411cb6: jmp 0x411cd1 */
L_411cb8:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411cb8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411cba: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411cbc: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411cbe: push 0 */
L_411cc0:
	m->esp -= 4; M32(m->esp) = 0x411cc6u; native_call(m, M32(0x4a9228u));	/* 411cc0: call dword ptr [0x4a9228] */
L_411cc6:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411cc6: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_412240;	/* 411ccb: jge 0x412240 */
L_411cd1:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 411cd1: push 7 */
	m->esp -= 4; M32(m->esp) = 0x411cd5u; native_call(m, m->ebx);	/* 411cd3: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 411cd5: fild dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 411cd9: fst dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 411cdd: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 411ce3: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 411ce7: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411ceb: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411cec: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411cf0u; native_call(m, m->esi);	/* 411cee: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 411cf0: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 411cf4: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 411cfa: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 411cfe: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 411d04: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 411d08: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 411d0c: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 411d12: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 411d16: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411d1a: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 411d1b: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 411d1f: fild dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 411d23: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411d27: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 411d28: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 411d2e: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 411d34: fstp dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 411d38: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411d3c: push eax */
	m->esp -= 4; M32(m->esp) = 0x411d3fu; native_call(m, m->edi);	/* 411d3d: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 411d3f: mov ecx, dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 411d43: mov edx, dword ptr [esp + 0x20] */
	m->eax = m->ecx;	/* 411d47: mov eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411d49: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411d4a: push eax */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 411d4b: mov dword ptr [esp + 0x44], ecx */
	m->esp -= 4; M32(m->esp) = 0x411d51u; native_call(m, m->esi);	/* 411d4f: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 411d51: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411d55: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 411d5b: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 411d5f: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 411d63: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 411d67: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411d6b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411d6c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411d6d: push eax */
	m->esp -= 4; M32(m->esp) = 0x411d70u; native_call(m, m->edi);	/* 411d6e: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 411d70: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 411d74: fadd dword ptr [0x4a9424] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 411d7a: mov edx, dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 411d7e: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 411d84: fstp dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 411d88: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411d8c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411d8d: push edx */
	m->esp -= 4; M32(m->esp) = 0x411d90u; native_call(m, m->esi);	/* 411d8e: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 411d90: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 411d94: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 411d9a: mov eax, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 411d9e: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411da2: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 411da3: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 411da7: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411dab: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411dac: push edx */
	m->esp -= 4; M32(m->esp) = 0x411dafu; native_call(m, m->edi);	/* 411dad: call edi */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 411daf: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411db3: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411db4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411db8u; native_call(m, m->esi);	/* 411db6: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 411db8: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 411dbc: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 411dc0: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411dc4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 411dc5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 411dc6: push eax */
	goto L_41233e;	/* 411dc7: jmp 0x41233e */
L_411dcc:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411dcc: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411dd1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411dd6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ddb: push 0x3f800000 */
	goto L_411cc0;	/* 411de0: jmp 0x411cc0 */
L_411de5:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411de5: cmp eax, 1 */
	if (!m->zf) goto L_4120b7;	/* 411de8: jne 0x4120b7 */
L_411dee:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 411dee: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 411df2: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 411df4: cmp eax, 3 */
	if (m->sf == m->of) goto L_411f66;	/* 411df7: jge 0x411f66 */
	m->esp -= 4; M32(m->esp) = 0x411dffu; native_call(m, m->ebx);	/* 411dfd: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411dff: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e01: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411e05u; native_call(m, m->esi);	/* 411e03: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411e05: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 411e0b: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411e11: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411e12: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411e18: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e1b: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e20: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411e27u; native_call(m, m->edi);	/* 411e25: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411e27: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411e2d: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e33: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411e35: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 411e36: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411e3c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411e41u; native_call(m, m->esi);	/* 411e3f: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e41: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e46: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e4b: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411e52u; native_call(m, m->edi);	/* 411e50: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411e52: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411e58: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e5e: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411e63: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 411e64: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411e6a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411e6fu; native_call(m, m->esi);	/* 411e6d: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e6f: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e74: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e79: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411e80u; native_call(m, m->edi);	/* 411e7e: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e80: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e85: push 0 */
	m->esp -= 4; M32(m->esp) = 0x411e89u; native_call(m, m->esi);	/* 411e87: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411e89: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 411e8f: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411e95: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411e96: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411e9c: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411e9f: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ea4: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411eabu; native_call(m, m->edi);	/* 411ea9: call edi */
	m->esp -= 4; M32(m->esp) = 0x411eadu; native_call(m, m->ebp);	/* 411eab: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ead: push 7 */
	m->esp -= 4; M32(m->esp) = 0x411eb1u; native_call(m, m->ebx);	/* 411eaf: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411eb1: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411eb7: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ebd: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411ebf: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 411ec0: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411ec6: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411ecbu; native_call(m, m->esi);	/* 411ec9: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ecb: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ed0: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ed5: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411edcu; native_call(m, m->edi);	/* 411eda: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411edc: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ede: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411ee5u; native_call(m, m->esi);	/* 411ee3: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411ee5: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 411eeb: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411ef1: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411ef2: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411ef8: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411efb: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f00: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411f07u; native_call(m, m->edi);	/* 411f05: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f07: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f0c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411f13u; native_call(m, m->esi);	/* 411f11: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411f13: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 411f19: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411f1f: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411f20: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411f26: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f29: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f2e: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411f35u; native_call(m, m->edi);	/* 411f33: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411f35: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411f3b: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f41: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411f46: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 411f47: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411f4d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411f52u; native_call(m, m->esi);	/* 411f50: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f52: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f57: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f5c: push 0xc1ef3333 */
	goto L_41233e;	/* 411f61: jmp 0x41233e */
L_411f66:
	m->esp -= 4; M32(m->esp) = 0x411f68u; native_call(m, m->ebx);	/* 411f66: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411f68: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411f6e: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f74: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411f76: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411f77: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411f7cu; native_call(m, m->esi);	/* 411f7a: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f7c: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f81: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f86: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411f8du; native_call(m, m->edi);	/* 411f8b: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f8d: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411f8f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411f96u; native_call(m, m->esi);	/* 411f94: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411f96: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 411f9c: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411fa2: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411fa3: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411fa9: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411fac: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411fb1: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411fb8u; native_call(m, m->edi);	/* 411fb6: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411fb8: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411fbd: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x411fc4u; native_call(m, m->esi);	/* 411fc2: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411fc4: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 411fca: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411fd0: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 411fd1: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411fd7: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411fda: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 411fdf: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x411fe6u; native_call(m, m->edi);	/* 411fe4: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 411fe6: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 411fec: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ff2: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 411ff7: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 411ff8: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x411ffdu; native_call(m, m->esi);	/* 411ffb: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 411ffd: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412002: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 412007: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x41200eu; native_call(m, m->edi);	/* 41200c: call edi */
	m->esp -= 4; M32(m->esp) = 0x412010u; native_call(m, m->ebp);	/* 41200e: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 412010: push 7 */
	m->esp -= 4; M32(m->esp) = 0x412014u; native_call(m, m->ebx);	/* 412012: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412014: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412016: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41201au; native_call(m, m->esi);	/* 412018: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 41201a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 412020: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412026: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 412027: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41202d: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412030: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 412035: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x41203cu; native_call(m, m->edi);	/* 41203a: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 41203c: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 412042: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 412048: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41204a: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41204b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x412050u; native_call(m, m->esi);	/* 41204e: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412050: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412055: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 41205a: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x412061u; native_call(m, m->edi);	/* 41205f: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 412061: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 412067: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41206d: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412072: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 412073: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x412078u; native_call(m, m->esi);	/* 412076: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412078: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41207d: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 412082: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x412089u; native_call(m, m->edi);	/* 412087: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412089: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41208e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x412092u; native_call(m, m->esi);	/* 412090: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 412092: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 412098: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41209e: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 41209f: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4120a5: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4120a8: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4120ad: push 0x41ef3333 */
	goto L_41233e;	/* 4120b2: jmp 0x41233e */
L_4120b7:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4120b7: test eax, eax */
	if (!m->zf) goto L_411cc6;	/* 4120b9: jne 0x411cc6 */
L_4120bf:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4120bf: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4120c3: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4120c5: cmp eax, 3 */
	if (m->sf == m->of) goto L_412187;	/* 4120c8: jge 0x412187 */
	m->esp -= 4; M32(m->esp) = 0x4120d0u; native_call(m, m->ebx);	/* 4120ce: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4120d0: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4120d5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4120d9u; native_call(m, m->esi);	/* 4120d7: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4120d9: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4120dd: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4120e3: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 4120e7: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4120ed: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4120f1: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4120f5: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4120fb: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4120ff: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412103: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 412104: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 412108: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41210c: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41210d: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x412114u; native_call(m, m->edi);	/* 412112: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412114: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412119: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x412120u; native_call(m, m->esi);	/* 41211e: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 412120: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 412124: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 41212a: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 41212e: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 412132: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412136: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412137: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412138: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x41213fu; native_call(m, m->edi);	/* 41213d: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41213f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412144: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41214bu; native_call(m, m->esi);	/* 412149: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41214b: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 41214f: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 412155: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412159: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 41215a: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 41215e: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412162: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412163: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x41216au; native_call(m, m->edi);	/* 412168: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41216a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41216f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x412173u; native_call(m, m->esi);	/* 412171: call esi */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 412173: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 412177: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41217b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41217c: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41217d: push 0xc1f00000 */
	goto L_41233e;	/* 412182: jmp 0x41233e */
L_412187:
	m->esp -= 4; M32(m->esp) = 0x412189u; native_call(m, m->ebx);	/* 412187: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412189: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41218e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x412195u; native_call(m, m->esi);	/* 412193: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 412195: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 412199: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 41219f: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 4121a3: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4121a9: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4121ad: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4121b1: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4121b7: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4121bb: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4121bf: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4121c0: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4121c4: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4121c8: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4121c9: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4121d0u; native_call(m, m->edi);	/* 4121ce: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4121d0: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4121d5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4121d9u; native_call(m, m->esi);	/* 4121d7: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4121d9: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4121dd: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4121e3: mov ecx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4121e7: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4121eb: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4121ef: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4121f0: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4121f1: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4121f8u; native_call(m, m->edi);	/* 4121f6: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4121f8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4121fd: push 0 */
	m->esp -= 4; M32(m->esp) = 0x412201u; native_call(m, m->esi);	/* 4121ff: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 412201: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 412205: fsub dword ptr [0x4a9418] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 41220b: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41220f: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 412210: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 412214: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412218: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412219: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x412220u; native_call(m, m->edi);	/* 41221e: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412220: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412225: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41222cu; native_call(m, m->esi);	/* 41222a: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 41222c: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 412230: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412234: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412235: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412236: push 0x41f00000 */
	goto L_41233e;	/* 41223b: jmp 0x41233e */
L_412240:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 412240: push 7 */
	m->esp -= 4; M32(m->esp) = 0x412244u; native_call(m, m->ebx);	/* 412242: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 412244: fild dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 412248: mov edx, dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 41224c: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 412252: fst dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 412256: fadd dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 41225a: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 41225e: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412262: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412263: push edx */
	m->esp -= 4; M32(m->esp) = 0x412266u; native_call(m, m->esi);	/* 412264: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 412266: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 41226a: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 412270: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 412274: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 41227a: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 41227e: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 412282: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 412288: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 41228c: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412290: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 412291: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 412295: fild dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 412299: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41229d: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 41229e: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 4122a4: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4122aa: fstp dword ptr [esp + 0x3c] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 4122ae: mov edx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4122b2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4122b5u; native_call(m, m->edi);	/* 4122b3: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4122b5: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 4122b9: fadd dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4122bd: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4122c1: push eax */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4122c2: fstp dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 4122c6: mov ecx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4122ca: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4122cdu; native_call(m, m->esi);	/* 4122cb: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4122cd: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4122d1: fadd dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4122d7: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 4122db: mov ecx, dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4122df: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4122e3: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4122e7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4122e8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4122e9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4122ecu; native_call(m, m->edi);	/* 4122ea: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4122ec: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 4122f0: fadd dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 4122f4: mov eax, dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4122f8: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4122fc: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412300: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412301: push eax */
	m->esp -= 4; M32(m->esp) = 0x412304u; native_call(m, m->esi);	/* 412302: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 412304: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 412308: fsub dword ptr [0x4a9418] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 41230e: mov ecx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 412312: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412316: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 412317: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 41231b: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41231f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412320: push eax */
	m->esp -= 4; M32(m->esp) = 0x412323u; native_call(m, m->edi);	/* 412321: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 412323: mov ecx, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 412327: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41232b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41232c: push edx */
	m->esp -= 4; M32(m->esp) = 0x41232fu; native_call(m, m->esi);	/* 41232d: call esi */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 41232f: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 412333: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 412337: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41233b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41233c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41233d: push edx */
L_41233e:
	m->esp -= 4; M32(m->esp) = 0x412340u; native_call(m, m->edi);	/* 41233e: call edi */
	m->esp -= 4; M32(m->esp) = 0x412342u; native_call(m, m->ebp);	/* 412340: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 412342: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 412346: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412347: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 41234a: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_411bd4;	/* 41234e: jl 0x411bd4 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 412354: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 412358: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412359: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 41235c: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_411b04;	/* 412360: jl 0x411b04 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 412366: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x412371u; native_call(m, M32(0x4a922cu));	/* 41236b: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 412371: mov eax, dword ptr [0x680398] */
	m->edi = M32(m->esp); m->esp += 4;	/* 412376: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 412377: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 412378: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 412379: test eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41237b: pop ebx */
	if (m->zf) goto L_4123c4;	/* 41237c: je 0x4123c4 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41237e: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 412384: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 41238a: fadd dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu));	/* 412390: fcom dword ptr [0x4a93fc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 412396: fst dword ptr [0x680ccc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41239c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41239e: test ah, 0x41 */
	if (m->zf) goto L_4123ad;	/* 4123a1: je 0x4123ad */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 4123a3: mov dword ptr [0x4df454], 0x3f800000 */
L_4123ad:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 4123ad: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4123b3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4123b5: test ah, 1 */
	if (!m->zf) goto L_4123c4;	/* 4123b8: jne 0x4123c4 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 4123ba: mov dword ptr [0x4df454], 0xbf800000 */
L_4123c4:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 4123c4: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 4123ca: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 4123d0: fadd dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 4123d6: fcom dword ptr [0x4a93e8] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 4123dc: fst dword ptr [0x9db978] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4123e2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4123e4: test ah, 0x41 */
	if (m->zf) goto L_4123f3;	/* 4123e7: je 0x4123f3 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 4123e9: mov dword ptr [0x4df010], 0x3f800000 */
L_4123f3:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 4123f3: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4123f9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4123fb: test ah, 1 */
	if (!m->zf) goto L_41240a;	/* 4123fe: jne 0x41240a */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 412400: mov dword ptr [0x4df010], 0xbf800000 */
L_41240a:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 41240a: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 412410: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 412416: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 41241c: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 412422: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 412428: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41242a: test ah, 1 */
	if (!m->zf) goto L_412439;	/* 41242d: jne 0x412439 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 41242f: mov dword ptr [0x4e14fc], 0 */
L_412439:
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412439: add esp, 0x48 */
	m->esp += 4 + 0; return;	/* 41243c: ret  */
}

/* room_4388e0 (0x4388e0), lifted by tools/lift.py */
static void lift_4388e0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4388e0: sub esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4388e3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4388e4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4388e5: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4388e6: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4388e7: push 1 */
	M32((DWORD)(m->esp + 0x50u)) = 0xc2200000u;	/* 4388e9: mov dword ptr [esp + 0x50], 0xc2200000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 4388f1: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x42200000u;	/* 4388f9: mov dword ptr [esp + 0x58], 0x42200000 */
	m->esp -= 4; M32(m->esp) = 0x438906u; native_call(m, 0x41ef90u);	/* 438901: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 438906: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 438909: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x438914u; native_call(m, M32(0x4a9224u));	/* 43890e: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 438914: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 43891a: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 438920: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 438926: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43892c: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 43892e: mov dword ptr [esp + 0x1c], eax */
	goto L_438938;	/* 438932: jmp 0x438938 */
L_438934:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 438934: mov eax, dword ptr [esp + 0x1c] */
L_438938:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438938: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 43893b: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 438943: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 43894b: mov dword ptr [esp + 0x40], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3e800000u;	/* 438953: mov dword ptr [esp + 0x44], 0x3e800000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f000000u;	/* 43895b: mov dword ptr [esp + 0x38], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_43898d;	/* 438963: jle 0x43898d */
	M32((DWORD)(m->esp + 0x28u)) = 0x3f000000u;	/* 438965: mov dword ptr [esp + 0x28], 0x3f000000 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 43896d: mov dword ptr [esp + 0x30], 0 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3ef00000u;	/* 438975: mov dword ptr [esp + 0x40], 0x3ef00000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f200000u;	/* 43897d: mov dword ptr [esp + 0x44], 0x3f200000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 438985: mov dword ptr [esp + 0x38], 0x3f800000 */
L_43898d:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43898d: cmp eax, 2 */
	if (m->sf == m->of) goto L_4389c2;	/* 438990: jge 0x4389c2 */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 438992: mov eax, dword ptr [0x4e0cd0] */
	m->ecx = m->eax;	/* 438997: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 438999: and ecx, 0x800001ff */
	if (!m->sf) goto L_4389a9;	/* 43899f: jns 0x4389a9 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4389a1: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4389a2: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4389a8: inc ecx */
L_4389a9:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4389a9: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4389aa: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4389b0: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4389b1: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4389b3: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4389b9: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4389bc: mov ecx, dword ptr [edx + eax*4 + 4] */
	goto L_4389f7;	/* 4389c0: jmp 0x4389f7 */
L_4389c2:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4389c2: shl eax, 2 */
	m->ecx = 0x4df910u;	/* 4389c5: mov ecx, 0x4df910 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4389ca: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 4389cc: mov eax, dword ptr [ecx] */
	m->edx = m->eax;	/* 4389ce: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4389d0: and edx, 0x800001ff */
	if (!m->sf) goto L_4389e0;	/* 4389d6: jns 0x4389e0 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4389d8: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4389d9: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4389df: inc edx */
L_4389e0:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4389e0: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4389e1: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4389e7: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4389e8: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4389ee: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4389f0: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4389f3: mov ecx, dword ptr [ecx + eax*4 + 4] */
L_4389f7:
	m->esp -= 4; M32(m->esp) = 0x4389fcu; native_call(m, 0x4566c0u);	/* 4389f7: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 4389fc: mov dword ptr [esp + 0x18], 0 */
L_438a04:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438a04: mov eax, dword ptr [esp + 0x18] */
	m->ecx = 0x3u;	/* 438a08: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 438a0d: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 438a0e: idiv ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 438a10: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x438a19u; native_call(m, 0x41f050u);	/* 438a14: call 0x41f050 */
	m->edx = M32((DWORD)(0x9dd698u));	/* 438a19: mov edx, dword ptr [0x9dd698] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438a1f: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438a20: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438a22: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438a2au; native_call(m, M32(0x4a9214u));	/* 438a24: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438a2a: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_438a3c;	/* 438a2f: jge 0x438a3c */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 438a31: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + m->eax*4 + 0x4cu));	/* 438a35: mov ecx, dword ptr [esp + eax*4 + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438a39: push ecx */
	goto L_438a4a;	/* 438a3a: jmp 0x438a4a */
L_438a3c:
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 438a3c: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438a40: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->edx*4 + 0x50u)));	/* 438a41: fld dword ptr [esp + edx*4 + 0x50] */
	ST(0) = -ST(0);	/* 438a45: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438a47: fstp dword ptr [esp] */
L_438a4a:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438a4a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438a4c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438a53u; native_call(m, 0x41ef20u);	/* 438a4e: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 438a53: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 438a57: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438a5a: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_438c17;	/* 438a5d: ja 0x438c17 */
	switch (m->eax) { case 0: goto L_438a6a; case 1: goto L_438a97; case 2: goto L_438ab6; case 3: goto L_438bfe; default: abort(); }	/* 438a63: jmp dword ptr [eax*4 + 0x4392a8] */
L_438a6a:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 438a6a: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 438a70: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438a76: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 438a77: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438a7d: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438a80: push 0x3f333333 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438a85: push 0 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438a87: push 0x3f333333 */
	m->esp -= 4; M32(m->esp) = 0x438a92u; native_call(m, M32(0x4a9228u));	/* 438a8c: call dword ptr [0x4a9228] */
	goto L_438ef1;	/* 438a92: jmp 0x438ef1 */
L_438a97:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438a97: push 0x3f333333 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 438a9c: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 438aa1: push 0x3dcccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438aa6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438ab1u; native_call(m, M32(0x4a9228u));	/* 438aab: call dword ptr [0x4a9228] */
	goto L_438c20;	/* 438ab1: jmp 0x438c20 */
L_438ab6:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438ab6: cmp dword ptr [esp + 0x18], -1 */
	if (!m->zf) goto L_438aea;	/* 438abb: jne 0x438aea */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 438abd: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9428u));	/* 438ac3: fmul dword ptr [0x4a9428] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438ac9: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438aca: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438ad0: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438ad3: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 438ad8: push 0x3dcccccd */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438add: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x438ae8u; native_call(m, M32(0x4a9228u));	/* 438ae2: call dword ptr [0x4a9228] */
	goto L_438b03;	/* 438ae8: jmp 0x438b03 */
L_438aea:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438aea: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438aec: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438aee: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438af0: push 0 */
L_438af2:
	m->esp -= 4; M32(m->esp) = 0x438af8u; native_call(m, M32(0x4a9228u));	/* 438af2: call dword ptr [0x4a9228] */
L_438af8:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438af8: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_439072;	/* 438afd: jge 0x439072 */
L_438b03:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 438b03: push 7 */
	m->esp -= 4; M32(m->esp) = 0x438b07u; native_call(m, m->ebx);	/* 438b05: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 438b07: fild dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 438b0b: fst dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 438b0f: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 438b15: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 438b19: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438b1d: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438b1e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438b22u; native_call(m, m->esi);	/* 438b20: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 438b22: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 438b26: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 438b2c: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 438b30: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 438b36: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 438b3a: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 438b3e: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 438b44: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 438b48: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438b4c: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438b4d: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 438b51: fild dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438b55: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438b59: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 438b5a: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 438b60: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 438b66: fstp dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 438b6a: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438b6e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x438b71u; native_call(m, m->edi);	/* 438b6f: call edi */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 438b71: mov edx, dword ptr [esp + 0x38] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 438b75: mov eax, dword ptr [esp + 0x20] */
	m->ecx = m->edx;	/* 438b79: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438b7b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438b7c: push ecx */
	M32((DWORD)(m->esp + 0x44u)) = m->edx;	/* 438b7d: mov dword ptr [esp + 0x44], edx */
	m->esp -= 4; M32(m->esp) = 0x438b83u; native_call(m, m->esi);	/* 438b81: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 438b83: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438b87: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 438b8d: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 438b91: mov ecx, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 438b95: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 438b99: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438b9d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438b9e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438b9f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x438ba2u; native_call(m, m->edi);	/* 438ba0: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 438ba2: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438ba6: fadd dword ptr [0x4a9424] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 438bac: mov eax, dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 438bb0: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 438bb6: fstp dword ptr [esp + 0x34] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 438bba: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438bbe: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438bbf: push eax */
	m->esp -= 4; M32(m->esp) = 0x438bc2u; native_call(m, m->esi);	/* 438bc0: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 438bc2: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 438bc6: fsub dword ptr [0x4a9418] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 438bcc: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 438bd0: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438bd4: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438bd5: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 438bd9: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438bdd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438bde: push eax */
	m->esp -= 4; M32(m->esp) = 0x438be1u; native_call(m, m->edi);	/* 438bdf: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 438be1: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438be5: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438be6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438beau; native_call(m, m->esi);	/* 438be8: call esi */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 438bea: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 438bee: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 438bf2: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438bf6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438bf7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438bf8: push ecx */
	goto L_439170;	/* 438bf9: jmp 0x439170 */
L_438bfe:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438bfe: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c03: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c08: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c0d: push 0x3f800000 */
	goto L_438af2;	/* 438c12: jmp 0x438af2 */
L_438c17:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438c17: cmp eax, 1 */
	if (!m->zf) goto L_438ee9;	/* 438c1a: jne 0x438ee9 */
L_438c20:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438c20: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c24: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438c26: cmp eax, 3 */
	if (m->sf == m->of) goto L_438d98;	/* 438c29: jge 0x438d98 */
	m->esp -= 4; M32(m->esp) = 0x438c31u; native_call(m, m->ebx);	/* 438c2f: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c31: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c33: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438c37u; native_call(m, m->esi);	/* 438c35: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438c37: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438c3d: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438c43: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438c44: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438c4a: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c4d: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c52: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438c59u; native_call(m, m->edi);	/* 438c57: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438c59: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438c5f: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c65: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438c67: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438c68: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438c6e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438c73u; native_call(m, m->esi);	/* 438c71: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c73: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c78: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c7d: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438c84u; native_call(m, m->edi);	/* 438c82: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438c84: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438c8a: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438c90: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438c95: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438c96: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438c9c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438ca1u; native_call(m, m->esi);	/* 438c9f: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438ca1: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438ca6: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438cab: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438cb2u; native_call(m, m->edi);	/* 438cb0: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438cb2: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438cb7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438cbbu; native_call(m, m->esi);	/* 438cb9: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438cbb: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438cc1: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438cc7: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438cc8: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438cce: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438cd1: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438cd6: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438cddu; native_call(m, m->edi);	/* 438cdb: call edi */
	m->esp -= 4; M32(m->esp) = 0x438cdfu; native_call(m, m->ebp);	/* 438cdd: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 438cdf: push 7 */
	m->esp -= 4; M32(m->esp) = 0x438ce3u; native_call(m, m->ebx);	/* 438ce1: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438ce3: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438ce9: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438cef: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438cf1: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438cf2: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438cf8: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438cfdu; native_call(m, m->esi);	/* 438cfb: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438cfd: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d02: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d07: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438d0eu; native_call(m, m->edi);	/* 438d0c: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d0e: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d10: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438d17u; native_call(m, m->esi);	/* 438d15: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438d17: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438d1d: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438d23: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438d24: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438d2a: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d2d: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d32: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438d39u; native_call(m, m->edi);	/* 438d37: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d39: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d3e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438d45u; native_call(m, m->esi);	/* 438d43: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438d45: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438d4b: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438d51: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438d52: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438d58: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d5b: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d60: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438d67u; native_call(m, m->edi);	/* 438d65: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438d67: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438d6d: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d73: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438d78: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438d79: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438d7f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438d84u; native_call(m, m->esi);	/* 438d82: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d84: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d89: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438d8e: push 0xc1ef3333 */
	goto L_439170;	/* 438d93: jmp 0x439170 */
L_438d98:
	m->esp -= 4; M32(m->esp) = 0x438d9au; native_call(m, m->ebx);	/* 438d98: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438d9a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438da0: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438da6: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438da8: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438da9: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438daeu; native_call(m, m->esi);	/* 438dac: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438dae: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438db3: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438db8: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438dbfu; native_call(m, m->edi);	/* 438dbd: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438dbf: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438dc1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438dc8u; native_call(m, m->esi);	/* 438dc6: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438dc8: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438dce: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438dd4: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438dd5: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438ddb: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438dde: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438de3: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438deau; native_call(m, m->edi);	/* 438de8: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438dea: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438def: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438df6u; native_call(m, m->esi);	/* 438df4: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438df6: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438dfc: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438e02: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438e03: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438e09: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e0c: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e11: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438e18u; native_call(m, m->edi);	/* 438e16: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438e18: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438e1e: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e24: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438e29: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438e2a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438e2fu; native_call(m, m->esi);	/* 438e2d: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e2f: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e34: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e39: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438e40u; native_call(m, m->edi);	/* 438e3e: call edi */
	m->esp -= 4; M32(m->esp) = 0x438e42u; native_call(m, m->ebp);	/* 438e40: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e42: push 7 */
	m->esp -= 4; M32(m->esp) = 0x438e46u; native_call(m, m->ebx);	/* 438e44: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e46: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e48: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438e4cu; native_call(m, m->esi);	/* 438e4a: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438e4c: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438e52: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438e58: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438e59: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438e5f: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e62: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e67: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438e6eu; native_call(m, m->edi);	/* 438e6c: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438e6e: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438e74: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e7a: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438e7c: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438e7d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438e82u; native_call(m, m->esi);	/* 438e80: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e82: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e87: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e8c: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438e93u; native_call(m, m->edi);	/* 438e91: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438e93: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438e99: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438e9f: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438ea4: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438ea5: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438eaau; native_call(m, m->esi);	/* 438ea8: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438eaa: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438eaf: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438eb4: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438ebbu; native_call(m, m->edi);	/* 438eb9: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438ebb: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438ec0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438ec4u; native_call(m, m->esi);	/* 438ec2: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438ec4: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438eca: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438ed0: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438ed1: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438ed7: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438eda: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438edf: push 0x41ef3333 */
	goto L_439170;	/* 438ee4: jmp 0x439170 */
L_438ee9:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 438ee9: test eax, eax */
	if (!m->zf) goto L_438af8;	/* 438eeb: jne 0x438af8 */
L_438ef1:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438ef1: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 438ef5: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438ef7: cmp eax, 3 */
	if (m->sf == m->of) goto L_438fb9;	/* 438efa: jge 0x438fb9 */
	m->esp -= 4; M32(m->esp) = 0x438f02u; native_call(m, m->ebx);	/* 438f00: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f02: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f07: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438f0bu; native_call(m, m->esi);	/* 438f09: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 438f0b: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 438f0f: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 438f15: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 438f19: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 438f1f: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 438f23: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 438f27: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 438f2d: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 438f31: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438f35: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438f36: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 438f3a: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438f3e: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f3f: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x438f46u; native_call(m, m->edi);	/* 438f44: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f46: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f4b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438f52u; native_call(m, m->esi);	/* 438f50: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 438f52: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438f56: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 438f5c: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 438f60: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 438f64: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438f68: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438f69: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f6a: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x438f71u; native_call(m, m->edi);	/* 438f6f: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f71: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f76: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438f7du; native_call(m, m->esi);	/* 438f7b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 438f7d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 438f81: fsub dword ptr [0x4a9418] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 438f87: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438f8b: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438f8c: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 438f90: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438f94: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f95: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x438f9cu; native_call(m, m->edi);	/* 438f9a: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438f9c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438fa1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438fa5u; native_call(m, m->esi);	/* 438fa3: call esi */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 438fa5: mov eax, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 438fa9: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438fad: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438fae: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438faf: push 0xc1f00000 */
	goto L_439170;	/* 438fb4: jmp 0x439170 */
L_438fb9:
	m->esp -= 4; M32(m->esp) = 0x438fbbu; native_call(m, m->ebx);	/* 438fb9: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438fbb: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438fc0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438fc7u; native_call(m, m->esi);	/* 438fc5: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 438fc7: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 438fcb: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 438fd1: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 438fd5: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 438fdb: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 438fdf: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 438fe3: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 438fe9: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 438fed: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438ff1: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438ff2: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438ff6: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438ffa: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438ffb: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x439002u; native_call(m, m->edi);	/* 439000: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439002: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439007: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43900bu; native_call(m, m->esi);	/* 439009: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 43900b: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 43900f: fadd dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 439015: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 439019: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 43901d: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439021: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439022: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439023: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x43902au; native_call(m, m->edi);	/* 439028: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43902a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43902f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x439033u; native_call(m, m->esi);	/* 439031: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 439033: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 439037: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 43903d: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439041: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 439042: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 439046: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43904a: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43904b: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x439052u; native_call(m, m->edi);	/* 439050: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439052: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439057: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43905eu; native_call(m, m->esi);	/* 43905c: call esi */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 43905e: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 439062: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439066: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439067: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439068: push 0x41f00000 */
	goto L_439170;	/* 43906d: jmp 0x439170 */
L_439072:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 439072: push 7 */
	m->esp -= 4; M32(m->esp) = 0x439076u; native_call(m, m->ebx);	/* 439074: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 439076: fild dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 43907a: mov eax, dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 43907e: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 439084: fst dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 439088: fadd dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 43908c: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 439090: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439094: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439095: push eax */
	m->esp -= 4; M32(m->esp) = 0x439098u; native_call(m, m->esi);	/* 439096: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 439098: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 43909c: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4390a2: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 4390a6: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4390ac: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4390b0: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4390b4: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4390ba: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4390be: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4390c2: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4390c3: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4390c7: fild dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4390cb: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4390cf: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 4390d0: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 4390d6: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4390dc: fstp dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 4390e0: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4390e4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4390e7u; native_call(m, m->edi);	/* 4390e5: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4390e7: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 4390eb: fadd dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4390ef: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4390f3: push ecx */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4390f4: fstp dword ptr [esp + 0x4c] */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 4390f8: mov edx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4390fc: push edx */
	m->esp -= 4; M32(m->esp) = 0x4390ffu; native_call(m, m->esi);	/* 4390fd: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4390ff: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 439103: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 439109: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 43910d: mov edx, dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 439111: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 439115: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439119: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43911a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43911b: push edx */
	m->esp -= 4; M32(m->esp) = 0x43911eu; native_call(m, m->edi);	/* 43911c: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 43911e: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 439122: fadd dword ptr [esp + 0x44] */
	m->ecx = M32((DWORD)(m->esp + 0x48u));	/* 439126: mov ecx, dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 43912a: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 43912e: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439132: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439133: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439136u; native_call(m, m->esi);	/* 439134: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 439136: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 43913a: fsub dword ptr [0x4a9418] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 439140: mov edx, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 439144: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439148: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 439149: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 43914d: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439151: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439152: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439155u; native_call(m, m->edi);	/* 439153: call edi */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 439155: mov edx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 439159: mov eax, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43915d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43915e: push eax */
	m->esp -= 4; M32(m->esp) = 0x439161u; native_call(m, m->esi);	/* 43915f: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 439161: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 439165: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 439169: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43916d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43916e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43916f: push eax */
L_439170:
	m->esp -= 4; M32(m->esp) = 0x439172u; native_call(m, m->edi);	/* 439170: call edi */
	m->esp -= 4; M32(m->esp) = 0x439174u; native_call(m, m->ebp);	/* 439172: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 439174: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 439178: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 439179: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 43917c: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_438a04;	/* 439180: jl 0x438a04 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 439186: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 43918a: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43918b: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 43918e: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_438934;	/* 439192: jl 0x438934 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439198: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4391a3u; native_call(m, M32(0x4a922cu));	/* 43919d: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 4391a3: mov eax, dword ptr [0x680398] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4391a8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4391a9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4391aa: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4391ab: test eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4391ad: pop ebx */
	if (m->zf) goto L_439212;	/* 4391ae: je 0x439212 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 4391b0: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 4391b6: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 4391bc: fadd dword ptr [0x680ccc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 4391c2: fst dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 4391c8: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4391ce: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4391d0: test ah, 0x41 */
	if (m->zf) goto L_4391eb;	/* 4391d3: je 0x4391eb */
	M32((DWORD)(0x680cccu)) = 0x40000000u;	/* 4391d5: mov dword ptr [0x680ccc], 0x40000000 */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 4391df: mov dword ptr [0x4df454], 0x3f800000 */
	goto L_439212;	/* 4391e9: jmp 0x439212 */
L_4391eb:
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 4391eb: fld dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 4391f1: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4391f7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4391f9: test ah, 1 */
	if (!m->zf) goto L_439212;	/* 4391fc: jne 0x439212 */
	M32((DWORD)(0x680cccu)) = 0x42180000u;	/* 4391fe: mov dword ptr [0x680ccc], 0x42180000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 439208: mov dword ptr [0x4df454], 0xbf800000 */
L_439212:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 439212: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 439218: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 43921e: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 439224: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 43922a: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 439230: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 439232: test ah, 0x41 */
	if (m->zf) goto L_43924d;	/* 439235: je 0x43924d */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 439237: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 439241: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_439274;	/* 43924b: jmp 0x439274 */
L_43924d:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 43924d: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 439253: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 439259: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43925b: test ah, 1 */
	if (!m->zf) goto L_439274;	/* 43925e: jne 0x439274 */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 439260: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 43926a: mov dword ptr [0x4df010], 0xbf800000 */
L_439274:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 439274: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 43927a: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 439280: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 439286: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 43928c: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 439292: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 439294: test ah, 1 */
	if (!m->zf) goto L_4392a3;	/* 439297: jne 0x4392a3 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 439299: mov dword ptr [0x4e14fc], 0 */
L_4392a3:
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4392a3: add esp, 0x48 */
	m->esp += 4 + 0; return;	/* 4392a6: ret  */
}

/* arena_4091b0 (0x4091b0), lifted by tools/lift.py */
static void lift_4091b0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4091b0: sub esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4091b3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4091b4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4091b5: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4091b6: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4091b7: push 1 */
	M32((DWORD)(m->esp + 0x54u)) = 0xc20c0000u;	/* 4091b9: mov dword ptr [esp + 0x54], 0xc20c0000 */
	M32((DWORD)(m->esp + 0x58u)) = 0x420c0000u;	/* 4091c1: mov dword ptr [esp + 0x58], 0x420c0000 */
	m->esp -= 4; M32(m->esp) = 0x4091ceu; native_call(m, 0x41ef90u);	/* 4091c9: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4091ce: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4091d1: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4091dcu; native_call(m, M32(0x4a9224u));	/* 4091d6: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 4091dc: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4091e2: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 4091e8: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 4091ee: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4091f4: xor eax, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4091f6: mov dword ptr [esp + 0x24], eax */
	goto L_409200;	/* 4091fa: jmp 0x409200 */
L_4091fc:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4091fc: mov eax, dword ptr [esp + 0x24] */
L_409200:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409200: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 409203: mov dword ptr [esp + 0x1c], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3f000000u;	/* 40920b: mov dword ptr [esp + 0x34], 0x3f000000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x0u;	/* 409213: mov dword ptr [esp + 0x44], 0 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3e800000u;	/* 40921b: mov dword ptr [esp + 0x48], 0x3e800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f000000u;	/* 409223: mov dword ptr [esp + 0x3c], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_409255;	/* 40922b: jle 0x409255 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x3f000000u;	/* 40922d: mov dword ptr [esp + 0x1c], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 409235: mov dword ptr [esp + 0x34], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f000000u;	/* 40923d: mov dword ptr [esp + 0x44], 0x3f000000 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3f400000u;	/* 409245: mov dword ptr [esp + 0x48], 0x3f400000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f800000u;	/* 40924d: mov dword ptr [esp + 0x3c], 0x3f800000 */
L_409255:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409255: cmp eax, 2 */
	if (m->sf == m->of) goto L_40928a;	/* 409258: jge 0x40928a */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 40925a: mov eax, dword ptr [0x4e0cd0] */
	m->ecx = m->eax;	/* 40925f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 409261: and ecx, 0x800001ff */
	if (!m->sf) goto L_409271;	/* 409267: jns 0x409271 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 409269: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40926a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 409270: inc ecx */
L_409271:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 409271: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 409272: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409278: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409279: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40927b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 409281: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 409284: mov ecx, dword ptr [edx + eax*4 + 4] */
	goto L_4092bf;	/* 409288: jmp 0x4092bf */
L_40928a:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40928a: shl eax, 2 */
	m->ecx = 0x4df04cu;	/* 40928d: mov ecx, 0x4df04c */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409292: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 409294: mov eax, dword ptr [ecx] */
	m->edx = m->eax;	/* 409296: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 409298: and edx, 0x800001ff */
	if (!m->sf) goto L_4092a8;	/* 40929e: jns 0x4092a8 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4092a0: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4092a1: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4092a7: inc edx */
L_4092a8:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4092a8: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4092a9: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4092af: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4092b0: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4092b6: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4092b8: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4092bb: mov ecx, dword ptr [ecx + eax*4 + 4] */
L_4092bf:
	m->esp -= 4; M32(m->esp) = 0x4092c4u; native_call(m, 0x4566c0u);	/* 4092bf: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 4092c4: mov dword ptr [esp + 0x20], 0 */
L_4092cc:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4092cc: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4092d0: and eax, 0x80000001 */
	if (!m->sf) goto L_4092dc;	/* 4092d5: jns 0x4092dc */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4092d7: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4092d8: or eax, 0xfffffffe */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4092db: inc eax */
L_4092dc:
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 4092dc: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x4092e5u; native_call(m, 0x41f050u);	/* 4092e0: call 0x41f050 */
	m->edx = M32((DWORD)(0x4dba68u));	/* 4092e5: mov edx, dword ptr [0x4dba68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4092eb: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4092ec: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4092ee: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4092f6u; native_call(m, M32(0x4a9214u));	/* 4092f0: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4092f6: cmp dword ptr [esp + 0x20], 2 */
	if (m->sf == m->of) goto L_409308;	/* 4092fb: jge 0x409308 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4092fd: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + m->eax*4 + 0x50u));	/* 409301: mov ecx, dword ptr [esp + eax*4 + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409305: push ecx */
	goto L_409316;	/* 409306: jmp 0x409316 */
L_409308:
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 409308: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40930c: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->edx*4 + 0x54u)));	/* 40930d: fld dword ptr [esp + edx*4 + 0x54] */
	ST(0) = -ST(0);	/* 409311: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409313: fstp dword ptr [esp] */
L_409316:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409316: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409318: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40931fu; native_call(m, 0x41ef20u);	/* 40931a: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 40931f: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409323: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409326: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_4094f4;	/* 409329: ja 0x4094f4 */
	switch (m->eax) { case 0: goto L_409336; case 1: goto L_409366; case 2: goto L_409385; case 3: goto L_4094db; default: abort(); }	/* 40932f: jmp dword ptr [eax*4 + 0x409bb0] */
L_409336:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 409336: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 40933c: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409342: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 409343: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409349: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40934c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409351: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409356: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409361u; native_call(m, M32(0x4a9228u));	/* 40935b: call dword ptr [0x4a9228] */
	goto L_4097ce;	/* 409361: jmp 0x4097ce */
L_409366:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 409366: push 0x3ecccccd */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40936b: push 0x41200000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409370: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409375: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409380u; native_call(m, M32(0x4a9228u));	/* 40937a: call dword ptr [0x4a9228] */
	goto L_4094fd;	/* 409380: jmp 0x4094fd */
L_409385:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409385: cmp dword ptr [esp + 0x20], -1 */
	if (!m->zf) goto L_4093b9;	/* 40938a: jne 0x4093b9 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 40938c: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9428u));	/* 409392: fmul dword ptr [0x4a9428] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409398: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 409399: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 40939f: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093a2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093a7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093ac: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4093b7u; native_call(m, M32(0x4a9228u));	/* 4093b1: call dword ptr [0x4a9228] */
	goto L_4093d2;	/* 4093b7: jmp 0x4093d2 */
L_4093b9:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093b9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093bb: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093bd: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093bf: push 0 */
L_4093c1:
	m->esp -= 4; M32(m->esp) = 0x4093c7u; native_call(m, M32(0x4a9228u));	/* 4093c1: call dword ptr [0x4a9228] */
L_4093c7:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4093c7: cmp dword ptr [esp + 0x20], 2 */
	if (m->sf == m->of) goto L_40996b;	/* 4093cc: jge 0x40996b */
L_4093d2:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093d2: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4093d6u; native_call(m, m->ebx);	/* 4093d4: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 4093d6: fild dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 4093da: fst dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 4093de: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4093e4: fstp dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4093e8: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4093ec: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4093ed: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4093f1u; native_call(m, m->esi);	/* 4093ef: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4093f1: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4093f5: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4093fb: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 4093ff: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 409405: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 409409: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 40940d: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 409411: fmul dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 409417: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40941b: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 40941c: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 409420: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 409426: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 40942a: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 40942e: fild dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 409432: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409436: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 409437: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 40943d: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 409443: fstp dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 409447: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40944b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40944eu; native_call(m, m->edi);	/* 40944c: call edi */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 40944e: mov edx, dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 409452: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = m->edx;	/* 409456: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409458: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409459: push ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 40945a: mov dword ptr [esp + 0x48], edx */
	m->esp -= 4; M32(m->esp) = 0x409460u; native_call(m, m->esi);	/* 40945e: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 409460: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 409464: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 40946a: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 40946e: mov ecx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 409472: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 409476: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40947a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40947b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40947c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40947fu; native_call(m, m->edi);	/* 40947d: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 40947f: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 409483: fadd dword ptr [0x4a9424] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 409489: mov eax, dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 40948d: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 409493: fstp dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 409497: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40949b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40949c: push eax */
	m->esp -= 4; M32(m->esp) = 0x40949fu; native_call(m, m->esi);	/* 40949d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 40949f: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4094a3: fsub dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4094a9: mov ecx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4094ad: mov eax, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4094b1: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4094b2: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4094b6: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4094ba: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4094bb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4094beu; native_call(m, m->edi);	/* 4094bc: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4094be: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4094c2: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4094c3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4094c7u; native_call(m, m->esi);	/* 4094c5: call esi */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 4094c7: mov edx, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4094cb: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4094cf: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4094d3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4094d4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4094d5: push ecx */
	goto L_409a77;	/* 4094d6: jmp 0x409a77 */
L_4094db:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4094db: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4094e0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4094e5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4094ea: push 0x3f800000 */
	goto L_4093c1;	/* 4094ef: jmp 0x4093c1 */
L_4094f4:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4094f4: cmp eax, 1 */
	if (!m->zf) goto L_4097c6;	/* 4094f7: jne 0x4097c6 */
L_4094fd:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4094fd: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 409501: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409503: cmp eax, 2 */
	if (m->sf == m->of) goto L_409675;	/* 409506: jge 0x409675 */
	m->esp -= 4; M32(m->esp) = 0x40950eu; native_call(m, m->ebx);	/* 40950c: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40950e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409510: push 0 */
	m->esp -= 4; M32(m->esp) = 0x409514u; native_call(m, m->esi);	/* 409512: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409514: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 40951a: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409520: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 409521: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409527: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40952a: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40952f: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x409536u; native_call(m, m->edi);	/* 409534: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409536: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 40953c: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409542: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409544: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 409545: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 40954b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x409550u; native_call(m, m->esi);	/* 40954e: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409550: push 0xc2200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409555: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40955a: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x409561u; native_call(m, m->edi);	/* 40955f: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409561: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 409567: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40956d: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409572: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 409573: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409579: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x40957eu; native_call(m, m->esi);	/* 40957c: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40957e: push 0xc2200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409583: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 409588: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x40958fu; native_call(m, m->edi);	/* 40958d: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40958f: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409594: push 0 */
	m->esp -= 4; M32(m->esp) = 0x409598u; native_call(m, m->esi);	/* 409596: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409598: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 40959e: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4095a4: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4095a5: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4095ab: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095ae: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095b3: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4095bau; native_call(m, m->edi);	/* 4095b8: call edi */
	m->esp -= 4; M32(m->esp) = 0x4095bcu; native_call(m, m->ebp);	/* 4095ba: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095bc: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4095c0u; native_call(m, m->ebx);	/* 4095be: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4095c0: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4095c6: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095cc: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4095ce: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4095cf: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4095d5: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4095dau; native_call(m, m->esi);	/* 4095d8: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095da: push 0x42200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095df: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095e4: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4095ebu; native_call(m, m->edi);	/* 4095e9: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095eb: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4095ed: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4095f4u; native_call(m, m->esi);	/* 4095f2: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4095f4: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4095fa: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409600: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 409601: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409607: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40960a: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40960f: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x409616u; native_call(m, m->edi);	/* 409614: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409616: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40961b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409622u; native_call(m, m->esi);	/* 409620: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409622: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 409628: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40962e: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 40962f: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409635: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409638: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40963d: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x409644u; native_call(m, m->edi);	/* 409642: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409644: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 40964a: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409650: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409655: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 409656: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 40965c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x409661u; native_call(m, m->esi);	/* 40965f: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409661: push 0x42200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409666: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 40966b: push 0xc1ef3333 */
	goto L_409a77;	/* 409670: jmp 0x409a77 */
L_409675:
	m->esp -= 4; M32(m->esp) = 0x409677u; native_call(m, m->ebx);	/* 409675: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409677: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 40967d: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409683: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409685: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409686: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x40968bu; native_call(m, m->esi);	/* 409689: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40968b: push 0xc2200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409690: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 409695: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x40969cu; native_call(m, m->edi);	/* 40969a: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40969c: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40969e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4096a5u; native_call(m, m->esi);	/* 4096a3: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4096a5: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4096ab: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4096b1: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4096b2: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4096b8: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4096bb: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4096c0: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4096c7u; native_call(m, m->edi);	/* 4096c5: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4096c7: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4096cc: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4096d3u; native_call(m, m->esi);	/* 4096d1: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4096d3: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4096d9: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4096df: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4096e0: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4096e6: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4096e9: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4096ee: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4096f5u; native_call(m, m->edi);	/* 4096f3: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4096f5: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4096fb: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409701: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409706: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409707: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x40970cu; native_call(m, m->esi);	/* 40970a: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40970c: push 0xc2200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409711: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 409716: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x40971du; native_call(m, m->edi);	/* 40971b: call edi */
	m->esp -= 4; M32(m->esp) = 0x40971fu; native_call(m, m->ebp);	/* 40971d: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40971f: push 7 */
	m->esp -= 4; M32(m->esp) = 0x409723u; native_call(m, m->ebx);	/* 409721: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409723: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409725: push 0 */
	m->esp -= 4; M32(m->esp) = 0x409729u; native_call(m, m->esi);	/* 409727: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409729: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 40972f: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409735: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 409736: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 40973c: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40973f: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 409744: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x40974bu; native_call(m, m->edi);	/* 409749: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 40974b: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 409751: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409757: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409759: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 40975a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x40975fu; native_call(m, m->esi);	/* 40975d: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40975f: push 0x42200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409764: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 409769: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x409770u; native_call(m, m->edi);	/* 40976e: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 409770: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 409776: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40977c: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409781: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 409782: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x409787u; native_call(m, m->esi);	/* 409785: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409787: push 0x42200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40978c: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 409791: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x409798u; native_call(m, m->edi);	/* 409796: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409798: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40979d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4097a1u; native_call(m, m->esi);	/* 40979f: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4097a1: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4097a7: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4097ad: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4097ae: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4097b4: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4097b7: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4097bc: push 0x41ef3333 */
	goto L_409a77;	/* 4097c1: jmp 0x409a77 */
L_4097c6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4097c6: test eax, eax */
	if (!m->zf) goto L_4093c7;	/* 4097c8: jne 0x4093c7 */
L_4097ce:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4097ce: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4097d2: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4097d4: cmp eax, 2 */
	if (m->sf == m->of) goto L_4098a4;	/* 4097d7: jge 0x4098a4 */
	m->esp -= 4; M32(m->esp) = 0x4097dfu; native_call(m, m->ebx);	/* 4097dd: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4097df: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4097e4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4097e8u; native_call(m, m->esi);	/* 4097e6: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4097e8: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4097ec: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4097f2: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 4097f6: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4097fc: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 409800: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 409804: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 409808: fmul dword ptr [0x4a9410] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 40980e: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409812: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 409813: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 409817: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 40981d: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 409821: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 409825: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409829: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40982a: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x409831u; native_call(m, m->edi);	/* 40982f: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409831: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409836: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40983du; native_call(m, m->esi);	/* 40983b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 40983d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 409841: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 409847: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 40984b: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 40984f: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409853: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409854: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409855: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x40985cu; native_call(m, m->edi);	/* 40985a: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40985c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409861: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409868u; native_call(m, m->esi);	/* 409866: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 409868: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 40986c: fsub dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 409872: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409876: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 409877: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 40987b: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40987f: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409880: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x409887u; native_call(m, m->edi);	/* 409885: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409887: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40988c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x409890u; native_call(m, m->esi);	/* 40988e: call esi */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 409890: mov eax, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 409894: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409898: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409899: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40989a: push 0xc1f00000 */
	goto L_409a77;	/* 40989f: jmp 0x409a77 */
L_4098a4:
	m->esp -= 4; M32(m->esp) = 0x4098a6u; native_call(m, m->ebx);	/* 4098a4: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4098a6: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4098ab: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4098b2u; native_call(m, m->esi);	/* 4098b0: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4098b2: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4098b6: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4098bc: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 4098c0: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4098c6: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 4098ca: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4098ce: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4098d2: fmul dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 4098d8: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4098dc: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4098dd: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 4098e1: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 4098e7: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4098eb: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4098ef: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4098f3: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4098f4: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4098fbu; native_call(m, m->edi);	/* 4098f9: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4098fb: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409900: push 0 */
	m->esp -= 4; M32(m->esp) = 0x409904u; native_call(m, m->esi);	/* 409902: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 409904: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 409908: fadd dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 40990e: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 409912: fstp dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 409916: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40991a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40991b: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40991c: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x409923u; native_call(m, m->edi);	/* 409921: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409923: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409928: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40992cu; native_call(m, m->esi);	/* 40992a: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 40992c: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 409930: fsub dword ptr [0x4a9410] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 409936: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40993a: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 40993b: fstp dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 40993f: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409943: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409944: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x40994bu; native_call(m, m->edi);	/* 409949: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40994b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409950: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409957u; native_call(m, m->esi);	/* 409955: call esi */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 409957: mov edx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 40995b: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40995f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409960: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409961: push 0x41f00000 */
	goto L_409a77;	/* 409966: jmp 0x409a77 */
L_40996b:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40996b: push 7 */
	m->esp -= 4; M32(m->esp) = 0x40996fu; native_call(m, m->ebx);	/* 40996d: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 40996f: fild dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 409973: mov eax, dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 409977: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 40997d: fst dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 409981: fadd dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 409985: fstp dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 409989: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40998d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40998e: push eax */
	m->esp -= 4; M32(m->esp) = 0x409991u; native_call(m, m->esi);	/* 40998f: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 409991: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 409995: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 40999b: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 40999f: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4099a5: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 4099a9: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4099ad: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4099b1: fmul dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4099b7: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4099bb: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4099bc: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 4099c0: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 4099c6: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4099ca: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4099ce: fild dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4099d2: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4099d6: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 4099d7: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 4099dd: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4099e3: fstp dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 4099e7: mov eax, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4099eb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4099eeu; native_call(m, m->edi);	/* 4099ec: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4099ee: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 4099f2: fadd dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4099f6: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4099fa: push ecx */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4099fb: fstp dword ptr [esp + 0x50] */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 4099ff: mov edx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a03: push edx */
	m->esp -= 4; M32(m->esp) = 0x409a06u; native_call(m, m->esi);	/* 409a04: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 409a06: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 409a0a: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 409a10: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 409a14: mov edx, dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 409a18: fstp dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 409a1c: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409a20: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a21: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a22: push edx */
	m->esp -= 4; M32(m->esp) = 0x409a25u; native_call(m, m->edi);	/* 409a23: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 409a25: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 409a29: fadd dword ptr [esp + 0x48] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 409a2d: mov ecx, dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 409a31: fstp dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 409a35: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409a39: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a3a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x409a3du; native_call(m, m->esi);	/* 409a3b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 409a3d: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 409a41: fsub dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 409a47: mov edx, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 409a4b: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a4f: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 409a50: fstp dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 409a54: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409a58: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a59: push ecx */
	m->esp -= 4; M32(m->esp) = 0x409a5cu; native_call(m, m->edi);	/* 409a5a: call edi */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 409a5c: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 409a60: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a64: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409a65: push eax */
	m->esp -= 4; M32(m->esp) = 0x409a68u; native_call(m, m->esi);	/* 409a66: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 409a68: mov ecx, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 409a6c: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 409a70: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a74: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409a75: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409a76: push eax */
L_409a77:
	m->esp -= 4; M32(m->esp) = 0x409a79u; native_call(m, m->edi);	/* 409a77: call edi */
	m->esp -= 4; M32(m->esp) = 0x409a7bu; native_call(m, m->ebp);	/* 409a79: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 409a7b: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 409a7f: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409a80: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 409a83: mov dword ptr [esp + 0x20], eax */
	if (m->sf != m->of) goto L_4092cc;	/* 409a87: jl 0x4092cc */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 409a8d: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 409a91: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409a92: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 409a95: mov dword ptr [esp + 0x24], eax */
	if (m->sf != m->of) goto L_4091fc;	/* 409a99: jl 0x4091fc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 409a9f: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x409aaau; native_call(m, M32(0x4a922cu));	/* 409aa4: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 409aaa: mov eax, dword ptr [0x680398] */
	m->edi = M32(m->esp); m->esp += 4;	/* 409aaf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 409ab0: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 409ab1: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 409ab2: test eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 409ab4: pop ebx */
	if (m->zf) goto L_409b19;	/* 409ab5: je 0x409b19 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 409ab7: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 409abd: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 409ac3: fadd dword ptr [0x680ccc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 409ac9: fst dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 409acf: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 409ad5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 409ad7: test ah, 0x41 */
	if (m->zf) goto L_409af2;	/* 409ada: je 0x409af2 */
	M32((DWORD)(0x680cccu)) = 0x40000000u;	/* 409adc: mov dword ptr [0x680ccc], 0x40000000 */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 409ae6: mov dword ptr [0x4df454], 0x3f800000 */
	goto L_409b19;	/* 409af0: jmp 0x409b19 */
L_409af2:
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 409af2: fld dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 409af8: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 409afe: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 409b00: test ah, 1 */
	if (!m->zf) goto L_409b19;	/* 409b03: jne 0x409b19 */
	M32((DWORD)(0x680cccu)) = 0x42180000u;	/* 409b05: mov dword ptr [0x680ccc], 0x42180000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 409b0f: mov dword ptr [0x4df454], 0xbf800000 */
L_409b19:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 409b19: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 409b1f: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 409b25: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 409b2b: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 409b31: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 409b37: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 409b39: test ah, 0x41 */
	if (m->zf) goto L_409b54;	/* 409b3c: je 0x409b54 */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 409b3e: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 409b48: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_409b7b;	/* 409b52: jmp 0x409b7b */
L_409b54:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 409b54: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 409b5a: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 409b60: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 409b62: test ah, 1 */
	if (!m->zf) goto L_409b7b;	/* 409b65: jne 0x409b7b */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 409b67: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 409b71: mov dword ptr [0x4df010], 0xbf800000 */
L_409b7b:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 409b7b: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 409b81: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 409b87: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 409b8d: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 409b93: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 409b99: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 409b9b: test ah, 1 */
	if (!m->zf) goto L_409baa;	/* 409b9e: jne 0x409baa */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 409ba0: mov dword ptr [0x4e14fc], 0 */
L_409baa:
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409baa: add esp, 0x48 */
	m->esp += 4 + 0; return;	/* 409bad: ret  */
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
