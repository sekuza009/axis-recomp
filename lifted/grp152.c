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

static void lift_487f00(X86 *m);

/* replay_frame (0x487f00), lifted by tools/lift.py */
static void lift_487f00(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x27cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487f00: sub esp, 0x27c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 487f06: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487f07: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487f08: push esi */
	m->esi = m->ecx;	/* 487f09: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 487f0b: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 487f0c: xor edi, edi */
	m->eax = M32((DWORD)(m->esi + 0x233cc28u));	/* 487f0e: mov eax, dword ptr [esi + 0x233cc28] */
	m->ebx = 0xau;	/* 487f14: mov ebx, 0xa */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487f19: cmp eax, edi */
	m->ebp = 0x1u;	/* 487f1b: mov ebp, 1 */
	if (!m->zf) goto L_48807c;	/* 487f20: jne 0x48807c */
	m->eax = (DWORD)(m->esi + 0x22ee228u);	/* 487f26: lea eax, [esi + 0x22ee228] */
	m->ecx = (DWORD)(m->esi + 0x233ca04u);	/* 487f2c: lea ecx, [esi + 0x233ca04] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 487f32: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 487f34: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 487f36: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 487f39: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 487f3c: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 487f3f: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->esi + 0x22ee234u));	/* 487f42: mov ecx, dword ptr [esi + 0x22ee234] */
	M32((DWORD)(m->esi + 0x233ca28u)) = m->ecx;	/* 487f48: mov dword ptr [esi + 0x233ca28], ecx */
	m->edx = M32((DWORD)(m->esi + 0x22ee238u));	/* 487f4e: mov edx, dword ptr [esi + 0x22ee238] */
	M32((DWORD)(m->esi + 0x233ca2cu)) = m->edx;	/* 487f54: mov dword ptr [esi + 0x233ca2c], edx */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->edi;	/* 487f5a: mov dword ptr [esi + 0x233cc10], edi */
L_487f60:
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 487f60: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca30u));	/* 487f66: mov ecx, dword ptr [esi + eax*4 + 0x233ca30] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb20u)) = m->ecx;	/* 487f6d: mov dword ptr [esi + eax*4 + 0x233cb20], ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 487f74: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca58u));	/* 487f7a: mov edx, dword ptr [esi + eax*4 + 0x233ca58] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb48u)) = m->edx;	/* 487f81: mov dword ptr [esi + eax*4 + 0x233cb48], edx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 487f88: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca80u));	/* 487f8e: mov ecx, dword ptr [esi + eax*4 + 0x233ca80] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb70u)) = m->ecx;	/* 487f95: mov dword ptr [esi + eax*4 + 0x233cb70], ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 487f9c: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233caa8u));	/* 487fa2: mov edx, dword ptr [esi + eax*4 + 0x233caa8] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb98u)) = m->edx;	/* 487fa9: mov dword ptr [esi + eax*4 + 0x233cb98], edx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 487fb0: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233cad0u));	/* 487fb6: mov ecx, dword ptr [esi + eax*4 + 0x233cad0] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cbc0u)) = m->ecx;	/* 487fbd: mov dword ptr [esi + eax*4 + 0x233cbc0], ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 487fc4: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233caf8u));	/* 487fca: mov edx, dword ptr [esi + eax*4 + 0x233caf8] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cbe8u)) = m->edx;	/* 487fd1: mov dword ptr [esi + eax*4 + 0x233cbe8], edx */
	m->ecx = M32((DWORD)(m->esi + 0x233cc10u));	/* 487fd8: mov ecx, dword ptr [esi + 0x233cc10] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 487fde: inc ecx */
	m->eax = m->ecx;	/* 487fdf: mov eax, ecx */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->ecx;	/* 487fe1: mov dword ptr [esi + 0x233cc10], ecx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487fe7: cmp eax, ebx */
	if (m->sf != m->of) goto L_487f60;	/* 487fe9: jl 0x487f60 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 487fef: push -1 */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 487ff1: lea ecx, [esi + 0x1f36c8] */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->ebp;	/* 487ff7: mov dword ptr [esi + 0x233cc10], ebp */
	m->esp -= 4; M32(m->esp) = 0x488002u; native_call(m, 0x45dfb0u);	/* 487ffd: call 0x45dfb0 */
	M32((DWORD)(m->esi + 0x2340c64u)) = 0xffffffffu;	/* 488002: mov dword ptr [esi + 0x2340c64], 0xffffffff */
	M32((DWORD)(m->esi + 0x2340c68u)) = m->edi;	/* 48800c: mov dword ptr [esi + 0x2340c68], edi */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 488012: mov dword ptr [esi + 0x2340c6c], edi */
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 488018: lea ecx, [esi + 0xc] */
	M32((DWORD)(m->esi + 0x2340c70u)) = m->edi;	/* 48801b: mov dword ptr [esi + 0x2340c70], edi */
	m->esp -= 4; M32(m->esp) = 0x488026u; { long double r_ = native_call_fp(m, 0x487490u); FPUSH(r_); }	/* 488021: call 0x487490 */
	ST(0) = ST(0); FPOP();	/* 488026: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x48802du; native_call(m, 0x4685c0u);	/* 488028: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48802d: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48802e: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 488030: sar eax, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488032: push eax */
	m->esp -= 4; M32(m->esp) = 0x488038u; native_call(m, 0x4685b0u);	/* 488033: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 488038: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 488039: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48803b: sar eax, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48803d: push eax */
	m->esp -= 4; M32(m->esp) = 0x488043u; native_call(m, 0x487c80u);	/* 48803e: call 0x487c80 */
	M32((DWORD)(m->esi + 0x233cc38u)) = m->edi;	/* 488043: mov dword ptr [esi + 0x233cc38], edi */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->edi;	/* 488049: mov dword ptr [esi + 0x233cc3c], edi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48804f: add esp, 8 */
	M32((DWORD)(m->esi + 0x2342425u)) = m->edi;	/* 488052: mov dword ptr [esi + 0x2342425], edi */
	M32((DWORD)(m->esi + 0x233cc30u)) = m->edi;	/* 488058: mov dword ptr [esi + 0x233cc30], edi */
	M32((DWORD)(m->esi + 0x233cc34u)) = m->edi;	/* 48805e: mov dword ptr [esi + 0x233cc34], edi */
	M32((DWORD)(m->esi + 0x2340d29u)) = m->edi;	/* 488064: mov dword ptr [esi + 0x2340d29], edi */
	{ DWORD v_ = 0x42700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48806a: push 0x42700000 */
	m->ecx = m->esi;	/* 48806f: mov ecx, esi */
	M32((DWORD)(m->esi + 0x2340d2du)) = m->edi;	/* 488071: mov dword ptr [esi + 0x2340d2d], edi */
	m->esp -= 4; M32(m->esp) = 0x48807cu; native_call(m, 0x4629c0u);	/* 488077: call 0x4629c0 */
L_48807c:
	m->ecx = m->esi;	/* 48807c: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x488083u; { long double r_ = native_call_fp(m, 0x461210u); FPUSH(r_); }	/* 48807e: call 0x461210 */
	ST(0) = ST(0); FPOP();	/* 488083: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc34u)));	/* 488085: fld dword ptr [esi + 0x233cc34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 48808b: fadd dword ptr [esi + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 48808e: fcom dword ptr [0x4a9424] */
	MF((DWORD)(m->esi + 0x233cc34u)) = (float)ST(0);	/* 488094: fst dword ptr [esi + 0x233cc34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48809a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48809c: test ah, 0x41 */
	if (!m->zf) goto L_4880cd;	/* 48809f: jne 0x4880cd */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4880a1: call 0x49ec14 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x233cc30u)), b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->esi + 0x233cc30u)) = r_; }	/* 4880a6: add dword ptr [esi + 0x233cc30], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc34u)));	/* 4880ac: fld dword ptr [esi + 0x233cc34] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4880b2: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4880b7: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4880bb: fild dword ptr [esp + 0x28] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esi + 0x233cc34u));	/* 4880bf: fsubr dword ptr [esi + 0x233cc34] */
	MF((DWORD)(m->esi + 0x233cc34u)) = (float)ST(0); FPOP();	/* 4880c5: fstp dword ptr [esi + 0x233cc34] */
	goto L_4880cf;	/* 4880cb: jmp 0x4880cf */
L_4880cd:
	ST(0) = ST(0); FPOP();	/* 4880cd: fstp st(0) */
L_4880cf:
	m->ecx = m->esi;	/* 4880cf: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4880d6u; native_call(m, 0x461f10u);	/* 4880d1: call 0x461f10 */
	m->eax = M32((DWORD)(0x4def30u));	/* 4880d6: mov eax, dword ptr [0x4def30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4880db: push eax */
	m->esp -= 4; M32(m->esp) = 0x4880e1u; native_call(m, 0x401590u);	/* 4880dc: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4880e1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4880e4: test eax, eax */
	if (!m->zf) goto L_4880fb;	/* 4880e6: jne 0x4880fb */
	m->ecx = M32((DWORD)(0x4def34u));	/* 4880e8: mov ecx, dword ptr [0x4def34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4880ee: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4880f4u; native_call(m, 0x401590u);	/* 4880ef: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4880f4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4880f7: test eax, eax */
	if (m->zf) goto L_488101;	/* 4880f9: je 0x488101 */
L_4880fb:
	M32((DWORD)(m->esi + 0x234325fu)) = m->ebp;	/* 4880fb: mov dword ptr [esi + 0x234325f], ebp */
L_488101:
	m->edx = M32((DWORD)(0x4def10u));	/* 488101: mov edx, dword ptr [0x4def10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488107: push edx */
	m->esp -= 4; M32(m->esp) = 0x48810du; native_call(m, 0x401590u);	/* 488108: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48810d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488110: test eax, eax */
	if (!m->zf) goto L_488126;	/* 488112: jne 0x488126 */
	m->eax = M32((DWORD)(0x4def14u));	/* 488114: mov eax, dword ptr [0x4def14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488119: push eax */
	m->esp -= 4; M32(m->esp) = 0x48811fu; native_call(m, 0x401590u);	/* 48811a: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48811f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488122: test eax, eax */
	if (m->zf) goto L_48812c;	/* 488124: je 0x48812c */
L_488126:
	M32((DWORD)(m->esi + 0x234326bu)) = m->ebp;	/* 488126: mov dword ptr [esi + 0x234326b], ebp */
L_48812c:
	m->ecx = M32((DWORD)(0x4def18u));	/* 48812c: mov ecx, dword ptr [0x4def18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488132: push ecx */
	m->esp -= 4; M32(m->esp) = 0x488138u; native_call(m, 0x401590u);	/* 488133: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488138: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48813b: test eax, eax */
	if (!m->zf) goto L_488152;	/* 48813d: jne 0x488152 */
	m->edx = M32((DWORD)(0x4def1cu));	/* 48813f: mov edx, dword ptr [0x4def1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488145: push edx */
	m->esp -= 4; M32(m->esp) = 0x48814bu; native_call(m, 0x401590u);	/* 488146: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48814b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48814e: test eax, eax */
	if (m->zf) goto L_488158;	/* 488150: je 0x488158 */
L_488152:
	M32((DWORD)(m->esi + 0x234326fu)) = m->ebp;	/* 488152: mov dword ptr [esi + 0x234326f], ebp */
L_488158:
	m->eax = M32((DWORD)(0x4def00u));	/* 488158: mov eax, dword ptr [0x4def00] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48815d: push eax */
	m->esp -= 4; M32(m->esp) = 0x488163u; native_call(m, 0x401590u);	/* 48815e: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488163: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488166: test eax, eax */
	if (!m->zf) goto L_48817d;	/* 488168: jne 0x48817d */
	m->ecx = M32((DWORD)(0x4def04u));	/* 48816a: mov ecx, dword ptr [0x4def04] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488170: push ecx */
	m->esp -= 4; M32(m->esp) = 0x488176u; native_call(m, 0x401590u);	/* 488171: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488176: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488179: test eax, eax */
	if (m->zf) goto L_488183;	/* 48817b: je 0x488183 */
L_48817d:
	M32((DWORD)(m->esi + 0x2343263u)) = m->ebp;	/* 48817d: mov dword ptr [esi + 0x2343263], ebp */
L_488183:
	m->edx = M32((DWORD)(0x4def08u));	/* 488183: mov edx, dword ptr [0x4def08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488189: push edx */
	m->esp -= 4; M32(m->esp) = 0x48818fu; native_call(m, 0x401590u);	/* 48818a: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48818f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488192: test eax, eax */
	if (!m->zf) goto L_4881a8;	/* 488194: jne 0x4881a8 */
	m->eax = M32((DWORD)(0x4def0cu));	/* 488196: mov eax, dword ptr [0x4def0c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48819b: push eax */
	m->esp -= 4; M32(m->esp) = 0x4881a1u; native_call(m, 0x401590u);	/* 48819c: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4881a1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4881a4: test eax, eax */
	if (m->zf) goto L_4881ae;	/* 4881a6: je 0x4881ae */
L_4881a8:
	M32((DWORD)(m->esi + 0x2343267u)) = m->ebp;	/* 4881a8: mov dword ptr [esi + 0x2343267], ebp */
L_4881ae:
	m->ecx = M32((DWORD)(0x4def40u));	/* 4881ae: mov ecx, dword ptr [0x4def40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4881b4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4881bau; native_call(m, 0x401590u);	/* 4881b5: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4881ba: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4881bd: test eax, eax */
	if (!m->zf) goto L_4881d4;	/* 4881bf: jne 0x4881d4 */
	m->edx = M32((DWORD)(0x4def44u));	/* 4881c1: mov edx, dword ptr [0x4def44] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4881c7: push edx */
	m->esp -= 4; M32(m->esp) = 0x4881cdu; native_call(m, 0x401590u);	/* 4881c8: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4881cd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4881d0: test eax, eax */
	if (m->zf) goto L_4881da;	/* 4881d2: je 0x4881da */
L_4881d4:
	M32((DWORD)(m->esi + 0x2343273u)) = m->ebp;	/* 4881d4: mov dword ptr [esi + 0x2343273], ebp */
L_4881da:
	m->eax = M32((DWORD)(0x4def48u));	/* 4881da: mov eax, dword ptr [0x4def48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4881df: push eax */
	m->esp -= 4; M32(m->esp) = 0x4881e5u; native_call(m, 0x401590u);	/* 4881e0: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4881e5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4881e8: test eax, eax */
	if (!m->zf) goto L_4881ff;	/* 4881ea: jne 0x4881ff */
	m->ecx = M32((DWORD)(0x4def4cu));	/* 4881ec: mov ecx, dword ptr [0x4def4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4881f2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4881f8u; native_call(m, 0x401590u);	/* 4881f3: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4881f8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4881fb: test eax, eax */
	if (m->zf) goto L_488205;	/* 4881fd: je 0x488205 */
L_4881ff:
	M32((DWORD)(m->esi + 0x2343277u)) = m->ebp;	/* 4881ff: mov dword ptr [esi + 0x2343277], ebp */
L_488205:
	{ DWORD a_ = M32((DWORD)(0x4ded88u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488205: cmp dword ptr [0x4ded88], edi */
	if (m->zf) goto L_488219;	/* 48820b: je 0x488219 */
	M32((DWORD)(m->esi + 0x234331bu)) = m->ebp;	/* 48820d: mov dword ptr [esi + 0x234331b], ebp */
	M32((DWORD)(m->esi + 0x2340c68u)) = m->ebp;	/* 488213: mov dword ptr [esi + 0x2340c68], ebp */
L_488219:
	{ DWORD a_ = M32((DWORD)(0x4ded8cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488219: cmp dword ptr [0x4ded8c], edi */
	if (m->zf) goto L_488233;	/* 48821f: je 0x488233 */
	M32((DWORD)(m->esi + 0x234331fu)) = m->ebp;	/* 488221: mov dword ptr [esi + 0x234331f], ebp */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 488227: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 48822d: mov dword ptr [esi + 0x23432cb], ebp */
L_488233:
	m->edx = M32((DWORD)(0x4dec90u));	/* 488233: mov edx, dword ptr [0x4dec90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488239: push edx */
	m->esp -= 4; M32(m->esp) = 0x48823fu; native_call(m, 0x401600u);	/* 48823a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48823f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488242: test eax, eax */
	if (m->zf) goto L_488258;	/* 488244: je 0x488258 */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->ebp;	/* 488246: mov dword ptr [esi + 0x233cc10], ebp */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 48824c: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 488252: mov dword ptr [esi + 0x23432cb], ebp */
L_488258:
	m->eax = M32((DWORD)(0x4dec8cu));	/* 488258: mov eax, dword ptr [0x4dec8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48825d: push eax */
	m->esp -= 4; M32(m->esp) = 0x488263u; native_call(m, 0x401600u);	/* 48825e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488263: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488266: test eax, eax */
	if (m->zf) goto L_488280;	/* 488268: je 0x488280 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x2u;	/* 48826a: mov dword ptr [esi + 0x233cc10], 2 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 488274: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 48827a: mov dword ptr [esi + 0x23432cb], ebp */
L_488280:
	m->ecx = M32((DWORD)(0x4deb5cu));	/* 488280: mov ecx, dword ptr [0x4deb5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488286: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48828cu; native_call(m, 0x401600u);	/* 488287: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48828c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48828f: test eax, eax */
	if (m->zf) goto L_4882a9;	/* 488291: je 0x4882a9 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x3u;	/* 488293: mov dword ptr [esi + 0x233cc10], 3 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 48829d: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 4882a3: mov dword ptr [esi + 0x23432cb], ebp */
L_4882a9:
	m->edx = M32((DWORD)(0x4deb58u));	/* 4882a9: mov edx, dword ptr [0x4deb58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4882af: push edx */
	m->esp -= 4; M32(m->esp) = 0x4882b5u; native_call(m, 0x401600u);	/* 4882b0: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4882b5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4882b8: test eax, eax */
	if (m->zf) goto L_4882d2;	/* 4882ba: je 0x4882d2 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x4u;	/* 4882bc: mov dword ptr [esi + 0x233cc10], 4 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 4882c6: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 4882cc: mov dword ptr [esi + 0x23432cb], ebp */
L_4882d2:
	m->eax = M32((DWORD)(0x4deb64u));	/* 4882d2: mov eax, dword ptr [0x4deb64] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4882d7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4882ddu; native_call(m, 0x401600u);	/* 4882d8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4882dd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4882e0: test eax, eax */
	if (m->zf) goto L_4882fa;	/* 4882e2: je 0x4882fa */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x5u;	/* 4882e4: mov dword ptr [esi + 0x233cc10], 5 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 4882ee: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 4882f4: mov dword ptr [esi + 0x23432cb], ebp */
L_4882fa:
	m->ecx = M32((DWORD)(0x4deb60u));	/* 4882fa: mov ecx, dword ptr [0x4deb60] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488300: push ecx */
	m->esp -= 4; M32(m->esp) = 0x488306u; native_call(m, 0x401600u);	/* 488301: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488306: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488309: test eax, eax */
	if (m->zf) goto L_488323;	/* 48830b: je 0x488323 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x6u;	/* 48830d: mov dword ptr [esi + 0x233cc10], 6 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 488317: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 48831d: mov dword ptr [esi + 0x23432cb], ebp */
L_488323:
	m->edx = M32((DWORD)(0x4deb6cu));	/* 488323: mov edx, dword ptr [0x4deb6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488329: push edx */
	m->esp -= 4; M32(m->esp) = 0x48832fu; native_call(m, 0x401600u);	/* 48832a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48832f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488332: test eax, eax */
	if (m->zf) goto L_48834c;	/* 488334: je 0x48834c */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x7u;	/* 488336: mov dword ptr [esi + 0x233cc10], 7 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 488340: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 488346: mov dword ptr [esi + 0x23432cb], ebp */
L_48834c:
	m->eax = M32((DWORD)(0x4deb68u));	/* 48834c: mov eax, dword ptr [0x4deb68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488351: push eax */
	m->esp -= 4; M32(m->esp) = 0x488357u; native_call(m, 0x401600u);	/* 488352: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488357: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48835a: test eax, eax */
	if (m->zf) goto L_488374;	/* 48835c: je 0x488374 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x8u;	/* 48835e: mov dword ptr [esi + 0x233cc10], 8 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 488368: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 48836e: mov dword ptr [esi + 0x23432cb], ebp */
L_488374:
	m->ecx = M32((DWORD)(0x4deb70u));	/* 488374: mov ecx, dword ptr [0x4deb70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48837a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x488380u; native_call(m, 0x401600u);	/* 48837b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488380: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488383: test eax, eax */
	if (m->zf) goto L_48839d;	/* 488385: je 0x48839d */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x9u;	/* 488387: mov dword ptr [esi + 0x233cc10], 9 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 488391: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 488397: mov dword ptr [esi + 0x23432cb], ebp */
L_48839d:
	m->edx = M32((DWORD)(0x4deb78u));	/* 48839d: mov edx, dword ptr [0x4deb78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4883a3: push edx */
	m->esp -= 4; M32(m->esp) = 0x4883a9u; native_call(m, 0x401600u);	/* 4883a4: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4883a9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4883ac: test eax, eax */
	if (m->zf) goto L_4883c2;	/* 4883ae: je 0x4883c2 */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->edi;	/* 4883b0: mov dword ptr [esi + 0x233cc10], edi */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->ebp;	/* 4883b6: mov dword ptr [esi + 0x2340c6c], ebp */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 4883bc: mov dword ptr [esi + 0x23432cb], ebp */
L_4883c2:
	m->eax = M32((DWORD)(0x4e0468u));	/* 4883c2: mov eax, dword ptr [0x4e0468] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4883c7: xor edi, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4883c9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4883cfu; native_call(m, 0x401600u);	/* 4883ca: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4883cf: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4883d2: test eax, eax */
	if (m->zf) goto L_4883ee;	/* 4883d4: je 0x4883ee */
	m->ecx = M32((DWORD)(0x67ef24u));	/* 4883d6: mov ecx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4883dc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4883e2u; native_call(m, 0x401600u);	/* 4883dd: call 0x401600 */
	m->edi = m->eax;	/* 4883e2: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4883e4: add esp, 4 */
	{ DWORD a_ = m->edi, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->edi = r_; }	/* 4883e7: neg edi */
	{ DWORD a_ = m->edi, b_ = m->edi, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->edi = r_; }	/* 4883e9: sbb edi, edi */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4883eb: and edi, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 4883ed: inc edi */
L_4883ee:
	m->edx = M32((DWORD)(0x4e0468u));	/* 4883ee: mov edx, dword ptr [0x4e0468] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4883f4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4883fau; native_call(m, 0x401600u);	/* 4883f5: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4883fa: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4883fd: test eax, eax */
	if (m->zf) goto L_48841a;	/* 4883ff: je 0x48841a */
	m->eax = M32((DWORD)(0x67ef24u));	/* 488401: mov eax, dword ptr [0x67ef24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488406: push eax */
	m->esp -= 4; M32(m->esp) = 0x48840cu; native_call(m, 0x401600u);	/* 488407: call 0x401600 */
	m->edi = m->eax;	/* 48840c: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48840e: add esp, 4 */
	{ DWORD a_ = m->edi, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->edi = r_; }	/* 488411: neg edi */
	{ DWORD a_ = m->edi, b_ = m->edi, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->edi = r_; }	/* 488413: sbb edi, edi */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 488415: and edi, ebx */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 488417: add edi, 2 */
L_48841a:
	m->ecx = M32((DWORD)(0x4e0468u));	/* 48841a: mov ecx, dword ptr [0x4e0468] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488420: push ecx */
	m->esp -= 4; M32(m->esp) = 0x488426u; native_call(m, 0x401600u);	/* 488421: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488426: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488429: test eax, eax */
	if (m->zf) goto L_488447;	/* 48842b: je 0x488447 */
	m->edx = M32((DWORD)(0x67ef24u));	/* 48842d: mov edx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488433: push edx */
	m->esp -= 4; M32(m->esp) = 0x488439u; native_call(m, 0x401600u);	/* 488434: call 0x401600 */
	m->edi = m->eax;	/* 488439: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48843b: add esp, 4 */
	{ DWORD a_ = m->edi, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->edi = r_; }	/* 48843e: neg edi */
	{ DWORD a_ = m->edi, b_ = m->edi, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->edi = r_; }	/* 488440: sbb edi, edi */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 488442: and edi, ebx */
	{ DWORD a_ = m->edi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 488444: add edi, 3 */
L_488447:
	m->eax = M32((DWORD)(0x4e0468u));	/* 488447: mov eax, dword ptr [0x4e0468] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48844c: push eax */
	m->esp -= 4; M32(m->esp) = 0x488452u; native_call(m, 0x401600u);	/* 48844d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488452: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488455: test eax, eax */
	if (m->zf) goto L_488473;	/* 488457: je 0x488473 */
	m->ecx = M32((DWORD)(0x67ef24u));	/* 488459: mov ecx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48845f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x488465u; native_call(m, 0x401600u);	/* 488460: call 0x401600 */
	m->edi = m->eax;	/* 488465: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488467: add esp, 4 */
	{ DWORD a_ = m->edi, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->edi = r_; }	/* 48846a: neg edi */
	{ DWORD a_ = m->edi, b_ = m->edi, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->edi = r_; }	/* 48846c: sbb edi, edi */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48846e: and edi, ebx */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 488470: add edi, 4 */
L_488473:
	m->edx = M32((DWORD)(0x4e0468u));	/* 488473: mov edx, dword ptr [0x4e0468] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488479: push edx */
	m->esp -= 4; M32(m->esp) = 0x48847fu; native_call(m, 0x401600u);	/* 48847a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48847f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488482: test eax, eax */
	if (m->zf) goto L_48849f;	/* 488484: je 0x48849f */
	m->eax = M32((DWORD)(0x67ef24u));	/* 488486: mov eax, dword ptr [0x67ef24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48848b: push eax */
	m->esp -= 4; M32(m->esp) = 0x488491u; native_call(m, 0x401600u);	/* 48848c: call 0x401600 */
	m->edi = m->eax;	/* 488491: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488493: add esp, 4 */
	{ DWORD a_ = m->edi, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->edi = r_; }	/* 488496: neg edi */
	{ DWORD a_ = m->edi, b_ = m->edi, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->edi = r_; }	/* 488498: sbb edi, edi */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48849a: and edi, ebx */
	{ DWORD a_ = m->edi, b_ = 0x5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48849c: add edi, 5 */
L_48849f:
	m->ecx = M32((DWORD)(0x4e0468u));	/* 48849f: mov ecx, dword ptr [0x4e0468] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4884a5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4884abu; native_call(m, 0x401600u);	/* 4884a6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4884ab: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4884ae: test eax, eax */
	if (m->zf) goto L_4884cc;	/* 4884b0: je 0x4884cc */
	m->edx = M32((DWORD)(0x67ef24u));	/* 4884b2: mov edx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4884b8: push edx */
	m->esp -= 4; M32(m->esp) = 0x4884beu; native_call(m, 0x401600u);	/* 4884b9: call 0x401600 */
	m->edi = m->eax;	/* 4884be: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4884c0: add esp, 4 */
	{ DWORD a_ = m->edi, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->edi = r_; }	/* 4884c3: neg edi */
	{ DWORD a_ = m->edi, b_ = m->edi, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->edi = r_; }	/* 4884c5: sbb edi, edi */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4884c7: and edi, ebx */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4884c9: add edi, 6 */
L_4884cc:
	m->eax = M32((DWORD)(0x4e0468u));	/* 4884cc: mov eax, dword ptr [0x4e0468] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4884d1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4884d7u; native_call(m, 0x401600u);	/* 4884d2: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4884d7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4884da: test eax, eax */
	if (m->zf) goto L_4884e3;	/* 4884dc: je 0x4884e3 */
	m->edi = 0x7u;	/* 4884de: mov edi, 7 */
L_4884e3:
	m->ecx = M32((DWORD)(0x4e0468u));	/* 4884e3: mov ecx, dword ptr [0x4e0468] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4884e9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4884efu; native_call(m, 0x401600u);	/* 4884ea: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4884ef: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4884f2: test eax, eax */
	if (m->zf) goto L_4884fb;	/* 4884f4: je 0x4884fb */
	m->edi = 0x8u;	/* 4884f6: mov edi, 8 */
L_4884fb:
	m->edx = M32((DWORD)(0x4e0468u));	/* 4884fb: mov edx, dword ptr [0x4e0468] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488501: push edx */
	m->esp -= 4; M32(m->esp) = 0x488507u; native_call(m, 0x401600u);	/* 488502: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488507: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48850a: test eax, eax */
	if (m->zf) goto L_488513;	/* 48850c: je 0x488513 */
	m->edi = 0x9u;	/* 48850e: mov edi, 9 */
L_488513:
	m->eax = M32((DWORD)(0x4e0468u));	/* 488513: mov eax, dword ptr [0x4e0468] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488518: push eax */
	m->esp -= 4; M32(m->esp) = 0x48851eu; native_call(m, 0x401600u);	/* 488519: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48851e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488521: test eax, eax */
	if (m->zf) goto L_488527;	/* 488523: je 0x488527 */
	m->edi = m->ebx;	/* 488525: mov edi, ebx */
L_488527:
	m->ecx = M32((DWORD)(0x5b1da8u));	/* 488527: mov ecx, dword ptr [0x5b1da8] */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 48852d: dec edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48852e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x488534u; native_call(m, 0x401590u);	/* 48852f: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488534: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488537: test eax, eax */
	if (m->zf) goto L_488545;	/* 488539: je 0x488545 */
	M32((DWORD)(m->esi + 0x2340d21u)) = m->ebp;	/* 48853b: mov dword ptr [esi + 0x2340d21], ebp */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 488541: xor ebx, ebx */
	goto L_48854d;	/* 488543: jmp 0x48854d */
L_488545:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 488545: xor ebx, ebx */
	M32((DWORD)(m->esi + 0x2340d21u)) = m->ebx;	/* 488547: mov dword ptr [esi + 0x2340d21], ebx */
L_48854d:
	m->edx = M32((DWORD)(0x9dae70u));	/* 48854d: mov edx, dword ptr [0x9dae70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488553: push edx */
	m->esp -= 4; M32(m->esp) = 0x488559u; native_call(m, 0x401590u);	/* 488554: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488559: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48855c: test eax, eax */
	if (m->zf) goto L_488568;	/* 48855e: je 0x488568 */
	M32((DWORD)(m->esi + 0x2340d25u)) = m->ebp;	/* 488560: mov dword ptr [esi + 0x2340d25], ebp */
	goto L_48856e;	/* 488566: jmp 0x48856e */
L_488568:
	M32((DWORD)(m->esi + 0x2340d25u)) = m->ebx;	/* 488568: mov dword ptr [esi + 0x2340d25], ebx */
L_48856e:
	m->eax = M32((DWORD)(0x4defe0u));	/* 48856e: mov eax, dword ptr [0x4defe0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488573: push eax */
	m->esp -= 4; M32(m->esp) = 0x488579u; native_call(m, 0x401590u);	/* 488574: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488579: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48857c: test eax, eax */
	if (!m->zf) goto L_488593;	/* 48857e: jne 0x488593 */
	m->ecx = M32((DWORD)(0x4defe4u));	/* 488580: mov ecx, dword ptr [0x4defe4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488586: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48858cu; native_call(m, 0x401590u);	/* 488587: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48858c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48858f: test eax, eax */
	if (m->zf) goto L_488599;	/* 488591: je 0x488599 */
L_488593:
	M32((DWORD)(m->esi + 0x234328fu)) = m->ebp;	/* 488593: mov dword ptr [esi + 0x234328f], ebp */
L_488599:
	m->edx = M32((DWORD)(0x4df8d0u));	/* 488599: mov edx, dword ptr [0x4df8d0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48859f: push edx */
	m->esp -= 4; M32(m->esp) = 0x4885a5u; native_call(m, 0x401600u);	/* 4885a0: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4885a5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4885a8: test eax, eax */
	if (m->zf) goto L_4885f0;	/* 4885aa: je 0x4885f0 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340ce8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4885ac: cmp dword ptr [esi + 0x2340ce8], ebx */
	if (!m->zf) goto L_4885c1;	/* 4885b2: jne 0x4885c1 */
	M32((DWORD)(m->esi + 0x2340ce8u)) = m->ebp;	/* 4885b4: mov dword ptr [esi + 0x2340ce8], ebp */
	{ DWORD v_ = 0x4c7d00u; m->esp -= 4; M32(m->esp) = v_; }	/* 4885ba: push 0x4c7d00 */
	goto L_4885e7;	/* 4885bf: jmp 0x4885e7 */
L_4885c1:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340ce4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4885c1: cmp dword ptr [esi + 0x2340ce4], ebx */
	if (!m->zf) goto L_4885d6;	/* 4885c7: jne 0x4885d6 */
	M32((DWORD)(m->esi + 0x2340ce4u)) = m->ebp;	/* 4885c9: mov dword ptr [esi + 0x2340ce4], ebp */
	{ DWORD v_ = 0x4c7cf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4885cf: push 0x4c7cf0 */
	goto L_4885e7;	/* 4885d4: jmp 0x4885e7 */
L_4885d6:
	M32((DWORD)(m->esi + 0x2340ce8u)) = m->ebx;	/* 4885d6: mov dword ptr [esi + 0x2340ce8], ebx */
	M32((DWORD)(m->esi + 0x2340ce4u)) = m->ebx;	/* 4885dc: mov dword ptr [esi + 0x2340ce4], ebx */
	{ DWORD v_ = 0x4c7ce4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4885e2: push 0x4c7ce4 */
L_4885e7:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4885e7: push esi */
	m->esp -= 4; M32(m->esp) = 0x4885edu; native_call(m, 0x463450u);	/* 4885e8: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4885ed: add esp, 8 */
L_4885f0:
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4885f0: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4885f5: mov ecx, dword ptr [0x4ded68] */
	M32((DWORD)(m->esi + 0x2343257u)) = m->ecx;	/* 4885fb: mov dword ptr [esi + 0x2343257], ecx */
	M32((DWORD)(m->esi + 0x234325bu)) = m->eax;	/* 488601: mov dword ptr [esi + 0x234325b], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 488607: fld dword ptr [esi + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94f8u)); FPOP();	/* 48860a: fcomp dword ptr [0x4a94f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488610: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488612: test ah, 1 */
	if (m->zf) goto L_488681;	/* 488615: je 0x488681 */
	{ DWORD a_ = M32((DWORD)(0x4df000u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488617: cmp dword ptr [0x4df000], ebx */
	if (!m->zf) goto L_48863b;	/* 48861d: jne 0x48863b */
	m->esp -= 4; M32(m->esp) = 0x488624u; native_call(m, 0x4685c0u);	/* 48861f: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 488624: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 488625: sub eax, edx */
	m->edx = M32((DWORD)(m->esi + 0x234325bu));	/* 488627: mov edx, dword ptr [esi + 0x234325b] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48862d: sar eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48862f: sub edx, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 488631: mov dword ptr [esp + 0x28], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 488635: fild dword ptr [esp + 0x28] */
	goto L_488657;	/* 488639: jmp 0x488657 */
L_48863b:
	m->esp -= 4; M32(m->esp) = 0x488640u; native_call(m, 0x4685c0u);	/* 48863b: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esi + 0x234325bu));	/* 488640: mov ecx, dword ptr [esi + 0x234325b] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 488646: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 488647: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 488649: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48864b: sub ecx, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 48864d: mov dword ptr [esp + 0x28], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 488651: fild dword ptr [esp + 0x28] */
	ST(0) = -ST(0);	/* 488655: fchs  */
L_488657:
	MF((DWORD)(m->esi + 0x2343293u)) = (float)ST(0); FPOP();	/* 488657: fstp dword ptr [esi + 0x2343293] */
	m->esp -= 4; M32(m->esp) = 0x488662u; native_call(m, 0x4685b0u);	/* 48865d: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 488662: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 488663: sub eax, edx */
	m->edx = M32((DWORD)(m->esi + 0x2343257u));	/* 488665: mov edx, dword ptr [esi + 0x2343257] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48866b: sar eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48866d: sub edx, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 48866f: mov dword ptr [esp + 0x28], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 488673: fild dword ptr [esp + 0x28] */
	ST(0) = -ST(0);	/* 488677: fchs  */
	MF((DWORD)(m->esi + 0x2343297u)) = (float)ST(0); FPOP();	/* 488679: fstp dword ptr [esi + 0x2343297] */
	goto L_48868d;	/* 48867f: jmp 0x48868d */
L_488681:
	M32((DWORD)(m->esi + 0x2343293u)) = m->ebx;	/* 488681: mov dword ptr [esi + 0x2343293], ebx */
	M32((DWORD)(m->esi + 0x2343297u)) = m->ebx;	/* 488687: mov dword ptr [esi + 0x2343297], ebx */
L_48868d:
	FPUSH((long double)(int)M32((DWORD)(0x4df008u)));	/* 48868d: fild dword ptr [0x4df008] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa480u));	/* 488693: fmul dword ptr [0x4aa480] */
	{ long double t = ST(0); FPUSH(t); }	/* 488699: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 48869b: fmulp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 48869d: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4886a3: fmul dword ptr [0x4a942c] */
	{ long double t = ST(0); FPUSH(t); }	/* 4886a9: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343293u));	/* 4886ab: fmul dword ptr [esi + 0x2343293] */
	MF((DWORD)(m->esi + 0x2343293u)) = (float)ST(0); FPOP();	/* 4886b1: fstp dword ptr [esi + 0x2343293] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343297u));	/* 4886b7: fmul dword ptr [esi + 0x2343297] */
	MF((DWORD)(m->esi + 0x2343297u)) = (float)ST(0); FPOP();	/* 4886bd: fstp dword ptr [esi + 0x2343297] */
	m->esp -= 4; M32(m->esp) = 0x4886c8u; native_call(m, 0x4685b0u);	/* 4886c3: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4886c8: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4886c9: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4886cb: sar eax, 1 */
	M32((DWORD)(0x4ded68u)) = m->eax;	/* 4886cd: mov dword ptr [0x4ded68], eax */
	m->esp -= 4; M32(m->esp) = 0x4886d7u; native_call(m, 0x4685c0u);	/* 4886d2: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4886d7: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4886d8: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4886da: sar eax, 1 */
	M32((DWORD)(0x4ded6cu)) = m->eax;	/* 4886dc: mov dword ptr [0x4ded6c], eax */
	m->eax = M32((DWORD)(0x4defc8u));	/* 4886e1: mov eax, dword ptr [0x4defc8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4886e6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4886ecu; native_call(m, 0x401600u);	/* 4886e7: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4886ec: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4886ef: test eax, eax */
	if (!m->zf) goto L_488706;	/* 4886f1: jne 0x488706 */
	m->ecx = M32((DWORD)(0x4defccu));	/* 4886f3: mov ecx, dword ptr [0x4defcc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4886f9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4886ffu; native_call(m, 0x401600u);	/* 4886fa: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4886ff: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488702: test eax, eax */
	if (m->zf) goto L_488725;	/* 488704: je 0x488725 */
L_488706:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d39u)));	/* 488706: fld dword ptr [esi + 0x2340d39] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48870c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488712: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488714: test ah, 0x41 */
	if (m->zf) goto L_488725;	/* 488717: je 0x488725 */
	M32((DWORD)(0x9db994u)) = m->ebx;	/* 488719: mov dword ptr [0x9db994], ebx */
	M32((DWORD)(m->esi + 0x23432cfu)) = m->ebp;	/* 48871f: mov dword ptr [esi + 0x23432cf], ebp */
L_488725:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc40u)));	/* 488725: fld dword ptr [esi + 0x233cc40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48872b: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488731: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488733: test ah, 0x41 */
	if (!m->zf) goto L_48875a;	/* 488736: jne 0x48875a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc40u)));	/* 488738: fld dword ptr [esi + 0x233cc40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 48873e: fsub dword ptr [esi + 0x44] */
	MF((DWORD)(m->esi + 0x233cc40u)) = (float)ST(0);	/* 488741: fst dword ptr [esi + 0x233cc40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 488747: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48874d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48874f: test ah, 1 */
	if (m->zf) goto L_48875a;	/* 488752: je 0x48875a */
	M32((DWORD)(m->esi + 0x233cc40u)) = m->ebx;	/* 488754: mov dword ptr [esi + 0x233cc40], ebx */
L_48875a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2342f02u)));	/* 48875a: fld dword ptr [esi + 0x2342f02] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 488760: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488766: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488768: test ah, 0x41 */
	if (!m->zf) goto L_48878f;	/* 48876b: jne 0x48878f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2342f02u)));	/* 48876d: fld dword ptr [esi + 0x2342f02] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 488773: fsub dword ptr [esi + 0x44] */
	MF((DWORD)(m->esi + 0x2342f02u)) = (float)ST(0);	/* 488776: fst dword ptr [esi + 0x2342f02] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48877c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488782: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488784: test ah, 1 */
	if (m->zf) goto L_48878f;	/* 488787: je 0x48878f */
	M32((DWORD)(m->esi + 0x2342f02u)) = m->ebx;	/* 488789: mov dword ptr [esi + 0x2342f02], ebx */
L_48878f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2342425u)));	/* 48878f: fld dword ptr [esi + 0x2342425] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 488795: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48879b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48879d: test ah, 0x41 */
	if (!m->zf) goto L_4887cf;	/* 4887a0: jne 0x4887cf */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2342425u)));	/* 4887a2: fld dword ptr [esi + 0x2342425] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 4887a8: fsub dword ptr [esi + 0x44] */
	MF((DWORD)(m->esi + 0x2342425u)) = (float)ST(0);	/* 4887ab: fst dword ptr [esi + 0x2342425] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4887b1: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4887b7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4887b9: test ah, 1 */
	if (m->zf) goto L_4887cf;	/* 4887bc: je 0x4887cf */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 4887be: lea ecx, [esi + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x4887c9u; native_call(m, 0x473610u);	/* 4887c4: call 0x473610 */
	M32((DWORD)(m->esi + 0x2342425u)) = m->ebx;	/* 4887c9: mov dword ptr [esi + 0x2342425], ebx */
L_4887cf:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 4887cf: fld dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9554u));	/* 4887d2: fmul dword ptr [0x4a9554] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 4887d8: fst dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1f4164u)));	/* 4887dc: fld dword ptr [esi + 0x1f4164] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 4887e2: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 4887e4: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4887e6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4887e8: test ah, 0x41 */
	if (!m->zf) goto L_4887f7;	/* 4887eb: jne 0x4887f7 */
	m->edx = M32((DWORD)(m->esi + 0x1f4164u));	/* 4887ed: mov edx, dword ptr [esi + 0x1f4164] */
	M32((DWORD)(m->esp + 0x38u)) = m->edx;	/* 4887f3: mov dword ptr [esp + 0x38], edx */
L_4887f7:
	m->esp -= 4; M32(m->esp) = 0x4887fcu; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 4887f7: call 0x4686d0 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa2a8u));	/* 4887fc: fmul dword ptr [0x4aa2a8] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432abu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488802: cmp dword ptr [esi + 0x23432ab], ebp */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 488808: fmul dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9560u));	/* 48880b: fmul dword ptr [0x4a9560] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 488811: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 488815: fld dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a945cu));	/* 488818: fmul dword ptr [0x4a945c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 48881e: fstp dword ptr [esp + 0x28] */
	if (!m->zf) goto L_48885c;	/* 488822: jne 0x48885c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 488824: fld dword ptr [esi + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 488827: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48882d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48882f: test ah, 1 */
	if (m->zf) goto L_488839;	/* 488832: je 0x488839 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 488834: fld dword ptr [esi + 0x44] */
	goto L_48883f;	/* 488837: jmp 0x48883f */
L_488839:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 488839: fld dword ptr [0x4a9424] */
L_48883f:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9508u));	/* 48883f: fmul dword ptr [0x4a9508] */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 488845: mov eax, dword ptr [esi + 0x233cc10] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 48884b: fsubr dword ptr [0x4a9424] */
	m->eax = (DWORD)(m->esi + m->eax*4 + 0x233cb70u);	/* 488851: lea eax, [esi + eax*4 + 0x233cb70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 488858: fmul dword ptr [eax] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 48885a: fstp dword ptr [eax] */
L_48885c:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432afu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48885c: cmp dword ptr [esi + 0x23432af], ebp */
	if (!m->zf) goto L_48889c;	/* 488862: jne 0x48889c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 488864: fld dword ptr [esi + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 488867: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48886d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48886f: test ah, 1 */
	if (m->zf) goto L_488879;	/* 488872: je 0x488879 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 488874: fld dword ptr [esi + 0x44] */
	goto L_48887f;	/* 488877: jmp 0x48887f */
L_488879:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 488879: fld dword ptr [0x4a9424] */
L_48887f:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9508u));	/* 48887f: fmul dword ptr [0x4a9508] */
	m->ecx = M32((DWORD)(m->esi + 0x233cc10u));	/* 488885: mov ecx, dword ptr [esi + 0x233cc10] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 48888b: fsubr dword ptr [0x4a9424] */
	m->eax = (DWORD)(m->esi + m->ecx*4 + 0x233cb70u);	/* 488891: lea eax, [esi + ecx*4 + 0x233cb70] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 488898: fdivr dword ptr [eax] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 48889a: fstp dword ptr [eax] */
L_48889c:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432cbu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48889c: cmp dword ptr [esi + 0x23432cb], ebp */
	if (!m->zf) goto L_48891c;	/* 4888a2: jne 0x48891c */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 4888a4: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca30u));	/* 4888aa: mov edx, dword ptr [esi + eax*4 + 0x233ca30] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb20u)) = m->edx;	/* 4888b1: mov dword ptr [esi + eax*4 + 0x233cb20], edx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 4888b8: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca58u));	/* 4888be: mov ecx, dword ptr [esi + eax*4 + 0x233ca58] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb48u)) = m->ecx;	/* 4888c5: mov dword ptr [esi + eax*4 + 0x233cb48], ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 4888cc: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca80u));	/* 4888d2: mov edx, dword ptr [esi + eax*4 + 0x233ca80] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb70u)) = m->edx;	/* 4888d9: mov dword ptr [esi + eax*4 + 0x233cb70], edx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 4888e0: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233caa8u));	/* 4888e6: mov ecx, dword ptr [esi + eax*4 + 0x233caa8] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb98u)) = m->ecx;	/* 4888ed: mov dword ptr [esi + eax*4 + 0x233cb98], ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 4888f4: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233cad0u));	/* 4888fa: mov edx, dword ptr [esi + eax*4 + 0x233cad0] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cbc0u)) = m->edx;	/* 488901: mov dword ptr [esi + eax*4 + 0x233cbc0], edx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 488908: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233caf8u));	/* 48890e: mov ecx, dword ptr [esi + eax*4 + 0x233caf8] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cbe8u)) = m->ecx;	/* 488915: mov dword ptr [esi + eax*4 + 0x233cbe8], ecx */
L_48891c:
	m->eax = M32((DWORD)(m->esi + 0x233c9fcu));	/* 48891c: mov eax, dword ptr [esi + 0x233c9fc] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 488922: sub eax, ebx */
	if (m->zf) goto L_488971;	/* 488924: je 0x488971 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 488926: dec eax */
	if (!m->zf) goto L_488b94;	/* 488927: jne 0x488b94 */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48892d: mov eax, dword ptr [esi + 0x233cc10] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488933: cmp eax, 2 */
	if (m->zf) goto L_488b94;	/* 488936: je 0x488b94 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2343297u)));	/* 48893c: fld dword ptr [esi + 0x2343297] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + m->eax*4 + 0x233cb48u));	/* 488942: fadd dword ptr [esi + eax*4 + 0x233cb48] */
	MF((DWORD)(m->esi + m->eax*4 + 0x233cb48u)) = (float)ST(0); FPOP();	/* 488949: fstp dword ptr [esi + eax*4 + 0x233cb48] */
	m->edx = M32((DWORD)(m->esi + 0x233cc10u));	/* 488950: mov edx, dword ptr [esi + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2343293u)));	/* 488956: fld dword ptr [esi + 0x2343293] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + m->edx*4 + 0x233cb20u));	/* 48895c: fadd dword ptr [esi + edx*4 + 0x233cb20] */
	m->eax = (DWORD)(m->esi + m->edx*4 + 0x233cb20u);	/* 488963: lea eax, [esi + edx*4 + 0x233cb20] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 48896a: fstp dword ptr [eax] */
	goto L_488b94;	/* 48896c: jmp 0x488b94 */
L_488971:
	m->ecx = M32((DWORD)(0xa0e7ecu));	/* 488971: mov ecx, dword ptr [0xa0e7ec] */
	m->eax = M32((DWORD)(0xa0e7e8u));	/* 488977: mov eax, dword ptr [0xa0e7e8] */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 48897c: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->esp + 0x40u)) = m->ecx;	/* 488982: mov dword ptr [esp + 0x40], ecx */
	m->ecx = M32((DWORD)(m->esi + 0x234326bu));	/* 488986: mov ecx, dword ptr [esi + 0x234326b] */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 48898c: mov dword ptr [esp + 0x3c], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 488990: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488992: cmp ecx, ebx */
	M32((DWORD)(m->esp + 0x44u)) = m->edx;	/* 488994: mov dword ptr [esp + 0x44], edx */
	if (m->zf) goto L_48899c;	/* 488998: je 0x48899c */
	m->eax = m->ebp;	/* 48899a: mov eax, ebp */
L_48899c:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234326fu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48899c: cmp dword ptr [esi + 0x234326f], ebx */
	if (m->zf) goto L_4889a6;	/* 4889a2: je 0x4889a6 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 4889a4: or al, 0x10 */
L_4889a6:
	m->ecx = M32((DWORD)(m->esi + 0x234325fu));	/* 4889a6: mov ecx, dword ptr [esi + 0x234325f] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4889ac: cmp ecx, ebx */
	if (!m->zf) goto L_4889ca;	/* 4889ae: jne 0x4889ca */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343263u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4889b0: cmp dword ptr [esi + 0x2343263], ebx */
	if (m->zf) goto L_4889bb;	/* 4889b6: je 0x4889bb */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 4889b8: or ah, 1 */
L_4889bb:
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4889bb: cmp ecx, ebx */
	if (!m->zf) goto L_4889ca;	/* 4889bd: jne 0x4889ca */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343267u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4889bf: cmp dword ptr [esi + 0x2343267], ebx */
	if (m->zf) goto L_4889ca;	/* 4889c5: je 0x4889ca */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 4889c7: or ah, 0x10 */
L_4889ca:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4889ca: cmp eax, ebx */
	if (m->zf) goto L_488a7a;	/* 4889cc: je 0x488a7a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4889d2: fld dword ptr [esp + 0x38] */
	ST(0) = -ST(0);	/* 4889d6: fchs  */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4889d8: fstp dword ptr [esp + 0x44] */
	{ DWORD a_ = m->eax, b_ = 0x110u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4889dc: cmp eax, 0x110 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x0u;	/* 4889e1: mov dword ptr [esp + 0x3c], 0 */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 4889e9: mov dword ptr [esp + 0x40], 0 */
	if (!m->cf && !m->zf) goto L_488a20;	/* 4889f1: ja 0x488a20 */
	if (m->zf) goto L_488a19;	/* 4889f3: je 0x488a19 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4889f5: dec eax */
	if (m->zf) goto L_488a12;	/* 4889f6: je 0x488a12 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4889f8: sub eax, 0xf */
	if (m->zf) goto L_488a0b;	/* 4889fb: je 0x488a0b */
	{ DWORD a_ = m->eax, b_ = 0xf1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4889fd: sub eax, 0xf1 */
	if (!m->zf) goto L_488a4d;	/* 488a02: jne 0x488a4d */
	{ DWORD v_ = 0xfffff3b2u; m->esp -= 4; M32(m->esp) = v_; }	/* 488a04: push 0xfffff3b2 */
	goto L_488a42;	/* 488a09: jmp 0x488a42 */
L_488a0b:
	{ DWORD v_ = 0xfffffc7cu; m->esp -= 4; M32(m->esp) = v_; }	/* 488a0b: push 0xfffffc7c */
	goto L_488a42;	/* 488a10: jmp 0x488a42 */
L_488a12:
	{ DWORD v_ = 0xfffff574u; m->esp -= 4; M32(m->esp) = v_; }	/* 488a12: push 0xfffff574 */
	goto L_488a42;	/* 488a17: jmp 0x488a42 */
L_488a19:
	{ DWORD v_ = 0xfffffe3eu; m->esp -= 4; M32(m->esp) = v_; }	/* 488a19: push 0xfffffe3e */
	goto L_488a42;	/* 488a1e: jmp 0x488a42 */
L_488a20:
	{ DWORD a_ = m->eax, b_ = 0x1000u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 488a20: sub eax, 0x1000 */
	if (m->zf) goto L_488a3d;	/* 488a25: je 0x488a3d */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 488a27: dec eax */
	if (m->zf) goto L_488a36;	/* 488a28: je 0x488a36 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 488a2a: sub eax, 0xf */
	if (!m->zf) goto L_488a4d;	/* 488a2d: jne 0x488a4d */
	{ DWORD v_ = 0xfffffabau; m->esp -= 4; M32(m->esp) = v_; }	/* 488a2f: push 0xfffffaba */
	goto L_488a42;	/* 488a34: jmp 0x488a42 */
L_488a36:
	{ DWORD v_ = 0xfffff736u; m->esp -= 4; M32(m->esp) = v_; }	/* 488a36: push 0xfffff736 */
	goto L_488a42;	/* 488a3b: jmp 0x488a42 */
L_488a3d:
	{ DWORD v_ = 0xfffff8f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 488a3d: push 0xfffff8f8 */
L_488a42:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 488a42: push 2 */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 488a44: lea ecx, [esp + 0x44] */
	m->esp -= 4; M32(m->esp) = 0x488a4du; native_call(m, 0x4677c0u);	/* 488a48: call 0x4677c0 */
L_488a4d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 488a4d: fld dword ptr [esi + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 488a53: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488a58: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488a59: push ebp */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 488a5a: lea ecx, [esp + 0x44] */
	m->esp -= 4; M32(m->esp) = 0x488a63u; native_call(m, 0x4677c0u);	/* 488a5e: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 488a63: fld dword ptr [esi + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 488a69: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488a6e: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 488a6f: push 2 */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 488a71: lea ecx, [esp + 0x44] */
	m->esp -= 4; M32(m->esp) = 0x488a7au; native_call(m, 0x4677c0u);	/* 488a75: call 0x4677c0 */
L_488a7a:
	m->eax = M32((DWORD)(m->esi + 0x234325fu));	/* 488a7a: mov eax, dword ptr [esi + 0x234325f] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488a80: cmp eax, ebx */
	if (m->zf) goto L_488a8c;	/* 488a82: je 0x488a8c */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343263u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488a84: cmp dword ptr [esi + 0x2343263], ebx */
	if (!m->zf) goto L_488a94;	/* 488a8a: jne 0x488a94 */
L_488a8c:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343273u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488a8c: cmp dword ptr [esi + 0x2343273], ebx */
	if (m->zf) goto L_488aa0;	/* 488a92: je 0x488aa0 */
L_488a94:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 488a94: fld dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 488a98: fadd dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 488a9c: fstp dword ptr [esp + 0x40] */
L_488aa0:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488aa0: cmp eax, ebx */
	if (m->zf) goto L_488aac;	/* 488aa2: je 0x488aac */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343267u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488aa4: cmp dword ptr [esi + 0x2343267], ebx */
	if (!m->zf) goto L_488ab4;	/* 488aaa: jne 0x488ab4 */
L_488aac:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343277u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488aac: cmp dword ptr [esi + 0x2343277], ebx */
	if (m->zf) goto L_488ac0;	/* 488ab2: je 0x488ac0 */
L_488ab4:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 488ab4: fld dword ptr [esp + 0x40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 488ab8: fsub dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 488abc: fstp dword ptr [esp + 0x40] */
L_488ac0:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2343283u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488ac0: cmp dword ptr [esi + 0x2343283], ebx */
	if (m->zf) goto L_488af2;	/* 488ac6: je 0x488af2 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 488ac8: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 488acc: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 488ad2: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 488ad6: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 488ada: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 488ae0: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 488ae4: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 488ae8: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 488aee: fstp dword ptr [esp + 0x44] */
L_488af2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 488af2: fld dword ptr [esp + 0x70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343293u));	/* 488af6: fmul dword ptr [esi + 0x2343293] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esi + 0x233ca28u));	/* 488afc: fsubr dword ptr [esi + 0x233ca28] */
	MF((DWORD)(m->esi + 0x233ca28u)) = (float)ST(0);	/* 488b02: fst dword ptr [esi + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a972cu)); FPOP();	/* 488b08: fcomp dword ptr [0x4a972c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488b0e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488b10: test ah, 0x41 */
	if (!m->zf) goto L_488b1f;	/* 488b13: jne 0x488b1f */
	M32((DWORD)(m->esi + 0x233ca28u)) = 0x445e8000u;	/* 488b15: mov dword ptr [esi + 0x233ca28], 0x445e8000 */
L_488b1f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 488b1f: fld dword ptr [esi + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9728u)); FPOP();	/* 488b25: fcomp dword ptr [0x4a9728] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488b2b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488b2d: test ah, 1 */
	if (m->zf) goto L_488b3c;	/* 488b30: je 0x488b3c */
	M32((DWORD)(m->esi + 0x233ca28u)) = 0xc45e8000u;	/* 488b32: mov dword ptr [esi + 0x233ca28], 0xc45e8000 */
L_488b3c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 488b3c: fld dword ptr [esp + 0x70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343297u));	/* 488b40: fmul dword ptr [esi + 0x2343297] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x233ca2cu));	/* 488b46: fadd dword ptr [esi + 0x233ca2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94c8u));	/* 488b4c: fcom dword ptr [0x4a94c8] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0);	/* 488b52: fst dword ptr [esi + 0x233ca2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488b58: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488b5a: test ah, 1 */
	if (!m->zf) goto L_488b6d;	/* 488b5d: jne 0x488b6d */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 488b5f: fsub dword ptr [0x4a94c8] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 488b65: fstp dword ptr [esi + 0x233ca2c] */
	goto L_488b6f;	/* 488b6b: jmp 0x488b6f */
L_488b6d:
	ST(0) = ST(0); FPOP();	/* 488b6d: fstp st(0) */
L_488b6f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 488b6f: fld dword ptr [esi + 0x233ca2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 488b75: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488b7b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488b7d: test ah, 1 */
	if (m->zf) goto L_488b94;	/* 488b80: je 0x488b94 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 488b82: fld dword ptr [esi + 0x233ca2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 488b88: fadd dword ptr [0x4a94c8] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 488b8e: fstp dword ptr [esi + 0x233ca2c] */
L_488b94:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234328bu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488b94: cmp dword ptr [esi + 0x234328b], ebx */
	if (m->zf) goto L_488bca;	/* 488b9a: je 0x488bca */
	m->esp -= 4; M32(m->esp) = 0x488ba1u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 488b9c: call 0x4686d0 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 488ba1: fsub dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488ba5: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 488ba6: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x488baeu; native_call(m, 0x4686e0u);	/* 488ba9: call 0x4686e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488bae: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x488bb6u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 488bb1: call 0x4686d0 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 488bb6: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488bbc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488bbe: test ah, 1 */
	if (m->zf) goto L_488bfe;	/* 488bc1: je 0x488bfe */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 488bc3: push 0x41200000 */
	goto L_488bf6;	/* 488bc8: jmp 0x488bf6 */
L_488bca:
	m->esp -= 4; M32(m->esp) = 0x488bcfu; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 488bca: call 0x4686d0 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 488bcf: fadd dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488bd3: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 488bd4: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x488bdcu; native_call(m, 0x4686e0u);	/* 488bd7: call 0x4686e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488bdc: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x488be4u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 488bdf: call 0x4686d0 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94dcu)); FPOP();	/* 488be4: fcomp dword ptr [0x4a94dc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488bea: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488bec: test ah, 0x41 */
	if (!m->zf) goto L_488bfe;	/* 488bef: jne 0x488bfe */
	{ DWORD v_ = 0x42700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 488bf1: push 0x42700000 */
L_488bf6:
	m->esp -= 4; M32(m->esp) = 0x488bfbu; native_call(m, 0x4686e0u);	/* 488bf6: call 0x4686e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488bfb: add esp, 4 */
L_488bfe:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340d21u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488bfe: cmp dword ptr [esi + 0x2340d21], ebp */
	if (!m->zf) goto L_488c15;	/* 488c04: jne 0x488c15 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 488c06: fld dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9468u));	/* 488c09: fmul dword ptr [0x4a9468] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 488c0f: fstp dword ptr [esp + 0x38] */
	goto L_488c1c;	/* 488c13: jmp 0x488c1c */
L_488c15:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 488c15: mov eax, dword ptr [esi + 0x44] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 488c18: mov dword ptr [esp + 0x38], eax */
L_488c1c:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340ce0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488c1c: cmp dword ptr [esi + 0x2340ce0], ebx */
	if (!m->zf) goto L_489157;	/* 488c22: jne 0x489157 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d29u)));	/* 488c28: fld dword ptr [esi + 0x2340d29] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x2340d2du)); FPOP();	/* 488c2e: fcomp dword ptr [esi + 0x2340d2d] */
	m->ebx = (DWORD)(m->esi + 0x2340d29u);	/* 488c34: lea ebx, [esi + 0x2340d29] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488c3a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488c3c: test ah, 0x41 */
	if (m->zf) goto L_488ce9;	/* 488c3f: je 0x488ce9 */
L_488c45:
	m->ecx = M32((DWORD)(m->esi + 0x2340d08u));	/* 488c45: mov ecx, dword ptr [esi + 0x2340d08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488c4b: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488c4c: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 488c4d: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 488c4f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x488c55u; native_call(m, 0x46cbe0u);	/* 488c50: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488c55: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488c58: test eax, eax */
	if (m->zf) goto L_488d75;	/* 488c5a: je 0x488d75 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340d25u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488c60: cmp dword ptr [esi + 0x2340d25], ebp */
	if (m->zf) goto L_488d75;	/* 488c66: je 0x488d75 */
	m->edx = M32((DWORD)(m->esi + 0x2340d08u));	/* 488c6c: mov edx, dword ptr [esi + 0x2340d08] */
	m->eax = (DWORD)(m->esp + 0x8cu);	/* 488c72: lea eax, [esp + 0x8c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488c79: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488c7a: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 488c7b: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488c7d: push eax */
	m->esp -= 4; M32(m->esp) = 0x488c83u; native_call(m, 0x46cbe0u);	/* 488c7e: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->esi + 0x2340d08u));	/* 488c83: mov ecx, dword ptr [esi + 0x2340d08] */
	m->edx = (DWORD)(m->esp + 0x7cu);	/* 488c89: lea edx, [esp + 0x7c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488c8d: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488c8e: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 488c8f: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488c91: push edx */
	m->esp -= 4; M32(m->esp) = 0x488c97u; native_call(m, 0x46cbe0u);	/* 488c92: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esi + 0x2340d08u));	/* 488c97: mov eax, dword ptr [esi + 0x2340d08] */
	m->ecx = M32((DWORD)(m->esp + 0x8cu));	/* 488c9d: mov ecx, dword ptr [esp + 0x8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488ca4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488ca5: push ecx */
	m->edx = (DWORD)(m->esp + 0x174u);	/* 488ca6: lea edx, [esp + 0x174] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488cad: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488cae: push edx */
	m->esp -= 4; M32(m->esp) = 0x488cb4u; native_call(m, 0x46cbe0u);	/* 488caf: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->esp + 0x9cu));	/* 488cb4: mov ecx, dword ptr [esp + 0x9c] */
	m->edx = M32((DWORD)(m->esp + 0xbcu));	/* 488cbb: mov edx, dword ptr [esp + 0xbc] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488cc2: add esp, 0x30 */
	m->eax = (DWORD)(m->esp + 0x14cu);	/* 488cc5: lea eax, [esp + 0x14c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 488ccc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 488ccd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 488cce: push edx */
	m->ecx = m->esi;	/* 488ccf: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x488cd6u; native_call(m, 0x48c830u);	/* 488cd1: call 0x48c830 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 488cd6: fld dword ptr [ebx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x2340d2du)); FPOP();	/* 488cd8: fcomp dword ptr [esi + 0x2340d2d] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488cde: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488ce0: test ah, 0x41 */
	if (!m->zf) goto L_488c45;	/* 488ce3: jne 0x488c45 */
L_488ce9:
	m->ebp = M32((DWORD)(m->esp + 0x38u));	/* 488ce9: mov ebp, dword ptr [esp + 0x38] */
	m->ebx = (DWORD)(m->esi + 0x1f36c8u);	/* 488ced: lea ebx, [esi + 0x1f36c8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488cf3: push ebp */
	m->ecx = m->ebx;	/* 488cf4: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x488cfbu; native_call(m, 0x496e40u);	/* 488cf6: call 0x496e40 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488cfb: push ebp */
	m->ecx = m->ebx;	/* 488cfc: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x488d03u; native_call(m, 0x490d40u);	/* 488cfe: call 0x490d40 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488d03: push ebp */
	m->ecx = m->ebx;	/* 488d04: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x488d0bu; native_call(m, 0x45e0c0u);	/* 488d06: call 0x45e0c0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488d0b: push ebp */
	m->ecx = m->ebx;	/* 488d0c: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x488d13u; native_call(m, 0x47d000u);	/* 488d0e: call 0x47d000 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488d13: push ebp */
	m->ecx = m->ebx;	/* 488d14: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x488d1bu; native_call(m, 0x479a90u);	/* 488d16: call 0x479a90 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 488d1b: push ebp */
	m->ecx = m->ebx;	/* 488d1c: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x488d23u; native_call(m, 0x48ed90u);	/* 488d1e: call 0x48ed90 */
	m->ecx = M32((DWORD)(m->esi + 0x2221f90u));	/* 488d23: mov ecx, dword ptr [esi + 0x2221f90] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488d29: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_489106;	/* 488d2b: jle 0x489106 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 488d31: xor ebp, ebp */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488d33: cmp edi, ebp */
	if (m->sf != m->of) goto L_488e33;	/* 488d35: jl 0x488e33 */
	m->ecx = m->edi;	/* 488d3b: mov ecx, edi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 488d3d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 488d40: add ecx, edi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 488d42: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 488d45: add ecx, edi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 488d47: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 488d4a: add ecx, edi */
	{ DWORD a_ = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb88u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488d4c: cmp dword ptr [esi + ecx*8 + 0x1eccb88], ebp */
	if (m->sf != m->of) goto L_488fc8;	/* 488d53: jl 0x488fc8 */
	M32((DWORD)(m->esi + 0x2340c64u)) = m->edi;	/* 488d59: mov dword ptr [esi + 0x2340c64], edi */
	m->ebx = 0x1u;	/* 488d5f: mov ebx, 1 */
	M32((DWORD)(m->esi + 0x2340c70u)) = m->ebp;	/* 488d64: mov dword ptr [esi + 0x2340c70], ebp */
	M32((DWORD)(m->esi + 0x2340c68u)) = m->ebx;	/* 488d6a: mov dword ptr [esi + 0x2340c68], ebx */
	goto L_488fcd;	/* 488d70: jmp 0x488fcd */
L_488d75:
	{ DWORD a_ = M32((DWORD)(0x9eeac0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488d75: cmp dword ptr [0x9eeac0], ebp */
	if (!m->zf) goto L_488dcc;	/* 488d7b: jne 0x488dcc */
	m->edi = (DWORD)(m->esi + 0x1f36c8u);	/* 488d7d: lea edi, [esi + 0x1f36c8] */
	m->ecx = m->edi;	/* 488d83: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x488d8au; native_call(m, 0x470a70u);	/* 488d85: call 0x470a70 */
	m->ecx = m->edi;	/* 488d8a: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x488d91u; native_call(m, 0x470ad0u);	/* 488d8c: call 0x470ad0 */
	m->ecx = M32((DWORD)(m->esi + 0x1f35bcu));	/* 488d91: mov ecx, dword ptr [esi + 0x1f35bc] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 488d97: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_488dc2;	/* 488d99: jle 0x488dc2 */
	m->edi = M32((DWORD)(0xa1efb8u));	/* 488d9b: mov edi, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 488da1: xor edx, edx */
	m->eax = m->edi;	/* 488da3: mov eax, edi */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 488da5: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 488daa: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 488db1: div ecx */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 488db3: inc edi */
	M32((DWORD)(0xa1efb8u)) = m->edi;	/* 488db4: mov dword ptr [0xa1efb8], edi */
	M32((DWORD)(m->esi + 0x1f35c0u)) = m->edx;	/* 488dba: mov dword ptr [esi + 0x1f35c0], edx */
	goto L_488e0b;	/* 488dc0: jmp 0x488e0b */
L_488dc2:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 488dc2: xor edx, edx */
	M32((DWORD)(m->esi + 0x1f35c0u)) = m->edx;	/* 488dc4: mov dword ptr [esi + 0x1f35c0], edx */
	goto L_488e0b;	/* 488dca: jmp 0x488e0b */
L_488dcc:
	m->edx = M32((DWORD)(m->esi + 0x1f35c0u));	/* 488dcc: mov edx, dword ptr [esi + 0x1f35c0] */
	m->ecx = M32((DWORD)(m->esi + 0x1f35bcu));	/* 488dd2: mov ecx, dword ptr [esi + 0x1f35bc] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 488dd8: inc edx */
	m->eax = m->edx;	/* 488dd9: mov eax, edx */
	M32((DWORD)(m->esi + 0x1f35c0u)) = m->edx;	/* 488ddb: mov dword ptr [esi + 0x1f35c0], edx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488de1: cmp eax, ecx */
	if (m->sf != m->of) goto L_488df7;	/* 488de3: jl 0x488df7 */
	{ DWORD a_ = M32((DWORD)(0x4b2a7cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488de5: cmp dword ptr [0x4b2a7c], ebp */
	if (!m->zf) goto L_488e28;	/* 488deb: jne 0x488e28 */
	M32((DWORD)(m->esi + 0x1f35c0u)) = 0x0u;	/* 488ded: mov dword ptr [esi + 0x1f35c0], 0 */
L_488df7:
	m->edi = (DWORD)(m->esi + 0x1f36c8u);	/* 488df7: lea edi, [esi + 0x1f36c8] */
	m->ecx = m->edi;	/* 488dfd: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x488e04u; native_call(m, 0x470a70u);	/* 488dff: call 0x470a70 */
	m->ecx = m->edi;	/* 488e04: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x488e0bu; native_call(m, 0x470ad0u);	/* 488e06: call 0x470ad0 */
L_488e0b:
	M32((DWORD)(m->esi + 0x233cc20u)) = m->ebp;	/* 488e0b: mov dword ptr [esi + 0x233cc20], ebp */
	M32((DWORD)(m->esi + 0x233cc28u)) = 0x0u;	/* 488e11: mov dword ptr [esi + 0x233cc28], 0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 488e1b: pop edi */
	m->eax = m->ebp;	/* 488e1c: mov eax, ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 488e1e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 488e1f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 488e20: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x27cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 488e21: add esp, 0x27c */
	m->esp += 4 + 0; return;	/* 488e27: ret  */
L_488e28:
	M32((DWORD)(m->esi + 0x23432cfu)) = m->ebp;	/* 488e28: mov dword ptr [esi + 0x23432cf], ebp */
	goto L_488ce9;	/* 488e2e: jmp 0x488ce9 */
L_488e33:
	m->eax = M32((DWORD)(m->esi + 0x234331bu));	/* 488e33: mov eax, dword ptr [esi + 0x234331b] */
	m->ebx = 0x1u;	/* 488e39: mov ebx, 1 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488e3e: cmp eax, ebx */
	if (!m->zf) goto L_488f42;	/* 488e40: jne 0x488f42 */
	m->edi = M32((DWORD)(m->esi + 0x2340c64u));	/* 488e46: mov edi, dword ptr [esi + 0x2340c64] */
	m->eax = (DWORD)(m->edi + 0x1u);	/* 488e4c: lea eax, [edi + 1] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488e4f: cmp eax, ecx */
	if (!m->zf) goto L_488ea6;	/* 488e51: jne 0x488ea6 */
	m->edx = (DWORD)(m->esi + 0x22ee228u);	/* 488e53: lea edx, [esi + 0x22ee228] */
	M32((DWORD)(m->esi + 0x2340c64u)) = 0xffffffffu;	/* 488e59: mov dword ptr [esi + 0x2340c64], 0xffffffff */
	M32((DWORD)(m->esi + 0x233c9fcu)) = m->ebp;	/* 488e63: mov dword ptr [esi + 0x233c9fc], ebp */
	M32((DWORD)(m->esi + 0x2340c70u)) = m->ebx;	/* 488e69: mov dword ptr [esi + 0x2340c70], ebx */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 488e6f: mov ecx, dword ptr [edx] */
	m->eax = (DWORD)(m->esi + 0x233ca04u);	/* 488e71: lea eax, [esi + 0x233ca04] */
	M32((DWORD)(m->esi + 0x233ca04u)) = m->ecx;	/* 488e77: mov dword ptr [esi + 0x233ca04], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 488e7d: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 488e80: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 488e83: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 488e86: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->esi + 0x22ee234u));	/* 488e89: mov eax, dword ptr [esi + 0x22ee234] */
	M32((DWORD)(m->esi + 0x233ca28u)) = m->eax;	/* 488e8f: mov dword ptr [esi + 0x233ca28], eax */
	m->ecx = M32((DWORD)(m->esi + 0x22ee238u));	/* 488e95: mov ecx, dword ptr [esi + 0x22ee238] */
	M32((DWORD)(m->esi + 0x233ca2cu)) = m->ecx;	/* 488e9b: mov dword ptr [esi + 0x233ca2c], ecx */
	goto L_488fcd;	/* 488ea1: jmp 0x488fcd */
L_488ea6:
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488ea6: cmp eax, edi */
	if (m->zf) goto L_488fcd;	/* 488ea8: je 0x488fcd */
	m->edx = m->eax;	/* 488eae: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 488eb0: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 488eb3: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 488eb5: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 488eb8: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 488eba: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 488ebd: add edx, eax */
	m->edx = (DWORD)(m->esi + m->edx*8 + 0x1eccb48u);	/* 488ebf: lea edx, [esi + edx*8 + 0x1eccb48] */
L_488ec6:
	{ DWORD a_ = M32((DWORD)(m->edx + 0x0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488ec6: cmp dword ptr [edx], ebx */
	if (m->zf) goto L_488ede;	/* 488ec8: je 0x488ede */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 488eca: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 488ecb: add edx, 0x8888 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488ed1: cmp eax, ecx */
	if (m->sf == m->of) goto L_488eef;	/* 488ed3: jge 0x488eef */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488ed5: cmp eax, edi */
	if (!m->zf) goto L_488ec6;	/* 488ed7: jne 0x488ec6 */
	goto L_488fcd;	/* 488ed9: jmp 0x488fcd */
L_488ede:
	M32((DWORD)(m->esi + 0x2340c64u)) = m->eax;	/* 488ede: mov dword ptr [esi + 0x2340c64], eax */
	M32((DWORD)(m->esi + 0x2340c70u)) = m->ebp;	/* 488ee4: mov dword ptr [esi + 0x2340c70], ebp */
	goto L_488fcd;	/* 488eea: jmp 0x488fcd */
L_488eef:
	m->eax = (DWORD)(m->esi + 0x22ee228u);	/* 488eef: lea eax, [esi + 0x22ee228] */
	M32((DWORD)(m->esi + 0x2340c64u)) = 0xffffffffu;	/* 488ef5: mov dword ptr [esi + 0x2340c64], 0xffffffff */
	M32((DWORD)(m->esi + 0x233c9fcu)) = m->ebp;	/* 488eff: mov dword ptr [esi + 0x233c9fc], ebp */
	M32((DWORD)(m->esi + 0x2340c70u)) = m->ebx;	/* 488f05: mov dword ptr [esi + 0x2340c70], ebx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 488f0b: mov edx, dword ptr [eax] */
	m->ecx = (DWORD)(m->esi + 0x233ca04u);	/* 488f0d: lea ecx, [esi + 0x233ca04] */
	M32((DWORD)(m->esi + 0x233ca04u)) = m->edx;	/* 488f13: mov dword ptr [esi + 0x233ca04], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 488f19: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 488f1c: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 488f1f: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 488f22: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->esi + 0x22ee234u));	/* 488f25: mov ecx, dword ptr [esi + 0x22ee234] */
	M32((DWORD)(m->esi + 0x233ca28u)) = m->ecx;	/* 488f2b: mov dword ptr [esi + 0x233ca28], ecx */
	m->edx = M32((DWORD)(m->esi + 0x22ee238u));	/* 488f31: mov edx, dword ptr [esi + 0x22ee238] */
	M32((DWORD)(m->esi + 0x233ca2cu)) = m->edx;	/* 488f37: mov dword ptr [esi + 0x233ca2c], edx */
	goto L_488fcd;	/* 488f3d: jmp 0x488fcd */
L_488f42:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340c70u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488f42: cmp dword ptr [esi + 0x2340c70], ebp */
	if (!m->zf) goto L_488f52;	/* 488f48: jne 0x488f52 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340c64u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488f4a: cmp dword ptr [esi + 0x2340c64], ebp */
	if (m->sf != m->of) goto L_488f6d;	/* 488f50: jl 0x488f6d */
L_488f52:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340c64u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488f52: cmp dword ptr [esi + 0x2340c64], ecx */
	if (m->sf == m->of) goto L_488f6d;	/* 488f58: jge 0x488f6d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc38u)));	/* 488f5a: fld dword ptr [esi + 0x233cc38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa278u)); FPOP();	/* 488f60: fcomp dword ptr [0x4aa278] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488f66: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488f68: test ah, 0x41 */
	if (!m->zf) goto L_488fcd;	/* 488f6b: jne 0x488fcd */
L_488f6d:
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488f6d: cmp ecx, ebp */
	if (m->zf || m->sf != m->of) goto L_488f92;	/* 488f6f: jle 0x488f92 */
	m->edi = M32((DWORD)(0xa1efb8u));	/* 488f71: mov edi, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 488f77: xor edx, edx */
	m->eax = m->edi;	/* 488f79: mov eax, edi */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 488f7b: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 488f80: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 488f87: div ecx */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 488f89: inc edi */
	M32((DWORD)(0xa1efb8u)) = m->edi;	/* 488f8a: mov dword ptr [0xa1efb8], edi */
	goto L_488f94;	/* 488f90: jmp 0x488f94 */
L_488f92:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 488f92: xor edx, edx */
L_488f94:
	m->ecx = m->edx;	/* 488f94: mov ecx, edx */
	M32((DWORD)(m->esi + 0x2340c64u)) = m->edx;	/* 488f96: mov dword ptr [esi + 0x2340c64], edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 488f9c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 488f9f: add ecx, edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 488fa1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 488fa4: add ecx, edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 488fa6: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 488fa9: add ecx, edx */
	{ DWORD a_ = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb78u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488fab: cmp dword ptr [esi + ecx*8 + 0x1eccb78], ebx */
	if (m->zf) goto L_488fc0;	/* 488fb2: je 0x488fc0 */
	M32((DWORD)(m->esi + 0x2340c64u)) = 0xffffffffu;	/* 488fb4: mov dword ptr [esi + 0x2340c64], 0xffffffff */
	goto L_488fcd;	/* 488fbe: jmp 0x488fcd */
L_488fc0:
	M32((DWORD)(m->esi + 0x233cc38u)) = m->ebp;	/* 488fc0: mov dword ptr [esi + 0x233cc38], ebp */
	goto L_488fcd;	/* 488fc6: jmp 0x488fcd */
L_488fc8:
	m->ebx = 0x1u;	/* 488fc8: mov ebx, 1 */
L_488fcd:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234331fu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 488fcd: cmp dword ptr [esi + 0x234331f], ebx */
	if (!m->zf) goto L_488fef;	/* 488fd3: jne 0x488fef */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 488fd5: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = 0xau;	/* 488fdb: mov ecx, 0xa */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 488fe0: inc eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 488fe1: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 488fe2: idiv ecx */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->edx;	/* 488fe4: mov dword ptr [esi + 0x233cc10], edx */
	goto L_489112;	/* 488fea: jmp 0x489112 */
L_488fef:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc3cu)));	/* 488fef: fld dword ptr [esi + 0x233cc3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa47cu)); FPOP();	/* 488ff5: fcomp dword ptr [0x4aa47c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 488ffb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 488ffd: test ah, 0x41 */
	if (!m->zf) goto L_489112;	/* 489000: jne 0x489112 */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 489006: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0x64u;	/* 48900c: mov edi, 0x64 */
	m->edx = m->ecx;	/* 489011: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 489013: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 489019: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 489020: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 489022: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 489024: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 489025: mov dword ptr [0xa1efb8], ecx */
	{ DWORD a_ = m->edx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48902b: cmp edx, 5 */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->edx;	/* 48902e: mov dword ptr [esi + 0x233cc10], edx */
	if (m->sf == m->of) goto L_489047;	/* 489034: jge 0x489047 */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->ebp;	/* 489036: mov dword ptr [esi + 0x233cc10], ebp */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 48903c: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 489042: jmp 0x489112 */
L_489047:
	{ DWORD a_ = m->edx, b_ = 0x23u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489047: cmp edx, 0x23 */
	if (m->sf == m->of) goto L_48905d;	/* 48904a: jge 0x48905d */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->ebx;	/* 48904c: mov dword ptr [esi + 0x233cc10], ebx */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 489052: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 489058: jmp 0x489112 */
L_48905d:
	{ DWORD a_ = m->edx, b_ = 0x2du & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48905d: cmp edx, 0x2d */
	if (m->sf == m->of) goto L_489077;	/* 489060: jge 0x489077 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x2u;	/* 489062: mov dword ptr [esi + 0x233cc10], 2 */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 48906c: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 489072: jmp 0x489112 */
L_489077:
	{ DWORD a_ = m->edx, b_ = 0x32u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489077: cmp edx, 0x32 */
	if (m->sf == m->of) goto L_489091;	/* 48907a: jge 0x489091 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x3u;	/* 48907c: mov dword ptr [esi + 0x233cc10], 3 */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 489086: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 48908c: jmp 0x489112 */
L_489091:
	{ DWORD a_ = m->edx, b_ = 0x37u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489091: cmp edx, 0x37 */
	if (m->sf == m->of) goto L_4890a8;	/* 489094: jge 0x4890a8 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x4u;	/* 489096: mov dword ptr [esi + 0x233cc10], 4 */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 4890a0: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 4890a6: jmp 0x489112 */
L_4890a8:
	{ DWORD a_ = m->edx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4890a8: cmp edx, 0x3c */
	if (m->sf == m->of) goto L_4890bf;	/* 4890ab: jge 0x4890bf */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x5u;	/* 4890ad: mov dword ptr [esi + 0x233cc10], 5 */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 4890b7: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 4890bd: jmp 0x489112 */
L_4890bf:
	{ DWORD a_ = m->edx, b_ = 0x41u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4890bf: cmp edx, 0x41 */
	if (m->sf == m->of) goto L_4890d6;	/* 4890c2: jge 0x4890d6 */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x6u;	/* 4890c4: mov dword ptr [esi + 0x233cc10], 6 */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 4890ce: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 4890d4: jmp 0x489112 */
L_4890d6:
	{ DWORD a_ = m->edx, b_ = 0x46u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4890d6: cmp edx, 0x46 */
	if (m->sf == m->of) goto L_4890ed;	/* 4890d9: jge 0x4890ed */
	M32((DWORD)(m->esi + 0x233cc10u)) = 0x7u;	/* 4890db: mov dword ptr [esi + 0x233cc10], 7 */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 4890e5: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 4890eb: jmp 0x489112 */
L_4890ed:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4890ed: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = 0x4bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4890ef: cmp edx, 0x4b */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 4890f2: setge al */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4890f5: add eax, 8 */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->eax;	/* 4890f8: mov dword ptr [esi + 0x233cc10], eax */
	M32((DWORD)(m->esi + 0x233cc3cu)) = m->ebp;	/* 4890fe: mov dword ptr [esi + 0x233cc3c], ebp */
	goto L_489112;	/* 489104: jmp 0x489112 */
L_489106:
	M32((DWORD)(m->esi + 0x2340c64u)) = 0xffffffffu;	/* 489106: mov dword ptr [esi + 0x2340c64], 0xffffffff */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 489110: xor ebp, ebp */
L_489112:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340c68u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489112: cmp dword ptr [esi + 0x2340c68], ebp */
	if (!m->zf) goto L_48912a;	/* 489118: jne 0x48912a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48911a: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x233cc38u));	/* 48911e: fadd dword ptr [esi + 0x233cc38] */
	MF((DWORD)(m->esi + 0x233cc38u)) = (float)ST(0); FPOP();	/* 489124: fstp dword ptr [esi + 0x233cc38] */
L_48912a:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340c6cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48912a: cmp dword ptr [esi + 0x2340c6c], ebp */
	if (!m->zf) goto L_489142;	/* 489130: jne 0x489142 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 489132: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x233cc3cu));	/* 489136: fadd dword ptr [esi + 0x233cc3c] */
	MF((DWORD)(m->esi + 0x233cc3cu)) = (float)ST(0); FPOP();	/* 48913c: fstp dword ptr [esi + 0x233cc3c] */
L_489142:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 489142: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x2340d2du));	/* 489146: fadd dword ptr [esi + 0x2340d2d] */
	m->ebp = 0x1u;	/* 48914c: mov ebp, 1 */
	MF((DWORD)(m->esi + 0x2340d2du)) = (float)ST(0); FPOP();	/* 489151: fstp dword ptr [esi + 0x2340d2d] */
L_489157:
	m->eax = M32((DWORD)(m->esi + 0x2221f90u));	/* 489157: mov eax, dword ptr [esi + 0x2221f90] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48915d: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48915f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_489193;	/* 489161: jle 0x489193 */
	m->edi = (DWORD)(m->esi + 0x1ed52d8u);	/* 489163: lea edi, [esi + 0x1ed52d8] */
L_489169:
	{ DWORD a_ = M32((DWORD)(m->edi + 0x0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489169: cmp dword ptr [edi], ebp */
	if (!m->zf) goto L_489182;	/* 48916b: jne 0x489182 */
	m->ecx = M32((DWORD)(m->edi + 0xffff7c58u));	/* 48916d: mov ecx, dword ptr [edi - 0x83a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489173: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 489174: push ebx */
	m->ecx = m->esi;	/* 489175: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48917cu; native_call(m, 0x4630c0u);	/* 489177: call 0x4630c0 */
	M32((DWORD)(m->edi + 0x0u)) = 0x0u;	/* 48917c: mov dword ptr [edi], 0 */
L_489182:
	m->eax = M32((DWORD)(m->esi + 0x2221f90u));	/* 489182: mov eax, dword ptr [esi + 0x2221f90] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 489188: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 489189: add edi, 0x8888 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48918f: cmp ebx, eax */
	if (m->sf != m->of) goto L_489169;	/* 489191: jl 0x489169 */
L_489193:
	m->edx = M32((DWORD)(m->esi + 0x44u));	/* 489193: mov edx, dword ptr [esi + 0x44] */
	m->ecx = m->esi;	/* 489196: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 489198: push edx */
	m->esp -= 4; M32(m->esp) = 0x48919eu; native_call(m, 0x462ac0u);	/* 489199: call 0x462ac0 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234328fu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48919e: cmp dword ptr [esi + 0x234328f], ebp */
	if (!m->zf) goto L_4891b0;	/* 4891a4: jne 0x4891b0 */
	M32((DWORD)(m->esi + 0x233cc40u)) = 0x40a00000u;	/* 4891a6: mov dword ptr [esi + 0x233cc40], 0x40a00000 */
L_4891b0:
	m->ecx = M32((DWORD)(m->esi + 0x2340c64u));	/* 4891b0: mov ecx, dword ptr [esi + 0x2340c64] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4891b6: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4891b8: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4891ba: cmp ecx, ebx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 4891bc: setge al */
	M32((DWORD)(m->esi + 0x233c9fcu)) = m->eax;	/* 4891bf: mov dword ptr [esi + 0x233c9fc], eax */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4891c5: sub eax, ebx */
	m->ebp = 0x3f800000u;	/* 4891c7: mov ebp, 0x3f800000 */
	if (m->zf) goto L_4899bf;	/* 4891cc: je 0x4899bf */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4891d2: dec eax */
	if (!m->zf) goto L_489b8a;	/* 4891d3: jne 0x489b8a */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 4891d9: mov eax, dword ptr [esi + 0x233cc10] */
	{ DWORD a_ = M32((DWORD)(m->esi + m->eax*4 + 0x233cb98u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4891df: cmp dword ptr [esi + eax*4 + 0x233cb98], ebx */
	if (!m->zf) goto L_4894d2;	/* 4891e6: jne 0x4894d2 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4891ec: cmp eax, 1 */
	if (m->zf) goto L_4894db;	/* 4891ef: je 0x4894db */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->eax*4 + 0x233cb20u)));	/* 4891f5: fld dword ptr [esi + eax*4 + 0x233cb20] */
	MF((DWORD)(m->esi + 0x233ca28u)) = (float)ST(0);	/* 4891fc: fst dword ptr [esi + 0x233ca28] */
	m->ecx = M32((DWORD)(m->esi + 0x233cc10u));	/* 489202: mov ecx, dword ptr [esi + 0x233cc10] */
	{ DWORD a_ = M32((DWORD)(m->esi + m->ecx*4 + 0x233cbc0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489208: cmp dword ptr [esi + ecx*4 + 0x233cbc0], ebx */
	if (!m->zf) goto L_489237;	/* 48920f: jne 0x489237 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 489211: mov eax, dword ptr [esi + 0x2340c64] */
	m->edx = m->eax;	/* 489217: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489219: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48921c: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48921e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489221: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489223: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489226: add edx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + m->edx*8 + 0x1eccbd0u));	/* 489228: fadd dword ptr [esi + edx*8 + 0x1eccbd0] */
	MF((DWORD)(m->esi + 0x233ca28u)) = (float)ST(0); FPOP();	/* 48922f: fstp dword ptr [esi + 0x233ca28] */
	goto L_489239;	/* 489235: jmp 0x489239 */
L_489237:
	ST(0) = ST(0); FPOP();	/* 489237: fstp st(0) */
L_489239:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 489239: fld dword ptr [esi + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a972cu)); FPOP();	/* 48923f: fcomp dword ptr [0x4a972c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489245: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489247: test ah, 0x41 */
	if (!m->zf) goto L_489256;	/* 48924a: jne 0x489256 */
	M32((DWORD)(m->esi + 0x233ca28u)) = 0x445e8000u;	/* 48924c: mov dword ptr [esi + 0x233ca28], 0x445e8000 */
L_489256:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 489256: fld dword ptr [esi + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9728u)); FPOP();	/* 48925c: fcomp dword ptr [0x4a9728] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489262: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489264: test ah, 1 */
	if (m->zf) goto L_489273;	/* 489267: je 0x489273 */
	M32((DWORD)(m->esi + 0x233ca28u)) = 0xc45e8000u;	/* 489269: mov dword ptr [esi + 0x233ca28], 0xc45e8000 */
L_489273:
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 489273: mov eax, dword ptr [esi + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->eax*4 + 0x233cb48u)));	/* 489279: fld dword ptr [esi + eax*4 + 0x233cb48] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0);	/* 489280: fst dword ptr [esi + 0x233ca2c] */
	m->ecx = M32((DWORD)(m->esi + 0x233cc10u));	/* 489286: mov ecx, dword ptr [esi + 0x233cc10] */
	{ DWORD a_ = M32((DWORD)(m->esi + m->ecx*4 + 0x233cbe8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48928c: cmp dword ptr [esi + ecx*4 + 0x233cbe8], ebx */
	if (!m->zf) goto L_4892bb;	/* 489293: jne 0x4892bb */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 489295: mov eax, dword ptr [esi + 0x2340c64] */
	m->edx = m->eax;	/* 48929b: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48929d: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4892a0: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4892a2: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4892a5: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4892a7: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4892aa: add edx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + m->edx*8 + 0x1eccbd4u));	/* 4892ac: fadd dword ptr [esi + edx*8 + 0x1eccbd4] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 4892b3: fstp dword ptr [esi + 0x233ca2c] */
	goto L_4892bd;	/* 4892b9: jmp 0x4892bd */
L_4892bb:
	ST(0) = ST(0); FPOP();	/* 4892bb: fstp st(0) */
L_4892bd:
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 4892bd: mov eax, dword ptr [esi + 0x2340c64] */
	m->ecx = m->eax;	/* 4892c3: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4892c5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4892c8: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4892ca: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4892cd: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4892cf: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4892d2: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*8 + 0x1ecce58u)));	/* 4892d4: fld dword ptr [esi + ecx*8 + 0x1ecce58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa478u));	/* 4892db: fmul dword ptr [0x4aa478] */
	M32((DWORD)(m->esp + 0x48u)) = 0x0u;	/* 4892e1: mov dword ptr [esp + 0x48], 0 */
	M32((DWORD)(m->esp + 0x50u)) = 0x0u;	/* 4892e9: mov dword ptr [esp + 0x50], 0 */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4892f1: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 4892f5: fld dword ptr [esi + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4892fb: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489300: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489301: push 1 */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 489303: lea ecx, [esp + 0x50] */
	m->esp -= 4; M32(m->esp) = 0x48930cu; native_call(m, 0x4677c0u);	/* 489307: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 48930c: fld dword ptr [esi + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 489312: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489317: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 489318: push 2 */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 48931a: lea ecx, [esp + 0x50] */
	m->esp -= 4; M32(m->esp) = 0x489323u; native_call(m, 0x4677c0u);	/* 48931e: call 0x4677c0 */
	m->edx = M32((DWORD)(m->esi + 0x233cc10u));	/* 489323: mov edx, dword ptr [esi + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->edx*4 + 0x233cb70u)));	/* 489329: fld dword ptr [esi + edx*4 + 0x233cb70] */
	ST(0) = -ST(0);	/* 489330: fchs  */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 489332: fsub dword ptr [0x4aa440] */
	M32((DWORD)(m->esp + 0x74u)) = 0x0u;	/* 489338: mov dword ptr [esp + 0x74], 0 */
	M32((DWORD)(m->esp + 0x78u)) = 0x0u;	/* 489340: mov dword ptr [esp + 0x78], 0 */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0); FPOP();	/* 489348: fstp dword ptr [esp + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 48934c: fld dword ptr [esi + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 489352: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489357: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489358: push 1 */
	m->ecx = (DWORD)(m->esp + 0x7cu);	/* 48935a: lea ecx, [esp + 0x7c] */
	m->esp -= 4; M32(m->esp) = 0x489363u; native_call(m, 0x4677c0u);	/* 48935e: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 489363: fld dword ptr [esi + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 489369: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48936e: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48936f: push 2 */
	m->ecx = (DWORD)(m->esp + 0x7cu);	/* 489371: lea ecx, [esp + 0x7c] */
	m->esp -= 4; M32(m->esp) = 0x48937au; native_call(m, 0x4677c0u);	/* 489375: call 0x4677c0 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 48937a: mov eax, dword ptr [esi + 0x2340c64] */
	m->edi = (DWORD)(m->esi + 0x233ca04u);	/* 489380: lea edi, [esi + 0x233ca04] */
	m->ecx = m->eax;	/* 489386: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 489388: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48938b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48938d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 489390: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 489392: fld dword ptr [esp + 0x48] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 489396: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 489399: add ecx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + m->ecx*8 + 0x1eccbc4u));	/* 48939b: fadd dword ptr [esi + ecx*8 + 0x1eccbc4] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x1eccbc4u);	/* 4893a2: lea eax, [esi + ecx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4893a9: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4893ad: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4893b1: fadd dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4893b4: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 4893b8: fld dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4893bc: fadd dword ptr [eax + 8] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4893bf: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 4893c3: fld dword ptr [esp + 0x74] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 4893c7: fadd dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4893cb: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4893cf: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 4893d3: fadd dword ptr [esp + 0x78] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4893d7: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 4893db: mov dword ptr [esp + 0x10], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4893df: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 4893e3: fld dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x7cu));	/* 4893e7: fadd dword ptr [esp + 0x7c] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4893eb: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4893ef: mov dword ptr [esp + 0x14], eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4893f3: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4893f7: mov ecx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 4893fb: mov dword ptr [esp + 0x18], ecx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 4893ff: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489403: push edi */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 489404: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 489408: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489409: push eax */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 48940a: lea ecx, [esi + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x489415u; native_call(m, 0x471740u);	/* 489410: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 489415: test eax, eax */
	if (!m->zf) goto L_48942f;	/* 489417: jne 0x48942f */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 489419: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48941d: mov eax, dword ptr [esp + 0x14] */
	m->ecx = m->edi;	/* 489421: mov ecx, edi */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 489423: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 489425: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 489429: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 48942c: mov dword ptr [ecx + 8], edx */
L_48942f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 48942f: fld dword ptr [edi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 489431: fsub dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 489435: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 489439: fld dword ptr [edi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 48943c: fsub dword ptr [esp + 0x4c] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 489440: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 489444: mov dword ptr [esp + 0x10], eax */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 489448: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 48944c: fld dword ptr [edi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 48944f: fsub dword ptr [esp + 0x50] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 489453: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 489457: mov dword ptr [esp + 0x14], ecx */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 48945b: lea ecx, [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 48945f: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 489463: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 489467: mov dword ptr [esp + 0x18], edx */
	m->esp -= 4; M32(m->esp) = 0x489470u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 48946b: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa440u)); FPOP();	/* 489470: fcomp dword ptr [0x4aa440] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489476: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489478: test ah, 0x41 */
	if (!m->zf) goto L_4894bf;	/* 48947b: jne 0x4894bf */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 48947d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 489481: fmul dword ptr [0x4aa440] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 489487: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 48948b: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 489491: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 489495: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 489499: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 48949f: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 4894a3: fld dword ptr [edi] */
	ST(0) = ST(0) - ST(1);	/* 4894a5: fsub st(1) */
	MF((DWORD)(m->edi + 0x0u)) = (float)ST(0); FPOP();	/* 4894a7: fstp dword ptr [edi] */
	ST(0) = ST(0); FPOP();	/* 4894a9: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 4894ab: fld dword ptr [edi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 4894ae: fsub dword ptr [esp + 0x58] */
	MF((DWORD)(m->edi + 0x4u)) = (float)ST(0); FPOP();	/* 4894b2: fstp dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 4894b5: fld dword ptr [edi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 4894b8: fsub dword ptr [esp + 0x5c] */
	MF((DWORD)(m->edi + 0x8u)) = (float)ST(0); FPOP();	/* 4894bc: fstp dword ptr [edi + 8] */
L_4894bf:
	m->edi = (DWORD)(m->esi + 0x233ca10u);	/* 4894bf: lea edi, [esi + 0x233ca10] */
	M32((DWORD)(m->edi + 0x0u)) = m->ebx;	/* 4894c5: mov dword ptr [edi], ebx */
	M32((DWORD)(m->edi + 0x4u)) = m->ebx;	/* 4894c7: mov dword ptr [edi + 4], ebx */
	M32((DWORD)(m->edi + 0x8u)) = m->ebp;	/* 4894ca: mov dword ptr [edi + 8], ebp */
	goto L_489b28;	/* 4894cd: jmp 0x489b28 */
L_4894d2:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4894d2: cmp eax, 1 */
	if (!m->zf) goto L_4897f8;	/* 4894d5: jne 0x4897f8 */
L_4894db:
	m->ebp = M32((DWORD)(m->esi + 0x2221f90u));	/* 4894db: mov ebp, dword ptr [esi + 0x2221f90] */
	{ DWORD a_ = m->ebx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4894e1: or ebx, 0xffffffff */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4894e4: xor edi, edi */
	M32((DWORD)(m->esp + 0x28u)) = 0x7f7fffffu;	/* 4894e6: mov dword ptr [esp + 0x28], 0x7f7fffff */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4894ee: test ebp, ebp */
	if (m->zf || m->sf != m->of) goto L_48963f;	/* 4894f0: jle 0x48963f */
	m->edx = (DWORD)(m->esi + 0x1eccbccu);	/* 4894f6: lea edx, [esi + 0x1eccbcc] */
L_4894fc:
	{ DWORD a_ = M32((DWORD)(m->edx + 0xffffffacu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4894fc: cmp dword ptr [edx - 0x54], 1 */
	if (!m->zf) goto L_489590;	/* 489500: jne 0x489590 */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489506: cmp edi, ecx */
	if (m->zf) goto L_489590;	/* 489508: je 0x489590 */
	m->eax = m->ecx;	/* 48950e: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 489510: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 489513: add eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 489515: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 489518: add eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48951a: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48951d: add eax, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->eax*8 + 0x1eccbc4u)));	/* 48951f: fld dword ptr [esi + eax*8 + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0xfffffff8u));	/* 489526: fsub dword ptr [edx - 8] */
	m->eax = (DWORD)(m->esi + m->eax*8 + 0x1eccbc4u);	/* 489529: lea eax, [esi + eax*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 489530: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 489534: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0xfffffffcu));	/* 489537: fsub dword ptr [edx - 4] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 48953a: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 48953e: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x0u));	/* 489541: fsub dword ptr [edx] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 489543: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 489547: mov dword ptr [esp + 0x10], eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 48954b: mov eax, dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 48954f: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 489553: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 489557: fmul dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 48955b: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 48955f: fmul dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 489563: mov dword ptr [esp + 0x14], eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 489567: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 48956b: mov dword ptr [esp + 0x18], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48956f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 489571: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 489575: fmul dword ptr [esp + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 489579: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u));	/* 48957b: fcom dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48957f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489581: test ah, 1 */
	if (m->zf) goto L_48958e;	/* 489584: je 0x48958e */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 489586: fstp dword ptr [esp + 0x28] */
	m->ebx = m->edi;	/* 48958a: mov ebx, edi */
	goto L_489590;	/* 48958c: jmp 0x489590 */
L_48958e:
	ST(0) = ST(0); FPOP();	/* 48958e: fstp st(0) */
L_489590:
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 489590: inc edi */
	{ DWORD a_ = m->edx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489591: add edx, 0x8888 */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489597: cmp edi, ebp */
	if (m->sf != m->of) goto L_4894fc;	/* 489599: jl 0x4894fc */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48959f: test ebx, ebx */
	if (m->sf != m->of) goto L_48963f;	/* 4895a1: jl 0x48963f */
	m->edx = m->ecx;	/* 4895a7: mov edx, ecx */
	m->edi = (DWORD)(m->esi + 0x233cc14u);	/* 4895a9: lea edi, [esi + 0x233cc14] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4895af: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4895b2: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4895b4: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4895b7: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4895b9: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4895bc: add edx, ecx */
	m->ecx = m->ebx;	/* 4895be: mov ecx, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4895c0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4895c3: add ecx, ebx */
	m->eax = (DWORD)(m->esi + m->edx*8 + 0x1eccbc4u);	/* 4895c5: lea eax, [esi + edx*8 + 0x1eccbc4] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4895cc: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4895cf: add ecx, ebx */
	m->edx = m->edi;	/* 4895d1: mov edx, edi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4895d3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4895d6: add ecx, ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*8 + 0x1eccbc4u)));	/* 4895d8: fld dword ptr [esi + ecx*8 + 0x1eccbc4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4895df: fadd dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*8 + 0x1eccbc8u)));	/* 4895e1: fld dword ptr [esi + ecx*8 + 0x1eccbc8] */
	m->ecx = (DWORD)(m->esi + m->ecx*8 + 0x1eccbc4u);	/* 4895e8: lea ecx, [esi + ecx*8 + 0x1eccbc4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4895ef: fadd dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 4895f2: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 4895f6: fld dword ptr [ecx + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4895f9: fadd dword ptr [eax + 8] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 4895fc: fstp dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 489600: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 489606: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 48960a: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 48960e: fmul dword ptr [0x4a942c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 489614: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 489618: mov dword ptr [edx], ecx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 48961a: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 48961e: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 489622: fmul dword ptr [0x4a942c] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 489628: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 48962c: mov dword ptr [edx + 4], ecx */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 48962f: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 489633: mov ecx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 489637: mov dword ptr [edx + 8], ecx */
	goto L_4896f1;	/* 48963a: jmp 0x4896f1 */
L_48963f:
	m->edx = m->ecx;	/* 48963f: mov edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489641: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489644: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489646: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489649: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48964b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48964e: add edx, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->edx*8 + 0x1ecce58u)));	/* 489650: fld dword ptr [esi + edx*8 + 0x1ecce58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 489657: fmul dword ptr [0x4a93d0] */
	m->eax = (DWORD)(m->esi + m->edx*8 + 0x0u);	/* 48965d: lea eax, [esi + edx*8] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 489660: mov dword ptr [esp + 0x10], 0 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 489668: mov dword ptr [esp + 0x14], 0 */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 489670: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1eccbd4u)));	/* 489674: fld dword ptr [eax + 0x1eccbd4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48967a: call 0x49ec14 */
	m->ecx = 0x64u;	/* 48967f: mov ecx, 0x64 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 489684: sub ecx, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489686: push ecx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 489687: push 2 */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 489689: lea ecx, [esp + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x489692u; native_call(m, 0x4677c0u);	/* 48968d: call 0x4677c0 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 489692: mov eax, dword ptr [esi + 0x2340c64] */
	m->edi = (DWORD)(m->esi + 0x233cc14u);	/* 489698: lea edi, [esi + 0x233cc14] */
	m->edx = m->eax;	/* 48969e: mov edx, eax */
	m->ecx = m->edi;	/* 4896a0: mov ecx, edi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4896a2: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4896a5: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4896a7: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4896aa: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4896ac: fld dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4896b0: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4896b3: add edx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + m->edx*8 + 0x1eccbc4u));	/* 4896b5: fadd dword ptr [esi + edx*8 + 0x1eccbc4] */
	m->eax = (DWORD)(m->esi + m->edx*8 + 0x1eccbc4u);	/* 4896bc: lea eax, [esi + edx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4896c3: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4896c7: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4896cb: fadd dword ptr [eax + 4] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4896ce: mov edx, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4896d2: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4896d6: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4896da: fadd dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 4896dd: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4896df: mov edx, dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4896e3: fstp dword ptr [esp + 0x24] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 4896e7: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4896ea: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 4896ee: mov dword ptr [ecx + 8], edx */
L_4896f1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4896f1: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 4896f3: fsub dword ptr [edi] */
	m->ebx = (DWORD)(m->esi + 0x233ca10u);	/* 4896f5: lea ebx, [esi + 0x233ca10] */
	m->ebp = m->ebx;	/* 4896fb: mov ebp, ebx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4896fd: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 489701: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 489704: fsub dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 489707: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 48970b: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 48970e: fsub dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 489711: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 489715: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->ebp + 0x0u)) = m->eax;	/* 489719: mov dword ptr [ebp], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 48971c: mov dword ptr [esp + 0x14], ecx */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 489720: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 489724: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ebp + 0x4u)) = m->ecx;	/* 489728: mov dword ptr [ebp + 4], ecx */
	m->ecx = m->ebx;	/* 48972b: mov ecx, ebx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 48972d: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 489731: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->ebp + 0x8u)) = m->edx;	/* 489735: mov dword ptr [ebp + 8], edx */
	m->esp -= 4; M32(m->esp) = 0x48973du; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 489738: call 0x467760 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 48973d: mov eax, dword ptr [esi + 0x2340c64] */
	m->ecx = m->eax;	/* 489743: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 489745: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 489748: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48974a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48974d: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48974f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 489752: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*8 + 0x1ecce58u)));	/* 489754: fld dword ptr [esi + ecx*8 + 0x1ecce58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 48975b: fmul dword ptr [0x4a9534] */
	{ long double t = ST(0); FPUSH(t); }	/* 489761: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 489763: fmul dword ptr [ebx] */
	MF((DWORD)(m->ebx + 0x0u)) = (float)ST(0); FPOP();	/* 489765: fstp dword ptr [ebx] */
	{ long double t = ST(0); FPUSH(t); }	/* 489767: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 489769: fmul dword ptr [ebx + 4] */
	MF((DWORD)(m->ebx + 0x4u)) = (float)ST(0); FPOP();	/* 48976c: fstp dword ptr [ebx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 48976f: fmul dword ptr [ebx + 8] */
	MF((DWORD)(m->ebx + 0x8u)) = (float)ST(0); FPOP();	/* 489772: fstp dword ptr [ebx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 489775: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 489779: fadd dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 48977b: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 48977f: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 489783: fadd dword ptr [ebx + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 489786: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 48978a: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 48978e: fadd dword ptr [ebx + 8] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 489791: fstp dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa474u));	/* 489795: fsub dword ptr [0x4aa474] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa470u));	/* 48979b: fmul dword ptr [0x4aa470] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4897a1: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4897a6: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4897a7: push 2 */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 4897a9: lea ecx, [esp + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x4897b2u; native_call(m, 0x4677c0u);	/* 4897ad: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4897b2: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 4897b6: fadd dword ptr [edi] */
	m->ebx = (DWORD)(m->esi + 0x233ca04u);	/* 4897b8: lea ebx, [esi + 0x233ca04] */
	m->ebp = 0x3f800000u;	/* 4897be: mov ebp, 0x3f800000 */
	m->edx = m->ebx;	/* 4897c3: mov edx, ebx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4897c5: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4897c9: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 4897cd: fadd dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4897d0: mov eax, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4897d4: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4897d8: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 4897dc: fadd dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4897df: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 4897e3: mov dword ptr [edx], eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4897e5: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4897e9: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 4897ed: mov dword ptr [edx + 4], ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 4897f0: mov dword ptr [edx + 8], eax */
	goto L_489967;	/* 4897f3: jmp 0x489967 */
L_4897f8:
	m->edx = m->ecx;	/* 4897f8: mov edx, ecx */
	m->edi = (DWORD)(m->esi + 0x233cc14u);	/* 4897fa: lea edi, [esi + 0x233cc14] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489800: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489803: add edx, ecx */
	m->ebx = (DWORD)(m->esi + 0x233ca04u);	/* 489805: lea ebx, [esi + 0x233ca04] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48980b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48980e: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489810: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489813: add edx, ecx */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 489815: lea ecx, [esi + 0x1f36c8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->edx*8 + 0x1eccbc4u)));	/* 48981b: fld dword ptr [esi + edx*8 + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 489822: fsub dword ptr [edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->edx*8 + 0x1eccbc8u)));	/* 489824: fld dword ptr [esi + edx*8 + 0x1eccbc8] */
	m->eax = (DWORD)(m->esi + m->edx*8 + 0x1eccbc4u);	/* 48982b: lea eax, [esi + edx*8 + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 489832: fsub dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 489835: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 489839: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 48983c: fsub dword ptr [edi + 8] */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 48983f: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489843: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489844: push edi */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 489845: fstp dword ptr [esp + 0x64] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 489849: push ebx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 48984a: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 489850: fld dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 489854: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 48985a: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 48985e: fld dword ptr [esp + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 489862: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 489868: fstp dword ptr [esp + 0x74] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 48986c: fadd dword ptr [edi] */
	MF((DWORD)(m->edi + 0x0u)) = (float)ST(0); FPOP();	/* 48986e: fstp dword ptr [edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 489870: fld dword ptr [esp + 0x70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 489874: fadd dword ptr [edi + 4] */
	MF((DWORD)(m->edi + 0x4u)) = (float)ST(0); FPOP();	/* 489877: fstp dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 48987a: fld dword ptr [esp + 0x74] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 48987e: fadd dword ptr [edi + 8] */
	MF((DWORD)(m->edi + 0x8u)) = (float)ST(0); FPOP();	/* 489881: fstp dword ptr [edi + 8] */
	m->esp -= 4; M32(m->esp) = 0x489889u; native_call(m, 0x471740u);	/* 489884: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 489889: test eax, eax */
	if (m->zf) goto L_489967;	/* 48988b: je 0x489967 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 489891: mov eax, dword ptr [esi + 0x2340c64] */
	m->ecx = m->eax;	/* 489897: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 489899: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48989c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48989e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4898a1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4898a3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4898a6: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*8 + 0x1ecce58u)));	/* 4898a8: fld dword ptr [esi + ecx*8 + 0x1ecce58] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 4898af: lea eax, [esi + ecx*8] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 4898b2: mov dword ptr [esp + 0x10], 0 */
	ST(0) = -ST(0);	/* 4898ba: fchs  */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4898bc: fstp dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 4898c0: mov dword ptr [esp + 0x14], 0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1eccbd0u)));	/* 4898c8: fld dword ptr [eax + 0x1eccbd0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4898ce: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4898d3: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4898d4: push 1 */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 4898d6: lea ecx, [esp + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x4898dfu; native_call(m, 0x4677c0u);	/* 4898da: call 0x4677c0 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 4898df: mov eax, dword ptr [esi + 0x2340c64] */
	m->edx = m->eax;	/* 4898e5: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4898e7: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4898ea: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4898ec: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4898ef: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4898f1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4898f4: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->edx*8 + 0x1eccbd4u)));	/* 4898f6: fld dword ptr [esi + edx*8 + 0x1eccbd4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4898fd: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489902: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 489903: push 2 */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 489905: lea ecx, [esp + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x48990eu; native_call(m, 0x4677c0u);	/* 489909: call 0x4677c0 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 48990e: mov eax, dword ptr [esi + 0x2340c64] */
	m->edx = m->ebx;	/* 489914: mov edx, ebx */
	m->ecx = m->eax;	/* 489916: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 489918: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48991b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48991d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 489920: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 489922: fld dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 489926: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 489929: add ecx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + m->ecx*8 + 0x1eccbc4u));	/* 48992b: fadd dword ptr [esi + ecx*8 + 0x1eccbc4] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x1eccbc4u);	/* 489932: lea eax, [esi + ecx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 489939: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 48993d: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 489941: fadd dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 489944: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 489948: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 48994c: fadd dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 48994f: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 489953: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 489957: mov dword ptr [edx], eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 489959: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 48995d: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 489961: mov dword ptr [edx + 4], ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 489964: mov dword ptr [edx + 8], eax */
L_489967:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 489967: fld dword ptr [edi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 489969: fsub dword ptr [ebx] */
	m->ecx = (DWORD)(m->esi + 0x233ca10u);	/* 48996b: lea ecx, [esi + 0x233ca10] */
	m->edx = m->ecx;	/* 489971: mov edx, ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 489973: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 489977: fld dword ptr [edi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 48997a: fsub dword ptr [ebx + 4] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 48997d: mov eax, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 489981: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 489985: fld dword ptr [edi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 489988: fsub dword ptr [ebx + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 48998b: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 48998d: mov eax, dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 489991: fstp dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 489995: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 489998: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 48999c: mov dword ptr [edx + 8], eax */
	m->esp -= 4; M32(m->esp) = 0x4899a4u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 48999f: call 0x467760 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4899a4: xor eax, eax */
	M32((DWORD)(m->esi + 0x233ca20u)) = m->ebp;	/* 4899a6: mov dword ptr [esi + 0x233ca20], ebp */
	ST(0) = ST(0); FPOP();	/* 4899ac: fstp st(0) */
	M32((DWORD)(m->esi + 0x233ca1cu)) = m->eax;	/* 4899ae: mov dword ptr [esi + 0x233ca1c], eax */
	M32((DWORD)(m->esi + 0x233ca24u)) = m->eax;	/* 4899b4: mov dword ptr [esi + 0x233ca24], eax */
	goto L_489b8a;	/* 4899ba: jmp 0x489b8a */
L_4899bf:
	m->eax = M32((DWORD)(m->esi + 0x234325fu));	/* 4899bf: mov eax, dword ptr [esi + 0x234325f] */
	m->ecx = (DWORD)(m->esp + 0x13cu);	/* 4899c5: lea ecx, [esp + 0x13c] */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 4899cc: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4899ce: sbb eax, eax */
	m->edx = (DWORD)(m->esp + 0x138u);	/* 4899d0: lea edx, [esp + 0x138] */
	{ DWORD a_ = m->eax, b_ = 0xa0e7d8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4899d7: and eax, 0xa0e7d8 */
	m->edi = (DWORD)(m->esi + 0x233ca04u);	/* 4899dc: lea edi, [esi + 0x233ca04] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4899e2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4899e3: push ecx */
	m->eax = (DWORD)(m->esp + 0x128u);	/* 4899e4: lea eax, [esp + 0x128] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4899eb: push edx */
	m->ecx = (DWORD)(m->esp + 0xe4u);	/* 4899ec: lea ecx, [esp + 0xe4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4899f3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4899f4: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4899f5: push ebx */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 4899f6: lea edx, [esp + 0x54] */
	{ DWORD v_ = 0x43fa0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4899fa: push 0x43fa0000 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4899ff: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489a00: push edi */
	{ DWORD v_ = 0x43fa0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 489a01: push 0x43fa0000 */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 489a06: lea ecx, [esi + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x489a11u; native_call(m, 0x471400u);	/* 489a0c: call 0x471400 */
	m->edx = M32((DWORD)(m->esp + 0xd8u));	/* 489a11: mov edx, dword ptr [esp + 0xd8] */
	m->ecx = m->edi;	/* 489a18: mov ecx, edi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489a1a: cmp eax, 1 */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 489a1d: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0xdcu));	/* 489a1f: mov edx, dword ptr [esp + 0xdc] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 489a26: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0xe0u));	/* 489a29: mov edx, dword ptr [esp + 0xe0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 489a30: mov dword ptr [ecx + 8], edx */
	if (!m->zf) goto L_489a66;	/* 489a33: jne 0x489a66 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x120u)));	/* 489a35: fld dword ptr [esp + 0x120] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 489a3c: fadd dword ptr [edi] */
	MF((DWORD)(m->edi + 0x0u)) = (float)ST(0); FPOP();	/* 489a3e: fstp dword ptr [edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x128u)));	/* 489a40: fld dword ptr [esp + 0x128] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x233ca0cu));	/* 489a47: fadd dword ptr [esi + 0x233ca0c] */
	MF((DWORD)(m->esi + 0x233ca0cu)) = (float)ST(0); FPOP();	/* 489a4d: fstp dword ptr [esi + 0x233ca0c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x124u)));	/* 489a53: fld dword ptr [esp + 0x124] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x233ca08u));	/* 489a5a: fadd dword ptr [esi + 0x233ca08] */
	MF((DWORD)(m->esi + 0x233ca08u)) = (float)ST(0); FPOP();	/* 489a60: fstp dword ptr [esi + 0x233ca08] */
L_489a66:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 489a66: fld dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xbe2fccu)); FPOP();	/* 489a68: fcomp dword ptr [esi + 0xbe2fcc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489a6e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489a70: test ah, 1 */
	if (m->zf) goto L_489a7f;	/* 489a73: je 0x489a7f */
	m->eax = M32((DWORD)(m->esi + 0xbe2fccu));	/* 489a75: mov eax, dword ptr [esi + 0xbe2fcc] */
	M32((DWORD)(m->edi + 0x0u)) = m->eax;	/* 489a7b: mov dword ptr [edi], eax */
	goto L_489a96;	/* 489a7d: jmp 0x489a96 */
L_489a7f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 489a7f: fld dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xbe2fd8u)); FPOP();	/* 489a81: fcomp dword ptr [esi + 0xbe2fd8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489a87: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489a89: test ah, 0x41 */
	if (!m->zf) goto L_489a96;	/* 489a8c: jne 0x489a96 */
	m->ecx = M32((DWORD)(m->esi + 0xbe2fd8u));	/* 489a8e: mov ecx, dword ptr [esi + 0xbe2fd8] */
	M32((DWORD)(m->edi + 0x0u)) = m->ecx;	/* 489a94: mov dword ptr [edi], ecx */
L_489a96:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca08u)));	/* 489a96: fld dword ptr [esi + 0x233ca08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xbe2fd0u)); FPOP();	/* 489a9c: fcomp dword ptr [esi + 0xbe2fd0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489aa2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489aa4: test ah, 1 */
	if (m->zf) goto L_489ab7;	/* 489aa7: je 0x489ab7 */
	m->edx = M32((DWORD)(m->esi + 0xbe2fd0u));	/* 489aa9: mov edx, dword ptr [esi + 0xbe2fd0] */
	M32((DWORD)(m->esi + 0x233ca08u)) = m->edx;	/* 489aaf: mov dword ptr [esi + 0x233ca08], edx */
	goto L_489ad6;	/* 489ab5: jmp 0x489ad6 */
L_489ab7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca08u)));	/* 489ab7: fld dword ptr [esi + 0x233ca08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xbe2fdcu)); FPOP();	/* 489abd: fcomp dword ptr [esi + 0xbe2fdc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489ac3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489ac5: test ah, 0x41 */
	if (!m->zf) goto L_489ad6;	/* 489ac8: jne 0x489ad6 */
	m->eax = M32((DWORD)(m->esi + 0xbe2fdcu));	/* 489aca: mov eax, dword ptr [esi + 0xbe2fdc] */
	M32((DWORD)(m->esi + 0x233ca08u)) = m->eax;	/* 489ad0: mov dword ptr [esi + 0x233ca08], eax */
L_489ad6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca0cu)));	/* 489ad6: fld dword ptr [esi + 0x233ca0c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xbe2fd4u)); FPOP();	/* 489adc: fcomp dword ptr [esi + 0xbe2fd4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489ae2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489ae4: test ah, 1 */
	if (m->zf) goto L_489af7;	/* 489ae7: je 0x489af7 */
	m->ecx = M32((DWORD)(m->esi + 0xbe2fd4u));	/* 489ae9: mov ecx, dword ptr [esi + 0xbe2fd4] */
	M32((DWORD)(m->esi + 0x233ca0cu)) = m->ecx;	/* 489aef: mov dword ptr [esi + 0x233ca0c], ecx */
	goto L_489b16;	/* 489af5: jmp 0x489b16 */
L_489af7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca0cu)));	/* 489af7: fld dword ptr [esi + 0x233ca0c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0xbe2fe0u)); FPOP();	/* 489afd: fcomp dword ptr [esi + 0xbe2fe0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 489b03: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 489b05: test ah, 0x41 */
	if (!m->zf) goto L_489b16;	/* 489b08: jne 0x489b16 */
	m->edx = M32((DWORD)(m->esi + 0xbe2fe0u));	/* 489b0a: mov edx, dword ptr [esi + 0xbe2fe0] */
	M32((DWORD)(m->esi + 0x233ca0cu)) = m->edx;	/* 489b10: mov dword ptr [esi + 0x233ca0c], edx */
L_489b16:
	m->edi = (DWORD)(m->esi + 0x233ca10u);	/* 489b16: lea edi, [esi + 0x233ca10] */
	M32((DWORD)(m->edi + 0x0u)) = m->ebx;	/* 489b1c: mov dword ptr [edi], ebx */
	M32((DWORD)(m->edi + 0x4u)) = m->ebx;	/* 489b1e: mov dword ptr [edi + 4], ebx */
	M32((DWORD)(m->edi + 0x8u)) = 0xbf800000u;	/* 489b21: mov dword ptr [edi + 8], 0xbf800000 */
L_489b28:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 489b28: fld dword ptr [esi + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 489b2e: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489b33: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489b34: push 1 */
	m->ecx = m->edi;	/* 489b36: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x489b3du; native_call(m, 0x4677c0u);	/* 489b38: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 489b3d: fld dword ptr [esi + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 489b43: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489b48: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 489b49: push 2 */
	m->ecx = m->edi;	/* 489b4b: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x489b52u; native_call(m, 0x4677c0u);	/* 489b4d: call 0x4677c0 */
	m->edi = (DWORD)(m->esi + 0x233ca1cu);	/* 489b52: lea edi, [esi + 0x233ca1c] */
	M32((DWORD)(m->edi + 0x0u)) = m->ebx;	/* 489b58: mov dword ptr [edi], ebx */
	M32((DWORD)(m->edi + 0x4u)) = m->ebp;	/* 489b5a: mov dword ptr [edi + 4], ebp */
	M32((DWORD)(m->edi + 0x8u)) = m->ebx;	/* 489b5d: mov dword ptr [edi + 8], ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 489b60: fld dword ptr [esi + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 489b66: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489b6b: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489b6c: push 1 */
	m->ecx = m->edi;	/* 489b6e: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x489b75u; native_call(m, 0x4677c0u);	/* 489b70: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 489b75: fld dword ptr [esi + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 489b7b: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489b80: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 489b81: push 2 */
	m->ecx = m->edi;	/* 489b83: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x489b8au; native_call(m, 0x4677c0u);	/* 489b85: call 0x4677c0 */
L_489b8a:
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 489b8a: mov eax, dword ptr [esi + 0x44] */
	m->ebx = (DWORD)(m->esi + 0x1f36c8u);	/* 489b8d: lea ebx, [esi + 0x1f36c8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489b93: push eax */
	m->esp -= 4; M32(m->esp) = 0x489b99u; { long double r_ = native_call_fp(m, 0x468700u); FPUSH(r_); }	/* 489b94: call 0x468700 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489b99: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 489b9a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x489ba2u; { long double r_ = native_call_fp(m, 0x4686f0u); FPUSH(r_); }	/* 489b9d: call 0x4686f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489ba2: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 489ba3: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x489babu; native_call(m, 0x4685c0u);	/* 489ba6: call 0x4685c0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489bab: push eax */
	m->esp -= 4; M32(m->esp) = 0x489bb1u; native_call(m, 0x4685b0u);	/* 489bac: call 0x4685b0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489bb1: push eax */
	m->esp -= 4; M32(m->esp) = 0x489bb7u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 489bb2: call 0x4686d0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489bb7: push ecx */
	m->ecx = (DWORD)(m->esi + 0x233ca1cu);	/* 489bb8: lea ecx, [esi + 0x233ca1c] */
	m->edx = (DWORD)(m->esi + 0x233ca10u);	/* 489bbe: lea edx, [esi + 0x233ca10] */
	m->eax = (DWORD)(m->esi + 0x233ca04u);	/* 489bc4: lea eax, [esi + 0x233ca04] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 489bca: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489bcd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 489bce: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489bcf: push eax */
	m->ecx = m->ebx;	/* 489bd0: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x489bd7u; native_call(m, 0x4729b0u);	/* 489bd2: call 0x4729b0 */
	m->ecx = M32((DWORD)(m->esi + 0x233cc28u));	/* 489bd7: mov ecx, dword ptr [esi + 0x233cc28] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 489bdd: inc ecx */
	M32((DWORD)(m->esi + 0x233cc28u)) = m->ecx;	/* 489bde: mov dword ptr [esi + 0x233cc28], ecx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 489be4: mov ecx, dword ptr [0xa0e010] */
	m->esp -= 4; M32(m->esp) = 0x489befu; native_call(m, 0x456b50u);	/* 489bea: call 0x456b50 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xbe16f8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489bef: cmp dword ptr [esi + 0xbe16f8], 1 */
	if (!m->zf) goto L_489c28;	/* 489bf6: jne 0x489c28 */
	m->ecx = M32((DWORD)(m->esi + 0xbe1704u));	/* 489bf8: mov ecx, dword ptr [esi + 0xbe1704] */
	m->edx = M32((DWORD)(m->esi + 0xbe1700u));	/* 489bfe: mov edx, dword ptr [esi + 0xbe1700] */
	m->eax = M32((DWORD)(m->esi + 0xbe16fcu));	/* 489c04: mov eax, dword ptr [esi + 0xbe16fc] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 489c0a: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489c0b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 489c0c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489c0d: push eax */
	m->esp -= 4; M32(m->esp) = 0x489c14u; native_call(m, M32(0x4a91e0u));	/* 489c0e: call dword ptr [0x4a91e0] */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 489c14: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 489c19: push 0 */
	m->esp -= 4; M32(m->esp) = 0x489c21u; native_call(m, M32(0x4a91dcu));	/* 489c1b: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x4100u; m->esp -= 4; M32(m->esp) = v_; }	/* 489c21: push 0x4100 */
	goto L_489c3a;	/* 489c26: jmp 0x489c3a */
L_489c28:
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 489c28: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 489c2d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x489c35u; native_call(m, M32(0x4a91dcu));	/* 489c2f: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 489c35: push 0x100 */
L_489c3a:
	m->esp -= 4; M32(m->esp) = 0x489c40u; native_call(m, M32(0x4a91e8u));	/* 489c3a: call dword ptr [0x4a91e8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 489c40: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489c41: push 1 */
	m->esp -= 4; M32(m->esp) = 0x489c48u; native_call(m, 0x4685f0u);	/* 489c43: call 0x4685f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 489c48: add esp, 8 */
	m->ecx = (DWORD)(m->esi + 0x22e7068u);	/* 489c4b: lea ecx, [esi + 0x22e7068] */
	m->edi = (DWORD)(m->esi + 0x74u);	/* 489c51: lea edi, [esi + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489c54: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 489c55: push 0 */
	m->ecx = m->edi;	/* 489c57: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x489c5eu; native_call(m, 0x4841f0u);	/* 489c59: call 0x4841f0 */
	m->ecx = m->edi;	/* 489c5e: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x489c65u; native_call(m, 0x484260u);	/* 489c60: call 0x484260 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x233c9fcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489c65: cmp dword ptr [esi + 0x233c9fc], 1 */
	if (!m->zf) goto L_489c9d;	/* 489c6c: jne 0x489c9d */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x233cc10u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489c6e: cmp dword ptr [esi + 0x233cc10], 2 */
	if (!m->zf) goto L_489c9d;	/* 489c75: jne 0x489c9d */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 489c77: mov eax, dword ptr [esi + 0x2340c64] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 489c7d: test eax, eax */
	if (m->sf != m->of) goto L_489c9d;	/* 489c7f: jl 0x489c9d */
	m->edx = m->eax;	/* 489c81: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489c83: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489c86: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489c88: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489c8b: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 489c8d: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 489c90: add edx, eax */
	M32((DWORD)(m->esi + m->edx*8 + 0x1eccfc0u)) = 0x1u;	/* 489c92: mov dword ptr [esi + edx*8 + 0x1eccfc0], 1 */
L_489c9d:
	m->esp -= 4; M32(m->esp) = 0x489ca2u; { long double r_ = native_call_fp(m, 0x468700u); FPUSH(r_); }	/* 489c9d: call 0x468700 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489ca2: push ecx */
	m->ecx = m->ebx;	/* 489ca3: mov ecx, ebx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 489ca5: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x489cadu; native_call(m, 0x496f20u);	/* 489ca8: call 0x496f20 */
	m->esp -= 4; M32(m->esp) = 0x489cb2u; { long double r_ = native_call_fp(m, 0x468700u); FPUSH(r_); }	/* 489cad: call 0x468700 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489cb2: push ecx */
	m->ecx = m->ebx;	/* 489cb3: mov ecx, ebx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 489cb5: fstp dword ptr [esp] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489cb8: push edi */
	m->esp -= 4; M32(m->esp) = 0x489cbeu; native_call(m, 0x497d20u);	/* 489cb9: call 0x497d20 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489cbe: push edi */
	m->ecx = m->ebx;	/* 489cbf: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x489cc6u; native_call(m, 0x490da0u);	/* 489cc1: call 0x490da0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 489cc6: push -1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489cc8: push edi */
	m->ecx = m->ebx;	/* 489cc9: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x489cd0u; native_call(m, 0x45e170u);	/* 489ccb: call 0x45e170 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489cd0: push edi */
	m->ecx = m->ebx;	/* 489cd1: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x489cd8u; native_call(m, 0x47d060u);	/* 489cd3: call 0x47d060 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489cd8: push edi */
	m->ecx = m->ebx;	/* 489cd9: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x489ce0u; native_call(m, 0x479af0u);	/* 489cdb: call 0x479af0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 489ce0: push edi */
	m->ecx = m->ebx;	/* 489ce1: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x489ce8u; native_call(m, 0x48f970u);	/* 489ce3: call 0x48f970 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340cd4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489ce8: cmp dword ptr [esi + 0x2340cd4], 1 */
	if (!m->zf) goto L_48a11d;	/* 489cef: jne 0x48a11d */
	m->eax = M32((DWORD)(m->esi + 0xbcb6c8u));	/* 489cf5: mov eax, dword ptr [esi + 0xbcb6c8] */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 489cfb: mov dword ptr [esp + 0x28], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 489d03: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48a11d;	/* 489d05: jle 0x48a11d */
	m->ebp = (DWORD)(m->esi + 0xbc06d8u);	/* 489d0b: lea ebp, [esi + 0xbc06d8] */
L_489d11:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xfffffff4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 489d11: cmp dword ptr [ebp - 0xc], 1 */
	if (!m->zf) goto L_48a103;	/* 489d15: jne 0x48a103 */
	m->eax = m->ebp;	/* 489d1b: mov eax, ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489d1d: push 1 */
	M32((DWORD)(m->esp + 0x14u)) = 0x42c80000u;	/* 489d1f: mov dword ptr [esp + 0x14], 0x42c80000 */
	M32((DWORD)(m->esp + 0x18u)) = 0x42c80000u;	/* 489d27: mov dword ptr [esp + 0x18], 0x42c80000 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 489d2f: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = 0x42c80000u;	/* 489d31: mov dword ptr [esp + 0x1c], 0x42c80000 */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 489d39: mov dword ptr [esp + 0x30], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 489d3d: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489d41: fadd dword ptr [0x4a93f4] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 489d47: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 489d4a: mov dword ptr [esp + 0x34], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 489d4e: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 489d52: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489d56: fadd dword ptr [0x4a93f4] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 489d5c: mov eax, dword ptr [eax + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 489d5f: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 489d63: mov dword ptr [esp + 0x38], eax */
	M32((DWORD)(m->esp + 0xf4u)) = m->ecx;	/* 489d67: mov dword ptr [esp + 0xf4], ecx */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 489d6e: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 489d72: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489d76: fadd dword ptr [0x4a93f4] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 489d7c: mov edx, dword ptr [esp + 0x24] */
	m->ecx = (DWORD)(m->esp + 0xf4u);	/* 489d80: lea ecx, [esp + 0xf4] */
	M32((DWORD)(m->esp + 0xf8u)) = m->edx;	/* 489d87: mov dword ptr [esp + 0xf8], edx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 489d8e: lea edx, [esp + 0x30] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 489d92: fstp dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 489d96: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489d9a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 489d9b: push edx */
	{ DWORD v_ = 0xa1f208u; m->esp -= 4; M32(m->esp) = v_; }	/* 489d9c: push 0xa1f208 */
	m->ecx = m->edi;	/* 489da1: mov ecx, edi */
	M32((DWORD)(m->esp + 0x108u)) = m->eax;	/* 489da3: mov dword ptr [esp + 0x108], eax */
	m->esp -= 4; M32(m->esp) = 0x489dafu; native_call(m, 0x485120u);	/* 489daa: call 0x485120 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 489daf: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 489db3: fsub dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489db7: push 1 */
	MF((DWORD)(m->esp + 0xb8u)) = (float)ST(0); FPOP();	/* 489db9: fstp dword ptr [esp + 0xb8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 489dc0: fld dword ptr [esp + 0x34] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 489dc4: fsub dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0xb8u));	/* 489dc8: mov eax, dword ptr [esp + 0xb8] */
	M32((DWORD)(m->esp + 0xc4u)) = m->eax;	/* 489dcf: mov dword ptr [esp + 0xc4], eax */
	m->eax = (DWORD)(m->esp + 0xc4u);	/* 489dd6: lea eax, [esp + 0xc4] */
	MF((DWORD)(m->esp + 0xbcu)) = (float)ST(0); FPOP();	/* 489ddd: fstp dword ptr [esp + 0xbc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 489de4: fld dword ptr [esp + 0x38] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 489de8: fsub dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0xbcu));	/* 489dec: mov ecx, dword ptr [esp + 0xbc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489df3: push eax */
	M32((DWORD)(m->esp + 0xccu)) = m->ecx;	/* 489df4: mov dword ptr [esp + 0xcc], ecx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 489dfb: lea ecx, [esp + 0x34] */
	MF((DWORD)(m->esp + 0xc4u)) = (float)ST(0); FPOP();	/* 489dff: fstp dword ptr [esp + 0xc4] */
	m->edx = M32((DWORD)(m->esp + 0xc4u));	/* 489e06: mov edx, dword ptr [esp + 0xc4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489e0d: push ecx */
	{ DWORD v_ = 0xa1f208u; m->esp -= 4; M32(m->esp) = v_; }	/* 489e0e: push 0xa1f208 */
	m->ecx = m->edi;	/* 489e13: mov ecx, edi */
	M32((DWORD)(m->esp + 0xd8u)) = m->edx;	/* 489e15: mov dword ptr [esp + 0xd8], edx */
	m->esp -= 4; M32(m->esp) = 0x489e21u; native_call(m, 0x485120u);	/* 489e1c: call 0x485120 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 489e21: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489e25: fadd dword ptr [0x4a93f4] */
	M32((DWORD)(m->esp + 0x10u)) = 0x42c80000u;	/* 489e2b: mov dword ptr [esp + 0x10], 0x42c80000 */
	M32((DWORD)(m->esp + 0x14u)) = 0xc2c80000u;	/* 489e33: mov dword ptr [esp + 0x14], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x18u)) = 0x42c80000u;	/* 489e3b: mov dword ptr [esp + 0x18], 0x42c80000 */
	MF((DWORD)(m->esp + 0x90u)) = (float)ST(0); FPOP();	/* 489e43: fstp dword ptr [esp + 0x90] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 489e4a: fld dword ptr [esp + 0x30] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489e4e: fsub dword ptr [0x4a93f4] */
	m->edx = M32((DWORD)(m->esp + 0x90u));	/* 489e54: mov edx, dword ptr [esp + 0x90] */
	M32((DWORD)(m->esp + 0x108u)) = m->edx;	/* 489e5b: mov dword ptr [esp + 0x108], edx */
	MF((DWORD)(m->esp + 0x94u)) = (float)ST(0); FPOP();	/* 489e62: fstp dword ptr [esp + 0x94] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 489e69: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489e6d: fadd dword ptr [0x4a93f4] */
	m->eax = M32((DWORD)(m->esp + 0x94u));	/* 489e73: mov eax, dword ptr [esp + 0x94] */
	M32((DWORD)(m->esp + 0x10cu)) = m->eax;	/* 489e7a: mov dword ptr [esp + 0x10c], eax */
	MF((DWORD)(m->esp + 0x98u)) = (float)ST(0); FPOP();	/* 489e81: fstp dword ptr [esp + 0x98] */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 489e88: mov ecx, dword ptr [esp + 0x98] */
	m->edx = (DWORD)(m->esp + 0x108u);	/* 489e8f: lea edx, [esp + 0x108] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489e96: push 1 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 489e98: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 489e9c: push edx */
	M32((DWORD)(m->esp + 0x118u)) = m->ecx;	/* 489e9d: mov dword ptr [esp + 0x118], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489ea4: push eax */
	{ DWORD v_ = 0xa1f208u; m->esp -= 4; M32(m->esp) = v_; }	/* 489ea5: push 0xa1f208 */
	m->ecx = m->edi;	/* 489eaa: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x489eb1u; native_call(m, 0x485120u);	/* 489eac: call 0x485120 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 489eb1: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 489eb5: fsub dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489eb9: push 1 */
	MF((DWORD)(m->esp + 0xacu)) = (float)ST(0); FPOP();	/* 489ebb: fstp dword ptr [esp + 0xac] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 489ec2: fld dword ptr [esp + 0x34] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 489ec6: fsub dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 489eca: mov ecx, dword ptr [esp + 0xac] */
	M32((DWORD)(m->esp + 0x130u)) = m->ecx;	/* 489ed1: mov dword ptr [esp + 0x130], ecx */
	m->ecx = (DWORD)(m->esp + 0x130u);	/* 489ed8: lea ecx, [esp + 0x130] */
	MF((DWORD)(m->esp + 0xb0u)) = (float)ST(0); FPOP();	/* 489edf: fstp dword ptr [esp + 0xb0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 489ee6: fld dword ptr [esp + 0x38] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 489eea: fsub dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0xb0u));	/* 489eee: mov edx, dword ptr [esp + 0xb0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489ef5: push ecx */
	M32((DWORD)(m->esp + 0x138u)) = m->edx;	/* 489ef6: mov dword ptr [esp + 0x138], edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 489efd: lea edx, [esp + 0x34] */
	MF((DWORD)(m->esp + 0xb8u)) = (float)ST(0); FPOP();	/* 489f01: fstp dword ptr [esp + 0xb8] */
	m->eax = M32((DWORD)(m->esp + 0xb8u));	/* 489f08: mov eax, dword ptr [esp + 0xb8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 489f0f: push edx */
	{ DWORD v_ = 0xa1f208u; m->esp -= 4; M32(m->esp) = v_; }	/* 489f10: push 0xa1f208 */
	m->ecx = m->edi;	/* 489f15: mov ecx, edi */
	M32((DWORD)(m->esp + 0x144u)) = m->eax;	/* 489f17: mov dword ptr [esp + 0x144], eax */
	m->esp -= 4; M32(m->esp) = 0x489f23u; native_call(m, 0x485120u);	/* 489f1e: call 0x485120 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 489f23: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489f27: fsub dword ptr [0x4a93f4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 489f2d: push 1 */
	M32((DWORD)(m->esp + 0x14u)) = 0xc2c80000u;	/* 489f2f: mov dword ptr [esp + 0x14], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x18u)) = 0x42c80000u;	/* 489f37: mov dword ptr [esp + 0x18], 0x42c80000 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x42c80000u;	/* 489f3f: mov dword ptr [esp + 0x1c], 0x42c80000 */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 489f47: fstp dword ptr [esp + 0x84] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 489f4e: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489f52: fadd dword ptr [0x4a93f4] */
	m->eax = M32((DWORD)(m->esp + 0x84u));	/* 489f58: mov eax, dword ptr [esp + 0x84] */
	M32((DWORD)(m->esp + 0xd0u)) = m->eax;	/* 489f5f: mov dword ptr [esp + 0xd0], eax */
	m->eax = (DWORD)(m->esp + 0xd0u);	/* 489f66: lea eax, [esp + 0xd0] */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 489f6d: fstp dword ptr [esp + 0x88] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 489f74: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 489f78: fadd dword ptr [0x4a93f4] */
	m->ecx = M32((DWORD)(m->esp + 0x88u));	/* 489f7e: mov ecx, dword ptr [esp + 0x88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 489f85: push eax */
	M32((DWORD)(m->esp + 0xd8u)) = m->ecx;	/* 489f86: mov dword ptr [esp + 0xd8], ecx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 489f8d: lea ecx, [esp + 0x34] */
	MF((DWORD)(m->esp + 0x90u)) = (float)ST(0); FPOP();	/* 489f91: fstp dword ptr [esp + 0x90] */
	m->edx = M32((DWORD)(m->esp + 0x90u));	/* 489f98: mov edx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 489f9f: push ecx */
	{ DWORD v_ = 0xa1f208u; m->esp -= 4; M32(m->esp) = v_; }	/* 489fa0: push 0xa1f208 */
	m->ecx = m->edi;	/* 489fa5: mov ecx, edi */
	M32((DWORD)(m->esp + 0xe4u)) = m->edx;	/* 489fa7: mov dword ptr [esp + 0xe4], edx */
	m->esp -= 4; M32(m->esp) = 0x489fb3u; native_call(m, 0x485120u);	/* 489fae: call 0x485120 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 489fb3: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 489fb7: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x9cu)) = (float)ST(0); FPOP();	/* 489fbb: fstp dword ptr [esp + 0x9c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 489fc2: fld dword ptr [esp + 0x30] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 489fc6: fsub dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x9cu));	/* 489fca: mov edx, dword ptr [esp + 0x9c] */
	M32((DWORD)(m->esp + 0xe4u)) = m->edx;	/* 489fd1: mov dword ptr [esp + 0xe4], edx */
	MF((DWORD)(m->esp + 0xa0u)) = (float)ST(0); FPOP();	/* 489fd8: fstp dword ptr [esp + 0xa0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 489fdf: fld dword ptr [esp + 0x34] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 489fe3: fsub dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0xa0u));	/* 489fe7: mov eax, dword ptr [esp + 0xa0] */
	M32((DWORD)(m->esp + 0xe8u)) = m->eax;	/* 489fee: mov dword ptr [esp + 0xe8], eax */
	MF((DWORD)(m->esp + 0xa4u)) = (float)ST(0); FPOP();	/* 489ff5: fstp dword ptr [esp + 0xa4] */
	m->ecx = M32((DWORD)(m->esp + 0xa4u));	/* 489ffc: mov ecx, dword ptr [esp + 0xa4] */
	m->edx = (DWORD)(m->esp + 0xe4u);	/* 48a003: lea edx, [esp + 0xe4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a00a: push 1 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 48a00c: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a010: push edx */
	M32((DWORD)(m->esp + 0xf4u)) = m->ecx;	/* 48a011: mov dword ptr [esp + 0xf4], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a018: push eax */
	{ DWORD v_ = 0xa1f208u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a019: push 0xa1f208 */
	m->ecx = m->edi;	/* 48a01e: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x48a025u; native_call(m, 0x485120u);	/* 48a020: call 0x485120 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 48a025: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 48a029: fsub dword ptr [0x4a93f4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a02f: push 1 */
	M32((DWORD)(m->esp + 0x14u)) = 0xc2c80000u;	/* 48a031: mov dword ptr [esp + 0x14], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x18u)) = 0xc2c80000u;	/* 48a039: mov dword ptr [esp + 0x18], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x42c80000u;	/* 48a041: mov dword ptr [esp + 0x1c], 0x42c80000 */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 48a049: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 48a04d: fld dword ptr [esp + 0x34] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 48a051: fsub dword ptr [0x4a93f4] */
	m->ecx = M32((DWORD)(m->esp + 0x64u));	/* 48a057: mov ecx, dword ptr [esp + 0x64] */
	M32((DWORD)(m->esp + 0x100u)) = m->ecx;	/* 48a05b: mov dword ptr [esp + 0x100], ecx */
	m->ecx = (DWORD)(m->esp + 0x100u);	/* 48a062: lea ecx, [esp + 0x100] */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 48a069: fstp dword ptr [esp + 0x68] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48a06d: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 48a071: fadd dword ptr [0x4a93f4] */
	m->edx = M32((DWORD)(m->esp + 0x68u));	/* 48a077: mov edx, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a07b: push ecx */
	M32((DWORD)(m->esp + 0x108u)) = m->edx;	/* 48a07c: mov dword ptr [esp + 0x108], edx */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 48a083: lea edx, [esp + 0x34] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 48a087: fstp dword ptr [esp + 0x70] */
	m->eax = M32((DWORD)(m->esp + 0x70u));	/* 48a08b: mov eax, dword ptr [esp + 0x70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a08f: push edx */
	{ DWORD v_ = 0xa1f208u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a090: push 0xa1f208 */
	m->ecx = m->edi;	/* 48a095: mov ecx, edi */
	M32((DWORD)(m->esp + 0x114u)) = m->eax;	/* 48a097: mov dword ptr [esp + 0x114], eax */
	m->esp -= 4; M32(m->esp) = 0x48a0a3u; native_call(m, 0x485120u);	/* 48a09e: call 0x485120 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 48a0a3: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48a0a7: fsub dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a0ab: push 1 */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 48a0ad: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 48a0b1: fld dword ptr [esp + 0x34] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 48a0b5: fsub dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 48a0b9: mov eax, dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0x118u)) = m->eax;	/* 48a0bd: mov dword ptr [esp + 0x118], eax */
	m->eax = (DWORD)(m->esp + 0x118u);	/* 48a0c4: lea eax, [esp + 0x118] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 48a0cb: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48a0cf: fld dword ptr [esp + 0x38] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 48a0d3: fsub dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 48a0d7: mov ecx, dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a0db: push eax */
	M32((DWORD)(m->esp + 0x120u)) = m->ecx;	/* 48a0dc: mov dword ptr [esp + 0x120], ecx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 48a0e3: lea ecx, [esp + 0x34] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 48a0e7: fstp dword ptr [esp + 0x64] */
	m->edx = M32((DWORD)(m->esp + 0x64u));	/* 48a0eb: mov edx, dword ptr [esp + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a0ef: push ecx */
	{ DWORD v_ = 0xa1f208u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a0f0: push 0xa1f208 */
	m->ecx = m->edi;	/* 48a0f5: mov ecx, edi */
	M32((DWORD)(m->esp + 0x12cu)) = m->edx;	/* 48a0f7: mov dword ptr [esp + 0x12c], edx */
	m->esp -= 4; M32(m->esp) = 0x48a103u; native_call(m, 0x485120u);	/* 48a0fe: call 0x485120 */
L_48a103:
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 48a103: mov eax, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esi + 0xbcb6c8u));	/* 48a107: mov ecx, dword ptr [esi + 0xbcb6c8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48a10d: inc eax */
	{ DWORD a_ = m->ebp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 48a10e: add ebp, 0x2c */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a111: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 48a113: mov dword ptr [esp + 0x28], eax */
	if (m->sf != m->of) goto L_489d11;	/* 48a117: jl 0x489d11 */
L_48a11d:
	m->eax = M32((DWORD)(m->esi + 0xbe170cu));	/* 48a11d: mov eax, dword ptr [esi + 0xbe170c] */
	m->ebp = 0x1u;	/* 48a123: mov ebp, 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a128: cmp eax, ebp */
	if (!m->zf) goto L_48a15a;	/* 48a12a: jne 0x48a15a */
	m->edx = M32((DWORD)(m->ebx + 0x9ee060u));	/* 48a12c: mov edx, dword ptr [ebx + 0x9ee060] */
	m->eax = M32((DWORD)(m->ebx + 0x9ee05cu));	/* 48a132: mov eax, dword ptr [ebx + 0x9ee05c] */
	m->ecx = M32((DWORD)(m->ebx + 0x9ee058u));	/* 48a138: mov ecx, dword ptr [ebx + 0x9ee058] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a13e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a13f: push eax */
	m->edx = (DWORD)(m->ebx + 0x9ee048u);	/* 48a140: lea edx, [ebx + 0x9ee048] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a146: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a147: push edx */
	m->ecx = m->ebx;	/* 48a148: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48a14fu; native_call(m, 0x472900u);	/* 48a14a: call 0x472900 */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a14f: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x48a15au; native_call(m, M32(0x4a9224u));	/* 48a154: call dword ptr [0x4a9224] */
L_48a15a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x22f040cu)));	/* 48a15a: fld dword ptr [esi + 0x22f040c] */
	m->eax = M32((DWORD)(m->esi + 0x1f1664u));	/* 48a160: mov eax, dword ptr [esi + 0x1f1664] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a166: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48a167: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a16a: push eax */
	m->ecx = m->edi;	/* 48a16b: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x48a172u; native_call(m, 0x485af0u);	/* 48a16d: call 0x485af0 */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a172: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x48a17du; native_call(m, M32(0x4a922cu));	/* 48a177: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a17d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a182: push 0 */
	m->esp -= 4; M32(m->esp) = 0x48a189u; native_call(m, 0x4685f0u);	/* 48a184: call 0x4685f0 */
	m->eax = M32((DWORD)(m->esi + 0x2340ce4u));	/* 48a189: mov eax, dword ptr [esi + 0x2340ce4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a18f: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a192: test eax, eax */
	if (!m->zf) goto L_48a31d;	/* 48a194: jne 0x48a31d */
	m->ecx = m->esi;	/* 48a19a: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48a1a1u; native_call(m, 0x48a1a1u + M32(0x48a19du));	/* 0x4913a0 unless the patch DLL retargets it */	/* 48a19c: call 0x4913a0 */
	m->eax = M32((DWORD)(m->esi + 0x2340ce8u));	/* 48a1a1: mov eax, dword ptr [esi + 0x2340ce8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a1a7: test eax, eax */
	if (!m->zf) goto L_48a1c5;	/* 48a1a9: jne 0x48a1c5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc40u)));	/* 48a1ab: fld dword ptr [esi + 0x233cc40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48a1b1: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48a1b7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48a1b9: test ah, 0x41 */
	if (!m->zf) goto L_48a1c5;	/* 48a1bc: jne 0x48a1c5 */
	m->ecx = m->esi;	/* 48a1be: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48a1c5u; native_call(m, 0x48a1c5u + M32(0x48a1c1u));	/* 0x495190 unless the patch DLL retargets it */	/* 48a1c0: call 0x495190 */
L_48a1c5:
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 48a1c5: mov eax, dword ptr [esi + 0x2340c64] */
	m->edi = M32((DWORD)(0x4a9228u));	/* 48a1cb: mov edi, dword ptr [0x4a9228] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a1d1: test eax, eax */
	if (m->sf != m->of) goto L_48a261;	/* 48a1d3: jl 0x48a261 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a1d9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a1de: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a1e3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a1e8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x48a1efu; native_call(m, m->edi);	/* 48a1ed: call edi */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a1ef: push 6 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a1f1: push 0x10 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a1f3: push 0x10 */
	m->ecx = m->esi;	/* 48a1f5: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48a1fcu; native_call(m, 0x48a1fcu + M32(0x48a1f8u));	/* 0x496820 unless the patch DLL retargets it */	/* 48a1f7: call 0x496820 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a1fc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a201: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a206: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a20b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x48a215u; native_call(m, 0x44ad30u);	/* 48a210: call 0x44ad30 */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48a215: mov eax, dword ptr [esi + 0x233cc10] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a21b: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a21e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48a232;	/* 48a220: jle 0x48a232 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a222: push eax */
	m->ecx = (DWORD)(m->esp + 0x190u);	/* 48a223: lea ecx, [esp + 0x190] */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a22a: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a22f: push ecx */
	goto L_48a243;	/* 48a230: jmp 0x48a243 */
L_48a232:
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48a232: add eax, 0xa */
	m->edx = (DWORD)(m->esp + 0x18cu);	/* 48a235: lea edx, [esp + 0x18c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a23c: push eax */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a23d: push 0x4b0320 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a242: push edx */
L_48a243:
	m->esp -= 4; M32(m->esp) = 0x48a248u; native_call(m, 0x49e9ddu);	/* 48a243: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a248: add esp, 0xc */
	m->eax = (DWORD)(m->esp + 0x18cu);	/* 48a24b: lea eax, [esp + 0x18c] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a252: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a254: push eax */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a255: push 0x10 */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a257: push 0x28 */
	m->esp -= 4; M32(m->esp) = 0x48a25eu; native_call(m, 0x48a25eu + M32(0x48a25au));	/* 0x44ad60 unless the patch DLL retargets it */	/* 48a259: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a25e: add esp, 0x10 */
L_48a261:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc34u)));	/* 48a261: fld dword ptr [esi + 0x233cc34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 48a267: fcomp dword ptr [0x4a942c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48a26d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48a26f: test ah, 1 */
	if (m->zf) goto L_48a307;	/* 48a272: je 0x48a307 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a278: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a27d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a282: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a287: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x48a28eu; native_call(m, m->edi);	/* 48a28c: call edi */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a28e: push 5 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a290: push 0x10 */
	{ DWORD v_ = 0x20eu; m->esp -= 4; M32(m->esp) = v_; }	/* 48a292: push 0x20e */
	m->ecx = m->esi;	/* 48a297: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48a29eu; native_call(m, 0x48a29eu + M32(0x48a29au));	/* 0x496820 unless the patch DLL retargets it */	/* 48a299: call 0x496820 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a29e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2a3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2a8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2ad: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x48a2b7u; native_call(m, 0x44ad30u);	/* 48a2b2: call 0x44ad30 */
	m->ecx = M32((DWORD)(m->esi + 0x233cc30u));	/* 48a2b7: mov ecx, dword ptr [esi + 0x233cc30] */
	m->edi = 0x3cu;	/* 48a2bd: mov edi, 0x3c */
	m->eax = m->ecx;	/* 48a2c2: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48a2c4: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48a2c5: idiv edi */
	m->eax = 0x88888889u;	/* 48a2c7: mov eax, 0x88888889 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2cc: push edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 48a2cd: imul ecx */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48a2cf: add edx, ecx */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48a2d1: sar edx, 5 */
	m->ecx = m->edx;	/* 48a2d4: mov ecx, edx */
	{ DWORD a_ = m->ecx, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48a2d6: shr ecx, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48a2d9: add edx, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2db: push edx */
	m->edx = (DWORD)(m->esp + 0x1a4u);	/* 48a2dc: lea edx, [esp + 0x1a4] */
	{ DWORD v_ = 0x4c7cd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2e3: push 0x4c7cd8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2e8: push edx */
	m->esp -= 4; M32(m->esp) = 0x48a2eeu; native_call(m, 0x49e9ddu);	/* 48a2e9: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 48a2ee: lea eax, [esp + 0x1ac] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2f5: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2f7: push eax */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2f8: push 0x10 */
	{ DWORD v_ = 0x226u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a2fa: push 0x226 */
	m->esp -= 4; M32(m->esp) = 0x48a304u; native_call(m, 0x48a304u + M32(0x48a300u));	/* 0x44ad60 unless the patch DLL retargets it */	/* 48a2ff: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a304: add esp, 0x30 */
L_48a307:
	m->ecx = m->esi;	/* 48a307: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48a30eu; native_call(m, 0x48a30eu + M32(0x48a30au));	/* 0x496b80 unless the patch DLL retargets it */	/* 48a309: call 0x496b80 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x234328fu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a30e: cmp dword ptr [esi + 0x234328f], ebp */
	if (!m->zf) goto L_48a31d;	/* 48a314: jne 0x48a31d */
	m->ecx = m->esi;	/* 48a316: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48a31du; native_call(m, 0x48a31du + M32(0x48a319u));	/* 0x494930 unless the patch DLL retargets it */	/* 48a318: call 0x494930 */
L_48a31d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2342f02u)));	/* 48a31d: fld dword ptr [esi + 0x2342f02] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48a323: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48a329: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48a32b: test ah, 0x41 */
	if (!m->zf) goto L_48a337;	/* 48a32e: jne 0x48a337 */
	m->ecx = m->esi;	/* 48a330: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48a337u; native_call(m, 0x496c20u);	/* 48a332: call 0x496c20 */
L_48a337:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432cfu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a337: cmp dword ptr [esi + 0x23432cf], ebp */
	if (!m->zf) goto L_48a360;	/* 48a33d: jne 0x48a360 */
	m->ecx = M32((DWORD)(m->esi + 0x2340d08u));	/* 48a33f: mov ecx, dword ptr [esi + 0x2340d08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a345: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48a34bu; native_call(m, 0x49e7e0u);	/* 48a346: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a34b: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x48a353u; native_call(m, 0x457310u);	/* 48a34e: call 0x457310 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48a353: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48a354: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48a355: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48a356: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48a358: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x27cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a359: add esp, 0x27c */
	m->esp += 4 + 0; return;	/* 48a35f: ret  */
L_48a360:
	m->edi = M32(m->esp); m->esp += 4;	/* 48a360: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48a361: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48a362: pop ebp */
	m->eax = 0x4u;	/* 48a363: mov eax, 4 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48a368: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x27cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a369: add esp, 0x27c */
	m->esp += 4 + 0; return;	/* 48a36f: ret  */
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
