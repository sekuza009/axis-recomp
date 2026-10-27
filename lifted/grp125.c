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

static void lift_41ed70(X86 *m);
static void lift_453180(X86 *m);
static void lift_41f970(X86 *m);
static void lift_435b00(X86 *m);
static void lift_4346c0(X86 *m);
static void lift_436620(X86 *m);
static void lift_40fd30(X86 *m);
static void lift_40ff40(X86 *m);
static void lift_436400(X86 *m);
static void lift_437630(X86 *m);
static void lift_441c00(X86 *m);
static void lift_422480(X86 *m);
static void lift_43e7b0(X86 *m);
static void lift_4221d0(X86 *m);
static void lift_422e10(X86 *m);
static void lift_422830(X86 *m);
static void lift_43df80(X86 *m);
static void lift_40ee20(X86 *m);
static void lift_4372f0(X86 *m);
static void lift_435fc0(X86 *m);
static void lift_436990(X86 *m);
static void lift_41edc0(X86 *m);

/* FUN_0041edc0 (0x41edc0), lifted by tools/lift.py */
static void lift_41edc0(X86 *m)
{
L_41edc0:
	m->eax = M32((DWORD)(0x67fb3cu));	/* 41edc0: mov eax, dword ptr [0x67fb3c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41edc5: test eax, eax */
	if (m->zf) goto L_41edd8;	/* 41edc7: je 0x41edd8 */
	{ DWORD v_ = 0x67fb3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41edc9: push 0x67fb3c */
	m->esp -= 4; M32(m->esp) = 0x41edd3u; native_call(m, 0x441190u);	/* 41edce: call 0x441190 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41edd3: add esp, 4 */
	goto L_41edc0;	/* 41edd6: jmp 0x41edc0 */
L_41edd8:
	m->esp -= 4; M32(m->esp) = 0x41edddu; native_call(m, 0x41e9d0u);	/* 41edd8: call 0x41e9d0 */
	M32((DWORD)(0x76d3e8u)) = 0x12cu;	/* 41eddd: mov dword ptr [0x76d3e8], 0x12c */
	m->esp += 4 + 0; return;	/* 41ede7: ret  */
}

/* FUN_0041ed70 (0x41ed70), lifted by tools/lift.py */
static void lift_41ed70(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41ed70: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 41ed71: xor esi, esi */
L_41ed73:
	{ DWORD a_ = M32((DWORD)(0x67fb3cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41ed73: cmp dword ptr [0x67fb3c], esi */
	if (m->zf) goto L_41ed8a;	/* 41ed79: je 0x41ed8a */
	{ DWORD v_ = 0x67fb3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41ed7b: push 0x67fb3c */
	m->esp -= 4; M32(m->esp) = 0x41ed85u; native_call(m, 0x441190u);	/* 41ed80: call 0x441190 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41ed85: add esp, 4 */
	goto L_41ed73;	/* 41ed88: jmp 0x41ed73 */
L_41ed8a:
	m->esp -= 4; M32(m->esp) = 0x41ed8fu; native_call(m, 0x41e8b0u);	/* 41ed8a: call 0x41e8b0 */
	M32((DWORD)(0x9dd838u)) = m->esi;	/* 41ed8f: mov dword ptr [0x9dd838], esi */
	M32((DWORD)(0x9dd6a4u)) = m->esi;	/* 41ed95: mov dword ptr [0x9dd6a4], esi */
	M32((DWORD)(0x9dd1b0u)) = m->esi;	/* 41ed9b: mov dword ptr [0x9dd1b0], esi */
	M32((DWORD)(0x9dd6d4u)) = m->esi;	/* 41eda1: mov dword ptr [0x9dd6d4], esi */
	M32((DWORD)(0x76d3e8u)) = 0x12cu;	/* 41eda7: mov dword ptr [0x76d3e8], 0x12c */
	m->esi = M32(m->esp); m->esp += 4;	/* 41edb1: pop esi */
	m->esp += 4 + 0; return;	/* 41edb2: ret  */
}

/* arena_453180 (0x453180), lifted by tools/lift.py */
static void lift_453180(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 453180: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453184: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453185: push eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 453186: xor esi, esi */
	m->esp -= 4; M32(m->esp) = 0x45318du; native_call(m, 0x4532b0u);	/* 453188: call 0x4532b0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45318d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453190: test eax, eax */
	if (!m->zf) goto L_45319b;	/* 453192: jne 0x45319b */
	m->eax = 0x1f7u;	/* 453194: mov eax, 0x1f7 */
	m->esi = M32(m->esp); m->esp += 4;	/* 453199: pop esi */
	m->esp += 4 + 0; return;	/* 45319a: ret  */
L_45319b:
	m->edx = M32((DWORD)(m->eax + 0x2au));	/* 45319b: mov edx, dword ptr [eax + 0x2a] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45319e: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x26u))) & 0xff) << 0);	/* 4531a0: mov cl, byte ptr [eax + 0x26] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4531a3: cmp edx, ecx */
	if (!m->zf) goto L_4531ae;	/* 4531a5: jne 0x4531ae */
	m->eax = 0x1f5u;	/* 4531a7: mov eax, 0x1f5 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4531ac: pop esi */
	m->esp += 4 + 0; return;	/* 4531ad: ret  */
L_4531ae:
	m->ecx = M32((DWORD)(0xa0b418u));	/* 4531ae: mov ecx, dword ptr [0xa0b418] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4531b4: cmp ecx, 3 */
	if (!m->cf && !m->zf) goto L_453246;	/* 4531b7: ja 0x453246 */
	switch (m->ecx) { case 0: goto L_4531c4; case 1: goto L_4531e5; case 2: goto L_453206; case 3: goto L_453227; default: abort(); }	/* 4531bd: jmp dword ptr [ecx*4 + 0x45324c] */
L_4531c4:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4531c4: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4531c8: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x27u))) & 0xff) << 0);	/* 4531ca: mov dl, byte ptr [eax + 0x27] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4531cd: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4531d1: push edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4531d2: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4531d6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4531d7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4531d8: push edx */
	m->esp -= 4; M32(m->esp) = 0x4531deu; native_call(m, 0x454a20u);	/* 4531d9: call 0x454a20 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4531de: add esp, 0x10 */
	m->esi = m->eax;	/* 4531e1: mov esi, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 4531e3: pop esi */
	m->esp += 4 + 0; return;	/* 4531e4: ret  */
L_4531e5:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4531e5: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4531e9: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x27u))) & 0xff) << 0);	/* 4531eb: mov cl, byte ptr [eax + 0x27] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4531ee: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4531f2: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4531f3: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4531f7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4531f8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4531f9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4531ffu; native_call(m, 0x454b40u);	/* 4531fa: call 0x454b40 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4531ff: add esp, 0x10 */
	m->esi = m->eax;	/* 453202: mov esi, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 453204: pop esi */
	m->esp += 4 + 0; return;	/* 453205: ret  */
L_453206:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 453206: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 45320a: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x27u))) & 0xff) << 0);	/* 45320c: mov dl, byte ptr [eax + 0x27] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45320f: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453213: push edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 453214: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453218: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453219: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45321a: push edx */
	m->esp -= 4; M32(m->esp) = 0x453220u; native_call(m, 0x454c50u);	/* 45321b: call 0x454c50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453220: add esp, 0x10 */
	m->esi = m->eax;	/* 453223: mov esi, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 453225: pop esi */
	m->esp += 4 + 0; return;	/* 453226: ret  */
L_453227:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 453227: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45322b: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x27u))) & 0xff) << 0);	/* 45322d: mov cl, byte ptr [eax + 0x27] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 453230: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453234: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 453235: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453239: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45323a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45323b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x453241u; native_call(m, 0x454d60u);	/* 45323c: call 0x454d60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453241: add esp, 0x10 */
	m->esi = m->eax;	/* 453244: mov esi, eax */
L_453246:
	m->eax = m->esi;	/* 453246: mov eax, esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 453248: pop esi */
	m->esp += 4 + 0; return;	/* 453249: ret  */
}

/* menu_enterState (0x41f970), lifted by tools/lift.py */
static void lift_41f970(X86 *m)
{
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41f970: mov eax, dword ptr [0x76d3e8] */
	{ DWORD a_ = m->eax, b_ = 0x258u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f975: cmp eax, 0x258 */
	if (!m->zf && m->sf == m->of) goto L_41f9f8;	/* 41f97a: jg 0x41f9f8 */
	if (m->zf) goto L_41f9e8;	/* 41f97c: je 0x41f9e8 */
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f97e: cmp eax, 0x190 */
	if (!m->zf && m->sf == m->of) goto L_41f9d1;	/* 41f983: jg 0x41f9d1 */
	if (m->zf) goto L_41f9c1;	/* 41f985: je 0x41f9c1 */
	{ DWORD a_ = m->eax, b_ = 0xd2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41f987: sub eax, 0xd2 */
	if (m->zf) goto L_41f9b1;	/* 41f98c: je 0x41f9b1 */
	{ DWORD a_ = m->eax, b_ = 0x5au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41f98e: sub eax, 0x5a */
	if (!m->zf) goto L_41fa30;	/* 41f991: jne 0x41fa30 */
	M32((DWORD)(0x4deb48u)) = 0x1u;	/* 41f997: mov dword ptr [0x4deb48], 1 */
	m->esp -= 4; M32(m->esp) = 0x41f9a6u; native_call(m, 0x440bb0u);	/* 41f9a1: call 0x440bb0 */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41f9a6: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41f9ab: mov dword ptr [0x67ef0c], eax */
	m->esp += 4 + 0; return;	/* 41f9b0: ret  */
L_41f9b1:
	m->esp -= 4; M32(m->esp) = 0x41f9b6u; native_call(m, 0x44b420u);	/* 41f9b1: call 0x44b420 */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41f9b6: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41f9bb: mov dword ptr [0x67ef0c], eax */
	m->esp += 4 + 0; return;	/* 41f9c0: ret  */
L_41f9c1:
	m->esp -= 4; M32(m->esp) = 0x41f9c6u; native_call(m, 0x404640u);	/* 41f9c1: call 0x404640 */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41f9c6: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41f9cb: mov dword ptr [0x67ef0c], eax */
	m->esp += 4 + 0; return;	/* 41f9d0: ret  */
L_41f9d1:
	{ DWORD a_ = m->eax, b_ = 0x1f4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f9d1: cmp eax, 0x1f4 */
	if (!m->zf) goto L_41fa30;	/* 41f9d6: jne 0x41fa30 */
	m->esp -= 4; M32(m->esp) = 0x41f9ddu; native_call(m, 0x447750u);	/* 41f9d8: call 0x447750 */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41f9dd: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41f9e2: mov dword ptr [0x67ef0c], eax */
	m->esp += 4 + 0; return;	/* 41f9e7: ret  */
L_41f9e8:
	m->esp -= 4; M32(m->esp) = 0x41f9edu; native_call(m, 0x420770u);	/* 41f9e8: call 0x420770 */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41f9ed: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41f9f2: mov dword ptr [0x67ef0c], eax */
	m->esp += 4 + 0; return;	/* 41f9f7: ret  */
L_41f9f8:
	{ DWORD a_ = m->eax, b_ = 0x320u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41f9f8: sub eax, 0x320 */
	if (m->zf) goto L_41fa2b;	/* 41f9fd: je 0x41fa2b */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41f9ff: sub eax, 0x64 */
	if (m->zf) goto L_41fa1b;	/* 41fa02: je 0x41fa1b */
	{ DWORD a_ = m->eax, b_ = 0x238bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41fa04: sub eax, 0x238b */
	if (!m->zf) goto L_41fa30;	/* 41fa09: jne 0x41fa30 */
	m->esp -= 4; M32(m->esp) = 0x41fa10u; native_call(m, 0x41fd40u);	/* 41fa0b: call 0x41fd40 */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41fa10: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41fa15: mov dword ptr [0x67ef0c], eax */
	m->esp += 4 + 0; return;	/* 41fa1a: ret  */
L_41fa1b:
	m->esp -= 4; M32(m->esp) = 0x41fa20u; native_call(m, 0x443950u);	/* 41fa1b: call 0x443950 */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41fa20: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41fa25: mov dword ptr [0x67ef0c], eax */
	m->esp += 4 + 0; return;	/* 41fa2a: ret  */
L_41fa2b:
	m->esp -= 4; M32(m->esp) = 0x41fa30u; native_call(m, 0x432ff0u);	/* 41fa2b: call 0x432ff0 */
L_41fa30:
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41fa30: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41fa35: mov dword ptr [0x67ef0c], eax */
	m->esp += 4 + 0; return;	/* 41fa3a: ret  */
}

/* room_435b00 (0x435b00), lifted by tools/lift.py */
static void lift_435b00(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd1c8u));	/* 435b00: mov eax, dword ptr [0x9dd1c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435b05: test eax, eax */
	if (!m->zf) goto L_435b59;	/* 435b07: jne 0x435b59 */
	m->eax = M32((DWORD)(0x9dd838u));	/* 435b09: mov eax, dword ptr [0x9dd838] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435b0e: test eax, eax */
	if (!m->zf) goto L_435b59;	/* 435b10: jne 0x435b59 */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 435b12: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435b17: test eax, eax */
	if (!m->zf) goto L_435b59;	/* 435b19: jne 0x435b59 */
	m->eax = M32((DWORD)(0x4ded88u));	/* 435b1b: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435b20: test eax, eax */
	if (m->zf) goto L_435b59;	/* 435b22: je 0x435b59 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 435b24: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 435b29: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435b2f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435b30: push ecx */
	m->esp -= 4; M32(m->esp) = 0x435b36u; native_call(m, 0x432200u);	/* 435b31: call 0x432200 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435b36: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435b39: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_435b59;	/* 435b3c: ja 0x435b59 */
	switch (m->eax) { case 0: goto L_435b45; case 1: goto L_435b5a; case 2: goto L_435b6f; case 3: goto L_435b9c; case 4: goto L_435bfc; default: abort(); }	/* 435b3e: jmp dword ptr [eax*4 + 0x435c0c] */
L_435b45:
	m->esp -= 4; M32(m->esp) = 0x435b4au; native_call(m, 0x433c70u);	/* 435b45: call 0x433c70 */
	m->esp -= 4; M32(m->esp) = 0x435b4fu; native_call(m, 0x433b00u);	/* 435b4a: call 0x433b00 */
	M32((DWORD)(0x9dd1ccu)) = 0x1u;	/* 435b4f: mov dword ptr [0x9dd1cc], 1 */
L_435b59:
	m->esp += 4 + 0; return;	/* 435b59: ret  */
L_435b5a:
	m->esp -= 4; M32(m->esp) = 0x435b5fu; native_call(m, 0x433c70u);	/* 435b5a: call 0x433c70 */
	m->esp -= 4; M32(m->esp) = 0x435b64u; native_call(m, 0x433bb0u);	/* 435b5f: call 0x433bb0 */
	M32((DWORD)(0x9dd6b0u)) = 0x1u;	/* 435b64: mov dword ptr [0x9dd6b0], 1 */
	m->esp += 4 + 0; return;	/* 435b6e: ret  */
L_435b6f:
	m->eax = M32((DWORD)(0x9dd1c8u));	/* 435b6f: mov eax, dword ptr [0x9dd1c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435b74: test eax, eax */
	if (!m->zf) goto L_435b59;	/* 435b76: jne 0x435b59 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435b78: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435b7fu; native_call(m, 0x41e760u);	/* 435b7a: call 0x41e760 */
	m->eax = 0x1u;	/* 435b7f: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435b84: add esp, 4 */
	M32((DWORD)(0x9dd198u)) = m->eax;	/* 435b87: mov dword ptr [0x9dd198], eax */
	M32((DWORD)(0x9dd1c8u)) = m->eax;	/* 435b8c: mov dword ptr [0x9dd1c8], eax */
	M32((DWORD)(0x9dd850u)) = 0x0u;	/* 435b91: mov dword ptr [0x9dd850], 0 */
	m->esp += 4 + 0; return;	/* 435b9b: ret  */
L_435b9c:
	m->eax = M32((DWORD)(0x68039cu));	/* 435b9c: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435ba1: test eax, eax */
	if (m->zf) goto L_435bc3;	/* 435ba3: je 0x435bc3 */
	M32((DWORD)(0x68039cu)) = 0x0u;	/* 435ba5: mov dword ptr [0x68039c], 0 */
	m->esp -= 4; M32(m->esp) = 0x435bb4u; native_call(m, 0x431590u);	/* 435baf: call 0x431590 */
	m->edx = M32((DWORD)(0x4ded18u));	/* 435bb4: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 435bba: push edx */
	m->esp -= 4; M32(m->esp) = 0x435bc0u; native_call(m, 0x401310u);	/* 435bbb: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435bc0: add esp, 4 */
L_435bc3:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435bc3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435bcau; native_call(m, 0x41e760u);	/* 435bc5: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 435bca: push 4 */
	m->esp -= 4; M32(m->esp) = 0x435bd1u; native_call(m, 0x441250u);	/* 435bcc: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435bd1: add esp, 8 */
	M32((DWORD)(0x9dd834u)) = 0x63u;	/* 435bd4: mov dword ptr [0x9dd834], 0x63 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 435bde: mov dword ptr [0x67ef20], 0x12c */
	M32((DWORD)(0x4e1868u)) = 0x0u;	/* 435be8: mov dword ptr [0x4e1868], 0 */
	m->esp -= 4; M32(m->esp) = 0x435bf7u; native_call(m, 0x48b420u);	/* 435bf2: call 0x48b420 */
	native_call(m, 0x451e60u); return;	/* 435bf7: jmp 0x451e60 */
L_435bfc:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435bfc: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435c03u; native_call(m, 0x41e760u);	/* 435bfe: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435c03: add esp, 4 */
	native_call(m, 0x4338c0u); return;	/* 435c06: jmp 0x4338c0 */
}

/* room_4346c0 (0x4346c0), lifted by tools/lift.py */
static void lift_4346c0(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4346c0: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4346c1: push edi */
	m->esp -= 4; M32(m->esp) = 0x4346c7u; native_call(m, 0x433d30u);	/* 4346c2: call 0x433d30 */
	m->edi = 0x9dd1d8u;	/* 4346c7: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4346cc: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4346cf: xor eax, eax */
	M32((DWORD)(0x68039cu)) = 0x0u;	/* 4346d1: mov dword ptr [0x68039c], 0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4346db: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4346dd: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4346df: dec ecx */
	M32((DWORD)(0x9dc428u)) = 0x0u;	/* 4346e0: mov dword ptr [0x9dc428], 0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4346ea: test ecx, ecx */
	if (!m->zf && m->sf == m->of) goto L_434705;	/* 4346ec: jg 0x434705 */
	{ DWORD v_ = 0x24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4346ee: push 0x24 */
	m->esp -= 4; M32(m->esp) = 0x4346f5u; native_call(m, 0x41ee40u);	/* 4346f0: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4346f5: add esp, 4 */
	M32((DWORD)(0x9dd348u)) = 0x1u;	/* 4346f8: mov dword ptr [0x9dd348], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 434702: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 434703: pop ebp */
	m->esp += 4 + 0; return;	/* 434704: ret  */
L_434705:
	{ DWORD v_ = 0x9dd1d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 434705: push 0x9dd1d8 */
	m->esp -= 4; M32(m->esp) = 0x43470fu; native_call(m, 0x4343b0u);	/* 43470a: call 0x4343b0 */
	m->ebp = 0x1u;	/* 43470f: mov ebp, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434714: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434717: cmp eax, ebp */
	if (!m->zf) goto L_43472e;	/* 434719: jne 0x43472e */
	{ DWORD v_ = 0x24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43471b: push 0x24 */
	m->esp -= 4; M32(m->esp) = 0x434722u; native_call(m, 0x41ee40u);	/* 43471d: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434722: add esp, 4 */
	M32((DWORD)(0x9dd348u)) = m->ebp;	/* 434725: mov dword ptr [0x9dd348], ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 43472b: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43472c: pop ebp */
	m->esp += 4 + 0; return;	/* 43472d: ret  */
L_43472e:
	{ DWORD v_ = 0x9dd1d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43472e: push 0x9dd1d8 */
	m->esp -= 4; M32(m->esp) = 0x434738u; native_call(m, 0x434400u);	/* 434733: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434738: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43473b: cmp eax, ebp */
	if (!m->zf) goto L_434755;	/* 43473d: jne 0x434755 */
	{ DWORD v_ = 0x15au; m->esp -= 4; M32(m->esp) = v_; }	/* 43473f: push 0x15a */
	m->esp -= 4; M32(m->esp) = 0x434749u; native_call(m, 0x41ee40u);	/* 434744: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434749: add esp, 4 */
	M32((DWORD)(0x9dd348u)) = m->ebp;	/* 43474c: mov dword ptr [0x9dd348], ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 434752: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 434753: pop ebp */
	m->esp += 4 + 0; return;	/* 434754: ret  */
L_434755:
	m->edi = 0x9dd1f6u;	/* 434755: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43475a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43475d: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43475f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434761: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 434763: dec ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 434764: test ecx, ecx */
	if (!m->zf && m->sf == m->of) goto L_43477b;	/* 434766: jg 0x43477b */
	{ DWORD v_ = 0x25u; m->esp -= 4; M32(m->esp) = v_; }	/* 434768: push 0x25 */
	m->esp -= 4; M32(m->esp) = 0x43476fu; native_call(m, 0x41ee40u);	/* 43476a: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43476f: add esp, 4 */
	M32((DWORD)(0x9dd3f8u)) = m->ebp;	/* 434772: mov dword ptr [0x9dd3f8], ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 434778: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 434779: pop ebp */
	m->esp += 4 + 0; return;	/* 43477a: ret  */
L_43477b:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43477b: push esi */
	m->esi = 0x9dd202u;	/* 43477c: mov esi, 0x9dd202 */
	m->eax = 0x9dd1f6u;	/* 434781: mov eax, 0x9dd1f6 */
L_434786:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 434786: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 434788: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43478a: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_4347aa;	/* 43478c: jne 0x4347aa */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43478e: test cl, cl */
	if (m->zf) goto L_4347a6;	/* 434790: je 0x4347a6 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 434792: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 434795: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434797: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_4347aa;	/* 43479a: jne 0x4347aa */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43479c: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43479f: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4347a2: test cl, cl */
	if (!m->zf) goto L_434786;	/* 4347a4: jne 0x434786 */
L_4347a6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4347a6: xor eax, eax */
	goto L_4347af;	/* 4347a8: jmp 0x4347af */
L_4347aa:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4347aa: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4347ac: sbb eax, -1 */
L_4347af:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4347af: test eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 4347b1: pop esi */
	if (m->zf) goto L_4347c7;	/* 4347b2: je 0x4347c7 */
	{ DWORD v_ = 0x21u; m->esp -= 4; M32(m->esp) = v_; }	/* 4347b4: push 0x21 */
	m->esp -= 4; M32(m->esp) = 0x4347bbu; native_call(m, 0x41ee40u);	/* 4347b6: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4347bb: add esp, 4 */
	M32((DWORD)(0x9dd3f8u)) = m->ebp;	/* 4347be: mov dword ptr [0x9dd3f8], ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 4347c4: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4347c5: pop ebp */
	m->esp += 4 + 0; return;	/* 4347c6: ret  */
L_4347c7:
	{ DWORD v_ = 0x9dd1f6u; m->esp -= 4; M32(m->esp) = v_; }	/* 4347c7: push 0x9dd1f6 */
	m->esp -= 4; M32(m->esp) = 0x4347d1u; native_call(m, 0x434400u);	/* 4347cc: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4347d1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4347d4: cmp eax, ebp */
	if (!m->zf) goto L_4347ee;	/* 4347d6: jne 0x4347ee */
	{ DWORD v_ = 0x15bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4347d8: push 0x15b */
	m->esp -= 4; M32(m->esp) = 0x4347e2u; native_call(m, 0x41ee40u);	/* 4347dd: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4347e2: add esp, 4 */
	M32((DWORD)(0x9dd3f8u)) = m->ebp;	/* 4347e5: mov dword ptr [0x9dd3f8], ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 4347eb: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4347ec: pop ebp */
	m->esp += 4 + 0; return;	/* 4347ed: ret  */
L_4347ee:
	{ DWORD v_ = 0x9dd20eu; m->esp -= 4; M32(m->esp) = v_; }	/* 4347ee: push 0x9dd20e */
	m->esp -= 4; M32(m->esp) = 0x4347f8u; native_call(m, 0x434400u);	/* 4347f3: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4347f8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4347fb: cmp eax, ebp */
	if (!m->zf) goto L_434815;	/* 4347fd: jne 0x434815 */
	{ DWORD v_ = 0x81u; m->esp -= 4; M32(m->esp) = v_; }	/* 4347ff: push 0x81 */
	m->esp -= 4; M32(m->esp) = 0x434809u; native_call(m, 0x41ee40u);	/* 434804: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434809: add esp, 4 */
	M32((DWORD)(0x9dd6ccu)) = m->ebp;	/* 43480c: mov dword ptr [0x9dd6cc], ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 434812: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 434813: pop ebp */
	m->esp += 4 + 0; return;	/* 434814: ret  */
L_434815:
	m->esp -= 4; M32(m->esp) = 0x43481au; native_call(m, 0x433980u);	/* 434815: call 0x433980 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43481a: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43481b: pop ebp */
	m->esp += 4 + 0; return;	/* 43481c: ret  */
}

/* room_436620 (0x436620), lifted by tools/lift.py */
static void lift_436620(X86 *m)
{
	m->eax = M32((DWORD)(0x9dce48u));	/* 436620: mov eax, dword ptr [0x9dce48] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 436625: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436626: push edi */
	m->edi = 0x1u;	/* 436627: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43662c: cmp eax, edi */
	if (m->zf) goto L_4367d7;	/* 43662e: je 0x4367d7 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 436634: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436636: cmp eax, esi */
	if (m->zf) goto L_4367d7;	/* 436638: je 0x4367d7 */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43663e: cmp dword ptr [0x90d1c4], esi */
	if (!m->zf) goto L_4367d7;	/* 436644: jne 0x4367d7 */
	{ DWORD a_ = M32((DWORD)(0x4ded8cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43664a: cmp dword ptr [0x4ded8c], esi */
	if (m->zf) goto L_436660;	/* 436650: je 0x436660 */
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436652: cmp dword ptr [0x9dd6b8], esi */
	if (!m->zf) goto L_436660;	/* 436658: jne 0x436660 */
	M32((DWORD)(0x9dce48u)) = m->esi;	/* 43665a: mov dword ptr [0x9dce48], esi */
L_436660:
	{ DWORD a_ = M32((DWORD)(0x4ded88u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436660: cmp dword ptr [0x4ded88], esi */
	if (m->zf) goto L_4367d7;	/* 436666: je 0x4367d7 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 43666c: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 436671: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436677: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436678: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43667eu; native_call(m, 0x4323c0u);	/* 436679: call 0x4323c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43667e: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436681: cmp eax, 8 */
	if (!m->cf && !m->zf) goto L_4367d7;	/* 436684: ja 0x4367d7 */
	switch (m->eax) { case 0: goto L_436691; case 1: goto L_4366ae; case 2: goto L_4366cb; case 3: goto L_4366e8; case 4: goto L_436728; case 5: goto L_436746; case 6: goto L_4367d7; case 7: goto L_43676f; case 8: goto L_436794; default: abort(); }	/* 43668a: jmp dword ptr [eax*4 + 0x4367dc] */
L_436691:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436691: cmp dword ptr [0x9dd6b8], esi */
	if (!m->zf) goto L_4367d7;	/* 436697: jne 0x4367d7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43669d: push esi */
	m->esp -= 4; M32(m->esp) = 0x4366a3u; native_call(m, 0x41e760u);	/* 43669e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4366a3: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4366abu; native_call(m, 0x435970u);	/* 4366a6: call 0x435970 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4366ab: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4366ac: pop esi */
	m->esp += 4 + 0; return;	/* 4366ad: ret  */
L_4366ae:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4366ae: cmp dword ptr [0x9dd6b8], esi */
	if (!m->zf) goto L_4367d7;	/* 4366b4: jne 0x4367d7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4366ba: push esi */
	m->esp -= 4; M32(m->esp) = 0x4366c0u; native_call(m, 0x41e760u);	/* 4366bb: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4366c0: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4366c8u; native_call(m, 0x4359b0u);	/* 4366c3: call 0x4359b0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4366c8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4366c9: pop esi */
	m->esp += 4 + 0; return;	/* 4366ca: ret  */
L_4366cb:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4366cb: cmp dword ptr [0x9dd6b8], esi */
	if (!m->zf) goto L_4367d7;	/* 4366d1: jne 0x4367d7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4366d7: push esi */
	m->esp -= 4; M32(m->esp) = 0x4366ddu; native_call(m, 0x41e760u);	/* 4366d8: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4366dd: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4366e5u; native_call(m, 0x4359f0u);	/* 4366e0: call 0x4359f0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4366e5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4366e6: pop esi */
	m->esp += 4 + 0; return;	/* 4366e7: ret  */
L_4366e8:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4366e8: cmp dword ptr [0x9dd6b8], esi */
	if (m->zf) goto L_4367d7;	/* 4366ee: je 0x4367d7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4366f4: push esi */
	m->esp -= 4; M32(m->esp) = 0x4366fau; native_call(m, 0x41e760u);	/* 4366f5: call 0x41e760 */
	m->edx = M32((DWORD)(0x9dd300u));	/* 4366fa: mov edx, dword ptr [0x9dd300] */
	m->eax = M32((DWORD)(0x9dd1b4u));	/* 436700: mov eax, dword ptr [0x9dd1b4] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436705: add esp, 4 */
	M32((DWORD)(0x9dd3b0u)) = m->edi;	/* 436708: mov dword ptr [0x9dd3b0], edi */
	M32((DWORD)(0x9dd6b8u)) = m->esi;	/* 43670e: mov dword ptr [0x9dd6b8], esi */
	M32((DWORD)(0x76d40cu)) = m->esi;	/* 436714: mov dword ptr [0x76d40c], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 43671a: pop edi */
	M32((DWORD)(0x9dd1d0u)) = m->edx;	/* 43671b: mov dword ptr [0x9dd1d0], edx */
	M32((DWORD)(0x9dd6acu)) = m->eax;	/* 436721: mov dword ptr [0x9dd6ac], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 436726: pop esi */
	m->esp += 4 + 0; return;	/* 436727: ret  */
L_436728:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436728: cmp dword ptr [0x9dd6b8], esi */
	if (!m->zf) goto L_4367d7;	/* 43672e: jne 0x4367d7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 436734: push esi */
	m->esp -= 4; M32(m->esp) = 0x43673au; native_call(m, 0x41e760u);	/* 436735: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43673a: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = m->esi;	/* 43673d: mov dword ptr [0x9dce48], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436743: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436744: pop esi */
	m->esp += 4 + 0; return;	/* 436745: ret  */
L_436746:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436746: cmp dword ptr [0x9dd6b8], esi */
	if (!m->zf) goto L_4367d7;	/* 43674c: jne 0x4367d7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 436752: push esi */
	m->esp -= 4; M32(m->esp) = 0x436758u; native_call(m, 0x41e760u);	/* 436753: call 0x41e760 */
	m->ecx = M32((DWORD)(0x9dd1d0u));	/* 436758: mov ecx, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43675e: add esp, 4 */
	M32((DWORD)(0x9dd300u)) = m->ecx;	/* 436761: mov dword ptr [0x9dd300], ecx */
	M32((DWORD)(0x9dd1d0u)) = m->esi;	/* 436767: mov dword ptr [0x9dd1d0], esi */
	goto L_4367b9;	/* 43676d: jmp 0x4367b9 */
L_43676f:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43676f: cmp dword ptr [0x9dd6b8], esi */
	if (!m->zf) goto L_4367d7;	/* 436775: jne 0x4367d7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 436777: push esi */
	m->esp -= 4; M32(m->esp) = 0x43677du; native_call(m, 0x41e760u);	/* 436778: call 0x41e760 */
	m->edx = M32((DWORD)(0x9dd1d0u));	/* 43677d: mov edx, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436783: add esp, 4 */
	M32((DWORD)(0x9dd300u)) = m->edx;	/* 436786: mov dword ptr [0x9dd300], edx */
	M32((DWORD)(0x9dd1d0u)) = m->edi;	/* 43678c: mov dword ptr [0x9dd1d0], edi */
	goto L_4367b9;	/* 436792: jmp 0x4367b9 */
L_436794:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436794: cmp dword ptr [0x9dd6b8], esi */
	if (!m->zf) goto L_4367d7;	/* 43679a: jne 0x4367d7 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43679c: push esi */
	m->esp -= 4; M32(m->esp) = 0x4367a2u; native_call(m, 0x41e760u);	/* 43679d: call 0x41e760 */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 4367a2: mov eax, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4367a7: add esp, 4 */
	M32((DWORD)(0x9dd300u)) = m->eax;	/* 4367aa: mov dword ptr [0x9dd300], eax */
	M32((DWORD)(0x9dd1d0u)) = 0x2u;	/* 4367af: mov dword ptr [0x9dd1d0], 2 */
L_4367b9:
	M32((DWORD)(0x9dd350u)) = m->edi;	/* 4367b9: mov dword ptr [0x9dd350], edi */
	M32((DWORD)(0x9dd3b0u)) = m->esi;	/* 4367bf: mov dword ptr [0x9dd3b0], esi */
	M32((DWORD)(0x76d40cu)) = m->esi;	/* 4367c5: mov dword ptr [0x76d40c], esi */
	M32((DWORD)(0xa0b350u)) = m->esi;	/* 4367cb: mov dword ptr [0xa0b350], esi */
	M32((DWORD)(0xa0b35cu)) = m->esi;	/* 4367d1: mov dword ptr [0xa0b35c], esi */
L_4367d7:
	m->edi = M32(m->esp); m->esp += 4;	/* 4367d7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4367d8: pop esi */
	m->esp += 4 + 0; return;	/* 4367d9: ret  */
}

/* armc_40fd30 (0x40fd30), lifted by tools/lift.py */
static void lift_40fd30(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 40fd30: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40fd35: test eax, eax */
	if (m->zf) goto L_40feff;	/* 40fd37: je 0x40feff */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 40fd3d: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 40fd42: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fd48: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fd49: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40fd4fu; native_call(m, 0x40e490u);	/* 40fd4a: call 0x40e490 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fd4f: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fd52: cmp eax, 0xe */
	if (!m->cf && !m->zf) goto L_40feff;	/* 40fd55: ja 0x40feff */
	switch (m->eax) { case 0: goto L_40fd62; case 1: goto L_40feff; case 2: goto L_40fd85; case 3: goto L_40fda8; case 4: goto L_40fdba; case 5: goto L_40feff; case 6: goto L_40fdcc; case 7: goto L_40fdde; case 8: goto L_40fdf0; case 9: goto L_40fe02; case 10: goto L_40fe14; case 11: goto L_40fe26; case 12: goto L_40fe38; case 13: goto L_40fe8d; case 14: goto L_40fee3; default: abort(); }	/* 40fd5b: jmp dword ptr [eax*4 + 0x40ff00] */
L_40fd62:
	{ DWORD a_ = M32((DWORD)(0x4dc798u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fd62: cmp dword ptr [0x4dc798], 1 */
	if (m->zf) goto L_40feff;	/* 40fd69: je 0x40feff */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fd6f: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fd76u; native_call(m, 0x41e760u);	/* 40fd71: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fd76: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fd7du; native_call(m, 0x40f870u);	/* 40fd78: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fd7d: add esp, 8 */
	native_call(m, 0x40f200u); return;	/* 40fd80: jmp 0x40f200 */
L_40fd85:
	{ DWORD a_ = M32((DWORD)(0x4dc798u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fd85: cmp dword ptr [0x4dc798], 3 */
	if (m->zf) goto L_40feff;	/* 40fd8c: je 0x40feff */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fd92: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fd99u; native_call(m, 0x41e760u);	/* 40fd94: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fd99: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fda0u; native_call(m, 0x40f870u);	/* 40fd9b: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fda0: add esp, 8 */
	native_call(m, 0x40f320u); return;	/* 40fda3: jmp 0x40f320 */
L_40fda8:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fda8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fdafu; native_call(m, 0x41e760u);	/* 40fdaa: call 0x41e760 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fdaf: push 1 */
	m->esp -= 4; M32(m->esp) = 0x40fdb6u; native_call(m, 0x40f0f0u);	/* 40fdb1: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fdb6: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40fdb9: ret  */
L_40fdba:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fdba: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fdc1u; native_call(m, 0x41e760u);	/* 40fdbc: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fdc1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fdc8u; native_call(m, 0x40f0f0u);	/* 40fdc3: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fdc8: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40fdcb: ret  */
L_40fdcc:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fdcc: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fdd3u; native_call(m, 0x40f870u);	/* 40fdce: call 0x40f870 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fdd3: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fddau; native_call(m, 0x41e760u);	/* 40fdd5: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fdda: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40fddd: ret  */
L_40fdde:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fdde: push 1 */
	m->esp -= 4; M32(m->esp) = 0x40fde5u; native_call(m, 0x40f870u);	/* 40fde0: call 0x40f870 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fde5: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fdecu; native_call(m, 0x41e760u);	/* 40fde7: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fdec: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40fdef: ret  */
L_40fdf0:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fdf0: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fdf7u; native_call(m, 0x40f870u);	/* 40fdf2: call 0x40f870 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fdf7: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fdfeu; native_call(m, 0x41e760u);	/* 40fdf9: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fdfe: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40fe01: ret  */
L_40fe02:
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fe02: push 3 */
	m->esp -= 4; M32(m->esp) = 0x40fe09u; native_call(m, 0x40f870u);	/* 40fe04: call 0x40f870 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fe09: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fe10u; native_call(m, 0x41e760u);	/* 40fe0b: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fe10: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40fe13: ret  */
L_40fe14:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fe14: push 4 */
	m->esp -= 4; M32(m->esp) = 0x40fe1bu; native_call(m, 0x40f870u);	/* 40fe16: call 0x40f870 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fe1b: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fe22u; native_call(m, 0x41e760u);	/* 40fe1d: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fe22: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40fe25: ret  */
L_40fe26:
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fe26: push 5 */
	m->esp -= 4; M32(m->esp) = 0x40fe2du; native_call(m, 0x40f870u);	/* 40fe28: call 0x40f870 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fe2d: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fe34u; native_call(m, 0x41e760u);	/* 40fe2f: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fe34: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40fe37: ret  */
L_40fe38:
	m->eax = M32((DWORD)(0x4dc77cu));	/* 40fe38: mov eax, dword ptr [0x4dc77c] */
	m->ecx = M32((DWORD)(0x4dbe48u));	/* 40fe3d: mov ecx, dword ptr [0x4dbe48] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40fe43: dec eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40fe44: test ecx, ecx */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 40fe46: mov dword ptr [0x4dc77c], eax */
	if (!m->zf) goto L_40fe60;	/* 40fe4b: jne 0x40fe60 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40fe4d: test eax, eax */
	if (!m->zf) goto L_40fe79;	/* 40fe4f: jne 0x40fe79 */
	m->edx = M32((DWORD)(0x4dc244u));	/* 40fe51: mov edx, dword ptr [0x4dc244] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 40fe57: dec edx */
	M32((DWORD)(0x4dc77cu)) = m->edx;	/* 40fe58: mov dword ptr [0x4dc77c], edx */
	goto L_40fe79;	/* 40fe5e: jmp 0x40fe79 */
L_40fe60:
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fe60: cmp ecx, 3 */
	if (m->zf || m->sf != m->of) goto L_40fe79;	/* 40fe63: jle 0x40fe79 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fe65: push eax */
	m->esp -= 4; M32(m->esp) = 0x40fe6bu; native_call(m, 0x40f830u);	/* 40fe66: call 0x40f830 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fe6b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fe6e: cmp eax, 1 */
	if (!m->zf) goto L_40fe79;	/* 40fe71: jne 0x40fe79 */
	{ DWORD a_ = M32((DWORD)(0x4dc77cu)), r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); M32((DWORD)(0x4dc77cu)) = r_; }	/* 40fe73: dec dword ptr [0x4dc77c] */
L_40fe79:
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fe79: push 8 */
	m->esp -= 4; M32(m->esp) = 0x40fe80u; native_call(m, 0x41e760u);	/* 40fe7b: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fe80: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40fe88u; native_call(m, 0x40f950u);	/* 40fe83: call 0x40f950 */
	native_call(m, 0x40f9e0u); return;	/* 40fe88: jmp 0x40f9e0 */
L_40fe8d:
	m->eax = M32((DWORD)(0x4dc77cu));	/* 40fe8d: mov eax, dword ptr [0x4dc77c] */
	m->ecx = M32((DWORD)(0x4dbe48u));	/* 40fe92: mov ecx, dword ptr [0x4dbe48] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40fe98: inc eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40fe99: test ecx, ecx */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 40fe9b: mov dword ptr [0x4dc77c], eax */
	if (!m->zf) goto L_40feb6;	/* 40fea0: jne 0x40feb6 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(0x4dc244u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fea2: cmp eax, dword ptr [0x4dc244] */
	if (m->sf != m->of) goto L_40fecf;	/* 40fea8: jl 0x40fecf */
	M32((DWORD)(0x4dc77cu)) = 0x1u;	/* 40feaa: mov dword ptr [0x4dc77c], 1 */
	goto L_40fecf;	/* 40feb4: jmp 0x40fecf */
L_40feb6:
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40feb6: cmp ecx, 3 */
	if (m->zf || m->sf != m->of) goto L_40fecf;	/* 40feb9: jle 0x40fecf */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40febb: push eax */
	m->esp -= 4; M32(m->esp) = 0x40fec1u; native_call(m, 0x40f830u);	/* 40febc: call 0x40f830 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fec1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fec4: cmp eax, 1 */
	if (!m->zf) goto L_40fecf;	/* 40fec7: jne 0x40fecf */
	{ DWORD a_ = M32((DWORD)(0x4dc77cu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dc77cu)) = r_; }	/* 40fec9: inc dword ptr [0x4dc77c] */
L_40fecf:
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fecf: push 8 */
	m->esp -= 4; M32(m->esp) = 0x40fed6u; native_call(m, 0x41e760u);	/* 40fed1: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fed6: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40fedeu; native_call(m, 0x40f950u);	/* 40fed9: call 0x40f950 */
	native_call(m, 0x40f9e0u); return;	/* 40fede: jmp 0x40f9e0 */
L_40fee3:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fee3: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40feeau; native_call(m, 0x41e760u);	/* 40fee5: call 0x41e760 */
	m->ecx = M32((DWORD)(0x4dceacu));	/* 40feea: mov ecx, dword ptr [0x4dceac] */
	m->eax = 0x1u;	/* 40fef0: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fef5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40fef8: sub eax, ecx */
	M32((DWORD)(0x4dceacu)) = m->eax;	/* 40fefa: mov dword ptr [0x4dceac], eax */
L_40feff:
	m->esp += 4 + 0; return;	/* 40feff: ret  */
}

/* armc_colourScreenInput (0x40ff40), lifted by tools/lift.py */
static void lift_40ff40(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 40ff40: mov eax, dword ptr [0x4ded88] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40ff45: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40ff46: test eax, eax */
	if (m->zf) goto L_410110;	/* 40ff48: je 0x410110 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 40ff4e: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 40ff53: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ff59: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ff5a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40ff60u; native_call(m, 0x40e4d0u);	/* 40ff5b: call 0x40e4d0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ff60: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ff63: cmp eax, 0x11 */
	if (!m->cf && !m->zf) goto L_410110;	/* 40ff66: ja 0x410110 */
	switch (m->eax) { case 0: goto L_40ff73; case 1: goto L_40ff91; case 2: goto L_40ffb3; case 3: goto L_40ffd1; case 4: goto L_40ffe4; case 5: goto L_40fff7; case 6: goto L_41001a; case 7: goto L_41003e; case 8: goto L_410061; case 9: goto L_410085; case 10: goto L_4100a5; case 11: goto L_4100ca; case 12: goto L_4100d1; case 13: goto L_4100d8; case 14: goto L_4100df; case 15: goto L_4100e6; case 16: goto L_4100ed; case 17: goto L_4100f4; default: abort(); }	/* 40ff6c: jmp dword ptr [eax*4 + 0x410114] */
L_40ff73:
	{ DWORD a_ = M32((DWORD)(0x4dc798u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ff73: cmp dword ptr [0x4dc798], 1 */
	if (m->zf) goto L_410110;	/* 40ff7a: je 0x410110 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ff80: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40ff87u; native_call(m, 0x41e760u);	/* 40ff82: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ff87: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40ff8fu; native_call(m, 0x40f200u);	/* 40ff8a: call 0x40f200 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40ff8f: pop esi */
	m->esp += 4 + 0; return;	/* 40ff90: ret  */
L_40ff91:
	m->eax = M32((DWORD)(0x4dc798u));	/* 40ff91: mov eax, dword ptr [0x4dc798] */
	m->esi = 0x2u;	/* 40ff96: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ff9b: cmp eax, esi */
	if (m->zf) goto L_410110;	/* 40ff9d: je 0x410110 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40ffa3: push esi */
	m->esp -= 4; M32(m->esp) = 0x40ffa9u; native_call(m, 0x41e760u);	/* 40ffa4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ffa9: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40ffb1u; native_call(m, 0x40f220u);	/* 40ffac: call 0x40f220 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40ffb1: pop esi */
	m->esp += 4 + 0; return;	/* 40ffb2: ret  */
L_40ffb3:
	{ DWORD a_ = M32((DWORD)(0x4dc798u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ffb3: cmp dword ptr [0x4dc798], 3 */
	if (m->zf) goto L_410110;	/* 40ffba: je 0x410110 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ffc0: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40ffc7u; native_call(m, 0x41e760u);	/* 40ffc2: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ffc7: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40ffcfu; native_call(m, 0x40f320u);	/* 40ffca: call 0x40f320 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40ffcf: pop esi */
	m->esp += 4 + 0; return;	/* 40ffd0: ret  */
L_40ffd1:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ffd1: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40ffd8u; native_call(m, 0x41e760u);	/* 40ffd3: call 0x41e760 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ffd8: push 1 */
	m->esp -= 4; M32(m->esp) = 0x40ffdfu; native_call(m, 0x40f0f0u);	/* 40ffda: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ffdf: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40ffe2: pop esi */
	m->esp += 4 + 0; return;	/* 40ffe3: ret  */
L_40ffe4:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ffe4: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40ffebu; native_call(m, 0x41e760u);	/* 40ffe6: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ffeb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fff2u; native_call(m, 0x40f0f0u);	/* 40ffed: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fff2: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fff5: pop esi */
	m->esp += 4 + 0; return;	/* 40fff6: ret  */
L_40fff7:
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 40fff7: mov eax, dword ptr [0x4dc4b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40fffc: test eax, eax */
	if (m->zf) goto L_410110;	/* 40fffe: je 0x410110 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410004: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41000bu; native_call(m, 0x41e760u);	/* 410006: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41000b: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = 0x0u;	/* 41000e: mov dword ptr [0x4dc4b0], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410018: pop esi */
	m->esp += 4 + 0; return;	/* 410019: ret  */
L_41001a:
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41001a: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x1u;	/* 41001f: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410024: cmp eax, esi */
	if (m->zf) goto L_410110;	/* 410026: je 0x410110 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41002c: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410033u; native_call(m, 0x41e760u);	/* 41002e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410033: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 410036: mov dword ptr [0x4dc4b0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41003c: pop esi */
	m->esp += 4 + 0; return;	/* 41003d: ret  */
L_41003e:
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41003e: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x2u;	/* 410043: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410048: cmp eax, esi */
	if (m->zf) goto L_410110;	/* 41004a: je 0x410110 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 410050: push esi */
	m->esp -= 4; M32(m->esp) = 0x410056u; native_call(m, 0x41e760u);	/* 410051: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410056: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 410059: mov dword ptr [0x4dc4b0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41005f: pop esi */
	m->esp += 4 + 0; return;	/* 410060: ret  */
L_410061:
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 410061: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x3u;	/* 410066: mov esi, 3 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41006b: cmp eax, esi */
	if (m->zf) goto L_410110;	/* 41006d: je 0x410110 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410073: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41007au; native_call(m, 0x41e760u);	/* 410075: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41007a: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 41007d: mov dword ptr [0x4dc4b0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 410083: pop esi */
	m->esp += 4 + 0; return;	/* 410084: ret  */
L_410085:
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 410085: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x4u;	/* 41008a: mov esi, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41008f: cmp eax, esi */
	if (m->zf) goto L_410110;	/* 410091: je 0x410110 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410093: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41009au; native_call(m, 0x41e760u);	/* 410095: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41009a: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 41009d: mov dword ptr [0x4dc4b0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4100a3: pop esi */
	m->esp += 4 + 0; return;	/* 4100a4: ret  */
L_4100a5:
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 4100a5: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x5u;	/* 4100aa: mov esi, 5 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4100af: cmp eax, esi */
	if (m->zf) goto L_410110;	/* 4100b1: je 0x410110 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4100b3: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4100bau; native_call(m, 0x41e760u);	/* 4100b5: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4100ba: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 4100bd: mov dword ptr [0x4dc4b0], esi */
	m->esp -= 4; M32(m->esp) = 0x4100c8u; native_call(m, 0x40f590u);	/* 4100c3: call 0x40f590 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4100c8: pop esi */
	m->esp += 4 + 0; return;	/* 4100c9: ret  */
L_4100ca:
	m->esp -= 4; M32(m->esp) = 0x4100cfu; native_call(m, 0x40f5d0u);	/* 4100ca: call 0x40f5d0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4100cf: pop esi */
	m->esp += 4 + 0; return;	/* 4100d0: ret  */
L_4100d1:
	m->esp -= 4; M32(m->esp) = 0x4100d6u; native_call(m, 0x40f670u);	/* 4100d1: call 0x40f670 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4100d6: pop esi */
	m->esp += 4 + 0; return;	/* 4100d7: ret  */
L_4100d8:
	m->esp -= 4; M32(m->esp) = 0x4100ddu; native_call(m, 0x40f6b0u);	/* 4100d8: call 0x40f6b0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4100dd: pop esi */
	m->esp += 4 + 0; return;	/* 4100de: ret  */
L_4100df:
	m->esp -= 4; M32(m->esp) = 0x4100e4u; native_call(m, 0x40f6f0u);	/* 4100df: call 0x40f6f0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4100e4: pop esi */
	m->esp += 4 + 0; return;	/* 4100e5: ret  */
L_4100e6:
	m->esp -= 4; M32(m->esp) = 0x4100ebu; native_call(m, 0x40f790u);	/* 4100e6: call 0x40f790 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4100eb: pop esi */
	m->esp += 4 + 0; return;	/* 4100ec: ret  */
L_4100ed:
	m->esp -= 4; M32(m->esp) = 0x4100f2u; native_call(m, 0x40f7e0u);	/* 4100ed: call 0x40f7e0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4100f2: pop esi */
	m->esp += 4 + 0; return;	/* 4100f3: ret  */
L_4100f4:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4100f4: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4100fbu; native_call(m, 0x41e760u);	/* 4100f6: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dceacu));	/* 4100fb: mov eax, dword ptr [0x4dceac] */
	m->edx = 0x1u;	/* 410100: mov edx, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410105: add esp, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 410108: sub edx, eax */
	M32((DWORD)(0x4dceacu)) = m->edx;	/* 41010a: mov dword ptr [0x4dceac], edx */
L_410110:
	m->esi = M32(m->esp); m->esp += 4;	/* 410110: pop esi */
	m->esp += 4 + 0; return;	/* 410111: ret  */
}

/* room_436400 (0x436400), lifted by tools/lift.py */
static void lift_436400(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd380u));	/* 436400: mov eax, dword ptr [0x9dd380] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436405: test eax, eax */
	if (!m->zf) goto L_4365db;	/* 436407: jne 0x4365db */
	m->eax = M32((DWORD)(0x9dd388u));	/* 43640d: mov eax, dword ptr [0x9dd388] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436412: test eax, eax */
	if (!m->zf) goto L_4365db;	/* 436414: jne 0x4365db */
	m->eax = M32((DWORD)(0x9dd568u));	/* 43641a: mov eax, dword ptr [0x9dd568] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43641f: test eax, eax */
	if (!m->zf) goto L_4365db;	/* 436421: jne 0x4365db */
	m->eax = M32((DWORD)(0x9dd6a8u));	/* 436427: mov eax, dword ptr [0x9dd6a8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43642c: test eax, eax */
	if (!m->zf) goto L_4365db;	/* 43642e: jne 0x4365db */
	m->eax = M32((DWORD)(0x9dce48u));	/* 436434: mov eax, dword ptr [0x9dce48] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436439: cmp eax, 1 */
	if (m->zf) goto L_4365db;	/* 43643c: je 0x4365db */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436442: test eax, eax */
	if (m->zf) goto L_4365db;	/* 436444: je 0x4365db */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 43644a: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43644f: test eax, eax */
	if (!m->zf) goto L_4365db;	/* 436451: jne 0x4365db */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 436457: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43645c: test eax, eax */
	if (m->zf) goto L_43646a;	/* 43645e: je 0x43646a */
	M32((DWORD)(0x9dce48u)) = 0x0u;	/* 436460: mov dword ptr [0x9dce48], 0 */
L_43646a:
	m->eax = M32((DWORD)(0x4ded88u));	/* 43646a: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43646f: test eax, eax */
	if (m->zf) goto L_4365db;	/* 436471: je 0x4365db */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 436477: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 43647c: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436482: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436483: push ecx */
	m->esp -= 4; M32(m->esp) = 0x436489u; native_call(m, 0x432380u);	/* 436484: call 0x432380 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436489: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43648c: cmp eax, 0xd */
	if (!m->cf && !m->zf) goto L_4365db;	/* 43648f: ja 0x4365db */
	switch (m->eax) { case 0: goto L_43649c; case 1: goto L_4364a1; case 2: goto L_4365bf; case 3: goto L_4364a6; case 4: goto L_4365db; case 5: goto L_4364c2; case 6: goto L_436557; case 7: goto L_43656f; case 8: goto L_436587; case 9: goto L_43659f; case 10: goto L_4365bf; case 11: goto L_4365b4; case 12: goto L_4365bf; case 13: goto L_4365ca; default: abort(); }	/* 436495: jmp dword ptr [eax*4 + 0x4365dc] */
L_43649c:
	native_call(m, 0x4339e0u); return;	/* 43649c: jmp 0x4339e0 */
L_4364a1:
	native_call(m, 0x433a80u); return;	/* 4364a1: jmp 0x433a80 */
L_4364a6:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9e9u))) & 0xff) << 0);	/* 4364a6: mov al, byte ptr [0x4df9e9] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = (a_ + b_) & 0xffu; FLAGS(r_, 8); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 4364ab: add al, 2 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4364ad: cmp al, 0x10 */
	M8((DWORD)(0x4df9e9u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4364af: mov byte ptr [0x4df9e9], al */
	if (m->zf || m->sf != m->of) goto L_4365db;	/* 4364b4: jle 0x4365db */
	M8((DWORD)(0x4df9e9u)) = (BYTE)(0x2u);	/* 4364ba: mov byte ptr [0x4df9e9], 2 */
	m->esp += 4 + 0; return;	/* 4364c1: ret  */
L_4364c2:
	m->edx = M32((DWORD)(0x67ef24u));	/* 4364c2: mov edx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4364c8: push edx */
	m->esp -= 4; M32(m->esp) = 0x4364ceu; native_call(m, 0x401590u);	/* 4364c9: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4364ce: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4364d1: test eax, eax */
	if (!m->zf) goto L_436533;	/* 4364d3: jne 0x436533 */
	m->eax = M32((DWORD)(0x9db0acu));	/* 4364d5: mov eax, dword ptr [0x9db0ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4364da: push eax */
	m->esp -= 4; M32(m->esp) = 0x4364e0u; native_call(m, 0x401590u);	/* 4364db: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4364e0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4364e3: test eax, eax */
	if (!m->zf) goto L_436533;	/* 4364e5: jne 0x436533 */
	m->ecx = M32((DWORD)(0x6803a8u));	/* 4364e7: mov ecx, dword ptr [0x6803a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4364ed: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4364f3u; native_call(m, 0x401590u);	/* 4364ee: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4364f3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4364f6: test eax, eax */
	if (!m->zf) goto L_436533;	/* 4364f8: jne 0x436533 */
	m->edx = M32((DWORD)(0x9dad8cu));	/* 4364fa: mov edx, dword ptr [0x9dad8c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 436500: push edx */
	m->esp -= 4; M32(m->esp) = 0x436506u; native_call(m, 0x401590u);	/* 436501: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436506: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436509: test eax, eax */
	if (!m->zf) goto L_436533;	/* 43650b: jne 0x436533 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43650d: push 2 */
	m->esp -= 4; M32(m->esp) = 0x436514u; native_call(m, 0x41e760u);	/* 43650f: call 0x41e760 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9ebu))) & 0xff) << 0);	/* 436514: mov al, byte ptr [0x4df9eb] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436519: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 43651c: inc al */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x9u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43651e: cmp al, 9 */
	M8((DWORD)(0x4df9ebu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 436520: mov byte ptr [0x4df9eb], al */
	if (m->zf || m->sf != m->of) goto L_4365db;	/* 436525: jle 0x4365db */
	M8((DWORD)(0x4df9ebu)) = (BYTE)(0x0u);	/* 43652b: mov byte ptr [0x4df9eb], 0 */
	m->esp += 4 + 0; return;	/* 436532: ret  */
L_436533:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 436533: push 2 */
	m->esp -= 4; M32(m->esp) = 0x43653au; native_call(m, 0x41e760u);	/* 436535: call 0x41e760 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9ebu))) & 0xff) << 0);	/* 43653a: mov al, byte ptr [0x4df9eb] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43653f: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ - 1) & 0xffu; FLAGS(r_, 8); m->of = (a_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 436542: dec al */
	M8((DWORD)(0x4df9ebu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 436544: mov byte ptr [0x4df9eb], al */
	if (!m->sf) goto L_4365db;	/* 436549: jns 0x4365db */
	M8((DWORD)(0x4df9ebu)) = (BYTE)(0x9u);	/* 43654f: mov byte ptr [0x4df9eb], 9 */
	m->esp += 4 + 0; return;	/* 436556: ret  */
L_436557:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9ecu))) & 0xff) << 0);	/* 436557: mov al, byte ptr [0x4df9ec] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x5u & 0xffu, r_ = (a_ + b_) & 0xffu; FLAGS(r_, 8); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 43655c: add al, 5 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x32u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43655e: cmp al, 0x32 */
	M8((DWORD)(0x4df9ecu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 436560: mov byte ptr [0x4df9ec], al */
	if (m->cf || m->zf) goto L_4365db;	/* 436565: jbe 0x4365db */
	M8((DWORD)(0x4df9ecu)) = (BYTE)(0x5u);	/* 436567: mov byte ptr [0x4df9ec], 5 */
	m->esp += 4 + 0; return;	/* 43656e: ret  */
L_43656f:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9edu))) & 0xff) << 0);	/* 43656f: mov al, byte ptr [0x4df9ed] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x5u & 0xffu, r_ = (a_ + b_) & 0xffu; FLAGS(r_, 8); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 436574: add al, 5 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x3cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 436576: cmp al, 0x3c */
	M8((DWORD)(0x4df9edu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 436578: mov byte ptr [0x4df9ed], al */
	if (m->cf || m->zf) goto L_4365db;	/* 43657d: jbe 0x4365db */
	M8((DWORD)(0x4df9edu)) = (BYTE)(0x5u);	/* 43657f: mov byte ptr [0x4df9ed], 5 */
	m->esp += 4 + 0; return;	/* 436586: ret  */
L_436587:
	m->eax = M32((DWORD)(0x4ded54u));	/* 436587: mov eax, dword ptr [0x4ded54] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43658c: test eax, eax */
	if (!m->zf) goto L_4365db;	/* 43658e: jne 0x4365db */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 436590: push 0 */
	m->esp -= 4; M32(m->esp) = 0x436597u; native_call(m, 0x41e760u);	/* 436592: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436597: add esp, 4 */
	native_call(m, 0x4351c0u); return;	/* 43659a: jmp 0x4351c0 */
L_43659f:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43659f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4365a6u; native_call(m, 0x41e760u);	/* 4365a1: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4365a6: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = 0x0u;	/* 4365a9: mov dword ptr [0x9dce48], 0 */
	m->esp += 4 + 0; return;	/* 4365b3: ret  */
L_4365b4:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4365b4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4365bbu; native_call(m, 0x4356f0u);	/* 4365b6: call 0x4356f0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4365bb: add esp, 4 */
	m->esp += 4 + 0; return;	/* 4365be: ret  */
L_4365bf:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4365bf: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4365c6u; native_call(m, 0x4356f0u);	/* 4365c1: call 0x4356f0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4365c6: add esp, 4 */
	m->esp += 4 + 0; return;	/* 4365c9: ret  */
L_4365ca:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4365ca: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4365d1u; native_call(m, 0x41e760u);	/* 4365cc: call 0x41e760 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4365d1: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4365d8u; native_call(m, 0x403490u);	/* 4365d3: call 0x403490 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4365d8: add esp, 8 */
L_4365db:
	m->esp += 4 + 0; return;	/* 4365db: ret  */
}

/* menu_437630 (0x437630), lifted by tools/lift.py */
static void lift_437630(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 437630: mov eax, dword ptr [0x90d1c4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 437635: push ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 437636: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 437638: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437639: cmp eax, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43763b: push edi */
	if (!m->zf) goto L_43780b;	/* 43763c: jne 0x43780b */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437642: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_43780b;	/* 437648: jne 0x43780b */
	{ DWORD a_ = M32((DWORD)(0x9dd380u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43764e: cmp dword ptr [0x9dd380], ebx */
	if (m->zf) goto L_4376d2;	/* 437654: je 0x4376d2 */
	m->edi = 0x9dc92cu;	/* 437656: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43765b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43765e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 437660: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 437662: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 437664: dec ecx */
	if (!m->zf) goto L_437671;	/* 437665: jne 0x437671 */
	m->edi = M32(m->esp); m->esp += 4;	/* 437667: pop edi */
	M32((DWORD)(0x9dd380u)) = m->ebx;	/* 437668: mov dword ptr [0x9dd380], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43766e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43766f: pop ebx */
	m->esp += 4 + 0; return;	/* 437670: ret  */
L_437671:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 437671: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x43767bu; native_call(m, 0x4343b0u);	/* 437676: call 0x4343b0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43767b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43767e: cmp eax, 1 */
	if (!m->zf) goto L_437697;	/* 437681: jne 0x437697 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 437683: push 6 */
	m->esp -= 4; M32(m->esp) = 0x43768au; native_call(m, 0x41e760u);	/* 437685: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43768a: add esp, 4 */
	M32((DWORD)(0x9dd380u)) = m->ebx;	/* 43768d: mov dword ptr [0x9dd380], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 437693: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 437694: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 437695: pop ebx */
	m->esp += 4 + 0; return;	/* 437696: ret  */
L_437697:
	m->ecx = 0x8u;	/* 437697: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43769c: xor eax, eax */
	m->edi = 0x4df9c8u;	/* 43769e: mov edi, 0x4df9c8 */
	M32((DWORD)(0x9dd380u)) = m->ebx;	/* 4376a3: mov dword ptr [0x9dd380], ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4376a9: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dc92cu;	/* 4376ab: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4376b0: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4376b3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4376b5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4376b7: sub edi, ecx */
	m->eax = m->ecx;	/* 4376b9: mov eax, ecx */
	m->esi = m->edi;	/* 4376bb: mov esi, edi */
	m->edi = 0x4df9c8u;	/* 4376bd: mov edi, 0x4df9c8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4376c2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4376c5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4376c7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4376c9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4376cc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4376ce: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4376cf: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4376d0: pop ebx */
	m->esp += 4 + 0; return;	/* 4376d1: ret  */
L_4376d2:
	{ DWORD a_ = M32((DWORD)(0x9dd6a8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4376d2: cmp dword ptr [0x9dd6a8], ebx */
	if (m->zf) goto L_43771d;	/* 4376d8: je 0x43771d */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4376da: xor ecx, ecx */
	m->edi = 0x9dc92cu;	/* 4376dc: mov edi, 0x9dc92c */
	M32((DWORD)(0x4df9eeu)) = m->ecx;	/* 4376e1: mov dword ptr [0x4df9ee], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4376e7: xor eax, eax */
	M32((DWORD)(0x4df9f2u)) = m->ecx;	/* 4376e9: mov dword ptr [0x4df9f2], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4376ef: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4376f2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4376f4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4376f6: sub edi, ecx */
	M32((DWORD)(0x9dd6a8u)) = m->ebx;	/* 4376f8: mov dword ptr [0x9dd6a8], ebx */
	m->edx = m->ecx;	/* 4376fe: mov edx, ecx */
	m->esi = m->edi;	/* 437700: mov esi, edi */
	m->edi = 0x4df9eeu;	/* 437702: mov edi, 0x4df9ee */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 437707: mov dword ptr [0x4e1868], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43770d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 437710: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 437712: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 437714: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 437717: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 437719: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43771a: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43771b: pop ebx */
	m->esp += 4 + 0; return;	/* 43771c: ret  */
L_43771d:
	{ DWORD a_ = M32((DWORD)(0x9dd388u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43771d: cmp dword ptr [0x9dd388], ebx */
	if (m->zf) goto L_43775c;	/* 437723: je 0x43775c */
	m->edi = 0x9dc92cu;	/* 437725: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43772a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43772d: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43772f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 437731: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 437733: dec ecx */
	if (!m->zf) goto L_437740;	/* 437734: jne 0x437740 */
	m->edi = M32(m->esp); m->esp += 4;	/* 437736: pop edi */
	M32((DWORD)(0x9dd388u)) = m->ebx;	/* 437737: mov dword ptr [0x9dd388], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43773d: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43773e: pop ebx */
	m->esp += 4 + 0; return;	/* 43773f: ret  */
L_437740:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 437740: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x43774au; native_call(m, 0x49ec09u);	/* 437745: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43774a: add esp, 4 */
	M32((DWORD)(0x9dd388u)) = m->ebx;	/* 43774d: mov dword ptr [0x9dd388], ebx */
	M8((DWORD)(0x4df9ecu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 437753: mov byte ptr [0x4df9ec], al */
	m->edi = M32(m->esp); m->esp += 4;	/* 437758: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 437759: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43775a: pop ebx */
	m->esp += 4 + 0; return;	/* 43775b: ret  */
L_43775c:
	{ DWORD a_ = M32((DWORD)(0x9dd568u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43775c: cmp dword ptr [0x9dd568], ebx */
	if (m->zf) goto L_43779b;	/* 437762: je 0x43779b */
	m->edi = 0x9dc92cu;	/* 437764: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 437769: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43776c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43776e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 437770: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 437772: dec ecx */
	if (!m->zf) goto L_43777f;	/* 437773: jne 0x43777f */
	m->edi = M32(m->esp); m->esp += 4;	/* 437775: pop edi */
	M32((DWORD)(0x9dd568u)) = m->ebx;	/* 437776: mov dword ptr [0x9dd568], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43777c: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43777d: pop ebx */
	m->esp += 4 + 0; return;	/* 43777e: ret  */
L_43777f:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43777f: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x437789u; native_call(m, 0x49ec09u);	/* 437784: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437789: add esp, 4 */
	M32((DWORD)(0x9dd568u)) = m->ebx;	/* 43778c: mov dword ptr [0x9dd568], ebx */
	M8((DWORD)(0x4df9edu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 437792: mov byte ptr [0x4df9ed], al */
	m->edi = M32(m->esp); m->esp += 4;	/* 437797: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 437798: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 437799: pop ebx */
	m->esp += 4 + 0; return;	/* 43779a: ret  */
L_43779b:
	m->eax = M32((DWORD)(0x4e1510u));	/* 43779b: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4377a0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4377a6u; native_call(m, 0x401600u);	/* 4377a1: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4377a6: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4377a9: test eax, eax */
	if (m->zf) goto L_4377c7;	/* 4377ab: je 0x4377c7 */
	{ DWORD a_ = M32((DWORD)(0x4ded54u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4377ad: cmp dword ptr [0x4ded54], ebx */
	if (!m->zf) goto L_4377c7;	/* 4377b3: jne 0x4377c7 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4377b5: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4377bbu; native_call(m, 0x41e760u);	/* 4377b6: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4377bb: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4377c3u; native_call(m, 0x4351c0u);	/* 4377be: call 0x4351c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4377c3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4377c4: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4377c5: pop ebx */
	m->esp += 4 + 0; return;	/* 4377c6: ret  */
L_4377c7:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 4377c7: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4377cd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4377d3u; native_call(m, 0x401600u);	/* 4377ce: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4377d3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4377d6: test eax, eax */
	if (m->zf) goto L_4377e9;	/* 4377d8: je 0x4377e9 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4377da: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4377e0u; native_call(m, 0x41e760u);	/* 4377db: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4377e0: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = m->ebx;	/* 4377e3: mov dword ptr [0x9dce48], ebx */
L_4377e9:
	m->edx = M32((DWORD)(0x76d48cu));	/* 4377e9: mov edx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4377ef: push edx */
	m->esp -= 4; M32(m->esp) = 0x4377f5u; native_call(m, 0x401600u);	/* 4377f0: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4377f5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4377f8: test eax, eax */
	if (m->zf) goto L_43780b;	/* 4377fa: je 0x43780b */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4377fc: push ebx */
	m->esp -= 4; M32(m->esp) = 0x437802u; native_call(m, 0x41e760u);	/* 4377fd: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437802: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = m->ebx;	/* 437805: mov dword ptr [0x9dce48], ebx */
L_43780b:
	m->edi = M32(m->esp); m->esp += 4;	/* 43780b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43780c: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43780d: pop ebx */
	m->esp += 4 + 0; return;	/* 43780e: ret  */
}

/* mainmenu_441c00 (0x441c00), lifted by tools/lift.py */
static void lift_441c00(X86 *m)
{
	m->eax = M32((DWORD)(0x76d48cu));	/* 441c00: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441c05: push eax */
	m->esp -= 4; M32(m->esp) = 0x441c0bu; native_call(m, 0x401600u);	/* 441c06: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441c0b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441c0e: cmp eax, 1 */
	if (!m->zf) goto L_441c28;	/* 441c11: jne 0x441c28 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441c13: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441c1au; native_call(m, 0x41e760u);	/* 441c15: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441c1a: add esp, 4 */
	M32((DWORD)(0x9eeab4u)) = 0x0u;	/* 441c1d: mov dword ptr [0x9eeab4], 0 */
	m->esp += 4 + 0; return;	/* 441c27: ret  */
L_441c28:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 441c28: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441c2e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x441c34u; native_call(m, 0x401600u);	/* 441c2f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441c34: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441c37: cmp eax, 1 */
	if (!m->zf) goto L_441c41;	/* 441c3a: jne 0x441c41 */
	native_call(m, 0x441770u); return;	/* 441c3c: jmp 0x441770 */
L_441c41:
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 441c41: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 441c47: push edx */
	m->esp -= 4; M32(m->esp) = 0x441c4du; native_call(m, 0x401600u);	/* 441c48: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441c4d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441c50: cmp eax, 1 */
	if (!m->zf) goto L_441c6a;	/* 441c53: jne 0x441c6a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441c55: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441c5cu; native_call(m, 0x41e760u);	/* 441c57: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441c5c: add esp, 4 */
	M32((DWORD)(0x9eeab4u)) = 0x0u;	/* 441c5f: mov dword ptr [0x9eeab4], 0 */
	m->esp += 4 + 0; return;	/* 441c69: ret  */
L_441c6a:
	m->eax = M32((DWORD)(0x4e151cu));	/* 441c6a: mov eax, dword ptr [0x4e151c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441c6f: push eax */
	m->esp -= 4; M32(m->esp) = 0x441c75u; native_call(m, 0x401600u);	/* 441c70: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441c75: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441c78: cmp eax, 1 */
	if (!m->zf) goto L_441c9a;	/* 441c7b: jne 0x441c9a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441c7d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441c84u; native_call(m, 0x41e760u);	/* 441c7f: call 0x41e760 */
	m->eax = M32((DWORD)(0x9eeac0u));	/* 441c84: mov eax, dword ptr [0x9eeac0] */
	m->ecx = 0x1u;	/* 441c89: mov ecx, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441c8e: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 441c91: sub ecx, eax */
	M32((DWORD)(0x9eeac0u)) = m->ecx;	/* 441c93: mov dword ptr [0x9eeac0], ecx */
	m->esp += 4 + 0; return;	/* 441c99: ret  */
L_441c9a:
	m->edx = M32((DWORD)(0x4e0ce0u));	/* 441c9a: mov edx, dword ptr [0x4e0ce0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 441ca0: push edx */
	m->esp -= 4; M32(m->esp) = 0x441ca6u; native_call(m, 0x401600u);	/* 441ca1: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441ca6: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441ca9: cmp eax, 1 */
	if (!m->zf) goto L_441cbd;	/* 441cac: jne 0x441cbd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441cae: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441cb5u; native_call(m, 0x41e760u);	/* 441cb0: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441cb5: add esp, 4 */
	native_call(m, 0x440df0u); return;	/* 441cb8: jmp 0x440df0 */
L_441cbd:
	m->eax = M32((DWORD)(0x4e0cd4u));	/* 441cbd: mov eax, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441cc2: push eax */
	m->esp -= 4; M32(m->esp) = 0x441cc8u; native_call(m, 0x401600u);	/* 441cc3: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441cc8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441ccb: cmp eax, 1 */
	if (!m->zf) goto L_441cdf;	/* 441cce: jne 0x441cdf */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 441cd0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441cd7u; native_call(m, 0x41e760u);	/* 441cd2: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441cd7: add esp, 4 */
	native_call(m, 0x4417f0u); return;	/* 441cda: jmp 0x4417f0 */
L_441cdf:
	m->ecx = M32((DWORD)(0x9db0a0u));	/* 441cdf: mov ecx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441ce5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x441cebu; native_call(m, 0x401590u);	/* 441ce6: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441ceb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441cee: test eax, eax */
	if (!m->zf) goto L_441cf7;	/* 441cf0: jne 0x441cf7 */
	M32((DWORD)(0x76d37cu)) = m->eax;	/* 441cf2: mov dword ptr [0x76d37c], eax */
L_441cf7:
	m->edx = M32((DWORD)(0x9db0a0u));	/* 441cf7: mov edx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 441cfd: push edx */
	m->esp -= 4; M32(m->esp) = 0x441d03u; native_call(m, 0x401590u);	/* 441cfe: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441d03: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441d06: cmp eax, 1 */
	if (!m->zf) goto L_441d66;	/* 441d09: jne 0x441d66 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d37cu)));	/* 441d0b: fld dword ptr [0x76d37c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 441d11: fcomp dword ptr [0x4a93e8] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441d17: mov dword ptr [0x4dda44], 0 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 441d21: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 441d23: test ah, 0x41 */
	if (!m->zf) goto L_441d3b;	/* 441d26: jne 0x441d3b */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d37cu)));	/* 441d28: fld dword ptr [0x76d37c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 441d2e: fsub dword ptr [0x4b071c] */
	MF((DWORD)(0x76d37cu)) = (float)ST(0); FPOP();	/* 441d34: fstp dword ptr [0x76d37c] */
	m->esp += 4 + 0; return;	/* 441d3a: ret  */
L_441d3b:
	m->eax = M32((DWORD)(0x9dd92cu));	/* 441d3b: mov eax, dword ptr [0x9dd92c] */
	M32((DWORD)(0x76d37cu)) = 0x40800000u;	/* 441d40: mov dword ptr [0x76d37c], 0x40800000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441d4a: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_441df2;	/* 441d4c: jle 0x441df2 */
	m->edx = m->eax;	/* 441d52: mov edx, eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441d54: push 2 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 441d56: dec edx */
	M32((DWORD)(0x9dd92cu)) = m->edx;	/* 441d57: mov dword ptr [0x9dd92c], edx */
	m->esp -= 4; M32(m->esp) = 0x441d62u; native_call(m, 0x41e760u);	/* 441d5d: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441d62: add esp, 4 */
	m->esp += 4 + 0; return;	/* 441d65: ret  */
L_441d66:
	m->eax = M32((DWORD)(0x76d330u));	/* 441d66: mov eax, dword ptr [0x76d330] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441d6b: push eax */
	m->esp -= 4; M32(m->esp) = 0x441d71u; native_call(m, 0x401590u);	/* 441d6c: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441d71: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441d74: test eax, eax */
	if (!m->zf) goto L_441d7d;	/* 441d76: jne 0x441d7d */
	M32((DWORD)(0x680bb4u)) = m->eax;	/* 441d78: mov dword ptr [0x680bb4], eax */
L_441d7d:
	m->ecx = M32((DWORD)(0x76d330u));	/* 441d7d: mov ecx, dword ptr [0x76d330] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441d83: push ecx */
	m->esp -= 4; M32(m->esp) = 0x441d89u; native_call(m, 0x401590u);	/* 441d84: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441d89: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441d8c: cmp eax, 1 */
	if (!m->zf) goto L_441df2;	/* 441d8f: jne 0x441df2 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bb4u)));	/* 441d91: fld dword ptr [0x680bb4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 441d97: fcomp dword ptr [0x4a93e8] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 441d9d: mov dword ptr [0x4dda44], 0 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 441da7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 441da9: test ah, 0x41 */
	if (!m->zf) goto L_441dc1;	/* 441dac: jne 0x441dc1 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bb4u)));	/* 441dae: fld dword ptr [0x680bb4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 441db4: fsub dword ptr [0x4b071c] */
	MF((DWORD)(0x680bb4u)) = (float)ST(0); FPOP();	/* 441dba: fstp dword ptr [0x680bb4] */
	m->esp += 4 + 0; return;	/* 441dc0: ret  */
L_441dc1:
	m->edx = M32((DWORD)(0x9dd92cu));	/* 441dc1: mov edx, dword ptr [0x9dd92c] */
	m->eax = M32((DWORD)(0x9dd928u));	/* 441dc7: mov eax, dword ptr [0x9dd928] */
	{ DWORD a_ = m->edx, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 441dcc: add edx, 0xa */
	M32((DWORD)(0x680bb4u)) = 0x40800000u;	/* 441dcf: mov dword ptr [0x680bb4], 0x40800000 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441dd9: cmp edx, eax */
	if (m->sf == m->of) goto L_441df2;	/* 441ddb: jge 0x441df2 */
	m->edx = M32((DWORD)(0x9dd92cu));	/* 441ddd: mov edx, dword ptr [0x9dd92c] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441de3: push 2 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 441de5: inc edx */
	M32((DWORD)(0x9dd92cu)) = m->edx;	/* 441de6: mov dword ptr [0x9dd92c], edx */
	m->esp -= 4; M32(m->esp) = 0x441df1u; native_call(m, 0x41e760u);	/* 441dec: call 0x41e760 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 441df1: pop ecx */
L_441df2:
	m->esp += 4 + 0; return;	/* 441df2: ret  */
}

/* setup_drawGraphicTab (0x422480), lifted by tools/lift.py */
static void lift_422480(X86 *m)
{
	m->eax = M32((DWORD)(0x4ddcecu));	/* 422480: mov eax, dword ptr [0x4ddcec] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422485: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 422486: push esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422487: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42248a: push edi */
	if (m->zf) goto L_42267f;	/* 42248b: je 0x42267f */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 422491: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422493: cmp eax, ebx */
	if (m->zf) goto L_42267f;	/* 422495: je 0x42267f */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42249b: cmp dword ptr [0x90d1c4], ebx */
	if (!m->zf) goto L_42267f;	/* 4224a1: jne 0x42267f */
	{ DWORD a_ = M32((DWORD)(0x4ded8cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4224a7: cmp dword ptr [0x4ded8c], ebx */
	if (m->zf) goto L_4224b5;	/* 4224ad: je 0x4224b5 */
	M32((DWORD)(0x4ddcecu)) = m->ebx;	/* 4224af: mov dword ptr [0x4ddcec], ebx */
L_4224b5:
	{ DWORD a_ = M32((DWORD)(0x4ded88u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4224b5: cmp dword ptr [0x4ded88], ebx */
	if (m->zf) goto L_42267f;	/* 4224bb: je 0x42267f */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4224c1: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4224c6: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4224cc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4224cd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4224d3u; native_call(m, 0x4206b0u);	/* 4224ce: call 0x4206b0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4224d3: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4224d6: cmp eax, 8 */
	if (!m->cf && !m->zf) goto L_42267f;	/* 4224d9: ja 0x42267f */
	switch (m->eax) { case 0: goto L_4224e6; case 1: goto L_42250e; case 2: goto L_42252e; case 3: goto L_42254e; case 4: goto L_42256e; case 5: goto L_42258e; case 6: goto L_4225ae; case 7: goto L_4225e1; case 8: goto L_422670; default: abort(); }	/* 4224df: jmp dword ptr [eax*4 + 0x422684] */
L_4224e6:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4224e6: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4224edu; native_call(m, 0x41e760u);	/* 4224e8: call 0x41e760 */
	m->eax = M32((DWORD)(0x4ddba0u));	/* 4224ed: mov eax, dword ptr [0x4ddba0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4224f2: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4224f5: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4224f6: cmp eax, 7 */
	M32((DWORD)(0x4ddba0u)) = m->eax;	/* 4224f9: mov dword ptr [0x4ddba0], eax */
	if (m->zf || m->sf != m->of) goto L_42267f;	/* 4224fe: jle 0x42267f */
	m->edi = M32(m->esp); m->esp += 4;	/* 422504: pop edi */
	M32((DWORD)(0x4ddba0u)) = m->ebx;	/* 422505: mov dword ptr [0x4ddba0], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 42250b: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42250c: pop ebx */
	m->esp += 4 + 0; return;	/* 42250d: ret  */
L_42250e:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42250e: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422515u; native_call(m, 0x41e760u);	/* 422510: call 0x41e760 */
	m->eax = M32((DWORD)(0x4ddba4u));	/* 422515: mov eax, dword ptr [0x4ddba4] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42251a: add esp, 4 */
	m->edx = 0x1u;	/* 42251d: mov edx, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 422522: sub edx, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 422524: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422525: pop esi */
	M32((DWORD)(0x4ddba4u)) = m->edx;	/* 422526: mov dword ptr [0x4ddba4], edx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42252c: pop ebx */
	m->esp += 4 + 0; return;	/* 42252d: ret  */
L_42252e:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42252e: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422535u; native_call(m, 0x41e760u);	/* 422530: call 0x41e760 */
	m->ecx = M32((DWORD)(0x4ddba8u));	/* 422535: mov ecx, dword ptr [0x4ddba8] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42253b: add esp, 4 */
	m->eax = 0x1u;	/* 42253e: mov eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 422543: sub eax, ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 422545: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422546: pop esi */
	M32((DWORD)(0x4ddba8u)) = m->eax;	/* 422547: mov dword ptr [0x4ddba8], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42254c: pop ebx */
	m->esp += 4 + 0; return;	/* 42254d: ret  */
L_42254e:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42254e: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422555u; native_call(m, 0x41e760u);	/* 422550: call 0x41e760 */
	m->eax = M32((DWORD)(0x4ddbacu));	/* 422555: mov eax, dword ptr [0x4ddbac] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42255a: add esp, 4 */
	m->ecx = 0x1u;	/* 42255d: mov ecx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 422562: sub ecx, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 422564: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422565: pop esi */
	M32((DWORD)(0x4ddbacu)) = m->ecx;	/* 422566: mov dword ptr [0x4ddbac], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42256c: pop ebx */
	m->esp += 4 + 0; return;	/* 42256d: ret  */
L_42256e:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42256e: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422575u; native_call(m, 0x41e760u);	/* 422570: call 0x41e760 */
	m->eax = M32((DWORD)(0x4ddbb0u));	/* 422575: mov eax, dword ptr [0x4ddbb0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42257a: add esp, 4 */
	m->edx = 0x1u;	/* 42257d: mov edx, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 422582: sub edx, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 422584: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422585: pop esi */
	M32((DWORD)(0x4ddbb0u)) = m->edx;	/* 422586: mov dword ptr [0x4ddbb0], edx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42258c: pop ebx */
	m->esp += 4 + 0; return;	/* 42258d: ret  */
L_42258e:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42258e: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422595u; native_call(m, 0x41e760u);	/* 422590: call 0x41e760 */
	m->ecx = M32((DWORD)(0x4ddbb4u));	/* 422595: mov ecx, dword ptr [0x4ddbb4] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42259b: add esp, 4 */
	m->eax = 0x1u;	/* 42259e: mov eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4225a3: sub eax, ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 4225a5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4225a6: pop esi */
	M32((DWORD)(0x4ddbb4u)) = m->eax;	/* 4225a7: mov dword ptr [0x4ddbb4], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4225ac: pop ebx */
	m->esp += 4 + 0; return;	/* 4225ad: ret  */
L_4225ae:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4225ae: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4225b5u; native_call(m, 0x41e760u);	/* 4225b0: call 0x41e760 */
	m->edx = M32((DWORD)(0x4ddbb8u));	/* 4225b5: mov edx, dword ptr [0x4ddbb8] */
	m->eax = M32((DWORD)(0x9da494u));	/* 4225bb: mov eax, dword ptr [0x9da494] */
	m->ecx = 0x1u;	/* 4225c0: mov ecx, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4225c5: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4225c8: sub ecx, edx */
	m->edx = 0x1u;	/* 4225ca: mov edx, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4225cf: sub edx, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 4225d1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4225d2: pop esi */
	M32((DWORD)(0x4ddbb8u)) = m->ecx;	/* 4225d3: mov dword ptr [0x4ddbb8], ecx */
	M32((DWORD)(0x9da494u)) = m->edx;	/* 4225d9: mov dword ptr [0x9da494], edx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4225df: pop ebx */
	m->esp += 4 + 0; return;	/* 4225e0: ret  */
L_4225e1:
	m->eax = M32((DWORD)(0x83a9c4u));	/* 4225e1: mov eax, dword ptr [0x83a9c4] */
	m->ecx = M32((DWORD)(0x4ddba4u));	/* 4225e6: mov ecx, dword ptr [0x4ddba4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4225ec: cmp eax, ecx */
	if (!m->zf) goto L_422646;	/* 4225ee: jne 0x422646 */
	m->ecx = M32((DWORD)(0x83a9c0u));	/* 4225f0: mov ecx, dword ptr [0x83a9c0] */
	m->eax = M32((DWORD)(0x4ddba0u));	/* 4225f6: mov eax, dword ptr [0x4ddba0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4225fb: cmp ecx, eax */
	if (!m->zf) goto L_422646;	/* 4225fd: jne 0x422646 */
	m->edx = M32((DWORD)(0x83a9ccu));	/* 4225ff: mov edx, dword ptr [0x83a9cc] */
	m->eax = M32((DWORD)(0x4ddbacu));	/* 422605: mov eax, dword ptr [0x4ddbac] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42260a: cmp edx, eax */
	if (!m->zf) goto L_422646;	/* 42260c: jne 0x422646 */
	m->eax = M32((DWORD)(0x83a9d0u));	/* 42260e: mov eax, dword ptr [0x83a9d0] */
	m->ecx = M32((DWORD)(0x4ddbb0u));	/* 422613: mov ecx, dword ptr [0x4ddbb0] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422619: cmp eax, ecx */
	if (!m->zf) goto L_422646;	/* 42261b: jne 0x422646 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42261d: push ebx */
	m->esp -= 4; M32(m->esp) = 0x422623u; native_call(m, 0x41e760u);	/* 42261e: call 0x41e760 */
	m->ecx = 0x7u;	/* 422623: mov ecx, 7 */
	m->esi = 0x4ddba0u;	/* 422628: mov esi, 0x4ddba0 */
	m->edi = 0x83a9c0u;	/* 42262d: mov edi, 0x83a9c0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422632: add esp, 4 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 422635: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x42263cu; native_call(m, 0x42d730u);	/* 422637: call 0x42d730 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42263c: pop edi */
	M32((DWORD)(0x4ddcecu)) = m->ebx;	/* 42263d: mov dword ptr [0x4ddcec], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 422643: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422644: pop ebx */
	m->esp += 4 + 0; return;	/* 422645: ret  */
L_422646:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422646: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42264cu; native_call(m, 0x41e760u);	/* 422647: call 0x41e760 */
	m->ecx = 0x7u;	/* 42264c: mov ecx, 7 */
	m->esi = 0x4ddba0u;	/* 422651: mov esi, 0x4ddba0 */
	m->edi = 0x83a9c0u;	/* 422656: mov edi, 0x83a9c0 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42265b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x422662u; native_call(m, 0x42d730u);	/* 42265d: call 0x42d730 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 422662: push 1 */
	m->esp -= 4; M32(m->esp) = 0x422669u; native_call(m, 0x41e7a0u);	/* 422664: call 0x41e7a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422669: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42266c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42266d: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42266e: pop ebx */
	m->esp += 4 + 0; return;	/* 42266f: ret  */
L_422670:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422670: push ebx */
	m->esp -= 4; M32(m->esp) = 0x422676u; native_call(m, 0x41e760u);	/* 422671: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422676: add esp, 4 */
	M32((DWORD)(0x4ddcecu)) = m->ebx;	/* 422679: mov dword ptr [0x4ddcec], ebx */
L_42267f:
	m->edi = M32(m->esp); m->esp += 4;	/* 42267f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422680: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422681: pop ebx */
	m->esp += 4 + 0; return;	/* 422682: ret  */
}

/* room_43e7b0 (0x43e7b0), lifted by tools/lift.py */
static void lift_43e7b0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43e7b0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43e7b1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43e7b2: push edi */
	m->esp -= 4; M32(m->esp) = 0x43e7b8u; native_call(m, 0x4388e0u);	/* 43e7b3: call 0x4388e0 */
	m->eax = M32((DWORD)(0x9dce48u));	/* 43e7b8: mov eax, dword ptr [0x9dce48] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e7bd: cmp eax, 1 */
	if (m->zf) goto L_43ea06;	/* 43e7c0: je 0x43ea06 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 43e7c6: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e7c8: cmp eax, ebx */
	if (m->zf) goto L_43ea06;	/* 43e7ca: je 0x43ea06 */
	{ DWORD a_ = M32((DWORD)(0x9dd834u)), b_ = 0x63u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e7d0: cmp dword ptr [0x9dd834], 0x63 */
	if (m->zf) goto L_43ea06;	/* 43e7d7: je 0x43ea06 */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e7dd: cmp dword ptr [0x90d1c4], ebx */
	if (m->zf) goto L_43e80b;	/* 43e7e3: je 0x43e80b */
	m->eax = M32((DWORD)(0x9dd374u));	/* 43e7e5: mov eax, dword ptr [0x9dd374] */
	m->ecx = M32((DWORD)(0x9dd370u));	/* 43e7ea: mov ecx, dword ptr [0x9dd370] */
	m->edx = M32((DWORD)(0x9dd36cu));	/* 43e7f0: mov edx, dword ptr [0x9dd36c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43e7f6: push eax */
	m->eax = M32((DWORD)(0x9dd368u));	/* 43e7f7: mov eax, dword ptr [0x9dd368] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43e7fc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43e7fd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43e7fe: push eax */
	m->esp -= 4; M32(m->esp) = 0x43e804u; native_call(m, 0x428c30u);	/* 43e7ff: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e804: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e807: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e808: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e809: pop ebx */
	m->esp += 4 + 0; return;	/* 43e80a: ret  */
L_43e80b:
	{ DWORD a_ = M32((DWORD)(0x9dd354u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e80b: cmp dword ptr [0x9dd354], ebx */
	if (m->zf) goto L_43e818;	/* 43e811: je 0x43e818 */
	m->esp -= 4; M32(m->esp) = 0x43e818u; native_call(m, 0x433610u);	/* 43e813: call 0x433610 */
L_43e818:
	m->esp -= 4; M32(m->esp) = 0x43e81du; native_call(m, 0x43a420u);	/* 43e818: call 0x43a420 */
	{ DWORD a_ = M32((DWORD)(0x9dd6d4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e81d: cmp dword ptr [0x9dd6d4], 1 */
	if (m->zf) goto L_43ea06;	/* 43e824: je 0x43ea06 */
	{ DWORD a_ = M32((DWORD)(0x9dd69cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e82a: cmp dword ptr [0x9dd69c], ebx */
	if (m->zf) goto L_43e8a0;	/* 43e830: je 0x43e8a0 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e832: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_43ea06;	/* 43e838: jne 0x43ea06 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e83e: xor ecx, ecx */
	m->edi = 0x9dc92cu;	/* 43e840: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd6d8u)) = m->ecx;	/* 43e845: mov dword ptr [0x9dd6d8], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e84b: xor eax, eax */
	M32((DWORD)(0x9dd6dcu)) = m->ecx;	/* 43e84d: mov dword ptr [0x9dd6dc], ecx */
	M32((DWORD)(0x9dd69cu)) = m->ebx;	/* 43e853: mov dword ptr [0x9dd69c], ebx */
	M32((DWORD)(0x9dd6e0u)) = m->ecx;	/* 43e859: mov dword ptr [0x9dd6e0], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e85f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e862: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e864: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e866: sub edi, ecx */
	m->eax = M32((DWORD)(0x9dc428u));	/* 43e868: mov eax, dword ptr [0x9dc428] */
	m->edx = m->ecx;	/* 43e86d: mov edx, ecx */
	m->esi = m->edi;	/* 43e86f: mov esi, edi */
	m->edi = 0x9dd6d8u;	/* 43e871: mov edi, 0x9dd6d8 */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 43e876: mov dword ptr [0x4e1868], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e87c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e87f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43e881: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e883: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e886: cmp eax, 0x14 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e889: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_43ea06;	/* 43e88b: jne 0x43ea06 */
	m->esp -= 4; M32(m->esp) = 0x43e896u; native_call(m, 0x4340e0u);	/* 43e891: call 0x4340e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e896: pop edi */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43e897: mov dword ptr [0x9dc428], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e89d: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e89e: pop ebx */
	m->esp += 4 + 0; return;	/* 43e89f: ret  */
L_43e8a0:
	{ DWORD a_ = M32((DWORD)(0x9dd37cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e8a0: cmp dword ptr [0x9dd37c], ebx */
	if (m->zf) goto L_43e925;	/* 43e8a6: je 0x43e925 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e8a8: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_43ea06;	/* 43e8ae: jne 0x43ea06 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e8b4: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43e8b6: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd1f6u)) = m->eax;	/* 43e8bb: mov dword ptr [0x9dd1f6], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e8c0: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd1fau)) = m->eax;	/* 43e8c3: mov dword ptr [0x9dd1fa], eax */
	M32((DWORD)(0x9dd37cu)) = m->ebx;	/* 43e8c8: mov dword ptr [0x9dd37c], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e8ce: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e8d0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e8d2: sub edi, ecx */
	M32((DWORD)(0x9dd1feu)) = m->eax;	/* 43e8d4: mov dword ptr [0x9dd1fe], eax */
	m->edx = m->ecx;	/* 43e8d9: mov edx, ecx */
	m->esi = m->edi;	/* 43e8db: mov esi, edi */
	m->edi = 0x9dd1f6u;	/* 43e8dd: mov edi, 0x9dd1f6 */
	m->eax = M32((DWORD)(0x9dc428u));	/* 43e8e2: mov eax, dword ptr [0x9dc428] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e8e7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e8ea: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43e8ec: mov ecx, edx */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 43e8ee: mov dword ptr [0x4e1868], ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e8f4: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e8f7: cmp eax, 0xa */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e8fa: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_43e90d;	/* 43e8fc: jne 0x43e90d */
	m->esp -= 4; M32(m->esp) = 0x43e903u; native_call(m, 0x434020u);	/* 43e8fe: call 0x434020 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e903: pop edi */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43e904: mov dword ptr [0x9dc428], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e90a: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e90b: pop ebx */
	m->esp += 4 + 0; return;	/* 43e90c: ret  */
L_43e90d:
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e90d: cmp eax, 0x14 */
	if (!m->zf) goto L_43ea06;	/* 43e910: jne 0x43ea06 */
	m->esp -= 4; M32(m->esp) = 0x43e91bu; native_call(m, 0x4341a0u);	/* 43e916: call 0x4341a0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e91b: pop edi */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43e91c: mov dword ptr [0x9dc428], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e922: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e923: pop ebx */
	m->esp += 4 + 0; return;	/* 43e924: ret  */
L_43e925:
	{ DWORD a_ = M32((DWORD)(0x9dd378u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e925: cmp dword ptr [0x9dd378], ebx */
	if (m->zf) goto L_43e9a0;	/* 43e92b: je 0x43e9a0 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e92d: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_43ea06;	/* 43e933: jne 0x43ea06 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e939: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43e93b: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd202u)) = m->eax;	/* 43e940: mov dword ptr [0x9dd202], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e945: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd206u)) = m->eax;	/* 43e948: mov dword ptr [0x9dd206], eax */
	M32((DWORD)(0x9dd378u)) = m->ebx;	/* 43e94d: mov dword ptr [0x9dd378], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e953: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e955: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e957: sub edi, ecx */
	M32((DWORD)(0x9dd20au)) = m->eax;	/* 43e959: mov dword ptr [0x9dd20a], eax */
	m->edx = m->ecx;	/* 43e95e: mov edx, ecx */
	m->esi = m->edi;	/* 43e960: mov esi, edi */
	m->edi = 0x9dd202u;	/* 43e962: mov edi, 0x9dd202 */
	m->eax = M32((DWORD)(0x9dc428u));	/* 43e967: mov eax, dword ptr [0x9dc428] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e96c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e96f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43e971: mov ecx, edx */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 43e973: mov dword ptr [0x4e1868], ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e979: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e97c: cmp eax, 0xa */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e97f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_43e98c;	/* 43e981: jne 0x43e98c */
	m->esp -= 4; M32(m->esp) = 0x43e988u; native_call(m, 0x4340e0u);	/* 43e983: call 0x4340e0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e988: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e989: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e98a: pop ebx */
	m->esp += 4 + 0; return;	/* 43e98b: ret  */
L_43e98c:
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e98c: cmp eax, 0x14 */
	if (!m->zf) goto L_43ea06;	/* 43e98f: jne 0x43ea06 */
	m->esp -= 4; M32(m->esp) = 0x43e996u; native_call(m, 0x434260u);	/* 43e991: call 0x434260 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e996: pop edi */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43e997: mov dword ptr [0x9dc428], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e99d: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e99e: pop ebx */
	m->esp += 4 + 0; return;	/* 43e99f: ret  */
L_43e9a0:
	{ DWORD a_ = M32((DWORD)(0x9dd304u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e9a0: cmp dword ptr [0x9dd304], ebx */
	if (m->zf) goto L_43ea06;	/* 43e9a6: je 0x43ea06 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e9a8: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_43ea06;	/* 43e9ae: jne 0x43ea06 */
	m->ecx = 0xcu;	/* 43e9b0: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e9b5: xor eax, eax */
	m->edi = 0x9dd20eu;	/* 43e9b7: mov edi, 0x9dd20e */
	M32((DWORD)(0x9dd304u)) = m->ebx;	/* 43e9bc: mov dword ptr [0x9dd304], ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43e9c2: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43e9c4: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 43e9c6: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e9cb: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e9ce: xor eax, eax */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 43e9d0: mov dword ptr [0x4e1868], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e9d6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e9d8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e9da: sub edi, ecx */
	m->eax = m->ecx;	/* 43e9dc: mov eax, ecx */
	m->esi = m->edi;	/* 43e9de: mov esi, edi */
	m->edi = 0x9dd20eu;	/* 43e9e0: mov edi, 0x9dd20e */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e9e5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e9e8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43e9ea: mov ecx, eax */
	m->eax = M32((DWORD)(0x9dc428u));	/* 43e9ec: mov eax, dword ptr [0x9dc428] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e9f1: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e9f4: cmp eax, 0xa */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e9f7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_43ea06;	/* 43e9f9: jne 0x43ea06 */
	m->esp -= 4; M32(m->esp) = 0x43ea00u; native_call(m, 0x4341a0u);	/* 43e9fb: call 0x4341a0 */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43ea00: mov dword ptr [0x9dc428], ebx */
L_43ea06:
	m->edi = M32(m->esp); m->esp += 4;	/* 43ea06: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43ea07: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43ea08: pop ebx */
	m->esp += 4 + 0; return;	/* 43ea09: ret  */
}

/* setup_drawSoundTab (0x4221d0), lifted by tools/lift.py */
static void lift_4221d0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4221d0: push ecx */
	m->eax = M32((DWORD)(0x4ddcecu));	/* 4221d1: mov eax, dword ptr [0x4ddcec] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4221d6: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4221d7: push edi */
	m->edi = 0x1u;	/* 4221d8: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4221dd: cmp eax, edi */
	if (m->zf) goto L_422452;	/* 4221df: je 0x422452 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4221e5: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4221e7: cmp eax, esi */
	if (m->zf) goto L_422452;	/* 4221e9: je 0x422452 */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4221ef: cmp dword ptr [0x90d1c4], esi */
	if (!m->zf) goto L_422452;	/* 4221f5: jne 0x422452 */
	{ DWORD a_ = M32((DWORD)(0x4ded8cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4221fb: cmp dword ptr [0x4ded8c], esi */
	if (m->zf) goto L_422209;	/* 422201: je 0x422209 */
	M32((DWORD)(0x4ddcecu)) = m->esi;	/* 422203: mov dword ptr [0x4ddcec], esi */
L_422209:
	{ DWORD a_ = M32((DWORD)(0x4ded88u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422209: cmp dword ptr [0x4ded88], esi */
	if (m->zf) goto L_422391;	/* 42220f: je 0x422391 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 422215: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 42221a: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422220: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 422221: push ecx */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 422222: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x422231u; native_call(m, 0x420670u);	/* 42222c: call 0x420670 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422231: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422234: cmp eax, 9 */
	if (!m->cf && !m->zf) goto L_422391;	/* 422237: ja 0x422391 */
	switch (m->eax) { case 0: goto L_422244; case 1: goto L_42226c; case 2: goto L_422295; case 3: goto L_422391; case 4: goto L_422391; case 5: goto L_4222cb; case 6: goto L_4222e7; case 7: goto L_422305; case 8: goto L_422320; case 9: goto L_422382; default: abort(); }	/* 42223d: jmp dword ptr [eax*4 + 0x422458] */
L_422244:
	m->eax = M32((DWORD)(0x4dde98u));	/* 422244: mov eax, dword ptr [0x4dde98] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422249: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_422391;	/* 42224b: jle 0x422391 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 422251: dec eax */
	M32((DWORD)(0x4dde90u)) = m->esi;	/* 422252: mov dword ptr [0x4dde90], esi */
	M32((DWORD)(0x4dde98u)) = m->eax;	/* 422258: mov dword ptr [0x4dde98], eax */
	M32((DWORD)(0x4ddb98u)) = 0x40a00000u;	/* 42225d: mov dword ptr [0x4ddb98], 0x40a00000 */
	goto L_422391;	/* 422267: jmp 0x422391 */
L_42226c:
	m->eax = M32((DWORD)(0x4dde98u));	/* 42226c: mov eax, dword ptr [0x4dde98] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422271: cmp eax, 0x64 */
	if (m->sf == m->of) goto L_422391;	/* 422274: jge 0x422391 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 42227a: inc eax */
	M32((DWORD)(0x4dde90u)) = m->edi;	/* 42227b: mov dword ptr [0x4dde90], edi */
	M32((DWORD)(0x4dde98u)) = m->eax;	/* 422281: mov dword ptr [0x4dde98], eax */
	M32((DWORD)(0x4ddb98u)) = 0x40a00000u;	/* 422286: mov dword ptr [0x4ddb98], 0x40a00000 */
	goto L_422391;	/* 422290: jmp 0x422391 */
L_422295:
	m->edx = M32((DWORD)(0x4ded68u));	/* 422295: mov edx, dword ptr [0x4ded68] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 42229b: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4222a1: sub edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x90u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4222a3: sub edx, 0x90 */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 4222a9: mov dword ptr [esp + 8], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x8u)));	/* 4222ad: fild dword ptr [esp + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f0u));	/* 4222b1: fmul dword ptr [0x4a94f0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4222b7: call 0x49ec14 */
	m->ecx = m->edi;	/* 4222bc: mov ecx, edi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4222be: sub ecx, eax */
	M32((DWORD)(0x4dde98u)) = m->ecx;	/* 4222c0: mov dword ptr [0x4dde98], ecx */
	goto L_422391;	/* 4222c6: jmp 0x422391 */
L_4222cb:
	m->eax = M32((DWORD)(0x4dde9cu));	/* 4222cb: mov eax, dword ptr [0x4dde9c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4222d0: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = 0x32u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4222d2: cmp eax, 0x32 */
	m->edx = (m->edx & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 4222d5: setge dl */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4222d8: dec edx */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4222d9: and edx, 0x64 */
	M32((DWORD)(0x4dde9cu)) = m->edx;	/* 4222dc: mov dword ptr [0x4dde9c], edx */
	goto L_422391;	/* 4222e2: jmp 0x422391 */
L_4222e7:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4222e7: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4222eeu; native_call(m, 0x41e760u);	/* 4222e9: call 0x41e760 */
	m->ecx = M32((DWORD)(0x4ddea0u));	/* 4222ee: mov ecx, dword ptr [0x4ddea0] */
	m->eax = m->edi;	/* 4222f4: mov eax, edi */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4222f6: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4222f9: sub eax, ecx */
	M32((DWORD)(0x4ddea0u)) = m->eax;	/* 4222fb: mov dword ptr [0x4ddea0], eax */
	goto L_422391;	/* 422300: jmp 0x422391 */
L_422305:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422305: push 2 */
	m->esp -= 4; M32(m->esp) = 0x42230cu; native_call(m, 0x41e760u);	/* 422307: call 0x41e760 */
	m->eax = M32((DWORD)(0x4ddea4u));	/* 42230c: mov eax, dword ptr [0x4ddea4] */
	m->ecx = m->edi;	/* 422311: mov ecx, edi */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422313: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 422316: sub ecx, eax */
	M32((DWORD)(0x4ddea4u)) = m->ecx;	/* 422318: mov dword ptr [0x4ddea4], ecx */
	goto L_422391;	/* 42231e: jmp 0x422391 */
L_422320:
	m->eax = M32((DWORD)(0x4dde98u));	/* 422320: mov eax, dword ptr [0x4dde98] */
	m->edx = M32((DWORD)(0x4dde9cu));	/* 422325: mov edx, dword ptr [0x4dde9c] */
	m->ecx = M32((DWORD)(0x4ddea0u));	/* 42232b: mov ecx, dword ptr [0x4ddea0] */
	M32((DWORD)(0x4e0c90u)) = m->eax;	/* 422331: mov dword ptr [0x4e0c90], eax */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0xfffffe0cu);	/* 422336: lea eax, [eax + eax*4 - 0x1f4] */
	M32((DWORD)(0x4e0c94u)) = m->edx;	/* 42233d: mov dword ptr [0x4e0c94], edx */
	m->edx = M32((DWORD)(0x4ddea4u));	/* 422343: mov edx, dword ptr [0x4ddea4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 422349: push esi */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42234a: shl eax, 2 */
	M32((DWORD)(0x4e0c98u)) = m->ecx;	/* 42234d: mov dword ptr [0x4e0c98], ecx */
	M32((DWORD)(0x4e0c9cu)) = m->edx;	/* 422353: mov dword ptr [0x4e0c9c], edx */
	M32((DWORD)(0x4dd984u)) = m->eax;	/* 422359: mov dword ptr [0x4dd984], eax */
	m->esp -= 4; M32(m->esp) = 0x422363u; native_call(m, 0x41e760u);	/* 42235e: call 0x41e760 */
	m->esp -= 4; M32(m->esp) = 0x422368u; native_call(m, 0x42d730u);	/* 422363: call 0x42d730 */
	M32((DWORD)(0x4ddcecu)) = m->esi;	/* 422368: mov dword ptr [0x4ddcec], esi */
	m->esp -= 4; M32(m->esp) = 0x422373u; native_call(m, 0x457310u);	/* 42236e: call 0x457310 */
	{ DWORD v_ = 0x4b01ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 422373: push 0x4b01cc */
	m->esp -= 4; M32(m->esp) = 0x42237du; native_call(m, 0x457150u);	/* 422378: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42237d: add esp, 8 */
	goto L_422391;	/* 422380: jmp 0x422391 */
L_422382:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 422382: push esi */
	m->esp -= 4; M32(m->esp) = 0x422388u; native_call(m, 0x41e760u);	/* 422383: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422388: add esp, 4 */
	M32((DWORD)(0x4ddcecu)) = m->esi;	/* 42238b: mov dword ptr [0x4ddcec], esi */
L_422391:
	{ DWORD a_ = M32((DWORD)(0x4ded94u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422391: cmp dword ptr [0x4ded94], esi */
	if (m->zf) goto L_422452;	/* 422397: je 0x422452 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 42239d: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 4223a3: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4223a9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4223ab: test ah, 0x41 */
	if (!m->zf) goto L_422452;	/* 4223ae: jne 0x422452 */
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 4223b4: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 4223ba: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4223c0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4223c1: push edx */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4223c2: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x4223d1u; native_call(m, 0x420670u);	/* 4223cc: call 0x420670 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4223d1: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4223d4: sub eax, esi */
	if (m->zf) goto L_422433;	/* 4223d6: je 0x422433 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4223d8: dec eax */
	if (m->zf) goto L_42240f;	/* 4223d9: je 0x42240f */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4223db: dec eax */
	if (!m->zf) goto L_422452;	/* 4223dc: jne 0x422452 */
	m->eax = M32((DWORD)(0x4ded68u));	/* 4223de: mov eax, dword ptr [0x4ded68] */
	m->esi = M32((DWORD)(0x4ddad0u));	/* 4223e3: mov esi, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4223e9: sub eax, esi */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4223eb: sub eax, 0x90 */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 4223f0: mov dword ptr [esp + 8], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x8u)));	/* 4223f4: fild dword ptr [esp + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f0u));	/* 4223f8: fmul dword ptr [0x4a94f0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4223fe: call 0x49ec14 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 422403: sub edi, eax */
	M32((DWORD)(0x4dde98u)) = m->edi;	/* 422405: mov dword ptr [0x4dde98], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 42240b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42240c: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 42240d: pop ecx */
	m->esp += 4 + 0; return;	/* 42240e: ret  */
L_42240f:
	m->eax = M32((DWORD)(0x4dde98u));	/* 42240f: mov eax, dword ptr [0x4dde98] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422414: cmp eax, 0x64 */
	if (m->sf == m->of) goto L_422452;	/* 422417: jge 0x422452 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 422419: inc eax */
	M32((DWORD)(0x4dde90u)) = m->edi;	/* 42241a: mov dword ptr [0x4dde90], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 422420: pop edi */
	M32((DWORD)(0x4dde98u)) = m->eax;	/* 422421: mov dword ptr [0x4dde98], eax */
	M32((DWORD)(0x4ddb98u)) = 0x40a00000u;	/* 422426: mov dword ptr [0x4ddb98], 0x40a00000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422430: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 422431: pop ecx */
	m->esp += 4 + 0; return;	/* 422432: ret  */
L_422433:
	m->eax = M32((DWORD)(0x4dde98u));	/* 422433: mov eax, dword ptr [0x4dde98] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422438: cmp eax, esi */
	if (m->zf || m->sf != m->of) goto L_422452;	/* 42243a: jle 0x422452 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42243c: dec eax */
	M32((DWORD)(0x4dde90u)) = m->esi;	/* 42243d: mov dword ptr [0x4dde90], esi */
	M32((DWORD)(0x4dde98u)) = m->eax;	/* 422443: mov dword ptr [0x4dde98], eax */
	M32((DWORD)(0x4ddb98u)) = 0x40a00000u;	/* 422448: mov dword ptr [0x4ddb98], 0x40a00000 */
L_422452:
	m->edi = M32(m->esp); m->esp += 4;	/* 422452: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422453: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 422454: pop ecx */
	m->esp += 4 + 0; return;	/* 422455: ret  */
}

/* setup_controlTabKeys (0x422e10), lifted by tools/lift.py */
static void lift_422e10(X86 *m)
{
	m->eax = M32((DWORD)(0x9da440u));	/* 422e10: mov eax, dword ptr [0x9da440] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422e15: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 422e16: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422e17: push eax */
	m->esp -= 4; M32(m->esp) = 0x422e1du; native_call(m, 0x401600u);	/* 422e18: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422e1d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422e20: test eax, eax */
	if (m->zf) goto L_422e31;	/* 422e22: je 0x422e31 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 422e24: push 6 */
	m->esp -= 4; M32(m->esp) = 0x422e2bu; native_call(m, 0x41e760u);	/* 422e26: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422e2b: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422e2e: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422e2f: pop ebx */
	m->esp += 4 + 0; return;	/* 422e30: ret  */
L_422e31:
	m->eax = M32((DWORD)(0x4dddc8u));	/* 422e31: mov eax, dword ptr [0x4dddc8] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 422e36: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422e38: cmp eax, ebx */
	if (m->zf) goto L_422eb9;	/* 422e3a: je 0x422eb9 */
	m->ecx = M32((DWORD)(0x9da440u));	/* 422e3c: mov ecx, dword ptr [0x9da440] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 422e42: push ecx */
	m->esp -= 4; M32(m->esp) = 0x422e48u; native_call(m, 0x401600u);	/* 422e43: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422e48: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422e4b: test eax, eax */
	if (m->zf) goto L_422e5c;	/* 422e4d: je 0x422e5c */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 422e4f: push 6 */
	m->esp -= 4; M32(m->esp) = 0x422e56u; native_call(m, 0x41e760u);	/* 422e51: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422e56: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422e59: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422e5a: pop ebx */
	m->esp += 4 + 0; return;	/* 422e5b: ret  */
L_422e5c:
	m->edx = M32((DWORD)(0x76d48cu));	/* 422e5c: mov edx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 422e62: push edx */
	m->esp -= 4; M32(m->esp) = 0x422e68u; native_call(m, 0x401600u);	/* 422e63: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422e68: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422e6b: test eax, eax */
	if (m->zf) goto L_422e82;	/* 422e6d: je 0x422e82 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 422e6f: push 1 */
	m->esp -= 4; M32(m->esp) = 0x422e76u; native_call(m, 0x41e760u);	/* 422e71: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422e76: add esp, 4 */
	M32((DWORD)(0x4dddc8u)) = m->ebx;	/* 422e79: mov dword ptr [0x4dddc8], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 422e7f: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422e80: pop ebx */
	m->esp += 4 + 0; return;	/* 422e81: ret  */
L_422e82:
	m->esi = 0x2u;	/* 422e82: mov esi, 2 */
L_422e87:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 422e87: push esi */
	m->esp -= 4; M32(m->esp) = 0x422e8du; native_call(m, 0x401600u);	/* 422e88: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422e8d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422e90: test eax, eax */
	if (!m->zf) goto L_422ea0;	/* 422e92: jne 0x422ea0 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 422e94: inc esi */
	{ DWORD a_ = m->esi, b_ = 0xdeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422e95: cmp esi, 0xde */
	if (m->sf != m->of) goto L_422e87;	/* 422e9b: jl 0x422e87 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422e9d: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422e9e: pop ebx */
	m->esp += 4 + 0; return;	/* 422e9f: ret  */
L_422ea0:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422ea0: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422ea7u; native_call(m, 0x41e760u);	/* 422ea2: call 0x41e760 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 422ea7: push esi */
	m->esp -= 4; M32(m->esp) = 0x422eadu; native_call(m, 0x421680u);	/* 422ea8: call 0x421680 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422ead: add esp, 8 */
	M32((DWORD)(0x4dddc8u)) = m->ebx;	/* 422eb0: mov dword ptr [0x4dddc8], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 422eb6: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422eb7: pop ebx */
	m->esp += 4 + 0; return;	/* 422eb8: ret  */
L_422eb9:
	m->eax = M32((DWORD)(0x9dae70u));	/* 422eb9: mov eax, dword ptr [0x9dae70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422ebe: push eax */
	m->esp -= 4; M32(m->esp) = 0x422ec4u; native_call(m, 0x401600u);	/* 422ebf: call 0x401600 */
	m->esi = 0x1u;	/* 422ec4: mov esi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422ec9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422ecc: cmp eax, esi */
	if (!m->zf) goto L_422f08;	/* 422ece: jne 0x422f08 */
	{ DWORD a_ = M32((DWORD)(0x4de040u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422ed0: cmp dword ptr [0x4de040], ebx */
	if (m->sf != m->of) goto L_42309a;	/* 422ed6: jl 0x42309a */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422edc: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422ee3u; native_call(m, 0x41e760u);	/* 422ede: call 0x41e760 */
	m->eax = M32((DWORD)(0x4de040u));	/* 422ee3: mov eax, dword ptr [0x4de040] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422ee8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422eeb: cmp eax, 0xa */
	if (!m->zf) goto L_422eff;	/* 422eee: jne 0x422eff */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(0x4de1c0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 422ef0: sub esi, dword ptr [0x4de1c0] */
	M32((DWORD)(0x4de1c0u)) = m->esi;	/* 422ef6: mov dword ptr [0x4de1c0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422efc: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422efd: pop ebx */
	m->esp += 4 + 0; return;	/* 422efe: ret  */
L_422eff:
	M32((DWORD)(0x4dddc8u)) = m->esi;	/* 422eff: mov dword ptr [0x4dddc8], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422f05: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422f06: pop ebx */
	m->esp += 4 + 0; return;	/* 422f07: ret  */
L_422f08:
	m->ecx = M32((DWORD)(0x9db0a0u));	/* 422f08: mov ecx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 422f0e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x422f14u; native_call(m, 0x401600u);	/* 422f0f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422f14: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422f17: cmp eax, esi */
	if (!m->zf) goto L_422f31;	/* 422f19: jne 0x422f31 */
	m->eax = M32((DWORD)(0x4de040u));	/* 422f1b: mov eax, dword ptr [0x4de040] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422f20: cmp eax, ebx */
	if (m->sf != m->of) goto L_42309a;	/* 422f22: jl 0x42309a */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 422f28: dec eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 422f29: pop esi */
	M32((DWORD)(0x4de040u)) = m->eax;	/* 422f2a: mov dword ptr [0x4de040], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422f2f: pop ebx */
	m->esp += 4 + 0; return;	/* 422f30: ret  */
L_422f31:
	m->edx = M32((DWORD)(0x76d330u));	/* 422f31: mov edx, dword ptr [0x76d330] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 422f37: push edx */
	m->esp -= 4; M32(m->esp) = 0x422f3du; native_call(m, 0x401600u);	/* 422f38: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422f3d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422f40: cmp eax, esi */
	if (!m->zf) goto L_422f67;	/* 422f42: jne 0x422f67 */
	m->eax = M32((DWORD)(0x4ddce8u));	/* 422f44: mov eax, dword ptr [0x4ddce8] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b04ecu));	/* 422f49: mov ecx, dword ptr [eax*4 + 0x4b04ec] */
	m->eax = M32((DWORD)(0x4de040u));	/* 422f50: mov eax, dword ptr [0x4de040] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 422f55: dec ecx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422f56: cmp eax, ecx */
	if (m->sf == m->of) goto L_42309a;	/* 422f58: jge 0x42309a */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 422f5e: inc eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 422f5f: pop esi */
	M32((DWORD)(0x4de040u)) = m->eax;	/* 422f60: mov dword ptr [0x4de040], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422f65: pop ebx */
	m->esp += 4 + 0; return;	/* 422f66: ret  */
L_422f67:
	m->edx = M32((DWORD)(0x4e1508u));	/* 422f67: mov edx, dword ptr [0x4e1508] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 422f6d: push edx */
	m->esp -= 4; M32(m->esp) = 0x422f73u; native_call(m, 0x401600u);	/* 422f6e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422f73: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422f76: cmp eax, esi */
	if (!m->zf) goto L_422f8d;	/* 422f78: jne 0x422f8d */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422f7a: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422f81u; native_call(m, 0x41e760u);	/* 422f7c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422f81: add esp, 4 */
	M32((DWORD)(0x4ddce8u)) = m->ebx;	/* 422f84: mov dword ptr [0x4ddce8], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 422f8a: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422f8b: pop ebx */
	m->esp += 4 + 0; return;	/* 422f8c: ret  */
L_422f8d:
	m->eax = M32((DWORD)(0x4e1524u));	/* 422f8d: mov eax, dword ptr [0x4e1524] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422f92: push eax */
	m->esp -= 4; M32(m->esp) = 0x422f98u; native_call(m, 0x401600u);	/* 422f93: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422f98: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422f9b: cmp eax, esi */
	if (!m->zf) goto L_422fb2;	/* 422f9d: jne 0x422fb2 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422f9f: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422fa6u; native_call(m, 0x41e760u);	/* 422fa1: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422fa6: add esp, 4 */
	M32((DWORD)(0x4ddce8u)) = m->esi;	/* 422fa9: mov dword ptr [0x4ddce8], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422faf: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422fb0: pop ebx */
	m->esp += 4 + 0; return;	/* 422fb1: ret  */
L_422fb2:
	m->ecx = M32((DWORD)(0x4e14f4u));	/* 422fb2: mov ecx, dword ptr [0x4e14f4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 422fb8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x422fbeu; native_call(m, 0x401600u);	/* 422fb9: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422fbe: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422fc1: cmp eax, esi */
	if (!m->zf) goto L_422fdc;	/* 422fc3: jne 0x422fdc */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422fc5: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422fccu; native_call(m, 0x41e760u);	/* 422fc7: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422fcc: add esp, 4 */
	M32((DWORD)(0x4ddce8u)) = 0x2u;	/* 422fcf: mov dword ptr [0x4ddce8], 2 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422fd9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422fda: pop ebx */
	m->esp += 4 + 0; return;	/* 422fdb: ret  */
L_422fdc:
	m->edx = M32((DWORD)(0x4e1530u));	/* 422fdc: mov edx, dword ptr [0x4e1530] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 422fe2: push edx */
	m->esp -= 4; M32(m->esp) = 0x422fe8u; native_call(m, 0x401600u);	/* 422fe3: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422fe8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422feb: cmp eax, esi */
	if (!m->zf) goto L_423006;	/* 422fed: jne 0x423006 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422fef: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422ff6u; native_call(m, 0x41e760u);	/* 422ff1: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422ff6: add esp, 4 */
	M32((DWORD)(0x4ddce8u)) = 0x3u;	/* 422ff9: mov dword ptr [0x4ddce8], 3 */
	m->esi = M32(m->esp); m->esp += 4;	/* 423003: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 423004: pop ebx */
	m->esp += 4 + 0; return;	/* 423005: ret  */
L_423006:
	m->eax = M32((DWORD)(0x4e0cd4u));	/* 423006: mov eax, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42300b: push eax */
	m->esp -= 4; M32(m->esp) = 0x423011u; native_call(m, 0x401600u);	/* 42300c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423011: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423014: cmp eax, esi */
	if (!m->zf) goto L_423042;	/* 423016: jne 0x423042 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 423018: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 423019: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42301fu; native_call(m, 0x41e760u);	/* 42301a: call 0x41e760 */
	m->ecx = 0x44u;	/* 42301f: mov ecx, 0x44 */
	m->esi = 0x4de0c0u;	/* 423024: mov esi, 0x4de0c0 */
	m->edi = 0x4def00u;	/* 423029: mov edi, 0x4def00 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42302e: add esp, 4 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 423031: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x423038u; native_call(m, 0x42d730u);	/* 423033: call 0x42d730 */
	m->edi = M32(m->esp); m->esp += 4;	/* 423038: pop edi */
	M32((DWORD)(0x4ddcecu)) = m->ebx;	/* 423039: mov dword ptr [0x4ddcec], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 42303f: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 423040: pop ebx */
	m->esp += 4 + 0; return;	/* 423041: ret  */
L_423042:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 423042: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423048: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42304eu; native_call(m, 0x401600u);	/* 423049: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42304e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423051: cmp eax, esi */
	if (m->zf) goto L_42308b;	/* 423053: je 0x42308b */
	m->edx = M32((DWORD)(0x4e0ce0u));	/* 423055: mov edx, dword ptr [0x4e0ce0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42305b: push edx */
	m->esp -= 4; M32(m->esp) = 0x423061u; native_call(m, 0x401600u);	/* 42305c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423061: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423064: cmp eax, esi */
	if (!m->zf) goto L_423079;	/* 423066: jne 0x423079 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 423068: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42306eu; native_call(m, 0x41e760u);	/* 423069: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42306e: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x423076u; native_call(m, 0x420c10u);	/* 423071: call 0x420c10 */
	m->esi = M32(m->esp); m->esp += 4;	/* 423076: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 423077: pop ebx */
	m->esp += 4 + 0; return;	/* 423078: ret  */
L_423079:
	m->eax = M32((DWORD)(0x76d48cu));	/* 423079: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42307e: push eax */
	m->esp -= 4; M32(m->esp) = 0x423084u; native_call(m, 0x401600u);	/* 42307f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423084: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 423087: test eax, eax */
	if (m->zf) goto L_42309a;	/* 423089: je 0x42309a */
L_42308b:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42308b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x423091u; native_call(m, 0x41e760u);	/* 42308c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423091: add esp, 4 */
	M32((DWORD)(0x4ddcecu)) = m->ebx;	/* 423094: mov dword ptr [0x4ddcec], ebx */
L_42309a:
	m->esi = M32(m->esp); m->esp += 4;	/* 42309a: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42309b: pop ebx */
	m->esp += 4 + 0; return;	/* 42309c: ret  */
}

/* setup_drawControlTab (0x422830), lifted by tools/lift.py */
static void lift_422830(X86 *m)
{
	m->eax = M32((DWORD)(0x4ddcecu));	/* 422830: mov eax, dword ptr [0x4ddcec] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422835: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 422836: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 422837: push esi */
	m->esi = 0x1u;	/* 422838: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42283d: cmp eax, esi */
	if (m->zf) goto L_422ade;	/* 42283f: je 0x422ade */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 422845: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422847: cmp eax, ebx */
	if (m->zf) goto L_422ade;	/* 422849: je 0x422ade */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42284f: cmp dword ptr [0x90d1c4], ebx */
	if (!m->zf) goto L_422ade;	/* 422855: jne 0x422ade */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 42285b: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422860: cmp eax, ebx */
	m->eax = M32((DWORD)(0x4dddc8u));	/* 422862: mov eax, dword ptr [0x4dddc8] */
	if (m->zf) goto L_42288b;	/* 422867: je 0x42288b */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422869: cmp eax, ebx */
	if (m->zf) goto L_422885;	/* 42286b: je 0x422885 */
	m->eax = M32((DWORD)(0x76d424u));	/* 42286d: mov eax, dword ptr [0x76d424] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422872: push eax */
	m->esp -= 4; M32(m->esp) = 0x422878u; native_call(m, 0x421680u);	/* 422873: call 0x421680 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422878: add esp, 4 */
	M32((DWORD)(0x4dddc8u)) = m->ebx;	/* 42287b: mov dword ptr [0x4dddc8], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 422881: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 422882: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422883: pop ebx */
	m->esp += 4 + 0; return;	/* 422884: ret  */
L_422885:
	M32((DWORD)(0x4ddcecu)) = m->ebx;	/* 422885: mov dword ptr [0x4ddcec], ebx */
L_42288b:
	{ DWORD a_ = M32((DWORD)(0x4ded70u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42288b: cmp dword ptr [0x4ded70], ebx */
	if (m->zf) goto L_4228d4;	/* 422891: je 0x4228d4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422893: cmp eax, ebx */
	if (m->zf) goto L_4228d4;	/* 422895: je 0x4228d4 */
	m->eax = M32((DWORD)(0x4ded7cu));	/* 422897: mov eax, dword ptr [0x4ded7c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42289c: cmp eax, ebx */
	if (m->sf == m->of) goto L_4228b9;	/* 42289e: jge 0x4228b9 */
	m->ecx = M32((DWORD)(0x9da490u));	/* 4228a0: mov ecx, dword ptr [0x9da490] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4228a6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4228acu; native_call(m, 0x421680u);	/* 4228a7: call 0x421680 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4228ac: add esp, 4 */
	M32((DWORD)(0x4dddc8u)) = m->ebx;	/* 4228af: mov dword ptr [0x4dddc8], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 4228b5: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4228b6: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4228b7: pop ebx */
	m->esp += 4 + 0; return;	/* 4228b8: ret  */
L_4228b9:
	if (m->zf || m->sf != m->of) goto L_4228ca;	/* 4228b9: jle 0x4228ca */
	m->edx = M32((DWORD)(0x76d490u));	/* 4228bb: mov edx, dword ptr [0x76d490] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4228c1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4228c7u; native_call(m, 0x421680u);	/* 4228c2: call 0x421680 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4228c7: add esp, 4 */
L_4228ca:
	m->esi = M32(m->esp); m->esp += 4;	/* 4228ca: pop esi */
	M32((DWORD)(0x4dddc8u)) = m->ebx;	/* 4228cb: mov dword ptr [0x4dddc8], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4228d1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4228d2: pop ebx */
	m->esp += 4 + 0; return;	/* 4228d3: ret  */
L_4228d4:
	m->ecx = M32((DWORD)(0x4ded88u));	/* 4228d4: mov ecx, dword ptr [0x4ded88] */
	m->ebp = 0x3u;	/* 4228da: mov ebp, 3 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4228df: cmp ecx, ebx */
	if (m->zf) goto L_422a9c;	/* 4228e1: je 0x422a9c */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4228e7: cmp eax, ebx */
	if (m->zf) goto L_422903;	/* 4228e9: je 0x422903 */
	m->eax = M32((DWORD)(0x4de73cu));	/* 4228eb: mov eax, dword ptr [0x4de73c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4228f0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4228f6u; native_call(m, 0x421680u);	/* 4228f1: call 0x421680 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4228f6: add esp, 4 */
	M32((DWORD)(0x4dddc8u)) = m->ebx;	/* 4228f9: mov dword ptr [0x4dddc8], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 4228ff: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 422900: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422901: pop ebx */
	m->esp += 4 + 0; return;	/* 422902: ret  */
L_422903:
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 422903: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 422909: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42290f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 422910: push edx */
	m->esp -= 4; M32(m->esp) = 0x422916u; native_call(m, 0x4206f0u);	/* 422911: call 0x4206f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422916: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422919: cmp eax, 0x11 */
	if (!m->cf && !m->zf) goto L_422a9c;	/* 42291c: ja 0x422a9c */
	m->edx = M32((DWORD)(0x4de040u));	/* 422922: mov edx, dword ptr [0x4de040] */
	m->ecx = M32((DWORD)(0x4ddce8u));	/* 422928: mov ecx, dword ptr [0x4ddce8] */
	switch (m->eax) { case 0: goto L_422935; case 1: goto L_42294a; case 2: goto L_42295f; case 3: goto L_422978; case 4: goto L_42298d; case 5: goto L_4229b9; case 6: goto L_4229cd; case 7: goto L_4229e0; case 8: goto L_422a03; case 9: goto L_422a26; case 10: goto L_422a33; case 11: goto L_422a5e; case 12: goto L_422a89; case 13: goto L_422a89; case 14: goto L_422a89; case 15: goto L_422a89; case 16: goto L_422a89; case 17: goto L_422a89; default: abort(); }	/* 42292e: jmp dword ptr [eax*4 + 0x422ae4] */
L_422935:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422935: push 2 */
	m->esp -= 4; M32(m->esp) = 0x42293cu; native_call(m, 0x41e760u);	/* 422937: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42293c: add esp, 4 */
	M32((DWORD)(0x4ddce8u)) = m->ebx;	/* 42293f: mov dword ptr [0x4ddce8], ebx */
	goto L_422a9c;	/* 422945: jmp 0x422a9c */
L_42294a:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42294a: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422951u; native_call(m, 0x41e760u);	/* 42294c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422951: add esp, 4 */
	M32((DWORD)(0x4ddce8u)) = m->esi;	/* 422954: mov dword ptr [0x4ddce8], esi */
	goto L_422a9c;	/* 42295a: jmp 0x422a9c */
L_42295f:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42295f: push 2 */
	m->esp -= 4; M32(m->esp) = 0x422966u; native_call(m, 0x41e760u);	/* 422961: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422966: add esp, 4 */
	M32((DWORD)(0x4ddce8u)) = 0x2u;	/* 422969: mov dword ptr [0x4ddce8], 2 */
	goto L_422a9c;	/* 422973: jmp 0x422a9c */
L_422978:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 422978: push 2 */
	m->esp -= 4; M32(m->esp) = 0x42297fu; native_call(m, 0x41e760u);	/* 42297a: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42297f: add esp, 4 */
	M32((DWORD)(0x4ddce8u)) = m->ebp;	/* 422982: mov dword ptr [0x4ddce8], ebp */
	goto L_422a9c;	/* 422988: jmp 0x422a9c */
L_42298d:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42298d: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42298e: push ebx */
	m->esp -= 4; M32(m->esp) = 0x422994u; native_call(m, 0x41e760u);	/* 42298f: call 0x41e760 */
	m->ecx = 0x44u;	/* 422994: mov ecx, 0x44 */
	m->esi = 0x4de0c0u;	/* 422999: mov esi, 0x4de0c0 */
	m->edi = 0x4def00u;	/* 42299e: mov edi, 0x4def00 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4229a3: add esp, 4 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4229a6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x4229adu; native_call(m, 0x42d730u);	/* 4229a8: call 0x42d730 */
	M32((DWORD)(0x4ddcecu)) = m->ebx;	/* 4229ad: mov dword ptr [0x4ddcec], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 4229b3: pop edi */
	goto L_422a9c;	/* 4229b4: jmp 0x422a9c */
L_4229b9:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4229b9: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4229bfu; native_call(m, 0x41e760u);	/* 4229ba: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4229bf: add esp, 4 */
	M32((DWORD)(0x4ddcecu)) = m->ebx;	/* 4229c2: mov dword ptr [0x4ddcec], ebx */
	goto L_422a9c;	/* 4229c8: jmp 0x422a9c */
L_4229cd:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4229cd: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4229d3u; native_call(m, 0x41e760u);	/* 4229ce: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4229d3: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4229dbu; native_call(m, 0x420c10u);	/* 4229d6: call 0x420c10 */
	goto L_422a9c;	/* 4229db: jmp 0x422a9c */
L_4229e0:
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4229e0: cmp edx, ebx */
	if (m->sf != m->of) goto L_422a26;	/* 4229e2: jl 0x422a26 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4229e4: cmp ecx, ebp */
	if (!m->zf) goto L_422a03;	/* 4229e6: jne 0x422a03 */
	m->edx = M32((DWORD)(0x4de1c0u));	/* 4229e8: mov edx, dword ptr [0x4de1c0] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4229ee: push ebx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4229ef: sub esi, edx */
	M32((DWORD)(0x4de1c0u)) = m->esi;	/* 4229f1: mov dword ptr [0x4de1c0], esi */
	m->esp -= 4; M32(m->esp) = 0x4229fcu; native_call(m, 0x41e760u);	/* 4229f7: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4229fc: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4229ff: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 422a00: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422a01: pop ebx */
	m->esp += 4 + 0; return;	/* 422a02: ret  */
L_422a03:
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a03: cmp edx, ebx */
	if (m->sf != m->of) goto L_422a26;	/* 422a05: jl 0x422a26 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a07: cmp ecx, ebp */
	if (!m->zf) goto L_422a89;	/* 422a09: jne 0x422a89 */
	m->edx = M32((DWORD)(0x4de1c4u));	/* 422a0b: mov edx, dword ptr [0x4de1c4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422a11: push ebx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 422a12: sub esi, edx */
	M32((DWORD)(0x4de1c4u)) = m->esi;	/* 422a14: mov dword ptr [0x4de1c4], esi */
	m->esp -= 4; M32(m->esp) = 0x422a1fu; native_call(m, 0x41e760u);	/* 422a1a: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422a1f: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422a22: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 422a23: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422a24: pop ebx */
	m->esp += 4 + 0; return;	/* 422a25: ret  */
L_422a26:
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a26: cmp ecx, ebp */
	if (!m->zf) goto L_422a89;	/* 422a28: jne 0x422a89 */
	m->esp -= 4; M32(m->esp) = 0x422a2fu; native_call(m, 0x4226b0u);	/* 422a2a: call 0x4226b0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422a2f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 422a30: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422a31: pop ebx */
	m->esp += 4 + 0; return;	/* 422a32: ret  */
L_422a33:
	{ DWORD a_ = M32((DWORD)(0x4ddce8u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a33: cmp dword ptr [0x4ddce8], ebp */
	if (!m->zf) goto L_422a89;	/* 422a39: jne 0x422a89 */
	m->eax = M32((DWORD)(0x4de1ccu));	/* 422a3b: mov eax, dword ptr [0x4de1cc] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 422a40: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a41: cmp eax, 7 */
	M32((DWORD)(0x4de1ccu)) = m->eax;	/* 422a44: mov dword ptr [0x4de1cc], eax */
	if (m->zf || m->sf != m->of) goto L_422a51;	/* 422a49: jle 0x422a51 */
	M32((DWORD)(0x4de1ccu)) = m->ebx;	/* 422a4b: mov dword ptr [0x4de1cc], ebx */
L_422a51:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422a51: push ebx */
	m->esp -= 4; M32(m->esp) = 0x422a57u; native_call(m, 0x41e760u);	/* 422a52: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422a57: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422a5a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 422a5b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422a5c: pop ebx */
	m->esp += 4 + 0; return;	/* 422a5d: ret  */
L_422a5e:
	{ DWORD a_ = M32((DWORD)(0x4ddce8u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a5e: cmp dword ptr [0x4ddce8], ebp */
	if (!m->zf) goto L_422a89;	/* 422a64: jne 0x422a89 */
	m->eax = M32((DWORD)(0x4de1ccu));	/* 422a66: mov eax, dword ptr [0x4de1cc] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 422a6b: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a6c: cmp eax, 7 */
	M32((DWORD)(0x4de1ccu)) = m->eax;	/* 422a6f: mov dword ptr [0x4de1cc], eax */
	if (m->zf || m->sf != m->of) goto L_422a7c;	/* 422a74: jle 0x422a7c */
	M32((DWORD)(0x4de1ccu)) = m->ebx;	/* 422a76: mov dword ptr [0x4de1cc], ebx */
L_422a7c:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422a7c: push ebx */
	m->esp -= 4; M32(m->esp) = 0x422a82u; native_call(m, 0x41e760u);	/* 422a7d: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422a82: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422a85: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 422a86: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422a87: pop ebx */
	m->esp += 4 + 0; return;	/* 422a88: ret  */
L_422a89:
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a89: cmp edx, ebx */
	if (m->sf != m->of) goto L_422a9c;	/* 422a8b: jl 0x422a9c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 422a8d: push ebx */
	M32((DWORD)(0x4dddc8u)) = m->esi;	/* 422a8e: mov dword ptr [0x4dddc8], esi */
	m->esp -= 4; M32(m->esp) = 0x422a99u; native_call(m, 0x41e760u);	/* 422a94: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422a99: add esp, 4 */
L_422a9c:
	{ DWORD a_ = M32((DWORD)(0x4ded94u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422a9c: cmp dword ptr [0x4ded94], ebx */
	if (m->zf) goto L_422ade;	/* 422aa2: je 0x422ade */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 422aa4: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 422aaa: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 422ab0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 422ab2: test ah, 0x41 */
	if (!m->zf) goto L_422ade;	/* 422ab5: jne 0x422ade */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 422ab7: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 422abc: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422ac2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 422ac3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x422ac9u; native_call(m, 0x4206f0u);	/* 422ac4: call 0x4206f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422ac9: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422acc: cmp eax, 9 */
	if (!m->zf) goto L_422ade;	/* 422acf: jne 0x422ade */
	{ DWORD a_ = M32((DWORD)(0x4ddce8u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422ad1: cmp dword ptr [0x4ddce8], ebp */
	if (!m->zf) goto L_422ade;	/* 422ad7: jne 0x422ade */
	m->esp -= 4; M32(m->esp) = 0x422adeu; native_call(m, 0x4226b0u);	/* 422ad9: call 0x4226b0 */
L_422ade:
	m->esi = M32(m->esp); m->esp += 4;	/* 422ade: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 422adf: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 422ae0: pop ebx */
	m->esp += 4 + 0; return;	/* 422ae1: ret  */
}

/* room_43df80 (0x43df80), lifted by tools/lift.py */
static void lift_43df80(X86 *m)
{
	m->eax = M32((DWORD)(0x9dced0u));	/* 43df80: mov eax, dword ptr [0x9dced0] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43df85: push ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 43df86: xor ebx, ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43df88: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43df89: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43df8a: cmp eax, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43df8c: push edi */
	if (m->zf) goto L_43dfa4;	/* 43df8d: je 0x43dfa4 */
	m->esp -= 4; M32(m->esp) = 0x43df94u; native_call(m, 0x432be0u);	/* 43df8f: call 0x432be0 */
	m->esp -= 4; M32(m->esp) = 0x43df99u; native_call(m, 0x433bb0u);	/* 43df94: call 0x433bb0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43df99: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43df9a: pop esi */
	M32((DWORD)(0x9dced0u)) = m->ebx;	/* 43df9b: mov dword ptr [0x9dced0], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43dfa1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43dfa2: pop ebx */
	m->esp += 4 + 0; return;	/* 43dfa3: ret  */
L_43dfa4:
	m->eax = M32((DWORD)(0x9dd198u));	/* 43dfa4: mov eax, dword ptr [0x9dd198] */
	m->ebp = 0x1u;	/* 43dfa9: mov ebp, 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43dfae: cmp eax, ebp */
	if (!m->zf) goto L_43dfc7;	/* 43dfb0: jne 0x43dfc7 */
	m->esp -= 4; M32(m->esp) = 0x43dfb7u; native_call(m, 0x433c70u);	/* 43dfb2: call 0x433c70 */
	m->esp -= 4; M32(m->esp) = 0x43dfbcu; native_call(m, 0x434490u);	/* 43dfb7: call 0x434490 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43dfbc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43dfbd: pop esi */
	M32((DWORD)(0x9dd198u)) = m->ebx;	/* 43dfbe: mov dword ptr [0x9dd198], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43dfc4: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43dfc5: pop ebx */
	m->esp += 4 + 0; return;	/* 43dfc6: ret  */
L_43dfc7:
	{ DWORD a_ = M32((DWORD)(0x9dd830u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43dfc7: cmp dword ptr [0x9dd830], ebx */
	if (m->zf) goto L_43e0a5;	/* 43dfcd: je 0x43e0a5 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43dfd3: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_43e232;	/* 43dfd9: jne 0x43e232 */
	m->ecx = 0x7u;	/* 43dfdf: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43dfe4: xor eax, eax */
	m->edi = 0x9dd1d8u;	/* 43dfe6: mov edi, 0x9dd1d8 */
	M32((DWORD)(0x9dd830u)) = m->ebx;	/* 43dfeb: mov dword ptr [0x9dd830], ebx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43dff1: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43dff3: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 43dff5: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43dffa: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43dffd: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43dfff: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e001: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e003: sub edi, ecx */
	m->eax = m->ecx;	/* 43e005: mov eax, ecx */
	m->esi = m->edi;	/* 43e007: mov esi, edi */
	m->edi = 0x9dd1d8u;	/* 43e009: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e00e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e011: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43e013: mov ecx, eax */
	m->eax = M32((DWORD)(0x9dc428u));	/* 43e015: mov eax, dword ptr [0x9dc428] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e01a: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e01d: cmp eax, 0xa */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e020: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_43e07a;	/* 43e022: jne 0x43e07a */
	m->ecx = M32((DWORD)(0x9dd358u));	/* 43e024: mov ecx, dword ptr [0x9dd358] */
	m->edx = M32((DWORD)(0x9dd364u));	/* 43e02a: mov edx, dword ptr [0x9dd364] */
	{ DWORD a_ = m->ecx, b_ = 0x1a2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43e030: add ecx, 0x1a2 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e036: pop edi */
	M32((DWORD)(0x76d42cu)) = m->ebp;	/* 43e037: mov dword ptr [0x76d42c], ebp */
	{ DWORD a_ = m->edx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43e03d: add edx, -0x30 */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e040: pop esi */
	M32((DWORD)(0x9dd1ccu)) = m->ebx;	/* 43e041: mov dword ptr [0x9dd1cc], ebx */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43e047: mov dword ptr [0x9dc428], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e04d: pop ebp */
	M32((DWORD)(0x74de1cu)) = 0x3u;	/* 43e04e: mov dword ptr [0x74de1c], 3 */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 43e058: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 43e062: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->ecx;	/* 43e06c: mov dword ptr [0x67ef34], ecx */
	M32((DWORD)(0x67fb38u)) = m->edx;	/* 43e072: mov dword ptr [0x67fb38], edx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e078: pop ebx */
	m->esp += 4 + 0; return;	/* 43e079: ret  */
L_43e07a:
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e07a: cmp eax, 0x14 */
	if (!m->zf) goto L_43e232;	/* 43e07d: jne 0x43e232 */
	M32((DWORD)(0x9dd1ccu)) = m->ebx;	/* 43e083: mov dword ptr [0x9dd1cc], ebx */
	m->esp -= 4; M32(m->esp) = 0x43e08eu; native_call(m, 0x433bb0u);	/* 43e089: call 0x433bb0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e08e: pop edi */
	M32((DWORD)(0x9dd6b0u)) = m->ebp;	/* 43e08f: mov dword ptr [0x9dd6b0], ebp */
	M32((DWORD)(0x4e1868u)) = m->ebp;	/* 43e095: mov dword ptr [0x4e1868], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e09b: pop esi */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43e09c: mov dword ptr [0x9dc428], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e0a2: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e0a3: pop ebx */
	m->esp += 4 + 0; return;	/* 43e0a4: ret  */
L_43e0a5:
	{ DWORD a_ = M32((DWORD)(0x9dd38cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e0a5: cmp dword ptr [0x9dd38c], ebx */
	if (m->zf) goto L_43e18b;	/* 43e0ab: je 0x43e18b */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e0b1: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_43e232;	/* 43e0b7: jne 0x43e232 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e0bd: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43e0bf: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd1f6u)) = m->eax;	/* 43e0c4: mov dword ptr [0x9dd1f6], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e0c9: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd1fau)) = m->eax;	/* 43e0cc: mov dword ptr [0x9dd1fa], eax */
	M32((DWORD)(0x9dd38cu)) = m->ebx;	/* 43e0d1: mov dword ptr [0x9dd38c], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e0d7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e0d9: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e0db: sub edi, ecx */
	M32((DWORD)(0x9dd1feu)) = m->eax;	/* 43e0dd: mov dword ptr [0x9dd1fe], eax */
	m->edx = m->ecx;	/* 43e0e2: mov edx, ecx */
	m->esi = m->edi;	/* 43e0e4: mov esi, edi */
	m->edi = 0x9dd1f6u;	/* 43e0e6: mov edi, 0x9dd1f6 */
	m->eax = M32((DWORD)(0x9dc428u));	/* 43e0eb: mov eax, dword ptr [0x9dc428] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e0f0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e0f3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43e0f5: mov ecx, edx */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 43e0f7: mov dword ptr [0x4e1868], ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e0fd: and ecx, 3 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e100: cmp eax, 0xa */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e103: rep movsb byte ptr es:[edi], byte ptr [esi] */
	if (!m->zf) goto L_43e129;	/* 43e105: jne 0x43e129 */
	M32((DWORD)(0x9dd1ccu)) = m->ebp;	/* 43e107: mov dword ptr [0x9dd1cc], ebp */
	M32((DWORD)(0x9dd6b0u)) = m->ebx;	/* 43e10d: mov dword ptr [0x9dd6b0], ebx */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 43e113: mov dword ptr [0x4e1868], ebx */
	m->esp -= 4; M32(m->esp) = 0x43e11eu; native_call(m, 0x433b00u);	/* 43e119: call 0x433b00 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e11e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e11f: pop esi */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43e120: mov dword ptr [0x9dc428], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e126: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e127: pop ebx */
	m->esp += 4 + 0; return;	/* 43e128: ret  */
L_43e129:
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e129: cmp eax, 0x14 */
	if (!m->zf) goto L_43e232;	/* 43e12c: jne 0x43e232 */
	m->eax = M32((DWORD)(0x9dd358u));	/* 43e132: mov eax, dword ptr [0x9dd358] */
	m->ecx = M32((DWORD)(0x9dd364u));	/* 43e137: mov ecx, dword ptr [0x9dd364] */
	{ DWORD a_ = m->eax, b_ = 0x62u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43e13d: add eax, 0x62 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e140: pop edi */
	M32((DWORD)(0x74de1cu)) = m->ebp;	/* 43e141: mov dword ptr [0x74de1c], ebp */
	M32((DWORD)(0x76d42cu)) = m->ebp;	/* 43e147: mov dword ptr [0x76d42c], ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43e14d: add ecx, -0x30 */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e150: pop esi */
	M32((DWORD)(0x9dd1ccu)) = m->ebx;	/* 43e151: mov dword ptr [0x9dd1cc], ebx */
	M32((DWORD)(0x9dd6b0u)) = m->ebx;	/* 43e157: mov dword ptr [0x9dd6b0], ebx */
	M32((DWORD)(0x4e1868u)) = m->ebx;	/* 43e15d: mov dword ptr [0x4e1868], ebx */
	M32((DWORD)(0x9dc428u)) = m->ebx;	/* 43e163: mov dword ptr [0x9dc428], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e169: pop ebp */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 43e16a: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 43e174: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->eax;	/* 43e17e: mov dword ptr [0x67ef34], eax */
	M32((DWORD)(0x67fb38u)) = m->ecx;	/* 43e183: mov dword ptr [0x67fb38], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e189: pop ebx */
	m->esp += 4 + 0; return;	/* 43e18a: ret  */
L_43e18b:
	{ DWORD a_ = M32((DWORD)(0x9dd838u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e18b: cmp dword ptr [0x9dd838], ebx */
	if (m->zf) goto L_43e232;	/* 43e191: je 0x43e232 */
	m->eax = M32((DWORD)(0xa0b378u));	/* 43e197: mov eax, dword ptr [0xa0b378] */
	{ DWORD a_ = m->eax, b_ = 0x2au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e19c: cmp eax, 0x2a */
	if (!m->cf && !m->zf) goto L_43e216;	/* 43e19f: ja 0x43e216 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43e1a1: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x43e258u))) & 0xff) << 0);	/* 43e1a3: mov dl, byte ptr [eax + 0x43e258] */
	switch (m->edx) { case 0: goto L_43e232; case 1: goto L_43e1db; case 2: goto L_43e1e5; case 3: goto L_43e1b0; case 4: goto L_43e1ef; case 5: goto L_43e216; case 6: goto L_43e1f9; case 7: goto L_43e216; default: abort(); }	/* 43e1a9: jmp dword ptr [edx*4 + 0x43e238] */
L_43e1b0:
	M32((DWORD)(0x9dd834u)) = 0x63u;	/* 43e1b0: mov dword ptr [0x9dd834], 0x63 */
	M32((DWORD)(0x9dd838u)) = m->ebx;	/* 43e1ba: mov dword ptr [0x9dd838], ebx */
	m->esp -= 4; M32(m->esp) = 0x43e1c5u; native_call(m, 0x432400u);	/* 43e1c0: call 0x432400 */
	m->esp -= 4; M32(m->esp) = 0x43e1cau; native_call(m, 0x432db0u);	/* 43e1c5: call 0x432db0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e1ca: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e1cb: pop esi */
	M32((DWORD)(0xa0b378u)) = m->ebx;	/* 43e1cc: mov dword ptr [0xa0b378], ebx */
	M32((DWORD)(0x9dd1c8u)) = m->ebx;	/* 43e1d2: mov dword ptr [0x9dd1c8], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e1d8: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e1d9: pop ebx */
	m->esp += 4 + 0; return;	/* 43e1da: ret  */
L_43e1db:
	M32((DWORD)(0x9dd838u)) = m->ebx;	/* 43e1db: mov dword ptr [0x9dd838], ebx */
	{ DWORD v_ = 0x1fu; m->esp -= 4; M32(m->esp) = v_; }	/* 43e1e1: push 0x1f */
	goto L_43e21e;	/* 43e1e3: jmp 0x43e21e */
L_43e1e5:
	M32((DWORD)(0x9dd838u)) = m->ebx;	/* 43e1e5: mov dword ptr [0x9dd838], ebx */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 43e1eb: push 0x20 */
	goto L_43e21e;	/* 43e1ed: jmp 0x43e21e */
L_43e1ef:
	M32((DWORD)(0x9dd838u)) = m->ebx;	/* 43e1ef: mov dword ptr [0x9dd838], ebx */
	{ DWORD v_ = 0x23u; m->esp -= 4; M32(m->esp) = v_; }	/* 43e1f5: push 0x23 */
	goto L_43e21e;	/* 43e1f7: jmp 0x43e21e */
L_43e1f9:
	m->edi = M32(m->esp); m->esp += 4;	/* 43e1f9: pop edi */
	M32((DWORD)(0x9dd850u)) = m->ebp;	/* 43e1fa: mov dword ptr [0x9dd850], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e200: pop esi */
	M32((DWORD)(0x9dd838u)) = m->ebx;	/* 43e201: mov dword ptr [0x9dd838], ebx */
	M32((DWORD)(0xa0b378u)) = m->ebx;	/* 43e207: mov dword ptr [0xa0b378], ebx */
	M32((DWORD)(0x9dd1c8u)) = m->ebx;	/* 43e20d: mov dword ptr [0x9dd1c8], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e213: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e214: pop ebx */
	m->esp += 4 + 0; return;	/* 43e215: ret  */
L_43e216:
	M32((DWORD)(0x9dd838u)) = m->ebx;	/* 43e216: mov dword ptr [0x9dd838], ebx */
	{ DWORD v_ = 0x2au; m->esp -= 4; M32(m->esp) = v_; }	/* 43e21c: push 0x2a */
L_43e21e:
	m->esp -= 4; M32(m->esp) = 0x43e223u; native_call(m, 0x41ee40u);	/* 43e21e: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e223: add esp, 4 */
	M32((DWORD)(0xa0b378u)) = m->ebx;	/* 43e226: mov dword ptr [0xa0b378], ebx */
	M32((DWORD)(0x9dd1c8u)) = m->ebx;	/* 43e22c: mov dword ptr [0x9dd1c8], ebx */
L_43e232:
	m->edi = M32(m->esp); m->esp += 4;	/* 43e232: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e233: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e234: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e235: pop ebx */
	m->esp += 4 + 0; return;	/* 43e236: ret  */
}

/* menu_enterMenus (0x40ee20), lifted by tools/lift.py */
static void lift_40ee20(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40ee20: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40ee21: xor esi, esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40ee23: push edi */
	M32((DWORD)(0x4dd078u)) = m->esi;	/* 40ee24: mov dword ptr [0x4dd078], esi */
	M32((DWORD)(0x4dbe48u)) = m->esi;	/* 40ee2a: mov dword ptr [0x4dbe48], esi */
	m->esp -= 4; M32(m->esp) = 0x40ee35u; native_call(m, 0x40e510u);	/* 40ee30: call 0x40e510 */
	{ DWORD v_ = 0x4b01b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ee35: push 0x4b01b0 */
	m->esp -= 4; M32(m->esp) = 0x40ee3fu; native_call(m, 0x457150u);	/* 40ee3a: call 0x457150 */
	m->eax = 0x5u;	/* 40ee3f: mov eax, 5 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ee44: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = m->eax;	/* 40ee47: mov dword ptr [0x4dbc6c], eax */
	M32((DWORD)(0x4dce38u)) = m->eax;	/* 40ee4c: mov dword ptr [0x4dce38], eax */
	M32((DWORD)(0x4dc4b0u)) = m->eax;	/* 40ee51: mov dword ptr [0x4dc4b0], eax */
	m->eax = M32((DWORD)(0x4dc24cu));	/* 40ee56: mov eax, dword ptr [0x4dc24c] */
	m->edi = 0x1u;	/* 40ee5b: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ee60: cmp eax, 3 */
	M32((DWORD)(0x4dc798u)) = m->edi;	/* 40ee63: mov dword ptr [0x4dc798], edi */
	M32((DWORD)(0x4dc788u)) = m->esi;	/* 40ee69: mov dword ptr [0x4dc788], esi */
	M32((DWORD)(0x4df024u)) = m->esi;	/* 40ee6f: mov dword ptr [0x4df024], esi */
	M32((DWORD)(0x4df028u)) = m->esi;	/* 40ee75: mov dword ptr [0x4df028], esi */
	if (!m->zf) goto L_40eea1;	/* 40ee7b: jne 0x40eea1 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9458u)));	/* 40ee7d: fld dword ptr [0x4a9458] */
	M32((DWORD)(0x680378u)) = m->esi;	/* 40ee83: mov dword ptr [0x680378], esi */
	M32((DWORD)(0x68037cu)) = m->esi;	/* 40ee89: mov dword ptr [0x68037c], esi */
	MF((DWORD)(0x4df02cu)) = (float)ST(0);	/* 40ee8f: fst dword ptr [0x4df02c] */
	M32((DWORD)(0x680380u)) = 0xc4ce4000u;	/* 40ee95: mov dword ptr [0x680380], 0xc4ce4000 */
	goto L_40eecb;	/* 40ee9f: jmp 0x40eecb */
L_40eea1:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9454u)));	/* 40eea1: fld dword ptr [0x4a9454] */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 40eea7: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 40eeb1: mov dword ptr [0x68037c], 0 */
	MF((DWORD)(0x4df02cu)) = (float)ST(0);	/* 40eebb: fst dword ptr [0x4df02c] */
	M32((DWORD)(0x680380u)) = 0xc4098000u;	/* 40eec1: mov dword ptr [0x680380], 0xc4098000 */
L_40eecb:
	m->ecx = 0xau;	/* 40eecb: mov ecx, 0xa */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eed0: cmp eax, 3 */
	M32((DWORD)(0x4dcc90u)) = m->ecx;	/* 40eed3: mov dword ptr [0x4dcc90], ecx */
	M32((DWORD)(0x4dcc94u)) = m->ecx;	/* 40eed9: mov dword ptr [0x4dcc94], ecx */
	M32((DWORD)(0x4dcc98u)) = 0x276u;	/* 40eedf: mov dword ptr [0x4dcc98], 0x276 */
	M32((DWORD)(0x4dcc9cu)) = 0x1d6u;	/* 40eee9: mov dword ptr [0x4dcc9c], 0x1d6 */
	M32((DWORD)(0x4dbc58u)) = 0x0u;	/* 40eef3: mov dword ptr [0x4dbc58], 0 */
	M32((DWORD)(0x4dbc5cu)) = 0x3f800000u;	/* 40eefd: mov dword ptr [0x4dbc5c], 0x3f800000 */
	M32((DWORD)(0x4dbc60u)) = 0x3f800000u;	/* 40ef07: mov dword ptr [0x4dbc60], 0x3f800000 */
	M32((DWORD)(0x4dbc64u)) = 0x3f800000u;	/* 40ef11: mov dword ptr [0x4dbc64], 0x3f800000 */
	M32((DWORD)(0x4dc1d0u)) = 0x0u;	/* 40ef1b: mov dword ptr [0x4dc1d0], 0 */
	M32((DWORD)(0x4dc1d4u)) = 0x3f19999au;	/* 40ef25: mov dword ptr [0x4dc1d4], 0x3f19999a */
	M32((DWORD)(0x4dc1d8u)) = 0x3f19999au;	/* 40ef2f: mov dword ptr [0x4dc1d8], 0x3f19999a */
	M32((DWORD)(0x4dc1dcu)) = 0x3f800000u;	/* 40ef39: mov dword ptr [0x4dc1dc], 0x3f800000 */
	M32((DWORD)(0x4dcf34u)) = m->esi;	/* 40ef43: mov dword ptr [0x4dcf34], esi */
	M32((DWORD)(0x4df870u)) = 0x0u;	/* 40ef49: mov dword ptr [0x4df870], 0 */
	M32((DWORD)(0x4df874u)) = 0x0u;	/* 40ef53: mov dword ptr [0x4df874], 0 */
	if (!m->zf) goto L_40ef98;	/* 40ef5d: jne 0x40ef98 */
	m->eax = M32((DWORD)(0x9dd5d8u));	/* 40ef5f: mov eax, dword ptr [0x9dd5d8] */
	m->ecx = M32((DWORD)(0x4dc4b4u));	/* 40ef64: mov ecx, dword ptr [0x4dc4b4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ef6a: cmp eax, ecx */
	M32((DWORD)(0x4df878u)) = 0xc47a0000u;	/* 40ef6c: mov dword ptr [0x4df878], 0xc47a0000 */
	M32((DWORD)(0x76d388u)) = 0x0u;	/* 40ef76: mov dword ptr [0x76d388], 0 */
	M32((DWORD)(0x76d38cu)) = 0x0u;	/* 40ef80: mov dword ptr [0x76d38c], 0 */
	M32((DWORD)(0x76d390u)) = 0xc4898000u;	/* 40ef8a: mov dword ptr [0x76d390], 0xc4898000 */
	if (m->zf || m->sf != m->of) goto L_40efd5;	/* 40ef94: jle 0x40efd5 */
	goto L_40efcf;	/* 40ef96: jmp 0x40efcf */
L_40ef98:
	m->ecx = M32((DWORD)(0x9f181cu));	/* 40ef98: mov ecx, dword ptr [0x9f181c] */
	m->eax = M32((DWORD)(0x4dc1e0u));	/* 40ef9e: mov eax, dword ptr [0x4dc1e0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40efa3: cmp ecx, eax */
	M32((DWORD)(0x4df878u)) = 0x42c80000u;	/* 40efa5: mov dword ptr [0x4df878], 0x42c80000 */
	M32((DWORD)(0x76d388u)) = 0x0u;	/* 40efaf: mov dword ptr [0x76d388], 0 */
	M32((DWORD)(0x76d38cu)) = 0x0u;	/* 40efb9: mov dword ptr [0x76d38c], 0 */
	M32((DWORD)(0x76d390u)) = 0x0u;	/* 40efc3: mov dword ptr [0x76d390], 0 */
	if (m->zf || m->sf != m->of) goto L_40efd5;	/* 40efcd: jle 0x40efd5 */
L_40efcf:
	M32((DWORD)(0x4dcf34u)) = m->edi;	/* 40efcf: mov dword ptr [0x4dcf34], edi */
L_40efd5:
	m->edx = M32((DWORD)(0x680380u));	/* 40efd5: mov edx, dword ptr [0x680380] */
	m->eax = 0x2bcu;	/* 40efdb: mov eax, 0x2bc */
	MF((DWORD)(0x9db098u)) = (float)ST(0); FPOP();	/* 40efe0: fstp dword ptr [0x9db098] */
	M32((DWORD)(0x9db090u)) = 0x0u;	/* 40efe6: mov dword ptr [0x9db090], 0 */
	M32((DWORD)(0x9db094u)) = 0x0u;	/* 40eff0: mov dword ptr [0x9db094], 0 */
	M32((DWORD)(0x76d3f8u)) = 0x0u;	/* 40effa: mov dword ptr [0x76d3f8], 0 */
	M32((DWORD)(0x76d3fcu)) = 0x0u;	/* 40f004: mov dword ptr [0x76d3fc], 0 */
	M32((DWORD)(0x76d400u)) = m->edx;	/* 40f00e: mov dword ptr [0x76d400], edx */
	M32((DWORD)(0x4dc790u)) = m->edi;	/* 40f014: mov dword ptr [0x4dc790], edi */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 40f01a: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 40f01f: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 40f024: mov dword ptr [0x67ef20], eax */
	m->esp -= 4; M32(m->esp) = 0x40f02eu; native_call(m, 0x40e060u);	/* 40f029: call 0x40e060 */
	m->esp -= 4; M32(m->esp) = 0x40f033u; native_call(m, 0x40e1c0u);	/* 40f02e: call 0x40e1c0 */
	m->esp -= 4; M32(m->esp) = 0x40f038u; native_call(m, 0x40e300u);	/* 40f033: call 0x40e300 */
	m->esp -= 4; M32(m->esp) = 0x40f03du; native_call(m, 0x40da40u);	/* 40f038: call 0x40da40 */
	m->eax = M32((DWORD)(0x4dc24cu));	/* 40f03d: mov eax, dword ptr [0x4dc24c] */
	M32((DWORD)(0x4dc868u)) = m->edi;	/* 40f042: mov dword ptr [0x4dc868], edi */
	M32((DWORD)(0x4dceacu)) = m->edi;	/* 40f048: mov dword ptr [0x4dceac], edi */
	M32((DWORD)(0x4dcc58u)) = m->edi;	/* 40f04e: mov dword ptr [0x4dcc58], edi */
	M32((DWORD)(0x4dbc68u)) = m->esi;	/* 40f054: mov dword ptr [0x4dbc68], esi */
	M32((DWORD)(0x4dc86cu)) = m->esi;	/* 40f05a: mov dword ptr [0x4dc86c], esi */
	M32((DWORD)(0x4dc54cu)) = m->esi;	/* 40f060: mov dword ptr [0x4dc54c], esi */
	M32((DWORD)(0x4dcf10u)) = m->esi;	/* 40f066: mov dword ptr [0x4dcf10], esi */
	M32((DWORD)(0x4dbc00u)) = m->esi;	/* 40f06c: mov dword ptr [0x4dbc00], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 40f072: pop edi */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f073: cmp eax, 3 */
	M32((DWORD)(0x4dbc04u)) = 0x0u;	/* 40f076: mov dword ptr [0x4dbc04], 0 */
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 40f080: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40f08a: pop esi */
	if (!m->zf) goto L_40f094;	/* 40f08b: jne 0x40f094 */
	m->esp -= 4; M32(m->esp) = 0x40f092u; native_call(m, 0x40ddb0u);	/* 40f08d: call 0x40ddb0 */
	goto L_40f099;	/* 40f092: jmp 0x40f099 */
L_40f094:
	m->esp -= 4; M32(m->esp) = 0x40f099u; native_call(m, 0x4463a0u);	/* 40f094: call 0x4463a0 */
L_40f099:
	m->esp -= 4; M32(m->esp) = 0x40f09eu; native_call(m, 0x40e6c0u);	/* 40f099: call 0x40e6c0 */
	m->esp -= 4; M32(m->esp) = 0x40f0a3u; native_call(m, 0x40de80u);	/* 40f09e: call 0x40de80 */
	m->esp -= 4; M32(m->esp) = 0x40f0a8u; native_call(m, 0x40dfa0u);	/* 40f0a3: call 0x40dfa0 */
	m->esp -= 4; M32(m->esp) = 0x40f0adu; native_call(m, 0x40ed20u);	/* 40f0a8: call 0x40ed20 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f0ad: push 4 */
	m->esp -= 4; M32(m->esp) = 0x40f0b4u; native_call(m, 0x41e760u);	/* 40f0af: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dc24cu));	/* 40f0b4: mov eax, dword ptr [0x4dc24c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40f0b9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f0bc: cmp eax, 3 */
	if (!m->zf) goto L_40f0d6;	/* 40f0bf: jne 0x40f0d6 */
	m->eax = M32((DWORD)(0x9dd5d8u));	/* 40f0c1: mov eax, dword ptr [0x9dd5d8] */
	m->ecx = M32((DWORD)(0x4dc4b4u));	/* 40f0c6: mov ecx, dword ptr [0x4dc4b4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f0cc: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_40f0ea;	/* 40f0ce: jle 0x40f0ea */
	M32((DWORD)(0x4dc4b4u)) = m->eax;	/* 40f0d0: mov dword ptr [0x4dc4b4], eax */
	m->esp += 4 + 0; return;	/* 40f0d5: ret  */
L_40f0d6:
	m->eax = M32((DWORD)(0x9f181cu));	/* 40f0d6: mov eax, dword ptr [0x9f181c] */
	m->ecx = M32((DWORD)(0x4dc1e0u));	/* 40f0db: mov ecx, dword ptr [0x4dc1e0] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f0e1: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_40f0ea;	/* 40f0e3: jle 0x40f0ea */
	M32((DWORD)(0x4dc1e0u)) = m->eax;	/* 40f0e5: mov dword ptr [0x4dc1e0], eax */
L_40f0ea:
	m->esp += 4 + 0; return;	/* 40f0ea: ret  */
}

/* menu_4372f0 (0x4372f0), lifted by tools/lift.py */
static void lift_4372f0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd6b4u));	/* 4372f0: mov eax, dword ptr [0x9dd6b4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4372f5: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4372f6: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4372f8: cmp eax, esi */
	if (!m->zf) goto L_437624;	/* 4372fa: jne 0x437624 */
	{ DWORD a_ = M32((DWORD)(0x4db8b4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437300: cmp dword ptr [0x4db8b4], esi */
	if (m->zf) goto L_437352;	/* 437306: je 0x437352 */
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 437308: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43730d: push eax */
	m->esp -= 4; M32(m->esp) = 0x437313u; native_call(m, 0x401600u);	/* 43730e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437313: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437316: test eax, eax */
	if (m->zf) goto L_437624;	/* 437318: je 0x437624 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43731e: push esi */
	m->esp -= 4; M32(m->esp) = 0x437324u; native_call(m, 0x41e760u);	/* 43731f: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437324: add esp, 4 */
	M32((DWORD)(0x4dbb10u)) = m->esi;	/* 437327: mov dword ptr [0x4dbb10], esi */
	M32((DWORD)(0x4dbb78u)) = m->esi;	/* 43732d: mov dword ptr [0x4dbb78], esi */
	m->esp -= 4; M32(m->esp) = 0x437338u; native_call(m, 0x452fe0u);	/* 437333: call 0x452fe0 */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 437338: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x378u; m->esp -= 4; M32(m->esp) = v_; }	/* 43733e: push 0x378 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 437343: push ecx */
	M32((DWORD)(0x4db8b4u)) = m->esi;	/* 437344: mov dword ptr [0x4db8b4], esi */
	m->esp -= 4; M32(m->esp) = 0x437350u; native_call(m, M32(0x4a9330u));	/* 43734a: call dword ptr [0x4a9330] */
	m->esi = M32(m->esp); m->esp += 4;	/* 437350: pop esi */
	m->esp += 4 + 0; return;	/* 437351: ret  */
L_437352:
	m->edx = M32((DWORD)(0x4e14f8u));	/* 437352: mov edx, dword ptr [0x4e14f8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 437358: push edx */
	m->esp -= 4; M32(m->esp) = 0x43735eu; native_call(m, 0x401600u);	/* 437359: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43735e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437361: test eax, eax */
	if (m->zf) goto L_437395;	/* 437363: je 0x437395 */
	{ DWORD a_ = M32((DWORD)(0x9dd56cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437365: cmp dword ptr [0x9dd56c], esi */
	if (!m->zf) goto L_437624;	/* 43736b: jne 0x437624 */
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437371: cmp dword ptr [0x9dd6a0], esi */
	if (!m->zf) goto L_4373cb;	/* 437377: jne 0x4373cb */
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437379: cmp dword ptr [0x9dd3fc], esi */
	if (!m->zf) goto L_4373cb;	/* 43737f: jne 0x4373cb */
	{ DWORD a_ = M32((DWORD)(0x67ef30u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437381: cmp dword ptr [0x67ef30], esi */
	if (!m->zf && m->sf == m->of) goto L_4373d7;	/* 437387: jg 0x4373d7 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 437389: push 6 */
	m->esp -= 4; M32(m->esp) = 0x437390u; native_call(m, 0x41e760u);	/* 43738b: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437390: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 437393: pop esi */
	m->esp += 4 + 0; return;	/* 437394: ret  */
L_437395:
	m->eax = M32((DWORD)(0x9dae70u));	/* 437395: mov eax, dword ptr [0x9dae70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43739a: push eax */
	m->esp -= 4; M32(m->esp) = 0x4373a0u; native_call(m, 0x401600u);	/* 43739b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4373a0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4373a3: test eax, eax */
	if (m->zf) goto L_4373f1;	/* 4373a5: je 0x4373f1 */
	{ DWORD a_ = M32((DWORD)(0x9dd56cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4373a7: cmp dword ptr [0x9dd56c], esi */
	if (!m->zf) goto L_437624;	/* 4373ad: jne 0x437624 */
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4373b3: cmp dword ptr [0x9dd6a0], esi */
	if (!m->zf) goto L_4373cb;	/* 4373b9: jne 0x4373cb */
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4373bb: cmp dword ptr [0x9dd3fc], esi */
	if (!m->zf) goto L_4373cb;	/* 4373c1: jne 0x4373cb */
	{ DWORD a_ = M32((DWORD)(0x67ef30u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4373c3: cmp dword ptr [0x67ef30], esi */
	if (!m->zf && m->sf == m->of) goto L_4373d7;	/* 4373c9: jg 0x4373d7 */
L_4373cb:
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 4373cb: push 6 */
	m->esp -= 4; M32(m->esp) = 0x4373d2u; native_call(m, 0x41e760u);	/* 4373cd: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4373d2: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4373d5: pop esi */
	m->esp += 4 + 0; return;	/* 4373d6: ret  */
L_4373d7:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4373d7: push esi */
	m->esp -= 4; M32(m->esp) = 0x4373ddu; native_call(m, 0x41e760u);	/* 4373d8: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4373dd: add esp, 4 */
	M32((DWORD)(0x9dd56cu)) = 0x1u;	/* 4373e0: mov dword ptr [0x9dd56c], 1 */
	m->esp -= 4; M32(m->esp) = 0x4373efu; native_call(m, 0x434da0u);	/* 4373ea: call 0x434da0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4373ef: pop esi */
	m->esp += 4 + 0; return;	/* 4373f0: ret  */
L_4373f1:
	m->ecx = M32((DWORD)(0x4e151cu));	/* 4373f1: mov ecx, dword ptr [0x4e151c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4373f7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4373fdu; native_call(m, 0x401600u);	/* 4373f8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4373fd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437400: test eax, eax */
	if (m->zf) goto L_437449;	/* 437402: je 0x437449 */
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437404: cmp dword ptr [0x9dd6a0], esi */
	if (!m->zf) goto L_4373cb;	/* 43740a: jne 0x4373cb */
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43740c: cmp dword ptr [0x9dd3fc], esi */
	if (!m->zf) goto L_4373cb;	/* 437412: jne 0x4373cb */
	M32((DWORD)(0xa0b358u)) = m->esi;	/* 437414: mov dword ptr [0xa0b358], esi */
	M32((DWORD)(0x680bb8u)) = m->esi;	/* 43741a: mov dword ptr [0x680bb8], esi */
	m->esp -= 4; M32(m->esp) = 0x437425u; native_call(m, 0x434d00u);	/* 437420: call 0x434d00 */
	m->ecx = 0x1u;	/* 437425: mov ecx, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43742a: cmp eax, ecx */
	if (!m->zf) goto L_437624;	/* 43742c: jne 0x437624 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 437432: push esi */
	M32((DWORD)(0x9dd6a0u)) = m->ecx;	/* 437433: mov dword ptr [0x9dd6a0], ecx */
	M32((DWORD)(0x9dd4bcu)) = m->ecx;	/* 437439: mov dword ptr [0x9dd4bc], ecx */
	m->esp -= 4; M32(m->esp) = 0x437444u; native_call(m, 0x41e760u);	/* 43743f: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437444: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 437447: pop esi */
	m->esp += 4 + 0; return;	/* 437448: ret  */
L_437449:
	m->edx = M32((DWORD)(0x4e1524u));	/* 437449: mov edx, dword ptr [0x4e1524] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43744f: push edx */
	m->esp -= 4; M32(m->esp) = 0x437455u; native_call(m, 0x401600u);	/* 437450: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437455: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437458: test eax, eax */
	if (m->zf) goto L_4374a3;	/* 43745a: je 0x4374a3 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43745c: push esi */
	m->esp -= 4; M32(m->esp) = 0x437462u; native_call(m, 0x41e760u);	/* 43745d: call 0x41e760 */
	m->eax = M32((DWORD)(0x9dd3fcu));	/* 437462: mov eax, dword ptr [0x9dd3fc] */
	m->ecx = 0x1u;	/* 437467: mov ecx, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43746c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43746f: cmp eax, ecx */
	M32((DWORD)(0xa0b34cu)) = m->esi;	/* 437471: mov dword ptr [0xa0b34c], esi */
	M32((DWORD)(0x4dba80u)) = 0x3f800000u;	/* 437477: mov dword ptr [0x4dba80], 0x3f800000 */
	M32((DWORD)(0x9da498u)) = m->ecx;	/* 437481: mov dword ptr [0x9da498], ecx */
	if (!m->zf) goto L_43749b;	/* 437487: jne 0x43749b */
	M32((DWORD)(0x9dd3fcu)) = m->esi;	/* 437489: mov dword ptr [0x9dd3fc], esi */
	M32((DWORD)(0x9dd6a0u)) = m->esi;	/* 43748f: mov dword ptr [0x9dd6a0], esi */
	M32((DWORD)(0x9da498u)) = m->esi;	/* 437495: mov dword ptr [0x9da498], esi */
L_43749b:
	M32((DWORD)(0xa0d7a0u)) = m->ecx;	/* 43749b: mov dword ptr [0xa0d7a0], ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 4374a1: pop esi */
	m->esp += 4 + 0; return;	/* 4374a2: ret  */
L_4374a3:
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 4374a3: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4374a8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4374aeu; native_call(m, 0x401600u);	/* 4374a9: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4374ae: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4374b1: test eax, eax */
	if (m->zf) goto L_4374f4;	/* 4374b3: je 0x4374f4 */
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4374b5: cmp dword ptr [0x9dd6a0], esi */
	if (!m->zf) goto L_4373cb;	/* 4374bb: jne 0x4373cb */
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4374c1: cmp dword ptr [0x9dd3fc], esi */
	if (!m->zf) goto L_4373cb;	/* 4374c7: jne 0x4373cb */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4374cd: push esi */
	m->esp -= 4; M32(m->esp) = 0x4374d3u; native_call(m, 0x41e760u);	/* 4374ce: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4374d3: add esp, 4 */
	M32((DWORD)(0xa0b34cu)) = m->esi;	/* 4374d6: mov dword ptr [0xa0b34c], esi */
	M32((DWORD)(0x9dce48u)) = m->esi;	/* 4374dc: mov dword ptr [0x9dce48], esi */
	M32((DWORD)(0xa0b364u)) = m->esi;	/* 4374e2: mov dword ptr [0xa0b364], esi */
	M32((DWORD)(0xa0d7a0u)) = 0x1u;	/* 4374e8: mov dword ptr [0xa0d7a0], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4374f2: pop esi */
	m->esp += 4 + 0; return;	/* 4374f3: ret  */
L_4374f4:
	m->ecx = M32((DWORD)(0x9db0a0u));	/* 4374f4: mov ecx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4374fa: push ecx */
	m->esp -= 4; M32(m->esp) = 0x437500u; native_call(m, 0x401590u);	/* 4374fb: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437500: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437503: test eax, eax */
	if (m->zf) goto L_437572;	/* 437505: je 0x437572 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 437507: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 43750d: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 437513: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 437515: test ah, 1 */
	if (!m->zf) goto L_437624;	/* 437518: jne 0x437624 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43751e: push 2 */
	m->esp -= 4; M32(m->esp) = 0x437525u; native_call(m, 0x41e760u);	/* 437520: call 0x41e760 */
	m->eax = M32((DWORD)(0x4df818u));	/* 437525: mov eax, dword ptr [0x4df818] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43752a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43752d: cmp eax, esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 43752f: mov dword ptr [0x4dda44], 0 */
	if (m->zf || m->sf != m->of) goto L_437551;	/* 437539: jle 0x437551 */
	m->edx = M32((DWORD)(0x680bb0u));	/* 43753b: mov edx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 437541: dec eax */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 437542: add edx, eax */
	M32((DWORD)(0x4df818u)) = m->eax;	/* 437544: mov dword ptr [0x4df818], eax */
	M32((DWORD)(0x76d41cu)) = m->edx;	/* 437549: mov dword ptr [0x76d41c], edx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43754f: pop esi */
	m->esp += 4 + 0; return;	/* 437550: ret  */
L_437551:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 437551: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437557: cmp ecx, esi */
	if (m->zf || m->sf != m->of) goto L_437562;	/* 437559: jle 0x437562 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43755b: dec ecx */
	M32((DWORD)(0x680bb0u)) = m->ecx;	/* 43755c: mov dword ptr [0x680bb0], ecx */
L_437562:
	m->edx = M32((DWORD)(0x680bb0u));	/* 437562: mov edx, dword ptr [0x680bb0] */
	m->esi = M32(m->esp); m->esp += 4;	/* 437568: pop esi */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 437569: add edx, eax */
	M32((DWORD)(0x76d41cu)) = m->edx;	/* 43756b: mov dword ptr [0x76d41c], edx */
	m->esp += 4 + 0; return;	/* 437571: ret  */
L_437572:
	m->eax = M32((DWORD)(0x76d330u));	/* 437572: mov eax, dword ptr [0x76d330] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 437577: push eax */
	m->esp -= 4; M32(m->esp) = 0x43757du; native_call(m, 0x401590u);	/* 437578: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43757d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437580: test eax, eax */
	if (m->zf) goto L_4375fc;	/* 437582: je 0x4375fc */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 437584: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 43758a: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 437590: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 437592: test ah, 1 */
	if (!m->zf) goto L_437624;	/* 437595: jne 0x437624 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43759b: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43759c: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4375a3u; native_call(m, 0x41e760u);	/* 43759e: call 0x41e760 */
	m->esi = M32((DWORD)(0x680bb0u));	/* 4375a3: mov esi, dword ptr [0x680bb0] */
	m->edx = M32((DWORD)(0x4df818u));	/* 4375a9: mov edx, dword ptr [0x4df818] */
	m->ecx = M32((DWORD)(0x67ef30u));	/* 4375af: mov ecx, dword ptr [0x67ef30] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4375b5: add esp, 4 */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x0u);	/* 4375b8: lea eax, [esi + edx] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4375bb: mov dword ptr [0x4dda44], 0 */
	m->edi = (DWORD)(m->ecx + 0xffffffffu);	/* 4375c5: lea edi, [ecx - 1] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4375c8: cmp eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4375ca: pop edi */
	if (m->sf == m->of) goto L_437624;	/* 4375cb: jge 0x437624 */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4375cd: cmp edx, 8 */
	if (m->sf == m->of) goto L_4375e7;	/* 4375d0: jge 0x4375e7 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4375d2: cmp eax, ecx */
	if (m->sf == m->of) goto L_4375f2;	/* 4375d4: jge 0x4375f2 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4375d6: inc edx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4375d7: add esi, edx */
	M32((DWORD)(0x4df818u)) = m->edx;	/* 4375d9: mov dword ptr [0x4df818], edx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 4375df: mov dword ptr [0x76d41c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4375e5: pop esi */
	m->esp += 4 + 0; return;	/* 4375e6: ret  */
L_4375e7:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4375e7: cmp eax, ecx */
	if (m->sf == m->of) goto L_4375f2;	/* 4375e9: jge 0x4375f2 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4375eb: inc esi */
	M32((DWORD)(0x680bb0u)) = m->esi;	/* 4375ec: mov dword ptr [0x680bb0], esi */
L_4375f2:
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4375f2: add esi, edx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 4375f4: mov dword ptr [0x76d41c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4375fa: pop esi */
	m->esp += 4 + 0; return;	/* 4375fb: ret  */
L_4375fc:
	m->ecx = M32((DWORD)(0x76d48cu));	/* 4375fc: mov ecx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 437602: push ecx */
	m->esp -= 4; M32(m->esp) = 0x437608u; native_call(m, 0x401600u);	/* 437603: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437608: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43760b: test eax, eax */
	if (m->zf) goto L_437624;	/* 43760d: je 0x437624 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43760f: push esi */
	m->esp -= 4; M32(m->esp) = 0x437615u; native_call(m, 0x41e760u);	/* 437610: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437615: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = m->esi;	/* 437618: mov dword ptr [0x9dce48], esi */
	M32((DWORD)(0xa0b34cu)) = m->esi;	/* 43761e: mov dword ptr [0xa0b34c], esi */
L_437624:
	m->esi = M32(m->esp); m->esp += 4;	/* 437624: pop esi */
	m->esp += 4 + 0; return;	/* 437625: ret  */
}

/* room_435fc0 (0x435fc0), lifted by tools/lift.py */
static void lift_435fc0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dce48u));	/* 435fc0: mov eax, dword ptr [0x9dce48] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 435fc5: push ebx */
	m->ebx = 0x1u;	/* 435fc6: mov ebx, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 435fcb: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435fcc: cmp eax, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 435fce: push edi */
	if (m->zf) goto L_4363cf;	/* 435fcf: je 0x4363cf */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 435fd5: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435fd7: cmp eax, edi */
	if (m->zf) goto L_4363cf;	/* 435fd9: je 0x4363cf */
	{ DWORD a_ = M32((DWORD)(0x9dd6b4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435fdf: cmp dword ptr [0x9dd6b4], edi */
	if (!m->zf) goto L_4363cf;	/* 435fe5: jne 0x4363cf */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435feb: cmp dword ptr [0x90d1c4], edi */
	if (!m->zf) goto L_4363cf;	/* 435ff1: jne 0x4363cf */
	{ DWORD a_ = M32((DWORD)(0x4ded8cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435ff7: cmp dword ptr [0x4ded8c], edi */
	if (m->zf) goto L_43602a;	/* 435ffd: je 0x43602a */
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435fff: cmp dword ptr [0x9dd6a0], edi */
	if (!m->zf) goto L_4363cf;	/* 436005: jne 0x4363cf */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43600b: push edi */
	m->esp -= 4; M32(m->esp) = 0x436011u; native_call(m, 0x41e760u);	/* 43600c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436011: add esp, 4 */
	M32((DWORD)(0xa0b34cu)) = m->edi;	/* 436014: mov dword ptr [0xa0b34c], edi */
	M32((DWORD)(0x9dce48u)) = m->edi;	/* 43601a: mov dword ptr [0x9dce48], edi */
	M32((DWORD)(0xa0b364u)) = m->edi;	/* 436020: mov dword ptr [0xa0b364], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436026: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436027: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 436028: pop ebx */
	m->esp += 4 + 0; return;	/* 436029: ret  */
L_43602a:
	{ DWORD a_ = M32((DWORD)(0x4ded88u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43602a: cmp dword ptr [0x4ded88], edi */
	if (m->zf) goto L_4362d2;	/* 436030: je 0x4362d2 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 436036: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 43603b: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436041: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436042: push ecx */
	m->esp -= 4; M32(m->esp) = 0x436048u; native_call(m, 0x432300u);	/* 436043: call 0x432300 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436048: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43604b: cmp eax, 0xe */
	if (!m->cf && !m->zf) goto L_43621b;	/* 43604e: ja 0x43621b */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 436054: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x4363f0u))) & 0xff) << 0);	/* 436056: mov dl, byte ptr [eax + 0x4363f0] */
	switch (m->edx) { case 0: goto L_436063; case 1: goto L_4360ae; case 2: goto L_4360fd; case 3: goto L_436142; case 4: goto L_436180; case 5: goto L_4361c6; case 6: goto L_43621b; default: abort(); }	/* 43605c: jmp dword ptr [edx*4 + 0x4363d4] */
L_436063:
	{ DWORD a_ = M32((DWORD)(0x9dd56cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436063: cmp dword ptr [0x9dd56c], edi */
	if (!m->zf) goto L_4363cf;	/* 436069: jne 0x4363cf */
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43606f: cmp dword ptr [0x9dd6a0], edi */
	if (!m->zf) goto L_436087;	/* 436075: jne 0x436087 */
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436077: cmp dword ptr [0x9dd3fc], edi */
	if (!m->zf) goto L_436087;	/* 43607d: jne 0x436087 */
	{ DWORD a_ = M32((DWORD)(0x67ef30u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43607f: cmp dword ptr [0x67ef30], edi */
	if (!m->zf && m->sf == m->of) goto L_436095;	/* 436085: jg 0x436095 */
L_436087:
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 436087: push 6 */
	m->esp -= 4; M32(m->esp) = 0x43608eu; native_call(m, 0x41e760u);	/* 436089: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43608e: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436091: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436092: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 436093: pop ebx */
	m->esp += 4 + 0; return;	/* 436094: ret  */
L_436095:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436095: push edi */
	m->esp -= 4; M32(m->esp) = 0x43609bu; native_call(m, 0x41e760u);	/* 436096: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43609b: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4360a3u; native_call(m, 0x434da0u);	/* 43609e: call 0x434da0 */
	M32((DWORD)(0x9dd56cu)) = m->ebx;	/* 4360a3: mov dword ptr [0x9dd56c], ebx */
	goto L_4362d2;	/* 4360a9: jmp 0x4362d2 */
L_4360ae:
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4360ae: cmp dword ptr [0x9dd6a0], edi */
	if (!m->zf) goto L_436087;	/* 4360b4: jne 0x436087 */
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4360b6: cmp dword ptr [0x9dd3fc], edi */
	if (!m->zf) goto L_436087;	/* 4360bc: jne 0x436087 */
	{ DWORD a_ = M32((DWORD)(0x9dd56cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4360be: cmp dword ptr [0x9dd56c], edi */
	if (!m->zf) goto L_4363cf;	/* 4360c4: jne 0x4363cf */
	M32((DWORD)(0xa0b358u)) = m->edi;	/* 4360ca: mov dword ptr [0xa0b358], edi */
	M32((DWORD)(0x680bb8u)) = m->edi;	/* 4360d0: mov dword ptr [0x680bb8], edi */
	m->esp -= 4; M32(m->esp) = 0x4360dbu; native_call(m, 0x434d00u);	/* 4360d6: call 0x434d00 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4360db: cmp eax, ebx */
	if (!m->zf) goto L_4362d2;	/* 4360dd: jne 0x4362d2 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4360e3: push edi */
	m->esp -= 4; M32(m->esp) = 0x4360e9u; native_call(m, 0x41e760u);	/* 4360e4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4360e9: add esp, 4 */
	M32((DWORD)(0x9dd6a0u)) = m->ebx;	/* 4360ec: mov dword ptr [0x9dd6a0], ebx */
	M32((DWORD)(0x9dd4bcu)) = m->ebx;	/* 4360f2: mov dword ptr [0x9dd4bc], ebx */
	goto L_4362d2;	/* 4360f8: jmp 0x4362d2 */
L_4360fd:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4360fd: push edi */
	m->esp -= 4; M32(m->esp) = 0x436103u; native_call(m, 0x41e760u);	/* 4360fe: call 0x41e760 */
	m->eax = M32((DWORD)(0x9dd3fcu));	/* 436103: mov eax, dword ptr [0x9dd3fc] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436108: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43610b: cmp eax, ebx */
	M32((DWORD)(0x4dba80u)) = 0x3f800000u;	/* 43610d: mov dword ptr [0x4dba80], 0x3f800000 */
	M32((DWORD)(0xa0b34cu)) = m->edi;	/* 436117: mov dword ptr [0xa0b34c], edi */
	M32((DWORD)(0x9da498u)) = m->ebx;	/* 43611d: mov dword ptr [0x9da498], ebx */
	if (!m->zf) goto L_436137;	/* 436123: jne 0x436137 */
	M32((DWORD)(0x9dd3fcu)) = m->edi;	/* 436125: mov dword ptr [0x9dd3fc], edi */
	M32((DWORD)(0x9dd6a0u)) = m->edi;	/* 43612b: mov dword ptr [0x9dd6a0], edi */
	M32((DWORD)(0x9da498u)) = m->edi;	/* 436131: mov dword ptr [0x9da498], edi */
L_436137:
	M32((DWORD)(0xa0d7a0u)) = m->ebx;	/* 436137: mov dword ptr [0xa0d7a0], ebx */
	goto L_4362d2;	/* 43613d: jmp 0x4362d2 */
L_436142:
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436142: cmp dword ptr [0x9dd6a0], edi */
	if (!m->zf) goto L_436087;	/* 436148: jne 0x436087 */
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43614e: cmp dword ptr [0x9dd3fc], edi */
	if (!m->zf) goto L_436087;	/* 436154: jne 0x436087 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43615a: push edi */
	m->esp -= 4; M32(m->esp) = 0x436160u; native_call(m, 0x41e760u);	/* 43615b: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436160: add esp, 4 */
	M32((DWORD)(0xa0b34cu)) = m->edi;	/* 436163: mov dword ptr [0xa0b34c], edi */
	M32((DWORD)(0x9dce48u)) = m->edi;	/* 436169: mov dword ptr [0x9dce48], edi */
	M32((DWORD)(0xa0b364u)) = m->edi;	/* 43616f: mov dword ptr [0xa0b364], edi */
	M32((DWORD)(0xa0d7a0u)) = m->ebx;	/* 436175: mov dword ptr [0xa0d7a0], ebx */
	goto L_4362d2;	/* 43617b: jmp 0x4362d2 */
L_436180:
	m->eax = M32((DWORD)(0x4df818u));	/* 436180: mov eax, dword ptr [0x4df818] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436185: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_4361a2;	/* 436187: jle 0x4361a2 */
	m->ecx = M32((DWORD)(0x680bb0u));	/* 436189: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 43618f: dec eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 436190: add ecx, eax */
	M32((DWORD)(0x4df818u)) = m->eax;	/* 436192: mov dword ptr [0x4df818], eax */
	M32((DWORD)(0x76d41cu)) = m->ecx;	/* 436197: mov dword ptr [0x76d41c], ecx */
	goto L_4362d2;	/* 43619d: jmp 0x4362d2 */
L_4361a2:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 4361a2: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4361a8: cmp ecx, edi */
	if (m->zf || m->sf != m->of) goto L_4361b3;	/* 4361aa: jle 0x4361b3 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4361ac: dec ecx */
	M32((DWORD)(0x680bb0u)) = m->ecx;	/* 4361ad: mov dword ptr [0x680bb0], ecx */
L_4361b3:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 4361b3: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4361b9: add ecx, eax */
	M32((DWORD)(0x76d41cu)) = m->ecx;	/* 4361bb: mov dword ptr [0x76d41c], ecx */
	goto L_4362d2;	/* 4361c1: jmp 0x4362d2 */
L_4361c6:
	m->esi = M32((DWORD)(0x680bb0u));	/* 4361c6: mov esi, dword ptr [0x680bb0] */
	m->edx = M32((DWORD)(0x4df818u));	/* 4361cc: mov edx, dword ptr [0x4df818] */
	m->ecx = M32((DWORD)(0x67ef30u));	/* 4361d2: mov ecx, dword ptr [0x67ef30] */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x0u);	/* 4361d8: lea eax, [esi + edx] */
	m->ebx = (DWORD)(m->ecx + 0xffffffffu);	/* 4361db: lea ebx, [ecx - 1] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4361de: cmp eax, ebx */
	if (m->sf == m->of) goto L_4363cf;	/* 4361e0: jge 0x4363cf */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4361e6: cmp edx, 8 */
	if (m->sf == m->of) goto L_436203;	/* 4361e9: jge 0x436203 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4361eb: cmp eax, ecx */
	if (m->sf == m->of) goto L_43620e;	/* 4361ed: jge 0x43620e */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4361ef: inc edx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4361f0: add esi, edx */
	M32((DWORD)(0x4df818u)) = m->edx;	/* 4361f2: mov dword ptr [0x4df818], edx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 4361f8: mov dword ptr [0x76d41c], esi */
	goto L_4362d2;	/* 4361fe: jmp 0x4362d2 */
L_436203:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436203: cmp eax, ecx */
	if (m->sf == m->of) goto L_43620e;	/* 436205: jge 0x43620e */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 436207: inc esi */
	M32((DWORD)(0x680bb0u)) = m->esi;	/* 436208: mov dword ptr [0x680bb0], esi */
L_43620e:
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43620e: add esi, edx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 436210: mov dword ptr [0x76d41c], esi */
	goto L_4362d2;	/* 436216: jmp 0x4362d2 */
L_43621b:
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43621b: cmp eax, 4 */
	if (m->sf != m->of) goto L_4362d2;	/* 43621e: jl 0x4362d2 */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436224: cmp eax, 0xc */
	if (!m->zf && m->sf == m->of) goto L_4362d2;	/* 436227: jg 0x4362d2 */
	m->edx = M32((DWORD)(0x680bb0u));	/* 43622d: mov edx, dword ptr [0x680bb0] */
	m->esi = (DWORD)(m->eax + 0xfffffffcu);	/* 436233: lea esi, [eax - 4] */
	m->eax = M32((DWORD)(0x67ef30u));	/* 436236: mov eax, dword ptr [0x67ef30] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43623b: add edx, esi */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43623d: cmp edx, eax */
	if (m->sf == m->of) goto L_4363cf;	/* 43623f: jge 0x4363cf */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(0x4df818u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436245: cmp esi, dword ptr [0x4df818] */
	if (!m->zf) goto L_4362a7;	/* 43624b: jne 0x4362a7 */
	{ DWORD a_ = M32((DWORD)(0x9dd34cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43624d: cmp dword ptr [0x9dd34c], edi */
	if (m->zf) goto L_4362a7;	/* 436253: je 0x4362a7 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436255: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_4363cf;	/* 436257: jle 0x4363cf */
	{ DWORD a_ = M32((DWORD)(0x9dd6a0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43625d: cmp dword ptr [0x9dd6a0], edi */
	if (!m->zf) goto L_436087;	/* 436263: jne 0x436087 */
	{ DWORD a_ = M32((DWORD)(0x9dd3fcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436269: cmp dword ptr [0x9dd3fc], edi */
	if (!m->zf) goto L_436087;	/* 43626f: jne 0x436087 */
	{ DWORD a_ = M32((DWORD)(0x9dd56cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436275: cmp dword ptr [0x9dd56c], edi */
	if (!m->zf) goto L_4363cf;	/* 43627b: jne 0x4363cf */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436281: push edi */
	m->esp -= 4; M32(m->esp) = 0x436287u; native_call(m, 0x41e760u);	/* 436282: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436287: add esp, 4 */
	M32((DWORD)(0x9dd34cu)) = m->edi;	/* 43628a: mov dword ptr [0x9dd34c], edi */
	M32((DWORD)(0x9dcd40u)) = 0x0u;	/* 436290: mov dword ptr [0x9dcd40], 0 */
	M32((DWORD)(0x9dd56cu)) = m->ebx;	/* 43629a: mov dword ptr [0x9dd56c], ebx */
	m->esp -= 4; M32(m->esp) = 0x4362a5u; native_call(m, 0x434da0u);	/* 4362a0: call 0x434da0 */
	goto L_4362d2;	/* 4362a5: jmp 0x4362d2 */
L_4362a7:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4362a7: push edi */
	m->esp -= 4; M32(m->esp) = 0x4362adu; native_call(m, 0x41e760u);	/* 4362a8: call 0x41e760 */
	m->eax = M32((DWORD)(0x680bb0u));	/* 4362ad: mov eax, dword ptr [0x680bb0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4362b2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4362b5: add eax, esi */
	M32((DWORD)(0x9dd34cu)) = m->ebx;	/* 4362b7: mov dword ptr [0x9dd34c], ebx */
	M32((DWORD)(0x9dcd40u)) = 0x0u;	/* 4362bd: mov dword ptr [0x9dcd40], 0 */
	M32((DWORD)(0x4df818u)) = m->esi;	/* 4362c7: mov dword ptr [0x4df818], esi */
	M32((DWORD)(0x76d41cu)) = m->eax;	/* 4362cd: mov dword ptr [0x76d41c], eax */
L_4362d2:
	{ DWORD a_ = M32((DWORD)(0x4ded94u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4362d2: cmp dword ptr [0x4ded94], edi */
	if (m->zf) goto L_4363cf;	/* 4362d8: je 0x4363cf */
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 4362de: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 4362e4: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4362ea: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4362eb: push edx */
	m->esp -= 4; M32(m->esp) = 0x4362f1u; native_call(m, 0x432300u);	/* 4362ec: call 0x432300 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4362f1: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4362f4: sub eax, 0xd */
	if (m->zf) goto L_436382;	/* 4362f7: je 0x436382 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4362fd: dec eax */
	if (!m->zf) goto L_4363cf;	/* 4362fe: jne 0x4363cf */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 436304: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 43630a: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 436310: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 436312: test ah, 1 */
	if (!m->zf) goto L_4363cf;	/* 436315: jne 0x4363cf */
	m->esi = M32((DWORD)(0x680bb0u));	/* 43631b: mov esi, dword ptr [0x680bb0] */
	m->edx = M32((DWORD)(0x4df818u));	/* 436321: mov edx, dword ptr [0x4df818] */
	m->ecx = M32((DWORD)(0x67ef30u));	/* 436327: mov ecx, dword ptr [0x67ef30] */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x0u);	/* 43632d: lea eax, [esi + edx] */
	m->edi = (DWORD)(m->ecx + 0xffffffffu);	/* 436330: lea edi, [ecx - 1] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436333: cmp eax, edi */
	if (m->sf == m->of) goto L_4363cf;	/* 436335: jge 0x4363cf */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43633b: cmp edx, 8 */
	if (m->sf == m->of) goto L_436361;	/* 43633e: jge 0x436361 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436340: cmp eax, ecx */
	if (m->sf == m->of) goto L_43636c;	/* 436342: jge 0x43636c */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 436344: inc edx */
	m->edi = M32(m->esp); m->esp += 4;	/* 436345: pop edi */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 436346: add esi, edx */
	M32((DWORD)(0x4df818u)) = m->edx;	/* 436348: mov dword ptr [0x4df818], edx */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 43634e: mov dword ptr [0x76d41c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436354: pop esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 436355: mov dword ptr [0x4dda44], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43635f: pop ebx */
	m->esp += 4 + 0; return;	/* 436360: ret  */
L_436361:
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436361: cmp eax, ecx */
	if (m->sf == m->of) goto L_43636c;	/* 436363: jge 0x43636c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 436365: inc esi */
	M32((DWORD)(0x680bb0u)) = m->esi;	/* 436366: mov dword ptr [0x680bb0], esi */
L_43636c:
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43636c: add esi, edx */
	m->edi = M32(m->esp); m->esp += 4;	/* 43636e: pop edi */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 43636f: mov dword ptr [0x76d41c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436375: pop esi */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 436376: mov dword ptr [0x4dda44], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 436380: pop ebx */
	m->esp += 4 + 0; return;	/* 436381: ret  */
L_436382:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 436382: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 436388: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43638e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 436390: test ah, 1 */
	if (!m->zf) goto L_4363cf;	/* 436393: jne 0x4363cf */
	m->eax = M32((DWORD)(0x4df818u));	/* 436395: mov eax, dword ptr [0x4df818] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43639a: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_4363a6;	/* 43639c: jle 0x4363a6 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 43639e: dec eax */
	M32((DWORD)(0x4df818u)) = m->eax;	/* 43639f: mov dword ptr [0x4df818], eax */
	goto L_4363b7;	/* 4363a4: jmp 0x4363b7 */
L_4363a6:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 4363a6: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4363ac: cmp ecx, edi */
	if (m->zf || m->sf != m->of) goto L_4363b7;	/* 4363ae: jle 0x4363b7 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4363b0: dec ecx */
	M32((DWORD)(0x680bb0u)) = m->ecx;	/* 4363b1: mov dword ptr [0x680bb0], ecx */
L_4363b7:
	m->ecx = M32((DWORD)(0x680bb0u));	/* 4363b7: mov ecx, dword ptr [0x680bb0] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4363bd: mov dword ptr [0x4dda44], 0 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4363c7: add ecx, eax */
	M32((DWORD)(0x76d41cu)) = m->ecx;	/* 4363c9: mov dword ptr [0x76d41c], ecx */
L_4363cf:
	m->edi = M32(m->esp); m->esp += 4;	/* 4363cf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4363d0: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4363d1: pop ebx */
	m->esp += 4 + 0; return;	/* 4363d2: ret  */
}

/* menu_436990 (0x436990), lifted by tools/lift.py */
static void lift_436990(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd838u));	/* 436990: mov eax, dword ptr [0x9dd838] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 436995: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436996: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 436997: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436999: cmp eax, edi */
	if (!m->zf) goto L_4369a5;	/* 43699b: jne 0x4369a5 */
	{ DWORD a_ = M32((DWORD)(0x9dd1c8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43699d: cmp dword ptr [0x9dd1c8], edi */
	if (m->zf) goto L_436a06;	/* 4369a3: je 0x436a06 */
L_4369a5:
	m->eax = M32((DWORD)(0x76d48cu));	/* 4369a5: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4369aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4369b0u; native_call(m, 0x401600u);	/* 4369ab: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4369b0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4369b3: test eax, eax */
	if (m->zf) goto L_4369ee;	/* 4369b5: je 0x4369ee */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4369b7: push 4 */
	M32((DWORD)(0x9dd838u)) = m->edi;	/* 4369b9: mov dword ptr [0x9dd838], edi */
	M32((DWORD)(0xa0b378u)) = m->edi;	/* 4369bf: mov dword ptr [0xa0b378], edi */
	M32((DWORD)(0x9dd1c8u)) = m->edi;	/* 4369c5: mov dword ptr [0x9dd1c8], edi */
	M32((DWORD)(0x4e1868u)) = m->edi;	/* 4369cb: mov dword ptr [0x4e1868], edi */
	M32((DWORD)(0x68039cu)) = m->edi;	/* 4369d1: mov dword ptr [0x68039c], edi */
	m->esp -= 4; M32(m->esp) = 0x4369dcu; native_call(m, 0x441250u);	/* 4369d7: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4369dc: add esp, 4 */
	M32((DWORD)(0x9dd834u)) = 0x63u;	/* 4369df: mov dword ptr [0x9dd834], 0x63 */
	goto L_436a91;	/* 4369e9: jmp 0x436a91 */
L_4369ee:
	{ DWORD a_ = M32((DWORD)(0x9dd1c8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4369ee: cmp dword ptr [0x9dd1c8], edi */
	if (!m->zf) goto L_436e09;	/* 4369f4: jne 0x436e09 */
	{ DWORD a_ = M32((DWORD)(0x9dd838u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4369fa: cmp dword ptr [0x9dd838], edi */
	if (!m->zf) goto L_436e09;	/* 436a00: jne 0x436e09 */
L_436a06:
	m->ecx = M32((DWORD)(0x9dae70u));	/* 436a06: mov ecx, dword ptr [0x9dae70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436a0c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x436a12u; native_call(m, 0x401600u);	/* 436a0d: call 0x401600 */
	m->esi = 0x1u;	/* 436a12: mov esi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436a17: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436a1a: cmp eax, esi */
	if (!m->zf) goto L_436ad0;	/* 436a1c: jne 0x436ad0 */
	m->edx = M32((DWORD)(0x4ded6cu));	/* 436a22: mov edx, dword ptr [0x4ded6c] */
	m->eax = M32((DWORD)(0x4ded68u));	/* 436a28: mov eax, dword ptr [0x4ded68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 436a2d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436a2e: push eax */
	m->esp -= 4; M32(m->esp) = 0x436a34u; native_call(m, 0x432200u);	/* 436a2f: call 0x432200 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436a34: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436a37: cmp eax, 2 */
	if (!m->zf) goto L_436a66;	/* 436a3a: jne 0x436a66 */
	{ DWORD a_ = M32((DWORD)(0x9dd1c8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436a3c: cmp dword ptr [0x9dd1c8], edi */
	if (!m->zf) goto L_436e09;	/* 436a42: jne 0x436e09 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436a48: push edi */
	m->esp -= 4; M32(m->esp) = 0x436a4eu; native_call(m, 0x41e760u);	/* 436a49: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436a4e: add esp, 4 */
	M32((DWORD)(0x76d42cu)) = m->edi;	/* 436a51: mov dword ptr [0x76d42c], edi */
	M32((DWORD)(0x9dd198u)) = m->esi;	/* 436a57: mov dword ptr [0x9dd198], esi */
	M32((DWORD)(0x9dd1c8u)) = m->esi;	/* 436a5d: mov dword ptr [0x9dd1c8], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436a63: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436a64: pop esi */
	m->esp += 4 + 0; return;	/* 436a65: ret  */
L_436a66:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436a66: cmp eax, 3 */
	if (!m->zf) goto L_436aae;	/* 436a69: jne 0x436aae */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436a6b: push edi */
	m->esp -= 4; M32(m->esp) = 0x436a71u; native_call(m, 0x41e760u);	/* 436a6c: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 436a71: push 4 */
	M32((DWORD)(0x68039cu)) = m->edi;	/* 436a73: mov dword ptr [0x68039c], edi */
	m->esp -= 4; M32(m->esp) = 0x436a7eu; native_call(m, 0x441250u);	/* 436a79: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436a7e: add esp, 8 */
	M32((DWORD)(0x9dd834u)) = 0x63u;	/* 436a81: mov dword ptr [0x9dd834], 0x63 */
	M32((DWORD)(0x4e1868u)) = m->edi;	/* 436a8b: mov dword ptr [0x4e1868], edi */
L_436a91:
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 436a91: mov dword ptr [0x67ef20], 0x12c */
	m->esp -= 4; M32(m->esp) = 0x436aa0u; native_call(m, 0x48b420u);	/* 436a9b: call 0x48b420 */
	M32((DWORD)(0x76d42cu)) = m->edi;	/* 436aa0: mov dword ptr [0x76d42c], edi */
	m->esp -= 4; M32(m->esp) = 0x436aabu; native_call(m, 0x451e60u);	/* 436aa6: call 0x451e60 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436aab: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436aac: pop esi */
	m->esp += 4 + 0; return;	/* 436aad: ret  */
L_436aae:
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436aae: cmp eax, 4 */
	if (!m->zf) goto L_436ad0;	/* 436ab1: jne 0x436ad0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436ab3: push edi */
	M32((DWORD)(0x68039cu)) = m->edi;	/* 436ab4: mov dword ptr [0x68039c], edi */
	M32((DWORD)(0x76d42cu)) = m->edi;	/* 436aba: mov dword ptr [0x76d42c], edi */
	m->esp -= 4; M32(m->esp) = 0x436ac5u; native_call(m, 0x41e760u);	/* 436ac0: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436ac5: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x436acdu; native_call(m, 0x4338c0u);	/* 436ac8: call 0x4338c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436acd: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436ace: pop esi */
	m->esp += 4 + 0; return;	/* 436acf: ret  */
L_436ad0:
	m->ecx = M32((DWORD)(0x4e14f4u));	/* 436ad0: mov ecx, dword ptr [0x4e14f4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436ad6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x436adcu; native_call(m, 0x401600u);	/* 436ad7: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436adc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436adf: cmp eax, esi */
	if (!m->zf) goto L_436b13;	/* 436ae1: jne 0x436b13 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436ae3: cmp dword ptr [0x68039c], edi */
	if (!m->zf) goto L_436e09;	/* 436ae9: jne 0x436e09 */
	{ DWORD a_ = M32((DWORD)(0x9dd1c8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436aef: cmp dword ptr [0x9dd1c8], edi */
	if (!m->zf) goto L_436e09;	/* 436af5: jne 0x436e09 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436afb: push edi */
	m->esp -= 4; M32(m->esp) = 0x436b01u; native_call(m, 0x41e760u);	/* 436afc: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436b01: add esp, 4 */
	M32((DWORD)(0x9dd198u)) = m->esi;	/* 436b04: mov dword ptr [0x9dd198], esi */
	M32((DWORD)(0x9dd1c8u)) = m->esi;	/* 436b0a: mov dword ptr [0x9dd1c8], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436b10: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436b11: pop esi */
	m->esp += 4 + 0; return;	/* 436b12: ret  */
L_436b13:
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 436b13: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 436b19: push edx */
	m->esp -= 4; M32(m->esp) = 0x436b1fu; native_call(m, 0x401600u);	/* 436b1a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436b1f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436b22: cmp eax, esi */
	if (!m->zf) goto L_436b64;	/* 436b24: jne 0x436b64 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436b26: cmp dword ptr [0x68039c], edi */
	if (!m->zf) goto L_436e09;	/* 436b2c: jne 0x436e09 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436b32: push edi */
	M32((DWORD)(0x4e1868u)) = m->edi;	/* 436b33: mov dword ptr [0x4e1868], edi */
	m->esp -= 4; M32(m->esp) = 0x436b3eu; native_call(m, 0x41e760u);	/* 436b39: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 436b3e: push 4 */
	m->esp -= 4; M32(m->esp) = 0x436b45u; native_call(m, 0x441250u);	/* 436b40: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436b45: add esp, 8 */
	M32((DWORD)(0x9dd834u)) = 0x63u;	/* 436b48: mov dword ptr [0x9dd834], 0x63 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 436b52: mov dword ptr [0x67ef20], 0x12c */
	m->esp -= 4; M32(m->esp) = 0x436b61u; native_call(m, 0x48b420u);	/* 436b5c: call 0x48b420 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436b61: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436b62: pop esi */
	m->esp += 4 + 0; return;	/* 436b63: ret  */
L_436b64:
	m->eax = M32((DWORD)(0x4e150cu));	/* 436b64: mov eax, dword ptr [0x4e150c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436b69: push eax */
	m->esp -= 4; M32(m->esp) = 0x436b6fu; native_call(m, 0x401600u);	/* 436b6a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436b6f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436b72: cmp eax, esi */
	if (!m->zf) goto L_436b93;	/* 436b74: jne 0x436b93 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436b76: cmp dword ptr [0x68039c], edi */
	if (!m->zf) goto L_436e09;	/* 436b7c: jne 0x436e09 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 436b82: push edi */
	m->esp -= 4; M32(m->esp) = 0x436b88u; native_call(m, 0x41e760u);	/* 436b83: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436b88: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x436b90u; native_call(m, 0x4338c0u);	/* 436b8b: call 0x4338c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 436b90: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436b91: pop esi */
	m->esp += 4 + 0; return;	/* 436b92: ret  */
L_436b93:
	m->ecx = M32((DWORD)(0x680390u));	/* 436b93: mov ecx, dword ptr [0x680390] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436b99: push ecx */
	m->esp -= 4; M32(m->esp) = 0x436b9fu; native_call(m, 0x401600u);	/* 436b9a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436b9f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436ba2: cmp eax, esi */
	if (!m->zf) goto L_436e09;	/* 436ba4: jne 0x436e09 */
	m->edx = M32((DWORD)(0x67ef24u));	/* 436baa: mov edx, dword ptr [0x67ef24] */
	M32((DWORD)(0x9dc428u)) = 0x14u;	/* 436bb0: mov dword ptr [0x9dc428], 0x14 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 436bba: push edx */
	m->esp -= 4; M32(m->esp) = 0x436bc0u; native_call(m, 0x401590u);	/* 436bbb: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436bc0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436bc3: cmp eax, esi */
	if (m->zf) goto L_436bd9;	/* 436bc5: je 0x436bd9 */
	m->eax = M32((DWORD)(0x9db0acu));	/* 436bc7: mov eax, dword ptr [0x9db0ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436bcc: push eax */
	m->esp -= 4; M32(m->esp) = 0x436bd2u; native_call(m, 0x401590u);	/* 436bcd: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436bd2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436bd5: cmp eax, esi */
	if (!m->zf) goto L_436be8;	/* 436bd7: jne 0x436be8 */
L_436bd9:
	M32((DWORD)(0x9dc428u)) = 0xau;	/* 436bd9: mov dword ptr [0x9dc428], 0xa */
	goto L_436d08;	/* 436be3: jmp 0x436d08 */
L_436be8:
	m->eax = M32((DWORD)(0x9dc428u));	/* 436be8: mov eax, dword ptr [0x9dc428] */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436bed: cmp eax, 0x14 */
	if (!m->zf) goto L_436cff;	/* 436bf0: jne 0x436cff */
	m->eax = M32((DWORD)(0x74de1cu));	/* 436bf6: mov eax, dword ptr [0x74de1c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 436bfb: dec eax */
	if (m->zf) goto L_436cb3;	/* 436bfc: je 0x436cb3 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 436c02: dec eax */
	if (m->zf) goto L_436c68;	/* 436c03: je 0x436c68 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 436c05: dec eax */
	if (!m->zf) goto L_436e09;	/* 436c06: jne 0x436e09 */
	m->ecx = M32((DWORD)(0x9dd358u));	/* 436c0c: mov ecx, dword ptr [0x9dd358] */
	m->edx = M32((DWORD)(0x9dd35cu));	/* 436c12: mov edx, dword ptr [0x9dd35c] */
	{ DWORD a_ = m->ecx, b_ = 0x180u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 436c18: add ecx, 0x180 */
	{ DWORD a_ = m->edx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 436c1e: add edx, 0x88 */
	M32((DWORD)(0x74de1cu)) = 0x3u;	/* 436c24: mov dword ptr [0x74de1c], 3 */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 436c2e: mov dword ptr [0x76d42c], esi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 436c34: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 436c3e: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->ecx;	/* 436c48: mov dword ptr [0x67ef34], ecx */
	M32((DWORD)(0x67fb38u)) = m->edx;	/* 436c4e: mov dword ptr [0x67fb38], edx */
	m->esp -= 4; M32(m->esp) = 0x436c59u; native_call(m, 0x433b00u);	/* 436c54: call 0x433b00 */
	M32((DWORD)(0x9dc428u)) = m->edi;	/* 436c59: mov dword ptr [0x9dc428], edi */
	M32((DWORD)(0x9dd1ccu)) = m->esi;	/* 436c5f: mov dword ptr [0x9dd1cc], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436c65: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436c66: pop esi */
	m->esp += 4 + 0; return;	/* 436c67: ret  */
L_436c68:
	m->eax = M32((DWORD)(0x9dd358u));	/* 436c68: mov eax, dword ptr [0x9dd358] */
	m->ecx = M32((DWORD)(0x9dd364u));	/* 436c6d: mov ecx, dword ptr [0x9dd364] */
	{ DWORD a_ = m->eax, b_ = 0x1a2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 436c73: add eax, 0x1a2 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 436c78: add ecx, -0x30 */
	M32((DWORD)(0x9dc428u)) = m->edi;	/* 436c7b: mov dword ptr [0x9dc428], edi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 436c81: mov dword ptr [0x76d42c], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436c87: pop edi */
	M32((DWORD)(0x74de1cu)) = 0x3u;	/* 436c88: mov dword ptr [0x74de1c], 3 */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 436c92: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 436c9c: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->eax;	/* 436ca6: mov dword ptr [0x67ef34], eax */
	M32((DWORD)(0x67fb38u)) = m->ecx;	/* 436cab: mov dword ptr [0x67fb38], ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 436cb1: pop esi */
	m->esp += 4 + 0; return;	/* 436cb2: ret  */
L_436cb3:
	m->edx = M32((DWORD)(0x9dd358u));	/* 436cb3: mov edx, dword ptr [0x9dd358] */
	m->eax = M32((DWORD)(0x9dd364u));	/* 436cb9: mov eax, dword ptr [0x9dd364] */
	{ DWORD a_ = m->edx, b_ = 0x102u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 436cbe: add edx, 0x102 */
	{ DWORD a_ = m->eax, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 436cc4: add eax, -0x30 */
	M32((DWORD)(0x9dc428u)) = m->edi;	/* 436cc7: mov dword ptr [0x9dc428], edi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 436ccd: mov dword ptr [0x76d42c], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436cd3: pop edi */
	M32((DWORD)(0x74de1cu)) = 0x2u;	/* 436cd4: mov dword ptr [0x74de1c], 2 */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 436cde: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 436ce8: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->edx;	/* 436cf2: mov dword ptr [0x67ef34], edx */
	M32((DWORD)(0x67fb38u)) = m->eax;	/* 436cf8: mov dword ptr [0x67fb38], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 436cfd: pop esi */
	m->esp += 4 + 0; return;	/* 436cfe: ret  */
L_436cff:
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436cff: cmp eax, 0xa */
	if (!m->zf) goto L_436e09;	/* 436d02: jne 0x436e09 */
L_436d08:
	m->eax = M32((DWORD)(0x74de1cu));	/* 436d08: mov eax, dword ptr [0x74de1c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 436d0d: dec eax */
	if (m->zf) goto L_436db1;	/* 436d0e: je 0x436db1 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 436d14: dec eax */
	if (m->zf) goto L_436d6c;	/* 436d15: je 0x436d6c */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 436d17: dec eax */
	if (!m->zf) goto L_436e09;	/* 436d18: jne 0x436e09 */
	m->ecx = M32((DWORD)(0x9dd358u));	/* 436d1e: mov ecx, dword ptr [0x9dd358] */
	m->edx = M32((DWORD)(0x9dd364u));	/* 436d24: mov edx, dword ptr [0x9dd364] */
	{ DWORD a_ = m->ecx, b_ = 0x102u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 436d2a: add ecx, 0x102 */
	{ DWORD a_ = m->edx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 436d30: add edx, -0x30 */
	M32((DWORD)(0x9dc428u)) = m->edi;	/* 436d33: mov dword ptr [0x9dc428], edi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 436d39: mov dword ptr [0x76d42c], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436d3f: pop edi */
	M32((DWORD)(0x74de1cu)) = 0x2u;	/* 436d40: mov dword ptr [0x74de1c], 2 */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 436d4a: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 436d54: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->ecx;	/* 436d5e: mov dword ptr [0x67ef34], ecx */
	M32((DWORD)(0x67fb38u)) = m->edx;	/* 436d64: mov dword ptr [0x67fb38], edx */
	m->esi = M32(m->esp); m->esp += 4;	/* 436d6a: pop esi */
	m->esp += 4 + 0; return;	/* 436d6b: ret  */
L_436d6c:
	m->eax = M32((DWORD)(0x9dd358u));	/* 436d6c: mov eax, dword ptr [0x9dd358] */
	m->ecx = M32((DWORD)(0x9dd364u));	/* 436d71: mov ecx, dword ptr [0x9dd364] */
	{ DWORD a_ = m->eax, b_ = 0x62u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 436d77: add eax, 0x62 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 436d7a: add ecx, -0x30 */
	M32((DWORD)(0x9dc428u)) = m->edi;	/* 436d7d: mov dword ptr [0x9dc428], edi */
	M32((DWORD)(0x74de1cu)) = m->esi;	/* 436d83: mov dword ptr [0x74de1c], esi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 436d89: mov dword ptr [0x76d42c], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 436d8f: pop edi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 436d90: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 436d9a: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->eax;	/* 436da4: mov dword ptr [0x67ef34], eax */
	M32((DWORD)(0x67fb38u)) = m->ecx;	/* 436da9: mov dword ptr [0x67fb38], ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 436daf: pop esi */
	m->esp += 4 + 0; return;	/* 436db0: ret  */
L_436db1:
	m->edx = M32((DWORD)(0x9dd358u));	/* 436db1: mov edx, dword ptr [0x9dd358] */
	m->eax = M32((DWORD)(0x9dd35cu));	/* 436db7: mov eax, dword ptr [0x9dd35c] */
	{ DWORD a_ = m->edx, b_ = 0x180u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 436dbc: add edx, 0x180 */
	{ DWORD a_ = m->eax, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 436dc2: add eax, 0x88 */
	M32((DWORD)(0x74de1cu)) = m->edi;	/* 436dc7: mov dword ptr [0x74de1c], edi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 436dcd: mov dword ptr [0x76d42c], esi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 436dd3: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 436ddd: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->edx;	/* 436de7: mov dword ptr [0x67ef34], edx */
	M32((DWORD)(0x67fb38u)) = m->eax;	/* 436ded: mov dword ptr [0x67fb38], eax */
	m->esp -= 4; M32(m->esp) = 0x436df7u; native_call(m, 0x433bb0u);	/* 436df2: call 0x433bb0 */
	M32((DWORD)(0x9dd6b0u)) = m->esi;	/* 436df7: mov dword ptr [0x9dd6b0], esi */
	M32((DWORD)(0x4e1868u)) = m->esi;	/* 436dfd: mov dword ptr [0x4e1868], esi */
	M32((DWORD)(0x9dc428u)) = m->edi;	/* 436e03: mov dword ptr [0x9dc428], edi */
L_436e09:
	m->edi = M32(m->esp); m->esp += 4;	/* 436e09: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 436e0a: pop esi */
	m->esp += 4 + 0; return;	/* 436e0b: ret  */
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
