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

static void lift_41ef90(X86 *m);

/* gfx_setProjection2D3D (0x41ef90), lifted by tools/lift.py */
static void lift_41ef90(X86 *m)
{
	m->eax = M32((DWORD)(0x5ae9bcu));	/* 41ef90: mov eax, dword ptr [0x5ae9bc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41ef95: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 41ef96: mov esi, dword ptr [esp + 8] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ef9a: cmp esi, eax */
	if (m->zf) goto L_41f045;	/* 41ef9c: je 0x41f045 */
	goto L_4a8fa4;	/* 41efa2: jmp 0x4a8fa4 */
	;	/* 41efa7: nop  */
	;	/* 41efa8: nop  */
L_41efa9:
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 41efa9: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x41efb0u; native_call(m, m->edi);	/* 41efae: call edi */
	{ DWORD a_ = m->esi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41efb0: cmp esi, 1 */
	if (!m->zf) goto L_41f001;	/* 41efb3: jne 0x41f001 */
	m->esp -= 4; M32(m->esp) = 0x41efbbu; native_call(m, M32(0x4a9218u));	/* 41efb5: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 41efbb: fld dword ptr [0x4e1870] */
	{ DWORD v_ = 0x40d38800u; m->esp -= 4; M32(m->esp) = v_; }	/* 41efc1: push 0x40d38800 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41efc6: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41efc8: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41efcd: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41efcf: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41efd2: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 41efd5: fld dword ptr [0x68038c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41efdb: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41efde: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x41efe6u; native_call(m, 0x4509c6u);	/* 41efe1: call 0x4509c6 */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 41efe6: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x41eff1u; native_call(m, M32(0x4a9224u));	/* 41efeb: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 41eff1: push 0x1700 */
	M32((DWORD)(0x5ae9bcu)) = m->esi;	/* 41eff6: mov dword ptr [0x5ae9bc], esi */
	m->esp -= 4; M32(m->esp) = 0x41effeu; native_call(m, m->edi);	/* 41effc: call edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 41effe: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41efff: pop esi */
	m->esp += 4 + 0; return;	/* 41f000: ret  */
L_41f001:
	m->esp -= 4; M32(m->esp) = 0x41f007u; native_call(m, M32(0x4a9218u));	/* 41f001: call dword ptr [0x4a9218] */
	FPUSH((long double)(int)M32((DWORD)(0x4e045cu)));	/* 41f007: fild dword ptr [0x4e045c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f00d: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41f010: fstp qword ptr [esp] */
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 41f013: fild dword ptr [0x5b1998] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f019: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f01b: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f01d: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41f020: fstp qword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f023: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f025: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41f02cu; native_call(m, 0x4509ccu);	/* 41f027: call 0x4509cc */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f02c: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x41f037u; native_call(m, M32(0x4a922cu));	/* 41f031: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f037: push 0x1700 */
	M32((DWORD)(0x5ae9bcu)) = m->esi;	/* 41f03c: mov dword ptr [0x5ae9bc], esi */
	m->esp -= 4; M32(m->esp) = 0x41f044u; native_call(m, m->edi);	/* 41f042: call edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 41f044: pop edi */
L_41f045:
	m->esi = M32(m->esp); m->esp += 4;	/* 41f045: pop esi */
	m->esp += 4 + 0; return;	/* 41f046: ret  */
L_4a8fa4:
	{ DWORD e_ = m->esp; m->esp -= 32; M32(m->esp + 28) = m->eax; M32(m->esp + 24) = m->ecx; M32(m->esp + 20) = m->edx; M32(m->esp + 16) = m->ebx; M32(m->esp + 12) = e_; M32(m->esp + 8) = m->ebp; M32(m->esp + 4) = m->esi; M32(m->esp) = m->edi; }	/* 4a8fa4: pushal  */
	m->eax = M32((DWORD)(0x4e045cu));	/* 4a8fa5: mov eax, dword ptr [0x4e045c] */
	m->ecx = M32((DWORD)(0x5b1998u));	/* 4a8faa: mov ecx, dword ptr [0x5b1998] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8fb0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8fb1: push ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4a8fb2: xor edx, edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8fb4: push edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8fb5: push edx */
	{ DWORD a_ = m->esi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4a8fb6: cmp esi, 1 */
	if (m->zf) goto L_4a8fd7;	/* 4a8fb9: je 0x4a8fd7 */
	if (M8(0x4a8fbbu) == 0xc1 && M8(0x4a8fbcu) == 0xe0 && M8(0x4a8fbdu) == 0x02 && M8(0x4a8fbeu) == 0xbb && M8(0x4a8fbfu) == 0x03 && M8(0x4a8fc0u) == 0x00 && M8(0x4a8fc1u) == 0x00 && M8(0x4a8fc2u) == 0x00) {	/* the patch DLL's block (8 bytes) */
		{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* patched 4a8fbb: shl eax, 2 */
		m->ebx = 0x3u;	/* patched 4a8fbe: mov ebx, 3 */
		goto L_4a8fc3;
	}
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4a8fbb: shl eax, 4 */
	m->ebx = 0x9u;	/* 4a8fbe: mov ebx, 9 */
L_4a8fc3:
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ebx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 4a8fc3: div ebx */
	m->ebx = (DWORD)(m->eax + 0x8u);	/* 4a8fc5: lea ebx, [eax + 8] */
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4a8fc8: cmp ebx, ecx */
	if (m->sf == m->of) goto L_4a8fd7;	/* 4a8fca: jge 0x4a8fd7 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4a8fcc: sub ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4a8fce: sar ecx, 1 */
	M32((DWORD)(m->esp + 0x0u)) = m->ecx;	/* 4a8fd0: mov dword ptr [esp], ecx */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 4a8fd3: mov dword ptr [esp + 8], eax */
L_4a8fd7:
	m->esp -= 4; M32(m->esp) = 0x4a8fddu; native_call(m, M32(0x4a91d4u));	/* 4a8fd7: call dword ptr [0x4a91d4] */
	{ m->edi = M32(m->esp); m->esi = M32(m->esp + 4); m->ebp = M32(m->esp + 8); m->ebx = M32(m->esp + 16); m->edx = M32(m->esp + 20); m->ecx = M32(m->esp + 24); m->eax = M32(m->esp + 28); m->esp += 32; }	/* 4a8fdd: popal  */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8fde: push edi */
	m->edi = M32((DWORD)(0x4a91fcu));	/* 4a8fdf: mov edi, dword ptr [0x4a91fc] */
	goto L_41efa9;	/* 4a8fe5: jmp 0x41efa9 */
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
