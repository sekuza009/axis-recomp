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

static void lift_47ce50(X86 *m);

/* bullet_spawn (0x47ce50), lifted by tools/lift.py */
static void lift_47ce50(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ce50: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 47ce51: mov ebx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->ebx + 0x4u));	/* 47ce55: mov eax, dword ptr [ebx + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47ce58: test eax, eax */
	if (m->sf == m->of) goto L_47ce63;	/* 47ce5a: jge 0x47ce63 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47ce5c: or eax, 0xffffffff */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47ce5f: pop ebx */
	m->esp += 4 + 20; return;	/* 47ce60: ret 0x14 */
L_47ce63:
	m->edx = M32((DWORD)(m->ecx + 0x20a99b8u));	/* 47ce63: mov edx, dword ptr [ecx + 0x20a99b8] */
	{ DWORD a_ = m->edx, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47ce69: cmp edx, 0x190 */
	if (m->sf != m->of) goto L_47ce78;	/* 47ce6f: jl 0x47ce78 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47ce71: or eax, 0xffffffff */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47ce74: pop ebx */
	m->esp += 4 + 20; return;	/* 47ce75: ret 0x14 */
L_47ce78:
	m->eax = M32((DWORD)(m->ecx + 0x20a99b4u));	/* 47ce78: mov eax, dword ptr [ecx + 0x20a99b4] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47ce7e: cmp edx, eax */
	if (!m->zf) goto L_47ce9f;	/* 47ce80: jne 0x47ce9f */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47ce82: inc eax */
	M32((DWORD)(m->ecx + 0x20a99b4u)) = m->eax;	/* 47ce83: mov dword ptr [ecx + 0x20a99b4], eax */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47ce89: lea edx, [eax + eax*4] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47ce8c: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47ce8f: sub edx, eax */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 47ce91: lea eax, [eax + edx*4] */
	M32((DWORD)(m->ecx + m->eax*8 + 0x202ef38u)) = 0x0u;	/* 47ce94: mov dword ptr [ecx + eax*8 + 0x202ef38], 0 */
L_47ce9f:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47ce9f: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x20a99b4u));	/* 47cea0: mov esi, dword ptr [ecx + 0x20a99b4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47cea6: push edi */
	m->edi = M32((DWORD)(m->ecx + 0x20a99b8u));	/* 47cea7: mov edi, dword ptr [ecx + 0x20a99b8] */
	m->eax = (DWORD)(m->edi + 0x1u);	/* 47cead: lea eax, [edi + 1] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47ceb0: cmp eax, esi */
	if (!m->zf && m->sf == m->of) goto L_47cede;	/* 47ceb2: jg 0x47cede */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47ceb4: lea edx, [eax + eax*4] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47ceb7: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47ceba: sub edx, eax */
	m->edx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 47cebc: lea edx, [eax + edx*4] */
	m->edx = (DWORD)(m->ecx + m->edx*8 + 0x202ef38u);	/* 47cebf: lea edx, [ecx + edx*8 + 0x202ef38] */
L_47cec6:
	{ DWORD a_ = M32((DWORD)(m->edx + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47cec6: cmp dword ptr [edx], 0 */
	if (m->zf) goto L_47ced8;	/* 47cec9: je 0x47ced8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47cecb: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x4e8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47cecc: add edx, 0x4e8 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47ced2: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_47cec6;	/* 47ced4: jle 0x47cec6 */
	goto L_47cede;	/* 47ced6: jmp 0x47cede */
L_47ced8:
	M32((DWORD)(m->ecx + 0x20a99b8u)) = m->eax;	/* 47ced8: mov dword ptr [ecx + 0x20a99b8], eax */
L_47cede:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 47cede: mov eax, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 47cee2: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47cee6: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 47cee7: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ceeb: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ceec: push edx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 47ceed: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47cef1: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47cef2: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47cef3: push edi */
	m->esp -= 4; M32(m->esp) = 0x47cef9u; native_call(m, 0x479b40u);	/* 47cef4: call 0x479b40 */
	m->eax = m->edi;	/* 47cef9: mov eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 47cefb: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47cefc: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47cefd: pop ebx */
	m->esp += 4 + 20; return;	/* 47cefe: ret 0x14 */
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
