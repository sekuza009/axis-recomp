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

static void lift_497d20(X86 *m);
static void lift_472400(X86 *m);

/* light_computeLayerLightBy (0x472400), lifted by tools/lift.py */
static void lift_472400(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472400: sub esp, 0x14 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 472403: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 472404: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 472408: push edi */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 472409: mov dword ptr [esp + 0x18], ecx */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x0u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47240d: cmp dword ptr [ebp], 2 */
	if (!m->zf) goto L_472457;	/* 472411: jne 0x472457 */
	m->ecx = M32((DWORD)(m->ebp + 0x20u));	/* 472413: mov ecx, dword ptr [ebp + 0x20] */
	m->eax = M32((DWORD)(m->ebp + 0x1cu));	/* 472416: mov eax, dword ptr [ebp + 0x1c] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 472419: inc ecx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47241a: inc eax */
	{ long long p_ = (long long)(int)m->ecx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 47241b: imul ecx, eax */
	m->edi = M32((DWORD)(m->ebp + 0x48u));	/* 47241e: mov edi, dword ptr [ebp + 0x48] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472421: or eax, 0xffffffff */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 472424: shl ecx, 2 */
	m->edx = m->ecx;	/* 472427: mov edx, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 472429: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 47242c: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 47242e: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 472430: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 472433: rep stosb byte ptr es:[edi], al */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x30u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472435: cmp dword ptr [ebp + 0x30], 1 */
	if (!m->zf) goto L_4728d1;	/* 472439: jne 0x4728d1 */
	m->ecx = 0xcu;	/* 47243f: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472444: or eax, 0xffffffff */
	m->edi = (DWORD)(m->ebp + 0xfcu);	/* 472447: lea edi, [ebp + 0xfc] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 47244d: rep stosd dword ptr es:[edi], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 47244f: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 472450: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472451: add esp, 0x14 */
	m->esp += 4 + 28; return;	/* 472454: ret 0x1c */
L_472457:
	m->eax = M32((DWORD)(m->ecx + 0x9d8000u));	/* 472457: mov eax, dword ptr [ecx + 0x9d8000] */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 47245d: mov dword ptr [esp + 0x14], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472465: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4728d1;	/* 472467: jle 0x4728d1 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47246d: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47246e: push esi */
	m->edi = (DWORD)(m->ecx + 0x9cd008u);	/* 47246f: lea edi, [ecx + 0x9cd008] */
L_472475:
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 472475: mov ecx, dword ptr [edi] */
	m->eax = m->ecx;	/* 472477: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472479: sub eax, 0 */
	if (m->zf) goto L_4728b1;	/* 47247c: je 0x4728b1 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 472482: dec eax */
	if (m->zf) goto L_4724a4;	/* 472483: je 0x4724a4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 472485: dec eax */
	if (m->zf) goto L_4728b1;	/* 472486: je 0x4728b1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47248c: push ecx */
	{ DWORD v_ = 0x4c74a8u; m->esp -= 4; M32(m->esp) = v_; }	/* 47248d: push 0x4c74a8 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 472492: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x47249cu; native_call(m, 0x46c710u);	/* 472497: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47249c: add esp, 0xc */
	goto L_4728b1;	/* 47249f: jmp 0x4728b1 */
L_4724a4:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4724a4: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 4724a8: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4724ac: cmp eax, 1 */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 4724af: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4724b3: mov dword ptr [esp + 0x18], eax */
	if (!m->zf) goto L_47269f;	/* 4724b7: jne 0x47269f */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4724bd: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_4725cd;	/* 4724bf: jg 0x4725cd */
L_4724c5:
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 4724c5: mov eax, dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 4724c9: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4724cd: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4724cf: mov dword ptr [esp + 0x14], eax */
	if (!m->zf && m->sf == m->of) goto L_4725b8;	/* 4724d3: jg 0x4725b8 */
L_4724d9:
	m->esi = M32((DWORD)(m->ebp + 0x20u));	/* 4724d9: mov esi, dword ptr [ebp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4724dc: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4724e0: inc esi */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 4724e1: imul esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4724e6: add esi, ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x44u));	/* 4724e8: mov ecx, dword ptr [ebp + 0x44] */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 4724eb: lea eax, [esi + esi*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->eax*4 + 0x4u)));	/* 4724ee: fld dword ptr [ecx + eax*4 + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x18u));	/* 4724f2: fmul dword ptr [edi + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->eax*4 + 0x8u)));	/* 4724f5: fld dword ptr [ecx + eax*4 + 8] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 4724f9: lea eax, [ecx + eax*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x1cu));	/* 4724fc: fmul dword ptr [edi + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4724ff: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 472501: fld dword ptr [edi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 472504: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472506: faddp st(1) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 472508: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 47250e: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 472514: call 0x49ec14 */
	m->ecx = m->eax;	/* 472519: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47251b: test ecx, ecx */
	if (m->sf == m->of) goto L_472521;	/* 47251d: jge 0x472521 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47251f: xor ecx, ecx */
L_472521:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472521: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 472523: mov al, byte ptr [edi + 4] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 472526: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 472529: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47252a: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472530: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 472532: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472535: cmp eax, 0xff */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 47253a: mov dword ptr [esp + 0x10], eax */
	if (m->zf || m->sf != m->of) goto L_472548;	/* 47253e: jle 0x472548 */
	M32((DWORD)(m->esp + 0x10u)) = 0xffu;	/* 472540: mov dword ptr [esp + 0x10], 0xff */
L_472548:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472548: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x5u))) & 0xff) << 0);	/* 47254a: mov al, byte ptr [edi + 5] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 47254d: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 472550: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472551: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472557: add eax, edx */
	m->ebx = m->eax;	/* 472559: mov ebx, eax */
	{ DWORD a_ = m->ebx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 47255b: sar ebx, 8 */
	{ DWORD a_ = m->ebx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47255e: cmp ebx, 0xff */
	if (m->zf || m->sf != m->of) goto L_47256b;	/* 472564: jle 0x47256b */
	m->ebx = 0xffu;	/* 472566: mov ebx, 0xff */
L_47256b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47256b: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x6u))) & 0xff) << 0);	/* 47256d: mov al, byte ptr [edi + 6] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 472570: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 472573: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472574: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47257a: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47257c: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47257f: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_47258b;	/* 472584: jle 0x47258b */
	m->eax = 0xffu;	/* 472586: mov eax, 0xff */
L_47258b:
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 47258b: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 47258f: mov dl, byte ptr [esp + 0x10] */
	M8((DWORD)(m->ecx + m->esi*4 + 0x2u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 472593: mov byte ptr [ecx + esi*4 + 2], al */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 472597: mov eax, dword ptr [esp + 0x14] */
	M8((DWORD)(m->ecx + m->esi*4 + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 47259b: mov byte ptr [ecx + esi*4], dl */
	M8((DWORD)(m->ecx + m->esi*4 + 0x1u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 47259e: mov byte ptr [ecx + esi*4 + 1], bl */
	M8((DWORD)(m->ecx + m->esi*4 + 0x3u)) = (BYTE)(0xffu);	/* 4725a2: mov byte ptr [ecx + esi*4 + 3], 0xff */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 4725a7: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4725ab: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4725ac: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4725ae: mov dword ptr [esp + 0x14], eax */
	if (m->zf || m->sf != m->of) goto L_4724d9;	/* 4725b2: jle 0x4724d9 */
L_4725b8:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4725b8: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 4725bc: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4725c0: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4725c1: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4725c3: mov dword ptr [esp + 0x18], eax */
	if (m->zf || m->sf != m->of) goto L_4724c5;	/* 4725c7: jle 0x4724c5 */
L_4725cd:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x30u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4725cd: cmp dword ptr [ebp + 0x30], 1 */
	if (!m->zf) goto L_472692;	/* 4725d1: jne 0x472692 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4725d7: cmp dword ptr [ebp], 1 */
	if (m->zf) goto L_4725e5;	/* 4725db: je 0x4725e5 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4725dd: fld dword ptr [0x4a9424] */
	goto L_4725eb;	/* 4725e3: jmp 0x4725eb */
L_4725e5:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 4725e5: fld dword ptr [0x4a9474] */
L_4725eb:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x18u));	/* 4725eb: fmul dword ptr [edi + 0x18] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4725ee: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 4725f4: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4725fa: call 0x49ec14 */
	m->ecx = m->eax;	/* 4725ff: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472601: test ecx, ecx */
	if (m->sf == m->of) goto L_472607;	/* 472603: jge 0x472607 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 472605: xor ecx, ecx */
L_472607:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472607: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 472609: mov al, byte ptr [edi + 4] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 47260c: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47260f: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472610: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472616: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 472618: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47261b: cmp eax, 0xff */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 472620: mov dword ptr [esp + 0x10], eax */
	if (m->zf || m->sf != m->of) goto L_47262e;	/* 472624: jle 0x47262e */
	M32((DWORD)(m->esp + 0x10u)) = 0xffu;	/* 472626: mov dword ptr [esp + 0x10], 0xff */
L_47262e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47262e: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x5u))) & 0xff) << 0);	/* 472630: mov al, byte ptr [edi + 5] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 472633: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 472636: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472637: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47263d: add eax, edx */
	m->ebx = m->eax;	/* 47263f: mov ebx, eax */
	{ DWORD a_ = m->ebx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 472641: sar ebx, 8 */
	{ DWORD a_ = m->ebx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472644: cmp ebx, 0xff */
	if (m->zf || m->sf != m->of) goto L_472651;	/* 47264a: jle 0x472651 */
	m->ebx = 0xffu;	/* 47264c: mov ebx, 0xff */
L_472651:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472651: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x6u))) & 0xff) << 0);	/* 472653: mov al, byte ptr [edi + 6] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 472656: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 472659: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47265a: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472660: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 472662: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472665: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_472671;	/* 47266a: jle 0x472671 */
	m->eax = 0xffu;	/* 47266c: mov eax, 0xff */
L_472671:
	m->ecx = (DWORD)(m->ebp + 0xfeu);	/* 472671: lea ecx, [ebp + 0xfe] */
	m->esi = 0xcu;	/* 472677: mov esi, 0xc */
L_47267c:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 47267c: mov dl, byte ptr [esp + 0x10] */
	M8((DWORD)(m->ecx + 0xffffffffu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 472680: mov byte ptr [ecx - 1], bl */
	M8((DWORD)(m->ecx + 0xfffffffeu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 472683: mov byte ptr [ecx - 2], dl */
	M8((DWORD)(m->ecx + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 472686: mov byte ptr [ecx], al */
	M8((DWORD)(m->ecx + 0x1u)) = (BYTE)(0xffu);	/* 472688: mov byte ptr [ecx + 1], 0xff */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47268c: add ecx, 4 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 47268f: dec esi */
	if (!m->zf) goto L_47267c;	/* 472690: jne 0x47267c */
L_472692:
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 472692: mov dword ptr [esp + 0x30], 0 */
	goto L_4728b1;	/* 47269a: jmp 0x4728b1 */
L_47269f:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47269f: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_4727ce;	/* 4726a1: jg 0x4727ce */
L_4726a7:
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 4726a7: mov eax, dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 4726ab: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4726af: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4726b1: mov dword ptr [esp + 0x14], eax */
	if (!m->zf && m->sf == m->of) goto L_4727b9;	/* 4726b5: jg 0x4727b9 */
L_4726bb:
	m->esi = M32((DWORD)(m->ebp + 0x20u));	/* 4726bb: mov esi, dword ptr [ebp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4726be: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4726c2: inc esi */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 4726c3: imul esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4726c8: add esi, ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x44u));	/* 4726ca: mov ecx, dword ptr [ebp + 0x44] */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 4726cd: lea eax, [esi + esi*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->eax*4 + 0x4u)));	/* 4726d0: fld dword ptr [ecx + eax*4 + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x18u));	/* 4726d4: fmul dword ptr [edi + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->eax*4 + 0x8u)));	/* 4726d7: fld dword ptr [ecx + eax*4 + 8] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 4726db: lea eax, [ecx + eax*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x1cu));	/* 4726de: fmul dword ptr [edi + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4726e1: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 4726e3: fld dword ptr [edi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4726e6: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4726e8: faddp st(1) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4726ea: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 4726f0: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4726f6: call 0x49ec14 */
	m->ebp = m->eax;	/* 4726fb: mov ebp, eax */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4726fd: test ebp, ebp */
	if (m->sf == m->of) goto L_472703;	/* 4726ff: jge 0x472703 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 472701: xor ebp, ebp */
L_472703:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472703: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 472705: mov al, byte ptr [edi + 4] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 472708: imul eax, ebp */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47270b: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47270c: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472712: add eax, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472714: xor edx, edx */
	m->ebx = m->eax;	/* 472716: mov ebx, eax */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 472718: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ebx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 47271c: sar ebx, 8 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + m->esi*4 + 0x0u))) & 0xff) << 0);	/* 47271f: mov dl, byte ptr [eax + esi*4] */
	{ DWORD a_ = m->ebx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 472722: add ebx, edx */
	{ DWORD a_ = m->ebx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472724: cmp ebx, 0xff */
	if (m->zf || m->sf != m->of) goto L_472731;	/* 47272a: jle 0x472731 */
	m->ebx = 0xffu;	/* 47272c: mov ebx, 0xff */
L_472731:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472731: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x5u))) & 0xff) << 0);	/* 472733: mov al, byte ptr [edi + 5] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 472736: imul eax, ebp */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 472739: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47273a: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472740: add eax, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472742: xor edx, edx */
	m->ecx = m->eax;	/* 472744: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 472746: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 47274a: sar ecx, 8 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + m->esi*4 + 0x1u))) & 0xff) << 0);	/* 47274d: mov dl, byte ptr [eax + esi*4 + 1] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 472751: add ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472753: cmp ecx, 0xff */
	if (m->zf || m->sf != m->of) goto L_472760;	/* 472759: jle 0x472760 */
	m->ecx = 0xffu;	/* 47275b: mov ecx, 0xff */
L_472760:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472760: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x6u))) & 0xff) << 0);	/* 472762: mov al, byte ptr [edi + 6] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 472765: imul eax, ebp */
	m->ebp = M32((DWORD)(m->esp + 0x2cu));	/* 472768: mov ebp, dword ptr [esp + 0x2c] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47276c: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47276d: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472773: add eax, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472775: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->esi*4 + 0x2u))) & 0xff) << 0);	/* 472777: mov dl, byte ptr [ebp + esi*4 + 2] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47277b: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47277e: add eax, edx */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472780: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_47278c;	/* 472785: jle 0x47278c */
	m->eax = 0xffu;	/* 472787: mov eax, 0xff */
L_47278c:
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 47278c: mov edx, dword ptr [esp + 0x2c] */
	m->ebp = M32((DWORD)(m->esp + 0x28u));	/* 472790: mov ebp, dword ptr [esp + 0x28] */
	M8((DWORD)(m->edx + m->esi*4 + 0x2u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 472794: mov byte ptr [edx + esi*4 + 2], al */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 472798: mov eax, dword ptr [esp + 0x14] */
	M8((DWORD)(m->edx + m->esi*4 + 0x1u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 47279c: mov byte ptr [edx + esi*4 + 1], cl */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 4727a0: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4727a4: inc eax */
	M8((DWORD)(m->edx + m->esi*4 + 0x0u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4727a5: mov byte ptr [edx + esi*4], bl */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4727a8: cmp eax, ecx */
	M8((DWORD)(m->edx + m->esi*4 + 0x3u)) = (BYTE)(0xffu);	/* 4727aa: mov byte ptr [edx + esi*4 + 3], 0xff */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4727af: mov dword ptr [esp + 0x14], eax */
	if (m->zf || m->sf != m->of) goto L_4726bb;	/* 4727b3: jle 0x4726bb */
L_4727b9:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4727b9: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 4727bd: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4727c1: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4727c2: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4727c4: mov dword ptr [esp + 0x18], eax */
	if (m->zf || m->sf != m->of) goto L_4726a7;	/* 4727c8: jle 0x4726a7 */
L_4727ce:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x30u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4727ce: cmp dword ptr [ebp + 0x30], 1 */
	if (!m->zf) goto L_4728b1;	/* 4727d2: jne 0x4728b1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4727d8: cmp dword ptr [ebp], 1 */
	if (m->zf) goto L_4727e6;	/* 4727dc: je 0x4727e6 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4727de: fld dword ptr [0x4a9424] */
	goto L_4727ec;	/* 4727e4: jmp 0x4727ec */
L_4727e6:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 4727e6: fld dword ptr [0x4a9474] */
L_4727ec:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x18u));	/* 4727ec: fmul dword ptr [edi + 0x18] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4727ef: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 4727f5: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4727fb: call 0x49ec14 */
	m->ecx = m->eax;	/* 472800: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472802: test ecx, ecx */
	if (m->sf == m->of) goto L_472808;	/* 472804: jge 0x472808 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 472806: xor ecx, ecx */
L_472808:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472808: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 47280a: mov al, byte ptr [edi + 4] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 47280d: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 472810: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472811: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472817: add eax, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472819: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0xfcu))) & 0xff) << 0);	/* 47281b: mov dl, byte ptr [ebp + 0xfc] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 472821: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472824: add eax, edx */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472826: cmp eax, 0xff */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 47282b: mov dword ptr [esp + 0x10], eax */
	if (m->zf || m->sf != m->of) goto L_472839;	/* 47282f: jle 0x472839 */
	M32((DWORD)(m->esp + 0x10u)) = 0xffu;	/* 472831: mov dword ptr [esp + 0x10], 0xff */
L_472839:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472839: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x5u))) & 0xff) << 0);	/* 47283b: mov al, byte ptr [edi + 5] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 47283e: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 472841: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 472842: and edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472848: add eax, edx */
	m->ebx = m->eax;	/* 47284a: mov ebx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47284c: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0xfdu))) & 0xff) << 0);	/* 47284e: mov al, byte ptr [ebp + 0xfd] */
	{ DWORD a_ = m->ebx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 472854: sar ebx, 8 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 472857: add ebx, eax */
	{ DWORD a_ = m->ebx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472859: cmp ebx, 0xff */
	if (m->zf || m->sf != m->of) goto L_472866;	/* 47285f: jle 0x472866 */
	m->ebx = 0xffu;	/* 472861: mov ebx, 0xff */
L_472866:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472866: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x6u))) & 0xff) << 0);	/* 472868: mov al, byte ptr [edi + 6] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 47286b: imul eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47286e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47286f: and edx, 0xff */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 472875: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0xfeu))) & 0xff) << 0);	/* 472877: mov cl, byte ptr [ebp + 0xfe] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47287d: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47287f: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472882: add eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472884: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_472890;	/* 472889: jle 0x472890 */
	m->eax = 0xffu;	/* 47288b: mov eax, 0xff */
L_472890:
	m->ecx = (DWORD)(m->ebp + 0xfeu);	/* 472890: lea ecx, [ebp + 0xfe] */
	m->esi = 0xcu;	/* 472896: mov esi, 0xc */
L_47289b:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x10u))) & 0xff) << 0);	/* 47289b: mov dl, byte ptr [esp + 0x10] */
	M8((DWORD)(m->ecx + 0xffffffffu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 47289f: mov byte ptr [ecx - 1], bl */
	M8((DWORD)(m->ecx + 0xfffffffeu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4728a2: mov byte ptr [ecx - 2], dl */
	M8((DWORD)(m->ecx + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4728a5: mov byte ptr [ecx], al */
	M8((DWORD)(m->ecx + 0x1u)) = (BYTE)(0xffu);	/* 4728a7: mov byte ptr [ecx + 1], 0xff */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4728ab: add ecx, 4 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 4728ae: dec esi */
	if (!m->zf) goto L_47289b;	/* 4728af: jne 0x47289b */
L_4728b1:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4728b1: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4728b5: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4728b9: inc eax */
	{ DWORD a_ = m->edi, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4728ba: add edi, 0x2c */
	m->edx = M32((DWORD)(m->ecx + 0x9d8000u));	/* 4728bd: mov edx, dword ptr [ecx + 0x9d8000] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4728c3: mov dword ptr [esp + 0x1c], eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4728c7: cmp eax, edx */
	if (m->sf != m->of) goto L_472475;	/* 4728c9: jl 0x472475 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4728cf: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4728d0: pop ebx */
L_4728d1:
	m->edi = M32(m->esp); m->esp += 4;	/* 4728d1: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4728d2: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4728d3: add esp, 0x14 */
	m->esp += 4 + 28; return;	/* 4728d6: ret 0x1c */
}

/* render_processRenderingBy (0x497d20), lifted by tools/lift.py */
static void lift_497d20(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497d20: sub esp, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 497d23: push ebx */
	m->ebx = m->ecx;	/* 497d24: mov ebx, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 497d26: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 497d27: xor ebp, ebp */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3970u)));	/* 497d29: fld dword ptr [ebx + 0x20f3970] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0xa08u));	/* 497d2f: fsub dword ptr [ebx + 0xa08] */
	m->eax = M32((DWORD)(m->ebx + 0xdc0a74u));	/* 497d35: mov eax, dword ptr [ebx + 0xdc0a74] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 497d3b: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497d3c: cmp eax, ebp */
	M32((DWORD)(m->esp + 0x44u)) = m->ebx;	/* 497d3e: mov dword ptr [esp + 0x44], ebx */
	M32((DWORD)(m->esp + 0x3cu)) = m->ebp;	/* 497d42: mov dword ptr [esp + 0x3c], ebp */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 497d46: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3978u)));	/* 497d4a: fld dword ptr [ebx + 0x20f3978] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0xa08u));	/* 497d50: fsub dword ptr [ebx + 0xa08] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 497d56: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0xa08u)));	/* 497d5a: fld dword ptr [ebx + 0xa08] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3970u));	/* 497d60: fadd dword ptr [ebx + 0x20f3970] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 497d66: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3978u)));	/* 497d6a: fld dword ptr [ebx + 0x20f3978] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0xa08u));	/* 497d70: fadd dword ptr [ebx + 0xa08] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 497d76: fstp dword ptr [esp + 0x34] */
	if (m->zf || m->sf != m->of) goto L_4982aa;	/* 497d7a: jle 0x4982aa */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 497d80: xor ecx, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 497d82: push edi */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 497d83: mov dword ptr [esp + 0x28], ecx */
	m->esi = (DWORD)(m->ebx + 0xdc0268u);	/* 497d87: lea esi, [ebx + 0xdc0268] */
	goto L_497d95;	/* 497d8d: jmp 0x497d95 */
L_497d8f:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 497d8f: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 497d93: xor ebp, ebp */
L_497d95:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffe0u)));	/* 497d95: fld dword ptr [esi - 0x20] */
	m->eax = M32((DWORD)(m->ebx + 0xdc0a8cu));	/* 497d98: mov eax, dword ptr [ebx + 0xdc0a8c] */
	m->edi = M32((DWORD)(m->ebx + 0xdc0cd8u));	/* 497d9e: mov edi, dword ptr [ebx + 0xdc0cd8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x2cu)); FPOP();	/* 497da4: fcomp dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 497da8: add eax, ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 497daa: add edi, ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 497dac: mov dword ptr [esp + 0x3c], eax */
	M32((DWORD)(m->esp + 0x44u)) = m->edi;	/* 497db0: mov dword ptr [esp + 0x44], edi */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 497db4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 497db6: test ah, 1 */
	if (m->zf) goto L_497dcf;	/* 497db9: je 0x497dcf */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 497dbb: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffe0u));	/* 497dbf: fsub dword ptr [esi - 0x20] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 497dc2: fdiv dword ptr [esi] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 497dc4: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 497dc9: mov dword ptr [esp + 0x1c], eax */
	goto L_497dd3;	/* 497dcd: jmp 0x497dd3 */
L_497dcf:
	M32((DWORD)(m->esp + 0x1cu)) = m->ebp;	/* 497dcf: mov dword ptr [esp + 0x1c], ebp */
L_497dd3:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffe8u)));	/* 497dd3: fld dword ptr [esi - 0x18] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x30u)); FPOP();	/* 497dd6: fcomp dword ptr [esp + 0x30] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 497dda: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 497ddc: test ah, 1 */
	if (m->zf) goto L_497df5;	/* 497ddf: je 0x497df5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 497de1: fld dword ptr [esp + 0x30] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffe8u));	/* 497de5: fsub dword ptr [esi - 0x18] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 497de8: fdiv dword ptr [esi] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 497dea: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 497def: mov dword ptr [esp + 0x18], eax */
	goto L_497df9;	/* 497df3: jmp 0x497df9 */
L_497df5:
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 497df5: mov dword ptr [esp + 0x18], ebp */
L_497df9:
	m->ebp = M32((DWORD)(m->esi + 0xfffffffcu));	/* 497df9: mov ebp, dword ptr [esi - 4] */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 497dfc: mov dword ptr [esp + 0x24], ebp */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 497e00: fild dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 497e04: fmul dword ptr [esi] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffe0u));	/* 497e06: fadd dword ptr [esi - 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x34u));	/* 497e09: fcom dword ptr [esp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 497e0d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 497e0f: test ah, 0x41 */
	if (!m->zf) goto L_497e23;	/* 497e12: jne 0x497e23 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 497e14: fsub dword ptr [esp + 0x34] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 497e18: fdiv dword ptr [esi] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 497e1a: call 0x49ec14 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 497e1f: sub ebp, eax */
	goto L_497e25;	/* 497e21: jmp 0x497e25 */
L_497e23:
	ST(0) = ST(0); FPOP();	/* 497e23: fstp st(0) */
L_497e25:
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 497e25: dec ebp */
	M32((DWORD)(m->esp + 0x20u)) = m->ebp;	/* 497e26: mov dword ptr [esp + 0x20], ebp */
	m->ebp = M32((DWORD)(m->esi + 0xfffffff8u));	/* 497e2a: mov ebp, dword ptr [esi - 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 497e2d: mov dword ptr [esp + 0x24], ebp */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 497e31: fild dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 497e35: fmul dword ptr [esi] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0xffffffe0u));	/* 497e37: fadd dword ptr [esi - 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x38u));	/* 497e3a: fcom dword ptr [esp + 0x38] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 497e3e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 497e40: test ah, 0x41 */
	if (!m->zf) goto L_497e54;	/* 497e43: jne 0x497e54 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 497e45: fsub dword ptr [esp + 0x38] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 497e49: fdiv dword ptr [esi] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 497e4b: call 0x49ec14 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 497e50: sub ebp, eax */
	goto L_497e56;	/* 497e52: jmp 0x497e56 */
L_497e54:
	ST(0) = ST(0); FPOP();	/* 497e54: fstp st(0) */
L_497e56:
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 497e56: mov ecx, dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esi + 0x24u));	/* 497e5a: mov eax, dword ptr [esi + 0x24] */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 497e5d: dec ebp */
	M32((DWORD)(m->ecx + 0x58u)) = m->eax;	/* 497e5e: mov dword ptr [ecx + 0x58], eax */
	m->eax = M32((DWORD)(m->esi + 0xfffffffcu));	/* 497e61: mov eax, dword ptr [esi - 4] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 497e64: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 497e68: mov dword ptr [esp + 0x24], ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 497e6c: xor ebp, ebp */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 497e6e: inc eax */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 497e6f: mov dword ptr [esp + 0x10], eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 497e73: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497e77: cmp ecx, eax */
	M32((DWORD)(m->esi + 0x38u)) = m->ebp;	/* 497e79: mov dword ptr [esi + 0x38], ebp */
	M32((DWORD)(m->esi + 0x44u)) = m->ebp;	/* 497e7c: mov dword ptr [esi + 0x44], ebp */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 497e7f: mov dword ptr [esp + 0x14], ecx */
	if (!m->zf && m->sf == m->of) goto L_498051;	/* 497e83: jg 0x498051 */
	goto L_497e8d;	/* 497e89: jmp 0x497e8d */
L_497e8b:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 497e8b: xor ebp, ebp */
L_497e8d:
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 497e8d: mov ebx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 497e91: xor eax, eax */
	m->edx = m->ebx;	/* 497e93: mov edx, ebx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 497e95: xor edi, edi */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esp + 0x20u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497e97: cmp edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 497e9b: mov dword ptr [esp + 0x18], eax */
	if (!m->zf && m->sf == m->of) goto L_498036;	/* 497e9f: jg 0x498036 */
L_497ea5:
	m->edx = m->ecx;	/* 497ea5: mov edx, ecx */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esi + 0xfffffffcu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 497ea7: imul edx, dword ptr [esi - 4] */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esi + 0x18u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 497eab: add edx, dword ptr [esi + 0x18] */
	{ DWORD a_ = M8((DWORD)(m->edx + m->ebx*1 + 0x0u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 497eae: test byte ptr [edx + ebx], 1 */
	if (m->zf) goto L_497f65;	/* 497eb2: je 0x497f65 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 497eb8: test eax, eax */
	if (!m->zf) goto L_497f0f;	/* 497eba: jne 0x497f0f */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 497ebc: mov eax, dword ptr [esi + 0x44] */
	m->edx = M32((DWORD)(m->esi + 0x3cu));	/* 497ebf: mov edx, dword ptr [esi + 0x3c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497ec2: cmp eax, edx */
	if (m->sf != m->of) goto L_497edf;	/* 497ec4: jl 0x497edf */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 497ec6: inc eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 497ec7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 497ec8: push eax */
	{ DWORD v_ = 0x4d056cu; m->esp -= 4; M32(m->esp) = v_; }	/* 497ec9: push 0x4d056c */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 497ece: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x497ed8u; native_call(m, 0x46c710u);	/* 497ed3: call 0x46c710 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 497ed8: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497edc: add esp, 0x10 */
L_497edf:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 497edf: mov eax, dword ptr [esi + 0x44] */
	m->edi = M32((DWORD)(m->esi + 0x40u));	/* 497ee2: mov edi, dword ptr [esi + 0x40] */
	M32((DWORD)(m->esp + 0x18u)) = 0x1u;	/* 497ee5: mov dword ptr [esp + 0x18], 1 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 497eed: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 497ef0: inc eax */
	M32((DWORD)(m->esi + 0x44u)) = m->eax;	/* 497ef1: mov dword ptr [esi + 0x44], eax */
	m->ebp = (DWORD)(m->edi + m->edx*4 + 0x0u);	/* 497ef4: lea ebp, [edi + edx*4] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 497ef7: xor edi, edi */
	M32((DWORD)(m->ebp + 0x0u)) = 0x5u;	/* 497ef9: mov dword ptr [ebp], 5 */
	M32((DWORD)(m->ebp + 0x4u)) = m->edi;	/* 497f00: mov dword ptr [ebp + 4], edi */
	m->eax = M32((DWORD)(m->esi + 0x38u));	/* 497f03: mov eax, dword ptr [esi + 0x38] */
	m->edx = M32((DWORD)(m->esi + 0x34u));	/* 497f06: mov edx, dword ptr [esi + 0x34] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 497f09: lea eax, [edx + eax*4] */
	M32((DWORD)(m->ebp + 0x8u)) = m->eax;	/* 497f0c: mov dword ptr [ebp + 8], eax */
L_497f0f:
	m->eax = M32((DWORD)(m->esi + 0x38u));	/* 497f0f: mov eax, dword ptr [esi + 0x38] */
	m->edx = M32((DWORD)(m->esi + 0x30u));	/* 497f12: mov edx, dword ptr [esi + 0x30] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 497f15: add eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497f18: cmp eax, edx */
	if (m->zf || m->sf != m->of) goto L_497f34;	/* 497f1a: jle 0x497f34 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 497f1c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 497f1d: push eax */
	{ DWORD v_ = 0x4d052cu; m->esp -= 4; M32(m->esp) = v_; }	/* 497f1e: push 0x4d052c */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 497f23: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x497f2du; native_call(m, 0x46c710u);	/* 497f28: call 0x46c710 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 497f2d: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497f31: add esp, 0x10 */
L_497f34:
	m->edx = m->ecx;	/* 497f34: mov edx, ecx */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 497f36: mov eax, dword ptr [ebp + 8] */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 497f39: imul edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 497f3e: add edx, ebx */
	M32((DWORD)(m->eax + m->edi*4 + 0x0u)) = m->edx;	/* 497f40: mov dword ptr [eax + edi*4], edx */
	m->edx = M32((DWORD)(m->esi + 0x38u));	/* 497f43: mov edx, dword ptr [esi + 0x38] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 497f46: inc edi */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 497f47: inc edx */
	M32((DWORD)(m->esi + 0x38u)) = m->edx;	/* 497f48: mov dword ptr [esi + 0x38], edx */
	m->edx = (DWORD)(m->ecx + 0x1u);	/* 497f4b: lea edx, [ecx + 1] */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 497f4e: imul edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 497f53: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 497f56: add edx, ebx */
	M32((DWORD)(m->eax + m->edi*4 + 0x0u)) = m->edx;	/* 497f58: mov dword ptr [eax + edi*4], edx */
	m->eax = M32((DWORD)(m->esi + 0x38u));	/* 497f5b: mov eax, dword ptr [esi + 0x38] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 497f5e: inc edi */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 497f5f: inc eax */
	M32((DWORD)(m->esi + 0x38u)) = m->eax;	/* 497f60: mov dword ptr [esi + 0x38], eax */
	goto L_497fc9;	/* 497f63: jmp 0x497fc9 */
L_497f65:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497f65: cmp eax, 1 */
	if (!m->zf) goto L_497fcd;	/* 497f68: jne 0x497fcd */
	m->eax = M32((DWORD)(m->esi + 0x38u));	/* 497f6a: mov eax, dword ptr [esi + 0x38] */
	m->edx = M32((DWORD)(m->esi + 0x30u));	/* 497f6d: mov edx, dword ptr [esi + 0x30] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 497f70: add eax, 2 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 497f73: mov dword ptr [esp + 0x18], 0 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497f7b: cmp eax, edx */
	if (m->zf || m->sf != m->of) goto L_497f97;	/* 497f7d: jle 0x497f97 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 497f7f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 497f80: push eax */
	{ DWORD v_ = 0x4d052cu; m->esp -= 4; M32(m->esp) = v_; }	/* 497f81: push 0x4d052c */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 497f86: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x497f90u; native_call(m, 0x46c710u);	/* 497f8b: call 0x46c710 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 497f90: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497f94: add esp, 0x10 */
L_497f97:
	m->edx = m->ecx;	/* 497f97: mov edx, ecx */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 497f99: mov eax, dword ptr [ebp + 8] */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 497f9c: imul edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 497fa1: add edx, ebx */
	M32((DWORD)(m->eax + m->edi*4 + 0x0u)) = m->edx;	/* 497fa3: mov dword ptr [eax + edi*4], edx */
	m->edx = M32((DWORD)(m->esi + 0x38u));	/* 497fa6: mov edx, dword ptr [esi + 0x38] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 497fa9: inc edi */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 497faa: inc edx */
	M32((DWORD)(m->esi + 0x38u)) = m->edx;	/* 497fab: mov dword ptr [esi + 0x38], edx */
	m->edx = (DWORD)(m->ecx + 0x1u);	/* 497fae: lea edx, [ecx + 1] */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 497fb1: imul edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 497fb6: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 497fb9: add edx, ebx */
	M32((DWORD)(m->eax + m->edi*4 + 0x0u)) = m->edx;	/* 497fbb: mov dword ptr [eax + edi*4], edx */
	m->eax = M32((DWORD)(m->esi + 0x38u));	/* 497fbe: mov eax, dword ptr [esi + 0x38] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 497fc1: inc edi */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 497fc2: inc eax */
	M32((DWORD)(m->esi + 0x38u)) = m->eax;	/* 497fc3: mov dword ptr [esi + 0x38], eax */
	M32((DWORD)(m->ebp + 0x4u)) = m->edi;	/* 497fc6: mov dword ptr [ebp + 4], edi */
L_497fc9:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 497fc9: mov eax, dword ptr [esp + 0x18] */
L_497fcd:
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 497fcd: mov edx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 497fd1: inc ebx */
	{ DWORD a_ = m->ebx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497fd2: cmp ebx, edx */
	if (m->zf || m->sf != m->of) goto L_497ea5;	/* 497fd4: jle 0x497ea5 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497fda: cmp eax, 1 */
	if (!m->zf) goto L_498036;	/* 497fdd: jne 0x498036 */
	m->eax = M32((DWORD)(m->esi + 0x38u));	/* 497fdf: mov eax, dword ptr [esi + 0x38] */
	m->edx = M32((DWORD)(m->esi + 0x30u));	/* 497fe2: mov edx, dword ptr [esi + 0x30] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 497fe5: add eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497fe8: cmp eax, edx */
	if (m->zf || m->sf != m->of) goto L_498004;	/* 497fea: jle 0x498004 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 497fec: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 497fed: push eax */
	{ DWORD v_ = 0x4d052cu; m->esp -= 4; M32(m->esp) = v_; }	/* 497fee: push 0x4d052c */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 497ff3: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x497ffdu; native_call(m, 0x46c710u);	/* 497ff8: call 0x46c710 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 497ffd: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498001: add esp, 0x10 */
L_498004:
	m->edx = m->ecx;	/* 498004: mov edx, ecx */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 498006: mov eax, dword ptr [ebp + 8] */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 498009: imul edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49800e: add edx, ebx */
	M32((DWORD)(m->eax + m->edi*4 + 0x0u)) = m->edx;	/* 498010: mov dword ptr [eax + edi*4], edx */
	m->edx = M32((DWORD)(m->esi + 0x38u));	/* 498013: mov edx, dword ptr [esi + 0x38] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 498016: inc edi */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 498017: inc edx */
	M32((DWORD)(m->esi + 0x38u)) = m->edx;	/* 498018: mov dword ptr [esi + 0x38], edx */
	m->edx = (DWORD)(m->ecx + 0x1u);	/* 49801b: lea edx, [ecx + 1] */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x10u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 49801e: imul edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 498023: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498026: add edx, ebx */
	M32((DWORD)(m->eax + m->edi*4 + 0x0u)) = m->edx;	/* 498028: mov dword ptr [eax + edi*4], edx */
	m->eax = M32((DWORD)(m->esi + 0x38u));	/* 49802b: mov eax, dword ptr [esi + 0x38] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49802e: inc eax */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 49802f: inc edi */
	M32((DWORD)(m->esi + 0x38u)) = m->eax;	/* 498030: mov dword ptr [esi + 0x38], eax */
	M32((DWORD)(m->ebp + 0x4u)) = m->edi;	/* 498033: mov dword ptr [ebp + 4], edi */
L_498036:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 498036: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49803a: inc ecx */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49803b: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 49803d: mov dword ptr [esp + 0x14], ecx */
	if (m->zf || m->sf != m->of) goto L_497e8b;	/* 498041: jle 0x497e8b */
	m->edi = M32((DWORD)(m->esp + 0x44u));	/* 498047: mov edi, dword ptr [esp + 0x44] */
	m->ebx = M32((DWORD)(m->esp + 0x48u));	/* 49804b: mov ebx, dword ptr [esp + 0x48] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 49804f: xor ebp, ebp */
L_498051:
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 498051: mov edx, dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esi + 0x44u));	/* 498055: mov ecx, dword ptr [esi + 0x44] */
	M32((DWORD)(m->edx + 0x60u)) = m->ecx;	/* 498058: mov dword ptr [edx + 0x60], ecx */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 49805b: mov eax, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49805e: cmp eax, 1 */
	if (!m->zf) goto L_498279;	/* 498061: jne 0x498279 */
	M32((DWORD)(m->edi + 0x60u)) = 0x4u;	/* 498067: mov dword ptr [edi + 0x60], 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 49806e: mov dword ptr [esp + 0x24], ebp */
	M32((DWORD)(m->esp + 0x3cu)) = m->ebp;	/* 498072: mov dword ptr [esp + 0x3c], ebp */
L_498076:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0xa08u)));	/* 498076: fld dword ptr [ebx + 0xa08] */
	ST(0) = -ST(0);	/* 49807c: fchs  */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0);	/* 49807e: fst dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffe4u)));	/* 498082: fld dword ptr [esi - 0x1c] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 498085: fstp dword ptr [esp + 0x50] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 498089: push ebp */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49808a: push 2 */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 49808c: fstp dword ptr [esp + 0x5c] */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 498090: lea ecx, [esp + 0x54] */
	m->esp -= 4; M32(m->esp) = 0x498099u; native_call(m, 0x4677c0u);	/* 498094: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 498099: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3970u));	/* 49809d: fadd dword ptr [ebx + 0x20f3970] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 4980a3: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->ebp, b_ = 0x384u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4980a7: add ebp, 0x384 */
	m->eax = m->ecx;	/* 4980ad: mov eax, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4980af: add ecx, 0xc */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 4980b2: mov dword ptr [esp + 0x3c], ecx */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4980b6: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 4980ba: fld dword ptr [esp + 0x54] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3978u));	/* 4980be: fadd dword ptr [ebx + 0x20f3978] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 4980c4: fstp dword ptr [esp + 0x54] */
	m->edx = M32((DWORD)(m->edi + 0x50u));	/* 4980c8: mov edx, dword ptr [edi + 0x50] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4980cb: add eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 4980cd: mov edx, dword ptr [esp + 0x4c] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 4980d1: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 4980d3: mov edx, dword ptr [esp + 0x50] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4980d7: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 4980da: mov edx, dword ptr [esp + 0x54] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 4980de: mov dword ptr [eax + 8], edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4980e1: mov edx, dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 4980e5: fld dword ptr [esp + 0x54] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 4980e9: fdiv dword ptr [esi + 8] */
	m->eax = m->edx;	/* 4980ec: mov eax, edx */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4980ee: add edx, 8 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->edi + 0x5cu)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4980f1: add eax, dword ptr [edi + 0x5c] */
	{ DWORD a_ = m->ebp, b_ = 0xe10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4980f4: cmp ebp, 0xe10 */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 4980fa: mov dword ptr [esp + 0x24], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4980fe: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 498102: fdiv dword ptr [esi + 8] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 498105: fstp dword ptr [eax] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 498107: fstp dword ptr [eax + 4] */
	if (m->sf != m->of) goto L_498076;	/* 49810a: jl 0x498076 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 498110: xor ebp, ebp */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 498112: mov dword ptr [esp + 0x24], ebp */
	M32((DWORD)(m->esp + 0x3cu)) = m->ebp;	/* 498116: mov dword ptr [esp + 0x3c], ebp */
L_49811a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0xa08u)));	/* 49811a: fld dword ptr [ebx + 0xa08] */
	ST(0) = -ST(0);	/* 498120: fchs  */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0);	/* 498122: fst dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffe4u)));	/* 498126: fld dword ptr [esi - 0x1c] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 498129: fstp dword ptr [esp + 0x50] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49812d: push ebp */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49812e: push 2 */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 498130: fstp dword ptr [esp + 0x5c] */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 498134: lea ecx, [esp + 0x54] */
	m->esp -= 4; M32(m->esp) = 0x49813du; native_call(m, 0x4677c0u);	/* 498138: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 49813d: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3970u));	/* 498141: fadd dword ptr [ebx + 0x20f3970] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 498147: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->ebp, b_ = 0x384u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 49814b: add ebp, 0x384 */
	m->eax = m->ecx;	/* 498151: mov eax, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498153: add ecx, 0xc */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 498156: mov dword ptr [esp + 0x3c], ecx */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49815a: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 49815e: fld dword ptr [esp + 0x54] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3978u));	/* 498162: fadd dword ptr [ebx + 0x20f3978] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 498168: fstp dword ptr [esp + 0x54] */
	m->edx = M32((DWORD)(m->edi + 0x50u));	/* 49816c: mov edx, dword ptr [edi + 0x50] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49816f: add eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 498171: mov edx, dword ptr [esp + 0x4c] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 498175: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 498177: mov edx, dword ptr [esp + 0x50] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 49817b: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 49817e: mov edx, dword ptr [esp + 0x54] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 498182: mov dword ptr [eax + 8], edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 498185: mov edx, dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 498189: fld dword ptr [esp + 0x54] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 49818d: fdiv dword ptr [esi + 8] */
	m->eax = m->edx;	/* 498190: mov eax, edx */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498192: add edx, 8 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->edi + 0x5cu)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 498195: add eax, dword ptr [edi + 0x5c] */
	{ DWORD a_ = m->ebp, b_ = 0xe10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498198: cmp ebp, 0xe10 */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49819e: mov dword ptr [esp + 0x24], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4981a2: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 4981a6: fdiv dword ptr [esi + 8] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 4981a9: fstp dword ptr [eax] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 4981ab: fstp dword ptr [eax + 4] */
	if (m->sf != m->of) goto L_49811a;	/* 4981ae: jl 0x49811a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 4981b4: fld dword ptr [esp + 0x60] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa500u));	/* 4981b8: fmul dword ptr [0x4aa500] */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 4981be: mov dword ptr [esp + 0x24], 0 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x20u;	/* 4981c6: mov dword ptr [esp + 0x3c], 0x20 */
	m->ebp = 0x30u;	/* 4981ce: mov ebp, 0x30 */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4981d3: fstp dword ptr [esp + 0x44] */
L_4981d7:
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4981d7: mov ecx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 4981db: mov eax, dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xffffffe4u)));	/* 4981df: fld dword ptr [esi - 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4981e2: push ecx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4981e3: push 2 */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 4981e5: fstp dword ptr [esp + 0x58] */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 4981e9: lea ecx, [esp + 0x54] */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 4981ed: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x5cu)) = m->eax;	/* 4981f5: mov dword ptr [esp + 0x5c], eax */
	m->esp -= 4; M32(m->esp) = 0x4981feu; native_call(m, 0x4677c0u);	/* 4981f9: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4981fe: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3970u));	/* 498202: fadd dword ptr [ebx + 0x20f3970] */
	m->edx = m->ebp;	/* 498208: mov edx, ebp */
	{ DWORD a_ = m->ebp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 49820a: add ebp, 0xc */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49820d: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 498211: fld dword ptr [esp + 0x54] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3978u));	/* 498215: fadd dword ptr [ebx + 0x20f3978] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 49821b: fstp dword ptr [esp + 0x54] */
	m->eax = M32((DWORD)(m->edi + 0x50u));	/* 49821f: mov eax, dword ptr [edi + 0x50] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498222: add edx, eax */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 498224: mov eax, dword ptr [esp + 0x4c] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 498228: mov dword ptr [edx], eax */
	m->ecx = M32((DWORD)(m->esp + 0x50u));	/* 49822a: mov ecx, dword ptr [esp + 0x50] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 49822e: mov dword ptr [edx + 4], ecx */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 498231: mov eax, dword ptr [esp + 0x54] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 498235: mov ecx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 498239: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->edi + 0x5cu));	/* 49823c: mov edx, dword ptr [edi + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 49823f: fld dword ptr [esp + 0x54] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 498243: fdiv dword ptr [esi + 8] */
	m->eax = m->ecx;	/* 498246: mov eax, ecx */
	{ DWORD a_ = m->ecx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498248: add ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49824b: add eax, edx */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 49824d: mov dword ptr [esp + 0x3c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 498251: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = 0x1c2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498255: add ecx, 0x1c2 */
	{ DWORD a_ = m->ebp, b_ = 0x90u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49825b: cmp ebp, 0x90 */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 498261: mov dword ptr [esp + 0x24], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 498265: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 498269: fdiv dword ptr [esi + 8] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 49826c: fstp dword ptr [eax] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 49826e: fstp dword ptr [eax + 4] */
	if (m->sf != m->of) goto L_4981d7;	/* 498271: jl 0x4981d7 */
	goto L_49827c;	/* 498277: jmp 0x49827c */
L_498279:
	M32((DWORD)(m->edi + 0x60u)) = m->ebp;	/* 498279: mov dword ptr [edi + 0x60], ebp */
L_49827c:
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 49827c: mov eax, dword ptr [esp + 0x40] */
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 498280: mov edi, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->ebx + 0xdc0a74u));	/* 498284: mov ecx, dword ptr [ebx + 0xdc0a74] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49828a: inc eax */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49828b: add edi, 0x80 */
	{ DWORD a_ = m->esi, b_ = 0x20cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 498291: add esi, 0x20c */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498297: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x40u)) = m->eax;	/* 498299: mov dword ptr [esp + 0x40], eax */
	M32((DWORD)(m->esp + 0x28u)) = m->edi;	/* 49829d: mov dword ptr [esp + 0x28], edi */
	if (m->sf != m->of) goto L_497d8f;	/* 4982a1: jl 0x497d8f */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4982a7: xor ebp, ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 4982a9: pop edi */
L_4982aa:
	m->esi = M32((DWORD)(m->esp + 0x58u));	/* 4982aa: mov esi, dword ptr [esp + 0x58] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982ae: push ebp */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4982af: push -1 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982b1: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982b2: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982b3: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982b4: push ebp */
	m->ecx = (DWORD)(m->ebx + 0xdc0cc4u);	/* 4982b5: lea ecx, [ebx + 0xdc0cc4] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982bb: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4982bc: push ecx */
	m->ecx = m->esi;	/* 4982bd: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4982c4u; native_call(m, 0x4853c0u);	/* 4982bf: call 0x4853c0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982c4: push ebp */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4982c5: push -1 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982c7: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982c8: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982c9: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982ca: push ebp */
	{ DWORD a_ = m->ebx, b_ = 0xdc0a78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4982cb: add ebx, 0xdc0a78 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4982d1: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4982d2: push ebx */
	m->ecx = m->esi;	/* 4982d3: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4982dau; native_call(m, 0x4853c0u);	/* 4982d5: call 0x4853c0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4982da: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4982db: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4982dc: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4982dd: add esp, 0x48 */
	m->esp += 4 + 8; return;	/* 4982e0: ret 8 */
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
