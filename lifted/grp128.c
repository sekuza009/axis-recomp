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

static void lift_453a90(X86 *m);
static void lift_420100(X86 *m);

/* game_postMatch (0x420100), lifted by tools/lift.py */
static void lift_420100(X86 *m)
{
	m->eax = M32((DWORD)(0x76d410u));	/* 420100: mov eax, dword ptr [0x76d410] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 420105: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 420106: push edi */
	m->esi = 0x1u;	/* 420107: mov esi, 1 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 42010c: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42010e: cmp eax, esi */
	M32((DWORD)(0x4de6f8u)) = m->esi;	/* 420110: mov dword ptr [0x4de6f8], esi */
	M32((DWORD)(0x5b1dacu)) = m->edi;	/* 420116: mov dword ptr [0x5b1dac], edi */
	if (!m->zf) goto L_420134;	/* 42011c: jne 0x420134 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42011e: push edi */
	m->esp -= 4; M32(m->esp) = 0x420124u; native_call(m, 0x41e7a0u);	/* 42011f: call 0x41e7a0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 420124: add esp, 4 */
	M32((DWORD)(0x76d3e8u)) = 0xffffffffu;	/* 420127: mov dword ptr [0x76d3e8], 0xffffffff */
	m->edi = M32(m->esp); m->esp += 4;	/* 420131: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 420132: pop esi */
	m->esp += 4 + 0; return;	/* 420133: ret  */
L_420134:
	{ DWORD a_ = M32((DWORD)(0x9db990u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420134: cmp dword ptr [0x9db990], edi */
	if (m->zf) goto L_420142;	/* 42013a: je 0x420142 */
	M32((DWORD)(0x5ae9c4u)) = m->edi;	/* 42013c: mov dword ptr [0x5ae9c4], edi */
L_420142:
	m->eax = M32((DWORD)(0x5ae9c4u));	/* 420142: mov eax, dword ptr [0x5ae9c4] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 420147: dec eax */
	if (m->zf) goto L_420225;	/* 420148: je 0x420225 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42014e: dec eax */
	if (m->zf) goto L_4201ae;	/* 42014f: je 0x4201ae */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 420151: dec eax */
	if (m->zf) goto L_42015e;	/* 420152: je 0x42015e */
L_420154:
	m->esp -= 4; M32(m->esp) = 0x420159u; native_call(m, 0x41e8b0u);	/* 420154: call 0x41e8b0 */
	goto L_42024d;	/* 420159: jmp 0x42024d */
L_42015e:
	m->eax = M32((DWORD)(0x9f181cu));	/* 42015e: mov eax, dword ptr [0x9f181c] */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420163: cmp eax, 0xf */
	if (!m->zf) goto L_420191;	/* 420166: jne 0x420191 */
	M32((DWORD)(0x9f181cu)) = 0x10u;	/* 420168: mov dword ptr [0x9f181c], 0x10 */
	m->esp -= 4; M32(m->esp) = 0x420177u; native_call(m, 0x447010u);	/* 420172: call 0x447010 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 420177: push esi */
	m->esp -= 4; M32(m->esp) = 0x42017du; native_call(m, 0x41f880u);	/* 420178: call 0x41f880 */
	m->esp -= 4; M32(m->esp) = 0x420182u; native_call(m, 0x457310u);	/* 42017d: call 0x457310 */
	{ DWORD v_ = 0x63u; m->esp -= 4; M32(m->esp) = v_; }	/* 420182: push 0x63 */
	m->esp -= 4; M32(m->esp) = 0x420189u; native_call(m, 0x41e7a0u);	/* 420184: call 0x41e7a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 420189: add esp, 8 */
	goto L_42025a;	/* 42018c: jmp 0x42025a */
L_420191:
	if (m->sf != m->of) goto L_420196;	/* 420191: jl 0x420196 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 420193: push esi */
	goto L_420197;	/* 420194: jmp 0x420197 */
L_420196:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 420196: push edi */
L_420197:
	m->esp -= 4; M32(m->esp) = 0x42019cu; native_call(m, 0x41f880u);	/* 420197: call 0x41f880 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42019c: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4201a4u; native_call(m, 0x447010u);	/* 42019f: call 0x447010 */
	m->esp -= 4; M32(m->esp) = 0x4201a9u; native_call(m, 0x41ec50u);	/* 4201a4: call 0x41ec50 */
	goto L_42024d;	/* 4201a9: jmp 0x42024d */
L_4201ae:
	{ DWORD a_ = M32((DWORD)(0xa0baf8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4201ae: cmp dword ptr [0xa0baf8], edi */
	if (m->zf) goto L_42020d;	/* 4201b4: je 0x42020d */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4201b6: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4201b7: push edi */
	{ DWORD v_ = 0x9f9418u; m->esp -= 4; M32(m->esp) = v_; }	/* 4201b8: push 0x9f9418 */
	M32((DWORD)(0x9f941cu)) = m->esi;	/* 4201bd: mov dword ptr [0x9f941c], esi */
	m->esp -= 4; M32(m->esp) = 0x4201c8u; native_call(m, 0x451270u);	/* 4201c3: call 0x451270 */
	m->eax = M32((DWORD)(0xa0b328u));	/* 4201c8: mov eax, dword ptr [0xa0b328] */
	m->ecx = M32((DWORD)(0xa0b330u));	/* 4201cd: mov ecx, dword ptr [0xa0b330] */
	m->esi = M32((DWORD)(0x4a911cu));	/* 4201d3: mov esi, dword ptr [0x4a911c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4201d9: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x43u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4201dc: add eax, 0x43 */
	{ DWORD a_ = m->ecx, b_ = 0x43u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4201df: add ecx, 0x43 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4201e2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4201e3: push ecx */
	M32((DWORD)(0x9f941cu)) = m->edi;	/* 4201e4: mov dword ptr [0x9f941c], edi */
	m->esp -= 4; M32(m->esp) = 0x4201ecu; native_call(m, m->esi);	/* 4201ea: call esi */
	m->edx = M32((DWORD)(0xa0b328u));	/* 4201ec: mov edx, dword ptr [0xa0b328] */
	m->eax = M32((DWORD)(0xa0b330u));	/* 4201f2: mov eax, dword ptr [0xa0b330] */
	{ DWORD a_ = m->edx, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4201f7: add edx, 0x33 */
	{ DWORD a_ = m->eax, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4201fa: add eax, 0x33 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4201fd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4201fe: push eax */
	m->esp -= 4; M32(m->esp) = 0x420201u; native_call(m, m->esi);	/* 4201ff: call esi */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 420201: push 0x65 */
	{ DWORD v_ = 0x16u; m->esp -= 4; M32(m->esp) = v_; }	/* 420203: push 0x16 */
	m->esp -= 4; M32(m->esp) = 0x42020au; native_call(m, 0x4521c0u);	/* 420205: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42020a: add esp, 8 */
L_42020d:
	{ DWORD a_ = M32((DWORD)(0xa05630u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42020d: cmp dword ptr [0xa05630], edi */
	if (m->zf) goto L_420154;	/* 420213: je 0x420154 */
	m->esp -= 4; M32(m->esp) = 0x42021eu; native_call(m, 0x44aee0u);	/* 420219: call 0x44aee0 */
	m->esp -= 4; M32(m->esp) = 0x420223u; native_call(m, 0x41eb00u);	/* 42021e: call 0x41eb00 */
	goto L_42024d;	/* 420223: jmp 0x42024d */
L_420225:
	{ DWORD a_ = M32((DWORD)(0xa0baf8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420225: cmp dword ptr [0xa0baf8], edi */
	if (m->zf) goto L_420248;	/* 42022b: je 0x420248 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42022d: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42022e: push edi */
	{ DWORD v_ = 0x9f9418u; m->esp -= 4; M32(m->esp) = v_; }	/* 42022f: push 0x9f9418 */
	M32((DWORD)(0x9f941cu)) = m->esi;	/* 420234: mov dword ptr [0x9f941c], esi */
	m->esp -= 4; M32(m->esp) = 0x42023fu; native_call(m, 0x451270u);	/* 42023a: call 0x451270 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42023f: add esp, 0xc */
	M32((DWORD)(0x9f941cu)) = m->edi;	/* 420242: mov dword ptr [0x9f941c], edi */
L_420248:
	m->esp -= 4; M32(m->esp) = 0x42024du; native_call(m, 0x41e9d0u);	/* 420248: call 0x41e9d0 */
L_42024d:
	{ DWORD v_ = 0x4b01ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 42024d: push 0x4b01cc */
	m->esp -= 4; M32(m->esp) = 0x420257u; native_call(m, 0x457150u);	/* 420252: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 420257: add esp, 4 */
L_42025a:
	{ DWORD a_ = M32((DWORD)(0xa0ea94u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42025a: cmp dword ptr [0xa0ea94], edi */
	if (m->zf) goto L_420272;	/* 420260: je 0x420272 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 420262: push 6 */
	m->esp -= 4; M32(m->esp) = 0x420269u; native_call(m, 0x41ee40u);	/* 420264: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 420269: add esp, 4 */
	M32((DWORD)(0xa0ea94u)) = m->edi;	/* 42026c: mov dword ptr [0xa0ea94], edi */
L_420272:
	m->edi = M32(m->esp); m->esp += 4;	/* 420272: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 420273: pop esi */
	m->esp += 4 + 0; return;	/* 420274: ret  */
}

/* dplay_initConnection (0x453a90), lifted by tools/lift.py */
static void lift_453a90(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x13cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453a90: sub esp, 0x13c */
	m->eax = M32((DWORD)(0xa0b404u));	/* 453a96: mov eax, dword ptr [0xa0b404] */
	M32((DWORD)(m->esp + 0x0u)) = 0x0u;	/* 453a9b: mov dword ptr [esp], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453aa3: test eax, eax */
	if (m->zf) goto L_453aba;	/* 453aa5: je 0x453aba */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453aa7: push eax */
	m->esp -= 4; M32(m->esp) = 0x453aadu; native_call(m, 0x453a10u);	/* 453aa8: call 0x453a10 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453aad: add esp, 4 */
	M32((DWORD)(0xa0b404u)) = 0x0u;	/* 453ab0: mov dword ptr [0xa0b404], 0 */
L_453aba:
	m->eax = M32((DWORD)(m->esp + 0x140u));	/* 453aba: mov eax, dword ptr [esp + 0x140] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 453ac1: push edi */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453ac2: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_453b33;	/* 453ac5: ja 0x453b33 */
	switch (m->eax) { case 0: goto L_453ace; case 1: goto L_453ae4; case 2: goto L_453aff; case 3: goto L_453b1a; default: abort(); }	/* 453ac7: jmp dword ptr [eax*4 + 0x453cdc] */
L_453ace:
	m->eax = M32((DWORD)(0xa0bae0u));	/* 453ace: mov eax, dword ptr [0xa0bae0] */
	M32((DWORD)(0xa0bad8u)) = 0xa0b3a0u;	/* 453ad3: mov dword ptr [0xa0bad8], 0xa0b3a0 */
	M32((DWORD)(0xa0badcu)) = m->eax;	/* 453add: mov dword ptr [0xa0badc], eax */
	goto L_453b3b;	/* 453ae2: jmp 0x453b3b */
L_453ae4:
	m->ecx = M32((DWORD)(0xa0bae4u));	/* 453ae4: mov ecx, dword ptr [0xa0bae4] */
	M32((DWORD)(0xa0bad8u)) = 0xa0b450u;	/* 453aea: mov dword ptr [0xa0bad8], 0xa0b450 */
	M32((DWORD)(0xa0badcu)) = m->ecx;	/* 453af4: mov dword ptr [0xa0badc], ecx */
	goto L_453c36;	/* 453afa: jmp 0x453c36 */
L_453aff:
	m->edx = M32((DWORD)(0xa0bae8u));	/* 453aff: mov edx, dword ptr [0xa0bae8] */
	M32((DWORD)(0xa0bad8u)) = 0xa0b408u;	/* 453b05: mov dword ptr [0xa0bad8], 0xa0b408 */
	M32((DWORD)(0xa0badcu)) = m->edx;	/* 453b0f: mov dword ptr [0xa0badc], edx */
	goto L_453c36;	/* 453b15: jmp 0x453c36 */
L_453b1a:
	m->eax = M32((DWORD)(0xa0baecu));	/* 453b1a: mov eax, dword ptr [0xa0baec] */
	M32((DWORD)(0xa0bad8u)) = 0xa0bab8u;	/* 453b1f: mov dword ptr [0xa0bad8], 0xa0bab8 */
	M32((DWORD)(0xa0badcu)) = m->eax;	/* 453b29: mov dword ptr [0xa0badc], eax */
	goto L_453c36;	/* 453b2e: jmp 0x453c36 */
L_453b33:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453b33: test eax, eax */
	if (!m->zf) goto L_453c36;	/* 453b35: jne 0x453c36 */
L_453b3b:
	m->edi = M32((DWORD)(m->esp + 0x148u));	/* 453b3b: mov edi, dword ptr [esp + 0x148] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453b42: push esi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453b43: test edi, edi */
	m->edx = (DWORD)(m->esp + 0x7cu);	/* 453b45: lea edx, [esp + 0x7c] */
	if (!m->zf) goto L_453b50;	/* 453b49: jne 0x453b50 */
	m->edi = 0xa0bb0cu;	/* 453b4b: mov edi, 0xa0bb0c */
L_453b50:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 453b50: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453b53: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 453b55: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 453b57: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 453b59: sub edi, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = 0x10u;	/* 453b5b: mov dword ptr [esp + 0x1c], 0x10 */
	m->eax = m->ecx;	/* 453b63: mov eax, ecx */
	m->esi = m->edi;	/* 453b65: mov esi, edi */
	m->edi = m->edx;	/* 453b67: mov edi, edx */
	m->edx = M32((DWORD)(0x4a963cu));	/* 453b69: mov edx, dword ptr [0x4a963c] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 453b6f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 453b72: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 453b74: mov ecx, eax */
	m->eax = M32((DWORD)(0x4a9640u));	/* 453b76: mov eax, dword ptr [0x4a9640] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 453b7b: and ecx, 3 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 453b7e: mov dword ptr [esp + 0x14], eax */
	m->eax = M32((DWORD)(0x4a9628u));	/* 453b82: mov eax, dword ptr [0x4a9628] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 453b87: mov dword ptr [esp + 0x10], edx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 453b8b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4a9638u));	/* 453b8d: mov ecx, dword ptr [0x4a9638] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 453b93: mov dword ptr [esp + 0x24], eax */
	m->eax = M32((DWORD)(0x4a9634u));	/* 453b97: mov eax, dword ptr [0x4a9634] */
	M32((DWORD)(m->esp + 0xcu)) = m->ecx;	/* 453b9c: mov dword ptr [esp + 0xc], ecx */
	m->ecx = M32((DWORD)(0x4a9644u));	/* 453ba0: mov ecx, dword ptr [0x4a9644] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 453ba6: mov dword ptr [esp + 0x30], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 453baa: mov dword ptr [esp + 0x18], ecx */
	m->ecx = M32((DWORD)(0x4a962cu));	/* 453bae: mov ecx, dword ptr [0x4a962c] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 453bb4: mov dword ptr [esp + 0x28], ecx */
	m->edi = (DWORD)(m->esp + 0x7cu);	/* 453bb8: lea edi, [esp + 0x7c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 453bbc: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453bbf: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 453bc1: repne scasb al, byte ptr es:[edi] */
	m->edx = M32((DWORD)(0xa0bad8u));	/* 453bc3: mov edx, dword ptr [0xa0bad8] */
	m->eax = M32((DWORD)(0xa0b398u));	/* 453bc9: mov eax, dword ptr [0xa0b398] */
	m->ecx = ~m->ecx;	/* 453bce: not ecx */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 453bd0: mov dword ptr [esp + 0x34], ecx */
	m->ecx = (DWORD)(m->esp + 0x7cu);	/* 453bd4: lea ecx, [esp + 0x7c] */
	M32((DWORD)(m->esp + 0x38u)) = m->ecx;	/* 453bd8: mov dword ptr [esp + 0x38], ecx */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 453bdc: lea ecx, [esp + 8] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 453be0: mov dword ptr [esp + 0x20], edx */
	m->edx = M32((DWORD)(0x4a9630u));	/* 453be4: mov edx, dword ptr [0x4a9630] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453bea: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453beb: push 0 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 453bed: lea ecx, [esp + 0x14] */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 453bf1: mov dword ptr [esp + 0x34], edx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 453bf5: mov edx, dword ptr [eax] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 453bf7: push 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453bf9: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453bfa: push eax */
	m->esp -= 4; M32(m->esp) = 0x453bfeu; native_call(m, M32((DWORD)(m->edx + 0x38u)));	/* 453bfb: call dword ptr [edx + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 453bfe: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453c02: push edx */
	m->esp -= 4; M32(m->esp) = 0x453c08u; native_call(m, 0x49eeb0u);	/* 453c03: call 0x49eeb0 */
	m->ecx = M32((DWORD)(0xa0b398u));	/* 453c08: mov ecx, dword ptr [0xa0b398] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453c0e: add esp, 4 */
	m->esi = (DWORD)(m->esp + 0x8u);	/* 453c11: lea esi, [esp + 8] */
	M32((DWORD)(0xa0baf0u)) = m->eax;	/* 453c15: mov dword ptr [0xa0baf0], eax */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 453c1a: mov edx, dword ptr [ecx] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453c1c: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453c1d: push eax */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 453c1e: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 453c22: push 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453c24: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453c25: push ecx */
	m->esp -= 4; M32(m->esp) = 0x453c29u; native_call(m, M32((DWORD)(m->edx + 0x38u)));	/* 453c26: call dword ptr [edx + 0x38] */
	m->ecx = M32((DWORD)(0xa0baf0u));	/* 453c29: mov ecx, dword ptr [0xa0baf0] */
	m->esi = M32(m->esp); m->esp += 4;	/* 453c2f: pop esi */
	M32((DWORD)(0xa0badcu)) = m->ecx;	/* 453c30: mov dword ptr [0xa0badc], ecx */
L_453c36:
	m->eax = M32((DWORD)(0xa0badcu));	/* 453c36: mov eax, dword ptr [0xa0badc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453c3b: test eax, eax */
	if (m->zf) goto L_453ccf;	/* 453c3d: je 0x453ccf */
	{ DWORD v_ = 0xa0b404u; m->esp -= 4; M32(m->esp) = v_; }	/* 453c43: push 0xa0b404 */
	m->esp -= 4; M32(m->esp) = 0x453c4du; native_call(m, 0x4539f0u);	/* 453c48: call 0x4539f0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453c4d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453c50: test eax, eax */
	if (m->sf != m->of) goto L_453ca8;	/* 453c52: jl 0x453ca8 */
	m->eax = M32((DWORD)(0xa0b404u));	/* 453c54: mov eax, dword ptr [0xa0b404] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453c59: test eax, eax */
	if (m->zf) goto L_453ca8;	/* 453c5b: je 0x453ca8 */
	m->ecx = M32((DWORD)(0xa0badcu));	/* 453c5d: mov ecx, dword ptr [0xa0badc] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 453c63: mov edx, dword ptr [eax] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453c65: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453c67: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453c68: push eax */
	m->esp -= 4; M32(m->esp) = 0x453c6fu; native_call(m, M32((DWORD)(m->edx + 0x98u)));	/* 453c69: call dword ptr [edx + 0x98] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453c6f: test eax, eax */
	if (m->sf == m->of) goto L_453c7d;	/* 453c71: jge 0x453c7d */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453c73: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 453c75: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x13cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453c76: add esp, 0x13c */
	m->esp += 4 + 0; return;	/* 453c7c: ret  */
L_453c7d:
	m->ecx = 0xau;	/* 453c7d: mov ecx, 0xa */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453c82: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x50u);	/* 453c84: lea edi, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 453c88: push 0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 453c8a: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0xa0b404u));	/* 453c8c: mov eax, dword ptr [0xa0b404] */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 453c91: lea ecx, [esp + 0x54] */
	M32((DWORD)(m->esp + 0x54u)) = 0x28u;	/* 453c95: mov dword ptr [esp + 0x54], 0x28 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453c9d: push ecx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 453c9e: mov edx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453ca0: push eax */
	m->esp -= 4; M32(m->esp) = 0x453ca4u; native_call(m, M32((DWORD)(m->edx + 0x38u)));	/* 453ca1: call dword ptr [edx + 0x38] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453ca4: test eax, eax */
	if (m->zf) goto L_453cb2;	/* 453ca6: je 0x453cb2 */
L_453ca8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453ca8: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 453caa: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x13cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453cab: add esp, 0x13c */
	m->esp += 4 + 0; return;	/* 453cb1: ret  */
L_453cb2:
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 453cb2: mov edx, dword ptr [esp + 0x74] */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 453cb6: mov eax, dword ptr [esp + 0x58] */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 453cba: mov ecx, dword ptr [esp + 0x5c] */
	M32((DWORD)(0xa0bb00u)) = m->edx;	/* 453cbe: mov dword ptr [0xa0bb00], edx */
	M32((DWORD)(0xa0bb04u)) = m->eax;	/* 453cc4: mov dword ptr [0xa0bb04], eax */
	M32((DWORD)(0xa0bb08u)) = m->ecx;	/* 453cc9: mov dword ptr [0xa0bb08], ecx */
L_453ccf:
	m->eax = 0x1u;	/* 453ccf: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 453cd4: pop edi */
	{ DWORD a_ = m->esp, b_ = 0x13cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453cd5: add esp, 0x13c */
	m->esp += 4 + 0; return;	/* 453cdb: ret  */
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
