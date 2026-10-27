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

static void lift_41fd40(X86 *m);

/* console_init (0x41fd40), lifted by tools/lift.py */
static void lift_41fd40(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fd40: sub esp, 0x80 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41fd46: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 41fd47: xor ebp, ebp */
L_41fd49:
	{ DWORD a_ = M32((DWORD)(0x67fb3cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fd49: cmp dword ptr [0x67fb3c], ebp */
	if (m->zf) goto L_41fd60;	/* 41fd4f: je 0x41fd60 */
	{ DWORD v_ = 0x67fb3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41fd51: push 0x67fb3c */
	m->esp -= 4; M32(m->esp) = 0x41fd5bu; native_call(m, 0x441190u);	/* 41fd56: call 0x441190 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fd5b: add esp, 4 */
	goto L_41fd49;	/* 41fd5e: jmp 0x41fd49 */
L_41fd60:
	{ DWORD a_ = M32((DWORD)(0x76d410u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fd60: cmp dword ptr [0x76d410], ebp */
	if (!m->zf) goto L_41fdfd;	/* 41fd66: jne 0x41fdfd */
	m->esp -= 4; M32(m->esp) = 0x41fd71u; native_call(m, 0x41e6d0u);	/* 41fd6c: call 0x41e6d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fd71: test eax, eax */
	if (!m->zf) goto L_41fd89;	/* 41fd73: jne 0x41fd89 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fd75: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x41fd7fu; native_call(m, 0x41edf0u);	/* 41fd7a: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fd7f: add esp, 4 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 41fd82: push -1 */
	m->esp -= 4; M32(m->esp) = 0x41fd89u; native_call(m, 0x49edacu);	/* 41fd84: call 0x49edac */
L_41fd89:
	m->esp -= 4; M32(m->esp) = 0x41fd8eu; native_call(m, 0x41e550u);	/* 41fd89: call 0x41e550 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fd8e: test eax, eax */
	if (!m->zf) goto L_41fda6;	/* 41fd90: jne 0x41fda6 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fd92: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x41fd9cu; native_call(m, 0x41edf0u);	/* 41fd97: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fd9c: add esp, 4 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 41fd9f: push -1 */
	m->esp -= 4; M32(m->esp) = 0x41fda6u; native_call(m, 0x49edacu);	/* 41fda1: call 0x49edac */
L_41fda6:
	m->esp -= 4; M32(m->esp) = 0x41fdabu; native_call(m, 0x41e550u);	/* 41fda6: call 0x41e550 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fdab: test eax, eax */
	if (!m->zf) goto L_41fdc3;	/* 41fdad: jne 0x41fdc3 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fdaf: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x41fdb9u; native_call(m, 0x41edf0u);	/* 41fdb4: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fdb9: add esp, 4 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 41fdbc: push -1 */
	m->esp -= 4; M32(m->esp) = 0x41fdc3u; native_call(m, 0x49edacu);	/* 41fdbe: call 0x49edac */
L_41fdc3:
	m->esp -= 4; M32(m->esp) = 0x41fdc8u; native_call(m, 0x41e550u);	/* 41fdc3: call 0x41e550 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fdc8: test eax, eax */
	if (!m->zf) goto L_41fde0;	/* 41fdca: jne 0x41fde0 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fdcc: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x41fdd6u; native_call(m, 0x41edf0u);	/* 41fdd1: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fdd6: add esp, 4 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 41fdd9: push -1 */
	m->esp -= 4; M32(m->esp) = 0x41fde0u; native_call(m, 0x49edacu);	/* 41fddb: call 0x49edac */
L_41fde0:
	m->esp -= 4; M32(m->esp) = 0x41fde5u; native_call(m, 0x41e550u);	/* 41fde0: call 0x41e550 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fde5: test eax, eax */
	if (!m->zf) goto L_41fdfd;	/* 41fde7: jne 0x41fdfd */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fde9: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x41fdf3u; native_call(m, 0x41edf0u);	/* 41fdee: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fdf3: add esp, 4 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 41fdf6: push -1 */
	m->esp -= 4; M32(m->esp) = 0x41fdfdu; native_call(m, 0x49edacu);	/* 41fdf8: call 0x49edac */
L_41fdfd:
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 41fdfd: fild dword ptr [0x5b1998] */
	M32((DWORD)(0x5b1dacu)) = 0x1u;	/* 41fe03: mov dword ptr [0x5b1dac], 1 */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(0x4e045cu));	/* 41fe0d: fidiv dword ptr [0x4e045c] */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 41fe13: fstp dword ptr [0x4e1870] */
	m->esp -= 4; M32(m->esp) = 0x41fe1eu; native_call(m, 0x43f300u);	/* 41fe19: call 0x43f300 */
	m->eax = M32((DWORD)(0x76d480u));	/* 41fe1e: mov eax, dword ptr [0x76d480] */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 41fe23: mov ecx, dword ptr [0x4ded18] */
	m->edx = M32((DWORD)(0x83a9c4u));	/* 41fe29: mov edx, dword ptr [0x83a9c4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe2f: push eax */
	m->eax = M32((DWORD)(0x4e045cu));	/* 41fe30: mov eax, dword ptr [0x4e045c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe35: push ecx */
	m->ecx = M32((DWORD)(0x5b1998u));	/* 41fe36: mov ecx, dword ptr [0x5b1998] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe3c: push ebp */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe3d: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe3f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe40: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe41: push ecx */
	{ DWORD v_ = 0x4b04a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe42: push 0x4b04a0 */
	m->esp -= 4; M32(m->esp) = 0x41fe4cu; native_call(m, 0x468250u);	/* 41fe47: call 0x468250 */
	m->eax = M32((DWORD)(0x9db990u));	/* 41fe4c: mov eax, dword ptr [0x9db990] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fe51: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fe54: cmp eax, ebp */
	if (m->zf) goto L_41fe74;	/* 41fe56: je 0x41fe74 */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41fe58: mov ecx, dword ptr [0x9087b4] */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe5e: push 3 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe60: push ebp */
	M32((DWORD)(0x5ae9c4u)) = m->ebp;	/* 41fe61: mov dword ptr [0x5ae9c4], ebp */
	m->esp -= 4; M32(m->esp) = 0x41fe6cu; native_call(m, 0x460cb0u);	/* 41fe67: call 0x460cb0 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41fe6c: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fe6d: add esp, 0x80 */
	m->esp += 4 + 0; return;	/* 41fe73: ret  */
L_41fe74:
	m->edx = M32((DWORD)(0x9dad94u));	/* 41fe74: mov edx, dword ptr [0x9dad94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe7a: push edx */
	m->esp -= 4; M32(m->esp) = 0x41fe80u; native_call(m, 0x41e7c0u);	/* 41fe7b: call 0x41e7c0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fe80: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fe83: test eax, eax */
	if (!m->zf) goto L_41feca;	/* 41fe85: jne 0x41feca */
	m->eax = M32((DWORD)(0x5ae9c4u));	/* 41fe87: mov eax, dword ptr [0x5ae9c4] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41fe8c: dec eax */
	if (m->zf) goto L_41feae;	/* 41fe8d: je 0x41feae */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41fe8f: dec eax */
	if (!m->zf) goto L_41feb8;	/* 41fe90: jne 0x41feb8 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fe92: push 6 */
	M32((DWORD)(0x76d3e8u)) = 0x320u;	/* 41fe94: mov dword ptr [0x76d3e8], 0x320 */
	m->esp -= 4; M32(m->esp) = 0x41fea3u; native_call(m, 0x41ee40u);	/* 41fe9e: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fea3: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41fea6: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fea7: add esp, 0x80 */
	m->esp += 4 + 0; return;	/* 41fead: ret  */
L_41feae:
	M32((DWORD)(0x76d3e8u)) = 0x190u;	/* 41feae: mov dword ptr [0x76d3e8], 0x190 */
L_41feb8:
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 41feb8: push 6 */
	m->esp -= 4; M32(m->esp) = 0x41febfu; native_call(m, 0x41ee40u);	/* 41feba: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41febf: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41fec2: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fec3: add esp, 0x80 */
	m->esp += 4 + 0; return;	/* 41fec9: ret  */
L_41feca:
	m->eax = M32((DWORD)(0x5ae9c4u));	/* 41feca: mov eax, dword ptr [0x5ae9c4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41fecf: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41fed0: push esi */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41fed1: dec eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41fed2: push edi */
	if (m->zf) goto L_41ffcf;	/* 41fed3: je 0x41ffcf */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41fed9: dec eax */
	if (m->zf) goto L_41ff1b;	/* 41feda: je 0x41ff1b */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41fedc: dec eax */
	if (!m->zf) goto L_420076;	/* 41fedd: jne 0x420076 */
	m->ecx = 0x8u;	/* 41fee3: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41fee8: xor eax, eax */
	m->edi = 0x4dedd8u;	/* 41feea: mov edi, 0x4dedd8 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41feef: push ebp */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41fef0: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9f1798u;	/* 41fef2: mov edi, 0x9f1798 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41fef7: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41fefa: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41fefc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41fefe: sub edi, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41ff00: push ebp */
	m->eax = m->ecx;	/* 41ff01: mov eax, ecx */
	m->esi = m->edi;	/* 41ff03: mov esi, edi */
	m->edi = 0x4dedd8u;	/* 41ff05: mov edi, 0x4dedd8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41ff0a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41ff0d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 41ff0f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41ff11: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41ff14: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42006b;	/* 41ff16: jmp 0x42006b */
L_41ff1b:
	m->esp -= 4; M32(m->esp) = 0x41ff20u; native_call(m, 0x41e390u);	/* 41ff1b: call 0x41e390 */
	m->eax = M32((DWORD)(0x9dd5d8u));	/* 41ff20: mov eax, dword ptr [0x9dd5d8] */
	m->ebx = 0x14u;	/* 41ff25: mov ebx, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ff2a: cmp eax, ebx */
	if (m->zf) goto L_41ff33;	/* 41ff2c: je 0x41ff33 */
	m->esp -= 4; M32(m->esp) = 0x41ff33u; native_call(m, 0x40d990u);	/* 41ff2e: call 0x40d990 */
L_41ff33:
	m->esp -= 4; M32(m->esp) = 0x41ff38u; native_call(m, 0x42b590u);	/* 41ff33: call 0x42b590 */
	m->ecx = 0x8u;	/* 41ff38: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41ff3d: xor eax, eax */
	m->edi = 0x4dedd8u;	/* 41ff3f: mov edi, 0x4dedd8 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 41ff44: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dd570u;	/* 41ff46: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41ff4b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41ff4e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41ff50: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 41ff52: sub edi, ecx */
	m->eax = M32((DWORD)(0x9dd5d8u));	/* 41ff54: mov eax, dword ptr [0x9dd5d8] */
	m->edx = m->ecx;	/* 41ff59: mov edx, ecx */
	m->esi = m->edi;	/* 41ff5b: mov esi, edi */
	m->edi = 0x4dedd8u;	/* 41ff5d: mov edi, 0x4dedd8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 41ff62: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 41ff65: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 41ff67: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41ff69: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ff6c: cmp eax, ebx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 41ff6e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (m->zf) goto L_42005a;	/* 41ff70: je 0x42005a */
	m->ecx = M32((DWORD)(0x4dc878u));	/* 41ff76: mov ecx, dword ptr [0x4dc878] */
	m->eax = 0x13u;	/* 41ff7c: mov eax, 0x13 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ff81: cmp ecx, eax */
	goto L_41ff8b;	/* 41ff83: jmp 0x41ff8b */
	M32((DWORD)(0x4dc878u)) = m->ebp;	/* 41ff85: mov dword ptr [0x4dc878], ebp */
L_41ff8b:
	{ DWORD a_ = M32((DWORD)(0x4dc87cu)), b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ff8b: cmp dword ptr [0x4dc87c], 0xd */
	goto L_41ff9a;	/* 41ff92: jmp 0x41ff9a */
	M32((DWORD)(0x4dc87cu)) = m->ebp;	/* 41ff94: mov dword ptr [0x4dc87c], ebp */
L_41ff9a:
	{ DWORD a_ = M32((DWORD)(0x4dc880u)), b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ff9a: cmp dword ptr [0x4dc880], 0x11 */
	goto L_41ffa9;	/* 41ffa1: jmp 0x41ffa9 */
	M32((DWORD)(0x4dc880u)) = m->ebp;	/* 41ffa3: mov dword ptr [0x4dc880], ebp */
L_41ffa9:
	{ DWORD a_ = M32((DWORD)(0x4dc888u)), b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ffa9: cmp dword ptr [0x4dc888], 0xf */
	goto L_41ffb8;	/* 41ffb0: jmp 0x41ffb8 */
	M32((DWORD)(0x4dc888u)) = m->ebp;	/* 41ffb2: mov dword ptr [0x4dc888], ebp */
L_41ffb8:
	{ DWORD a_ = M32((DWORD)(0x4dc884u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ffb8: cmp dword ptr [0x4dc884], eax */
	;	/* 41ffbe: nop  */
	goto L_42005a;	/* 41ffbf: jmp 0x42005a */
	M32((DWORD)(0x4dc884u)) = m->ebp;	/* 41ffc4: mov dword ptr [0x4dc884], ebp */
	goto L_42005a;	/* 41ffca: jmp 0x42005a */
L_41ffcf:
	m->ecx = M32((DWORD)(0x4dc878u));	/* 41ffcf: mov ecx, dword ptr [0x4dc878] */
	m->eax = 0x13u;	/* 41ffd5: mov eax, 0x13 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ffda: cmp ecx, eax */
	goto L_41ffe4;	/* 41ffdc: jmp 0x41ffe4 */
	M32((DWORD)(0x4dc878u)) = m->ebp;	/* 41ffde: mov dword ptr [0x4dc878], ebp */
L_41ffe4:
	{ DWORD a_ = M32((DWORD)(0x4dc87cu)), b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ffe4: cmp dword ptr [0x4dc87c], 0xd */
	goto L_41fff3;	/* 41ffeb: jmp 0x41fff3 */
	M32((DWORD)(0x4dc87cu)) = m->ebp;	/* 41ffed: mov dword ptr [0x4dc87c], ebp */
L_41fff3:
	{ DWORD a_ = M32((DWORD)(0x4dc880u)), b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fff3: cmp dword ptr [0x4dc880], 0x11 */
	goto L_420002;	/* 41fffa: jmp 0x420002 */
	M32((DWORD)(0x4dc880u)) = m->ebp;	/* 41fffc: mov dword ptr [0x4dc880], ebp */
L_420002:
	{ DWORD a_ = M32((DWORD)(0x4dc888u)), b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420002: cmp dword ptr [0x4dc888], 0xf */
	goto L_420011;	/* 420009: jmp 0x420011 */
	M32((DWORD)(0x4dc888u)) = m->ebp;	/* 42000b: mov dword ptr [0x4dc888], ebp */
L_420011:
	{ DWORD a_ = M32((DWORD)(0x4dc884u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420011: cmp dword ptr [0x4dc884], eax */
	goto L_42001f;	/* 420017: jmp 0x42001f */
	M32((DWORD)(0x4dc884u)) = m->ebp;	/* 420019: mov dword ptr [0x4dc884], ebp */
L_42001f:
	m->esp -= 4; M32(m->esp) = 0x420024u; native_call(m, 0x42b590u);	/* 42001f: call 0x42b590 */
	m->ecx = 0x8u;	/* 420024: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 420029: xor eax, eax */
	m->edi = 0x4dedd8u;	/* 42002b: mov edi, 0x4dedd8 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 420030: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x4dedb0u;	/* 420032: mov edi, 0x4dedb0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 420037: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42003a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42003c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42003e: sub edi, ecx */
	m->eax = m->ecx;	/* 420040: mov eax, ecx */
	m->esi = m->edi;	/* 420042: mov esi, edi */
	m->edi = 0x4dedd8u;	/* 420044: mov edi, 0x4dedd8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 420049: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42004c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42004e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 420050: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 420053: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x42005au; native_call(m, 0x40d990u);	/* 420055: call 0x40d990 */
L_42005a:
	m->eax = M32((DWORD)(0x67ef04u));	/* 42005a: mov eax, dword ptr [0x67ef04] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42005f: push 1 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420061: cmp eax, 1 */
	if (!m->zf) goto L_420069;	/* 420064: jne 0x420069 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 420066: push ebp */
	goto L_42006b;	/* 420067: jmp 0x42006b */
L_420069:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 420069: push 1 */
L_42006b:
	m->ecx = M32((DWORD)(0x9087b4u));	/* 42006b: mov ecx, dword ptr [0x9087b4] */
	m->esp -= 4; M32(m->esp) = 0x420076u; native_call(m, 0x460cb0u);	/* 420071: call 0x460cb0 */
L_420076:
	m->ecx = 0x20u;	/* 420076: mov ecx, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42007b: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 42007d: lea edi, [esp + 0x10] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 420081: lea edx, [esp + 0x10] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 420085: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x4b0498u;	/* 420087: mov edi, 0x4b0498 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42008c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42008f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 420091: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 420093: sub edi, ecx */
	m->ebx = (DWORD)(m->esp + 0x10u);	/* 420095: lea ebx, [esp + 0x10] */
	m->eax = m->ecx;	/* 420099: mov eax, ecx */
	m->esi = m->edi;	/* 42009b: mov esi, edi */
	m->edi = m->edx;	/* 42009d: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42009f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4200a2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4200a4: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4200a6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4200a8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4200ab: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dad94u));	/* 4200ad: mov ecx, dword ptr [0x9dad94] */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4200b3: shl ecx, 5 */
	m->edx = (DWORD)(m->ecx + 0x907b30u);	/* 4200b6: lea edx, [ecx + 0x907b30] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4200bc: or ecx, 0xffffffff */
	m->edi = m->edx;	/* 4200bf: mov edi, edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4200c1: push edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4200c2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4200c4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4200c6: sub edi, ecx */
	m->esi = m->edi;	/* 4200c8: mov esi, edi */
	m->ebp = m->ecx;	/* 4200ca: mov ebp, ecx */
	m->edi = m->ebx;	/* 4200cc: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4200ce: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4200d1: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 4200d3: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4200d5: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4200d6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4200d9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 4200db: mov ecx, ebp */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4200dd: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4200e0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 4200e2: mov ecx, dword ptr [0x9087b4] */
	m->esp -= 4; M32(m->esp) = 0x4200edu; native_call(m, 0x461ec0u);	/* 4200e8: call 0x461ec0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4200ed: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4200ee: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4200ef: pop ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4200f0: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4200f1: add esp, 0x80 */
	m->esp += 4 + 0; return;	/* 4200f7: ret  */
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
