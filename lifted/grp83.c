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

static void lift_43bfe0(X86 *m);

/* room_drawGameSettings (0x43bfe0), lifted by tools/lift.py */
static void lift_43bfe0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bfe0: sub esp, 0x18 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 43bfe3: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 43bfe8: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfee: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfef: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43bff0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43bff1: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bff2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bff3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43bff9u; native_call(m, 0x432380u);	/* 43bff4: call 0x432380 */
	m->ebx = m->eax;	/* 43bff9: mov ebx, eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bffb: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebx;	/* 43bffd: mov dword ptr [esp + 0x1c], ebx */
	m->esp -= 4; M32(m->esp) = 0x43c006u; native_call(m, 0x41ef90u);	/* 43c001: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c006: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x43c00fu; native_call(m, M32(0x4a9218u));	/* 43c009: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c00f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c014: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c019: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c01e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43c029u; native_call(m, M32(0x4a9228u));	/* 43c023: call dword ptr [0x4a9228] */
	m->edx = M32((DWORD)(0x4deb50u));	/* 43c029: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9dd1c4u));	/* 43c02f: mov eax, dword ptr [0x9dd1c4] */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43c034: mov ecx, dword ptr [0x9dd1c0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c03a: push edx */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43c03b: mov edx, dword ptr [0x9dd1bc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c041: push eax */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c042: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c047: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c048: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c049: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c04fu; native_call(m, 0x427a90u);	/* 43c04a: call 0x427a90 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43c04f: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43c055: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43c05b: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c060: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43c061: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c067: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c068: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c069: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c06a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c074u; native_call(m, 0x41f0e0u);	/* 43c06f: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43c074: mov edx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c07a: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c07f: add edx, 0x10 */
	{ DWORD v_ = 0x75a424u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c082: push 0x75a424 */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c087: add eax, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c08a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c08b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c091u; native_call(m, 0x4028b0u);	/* 43c08c: call 0x4028b0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c091: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c096: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c09b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0a0: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0a2: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c0acu; native_call(m, 0x41f0e0u);	/* 43c0a7: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c0ac: mov ecx, dword ptr [0x9dd1bc] */
	m->edx = M32((DWORD)(0x9dd1c0u));	/* 43c0b2: mov edx, dword ptr [0x9dd1c0] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c0b8: add esp, 0x48 */
	{ DWORD a_ = m->edx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c0bb: add edx, -0x10 */
	m->eax = (DWORD)(m->ecx + 0x28u);	/* 43c0be: lea eax, [ecx + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0c1: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0c2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0c3: push eax */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c0c4: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c0c9: add eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0cc: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c0d2u; native_call(m, 0x427a40u);	/* 43c0cd: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c0d2: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 43c0d5: xor edi, edi */
	m->esi = 0x75a4a4u;	/* 43c0d7: mov esi, 0x75a4a4 */
L_43c0dc:
	{ DWORD a_ = m->esi, b_ = 0x75a824u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43c0dc: cmp esi, 0x75a824 */
	if (m->zf || m->sf != m->of) goto L_43c105;	/* 43c0e2: jle 0x43c105 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0e4: push 0x3f800000 */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0e9: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0ee: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0f3: push 0x3f19999a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c0f8: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c102u; native_call(m, 0x41f0e0u);	/* 43c0fd: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c102: add esp, 0x14 */
L_43c105:
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c105: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c10b: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43c110: push esi */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c111: add eax, 0x40 */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x32u);	/* 43c114: lea edx, [edi + ecx + 0x32] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c118: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c119: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c11fu; native_call(m, 0x402620u);	/* 43c11a: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43c11f: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c125: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x22u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43c128: add edi, 0x22 */
	{ DWORD a_ = m->esi, b_ = 0x75a8a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43c12b: cmp esi, 0x75a8a4 */
	if (m->sf != m->of) goto L_43c0dc;	/* 43c131: jl 0x43c0dc */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c133: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c138: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c13a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c13c: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c13e: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c148u; native_call(m, 0x41f0e0u);	/* 43c143: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c148: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c14e: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c153: push 1 */
	m->edx = (DWORD)(m->ecx + 0x45u);	/* 43c155: lea edx, [ecx + 0x45] */
	{ DWORD a_ = m->ecx, b_ = 0x2fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c158: add ecx, 0x2f */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c15b: push edx */
	m->edx = (DWORD)(m->eax + 0x1a7u);	/* 43c15c: lea edx, [eax + 0x1a7] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c162: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c163: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c168: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c169: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c16fu; native_call(m, 0x427970u);	/* 43c16a: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c16f: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c174: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c179: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c17e: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c180: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c18au; native_call(m, 0x41f0e0u);	/* 43c185: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c18a: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c190: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c195: push 0 */
	m->edx = (DWORD)(m->ecx + 0x45u);	/* 43c197: lea edx, [ecx + 0x45] */
	{ DWORD a_ = m->ecx, b_ = 0x2fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c19a: add ecx, 0x2f */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c19d: push edx */
	m->edx = (DWORD)(m->eax + 0x1a7u);	/* 43c19e: lea edx, [eax + 0x1a7] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1a4: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c1a5: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1aa: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1ab: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c1b1u; native_call(m, 0x427970u);	/* 43c1ac: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c1b1: add esp, 0x50 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1b4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1b9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1be: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1c3: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1c8: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c1d2u; native_call(m, 0x41f0e0u);	/* 43c1cd: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd380u));	/* 43c1d2: mov eax, dword ptr [0x9dd380] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c1d7: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43c1da: test eax, eax */
	if (!m->zf) goto L_43c201;	/* 43c1dc: jne 0x43c201 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43c1de: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43c1e3: mov ecx, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->eax, b_ = 0x32u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c1e9: add eax, 0x32 */
	{ DWORD v_ = 0x4df9c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1ec: push 0x4df9c8 */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c1f1: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1f7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c1f8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c1feu; native_call(m, 0x402620u);	/* 43c1f9: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c1fe: add esp, 0xc */
L_43c201:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c201: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c206: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c208: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c20a: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c20c: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c216u; native_call(m, 0x41f0e0u);	/* 43c211: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c216: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c21c: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c221: push 1 */
	m->edx = (DWORD)(m->ecx + 0x67u);	/* 43c223: lea edx, [ecx + 0x67] */
	{ DWORD a_ = m->ecx, b_ = 0x51u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c226: add ecx, 0x51 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c229: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c22a: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c230: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c231: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c236: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c237: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c23du; native_call(m, 0x427970u);	/* 43c238: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c23d: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c242: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c247: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c24c: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c24e: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c258u; native_call(m, 0x41f0e0u);	/* 43c253: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c258: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c25e: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c263: push 0 */
	m->edx = (DWORD)(m->ecx + 0x67u);	/* 43c265: lea edx, [ecx + 0x67] */
	{ DWORD a_ = m->ecx, b_ = 0x51u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c268: add ecx, 0x51 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c26b: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c26c: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c272: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c273: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c278: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c279: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c27fu; native_call(m, 0x427970u);	/* 43c27a: call 0x427970 */
	m->eax = M32((DWORD)(0x9dd6a8u));	/* 43c27f: mov eax, dword ptr [0x9dd6a8] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c284: add esp, 0x50 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43c287: test eax, eax */
	if (!m->zf) goto L_43c2ed;	/* 43c289: jne 0x43c2ed */
	m->edi = 0x4df9eeu;	/* 43c28b: mov edi, 0x4df9ee */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43c290: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43c293: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43c295: repne scasb al, byte ptr es:[edi] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 43c297: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 43c29b: mov dword ptr [esp + 0x18], eax */
	m->ecx = ~m->ecx;	/* 43c29f: not ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 43c2a1: mov dword ptr [esp + 0x1c], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43c2a5: dec ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 43c2a6: mov dword ptr [esp + 0x20], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43c2aa: test ecx, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 43c2ac: mov dword ptr [esp + 0x24], eax */
	if (m->zf || m->sf != m->of) goto L_43c2c9;	/* 43c2b0: jle 0x43c2c9 */
	m->edx = m->ecx;	/* 43c2b2: mov edx, ecx */
	m->eax = 0x2a2a2a2au;	/* 43c2b4: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 43c2b9: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43c2bd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43c2c0: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 43c2c2: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43c2c4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 43c2c7: rep stosb byte ptr es:[edi], al */
L_43c2c9:
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c2c9: mov ecx, dword ptr [0x9dd1bc] */
	m->edx = M32((DWORD)(0x9dd1b8u));	/* 43c2cf: mov edx, dword ptr [0x9dd1b8] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 43c2d5: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c2d9: add ecx, 0x54 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c2dc: push eax */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c2dd: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c2e3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c2e4: push edx */
	m->esp -= 4; M32(m->esp) = 0x43c2eau; native_call(m, 0x402620u);	/* 43c2e5: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c2ea: add esp, 0xc */
L_43c2ed:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c2ed: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c2f2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c2f4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c2f6: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c2f8: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c302u; native_call(m, 0x41f0e0u);	/* 43c2fd: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c302: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c308: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c30d: push 1 */
	m->edx = (DWORD)(m->ecx + 0x91u);	/* 43c30f: lea edx, [ecx + 0x91] */
	{ DWORD a_ = m->ecx, b_ = 0x6du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c315: add ecx, 0x6d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c318: push edx */
	m->edx = (DWORD)(m->eax + 0x18fu);	/* 43c319: lea edx, [eax + 0x18f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c31f: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c320: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c325: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c326: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c32cu; native_call(m, 0x427970u);	/* 43c327: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c32c: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c331: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c336: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c33b: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c33d: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c347u; native_call(m, 0x41f0e0u);	/* 43c342: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c347: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c34d: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c352: push 0 */
	m->edx = (DWORD)(m->ecx + 0x91u);	/* 43c354: lea edx, [ecx + 0x91] */
	{ DWORD a_ = m->ecx, b_ = 0x6du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c35a: add ecx, 0x6d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c35d: push edx */
	m->edx = (DWORD)(m->eax + 0x18fu);	/* 43c35e: lea edx, [eax + 0x18f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c364: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c365: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c36a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c36b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c371u; native_call(m, 0x427970u);	/* 43c36c: call 0x427970 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9eau))) & 0xff) << 0);	/* 43c371: mov al, byte ptr [0x4df9ea] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c376: add esp, 0x50 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43c379: test al, al */
	if (m->zf) goto L_43c38c;	/* 43c37b: je 0x43c38c */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43c37d: mov eax, dword ptr [0x9dd1bc] */
	{ DWORD v_ = 0x4ad56cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c382: push 0x4ad56c */
	{ DWORD a_ = m->eax, b_ = 0x76u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c387: add eax, 0x76 */
	goto L_43c3a8;	/* 43c38a: jmp 0x43c3a8 */
L_43c38c:
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9e8u)));	/* 43c38c: movsx eax, byte ptr [0x4df9e8] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43c393: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43c396: mov eax, dword ptr [0x9dd1bc] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43c39b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = 0x5ae9d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c39e: add edx, 0x5ae9d0 */
	{ DWORD a_ = m->eax, b_ = 0x6fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c3a4: add eax, 0x6f */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3a7: push edx */
L_43c3a8:
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43c3a8: mov ecx, dword ptr [0x9dd1b8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3ae: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c3af: add ecx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3b5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c3bbu; native_call(m, 0x402620u);	/* 43c3b6: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c3bb: add esp, 0xc */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3be: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3c3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3c5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3c7: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3c9: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c3d3u; native_call(m, 0x41f0e0u);	/* 43c3ce: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c3d3: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c3d9: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3de: push 1 */
	m->edx = (DWORD)(m->ecx + 0xabu);	/* 43c3e0: lea edx, [ecx + 0xab] */
	{ DWORD a_ = m->ecx, b_ = 0x95u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c3e6: add ecx, 0x95 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3ec: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c3ed: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3f3: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c3f4: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3f9: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c3fa: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c400u; native_call(m, 0x427970u);	/* 43c3fb: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c400: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c405: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c40a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c40f: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c411: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c41bu; native_call(m, 0x41f0e0u);	/* 43c416: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c41b: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c421: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c426: push 0 */
	m->edx = (DWORD)(m->ecx + 0xabu);	/* 43c428: lea edx, [ecx + 0xab] */
	{ DWORD a_ = m->ecx, b_ = 0x95u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c42e: add ecx, 0x95 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c434: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c435: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c43b: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c43c: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c441: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c442: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c448u; native_call(m, 0x427970u);	/* 43c443: call 0x427970 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9e9u)));	/* 43c448: movsx ecx, byte ptr [0x4df9e9] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c44f: add esp, 0x50 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 43c452: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43c456: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c458: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c459: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c45fu; native_call(m, 0x49fb53u);	/* 43c45a: call 0x49fb53 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43c45f: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43c464: mov ecx, dword ptr [0x9dd1b8] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 43c46a: lea edx, [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c46e: add eax, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c473: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c474: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c47a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c47b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c481u; native_call(m, 0x402620u);	/* 43c47c: call 0x402620 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c481: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c486: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c488: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c48a: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c48c: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c496u; native_call(m, 0x41f0e0u);	/* 43c491: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c496: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c49c: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4a1: push 1 */
	m->edx = (DWORD)(m->ecx + 0xcdu);	/* 43c4a3: lea edx, [ecx + 0xcd] */
	{ DWORD a_ = m->ecx, b_ = 0xb7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c4a9: add ecx, 0xb7 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4af: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c4b0: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4b6: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c4b7: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4bc: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4bd: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c4c3u; native_call(m, 0x427970u);	/* 43c4be: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c4c3: add esp, 0x40 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4c6: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4cb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4d0: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4d5: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4d7: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c4e1u; native_call(m, 0x41f0e0u);	/* 43c4dc: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c4e1: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c4e7: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4ec: push 0 */
	m->edx = (DWORD)(m->ecx + 0xcdu);	/* 43c4ee: lea edx, [ecx + 0xcd] */
	{ DWORD a_ = m->ecx, b_ = 0xb7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c4f4: add ecx, 0xb7 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c4fa: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c4fb: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c501: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c502: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c507: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c508: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c50eu; native_call(m, 0x427970u);	/* 43c509: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c50e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c513: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c518: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c51d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c522: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c52cu; native_call(m, 0x41f0e0u);	/* 43c527: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43c52c: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43c531: mov ecx, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->eax, b_ = 0xbau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c537: add eax, 0xba */
	{ DWORD v_ = 0x74e6a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c53c: push 0x74e6a4 */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c541: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c547: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c548: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c54eu; native_call(m, 0x402620u);	/* 43c549: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c54e: add esp, 0x48 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c551: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c556: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c558: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c55a: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c55c: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c566u; native_call(m, 0x41f0e0u);	/* 43c561: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c566: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c56c: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c571: push 1 */
	m->edx = (DWORD)(m->ecx + 0xefu);	/* 43c573: lea edx, [ecx + 0xef] */
	{ DWORD a_ = m->ecx, b_ = 0xd9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c579: add ecx, 0xd9 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c57f: push edx */
	m->edx = (DWORD)(m->eax + 0x18fu);	/* 43c580: lea edx, [eax + 0x18f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c586: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c587: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c58c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c58d: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c593u; native_call(m, 0x427970u);	/* 43c58e: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c593: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c598: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c59d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5a2: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5a4: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c5aeu; native_call(m, 0x41f0e0u);	/* 43c5a9: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c5ae: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c5b4: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5b9: push 0 */
	m->edx = (DWORD)(m->ecx + 0xefu);	/* 43c5bb: lea edx, [ecx + 0xef] */
	{ DWORD a_ = m->ecx, b_ = 0xd9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c5c1: add ecx, 0xd9 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5c7: push edx */
	m->edx = (DWORD)(m->eax + 0x18fu);	/* 43c5c8: lea edx, [eax + 0x18f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5ce: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c5cf: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5d4: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5d5: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c5dbu; native_call(m, 0x427970u);	/* 43c5d6: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c5db: add esp, 0x50 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5de: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5e3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5e8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5ed: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c5f2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c5fcu; native_call(m, 0x41f0e0u);	/* 43c5f7: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9ebu)));	/* 43c5fc: movsx eax, byte ptr [0x4df9eb] */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c603: mov ecx, dword ptr [0x9dd1bc] */
	m->edx = M32((DWORD)(0x9dd1b8u));	/* 43c609: mov edx, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43c60f: shl eax, 7 */
	{ DWORD a_ = m->eax, b_ = 0x7669a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c612: add eax, 0x7669a4 */
	{ DWORD a_ = m->ecx, b_ = 0xdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c617: add ecx, 0xdc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c61d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c61e: push ecx */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c61f: add edx, 0xa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c625: push edx */
	m->esp -= 4; M32(m->esp) = 0x43c62bu; native_call(m, 0x402620u);	/* 43c626: call 0x402620 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c62b: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c630: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c632: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c634: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c636: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c640u; native_call(m, 0x41f0e0u);	/* 43c63b: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c640: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c646: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c64b: push 1 */
	m->edx = (DWORD)(m->ecx + 0x111u);	/* 43c64d: lea edx, [ecx + 0x111] */
	{ DWORD a_ = m->ecx, b_ = 0xfbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c653: add ecx, 0xfb */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c659: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c65a: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c660: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c661: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c666: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c667: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c66du; native_call(m, 0x427970u);	/* 43c668: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c66d: add esp, 0x48 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c670: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c675: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c67a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c67f: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c681: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c68bu; native_call(m, 0x41f0e0u);	/* 43c686: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c68b: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c691: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c696: push 0 */
	m->edx = (DWORD)(m->ecx + 0x111u);	/* 43c698: lea edx, [ecx + 0x111] */
	{ DWORD a_ = m->ecx, b_ = 0xfbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c69e: add ecx, 0xfb */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6a4: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c6a5: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6ab: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c6ac: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6b1: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6b2: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c6b8u; native_call(m, 0x427970u);	/* 43c6b3: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6b8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6bd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6c2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6c7: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6cc: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c6d6u; native_call(m, 0x41f0e0u);	/* 43c6d1: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd388u));	/* 43c6d6: mov eax, dword ptr [0x9dd388] */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c6db: add esp, 0x3c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43c6de: test eax, eax */
	if (!m->zf) goto L_43c720;	/* 43c6e0: jne 0x43c720 */
	m->ecx = M32((DWORD)(0x4df9ecu));	/* 43c6e2: mov ecx, dword ptr [0x4df9ec] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 43c6e8: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6ec: push 0xa */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43c6ee: and ecx, 0xff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6f4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c6f5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c6fbu; native_call(m, 0x49fb53u);	/* 43c6f6: call 0x49fb53 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43c6fb: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43c700: mov ecx, dword ptr [0x9dd1b8] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 43c706: lea edx, [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0xfeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c70a: add eax, 0xfe */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c70f: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c710: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c716: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c717: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c71du; native_call(m, 0x402620u);	/* 43c718: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c71d: add esp, 0x18 */
L_43c720:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c720: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c725: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c727: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c729: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c72b: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c735u; native_call(m, 0x41f0e0u);	/* 43c730: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c735: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c73b: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c740: push 1 */
	m->edx = (DWORD)(m->ecx + 0x133u);	/* 43c742: lea edx, [ecx + 0x133] */
	{ DWORD a_ = m->ecx, b_ = 0x11du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c748: add ecx, 0x11d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c74e: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c74f: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c755: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c756: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c75b: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c75c: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c762u; native_call(m, 0x427970u);	/* 43c75d: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c762: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c767: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c76c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c771: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c773: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43c77du; native_call(m, 0x41f0e0u);	/* 43c778: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c77d: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c783: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c788: push 0 */
	m->edx = (DWORD)(m->ecx + 0x133u);	/* 43c78a: lea edx, [ecx + 0x133] */
	{ DWORD a_ = m->ecx, b_ = 0x11du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c790: add ecx, 0x11d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c796: push edx */
	m->edx = (DWORD)(m->eax + 0xefu);	/* 43c797: lea edx, [eax + 0xef] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c79d: push edx */
	{ DWORD a_ = m->eax, b_ = 0x9fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c79e: add eax, 0x9f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c7a3: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c7a4: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c7aau; native_call(m, 0x427970u);	/* 43c7a5: call 0x427970 */
	m->eax = M32((DWORD)(0x9dd568u));	/* 43c7aa: mov eax, dword ptr [0x9dd568] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c7af: add esp, 0x50 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43c7b2: test eax, eax */
	if (!m->zf) goto L_43c7f0;	/* 43c7b4: jne 0x43c7f0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43c7b6: xor ecx, ecx */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 43c7b8: lea eax, [esp + 0x14] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9edu))) & 0xff) << 0);	/* 43c7bc: mov cl, byte ptr [0x4df9ed] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43c7c2: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c7c4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c7c5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c7cbu; native_call(m, 0x49fb53u);	/* 43c7c6: call 0x49fb53 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43c7cb: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43c7d0: mov ecx, dword ptr [0x9dd1b8] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 43c7d6: lea edx, [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x120u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c7da: add eax, 0x120 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c7df: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c7e0: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c7e6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c7e7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43c7edu; native_call(m, 0x402620u);	/* 43c7e8: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c7ed: add esp, 0x18 */
L_43c7f0:
	m->eax = M32((DWORD)(0x68039cu));	/* 43c7f0: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43c7f5: test eax, eax */
	if (!m->zf) goto L_43cc40;	/* 43c7f7: jne 0x43cc40 */
	m->eax = M32((DWORD)(0x907b2cu));	/* 43c7fd: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43c802: test eax, eax */
	if (!m->zf) goto L_43cc40;	/* 43c804: jne 0x43cc40 */
	{ DWORD a_ = m->ebx, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43c80a: cmp ebx, 7 */
	if (!m->cf && !m->zf) goto L_43cc40;	/* 43c80d: ja 0x43cc40 */
	switch (m->ebx) { case 0: goto L_43c81a; case 1: goto L_43c885; case 2: goto L_43c930; case 3: goto L_43c9dc; case 4: goto L_43cc40; case 5: goto L_43ca70; case 6: goto L_43cb0d; case 7: goto L_43cba4; default: abort(); }	/* 43c813: jmp dword ptr [ebx*4 + 0x43d034] */
L_43c81a:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c81a: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c81f: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c824: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c829: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c82e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c838u; native_call(m, 0x41f0e0u);	/* 43c833: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43c838: mov edx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43c83e: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->edx, b_ = 0x32u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c843: add edx, 0x32 */
	{ DWORD v_ = 0x4df9c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c846: push 0x4df9c8 */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c84b: add eax, 0xa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c850: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c851: push eax */
	m->esp -= 4; M32(m->esp) = 0x43c857u; native_call(m, 0x402620u);	/* 43c852: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c857: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c85c: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c85e: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c863: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c868: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c872u; native_call(m, 0x41f0e0u);	/* 43c86d: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c872: mov ecx, dword ptr [0x9dd1bc] */
	{ DWORD v_ = 0x4df9c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c878: push 0x4df9c8 */
	{ DWORD a_ = m->ecx, b_ = 0x31u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c87d: add ecx, 0x31 */
	goto L_43c9c1;	/* 43c880: jmp 0x43c9c1 */
L_43c885:
	m->edi = 0x4df9eeu;	/* 43c885: mov edi, 0x4df9ee */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43c88a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43c88d: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43c88f: repne scasb al, byte ptr es:[edi] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 43c891: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 43c895: mov dword ptr [esp + 0x18], eax */
	m->ecx = ~m->ecx;	/* 43c899: not ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 43c89b: mov dword ptr [esp + 0x1c], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43c89f: dec ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 43c8a0: mov dword ptr [esp + 0x20], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43c8a4: test ecx, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 43c8a6: mov dword ptr [esp + 0x24], eax */
	if (m->zf || m->sf != m->of) goto L_43c8c3;	/* 43c8aa: jle 0x43c8c3 */
	m->edx = m->ecx;	/* 43c8ac: mov edx, ecx */
	m->eax = 0x2a2a2a2au;	/* 43c8ae: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 43c8b3: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43c8b7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43c8ba: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 43c8bc: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43c8be: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 43c8c1: rep stosb byte ptr es:[edi], al */
L_43c8c3:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c8c3: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c8c8: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c8cd: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c8d2: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c8d7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c8e1u; native_call(m, 0x41f0e0u);	/* 43c8dc: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c8e1: mov ecx, dword ptr [0x9dd1bc] */
	m->edx = M32((DWORD)(0x9dd1b8u));	/* 43c8e7: mov edx, dword ptr [0x9dd1b8] */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 43c8ed: lea eax, [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x54u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c8f1: add ecx, 0x54 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c8f4: push eax */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c8f5: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c8fb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c8fc: push edx */
	m->esp -= 4; M32(m->esp) = 0x43c902u; native_call(m, 0x402620u);	/* 43c8fd: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c902: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c907: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c909: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c90e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c913: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c91du; native_call(m, 0x41f0e0u);	/* 43c918: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c91d: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 43c923: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c927: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c928: add ecx, 0x53 */
	goto L_43c9c1;	/* 43c92b: jmp 0x43c9c1 */
L_43c930:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9eau))) & 0xff) << 0);	/* 43c930: mov al, byte ptr [0x4df9ea] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43c935: test al, al */
	if (!m->zf) goto L_43cc40;	/* 43c937: jne 0x43cc40 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c93d: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c942: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c947: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c94c: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c951: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c95bu; native_call(m, 0x41f0e0u);	/* 43c956: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9e8u)));	/* 43c95b: movsx eax, byte ptr [0x4df9e8] */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c962: mov ecx, dword ptr [0x9dd1bc] */
	m->edx = M32((DWORD)(0x9dd1b8u));	/* 43c968: mov edx, dword ptr [0x9dd1b8] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43c96e: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->ecx, b_ = 0x6fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c971: add ecx, 0x6f */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43c974: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x5ae9d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c977: add eax, 0x5ae9d0 */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c97c: add edx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c982: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c983: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c984: push edx */
	m->esp -= 4; M32(m->esp) = 0x43c98au; native_call(m, 0x402620u);	/* 43c985: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c98a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c98f: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43c991: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c996: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c99b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c9a5u; native_call(m, 0x41f0e0u);	/* 43c9a0: call 0x41f0e0 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9e8u)));	/* 43c9a5: movsx eax, byte ptr [0x4df9e8] */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43c9ac: mov ecx, dword ptr [0x9dd1bc] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43c9b2: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43c9b5: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0x5ae9d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43c9b8: add eax, 0x5ae9d0 */
	{ DWORD a_ = m->ecx, b_ = 0x6eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43c9bd: add ecx, 0x6e */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43c9c0: push eax */
L_43c9c1:
	m->edx = M32((DWORD)(0x9dd1b8u));	/* 43c9c1: mov edx, dword ptr [0x9dd1b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c9c7: push ecx */
	{ DWORD a_ = m->edx, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43c9c8: add edx, 0xa3 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43c9ce: push edx */
	m->esp -= 4; M32(m->esp) = 0x43c9d4u; native_call(m, 0x402620u);	/* 43c9cf: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43c9d4: add esp, 0x40 */
	goto L_43cc40;	/* 43c9d7: jmp 0x43cc40 */
L_43c9dc:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c9dc: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c9e1: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c9e6: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43c9eb: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43c9f0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43c9fau; native_call(m, 0x41f0e0u);	/* 43c9f5: call 0x41f0e0 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9e9u)));	/* 43c9fa: movsx ecx, byte ptr [0x4df9e9] */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 43ca01: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca05: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca07: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca08: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ca0eu; native_call(m, 0x49fb53u);	/* 43ca09: call 0x49fb53 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43ca0e: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43ca13: mov ecx, dword ptr [0x9dd1b8] */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 43ca19: lea edx, [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ca1d: add eax, 0x98 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca22: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ca23: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca29: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca2a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ca30u; native_call(m, 0x402620u);	/* 43ca2b: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca30: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca35: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca37: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca3c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca41: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43ca4bu; native_call(m, 0x41f0e0u);	/* 43ca46: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43ca4b: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43ca50: mov ecx, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ca56: add esp, 0x40 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 43ca59: lea edx, [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x97u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ca5d: add eax, 0x97 */
	{ DWORD a_ = m->ecx, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ca62: add ecx, 0xa3 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca68: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca69: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca6a: push ecx */
	goto L_43cc38;	/* 43ca6b: jmp 0x43cc38 */
L_43ca70:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca70: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca75: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca7a: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca7f: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ca84: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43ca8eu; native_call(m, 0x41f0e0u);	/* 43ca89: call 0x41f0e0 */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9ebu)));	/* 43ca8e: movsx edx, byte ptr [0x4df9eb] */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43ca95: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43ca9a: mov ecx, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43caa0: shl edx, 7 */
	{ DWORD a_ = m->edx, b_ = 0x7669a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43caa3: add edx, 0x7669a4 */
	{ DWORD a_ = m->eax, b_ = 0xdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43caa9: add eax, 0xdc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43caae: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43caaf: add ecx, 0xa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cab5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cab6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43cabcu; native_call(m, 0x402620u);	/* 43cab7: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cabc: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cac1: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43cac3: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cac8: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cacd: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43cad7u; native_call(m, 0x41f0e0u);	/* 43cad2: call 0x41f0e0 */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9ebu)));	/* 43cad7: movsx edx, byte ptr [0x4df9eb] */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43cade: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1b8u));	/* 43cae3: mov ecx, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43cae9: shl edx, 7 */
	{ DWORD a_ = m->edx, b_ = 0x7669a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43caec: add edx, 0x7669a4 */
	{ DWORD a_ = m->eax, b_ = 0xdbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43caf2: add eax, 0xdb */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43caf7: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43caf8: add ecx, 0xa3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cafe: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43caff: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43cb05u; native_call(m, 0x402620u);	/* 43cb00: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cb05: add esp, 0x40 */
	goto L_43cc40;	/* 43cb08: jmp 0x43cc40 */
L_43cb0d:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb0d: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb12: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb17: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb1c: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb21: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43cb2bu; native_call(m, 0x41f0e0u);	/* 43cb26: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4df9ecu));	/* 43cb2b: mov eax, dword ptr [0x4df9ec] */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 43cb30: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb34: push 0xa */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43cb36: and eax, 0xff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb3b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb3c: push eax */
	m->esp -= 4; M32(m->esp) = 0x43cb42u; native_call(m, 0x49fb53u);	/* 43cb3d: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43cb42: mov edx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43cb48: mov eax, dword ptr [0x9dd1b8] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 43cb4d: lea ecx, [esp + 0x34] */
	{ DWORD a_ = m->edx, b_ = 0xfeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43cb51: add edx, 0xfe */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb57: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43cb58: add eax, 0xa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb5d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb5e: push eax */
	m->esp -= 4; M32(m->esp) = 0x43cb64u; native_call(m, 0x402620u);	/* 43cb5f: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb64: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb69: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb6b: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb70: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb75: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43cb7fu; native_call(m, 0x41f0e0u);	/* 43cb7a: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43cb7f: mov edx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43cb85: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cb8a: add esp, 0x40 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 43cb8d: lea ecx, [esp + 0x14] */
	{ DWORD a_ = m->edx, b_ = 0xfdu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43cb91: add edx, 0xfd */
	{ DWORD a_ = m->eax, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43cb97: add eax, 0xa3 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb9c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb9d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cb9e: push eax */
	goto L_43cc38;	/* 43cb9f: jmp 0x43cc38 */
L_43cba4:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cba4: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43cba9: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbae: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbb3: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbb8: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43cbc2u; native_call(m, 0x41f0e0u);	/* 43cbbd: call 0x41f0e0 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43cbc2: xor edx, edx */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 43cbc4: lea ecx, [esp + 0x28] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9edu))) & 0xff) << 0);	/* 43cbc8: mov dl, byte ptr [0x4df9ed] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbce: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbd0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbd1: push edx */
	m->esp -= 4; M32(m->esp) = 0x43cbd7u; native_call(m, 0x49fb53u);	/* 43cbd2: call 0x49fb53 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43cbd7: mov ecx, dword ptr [0x9dd1bc] */
	m->edx = M32((DWORD)(0x9dd1b8u));	/* 43cbdd: mov edx, dword ptr [0x9dd1b8] */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 43cbe3: lea eax, [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0x120u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43cbe7: add ecx, 0x120 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbed: push eax */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43cbee: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbf4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbf5: push edx */
	m->esp -= 4; M32(m->esp) = 0x43cbfbu; native_call(m, 0x402620u);	/* 43cbf6: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cbfb: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc00: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc02: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc07: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc0c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43cc16u; native_call(m, 0x41f0e0u);	/* 43cc11: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43cc16: mov ecx, dword ptr [0x9dd1bc] */
	m->edx = M32((DWORD)(0x9dd1b8u));	/* 43cc1c: mov edx, dword ptr [0x9dd1b8] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cc22: add esp, 0x40 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 43cc25: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x11fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43cc29: add ecx, 0x11f */
	{ DWORD a_ = m->edx, b_ = 0xa3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43cc2f: add edx, 0xa3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc35: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc36: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc37: push edx */
L_43cc38:
	m->esp -= 4; M32(m->esp) = 0x43cc3du; native_call(m, 0x402620u);	/* 43cc38: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cc3d: add esp, 0xc */
L_43cc40:
	m->ebp = M32((DWORD)(0x4a9224u));	/* 43cc40: mov ebp, dword ptr [0x4a9224] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 43cc46: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43cc48: xor esi, esi */
	m->edi = 0x75a8a4u;	/* 43cc4a: mov edi, 0x75a8a4 */
L_43cc4f:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc4f: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43cc56u; native_call(m, m->ebp);	/* 43cc54: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43cc56: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 43cc5b: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43cc5d: and ecx, 0x800001ff */
	if (!m->sf) goto L_43cc6d;	/* 43cc63: jns 0x43cc6d */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43cc65: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43cc66: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43cc6c: inc ecx */
L_43cc6d:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43cc6d: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43cc6e: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc74: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43cc75: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43cc77: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43cc7d: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43cc80: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43cc89u; native_call(m, 0x4566c0u);	/* 43cc84: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 43cc89: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebx + 0x8u);	/* 43cc8d: lea eax, [ebx + 8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43cc90: cmp ecx, eax */
	if (!m->zf) goto L_43ccfa;	/* 43cc92: jne 0x43ccfa */
	m->eax = M32((DWORD)(0x68039cu));	/* 43cc94: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43cc99: test eax, eax */
	if (!m->zf) goto L_43ccfa;	/* 43cc9b: jne 0x43ccfa */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cc9d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cca2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cca7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccac: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43ccb7u; native_call(m, M32(0x4a9228u));	/* 43ccb1: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x9dd1c4u));	/* 43ccb7: mov ecx, dword ptr [0x9dd1c4] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43ccbd: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccc2: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 43ccc4: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ccc7: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccca: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 43cccb: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccd2: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 43ccd3: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccd7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccd8: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ccdeu; native_call(m, 0x4282f0u);	/* 43ccd9: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43ccde: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43cce4: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43ccea: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccef: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43ccf0: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccf6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccf7: push eax */
	goto L_43cd55;	/* 43ccf8: jmp 0x43cd55 */
L_43ccfa:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccfa: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ccff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd04: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd09: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43cd14u; native_call(m, M32(0x4a9228u));	/* 43cd0e: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x9dd1c4u));	/* 43cd14: mov ecx, dword ptr [0x9dd1c4] */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43cd1a: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd1f: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 43cd21: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43cd24: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd27: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 43cd28: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd2f: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 43cd30: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd34: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd35: push eax */
	m->esp -= 4; M32(m->esp) = 0x43cd3bu; native_call(m, 0x4282f0u);	/* 43cd36: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dd344u));	/* 43cd3b: mov ecx, dword ptr [0x9dd344] */
	m->edx = M32((DWORD)(0x9dd340u));	/* 43cd41: mov edx, dword ptr [0x9dd340] */
	m->eax = M32((DWORD)(0x9dd33cu));	/* 43cd47: mov eax, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd4c: push ecx */
	m->ecx = M32((DWORD)(0x9dd338u));	/* 43cd4d: mov ecx, dword ptr [0x9dd338] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd53: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd54: push eax */
L_43cd55:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd55: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd56: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43cd60u; native_call(m, 0x41f0e0u);	/* 43cd5b: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43cd60: mov eax, dword ptr [0x9dd1b8] */
	m->ecx = M32((DWORD)(0x9dd1c4u));	/* 43cd65: mov ecx, dword ptr [0x9dd1c4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cd6b: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43cd6e: add ecx, -0x38 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x104u);	/* 43cd71: lea edx, [esi + eax + 0x104] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd78: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd79: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 43cd7a: lea edx, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd7e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cd7f: push edx */
	m->esp -= 4; M32(m->esp) = 0x43cd85u; native_call(m, 0x4029d0u);	/* 43cd80: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cd85: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43cd88: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 43cd8e: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43cd8f: add esi, 0xc8 */
	{ DWORD a_ = m->edi, b_ = 0x75a9a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43cd95: cmp edi, 0x75a9a4 */
	if (m->sf != m->of) goto L_43cc4f;	/* 43cd9b: jl 0x43cc4f */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4df9e8u)));	/* 43cda1: movsx eax, byte ptr [0x4df9e8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cda8: push eax */
	m->esp -= 4; M32(m->esp) = 0x43cdaeu; native_call(m, 0x43bde0u);	/* 43cda9: call 0x43bde0 */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43cdae: mov eax, dword ptr [0x9db0a4] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cdb3: add esp, 4 */
	m->ecx = m->eax;	/* 43cdb6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43cdb8: and ecx, 0x800001ff */
	if (!m->sf) goto L_43cdc8;	/* 43cdbe: jns 0x43cdc8 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43cdc0: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43cdc1: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43cdc7: inc ecx */
L_43cdc8:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43cdc8: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43cdc9: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cdcf: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43cdd0: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43cdd2: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43cdd8: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43cddb: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43cde4u; native_call(m, 0x4566c0u);	/* 43cddf: call 0x4566c0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cde4: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43cdebu; native_call(m, m->ebp);	/* 43cde9: call ebp */
	m->edi = M32((DWORD)(0x4a9228u));	/* 43cdeb: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cdf1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cdf6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cdfb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce00: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43ce07u; native_call(m, m->edi);	/* 43ce05: call edi */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 43ce07: mov esi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->esi, b_ = 0xbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ce0b: cmp esi, 0xb */
	if (!m->zf) goto L_43cf11;	/* 43ce0e: jne 0x43cf11 */
	m->eax = M32((DWORD)(0x68039cu));	/* 43ce14: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ce19: test eax, eax */
	if (!m->zf) goto L_43cf11;	/* 43ce1b: jne 0x43cf11 */
	m->eax = M32((DWORD)(0x907b2cu));	/* 43ce21: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ce26: test eax, eax */
	if (!m->zf) goto L_43cf11;	/* 43ce28: jne 0x43cf11 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43ce2e: mov eax, dword ptr [0x9dd1bc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce33: push 1 */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 43ce35: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, b_ = 0xd7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ce3b: add eax, 0xd7 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce40: push ecx */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43ce41: mov ecx, dword ptr [0x9dd1c0] */
	m->edx = (DWORD)(m->ecx + 0xffffffa4u);	/* 43ce47: lea edx, [ecx - 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ce4a: add ecx, 0xffffff74 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce50: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce51: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce52: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ce58u; native_call(m, 0x4284d0u);	/* 43ce53: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ce58: add esp, 0x14 */
L_43ce5b:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce5b: push 0 */
L_43ce5d:
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43ce5d: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 43ce62: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, b_ = 0xd7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ce68: add eax, 0xd7 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce6d: push ecx */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43ce6e: mov ecx, dword ptr [0x9dd1c0] */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 43ce74: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffb0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ce77: add ecx, -0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce7a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce7b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce7c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ce82u; native_call(m, 0x4285c0u);	/* 43ce7d: call 0x4285c0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ce82: add esp, 0x14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ce85: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43ce8cu; native_call(m, m->ebp);	/* 43ce8a: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43ce8c: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 43ce91: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43ce93: and ecx, 0x800001ff */
	if (!m->sf) goto L_43cea3;	/* 43ce99: jns 0x43cea3 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43ce9b: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43ce9c: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43cea2: inc ecx */
L_43cea3:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43cea3: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43cea4: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ceaa: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ceab: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43cead: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43ceb3: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43ceb6: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43cebfu; native_call(m, 0x4566c0u);	/* 43ceba: call 0x4566c0 */
	{ DWORD a_ = m->esi, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43cebf: cmp esi, 0xd */
	if (!m->zf) goto L_43cf68;	/* 43cec2: jne 0x43cf68 */
	m->eax = M32((DWORD)(0x68039cu));	/* 43cec8: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43cecd: test eax, eax */
	if (!m->zf) goto L_43cf68;	/* 43cecf: jne 0x43cf68 */
	m->eax = M32((DWORD)(0x4db508u));	/* 43ced5: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ceda: test eax, eax */
	if (!m->zf) goto L_43cf68;	/* 43cedc: jne 0x43cf68 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cee2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cee7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ceec: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cef1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43cef8u; native_call(m, m->edi);	/* 43cef6: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cef8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cefd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf02: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf07: push 0x3f800000 */
	goto L_43cf92;	/* 43cf0c: jmp 0x43cf92 */
L_43cf11:
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43cf11: mov eax, dword ptr [0x9dd1bc] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf16: push 0 */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 43cf18: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, b_ = 0xd7u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43cf1e: add eax, 0xd7 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf23: push ecx */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43cf24: mov ecx, dword ptr [0x9dd1c0] */
	m->edx = (DWORD)(m->ecx + 0xffffffa4u);	/* 43cf2a: lea edx, [ecx - 0x5c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43cf2d: add ecx, 0xffffff74 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf33: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf34: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf35: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43cf3bu; native_call(m, 0x4284d0u);	/* 43cf36: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cf3b: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43cf3e: cmp esi, 0xc */
	if (!m->zf) goto L_43ce5b;	/* 43cf41: jne 0x43ce5b */
	m->eax = M32((DWORD)(0x68039cu));	/* 43cf47: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43cf4c: test eax, eax */
	if (!m->zf) goto L_43ce5b;	/* 43cf4e: jne 0x43ce5b */
	m->eax = M32((DWORD)(0x907b2cu));	/* 43cf54: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43cf59: test eax, eax */
	if (!m->zf) goto L_43ce5b;	/* 43cf5b: jne 0x43ce5b */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf61: push 1 */
	goto L_43ce5d;	/* 43cf63: jmp 0x43ce5d */
L_43cf68:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf68: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf6d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf72: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf77: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43cf7eu; native_call(m, m->edi);	/* 43cf7c: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf7e: push 0x3f800000 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf83: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf88: push 0x3f333333 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf8d: push 0x3e99999a */
L_43cf92:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cf92: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43cf9cu; native_call(m, 0x41f0e0u);	/* 43cf97: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43cf9c: mov eax, dword ptr [0x9dd1bc] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cfa1: add esp, 0x14 */
	m->ecx = (DWORD)(m->eax + 0x111u);	/* 43cfa4: lea ecx, [eax + 0x111] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfaa: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfac: push ecx */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43cfad: mov ecx, dword ptr [0x9dd1c0] */
	{ DWORD a_ = m->eax, b_ = 0xf5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43cfb3: add eax, 0xf5 */
	m->edx = (DWORD)(m->ecx + 0xffffffeau);	/* 43cfb8: lea edx, [ecx - 0x16] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43cfbb: add ecx, 0xffffff6a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfc1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfc2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfc3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43cfc9u; native_call(m, 0x4282f0u);	/* 43cfc4: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9dd1c0u));	/* 43cfc9: mov eax, dword ptr [0x9dd1c0] */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43cfce: mov edx, dword ptr [0x9dd1bc] */
	{ DWORD v_ = 0x75d8a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfd4: push 0x75d8a4 */
	{ DWORD a_ = m->edx, b_ = 0xfbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43cfd9: add edx, 0xfb */
	m->ecx = (DWORD)(m->eax + 0xffffffeau);	/* 43cfdf: lea ecx, [eax - 0x16] */
	{ DWORD a_ = m->eax, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43cfe2: add eax, 0xffffff6a */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfe7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfe8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43cfe9: push eax */
	m->esp -= 4; M32(m->esp) = 0x43cfefu; native_call(m, 0x4029d0u);	/* 43cfea: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43cfef: add esp, 0x24 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cff2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cff7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43cffc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d001: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43d008u; native_call(m, m->edi);	/* 43d006: call edi */
	m->eax = M32((DWORD)(0x9dd1c4u));	/* 43d008: mov eax, dword ptr [0x9dd1c4] */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43d00d: mov ecx, dword ptr [0x9dd1c0] */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43d013: mov edx, dword ptr [0x9dd1bc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d019: push eax */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43d01a: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d01f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d020: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d021: push eax */
	m->esp -= 4; M32(m->esp) = 0x43d027u; native_call(m, 0x428a00u);	/* 43d022: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d027: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43d02a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43d02b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43d02c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43d02d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d02e: add esp, 0x18 */
	m->esp += 4 + 0; return;	/* 43d031: ret  */
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
