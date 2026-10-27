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

static void lift_447a50(X86 *m);
static void lift_444070(X86 *m);
static void lift_434320(X86 *m);
static void lift_405010(X86 *m);
static void lift_443f20(X86 *m);
static void lift_4479d0(X86 *m);
static void lift_443ef0(X86 *m);
static void lift_447b10(X86 *m);
static void lift_4440f0(X86 *m);
static void lift_405200(X86 *m);
static void lift_434da0(X86 *m);
static void lift_443e20(X86 *m);

/* skirmish_saveSettings (0x443e20), lifted by tools/lift.py */
static void lift_443e20(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 443e20: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 443e25: test eax, eax */
	if (!m->zf) goto L_443e72;	/* 443e27: jne 0x443e72 */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 443e29: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 443e2e: test eax, eax */
	if (m->zf) goto L_443e37;	/* 443e30: je 0x443e37 */
	m->esp -= 4; M32(m->esp) = 0x443e37u; native_call(m, 0x443c80u);	/* 443e32: call 0x443c80 */
L_443e37:
	m->eax = M32((DWORD)(0x4ded88u));	/* 443e37: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 443e3c: test eax, eax */
	if (m->zf) goto L_443e72;	/* 443e3e: je 0x443e72 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 443e40: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 443e45: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443e4b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443e4c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443e52u; native_call(m, 0x4438d0u);	/* 443e4d: call 0x4438d0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443e52: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443e55: cmp eax, 9 */
	if (!m->cf && !m->zf) goto L_443e72;	/* 443e58: ja 0x443e72 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 443e5a: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x443e94u))) & 0xff) << 0);	/* 443e5c: mov dl, byte ptr [eax + 0x443e94] */
	switch (m->edx) { case 0: goto L_443e69; case 1: goto L_443e73; case 2: goto L_443e82; default: abort(); }	/* 443e62: jmp dword ptr [edx*4 + 0x443e88] */
L_443e69:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443e69: push eax */
	m->esp -= 4; M32(m->esp) = 0x443e6fu; native_call(m, 0x443d50u);	/* 443e6a: call 0x443d50 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443e6f: add esp, 4 */
L_443e72:
	m->esp += 4 + 0; return;	/* 443e72: ret  */
L_443e73:
	m->eax = M32((DWORD)(0x9f16a4u));	/* 443e73: mov eax, dword ptr [0x9f16a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443e78: push eax */
	m->esp -= 4; M32(m->esp) = 0x443e7eu; native_call(m, 0x443af0u);	/* 443e79: call 0x443af0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443e7e: add esp, 4 */
	m->esp += 4 + 0; return;	/* 443e81: ret  */
L_443e82:
	native_call(m, 0x443c80u); return;	/* 443e82: jmp 0x443c80 */
}

/* mission_447a50 (0x447a50), lifted by tools/lift.py */
static void lift_447a50(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 447a50: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447a55: test eax, eax */
	if (!m->zf) goto L_447ad5;	/* 447a57: jne 0x447ad5 */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 447a59: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447a5e: test eax, eax */
	if (m->zf) goto L_447a67;	/* 447a60: je 0x447a67 */
	m->esp -= 4; M32(m->esp) = 0x447a67u; native_call(m, 0x447960u);	/* 447a62: call 0x447960 */
L_447a67:
	m->eax = M32((DWORD)(0x4ded88u));	/* 447a67: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447a6c: test eax, eax */
	if (m->zf) goto L_447ad5;	/* 447a6e: je 0x447ad5 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 447a70: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 447a75: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447a7b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 447a7c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x447a82u; native_call(m, 0x447710u);	/* 447a7d: call 0x447710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447a82: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447a85: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_447ad5;	/* 447a88: ja 0x447ad5 */
	switch (m->eax) { case 0: goto L_447a91; case 1: goto L_447a96; case 2: goto L_447a9b; case 3: goto L_447ab4; default: abort(); }	/* 447a8a: jmp dword ptr [eax*4 + 0x447ad8] */
L_447a91:
	lift_4479d0(m); return;	/* 447a91: jmp 0x4479d0 */
L_447a96:
	native_call(m, 0x447960u); return;	/* 447a96: jmp 0x447960 */
L_447a9b:
	m->eax = M32((DWORD)(0x9f63b4u));	/* 447a9b: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447aa0: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_447ad5;	/* 447aa2: jle 0x447ad5 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 447aa4: dec eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447aa5: push eax */
	M32((DWORD)(0x9f63b4u)) = m->eax;	/* 447aa6: mov dword ptr [0x9f63b4], eax */
	m->esp -= 4; M32(m->esp) = 0x447ab0u; native_call(m, 0x4479b0u);	/* 447aab: call 0x4479b0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447ab0: add esp, 4 */
	m->esp += 4 + 0; return;	/* 447ab3: ret  */
L_447ab4:
	m->eax = M32((DWORD)(0x9f63b4u));	/* 447ab4: mov eax, dword ptr [0x9f63b4] */
	m->ecx = M32((DWORD)(0x9f181cu));	/* 447ab9: mov ecx, dword ptr [0x9f181c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447abf: cmp eax, ecx */
	if (m->sf == m->of) goto L_447ad5;	/* 447ac1: jge 0x447ad5 */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447ac3: cmp eax, 0xe */
	if (m->sf == m->of) goto L_447ad5;	/* 447ac6: jge 0x447ad5 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 447ac8: inc eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447ac9: push eax */
	M32((DWORD)(0x9f63b4u)) = m->eax;	/* 447aca: mov dword ptr [0x9f63b4], eax */
	m->esp -= 4; M32(m->esp) = 0x447ad4u; native_call(m, 0x4479b0u);	/* 447acf: call 0x4479b0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 447ad4: pop ecx */
L_447ad5:
	m->esp += 4 + 0; return;	/* 447ad5: ret  */
}

/* menu_444070 (0x444070), lifted by tools/lift.py */
static void lift_444070(X86 *m)
{
	m->eax = M32((DWORD)(0x4e0cd4u));	/* 444070: mov eax, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444075: push eax */
	m->esp -= 4; M32(m->esp) = 0x44407bu; native_call(m, 0x401600u);	/* 444076: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44407b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44407e: cmp eax, 1 */
	if (m->zf) goto L_4440e6;	/* 444081: je 0x4440e6 */
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 444083: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444089: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44408fu; native_call(m, 0x401600u);	/* 44408a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44408f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444092: cmp eax, 1 */
	if (m->zf) goto L_4440dc;	/* 444095: je 0x4440dc */
	m->edx = M32((DWORD)(0x76d48cu));	/* 444097: mov edx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44409d: push edx */
	m->esp -= 4; M32(m->esp) = 0x4440a3u; native_call(m, 0x401600u);	/* 44409e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4440a3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4440a6: cmp eax, 1 */
	if (m->zf) goto L_4440dc;	/* 4440a9: je 0x4440dc */
	m->eax = M32((DWORD)(0x4e150cu));	/* 4440ab: mov eax, dword ptr [0x4e150c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4440b0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4440b6u; native_call(m, 0x401600u);	/* 4440b1: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4440b6: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4440b9: cmp eax, 1 */
	if (!m->zf) goto L_4440c3;	/* 4440bc: jne 0x4440c3 */
	native_call(m, 0x443d80u); return;	/* 4440be: jmp 0x443d80 */
L_4440c3:
	m->ecx = M32((DWORD)(0x4e1514u));	/* 4440c3: mov ecx, dword ptr [0x4e1514] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4440c9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4440cfu; native_call(m, 0x401600u);	/* 4440ca: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4440cf: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4440d2: cmp eax, 1 */
	if (!m->zf) goto L_4440e6;	/* 4440d5: jne 0x4440e6 */
	native_call(m, 0x443de0u); return;	/* 4440d7: jmp 0x443de0 */
L_4440dc:
	M32((DWORD)(0x9ef1f8u)) = 0xau;	/* 4440dc: mov dword ptr [0x9ef1f8], 0xa */
L_4440e6:
	m->esp += 4 + 0; return;	/* 4440e6: ret  */
}

/* room_434320 (0x434320), lifted by tools/lift.py */
static void lift_434320(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434320: push edi */
	m->esp -= 4; M32(m->esp) = 0x434326u; native_call(m, 0x401460u);	/* 434321: call 0x401460 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 434326: push 8 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 434328: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x434337u; native_call(m, 0x431560u);	/* 434332: call 0x431560 */
	m->ecx = 0x100u;	/* 434337: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43433c: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43433e: mov edi, 0x9dc92c */
	m->edx = M32((DWORD)(0x9dd4acu));	/* 434343: mov edx, dword ptr [0x9dd4ac] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 434349: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43434b: mov ecx, dword ptr [0x9dd4a8] */
	M32((DWORD)(0x9dcee8u)) = m->eax;	/* 434351: mov dword ptr [0x9dcee8], eax */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 434356: add ecx, 0xd8 */
	m->edi = 0x9dc92cu;	/* 43435c: mov edi, 0x9dc92c */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 434361: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434367: or ecx, 0xffffffff */
	{ DWORD a_ = m->edx, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43436a: add edx, 0xd0 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 434370: push 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434372: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434374: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 434376: dec ecx */
	M32((DWORD)(0x9dceecu)) = m->eax;	/* 434377: mov dword ptr [0x9dceec], eax */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 43437c: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 434386: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 43438c: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x9dd6c8u)) = 0x1u;	/* 434392: mov dword ptr [0x9dd6c8], 1 */
	m->esp -= 4; M32(m->esp) = 0x4343a1u; native_call(m, 0x43f460u);	/* 43439c: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4343a1: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4343a4: pop edi */
	m->esp += 4 + 0; return;	/* 4343a5: ret  */
}

/* arena_editTextField_405010 (0x405010), lifted by tools/lift.py */
static void lift_405010(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 405010: push edi */
	m->esp -= 4; M32(m->esp) = 0x405016u; native_call(m, 0x401460u);	/* 405011: call 0x401460 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 405016: push 8 */
	M32((DWORD)(0x68039cu)) = 0x1u;	/* 405018: mov dword ptr [0x68039c], 1 */
	m->esp -= 4; M32(m->esp) = 0x405027u; native_call(m, 0x431560u);	/* 405022: call 0x431560 */
	m->ecx = 0x100u;	/* 405027: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40502c: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 40502e: mov edi, 0x9dc92c */
	m->edx = M32((DWORD)(0x4db8ccu));	/* 405033: mov edx, dword ptr [0x4db8cc] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 405039: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x4db8c8u));	/* 40503b: mov ecx, dword ptr [0x4db8c8] */
	M32((DWORD)(0x4db520u)) = m->eax;	/* 405041: mov dword ptr [0x4db520], eax */
	{ DWORD a_ = m->ecx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 405046: add ecx, 0xd8 */
	m->edi = 0x9dc92cu;	/* 40504c: mov edi, 0x9dc92c */
	M32((DWORD)(0x9da3d8u)) = m->ecx;	/* 405051: mov dword ptr [0x9da3d8], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 405057: or ecx, 0xffffffff */
	{ DWORD a_ = m->edx, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40505a: add edx, 0xd0 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 405060: push 8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 405062: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 405064: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 405066: dec ecx */
	M32((DWORD)(0x4db524u)) = m->eax;	/* 405067: mov dword ptr [0x4db524], eax */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 40506c: mov dword ptr [0x9da434], 0x40a00000 */
	M32((DWORD)(0x9da3dcu)) = m->edx;	/* 405076: mov dword ptr [0x9da3dc], edx */
	M32((DWORD)(0x9dbf10u)) = m->ecx;	/* 40507c: mov dword ptr [0x9dbf10], ecx */
	M32((DWORD)(0x4db70cu)) = 0x1u;	/* 405082: mov dword ptr [0x4db70c], 1 */
	m->esp -= 4; M32(m->esp) = 0x405091u; native_call(m, 0x43f460u);	/* 40508c: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405091: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 405094: pop edi */
	m->esp += 4 + 0; return;	/* 405095: ret  */
}

/* skirmish_processKeys (0x443f20), lifted by tools/lift.py */
static void lift_443f20(X86 *m)
{
	m->eax = M32((DWORD)(0x4e0cd4u));	/* 443f20: mov eax, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443f25: push eax */
	m->esp -= 4; M32(m->esp) = 0x443f2bu; native_call(m, 0x401600u);	/* 443f26: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443f2b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443f2e: cmp eax, 1 */
	if (!m->zf) goto L_443f43;	/* 443f31: jne 0x443f43 */
	m->ecx = M32((DWORD)(0x9f16a4u));	/* 443f33: mov ecx, dword ptr [0x9f16a4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443f39: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443f3fu; native_call(m, 0x443af0u);	/* 443f3a: call 0x443af0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443f3f: add esp, 4 */
L_443f42:
	m->esp += 4 + 0; return;	/* 443f42: ret  */
L_443f43:
	m->edx = M32((DWORD)(0x9dae70u));	/* 443f43: mov edx, dword ptr [0x9dae70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443f49: push edx */
	m->esp -= 4; M32(m->esp) = 0x443f4fu; native_call(m, 0x401600u);	/* 443f4a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443f4f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443f52: cmp eax, 1 */
	if (!m->zf) goto L_443f66;	/* 443f55: jne 0x443f66 */
	m->eax = M32((DWORD)(0x9f16a4u));	/* 443f57: mov eax, dword ptr [0x9f16a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443f5c: push eax */
	m->esp -= 4; M32(m->esp) = 0x443f62u; native_call(m, 0x443af0u);	/* 443f5d: call 0x443af0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443f62: add esp, 4 */
	m->esp += 4 + 0; return;	/* 443f65: ret  */
L_443f66:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 443f66: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443f6c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443f72u; native_call(m, 0x401600u);	/* 443f6d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443f72: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443f75: cmp eax, 1 */
	if (!m->zf) goto L_443f7f;	/* 443f78: jne 0x443f7f */
	native_call(m, 0x443c80u); return;	/* 443f7a: jmp 0x443c80 */
L_443f7f:
	m->edx = M32((DWORD)(0x76d48cu));	/* 443f7f: mov edx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443f85: push edx */
	m->esp -= 4; M32(m->esp) = 0x443f8bu; native_call(m, 0x401600u);	/* 443f86: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443f8b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443f8e: cmp eax, 1 */
	if (!m->zf) goto L_443f98;	/* 443f91: jne 0x443f98 */
	native_call(m, 0x443c80u); return;	/* 443f93: jmp 0x443c80 */
L_443f98:
	m->eax = M32((DWORD)(0x9db0a0u));	/* 443f98: mov eax, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443f9d: push eax */
	m->esp -= 4; M32(m->esp) = 0x443fa3u; native_call(m, 0x401590u);	/* 443f9e: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443fa3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 443fa6: test eax, eax */
	if (!m->zf) goto L_443faf;	/* 443fa8: jne 0x443faf */
	M32((DWORD)(0x76d37cu)) = m->eax;	/* 443faa: mov dword ptr [0x76d37c], eax */
L_443faf:
	m->ecx = M32((DWORD)(0x9db0a0u));	/* 443faf: mov ecx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443fb5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443fbbu; native_call(m, 0x401590u);	/* 443fb6: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443fbb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443fbe: cmp eax, 1 */
	if (!m->zf) goto L_444002;	/* 443fc1: jne 0x444002 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d37cu)));	/* 443fc3: fld dword ptr [0x76d37c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 443fc9: fcomp dword ptr [0x4a93e8] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 443fcf: mov dword ptr [0x4dda44], 0 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 443fd9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 443fdb: test ah, 0x41 */
	if (!m->zf) goto L_443ff3;	/* 443fde: jne 0x443ff3 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d37cu)));	/* 443fe0: fld dword ptr [0x76d37c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 443fe6: fsub dword ptr [0x4b071c] */
	MF((DWORD)(0x76d37cu)) = (float)ST(0); FPOP();	/* 443fec: fstp dword ptr [0x76d37c] */
	m->esp += 4 + 0; return;	/* 443ff2: ret  */
L_443ff3:
	M32((DWORD)(0x76d37cu)) = 0x40800000u;	/* 443ff3: mov dword ptr [0x76d37c], 0x40800000 */
	native_call(m, 0x443cd0u); return;	/* 443ffd: jmp 0x443cd0 */
L_444002:
	m->edx = M32((DWORD)(0x76d330u));	/* 444002: mov edx, dword ptr [0x76d330] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444008: push edx */
	m->esp -= 4; M32(m->esp) = 0x44400eu; native_call(m, 0x401590u);	/* 444009: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44400e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 444011: test eax, eax */
	if (!m->zf) goto L_44401a;	/* 444013: jne 0x44401a */
	M32((DWORD)(0x680bb4u)) = m->eax;	/* 444015: mov dword ptr [0x680bb4], eax */
L_44401a:
	m->eax = M32((DWORD)(0x76d330u));	/* 44401a: mov eax, dword ptr [0x76d330] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44401f: push eax */
	m->esp -= 4; M32(m->esp) = 0x444025u; native_call(m, 0x401590u);	/* 444020: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 444025: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444028: cmp eax, 1 */
	if (!m->zf) goto L_443f42;	/* 44402b: jne 0x443f42 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bb4u)));	/* 444031: fld dword ptr [0x680bb4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 444037: fcomp dword ptr [0x4a93e8] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44403d: mov dword ptr [0x4dda44], 0 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 444047: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 444049: test ah, 0x41 */
	if (!m->zf) goto L_444061;	/* 44404c: jne 0x444061 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bb4u)));	/* 44404e: fld dword ptr [0x680bb4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 444054: fsub dword ptr [0x4b071c] */
	MF((DWORD)(0x680bb4u)) = (float)ST(0); FPOP();	/* 44405a: fstp dword ptr [0x680bb4] */
	m->esp += 4 + 0; return;	/* 444060: ret  */
L_444061:
	M32((DWORD)(0x680bb4u)) = 0x40800000u;	/* 444061: mov dword ptr [0x680bb4], 0x40800000 */
	native_call(m, 0x443d10u); return;	/* 44406b: jmp 0x443d10 */
}

/* mission_4479d0 (0x4479d0), lifted by tools/lift.py */
static void lift_4479d0(X86 *m)
{
	m->edx = M32((DWORD)(0x9f63b4u));	/* 4479d0: mov edx, dword ptr [0x9f63b4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4479d6: push esi */
	m->esi = m->edx;	/* 4479d7: mov esi, edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4479d9: push edi */
	m->eax = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 4479da: lea eax, [edx + edx*2] */
	m->ecx = 0x8u;	/* 4479dd: mov ecx, 8 */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4479e2: shl eax, 3 */
	{ DWORD a_ = m->esi, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4479e5: shl esi, 5 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4479e8: sub eax, edx */
	{ DWORD a_ = m->esi, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4479ea: add esi, 0x907b30 */
	m->edi = 0x67fb44u;	/* 4479f0: mov edi, 0x67fb44 */
	M32((DWORD)(0x9dad94u)) = m->edx;	/* 4479f5: mov dword ptr [0x9dad94], edx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4479fb: shl eax, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4479fe: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(m->eax + 0x9db9e4u));	/* 447a00: mov ecx, dword ptr [eax + 0x9db9e4] */
	m->edx = M32((DWORD)(m->eax + 0x9db9ecu));	/* 447a06: mov edx, dword ptr [eax + 0x9db9ec] */
	m->eax = M32((DWORD)(m->eax + 0x9db9e8u));	/* 447a0c: mov eax, dword ptr [eax + 0x9db9e8] */
	M32((DWORD)(0x9da3e0u)) = 0x0u;	/* 447a12: mov dword ptr [0x9da3e0], 0 */
	M32((DWORD)(0x76d368u)) = m->ecx;	/* 447a1c: mov dword ptr [0x76d368], ecx */
	M32((DWORD)(0x4df8e8u)) = m->edx;	/* 447a22: mov dword ptr [0x4df8e8], edx */
	M32((DWORD)(0x76d408u)) = m->eax;	/* 447a28: mov dword ptr [0x76d408], eax */
	m->esp -= 4; M32(m->esp) = 0x447a32u; native_call(m, 0x447960u);	/* 447a2d: call 0x447960 */
	m->edi = M32(m->esp); m->esp += 4;	/* 447a32: pop edi */
	M32((DWORD)(0x67ef14u)) = 0x1u;	/* 447a33: mov dword ptr [0x67ef14], 1 */
	M32((DWORD)(0x5ae9c4u)) = 0x3u;	/* 447a3d: mov dword ptr [0x5ae9c4], 3 */
	m->esi = M32(m->esp); m->esp += 4;	/* 447a47: pop esi */
	m->esp += 4 + 0; return;	/* 447a48: ret  */
}

/* menu_443ef0 (0x443ef0), lifted by tools/lift.py */
static void lift_443ef0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 443ef0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 443ef5: test eax, eax */
	if (!m->zf) goto L_443f12;	/* 443ef7: jne 0x443f12 */
	m->eax = M32((DWORD)(0x9ef1f8u));	/* 443ef9: mov eax, dword ptr [0x9ef1f8] */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443efe: cmp eax, 0xa */
	if (m->zf) goto L_443f0d;	/* 443f01: je 0x443f0d */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443f03: cmp eax, 0x14 */
	if (!m->zf) goto L_443f12;	/* 443f06: jne 0x443f12 */
	native_call(m, 0x443ea0u); return;	/* 443f08: jmp 0x443ea0 */
L_443f0d:
	lift_443e20(m); return;	/* 443f0d: jmp 0x443e20 */
L_443f12:
	m->esp += 4 + 0; return;	/* 443f12: ret  */
}

/* mission_unlockCheat (0x447b10), lifted by tools/lift.py */
static void lift_447b10(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 447b10: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447b15: test eax, eax */
	if (!m->zf) goto L_447b35;	/* 447b17: jne 0x447b35 */
	m->eax = M32((DWORD)(0x9f6300u));	/* 447b19: mov eax, dword ptr [0x9f6300] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447b1e: test eax, eax */
	if (!m->zf) goto L_447b35;	/* 447b20: jne 0x447b35 */
	m->eax = M32((DWORD)(0x9f62e0u));	/* 447b22: mov eax, dword ptr [0x9f62e0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447b27: test eax, eax */
	if (m->zf) goto L_447b30;	/* 447b29: je 0x447b30 */
	native_call(m, 0x447af0u); return;	/* 447b2b: jmp 0x447af0 */
L_447b30:
	lift_447a50(m); return;	/* 447b30: jmp 0x447a50 */
L_447b35:
	m->esp += 4 + 0; return;	/* 447b35: ret  */
}

/* menu_4440f0 (0x4440f0), lifted by tools/lift.py */
static void lift_4440f0(X86 *m)
{
	m->eax = M32((DWORD)(0x9ef1f0u));	/* 4440f0: mov eax, dword ptr [0x9ef1f0] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4440f5: cmp eax, 1 */
	if (m->zf) goto L_444120;	/* 4440f8: je 0x444120 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4440fa: test eax, eax */
	if (m->zf) goto L_444120;	/* 4440fc: je 0x444120 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 4440fe: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 444103: test eax, eax */
	if (!m->zf) goto L_444120;	/* 444105: jne 0x444120 */
	m->eax = M32((DWORD)(0x9ef1f8u));	/* 444107: mov eax, dword ptr [0x9ef1f8] */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44410c: cmp eax, 0xa */
	if (m->zf) goto L_44411b;	/* 44410f: je 0x44411b */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 444111: cmp eax, 0x14 */
	if (!m->zf) goto L_444120;	/* 444114: jne 0x444120 */
	lift_444070(m); return;	/* 444116: jmp 0x444070 */
L_44411b:
	lift_443f20(m); return;	/* 44411b: jmp 0x443f20 */
L_444120:
	m->esp += 4 + 0; return;	/* 444120: ret  */
}

/* FUN_00405200 (0x405200), lifted by tools/lift.py */
static void lift_405200(X86 *m)
{
	m->eax = M32((DWORD)(0x76d41cu));	/* 405200: mov eax, dword ptr [0x76d41c] */
	M32((DWORD)(0x4db8bcu)) = 0x0u;	/* 405205: mov dword ptr [0x4db8bc], 0 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 40520f: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 405212: lea edx, [eax + ecx*4] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx*2 + 0x908807u))) & 0xff) << 0);	/* 405215: mov al, byte ptr [edx*2 + 0x908807] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40521c: test al, al */
	if (m->zf) goto L_40522f;	/* 40521e: je 0x40522f */
	M32((DWORD)(0x4db8bcu)) = 0x1u;	/* 405220: mov dword ptr [0x4db8bc], 1 */
	lift_405010(m); return;	/* 40522a: jmp 0x405010 */
L_40522f:
	m->esp += 4 + 0; return;	/* 40522f: ret  */
}

/* room_434da0 (0x434da0), lifted by tools/lift.py */
static void lift_434da0(X86 *m)
{
	m->eax = M32((DWORD)(0x76d41cu));	/* 434da0: mov eax, dword ptr [0x76d41c] */
	M32((DWORD)(0x9dd6b4u)) = 0x0u;	/* 434da5: mov dword ptr [0x9dd6b4], 0 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 434daf: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 434db2: lea edx, [eax + ecx*4] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx*2 + 0x908807u))) & 0xff) << 0);	/* 434db5: mov al, byte ptr [edx*2 + 0x908807] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 434dbc: test al, al */
	if (m->zf) goto L_434dcf;	/* 434dbe: je 0x434dcf */
	M32((DWORD)(0x9dd6b4u)) = 0x1u;	/* 434dc0: mov dword ptr [0x9dd6b4], 1 */
	lift_434320(m); return;	/* 434dca: jmp 0x434320 */
L_434dcf:
	m->esp += 4 + 0; return;	/* 434dcf: ret  */
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
