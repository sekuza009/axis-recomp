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

static void lift_442050(X86 *m);

/* menu_mainMenu (0x442050), lifted by tools/lift.py */
static void lift_442050(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442050: sub esp, 0x4c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 442053: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 442054: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 442055: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 442056: push edi */
	M32((DWORD)(m->esp + 0x30u)) = 0xffffffffu;	/* 442057: mov dword ptr [esp + 0x30], 0xffffffff */
	M32((DWORD)(m->esp + 0x50u)) = 0xc2200000u;	/* 44205f: mov dword ptr [esp + 0x50], 0xc2200000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 442067: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x42200000u;	/* 44206f: mov dword ptr [esp + 0x58], 0x42200000 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 442077: xor ebp, ebp */
	m->ebx = 0x4deb80u;	/* 442079: mov ebx, 0x4deb80 */
L_44207e:
	m->eax = M32((DWORD)(0x9eeaa8u));	/* 44207e: mov eax, dword ptr [0x9eeaa8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 442083: test eax, eax */
	if (!m->zf) goto L_4420c6;	/* 442085: jne 0x4420c6 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 442087: mov eax, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44208c: sub esp, 0x2c */
	m->ecx = 0xbu;	/* 44208f: mov ecx, 0xb */
	m->esi = m->ebx;	/* 442094: mov esi, ebx */
	m->edi = m->esp;	/* 442096: mov edi, esp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442098: push eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 442099: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44209b: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4420a1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4420a7u; native_call(m, 0x41eea0u);	/* 4420a2: call 0x41eea0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4420a7: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4420aa: cmp eax, 1 */
	if (m->zf) goto L_4420bd;	/* 4420ad: je 0x4420bd */
	{ DWORD a_ = m->ebx, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4420af: add ebx, 0x2c */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 4420b2: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x4dec88u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4420b3: cmp ebx, 0x4dec88 */
	if (m->sf != m->of) goto L_44207e;	/* 4420b9: jl 0x44207e */
	goto L_4420c6;	/* 4420bb: jmp 0x4420c6 */
L_4420bd:
	{ DWORD a_ = m->ebp, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4420bd: cmp ebp, -1 */
	M32((DWORD)(m->esp + 0x30u)) = m->ebp;	/* 4420c0: mov dword ptr [esp + 0x30], ebp */
	if (!m->zf) goto L_4420e7;	/* 4420c4: jne 0x4420e7 */
L_4420c6:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 4420c6: fld dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9dda80u));	/* 4420cc: fadd dword ptr [0x9dda80] */
	M32((DWORD)(0x680398u)) = 0x0u;	/* 4420d2: mov dword ptr [0x680398], 0 */
	MF((DWORD)(0x9dda80u)) = (float)ST(0); FPOP();	/* 4420dc: fstp dword ptr [0x9dda80] */
	goto L_44216d;	/* 4420e2: jmp 0x44216d */
L_4420e7:
	m->eax = M32((DWORD)(0x9eeab4u));	/* 4420e7: mov eax, dword ptr [0x9eeab4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4420ec: test eax, eax */
	if (m->zf) goto L_442122;	/* 4420ee: je 0x442122 */
	M32((DWORD)(0x680398u)) = 0x0u;	/* 4420f0: mov dword ptr [0x680398], 0 */
	M32((DWORD)(0x9dda80u)) = 0x0u;	/* 4420fa: mov dword ptr [0x9dda80], 0 */
	M32((DWORD)(0x9eea8cu)) = 0x0u;	/* 442104: mov dword ptr [0x9eea8c], 0 */
	M32((DWORD)(0x9dd948u)) = 0x3d4ccccdu;	/* 44210e: mov dword ptr [0x9dd948], 0x3d4ccccd */
	M32((DWORD)(m->esp + 0x30u)) = 0xffffffffu;	/* 442118: mov dword ptr [esp + 0x30], 0xffffffff */
	goto L_44216d;	/* 442120: jmp 0x44216d */
L_442122:
	m->eax = M32((DWORD)(0x907b24u));	/* 442122: mov eax, dword ptr [0x907b24] */
	M32((DWORD)(0x680398u)) = 0x1u;	/* 442127: mov dword ptr [0x680398], 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442131: cmp eax, ebp */
	M32((DWORD)(0x9dda80u)) = 0x0u;	/* 442133: mov dword ptr [0x9dda80], 0 */
	M32((DWORD)(0x9eea8cu)) = 0x0u;	/* 44213d: mov dword ptr [0x9eea8c], 0 */
	M32((DWORD)(0x9dd948u)) = 0x3d4ccccdu;	/* 442147: mov dword ptr [0x9dd948], 0x3d4ccccd */
	if (m->zf) goto L_44216d;	/* 442151: je 0x44216d */
	M32((DWORD)(0x907b24u)) = m->ebp;	/* 442153: mov dword ptr [0x907b24], ebp */
	M32((DWORD)(0x680cccu)) = 0x42200000u;	/* 442159: mov dword ptr [0x680ccc], 0x42200000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 442163: mov dword ptr [0x4df454], 0xbf800000 */
L_44216d:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44216d: push 1 */
	m->esp -= 4; M32(m->esp) = 0x442174u; native_call(m, 0x41ef90u);	/* 44216f: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442174: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 442177: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x442182u; native_call(m, M32(0x4a9224u));	/* 44217c: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9eeaa8u));	/* 442182: mov eax, dword ptr [0x9eeaa8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 442187: test eax, eax */
	if (m->zf) goto L_4421e9;	/* 442189: je 0x4421e9 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9eea90u)));	/* 44218b: fld dword ptr [0x9eea90] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9498u));	/* 442191: fadd dword ptr [0x4a9498] */
	m->eax = M32((DWORD)(0x9eeab0u));	/* 442197: mov eax, dword ptr [0x9eeab0] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44219c: inc eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44219d: fmul dword ptr [0x4b071c] */
	M32((DWORD)(0x9eeab0u)) = m->eax;	/* 4421a3: mov dword ptr [0x9eeab0], eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 4421a8: fmul dword ptr [0x4a93ec] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9eea90u)));	/* 4421ae: fld dword ptr [0x9eea90] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a95d0u)); FPOP();	/* 4421b4: fcomp dword ptr [0x4a95d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4421ba: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4421bc: test ah, 0x41 */
	if (m->zf) goto L_4421d9;	/* 4421bf: je 0x4421d9 */
	ST(0) = ST(0); FPOP();	/* 4421c1: fstp st(0) */
	M32((DWORD)(0x9eeaa8u)) = 0x0u;	/* 4421c3: mov dword ptr [0x9eeaa8], 0 */
	M32((DWORD)(0x9eea90u)) = 0xc4098000u;	/* 4421cd: mov dword ptr [0x9eea90], 0xc4098000 */
	goto L_4421e9;	/* 4421d7: jmp 0x4421e9 */
L_4421d9:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9eea90u)));	/* 4421d9: fld dword ptr [0x9eea90] */
	ST(0) = ST(0) - ST(1);	/* 4421df: fsub st(1) */
	MF((DWORD)(0x9eea90u)) = (float)ST(0); FPOP();	/* 4421e1: fstp dword ptr [0x9eea90] */
	ST(0) = ST(0); FPOP();	/* 4421e7: fstp st(0) */
L_4421e9:
	m->ebx = M32((DWORD)(0x4a921cu));	/* 4421e9: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4421ef: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 4421f5: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 4421fb: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 442201: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 442203: mov dword ptr [esp + 0x1c], eax */
	goto L_44220d;	/* 442207: jmp 0x44220d */
L_442209:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 442209: mov eax, dword ptr [esp + 0x1c] */
L_44220d:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44220d: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 442210: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3f000000u;	/* 442218: mov dword ptr [esp + 0x34], 0x3f000000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x0u;	/* 442220: mov dword ptr [esp + 0x44], 0 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3e800000u;	/* 442228: mov dword ptr [esp + 0x48], 0x3e800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f000000u;	/* 442230: mov dword ptr [esp + 0x3c], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_442262;	/* 442238: jle 0x442262 */
	M32((DWORD)(m->esp + 0x28u)) = 0x3f000000u;	/* 44223a: mov dword ptr [esp + 0x28], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 442242: mov dword ptr [esp + 0x34], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3ef00000u;	/* 44224a: mov dword ptr [esp + 0x44], 0x3ef00000 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3f200000u;	/* 442252: mov dword ptr [esp + 0x48], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f800000u;	/* 44225a: mov dword ptr [esp + 0x3c], 0x3f800000 */
L_442262:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442262: cmp eax, 2 */
	if (m->sf == m->of) goto L_442297;	/* 442265: jge 0x442297 */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 442267: mov eax, dword ptr [0x4e0cd0] */
	m->edx = m->eax;	/* 44226c: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44226e: and edx, 0x800001ff */
	if (!m->sf) goto L_44227e;	/* 442274: jns 0x44227e */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 442276: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 442277: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44227d: inc edx */
L_44227e:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44227e: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 44227f: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 442285: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 442286: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44228c: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44228e: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 442291: mov ecx, dword ptr [ecx + eax*4 + 4] */
	goto L_4422d0;	/* 442295: jmp 0x4422d0 */
L_442297:
	m->edx = (DWORD)(m->eax*4 + 0x0u);	/* 442297: lea edx, [eax*4] */
	m->eax = 0x76d484u;	/* 44229e: mov eax, 0x76d484 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4422a3: sub eax, edx */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 4422a5: mov eax, dword ptr [eax] */
	m->ecx = m->eax;	/* 4422a7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4422a9: and ecx, 0x800001ff */
	if (!m->sf) goto L_4422b9;	/* 4422af: jns 0x4422b9 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4422b1: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4422b2: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4422b8: inc ecx */
L_4422b9:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4422b9: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4422ba: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4422c0: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4422c1: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4422c3: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4422c9: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4422cc: mov ecx, dword ptr [edx + eax*4 + 4] */
L_4422d0:
	m->esp -= 4; M32(m->esp) = 0x4422d5u; native_call(m, 0x4566c0u);	/* 4422d0: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 4422d5: mov dword ptr [esp + 0x18], 0 */
L_4422dd:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4422dd: mov eax, dword ptr [esp + 0x18] */
	m->ecx = 0x3u;	/* 4422e1: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4422e6: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4422e7: idiv ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 4422e9: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x4422f2u; native_call(m, 0x41f050u);	/* 4422ed: call 0x41f050 */
	m->edx = M32((DWORD)(0x9eea90u));	/* 4422f2: mov edx, dword ptr [0x9eea90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4422f8: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4422f9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4422fb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x442303u; native_call(m, M32(0x4a9214u));	/* 4422fd: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442303: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_442315;	/* 442308: jge 0x442315 */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 44230a: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + m->eax*4 + 0x50u));	/* 44230e: mov ecx, dword ptr [esp + eax*4 + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442312: push ecx */
	goto L_442323;	/* 442313: jmp 0x442323 */
L_442315:
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 442315: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442319: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->edx*4 + 0x54u)));	/* 44231a: fld dword ptr [esp + edx*4 + 0x54] */
	ST(0) = -ST(0);	/* 44231e: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 442320: fstp dword ptr [esp] */
L_442323:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442323: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442325: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44232cu; native_call(m, 0x41ef20u);	/* 442327: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 44232c: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442330: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442333: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_442506;	/* 442336: ja 0x442506 */
	switch (m->eax) { case 0: goto L_442343; case 1: goto L_442373; case 2: goto L_442392; case 3: goto L_4423c0; default: abort(); }	/* 44233c: jmp dword ptr [eax*4 + 0x442cf4] */
L_442343:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 442343: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 442349: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44234f: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 442350: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 442356: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442359: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44235e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442363: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44236eu; native_call(m, M32(0x4a9228u));	/* 442368: call dword ptr [0x4a9228] */
	goto L_4427e0;	/* 44236e: jmp 0x4427e0 */
L_442373:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 442373: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442378: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44237d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442382: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44238du; native_call(m, M32(0x4a9228u));	/* 442387: call dword ptr [0x4a9228] */
	goto L_44250f;	/* 44238d: jmp 0x44250f */
L_442392:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 442392: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 442396: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44239a: cmp ecx, eax */
	if (!m->zf) goto L_4423b6;	/* 44239c: jne 0x4423b6 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 44239e: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9428u));	/* 4423a4: fmul dword ptr [0x4a9428] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4423aa: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4423ab: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4423b1: fstp dword ptr [esp] */
	goto L_4423e9;	/* 4423b4: jmp 0x4423e9 */
L_4423b6:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4423b6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4423b8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4423ba: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4423bc: push 0 */
	goto L_4423f8;	/* 4423be: jmp 0x4423f8 */
L_4423c0:
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4423c0: mov ecx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4423c4: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4423c8: cmp eax, ecx */
	if (!m->zf) goto L_4423e4;	/* 4423ca: jne 0x4423e4 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 4423cc: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4423d2: fmul dword ptr [0x4a9420] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4423d8: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4423d9: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4423df: fstp dword ptr [esp] */
	goto L_4423e9;	/* 4423e2: jmp 0x4423e9 */
L_4423e4:
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 4423e4: push 0x3f19999a */
L_4423e9:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4423e9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4423ee: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4423f3: push 0x3f800000 */
L_4423f8:
	m->esp -= 4; M32(m->esp) = 0x4423feu; native_call(m, M32(0x4a9228u));	/* 4423f8: call dword ptr [0x4a9228] */
L_4423fe:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4423fe: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 442402: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442404: cmp eax, 3 */
	if (m->sf == m->of) goto L_442961;	/* 442407: jge 0x442961 */
	m->esp -= 4; M32(m->esp) = 0x44240fu; native_call(m, m->ebx);	/* 44240d: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 44240f: fild dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 442413: fst dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 442417: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 44241d: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 442421: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442425: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442426: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44242au; native_call(m, m->esi);	/* 442428: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 44242a: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 44242e: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 442434: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 442438: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44243e: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 442442: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 442446: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44244c: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 442450: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442454: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 442455: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 442459: fild dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 44245d: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442461: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 442462: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 442468: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 44246e: fstp dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 442472: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442476: push eax */
	m->esp -= 4; M32(m->esp) = 0x442479u; native_call(m, m->edi);	/* 442477: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 442479: mov ecx, dword ptr [esp + 0x3c] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 44247d: mov edx, dword ptr [esp + 0x20] */
	m->eax = m->ecx;	/* 442481: mov eax, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442483: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442484: push eax */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 442485: mov dword ptr [esp + 0x48], ecx */
	m->esp -= 4; M32(m->esp) = 0x44248bu; native_call(m, m->esi);	/* 442489: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 44248b: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 44248f: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 442495: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 442499: mov eax, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 44249d: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4424a1: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4424a5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4424a6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4424a7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4424aau; native_call(m, m->edi);	/* 4424a8: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4424aa: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4424ae: fadd dword ptr [0x4a9424] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 4424b4: mov edx, dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 4424b8: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4424be: fstp dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4424c2: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4424c6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4424c7: push edx */
	m->esp -= 4; M32(m->esp) = 0x4424cau; native_call(m, m->esi);	/* 4424c8: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4424ca: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4424ce: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4424d4: mov eax, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 4424d8: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4424dc: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4424dd: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4424e1: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4424e5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4424e6: push edx */
	m->esp -= 4; M32(m->esp) = 0x4424e9u; native_call(m, m->edi);	/* 4424e7: call edi */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 4424e9: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4424ed: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4424ee: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4424f2u; native_call(m, m->esi);	/* 4424f0: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4424f2: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4424f6: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4424fa: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4424fe: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4424ff: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442500: push eax */
	goto L_442a5d;	/* 442501: jmp 0x442a5d */
L_442506:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442506: cmp eax, 1 */
	if (!m->zf) goto L_4427d8;	/* 442509: jne 0x4427d8 */
L_44250f:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 44250f: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 442513: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442515: cmp eax, 3 */
	if (m->sf == m->of) goto L_442687;	/* 442518: jge 0x442687 */
	m->esp -= 4; M32(m->esp) = 0x442520u; native_call(m, m->ebx);	/* 44251e: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442520: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442522: push 0 */
	m->esp -= 4; M32(m->esp) = 0x442526u; native_call(m, m->esi);	/* 442524: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442526: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 44252c: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442532: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 442533: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 442539: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44253c: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 442541: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x442548u; native_call(m, m->edi);	/* 442546: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442548: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 44254e: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442554: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442556: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 442557: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44255d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x442562u; native_call(m, m->esi);	/* 442560: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442562: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442567: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44256c: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x442573u; native_call(m, m->edi);	/* 442571: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442573: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 442579: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44257f: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442584: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 442585: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44258b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x442590u; native_call(m, m->esi);	/* 44258e: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442590: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442595: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44259a: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4425a1u; native_call(m, m->edi);	/* 44259f: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425a1: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425a6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4425aau; native_call(m, m->esi);	/* 4425a8: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4425aa: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4425b0: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4425b6: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4425b7: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4425bd: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425c0: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425c5: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4425ccu; native_call(m, m->edi);	/* 4425ca: call edi */
	m->esp -= 4; M32(m->esp) = 0x4425ceu; native_call(m, m->ebp);	/* 4425cc: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425ce: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4425d2u; native_call(m, m->ebx);	/* 4425d0: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4425d2: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4425d8: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425de: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4425e0: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4425e1: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4425e7: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4425ecu; native_call(m, m->esi);	/* 4425ea: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425ec: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425f1: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425f6: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4425fdu; native_call(m, m->edi);	/* 4425fb: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425fd: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4425ff: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x442606u; native_call(m, m->esi);	/* 442604: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442606: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 44260c: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442612: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 442613: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 442619: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44261c: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 442621: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x442628u; native_call(m, m->edi);	/* 442626: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442628: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44262d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x442634u; native_call(m, m->esi);	/* 442632: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442634: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 44263a: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442640: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 442641: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 442647: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44264a: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44264f: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x442656u; native_call(m, m->edi);	/* 442654: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442656: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 44265c: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442662: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442667: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 442668: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44266e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x442673u; native_call(m, m->esi);	/* 442671: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442673: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442678: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44267d: push 0xc1ef3333 */
	goto L_442a5d;	/* 442682: jmp 0x442a5d */
L_442687:
	m->esp -= 4; M32(m->esp) = 0x442689u; native_call(m, m->ebx);	/* 442687: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442689: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 44268f: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442695: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442697: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 442698: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x44269du; native_call(m, m->esi);	/* 44269b: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44269d: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426a2: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426a7: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4426aeu; native_call(m, m->edi);	/* 4426ac: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426ae: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426b0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4426b7u; native_call(m, m->esi);	/* 4426b5: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4426b7: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4426bd: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4426c3: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4426c4: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4426ca: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426cd: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426d2: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4426d9u; native_call(m, m->edi);	/* 4426d7: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426d9: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426de: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4426e5u; native_call(m, m->esi);	/* 4426e3: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4426e5: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4426eb: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4426f1: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4426f2: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4426f8: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4426fb: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 442700: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x442707u; native_call(m, m->edi);	/* 442705: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442707: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 44270d: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442713: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442718: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 442719: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x44271eu; native_call(m, m->esi);	/* 44271c: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44271e: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442723: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 442728: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x44272fu; native_call(m, m->edi);	/* 44272d: call edi */
	m->esp -= 4; M32(m->esp) = 0x442731u; native_call(m, m->ebp);	/* 44272f: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 442731: push 7 */
	m->esp -= 4; M32(m->esp) = 0x442735u; native_call(m, m->ebx);	/* 442733: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442735: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442737: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44273bu; native_call(m, m->esi);	/* 442739: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 44273b: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 442741: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442747: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 442748: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44274e: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442751: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 442756: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x44275du; native_call(m, m->edi);	/* 44275b: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 44275d: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 442763: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442769: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44276b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44276c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x442771u; native_call(m, m->esi);	/* 44276f: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442771: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442776: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 44277b: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x442782u; native_call(m, m->edi);	/* 442780: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 442782: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 442788: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44278e: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442793: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 442794: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x442799u; native_call(m, m->esi);	/* 442797: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442799: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44279e: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4427a3: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4427aau; native_call(m, m->edi);	/* 4427a8: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4427aa: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4427af: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4427b3u; native_call(m, m->esi);	/* 4427b1: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4427b3: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4427b9: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4427bf: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4427c0: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4427c6: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4427c9: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4427ce: push 0x41ef3333 */
	goto L_442a5d;	/* 4427d3: jmp 0x442a5d */
L_4427d8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4427d8: test eax, eax */
	if (!m->zf) goto L_4423fe;	/* 4427da: jne 0x4423fe */
L_4427e0:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4427e0: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4427e4: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4427e6: cmp eax, 3 */
	if (m->sf == m->of) goto L_4428a8;	/* 4427e9: jge 0x4428a8 */
	m->esp -= 4; M32(m->esp) = 0x4427f1u; native_call(m, m->ebx);	/* 4427ef: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4427f1: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4427f6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4427fau; native_call(m, m->esi);	/* 4427f8: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4427fa: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4427fe: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 442804: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 442808: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44280e: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 442812: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 442816: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44281c: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 442820: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442824: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 442825: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 442829: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44282d: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44282e: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x442835u; native_call(m, m->edi);	/* 442833: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442835: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44283a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x442841u; native_call(m, m->esi);	/* 44283f: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 442841: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 442845: fsub dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 44284b: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 44284f: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 442853: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442857: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442858: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442859: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x442860u; native_call(m, m->edi);	/* 44285e: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442860: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442865: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44286cu; native_call(m, m->esi);	/* 44286a: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 44286c: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 442870: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 442876: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44287a: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 44287b: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 44287f: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442883: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442884: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x44288bu; native_call(m, m->edi);	/* 442889: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44288b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442890: push 0 */
	m->esp -= 4; M32(m->esp) = 0x442894u; native_call(m, m->esi);	/* 442892: call esi */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 442894: mov edx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 442898: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44289c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44289d: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44289e: push 0xc1f00000 */
	goto L_442a5d;	/* 4428a3: jmp 0x442a5d */
L_4428a8:
	m->esp -= 4; M32(m->esp) = 0x4428aau; native_call(m, m->ebx);	/* 4428a8: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4428aa: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4428af: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4428b6u; native_call(m, m->esi);	/* 4428b4: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4428b6: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4428ba: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4428c0: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 4428c4: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4428ca: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4428ce: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4428d2: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4428d8: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4428dc: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4428e0: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4428e1: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4428e5: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4428e9: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4428ea: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4428f1u; native_call(m, m->edi);	/* 4428ef: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4428f1: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4428f6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4428fau; native_call(m, m->esi);	/* 4428f8: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4428fa: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4428fe: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 442904: mov ecx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 442908: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 44290c: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442910: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442911: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442912: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x442919u; native_call(m, m->edi);	/* 442917: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442919: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44291e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x442922u; native_call(m, m->esi);	/* 442920: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 442922: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 442926: fsub dword ptr [0x4a9418] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 44292c: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442930: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 442931: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 442935: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442939: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44293a: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x442941u; native_call(m, m->edi);	/* 44293f: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442941: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442946: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44294du; native_call(m, m->esi);	/* 44294b: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 44294d: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 442951: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442955: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442956: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442957: push 0x41f00000 */
	goto L_442a5d;	/* 44295c: jmp 0x442a5d */
L_442961:
	m->esp -= 4; M32(m->esp) = 0x442963u; native_call(m, m->ebx);	/* 442961: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 442963: fild dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 442967: mov edx, dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 44296b: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 442971: fst dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 442975: fadd dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 442979: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 44297d: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442981: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442982: push edx */
	m->esp -= 4; M32(m->esp) = 0x442985u; native_call(m, m->esi);	/* 442983: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 442985: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 442989: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 44298f: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 442993: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 442999: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 44299d: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4429a1: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4429a7: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4429ab: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4429af: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4429b0: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 4429b4: fild dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4429b8: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4429bc: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 4429bd: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 4429c3: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4429c9: fstp dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 4429cd: mov edx, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4429d1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4429d4u; native_call(m, m->edi);	/* 4429d2: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4429d4: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 4429d8: fadd dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4429dc: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4429e0: push eax */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4429e1: fstp dword ptr [esp + 0x50] */
	m->ecx = M32((DWORD)(m->esp + 0x50u));	/* 4429e5: mov ecx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4429e9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4429ecu; native_call(m, m->esi);	/* 4429ea: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4429ec: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4429f0: fadd dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4429f6: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4429fa: mov ecx, dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4429fe: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 442a02: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a06: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442a07: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a08: push ecx */
	m->esp -= 4; M32(m->esp) = 0x442a0bu; native_call(m, m->edi);	/* 442a09: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 442a0b: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 442a0f: fadd dword ptr [esp + 0x48] */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 442a13: mov eax, dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 442a17: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 442a1b: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a1f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442a20: push eax */
	m->esp -= 4; M32(m->esp) = 0x442a23u; native_call(m, m->esi);	/* 442a21: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 442a23: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 442a27: fsub dword ptr [0x4a9418] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 442a2d: mov ecx, dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 442a31: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a35: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 442a36: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 442a3a: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a3e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442a3f: push eax */
	m->esp -= 4; M32(m->esp) = 0x442a42u; native_call(m, m->edi);	/* 442a40: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 442a42: mov ecx, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 442a46: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a4a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a4b: push edx */
	m->esp -= 4; M32(m->esp) = 0x442a4eu; native_call(m, m->esi);	/* 442a4c: call esi */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 442a4e: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 442a52: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 442a56: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442a5a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a5b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442a5c: push edx */
L_442a5d:
	m->esp -= 4; M32(m->esp) = 0x442a5fu; native_call(m, m->edi);	/* 442a5d: call edi */
	m->esp -= 4; M32(m->esp) = 0x442a61u; native_call(m, m->ebp);	/* 442a5f: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 442a61: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 442a65: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442a66: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 442a69: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_4422dd;	/* 442a6d: jl 0x4422dd */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 442a73: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 442a77: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442a78: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 442a7b: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_442209;	/* 442a7f: jl 0x442209 */
	m->eax = M32((DWORD)(0x680398u));	/* 442a85: mov eax, dword ptr [0x680398] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 442a8a: test eax, eax */
	if (m->zf) goto L_442af0;	/* 442a8c: je 0x442af0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df454u)));	/* 442a8e: fld dword ptr [0x4df454] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 442a94: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 442a9a: fadd dword ptr [0x680ccc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 442aa0: fst dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 442aa6: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442aac: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442aae: test ah, 0x41 */
	if (m->zf) goto L_442ac9;	/* 442ab1: je 0x442ac9 */
	M32((DWORD)(0x680cccu)) = 0x40000000u;	/* 442ab3: mov dword ptr [0x680ccc], 0x40000000 */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 442abd: mov dword ptr [0x4df454], 0x3f800000 */
	goto L_442af0;	/* 442ac7: jmp 0x442af0 */
L_442ac9:
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 442ac9: fld dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 442acf: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442ad5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442ad7: test ah, 1 */
	if (!m->zf) goto L_442af0;	/* 442ada: jne 0x442af0 */
	M32((DWORD)(0x680cccu)) = 0x42180000u;	/* 442adc: mov dword ptr [0x680ccc], 0x42180000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 442ae6: mov dword ptr [0x4df454], 0xbf800000 */
L_442af0:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 442af0: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 442af6: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 442afc: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 442b02: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 442b08: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442b0e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442b10: test ah, 0x41 */
	if (m->zf) goto L_442b2b;	/* 442b13: je 0x442b2b */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 442b15: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 442b1f: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_442b52;	/* 442b29: jmp 0x442b52 */
L_442b2b:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 442b2b: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 442b31: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442b37: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442b39: test ah, 1 */
	if (!m->zf) goto L_442b52;	/* 442b3c: jne 0x442b52 */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 442b3e: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 442b48: mov dword ptr [0x4df010], 0xbf800000 */
L_442b52:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 442b52: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 442b58: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 442b5e: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 442b64: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 442b6a: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442b70: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442b72: test ah, 1 */
	if (!m->zf) goto L_442b81;	/* 442b75: jne 0x442b81 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 442b77: mov dword ptr [0x4e14fc], 0 */
L_442b81:
	m->esi = M32((DWORD)(m->esp + 0x30u));	/* 442b81: mov esi, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(0x680370u));	/* 442b85: mov eax, dword ptr [0x680370] */
	{ DWORD a_ = m->esi, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442b8a: cmp esi, -1 */
	if (m->zf) goto L_442bde;	/* 442b8d: je 0x442bde */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 442b8f: test eax, eax */
	if (!m->zf) goto L_442ce1;	/* 442b91: jne 0x442ce1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 442b97: push 2 */
	m->esp -= 4; M32(m->esp) = 0x442b9eu; native_call(m, 0x41ef90u);	/* 442b99: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442b9e: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x442ba7u; native_call(m, M32(0x4a9218u));	/* 442ba1: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ba7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442bac: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442bb1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442bb6: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 442bbb: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x442bc5u; native_call(m, 0x41f0e0u);	/* 442bc0: call 0x41f0e0 */
	{ DWORD a_ = m->esi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 442bc5: shl esi, 7 */
	{ DWORD a_ = m->esi, b_ = 0x7501a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 442bc8: add esi, 0x7501a4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 442bce: push esi */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 442bcf: push 0x280 */
	{ DWORD v_ = 0x1bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 442bd4: push 0x1bc */
	goto L_442cd7;	/* 442bd9: jmp 0x442cd7 */
L_442bde:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 442bde: test eax, eax */
	if (!m->zf) goto L_442ce1;	/* 442be0: jne 0x442ce1 */
	m->eax = M32((DWORD)(0x9eeab4u));	/* 442be6: mov eax, dword ptr [0x9eeab4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 442beb: test eax, eax */
	if (!m->zf) goto L_442ce1;	/* 442bed: jne 0x442ce1 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9dda80u)));	/* 442bf3: fld dword ptr [0x9dda80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a95ccu)); FPOP();	/* 442bf9: fcomp dword ptr [0x4a95cc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442bff: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442c01: test ah, 0x41 */
	if (!m->zf) goto L_442ce1;	/* 442c04: jne 0x442ce1 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9dd948u)));	/* 442c0a: fld dword ptr [0x9dd948] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 442c10: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9eea8cu));	/* 442c16: fadd dword ptr [0x9eea8c] */
	MF((DWORD)(0x9eea8cu)) = (float)ST(0);	/* 442c1c: fst dword ptr [0x9eea8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9534u)); FPOP();	/* 442c22: fcomp dword ptr [0x4a9534] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442c28: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442c2a: test ah, 0x41 */
	if (!m->zf) goto L_442c45;	/* 442c2d: jne 0x442c45 */
	M32((DWORD)(0x9eea8cu)) = 0x3f800000u;	/* 442c2f: mov dword ptr [0x9eea8c], 0x3f800000 */
	M32((DWORD)(0x9dd948u)) = 0xbd4ccccdu;	/* 442c39: mov dword ptr [0x9dd948], 0xbd4ccccd */
	goto L_442c76;	/* 442c43: jmp 0x442c76 */
L_442c45:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9eea8cu)));	/* 442c45: fld dword ptr [0x9eea8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 442c4b: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442c51: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442c53: test ah, 1 */
	if (m->zf) goto L_442c76;	/* 442c56: je 0x442c76 */
	M32((DWORD)(0x9eea8cu)) = 0x0u;	/* 442c58: mov dword ptr [0x9eea8c], 0 */
	M32((DWORD)(0x9dd948u)) = 0x3d4ccccdu;	/* 442c62: mov dword ptr [0x9dd948], 0x3d4ccccd */
	M32((DWORD)(0x9dda80u)) = 0x0u;	/* 442c6c: mov dword ptr [0x9dda80], 0 */
L_442c76:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 442c76: push 2 */
	m->esp -= 4; M32(m->esp) = 0x442c7du; native_call(m, 0x41ef90u);	/* 442c78: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442c7d: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x442c86u; native_call(m, M32(0x4a9218u));	/* 442c80: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9eea8cu)));	/* 442c86: fld dword ptr [0x9eea8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 442c8c: fcomp dword ptr [0x4a9424] */
	m->eax = M32((DWORD)(0x9eea8cu));	/* 442c92: mov eax, dword ptr [0x9eea8c] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 442c97: mov dword ptr [esp + 0x4c], eax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 442c9b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 442c9d: test ah, 0x41 */
	if (!m->zf) goto L_442caa;	/* 442ca0: jne 0x442caa */
	M32((DWORD)(m->esp + 0x4cu)) = 0x3f800000u;	/* 442ca2: mov dword ptr [esp + 0x4c], 0x3f800000 */
L_442caa:
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 442caa: mov ecx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442cae: push ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442caf: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442cb4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442cb9: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 442cbe: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x442cc8u; native_call(m, 0x41f0e0u);	/* 442cc3: call 0x41f0e0 */
	{ DWORD v_ = 0x4b2a98u; m->esp -= 4; M32(m->esp) = v_; }	/* 442cc8: push 0x4b2a98 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ccd: push 0x280 */
	{ DWORD v_ = 0x1d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442cd2: push 0x1d0 */
L_442cd7:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442cd7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x442cdeu; native_call(m, 0x4029d0u);	/* 442cd9: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442cde: add esp, 0x24 */
L_442ce1:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ce1: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x442cecu; native_call(m, M32(0x4a922cu));	/* 442ce6: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 442cec: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 442ced: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 442cee: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 442cef: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442cf0: add esp, 0x4c */
	m->esp += 4 + 0; return;	/* 442cf3: ret  */
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
