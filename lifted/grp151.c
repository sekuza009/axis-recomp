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

static void lift_468750(X86 *m);

/* game_processLoadingMode (0x468750), lifted by tools/lift.py */
static void lift_468750(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x24cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468750: sub esp, 0x24c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 468756: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 468757: push ebp */
	m->ebp = m->ecx;	/* 468758: mov ebp, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46875a: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46875c: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46875d: push edi */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233cc28u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46875e: cmp dword ptr [ebp + 0x233cc28], ebx */
	if (!m->zf) goto L_4687b0;	/* 468764: jne 0x4687b0 */
	M32((DWORD)(0xa0ea8cu)) = m->ebp;	/* 468766: mov dword ptr [0xa0ea8c], ebp */
	M8((DWORD)(0xa0e988u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 46876c: mov byte ptr [0xa0e988], bl */
	m->edi = 0x4c52b0u;	/* 468772: mov edi, 0x4c52b0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 468777: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46877a: xor eax, eax */
	M32((DWORD)(m->ebp + 0x2340c60u)) = 0x1u;	/* 46877c: mov dword ptr [ebp + 0x2340c60], 1 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 468786: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 468788: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46878a: sub edi, ecx */
	m->edx = (DWORD)(m->ebp + 0x233cc60u);	/* 46878c: lea edx, [ebp + 0x233cc60] */
	m->eax = m->ecx;	/* 468792: mov eax, ecx */
	m->esi = m->edi;	/* 468794: mov esi, edi */
	m->edi = m->edx;	/* 468796: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 468798: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46879b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 46879d: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46879f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4687a2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M32((DWORD)(m->ebp + 0x233cc24u)) = m->ebx;	/* 4687a4: mov dword ptr [ebp + 0x233cc24], ebx */
	M32((DWORD)(m->ebp + 0x233cc2cu)) = m->ebx;	/* 4687aa: mov dword ptr [ebp + 0x233cc2c], ebx */
L_4687b0:
	{ DWORD v_ = 0x1bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4687b0: push 0x1b */
	m->esp -= 4; M32(m->esp) = 0x4687b7u; native_call(m, 0x487bd0u);	/* 4687b2: call 0x487bd0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4687b7: add esp, 4 */
	m->ebx = 0x8u;	/* 4687ba: mov ebx, 8 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 4687bf: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4687c1: sbb eax, eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 4687c3: neg eax */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4687c5: mov dword ptr [esp + 0x10], eax */
	m->eax = M32((DWORD)(m->ebp + 0x233cc24u));	/* 4687c9: mov eax, dword ptr [ebp + 0x233cc24] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4687cf: cmp eax, ebx */
	if (!m->cf && !m->zf) goto L_4689e4;	/* 4687d1: ja 0x4689e4 */
	switch (m->eax) { case 0: goto L_4687de; case 1: goto L_468ad9; case 2: goto L_468bac; case 3: goto L_468d30; case 4: goto L_468e22; case 5: goto L_468ede; case 6: goto L_468f92; case 7: goto L_46906d; case 8: goto L_46918b; default: abort(); }	/* 4687d7: jmp dword ptr [eax*4 + 0x4692a0] */
L_4687de:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4687de: cmp dword ptr [ebp + 8], 1 */
	if (!m->zf) goto L_468806;	/* 4687e2: jne 0x468806 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 4687e4: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4687ea: test eax, eax */
	if (!m->zf) goto L_468806;	/* 4687ec: jne 0x468806 */
	m->esp -= 4; M32(m->esp) = 0x4687f3u; native_call(m, 0x4a86d0u);	/* 4687ee: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4687f3: cmp eax, 1 */
	if (!m->zf) goto L_468806;	/* 4687f6: jne 0x468806 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 4687f8: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4687fe: push ecx */
	m->ecx = m->ebp;	/* 4687ff: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x468806u; native_call(m, 0x48dbf0u);	/* 468801: call 0x48dbf0 */
L_468806:
	m->esp -= 4; M32(m->esp) = 0x46880bu; native_call(m, 0x457310u);	/* 468806: call 0x457310 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46880b: cmp dword ptr [ebp + 8], 3 */
	if (!m->zf) goto L_468959;	/* 46880f: jne 0x468959 */
	m->edx = M32((DWORD)(m->ebp + 0x1f35c0u));	/* 468815: mov edx, dword ptr [ebp + 0x1f35c0] */
	m->ecx = (DWORD)(m->esp + 0x15cu);	/* 46881b: lea ecx, [esp + 0x15c] */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 468822: shl edx, 6 */
	m->eax = (DWORD)(m->edx + m->ebp*1 + 0x1f1cbcu);	/* 468825: lea eax, [edx + ebp + 0x1f1cbc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46882c: push eax */
	{ DWORD v_ = 0x4c52a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46882d: push 0x4c52a4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468832: push ecx */
	m->esp -= 4; M32(m->esp) = 0x468838u; native_call(m, 0x49e9ddu);	/* 468833: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x168u);	/* 468838: lea edx, [esp + 0x168] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 46883f: push 0x4ad170 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468844: push edx */
	m->esp -= 4; M32(m->esp) = 0x46884au; native_call(m, 0x49e9cau);	/* 468845: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46884a: add esp, 0x14 */
	M32((DWORD)(m->ebp + 0x2340d08u)) = m->eax;	/* 46884d: mov dword ptr [ebp + 0x2340d08], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468853: test eax, eax */
	if (!m->zf) goto L_468871;	/* 468855: jne 0x468871 */
	m->eax = (DWORD)(m->esp + 0x15cu);	/* 468857: lea eax, [esp + 0x15c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46885e: push eax */
	{ DWORD v_ = 0x4c5278u; m->esp -= 4; M32(m->esp) = v_; }	/* 46885f: push 0x4c5278 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 468864: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x46886eu; native_call(m, 0x46c710u);	/* 468869: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46886e: add esp, 0xc */
L_468871:
	m->ecx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 468871: mov ecx, dword ptr [ebp + 0x2340d08] */
	m->esi = (DWORD)(m->ebp + 0x1f35c4u);	/* 468877: lea esi, [ebp + 0x1f35c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46887d: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46887e: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 468880: push 4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 468882: push esi */
	m->esp -= 4; M32(m->esp) = 0x468888u; native_call(m, 0x46cbe0u);	/* 468883: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 468888: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46888a: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1201u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46888d: cmp eax, 0x1201 */
	if (m->zf) goto L_4688ae;	/* 468892: je 0x4688ae */
	m->edx = (DWORD)(m->esp + 0x15cu);	/* 468894: lea edx, [esp + 0x15c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46889b: push edx */
	{ DWORD v_ = 0x4c5234u; m->esp -= 4; M32(m->esp) = v_; }	/* 46889c: push 0x4c5234 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688a1: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x4688abu; native_call(m, 0x46c710u);	/* 4688a6: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4688ab: add esp, 0xc */
L_4688ae:
	m->eax = M32((DWORD)(m->ebp + 0x2340d08u));	/* 4688ae: mov eax, dword ptr [ebp + 0x2340d08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4688b4: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688b5: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688b7: push 4 */
	{ DWORD v_ = 0x5ae9c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688b9: push 0x5ae9c4 */
	m->esp -= 4; M32(m->esp) = 0x4688c3u; native_call(m, 0x46cbe0u);	/* 4688be: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 4688c3: mov ecx, dword ptr [ebp + 0x2340d08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4688c9: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688ca: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688cc: push 4 */
	{ DWORD v_ = 0x9dad94u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688ce: push 0x9dad94 */
	m->esp -= 4; M32(m->esp) = 0x4688d8u; native_call(m, 0x46cbe0u);	/* 4688d3: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 4688d8: mov edx, dword ptr [ebp + 0x2340d08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4688de: push edx */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688df: push 0x20 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688e1: push 1 */
	{ DWORD v_ = 0x67fb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688e3: push 0x67fb44 */
	m->esp -= 4; M32(m->esp) = 0x4688edu; native_call(m, 0x46cbe0u);	/* 4688e8: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d08u));	/* 4688ed: mov eax, dword ptr [ebp + 0x2340d08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4688f3: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688f4: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688f6: push 4 */
	{ DWORD v_ = 0x9da3e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4688f8: push 0x9da3e0 */
	m->esp -= 4; M32(m->esp) = 0x468902u; native_call(m, 0x46cbe0u);	/* 4688fd: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 468902: mov ecx, dword ptr [ebp + 0x2340d08] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468908: add esp, 0x40 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46890b: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46890c: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46890e: push 4 */
	{ DWORD v_ = 0x76d368u; m->esp -= 4; M32(m->esp) = v_; }	/* 468910: push 0x76d368 */
	m->esp -= 4; M32(m->esp) = 0x46891au; native_call(m, 0x46cbe0u);	/* 468915: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 46891a: mov edx, dword ptr [ebp + 0x2340d08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468920: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 468921: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 468923: push 4 */
	{ DWORD v_ = 0x4df8e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 468925: push 0x4df8e8 */
	m->esp -= 4; M32(m->esp) = 0x46892fu; native_call(m, 0x46cbe0u);	/* 46892a: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d08u));	/* 46892f: mov eax, dword ptr [ebp + 0x2340d08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468935: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 468936: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 468938: push 4 */
	{ DWORD v_ = 0x76d408u; m->esp -= 4; M32(m->esp) = v_; }	/* 46893a: push 0x76d408 */
	m->esp -= 4; M32(m->esp) = 0x468944u; native_call(m, 0x46cbe0u);	/* 46893f: call 0x46cbe0 */
	m->ecx = M32((DWORD)(0x76d368u));	/* 468944: mov ecx, dword ptr [0x76d368] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46894a: add esp, 0x30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46894d: push ecx */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 46894e: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x468959u; native_call(m, 0x4732f0u);	/* 468954: call 0x4732f0 */
L_468959:
	{ DWORD v_ = 0x4c521cu; m->esp -= 4; M32(m->esp) = v_; }	/* 468959: push 0x4c521c */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 46895e: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468964: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 468966: push -1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 468968: push esi */
	M32((DWORD)(0xae2ec8u)) = 0x469730u;	/* 468969: mov dword ptr [0xae2ec8], 0x469730 */
	m->esp -= 4; M32(m->esp) = 0x468978u; native_call(m, 0x470fc0u);	/* 468973: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468978: add esp, 0x10 */
	m->ecx = m->esi;	/* 46897b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x468982u; native_call(m, 0x470ad0u);	/* 46897d: call 0x470ad0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 468982: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468985: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_469165;	/* 468988: ja 0x469165 */
	switch (m->eax) { case 0: goto L_468b46; case 1: goto L_468b7f; case 2: goto L_468b7f; case 3: goto L_468995; default: abort(); }	/* 46898e: jmp dword ptr [eax*4 + 0x4692c4] */
L_468995:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468995: mov eax, dword ptr [ebp + 0x2340c60] */
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x1u;	/* 46899b: mov dword ptr [ebp + 0x233cc24], 1 */
	m->ecx = m->eax;	/* 4689a5: mov ecx, eax */
	m->edi = 0x4c520cu;	/* 4689a7: mov edi, 0x4c520c */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4689ac: shl ecx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4689af: inc eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x233cc60u);	/* 4689b0: lea edx, [ecx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 4689b7: mov dword ptr [ebp + 0x2340c60], eax */
L_4689bd:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4689bd: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4689c0: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4689c2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4689c4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4689c6: sub edi, ecx */
	m->eax = m->ecx;	/* 4689c8: mov eax, ecx */
	m->esi = m->edi;	/* 4689ca: mov esi, edi */
	m->edi = m->edx;	/* 4689cc: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4689ce: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4689d1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4689d3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4689d5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4689d8: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_4689da:
	M32((DWORD)(m->ebp + 0x233cc2cu)) = 0x0u;	/* 4689da: mov dword ptr [ebp + 0x233cc2c], 0 */
L_4689e4:
	m->ebx = M32((DWORD)(m->ebp + 0x233cc28u));	/* 4689e4: mov ebx, dword ptr [ebp + 0x233cc28] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4689ea: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4689ef: push 0 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4689f1: inc ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4689f2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4689f4: push 0 */
	M32((DWORD)(m->ebp + 0x233cc28u)) = m->ebx;	/* 4689f6: mov dword ptr [ebp + 0x233cc28], ebx */
	m->esp -= 4; M32(m->esp) = 0x468a02u; native_call(m, M32(0x4a91e0u));	/* 4689fc: call dword ptr [0x4a91e0] */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a02: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a07: push 0 */
	m->esp -= 4; M32(m->esp) = 0x468a0fu; native_call(m, M32(0x4a91dcu));	/* 468a09: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x4100u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a0f: push 0x4100 */
	m->esp -= 4; M32(m->esp) = 0x468a1au; native_call(m, M32(0x4a91e8u));	/* 468a14: call dword ptr [0x4a91e8] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a1a: push 0x3f800000 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a1f: push 1 */
	m->esp -= 4; M32(m->esp) = 0x468a26u; native_call(m, 0x4685f0u);	/* 468a21: call 0x4685f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468a26: add esp, 8 */
	m->edx = (DWORD)(m->ebp + 0x22e7068u);	/* 468a29: lea edx, [ebp + 0x22e7068] */
	m->esi = (DWORD)(m->ebp + 0x74u);	/* 468a2f: lea esi, [ebp + 0x74] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468a32: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a33: push 0 */
	m->ecx = m->esi;	/* 468a35: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x468a3cu; native_call(m, 0x4841f0u);	/* 468a37: call 0x4841f0 */
	m->ecx = m->esi;	/* 468a3c: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x468a43u; native_call(m, 0x484260u);	/* 468a3e: call 0x484260 */
	m->eax = M32((DWORD)(m->ebp + 0x1f1664u));	/* 468a43: mov eax, dword ptr [ebp + 0x1f1664] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a49: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468a4b: push eax */
	m->ecx = m->esi;	/* 468a4c: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x468a53u; native_call(m, 0x485af0u);	/* 468a4e: call 0x485af0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a53: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a58: push 0 */
	m->esp -= 4; M32(m->esp) = 0x468a5fu; native_call(m, 0x4685f0u);	/* 468a5a: call 0x4685f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468a5f: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a62: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a67: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a6c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a71: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x468a7cu; native_call(m, M32(0x4a9228u));	/* 468a76: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468a7c: mov eax, dword ptr [ebp + 0x2340c60] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 468a82: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468a84: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_468ac1;	/* 468a86: jle 0x468ac1 */
	m->edi = 0x8u;	/* 468a88: mov edi, 8 */
	m->ebx = (DWORD)(m->ebp + 0x233cc60u);	/* 468a8d: lea ebx, [ebp + 0x233cc60] */
L_468a93:
	{ DWORD a_ = m->ebx, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 468a93: add ebx, 0x100 */
	m->eax = m->edi;	/* 468a99: mov eax, edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 468a9b: push ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a9c: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468a9e: push eax */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 468a9f: push 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 468aa1: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 468aa2: add edi, 8 */
	m->esp -= 4; M32(m->esp) = 0x468aaau; native_call(m, 0x46bb00u);	/* 468aa5: call 0x46bb00 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468aaa: mov eax, dword ptr [ebp + 0x2340c60] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468ab0: add esp, 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 468ab3: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 468ab4: add edi, 8 */
	{ DWORD a_ = m->ebx, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 468ab7: add ebx, 0x100 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468abd: cmp esi, eax */
	if (m->sf != m->of) goto L_468a93;	/* 468abf: jl 0x468a93 */
L_468ac1:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x10u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468ac1: cmp dword ptr [esp + 0x10], 1 */
	if (!m->zf) goto L_46928d;	/* 468ac6: jne 0x46928d */
	m->edi = M32(m->esp); m->esp += 4;	/* 468acc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 468acd: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 468ace: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 468acf: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 468ad1: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468ad2: add esp, 0x24c */
	m->esp += 4 + 0; return;	/* 468ad8: ret  */
L_468ad9:
	{ DWORD v_ = 0x4c51f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 468ad9: push 0x4c51f4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468ade: push 0 */
	m->eax = (DWORD)(m->ebp + 0x1f36c8u);	/* 468ae0: lea eax, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 468ae6: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468ae8: push eax */
	m->esp -= 4; M32(m->esp) = 0x468aeeu; native_call(m, 0x470fc0u);	/* 468ae9: call 0x470fc0 */
	m->ecx = M32((DWORD)(0x9dad94u));	/* 468aee: mov ecx, dword ptr [0x9dad94] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468af4: add esp, 0x10 */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 468af7: shl ecx, 5 */
	M32((DWORD)(0xa0ea94u)) = 0x0u;	/* 468afa: mov dword ptr [0xa0ea94], 0 */
	m->eax = (DWORD)(m->ecx + 0x907b30u);	/* 468b04: lea eax, [ecx + 0x907b30] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x907b30u))) & 0xff) << 0);	/* 468b0a: mov cl, byte ptr [ecx + 0x907b30] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 468b10: test cl, cl */
	if (!m->zf) goto L_468b2b;	/* 468b12: jne 0x468b2b */
	m->edi = M32(m->esp); m->esp += 4;	/* 468b14: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 468b15: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 468b16: pop ebp */
	M32((DWORD)(0xa0ea94u)) = 0x1u;	/* 468b17: mov dword ptr [0xa0ea94], 1 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 468b21: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 468b23: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468b24: add esp, 0x24c */
	m->esp += 4 + 0; return;	/* 468b2a: ret  */
L_468b2b:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468b2b: push eax */
	m->ecx = m->ebp;	/* 468b2c: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x468b33u; native_call(m, 0x461ec0u);	/* 468b2e: call 0x461ec0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 468b33: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468b36: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_469165;	/* 468b39: ja 0x469165 */
	switch (m->eax) { case 0: goto L_468b46; case 1: goto L_468b7f; case 2: goto L_468b73; case 3: goto L_468b7f; default: abort(); }	/* 468b3f: jmp dword ptr [eax*4 + 0x4692d4] */
L_468b46:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468b46: mov eax, dword ptr [ebp + 0x2340c60] */
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x2u;	/* 468b4c: mov dword ptr [ebp + 0x233cc24], 2 */
	m->edx = m->eax;	/* 468b56: mov edx, eax */
	m->edi = 0x4c51e4u;	/* 468b58: mov edi, 0x4c51e4 */
	{ DWORD a_ = m->edx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 468b5d: shl edx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 468b60: inc eax */
	m->edx = (DWORD)(m->edx + m->ebp*1 + 0x233cc60u);	/* 468b61: lea edx, [edx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 468b68: mov dword ptr [ebp + 0x2340c60], eax */
	goto L_4689bd;	/* 468b6e: jmp 0x4689bd */
L_468b73:
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x6u;	/* 468b73: mov dword ptr [ebp + 0x233cc24], 6 */
	goto L_468b89;	/* 468b7d: jmp 0x468b89 */
L_468b7f:
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x2u;	/* 468b7f: mov dword ptr [ebp + 0x233cc24], 2 */
L_468b89:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468b89: mov eax, dword ptr [ebp + 0x2340c60] */
	m->edi = 0x4c51e4u;	/* 468b8f: mov edi, 0x4c51e4 */
	m->ecx = m->eax;	/* 468b94: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 468b96: shl ecx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 468b99: inc eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x233cc60u);	/* 468b9a: lea edx, [ecx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 468ba1: mov dword ptr [ebp + 0x2340c60], eax */
	goto L_4689bd;	/* 468ba7: jmp 0x4689bd */
L_468bac:
	{ DWORD v_ = 0x4c51c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468bac: push 0x4c51c0 */
	m->esi = 0x1u;	/* 468bb1: mov esi, 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468bb6: push 0 */
	m->eax = (DWORD)(m->ebp + 0x1f36c8u);	/* 468bb8: lea eax, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 468bbe: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468bbf: push eax */
	m->esp -= 4; M32(m->esp) = 0x468bc5u; native_call(m, 0x470fc0u);	/* 468bc0: call 0x470fc0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 468bc5: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468bc8: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468bcb: cmp eax, esi */
	if (!m->zf) goto L_468bf0;	/* 468bcd: jne 0x468bf0 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 468bcf: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468bd5: test eax, eax */
	if (!m->zf) goto L_468bf0;	/* 468bd7: jne 0x468bf0 */
	m->esp -= 4; M32(m->esp) = 0x468bdeu; native_call(m, 0x4a86d0u);	/* 468bd9: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468bde: cmp eax, esi */
	if (!m->zf) goto L_468bf0;	/* 468be0: jne 0x468bf0 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 468be2: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468be8: push ecx */
	m->ecx = m->ebp;	/* 468be9: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x468bf0u; native_call(m, 0x48dbf0u);	/* 468beb: call 0x48dbf0 */
L_468bf0:
	m->eax = M32((DWORD)(m->ebp + 0x1f1cb0u));	/* 468bf0: mov eax, dword ptr [ebp + 0x1f1cb0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468bf6: test eax, eax */
	if (!m->zf) goto L_468c64;	/* 468bf8: jne 0x468c64 */
	m->edx = M32((DWORD)(0x9dad94u));	/* 468bfa: mov edx, dword ptr [0x9dad94] */
	m->ecx = m->ebp;	/* 468c00: mov ecx, ebp */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 468c02: shl edx, 5 */
	{ DWORD a_ = m->edx, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 468c05: add edx, 0x907b30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468c0b: push edx */
	m->esp -= 4; M32(m->esp) = 0x468c11u; native_call(m, 0x461ec0u);	/* 468c0c: call 0x461ec0 */
	m->ecx = M32((DWORD)(m->ebp + 0x8u));	/* 468c11: mov ecx, dword ptr [ebp + 8] */
	m->eax = m->ecx;	/* 468c14: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 468c16: sub eax, 0 */
	if (m->zf) goto L_468c37;	/* 468c19: je 0x468c37 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 468c1b: dec eax */
	if (m->zf) goto L_468c37;	/* 468c1c: je 0x468c37 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 468c1e: sub eax, 2 */
	if (m->zf) goto L_468c37;	/* 468c21: je 0x468c37 */
	m->eax = M32((DWORD)(m->ebp + 0x233cc24u));	/* 468c23: mov eax, dword ptr [ebp + 0x233cc24] */
	m->edx = M32((DWORD)(m->ebp + 0x233cc20u));	/* 468c29: mov edx, dword ptr [ebp + 0x233cc20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468c2f: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468c30: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468c31: push ecx */
	goto L_469174;	/* 468c32: jmp 0x469174 */
L_468c37:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468c37: mov eax, dword ptr [ebp + 0x2340c60] */
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x3u;	/* 468c3d: mov dword ptr [ebp + 0x233cc24], 3 */
	m->ecx = m->eax;	/* 468c47: mov ecx, eax */
	m->edi = 0x4c51b0u;	/* 468c49: mov edi, 0x4c51b0 */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 468c4e: shl ecx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 468c51: inc eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x233cc60u);	/* 468c52: lea edx, [ecx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 468c59: mov dword ptr [ebp + 0x2340c60], eax */
	goto L_4689bd;	/* 468c5f: jmp 0x4689bd */
L_468c64:
	m->esp -= 4; M32(m->esp) = 0x468c69u; native_call(m, 0x4a8350u);	/* 468c64: call 0x4a8350 */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 468c69: lea ecx, [esp + 0x1c] */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 468c6d: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468c71: push ecx */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 468c72: lea eax, [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468c76: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468c77: push eax */
	m->esp -= 4; M32(m->esp) = 0x468c7du; native_call(m, 0x4a8450u);	/* 468c78: call 0x4a8450 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468c7d: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468c80: test eax, eax */
	if (m->zf) goto L_468cc4;	/* 468c82: je 0x468cc4 */
L_468c84:
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468c84: cmp eax, esi */
	if (!m->zf) goto L_468c9e;	/* 468c86: jne 0x468c9e */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 468c88: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 468c8c: mov eax, dword ptr [esp + 0x14] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 468c90: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468c94: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468c95: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468c96: push eax */
	m->ecx = m->ebp;	/* 468c97: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x468c9eu; native_call(m, 0x48c830u);	/* 468c99: call 0x48c830 */
L_468c9e:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340c7cu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebp + 0x2340c7cu)) = r_; }	/* 468c9e: inc dword ptr [ebp + 0x2340c7c] */
	m->esp -= 4; M32(m->esp) = 0x468ca9u; native_call(m, 0x4a8350u);	/* 468ca4: call 0x4a8350 */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 468ca9: lea ecx, [esp + 0x1c] */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 468cad: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468cb1: push ecx */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 468cb2: lea eax, [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468cb6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468cb7: push eax */
	m->esp -= 4; M32(m->esp) = 0x468cbdu; native_call(m, 0x4a8450u);	/* 468cb8: call 0x4a8450 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468cbd: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468cc0: test eax, eax */
	if (!m->zf) goto L_468c84;	/* 468cc2: jne 0x468c84 */
L_468cc4:
	m->esp -= 4; M32(m->esp) = 0x468cc9u; native_call(m, 0x4a86d0u);	/* 468cc4: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468cc9: test eax, eax */
	if (!m->zf) goto L_468ced;	/* 468ccb: jne 0x468ced */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 468ccd: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x2342395u));	/* 468cd0: fadd dword ptr [ebp + 0x2342395] */
	MF((DWORD)(m->ebp + 0x2342395u)) = (float)ST(0);	/* 468cd6: fst dword ptr [ebp + 0x2342395] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 468cdc: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 468ce2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 468ce4: test ah, 0x41 */
	if (!m->zf) goto L_468ced;	/* 468ce7: jne 0x468ced */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 468ce9: mov dword ptr [esp + 0x10], esi */
L_468ced:
	m->esp -= 4; M32(m->esp) = 0x468cf2u; native_call(m, 0x4a8730u);	/* 468ced: call 0x4a8730 */
	{ DWORD a_ = m->eax, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468cf2: cmp eax, 0x80 */
	if (m->sf != m->of) goto L_468cfd;	/* 468cf7: jl 0x468cfd */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 468cf9: mov dword ptr [esp + 0x10], esi */
L_468cfd:
	m->ecx = M32((DWORD)(0x4defc8u));	/* 468cfd: mov ecx, dword ptr [0x4defc8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468d03: push ecx */
	m->esp -= 4; M32(m->esp) = 0x468d09u; native_call(m, 0x401600u);	/* 468d04: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468d09: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468d0c: test eax, eax */
	if (!m->zf) goto L_468d27;	/* 468d0e: jne 0x468d27 */
	m->edx = M32((DWORD)(0x4defccu));	/* 468d10: mov edx, dword ptr [0x4defcc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468d16: push edx */
	m->esp -= 4; M32(m->esp) = 0x468d1cu; native_call(m, 0x401600u);	/* 468d17: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468d1c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468d1f: test eax, eax */
	if (m->zf) goto L_4689e4;	/* 468d21: je 0x4689e4 */
L_468d27:
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 468d27: mov dword ptr [esp + 0x10], esi */
	goto L_4689e4;	/* 468d2b: jmp 0x4689e4 */
L_468d30:
	{ DWORD v_ = 0x4c5198u; m->esp -= 4; M32(m->esp) = v_; }	/* 468d30: push 0x4c5198 */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 468d35: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468d3b: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 468d3d: push 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 468d3f: push esi */
	m->esp -= 4; M32(m->esp) = 0x468d45u; native_call(m, 0x470fc0u);	/* 468d40: call 0x470fc0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 468d45: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468d48: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468d4b: cmp eax, 1 */
	if (!m->zf) goto L_468d72;	/* 468d4e: jne 0x468d72 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 468d50: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468d56: test eax, eax */
	if (!m->zf) goto L_468d72;	/* 468d58: jne 0x468d72 */
	m->esp -= 4; M32(m->esp) = 0x468d5fu; native_call(m, 0x4a86d0u);	/* 468d5a: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468d5f: cmp eax, 1 */
	if (!m->zf) goto L_468d72;	/* 468d62: jne 0x468d72 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 468d64: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->ebp;	/* 468d6a: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468d6c: push eax */
	m->esp -= 4; M32(m->esp) = 0x468d72u; native_call(m, 0x48dbf0u);	/* 468d6d: call 0x48dbf0 */
L_468d72:
	m->ecx = (DWORD)(m->ebp + 0x1f35c8u);	/* 468d72: lea ecx, [ebp + 0x1f35c8] */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 468d78: lea edx, [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468d7c: push ecx */
	{ DWORD v_ = 0x4c5190u; m->esp -= 4; M32(m->esp) = v_; }	/* 468d7d: push 0x4c5190 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468d82: push edx */
	m->esp -= 4; M32(m->esp) = 0x468d88u; native_call(m, 0x49e9ddu);	/* 468d83: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468d88: add esp, 0xc */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 468d8b: lea eax, [esp + 0x5c] */
	m->ecx = m->esi;	/* 468d8f: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468d91: push eax */
	m->esp -= 4; M32(m->esp) = 0x468d97u; native_call(m, 0x48b9d0u);	/* 468d92: call 0x48b9d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468d97: test eax, eax */
	if (!m->zf) goto L_468dad;	/* 468d99: jne 0x468dad */
	{ DWORD v_ = 0x4c4598u; m->esp -= 4; M32(m->esp) = v_; }	/* 468d9b: push 0x4c4598 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 468da0: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x468daau; native_call(m, 0x46c710u);	/* 468da5: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468daa: add esp, 8 */
L_468dad:
	m->ecx = M32((DWORD)(0x9dad94u));	/* 468dad: mov ecx, dword ptr [0x9dad94] */
	m->eax = M32((DWORD)(m->ebp + 0xbe3000u));	/* 468db3: mov eax, dword ptr [ebp + 0xbe3000] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468db9: cmp ecx, eax */
	if (m->zf) goto L_468dcf;	/* 468dbb: je 0x468dcf */
	{ DWORD v_ = 0x4c4598u; m->esp -= 4; M32(m->esp) = v_; }	/* 468dbd: push 0x4c4598 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 468dc2: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x468dccu; native_call(m, 0x46c710u);	/* 468dc7: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468dcc: add esp, 8 */
L_468dcf:
	m->ecx = M32((DWORD)(m->ebp + 0x8u));	/* 468dcf: mov ecx, dword ptr [ebp + 8] */
	m->eax = m->ecx;	/* 468dd2: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 468dd4: sub eax, 0 */
	if (m->zf) goto L_468df5;	/* 468dd7: je 0x468df5 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 468dd9: dec eax */
	if (m->zf) goto L_468df5;	/* 468dda: je 0x468df5 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 468ddc: sub eax, 2 */
	if (m->zf) goto L_468df5;	/* 468ddf: je 0x468df5 */
	m->edx = M32((DWORD)(m->ebp + 0x233cc24u));	/* 468de1: mov edx, dword ptr [ebp + 0x233cc24] */
	m->eax = M32((DWORD)(m->ebp + 0x233cc20u));	/* 468de7: mov eax, dword ptr [ebp + 0x233cc20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468ded: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468dee: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468def: push ecx */
	goto L_469174;	/* 468df0: jmp 0x469174 */
L_468df5:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468df5: mov eax, dword ptr [ebp + 0x2340c60] */
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x4u;	/* 468dfb: mov dword ptr [ebp + 0x233cc24], 4 */
	m->ecx = m->eax;	/* 468e05: mov ecx, eax */
	m->edi = 0x4c5180u;	/* 468e07: mov edi, 0x4c5180 */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 468e0c: shl ecx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 468e0f: inc eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x233cc60u);	/* 468e10: lea edx, [ecx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 468e17: mov dword ptr [ebp + 0x2340c60], eax */
	goto L_4689bd;	/* 468e1d: jmp 0x4689bd */
L_468e22:
	{ DWORD v_ = 0x4c5164u; m->esp -= 4; M32(m->esp) = v_; }	/* 468e22: push 0x4c5164 */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 468e27: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468e2d: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 468e2f: push 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 468e31: push esi */
	m->esp -= 4; M32(m->esp) = 0x468e37u; native_call(m, 0x470fc0u);	/* 468e32: call 0x470fc0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 468e37: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468e3a: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468e3d: cmp eax, 1 */
	if (!m->zf) goto L_468e64;	/* 468e40: jne 0x468e64 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 468e42: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468e48: test eax, eax */
	if (!m->zf) goto L_468e64;	/* 468e4a: jne 0x468e64 */
	m->esp -= 4; M32(m->esp) = 0x468e51u; native_call(m, 0x4a86d0u);	/* 468e4c: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468e51: cmp eax, 1 */
	if (!m->zf) goto L_468e64;	/* 468e54: jne 0x468e64 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 468e56: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468e5c: push ecx */
	m->ecx = m->ebp;	/* 468e5d: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x468e64u; native_call(m, 0x48dbf0u);	/* 468e5f: call 0x48dbf0 */
L_468e64:
	m->edx = (DWORD)(m->ebp + 0x1f35c8u);	/* 468e64: lea edx, [ebp + 0x1f35c8] */
	m->eax = (DWORD)(m->esp + 0x5cu);	/* 468e6a: lea eax, [esp + 0x5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468e6e: push edx */
	{ DWORD v_ = 0x4c5190u; m->esp -= 4; M32(m->esp) = v_; }	/* 468e6f: push 0x4c5190 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468e74: push eax */
	m->esp -= 4; M32(m->esp) = 0x468e7au; native_call(m, 0x49e9ddu);	/* 468e75: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468e7a: add esp, 0xc */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 468e7d: lea ecx, [esp + 0x5c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468e81: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468e83: push ecx */
	m->ecx = m->esi;	/* 468e84: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x468e8bu; native_call(m, 0x48b710u);	/* 468e86: call 0x48b710 */
	m->ecx = M32((DWORD)(m->ebp + 0x8u));	/* 468e8b: mov ecx, dword ptr [ebp + 8] */
	m->eax = m->ecx;	/* 468e8e: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 468e90: sub eax, 0 */
	if (m->zf) goto L_468eb1;	/* 468e93: je 0x468eb1 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 468e95: dec eax */
	if (m->zf) goto L_468eb1;	/* 468e96: je 0x468eb1 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 468e98: sub eax, 2 */
	if (m->zf) goto L_468eb1;	/* 468e9b: je 0x468eb1 */
	m->edx = M32((DWORD)(m->ebp + 0x233cc24u));	/* 468e9d: mov edx, dword ptr [ebp + 0x233cc24] */
	m->eax = M32((DWORD)(m->ebp + 0x233cc20u));	/* 468ea3: mov eax, dword ptr [ebp + 0x233cc20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468ea9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468eaa: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468eab: push ecx */
	goto L_469174;	/* 468eac: jmp 0x469174 */
L_468eb1:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468eb1: mov eax, dword ptr [ebp + 0x2340c60] */
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x5u;	/* 468eb7: mov dword ptr [ebp + 0x233cc24], 5 */
	m->ecx = m->eax;	/* 468ec1: mov ecx, eax */
	m->edi = 0x4c514cu;	/* 468ec3: mov edi, 0x4c514c */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 468ec8: shl ecx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 468ecb: inc eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x233cc60u);	/* 468ecc: lea edx, [ecx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 468ed3: mov dword ptr [ebp + 0x2340c60], eax */
	goto L_4689bd;	/* 468ed9: jmp 0x4689bd */
L_468ede:
	{ DWORD v_ = 0x4c512cu; m->esp -= 4; M32(m->esp) = v_; }	/* 468ede: push 0x4c512c */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 468ee3: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468ee9: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 468eeb: push 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 468eed: push esi */
	m->esp -= 4; M32(m->esp) = 0x468ef3u; native_call(m, 0x470fc0u);	/* 468eee: call 0x470fc0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 468ef3: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468ef6: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468ef9: cmp eax, 1 */
	if (!m->zf) goto L_468f20;	/* 468efc: jne 0x468f20 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 468efe: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468f04: test eax, eax */
	if (!m->zf) goto L_468f20;	/* 468f06: jne 0x468f20 */
	m->esp -= 4; M32(m->esp) = 0x468f0du; native_call(m, 0x4a86d0u);	/* 468f08: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468f0d: cmp eax, 1 */
	if (!m->zf) goto L_468f20;	/* 468f10: jne 0x468f20 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 468f12: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468f18: push ecx */
	m->ecx = m->ebp;	/* 468f19: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x468f20u; native_call(m, 0x48dbf0u);	/* 468f1b: call 0x48dbf0 */
L_468f20:
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f20: push 3 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f22: push 0x10 */
	{ DWORD v_ = 0x43fa0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f24: push 0x43fa0000 */
	{ DWORD v_ = 0x469c4000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f29: push 0x469c4000 */
	{ DWORD v_ = 0x469c4000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f2e: push 0x469c4000 */
	{ DWORD v_ = 0x469c4000u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f33: push 0x469c4000 */
	m->ecx = m->esi;	/* 468f38: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x468f3fu; native_call(m, 0x471040u);	/* 468f3a: call 0x471040 */
	m->ecx = M32((DWORD)(m->ebp + 0x8u));	/* 468f3f: mov ecx, dword ptr [ebp + 8] */
	m->eax = m->ecx;	/* 468f42: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 468f44: sub eax, 0 */
	if (m->zf) goto L_468f65;	/* 468f47: je 0x468f65 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 468f49: dec eax */
	if (m->zf) goto L_468f65;	/* 468f4a: je 0x468f65 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 468f4c: sub eax, 2 */
	if (m->zf) goto L_468f65;	/* 468f4f: je 0x468f65 */
	m->edx = M32((DWORD)(m->ebp + 0x233cc24u));	/* 468f51: mov edx, dword ptr [ebp + 0x233cc24] */
	m->eax = M32((DWORD)(m->ebp + 0x233cc20u));	/* 468f57: mov eax, dword ptr [ebp + 0x233cc20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468f5d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468f5e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468f5f: push ecx */
	goto L_469174;	/* 468f60: jmp 0x469174 */
L_468f65:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 468f65: mov eax, dword ptr [ebp + 0x2340c60] */
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x6u;	/* 468f6b: mov dword ptr [ebp + 0x233cc24], 6 */
	m->ecx = m->eax;	/* 468f75: mov ecx, eax */
	m->edi = 0x4c511cu;	/* 468f77: mov edi, 0x4c511c */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 468f7c: shl ecx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 468f7f: inc eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x233cc60u);	/* 468f80: lea edx, [ecx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 468f87: mov dword ptr [ebp + 0x2340c60], eax */
	goto L_4689bd;	/* 468f8d: jmp 0x4689bd */
L_468f92:
	{ DWORD v_ = 0x4c5104u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f92: push 0x4c5104 */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 468f97: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f9d: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 468f9f: push 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 468fa1: push esi */
	m->esp -= 4; M32(m->esp) = 0x468fa7u; native_call(m, 0x470fc0u);	/* 468fa2: call 0x470fc0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 468fa7: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468faa: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468fad: cmp eax, 1 */
	if (!m->zf) goto L_468fd4;	/* 468fb0: jne 0x468fd4 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 468fb2: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468fb8: test eax, eax */
	if (!m->zf) goto L_468fd4;	/* 468fba: jne 0x468fd4 */
	m->esp -= 4; M32(m->esp) = 0x468fc1u; native_call(m, 0x4a86d0u);	/* 468fbc: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468fc1: cmp eax, 1 */
	if (!m->zf) goto L_468fd4;	/* 468fc4: jne 0x468fd4 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 468fc6: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468fcc: push ecx */
	m->ecx = m->ebp;	/* 468fcd: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x468fd4u; native_call(m, 0x48dbf0u);	/* 468fcf: call 0x48dbf0 */
L_468fd4:
	m->edx = M32((DWORD)(0x4df00cu));	/* 468fd4: mov edx, dword ptr [0x4df00c] */
	m->eax = (DWORD)(m->esp + 0x15cu);	/* 468fda: lea eax, [esp + 0x15c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468fe1: push edx */
	{ DWORD v_ = 0x4c50e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 468fe2: push 0x4c50e4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468fe7: push eax */
	m->esp -= 4; M32(m->esp) = 0x468fedu; native_call(m, 0x49e9ddu);	/* 468fe8: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468fed: add esp, 0xc */
	m->ecx = (DWORD)(m->esp + 0x15cu);	/* 468ff0: lea ecx, [esp + 0x15c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468ff7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468ff9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468ffb: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468ffd: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468fff: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 469001: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 469003: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469005: push ecx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 469006: mov ecx, dword ptr [0xa0e010] */
	m->esp -= 4; M32(m->esp) = 0x469011u; native_call(m, 0x456be0u);	/* 46900c: call 0x456be0 */
	m->edx = (DWORD)(m->ebp + 0x1f35c8u);	/* 469011: lea edx, [ebp + 0x1f35c8] */
	M32((DWORD)(m->ebp + 0x233c9f8u)) = m->eax;	/* 469017: mov dword ptr [ebp + 0x233c9f8], eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46901d: push edx */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 46901e: lea eax, [esp + 0x60] */
	{ DWORD v_ = 0x4c5190u; m->esp -= 4; M32(m->esp) = v_; }	/* 469022: push 0x4c5190 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469027: push eax */
	m->esp -= 4; M32(m->esp) = 0x46902du; native_call(m, 0x49e9ddu);	/* 469028: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46902d: add esp, 0xc */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 469030: lea ecx, [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469034: push ecx */
	m->ecx = m->esi;	/* 469035: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x46903cu; native_call(m, 0x4876b0u);	/* 469037: call 0x4876b0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 46903c: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46903f: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_469165;	/* 469042: ja 0x469165 */
	switch (m->eax) { case 0: goto L_46904f; case 1: goto L_46905e; case 2: goto L_46913c; case 3: goto L_46913c; default: abort(); }	/* 469048: jmp dword ptr [eax*4 + 0x4692e4] */
L_46904f:
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x7u;	/* 46904f: mov dword ptr [ebp + 0x233cc24], 7 */
	goto L_469119;	/* 469059: jmp 0x469119 */
L_46905e:
	M32((DWORD)(m->ebp + 0x233cc24u)) = 0x7u;	/* 46905e: mov dword ptr [ebp + 0x233cc24], 7 */
	goto L_469142;	/* 469068: jmp 0x469142 */
L_46906d:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46906d: cmp dword ptr [ebp + 8], 1 */
	if (!m->zf) goto L_469095;	/* 469071: jne 0x469095 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 469073: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 469079: test eax, eax */
	if (!m->zf) goto L_469095;	/* 46907b: jne 0x469095 */
	m->esp -= 4; M32(m->esp) = 0x469082u; native_call(m, 0x4a86d0u);	/* 46907d: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469082: cmp eax, 1 */
	if (!m->zf) goto L_469095;	/* 469085: jne 0x469095 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 469087: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->ebp;	/* 46908d: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46908f: push eax */
	m->esp -= 4; M32(m->esp) = 0x469095u; native_call(m, 0x48dbf0u);	/* 469090: call 0x48dbf0 */
L_469095:
	{ DWORD v_ = 0x4c50c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 469095: push 0x4c50c4 */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 46909a: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4690a0: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4690a2: push 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4690a4: push esi */
	m->esp -= 4; M32(m->esp) = 0x4690aau; native_call(m, 0x470fc0u);	/* 4690a5: call 0x470fc0 */
	m->edi = (DWORD)(m->ebp + 0x1f35c8u);	/* 4690aa: lea edi, [ebp + 0x1f35c8] */
	m->ecx = (DWORD)(m->esp + 0x6cu);	/* 4690b0: lea ecx, [esp + 0x6c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4690b4: push edi */
	{ DWORD v_ = 0x4c5190u; m->esp -= 4; M32(m->esp) = v_; }	/* 4690b5: push 0x4c5190 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4690ba: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4690c0u; native_call(m, 0x49e9ddu);	/* 4690bb: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4690c0: add esp, 0x1c */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 4690c3: lea edx, [esp + 0x5c] */
	m->ecx = m->esi;	/* 4690c7: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4690c9: push edx */
	m->esp -= 4; M32(m->esp) = 0x4690cfu; native_call(m, 0x48b5c0u);	/* 4690ca: call 0x48b5c0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 4690cf: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4690d2: test eax, eax */
	if (!m->zf) goto L_469104;	/* 4690d4: jne 0x469104 */
	{ DWORD v_ = 0x4c50b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4690d6: push 0x4c50b4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4690db: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4690dd: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4690df: push esi */
	m->esp -= 4; M32(m->esp) = 0x4690e5u; native_call(m, 0x470fc0u);	/* 4690e0: call 0x470fc0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4690e5: push edi */
	m->eax = (DWORD)(m->esp + 0x70u);	/* 4690e6: lea eax, [esp + 0x70] */
	{ DWORD v_ = 0x4c5190u; m->esp -= 4; M32(m->esp) = v_; }	/* 4690ea: push 0x4c5190 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4690ef: push eax */
	m->esp -= 4; M32(m->esp) = 0x4690f5u; native_call(m, 0x49e9ddu);	/* 4690f0: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4690f5: add esp, 0x1c */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 4690f8: lea ecx, [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4690fc: push ecx */
	m->ecx = m->esi;	/* 4690fd: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x469104u; native_call(m, 0x474550u);	/* 4690ff: call 0x474550 */
L_469104:
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 469104: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469107: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_469165;	/* 46910a: ja 0x469165 */
	switch (m->eax) { case 0: goto L_469113; case 1: goto L_46913c; case 2: goto L_46913c; case 3: goto L_46913c; default: abort(); }	/* 46910c: jmp dword ptr [eax*4 + 0x4692f4] */
L_469113:
	M32((DWORD)(m->ebp + 0x233cc24u)) = m->ebx;	/* 469113: mov dword ptr [ebp + 0x233cc24], ebx */
L_469119:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 469119: mov eax, dword ptr [ebp + 0x2340c60] */
	m->edi = 0x4c50a0u;	/* 46911f: mov edi, 0x4c50a0 */
	m->edx = m->eax;	/* 469124: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 469126: shl edx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 469129: inc eax */
	m->edx = (DWORD)(m->edx + m->ebp*1 + 0x233cc60u);	/* 46912a: lea edx, [edx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 469131: mov dword ptr [ebp + 0x2340c60], eax */
	goto L_4689bd;	/* 469137: jmp 0x4689bd */
L_46913c:
	M32((DWORD)(m->ebp + 0x233cc24u)) = m->ebx;	/* 46913c: mov dword ptr [ebp + 0x233cc24], ebx */
L_469142:
	m->eax = M32((DWORD)(m->ebp + 0x2340c60u));	/* 469142: mov eax, dword ptr [ebp + 0x2340c60] */
	m->edi = 0x4c50a0u;	/* 469148: mov edi, 0x4c50a0 */
	m->ecx = m->eax;	/* 46914d: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46914f: shl ecx, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 469152: inc eax */
	m->edx = (DWORD)(m->ecx + m->ebp*1 + 0x233cc60u);	/* 469153: lea edx, [ecx + ebp + 0x233cc60] */
	M32((DWORD)(m->ebp + 0x2340c60u)) = m->eax;	/* 46915a: mov dword ptr [ebp + 0x2340c60], eax */
	goto L_4689bd;	/* 469160: jmp 0x4689bd */
L_469165:
	m->ecx = M32((DWORD)(m->ebp + 0x233cc24u));	/* 469165: mov ecx, dword ptr [ebp + 0x233cc24] */
	m->edx = M32((DWORD)(m->ebp + 0x233cc20u));	/* 46916b: mov edx, dword ptr [ebp + 0x233cc20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469171: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469172: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469173: push eax */
L_469174:
	{ DWORD v_ = 0x4c5060u; m->esp -= 4; M32(m->esp) = v_; }	/* 469174: push 0x4c5060 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 469179: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x469183u; native_call(m, 0x46c710u);	/* 46917e: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469183: add esp, 0x14 */
	goto L_4689da;	/* 469186: jmp 0x4689da */
L_46918b:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46918b: xor edi, edi */
	{ DWORD v_ = 0x4c5048u; m->esp -= 4; M32(m->esp) = v_; }	/* 46918d: push 0x4c5048 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 469192: push edi */
	m->eax = (DWORD)(m->ebp + 0x1f36c8u);	/* 469193: lea eax, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0xfffffffeu; m->esp -= 4; M32(m->esp) = v_; }	/* 469199: push -2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46919b: push eax */
	m->esp -= 4; M32(m->esp) = 0x4691a1u; native_call(m, 0x470fc0u);	/* 46919c: call 0x470fc0 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 4691a1: mov eax, dword ptr [ebp + 8] */
	m->esi = 0x1u;	/* 4691a4: mov esi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4691a9: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4691ac: cmp eax, esi */
	if (!m->zf) goto L_4691cf;	/* 4691ae: jne 0x4691cf */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234240du)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4691b0: cmp dword ptr [ebp + 0x234240d], edi */
	if (!m->zf) goto L_4691cf;	/* 4691b6: jne 0x4691cf */
	m->esp -= 4; M32(m->esp) = 0x4691bdu; native_call(m, 0x4a86d0u);	/* 4691b8: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4691bd: cmp eax, esi */
	if (!m->zf) goto L_4691cf;	/* 4691bf: jne 0x4691cf */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 4691c1: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4691c7: push ecx */
	m->ecx = m->ebp;	/* 4691c8: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x4691cfu; native_call(m, 0x48dbf0u);	/* 4691ca: call 0x48dbf0 */
L_4691cf:
	m->ecx = m->ebp;	/* 4691cf: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x4691d6u; native_call(m, 0x462850u);	/* 4691d1: call 0x462850 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 4691d6: mov eax, dword ptr [ebp + 8] */
	M32((DWORD)(m->ebp + 0x233c9e8u)) = m->esi;	/* 4691d9: mov dword ptr [ebp + 0x233c9e8], esi */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4691df: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_469260;	/* 4691e2: ja 0x469260 */
	switch (m->eax) { case 0: goto L_4691eb; case 1: goto L_4691eb; case 2: goto L_469212; case 3: goto L_469239; default: abort(); }	/* 4691e4: jmp dword ptr [eax*4 + 0x469304] */
L_4691eb:
	M32((DWORD)(m->ebp + 0x233cc20u)) = 0x2u;	/* 4691eb: mov dword ptr [ebp + 0x233cc20], 2 */
	M32((DWORD)(m->ebp + 0x233cc28u)) = m->edi;	/* 4691f5: mov dword ptr [ebp + 0x233cc28], edi */
	M32((DWORD)(0xae2ec8u)) = m->edi;	/* 4691fb: mov dword ptr [0xae2ec8], edi */
	m->eax = M32((DWORD)(m->ebp + 0x233cc20u));	/* 469201: mov eax, dword ptr [ebp + 0x233cc20] */
	m->edi = M32(m->esp); m->esp += 4;	/* 469207: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 469208: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 469209: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46920a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46920b: add esp, 0x24c */
	m->esp += 4 + 0; return;	/* 469211: ret  */
L_469212:
	M32((DWORD)(m->ebp + 0x233cc20u)) = 0x3u;	/* 469212: mov dword ptr [ebp + 0x233cc20], 3 */
	M32((DWORD)(m->ebp + 0x233cc28u)) = m->edi;	/* 46921c: mov dword ptr [ebp + 0x233cc28], edi */
	M32((DWORD)(0xae2ec8u)) = m->edi;	/* 469222: mov dword ptr [0xae2ec8], edi */
	m->eax = M32((DWORD)(m->ebp + 0x233cc20u));	/* 469228: mov eax, dword ptr [ebp + 0x233cc20] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46922e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46922f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 469230: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 469231: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469232: add esp, 0x24c */
	m->esp += 4 + 0; return;	/* 469238: ret  */
L_469239:
	M32((DWORD)(m->ebp + 0x233cc20u)) = 0x4u;	/* 469239: mov dword ptr [ebp + 0x233cc20], 4 */
	M32((DWORD)(m->ebp + 0x233cc28u)) = m->edi;	/* 469243: mov dword ptr [ebp + 0x233cc28], edi */
	M32((DWORD)(0xae2ec8u)) = m->edi;	/* 469249: mov dword ptr [0xae2ec8], edi */
	m->eax = M32((DWORD)(m->ebp + 0x233cc20u));	/* 46924f: mov eax, dword ptr [ebp + 0x233cc20] */
	m->edi = M32(m->esp); m->esp += 4;	/* 469255: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 469256: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 469257: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 469258: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469259: add esp, 0x24c */
	m->esp += 4 + 0; return;	/* 46925f: ret  */
L_469260:
	m->edx = M32((DWORD)(m->ebp + 0x233cc24u));	/* 469260: mov edx, dword ptr [ebp + 0x233cc24] */
	m->ecx = M32((DWORD)(m->ebp + 0x233cc20u));	/* 469266: mov ecx, dword ptr [ebp + 0x233cc20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46926c: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46926d: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46926e: push eax */
	{ DWORD v_ = 0x4c5060u; m->esp -= 4; M32(m->esp) = v_; }	/* 46926f: push 0x4c5060 */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 469274: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x46927eu; native_call(m, 0x46c710u);	/* 469279: call 0x46c710 */
	M32((DWORD)(m->ebp + 0x233cc28u)) = m->edi;	/* 46927e: mov dword ptr [ebp + 0x233cc28], edi */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469284: add esp, 0x14 */
	M32((DWORD)(0xae2ec8u)) = m->edi;	/* 469287: mov dword ptr [0xae2ec8], edi */
L_46928d:
	m->eax = M32((DWORD)(m->ebp + 0x233cc20u));	/* 46928d: mov eax, dword ptr [ebp + 0x233cc20] */
	m->edi = M32(m->esp); m->esp += 4;	/* 469293: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 469294: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 469295: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 469296: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469297: add esp, 0x24c */
	m->esp += 4 + 0; return;	/* 46929d: ret  */
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
