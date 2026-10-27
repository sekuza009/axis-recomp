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

static void lift_479950(X86 *m);

/* particle_spawn (0x479950), lifted by tools/lift.py */
static void lift_479950(X86 *m)
{
	m->edx = M32((DWORD)(m->ecx + 0x20f2da4u));	/* 479950: mov edx, dword ptr [ecx + 0x20f2da4] */
	{ DWORD a_ = m->edx, b_ = 0x3e8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479956: cmp edx, 0x3e8 */
	if (m->sf != m->of) goto L_479964;	/* 47995c: jl 0x479964 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47995e: or eax, 0xffffffff */
	m->esp += 4 + 4; return;	/* 479961: ret 4 */
L_479964:
	m->eax = M32((DWORD)(m->ecx + 0x20f2da0u));	/* 479964: mov eax, dword ptr [ecx + 0x20f2da0] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47996a: cmp edx, eax */
	if (!m->zf) goto L_479989;	/* 47996c: jne 0x479989 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47996e: inc eax */
	M32((DWORD)(m->ecx + 0x20f2da0u)) = m->eax;	/* 47996f: mov dword ptr [ecx + 0x20f2da0], eax */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 479975: lea eax, [eax + eax*2] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 479978: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47997b: lea eax, [eax + eax*4] */
	M32((DWORD)(m->ecx + m->eax*4 + 0x20a99c4u)) = 0x0u;	/* 47997e: mov dword ptr [ecx + eax*4 + 0x20a99c4], 0 */
L_479989:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 479989: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x20f2da0u));	/* 47998a: mov esi, dword ptr [ecx + 0x20f2da0] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 479990: push edi */
	m->edi = M32((DWORD)(m->ecx + 0x20f2da4u));	/* 479991: mov edi, dword ptr [ecx + 0x20f2da4] */
	m->eax = (DWORD)(m->edi + 0x1u);	/* 479997: lea eax, [edi + 1] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47999a: cmp eax, esi */
	if (!m->zf && m->sf == m->of) goto L_4799d6;	/* 47999c: jg 0x4799d6 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 47999e: lea edx, [eax + eax*2] */
	m->edx = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 4799a1: lea edx, [edx + edx*4] */
	m->edx = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 4799a4: lea edx, [edx + edx*4] */
	m->edx = (DWORD)(m->ecx + m->edx*4 + 0x20a99c4u);	/* 4799a7: lea edx, [ecx + edx*4 + 0x20a99c4] */
L_4799ae:
	{ DWORD a_ = M32((DWORD)(m->edx + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4799ae: cmp dword ptr [edx], 0 */
	if (m->zf) goto L_4799d0;	/* 4799b1: je 0x4799d0 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4799b3: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4799b4: add edx, 0x12c */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4799ba: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_4799ae;	/* 4799bc: jle 0x4799ae */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 4799be: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4799c2: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4799c3: push edi */
	m->esp -= 4; M32(m->esp) = 0x4799c9u; native_call(m, 0x475070u);	/* 4799c4: call 0x475070 */
	m->eax = m->edi;	/* 4799c9: mov eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4799cb: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4799cc: pop esi */
	m->esp += 4 + 4; return;	/* 4799cd: ret 4 */
L_4799d0:
	M32((DWORD)(m->ecx + 0x20f2da4u)) = m->eax;	/* 4799d0: mov dword ptr [ecx + 0x20f2da4], eax */
L_4799d6:
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 4799d6: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4799da: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4799db: push edi */
	m->esp -= 4; M32(m->esp) = 0x4799e1u; native_call(m, 0x475070u);	/* 4799dc: call 0x475070 */
	m->eax = m->edi;	/* 4799e1: mov eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4799e3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4799e4: pop esi */
	m->esp += 4 + 4; return;	/* 4799e5: ret 4 */
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
