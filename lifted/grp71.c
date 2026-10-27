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

static void lift_44d720(X86 *m);
static void lift_448140(X86 *m);

/* missionsel_448140 (0x448140), lifted by tools/lift.py */
static void lift_448140(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448140: sub esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 448143: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 448144: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 448145: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 448146: push edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 448147: push 1 */
	M32((DWORD)(m->esp + 0x50u)) = 0xc2200000u;	/* 448149: mov dword ptr [esp + 0x50], 0xc2200000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 448151: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x42200000u;	/* 448159: mov dword ptr [esp + 0x58], 0x42200000 */
	m->esp -= 4; M32(m->esp) = 0x448166u; native_call(m, 0x41ef90u);	/* 448161: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448166: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 448169: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x448174u; native_call(m, M32(0x4a9224u));	/* 44816e: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 448174: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 44817a: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 448180: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 448186: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44818c: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 44818e: mov dword ptr [esp + 0x1c], eax */
	goto L_448198;	/* 448192: jmp 0x448198 */
L_448194:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 448194: mov eax, dword ptr [esp + 0x1c] */
L_448198:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448198: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 44819b: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 4481a3: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 4481ab: mov dword ptr [esp + 0x40], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3e800000u;	/* 4481b3: mov dword ptr [esp + 0x44], 0x3e800000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f000000u;	/* 4481bb: mov dword ptr [esp + 0x38], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_4481ed;	/* 4481c3: jle 0x4481ed */
	M32((DWORD)(m->esp + 0x28u)) = 0x3f000000u;	/* 4481c5: mov dword ptr [esp + 0x28], 0x3f000000 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 4481cd: mov dword ptr [esp + 0x30], 0 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3ef00000u;	/* 4481d5: mov dword ptr [esp + 0x40], 0x3ef00000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f200000u;	/* 4481dd: mov dword ptr [esp + 0x44], 0x3f200000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 4481e5: mov dword ptr [esp + 0x38], 0x3f800000 */
L_4481ed:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4481ed: cmp eax, 2 */
	if (m->sf == m->of) goto L_448222;	/* 4481f0: jge 0x448222 */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 4481f2: mov eax, dword ptr [0x4e0cd0] */
	m->ecx = m->eax;	/* 4481f7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4481f9: and ecx, 0x800001ff */
	if (!m->sf) goto L_448209;	/* 4481ff: jns 0x448209 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 448201: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 448202: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 448208: inc ecx */
L_448209:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 448209: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44820a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448210: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 448211: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 448213: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 448219: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44821c: mov ecx, dword ptr [edx + eax*4 + 4] */
	goto L_448257;	/* 448220: jmp 0x448257 */
L_448222:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 448222: shl eax, 2 */
	m->ecx = 0x76d484u;	/* 448225: mov ecx, 0x76d484 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44822a: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 44822c: mov eax, dword ptr [ecx] */
	m->edx = m->eax;	/* 44822e: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 448230: and edx, 0x800001ff */
	if (!m->sf) goto L_448240;	/* 448236: jns 0x448240 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 448238: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 448239: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44823f: inc edx */
L_448240:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448240: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 448241: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 448247: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 448248: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44824e: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 448250: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 448253: mov ecx, dword ptr [ecx + eax*4 + 4] */
L_448257:
	m->esp -= 4; M32(m->esp) = 0x44825cu; native_call(m, 0x4566c0u);	/* 448257: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 44825c: mov dword ptr [esp + 0x18], 0 */
L_448264:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 448264: mov eax, dword ptr [esp + 0x18] */
	m->ecx = 0x3u;	/* 448268: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44826d: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 44826e: idiv ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 448270: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x448279u; native_call(m, 0x41f050u);	/* 448274: call 0x41f050 */
	{ DWORD v_ = 0xc4098000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448279: push 0xc4098000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44827e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448280: push 0 */
	m->esp -= 4; M32(m->esp) = 0x448288u; native_call(m, M32(0x4a9214u));	/* 448282: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448288: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_44829a;	/* 44828d: jge 0x44829a */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 44828f: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + m->edx*4 + 0x4cu));	/* 448293: mov eax, dword ptr [esp + edx*4 + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448297: push eax */
	goto L_4482a8;	/* 448298: jmp 0x4482a8 */
L_44829a:
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 44829a: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44829e: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->ecx*4 + 0x50u)));	/* 44829f: fld dword ptr [esp + ecx*4 + 0x50] */
	ST(0) = -ST(0);	/* 4482a3: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4482a5: fstp dword ptr [esp] */
L_4482a8:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4482a8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4482aa: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4482b1u; native_call(m, 0x41ef20u);	/* 4482ac: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 4482b1: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4482b5: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4482b8: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_448439;	/* 4482bb: ja 0x448439 */
	switch (m->eax) { case 0: goto L_4482c8; case 1: goto L_4482f8; case 2: goto L_448994; case 3: goto L_448317; default: abort(); }	/* 4482c1: jmp dword ptr [eax*4 + 0x448aac] */
L_4482c8:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 4482c8: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 4482ce: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4482d4: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4482d5: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4482db: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4482de: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4482e3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4482e8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4482f3u; native_call(m, M32(0x4a9228u));	/* 4482ed: call dword ptr [0x4a9228] */
	goto L_448713;	/* 4482f3: jmp 0x448713 */
L_4482f8:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4482f8: push 0x3ecccccd */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4482fd: push 0x41200000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448302: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448307: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448312u; native_call(m, M32(0x4a9228u));	/* 44830c: call dword ptr [0x4a9228] */
	goto L_448442;	/* 448312: jmp 0x448442 */
L_448317:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448317: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44831c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448321: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448326: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448331u; native_call(m, M32(0x4a9228u));	/* 44832b: call dword ptr [0x4a9228] */
L_448331:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 448331: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 448335: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448337: cmp eax, 3 */
	if (m->sf == m->of) goto L_448894;	/* 44833a: jge 0x448894 */
	m->esp -= 4; M32(m->esp) = 0x448342u; native_call(m, m->ebx);	/* 448340: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 448342: fild dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 448346: fst dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 44834a: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 448350: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 448354: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448358: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448359: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44835du; native_call(m, m->esi);	/* 44835b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 44835d: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 448361: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 448367: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 44836b: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 448371: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 448375: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 448379: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44837f: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 448383: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448387: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 448388: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 44838c: fild dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 448390: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448394: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 448395: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 44839b: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 4483a1: fstp dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 4483a5: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4483a9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4483acu; native_call(m, m->edi);	/* 4483aa: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4483ac: mov ecx, dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4483b0: mov edx, dword ptr [esp + 0x20] */
	m->eax = m->ecx;	/* 4483b4: mov eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4483b6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4483b7: push eax */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 4483b8: mov dword ptr [esp + 0x44], ecx */
	m->esp -= 4; M32(m->esp) = 0x4483beu; native_call(m, m->esi);	/* 4483bc: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4483be: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4483c2: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4483c8: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4483cc: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4483d0: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4483d4: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4483d8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4483d9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4483da: push eax */
	m->esp -= 4; M32(m->esp) = 0x4483ddu; native_call(m, m->edi);	/* 4483db: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 4483dd: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4483e1: fadd dword ptr [0x4a9424] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 4483e7: mov edx, dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 4483eb: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 4483f1: fstp dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 4483f5: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4483f9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4483fa: push edx */
	m->esp -= 4; M32(m->esp) = 0x4483fdu; native_call(m, m->esi);	/* 4483fb: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4483fd: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 448401: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 448407: mov eax, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 44840b: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44840f: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 448410: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 448414: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448418: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448419: push edx */
	m->esp -= 4; M32(m->esp) = 0x44841cu; native_call(m, m->edi);	/* 44841a: call edi */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 44841c: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448420: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448421: push 0 */
	m->esp -= 4; M32(m->esp) = 0x448425u; native_call(m, m->esi);	/* 448423: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 448425: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 448429: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 44842d: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448431: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448432: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448433: push eax */
	goto L_448990;	/* 448434: jmp 0x448990 */
L_448439:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448439: cmp eax, 1 */
	if (!m->zf) goto L_44870b;	/* 44843c: jne 0x44870b */
L_448442:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 448442: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 448446: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448448: cmp eax, 3 */
	if (m->sf == m->of) goto L_4485ba;	/* 44844b: jge 0x4485ba */
	m->esp -= 4; M32(m->esp) = 0x448453u; native_call(m, m->ebx);	/* 448451: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448453: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448455: push 0 */
	m->esp -= 4; M32(m->esp) = 0x448459u; native_call(m, m->esi);	/* 448457: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 448459: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 44845f: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448465: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 448466: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44846c: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44846f: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448474: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x44847bu; native_call(m, m->edi);	/* 448479: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 44847b: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 448481: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448487: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448489: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 44848a: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 448490: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x448495u; native_call(m, m->esi);	/* 448493: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448495: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44849a: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44849f: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4484a6u; native_call(m, m->edi);	/* 4484a4: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4484a6: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4484ac: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4484b2: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4484b7: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4484b8: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4484be: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4484c3u; native_call(m, m->esi);	/* 4484c1: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4484c3: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4484c8: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4484cd: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4484d4u; native_call(m, m->edi);	/* 4484d2: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4484d4: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4484d9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4484ddu; native_call(m, m->esi);	/* 4484db: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4484dd: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4484e3: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4484e9: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4484ea: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4484f0: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4484f3: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4484f8: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4484ffu; native_call(m, m->edi);	/* 4484fd: call edi */
	m->esp -= 4; M32(m->esp) = 0x448501u; native_call(m, m->ebp);	/* 4484ff: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 448501: push 7 */
	m->esp -= 4; M32(m->esp) = 0x448505u; native_call(m, m->ebx);	/* 448503: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 448505: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 44850b: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448511: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448513: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 448514: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44851a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x44851fu; native_call(m, m->esi);	/* 44851d: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44851f: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448524: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448529: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x448530u; native_call(m, m->edi);	/* 44852e: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448530: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448532: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448539u; native_call(m, m->esi);	/* 448537: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 448539: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 44853f: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448545: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 448546: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44854c: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44854f: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448554: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x44855bu; native_call(m, m->edi);	/* 448559: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44855b: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448560: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448567u; native_call(m, m->esi);	/* 448565: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 448567: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 44856d: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448573: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 448574: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44857a: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44857d: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448582: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x448589u; native_call(m, m->edi);	/* 448587: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 448589: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 44858f: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448595: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44859a: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 44859b: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4485a1: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4485a6u; native_call(m, m->esi);	/* 4485a4: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485a6: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485ab: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485b0: push 0xc1ef3333 */
	goto L_448990;	/* 4485b5: jmp 0x448990 */
L_4485ba:
	m->esp -= 4; M32(m->esp) = 0x4485bcu; native_call(m, m->ebx);	/* 4485ba: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4485bc: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4485c2: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485c8: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4485ca: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4485cb: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4485d0u; native_call(m, m->esi);	/* 4485ce: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485d0: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485d5: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485da: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4485e1u; native_call(m, m->edi);	/* 4485df: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485e1: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4485e3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4485eau; native_call(m, m->esi);	/* 4485e8: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4485ea: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4485f0: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4485f6: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4485f7: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4485fd: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448600: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448605: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x44860cu; native_call(m, m->edi);	/* 44860a: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44860c: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448611: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448618u; native_call(m, m->esi);	/* 448616: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 448618: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 44861e: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448624: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 448625: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44862b: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44862e: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448633: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x44863au; native_call(m, m->edi);	/* 448638: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 44863a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 448640: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448646: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44864b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44864c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x448651u; native_call(m, m->esi);	/* 44864f: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448651: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448656: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44865b: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x448662u; native_call(m, m->edi);	/* 448660: call edi */
	m->esp -= 4; M32(m->esp) = 0x448664u; native_call(m, m->ebp);	/* 448662: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 448664: push 7 */
	m->esp -= 4; M32(m->esp) = 0x448668u; native_call(m, m->ebx);	/* 448666: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448668: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44866a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44866eu; native_call(m, m->esi);	/* 44866c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 44866e: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 448674: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44867a: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 44867b: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 448681: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448684: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448689: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x448690u; native_call(m, m->edi);	/* 44868e: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 448690: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 448696: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44869c: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44869e: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44869f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4486a4u; native_call(m, m->esi);	/* 4486a2: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486a4: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486a9: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486ae: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4486b5u; native_call(m, m->edi);	/* 4486b3: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4486b5: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4486bb: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486c1: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4486c6: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4486c7: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4486ccu; native_call(m, m->esi);	/* 4486ca: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486cc: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486d1: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486d6: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4486ddu; native_call(m, m->edi);	/* 4486db: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486dd: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486e2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4486e6u; native_call(m, m->esi);	/* 4486e4: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4486e6: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4486ec: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4486f2: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4486f3: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4486f9: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4486fc: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 448701: push 0x41ef3333 */
	goto L_448990;	/* 448706: jmp 0x448990 */
L_44870b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44870b: test eax, eax */
	if (!m->zf) goto L_448331;	/* 44870d: jne 0x448331 */
L_448713:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 448713: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 448717: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448719: cmp eax, 3 */
	if (m->sf == m->of) goto L_4487db;	/* 44871c: jge 0x4487db */
	m->esp -= 4; M32(m->esp) = 0x448724u; native_call(m, m->ebx);	/* 448722: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448724: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448729: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44872du; native_call(m, m->esi);	/* 44872b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 44872d: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 448731: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 448737: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 44873b: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 448741: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 448745: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 448749: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44874f: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 448753: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448757: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 448758: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 44875c: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448760: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448761: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x448768u; native_call(m, m->edi);	/* 448766: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448768: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44876d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448774u; native_call(m, m->esi);	/* 448772: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 448774: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 448778: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 44877e: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 448782: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 448786: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44878a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44878b: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44878c: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x448793u; native_call(m, m->edi);	/* 448791: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448793: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448798: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44879fu; native_call(m, m->esi);	/* 44879d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 44879f: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4487a3: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4487a9: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4487ad: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4487ae: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4487b2: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4487b6: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4487b7: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x4487beu; native_call(m, m->edi);	/* 4487bc: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4487be: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4487c3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4487c7u; native_call(m, m->esi);	/* 4487c5: call esi */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4487c7: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4487cb: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4487cf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4487d0: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4487d1: push 0xc1f00000 */
	goto L_448990;	/* 4487d6: jmp 0x448990 */
L_4487db:
	m->esp -= 4; M32(m->esp) = 0x4487ddu; native_call(m, m->ebx);	/* 4487db: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4487dd: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4487e2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4487e9u; native_call(m, m->esi);	/* 4487e7: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4487e9: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4487ed: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4487f3: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 4487f7: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4487fd: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 448801: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 448805: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44880b: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 44880f: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448813: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 448814: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 448818: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44881c: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44881d: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x448824u; native_call(m, m->edi);	/* 448822: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448824: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448829: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44882du; native_call(m, m->esi);	/* 44882b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 44882d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 448831: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 448837: mov ecx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 44883b: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 44883f: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448843: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448844: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448845: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x44884cu; native_call(m, m->edi);	/* 44884a: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44884c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 448851: push 0 */
	m->esp -= 4; M32(m->esp) = 0x448855u; native_call(m, m->esi);	/* 448853: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 448855: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 448859: fsub dword ptr [0x4a9418] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 44885f: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448863: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 448864: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 448868: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44886c: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44886d: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x448874u; native_call(m, m->edi);	/* 448872: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448874: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 448879: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x448880u; native_call(m, m->esi);	/* 44887e: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 448880: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 448884: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448888: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448889: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44888a: push 0x41f00000 */
	goto L_448990;	/* 44888f: jmp 0x448990 */
L_448894:
	m->esp -= 4; M32(m->esp) = 0x448896u; native_call(m, m->ebx);	/* 448894: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 448896: fild dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 44889a: mov edx, dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 44889e: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 4488a4: fst dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 4488a8: fadd dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4488ac: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4488b0: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4488b4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4488b5: push edx */
	m->esp -= 4; M32(m->esp) = 0x4488b8u; native_call(m, m->esi);	/* 4488b6: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4488b8: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4488bc: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4488c2: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 4488c6: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4488cc: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4488d0: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4488d4: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4488da: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4488de: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4488e2: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4488e3: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4488e7: fild dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4488eb: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4488ef: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 4488f0: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 4488f6: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4488fc: fstp dword ptr [esp + 0x3c] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 448900: mov edx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448904: push edx */
	m->esp -= 4; M32(m->esp) = 0x448907u; native_call(m, m->edi);	/* 448905: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 448907: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 44890b: fadd dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 44890f: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448913: push eax */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 448914: fstp dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 448918: mov ecx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44891c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44891fu; native_call(m, m->esi);	/* 44891d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 44891f: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 448923: fadd dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 448929: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 44892d: mov ecx, dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 448931: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 448935: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448939: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44893a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44893b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44893eu; native_call(m, m->edi);	/* 44893c: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 44893e: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 448942: fadd dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 448946: mov eax, dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 44894a: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 44894e: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448952: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448953: push eax */
	m->esp -= 4; M32(m->esp) = 0x448956u; native_call(m, m->esi);	/* 448954: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 448956: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 44895a: fsub dword ptr [0x4a9418] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 448960: mov ecx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 448964: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 448968: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 448969: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 44896d: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 448971: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 448972: push eax */
	m->esp -= 4; M32(m->esp) = 0x448975u; native_call(m, m->edi);	/* 448973: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 448975: mov ecx, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 448979: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44897d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44897e: push edx */
	m->esp -= 4; M32(m->esp) = 0x448981u; native_call(m, m->esi);	/* 44897f: call esi */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 448981: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 448985: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 448989: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44898d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44898e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44898f: push edx */
L_448990:
	m->esp -= 4; M32(m->esp) = 0x448992u; native_call(m, m->edi);	/* 448990: call edi */
	m->esp -= 4; M32(m->esp) = 0x448994u; native_call(m, m->ebp);	/* 448992: call ebp */
L_448994:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 448994: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 448998: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 448999: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 44899c: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_448264;	/* 4489a0: jl 0x448264 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4489a6: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4489aa: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4489ab: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4489ae: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_448194;	/* 4489b2: jl 0x448194 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4489b8: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4489c3u; native_call(m, M32(0x4a922cu));	/* 4489bd: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 4489c3: mov eax, dword ptr [0x680398] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4489c8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4489c9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4489ca: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4489cb: test eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4489cd: pop ebx */
	if (m->zf) goto L_448a16;	/* 4489ce: je 0x448a16 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 4489d0: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 4489d6: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 4489dc: fadd dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu));	/* 4489e2: fcom dword ptr [0x4a93fc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 4489e8: fst dword ptr [0x680ccc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4489ee: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4489f0: test ah, 0x41 */
	if (m->zf) goto L_4489ff;	/* 4489f3: je 0x4489ff */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 4489f5: mov dword ptr [0x4df454], 0x3f800000 */
L_4489ff:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 4489ff: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 448a05: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 448a07: test ah, 1 */
	if (!m->zf) goto L_448a16;	/* 448a0a: jne 0x448a16 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 448a0c: mov dword ptr [0x4df454], 0xbf800000 */
L_448a16:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 448a16: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 448a1c: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 448a22: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 448a28: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 448a2e: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 448a34: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 448a36: test ah, 0x41 */
	if (m->zf) goto L_448a51;	/* 448a39: je 0x448a51 */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 448a3b: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 448a45: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_448a78;	/* 448a4f: jmp 0x448a78 */
L_448a51:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 448a51: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 448a57: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 448a5d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 448a5f: test ah, 1 */
	if (!m->zf) goto L_448a78;	/* 448a62: jne 0x448a78 */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 448a64: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 448a6e: mov dword ptr [0x4df010], 0xbf800000 */
L_448a78:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 448a78: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 448a7e: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 448a84: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 448a8a: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 448a90: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 448a96: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 448a98: test ah, 1 */
	if (!m->zf) goto L_448aa7;	/* 448a9b: jne 0x448aa7 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 448a9d: mov dword ptr [0x4e14fc], 0 */
L_448aa7:
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 448aa7: add esp, 0x48 */
	m->esp += 4 + 0; return;	/* 448aaa: ret  */
}

/* mainmenu_drawScreen (0x44d720), lifted by tools/lift.py */
static void lift_44d720(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d720: sub esp, 8 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44d723: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44d728: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d72e: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d72f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44d730: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d731: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d732: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44d738u; native_call(m, 0x44b260u);	/* 44d733: call 0x44b260 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d738: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 44d73a: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x44d743u; native_call(m, 0x41ef90u);	/* 44d73e: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d743: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x44d74cu; native_call(m, M32(0x4a9218u));	/* 44d746: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44d74c: mov eax, dword ptr [0x9f8f10] */
	m->esi = 0x1u;	/* 44d751: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d756: cmp eax, esi */
	if (!m->zf) goto L_44d77f;	/* 44d758: jne 0x44d77f */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d75a: push 0x3f800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d75f: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d764: push 0 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d766: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d76b: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44d775u; native_call(m, 0x41f0e0u);	/* 44d770: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d775: add esp, 0x14 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d778: push 0x3f800000 */
	goto L_44d7a2;	/* 44d77d: jmp 0x44d7a2 */
L_44d77f:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d77f: push 0x3f000000 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 44d784: push 0x3e99999a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d789: push 0 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d78b: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d790: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44d79au; native_call(m, 0x41f0e0u);	/* 44d795: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d79a: add esp, 0x14 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d79d: push 0x3f000000 */
L_44d7a2:
	m->ebx = M32((DWORD)(0x4a9228u));	/* 44d7a2: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7a8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7ad: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7b2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44d7b9u; native_call(m, m->ebx);	/* 44d7b7: call ebx */
	m->edx = M32((DWORD)(0x4deb50u));	/* 44d7b9: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9f8ea4u));	/* 44d7bf: mov eax, dword ptr [0x9f8ea4] */
	m->ecx = M32((DWORD)(0x9f8ea0u));	/* 44d7c4: mov ecx, dword ptr [0x9f8ea0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7ca: push edx */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44d7cb: mov edx, dword ptr [0x9f8e4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7d1: push eax */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44d7d2: mov eax, dword ptr [0x9f8e48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7d7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7d8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7d9: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d7dfu; native_call(m, 0x427a90u);	/* 44d7da: call 0x427a90 */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44d7df: mov eax, dword ptr [0x9f8f10] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d7e4: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d7e7: cmp eax, esi */
	if (!m->zf) goto L_44d801;	/* 44d7e9: jne 0x44d801 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7eb: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7f0: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7f5: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d7fa: push 0x3f4ccccd */
	goto L_44d815;	/* 44d7ff: jmp 0x44d815 */
L_44d801:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d801: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d806: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d80b: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d810: push 0x3f000000 */
L_44d815:
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d815: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44d81fu; native_call(m, 0x41f0e0u);	/* 44d81a: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9f8ea4u));	/* 44d81f: mov ecx, dword ptr [0x9f8ea4] */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44d825: mov eax, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d82a: add esp, 0x14 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d82d: add ecx, -0x40 */
	m->edx = (DWORD)(m->eax + 0x100u);	/* 44d830: lea edx, [eax + 0x100] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d836: add eax, 0x20 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d839: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d83b: push ecx */
	m->ecx = M32((DWORD)(0x9f8e4cu));	/* 44d83c: mov ecx, dword ptr [0x9f8e4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d842: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d843: add ecx, 0x20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d846: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d847: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d84du; native_call(m, 0x427970u);	/* 44d848: call 0x427970 */
	m->edx = M32((DWORD)(0x9f8ea4u));	/* 44d84d: mov edx, dword ptr [0x9f8ea4] */
	m->eax = M32((DWORD)(0x9f8ea0u));	/* 44d853: mov eax, dword ptr [0x9f8ea0] */
	m->ecx = M32((DWORD)(0x9f8e4cu));	/* 44d858: mov ecx, dword ptr [0x9f8e4c] */
	{ DWORD a_ = m->edx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d85e: add edx, -0x40 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d861: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d863: push edx */
	m->edx = M32((DWORD)(0x9f8e48u));	/* 44d864: mov edx, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->eax, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d86a: add eax, -0x20 */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44d86d: add ecx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d870: push eax */
	{ DWORD a_ = m->edx, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d871: add edx, 0x108 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d877: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d878: push edx */
	m->esp -= 4; M32(m->esp) = 0x44d87eu; native_call(m, 0x427970u);	/* 44d879: call 0x427970 */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44d87e: mov eax, dword ptr [0x9f8f10] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d883: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d886: cmp eax, esi */
	if (!m->zf) goto L_44d8a6;	/* 44d888: jne 0x44d8a6 */
	m->eax = M32((DWORD)(0x9f8ebcu));	/* 44d88a: mov eax, dword ptr [0x9f8ebc] */
	m->ecx = M32((DWORD)(0x9f8eb8u));	/* 44d88f: mov ecx, dword ptr [0x9f8eb8] */
	m->edx = M32((DWORD)(0x9f8eb4u));	/* 44d895: mov edx, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d89b: push eax */
	m->eax = M32((DWORD)(0x9f8eb0u));	/* 44d89c: mov eax, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8a1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8a2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8a3: push eax */
	goto L_44d8c1;	/* 44d8a4: jmp 0x44d8c1 */
L_44d8a6:
	m->ecx = M32((DWORD)(0x9f8d64u));	/* 44d8a6: mov ecx, dword ptr [0x9f8d64] */
	m->edx = M32((DWORD)(0x9f8d60u));	/* 44d8ac: mov edx, dword ptr [0x9f8d60] */
	m->eax = M32((DWORD)(0x9f8d5cu));	/* 44d8b2: mov eax, dword ptr [0x9f8d5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8b7: push ecx */
	m->ecx = M32((DWORD)(0x9f8d58u));	/* 44d8b8: mov ecx, dword ptr [0x9f8d58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8be: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8bf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8c0: push ecx */
L_44d8c1:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8c1: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44d8cbu; native_call(m, 0x41f0e0u);	/* 44d8c6: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44d8cb: mov edx, dword ptr [0x9f8e4c] */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44d8d1: mov eax, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d8d6: add esp, 0x14 */
	{ DWORD a_ = m->edx, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44d8d9: add edx, 0xa */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44d8dc: add eax, 0x20 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8df: push ebp */
	{ DWORD v_ = 0x751a24u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8e0: push 0x751a24 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8e5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d8e6: push eax */
	m->esp -= 4; M32(m->esp) = 0x44d8ecu; native_call(m, 0x4028b0u);	/* 44d8e7: call 0x4028b0 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44d8ec: xor esi, esi */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44d8ee: add esp, 0xc */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 44d8f1: mov dword ptr [esp + 0x10], esi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 44d8f5: xor edi, edi */
	m->ebp = 0x751aa4u;	/* 44d8f7: mov ebp, 0x751aa4 */
	goto L_44d902;	/* 44d8fc: jmp 0x44d902 */
L_44d8fe:
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 44d8fe: mov esi, dword ptr [esp + 0x10] */
L_44d902:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d902: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d907: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d90c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d911: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44d918u; native_call(m, m->ebx);	/* 44d916: call ebx */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44d918: mov eax, dword ptr [0x9f8f10] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d91d: cmp eax, 1 */
	if (!m->zf) goto L_44d97b;	/* 44d920: jne 0x44d97b */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->esp + 0x14u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d922: cmp esi, dword ptr [esp + 0x14] */
	if (!m->zf) goto L_44d963;	/* 44d926: jne 0x44d963 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d928: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d92d: push 0x3f800000 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d932: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d937: push 0x3f800000 */
	m->esi = 0x1u;	/* 44d93c: mov esi, 1 */
	m->esp -= 4; M32(m->esp) = 0x44d943u; native_call(m, m->ebx);	/* 44d941: call ebx */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44d943: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44d949: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44d94f: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d954: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44d955: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d95b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d95c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d95d: push ecx */
	goto L_44d9ff;	/* 44d95e: jmp 0x44d9ff */
L_44d963:
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 44d963: push 0x3e99999a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d968: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d96d: push 0x3f800000 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44d972: xor esi, esi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d974: push 0x3f800000 */
	goto L_44d9e2;	/* 44d979: jmp 0x44d9e2 */
L_44d97b:
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44d97b: add esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44d97e: cmp eax, esi */
	if (!m->zf) goto L_44d9cc;	/* 44d980: jne 0x44d9cc */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d982: push 0x3f800000 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d987: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d98c: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d991: push 0x3f4ccccd */
	m->esi = 0x1u;	/* 44d996: mov esi, 1 */
	m->esp -= 4; M32(m->esp) = 0x44d99du; native_call(m, m->ebx);	/* 44d99b: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9f8eb8u)));	/* 44d99d: fld dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8ebcu));	/* 44d9a3: mov eax, dword ptr [0x9f8ebc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 44d9a8: fsub dword ptr [0x4a94f8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9ae: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9af: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44d9b0: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9f8eb4u)));	/* 44d9b3: fld dword ptr [0x9f8eb4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 44d9b9: fsub dword ptr [0x4a94f8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9bf: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44d9c0: mov ecx, dword ptr [0x9f8eb0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44d9c6: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9c9: push ecx */
	goto L_44d9ff;	/* 44d9ca: jmp 0x44d9ff */
L_44d9cc:
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9cc: push 0x3e99999a */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9d1: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9d6: push 0x3f4ccccd */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44d9db: xor esi, esi */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9dd: push 0x3f4ccccd */
L_44d9e2:
	m->esp -= 4; M32(m->esp) = 0x44d9e4u; native_call(m, m->ebx);	/* 44d9e2: call ebx */
	m->edx = M32((DWORD)(0x9f8d64u));	/* 44d9e4: mov edx, dword ptr [0x9f8d64] */
	m->eax = M32((DWORD)(0x9f8d60u));	/* 44d9ea: mov eax, dword ptr [0x9f8d60] */
	m->ecx = M32((DWORD)(0x9f8d5cu));	/* 44d9ef: mov ecx, dword ptr [0x9f8d5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9f5: push edx */
	m->edx = M32((DWORD)(0x9f8d58u));	/* 44d9f6: mov edx, dword ptr [0x9f8d58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9fc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9fd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9fe: push edx */
L_44d9ff:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44d9ff: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44da09u; native_call(m, 0x41f0e0u);	/* 44da04: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44da09: add esp, 0x14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44da0c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44da17u; native_call(m, M32(0x4a9224u));	/* 44da11: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44da17: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44da1c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44da1e: and ecx, 0x800001ff */
	if (!m->sf) goto L_44da2e;	/* 44da24: jns 0x44da2e */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44da26: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44da27: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44da2d: inc ecx */
L_44da2e:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44da2e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44da2f: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44da35: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44da36: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44da38: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44da3e: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44da41: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44da4au; native_call(m, 0x4566c0u);	/* 44da45: call 0x4566c0 */
	m->ecx = M32((DWORD)(0x9f8ea4u));	/* 44da4a: mov ecx, dword ptr [0x9f8ea4] */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44da50: mov eax, dword ptr [0x9f8e48] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44da55: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 44da57: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44da5a: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44da5d: push edx */
	m->edx = (DWORD)(m->edi + m->eax*1 + 0x88u);	/* 44da5e: lea edx, [edi + eax + 0x88] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44da65: push edx */
	m->eax = (DWORD)(m->edi + m->eax*1 + 0x28u);	/* 44da66: lea eax, [edi + eax + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44da6a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44da6b: push eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44da6c: test esi, esi */
	m->esp -= 4; M32(m->esp) = 0x44da73u; native_call(m, 0x4282f0u);	/* 44da6e: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44da73: mov eax, dword ptr [0x9f8e48] */
	m->edx = M32((DWORD)(0x9f8ea4u));	/* 44da78: mov edx, dword ptr [0x9f8ea4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44da7e: add esp, 0x14 */
	{ DWORD a_ = m->edx, b_ = 0xffffffd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44da81: add edx, -0x28 */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x88u);	/* 44da84: lea ecx, [edi + eax + 0x88] */
	m->eax = (DWORD)(m->edi + m->eax*1 + 0x28u);	/* 44da8b: lea eax, [edi + eax + 0x28] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44da8f: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44da90: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44da91: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44da92: push eax */
	m->esp -= 4; M32(m->esp) = 0x44da98u; native_call(m, 0x4029d0u);	/* 44da93: call 0x4029d0 */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 44da98: mov esi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44da9c: add esp, 0x10 */
	{ DWORD a_ = m->ebp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 44da9f: add ebp, 0x80 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 44daa5: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x72u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44daa6: add edi, 0x72 */
	{ DWORD a_ = m->ebp, b_ = 0x751ca4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44daa9: cmp ebp, 0x751ca4 */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 44daaf: mov dword ptr [esp + 0x10], esi */
	if (m->sf != m->of) goto L_44d8fe;	/* 44dab3: jl 0x44d8fe */
	m->esp -= 4; M32(m->esp) = 0x44dabeu; native_call(m, 0x44ce90u);	/* 44dab9: call 0x44ce90 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dabe: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44dac9u; native_call(m, M32(0x4a9224u));	/* 44dac3: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44dac9: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44dace: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44dad0: and ecx, 0x800001ff */
	if (!m->sf) goto L_44dae0;	/* 44dad6: jns 0x44dae0 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44dad8: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44dad9: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44dadf: inc ecx */
L_44dae0:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44dae0: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44dae1: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dae7: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44dae8: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44daea: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44daf0: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44daf3: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44dafcu; native_call(m, 0x4566c0u);	/* 44daf7: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dafc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44db01: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44db06: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44db0b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44db12u; native_call(m, m->ebx);	/* 44db10: call ebx */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 44db12: mov esi, dword ptr [esp + 0x14] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44db16: pop ebp */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44db17: cmp esi, 5 */
	if (!m->zf) goto L_44dbae;	/* 44db1a: jne 0x44dbae */
	m->eax = M32((DWORD)(0x9f8e4cu));	/* 44db20: mov eax, dword ptr [0x9f8e4c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44db25: push 1 */
	m->ecx = (DWORD)(m->eax + 0x80u);	/* 44db27: lea ecx, [eax + 0x80] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44db2d: add eax, 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44db30: push ecx */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44db31: mov ecx, dword ptr [0x9f8e48] */
	m->edx = (DWORD)(m->ecx + 0xf8u);	/* 44db37: lea edx, [ecx + 0xf8] */
	{ DWORD a_ = m->ecx, b_ = 0xe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44db3d: add ecx, 0xe0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44db43: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44db44: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44db45: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44db4bu; native_call(m, 0x4286b0u);	/* 44db46: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44db4b: add esp, 0x14 */
L_44db4e:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44db4e: push 0 */
L_44db50:
	m->eax = M32((DWORD)(0x9f8e4cu));	/* 44db50: mov eax, dword ptr [0x9f8e4c] */
	m->ecx = (DWORD)(m->eax + 0xe4u);	/* 44db55: lea ecx, [eax + 0xe4] */
	{ DWORD a_ = m->eax, b_ = 0xb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44db5b: add eax, 0xb4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44db60: push ecx */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44db61: mov ecx, dword ptr [0x9f8e48] */
	m->edx = (DWORD)(m->ecx + 0xf8u);	/* 44db67: lea edx, [ecx + 0xf8] */
	{ DWORD a_ = m->ecx, b_ = 0xe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44db6d: add ecx, 0xe0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44db73: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44db74: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44db75: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44db7bu; native_call(m, 0x4287a0u);	/* 44db76: call 0x4287a0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44db7b: add esp, 0x14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44db7e: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44db89u; native_call(m, M32(0x4a922cu));	/* 44db83: call dword ptr [0x4a922c] */
	m->esp -= 4; M32(m->esp) = 0x44db8eu; native_call(m, 0x44cf70u);	/* 44db89: call 0x44cf70 */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44db8e: mov eax, dword ptr [0x9f8f10] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44db93: push 0x3f800000 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44db98: cmp eax, 1 */
	if (!m->zf) goto L_44dbec;	/* 44db9b: jne 0x44dbec */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44db9d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dba2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dba7: push 0x3f800000 */
	goto L_44dbfb;	/* 44dbac: jmp 0x44dbfb */
L_44dbae:
	m->eax = M32((DWORD)(0x9f8e4cu));	/* 44dbae: mov eax, dword ptr [0x9f8e4c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbb3: push 0 */
	m->ecx = (DWORD)(m->eax + 0x80u);	/* 44dbb5: lea ecx, [eax + 0x80] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44dbbb: add eax, 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbbe: push ecx */
	m->ecx = M32((DWORD)(0x9f8e48u));	/* 44dbbf: mov ecx, dword ptr [0x9f8e48] */
	m->edx = (DWORD)(m->ecx + 0xf8u);	/* 44dbc5: lea edx, [ecx + 0xf8] */
	{ DWORD a_ = m->ecx, b_ = 0xe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44dbcb: add ecx, 0xe0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbd1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbd2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbd3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44dbd9u; native_call(m, 0x4286b0u);	/* 44dbd4: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44dbd9: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44dbdc: cmp esi, 6 */
	if (!m->zf) goto L_44db4e;	/* 44dbdf: jne 0x44db4e */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbe5: push 1 */
	goto L_44db50;	/* 44dbe7: jmp 0x44db50 */
L_44dbec:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbec: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbf1: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dbf6: push 0x3f000000 */
L_44dbfb:
	m->esp -= 4; M32(m->esp) = 0x44dbfdu; native_call(m, m->ebx);	/* 44dbfb: call ebx */
	m->eax = M32((DWORD)(0x9f8ea4u));	/* 44dbfd: mov eax, dword ptr [0x9f8ea4] */
	m->ecx = M32((DWORD)(0x9f8ea0u));	/* 44dc02: mov ecx, dword ptr [0x9f8ea0] */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44dc08: mov edx, dword ptr [0x9f8e4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc0e: push eax */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44dc0f: mov eax, dword ptr [0x9f8e48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc14: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc15: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc16: push eax */
	m->esp -= 4; M32(m->esp) = 0x44dc1cu; native_call(m, 0x428a00u);	/* 44dc17: call 0x428a00 */
	m->edi = 0x4b0384u;	/* 44dc1c: mov edi, 0x4b0384 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44dc21: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44dc24: xor eax, eax */
	{ DWORD v_ = 0x4b0384u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc26: push 0x4b0384 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44dc2b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44dc2d: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44dc2f: dec ecx */
	m->eax = 0x69u;	/* 44dc30: mov eax, 0x69 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44dc35: sub eax, ecx */
	{ DWORD v_ = 0x1d6u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc37: push 0x1d6 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 44dc3c: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44dc3f: shl ecx, 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc41: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44dc47u; native_call(m, 0x403170u);	/* 44dc42: call 0x403170 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44dc47: add esp, 0x1c */
	m->edi = M32(m->esp); m->esp += 4;	/* 44dc4a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44dc4b: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44dc4c: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44dc4d: add esp, 8 */
	m->esp += 4 + 0; return;	/* 44dc50: ret  */
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
