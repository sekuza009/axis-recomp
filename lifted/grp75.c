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

static void lift_408680(X86 *m);

/* lobbyTop_drawTitle (0x408680), lifted by tools/lift.py */
static void lift_408680(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408680: sub esp, 0x4c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 408683: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 408684: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 408685: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 408686: push edi */
	M32((DWORD)(m->esp + 0x3cu)) = 0xffffffffu;	/* 408687: mov dword ptr [esp + 0x3c], 0xffffffff */
	M32((DWORD)(m->esp + 0x54u)) = 0xc20c0000u;	/* 40868f: mov dword ptr [esp + 0x54], 0xc20c0000 */
	M32((DWORD)(m->esp + 0x58u)) = 0x420c0000u;	/* 408697: mov dword ptr [esp + 0x58], 0x420c0000 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 40869f: xor ebp, ebp */
	m->ebx = 0x5b1cf8u;	/* 4086a1: mov ebx, 0x5b1cf8 */
L_4086a6:
	m->eax = M32((DWORD)(0x4db85cu));	/* 4086a6: mov eax, dword ptr [0x4db85c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4086ab: test eax, eax */
	if (!m->zf) goto L_4086f8;	/* 4086ad: jne 0x4086f8 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4086af: mov eax, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4086b4: sub esp, 0x2c */
	m->ecx = 0xbu;	/* 4086b7: mov ecx, 0xb */
	m->esi = m->ebx;	/* 4086bc: mov esi, ebx */
	m->edi = m->esp;	/* 4086be: mov edi, esp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4086c0: push eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4086c1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4086c3: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4086c9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4086cfu; native_call(m, 0x41eea0u);	/* 4086ca: call 0x41eea0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4086cf: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4086d2: cmp eax, 1 */
	if (m->zf) goto L_4086ef;	/* 4086d5: je 0x4086ef */
	{ DWORD a_ = m->ebx, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4086d7: add ebx, 0x2c */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 4086da: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x5b1da8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4086db: cmp ebx, 0x5b1da8 */
	if (m->sf != m->of) goto L_4086a6;	/* 4086e1: jl 0x4086a6 */
	M32((DWORD)(0x680398u)) = 0x0u;	/* 4086e3: mov dword ptr [0x680398], 0 */
	goto L_408731;	/* 4086ed: jmp 0x408731 */
L_4086ef:
	{ DWORD a_ = m->ebp, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4086ef: cmp ebp, -1 */
	M32((DWORD)(m->esp + 0x3cu)) = m->ebp;	/* 4086f2: mov dword ptr [esp + 0x3c], ebp */
	if (!m->zf) goto L_408704;	/* 4086f6: jne 0x408704 */
L_4086f8:
	M32((DWORD)(0x680398u)) = 0x0u;	/* 4086f8: mov dword ptr [0x680398], 0 */
	goto L_408731;	/* 408702: jmp 0x408731 */
L_408704:
	m->eax = M32((DWORD)(0x907b24u));	/* 408704: mov eax, dword ptr [0x907b24] */
	M32((DWORD)(0x680398u)) = 0x1u;	/* 408709: mov dword ptr [0x680398], 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408713: cmp eax, ebp */
	if (m->zf) goto L_408731;	/* 408715: je 0x408731 */
	M32((DWORD)(0x907b24u)) = m->ebp;	/* 408717: mov dword ptr [0x907b24], ebp */
	M32((DWORD)(0x680cccu)) = 0x42200000u;	/* 40871d: mov dword ptr [0x680ccc], 0x42200000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 408727: mov dword ptr [0x4df454], 0xbf800000 */
L_408731:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 408731: push 1 */
	m->esp -= 4; M32(m->esp) = 0x408738u; native_call(m, 0x41ef90u);	/* 408733: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408738: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40873b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x408746u; native_call(m, M32(0x4a9224u));	/* 408740: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 408746: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 40874c: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 408752: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 408758: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40875e: xor eax, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 408760: mov dword ptr [esp + 0x24], eax */
	goto L_40876a;	/* 408764: jmp 0x40876a */
L_408766:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 408766: mov eax, dword ptr [esp + 0x24] */
L_40876a:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40876a: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 40876d: mov dword ptr [esp + 0x1c], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3f000000u;	/* 408775: mov dword ptr [esp + 0x34], 0x3f000000 */
	M32((DWORD)(m->esp + 0x48u)) = 0x0u;	/* 40877d: mov dword ptr [esp + 0x48], 0 */
	M32((DWORD)(m->esp + 0x4cu)) = 0x3e800000u;	/* 408785: mov dword ptr [esp + 0x4c], 0x3e800000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3f000000u;	/* 40878d: mov dword ptr [esp + 0x40], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_4087bf;	/* 408795: jle 0x4087bf */
	M32((DWORD)(m->esp + 0x1cu)) = 0x3f000000u;	/* 408797: mov dword ptr [esp + 0x1c], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 40879f: mov dword ptr [esp + 0x34], 0 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3f000000u;	/* 4087a7: mov dword ptr [esp + 0x48], 0x3f000000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0x3f400000u;	/* 4087af: mov dword ptr [esp + 0x4c], 0x3f400000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3f800000u;	/* 4087b7: mov dword ptr [esp + 0x40], 0x3f800000 */
L_4087bf:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4087bf: cmp eax, 2 */
	if (m->sf == m->of) goto L_4087f4;	/* 4087c2: jge 0x4087f4 */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 4087c4: mov eax, dword ptr [0x4e0cd0] */
	m->edx = m->eax;	/* 4087c9: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4087cb: and edx, 0x800001ff */
	if (!m->sf) goto L_4087db;	/* 4087d1: jns 0x4087db */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4087d3: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4087d4: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4087da: inc edx */
L_4087db:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4087db: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4087dc: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4087e2: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4087e3: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4087e9: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4087eb: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4087ee: mov ecx, dword ptr [ecx + eax*4 + 4] */
	goto L_40882d;	/* 4087f2: jmp 0x40882d */
L_4087f4:
	m->edx = (DWORD)(m->eax*4 + 0x0u);	/* 4087f4: lea edx, [eax*4] */
	m->eax = 0x4df04cu;	/* 4087fb: mov eax, 0x4df04c */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 408800: sub eax, edx */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 408802: mov eax, dword ptr [eax] */
	m->ecx = m->eax;	/* 408804: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 408806: and ecx, 0x800001ff */
	if (!m->sf) goto L_408816;	/* 40880c: jns 0x408816 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40880e: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40880f: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 408815: inc ecx */
L_408816:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 408816: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 408817: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40881d: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40881e: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 408820: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 408826: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 408829: mov ecx, dword ptr [edx + eax*4 + 4] */
L_40882d:
	m->esp -= 4; M32(m->esp) = 0x408832u; native_call(m, 0x4566c0u);	/* 40882d: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 408832: mov dword ptr [esp + 0x20], 0 */
L_40883a:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 40883a: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40883e: and eax, 0x80000001 */
	if (!m->sf) goto L_40884a;	/* 408843: jns 0x40884a */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 408845: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 408846: or eax, 0xfffffffe */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 408849: inc eax */
L_40884a:
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 40884a: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x408853u; native_call(m, 0x41f050u);	/* 40884e: call 0x41f050 */
	m->eax = M32((DWORD)(0x4dba68u));	/* 408853: mov eax, dword ptr [0x4dba68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408858: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408859: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40885b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408863u; native_call(m, M32(0x4a9214u));	/* 40885d: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408863: cmp dword ptr [esp + 0x20], 2 */
	if (m->sf == m->of) goto L_408875;	/* 408868: jge 0x408875 */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 40886a: mov ecx, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + m->ecx*4 + 0x54u));	/* 40886e: mov edx, dword ptr [esp + ecx*4 + 0x54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408872: push edx */
	goto L_408883;	/* 408873: jmp 0x408883 */
L_408875:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 408875: mov eax, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408879: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->eax*4 + 0x58u)));	/* 40887a: fld dword ptr [esp + eax*4 + 0x58] */
	ST(0) = -ST(0);	/* 40887e: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408880: fstp dword ptr [esp] */
L_408883:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408883: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408885: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40888cu; native_call(m, 0x41ef20u);	/* 408887: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 40888c: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408890: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408893: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_408a74;	/* 408896: ja 0x408a74 */
	switch (m->eax) { case 0: goto L_4088a3; case 1: goto L_4088d3; case 2: goto L_4088f2; case 3: goto L_408920; default: abort(); }	/* 40889c: jmp dword ptr [eax*4 + 0x409194] */
L_4088a3:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 4088a3: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 4088a9: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4088af: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4088b0: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4088b6: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4088b9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4088be: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4088c3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4088ceu; native_call(m, M32(0x4a9228u));	/* 4088c8: call dword ptr [0x4a9228] */
	goto L_408d4e;	/* 4088ce: jmp 0x408d4e */
L_4088d3:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4088d3: push 0x3ecccccd */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4088d8: push 0x41200000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4088dd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4088e2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4088edu; native_call(m, M32(0x4a9228u));	/* 4088e7: call dword ptr [0x4a9228] */
	goto L_408a7d;	/* 4088ed: jmp 0x408a7d */
L_4088f2:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4088f2: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 4088f6: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4088fa: cmp eax, ecx */
	if (!m->zf) goto L_408916;	/* 4088fc: jne 0x408916 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 4088fe: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9428u));	/* 408904: fmul dword ptr [0x4a9428] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40890a: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 40890b: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408911: fstp dword ptr [esp] */
	goto L_408949;	/* 408914: jmp 0x408949 */
L_408916:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408916: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408918: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40891a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40891c: push 0 */
	goto L_408958;	/* 40891e: jmp 0x408958 */
L_408920:
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 408920: mov edx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 408924: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408928: cmp eax, edx */
	if (!m->zf) goto L_408944;	/* 40892a: jne 0x408944 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 40892c: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 408932: fmul dword ptr [0x4a9420] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408938: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 408939: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 40893f: fstp dword ptr [esp] */
	goto L_408949;	/* 408942: jmp 0x408949 */
L_408944:
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 408944: push 0x3f19999a */
L_408949:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408949: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40894e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408953: push 0x3f800000 */
L_408958:
	m->esp -= 4; M32(m->esp) = 0x40895eu; native_call(m, M32(0x4a9228u));	/* 408958: call dword ptr [0x4a9228] */
L_40895e:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 40895e: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 408962: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408964: cmp eax, 2 */
	if (m->sf == m->of) goto L_408eeb;	/* 408967: jge 0x408eeb */
	m->esp -= 4; M32(m->esp) = 0x40896fu; native_call(m, m->ebx);	/* 40896d: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 40896f: fild dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 408973: fst dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 408977: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 40897d: fstp dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 408981: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408985: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408986: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40898au; native_call(m, m->esi);	/* 408988: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 40898a: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 40898e: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 408994: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 408998: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 40899e: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4089a2: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4089a6: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4089aa: fmul dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 4089b0: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4089b4: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4089b5: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 4089b9: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 4089bf: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4089c3: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 4089c7: fild dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4089cb: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4089cf: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 4089d0: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 4089d6: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4089dc: fstp dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4089e0: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4089e4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4089e7u; native_call(m, m->edi);	/* 4089e5: call edi */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 4089e7: mov edx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4089eb: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = m->edx;	/* 4089ef: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4089f1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4089f2: push ecx */
	M32((DWORD)(m->esp + 0x4cu)) = m->edx;	/* 4089f3: mov dword ptr [esp + 0x4c], edx */
	m->esp -= 4; M32(m->esp) = 0x4089f9u; native_call(m, m->esi);	/* 4089f7: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4089f9: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4089fd: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 408a03: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 408a07: mov ecx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 408a0b: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 408a0f: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408a13: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408a14: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408a15: push ecx */
	m->esp -= 4; M32(m->esp) = 0x408a18u; native_call(m, m->edi);	/* 408a16: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 408a18: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 408a1c: fadd dword ptr [0x4a9424] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 408a22: mov eax, dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 408a26: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 408a2c: fstp dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 408a30: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408a34: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408a35: push eax */
	m->esp -= 4; M32(m->esp) = 0x408a38u; native_call(m, m->esi);	/* 408a36: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 408a38: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 408a3c: fsub dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 408a42: mov ecx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 408a46: mov eax, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408a4a: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 408a4b: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 408a4f: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408a53: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408a54: push eax */
	m->esp -= 4; M32(m->esp) = 0x408a57u; native_call(m, m->edi);	/* 408a55: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 408a57: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408a5b: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408a5c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408a60u; native_call(m, m->esi);	/* 408a5e: call esi */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 408a60: mov edx, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 408a64: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 408a68: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408a6c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408a6d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408a6e: push ecx */
	goto L_408ff5;	/* 408a6f: jmp 0x408ff5 */
L_408a74:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408a74: cmp eax, 1 */
	if (!m->zf) goto L_408d46;	/* 408a77: jne 0x408d46 */
L_408a7d:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 408a7d: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 408a81: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408a83: cmp eax, 2 */
	if (m->sf == m->of) goto L_408bf5;	/* 408a86: jge 0x408bf5 */
	m->esp -= 4; M32(m->esp) = 0x408a8eu; native_call(m, m->ebx);	/* 408a8c: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408a8e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408a90: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408a94u; native_call(m, m->esi);	/* 408a92: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408a94: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 408a9a: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408aa0: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408aa1: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408aa7: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408aaa: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408aaf: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408ab6u; native_call(m, m->edi);	/* 408ab4: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408ab6: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 408abc: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ac2: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408ac4: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 408ac5: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408acb: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x408ad0u; native_call(m, m->esi);	/* 408ace: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ad0: push 0xc2200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ad5: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ada: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408ae1u; native_call(m, m->edi);	/* 408adf: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408ae1: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 408ae7: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408aed: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408af2: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 408af3: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408af9: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x408afeu; native_call(m, m->esi);	/* 408afc: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408afe: push 0xc2200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b03: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b08: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408b0fu; native_call(m, m->edi);	/* 408b0d: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b0f: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b14: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408b18u; native_call(m, m->esi);	/* 408b16: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408b18: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 408b1e: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408b24: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408b25: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408b2b: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b2e: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b33: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408b3au; native_call(m, m->edi);	/* 408b38: call edi */
	m->esp -= 4; M32(m->esp) = 0x408b3cu; native_call(m, m->ebp);	/* 408b3a: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b3c: push 7 */
	m->esp -= 4; M32(m->esp) = 0x408b40u; native_call(m, m->ebx);	/* 408b3e: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408b40: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 408b46: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b4c: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408b4e: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 408b4f: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408b55: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x408b5au; native_call(m, m->esi);	/* 408b58: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b5a: push 0x42200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b5f: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b64: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408b6bu; native_call(m, m->edi);	/* 408b69: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b6b: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b6d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x408b74u; native_call(m, m->esi);	/* 408b72: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408b74: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 408b7a: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408b80: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408b81: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408b87: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b8a: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b8f: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408b96u; native_call(m, m->edi);	/* 408b94: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b96: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408b9b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x408ba2u; native_call(m, m->esi);	/* 408ba0: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408ba2: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 408ba8: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408bae: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408baf: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408bb5: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408bb8: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408bbd: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408bc4u; native_call(m, m->edi);	/* 408bc2: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408bc4: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 408bca: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408bd0: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408bd5: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 408bd6: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408bdc: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x408be1u; native_call(m, m->esi);	/* 408bdf: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408be1: push 0x42200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408be6: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408beb: push 0xc1ef3333 */
	goto L_408ff5;	/* 408bf0: jmp 0x408ff5 */
L_408bf5:
	m->esp -= 4; M32(m->esp) = 0x408bf7u; native_call(m, m->ebx);	/* 408bf5: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408bf7: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 408bfd: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c03: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408c05: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408c06: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x408c0bu; native_call(m, m->esi);	/* 408c09: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c0b: push 0xc2200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c10: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c15: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408c1cu; native_call(m, m->edi);	/* 408c1a: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c1c: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c1e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x408c25u; native_call(m, m->esi);	/* 408c23: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408c25: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 408c2b: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408c31: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408c32: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408c38: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c3b: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c40: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408c47u; native_call(m, m->edi);	/* 408c45: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c47: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c4c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x408c53u; native_call(m, m->esi);	/* 408c51: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408c53: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 408c59: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408c5f: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408c60: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408c66: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c69: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c6e: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408c75u; native_call(m, m->edi);	/* 408c73: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408c75: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 408c7b: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c81: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408c86: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408c87: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x408c8cu; native_call(m, m->esi);	/* 408c8a: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c8c: push 0xc2200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c91: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c96: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408c9du; native_call(m, m->edi);	/* 408c9b: call edi */
	m->esp -= 4; M32(m->esp) = 0x408c9fu; native_call(m, m->ebp);	/* 408c9d: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 408c9f: push 7 */
	m->esp -= 4; M32(m->esp) = 0x408ca3u; native_call(m, m->ebx);	/* 408ca1: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ca3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ca5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408ca9u; native_call(m, m->esi);	/* 408ca7: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408ca9: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 408caf: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408cb5: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408cb6: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408cbc: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408cbf: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408cc4: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408ccbu; native_call(m, m->edi);	/* 408cc9: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408ccb: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 408cd1: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408cd7: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408cd9: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408cda: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x408cdfu; native_call(m, m->esi);	/* 408cdd: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408cdf: push 0x42200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ce4: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ce9: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408cf0u; native_call(m, m->edi);	/* 408cee: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408cf0: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 408cf6: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408cfc: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408d01: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408d02: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x408d07u; native_call(m, m->esi);	/* 408d05: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d07: push 0x42200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d0c: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d11: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x408d18u; native_call(m, m->edi);	/* 408d16: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d18: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d1d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408d21u; native_call(m, m->esi);	/* 408d1f: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 408d21: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 408d27: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408d2d: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408d2e: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 408d34: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d37: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d3c: push 0x41ef3333 */
	goto L_408ff5;	/* 408d41: jmp 0x408ff5 */
L_408d46:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408d46: test eax, eax */
	if (!m->zf) goto L_40895e;	/* 408d48: jne 0x40895e */
L_408d4e:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 408d4e: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d52: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408d54: cmp eax, 2 */
	if (m->sf == m->of) goto L_408e24;	/* 408d57: jge 0x408e24 */
	m->esp -= 4; M32(m->esp) = 0x408d5fu; native_call(m, m->ebx);	/* 408d5d: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d5f: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408d64: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408d68u; native_call(m, m->esi);	/* 408d66: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 408d68: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 408d6c: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 408d72: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 408d76: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 408d7c: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 408d80: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 408d84: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 408d88: fmul dword ptr [0x4a9410] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 408d8e: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408d92: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 408d93: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 408d97: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 408d9d: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 408da1: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 408da5: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408da9: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408daa: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x408db1u; native_call(m, m->edi);	/* 408daf: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408db1: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408db6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x408dbdu; native_call(m, m->esi);	/* 408dbb: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 408dbd: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408dc1: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 408dc7: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 408dcb: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 408dcf: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408dd3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408dd4: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408dd5: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x408ddcu; native_call(m, m->edi);	/* 408dda: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ddc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408de1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x408de8u; native_call(m, m->esi);	/* 408de6: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 408de8: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 408dec: fsub dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 408df2: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408df6: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 408df7: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 408dfb: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408dff: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e00: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x408e07u; native_call(m, m->edi);	/* 408e05: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e07: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e0c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408e10u; native_call(m, m->esi);	/* 408e0e: call esi */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 408e10: mov eax, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 408e14: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408e18: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408e19: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e1a: push 0xc1f00000 */
	goto L_408ff5;	/* 408e1f: jmp 0x408ff5 */
L_408e24:
	m->esp -= 4; M32(m->esp) = 0x408e26u; native_call(m, m->ebx);	/* 408e24: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e26: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e2b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x408e32u; native_call(m, m->esi);	/* 408e30: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 408e32: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 408e36: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 408e3c: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 408e40: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 408e46: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 408e4a: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 408e4e: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 408e52: fmul dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 408e58: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408e5c: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 408e5d: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 408e61: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 408e67: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 408e6b: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 408e6f: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408e73: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e74: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x408e7bu; native_call(m, m->edi);	/* 408e79: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e7b: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e80: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408e84u; native_call(m, m->esi);	/* 408e82: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 408e84: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408e88: fadd dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 408e8e: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 408e92: fstp dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 408e96: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408e9a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408e9b: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408e9c: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x408ea3u; native_call(m, m->edi);	/* 408ea1: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ea3: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ea8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x408eacu; native_call(m, m->esi);	/* 408eaa: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 408eac: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 408eb0: fsub dword ptr [0x4a9410] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 408eb6: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408eba: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 408ebb: fstp dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 408ebf: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408ec3: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ec4: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x408ecbu; native_call(m, m->edi);	/* 408ec9: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ecb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ed0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x408ed7u; native_call(m, m->esi);	/* 408ed5: call esi */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 408ed7: mov edx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 408edb: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408edf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408ee0: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 408ee1: push 0x41f00000 */
	goto L_408ff5;	/* 408ee6: jmp 0x408ff5 */
L_408eeb:
	m->esp -= 4; M32(m->esp) = 0x408eedu; native_call(m, m->ebx);	/* 408eeb: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 408eed: fild dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 408ef1: mov eax, dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 408ef5: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 408efb: fst dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 408eff: fadd dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 408f03: fstp dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 408f07: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408f0b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408f0c: push eax */
	m->esp -= 4; M32(m->esp) = 0x408f0fu; native_call(m, m->esi);	/* 408f0d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 408f0f: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 408f13: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 408f19: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 408f1d: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 408f23: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 408f27: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 408f2b: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 408f2f: fmul dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 408f35: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408f39: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 408f3a: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 408f3e: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 408f44: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 408f48: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 408f4c: fild dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 408f50: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408f54: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 408f55: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 408f5b: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 408f61: fstp dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 408f65: mov eax, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408f69: push eax */
	m->esp -= 4; M32(m->esp) = 0x408f6cu; native_call(m, m->edi);	/* 408f6a: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 408f6c: fld dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 408f70: fadd dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 408f74: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408f78: push ecx */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 408f79: fstp dword ptr [esp + 0x54] */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 408f7d: mov edx, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408f81: push edx */
	m->esp -= 4; M32(m->esp) = 0x408f84u; native_call(m, m->esi);	/* 408f82: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 408f84: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 408f88: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 408f8e: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 408f92: mov edx, dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 408f96: fstp dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 408f9a: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408f9e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408f9f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408fa0: push edx */
	m->esp -= 4; M32(m->esp) = 0x408fa3u; native_call(m, m->edi);	/* 408fa1: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 408fa3: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 408fa7: fadd dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x50u));	/* 408fab: mov ecx, dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 408faf: fstp dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 408fb3: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408fb7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408fb8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x408fbbu; native_call(m, m->esi);	/* 408fb9: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 408fbb: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 408fbf: fsub dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 408fc5: mov edx, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 408fc9: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408fcd: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 408fce: fstp dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 408fd2: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408fd6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408fd7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x408fdau; native_call(m, m->edi);	/* 408fd8: call edi */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 408fda: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 408fde: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408fe2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408fe3: push eax */
	m->esp -= 4; M32(m->esp) = 0x408fe6u; native_call(m, m->esi);	/* 408fe4: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 408fe6: mov ecx, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 408fea: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 408fee: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408ff2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 408ff3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408ff4: push eax */
L_408ff5:
	m->esp -= 4; M32(m->esp) = 0x408ff7u; native_call(m, m->edi);	/* 408ff5: call edi */
	m->esp -= 4; M32(m->esp) = 0x408ff9u; native_call(m, m->ebp);	/* 408ff7: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 408ff9: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 408ffd: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 408ffe: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 409001: mov dword ptr [esp + 0x20], eax */
	if (m->sf != m->of) goto L_40883a;	/* 409005: jl 0x40883a */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 40900b: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40900f: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409010: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 409013: mov dword ptr [esp + 0x24], eax */
	if (m->sf != m->of) goto L_408766;	/* 409017: jl 0x408766 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40901d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x409028u; native_call(m, M32(0x4a922cu));	/* 409022: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 409028: mov eax, dword ptr [0x680398] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40902d: test eax, eax */
	if (m->zf) goto L_409093;	/* 40902f: je 0x409093 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 409031: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 409037: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 40903d: fadd dword ptr [0x680ccc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 409043: fst dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 409049: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 40904f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 409051: test ah, 0x41 */
	if (m->zf) goto L_40906c;	/* 409054: je 0x40906c */
	M32((DWORD)(0x680cccu)) = 0x40000000u;	/* 409056: mov dword ptr [0x680ccc], 0x40000000 */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 409060: mov dword ptr [0x4df454], 0x3f800000 */
	goto L_409093;	/* 40906a: jmp 0x409093 */
L_40906c:
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 40906c: fld dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 409072: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 409078: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40907a: test ah, 1 */
	if (!m->zf) goto L_409093;	/* 40907d: jne 0x409093 */
	M32((DWORD)(0x680cccu)) = 0x42180000u;	/* 40907f: mov dword ptr [0x680ccc], 0x42180000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 409089: mov dword ptr [0x4df454], 0xbf800000 */
L_409093:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 409093: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 409099: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 40909f: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 4090a5: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4090ab: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4090b1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4090b3: test ah, 0x41 */
	if (m->zf) goto L_4090ce;	/* 4090b6: je 0x4090ce */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 4090b8: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 4090c2: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_4090f5;	/* 4090cc: jmp 0x4090f5 */
L_4090ce:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 4090ce: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 4090d4: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4090da: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4090dc: test ah, 1 */
	if (!m->zf) goto L_4090f5;	/* 4090df: jne 0x4090f5 */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 4090e1: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 4090eb: mov dword ptr [0x4df010], 0xbf800000 */
L_4090f5:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 4090f5: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 4090fb: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 409101: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 409107: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 40910d: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 409113: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 409115: test ah, 1 */
	if (!m->zf) goto L_409124;	/* 409118: jne 0x409124 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 40911a: mov dword ptr [0x4e14fc], 0 */
L_409124:
	m->esi = M32((DWORD)(m->esp + 0x3cu));	/* 409124: mov esi, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->esi, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409128: cmp esi, -1 */
	if (m->zf) goto L_40918b;	/* 40912b: je 0x40918b */
	{ DWORD a_ = M32((DWORD)(0x4dbb3cu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40912d: cmp dword ptr [0x4dbb3c], 2 */
	if (!m->zf) goto L_40918b;	/* 409134: jne 0x40918b */
	m->eax = M32((DWORD)(0x680370u));	/* 409136: mov eax, dword ptr [0x680370] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40913b: test eax, eax */
	if (!m->zf) goto L_40918b;	/* 40913d: jne 0x40918b */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40913f: push 2 */
	m->esp -= 4; M32(m->esp) = 0x409146u; native_call(m, 0x41ef90u);	/* 409141: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409146: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40914fu; native_call(m, M32(0x4a9218u));	/* 409149: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40914f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409154: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409159: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40915e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 409163: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40916du; native_call(m, 0x41f0e0u);	/* 409168: call 0x41f0e0 */
	{ DWORD a_ = m->esi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 40916d: shl esi, 7 */
	{ DWORD a_ = m->esi, b_ = 0x750924u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 409170: add esi, 0x750924 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 409176: push esi */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 409177: push 0x280 */
	{ DWORD v_ = 0x1bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 40917c: push 0x1bc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409181: push 0 */
	m->esp -= 4; M32(m->esp) = 0x409188u; native_call(m, 0x4029d0u);	/* 409183: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409188: add esp, 0x24 */
L_40918b:
	m->edi = M32(m->esp); m->esp += 4;	/* 40918b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40918c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40918d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40918e: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40918f: add esp, 0x4c */
	m->esp += 4 + 0; return;	/* 409192: ret  */
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
