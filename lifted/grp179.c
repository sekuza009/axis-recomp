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

static void lift_42eed0(X86 *m);

/* FUN_0042eed0 (0x42eed0), lifted by tools/lift.py */
static void lift_42eed0(X86 *m)
{
	goto L_4a8e54;	/* 42eed0: jmp 0x4a8e54 */
	;	/* 42eed5: nop  */
L_42eed6:
	m->eax = M32((DWORD)(m->esp + 0xa4u));	/* 42eed6: mov eax, dword ptr [esp + 0xa4] */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 42eedd: mov ecx, dword ptr [esp + 0x98] */
	m->edx = M32((DWORD)(m->esp + 0x9cu));	/* 42eee4: mov edx, dword ptr [esp + 0x9c] */
	M32((DWORD)(m->esp + 0x68u)) = m->eax;	/* 42eeeb: mov dword ptr [esp + 0x68], eax */
	m->eax = M32((DWORD)(m->esp + 0xa0u));	/* 42eeef: mov eax, dword ptr [esp + 0xa0] */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 42eef6: mov dword ptr [esp + 0x6c], ecx */
	m->ecx = (DWORD)(m->esp + 0x0u);	/* 42eefa: lea ecx, [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42eefe: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42eeff: push ecx */
	M32((DWORD)(m->esp + 0x78u)) = m->edx;	/* 42ef00: mov dword ptr [esp + 0x78], edx */
	M32((DWORD)(m->esp + 0x30u)) = 0x1c0000u;	/* 42ef04: mov dword ptr [esp + 0x30], 0x1c0000 */
	M16((DWORD)(m->esp + 0x2cu)) = (WORD)(0x94u);	/* 42ef0c: mov word ptr [esp + 0x2c], 0x94 */
	M16((DWORD)(m->esp + 0x44u)) = (WORD)(0x800u);	/* 42ef13: mov word ptr [esp + 0x44], 0x800 */
	m->esp -= 4; M32(m->esp) = 0x42ef20u; native_call(m, M32(0x4a9314u));	/* 42ef1a: call dword ptr [0x4a9314] */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ef20: add esp, 0x94 */
	m->esp += 4 + 0; return;	/* 42ef26: ret  */
L_4a8e54:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4a8e54: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(0x67eefcu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4a8e58: cmp eax, dword ptr [0x67eefc] */
	if (!m->zf) goto L_4a8e95;	/* 4a8e5e: jne 0x4a8e95 */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 4a8e64: mov eax, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(0x76d430u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4a8e68: cmp eax, dword ptr [0x76d430] */
	if (!m->zf) goto L_4a8e95;	/* 4a8e6e: jne 0x4a8e95 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4a8e74: xor eax, eax */
	{ DWORD a_ = M8((DWORD)(0xb12a80u)), b_ = 0x0u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4a8e76: cmp byte ptr [0xb12a80], 0 */
	if (m->zf) goto L_4a8e94;	/* 4a8e7d: je 0x4a8e94 */
	M8((DWORD)(0xb12a80u)) = (BYTE)(0x0u);	/* 4a8e83: mov byte ptr [0xb12a80], 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8e8a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8e8c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4a8e94u; native_call(m, M32(0x4a9314u));	/* 4a8e8e: call dword ptr [0x4a9314] */
L_4a8e94:
	m->esp += 4 + 0; return;	/* 4a8e94: ret  */
L_4a8e95:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4a8e95: mov eax, dword ptr [esp + 4] */
	M32((DWORD)(0xb12a84u)) = m->eax;	/* 4a8e99: mov dword ptr [0xb12a84], eax */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 4a8e9e: mov eax, dword ptr [esp + 8] */
	M32((DWORD)(0xb12a88u)) = m->eax;	/* 4a8ea2: mov dword ptr [0xb12a88], eax */
	M32((DWORD)(m->esp + 0x10u)) = 0x20u;	/* 4a8ea7: mov dword ptr [esp + 0x10], 0x20 */
	M8((DWORD)(0xb12a80u)) = (BYTE)(0x1u);	/* 4a8eaf: mov byte ptr [0xb12a80], 1 */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4a8eb6: sub esp, 0x94 */
	goto L_42eed6;	/* 4a8ebc: jmp 0x42eed6 */
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
