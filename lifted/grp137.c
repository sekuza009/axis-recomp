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

static void lift_41d600(X86 *m);
static void lift_41d8a0(X86 *m);
static void lift_40e5d0(X86 *m);

/* armc_40e5d0 (0x40e5d0), lifted by tools/lift.py */
static void lift_40e5d0(X86 *m)
{
	m->ecx = M32((DWORD)(0x9087b4u));	/* 40e5d0: mov ecx, dword ptr [0x9087b4] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40e5d6: push 2 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40e5d8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40e5dfu; native_call(m, 0x460cb0u);	/* 40e5da: call 0x460cb0 */
	m->eax = M32((DWORD)(0x4dcb1cu));	/* 40e5df: mov eax, dword ptr [0x4dcb1c] */
	m->ecx = M32((DWORD)(0x4dcb18u));	/* 40e5e4: mov ecx, dword ptr [0x4dcb18] */
	m->edx = M32((DWORD)(0x4dcb2cu));	/* 40e5ea: mov edx, dword ptr [0x4dcb2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40e5f0: push eax */
	m->eax = M32((DWORD)(0x4dcb28u));	/* 40e5f1: mov eax, dword ptr [0x4dcb28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e5f6: push ecx */
	m->ecx = M32((DWORD)(0x4dcb24u));	/* 40e5f7: mov ecx, dword ptr [0x4dcb24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e5fd: push edx */
	m->edx = M32((DWORD)(0x4dcb20u));	/* 40e5fe: mov edx, dword ptr [0x4dcb20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40e604: push eax */
	m->eax = M32((DWORD)(0x4dc770u));	/* 40e605: mov eax, dword ptr [0x4dc770] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e60a: push ecx */
	m->ecx = M32((DWORD)(0x4dc76cu));	/* 40e60b: mov ecx, dword ptr [0x4dc76c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e611: push edx */
	m->edx = M32((DWORD)(0x4dc768u));	/* 40e612: mov edx, dword ptr [0x4dc768] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40e618: push eax */
	m->eax = M32((DWORD)(0x4dc764u));	/* 40e619: mov eax, dword ptr [0x4dc764] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e61e: push ecx */
	m->ecx = M32((DWORD)(0x4dc760u));	/* 40e61f: mov ecx, dword ptr [0x4dc760] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e625: push edx */
	m->edx = M32((DWORD)(0x9f1818u));	/* 40e626: mov edx, dword ptr [0x9f1818] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40e62c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e62d: push ecx */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 40e62e: mov ecx, dword ptr [0x9087b4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40e634: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e636: push edx */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40e637: push 0x4dedb0 */
	m->esp -= 4; M32(m->esp) = 0x40e641u; native_call(m, 0x461250u);	/* 40e63c: call 0x461250 */
	m->eax = M32((DWORD)(0x9087b4u));	/* 40e641: mov eax, dword ptr [0x9087b4] */
	m->ecx = (DWORD)(m->eax + 0x1f36c8u);	/* 40e646: lea ecx, [eax + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x40e651u; native_call(m, 0x45ddc0u);	/* 40e64c: call 0x45ddc0 */
	m->eax = 0x1u;	/* 40e651: mov eax, 1 */
	M32((DWORD)(0x4dbc68u)) = m->eax;	/* 40e656: mov dword ptr [0x4dbc68], eax */
	M32((DWORD)(0x4dc54cu)) = m->eax;	/* 40e65b: mov dword ptr [0x4dc54c], eax */
	M32((DWORD)(0x4dd074u)) = m->eax;	/* 40e660: mov dword ptr [0x4dd074], eax */
	m->esp += 4 + 0; return;	/* 40e665: ret  */
}

/* armc_41d600 (0x41d600), lifted by tools/lift.py */
static void lift_41d600(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d600: sub esp, 0x24 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d603: push 1 */
	m->esp -= 4; M32(m->esp) = 0x41d60au; native_call(m, 0x41ef90u);	/* 41d605: call 0x41ef90 */
	m->eax = M32((DWORD)(0x4dcc58u));	/* 41d60a: mov eax, dword ptr [0x4dcc58] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d60f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d612: cmp eax, 1 */
	if (!m->zf) goto L_41d6b7;	/* 41d615: jne 0x41d6b7 */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 41d61b: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d620: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_41d68c;	/* 41d623: ja 0x41d68c */
	switch (m->eax) { case 0: goto L_41d62c; case 1: goto L_41d63f; case 2: goto L_41d653; case 3: goto L_41d667; case 4: goto L_41d67a; default: abort(); }	/* 41d625: jmp dword ptr [eax*4 + 0x41d88c] */
L_41d62c:
	m->eax = M32((DWORD)(0x4dc760u));	/* 41d62c: mov eax, dword ptr [0x4dc760] */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41d631: mov ecx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d637: push eax */
	m->esp -= 4; M32(m->esp) = 0x41d63du; native_call(m, 0x4613d0u);	/* 41d638: call 0x4613d0 */
	goto L_41d68c;	/* 41d63d: jmp 0x41d68c */
L_41d63f:
	m->ecx = M32((DWORD)(0x4dc764u));	/* 41d63f: mov ecx, dword ptr [0x4dc764] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d645: push ecx */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41d646: mov ecx, dword ptr [0x9087b4] */
	m->esp -= 4; M32(m->esp) = 0x41d651u; native_call(m, 0x461410u);	/* 41d64c: call 0x461410 */
	goto L_41d68c;	/* 41d651: jmp 0x41d68c */
L_41d653:
	m->edx = M32((DWORD)(0x4dc768u));	/* 41d653: mov edx, dword ptr [0x4dc768] */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41d659: mov ecx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d65f: push edx */
	m->esp -= 4; M32(m->esp) = 0x41d665u; native_call(m, 0x461450u);	/* 41d660: call 0x461450 */
	goto L_41d68c;	/* 41d665: jmp 0x41d68c */
L_41d667:
	m->eax = M32((DWORD)(0x4dc76cu));	/* 41d667: mov eax, dword ptr [0x4dc76c] */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41d66c: mov ecx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d672: push eax */
	m->esp -= 4; M32(m->esp) = 0x41d678u; native_call(m, 0x461490u);	/* 41d673: call 0x461490 */
	goto L_41d68c;	/* 41d678: jmp 0x41d68c */
L_41d67a:
	m->ecx = M32((DWORD)(0x4dc770u));	/* 41d67a: mov ecx, dword ptr [0x4dc770] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d680: push ecx */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41d681: mov ecx, dword ptr [0x9087b4] */
	m->esp -= 4; M32(m->esp) = 0x41d68cu; native_call(m, 0x4614d0u);	/* 41d687: call 0x4614d0 */
L_41d68c:
	m->esp -= 4; M32(m->esp) = 0x41d691u; native_call(m, 0x41b750u);	/* 41d68c: call 0x41b750 */
	m->edx = M32((DWORD)(0x4dbe48u));	/* 41d691: mov edx, dword ptr [0x4dbe48] */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41d697: mov ecx, dword ptr [0x9087b4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d69d: push edx */
	m->esp -= 4; M32(m->esp) = 0x41d6a3u; native_call(m, 0x461540u);	/* 41d69e: call 0x461540 */
	m->esp -= 4; M32(m->esp) = 0x41d6a8u; native_call(m, 0x41c510u);	/* 41d6a3: call 0x41c510 */
	M32((DWORD)(0x4dcc58u)) = 0x0u;	/* 41d6a8: mov dword ptr [0x4dcc58], 0 */
	m->esp -= 4; M32(m->esp) = 0x41d6b7u; native_call(m, 0x41d280u);	/* 41d6b2: call 0x41d280 */
L_41d6b7:
	{ DWORD a_ = M32((DWORD)(0x4dbc80u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d6b7: cmp dword ptr [0x4dbc80], 1 */
	if (!m->zf) goto L_41d6ca;	/* 41d6be: jne 0x41d6ca */
	M32((DWORD)(0x4dbc80u)) = 0x0u;	/* 41d6c0: mov dword ptr [0x4dbc80], 0 */
L_41d6ca:
	m->eax = M32((DWORD)(0x4dca98u));	/* 41d6ca: mov eax, dword ptr [0x4dca98] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41d6cf: test eax, eax */
	if (m->zf) goto L_41d6e2;	/* 41d6d1: je 0x41d6e2 */
	m->esp -= 4; M32(m->esp) = 0x41d6d8u; native_call(m, 0x41cf20u);	/* 41d6d3: call 0x41cf20 */
	M32((DWORD)(0x4dca98u)) = 0x0u;	/* 41d6d8: mov dword ptr [0x4dca98], 0 */
L_41d6e2:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41d6e2: push esi */
	m->esi = M32((DWORD)(0x4a91fcu));	/* 41d6e3: mov esi, dword ptr [0x4a91fc] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d6e9: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x41d6f0u; native_call(m, m->esi);	/* 41d6ee: call esi */
	m->esp -= 4; M32(m->esp) = 0x41d6f6u; native_call(m, M32(0x4a9218u));	/* 41d6f0: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 41d6f6: fld dword ptr [0x4e1870] */
	{ DWORD v_ = 0x40d38800u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d6fc: push 0x40d38800 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d701: push 0 */
	{ DWORD v_ = 0x40590000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d703: push 0x40590000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d708: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d70a: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41d70d: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 41d710: fld dword ptr [0x68038c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d716: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41d719: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x41d721u; native_call(m, 0x4509c6u);	/* 41d71c: call 0x4509c6 */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d721: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x41d72cu; native_call(m, M32(0x4a9224u));	/* 41d726: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d72c: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x41d733u; native_call(m, m->esi);	/* 41d731: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41d733: fld dword ptr [0x4dbc04] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 41d739: fmul dword ptr [0x4a93ec] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d73f: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d741: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41d742: fstp dword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d745: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41d74cu; native_call(m, 0x41ef20u);	/* 41d747: call 0x41ef20 */
	m->eax = M32((DWORD)(0xa0e7a8u));	/* 41d74c: mov eax, dword ptr [0xa0e7a8] */
	m->ecx = M32((DWORD)(0xa0e7acu));	/* 41d751: mov ecx, dword ptr [0xa0e7ac] */
	m->edx = M32((DWORD)(0xa0e7b0u));	/* 41d757: mov edx, dword ptr [0xa0e7b0] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 41d75d: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(0x4dc798u));	/* 41d761: mov eax, dword ptr [0x4dc798] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d766: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d769: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 41d76c: mov dword ptr [esp + 0x20], ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 41d770: mov dword ptr [esp + 0x24], edx */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 41d774: mov dword ptr [esp + 0x10], 0 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 41d77c: mov dword ptr [esp + 0x14], 0 */
	M32((DWORD)(m->esp + 0x18u)) = 0xbf800000u;	/* 41d784: mov dword ptr [esp + 0x18], 0xbf800000 */
	M32((DWORD)(m->esp + 0x4u)) = 0x0u;	/* 41d78c: mov dword ptr [esp + 4], 0 */
	M32((DWORD)(m->esp + 0x8u)) = 0x3f800000u;	/* 41d794: mov dword ptr [esp + 8], 0x3f800000 */
	M32((DWORD)(m->esp + 0xcu)) = 0x0u;	/* 41d79c: mov dword ptr [esp + 0xc], 0 */
	if (m->zf) goto L_41d7e1;	/* 41d7a4: je 0x41d7e1 */
	if (m->zf || m->sf != m->of) goto L_41d84d;	/* 41d7a6: jle 0x41d84d */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d7ac: cmp eax, 3 */
	if (!m->zf && m->sf == m->of) goto L_41d84d;	/* 41d7af: jg 0x41d84d */
	m->eax = M32((DWORD)(0x4e045cu));	/* 41d7b5: mov eax, dword ptr [0x4e045c] */
	m->ecx = M32((DWORD)(0x5b1998u));	/* 41d7ba: mov ecx, dword ptr [0x5b1998] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41d7c0: fld dword ptr [0x4dbc04] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7c6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7c7: push ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41d7c8: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7cd: push eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 41d7ce: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7d2: push -1 */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 41d7d4: lea eax, [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7d8: push edx */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 41d7d9: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7dd: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7de: push ecx */
	goto L_41d842;	/* 41d7df: jmp 0x41d842 */
L_41d7e1:
	m->esi = M32((DWORD)(0x4dbc6cu));	/* 41d7e1: mov esi, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d7e7: cmp esi, 5 */
	if (!m->zf) goto L_41d818;	/* 41d7ea: jne 0x41d818 */
	m->edx = M32((DWORD)(0x4e045cu));	/* 41d7ec: mov edx, dword ptr [0x4e045c] */
	m->eax = M32((DWORD)(0x5b1998u));	/* 41d7f2: mov eax, dword ptr [0x5b1998] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41d7f7: fld dword ptr [0x4dbc04] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7fd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d7fe: push eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41d7ff: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d804: push eax */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 41d805: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 41d809: push -1 */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 41d80b: lea edx, [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d80f: push ecx */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 41d810: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d814: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d815: push eax */
	goto L_41d842;	/* 41d816: jmp 0x41d842 */
L_41d818:
	m->ecx = M32((DWORD)(0x4e045cu));	/* 41d818: mov ecx, dword ptr [0x4e045c] */
	m->edx = M32((DWORD)(0x5b1998u));	/* 41d81e: mov edx, dword ptr [0x5b1998] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41d824: fld dword ptr [0x4dbc04] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d82a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d82b: push edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41d82c: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d831: push eax */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 41d832: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41d836: push esi */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 41d837: lea ecx, [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d83b: push eax */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 41d83c: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d840: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d841: push edx */
L_41d842:
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41d842: mov ecx, dword ptr [0x9087b4] */
	m->esp -= 4; M32(m->esp) = 0x41d84du; native_call(m, 0x461850u);	/* 41d848: call 0x461850 */
L_41d84d:
	m->eax = M32((DWORD)(0x4dceacu));	/* 41d84d: mov eax, dword ptr [0x4dceac] */
	m->esi = M32(m->esp); m->esp += 4;	/* 41d852: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41d853: test eax, eax */
	if (m->zf) goto L_41d886;	/* 41d855: je 0x41d886 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41d857: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 41d85d: fmul dword ptr [0x4a94cc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dbc04u));	/* 41d863: fadd dword ptr [0x4dbc04] */
	MF((DWORD)(0x4dbc04u)) = (float)ST(0);	/* 41d869: fst dword ptr [0x4dbc04] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94c8u)); FPOP();	/* 41d86f: fcomp dword ptr [0x4a94c8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41d875: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41d877: test ah, 1 */
	if (!m->zf) goto L_41d886;	/* 41d87a: jne 0x41d886 */
	M32((DWORD)(0x4dbc04u)) = 0x0u;	/* 41d87c: mov dword ptr [0x4dbc04], 0 */
L_41d886:
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d886: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 41d889: ret  */
}

/* armc_41d8a0 (0x41d8a0), lifted by tools/lift.py */
static void lift_41d8a0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d8a0: sub esp, 0x24 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8a3: push 1 */
	m->esp -= 4; M32(m->esp) = 0x41d8aau; native_call(m, 0x41ef90u);	/* 41d8a5: call 0x41ef90 */
	m->eax = M32((DWORD)(0x4dbc80u));	/* 41d8aa: mov eax, dword ptr [0x4dbc80] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d8af: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d8b2: cmp eax, 1 */
	if (!m->zf) goto L_41d8cd;	/* 41d8b5: jne 0x41d8cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8b7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8b9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41d8c0u; native_call(m, 0x41ca50u);	/* 41d8bb: call 0x41ca50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d8c0: add esp, 8 */
	M32((DWORD)(0x4dbc80u)) = 0x0u;	/* 41d8c3: mov dword ptr [0x4dbc80], 0 */
L_41d8cd:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8cd: push esi */
	m->esi = M32((DWORD)(0x4a91fcu));	/* 41d8ce: mov esi, dword ptr [0x4a91fc] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8d4: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x41d8dbu; native_call(m, m->esi);	/* 41d8d9: call esi */
	m->esp -= 4; M32(m->esp) = 0x41d8e1u; native_call(m, M32(0x4a9218u));	/* 41d8db: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 41d8e1: fld dword ptr [0x4e1870] */
	{ DWORD v_ = 0x40d38800u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8e7: push 0x40d38800 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8ec: push 0 */
	{ DWORD v_ = 0x40590000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8ee: push 0x40590000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d8f3: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d8f5: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41d8f8: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 41d8fb: fld dword ptr [0x68038c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d901: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41d904: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x41d90cu; native_call(m, 0x4509c6u);	/* 41d907: call 0x4509c6 */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d90c: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x41d917u; native_call(m, M32(0x4a9224u));	/* 41d911: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d917: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x41d91eu; native_call(m, m->esi);	/* 41d91c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41d91e: fld dword ptr [0x4dbc04] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 41d924: fmul dword ptr [0x4a93ec] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d92a: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d92c: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41d92d: fstp dword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d930: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41d937u; native_call(m, 0x41ef20u);	/* 41d932: call 0x41ef20 */
	m->eax = M32((DWORD)(0xa0e7a8u));	/* 41d937: mov eax, dword ptr [0xa0e7a8] */
	m->ecx = M32((DWORD)(0xa0e7acu));	/* 41d93c: mov ecx, dword ptr [0xa0e7ac] */
	m->edx = M32((DWORD)(0xa0e7b0u));	/* 41d942: mov edx, dword ptr [0xa0e7b0] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 41d948: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(0x4dc798u));	/* 41d94c: mov eax, dword ptr [0x4dc798] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41d951: add esp, 0xc */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41d954: dec eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 41d955: mov dword ptr [esp + 0x20], ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 41d959: mov dword ptr [esp + 0x24], edx */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 41d95d: mov dword ptr [esp + 0x10], 0 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 41d965: mov dword ptr [esp + 0x14], 0 */
	M32((DWORD)(m->esp + 0x18u)) = 0xbf800000u;	/* 41d96d: mov dword ptr [esp + 0x18], 0xbf800000 */
	M32((DWORD)(m->esp + 0x4u)) = 0x0u;	/* 41d975: mov dword ptr [esp + 4], 0 */
	M32((DWORD)(m->esp + 0x8u)) = 0x3f800000u;	/* 41d97d: mov dword ptr [esp + 8], 0x3f800000 */
	M32((DWORD)(m->esp + 0xcu)) = 0x0u;	/* 41d985: mov dword ptr [esp + 0xc], 0 */
	if (m->zf) goto L_41d9ff;	/* 41d98d: je 0x41d9ff */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41d98f: dec eax */
	if (m->zf) goto L_41d99b;	/* 41d990: je 0x41d99b */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41d992: dec eax */
	if (!m->zf) goto L_41da6a;	/* 41d993: jne 0x41da6a */
	goto L_41da0a;	/* 41d999: jmp 0x41da0a */
L_41d99b:
	m->esi = M32((DWORD)(0x4dbe48u));	/* 41d99b: mov esi, dword ptr [0x4dbe48] */
	m->edx = m->esi;	/* 41d9a1: mov edx, esi */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 41d9a3: shl edx, 7 */
	{ DWORD a_ = M32((DWORD)(m->edx + 0x4dbe90u)), b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d9a6: cmp dword ptr [edx + 0x4dbe90], -1 */
	if (m->zf) goto L_41da0a;	/* 41d9ad: je 0x41da0a */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41d9af: cmp esi, 3 */
	if (m->zf || m->sf != m->of) goto L_41d9d2;	/* 41d9b2: jle 0x41d9d2 */
	m->edx = M32((DWORD)(0x4e045cu));	/* 41d9b4: mov edx, dword ptr [0x4e045c] */
	m->eax = M32((DWORD)(0x5b1998u));	/* 41d9ba: mov eax, dword ptr [0x5b1998] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41d9bf: fld dword ptr [0x4dbc04] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9c5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9c6: push eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41d9c7: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9cc: push eax */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 41d9cd: add esi, 2 */
	goto L_41da4f;	/* 41d9d0: jmp 0x41da4f */
L_41d9d2:
	m->ecx = M32((DWORD)(0x4e045cu));	/* 41d9d2: mov ecx, dword ptr [0x4e045c] */
	m->edx = M32((DWORD)(0x5b1998u));	/* 41d9d8: mov edx, dword ptr [0x5b1998] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41d9de: fld dword ptr [0x4dbc04] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9e4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9e5: push edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41d9e6: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9eb: push eax */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 41d9ec: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9f0: push 5 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 41d9f2: lea ecx, [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9f6: push eax */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 41d9f7: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9fb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41d9fc: push edx */
	goto L_41da5f;	/* 41d9fd: jmp 0x41da5f */
L_41d9ff:
	m->esi = M32((DWORD)(0x4dbc6cu));	/* 41d9ff: mov esi, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41da05: cmp esi, 5 */
	if (!m->zf) goto L_41da36;	/* 41da08: jne 0x41da36 */
L_41da0a:
	m->eax = M32((DWORD)(0x4e045cu));	/* 41da0a: mov eax, dword ptr [0x4e045c] */
	m->ecx = M32((DWORD)(0x5b1998u));	/* 41da0f: mov ecx, dword ptr [0x5b1998] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41da15: fld dword ptr [0x4dbc04] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41da1b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41da1c: push ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41da1d: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41da22: push eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 41da23: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 41da27: push -1 */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 41da29: lea eax, [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41da2d: push edx */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 41da2e: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41da32: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41da33: push ecx */
	goto L_41da5f;	/* 41da34: jmp 0x41da5f */
L_41da36:
	m->edx = M32((DWORD)(0x4e045cu));	/* 41da36: mov edx, dword ptr [0x4e045c] */
	m->eax = M32((DWORD)(0x5b1998u));	/* 41da3c: mov eax, dword ptr [0x5b1998] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dbc04u)));	/* 41da41: fld dword ptr [0x4dbc04] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41da47: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41da48: push eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 41da49: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41da4e: push eax */
L_41da4f:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 41da4f: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41da53: push esi */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 41da54: lea edx, [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41da58: push ecx */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 41da59: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41da5d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41da5e: push eax */
L_41da5f:
	m->ecx = M32((DWORD)(0x9087b4u));	/* 41da5f: mov ecx, dword ptr [0x9087b4] */
	m->esp -= 4; M32(m->esp) = 0x41da6au; native_call(m, 0x461850u);	/* 41da65: call 0x461850 */
L_41da6a:
	m->eax = M32((DWORD)(0x4dceacu));	/* 41da6a: mov eax, dword ptr [0x4dceac] */
	m->esi = M32(m->esp); m->esp += 4;	/* 41da6f: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41da70: test eax, eax */
	if (m->zf) goto L_41daa3;	/* 41da72: je 0x41daa3 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41da74: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 41da7a: fmul dword ptr [0x4a94cc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dbc04u));	/* 41da80: fadd dword ptr [0x4dbc04] */
	MF((DWORD)(0x4dbc04u)) = (float)ST(0);	/* 41da86: fst dword ptr [0x4dbc04] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94c8u)); FPOP();	/* 41da8c: fcomp dword ptr [0x4a94c8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41da92: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41da94: test ah, 1 */
	if (!m->zf) goto L_41daa3;	/* 41da97: jne 0x41daa3 */
	M32((DWORD)(0x4dbc04u)) = 0x0u;	/* 41da99: mov dword ptr [0x4dbc04], 0 */
L_41daa3:
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41daa3: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 41daa6: ret  */
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
