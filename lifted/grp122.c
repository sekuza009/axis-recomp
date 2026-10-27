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

static void lift_433a80(X86 *m);
static void lift_456e50(X86 *m);
static void lift_431600(X86 *m);
static void lift_431950(X86 *m);
static void lift_403640(X86 *m);
static void lift_4512c0(X86 *m);
static void lift_405230(X86 *m);
static void lift_4318b0(X86 *m);
static void lift_452fe0(X86 *m);
static void lift_404cd0(X86 *m);
static void lift_404d70(X86 *m);
static void lift_4339e0(X86 *m);
static void lift_42bd40(X86 *m);
static void lift_437240(X86 *m);
static void lift_403590(X86 *m);
static void lift_433b00(X86 *m);
static void lift_404ed0(X86 *m);
static void lift_422c60(X86 *m);
static void lift_404e10(X86 *m);
static void lift_434260(X86 *m);
static void lift_457080(X86 *m);
static void lift_434020(X86 *m);
static void lift_4340e0(X86 *m);
static void lift_4341a0(X86 *m);
static void lift_433bb0(X86 *m);
static void lift_437810(X86 *m);
static void lift_404f90(X86 *m);

/* arena_editTextField_404f90 (0x404f90), lifted by tools/lift.py */
static void lift_404f90(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 404f90: push edi */
	m->esp -= 4; M32(m->esp) = 0x404f96u; native_call(m, 0x401460u);	/* 404f91: call 0x401460 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 404f96: push 8 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 404f98: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x404fa7u; native_call(m, 0x431560u);	/* 404fa2: call 0x431560 */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 404fa7: mov eax, dword ptr [0x4dbb00] */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 404fac: mov ecx, dword ptr [0x4dbb04] */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 404fb2: add eax, 0xa4 */
	{ DWORD a_ = m->ecx, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 404fb7: add ecx, 0x54 */
	M32((DWORD)(0x9da3d8u)) = m->eax;	/* 404fba: mov dword ptr [0x9da3d8], eax */
	M32((DWORD)(0x9da3dcu)) = m->ecx;	/* 404fbf: mov dword ptr [0x9da3dc], ecx */
	m->edi = 0x9dc92cu;	/* 404fc5: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404fca: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404fcd: xor eax, eax */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 404fcf: push 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404fd1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404fd3: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 404fd5: dec ecx */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 404fd6: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 404fe0: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x4dbaccu)) = 0x1u;	/* 404fe6: mov dword ptr [0x4dbacc], 1 */
	M32((DWORD)(0x4e1868u)) = 0x1u;	/* 404ff0: mov dword ptr [0x4e1868], 1 */
	m->esp -= 4; M32(m->esp) = 0x404fffu; native_call(m, 0x43f460u);	/* 404ffa: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404fff: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 405002: pop edi */
	m->esp += 4 + 0; return;	/* 405003: ret  */
}

/* room_433a80 (0x433a80), lifted by tools/lift.py */
static void lift_433a80(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 433a80: push edi */
	m->esp -= 4; M32(m->esp) = 0x433a86u; native_call(m, 0x401460u);	/* 433a81: call 0x401460 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 433a86: push 8 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 433a88: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x433a97u; native_call(m, 0x431560u);	/* 433a92: call 0x431560 */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 433a97: mov eax, dword ptr [0x9dd1b8] */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 433a9c: mov ecx, dword ptr [0x9dd1bc] */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 433aa2: add eax, 0xa4 */
	{ DWORD a_ = m->ecx, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 433aa7: add ecx, 0x54 */
	M32((DWORD)(0x9da3d8u)) = m->eax;	/* 433aaa: mov dword ptr [0x9da3d8], eax */
	M32((DWORD)(0x9da3dcu)) = m->ecx;	/* 433aaf: mov dword ptr [0x9da3dc], ecx */
	m->edi = 0x9dc92cu;	/* 433ab5: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433aba: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433abd: xor eax, eax */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 433abf: push 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433ac1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433ac3: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 433ac5: dec ecx */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 433ac6: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 433ad0: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x9dd6a8u)) = 0x1u;	/* 433ad6: mov dword ptr [0x9dd6a8], 1 */
	M32((DWORD)(0x4e1868u)) = 0x1u;	/* 433ae0: mov dword ptr [0x4e1868], 1 */
	m->esp -= 4; M32(m->esp) = 0x433aefu; native_call(m, 0x43f460u);	/* 433aea: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433aef: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 433af2: pop edi */
	m->esp += 4 + 0; return;	/* 433af3: ret  */
}

/* sound_playVolume (0x456e50), lifted by tools/lift.py */
static void lift_456e50(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e80cu));	/* 456e50: mov eax, dword ptr [0xa0e80c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456e55: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456e56: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456e58: push edi */
	if (m->zf) goto L_456ec2;	/* 456e59: je 0x456ec2 */
	m->edi = M32((DWORD)(m->esp + 0xcu));	/* 456e5b: mov edi, dword ptr [esp + 0xc] */
	m->esi = M32((DWORD)(m->edi*4 + 0xa0e02cu));	/* 456e5f: mov esi, dword ptr [edi*4 + 0xa0e02c] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456e66: test esi, esi */
	if (m->zf) goto L_456ec2;	/* 456e68: je 0x456ec2 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 456e6a: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456e6e: test eax, eax */
	if (m->sf == m->of) goto L_456e79;	/* 456e70: jge 0x456e79 */
	m->eax = 0xfffffc18u;	/* 456e72: mov eax, 0xfffffc18 */
	goto L_456eab;	/* 456e77: jmp 0x456eab */
L_456e79:
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456e79: cmp eax, 0x64 */
	if (m->zf || m->sf != m->of) goto L_456e85;	/* 456e7c: jle 0x456e85 */
	m->eax = M32((DWORD)(0xa0e66cu));	/* 456e7e: mov eax, dword ptr [0xa0e66c] */
	goto L_456eab;	/* 456e83: jmp 0x456eab */
L_456e85:
	m->eax = M32((DWORD)(0xa0e66cu));	/* 456e85: mov eax, dword ptr [0xa0e66c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 456e8a: fild dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = 0x2710u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 456e8e: add eax, 0x2710 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 456e93: mov dword ptr [esp + 0x10], eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 456e97: fmul dword ptr [0x4a9504] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x10u));	/* 456e9d: fimul dword ptr [esp + 0x10] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 456ea1: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 456ea6: sub eax, 0x2710 */
L_456eab:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456eab: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456eac: push esi */
	m->esp -= 4; M32(m->esp) = 0x456eb2u; native_call(m, 0x467db0u);	/* 456ead: call 0x467db0 */
	m->ecx = M32((DWORD)(m->edi*4 + 0xa0e02cu));	/* 456eb2: mov ecx, dword ptr [edi*4 + 0xa0e02c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456eb9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x456ebfu; native_call(m, 0x467d70u);	/* 456eba: call 0x467d70 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456ebf: add esp, 0xc */
L_456ec2:
	m->edi = M32(m->esp); m->esp += 4;	/* 456ec2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 456ec3: pop esi */
	m->esp += 4 + 0; return;	/* 456ec4: ret  */
}

/* room_431600 (0x431600), lifted by tools/lift.py */
static void lift_431600(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 431600: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 431604: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 431605: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431607: cmp eax, esi */
	M32((DWORD)(0x68039cu)) = m->esi;	/* 431609: mov dword ptr [0x68039c], esi */
	if (m->zf) goto L_43162b;	/* 43160f: je 0x43162b */
	m->esp -= 4; M32(m->esp) = 0x431616u; native_call(m, 0x431590u);	/* 431611: call 0x431590 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 431616: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43161b: push eax */
	m->esp -= 4; M32(m->esp) = 0x431621u; native_call(m, 0x401310u);	/* 43161c: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 431621: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x431629u; native_call(m, 0x4315c0u);	/* 431624: call 0x4315c0 */
	goto L_43165f;	/* 431629: jmp 0x43165f */
L_43162b:
	m->ecx = M32((DWORD)(0x9dcd30u));	/* 43162b: mov ecx, dword ptr [0x9dcd30] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431631: cmp ecx, esi */
	if (m->zf || m->sf != m->of) goto L_43164c;	/* 431633: jle 0x43164c */
	m->edx = m->ecx;	/* 431635: mov edx, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 431637: push edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 431638: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43163a: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43163f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 431642: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 431644: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 431646: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 431649: rep stosb byte ptr es:[edi], al */
	m->edi = M32(m->esp); m->esp += 4;	/* 43164b: pop edi */
L_43164c:
	m->esp -= 4; M32(m->esp) = 0x431651u; native_call(m, 0x431590u);	/* 43164c: call 0x431590 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 431651: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 431656: push eax */
	m->esp -= 4; M32(m->esp) = 0x43165cu; native_call(m, 0x401310u);	/* 431657: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43165c: add esp, 4 */
L_43165f:
	M32((DWORD)(0x9dcd30u)) = m->esi;	/* 43165f: mov dword ptr [0x9dcd30], esi */
	M32((DWORD)(0x9dbf10u)) = m->esi;	/* 431665: mov dword ptr [0x9dbf10], esi */
	M32((DWORD)(0x9da434u)) = 0x41200000u;	/* 43166b: mov dword ptr [0x9da434], 0x41200000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 431675: pop esi */
	m->esp += 4 + 0; return;	/* 431676: ret  */
}

/* menu_431950 (0x431950), lifted by tools/lift.py */
static void lift_431950(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae70u));	/* 431950: mov eax, dword ptr [0x9dae70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 431955: push eax */
	m->esp -= 4; M32(m->esp) = 0x43195bu; native_call(m, 0x401600u);	/* 431956: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43195b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43195e: cmp eax, 1 */
	if (!m->zf) goto L_431977;	/* 431961: jne 0x431977 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 431963: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4df900u)) = 0x0u;	/* 43196d: mov dword ptr [0x4df900], 0 */
L_431977:
	m->ecx = M32((DWORD)(0x5b1da8u));	/* 431977: mov ecx, dword ptr [0x5b1da8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43197d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x431983u; native_call(m, 0x401600u);	/* 43197e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 431983: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431986: cmp eax, 1 */
	if (!m->zf) goto L_43199f;	/* 431989: jne 0x43199f */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 43198b: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4df900u)) = 0x0u;	/* 431995: mov dword ptr [0x4df900], 0 */
L_43199f:
	m->edx = M32((DWORD)(0x6803a0u));	/* 43199f: mov edx, dword ptr [0x6803a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4319a5: push edx */
	m->esp -= 4; M32(m->esp) = 0x4319abu; native_call(m, 0x401600u);	/* 4319a6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4319ab: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4319ae: cmp eax, 1 */
	if (!m->zf) goto L_4319c7;	/* 4319b1: jne 0x4319c7 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4319b3: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4df900u)) = 0x0u;	/* 4319bd: mov dword ptr [0x4df900], 0 */
L_4319c7:
	m->esp += 4 + 0; return;	/* 4319c7: ret  */
}

/* room_403640 (0x403640), lifted by tools/lift.py */
static void lift_403640(X86 *m)
{
	m->edx = M32((DWORD)(0x67ef00u));	/* 403640: mov edx, dword ptr [0x67ef00] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403646: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 403647: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 403649: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40364b: cmp edx, esi */
	if (m->zf || m->sf != m->of) goto L_4036bb;	/* 40364d: jle 0x4036bb */
	m->ecx = 0x4d7358u;	/* 40364f: mov ecx, 0x4d7358 */
L_403654:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403654: cmp dword ptr [ecx], 1 */
	if (m->zf) goto L_403663;	/* 403657: je 0x403663 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 403659: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40365a: add ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40365d: cmp eax, edx */
	if (m->sf != m->of) goto L_403654;	/* 40365f: jl 0x403654 */
	m->esi = M32(m->esp); m->esp += 4;	/* 403661: pop esi */
	m->esp += 4 + 0; return;	/* 403662: ret  */
L_403663:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403663: push esi */
	m->esp -= 4; M32(m->esp) = 0x403669u; native_call(m, 0x41e760u);	/* 403664: call 0x41e760 */
	m->ecx = M32((DWORD)(0x67ef00u));	/* 403669: mov ecx, dword ptr [0x67ef00] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40366f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 403672: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403674: cmp ecx, esi */
	M32((DWORD)(0x4d7408u)) = m->esi;	/* 403676: mov dword ptr [0x4d7408], esi */
	M32((DWORD)(0x4d7410u)) = m->esi;	/* 40367c: mov dword ptr [0x4d7410], esi */
	M32((DWORD)(0x4d7418u)) = m->esi;	/* 403682: mov dword ptr [0x4d7418], esi */
	if (m->zf || m->sf != m->of) goto L_4036ab;	/* 403688: jle 0x4036ab */
L_40368a:
	m->edx = M32((DWORD)(m->eax*8 + 0x4d7358u));	/* 40368a: mov edx, dword ptr [eax*8 + 0x4d7358] */
	M32((DWORD)(m->eax*8 + 0x4d9508u)) = m->edx;	/* 403691: mov dword ptr [eax*8 + 0x4d9508], edx */
	m->edx = M32((DWORD)(m->eax*8 + 0x4d735cu));	/* 403698: mov edx, dword ptr [eax*8 + 0x4d735c] */
	M32((DWORD)(m->eax*8 + 0x4d950cu)) = m->edx;	/* 40369f: mov dword ptr [eax*8 + 0x4d950c], edx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4036a6: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4036a7: cmp eax, ecx */
	if (m->sf != m->of) goto L_40368a;	/* 4036a9: jl 0x40368a */
L_4036ab:
	M32((DWORD)(0x4db508u)) = m->esi;	/* 4036ab: mov dword ptr [0x4db508], esi */
	M32((DWORD)(0x4d94fcu)) = 0x1u;	/* 4036b1: mov dword ptr [0x4d94fc], 1 */
L_4036bb:
	m->esi = M32(m->esp); m->esp += 4;	/* 4036bb: pop esi */
	m->esp += 4 + 0; return;	/* 4036bc: ret  */
}

/* match_4512c0 (0x4512c0), lifted by tools/lift.py */
static void lift_4512c0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b424u));	/* 4512c0: mov eax, dword ptr [0xa0b424] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4512c5: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x8u));	/* 4512c6: mov ebx, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4512ca: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4512cb: push edi */
	{ DWORD v_ = 0x9fd944u; m->esp -= 4; M32(m->esp) = v_; }	/* 4512cc: push 0x9fd944 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4512d1: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4512d2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4512d8u; native_call(m, 0x451350u);	/* 4512d3: call 0x451350 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4512d8: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4512db: test eax, eax */
	if (m->sf != m->of) goto L_451301;	/* 4512dd: jl 0x451301 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4512df: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4512e6u; native_call(m, M32(0x4a9188u));	/* 4512e0: call dword ptr [0x4a9188] */
	m->edi = m->eax;	/* 4512e6: mov edi, eax */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4512e8: add edi, 0x10 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4512eb: push edi */
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 4512ec: push 0x42 */
	m->esp -= 4; M32(m->esp) = 0x4512f4u; native_call(m, M32(0x4a9070u));	/* 4512ee: call dword ptr [0x4a9070] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4512f4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4512fbu; native_call(m, M32(0x4a9198u));	/* 4512f5: call dword ptr [0x4a9198] */
	m->esi = m->eax;	/* 4512fb: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4512fd: test esi, esi */
	if (!m->zf) goto L_451307;	/* 4512ff: jne 0x451307 */
L_451301:
	m->edi = M32(m->esp); m->esp += 4;	/* 451301: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 451302: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451303: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 451305: pop ebx */
	m->esp += 4 + 0; return;	/* 451306: ret  */
L_451307:
	M32((DWORD)(m->esi + 0x0u)) = 0x1u;	/* 451307: mov dword ptr [esi], 1 */
	m->ecx = M32((DWORD)(0xa0b424u));	/* 45130d: mov ecx, dword ptr [0xa0b424] */
	m->edx = (DWORD)(m->esi + 0xcu);	/* 451313: lea edx, [esi + 0xc] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 451316: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451317: push edx */
	M32((DWORD)(m->esi + 0x8u)) = m->ecx;	/* 451318: mov dword ptr [esi + 8], ecx */
	m->esp -= 4; M32(m->esp) = 0x451321u; native_call(m, M32(0x4a911cu));	/* 45131b: call dword ptr [0x4a911c] */
	m->eax = M32((DWORD)(0xa0b424u));	/* 451321: mov eax, dword ptr [0xa0b424] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 451326: push edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451327: push esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 451328: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45132a: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45132c: push eax */
	m->esp -= 4; M32(m->esp) = 0x451332u; native_call(m, 0x450bf0u);	/* 45132d: call 0x450bf0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451332: add esp, 0x14 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451335: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 451337: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 451339: setge cl */
	m->edi = M32(m->esp); m->esp += 4;	/* 45133c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45133d: pop esi */
	m->eax = m->ecx;	/* 45133e: mov eax, ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 451340: pop ebx */
	m->esp += 4 + 0; return;	/* 451341: ret  */
}

/* lobby_editTextField_405230 (0x405230), lifted by tools/lift.py */
static void lift_405230(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 405230: push edi */
	m->esp -= 4; M32(m->esp) = 0x405236u; native_call(m, 0x401460u);	/* 405231: call 0x401460 */
	{ DWORD v_ = 0x14u; m->esp -= 4; M32(m->esp) = v_; }	/* 405236: push 0x14 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 405238: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x405247u; native_call(m, 0x431560u);	/* 405242: call 0x431560 */
	m->ecx = 0x100u;	/* 405247: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40524c: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 40524e: mov edi, 0x9dc92c */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 405253: mov edx, dword ptr [0x4db8cc] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 405259: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40525b: mov ecx, dword ptr [0x4db8c8] */
	M32((DWORD)(0x4dbbd4u)) = m->eax;	/* 405261: mov dword ptr [0x4dbbd4], eax */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 405266: add ecx, 0xd8 */
	m->edi = 0x9dc92cu;	/* 40526c: mov edi, 0x9dc92c */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 405271: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405277: or ecx, 0xffffffff */
	{ DWORD a_ = m->edx, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40527a: add edx, 0xd0 */
	{ DWORD v_ = 0x14u; m->esp -= 4; M32(m->esp) = v_; }	/* 405280: push 0x14 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 405282: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 405284: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 405286: dec ecx */
	M32((DWORD)(0x4dbbd8u)) = m->eax;	/* 405287: mov dword ptr [0x4dbbd8], eax */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 40528c: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 405296: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 40529c: mov dword ptr [0x9dbf10], ecx */
	m->esp -= 4; M32(m->esp) = 0x4052a7u; native_call(m, 0x43f460u);	/* 4052a2: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4052a7: add esp, 8 */
	M32((DWORD)(0x4db714u)) = 0x1u;	/* 4052aa: mov dword ptr [0x4db714], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4052b4: pop edi */
	m->esp += 4 + 0; return;	/* 4052b5: ret  */
}

/* menu_4318b0 (0x4318b0), lifted by tools/lift.py */
static void lift_4318b0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae70u));	/* 4318b0: mov eax, dword ptr [0x9dae70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4318b5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4318bbu; native_call(m, 0x401600u);	/* 4318b6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4318bb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4318be: cmp eax, 1 */
	if (!m->zf) goto L_4318e0;	/* 4318c1: jne 0x4318e0 */
	m->eax = M32((DWORD)(0x4df01cu));	/* 4318c3: mov eax, dword ptr [0x4df01c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4318c8: test eax, eax */
	if (!m->zf) goto L_431942;	/* 4318ca: jne 0x431942 */
	M32((DWORD)(0x4df01cu)) = 0x1u;	/* 4318cc: mov dword ptr [0x4df01c], 1 */
	M32((DWORD)(0x4e0458u)) = 0x0u;	/* 4318d6: mov dword ptr [0x4e0458], 0 */
L_4318e0:
	m->ecx = M32((DWORD)(0x5b1da8u));	/* 4318e0: mov ecx, dword ptr [0x5b1da8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4318e6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4318ecu; native_call(m, 0x401600u);	/* 4318e7: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4318ec: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4318ef: cmp eax, 1 */
	if (!m->zf) goto L_431911;	/* 4318f2: jne 0x431911 */
	m->eax = M32((DWORD)(0x4df01cu));	/* 4318f4: mov eax, dword ptr [0x4df01c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4318f9: test eax, eax */
	if (!m->zf) goto L_431942;	/* 4318fb: jne 0x431942 */
	M32((DWORD)(0x4df01cu)) = 0x1u;	/* 4318fd: mov dword ptr [0x4df01c], 1 */
	M32((DWORD)(0x4e0458u)) = 0x0u;	/* 431907: mov dword ptr [0x4e0458], 0 */
L_431911:
	m->edx = M32((DWORD)(0x6803a0u));	/* 431911: mov edx, dword ptr [0x6803a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 431917: push edx */
	m->esp -= 4; M32(m->esp) = 0x43191du; native_call(m, 0x401600u);	/* 431918: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43191d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431920: cmp eax, 1 */
	if (!m->zf) goto L_431942;	/* 431923: jne 0x431942 */
	m->eax = M32((DWORD)(0x4df01cu));	/* 431925: mov eax, dword ptr [0x4df01c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43192a: test eax, eax */
	if (!m->zf) goto L_431942;	/* 43192c: jne 0x431942 */
	M32((DWORD)(0x4df01cu)) = 0x1u;	/* 43192e: mov dword ptr [0x4df01c], 1 */
	M32((DWORD)(0x4e0458u)) = 0x0u;	/* 431938: mov dword ptr [0x4e0458], 0 */
L_431942:
	m->esp += 4 + 0; return;	/* 431942: ret  */
}

/* arena_452fe0 (0x452fe0), lifted by tools/lift.py */
static void lift_452fe0(X86 *m)
{
	m->ecx = M32((DWORD)(0xa0b390u));	/* 452fe0: mov ecx, dword ptr [0xa0b390] */
	m->eax = 0x1u;	/* 452fe6: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452feb: cmp ecx, eax */
	if (!m->zf) goto L_453075;	/* 452fed: jne 0x453075 */
	m->ecx = M32((DWORD)(0xa0b384u));	/* 452ff3: mov ecx, dword ptr [0xa0b384] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452ff9: test ecx, ecx */
	if (m->zf) goto L_453075;	/* 452ffb: je 0x453075 */
	m->ecx = M32((DWORD)(0xa0baf8u));	/* 452ffd: mov ecx, dword ptr [0xa0baf8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453003: test ecx, ecx */
	if (m->zf) goto L_45301d;	/* 453005: je 0x45301d */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453007: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453009: push 0 */
	{ DWORD v_ = 0x9f9418u; m->esp -= 4; M32(m->esp) = v_; }	/* 45300b: push 0x9f9418 */
	M32((DWORD)(0x9f941cu)) = m->eax;	/* 453010: mov dword ptr [0x9f941c], eax */
	m->esp -= 4; M32(m->esp) = 0x45301au; native_call(m, 0x451270u);	/* 453015: call 0x451270 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45301a: add esp, 0xc */
L_45301d:
	m->eax = M32((DWORD)(0xa0b418u));	/* 45301d: mov eax, dword ptr [0xa0b418] */
	M32((DWORD)(0xa0b418u)) = 0x4u;	/* 453022: mov dword ptr [0xa0b418], 4 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45302c: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_453052;	/* 45302f: ja 0x453052 */
	switch (m->eax) { case 0: goto L_453038; case 1: goto L_45303f; case 2: goto L_453046; case 3: goto L_45304d; default: abort(); }	/* 453031: jmp dword ptr [eax*4 + 0x453078] */
L_453038:
	m->esp -= 4; M32(m->esp) = 0x45303du; native_call(m, 0x4549a0u);	/* 453038: call 0x4549a0 */
	goto L_453052;	/* 45303d: jmp 0x453052 */
L_45303f:
	m->esp -= 4; M32(m->esp) = 0x453044u; native_call(m, 0x454ac0u);	/* 45303f: call 0x454ac0 */
	goto L_453052;	/* 453044: jmp 0x453052 */
L_453046:
	m->esp -= 4; M32(m->esp) = 0x45304bu; native_call(m, 0x454bd0u);	/* 453046: call 0x454bd0 */
	goto L_453052;	/* 45304b: jmp 0x453052 */
L_45304d:
	m->esp -= 4; M32(m->esp) = 0x453052u; native_call(m, 0x454ce0u);	/* 45304d: call 0x454ce0 */
L_453052:
	m->esp -= 4; M32(m->esp) = 0x453057u; native_call(m, 0x454130u);	/* 453052: call 0x454130 */
	M32((DWORD)(0xa0b384u)) = 0x0u;	/* 453057: mov dword ptr [0xa0b384], 0 */
	M32((DWORD)(0xa0b388u)) = 0x0u;	/* 453061: mov dword ptr [0xa0b388], 0 */
	M32((DWORD)(0xa0b390u)) = 0x0u;	/* 45306b: mov dword ptr [0xa0b390], 0 */
L_453075:
	m->esp += 4 + 0; return;	/* 453075: ret  */
}

/* arena_editTextField_404cd0 (0x404cd0), lifted by tools/lift.py */
static void lift_404cd0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 404cd0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 404cd1: push edi */
	m->esp -= 4; M32(m->esp) = 0x404cd7u; native_call(m, 0x401460u);	/* 404cd2: call 0x401460 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 404cd7: push 0x10 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 404cd9: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x404ce8u; native_call(m, 0x431560u);	/* 404ce3: call 0x431560 */
	m->edi = 0x4db560u;	/* 404ce8: mov edi, 0x4db560 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404ced: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404cf0: xor eax, eax */
	m->edx = M32((DWORD)(0x4dbb6cu));	/* 404cf2: mov edx, dword ptr [0x4dbb6c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404cf8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404cfa: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 404cfc: sub edi, ecx */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 404cfe: add edx, 0x64 */
	m->eax = m->ecx;	/* 404d01: mov eax, ecx */
	m->esi = m->edi;	/* 404d03: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 404d05: mov edi, 0x9dc92c */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 404d0a: push 0x10 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 404d0c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 404d0f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 404d11: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404d13: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404d15: and ecx, 3 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 404d18: mov dword ptr [0x9da434], 0x40a00000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 404d22: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dbb68u));	/* 404d24: mov ecx, dword ptr [0x4dbb68] */
	m->edi = 0x9dc92cu;	/* 404d2a: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xc2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 404d2f: add ecx, 0xc2 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 404d35: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 404d3b: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404d41: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404d44: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404d46: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 404d48: dec ecx */
	M32((DWORD)(0x4dbbd0u)) = 0x1u;	/* 404d49: mov dword ptr [0x4dbbd0], 1 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 404d53: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x4e1868u)) = m->eax;	/* 404d59: mov dword ptr [0x4e1868], eax */
	m->esp -= 4; M32(m->esp) = 0x404d63u; native_call(m, 0x43f460u);	/* 404d5e: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404d63: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 404d66: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 404d67: pop esi */
	m->esp += 4 + 0; return;	/* 404d68: ret  */
}

/* arena_editTextField_404d70 (0x404d70), lifted by tools/lift.py */
static void lift_404d70(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 404d70: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 404d71: push edi */
	m->esp -= 4; M32(m->esp) = 0x404d77u; native_call(m, 0x401460u);	/* 404d72: call 0x401460 */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 404d77: push 0x1e */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 404d79: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x404d88u; native_call(m, 0x431560u);	/* 404d83: call 0x431560 */
	m->edi = 0x4db528u;	/* 404d88: mov edi, 0x4db528 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404d8d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404d90: xor eax, eax */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 404d92: mov edx, dword ptr [0x4dbb04] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404d98: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404d9a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 404d9c: sub edi, ecx */
	{ DWORD a_ = m->edx, b_ = 0x32u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 404d9e: add edx, 0x32 */
	m->eax = m->ecx;	/* 404da1: mov eax, ecx */
	m->esi = m->edi;	/* 404da3: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 404da5: mov edi, 0x9dc92c */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 404daa: push 0x1e */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 404dac: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 404daf: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 404db1: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404db3: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404db5: and ecx, 3 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 404db8: mov dword ptr [0x9da434], 0x40a00000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 404dc2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dbb00u));	/* 404dc4: mov ecx, dword ptr [0x4dbb00] */
	m->edi = 0x9dc92cu;	/* 404dca: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 404dcf: add ecx, 0xa4 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 404dd5: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 404ddb: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404de1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404de4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404de6: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 404de8: dec ecx */
	M32((DWORD)(0x4dbab0u)) = 0x1u;	/* 404de9: mov dword ptr [0x4dbab0], 1 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 404df3: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x4e1868u)) = m->eax;	/* 404df9: mov dword ptr [0x4e1868], eax */
	m->esp -= 4; M32(m->esp) = 0x404e03u; native_call(m, 0x43f460u);	/* 404dfe: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404e03: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 404e06: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 404e07: pop esi */
	m->esp += 4 + 0; return;	/* 404e08: ret  */
}

/* room_4339e0 (0x4339e0), lifted by tools/lift.py */
static void lift_4339e0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4339e0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4339e1: push edi */
	m->esp -= 4; M32(m->esp) = 0x4339e7u; native_call(m, 0x401460u);	/* 4339e2: call 0x401460 */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 4339e7: push 0x1e */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 4339e9: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x4339f8u; native_call(m, 0x431560u);	/* 4339f3: call 0x431560 */
	m->edi = 0x4df9c8u;	/* 4339f8: mov edi, 0x4df9c8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4339fd: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433a00: xor eax, eax */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 433a02: mov edx, dword ptr [0x9dd1bc] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433a08: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433a0a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433a0c: sub edi, ecx */
	{ DWORD a_ = m->edx, b_ = 0x32u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 433a0e: add edx, 0x32 */
	m->eax = m->ecx;	/* 433a11: mov eax, ecx */
	m->esi = m->edi;	/* 433a13: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 433a15: mov edi, 0x9dc92c */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 433a1a: push 0x1e */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433a1c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433a1f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 433a21: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433a23: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433a25: and ecx, 3 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 433a28: mov dword ptr [0x9da434], 0x40a00000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433a32: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 433a34: mov ecx, dword ptr [0x9dd1b8] */
	m->edi = 0x9dc92cu;	/* 433a3a: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 433a3f: add ecx, 0xa4 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 433a45: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 433a4b: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433a51: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433a54: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433a56: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 433a58: dec ecx */
	M32((DWORD)(0x9dd380u)) = 0x1u;	/* 433a59: mov dword ptr [0x9dd380], 1 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 433a63: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x4e1868u)) = m->eax;	/* 433a69: mov dword ptr [0x4e1868], eax */
	m->esp -= 4; M32(m->esp) = 0x433a73u; native_call(m, 0x43f460u);	/* 433a6e: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433a73: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 433a76: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433a77: pop esi */
	m->esp += 4 + 0; return;	/* 433a78: ret  */
}

/* sound_loadMenuSounds (0x42bd40), lifted by tools/lift.py */
static void lift_42bd40(X86 *m)
{
	{ DWORD v_ = 0x4b1644u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bd40: push 0x4b1644 */
	m->esp -= 4; M32(m->esp) = 0x42bd4au; native_call(m, 0x467b90u);	/* 42bd45: call 0x467b90 */
	{ DWORD v_ = 0x4b1628u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bd4a: push 0x4b1628 */
	M32((DWORD)(0x4dd4d4u)) = m->eax;	/* 42bd4f: mov dword ptr [0x4dd4d4], eax */
	m->esp -= 4; M32(m->esp) = 0x42bd59u; native_call(m, 0x467b90u);	/* 42bd54: call 0x467b90 */
	{ DWORD v_ = 0x4b1610u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bd59: push 0x4b1610 */
	M32((DWORD)(0x4dd4d8u)) = m->eax;	/* 42bd5e: mov dword ptr [0x4dd4d8], eax */
	m->esp -= 4; M32(m->esp) = 0x42bd68u; native_call(m, 0x467b90u);	/* 42bd63: call 0x467b90 */
	{ DWORD v_ = 0x4b15f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bd68: push 0x4b15f4 */
	M32((DWORD)(0x4dd4dcu)) = m->eax;	/* 42bd6d: mov dword ptr [0x4dd4dc], eax */
	m->esp -= 4; M32(m->esp) = 0x42bd77u; native_call(m, 0x467b90u);	/* 42bd72: call 0x467b90 */
	{ DWORD v_ = 0x4b15dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bd77: push 0x4b15dc */
	M32((DWORD)(0x4dd4e0u)) = m->eax;	/* 42bd7c: mov dword ptr [0x4dd4e0], eax */
	m->esp -= 4; M32(m->esp) = 0x42bd86u; native_call(m, 0x467b90u);	/* 42bd81: call 0x467b90 */
	{ DWORD v_ = 0x4b15c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bd86: push 0x4b15c4 */
	M32((DWORD)(0x4dd4e4u)) = m->eax;	/* 42bd8b: mov dword ptr [0x4dd4e4], eax */
	m->esp -= 4; M32(m->esp) = 0x42bd95u; native_call(m, 0x467b90u);	/* 42bd90: call 0x467b90 */
	{ DWORD v_ = 0x4b15b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bd95: push 0x4b15b0 */
	M32((DWORD)(0x4dd4e8u)) = m->eax;	/* 42bd9a: mov dword ptr [0x4dd4e8], eax */
	m->esp -= 4; M32(m->esp) = 0x42bda4u; native_call(m, 0x467b90u);	/* 42bd9f: call 0x467b90 */
	{ DWORD v_ = 0x4b1598u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bda4: push 0x4b1598 */
	M32((DWORD)(0x4dd4ecu)) = m->eax;	/* 42bda9: mov dword ptr [0x4dd4ec], eax */
	m->esp -= 4; M32(m->esp) = 0x42bdb3u; native_call(m, 0x467b90u);	/* 42bdae: call 0x467b90 */
	{ DWORD v_ = 0x4b1580u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bdb3: push 0x4b1580 */
	M32((DWORD)(0x4dd4f0u)) = m->eax;	/* 42bdb8: mov dword ptr [0x4dd4f0], eax */
	m->esp -= 4; M32(m->esp) = 0x42bdc2u; native_call(m, 0x467b90u);	/* 42bdbd: call 0x467b90 */
	{ DWORD v_ = 0x4b1564u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bdc2: push 0x4b1564 */
	M32((DWORD)(0x4dd4f4u)) = m->eax;	/* 42bdc7: mov dword ptr [0x4dd4f4], eax */
	m->esp -= 4; M32(m->esp) = 0x42bdd1u; native_call(m, 0x467b90u);	/* 42bdcc: call 0x467b90 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bdd1: add esp, 0x28 */
	M32((DWORD)(0x4dd4f8u)) = m->eax;	/* 42bdd4: mov dword ptr [0x4dd4f8], eax */
	m->esp += 4 + 0; return;	/* 42bdd9: ret  */
}

/* menu_437240 (0x437240), lifted by tools/lift.py */
static void lift_437240(X86 *m)
{
	m->eax = M32((DWORD)(0x68039cu));	/* 437240: mov eax, dword ptr [0x68039c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 437245: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 437246: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437248: cmp eax, esi */
	if (!m->zf) goto L_4372e0;	/* 43724a: jne 0x4372e0 */
	{ DWORD a_ = M32((DWORD)(0x9dd6d4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437250: cmp dword ptr [0x9dd6d4], 1 */
	if (!m->zf) goto L_43727c;	/* 437257: jne 0x43727c */
	m->eax = M32((DWORD)(0x76d48cu));	/* 437259: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43725e: push eax */
	m->esp -= 4; M32(m->esp) = 0x437264u; native_call(m, 0x401600u);	/* 43725f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437264: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437267: test eax, eax */
	if (m->zf) goto L_4372e0;	/* 437269: je 0x4372e0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43726b: push esi */
	m->esp -= 4; M32(m->esp) = 0x437271u; native_call(m, 0x41e760u);	/* 43726c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437271: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = m->esi;	/* 437274: mov dword ptr [0x9dce48], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43727a: pop esi */
	m->esp += 4 + 0; return;	/* 43727b: ret  */
L_43727c:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 43727c: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 437282: push ecx */
	m->esp -= 4; M32(m->esp) = 0x437288u; native_call(m, 0x401600u);	/* 437283: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437288: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43728b: test eax, eax */
	if (m->zf) goto L_4372ac;	/* 43728d: je 0x4372ac */
	m->esp -= 4; M32(m->esp) = 0x437294u; native_call(m, 0x434b90u);	/* 43728f: call 0x434b90 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437294: cmp eax, 1 */
	if (m->zf) goto L_4372d1;	/* 437297: je 0x4372d1 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 437299: push 6 */
	m->esp -= 4; M32(m->esp) = 0x4372a0u; native_call(m, 0x41e760u);	/* 43729b: call 0x41e760 */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 4372a0: push 5 */
	m->esp -= 4; M32(m->esp) = 0x4372a7u; native_call(m, 0x41ee40u);	/* 4372a2: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4372a7: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4372aa: pop esi */
	m->esp += 4 + 0; return;	/* 4372ab: ret  */
L_4372ac:
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 4372ac: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4372b2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4372b8u; native_call(m, 0x401600u);	/* 4372b3: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4372b8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4372bb: test eax, eax */
	if (!m->zf) goto L_4372d1;	/* 4372bd: jne 0x4372d1 */
	m->eax = M32((DWORD)(0x76d48cu));	/* 4372bf: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4372c4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4372cau; native_call(m, 0x401600u);	/* 4372c5: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4372ca: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4372cd: test eax, eax */
	if (m->zf) goto L_4372e0;	/* 4372cf: je 0x4372e0 */
L_4372d1:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4372d1: push esi */
	m->esp -= 4; M32(m->esp) = 0x4372d7u; native_call(m, 0x41e760u);	/* 4372d2: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4372d7: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = m->esi;	/* 4372da: mov dword ptr [0x9dce48], esi */
L_4372e0:
	m->esi = M32(m->esp); m->esp += 4;	/* 4372e0: pop esi */
	m->esp += 4 + 0; return;	/* 4372e1: ret  */
}

/* room_403590 (0x403590), lifted by tools/lift.py */
static void lift_403590(X86 *m)
{
	m->eax = M32((DWORD)(0x67ef24u));	/* 403590: mov eax, dword ptr [0x67ef24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403595: push eax */
	m->esp -= 4; M32(m->esp) = 0x40359bu; native_call(m, 0x401590u);	/* 403596: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40359b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40359e: test eax, eax */
	if (!m->zf) goto L_403601;	/* 4035a0: jne 0x403601 */
	m->ecx = M32((DWORD)(0x9db0acu));	/* 4035a2: mov ecx, dword ptr [0x9db0ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4035a8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4035aeu; native_call(m, 0x401590u);	/* 4035a9: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4035ae: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4035b1: test eax, eax */
	if (!m->zf) goto L_403601;	/* 4035b3: jne 0x403601 */
	m->edx = M32((DWORD)(0x6803a8u));	/* 4035b5: mov edx, dword ptr [0x6803a8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4035bb: push edx */
	m->esp -= 4; M32(m->esp) = 0x4035c1u; native_call(m, 0x401590u);	/* 4035bc: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4035c1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4035c4: test eax, eax */
	if (!m->zf) goto L_403601;	/* 4035c6: jne 0x403601 */
	m->eax = M32((DWORD)(0x9dad8cu));	/* 4035c8: mov eax, dword ptr [0x9dad8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4035cd: push eax */
	m->esp -= 4; M32(m->esp) = 0x4035d3u; native_call(m, 0x401590u);	/* 4035ce: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4035d3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4035d6: test eax, eax */
	if (!m->zf) goto L_403601;	/* 4035d8: jne 0x403601 */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4035da: mov eax, dword ptr [esp + 4] */
	m->edx = M32((DWORD)(m->eax*8 + 0x4d735cu));	/* 4035de: mov edx, dword ptr [eax*8 + 0x4d735c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4035e5: inc edx */
	m->ecx = m->edx;	/* 4035e6: mov ecx, edx */
	M32((DWORD)(m->eax*8 + 0x4d735cu)) = m->edx;	/* 4035e8: mov dword ptr [eax*8 + 0x4d735c], edx */
	{ DWORD a_ = m->ecx, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4035ef: cmp ecx, 0xd */
	if (m->zf || m->sf != m->of) goto L_403621;	/* 4035f2: jle 0x403621 */
	M32((DWORD)(m->eax*8 + 0x4d735cu)) = 0x0u;	/* 4035f4: mov dword ptr [eax*8 + 0x4d735c], 0 */
	goto L_403621;	/* 4035ff: jmp 0x403621 */
L_403601:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 403601: mov eax, dword ptr [esp + 4] */
	m->ecx = M32((DWORD)(m->eax*8 + 0x4d735cu));	/* 403605: mov ecx, dword ptr [eax*8 + 0x4d735c] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40360c: dec ecx */
	M32((DWORD)(m->eax*8 + 0x4d735cu)) = m->ecx;	/* 40360d: mov dword ptr [eax*8 + 0x4d735c], ecx */
	if (!m->sf) goto L_403621;	/* 403614: jns 0x403621 */
	M32((DWORD)(m->eax*8 + 0x4d735cu)) = 0xdu;	/* 403616: mov dword ptr [eax*8 + 0x4d735c], 0xd */
L_403621:
	{ DWORD a_ = m->eax, b_ = 0x16u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403621: cmp eax, 0x16 */
	if (m->sf != m->of) goto L_403636;	/* 403624: jl 0x403636 */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403626: cmp eax, 0x18 */
	if (!m->zf && m->sf == m->of) goto L_403636;	/* 403629: jg 0x403636 */
	M32((DWORD)(m->eax*8 + 0x4d735cu)) = 0x0u;	/* 40362b: mov dword ptr [eax*8 + 0x4d735c], 0 */
L_403636:
	m->esp += 4 + 0; return;	/* 403636: ret  */
}

/* room_433b00 (0x433b00), lifted by tools/lift.py */
static void lift_433b00(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 433b00: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 433b01: push edi */
	m->esp -= 4; M32(m->esp) = 0x433b07u; native_call(m, 0x401460u);	/* 433b02: call 0x401460 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 433b07: push 0x10 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 433b09: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x433b18u; native_call(m, 0x431560u);	/* 433b13: call 0x431560 */
	m->ecx = 0x100u;	/* 433b18: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433b1d: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 433b1f: mov edi, 0x9dc92c */
	m->edx = M32((DWORD)(0x9dd35cu));	/* 433b24: mov edx, dword ptr [0x9dd35c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 433b2a: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dd1d8u;	/* 433b2c: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433b31: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433b34: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433b36: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433b38: sub edi, ecx */
	{ DWORD a_ = m->edx, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 433b3a: add edx, 0x58 */
	m->eax = m->ecx;	/* 433b3d: mov eax, ecx */
	m->esi = m->edi;	/* 433b3f: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 433b41: mov edi, 0x9dc92c */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 433b46: push 0x10 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433b48: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433b4b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 433b4d: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433b4f: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433b51: and ecx, 3 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 433b54: mov dword ptr [0x9da434], 0x40a00000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433b5e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd358u));	/* 433b60: mov ecx, dword ptr [0x9dd358] */
	m->edi = 0x9dc92cu;	/* 433b66: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 433b6b: add ecx, 0xc8 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 433b71: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 433b77: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433b7d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433b80: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433b82: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 433b84: dec ecx */
	M32((DWORD)(0x9dd830u)) = 0x1u;	/* 433b85: mov dword ptr [0x9dd830], 1 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 433b8f: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x9dd38cu)) = m->eax;	/* 433b95: mov dword ptr [0x9dd38c], eax */
	M32((DWORD)(0x4e1868u)) = m->eax;	/* 433b9a: mov dword ptr [0x4e1868], eax */
	m->esp -= 4; M32(m->esp) = 0x433ba4u; native_call(m, 0x43f460u);	/* 433b9f: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433ba4: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 433ba7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433ba8: pop esi */
	m->esp += 4 + 0; return;	/* 433ba9: ret  */
}

/* arena_editNumberField_404ed0 (0x404ed0), lifted by tools/lift.py */
static void lift_404ed0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404ed0: sub esp, 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 404ed3: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 404ed4: push edi */
	m->esp -= 4; M32(m->esp) = 0x404edau; native_call(m, 0x401460u);	/* 404ed5: call 0x401460 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 404eda: push 3 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 404edc: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x404eebu; native_call(m, 0x431560u);	/* 404ee6: call 0x431560 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404eeb: xor ecx, ecx */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 404eed: lea eax, [esp + 0xc] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54du))) & 0xff) << 0);	/* 404ef1: mov cl, byte ptr [0x4db54d] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 404ef7: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 404ef9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 404efa: push ecx */
	m->esp -= 4; M32(m->esp) = 0x404f00u; native_call(m, 0x49fb53u);	/* 404efb: call 0x49fb53 */
	m->edi = (DWORD)(m->esp + 0x18u);	/* 404f00: lea edi, [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404f04: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404f07: xor eax, eax */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 404f09: push 3 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404f0b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404f0d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 404f0f: sub edi, ecx */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 404f11: mov eax, dword ptr [0x4dbb00] */
	m->edx = m->ecx;	/* 404f16: mov edx, ecx */
	m->esi = m->edi;	/* 404f18: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 404f1a: mov edi, 0x9dc92c */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 404f1f: add eax, 0xa4 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 404f24: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 404f27: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 404f29: mov ecx, edx */
	M32((DWORD)(0x9da3d8u)) = m->eax;	/* 404f2b: mov dword ptr [0x9da3d8], eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404f30: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404f33: xor eax, eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 404f35: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 404f37: mov ecx, dword ptr [0x4dbb04] */
	m->edi = 0x9dc92cu;	/* 404f3d: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0x120u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 404f42: add ecx, 0x120 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 404f48: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9da3dcu)) = m->ecx;	/* 404f52: mov dword ptr [0x9da3dc], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404f58: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404f5b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404f5d: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 404f5f: dec ecx */
	M32((DWORD)(0x4db518u)) = 0x1u;	/* 404f60: mov dword ptr [0x4db518], 1 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 404f6a: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x4e1868u)) = m->eax;	/* 404f70: mov dword ptr [0x4e1868], eax */
	m->esp -= 4; M32(m->esp) = 0x404f7au; native_call(m, 0x43f460u);	/* 404f75: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404f7a: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 404f7d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 404f7e: pop esi */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404f7f: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 404f82: ret  */
}

/* setup_soundTabKeys (0x422c60), lifted by tools/lift.py */
static void lift_422c60(X86 *m)
{
	m->eax = M32((DWORD)(0x4e0cd4u));	/* 422c60: mov eax, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422c65: push eax */
	m->esp -= 4; M32(m->esp) = 0x422c6bu; native_call(m, 0x401600u);	/* 422c66: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422c6b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422c6e: test eax, eax */
	if (m->zf) goto L_422cd9;	/* 422c70: je 0x422cd9 */
	m->eax = M32((DWORD)(0x4dde98u));	/* 422c72: mov eax, dword ptr [0x4dde98] */
	m->edx = M32((DWORD)(0x4ddea0u));	/* 422c77: mov edx, dword ptr [0x4ddea0] */
	m->ecx = M32((DWORD)(0x4dde9cu));	/* 422c7d: mov ecx, dword ptr [0x4dde9c] */
	M32((DWORD)(0x4e0c98u)) = m->edx;	/* 422c83: mov dword ptr [0x4e0c98], edx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0xfffffe0cu);	/* 422c89: lea edx, [eax + eax*4 - 0x1f4] */
	M32((DWORD)(0x4e0c94u)) = m->ecx;	/* 422c90: mov dword ptr [0x4e0c94], ecx */
	m->ecx = M32((DWORD)(0x4ddea4u));	/* 422c96: mov ecx, dword ptr [0x4ddea4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422c9c: push 0 */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 422c9e: shl edx, 2 */
	M32((DWORD)(0x4e0c90u)) = m->eax;	/* 422ca1: mov dword ptr [0x4e0c90], eax */
	M32((DWORD)(0x4e0c9cu)) = m->ecx;	/* 422ca6: mov dword ptr [0x4e0c9c], ecx */
	M32((DWORD)(0x4dd984u)) = m->edx;	/* 422cac: mov dword ptr [0x4dd984], edx */
	m->esp -= 4; M32(m->esp) = 0x422cb7u; native_call(m, 0x41e760u);	/* 422cb2: call 0x41e760 */
	m->esp -= 4; M32(m->esp) = 0x422cbcu; native_call(m, 0x42d730u);	/* 422cb7: call 0x42d730 */
	M32((DWORD)(0x4ddcecu)) = 0x0u;	/* 422cbc: mov dword ptr [0x4ddcec], 0 */
	m->esp -= 4; M32(m->esp) = 0x422ccbu; native_call(m, 0x457310u);	/* 422cc6: call 0x457310 */
	{ DWORD v_ = 0x4b01ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 422ccb: push 0x4b01cc */
	m->esp -= 4; M32(m->esp) = 0x422cd5u; native_call(m, 0x457150u);	/* 422cd0: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422cd5: add esp, 8 */
	m->esp += 4 + 0; return;	/* 422cd8: ret  */
L_422cd9:
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 422cd9: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422cde: push eax */
	m->esp -= 4; M32(m->esp) = 0x422ce4u; native_call(m, 0x401600u);	/* 422cdf: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422ce4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422ce7: test eax, eax */
	if (!m->zf) goto L_422cfe;	/* 422ce9: jne 0x422cfe */
	m->ecx = M32((DWORD)(0x76d48cu));	/* 422ceb: mov ecx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 422cf1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x422cf7u; native_call(m, 0x401600u);	/* 422cf2: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422cf7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422cfa: test eax, eax */
	if (m->zf) goto L_422d12;	/* 422cfc: je 0x422d12 */
L_422cfe:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422cfe: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422d05u; native_call(m, 0x41e760u);	/* 422d00: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422d05: add esp, 4 */
	M32((DWORD)(0x4ddcecu)) = 0x0u;	/* 422d08: mov dword ptr [0x4ddcec], 0 */
L_422d12:
	m->esp += 4 + 0; return;	/* 422d12: ret  */
}

/* arena_editNumberField_404e10 (0x404e10), lifted by tools/lift.py */
static void lift_404e10(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404e10: sub esp, 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 404e13: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 404e14: push edi */
	m->esp -= 4; M32(m->esp) = 0x404e1au; native_call(m, 0x401460u);	/* 404e15: call 0x401460 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 404e1a: push 3 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 404e1c: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x404e2bu; native_call(m, 0x431560u);	/* 404e26: call 0x431560 */
	m->ecx = M32((DWORD)(0x4db54cu));	/* 404e2b: mov ecx, dword ptr [0x4db54c] */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 404e31: lea eax, [esp + 0xc] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 404e35: push 0xa */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404e37: and ecx, 0xff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 404e3d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 404e3e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x404e44u; native_call(m, 0x49fb53u);	/* 404e3f: call 0x49fb53 */
	m->edi = (DWORD)(m->esp + 0x18u);	/* 404e44: lea edi, [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404e48: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404e4b: xor eax, eax */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 404e4d: push 3 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404e4f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404e51: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 404e53: sub edi, ecx */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 404e55: mov eax, dword ptr [0x4dbb00] */
	m->edx = m->ecx;	/* 404e5a: mov edx, ecx */
	m->esi = m->edi;	/* 404e5c: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 404e5e: mov edi, 0x9dc92c */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 404e63: add eax, 0xa4 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 404e68: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 404e6b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 404e6d: mov ecx, edx */
	M32((DWORD)(0x9da3d8u)) = m->eax;	/* 404e6f: mov dword ptr [0x9da3d8], eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404e74: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 404e77: xor eax, eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 404e79: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 404e7b: mov ecx, dword ptr [0x4dbb04] */
	m->edi = 0x9dc92cu;	/* 404e81: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xfeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 404e86: add ecx, 0xfe */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 404e8c: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9da3dcu)) = m->ecx;	/* 404e96: mov dword ptr [0x9da3dc], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 404e9c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 404e9f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 404ea1: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 404ea3: dec ecx */
	M32((DWORD)(0x4db850u)) = 0x1u;	/* 404ea4: mov dword ptr [0x4db850], 1 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 404eae: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x4e1868u)) = m->eax;	/* 404eb4: mov dword ptr [0x4e1868], eax */
	m->esp -= 4; M32(m->esp) = 0x404ebeu; native_call(m, 0x43f460u);	/* 404eb9: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404ebe: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 404ec1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 404ec2: pop esi */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 404ec3: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 404ec6: ret  */
}

/* room_434260 (0x434260), lifted by tools/lift.py */
static void lift_434260(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 434260: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434261: push edi */
	m->esp -= 4; M32(m->esp) = 0x434267u; native_call(m, 0x401460u);	/* 434262: call 0x401460 */
	{ DWORD v_ = 0x32u; m->esp -= 4; M32(m->esp) = v_; }	/* 434267: push 0x32 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 434269: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x434278u; native_call(m, 0x431560u);	/* 434273: call 0x431560 */
	m->ecx = 0x100u;	/* 434278: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43427d: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43427f: mov edi, 0x9dc92c */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 434284: mov edx, dword ptr [0x9dd36c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43428a: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dd20eu;	/* 43428c: mov edi, 0x9dd20e */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434291: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434294: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434296: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434298: sub edi, ecx */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43429a: add edx, 0xa4 */
	m->eax = m->ecx;	/* 4342a0: mov eax, ecx */
	m->esi = m->edi;	/* 4342a2: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 4342a4: mov edi, 0x9dc92c */
	{ DWORD v_ = 0x32u; m->esp -= 4; M32(m->esp) = v_; }	/* 4342a9: push 0x32 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4342ab: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4342ae: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4342b0: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4342b2: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4342b4: and ecx, 3 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 4342b7: mov dword ptr [0x9da434], 0x40a00000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4342c1: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 4342c3: mov ecx, dword ptr [0x9dd368] */
	m->edi = 0x9dc92cu;	/* 4342c9: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4342ce: add ecx, 0x98 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 4342d4: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 4342da: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4342e0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4342e3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4342e5: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4342e7: dec ecx */
	M32((DWORD)(0x9dd69cu)) = m->eax;	/* 4342e8: mov dword ptr [0x9dd69c], eax */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 4342ed: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x9dd37cu)) = m->eax;	/* 4342f3: mov dword ptr [0x9dd37c], eax */
	M32((DWORD)(0x9dd378u)) = m->eax;	/* 4342f8: mov dword ptr [0x9dd378], eax */
	M32((DWORD)(0x9dd304u)) = 0x1u;	/* 4342fd: mov dword ptr [0x9dd304], 1 */
	M32((DWORD)(0x4e1868u)) = m->eax;	/* 434307: mov dword ptr [0x4e1868], eax */
	m->esp -= 4; M32(m->esp) = 0x434311u; native_call(m, 0x43f460u);	/* 43430c: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434311: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 434314: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 434315: pop esi */
	m->esp += 4 + 0; return;	/* 434316: ret  */
}

/* sound_playFile (0x457080), lifted by tools/lift.py */
static void lift_457080(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e80cu));	/* 457080: mov eax, dword ptr [0xa0e80c] */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 457085: sub esp, 0x104 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45708b: test eax, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45708d: push esi */
	if (m->zf) goto L_457130;	/* 45708e: je 0x457130 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 457094: push edi */
	m->edi = M32((DWORD)(m->esp + 0x110u));	/* 457095: mov edi, dword ptr [esp + 0x110] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45709c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45709f: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4570a1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4570a3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4570a5: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0xcu);	/* 4570a7: lea edx, [esp + 0xc] */
	m->eax = m->ecx;	/* 4570ab: mov eax, ecx */
	m->esi = m->edi;	/* 4570ad: mov esi, edi */
	m->edi = m->edx;	/* 4570af: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4570b1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4570b4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4570b6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4570b8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4570bb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0xcu);	/* 4570bd: lea ecx, [esp + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4570c1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4570c7u; native_call(m, 0x467b90u);	/* 4570c2: call 0x467b90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4570c7: add esp, 4 */
	m->esi = m->eax;	/* 4570ca: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4570cc: test esi, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4570ce: pop edi */
	if (m->zf) goto L_457130;	/* 4570cf: je 0x457130 */
	m->eax = M32((DWORD)(m->esp + 0x110u));	/* 4570d1: mov eax, dword ptr [esp + 0x110] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4570d8: test eax, eax */
	if (m->sf == m->of) goto L_4570e3;	/* 4570da: jge 0x4570e3 */
	m->eax = 0xfffffc18u;	/* 4570dc: mov eax, 0xfffffc18 */
	goto L_45711a;	/* 4570e1: jmp 0x45711a */
L_4570e3:
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4570e3: cmp eax, 0x64 */
	if (m->zf || m->sf != m->of) goto L_4570ef;	/* 4570e6: jle 0x4570ef */
	m->eax = M32((DWORD)(0xa0e66cu));	/* 4570e8: mov eax, dword ptr [0xa0e66c] */
	goto L_45711a;	/* 4570ed: jmp 0x45711a */
L_4570ef:
	m->edx = M32((DWORD)(0xa0e66cu));	/* 4570ef: mov edx, dword ptr [0xa0e66c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x110u)));	/* 4570f5: fild dword ptr [esp + 0x110] */
	{ DWORD a_ = m->edx, b_ = 0x2710u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4570fc: add edx, 0x2710 */
	M32((DWORD)(m->esp + 0x4u)) = m->edx;	/* 457102: mov dword ptr [esp + 4], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 457106: fmul dword ptr [0x4a9504] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x4u));	/* 45710c: fimul dword ptr [esp + 4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 457110: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 457115: sub eax, 0x2710 */
L_45711a:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45711a: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45711b: push esi */
	m->esp -= 4; M32(m->esp) = 0x457121u; native_call(m, 0x467db0u);	/* 45711c: call 0x467db0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 457121: push esi */
	m->esp -= 4; M32(m->esp) = 0x457127u; native_call(m, 0x467d70u);	/* 457122: call 0x467d70 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 457127: push esi */
	m->esp -= 4; M32(m->esp) = 0x45712du; native_call(m, 0x467d60u);	/* 457128: call 0x467d60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45712d: add esp, 0x10 */
L_457130:
	m->esi = M32(m->esp); m->esp += 4;	/* 457130: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 457131: add esp, 0x104 */
	m->esp += 4 + 0; return;	/* 457137: ret  */
}

/* room_434020 (0x434020), lifted by tools/lift.py */
static void lift_434020(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 434020: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434021: push edi */
	m->esp -= 4; M32(m->esp) = 0x434027u; native_call(m, 0x401460u);	/* 434022: call 0x401460 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 434027: push 0xc */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 434029: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x434038u; native_call(m, 0x431560u);	/* 434033: call 0x431560 */
	m->ecx = 0x100u;	/* 434038: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43403d: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43403f: mov edi, 0x9dc92c */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 434044: mov edx, dword ptr [0x9dd36c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43404a: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dd6d8u;	/* 43404c: mov edi, 0x9dd6d8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434051: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434054: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434056: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434058: sub edi, ecx */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43405a: add edx, 0x50 */
	m->eax = m->ecx;	/* 43405d: mov eax, ecx */
	m->esi = m->edi;	/* 43405f: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 434061: mov edi, 0x9dc92c */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 434066: push 0xc */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434068: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43406b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43406d: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43406f: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434071: and ecx, 3 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 434074: mov dword ptr [0x9da434], 0x40a00000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43407e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 434080: mov ecx, dword ptr [0x9dd368] */
	m->edi = 0x9dc92cu;	/* 434086: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43408b: add ecx, 0x98 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 434091: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 434097: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43409d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4340a0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4340a2: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4340a4: dec ecx */
	M32((DWORD)(0x9dd69cu)) = 0x1u;	/* 4340a5: mov dword ptr [0x9dd69c], 1 */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 4340af: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x9dd37cu)) = m->eax;	/* 4340b5: mov dword ptr [0x9dd37c], eax */
	M32((DWORD)(0x9dd378u)) = m->eax;	/* 4340ba: mov dword ptr [0x9dd378], eax */
	M32((DWORD)(0x9dd304u)) = m->eax;	/* 4340bf: mov dword ptr [0x9dd304], eax */
	M32((DWORD)(0x4e1868u)) = 0x1u;	/* 4340c4: mov dword ptr [0x4e1868], 1 */
	m->esp -= 4; M32(m->esp) = 0x4340d3u; native_call(m, 0x43f460u);	/* 4340ce: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4340d3: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4340d6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4340d7: pop esi */
	m->esp += 4 + 0; return;	/* 4340d8: ret  */
}

/* room_4340e0 (0x4340e0), lifted by tools/lift.py */
static void lift_4340e0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4340e0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4340e1: push edi */
	m->esp -= 4; M32(m->esp) = 0x4340e7u; native_call(m, 0x401460u);	/* 4340e2: call 0x401460 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4340e7: push 0xc */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 4340e9: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x4340f8u; native_call(m, 0x431560u);	/* 4340f3: call 0x431560 */
	m->ecx = 0x100u;	/* 4340f8: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4340fd: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 4340ff: mov edi, 0x9dc92c */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 434104: mov edx, dword ptr [0x9dd36c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43410a: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dd1f6u;	/* 43410c: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434111: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434114: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434116: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434118: sub edi, ecx */
	{ DWORD a_ = m->edx, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43411a: add edx, 0x6c */
	m->eax = m->ecx;	/* 43411d: mov eax, ecx */
	m->esi = m->edi;	/* 43411f: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 434121: mov edi, 0x9dc92c */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 434126: push 0xc */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434128: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43412b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43412d: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43412f: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434131: and ecx, 3 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 434134: mov dword ptr [0x9da434], 0x40a00000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43413e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 434140: mov ecx, dword ptr [0x9dd368] */
	m->edi = 0x9dc92cu;	/* 434146: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43414b: add ecx, 0x98 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 434151: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 434157: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43415d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434160: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434162: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 434164: dec ecx */
	M32((DWORD)(0x9dd69cu)) = m->eax;	/* 434165: mov dword ptr [0x9dd69c], eax */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 43416a: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x9dd37cu)) = 0x1u;	/* 434170: mov dword ptr [0x9dd37c], 1 */
	M32((DWORD)(0x9dd378u)) = m->eax;	/* 43417a: mov dword ptr [0x9dd378], eax */
	M32((DWORD)(0x9dd304u)) = m->eax;	/* 43417f: mov dword ptr [0x9dd304], eax */
	M32((DWORD)(0x4e1868u)) = 0x1u;	/* 434184: mov dword ptr [0x4e1868], 1 */
	m->esp -= 4; M32(m->esp) = 0x434193u; native_call(m, 0x43f460u);	/* 43418e: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434193: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 434196: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 434197: pop esi */
	m->esp += 4 + 0; return;	/* 434198: ret  */
}

/* room_4341a0 (0x4341a0), lifted by tools/lift.py */
static void lift_4341a0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4341a0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4341a1: push edi */
	m->esp -= 4; M32(m->esp) = 0x4341a7u; native_call(m, 0x401460u);	/* 4341a2: call 0x401460 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4341a7: push 0xc */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 4341a9: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x4341b8u; native_call(m, 0x431560u);	/* 4341b3: call 0x431560 */
	m->ecx = 0x100u;	/* 4341b8: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4341bd: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 4341bf: mov edi, 0x9dc92c */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 4341c4: mov edx, dword ptr [0x9dd36c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4341ca: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dd202u;	/* 4341cc: mov edi, 0x9dd202 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4341d1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4341d4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4341d6: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4341d8: sub edi, ecx */
	{ DWORD a_ = m->edx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4341da: add edx, 0x88 */
	m->eax = m->ecx;	/* 4341e0: mov eax, ecx */
	m->esi = m->edi;	/* 4341e2: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 4341e4: mov edi, 0x9dc92c */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4341e9: push 0xc */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4341eb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4341ee: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4341f0: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4341f2: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4341f4: and ecx, 3 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 4341f7: mov dword ptr [0x9da434], 0x40a00000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434201: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd368u));	/* 434203: mov ecx, dword ptr [0x9dd368] */
	m->edi = 0x9dc92cu;	/* 434209: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43420e: add ecx, 0x98 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 434214: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 43421a: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434220: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434223: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434225: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 434227: dec ecx */
	M32((DWORD)(0x9dd69cu)) = m->eax;	/* 434228: mov dword ptr [0x9dd69c], eax */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 43422d: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x9dd37cu)) = m->eax;	/* 434233: mov dword ptr [0x9dd37c], eax */
	M32((DWORD)(0x9dd378u)) = 0x1u;	/* 434238: mov dword ptr [0x9dd378], 1 */
	M32((DWORD)(0x9dd304u)) = m->eax;	/* 434242: mov dword ptr [0x9dd304], eax */
	M32((DWORD)(0x4e1868u)) = 0x1u;	/* 434247: mov dword ptr [0x4e1868], 1 */
	m->esp -= 4; M32(m->esp) = 0x434256u; native_call(m, 0x43f460u);	/* 434251: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434256: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 434259: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43425a: pop esi */
	m->esp += 4 + 0; return;	/* 43425b: ret  */
}

/* room_433bb0 (0x433bb0), lifted by tools/lift.py */
static void lift_433bb0(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 433bb0: push edi */
	m->esp -= 4; M32(m->esp) = 0x433bb6u; native_call(m, 0x401460u);	/* 433bb1: call 0x401460 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 433bb6: push 0xc */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 433bb8: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x433bc7u; native_call(m, 0x431560u);	/* 433bc2: call 0x431560 */
	m->ecx = 0x100u;	/* 433bc7: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433bcc: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 433bce: mov edi, 0x9dc92c */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433bd3: add esp, 4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 433bd6: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x9dced0u));	/* 433bd8: mov eax, dword ptr [0x9dced0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 433bdd: test eax, eax */
	if (!m->zf) goto L_433c08;	/* 433bdf: jne 0x433c08 */
	m->edi = 0x9dd1f6u;	/* 433be1: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433be6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433be9: xor eax, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 433beb: push esi */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433bec: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433bee: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433bf0: sub edi, ecx */
	m->eax = m->ecx;	/* 433bf2: mov eax, ecx */
	m->esi = m->edi;	/* 433bf4: mov esi, edi */
	m->edi = 0x9dc92cu;	/* 433bf6: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433bfb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433bfe: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 433c00: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433c02: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433c05: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = M32(m->esp); m->esp += 4;	/* 433c07: pop esi */
L_433c08:
	m->ecx = M32((DWORD)(0x9dd358u));	/* 433c08: mov ecx, dword ptr [0x9dd358] */
	m->edx = M32((DWORD)(0x9dd35cu));	/* 433c0e: mov edx, dword ptr [0x9dd35c] */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 433c14: add ecx, 0xc8 */
	m->edi = 0x9dc92cu;	/* 433c1a: mov edi, 0x9dc92c */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 433c1f: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433c25: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433c28: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 433c2a: add edx, 0x88 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433c30: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433c32: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 433c34: dec ecx */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 433c35: push 0xc */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 433c37: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 433c41: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 433c47: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x9dd830u)) = m->eax;	/* 433c4d: mov dword ptr [0x9dd830], eax */
	M32((DWORD)(0x9dd38cu)) = 0x1u;	/* 433c52: mov dword ptr [0x9dd38c], 1 */
	M32((DWORD)(0x4e1868u)) = 0x1u;	/* 433c5c: mov dword ptr [0x4e1868], 1 */
	m->esp -= 4; M32(m->esp) = 0x433c6bu; native_call(m, 0x43f460u);	/* 433c66: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433c6b: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 433c6e: pop edi */
	m->esp += 4 + 0; return;	/* 433c6f: ret  */
}

/* menu_437810 (0x437810), lifted by tools/lift.py */
static void lift_437810(X86 *m)
{
	m->eax = M32((DWORD)(0x4e1524u));	/* 437810: mov eax, dword ptr [0x4e1524] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 437815: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 437816: push eax */
	m->esp -= 4; M32(m->esp) = 0x43781cu; native_call(m, 0x401600u);	/* 437817: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43781c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43781f: test eax, eax */
	if (m->zf) goto L_43786b;	/* 437821: je 0x43786b */
	m->eax = M32((DWORD)(0x9dd6b8u));	/* 437823: mov eax, dword ptr [0x9dd6b8] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 437828: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43782a: cmp eax, esi */
	if (m->zf) goto L_4378d8;	/* 43782c: je 0x4378d8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 437832: push esi */
	m->esp -= 4; M32(m->esp) = 0x437838u; native_call(m, 0x41e760u);	/* 437833: call 0x41e760 */
	m->ecx = M32((DWORD)(0x9dd1b4u));	/* 437838: mov ecx, dword ptr [0x9dd1b4] */
	m->edx = M32((DWORD)(0x9dd300u));	/* 43783e: mov edx, dword ptr [0x9dd300] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437844: add esp, 4 */
	M32((DWORD)(0x9dd6b8u)) = m->esi;	/* 437847: mov dword ptr [0x9dd6b8], esi */
	M32((DWORD)(0x76d40cu)) = m->esi;	/* 43784d: mov dword ptr [0x76d40c], esi */
	M32((DWORD)(0x9dd6acu)) = m->ecx;	/* 437853: mov dword ptr [0x9dd6ac], ecx */
	M32((DWORD)(0x9dd1d0u)) = m->edx;	/* 437859: mov dword ptr [0x9dd1d0], edx */
	M32((DWORD)(0x9dd3b0u)) = 0x1u;	/* 43785f: mov dword ptr [0x9dd3b0], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 437869: pop esi */
	m->esp += 4 + 0; return;	/* 43786a: ret  */
L_43786b:
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 43786b: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 437870: push eax */
	m->esp -= 4; M32(m->esp) = 0x437876u; native_call(m, 0x401600u);	/* 437871: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437876: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437879: test eax, eax */
	if (m->zf) goto L_4378ab;	/* 43787b: je 0x4378ab */
	m->eax = M32((DWORD)(0x9dd6b8u));	/* 43787d: mov eax, dword ptr [0x9dd6b8] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 437882: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437884: cmp eax, esi */
	if (!m->zf) goto L_4378d8;	/* 437886: jne 0x4378d8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 437888: push esi */
	m->esp -= 4; M32(m->esp) = 0x43788eu; native_call(m, 0x41e760u);	/* 437889: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43788e: add esp, 4 */
	M32((DWORD)(0x9dd6b8u)) = m->esi;	/* 437891: mov dword ptr [0x9dd6b8], esi */
	M32((DWORD)(0x9dd3b0u)) = m->esi;	/* 437897: mov dword ptr [0x9dd3b0], esi */
	M32((DWORD)(0x76d40cu)) = m->esi;	/* 43789d: mov dword ptr [0x76d40c], esi */
	M32((DWORD)(0x9dce48u)) = m->esi;	/* 4378a3: mov dword ptr [0x9dce48], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4378a9: pop esi */
	m->esp += 4 + 0; return;	/* 4378aa: ret  */
L_4378ab:
	m->ecx = M32((DWORD)(0x76d48cu));	/* 4378ab: mov ecx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4378b1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4378b7u; native_call(m, 0x401600u);	/* 4378b2: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4378b7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4378ba: test eax, eax */
	if (m->zf) goto L_4378d8;	/* 4378bc: je 0x4378d8 */
	m->eax = M32((DWORD)(0x9dd6b8u));	/* 4378be: mov eax, dword ptr [0x9dd6b8] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4378c3: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4378c5: cmp eax, esi */
	if (!m->zf) goto L_4378d8;	/* 4378c7: jne 0x4378d8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4378c9: push esi */
	m->esp -= 4; M32(m->esp) = 0x4378cfu; native_call(m, 0x41e760u);	/* 4378ca: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4378cf: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = m->esi;	/* 4378d2: mov dword ptr [0x9dce48], esi */
L_4378d8:
	m->esi = M32(m->esp); m->esp += 4;	/* 4378d8: pop esi */
	m->esp += 4 + 0; return;	/* 4378d9: ret  */
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
