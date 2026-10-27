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

static void lift_4700a0(X86 *m);

/* item_initTextures (0x4700a0), lifted by tools/lift.py */
static void lift_4700a0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4700a0: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4700a4: sub esp, 0x128 */
	m->edx = M32((DWORD)(m->esp + 0x144u));	/* 4700aa: mov edx, dword ptr [esp + 0x144] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4700b1: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4700b2: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4700b3: push esi */
	m->esi = m->ecx;	/* 4700b4: mov esi, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x154u));	/* 4700b6: mov ecx, dword ptr [esp + 0x154] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4700bd: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4700be: push eax */
	m->eax = M32((DWORD)(m->esp + 0x154u));	/* 4700bf: mov eax, dword ptr [esp + 0x154] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4700c6: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x154u));	/* 4700c7: mov ecx, dword ptr [esp + 0x154] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4700ce: push edx */
	m->edx = M32((DWORD)(m->esp + 0x154u));	/* 4700cf: mov edx, dword ptr [esp + 0x154] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4700d6: push eax */
	m->eax = M32((DWORD)(m->esp + 0x154u));	/* 4700d7: mov eax, dword ptr [esp + 0x154] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4700de: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x154u));	/* 4700df: mov ecx, dword ptr [esp + 0x154] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4700e6: push edx */
	m->edx = M32((DWORD)(m->esp + 0x154u));	/* 4700e7: mov edx, dword ptr [esp + 0x154] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4700ee: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4700ef: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4700f0: push edx */
	m->ecx = m->esi;	/* 4700f1: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4700f8u; native_call(m, 0x470de0u);	/* 4700f3: call 0x470de0 */
	m->eax = (DWORD)(m->esi + 0xb04u);	/* 4700f8: lea eax, [esi + 0xb04] */
	{ DWORD v_ = 0x9c95f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4700fe: push 0x9c95f0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470103: push eax */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 470104: push 0x3e8 */
	{ DWORD v_ = 0x2710u; m->esp -= 4; M32(m->esp) = v_; }	/* 470109: push 0x2710 */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 47010e: push 0x3e8 */
	{ DWORD v_ = 0x27100u; m->esp -= 4; M32(m->esp) = v_; }	/* 470113: push 0x27100 */
	{ DWORD v_ = 0x9c40u; m->esp -= 4; M32(m->esp) = v_; }	/* 470118: push 0x9c40 */
	m->ecx = (DWORD)(m->esi + 0xa10u);	/* 47011d: lea ecx, [esi + 0xa10] */
	m->esp -= 4; M32(m->esp) = 0x470128u; native_call(m, 0x4813e0u);	/* 470123: call 0x4813e0 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 470128: xor ebx, ebx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 47012a: xor edi, edi */
	m->ebp = (DWORD)(m->esi + 0x9ccfd4u);	/* 47012c: lea ebp, [esi + 0x9ccfd4] */
L_470132:
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 470132: mov ecx, dword ptr [esp + 0x144] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 470139: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47013a: push ecx */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 47013b: lea edx, [esp + 0x40] */
	{ DWORD v_ = 0x4c7410u; m->esp -= 4; M32(m->esp) = v_; }	/* 47013f: push 0x4c7410 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 470144: push edx */
	m->esp -= 4; M32(m->esp) = 0x47014au; native_call(m, 0x49e9ddu);	/* 470145: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47014a: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47014d: cmp edi, 7 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470150: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470151: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470152: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470153: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470154: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470155: push ebx */
	if (!m->zf && m->sf == m->of) goto L_470160;	/* 470156: jg 0x470160 */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 470158: lea eax, [esp + 0x50] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47015c: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47015d: push eax */
	goto L_470167;	/* 47015e: jmp 0x470167 */
L_470160:
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 470160: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 470164: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 470166: push ecx */
L_470167:
	m->ecx = M32((DWORD)(0xa0e010u));	/* 470167: mov ecx, dword ptr [0xa0e010] */
	m->esp -= 4; M32(m->esp) = 0x470172u; native_call(m, 0x456be0u);	/* 47016d: call 0x456be0 */
	M32((DWORD)(m->ebp + 0x0u)) = m->eax;	/* 470172: mov dword ptr [ebp], eax */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 470175: inc edi */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 470176: add ebp, 4 */
	{ DWORD a_ = m->edi, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 470179: cmp edi, 0xa */
	if (m->sf != m->of) goto L_470132;	/* 47017c: jl 0x470132 */
	m->edi = (DWORD)(m->esi + 0x9ccffcu);	/* 47017e: lea edi, [esi + 0x9ccffc] */
	m->ecx = m->edi;	/* 470184: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x47018bu; native_call(m, 0x483d60u);	/* 470186: call 0x483d60 */
	{ DWORD v_ = 0xa1f23cu; m->esp -= 4; M32(m->esp) = v_; }	/* 47018b: push 0xa1f23c */
	m->ecx = m->edi;	/* 470190: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x470197u; native_call(m, 0x483e90u);	/* 470192: call 0x483e90 */
	m->ecx = m->esi;	/* 470197: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x47019eu; native_call(m, 0x4723e0u);	/* 470199: call 0x4723e0 */
	m->edi = (DWORD)(m->esi + 0x9e3020u);	/* 47019e: lea edi, [esi + 0x9e3020] */
	m->ecx = m->edi;	/* 4701a4: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4701abu; native_call(m, 0x483d60u);	/* 4701a6: call 0x483d60 */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 4701ab: lea edx, [esp + 0x2c] */
	m->ecx = m->edi;	/* 4701af: mov ecx, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4701b1: push edx */
	M8((DWORD)(m->esp + 0x30u)) = (BYTE)(0x40u);	/* 4701b2: mov byte ptr [esp + 0x30], 0x40 */
	M8((DWORD)(m->esp + 0x31u)) = (BYTE)(0x40u);	/* 4701b7: mov byte ptr [esp + 0x31], 0x40 */
	M8((DWORD)(m->esp + 0x32u)) = (BYTE)(0x40u);	/* 4701bc: mov byte ptr [esp + 0x32], 0x40 */
	M8((DWORD)(m->esp + 0x33u)) = (BYTE)(0xffu);	/* 4701c1: mov byte ptr [esp + 0x33], 0xff */
	m->esp -= 4; M32(m->esp) = 0x4701cbu; native_call(m, 0x483e90u);	/* 4701c6: call 0x483e90 */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 4701cb: lea eax, [esp + 0x18] */
	m->ecx = m->edi;	/* 4701cf: mov ecx, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4701d1: push eax */
	{ DWORD v_ = 0xa1f23cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4701d2: push 0xa1f23c */
	M32((DWORD)(m->esp + 0x20u)) = 0xbf800000u;	/* 4701d7: mov dword ptr [esp + 0x20], 0xbf800000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xbf800000u;	/* 4701df: mov dword ptr [esp + 0x24], 0xbf800000 */
	M32((DWORD)(m->esp + 0x28u)) = 0xbf800000u;	/* 4701e7: mov dword ptr [esp + 0x28], 0xbf800000 */
	m->esp -= 4; M32(m->esp) = 0x4701f4u; native_call(m, 0x483ec0u);	/* 4701ef: call 0x483ec0 */
	FPUSH((long double)*(const double *)(DWORD)(0x4aa408u));	/* 4701f4: fld qword ptr [0x4aa408] */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 4701fa: fsqrt  */
	M32((DWORD)(m->esi + 0x9ee030u)) = m->ebx;	/* 4701fc: mov dword ptr [esi + 0x9ee030], ebx */
	M32((DWORD)(m->esi + 0x9ee034u)) = m->ebx;	/* 470202: mov dword ptr [esi + 0x9ee034], ebx */
	M32((DWORD)(m->esi + 0x9ee038u)) = m->ebx;	/* 470208: mov dword ptr [esi + 0x9ee038], ebx */
	M32((DWORD)(m->esi + 0x9ee03cu)) = m->ebx;	/* 47020e: mov dword ptr [esi + 0x9ee03c], ebx */
	M32((DWORD)(m->esi + 0x9ee040u)) = m->ebx;	/* 470214: mov dword ptr [esi + 0x9ee040], ebx */
	M32((DWORD)(m->esi + 0x9ee044u)) = m->ebx;	/* 47021a: mov dword ptr [esi + 0x9ee044], ebx */
	M32((DWORD)(m->esi + 0x9ee048u)) = m->ebx;	/* 470220: mov dword ptr [esi + 0x9ee048], ebx */
	M32((DWORD)(m->esi + 0x9ee04cu)) = m->ebx;	/* 470226: mov dword ptr [esi + 0x9ee04c], ebx */
	M32((DWORD)(m->esi + 0x9ee050u)) = m->ebx;	/* 47022c: mov dword ptr [esi + 0x9ee050], ebx */
	M32((DWORD)(m->esi + 0x9ee054u)) = m->ebx;	/* 470232: mov dword ptr [esi + 0x9ee054], ebx */
	M32((DWORD)(m->esi + 0x9ee058u)) = m->ebx;	/* 470238: mov dword ptr [esi + 0x9ee058], ebx */
	M32((DWORD)(m->esi + 0x9ee05cu)) = m->ebx;	/* 47023e: mov dword ptr [esi + 0x9ee05c], ebx */
	M32((DWORD)(m->esi + 0x9ee060u)) = m->ebx;	/* 470244: mov dword ptr [esi + 0x9ee060], ebx */
	M32((DWORD)(m->esi + 0x9ee064u)) = m->ebx;	/* 47024a: mov dword ptr [esi + 0x9ee064], ebx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 470250: xor edi, edi */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 470252: fdivr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 470258: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 47025c: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 470262: fstp dword ptr [esp + 0x30] */
L_470266:
	m->eax = (DWORD)(m->edi + m->edi*2 + 0x0u);	/* 470266: lea eax, [edi + edi*2] */
	M32((DWORD)(m->esi + m->edi*4 + 0x9ee068u)) = 0xffffffffu;	/* 470269: mov dword ptr [esi + edi*4 + 0x9ee068], 0xffffffff */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 470274: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 470277: add eax, edi */
	M32((DWORD)(m->esp + 0x10u)) = 0x3u;	/* 470279: mov dword ptr [esp + 0x10], 3 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 470281: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->esi + m->ecx*4 + 0x9ee080u);	/* 470284: lea eax, [esi + ecx*4 + 0x9ee080] */
L_47028b:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 47028b: fild dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 47028f: xor ebp, ebp */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 470291: mov dword ptr [esp + 0x28], eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 470295: fstp dword ptr [esp + 0x24] */
L_470299:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 470299: fld dword ptr [esp + 0x24] */
	m->edx = (DWORD)(m->ebp + 0xfffffffdu);	/* 47029d: lea edx, [ebp - 3] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4702a0: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 4702a4: mov dword ptr [esp + 0x34], edx */
	{ DWORD a_ = m->edi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4702a8: cmp edi, 5 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x34u)));	/* 4702ab: fild dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4702af: mov dword ptr [esp + 0x18], eax */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4702b3: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4702b7: fld dword ptr [esp + 0x14] */
	ST(0) = ST(0) * ST(1);	/* 4702bb: fmul st(1) */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4702bd: fstp dword ptr [esp + 0x1c] */
	ST(0) = ST(0); FPOP();	/* 4702c1: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4702c3: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 4702c7: fmul dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4702cb: fstp dword ptr [esp + 0x20] */
	if (!m->cf && !m->zf) goto L_470306;	/* 4702cf: ja 0x470306 */
	switch (m->edi) { case 0: goto L_4702d8; case 1: goto L_4702df; case 2: goto L_4702df; case 3: goto L_4702df; case 4: goto L_4702df; case 5: goto L_4702f7; default: abort(); }	/* 4702d1: jmp dword ptr [edi*4 + 0x470a54] */
L_4702d8:
	{ DWORD v_ = 0x384u; m->esp -= 4; M32(m->esp) = v_; }	/* 4702d8: push 0x384 */
	goto L_4702fc;	/* 4702dd: jmp 0x4702fc */
L_4702df:
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 4702df: lea eax, [edi + edi*4] */
	m->edx = 0x384u;	/* 4702e2: mov edx, 0x384 */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4702e7: lea eax, [eax + eax*8] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4702ea: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4702ed: shl ecx, 2 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4702f0: sub edx, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4702f2: push edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4702f3: push 2 */
	goto L_4702fd;	/* 4702f5: jmp 0x4702fd */
L_4702f7:
	{ DWORD v_ = 0xfffffc7cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4702f7: push 0xfffffc7c */
L_4702fc:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4702fc: push ebx */
L_4702fd:
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 4702fd: lea ecx, [esp + 0x20] */
	m->esp -= 4; M32(m->esp) = 0x470306u; native_call(m, 0x4677c0u);	/* 470301: call 0x4677c0 */
L_470306:
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 470306: mov eax, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 47030a: mov edx, dword ptr [esp + 0x18] */
	m->ecx = m->eax;	/* 47030e: mov ecx, eax */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 470310: inc ebp */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 470311: add eax, 0xc */
	{ DWORD a_ = m->ebp, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 470314: cmp ebp, 6 */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 470317: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 470319: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 47031d: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 470321: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 470324: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 470328: mov dword ptr [ecx + 8], edx */
	if (m->zf || m->sf != m->of) goto L_470299;	/* 47032b: jle 0x470299 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 470331: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 470335: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 470336: cmp ecx, -3 */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 470339: mov dword ptr [esp + 0x10], ecx */
	if (m->sf == m->of) goto L_47028b;	/* 47033d: jge 0x47028b */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 470343: inc edi */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 470344: cmp edi, 6 */
	if (m->sf != m->of) goto L_470266;	/* 470347: jl 0x470266 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47034d: or eax, 0xffffffff */
	M32((DWORD)(m->esi + 0x9eee48u)) = m->ebx;	/* 470350: mov dword ptr [esi + 0x9eee48], ebx */
	M32((DWORD)(m->esi + 0x9eee4cu)) = m->eax;	/* 470356: mov dword ptr [esi + 0x9eee4c], eax */
	M32((DWORD)(m->esi + 0x9eee50u)) = m->eax;	/* 47035c: mov dword ptr [esi + 0x9eee50], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 470362: mov dword ptr [esp + 0x10], ebx */
	m->edi = (DWORD)(m->esi + 0x9eee54u);	/* 470366: lea edi, [esi + 0x9eee54] */
L_47036c:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 47036c: fild dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 470370: xor ebp, ebp */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 470372: mov dword ptr [esp + 0x14], ebp */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 470376: fsub dword ptr [0x4a9534] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 47037c: fmul dword ptr [0x4a93f0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 470382: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 470387: mov dword ptr [esp + 0x30], eax */
L_47038b:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47038b: mov eax, dword ptr [esp + 0x30] */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 47038f: lea ecx, [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470393: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 470394: push 1 */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 470396: mov dword ptr [esp + 0x20], 0 */
	M32((DWORD)(m->esp + 0x24u)) = 0x3f800000u;	/* 47039e: mov dword ptr [esp + 0x24], 0x3f800000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 4703a6: mov dword ptr [esp + 0x28], 0 */
	m->esp -= 4; M32(m->esp) = 0x4703b3u; native_call(m, 0x4677c0u);	/* 4703ae: call 0x4677c0 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4703b3: fild dword ptr [esp + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 4703b7: fsub dword ptr [0x4a9534] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 4703bd: fmul dword ptr [0x4a93f0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4703c3: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4703c8: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4703c9: push ebx */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 4703ca: lea ecx, [esp + 0x20] */
	m->esp -= 4; M32(m->esp) = 0x4703d3u; native_call(m, 0x4677c0u);	/* 4703ce: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4703d3: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4703d7: fsub dword ptr [0x4a942c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4703dd: mov edx, dword ptr [esp + 0x18] */
	m->ecx = m->edi;	/* 4703e1: mov ecx, edi */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 4703e3: inc ebp */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4703e4: add edi, 0xc */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 4703e7: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4703e9: mov edx, dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4703ed: fstp dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4703f1: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ebp, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4703f5: cmp ebp, 6 */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 4703f8: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 4703fb: mov dword ptr [esp + 0x14], ebp */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 4703ff: mov dword ptr [ecx + 8], edx */
	if (m->zf || m->sf != m->of) goto L_47038b;	/* 470402: jle 0x47038b */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 470404: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 470408: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 470409: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 47040c: mov dword ptr [esp + 0x10], eax */
	if (m->zf || m->sf != m->of) goto L_47036c;	/* 470410: jle 0x47036c */
	M32((DWORD)(m->esi + 0x9ef0a0u)) = m->ebx;	/* 470416: mov dword ptr [esi + 0x9ef0a0], ebx */
	M32((DWORD)(m->esi + 0x9ef0a4u)) = m->ebx;	/* 47041c: mov dword ptr [esi + 0x9ef0a4], ebx */
	m->eax = (DWORD)(m->esi + 0x9ef104u);	/* 470422: lea eax, [esi + 0x9ef104] */
	m->ecx = (DWORD)(m->esi + 0x9ef0b4u);	/* 470428: lea ecx, [esi + 0x9ef0b4] */
	M32((DWORD)(m->esi + 0x9ef0a8u)) = m->ebx;	/* 47042e: mov dword ptr [esi + 0x9ef0a8], ebx */
	M32((DWORD)(m->esi + 0x9ef0acu)) = m->ebx;	/* 470434: mov dword ptr [esi + 0x9ef0ac], ebx */
	M32((DWORD)(m->esi + 0x9ef0b0u)) = m->ebx;	/* 47043a: mov dword ptr [esi + 0x9ef0b0], ebx */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 470440: mov dword ptr [esp + 0x10], ebx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 470444: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 470448: mov dword ptr [esp + 0x14], ecx */
L_47044c:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 47044c: mov edx, dword ptr [esp + 0x14] */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 470450: mov ebp, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 470454: mov edi, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x24u)) = 0x4u;	/* 470458: mov dword ptr [esp + 0x24], 4 */
	M32((DWORD)(m->edx + 0x0u)) = 0xffffffffu;	/* 470460: mov dword ptr [edx], 0xffffffff */
L_470466:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 470466: push ebp */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 470467: push 2 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 470469: lea ecx, [esp + 0x20] */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 47046d: mov dword ptr [esp + 0x20], 0 */
	M32((DWORD)(m->esp + 0x24u)) = 0x3f800000u;	/* 470475: mov dword ptr [esp + 0x24], 0x3f800000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x3f800000u;	/* 47047d: mov dword ptr [esp + 0x28], 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x47048au; native_call(m, 0x4677c0u);	/* 470485: call 0x4677c0 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 47048a: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 47048e: mov edx, dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 470492: fld dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->edi + 0xffffffc8u);	/* 470496: lea eax, [edi - 0x38] */
	{ DWORD a_ = m->ebp, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 470499: add ebp, 0xc8 */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47049f: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4704a1: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4704a5: add edi, 0xc */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4704a8: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 4704ab: mov dword ptr [eax + 8], ecx */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4704ae: mov eax, dword ptr [esp + 0x24] */
	MF((DWORD)(m->edi + 0xffffffecu)) = (float)ST(0); FPOP();	/* 4704b2: fstp dword ptr [edi - 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4704b5: fld dword ptr [esp + 0x20] */
	MF((DWORD)(m->edi + 0xfffffff4u)) = (float)ST(0); FPOP();	/* 4704b9: fstp dword ptr [edi - 0xc] */
	M32((DWORD)(m->edi + 0xfffffff0u)) = m->ebx;	/* 4704bc: mov dword ptr [edi - 0x10], ebx */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4704bf: dec eax */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4704c0: mov dword ptr [esp + 0x24], eax */
	if (!m->zf) goto L_470466;	/* 4704c4: jne 0x470466 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4704c6: mov eax, dword ptr [esp + 0x10] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 4704ca: mov ebp, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 4704ce: mov edx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->eax, b_ = 0x258u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4704d2: add eax, 0x258 */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4704d7: add ebp, 4 */
	{ DWORD a_ = m->edx, b_ = 0x60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4704da: add edx, 0x60 */
	{ DWORD a_ = m->eax, b_ = 0xe10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4704dd: cmp eax, 0xe10 */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 4704e2: mov dword ptr [esp + 0x14], ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4704e6: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 4704ea: mov dword ptr [esp + 0x28], edx */
	if (m->sf != m->of) goto L_47044c;	/* 4704ee: jl 0x47044c */
	m->edi = (DWORD)(m->esi + 0x9ef310u);	/* 4704f4: lea edi, [esi + 0x9ef310] */
	m->ecx = 0x10u;	/* 4704fa: mov ecx, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4704ff: or eax, 0xffffffff */
	M32((DWORD)(m->esi + 0x9ef30cu)) = m->ebx;	/* 470502: mov dword ptr [esi + 0x9ef30c], ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 470508: rep stosd dword ptr es:[edi], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 47050a: mov dword ptr [esp + 0x10], ebx */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 47050e: mov dword ptr [esp + 0x1c], 0 */
	m->eax = (DWORD)(m->esi + 0x9ef350u);	/* 470516: lea eax, [esi + 0x9ef350] */
L_47051c:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 47051c: fild dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 470520: xor ecx, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 470522: mov dword ptr [esp + 0x14], ecx */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 470526: fsub dword ptr [0x4a93d0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa400u));	/* 47052c: fmul dword ptr [0x4aa400] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 470532: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 470536: mov edx, dword ptr [esp + 0x20] */
L_47053a:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 47053a: fild dword ptr [esp + 0x14] */
	m->edi = m->eax;	/* 47053e: mov edi, eax */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 470540: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 470541: add eax, 0xc */
	{ DWORD a_ = m->ecx, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 470544: cmp ecx, 0xa */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 470547: fsub dword ptr [0x4a93d0] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47054d: mov dword ptr [esp + 0x14], ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa400u));	/* 470551: fmul dword ptr [0x4aa400] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 470557: fstp dword ptr [esp + 0x18] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 47055b: mov ebp, dword ptr [esp + 0x18] */
	M32((DWORD)(m->edi + 0x0u)) = m->ebp;	/* 47055f: mov dword ptr [edi], ebp */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 470561: mov ebp, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->edi + 0x4u)) = m->ebp;	/* 470565: mov dword ptr [edi + 4], ebp */
	M32((DWORD)(m->edi + 0x8u)) = m->edx;	/* 470568: mov dword ptr [edi + 8], edx */
	if (m->zf || m->sf != m->of) goto L_47053a;	/* 47056b: jle 0x47053a */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 47056d: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 470571: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 470572: cmp ecx, 0xa */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 470575: mov dword ptr [esp + 0x10], ecx */
	if (m->zf || m->sf != m->of) goto L_47051c;	/* 470579: jle 0x47051c */
	m->eax = 0xc7c35000u;	/* 47057b: mov eax, 0xc7c35000 */
	M32((DWORD)(m->esi + 0x9ef8fcu)) = m->ebx;	/* 470580: mov dword ptr [esi + 0x9ef8fc], ebx */
	M32((DWORD)(m->esi + 0x9ef900u)) = m->ebx;	/* 470586: mov dword ptr [esi + 0x9ef900], ebx */
	M32((DWORD)(m->esi + 0x9ef904u)) = m->eax;	/* 47058c: mov dword ptr [esi + 0x9ef904], eax */
	M32((DWORD)(m->esi + 0x9ef908u)) = m->eax;	/* 470592: mov dword ptr [esi + 0x9ef908], eax */
	M32((DWORD)(m->esi + 0x9ef90cu)) = m->eax;	/* 470598: mov dword ptr [esi + 0x9ef90c], eax */
	m->eax = 0x47c35000u;	/* 47059e: mov eax, 0x47c35000 */
	m->edx = (DWORD)(m->esi + 0x9ef91cu);	/* 4705a3: lea edx, [esi + 0x9ef91c] */
	M32((DWORD)(m->esi + 0x9ef910u)) = m->eax;	/* 4705a9: mov dword ptr [esi + 0x9ef910], eax */
	M32((DWORD)(m->esi + 0x9ef914u)) = m->eax;	/* 4705af: mov dword ptr [esi + 0x9ef914], eax */
	M32((DWORD)(m->esi + 0x9ef918u)) = m->eax;	/* 4705b5: mov dword ptr [esi + 0x9ef918], eax */
	m->eax = M32((DWORD)(m->esi + 0x9ef904u));	/* 4705bb: mov eax, dword ptr [esi + 0x9ef904] */
	m->ecx = M32((DWORD)(m->esi + 0x9ef908u));	/* 4705c1: mov ecx, dword ptr [esi + 0x9ef908] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 4705c7: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esi + 0x9ef90cu));	/* 4705c9: mov eax, dword ptr [esi + 0x9ef90c] */
	{ DWORD v_ = 0xf4240u; m->esp -= 4; M32(m->esp) = v_; }	/* 4705cf: push 0xf4240 */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 4705d4: mov dword ptr [edx + 4], ecx */
	m->ecx = (DWORD)(m->esi + 0x9ef928u);	/* 4705d7: lea ecx, [esi + 0x9ef928] */
	M32((DWORD)(m->esi + 0x9ef934u)) = 0x3f800000u;	/* 4705dd: mov dword ptr [esi + 0x9ef934], 0x3f800000 */
	M32((DWORD)(m->esi + 0xdc0240u)) = m->ebx;	/* 4705e7: mov dword ptr [esi + 0xdc0240], ebx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 4705ed: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->esi + 0x9ef910u));	/* 4705f0: mov edx, dword ptr [esi + 0x9ef910] */
	m->eax = M32((DWORD)(m->esi + 0x9ef914u));	/* 4705f6: mov eax, dword ptr [esi + 0x9ef914] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 4705fc: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esi + 0x9ef918u));	/* 4705fe: mov edx, dword ptr [esi + 0x9ef918] */
	M32((DWORD)(m->esi + 0xdc0a74u)) = m->ebx;	/* 470604: mov dword ptr [esi + 0xdc0a74], ebx */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47060a: mov dword ptr [ecx + 4], eax */
	m->eax = (DWORD)(m->esi + 0xdc0ac4u);	/* 47060d: lea eax, [esi + 0xdc0ac4] */
	m->ebp = (DWORD)(m->esi + 0x308u);	/* 470613: lea ebp, [esi + 0x308] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 470619: mov dword ptr [ecx + 8], edx */
	m->edx = (DWORD)(m->esi + 0xe3cb88u);	/* 47061c: lea edx, [esi + 0xe3cb88] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 470622: push edx */
	m->ecx = (DWORD)(m->esi + 0xdc0d10u);	/* 470623: lea ecx, [esi + 0xdc0d10] */
	{ DWORD v_ = 0xe54c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470629: push 0xe54c0 */
	M32((DWORD)(m->esi + 0xdc0a8cu)) = m->eax;	/* 47062e: mov dword ptr [esi + 0xdc0a8c], eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 470634: push 2 */
	M32((DWORD)(m->esi + 0xdc0cd8u)) = m->ecx;	/* 470636: mov dword ptr [esi + 0xdc0cd8], ecx */
	{ DWORD v_ = 0x190u; m->esp -= 4; M32(m->esp) = v_; }	/* 47063c: push 0x190 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 470641: push ebp */
	m->ecx = (DWORD)(m->esi + 0xe3c93cu);	/* 470642: lea ecx, [esi + 0xe3c93c] */
	m->esp -= 4; M32(m->esp) = 0x47064du; native_call(m, 0x466a60u);	/* 470648: call 0x466a60 */
	m->eax = (DWORD)(m->esi + 0x1301800u);	/* 47064d: lea eax, [esi + 0x1301800] */
	{ DWORD v_ = 0x9c40u; m->esp -= 4; M32(m->esp) = v_; }	/* 470653: push 0x9c40 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470658: push eax */
	{ DWORD v_ = 0x7080u; m->esp -= 4; M32(m->esp) = v_; }	/* 470659: push 0x7080 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47065e: push 2 */
	m->ecx = (DWORD)(m->esi + 0x408u);	/* 470660: lea ecx, [esi + 0x408] */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 470666: push 0x64 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 470668: push ecx */
	m->ecx = (DWORD)(m->esi + 0x13016d0u);	/* 470669: lea ecx, [esi + 0x13016d0] */
	M32((DWORD)(m->esi + 0x13016c8u)) = m->ebx;	/* 47066f: mov dword ptr [esi + 0x13016c8], ebx */
	m->esp -= 4; M32(m->esp) = 0x47067au; native_call(m, 0x46aeb0u);	/* 470675: call 0x46aeb0 */
	M32((DWORD)(m->esi + 0x131ae40u)) = m->ebx;	/* 47067a: mov dword ptr [esi + 0x131ae40], ebx */
	M32((DWORD)(m->esi + 0x13c9b24u)) = m->ebx;	/* 470680: mov dword ptr [esi + 0x13c9b24], ebx */
	M32((DWORD)(m->esi + 0x13c9b28u)) = m->ebx;	/* 470686: mov dword ptr [esi + 0x13c9b28], ebx */
	M32((DWORD)(m->esi + 0x13c9b2cu)) = m->ebx;	/* 47068c: mov dword ptr [esi + 0x13c9b2c], ebx */
	M32((DWORD)(m->esi + 0x13eb000u)) = m->ebx;	/* 470692: mov dword ptr [esi + 0x13eb000], ebx */
	M32((DWORD)(m->esi + 0x140c8bcu)) = m->ebx;	/* 470698: mov dword ptr [esi + 0x140c8bc], ebx */
	M32((DWORD)(m->esi + 0x1447ec0u)) = m->ebx;	/* 47069e: mov dword ptr [esi + 0x1447ec0], ebx */
	M32((DWORD)(m->esi + 0x148646cu)) = m->ebx;	/* 4706a4: mov dword ptr [esi + 0x148646c], ebx */
	M32((DWORD)(m->esi + 0x14d1ab0u)) = m->ebx;	/* 4706aa: mov dword ptr [esi + 0x14d1ab0], ebx */
	M32((DWORD)(m->esi + 0x19e1888u)) = m->ebx;	/* 4706b0: mov dword ptr [esi + 0x19e1888], ebx */
	m->edi = (DWORD)(m->esi + 0x1561ea0u);	/* 4706b6: lea edi, [esi + 0x1561ea0] */
	M32((DWORD)(m->esp + 0x24u)) = 0x10u;	/* 4706bc: mov dword ptr [esp + 0x24], 0x10 */
L_4706c4:
	m->edx = (DWORD)(m->edi + 0x24cu);	/* 4706c4: lea edx, [edi + 0x24c] */
	{ DWORD v_ = 0x7d00u; m->esp -= 4; M32(m->esp) = v_; }	/* 4706ca: push 0x7d00 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4706cf: push edx */
	{ DWORD v_ = 0x7840u; m->esp -= 4; M32(m->esp) = v_; }	/* 4706d0: push 0x7840 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4706d5: push 2 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4706d7: push 8 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4706d9: push ebp */
	m->ecx = m->edi;	/* 4706da: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4706e1u; native_call(m, 0x466a60u);	/* 4706dc: call 0x466a60 */
	m->ecx = M32((DWORD)(m->esp + 0x14cu));	/* 4706e1: mov ecx, dword ptr [esp + 0x14c] */
	m->eax = (DWORD)(m->edi + 0x4332cu);	/* 4706e8: lea eax, [edi + 0x4332c] */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4706ee: push 0x7d0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4706f3: push eax */
	{ DWORD v_ = 0x6f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4706f4: push 0x6f0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4706f9: push 2 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4706fb: push 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4706fd: push ecx */
	m->ecx = (DWORD)(m->edi + 0x431fcu);	/* 4706fe: lea ecx, [edi + 0x431fc] */
	m->esp -= 4; M32(m->esp) = 0x470709u; native_call(m, 0x46aeb0u);	/* 470704: call 0x46aeb0 */
	m->edx = (DWORD)(m->edi + 0x8198u);	/* 470709: lea edx, [edi + 0x8198] */
	{ DWORD v_ = 0x7d00u; m->esp -= 4; M32(m->esp) = v_; }	/* 47070f: push 0x7d00 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 470714: push edx */
	{ DWORD v_ = 0x7840u; m->esp -= 4; M32(m->esp) = v_; }	/* 470715: push 0x7840 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47071a: push 2 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 47071c: push 8 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47071e: push ebp */
	m->ecx = (DWORD)(m->edi + 0x7f4cu);	/* 47071f: lea ecx, [edi + 0x7f4c] */
	m->esp -= 4; M32(m->esp) = 0x47072au; native_call(m, 0x466a60u);	/* 470725: call 0x466a60 */
	m->ecx = M32((DWORD)(m->esp + 0x14cu));	/* 47072a: mov ecx, dword ptr [esp + 0x14c] */
	m->eax = (DWORD)(m->edi + 0x43c2cu);	/* 470731: lea eax, [edi + 0x43c2c] */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470737: push 0x7d0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47073c: push eax */
	{ DWORD v_ = 0x6f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47073d: push 0x6f0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 470742: push 2 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 470744: push 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 470746: push ecx */
	m->ecx = (DWORD)(m->edi + 0x43afcu);	/* 470747: lea ecx, [edi + 0x43afc] */
	m->esp -= 4; M32(m->esp) = 0x470752u; native_call(m, 0x46aeb0u);	/* 47074d: call 0x46aeb0 */
	m->edx = (DWORD)(m->edi + 0x100e4u);	/* 470752: lea edx, [edi + 0x100e4] */
	{ DWORD v_ = 0xfa00u; m->esp -= 4; M32(m->esp) = v_; }	/* 470758: push 0xfa00 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47075d: push edx */
	{ DWORD v_ = 0xf080u; m->esp -= 4; M32(m->esp) = v_; }	/* 47075e: push 0xf080 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 470763: push 2 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 470765: push 0x10 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 470767: push ebp */
	m->ecx = (DWORD)(m->edi + 0xfe98u);	/* 470768: lea ecx, [edi + 0xfe98] */
	m->esp -= 4; M32(m->esp) = 0x470773u; native_call(m, 0x466a60u);	/* 47076e: call 0x466a60 */
	m->ecx = M32((DWORD)(m->esp + 0x14cu));	/* 470773: mov ecx, dword ptr [esp + 0x14c] */
	m->eax = (DWORD)(m->edi + 0x4452cu);	/* 47077a: lea eax, [edi + 0x4452c] */
	{ DWORD v_ = 0xfa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470780: push 0xfa0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470785: push eax */
	{ DWORD v_ = 0xec0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470786: push 0xec0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47078b: push 2 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47078d: push 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47078f: push ecx */
	m->ecx = (DWORD)(m->edi + 0x443fcu);	/* 470790: lea ecx, [edi + 0x443fc] */
	m->esp -= 4; M32(m->esp) = 0x47079bu; native_call(m, 0x46aeb0u);	/* 470796: call 0x46aeb0 */
	m->edx = (DWORD)(m->edi + 0x1fd30u);	/* 47079b: lea edx, [edi + 0x1fd30] */
	{ DWORD v_ = 0xfa00u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707a1: push 0xfa00 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4707a6: push edx */
	{ DWORD v_ = 0xf080u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707a7: push 0xf080 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707ac: push 2 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707ae: push 0x10 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4707b0: push ebp */
	m->ecx = (DWORD)(m->edi + 0x1fae4u);	/* 4707b1: lea ecx, [edi + 0x1fae4] */
	m->esp -= 4; M32(m->esp) = 0x4707bcu; native_call(m, 0x466a60u);	/* 4707b7: call 0x466a60 */
	m->ecx = M32((DWORD)(m->esp + 0x14cu));	/* 4707bc: mov ecx, dword ptr [esp + 0x14c] */
	m->eax = (DWORD)(m->edi + 0x455fcu);	/* 4707c3: lea eax, [edi + 0x455fc] */
	{ DWORD v_ = 0xfa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707c9: push 0xfa0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4707ce: push eax */
	{ DWORD v_ = 0xec0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707cf: push 0xec0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707d4: push 2 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707d6: push 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4707d8: push ecx */
	m->ecx = (DWORD)(m->edi + 0x454ccu);	/* 4707d9: lea ecx, [edi + 0x454cc] */
	m->esp -= 4; M32(m->esp) = 0x4707e4u; native_call(m, 0x46aeb0u);	/* 4707df: call 0x46aeb0 */
	m->edx = (DWORD)(m->edi + 0x2f97cu);	/* 4707e4: lea edx, [edi + 0x2f97c] */
	{ DWORD v_ = 0x13880u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707ea: push 0x13880 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4707ef: push edx */
	{ DWORD v_ = 0x12ca0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707f0: push 0x12ca0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707f5: push 2 */
	{ DWORD v_ = 0x14u; m->esp -= 4; M32(m->esp) = v_; }	/* 4707f7: push 0x14 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4707f9: push ebp */
	m->ecx = (DWORD)(m->edi + 0x2f730u);	/* 4707fa: lea ecx, [edi + 0x2f730] */
	m->esp -= 4; M32(m->esp) = 0x470805u; native_call(m, 0x466a60u);	/* 470800: call 0x466a60 */
	m->ecx = M32((DWORD)(m->esp + 0x14cu));	/* 470805: mov ecx, dword ptr [esp + 0x14c] */
	m->eax = (DWORD)(m->edi + 0x466ccu);	/* 47080c: lea eax, [edi + 0x466cc] */
	{ DWORD v_ = 0xfa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470812: push 0xfa0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470817: push eax */
	{ DWORD v_ = 0xec0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470818: push 0xec0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47081d: push 2 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47081f: push 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 470821: push ecx */
	m->ecx = (DWORD)(m->edi + 0x4659cu);	/* 470822: lea ecx, [edi + 0x4659c] */
	m->esp -= 4; M32(m->esp) = 0x47082du; native_call(m, 0x46aeb0u);	/* 470828: call 0x46aeb0 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47082d: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->edi, b_ = 0x47fd2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 470831: add edi, 0x47fd2 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 470837: dec eax */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 470838: mov dword ptr [esp + 0x24], eax */
	if (!m->zf) goto L_4706c4;	/* 47083c: jne 0x4706c4 */
	m->edx = (DWORD)(m->esi + 0x19e1ad8u);	/* 470842: lea edx, [esi + 0x19e1ad8] */
	{ DWORD v_ = 0x2dc6c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470848: push 0x2dc6c0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47084d: push edx */
	{ DWORD v_ = 0x2c6280u; m->esp -= 4; M32(m->esp) = v_; }	/* 47084e: push 0x2c6280 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 470853: push 2 */
	{ DWORD v_ = 0x258u; m->esp -= 4; M32(m->esp) = v_; }	/* 470855: push 0x258 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47085a: push ebp */
	m->ecx = (DWORD)(m->esi + 0x19e188cu);	/* 47085b: lea ecx, [esi + 0x19e188c] */
	m->esp -= 4; M32(m->esp) = 0x470866u; native_call(m, 0x466a60u);	/* 470861: call 0x466a60 */
	m->ecx = M32((DWORD)(m->esp + 0x14cu));	/* 470866: mov ecx, dword ptr [esp + 0x14c] */
	m->eax = (DWORD)(m->esi + 0x1cbe2c8u);	/* 47086d: lea eax, [esi + 0x1cbe2c8] */
	{ DWORD v_ = 0x186a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470873: push 0x186a0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470878: push eax */
	{ DWORD v_ = 0x15ae0u; m->esp -= 4; M32(m->esp) = v_; }	/* 470879: push 0x15ae0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47087e: push 2 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 470880: push 0x64 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 470882: push ecx */
	m->ecx = (DWORD)(m->esi + 0x1cbe198u);	/* 470883: lea ecx, [esi + 0x1cbe198] */
	m->esp -= 4; M32(m->esp) = 0x47088eu; native_call(m, 0x46aeb0u);	/* 470889: call 0x46aeb0 */
	m->ecx = m->esi;	/* 47088e: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470895u; native_call(m, 0x48b420u);	/* 470890: call 0x48b420 */
	m->ecx = m->esi;	/* 470895: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x47089cu; native_call(m, 0x48ec20u);	/* 470897: call 0x48ec20 */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 47089c: lea edx, [esp + 0x38] */
	{ DWORD v_ = 0x4c73f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4708a0: push 0x4c73f4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708a5: push edx */
	m->esp -= 4; M32(m->esp) = 0x4708abu; native_call(m, 0x49e9ddu);	/* 4708a6: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4708ab: add esp, 8 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4708ae: mov ecx, dword ptr [0xa0e010] */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 4708b4: lea eax, [esp + 0x38] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708b8: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708b9: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708ba: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708bb: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708bc: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708bd: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708be: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4708bf: push eax */
	m->esp -= 4; M32(m->esp) = 0x4708c5u; native_call(m, 0x456be0u);	/* 4708c0: call 0x456be0 */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 4708c5: lea ecx, [esp + 0x38] */
	{ DWORD v_ = 0x4c73d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4708c9: push 0x4c73d8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708ce: push ecx */
	M32((DWORD)(m->esi + 0x20f2f3cu)) = m->eax;	/* 4708cf: mov dword ptr [esi + 0x20f2f3c], eax */
	m->esp -= 4; M32(m->esp) = 0x4708dau; native_call(m, 0x49e9ddu);	/* 4708d5: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4708da: add esp, 8 */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4708dd: mov ecx, dword ptr [0xa0e010] */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 4708e3: lea edx, [esp + 0x38] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708e7: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708e8: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708e9: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708ea: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708eb: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708ec: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708ed: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4708ee: push edx */
	m->esp -= 4; M32(m->esp) = 0x4708f4u; native_call(m, 0x456be0u);	/* 4708ef: call 0x456be0 */
	M32((DWORD)(m->esi + 0x20f2f40u)) = m->eax;	/* 4708f4: mov dword ptr [esi + 0x20f2f40], eax */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 4708fa: lea eax, [esp + 0x38] */
	{ DWORD v_ = 0x4c73bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4708fe: push 0x4c73bc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 470903: push eax */
	m->esp -= 4; M32(m->esp) = 0x470909u; native_call(m, 0x49e9ddu);	/* 470904: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 470909: add esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 47090c: lea ecx, [esp + 0x38] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470910: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470911: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470912: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470913: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470914: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470915: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470916: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 470917: push ecx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 470918: mov ecx, dword ptr [0xa0e010] */
	m->esp -= 4; M32(m->esp) = 0x470923u; native_call(m, 0x456be0u);	/* 47091e: call 0x456be0 */
	M32((DWORD)(m->esi + 0x20f2f44u)) = m->eax;	/* 470923: mov dword ptr [esi + 0x20f2f44], eax */
	m->eax = 0x3f800000u;	/* 470929: mov eax, 0x3f800000 */
	M32((DWORD)(m->esi + 0x20f2f48u)) = m->eax;	/* 47092e: mov dword ptr [esi + 0x20f2f48], eax */
	M32((DWORD)(m->esi + 0x20f2f58u)) = m->ebx;	/* 470934: mov dword ptr [esi + 0x20f2f58], ebx */
	M32((DWORD)(m->esi + 0x20f2f68u)) = m->ebx;	/* 47093a: mov dword ptr [esi + 0x20f2f68], ebx */
	M32((DWORD)(m->esi + 0x20f2f78u)) = m->ebx;	/* 470940: mov dword ptr [esi + 0x20f2f78], ebx */
	M32((DWORD)(m->esi + 0x20f2f4cu)) = m->ebx;	/* 470946: mov dword ptr [esi + 0x20f2f4c], ebx */
	M32((DWORD)(m->esi + 0x20f2f5cu)) = m->eax;	/* 47094c: mov dword ptr [esi + 0x20f2f5c], eax */
	m->edx = (DWORD)(m->esi + 0x20fcfe0u);	/* 470952: lea edx, [esi + 0x20fcfe0] */
	m->ecx = 0x3f8ccccdu;	/* 470958: mov ecx, 0x3f8ccccd */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47095d: push edx */
	M32((DWORD)(m->esi + 0x20f2f6cu)) = m->ebx;	/* 47095e: mov dword ptr [esi + 0x20f2f6c], ebx */
	M32((DWORD)(m->esi + 0x20f2f7cu)) = m->ebx;	/* 470964: mov dword ptr [esi + 0x20f2f7c], ebx */
	M32((DWORD)(m->esi + 0x20f2f50u)) = m->ebx;	/* 47096a: mov dword ptr [esi + 0x20f2f50], ebx */
	M32((DWORD)(m->esi + 0x20f2f60u)) = m->ebx;	/* 470970: mov dword ptr [esi + 0x20f2f60], ebx */
	M32((DWORD)(m->esi + 0x20f2f70u)) = m->eax;	/* 470976: mov dword ptr [esi + 0x20f2f70], eax */
	M32((DWORD)(m->esi + 0x20f2f80u)) = m->ebx;	/* 47097c: mov dword ptr [esi + 0x20f2f80], ebx */
	M32((DWORD)(m->esi + 0x20f2f54u)) = m->ebx;	/* 470982: mov dword ptr [esi + 0x20f2f54], ebx */
	M32((DWORD)(m->esi + 0x20f2f64u)) = m->ebx;	/* 470988: mov dword ptr [esi + 0x20f2f64], ebx */
	M32((DWORD)(m->esi + 0x20f2f74u)) = m->ebx;	/* 47098e: mov dword ptr [esi + 0x20f2f74], ebx */
	M32((DWORD)(m->esi + 0x20f2f84u)) = m->eax;	/* 470994: mov dword ptr [esi + 0x20f2f84], eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47099a: push 1 */
	M32((DWORD)(m->esi + 0x20f2f88u)) = m->ecx;	/* 47099c: mov dword ptr [esi + 0x20f2f88], ecx */
	M32((DWORD)(m->esi + 0x20f2f98u)) = m->ebx;	/* 4709a2: mov dword ptr [esi + 0x20f2f98], ebx */
	M32((DWORD)(m->esi + 0x20f2fa8u)) = m->ebx;	/* 4709a8: mov dword ptr [esi + 0x20f2fa8], ebx */
	M32((DWORD)(m->esi + 0x20f2fb8u)) = m->ebx;	/* 4709ae: mov dword ptr [esi + 0x20f2fb8], ebx */
	M32((DWORD)(m->esi + 0x20f2f8cu)) = m->ebx;	/* 4709b4: mov dword ptr [esi + 0x20f2f8c], ebx */
	M32((DWORD)(m->esi + 0x20f2f9cu)) = m->ecx;	/* 4709ba: mov dword ptr [esi + 0x20f2f9c], ecx */
	M32((DWORD)(m->esi + 0x20f2facu)) = m->ebx;	/* 4709c0: mov dword ptr [esi + 0x20f2fac], ebx */
	M32((DWORD)(m->esi + 0x20f2fbcu)) = m->ebx;	/* 4709c6: mov dword ptr [esi + 0x20f2fbc], ebx */
	M32((DWORD)(m->esi + 0x20f2f90u)) = m->ebx;	/* 4709cc: mov dword ptr [esi + 0x20f2f90], ebx */
	M32((DWORD)(m->esi + 0x20f2fa0u)) = m->ebx;	/* 4709d2: mov dword ptr [esi + 0x20f2fa0], ebx */
	M32((DWORD)(m->esi + 0x20f2fb0u)) = m->ecx;	/* 4709d8: mov dword ptr [esi + 0x20f2fb0], ecx */
	M32((DWORD)(m->esi + 0x20f2fc0u)) = m->ebx;	/* 4709de: mov dword ptr [esi + 0x20f2fc0], ebx */
	M32((DWORD)(m->esi + 0x20f2f94u)) = m->ebx;	/* 4709e4: mov dword ptr [esi + 0x20f2f94], ebx */
	M32((DWORD)(m->esi + 0x20f2fa4u)) = m->ebx;	/* 4709ea: mov dword ptr [esi + 0x20f2fa4], ebx */
	M32((DWORD)(m->esi + 0x20f2fb4u)) = m->ebx;	/* 4709f0: mov dword ptr [esi + 0x20f2fb4], ebx */
	M32((DWORD)(m->esi + 0x20f2fc4u)) = m->eax;	/* 4709f6: mov dword ptr [esi + 0x20f2fc4], eax */
	m->esp -= 4; M32(m->esp) = 0x470a02u; native_call(m, M32(0x4a925cu));	/* 4709fc: call dword ptr [0x4a925c] */
	m->eax = (DWORD)(m->esi + 0x20fcfe4u);	/* 470a02: lea eax, [esi + 0x20fcfe4] */
	m->edx = 0x40u;	/* 470a08: mov edx, 0x40 */
L_470a0d:
	m->ecx = 0x80u;	/* 470a0d: mov ecx, 0x80 */
L_470a12:
	m->edi = M32((DWORD)(0xa1f220u));	/* 470a12: mov edi, dword ptr [0xa1f220] */
	M32((DWORD)(m->eax + 0x0u)) = m->edi;	/* 470a18: mov dword ptr [eax], edi */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 470a1a: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 470a1d: dec ecx */
	if (!m->zf) goto L_470a12;	/* 470a1e: jne 0x470a12 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 470a20: dec edx */
	if (!m->zf) goto L_470a0d;	/* 470a21: jne 0x470a0d */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 470a23: push ebx */
	m->ecx = m->esi;	/* 470a24: mov ecx, esi */
	M32((DWORD)(m->esi + 0x20f3ab4u)) = m->ebx;	/* 470a26: mov dword ptr [esi + 0x20f3ab4], ebx */
	m->esp -= 4; M32(m->esp) = 0x470a31u; native_call(m, 0x4732f0u);	/* 470a2c: call 0x4732f0 */
	m->ecx = m->esi;	/* 470a31: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470a38u; native_call(m, 0x470a70u);	/* 470a33: call 0x470a70 */
	m->ecx = m->esi;	/* 470a38: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x470a3fu; native_call(m, 0x470ad0u);	/* 470a3a: call 0x470ad0 */
	M32((DWORD)(m->esi + 0x4u)) = 0x1u;	/* 470a3f: mov dword ptr [esi + 4], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 470a46: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 470a47: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 470a48: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 470a49: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 470a4a: add esp, 0x128 */
	m->esp += 4 + 36; return;	/* 470a50: ret 0x24 */
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
