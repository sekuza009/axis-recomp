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

static void lift_4125f0(X86 *m);
static void lift_4290d0(X86 *m);
static void lift_428940(X86 *m);
static void lift_44ce90(X86 *m);
static void lift_442d10(X86 *m);
static void lift_4125c0(X86 *m);

/* armc_4125c0 (0x4125c0), lifted by tools/lift.py */
static void lift_4125c0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 4125c0: mov eax, dword ptr [0x9dae74] */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 4125c5: mov ecx, dword ptr [esp + 8] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 4125c9: mov edx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4125cd: cmp eax, 2 */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 4125d0: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4125d4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4125d5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4125d6: push edx */
	if (!m->zf) goto L_4125e2;	/* 4125d7: jne 0x4125e2 */
	m->esp -= 4; M32(m->esp) = 0x4125deu; native_call(m, 0x403170u);	/* 4125d9: call 0x403170 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4125de: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 4125e1: ret  */
L_4125e2:
	m->esp -= 4; M32(m->esp) = 0x4125e7u; native_call(m, 0x402620u);	/* 4125e2: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4125e7: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 4125ea: ret  */
}

/* armc_drawStatLabel (0x4125f0), lifted by tools/lift.py */
static void lift_4125f0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 4125f0: mov eax, dword ptr [0x9dae74] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4125f5: push edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 4125f6: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4125fa: cmp eax, 2 */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 4125fd: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 412601: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412602: push eax */
	if (!m->zf) goto L_412625;	/* 412603: jne 0x412625 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412605: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412608: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41260a: repne scasb al, byte ptr es:[edi] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 41260c: mov edx, dword ptr [esp + 0x10] */
	m->ecx = ~m->ecx;	/* 412610: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 412612: dec ecx */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 412613: lea ecx, [ecx + ecx*2] */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412616: shl ecx, 1 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 412618: sub edx, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41261a: push edx */
	m->esp -= 4; M32(m->esp) = 0x412620u; native_call(m, 0x403170u);	/* 41261b: call 0x403170 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412620: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 412623: pop edi */
	m->esp += 4 + 0; return;	/* 412624: ret  */
L_412625:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412625: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412628: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41262a: repne scasb al, byte ptr es:[edi] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 41262c: mov edx, dword ptr [esp + 0x10] */
	m->ecx = ~m->ecx;	/* 412630: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 412632: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 412633: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 412636: sub edx, ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412638: push edx */
	m->esp -= 4; M32(m->esp) = 0x41263eu; native_call(m, 0x402620u);	/* 412639: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41263e: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 412641: pop edi */
	m->esp += 4 + 0; return;	/* 412642: ret  */
}

/* menu_4290d0 (0x4290d0), lifted by tools/lift.py */
static void lift_4290d0(X86 *m)
{
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4290d0: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4290d7u; native_call(m, 0x41ef90u);	/* 4290d2: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4290d7: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4290e0u; native_call(m, M32(0x4a9218u));	/* 4290da: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4290e0: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4290e5: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4290ea: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4290ef: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4290f4: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4290feu; native_call(m, 0x41f0e0u);	/* 4290f9: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4290fe: push 1 */
	{ DWORD v_ = 0x118u; m->esp -= 4; M32(m->esp) = v_; }	/* 429100: push 0x118 */
	{ DWORD v_ = 0x230u; m->esp -= 4; M32(m->esp) = v_; }	/* 429105: push 0x230 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42910a: push 0xc8 */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42910f: push 0x50 */
	m->esp -= 4; M32(m->esp) = 0x429116u; native_call(m, 0x427970u);	/* 429111: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429116: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42911b: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42911d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429122: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 429127: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x429131u; native_call(m, 0x41f0e0u);	/* 42912c: call 0x41f0e0 */
	{ DWORD v_ = 0x4df81cu; m->esp -= 4; M32(m->esp) = v_; }	/* 429131: push 0x4df81c */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 429136: push 0x217 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42913b: push 0xdc */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 429140: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x429147u; native_call(m, 0x4029d0u);	/* 429142: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429147: add esp, 0x4c */
	{ DWORD v_ = 0x74de24u; m->esp -= 4; M32(m->esp) = v_; }	/* 42914a: push 0x74de24 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 42914f: push 0x217 */
	{ DWORD v_ = 0xf4u; m->esp -= 4; M32(m->esp) = v_; }	/* 429154: push 0xf4 */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 429159: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x429160u; native_call(m, 0x4029d0u);	/* 42915b: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429160: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 429163: ret  */
}

/* menu_428940 (0x428940), lifted by tools/lift.py */
static void lift_428940(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 428940: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428945: sub esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 428948: test eax, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42894a: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42894b: push esi */
	if (!m->zf) goto L_4289ec;	/* 42894c: jne 0x4289ec */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428952: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428957: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428959: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42895e: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 428960: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x42896au; native_call(m, 0x41f0e0u);	/* 428965: call 0x41f0e0 */
	m->ebx = M32((DWORD)(m->esp + 0x54u));	/* 42896a: mov ebx, dword ptr [esp + 0x54] */
	m->eax = M32((DWORD)(0x9dbf10u));	/* 42896e: mov eax, dword ptr [0x9dbf10] */
	m->esi = M32((DWORD)(m->esp + 0x58u));	/* 428973: mov esi, dword ptr [esp + 0x58] */
	m->ecx = (DWORD)(m->ebx + m->eax*8 + 0x0u);	/* 428977: lea ecx, [ebx + eax*8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42897a: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42897b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x428981u; native_call(m, 0x428890u);	/* 42897c: call 0x428890 */
	m->eax = M32((DWORD)(0x4e1868u));	/* 428981: mov eax, dword ptr [0x4e1868] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428986: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 428989: test eax, eax */
	if (m->zf) goto L_4289dd;	/* 42898b: je 0x4289dd */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42898d: push edi */
	m->edi = 0x9dc92cu;	/* 42898e: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 428993: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 428996: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 428998: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42899a: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42899c: dec ecx */
	m->edi = (DWORD)(m->esp + 0xcu);	/* 42899d: lea edi, [esp + 0xc] */
	m->edx = m->ecx;	/* 4289a1: mov edx, ecx */
	m->ecx = 0x7u;	/* 4289a3: mov ecx, 7 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4289a8: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4289aa: test edx, edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4289ac: stosw word ptr es:[edi], ax */
	if (m->zf || m->sf != m->of) goto L_4289c7;	/* 4289ae: jle 0x4289c7 */
	m->ecx = m->edx;	/* 4289b0: mov ecx, edx */
	m->eax = 0x2a2a2a2au;	/* 4289b2: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0xcu);	/* 4289b7: lea edi, [esp + 0xc] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4289bb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4289be: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 4289c0: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4289c2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 4289c5: rep stosb byte ptr es:[edi], al */
L_4289c7:
	m->eax = (DWORD)(m->esp + 0xcu);	/* 4289c7: lea eax, [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4289cb: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4289cc: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4289cd: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4289d3u; native_call(m, 0x402620u);	/* 4289ce: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4289d3: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 4289d6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4289d7: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4289d8: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4289d9: add esp, 0x34 */
	m->esp += 4 + 0; return;	/* 4289dc: ret  */
L_4289dd:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4289dd: push 0x9dc92c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4289e2: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4289e3: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4289e9u; native_call(m, 0x402620u);	/* 4289e4: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4289e9: add esp, 0xc */
L_4289ec:
	m->esi = M32(m->esp); m->esp += 4;	/* 4289ec: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4289ed: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4289ee: add esp, 0x34 */
	m->esp += 4 + 0; return;	/* 4289f1: ret  */
}

/* profile_44ce90 (0x44ce90), lifted by tools/lift.py */
static void lift_44ce90(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ce90: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ce91: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ce92: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 44ce93: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44ce95: xor esi, esi */
	m->ebx = 0x1u;	/* 44ce97: mov ebx, 1 */
L_44ce9c:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(0x9f9008u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ce9c: cmp edi, dword ptr [0x9f9008] */
	if (m->sf == m->of) goto L_44cf5f;	/* 44cea2: jge 0x44cf5f */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44cea8: mov eax, dword ptr [0x9f8f10] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cead: push 0x3f800000 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ceb2: cmp eax, ebx */
	if (!m->zf) goto L_44cec2;	/* 44ceb4: jne 0x44cec2 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ceb6: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cebb: push 0x3f000000 */
	goto L_44cecc;	/* 44cec0: jmp 0x44cecc */
L_44cec2:
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 44cec2: push 0x3e99999a */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 44cec7: push 0x3e99999a */
L_44cecc:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cecc: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cece: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44ced8u; native_call(m, 0x41f0e0u);	/* 44ced3: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8c4cu));	/* 44ced8: mov eax, dword ptr [0x9f8c4c] */
	m->ecx = M32((DWORD)(0x9f8d74u));	/* 44cedd: mov ecx, dword ptr [0x9f8d74] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cee3: add eax, edi */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cee5: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cee8: cmp eax, ecx */
	if (!m->zf) goto L_44cf1f;	/* 44ceea: jne 0x44cf1f */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44ceec: mov eax, dword ptr [0x9f8f10] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cef1: push 0x3f800000 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cef6: cmp eax, ebx */
	if (!m->zf) goto L_44cf06;	/* 44cef8: jne 0x44cf06 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cefa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ceff: push 0x3f800000 */
	goto L_44cf10;	/* 44cf04: jmp 0x44cf10 */
L_44cf06:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf06: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf0b: push 0x3f000000 */
L_44cf10:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf10: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf12: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44cf1cu; native_call(m, 0x41f0e0u);	/* 44cf17: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cf1c: add esp, 0x14 */
L_44cf1f:
	m->ecx = M32((DWORD)(0x9f8c4cu));	/* 44cf1f: mov ecx, dword ptr [0x9f8c4c] */
	m->eax = (DWORD)(m->ecx + m->edi*1 + 0x0u);	/* 44cf25: lea eax, [ecx + edi] */
	m->ecx = M32((DWORD)(0x9f8e4cu));	/* 44cf28: mov ecx, dword ptr [0x9f8e4c] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44cf2e: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->edx*8 + 0x9f684cu);	/* 44cf31: lea eax, [edx*8 + 0x9f684c] */
	m->edx = (DWORD)(m->esi + m->ecx*1 + 0x24u);	/* 44cf38: lea edx, [esi + ecx + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf3c: push eax */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44cf3d: mov eax, dword ptr [0x9f8e48] */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cf42: add eax, 0x28 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf45: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cf46: push eax */
	m->esp -= 4; M32(m->esp) = 0x44cf4cu; native_call(m, 0x402620u);	/* 44cf47: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cf4c: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44cf4f: add esi, 0x14 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 44cf52: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x104u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cf53: cmp esi, 0x104 */
	if (m->sf != m->of) goto L_44ce9c;	/* 44cf59: jl 0x44ce9c */
L_44cf5f:
	m->edi = M32(m->esp); m->esp += 4;	/* 44cf5f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44cf60: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44cf61: pop ebx */
	m->esp += 4 + 0; return;	/* 44cf62: ret  */
}

/* mainmenu_442d10 (0x442d10), lifted by tools/lift.py */
static void lift_442d10(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 442d10: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 442d11: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 442d12: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 442d14: xor esi, esi */
L_442d16:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(0x9dd928u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442d16: cmp edi, dword ptr [0x9dd928] */
	if (m->sf == m->of) goto L_442e05;	/* 442d1c: jge 0x442e05 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442d22: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442d27: push 0x3f800000 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 442d2c: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 442d31: push 0x3f4ccccd */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 442d36: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x442d40u; native_call(m, 0x41f0e0u);	/* 442d3b: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd92cu));	/* 442d40: mov eax, dword ptr [0x9dd92c] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442d45: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442d48: add eax, edi */
	m->ecx = m->eax;	/* 442d4a: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 442d4c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 442d4f: add ecx, eax */
	m->eax = M32((DWORD)(m->ecx*4 + 0x9ddac8u));	/* 442d51: mov eax, dword ptr [ecx*4 + 0x9ddac8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 442d58: test eax, eax */
	if (m->zf) goto L_442dc1;	/* 442d5a: je 0x442dc1 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442d5c: push 0x3f000000 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 442d61: push 0x3e99999a */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 442d66: push 0x3dcccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442d6b: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 442d70: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x442d7au; native_call(m, 0x41f0e0u);	/* 442d75: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd90cu));	/* 442d7a: mov eax, dword ptr [0x9dd90c] */
	m->ecx = M32((DWORD)(0x9dd910u));	/* 442d7f: mov ecx, dword ptr [0x9dd910] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 442d85: push 1 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffb0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 442d87: add ecx, -0x50 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x3du);	/* 442d8a: lea edx, [esi + eax + 0x3d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442d8e: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x2bu);	/* 442d8f: lea edx, [esi + eax + 0x2b] */
	m->eax = M32((DWORD)(0x9dd908u));	/* 442d93: mov eax, dword ptr [0x9dd908] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442d98: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442d99: add eax, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442d9c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442d9d: push eax */
	m->esp -= 4; M32(m->esp) = 0x442da3u; native_call(m, 0x427970u);	/* 442d9e: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442da3: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442da8: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442daa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442daf: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 442db4: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x442dbeu; native_call(m, 0x41f0e0u);	/* 442db9: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442dbe: add esp, 0x3c */
L_442dc1:
	m->ecx = M32((DWORD)(0x9dd92cu));	/* 442dc1: mov ecx, dword ptr [0x9dd92c] */
	m->eax = (DWORD)(m->ecx + m->edi*1 + 0x0u);	/* 442dc7: lea eax, [ecx + edi] */
	m->ecx = M32((DWORD)(0x9dd90cu));	/* 442dca: mov ecx, dword ptr [0x9dd90c] */
	m->edx = m->eax;	/* 442dd0: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 442dd2: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 442dd5: add edx, eax */
	m->eax = (DWORD)(m->edx*4 + 0x9dda88u);	/* 442dd7: lea eax, [edx*4 + 0x9dda88] */
	m->edx = (DWORD)(m->esi + m->ecx*1 + 0x2cu);	/* 442dde: lea edx, [esi + ecx + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442de2: push eax */
	m->eax = M32((DWORD)(0x9dd908u));	/* 442de3: mov eax, dword ptr [0x9dd908] */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442de8: add eax, 0x28 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442deb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442dec: push eax */
	m->esp -= 4; M32(m->esp) = 0x442df2u; native_call(m, 0x402620u);	/* 442ded: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442df2: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 442df5: add esi, 0x14 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 442df8: inc edi */
	{ DWORD a_ = m->esi, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 442df9: cmp esi, 0xc8 */
	if (m->sf != m->of) goto L_442d16;	/* 442dff: jl 0x442d16 */
L_442e05:
	m->edi = M32(m->esp); m->esp += 4;	/* 442e05: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 442e06: pop esi */
	m->esp += 4 + 0; return;	/* 442e07: ret  */
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
