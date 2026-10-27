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

static void lift_40f220(X86 *m);
static void lift_40f9e0(X86 *m);

/* armc_40f9e0 (0x40f9e0), lifted by tools/lift.py */
static void lift_40f9e0(X86 *m)
{
	m->ecx = M32((DWORD)(0x4dbe48u));	/* 40f9e0: mov ecx, dword ptr [0x4dbe48] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f9e6: or eax, 0xffffffff */
	{ DWORD a_ = m->ecx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f9e9: cmp ecx, 5 */
	if (!m->cf && !m->zf) goto L_40fa68;	/* 40f9ec: ja 0x40fa68 */
	switch (m->ecx) { case 0: goto L_40f9f5; case 1: goto L_40fa08; case 2: goto L_40fa1c; case 3: goto L_40fa2f; case 4: goto L_40fa43; case 5: goto L_40fa56; default: abort(); }	/* 40f9ee: jmp dword ptr [ecx*4 + 0x40fb08] */
L_40f9f5:
	m->eax = M32((DWORD)(0x4dc77cu));	/* 40f9f5: mov eax, dword ptr [0x4dc77c] */
	m->eax = M32((DWORD)(m->eax*4 + 0x4dc79cu));	/* 40f9fa: mov eax, dword ptr [eax*4 + 0x4dc79c] */
	M32((DWORD)(0x4dcb20u)) = m->eax;	/* 40fa01: mov dword ptr [0x4dcb20], eax */
	goto L_40fa68;	/* 40fa06: jmp 0x40fa68 */
L_40fa08:
	m->edx = M32((DWORD)(0x4dc77cu));	/* 40fa08: mov edx, dword ptr [0x4dc77c] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4dc79cu));	/* 40fa0e: mov eax, dword ptr [edx*4 + 0x4dc79c] */
	M32((DWORD)(0x4dcb24u)) = m->eax;	/* 40fa15: mov dword ptr [0x4dcb24], eax */
	goto L_40fa68;	/* 40fa1a: jmp 0x40fa68 */
L_40fa1c:
	m->eax = M32((DWORD)(0x4dc77cu));	/* 40fa1c: mov eax, dword ptr [0x4dc77c] */
	m->eax = M32((DWORD)(m->eax*4 + 0x4dc79cu));	/* 40fa21: mov eax, dword ptr [eax*4 + 0x4dc79c] */
	M32((DWORD)(0x4dcb28u)) = m->eax;	/* 40fa28: mov dword ptr [0x4dcb28], eax */
	goto L_40fa68;	/* 40fa2d: jmp 0x40fa68 */
L_40fa2f:
	m->edx = M32((DWORD)(0x4dc77cu));	/* 40fa2f: mov edx, dword ptr [0x4dc77c] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4dc79cu));	/* 40fa35: mov eax, dword ptr [edx*4 + 0x4dc79c] */
	M32((DWORD)(0x4dcb2cu)) = m->eax;	/* 40fa3c: mov dword ptr [0x4dcb2c], eax */
	goto L_40fa68;	/* 40fa41: jmp 0x40fa68 */
L_40fa43:
	m->eax = M32((DWORD)(0x4dc77cu));	/* 40fa43: mov eax, dword ptr [0x4dc77c] */
	m->eax = M32((DWORD)(m->eax*4 + 0x4dcca4u));	/* 40fa48: mov eax, dword ptr [eax*4 + 0x4dcca4] */
	M32((DWORD)(0x4dcb18u)) = m->eax;	/* 40fa4f: mov dword ptr [0x4dcb18], eax */
	goto L_40fa68;	/* 40fa54: jmp 0x40fa68 */
L_40fa56:
	m->edx = M32((DWORD)(0x4dc77cu));	/* 40fa56: mov edx, dword ptr [0x4dc77c] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4dcca4u));	/* 40fa5c: mov eax, dword ptr [edx*4 + 0x4dcca4] */
	M32((DWORD)(0x4dcb1cu)) = m->eax;	/* 40fa63: mov dword ptr [0x4dcb1c], eax */
L_40fa68:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40fa68: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fa69: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fa6a: push ecx */
	M32((DWORD)(0x4dcc64u)) = 0x1u;	/* 40fa6b: mov dword ptr [0x4dcc64], 1 */
	m->esp -= 4; M32(m->esp) = 0x40fa7au; native_call(m, 0x41ca50u);	/* 40fa75: call 0x41ca50 */
	m->eax = M32((DWORD)(0x4dbe48u));	/* 40fa7a: mov eax, dword ptr [0x4dbe48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fa7f: push eax */
	m->esp -= 4; M32(m->esp) = 0x40fa85u; native_call(m, 0x419000u);	/* 40fa80: call 0x419000 */
	m->ecx = M32((DWORD)(0x4dcb1cu));	/* 40fa85: mov ecx, dword ptr [0x4dcb1c] */
	m->edx = M32((DWORD)(0x4dcb18u));	/* 40fa8b: mov edx, dword ptr [0x4dcb18] */
	m->eax = M32((DWORD)(0x4dcb2cu));	/* 40fa91: mov eax, dword ptr [0x4dcb2c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fa96: add esp, 0xc */
	m->esi = M32((DWORD)(0x4dbe48u));	/* 40fa99: mov esi, dword ptr [0x4dbe48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fa9f: push ecx */
	m->ecx = M32((DWORD)(0x4dcb28u));	/* 40faa0: mov ecx, dword ptr [0x4dcb28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40faa6: push edx */
	m->edx = M32((DWORD)(0x4dcb24u));	/* 40faa7: mov edx, dword ptr [0x4dcb24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40faad: push eax */
	m->eax = M32((DWORD)(0x4dcb20u));	/* 40faae: mov eax, dword ptr [0x4dcb20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fab3: push ecx */
	m->ecx = M32((DWORD)(0x4dc770u));	/* 40fab4: mov ecx, dword ptr [0x4dc770] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40faba: push edx */
	m->edx = M32((DWORD)(0x4dc76cu));	/* 40fabb: mov edx, dword ptr [0x4dc76c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fac1: push eax */
	m->eax = M32((DWORD)(0x4dc768u));	/* 40fac2: mov eax, dword ptr [0x4dc768] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fac7: push ecx */
	m->ecx = M32((DWORD)(0x4dc764u));	/* 40fac8: mov ecx, dword ptr [0x4dc764] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40face: push edx */
	m->edx = M32((DWORD)(0x4dc760u));	/* 40facf: mov edx, dword ptr [0x4dc760] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fad5: push eax */
	m->eax = M32((DWORD)(0x9f1818u));	/* 40fad6: mov eax, dword ptr [0x9f1818] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fadb: push ecx */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 40fadc: mov ecx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fae2: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fae3: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fae5: push eax */
	{ DWORD v_ = 0x4dedd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fae6: push 0x4dedd8 */
	m->esp -= 4; M32(m->esp) = 0x40faf0u; native_call(m, 0x461250u);	/* 40faeb: call 0x461250 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40faf0: push esi */
	M32((DWORD)(0x4dbe48u)) = 0xffffffffu;	/* 40faf1: mov dword ptr [0x4dbe48], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x40fb00u; native_call(m, 0x40f870u);	/* 40fafb: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fb00: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fb03: pop esi */
	m->esp += 4 + 0; return;	/* 40fb04: ret  */
}

/* armc_drawPartScreen (0x40f220), lifted by tools/lift.py */
static void lift_40f220(X86 *m)
{
	m->eax = M32((DWORD)(0x4dcb20u));	/* 40f220: mov eax, dword ptr [0x4dcb20] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40f225: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40f226: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40f227: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f228: push 0 */
	M32((DWORD)(0x4dc798u)) = 0x2u;	/* 40f22a: mov dword ptr [0x4dc798], 2 */
	M32((DWORD)(0x4dbe48u)) = 0x0u;	/* 40f234: mov dword ptr [0x4dbe48], 0 */
	M32((DWORD)(0x4dc864u)) = 0x0u;	/* 40f23e: mov dword ptr [0x4dc864], 0 */
	m->esp -= 4; M32(m->esp) = 0x40f24du; native_call(m, 0x41ca50u);	/* 40f248: call 0x41ca50 */
	m->ecx = M32((DWORD)(0x4dcb24u));	/* 40f24d: mov ecx, dword ptr [0x4dcb24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40f253: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f254: push 1 */
	m->esp -= 4; M32(m->esp) = 0x40f25bu; native_call(m, 0x41ca50u);	/* 40f256: call 0x41ca50 */
	m->edx = M32((DWORD)(0x4dcb28u));	/* 40f25b: mov edx, dword ptr [0x4dcb28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40f261: push edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f262: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40f269u; native_call(m, 0x41ca50u);	/* 40f264: call 0x41ca50 */
	m->eax = M32((DWORD)(0x4dcb2cu));	/* 40f269: mov eax, dword ptr [0x4dcb2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40f26e: push eax */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f26f: push 3 */
	m->esp -= 4; M32(m->esp) = 0x40f276u; native_call(m, 0x41ca50u);	/* 40f271: call 0x41ca50 */
	m->ecx = M32((DWORD)(0x4dcb18u));	/* 40f276: mov ecx, dword ptr [0x4dcb18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40f27c: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f27d: push 4 */
	m->esp -= 4; M32(m->esp) = 0x40f284u; native_call(m, 0x41ca50u);	/* 40f27f: call 0x41ca50 */
	m->edx = M32((DWORD)(0x4dcb1cu));	/* 40f284: mov edx, dword ptr [0x4dcb1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40f28a: push edx */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f28b: push 5 */
	m->esp -= 4; M32(m->esp) = 0x40f292u; native_call(m, 0x41ca50u);	/* 40f28d: call 0x41ca50 */
	m->edx = M32((DWORD)(0x4dc244u));	/* 40f292: mov edx, dword ptr [0x4dc244] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40f298: add esp, 0x30 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40f29b: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f29d: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40f29f: test edx, edx */
	M32((DWORD)(0x4dc77cu)) = m->esi;	/* 40f2a1: mov dword ptr [0x4dc77c], esi */
	if (m->zf || m->sf != m->of) goto L_40f2ca;	/* 40f2a7: jle 0x40f2ca */
	m->edi = M32((DWORD)(0x4dcb20u));	/* 40f2a9: mov edi, dword ptr [0x4dcb20] */
	m->ecx = 0x4dc79cu;	/* 40f2af: mov ecx, 0x4dc79c */
L_40f2b4:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f2b4: cmp dword ptr [ecx], edi */
	if (m->zf) goto L_40f2c2;	/* 40f2b6: je 0x40f2c2 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40f2b8: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40f2b9: add ecx, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f2bc: cmp eax, edx */
	if (m->sf != m->of) goto L_40f2b4;	/* 40f2be: jl 0x40f2b4 */
	goto L_40f2ca;	/* 40f2c0: jmp 0x40f2ca */
L_40f2c2:
	m->esi = m->eax;	/* 40f2c2: mov esi, eax */
	M32((DWORD)(0x4dc77cu)) = m->esi;	/* 40f2c4: mov dword ptr [0x4dc77c], esi */
L_40f2ca:
	m->eax = M32((DWORD)(m->esi*4 + 0x4dc79cu));	/* 40f2ca: mov eax, dword ptr [esi*4 + 0x4dc79c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40f2d1: push eax */
	m->esp -= 4; M32(m->esp) = 0x40f2d7u; native_call(m, 0x41cca0u);	/* 40f2d2: call 0x41cca0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40f2d7: add esp, 4 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40f2da: xor esi, esi */
L_40f2dc:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40f2dc: push esi */
	m->esp -= 4; M32(m->esp) = 0x40f2e2u; native_call(m, 0x419000u);	/* 40f2dd: call 0x419000 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40f2e2: add esp, 4 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40f2e5: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f2e6: cmp esi, 7 */
	if (m->sf != m->of) goto L_40f2dc;	/* 40f2e9: jl 0x40f2dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f2eb: push 0 */
	M32((DWORD)(0x4dcc64u)) = 0x0u;	/* 40f2ed: mov dword ptr [0x4dcc64], 0 */
	M32((DWORD)(0x4dcf14u)) = 0x1u;	/* 40f2f7: mov dword ptr [0x4dcf14], 1 */
	M32((DWORD)(0x4dbe48u)) = 0xffffffffu;	/* 40f301: mov dword ptr [0x4dbe48], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x40f310u; native_call(m, 0x40f870u);	/* 40f30b: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40f310: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40f318u; native_call(m, 0x41b300u);	/* 40f313: call 0x41b300 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40f318: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40f319: pop esi */
	m->esp += 4 + 0; return;	/* 40f31a: ret  */
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
