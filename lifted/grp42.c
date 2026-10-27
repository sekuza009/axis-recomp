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

static void lift_46b950(X86 *m);

/* pen_init (0x46b950), lifted by tools/lift.py */
static void lift_46b950(X86 *m)
{
	m->eax = M32((DWORD)(0xa106a8u));	/* 46b950: mov eax, dword ptr [0xa106a8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b955: sub esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46b958: cmp eax, 1 */
	if (!m->zf) goto L_46b970;	/* 46b95b: jne 0x46b970 */
	{ DWORD v_ = 0x4c56fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 46b95d: push 0x4c56fc */
	m->esp -= 4; M32(m->esp) = 0x46b967u; native_call(m, 0x46c840u);	/* 46b962: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b967: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b96a: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b96c: add esp, 8 */
	m->esp += 4 + 0; return;	/* 46b96f: ret  */
L_46b970:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b970: push ebx */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46b971: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46b975: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46b976: push edi */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 46b977: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b97d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b97f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b981: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b983: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b985: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b987: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b989: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b98b: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b991u; native_call(m, 0x456be0u);	/* 46b98c: call 0x456be0 */
	M32((DWORD)(0xa106acu)) = m->eax;	/* 46b991: mov dword ptr [0xa106ac], eax */
	m->edx = 0x48u;	/* 46b996: mov edx, 0x48 */
	m->ecx = 0x69u;	/* 46b99b: mov ecx, 0x69 */
	m->eax = 0x8u;	/* 46b9a0: mov eax, 8 */
	m->edi = 0xa0fb28u;	/* 46b9a5: mov edi, 0xa0fb28 */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 46b9aa: mov dword ptr [esp + 0x10], edx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 46b9ae: xor esi, esi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 46b9b0: rep stosd dword ptr es:[edi], eax */
L_46b9b2:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 46b9b2: fild dword ptr [esp + 0x10] */
	m->edi = (DWORD)(m->edx + 0x8u);	/* 46b9b6: lea edi, [edx + 8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46b9b9: xor ecx, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->edi;	/* 46b9bb: mov dword ptr [esp + 0x18], edi */
	M32((DWORD)(m->esp + 0xcu)) = m->ecx;	/* 46b9bf: mov dword ptr [esp + 0xc], ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46b9c3: fmul dword ptr [0x4a957c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 46b9c9: fild dword ptr [esp + 0x18] */
	m->eax = m->esi;	/* 46b9cd: mov eax, esi */
	m->edx = 0x15u;	/* 46b9cf: mov edx, 0x15 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46b9d4: fmul dword ptr [0x4a957c] */
L_46b9da:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 46b9da: fild dword ptr [esp + 0xc] */
	{ DWORD a_ = m->ecx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46b9de: add ecx, 8 */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46b9e1: add eax, 8 */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 46b9e4: mov dword ptr [esp + 0x18], ecx */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 46b9e8: dec edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46b9e9: fmul dword ptr [0x4a957c] */
	M32((DWORD)(m->esp + 0xcu)) = m->ecx;	/* 46b9ef: mov dword ptr [esp + 0xc], ecx */
	MF((DWORD)(m->eax + 0xa0f490u)) = (float)ST(0);	/* 46b9f3: fst dword ptr [eax + 0xa0f490] */
	{ long double t = ST(2); FPUSH(t); }	/* 46b9f9: fld st(2) */
	MF((DWORD)(m->eax + 0xa0f494u)) = (float)ST(0); FPOP();	/* 46b9fb: fstp dword ptr [eax + 0xa0f494] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 46ba01: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46ba05: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->eax + 0xa10010u)) = (float)ST(0);	/* 46ba0b: fst dword ptr [eax + 0xa10010] */
	{ long double t = ST(3); FPUSH(t); }	/* 46ba11: fld st(3) */
	MF((DWORD)(m->eax + 0xa10014u)) = (float)ST(0); FPOP();	/* 46ba13: fstp dword ptr [eax + 0xa10014] */
	MF((DWORD)(m->eax + 0xa0f148u)) = (float)ST(0); FPOP();	/* 46ba19: fstp dword ptr [eax + 0xa0f148] */
	{ long double t = ST(1); FPUSH(t); }	/* 46ba1f: fld st(1) */
	MF((DWORD)(m->eax + 0xa0f14cu)) = (float)ST(0); FPOP();	/* 46ba21: fstp dword ptr [eax + 0xa0f14c] */
	MF((DWORD)(m->eax + 0xa0fcc8u)) = (float)ST(0); FPOP();	/* 46ba27: fstp dword ptr [eax + 0xa0fcc8] */
	MF((DWORD)(m->eax + 0xa0fcccu)) = (float)ST(0);	/* 46ba2d: fst dword ptr [eax + 0xa0fccc] */
	if (!m->zf) goto L_46b9da;	/* 46ba33: jne 0x46b9da */
	ST(0) = ST(0); FPOP();	/* 46ba35: fstp st(0) */
	m->edx = m->edi;	/* 46ba37: mov edx, edi */
	{ DWORD a_ = m->eax, b_ = 0x348u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ba39: cmp eax, 0x348 */
	ST(0) = ST(0); FPOP();	/* 46ba3e: fstp st(0) */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 46ba40: mov dword ptr [esp + 0x10], edx */
	m->esi = m->eax;	/* 46ba44: mov esi, eax */
	if (m->sf != m->of) goto L_46b9b2;	/* 46ba46: jl 0x46b9b2 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 46ba4c: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46ba4e: xor eax, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 46ba50: mov dword ptr [esp + 0x10], esi */
	m->ecx = 0x4c5558u;	/* 46ba54: mov ecx, 0x4c5558 */
L_46ba59:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 46ba59: fild dword ptr [esp + 0x10] */
	m->edi = (DWORD)(m->esi + 0xeu);	/* 46ba5d: lea edi, [esi + 0xe] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46ba60: xor edx, edx */
	M32((DWORD)(m->esp + 0x18u)) = m->edi;	/* 46ba62: mov dword ptr [esp + 0x18], edi */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 46ba66: mov dword ptr [esp + 0xc], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46ba6a: fmul dword ptr [0x4a957c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 46ba70: fild dword ptr [esp + 0x18] */
	m->esi = 0x15u;	/* 46ba74: mov esi, 0x15 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46ba79: fmul dword ptr [0x4a957c] */
L_46ba7f:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 46ba7f: fild dword ptr [esp + 0xc] */
	m->ebx = M32((DWORD)(m->ecx + 0x0u));	/* 46ba83: mov ebx, dword ptr [ecx] */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46ba85: add eax, 8 */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46ba88: add edx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46ba8a: add ecx, 4 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46ba8d: fmul dword ptr [0x4a957c] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 46ba93: mov dword ptr [esp + 0x18], edx */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 46ba97: dec esi */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 46ba98: mov dword ptr [esp + 0xc], edx */
	MF((DWORD)(m->eax + 0xa0eab8u)) = (float)ST(0);	/* 46ba9c: fst dword ptr [eax + 0xa0eab8] */
	{ long double t = ST(2); FPUSH(t); }	/* 46baa2: fld st(2) */
	MF((DWORD)(m->eax + 0xa0eabcu)) = (float)ST(0); FPOP();	/* 46baa4: fstp dword ptr [eax + 0xa0eabc] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 46baaa: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 46baae: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->eax + 0xa10358u)) = (float)ST(0);	/* 46bab4: fst dword ptr [eax + 0xa10358] */
	{ long double t = ST(3); FPUSH(t); }	/* 46baba: fld st(3) */
	MF((DWORD)(m->eax + 0xa1035cu)) = (float)ST(0); FPOP();	/* 46babc: fstp dword ptr [eax + 0xa1035c] */
	MF((DWORD)(m->eax + 0xa0ee00u)) = (float)ST(0); FPOP();	/* 46bac2: fstp dword ptr [eax + 0xa0ee00] */
	{ long double t = ST(1); FPUSH(t); }	/* 46bac8: fld st(1) */
	MF((DWORD)(m->eax + 0xa0ee04u)) = (float)ST(0); FPOP();	/* 46baca: fstp dword ptr [eax + 0xa0ee04] */
	MF((DWORD)(m->eax + 0xa0f7d8u)) = (float)ST(0); FPOP();	/* 46bad0: fstp dword ptr [eax + 0xa0f7d8] */
	MF((DWORD)(m->eax + 0xa0f7dcu)) = (float)ST(0);	/* 46bad6: fst dword ptr [eax + 0xa0f7dc] */
	if (!m->zf) goto L_46ba7f;	/* 46badc: jne 0x46ba7f */
	ST(0) = ST(0); FPOP();	/* 46bade: fstp st(0) */
	m->esi = m->edi;	/* 46bae0: mov esi, edi */
	{ DWORD a_ = m->ecx, b_ = 0x4c56fcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46bae2: cmp ecx, 0x4c56fc */
	ST(0) = ST(0); FPOP();	/* 46bae8: fstp st(0) */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 46baea: mov dword ptr [esp + 0x10], esi */
	if (m->sf != m->of) goto L_46ba59;	/* 46baee: jl 0x46ba59 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46baf4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46baf5: pop esi */
	m->eax = 0x1u;	/* 46baf6: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46bafb: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46bafc: add esp, 8 */
	m->esp += 4 + 0; return;	/* 46baff: ret  */
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
