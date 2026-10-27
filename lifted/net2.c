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

static void lift_434d00(X86 *m);
static void lift_4334c0(X86 *m);
static void lift_434b90(X86 *m);
static void lift_451e60(X86 *m);
static void lift_435a40(X86 *m);
static void lift_434820(X86 *m);
static void lift_40e930(X86 *m);
static void lift_4327f0(X86 *m);
static void lift_44aee0(X86 *m);
static void lift_451600(X86 *m);
static void lift_4521c0(X86 *m);

/* net_send (0x4521c0), lifted by tools/lift.py */
static void lift_4521c0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 4521c0: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4521c4: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 4521c5: mov esi, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4521c9: sub eax, 0x64 */
	if (m->zf) goto L_4521f7;	/* 4521cc: je 0x4521f7 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4521ce: dec eax */
	if (!m->zf) goto L_452221;	/* 4521cf: jne 0x452221 */
	m->eax = M32((DWORD)(0xa0b30cu));	/* 4521d1: mov eax, dword ptr [0xa0b30c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4521d6: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4521d8: je 0x4525cd */
	M32((DWORD)(m->eax + 0x0u)) = m->esi;	/* 4521de: mov dword ptr [eax], esi */
	m->eax = M32((DWORD)(0xa05630u));	/* 4521e0: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4521e5: test eax, eax */
	if (m->zf) goto L_45222e;	/* 4521e7: je 0x45222e */
	m->ecx = M32((DWORD)(0xa0b30cu));	/* 4521e9: mov ecx, dword ptr [0xa0b30c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4521ef: push 0 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4521f1: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4521f3: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4521f4: push eax */
	goto L_45221c;	/* 4521f5: jmp 0x45221c */
L_4521f7:
	m->eax = M32((DWORD)(0xa0b30cu));	/* 4521f7: mov eax, dword ptr [0xa0b30c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4521fc: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4521fe: je 0x4525cd */
	M32((DWORD)(m->eax + 0x0u)) = m->esi;	/* 452204: mov dword ptr [eax], esi */
	m->ecx = M32((DWORD)(0xa055f8u));	/* 452206: mov ecx, dword ptr [0xa055f8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45220c: test ecx, ecx */
	if (m->zf) goto L_452227;	/* 45220e: je 0x452227 */
	m->edx = M32((DWORD)(0xa0b30cu));	/* 452210: mov edx, dword ptr [0xa0b30c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452216: push 0 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 452218: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45221a: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45221b: push ecx */
L_45221c:
	m->esp -= 4; M32(m->esp) = 0x452221u; native_call(m, 0x4a82ceu);	/* 45221c: call 0x4a82ce */
L_452221:
	m->ecx = M32((DWORD)(0xa055f8u));	/* 452221: mov ecx, dword ptr [0xa055f8] */
L_452227:
	m->eax = M32((DWORD)(0xa05630u));	/* 452227: mov eax, dword ptr [0xa05630] */
	goto L_452234;	/* 45222c: jmp 0x452234 */
L_45222e:
	m->ecx = M32((DWORD)(0xa055f8u));	/* 45222e: mov ecx, dword ptr [0xa055f8] */
L_452234:
	m->edx = (DWORD)(m->esi + 0xfffffff6u);	/* 452234: lea edx, [esi - 0xa] */
	{ DWORD a_ = m->edx, b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452237: cmp edx, 0x13 */
	if (!m->cf && !m->zf) goto L_4525cd;	/* 45223a: ja 0x4525cd */
	switch (m->edx) { case 0: goto L_452247; case 1: goto L_452273; case 2: goto L_45229f; case 3: goto L_4522cb; case 4: goto L_45235f; case 5: goto L_45235f; case 6: goto L_4525cd; case 7: goto L_452404; case 8: goto L_45242d; case 9: goto L_45245a; case 10: goto L_452496; case 11: goto L_4524bf; case 12: goto L_4524f6; case 13: goto L_452302; case 14: goto L_452530; case 15: goto L_45256a; case 16: goto L_452585; case 17: goto L_4523af; case 18: goto L_4523db; case 19: goto L_4525aa; default: abort(); }	/* 452240: jmp dword ptr [edx*4 + 0x4525d0] */
L_452247:
	m->eax = M32((DWORD)(0xa0b310u));	/* 452247: mov eax, dword ptr [0xa0b310] */
	M32((DWORD)(0xa0b300u)) = 0xau;	/* 45224c: mov dword ptr [0xa0b300], 0xa */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452256: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452258: je 0x4525cd */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45225e: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 452260: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452266: push 0 */
	{ DWORD v_ = 0x5bu; m->esp -= 4; M32(m->esp) = v_; }	/* 452268: push 0x5b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45226a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45226b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x452271u; native_call(m, 0x4a82ceu);	/* 45226c: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 452271: pop esi */
	m->esp += 4 + 0; return;	/* 452272: ret  */
L_452273:
	m->eax = M32((DWORD)(0xa0b318u));	/* 452273: mov eax, dword ptr [0xa0b318] */
	M32((DWORD)(0xa0b300u)) = 0xbu;	/* 452278: mov dword ptr [0xa0b300], 0xb */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452282: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452284: je 0x4525cd */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45228a: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 45228c: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452292: push 0 */
	{ DWORD v_ = 0x5bu; m->esp -= 4; M32(m->esp) = v_; }	/* 452294: push 0x5b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452296: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452297: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45229du; native_call(m, 0x4a82ceu);	/* 452298: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 45229d: pop esi */
	m->esp += 4 + 0; return;	/* 45229e: ret  */
L_45229f:
	m->eax = M32((DWORD)(0xa0b314u));	/* 45229f: mov eax, dword ptr [0xa0b314] */
	M32((DWORD)(0xa0b300u)) = 0xcu;	/* 4522a4: mov dword ptr [0xa0b300], 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4522ae: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4522b0: je 0x4525cd */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4522b6: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 4522b8: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4522be: push 0 */
	{ DWORD v_ = 0x5bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4522c0: push 0x5b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4522c2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4522c3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4522c9u; native_call(m, 0x4a82ceu);	/* 4522c4: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 4522c9: pop esi */
	m->esp += 4 + 0; return;	/* 4522ca: ret  */
L_4522cb:
	m->esp -= 4; M32(m->esp) = 0x4522d0u; native_call(m, 0x452e60u);	/* 4522cb: call 0x452e60 */
	m->ecx = M32((DWORD)(0xa0b31cu));	/* 4522d0: mov ecx, dword ptr [0xa0b31c] */
	M32((DWORD)(0xa0b300u)) = 0xdu;	/* 4522d6: mov dword ptr [0xa0b300], 0xd */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4522e0: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 4522e2: je 0x4525cd */
	m->eax = M32((DWORD)(0xa055f8u));	/* 4522e8: mov eax, dword ptr [0xa055f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4522ed: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4522ef: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4522f5: push 0 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4522f7: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4522f9: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4522fa: push eax */
	m->esp -= 4; M32(m->esp) = 0x452300u; native_call(m, 0x4a82ceu);	/* 4522fb: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 452300: pop esi */
	m->esp += 4 + 0; return;	/* 452301: ret  */
L_452302:
	m->edx = M32((DWORD)(0xa0b304u));	/* 452302: mov edx, dword ptr [0xa0b304] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452308: test edx, edx */
	if (m->zf) goto L_4525cd;	/* 45230a: je 0x4525cd */
	m->eax = M32((DWORD)(0xa0b310u));	/* 452310: mov eax, dword ptr [0xa0b310] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452315: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452317: je 0x4525cd */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45231d: push edi */
	m->edi = (DWORD)(m->eax + 0x33u);	/* 45231e: lea edi, [eax + 0x33] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 452321: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 452324: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 452326: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 452328: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45232a: sub edi, ecx */
	m->eax = m->ecx;	/* 45232c: mov eax, ecx */
	m->esi = m->edi;	/* 45232e: mov esi, edi */
	m->edi = m->edx;	/* 452330: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 452332: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 452335: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 452337: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 452339: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 45233c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(0xa055f8u));	/* 45233e: mov eax, dword ptr [0xa055f8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 452343: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452344: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452346: je 0x4525cd */
	m->ecx = M32((DWORD)(0xa0b304u));	/* 45234c: mov ecx, dword ptr [0xa0b304] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452352: push 0 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 452354: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452356: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452357: push eax */
	m->esp -= 4; M32(m->esp) = 0x45235du; native_call(m, 0x4a82ceu);	/* 452358: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 45235d: pop esi */
	m->esp += 4 + 0; return;	/* 45235e: ret  */
L_45235f:
	m->eax = M32((DWORD)(0xa0b320u));	/* 45235f: mov eax, dword ptr [0xa0b320] */
	M32((DWORD)(0xa0b300u)) = m->esi;	/* 452364: mov dword ptr [0xa0b300], esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45236a: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 45236c: je 0x4525cd */
	m->esp -= 4; M32(m->esp) = 0x452377u; native_call(m, 0x4532e0u);	/* 452372: call 0x4532e0 */
	m->edx = M32((DWORD)(0xa0b320u));	/* 452377: mov edx, dword ptr [0xa0b320] */
	{ DWORD v_ = 0xa0b43cu; m->esp -= 4; M32(m->esp) = v_; }	/* 45237d: push 0xa0b43c */
	{ DWORD a_ = m->edx, b_ = 0x60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 452382: add edx, 0x60 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452385: push edx */
	m->esp -= 4; M32(m->esp) = 0x45238cu; native_call(m, M32(0x4a911cu));	/* 452386: call dword ptr [0x4a911c] */
	m->eax = M32((DWORD)(0xa05630u));	/* 45238c: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452391: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452393: je 0x4525cd */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 452399: mov ecx, dword ptr [0xa0b320] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45239f: push 0 */
	{ DWORD v_ = 0x10bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4523a1: push 0x10b */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4523a6: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4523a7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4523adu; native_call(m, 0x4a82ceu);	/* 4523a8: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 4523ad: pop esi */
	m->esp += 4 + 0; return;	/* 4523ae: ret  */
L_4523af:
	m->ecx = M32((DWORD)(0xa0b340u));	/* 4523af: mov ecx, dword ptr [0xa0b340] */
	M32((DWORD)(0xa0b300u)) = m->esi;	/* 4523b5: mov dword ptr [0xa0b300], esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4523bb: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 4523bd: je 0x4525cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4523c3: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4523c5: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4523cb: push 0 */
	{ DWORD v_ = 0xb9u; m->esp -= 4; M32(m->esp) = v_; }	/* 4523cd: push 0xb9 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4523d2: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4523d3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4523d9u; native_call(m, 0x4a82ceu);	/* 4523d4: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 4523d9: pop esi */
	m->esp += 4 + 0; return;	/* 4523da: ret  */
L_4523db:
	m->ecx = M32((DWORD)(0xa0b344u));	/* 4523db: mov ecx, dword ptr [0xa0b344] */
	M32((DWORD)(0xa0b300u)) = m->esi;	/* 4523e1: mov dword ptr [0xa0b300], esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4523e7: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 4523e9: je 0x4525cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4523ef: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4523f1: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4523f7: push 0 */
	{ DWORD v_ = 0x5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4523f9: push 0x5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4523fb: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4523fc: push eax */
	m->esp -= 4; M32(m->esp) = 0x452402u; native_call(m, 0x4a82ceu);	/* 4523fd: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 452402: pop esi */
	m->esp += 4 + 0; return;	/* 452403: ret  */
L_452404:
	m->ecx = M32((DWORD)(0xa0b338u));	/* 452404: mov ecx, dword ptr [0xa0b338] */
	M32((DWORD)(0xa0b300u)) = m->esi;	/* 45240a: mov dword ptr [0xa0b300], esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452410: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 452412: je 0x4525cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452418: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 45241a: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452420: push 0 */
	{ DWORD v_ = 0x36u; m->esp -= 4; M32(m->esp) = v_; }	/* 452422: push 0x36 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452424: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452425: push eax */
	m->esp -= 4; M32(m->esp) = 0x45242bu; native_call(m, 0x4a82ceu);	/* 452426: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 45242b: pop esi */
	m->esp += 4 + 0; return;	/* 45242c: ret  */
L_45242d:
	m->ecx = M32((DWORD)(0xa0b328u));	/* 45242d: mov ecx, dword ptr [0xa0b328] */
	M32((DWORD)(0xa0b300u)) = 0x12u;	/* 452433: mov dword ptr [0xa0b300], 0x12 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45243d: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 45243f: je 0x4525cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452445: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452447: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45244d: push 0 */
	{ DWORD v_ = 0x79u; m->esp -= 4; M32(m->esp) = v_; }	/* 45244f: push 0x79 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452451: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452452: push eax */
	m->esp -= 4; M32(m->esp) = 0x452458u; native_call(m, 0x4a82ceu);	/* 452453: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 452458: pop esi */
	m->esp += 4 + 0; return;	/* 452459: ret  */
L_45245a:
	m->esp -= 4; M32(m->esp) = 0x45245fu; native_call(m, 0x454690u);	/* 45245a: call 0x454690 */
	m->esp -= 4; M32(m->esp) = 0x452464u; native_call(m, 0x452e80u);	/* 45245f: call 0x452e80 */
	m->ecx = M32((DWORD)(0xa0b334u));	/* 452464: mov ecx, dword ptr [0xa0b334] */
	M32((DWORD)(0xa0b300u)) = 0x13u;	/* 45246a: mov dword ptr [0xa0b300], 0x13 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452474: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 452476: je 0x4525cd */
	m->eax = M32((DWORD)(0xa05630u));	/* 45247c: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452481: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452483: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452489: push 0 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45248b: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45248d: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45248e: push eax */
	m->esp -= 4; M32(m->esp) = 0x452494u; native_call(m, 0x4a82ceu);	/* 45248f: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 452494: pop esi */
	m->esp += 4 + 0; return;	/* 452495: ret  */
L_452496:
	m->ecx = M32((DWORD)(0xa0b32cu));	/* 452496: mov ecx, dword ptr [0xa0b32c] */
	M32((DWORD)(0xa0b300u)) = m->esi;	/* 45249c: mov dword ptr [0xa0b300], esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4524a2: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 4524a4: je 0x4525cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4524aa: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4524ac: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4524b2: push 0 */
	{ DWORD v_ = 0x79u; m->esp -= 4; M32(m->esp) = v_; }	/* 4524b4: push 0x79 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4524b6: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4524b7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4524bdu; native_call(m, 0x4a82ceu);	/* 4524b8: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 4524bd: pop esi */
	m->esp += 4 + 0; return;	/* 4524be: ret  */
L_4524bf:
	m->esp -= 4; M32(m->esp) = 0x4524c4u; native_call(m, 0x452ea0u);	/* 4524bf: call 0x452ea0 */
	m->ecx = M32((DWORD)(0xa0b324u));	/* 4524c4: mov ecx, dword ptr [0xa0b324] */
	M32((DWORD)(0xa0b300u)) = 0x15u;	/* 4524ca: mov dword ptr [0xa0b300], 0x15 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4524d4: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 4524d6: je 0x4525cd */
	m->eax = M32((DWORD)(0xa05630u));	/* 4524dc: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4524e1: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4524e3: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4524e9: push 0 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4524eb: push 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4524ed: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4524ee: push eax */
	m->esp -= 4; M32(m->esp) = 0x4524f4u; native_call(m, 0x4a82ceu);	/* 4524ef: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 4524f4: pop esi */
	m->esp += 4 + 0; return;	/* 4524f5: ret  */
L_4524f6:
	m->eax = M32((DWORD)(0xa0b330u));	/* 4524f6: mov eax, dword ptr [0xa0b330] */
	M32((DWORD)(0xa0b300u)) = 0x16u;	/* 4524fb: mov dword ptr [0xa0b300], 0x16 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452505: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452507: je 0x4525cd */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x1u);	/* 45250d: mov byte ptr [eax], 1 */
	m->eax = M32((DWORD)(0xa05630u));	/* 452510: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452515: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452517: je 0x4525cd */
	m->edx = M32((DWORD)(0xa0b330u));	/* 45251d: mov edx, dword ptr [0xa0b330] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452523: push 0 */
	{ DWORD v_ = 0x79u; m->esp -= 4; M32(m->esp) = v_; }	/* 452525: push 0x79 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452527: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452528: push eax */
	m->esp -= 4; M32(m->esp) = 0x45252eu; native_call(m, 0x4a82ceu);	/* 452529: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 45252e: pop esi */
	m->esp += 4 + 0; return;	/* 45252f: ret  */
L_452530:
	m->esp -= 4; M32(m->esp) = 0x452535u; native_call(m, 0x4532e0u);	/* 452530: call 0x4532e0 */
	m->eax = M32((DWORD)(0xa0b308u));	/* 452535: mov eax, dword ptr [0xa0b308] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45253a: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 45253c: je 0x4525cd */
	{ DWORD v_ = 0xa0b43cu; m->esp -= 4; M32(m->esp) = v_; }	/* 452542: push 0xa0b43c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452547: push eax */
	m->esp -= 4; M32(m->esp) = 0x45254eu; native_call(m, M32(0x4a911cu));	/* 452548: call dword ptr [0x4a911c] */
	m->eax = M32((DWORD)(0xa05630u));	/* 45254e: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452553: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452555: je 0x4525cd */
	m->ecx = M32((DWORD)(0xa0b308u));	/* 452557: mov ecx, dword ptr [0xa0b308] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45255d: push 0 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 45255f: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452561: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452562: push eax */
	m->esp -= 4; M32(m->esp) = 0x452568u; native_call(m, 0x4a82ceu);	/* 452563: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 452568: pop esi */
	m->esp += 4 + 0; return;	/* 452569: ret  */
L_45256a:
	m->ecx = M32((DWORD)(0xa0b33cu));	/* 45256a: mov ecx, dword ptr [0xa0b33c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452570: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 452572: je 0x4525cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452574: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 452576: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452578: push 0 */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 45257a: push 0x1e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45257c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45257d: push eax */
	m->esp -= 4; M32(m->esp) = 0x452583u; native_call(m, 0x4a82ceu);	/* 45257e: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 452583: pop esi */
	m->esp += 4 + 0; return;	/* 452584: ret  */
L_452585:
	m->esp -= 4; M32(m->esp) = 0x45258au; native_call(m, 0x452ea0u);	/* 452585: call 0x452ea0 */
	m->ecx = M32((DWORD)(0xa052e4u));	/* 45258a: mov ecx, dword ptr [0xa052e4] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452590: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 452592: je 0x4525cd */
	m->eax = M32((DWORD)(0xa05630u));	/* 452594: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452599: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 45259b: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45259d: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45259f: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4525a1: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4525a2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4525a8u; native_call(m, 0x4a82ceu);	/* 4525a3: call 0x4a82ce */
	m->esi = M32(m->esp); m->esp += 4;	/* 4525a8: pop esi */
	m->esp += 4 + 0; return;	/* 4525a9: ret  */
L_4525aa:
	m->ecx = M32((DWORD)(0xa055e0u));	/* 4525aa: mov ecx, dword ptr [0xa055e0] */
	M32((DWORD)(0xa0b300u)) = 0x1du;	/* 4525b0: mov dword ptr [0xa0b300], 0x1d */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4525ba: test ecx, ecx */
	if (m->zf) goto L_4525cd;	/* 4525bc: je 0x4525cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4525be: test eax, eax */
	if (m->zf) goto L_4525cd;	/* 4525c0: je 0x4525cd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4525c2: push 0 */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 4525c4: push 0x1e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4525c6: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4525c7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4525cdu; native_call(m, 0x4a82ceu);	/* 4525c8: call 0x4a82ce */
L_4525cd:
	m->esi = M32(m->esp); m->esp += 4;	/* 4525cd: pop esi */
	m->esp += 4 + 0; return;	/* 4525ce: ret  */
}

/* room_434d00 (0x434d00), lifted by tools/lift.py */
static void lift_434d00(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 434d00: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 434d01: xor esi, esi */
	M32((DWORD)(0x4dba88u)) = 0x1u;	/* 434d03: mov dword ptr [0x4dba88], 1 */
	M32((DWORD)(0x4ded60u)) = 0x2u;	/* 434d0d: mov dword ptr [0x4ded60], 2 */
	M32((DWORD)(0x9da498u)) = m->esi;	/* 434d17: mov dword ptr [0x9da498], esi */
	M32((DWORD)(0x9dd3fcu)) = m->esi;	/* 434d1d: mov dword ptr [0x9dd3fc], esi */
	M32((DWORD)(0x9dd6a0u)) = 0x1u;	/* 434d23: mov dword ptr [0x9dd6a0], 1 */
	M32((DWORD)(0xa0b34cu)) = m->esi;	/* 434d2d: mov dword ptr [0xa0b34c], esi */
	M32((DWORD)(0x9087b0u)) = m->esi;	/* 434d33: mov dword ptr [0x9087b0], esi */
	M32((DWORD)(0x67ef30u)) = m->esi;	/* 434d39: mov dword ptr [0x67ef30], esi */
	M32((DWORD)(0x9dd330u)) = 0x1u;	/* 434d3f: mov dword ptr [0x9dd330], 1 */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 434d49: mov dword ptr [0x76d41c], esi */
	M32((DWORD)(0x4dba80u)) = 0x447a0000u;	/* 434d4f: mov dword ptr [0x4dba80], 0x447a0000 */
	M32((DWORD)(0x680bb0u)) = m->esi;	/* 434d59: mov dword ptr [0x680bb0], esi */
	M32((DWORD)(0x4df818u)) = m->esi;	/* 434d5f: mov dword ptr [0x4df818], esi */
	m->esp -= 4; M32(m->esp) = 0x434d6au; native_call(m, 0x4045e0u);	/* 434d65: call 0x4045e0 */
	m->eax = M32((DWORD)(0xa0b334u));	/* 434d6a: mov eax, dword ptr [0xa0b334] */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 434d6f: push 0x65 */
	{ DWORD v_ = 0x13u; m->esp -= 4; M32(m->esp) = v_; }	/* 434d71: push 0x13 */
	M32((DWORD)(m->eax + 0x0u)) = 0x180001u;	/* 434d73: mov dword ptr [eax], 0x180001 */
	m->esp -= 4; M32(m->esp) = 0x434d7eu; lift_4521c0(m);	/* 434d79: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434d7e: add esp, 8 */
	M32((DWORD)(0x9dd840u)) = m->esi;	/* 434d81: mov dword ptr [0x9dd840], esi */
	M32((DWORD)(0x5b1914u)) = 0x1eu;	/* 434d87: mov dword ptr [0x5b1914], 0x1e */
	m->eax = 0x1u;	/* 434d91: mov eax, 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 434d96: pop esi */
	m->esp += 4 + 0; return;	/* 434d97: ret  */
}

/* room_4334c0 (0x4334c0), lifted by tools/lift.py */
static void lift_4334c0(X86 *m)
{
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4334c0: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4334c2: xor eax, eax */
	M32((DWORD)(0x9dd202u)) = m->ecx;	/* 4334c4: mov dword ptr [0x9dd202], ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4334ca: xor edx, edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4334cc: push ebx */
	M32((DWORD)(0x9dd1f6u)) = m->eax;	/* 4334cd: mov dword ptr [0x9dd1f6], eax */
	M32((DWORD)(0x9dd206u)) = m->ecx;	/* 4334d2: mov dword ptr [0x9dd206], ecx */
	M32((DWORD)(0x9dd6d8u)) = m->edx;	/* 4334d8: mov dword ptr [0x9dd6d8], edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4334de: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4334df: push edi */
	m->edi = M32((DWORD)(0xa055e0u));	/* 4334e0: mov edi, dword ptr [0xa055e0] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4334e6: xor ebx, ebx */
	M32((DWORD)(0x9dd1fau)) = m->eax;	/* 4334e8: mov dword ptr [0x9dd1fa], eax */
	M32((DWORD)(0x9dd20au)) = m->ecx;	/* 4334ed: mov dword ptr [0x9dd20a], ecx */
	M32((DWORD)(0x9dd6dcu)) = m->edx;	/* 4334f3: mov dword ptr [0x9dd6dc], edx */
	m->ecx = 0x7u;	/* 4334f9: mov ecx, 7 */
	M32((DWORD)(0x9dd834u)) = m->ebx;	/* 4334fe: mov dword ptr [0x9dd834], ebx */
	M32((DWORD)(0x9dce48u)) = 0x1u;	/* 433504: mov dword ptr [0x9dce48], 1 */
	M32((DWORD)(0x9dd6bcu)) = 0x3f333333u;	/* 43350e: mov dword ptr [0x9dd6bc], 0x3f333333 */
	M32((DWORD)(0x9dd69cu)) = m->ebx;	/* 433518: mov dword ptr [0x9dd69c], ebx */
	M32((DWORD)(0x9dd37cu)) = m->ebx;	/* 43351e: mov dword ptr [0x9dd37c], ebx */
	M32((DWORD)(0x9dd378u)) = m->ebx;	/* 433524: mov dword ptr [0x9dd378], ebx */
	M32((DWORD)(0x9dd304u)) = m->ebx;	/* 43352a: mov dword ptr [0x9dd304], ebx */
	M32((DWORD)(0x9dd6d0u)) = m->ebx;	/* 433530: mov dword ptr [0x9dd6d0], ebx */
	M32((DWORD)(0x9dd1feu)) = m->eax;	/* 433536: mov dword ptr [0x9dd1fe], eax */
	M32((DWORD)(0x9dd6e0u)) = m->edx;	/* 43353b: mov dword ptr [0x9dd6e0], edx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 433541: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 433543: stosw word ptr es:[edi], ax */
	m->edi = 0x9dd570u;	/* 433545: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43354a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43354d: xor eax, eax */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 43354f: push 0x65 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433551: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433553: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433555: sub edi, ecx */
	{ DWORD v_ = 0x1du; m->esp -= 4; M32(m->esp) = v_; }	/* 433557: push 0x1d */
	m->eax = m->ecx;	/* 433559: mov eax, ecx */
	m->esi = m->edi;	/* 43355b: mov esi, edi */
	m->edi = M32((DWORD)(0xa055e0u));	/* 43355d: mov edi, dword ptr [0xa055e0] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433563: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433566: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 433568: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43356a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43356d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x433574u; lift_4521c0(m);	/* 43356f: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433574: add esp, 8 */
	M32((DWORD)(0x9dd354u)) = m->ebx;	/* 433577: mov dword ptr [0x9dd354], ebx */
	M32((DWORD)(0x9dd6d4u)) = 0x1u;	/* 43357d: mov dword ptr [0x9dd6d4], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 433587: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433588: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 433589: pop ebx */
	m->esp += 4 + 0; return;	/* 43358a: ret  */
}

/* room_434b90 (0x434b90), lifted by tools/lift.py */
static void lift_434b90(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 434b90: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 434b91: push esi */
	m->esi = 0x9dd6d8u;	/* 434b92: mov esi, 0x9dd6d8 */
	m->eax = 0x9dd58eu;	/* 434b97: mov eax, 0x9dd58e */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 434b9c: xor ebx, ebx */
L_434b9e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 434b9e: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 434ba0: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434ba2: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_434bc2;	/* 434ba4: jne 0x434bc2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434ba6: cmp cl, bl */
	if (m->zf) goto L_434bbe;	/* 434ba8: je 0x434bbe */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 434baa: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 434bad: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434baf: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_434bc2;	/* 434bb2: jne 0x434bc2 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 434bb4: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 434bb7: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434bba: cmp cl, bl */
	if (!m->zf) goto L_434b9e;	/* 434bbc: jne 0x434b9e */
L_434bbe:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434bbe: xor eax, eax */
	goto L_434bc7;	/* 434bc0: jmp 0x434bc7 */
L_434bc2:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 434bc2: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 434bc4: sbb eax, -1 */
L_434bc7:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434bc7: cmp eax, ebx */
	if (!m->zf) goto L_434c61;	/* 434bc9: jne 0x434c61 */
	m->esi = 0x9dd202u;	/* 434bcf: mov esi, 0x9dd202 */
	m->eax = 0x9dd1f6u;	/* 434bd4: mov eax, 0x9dd1f6 */
L_434bd9:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 434bd9: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 434bdb: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434bdd: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_434bfd;	/* 434bdf: jne 0x434bfd */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434be1: cmp cl, bl */
	if (m->zf) goto L_434bf9;	/* 434be3: je 0x434bf9 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 434be5: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 434be8: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434bea: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_434bfd;	/* 434bed: jne 0x434bfd */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 434bef: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 434bf2: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 434bf5: cmp cl, bl */
	if (!m->zf) goto L_434bd9;	/* 434bf7: jne 0x434bd9 */
L_434bf9:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434bf9: xor eax, eax */
	goto L_434c02;	/* 434bfb: jmp 0x434c02 */
L_434bfd:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 434bfd: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 434bff: sbb eax, -1 */
L_434c02:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434c02: cmp eax, ebx */
	if (!m->zf) goto L_434c61;	/* 434c04: jne 0x434c61 */
	{ DWORD v_ = 0x9dd6d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 434c06: push 0x9dd6d8 */
	m->esp -= 4; M32(m->esp) = 0x434c10u; native_call(m, 0x434400u);	/* 434c0b: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434c10: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434c13: cmp eax, 1 */
	if (m->zf) goto L_434c4e;	/* 434c16: je 0x434c4e */
	{ DWORD v_ = 0x9dd1f6u; m->esp -= 4; M32(m->esp) = v_; }	/* 434c18: push 0x9dd1f6 */
	m->esp -= 4; M32(m->esp) = 0x434c22u; native_call(m, 0x434400u);	/* 434c1d: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434c22: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434c25: cmp eax, 1 */
	if (m->zf) goto L_434c4e;	/* 434c28: je 0x434c4e */
	{ DWORD v_ = 0x9dd202u; m->esp -= 4; M32(m->esp) = v_; }	/* 434c2a: push 0x9dd202 */
	m->esp -= 4; M32(m->esp) = 0x434c34u; native_call(m, 0x434400u);	/* 434c2f: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434c34: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434c37: cmp eax, 1 */
	if (m->zf) goto L_434c4e;	/* 434c3a: je 0x434c4e */
	{ DWORD v_ = 0x9dd20eu; m->esp -= 4; M32(m->esp) = v_; }	/* 434c3c: push 0x9dd20e */
	m->esp -= 4; M32(m->esp) = 0x434c46u; native_call(m, 0x434400u);	/* 434c41: call 0x434400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434c46: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434c49: cmp eax, 1 */
	if (!m->zf) goto L_434c66;	/* 434c4c: jne 0x434c66 */
L_434c4e:
	{ DWORD v_ = 0x81u; m->esp -= 4; M32(m->esp) = v_; }	/* 434c4e: push 0x81 */
	m->esp -= 4; M32(m->esp) = 0x434c58u; native_call(m, 0x41ee40u);	/* 434c53: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434c58: add esp, 4 */
	M32((DWORD)(0x9dd1c8u)) = m->ebx;	/* 434c5b: mov dword ptr [0x9dd1c8], ebx */
L_434c61:
	m->esi = M32(m->esp); m->esp += 4;	/* 434c61: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434c62: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 434c64: pop ebx */
	m->esp += 4 + 0; return;	/* 434c65: ret  */
L_434c66:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434c66: push edi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434c67: or ecx, 0xffffffff */
	m->edi = 0x9dd1d8u;	/* 434c6a: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434c6f: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434c71: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434c73: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434c75: sub edi, ecx */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 434c77: push 0x65 */
	m->eax = m->ecx;	/* 434c79: mov eax, ecx */
	m->esi = m->edi;	/* 434c7b: mov esi, edi */
	m->edi = M32((DWORD)(0xa0b344u));	/* 434c7d: mov edi, dword ptr [0xa0b344] */
	{ DWORD v_ = 0x1cu; m->esp -= 4; M32(m->esp) = v_; }	/* 434c83: push 0x1c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434c85: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434c88: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 434c8a: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434c8c: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434c8e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434c91: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b344u));	/* 434c93: mov ecx, dword ptr [0xa0b344] */
	m->edi = 0x9dd1f6u;	/* 434c99: mov edi, 0x9dd1f6 */
	m->edx = (DWORD)(m->ecx + 0x1eu);	/* 434c9e: lea edx, [ecx + 0x1e] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434ca1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434ca4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434ca6: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434ca8: sub edi, ecx */
	m->eax = m->ecx;	/* 434caa: mov eax, ecx */
	m->esi = m->edi;	/* 434cac: mov esi, edi */
	m->edi = m->edx;	/* 434cae: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434cb0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434cb3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 434cb5: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434cb7: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434cb9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434cbc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b344u));	/* 434cbe: mov ecx, dword ptr [0xa0b344] */
	m->edi = 0x9dd20eu;	/* 434cc4: mov edi, 0x9dd20e */
	m->edx = (DWORD)(m->ecx + 0x2au);	/* 434cc9: lea edx, [ecx + 0x2a] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434ccc: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434ccf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434cd1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434cd3: sub edi, ecx */
	m->eax = m->ecx;	/* 434cd5: mov eax, ecx */
	m->esi = m->edi;	/* 434cd7: mov esi, edi */
	m->edi = m->edx;	/* 434cd9: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434cdb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434cde: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 434ce0: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434ce2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434ce5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x434cecu; lift_4521c0(m);	/* 434ce7: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434cec: add esp, 8 */
	m->eax = 0x1u;	/* 434cef: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 434cf4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 434cf5: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 434cf6: pop ebx */
	m->esp += 4 + 0; return;	/* 434cf7: ret  */
}

/* net_disconnect (0x451e60), lifted by tools/lift.py */
static void lift_451e60(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b2fcu));	/* 451e60: mov eax, dword ptr [0xa0b2fc] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 451e65: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451e66: push esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451e67: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 451e6a: push edi */
	if (!m->zf) goto L_4520d8;	/* 451e6b: jne 0x4520d8 */
	m->eax = M32((DWORD)(0xa055f8u));	/* 451e71: mov eax, dword ptr [0xa055f8] */
	m->esi = M32((DWORD)(0x4a911cu));	/* 451e76: mov esi, dword ptr [0x4a911c] */
	m->edi = M32((DWORD)(0x4a9110u));	/* 451e7c: mov edi, dword ptr [0x4a9110] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 451e82: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451e84: cmp eax, ebp */
	if (m->zf) goto L_451fa1;	/* 451e86: je 0x451fa1 */
	{ DWORD a_ = M32((DWORD)(0xa0b360u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451e8c: cmp dword ptr [0xa0b360], ebp */
	if (!m->zf) goto L_451f77;	/* 451e92: jne 0x451f77 */
	m->eax = M32((DWORD)(0xa0b318u));	/* 451e98: mov eax, dword ptr [0xa0b318] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451e9d: cmp eax, ebp */
	if (m->zf) goto L_4520d8;	/* 451e9f: je 0x4520d8 */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x1u);	/* 451ea5: mov byte ptr [eax], 1 */
	m->eax = M32((DWORD)(0xa0b310u));	/* 451ea8: mov eax, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b318u));	/* 451ead: mov edx, dword ptr [0xa0b318] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x49u))) & 0xff) << 0);	/* 451eb3: mov cl, byte ptr [eax + 0x49] */
	M8((DWORD)(m->edx + 0x49u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 451eb6: mov byte ptr [edx + 0x49], cl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 451eb9: mov eax, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b318u));	/* 451ebe: mov edx, dword ptr [0xa0b318] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x47u))) & 0xff) << 0);	/* 451ec4: mov cl, byte ptr [eax + 0x47] */
	M8((DWORD)(m->edx + 0x47u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 451ec7: mov byte ptr [edx + 0x47], cl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 451eca: mov eax, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b318u));	/* 451ecf: mov edx, dword ptr [0xa0b318] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x48u))) & 0xff) << 0);	/* 451ed5: mov cl, byte ptr [eax + 0x48] */
	M8((DWORD)(m->edx + 0x48u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 451ed8: mov byte ptr [edx + 0x48], cl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 451edb: mov eax, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b318u));	/* 451ee0: mov edx, dword ptr [0xa0b318] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x46u))) & 0xff) << 0);	/* 451ee6: mov cl, byte ptr [eax + 0x46] */
	M8((DWORD)(m->edx + 0x46u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 451ee9: mov byte ptr [edx + 0x46], cl */
	m->eax = M32((DWORD)(0xa0b318u));	/* 451eec: mov eax, dword ptr [0xa0b318] */
	M8((DWORD)(m->eax + 0x45u)) = (BYTE)(0x1u);	/* 451ef1: mov byte ptr [eax + 0x45], 1 */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 451ef5: mov ecx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b318u));	/* 451efb: mov eax, dword ptr [0xa0b318] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x43u))) & 0xff) << 0);	/* 451f00: mov dl, byte ptr [ecx + 0x43] */
	M8((DWORD)(m->eax + 0x43u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 451f03: mov byte ptr [eax + 0x43], dl */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 451f06: mov ecx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b318u));	/* 451f0c: mov eax, dword ptr [0xa0b318] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x44u))) & 0xff) << 0);	/* 451f11: mov dl, byte ptr [ecx + 0x44] */
	M8((DWORD)(m->eax + 0x44u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 451f14: mov byte ptr [eax + 0x44], dl */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 451f17: mov ecx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b318u));	/* 451f1d: mov eax, dword ptr [0xa0b318] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x52u))) & 0xff) << 0);	/* 451f22: mov dl, byte ptr [ecx + 0x52] */
	M8((DWORD)(m->eax + 0x52u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 451f25: mov byte ptr [eax + 0x52], dl */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 451f28: mov ecx, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b318u));	/* 451f2e: mov edx, dword ptr [0xa0b318] */
	{ DWORD a_ = m->ecx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 451f34: add ecx, 0x53 */
	{ DWORD a_ = m->edx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 451f37: add edx, 0x53 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451f3a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451f3b: push edx */
	m->esp -= 4; M32(m->esp) = 0x451f3eu; native_call(m, m->esi);	/* 451f3c: call esi */
	m->eax = M32((DWORD)(0xa0b310u));	/* 451f3e: mov eax, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b318u));	/* 451f43: mov ecx, dword ptr [0xa0b318] */
	{ DWORD a_ = m->eax, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 451f49: add eax, 0x33 */
	{ DWORD a_ = m->ecx, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 451f4c: add ecx, 0x33 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451f4f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451f50: push ecx */
	m->esp -= 4; M32(m->esp) = 0x451f53u; native_call(m, m->esi);	/* 451f51: call esi */
	m->edx = M32((DWORD)(0xa0b310u));	/* 451f53: mov edx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b318u));	/* 451f59: mov eax, dword ptr [0xa0b318] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 451f5e: inc edx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 451f5f: inc eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451f60: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451f61: push eax */
	m->esp -= 4; M32(m->esp) = 0x451f64u; native_call(m, m->esi);	/* 451f62: call esi */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 451f64: push 0x64 */
	{ DWORD v_ = 0xbu; m->esp -= 4; M32(m->esp) = v_; }	/* 451f66: push 0xb */
	m->esp -= 4; M32(m->esp) = 0x451f6du; lift_4521c0(m);	/* 451f68: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451f6d: add esp, 8 */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 451f70: push 0x3e8 */
	m->esp -= 4; M32(m->esp) = 0x451f77u; native_call(m, m->edi);	/* 451f75: call edi */
L_451f77:
	m->esp -= 4; M32(m->esp) = 0x451f7cu; native_call(m, 0x4a8292u);	/* 451f77: call 0x4a8292 */
	m->ecx = M32((DWORD)(0xa055f8u));	/* 451f7c: mov ecx, dword ptr [0xa055f8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 451f82: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451f84: push ecx */
	m->esp -= 4; M32(m->esp) = 0x451f8au; native_call(m, 0x4a828cu);	/* 451f85: call 0x4a828c */
	m->edx = M32((DWORD)(0xa055f8u));	/* 451f8a: mov edx, dword ptr [0xa055f8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451f90: push edx */
	m->esp -= 4; M32(m->esp) = 0x451f96u; native_call(m, 0x4a8286u);	/* 451f91: call 0x4a8286 */
	M32((DWORD)(0xa055f8u)) = m->ebp;	/* 451f96: mov dword ptr [0xa055f8], ebp */
	m->esp -= 4; M32(m->esp) = 0x451fa1u; native_call(m, 0x4519b0u);	/* 451f9c: call 0x4519b0 */
L_451fa1:
	{ DWORD a_ = M32((DWORD)(0xa05630u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451fa1: cmp dword ptr [0xa05630], ebp */
	if (m->zf) goto L_4520c6;	/* 451fa7: je 0x4520c6 */
	{ DWORD a_ = M32((DWORD)(0xa0b364u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451fad: cmp dword ptr [0xa0b364], ebp */
	if (!m->zf) goto L_45209c;	/* 451fb3: jne 0x45209c */
	m->eax = M32((DWORD)(0xa0b330u));	/* 451fb9: mov eax, dword ptr [0xa0b330] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451fbe: cmp eax, ebp */
	if (m->zf) goto L_4520d8;	/* 451fc0: je 0x4520d8 */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x1u);	/* 451fc6: mov byte ptr [eax], 1 */
	m->eax = M32((DWORD)(0xa0b328u));	/* 451fc9: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b330u));	/* 451fce: mov edx, dword ptr [0xa0b330] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x67u))) & 0xff) << 0);	/* 451fd4: mov cl, byte ptr [eax + 0x67] */
	M8((DWORD)(m->edx + 0x67u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 451fd7: mov byte ptr [edx + 0x67], cl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 451fda: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b330u));	/* 451fdf: mov edx, dword ptr [0xa0b330] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x65u))) & 0xff) << 0);	/* 451fe5: mov cl, byte ptr [eax + 0x65] */
	M8((DWORD)(m->edx + 0x65u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 451fe8: mov byte ptr [edx + 0x65], cl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 451feb: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b330u));	/* 451ff0: mov edx, dword ptr [0xa0b330] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x64u))) & 0xff) << 0);	/* 451ff6: mov cl, byte ptr [eax + 0x64] */
	M8((DWORD)(m->edx + 0x64u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 451ff9: mov byte ptr [edx + 0x64], cl */
	m->eax = M32((DWORD)(0xa0b330u));	/* 451ffc: mov eax, dword ptr [0xa0b330] */
	M8((DWORD)(m->eax + 0x63u)) = (BYTE)(0x1u);	/* 452001: mov byte ptr [eax + 0x63], 1 */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 452005: mov ecx, dword ptr [0xa0b328] */
	m->eax = M32((DWORD)(0xa0b330u));	/* 45200b: mov eax, dword ptr [0xa0b330] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x61u))) & 0xff) << 0);	/* 452010: mov dl, byte ptr [ecx + 0x61] */
	M8((DWORD)(m->eax + 0x61u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452013: mov byte ptr [eax + 0x61], dl */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 452016: mov ecx, dword ptr [0xa0b328] */
	m->eax = M32((DWORD)(0xa0b330u));	/* 45201c: mov eax, dword ptr [0xa0b330] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x62u))) & 0xff) << 0);	/* 452021: mov dl, byte ptr [ecx + 0x62] */
	M8((DWORD)(m->eax + 0x62u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452024: mov byte ptr [eax + 0x62], dl */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 452027: mov ecx, dword ptr [0xa0b328] */
	m->eax = M32((DWORD)(0xa0b330u));	/* 45202d: mov eax, dword ptr [0xa0b330] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x66u))) & 0xff) << 0);	/* 452032: mov dl, byte ptr [ecx + 0x66] */
	M8((DWORD)(m->eax + 0x66u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452035: mov byte ptr [eax + 0x66], dl */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 452038: mov ecx, dword ptr [0xa0b328] */
	m->eax = M32((DWORD)(0xa0b330u));	/* 45203e: mov eax, dword ptr [0xa0b330] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x70u))) & 0xff) << 0);	/* 452043: mov dl, byte ptr [ecx + 0x70] */
	M8((DWORD)(m->eax + 0x70u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452046: mov byte ptr [eax + 0x70], dl */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 452049: mov ecx, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b330u));	/* 45204f: mov edx, dword ptr [0xa0b330] */
	{ DWORD a_ = m->ecx, b_ = 0x71u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 452055: add ecx, 0x71 */
	{ DWORD a_ = m->edx, b_ = 0x71u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 452058: add edx, 0x71 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45205b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45205c: push edx */
	m->esp -= 4; M32(m->esp) = 0x45205fu; native_call(m, m->esi);	/* 45205d: call esi */
	m->eax = M32((DWORD)(0xa0b328u));	/* 45205f: mov eax, dword ptr [0xa0b328] */
	m->ecx = M32((DWORD)(0xa0b330u));	/* 452064: mov ecx, dword ptr [0xa0b330] */
	{ DWORD a_ = m->eax, b_ = 0x43u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45206a: add eax, 0x43 */
	{ DWORD a_ = m->ecx, b_ = 0x43u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45206d: add ecx, 0x43 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452070: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452071: push ecx */
	m->esp -= 4; M32(m->esp) = 0x452074u; native_call(m, m->esi);	/* 452072: call esi */
	m->edx = M32((DWORD)(0xa0b328u));	/* 452074: mov edx, dword ptr [0xa0b328] */
	m->eax = M32((DWORD)(0xa0b330u));	/* 45207a: mov eax, dword ptr [0xa0b330] */
	{ DWORD a_ = m->edx, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45207f: add edx, 0x33 */
	{ DWORD a_ = m->eax, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452082: add eax, 0x33 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452085: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452086: push eax */
	m->esp -= 4; M32(m->esp) = 0x452089u; native_call(m, m->esi);	/* 452087: call esi */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 452089: push 0x65 */
	{ DWORD v_ = 0x16u; m->esp -= 4; M32(m->esp) = v_; }	/* 45208b: push 0x16 */
	m->esp -= 4; M32(m->esp) = 0x452092u; lift_4521c0(m);	/* 45208d: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 452092: add esp, 8 */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 452095: push 0x3e8 */
	m->esp -= 4; M32(m->esp) = 0x45209cu; native_call(m, m->edi);	/* 45209a: call edi */
L_45209c:
	m->esp -= 4; M32(m->esp) = 0x4520a1u; native_call(m, 0x4a8292u);	/* 45209c: call 0x4a8292 */
	m->ecx = M32((DWORD)(0xa05630u));	/* 4520a1: mov ecx, dword ptr [0xa05630] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4520a7: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4520a9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4520afu; native_call(m, 0x4a828cu);	/* 4520aa: call 0x4a828c */
	m->edx = M32((DWORD)(0xa05630u));	/* 4520af: mov edx, dword ptr [0xa05630] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4520b5: push edx */
	m->esp -= 4; M32(m->esp) = 0x4520bbu; native_call(m, 0x4a8286u);	/* 4520b6: call 0x4a8286 */
	M32((DWORD)(0xa05630u)) = m->ebp;	/* 4520bb: mov dword ptr [0xa05630], ebp */
	m->esp -= 4; M32(m->esp) = 0x4520c6u; native_call(m, 0x4519b0u);	/* 4520c1: call 0x4519b0 */
L_4520c6:
	M32((DWORD)(0xa0b300u)) = m->ebp;	/* 4520c6: mov dword ptr [0xa0b300], ebp */
	M32((DWORD)(0xa0b380u)) = m->ebp;	/* 4520cc: mov dword ptr [0xa0b380], ebp */
	M32((DWORD)(0xa0b2fcu)) = m->ebp;	/* 4520d2: mov dword ptr [0xa0b2fc], ebp */
L_4520d8:
	m->edi = M32(m->esp); m->esp += 4;	/* 4520d8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4520d9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4520da: pop ebp */
	m->esp += 4 + 0; return;	/* 4520db: ret  */
}

/* room_leaveGame (0x435a40), lifted by tools/lift.py */
static void lift_435a40(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 435a40: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 435a41: push edi */
	m->edi = 0x9dd570u;	/* 435a42: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 435a47: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 435a4a: xor eax, eax */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 435a4c: push 0x65 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 435a4e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 435a50: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 435a52: sub edi, ecx */
	{ DWORD v_ = 0x19u; m->esp -= 4; M32(m->esp) = v_; }	/* 435a54: push 0x19 */
	m->eax = m->ecx;	/* 435a56: mov eax, ecx */
	m->esi = m->edi;	/* 435a58: mov esi, edi */
	m->edi = M32((DWORD)(0xa0b33cu));	/* 435a5a: mov edi, dword ptr [0xa0b33c] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 435a60: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 435a63: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 435a65: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 435a67: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 435a6a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x435a71u; lift_4521c0(m);	/* 435a6c: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435a71: add esp, 8 */
	{ DWORD v_ = 0x1f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 435a74: push 0x1f4 */
	m->esp -= 4; M32(m->esp) = 0x435a7fu; native_call(m, M32(0x4a9110u));	/* 435a79: call dword ptr [0x4a9110] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 435a7f: push 4 */
	m->esp -= 4; M32(m->esp) = 0x435a86u; native_call(m, 0x441250u);	/* 435a81: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435a86: add esp, 4 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 435a89: mov dword ptr [0x67ef20], 0x12c */
	m->esp -= 4; M32(m->esp) = 0x435a98u; native_call(m, 0x48b420u);	/* 435a93: call 0x48b420 */
	m->esp -= 4; M32(m->esp) = 0x435a9du; lift_451e60(m);	/* 435a98: call 0x451e60 */
	M32((DWORD)(0x9dd84cu)) = 0x0u;	/* 435a9d: mov dword ptr [0x9dd84c], 0 */
	m->esp -= 4; M32(m->esp) = 0x435aacu; native_call(m, 0x4463a0u);	/* 435aa7: call 0x4463a0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 435aac: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 435aad: pop esi */
	m->esp += 4 + 0; return;	/* 435aae: ret  */
}

/* room_434820 (0x434820), lifted by tools/lift.py */
static void lift_434820(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 434820: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 434821: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 434822: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 434823: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434824: push edi */
	m->edi = 0x9dd1d8u;	/* 434825: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43482a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43482d: xor eax, eax */
	m->ebx = 0x3f800000u;	/* 43482f: mov ebx, 0x3f800000 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434834: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434836: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434838: sub edi, ecx */
	m->ebp = 0x3f19999au;	/* 43483a: mov ebp, 0x3f19999a */
	m->eax = m->ecx;	/* 43483f: mov eax, ecx */
	m->esi = m->edi;	/* 434841: mov esi, edi */
	m->edi = 0x9dd570u;	/* 434843: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434848: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43484b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43484d: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43484f: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434851: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434854: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x9dd20eu;	/* 434856: mov edi, 0x9dd20e */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43485b: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43485e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434860: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434862: sub edi, ecx */
	m->edx = m->ecx;	/* 434864: mov edx, ecx */
	m->esi = m->edi;	/* 434866: mov esi, edi */
	m->edi = 0x9dd5a6u;	/* 434868: mov edi, 0x9dd5a6 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43486d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434870: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 434872: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434874: and ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 434877: xor edx, edx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434879: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M8((DWORD)(0x9dd260u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 43487b: mov byte ptr [0x9dd260], dl */
	M8((DWORD)(0x9dd5f8u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434881: mov byte ptr [0x9dd5f8], dl */
	M8((DWORD)(0x9dd261u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434887: mov byte ptr [0x9dd261], dl */
	M8((DWORD)(0x9dd5f9u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 43488d: mov byte ptr [0x9dd5f9], dl */
	M8((DWORD)(0x9dd262u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434893: mov byte ptr [0x9dd262], dl */
	M8((DWORD)(0x9dd5fau)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434899: mov byte ptr [0x9dd5fa], dl */
	M8((DWORD)(0x9dd263u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 43489f: mov byte ptr [0x9dd263], dl */
	M8((DWORD)(0x9dd5fbu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4348a5: mov byte ptr [0x9dd5fb], dl */
	M8((DWORD)(0x9dd264u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4348ab: mov byte ptr [0x9dd264], dl */
	M8((DWORD)(0x9dd5fcu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4348b1: mov byte ptr [0x9dd5fc], dl */
	M8((DWORD)(0x9dd267u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4348b7: mov byte ptr [0x9dd267], dl */
	M8((DWORD)(0x9dd5ffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4348bd: mov byte ptr [0x9dd5ff], dl */
	M8((DWORD)(0x9dd268u)) = (BYTE)(0x2u);	/* 4348c3: mov byte ptr [0x9dd268], 2 */
	M8((DWORD)(0x9dd600u)) = (BYTE)(0x2u);	/* 4348ca: mov byte ptr [0x9dd600], 2 */
	M8((DWORD)(0x9dd269u)) = (BYTE)(0x8u);	/* 4348d1: mov byte ptr [0x9dd269], 8 */
	M8((DWORD)(0x9dd601u)) = (BYTE)(0x8u);	/* 4348d8: mov byte ptr [0x9dd601], 8 */
	M8((DWORD)(0x9dd26au)) = (BYTE)(0xffu);	/* 4348df: mov byte ptr [0x9dd26a], 0xff */
	M8((DWORD)(0x9dd602u)) = (BYTE)(0xffu);	/* 4348e6: mov byte ptr [0x9dd602], 0xff */
	M8((DWORD)(0x9dd266u)) = (BYTE)(0x11u);	/* 4348ed: mov byte ptr [0x9dd266], 0x11 */
	M8((DWORD)(0x9dd5feu)) = (BYTE)(0x11u);	/* 4348f4: mov byte ptr [0x9dd5fe], 0x11 */
	M8((DWORD)(0x9dd265u)) = (BYTE)(0xffu);	/* 4348fb: mov byte ptr [0x9dd265], 0xff */
	M8((DWORD)(0x9dd5fdu)) = (BYTE)(0xffu);	/* 434902: mov byte ptr [0x9dd5fd], 0xff */
L_434909:
	M32((DWORD)(m->eax + 0x9dd26bu)) = m->edx;	/* 434909: mov dword ptr [eax + 0x9dd26b], edx */
	M32((DWORD)(m->eax + 0x9dd603u)) = m->edx;	/* 43490f: mov dword ptr [eax + 0x9dd603], edx */
	M32((DWORD)(m->eax + 0x9dd26fu)) = m->ebx;	/* 434915: mov dword ptr [eax + 0x9dd26f], ebx */
	M32((DWORD)(m->eax + 0x9dd607u)) = m->ebx;	/* 43491b: mov dword ptr [eax + 0x9dd607], ebx */
	M32((DWORD)(m->eax + 0x9dd273u)) = m->ebp;	/* 434921: mov dword ptr [eax + 0x9dd273], ebp */
	M32((DWORD)(m->eax + 0x9dd60bu)) = m->ebp;	/* 434927: mov dword ptr [eax + 0x9dd60b], ebp */
	M32((DWORD)(m->eax + 0x9dd277u)) = m->edx;	/* 43492d: mov dword ptr [eax + 0x9dd277], edx */
	M32((DWORD)(m->eax + 0x9dd60fu)) = m->edx;	/* 434933: mov dword ptr [eax + 0x9dd60f], edx */
	M32((DWORD)(m->eax + 0x9dd27bu)) = m->ebx;	/* 434939: mov dword ptr [eax + 0x9dd27b], ebx */
	M32((DWORD)(m->eax + 0x9dd613u)) = m->ebx;	/* 43493f: mov dword ptr [eax + 0x9dd613], ebx */
	M32((DWORD)(m->eax + 0x9dd27fu)) = m->ebp;	/* 434945: mov dword ptr [eax + 0x9dd27f], ebp */
	M32((DWORD)(m->eax + 0x9dd617u)) = m->ebp;	/* 43494b: mov dword ptr [eax + 0x9dd617], ebp */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 434951: add eax, 0x18 */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434954: cmp eax, 0x90 */
	if (m->sf != m->of) goto L_434909;	/* 434959: jl 0x434909 */
	m->eax = 0x1u;	/* 43495b: mov eax, 1 */
	m->ecx = 0x7u;	/* 434960: mov ecx, 7 */
	M32((DWORD)(0x9dd240u)) = m->eax;	/* 434965: mov dword ptr [0x9dd240], eax */
	M32((DWORD)(0x9dd5d8u)) = m->eax;	/* 43496a: mov dword ptr [0x9dd5d8], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43496f: xor eax, eax */
	m->edi = 0x4de700u;	/* 434971: mov edi, 0x4de700 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 434976: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 434978: stosw word ptr es:[edi], ax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43497a: or ecx, 0xffffffff */
	m->edi = 0x9dd570u;	/* 43497d: mov edi, 0x9dd570 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434982: xor eax, eax */
	M32((DWORD)(0x9dd5dcu)) = m->edx;	/* 434984: mov dword ptr [0x9dd5dc], edx */
	M32((DWORD)(0x9dd5ecu)) = m->edx;	/* 43498a: mov dword ptr [0x9dd5ec], edx */
	M32((DWORD)(0x9dd5f0u)) = m->edx;	/* 434990: mov dword ptr [0x9dd5f0], edx */
	M32((DWORD)(0x9dd5e8u)) = m->edx;	/* 434996: mov dword ptr [0x9dd5e8], edx */
	M32((DWORD)(0x9dd5f4u)) = 0x0u;	/* 43499c: mov dword ptr [0x9dd5f4], 0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4349a6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4349a8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4349aa: sub edi, ecx */
	M32((DWORD)(0x9dd244u)) = m->edx;	/* 4349ac: mov dword ptr [0x9dd244], edx */
	m->eax = m->ecx;	/* 4349b2: mov eax, ecx */
	m->esi = m->edi;	/* 4349b4: mov esi, edi */
	m->edi = 0x4de700u;	/* 4349b6: mov edi, 0x4de700 */
	M32((DWORD)(0x9dd254u)) = m->edx;	/* 4349bb: mov dword ptr [0x9dd254], edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4349c1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4349c4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4349c6: mov ecx, eax */
	m->eax = M32((DWORD)(0xa0b320u));	/* 4349c8: mov eax, dword ptr [0xa0b320] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4349cd: and ecx, 3 */
	M32((DWORD)(0x9dd258u)) = m->edx;	/* 4349d0: mov dword ptr [0x9dd258], edx */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4349d6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd5e4u));	/* 4349d8: mov ecx, dword ptr [0x9dd5e4] */
	m->esi = (DWORD)(m->eax + 0x4u);	/* 4349de: lea esi, [eax + 4] */
	M32((DWORD)(0x4de726u)) = m->ecx;	/* 4349e1: mov dword ptr [0x4de726], ecx */
	m->edi = 0x9dd1d8u;	/* 4349e7: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4349ec: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4349ef: xor eax, eax */
	M32((DWORD)(0x9dd250u)) = m->edx;	/* 4349f1: mov dword ptr [0x9dd250], edx */
	M32((DWORD)(0x9dd25cu)) = 0x0u;	/* 4349f7: mov dword ptr [0x9dd25c], 0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434a01: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434a03: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434a05: sub edi, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 434a07: mov dword ptr [esp + 0x10], esi */
	m->eax = m->ecx;	/* 434a0b: mov eax, ecx */
	m->esi = m->edi;	/* 434a0d: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 434a0f: mov edi, dword ptr [esp + 0x10] */
	M32((DWORD)(0x4de71eu)) = 0x1u;	/* 434a13: mov dword ptr [0x4de71e], 1 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434a1d: shr ecx, 2 */
	M32((DWORD)(0x4de722u)) = m->edx;	/* 434a20: mov dword ptr [0x4de722], edx */
	M32((DWORD)(0x4de72eu)) = m->edx;	/* 434a26: mov dword ptr [0x4de72e], edx */
	M32((DWORD)(0x4de732u)) = m->edx;	/* 434a2c: mov dword ptr [0x4de732], edx */
	M32((DWORD)(0x4de72au)) = m->edx;	/* 434a32: mov dword ptr [0x4de72a], edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434a38: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 434a3a: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434a3c: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434a3e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434a41: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434a43: mov ecx, dword ptr [0xa0b320] */
	m->edi = 0x9dd1f6u;	/* 434a49: mov edi, 0x9dd1f6 */
	m->esi = (DWORD)(m->ecx + 0x22u);	/* 434a4e: lea esi, [ecx + 0x22] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434a51: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434a54: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434a56: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434a58: sub edi, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 434a5a: mov dword ptr [esp + 0x10], esi */
	m->eax = m->ecx;	/* 434a5e: mov eax, ecx */
	m->esi = m->edi;	/* 434a60: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 434a62: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434a66: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434a69: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 434a6b: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434a6d: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434a6f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434a72: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434a74: mov ecx, dword ptr [0xa0b320] */
	m->edi = 0x9dd20eu;	/* 434a7a: mov edi, 0x9dd20e */
	m->esi = (DWORD)(m->ecx + 0x2eu);	/* 434a7f: lea esi, [ecx + 0x2e] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434a82: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 434a85: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 434a87: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 434a89: sub edi, ecx */
	m->eax = m->ecx;	/* 434a8b: mov eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 434a8d: mov dword ptr [esp + 0x10], esi */
	m->esi = m->edi;	/* 434a91: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 434a93: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 434a97: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434a9a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 434a9c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434a9e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 434aa1: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434aa3: mov ecx, dword ptr [0xa0b320] */
	M8((DWORD)(m->ecx + 0x70u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434aa9: mov byte ptr [ecx + 0x70], dl */
	m->eax = M32((DWORD)(0xa0b320u));	/* 434aac: mov eax, dword ptr [0xa0b320] */
	M8((DWORD)(m->eax + 0x71u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434ab1: mov byte ptr [eax + 0x71], dl */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434ab4: mov ecx, dword ptr [0xa0b320] */
	M8((DWORD)(m->ecx + 0x72u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434aba: mov byte ptr [ecx + 0x72], dl */
	m->eax = M32((DWORD)(0xa0b320u));	/* 434abd: mov eax, dword ptr [0xa0b320] */
	M8((DWORD)(m->eax + 0x73u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434ac2: mov byte ptr [eax + 0x73], dl */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434ac5: mov ecx, dword ptr [0xa0b320] */
	M8((DWORD)(m->ecx + 0x74u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434acb: mov byte ptr [ecx + 0x74], dl */
	m->eax = M32((DWORD)(0xa0b320u));	/* 434ace: mov eax, dword ptr [0xa0b320] */
	M8((DWORD)(m->eax + 0x77u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434ad3: mov byte ptr [eax + 0x77], dl */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434ad6: mov ecx, dword ptr [0xa0b320] */
	M8((DWORD)(m->ecx + 0x78u)) = (BYTE)(0x2u);	/* 434adc: mov byte ptr [ecx + 0x78], 2 */
	m->eax = M32((DWORD)(0xa0b320u));	/* 434ae0: mov eax, dword ptr [0xa0b320] */
	M8((DWORD)(m->eax + 0x79u)) = (BYTE)(0x8u);	/* 434ae5: mov byte ptr [eax + 0x79], 8 */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434ae9: mov ecx, dword ptr [0xa0b320] */
	M8((DWORD)(m->ecx + 0x7au)) = (BYTE)(0xffu);	/* 434aef: mov byte ptr [ecx + 0x7a], 0xff */
	m->eax = M32((DWORD)(0xa0b320u));	/* 434af3: mov eax, dword ptr [0xa0b320] */
	M8((DWORD)(m->eax + 0x76u)) = (BYTE)(0x11u);	/* 434af8: mov byte ptr [eax + 0x76], 0x11 */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434afc: mov ecx, dword ptr [0xa0b320] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 434b02: xor eax, eax */
	M8((DWORD)(m->ecx + 0x75u)) = (BYTE)(0xffu);	/* 434b04: mov byte ptr [ecx + 0x75], 0xff */
L_434b08:
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434b08: mov ecx, dword ptr [0xa0b320] */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 434b0e: add eax, 0x18 */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434b11: cmp eax, 0x90 */
	M32((DWORD)(m->eax + m->ecx*1 + 0x63u)) = m->edx;	/* 434b16: mov dword ptr [eax + ecx + 0x63], edx */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434b1a: mov ecx, dword ptr [0xa0b320] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x67u)) = m->ebx;	/* 434b20: mov dword ptr [eax + ecx + 0x67], ebx */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434b24: mov ecx, dword ptr [0xa0b320] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x6bu)) = m->ebp;	/* 434b2a: mov dword ptr [eax + ecx + 0x6b], ebp */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434b2e: mov ecx, dword ptr [0xa0b320] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x6fu)) = m->edx;	/* 434b34: mov dword ptr [eax + ecx + 0x6f], edx */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434b38: mov ecx, dword ptr [0xa0b320] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x73u)) = m->ebx;	/* 434b3e: mov dword ptr [eax + ecx + 0x73], ebx */
	m->ecx = M32((DWORD)(0xa0b320u));	/* 434b42: mov ecx, dword ptr [0xa0b320] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x77u)) = m->ebp;	/* 434b48: mov dword ptr [eax + ecx + 0x77], ebp */
	if (m->sf != m->of) goto L_434b08;	/* 434b4c: jl 0x434b08 */
	m->edx = M32((DWORD)(0x9dd5d8u));	/* 434b4e: mov edx, dword ptr [0x9dd5d8] */
	m->eax = M32((DWORD)(0xa0b320u));	/* 434b54: mov eax, dword ptr [0xa0b320] */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 434b59: push 0x65 */
	M32((DWORD)(0x4dc4b4u)) = m->edx;	/* 434b5b: mov dword ptr [0x4dc4b4], edx */
	{ DWORD v_ = 0xfu; m->esp -= 4; M32(m->esp) = v_; }	/* 434b61: push 0xf */
	M32((DWORD)(m->eax + 0x0u)) = 0x18u;	/* 434b63: mov dword ptr [eax], 0x18 */
	m->esp -= 4; M32(m->esp) = 0x434b6eu; lift_4521c0(m);	/* 434b69: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434b6e: add esp, 8 */
	M32((DWORD)(0x9dd6a4u)) = 0x1u;	/* 434b71: mov dword ptr [0x9dd6a4], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 434b7b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 434b7c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 434b7d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 434b7e: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 434b7f: pop ecx */
	m->esp += 4 + 0; return;	/* 434b80: ret  */
}

/* armc_sendSelectionToNet (0x40e930), lifted by tools/lift.py */
static void lift_40e930(X86 *m)
{
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40e930: xor eax, eax */
L_40e932:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4b8u)));	/* 40e932: fld dword ptr [eax + 0x4dc4b8] */
	MF((DWORD)(m->eax + 0x4dcfe0u)) = (float)ST(0);	/* 40e938: fst dword ptr [eax + 0x4dcfe0] */
	MF((DWORD)(m->eax + 0x9dd603u)) = (float)ST(0); FPOP();	/* 40e93e: fstp dword ptr [eax + 0x9dd603] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4bcu)));	/* 40e944: fld dword ptr [eax + 0x4dc4bc] */
	MF((DWORD)(m->eax + 0x4dcfe4u)) = (float)ST(0);	/* 40e94a: fst dword ptr [eax + 0x4dcfe4] */
	MF((DWORD)(m->eax + 0x9dd607u)) = (float)ST(0); FPOP();	/* 40e950: fstp dword ptr [eax + 0x9dd607] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4c0u)));	/* 40e956: fld dword ptr [eax + 0x4dc4c0] */
	MF((DWORD)(m->eax + 0x4dcfe8u)) = (float)ST(0);	/* 40e95c: fst dword ptr [eax + 0x4dcfe8] */
	MF((DWORD)(m->eax + 0x9dd60bu)) = (float)ST(0); FPOP();	/* 40e962: fstp dword ptr [eax + 0x9dd60b] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4c4u)));	/* 40e968: fld dword ptr [eax + 0x4dc4c4] */
	MF((DWORD)(m->eax + 0x4dcfecu)) = (float)ST(0);	/* 40e96e: fst dword ptr [eax + 0x4dcfec] */
	MF((DWORD)(m->eax + 0x9dd60fu)) = (float)ST(0); FPOP();	/* 40e974: fstp dword ptr [eax + 0x9dd60f] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4c8u)));	/* 40e97a: fld dword ptr [eax + 0x4dc4c8] */
	MF((DWORD)(m->eax + 0x4dcff0u)) = (float)ST(0);	/* 40e980: fst dword ptr [eax + 0x4dcff0] */
	MF((DWORD)(m->eax + 0x9dd613u)) = (float)ST(0); FPOP();	/* 40e986: fstp dword ptr [eax + 0x9dd613] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4dc4ccu)));	/* 40e98c: fld dword ptr [eax + 0x4dc4cc] */
	MF((DWORD)(m->eax + 0x4dcff4u)) = (float)ST(0);	/* 40e992: fst dword ptr [eax + 0x4dcff4] */
	MF((DWORD)(m->eax + 0x9dd617u)) = (float)ST(0); FPOP();	/* 40e998: fstp dword ptr [eax + 0x9dd617] */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40e99e: add eax, 0x18 */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e9a1: cmp eax, 0x90 */
	if (m->sf != m->of) goto L_40e932;	/* 40e9a6: jl 0x40e932 */
	{ DWORD a_ = M32((DWORD)(0x9dd5d8u)), b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e9a8: cmp dword ptr [0x9dd5d8], 0x14 */
	if (m->zf) goto L_40e9b6;	/* 40e9af: je 0x40e9b6 */
	m->esp -= 4; M32(m->esp) = 0x40e9b6u; native_call(m, 0x40d990u);	/* 40e9b1: call 0x40d990 */
L_40e9b6:
	m->ecx = M32((DWORD)(0x4dc764u));	/* 40e9b6: mov ecx, dword ptr [0x4dc764] */
	m->edx = M32((DWORD)(0x4dc768u));	/* 40e9bc: mov edx, dword ptr [0x4dc768] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e9c2: push ebx */
	m->ebx = M32((DWORD)(0x9dd5d8u));	/* 40e9c3: mov ebx, dword ptr [0x9dd5d8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40e9c9: push ebp */
	m->ebp = M32((DWORD)(0x4dc760u));	/* 40e9ca: mov ebp, dword ptr [0x4dc760] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40e9d0: push esi */
	m->esi = M32((DWORD)(0x4dc770u));	/* 40e9d1: mov esi, dword ptr [0x4dc770] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40e9d7: push edi */
	m->edi = M32((DWORD)(0x4dc76cu));	/* 40e9d8: mov edi, dword ptr [0x4dc76c] */
	m->eax = m->ebp;	/* 40e9de: mov eax, ebp */
	{ DWORD a_ = m->ebx, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e9e0: cmp ebx, 0x14 */
	M32((DWORD)(0x4dc878u)) = m->eax;	/* 40e9e3: mov dword ptr [0x4dc878], eax */
	M32((DWORD)(0x4dc87cu)) = m->ecx;	/* 40e9e8: mov dword ptr [0x4dc87c], ecx */
	M32((DWORD)(0x4dc880u)) = m->edx;	/* 40e9ee: mov dword ptr [0x4dc880], edx */
	M32((DWORD)(0x4dc884u)) = m->edi;	/* 40e9f4: mov dword ptr [0x4dc884], edi */
	M32((DWORD)(0x4dc888u)) = m->esi;	/* 40e9fa: mov dword ptr [0x4dc888], esi */
	if (m->zf) goto L_40ea95;	/* 40ea00: je 0x40ea95 */
	{ DWORD a_ = m->ebp, b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea06: cmp ebp, 0x13 */
	goto L_40ea13;	/* 40ea09: jmp 0x40ea13 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 40ea0b: xor ebp, ebp */
	M32((DWORD)(0x4dc760u)) = m->ebp;	/* 40ea0d: mov dword ptr [0x4dc760], ebp */
L_40ea13:
	{ DWORD a_ = m->ecx, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea13: cmp ecx, 0xd */
	goto L_40ea22;	/* 40ea16: jmp 0x40ea22 */
	M32((DWORD)(0x4dc764u)) = 0x0u;	/* 40ea18: mov dword ptr [0x4dc764], 0 */
L_40ea22:
	{ DWORD a_ = M32((DWORD)(0x4dc768u)), b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea22: cmp dword ptr [0x4dc768], 0x11 */
	goto L_40ea35;	/* 40ea29: jmp 0x40ea35 */
	M32((DWORD)(0x4dc768u)) = 0x0u;	/* 40ea2b: mov dword ptr [0x4dc768], 0 */
L_40ea35:
	{ DWORD a_ = M32((DWORD)(0x4dc770u)), b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea35: cmp dword ptr [0x4dc770], 0xf */
	goto L_40ea48;	/* 40ea3c: jmp 0x40ea48 */
	M32((DWORD)(0x4dc770u)) = 0x0u;	/* 40ea3e: mov dword ptr [0x4dc770], 0 */
L_40ea48:
	{ DWORD a_ = M32((DWORD)(0x4dc76cu)), b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea48: cmp dword ptr [0x4dc76c], 0x13 */
	goto L_40ea5b;	/* 40ea4f: jmp 0x40ea5b */
	M32((DWORD)(0x4dc76cu)) = 0x0u;	/* 40ea51: mov dword ptr [0x4dc76c], 0 */
L_40ea5b:
	{ DWORD a_ = m->eax, b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea5b: cmp eax, 0x13 */
	goto L_40ea69;	/* 40ea5e: jmp 0x40ea69 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40ea60: xor eax, eax */
	M32((DWORD)(0x4dc878u)) = m->eax;	/* 40ea62: mov dword ptr [0x4dc878], eax */
	goto L_40ea6b;	/* 40ea67: jmp 0x40ea6b */
L_40ea69:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40ea69: xor eax, eax */
L_40ea6b:
	{ DWORD a_ = m->ecx, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea6b: cmp ecx, 0xd */
	goto L_40ea75;	/* 40ea6e: jmp 0x40ea75 */
	M32((DWORD)(0x4dc87cu)) = m->eax;	/* 40ea70: mov dword ptr [0x4dc87c], eax */
L_40ea75:
	{ DWORD a_ = m->edx, b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea75: cmp edx, 0x11 */
	goto L_40ea7f;	/* 40ea78: jmp 0x40ea7f */
	M32((DWORD)(0x4dc880u)) = m->eax;	/* 40ea7a: mov dword ptr [0x4dc880], eax */
L_40ea7f:
	{ DWORD a_ = m->esi, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea7f: cmp esi, 0xf */
	goto L_40ea89;	/* 40ea82: jmp 0x40ea89 */
	M32((DWORD)(0x4dc888u)) = m->eax;	/* 40ea84: mov dword ptr [0x4dc888], eax */
L_40ea89:
	{ DWORD a_ = m->edi, b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ea89: cmp edi, 0x13 */
	goto L_40ea97;	/* 40ea8c: jmp 0x40ea97 */
	M32((DWORD)(0x4dc884u)) = m->eax;	/* 40ea8e: mov dword ptr [0x4dc884], eax */
	goto L_40ea97;	/* 40ea93: jmp 0x40ea97 */
L_40ea95:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40ea95: xor eax, eax */
L_40ea97:
	m->ecx = M32((DWORD)(0x4dcb20u));	/* 40ea97: mov ecx, dword ptr [0x4dcb20] */
	m->edx = M32((DWORD)(0x4dcb24u));	/* 40ea9d: mov edx, dword ptr [0x4dcb24] */
	M32((DWORD)(0x4dcf20u)) = m->ecx;	/* 40eaa3: mov dword ptr [0x4dcf20], ecx */
	m->ecx = M32((DWORD)(0x4dcb28u));	/* 40eaa9: mov ecx, dword ptr [0x4dcb28] */
	M32((DWORD)(0x4dcf24u)) = m->edx;	/* 40eaaf: mov dword ptr [0x4dcf24], edx */
	m->edx = M32((DWORD)(0x4dcb2cu));	/* 40eab5: mov edx, dword ptr [0x4dcb2c] */
	M32((DWORD)(0x4dcf28u)) = m->ecx;	/* 40eabb: mov dword ptr [0x4dcf28], ecx */
	m->ecx = M32((DWORD)(0x4dcb1cu));	/* 40eac1: mov ecx, dword ptr [0x4dcb1c] */
	M32((DWORD)(0x4dcf2cu)) = m->edx;	/* 40eac7: mov dword ptr [0x4dcf2c], edx */
	m->edx = M32((DWORD)(0x4dcb18u));	/* 40eacd: mov edx, dword ptr [0x4dcb18] */
	M32((DWORD)(0x4dcf1cu)) = m->ecx;	/* 40ead3: mov dword ptr [0x4dcf1c], ecx */
	M32((DWORD)(0x4dcf18u)) = m->edx;	/* 40ead9: mov dword ptr [0x4dcf18], edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40eadf: xor ecx, ecx */
	m->eax = 0x4dcf20u;	/* 40eae1: mov eax, 0x4dcf20 */
L_40eae6:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 40eae6: mov bl, byte ptr [eax] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40eae8: add eax, 4 */
	M8((DWORD)(m->ecx + 0x9dd5ffu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 40eaeb: mov byte ptr [ecx + 0x9dd5ff], bl */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40eaf1: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x4dcf30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eaf2: cmp eax, 0x4dcf30 */
	if (m->sf != m->of) goto L_40eae6;	/* 40eaf7: jl 0x40eae6 */
	m->eax = M32((DWORD)(0x9dd5d8u));	/* 40eaf9: mov eax, dword ptr [0x9dd5d8] */
	M8((DWORD)(0x9dd5fdu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 40eafe: mov byte ptr [0x9dd5fd], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4dcb1cu))) & 0xff) << 0);	/* 40eb04: mov dl, byte ptr [0x4dcb1c] */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb0a: cmp eax, 0x14 */
	M8((DWORD)(0x9dd5feu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 40eb0d: mov byte ptr [0x9dd5fe], dl */
	if (m->zf) goto L_40ebc3;	/* 40eb13: je 0x40ebc3 */
	m->edi = 0x13u;	/* 40eb19: mov edi, 0x13 */
	{ DWORD a_ = m->ebp, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb1e: cmp ebp, edi */
	goto L_40eb2c;	/* 40eb20: jmp 0x40eb2c */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40eb22: xor edx, edx */
	M32((DWORD)(0x4dc760u)) = m->edx;	/* 40eb24: mov dword ptr [0x4dc760], edx */
	goto L_40eb2e;	/* 40eb2a: jmp 0x40eb2e */
L_40eb2c:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40eb2c: xor edx, edx */
L_40eb2e:
	m->ecx = M32((DWORD)(0x4dc764u));	/* 40eb2e: mov ecx, dword ptr [0x4dc764] */
	m->eax = 0xdu;	/* 40eb34: mov eax, 0xd */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb39: cmp ecx, eax */
	goto L_40eb43;	/* 40eb3b: jmp 0x40eb43 */
	M32((DWORD)(0x4dc764u)) = m->edx;	/* 40eb3d: mov dword ptr [0x4dc764], edx */
L_40eb43:
	m->esi = M32((DWORD)(0x4dc768u));	/* 40eb43: mov esi, dword ptr [0x4dc768] */
	m->ecx = 0x11u;	/* 40eb49: mov ecx, 0x11 */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb4e: cmp esi, ecx */
	goto L_40eb58;	/* 40eb50: jmp 0x40eb58 */
	M32((DWORD)(0x4dc768u)) = m->edx;	/* 40eb52: mov dword ptr [0x4dc768], edx */
L_40eb58:
	m->ebx = M32((DWORD)(0x4dc770u));	/* 40eb58: mov ebx, dword ptr [0x4dc770] */
	m->esi = 0xfu;	/* 40eb5e: mov esi, 0xf */
	{ DWORD a_ = m->ebx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb63: cmp ebx, esi */
	goto L_40eb6d;	/* 40eb65: jmp 0x40eb6d */
	M32((DWORD)(0x4dc770u)) = m->edx;	/* 40eb67: mov dword ptr [0x4dc770], edx */
L_40eb6d:
	{ DWORD a_ = M32((DWORD)(0x4dc76cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb6d: cmp dword ptr [0x4dc76c], edi */
	goto L_40eb7b;	/* 40eb73: jmp 0x40eb7b */
	M32((DWORD)(0x4dc76cu)) = m->edx;	/* 40eb75: mov dword ptr [0x4dc76c], edx */
L_40eb7b:
	{ DWORD a_ = M32((DWORD)(0x4dc878u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb7b: cmp dword ptr [0x4dc878], edi */
	goto L_40eb89;	/* 40eb81: jmp 0x40eb89 */
	M32((DWORD)(0x4dc878u)) = m->edx;	/* 40eb83: mov dword ptr [0x4dc878], edx */
L_40eb89:
	{ DWORD a_ = M32((DWORD)(0x4dc87cu)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb89: cmp dword ptr [0x4dc87c], eax */
	goto L_40eb97;	/* 40eb8f: jmp 0x40eb97 */
	M32((DWORD)(0x4dc87cu)) = m->edx;	/* 40eb91: mov dword ptr [0x4dc87c], edx */
L_40eb97:
	{ DWORD a_ = M32((DWORD)(0x4dc880u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eb97: cmp dword ptr [0x4dc880], ecx */
	goto L_40eba5;	/* 40eb9d: jmp 0x40eba5 */
	M32((DWORD)(0x4dc880u)) = m->edx;	/* 40eb9f: mov dword ptr [0x4dc880], edx */
L_40eba5:
	{ DWORD a_ = M32((DWORD)(0x4dc888u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40eba5: cmp dword ptr [0x4dc888], esi */
	goto L_40ebb3;	/* 40ebab: jmp 0x40ebb3 */
	M32((DWORD)(0x4dc888u)) = m->edx;	/* 40ebad: mov dword ptr [0x4dc888], edx */
L_40ebb3:
	{ DWORD a_ = M32((DWORD)(0x4dc884u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ebb3: cmp dword ptr [0x4dc884], edi */
	goto L_40ebc5;	/* 40ebb9: jmp 0x40ebc5 */
	M32((DWORD)(0x4dc884u)) = m->edx;	/* 40ebbb: mov dword ptr [0x4dc884], edx */
	goto L_40ebc5;	/* 40ebc1: jmp 0x40ebc5 */
L_40ebc3:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40ebc3: xor edx, edx */
L_40ebc5:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4dc878u))) & 0xff) << 0);	/* 40ebc5: mov al, byte ptr [0x4dc878] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4dc87cu))) & 0xff) << 0);	/* 40ebca: mov cl, byte ptr [0x4dc87c] */
	M8((DWORD)(0x9dd5f8u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40ebd0: mov byte ptr [0x9dd5f8], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4dc880u))) & 0xff) << 0);	/* 40ebd5: mov al, byte ptr [0x4dc880] */
	M8((DWORD)(0x9dd5f9u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40ebda: mov byte ptr [0x9dd5f9], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4dc884u))) & 0xff) << 0);	/* 40ebe0: mov cl, byte ptr [0x4dc884] */
	M8((DWORD)(0x9dd5fau)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40ebe6: mov byte ptr [0x9dd5fa], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4dc888u))) & 0xff) << 0);	/* 40ebeb: mov al, byte ptr [0x4dc888] */
	M8((DWORD)(0x9dd5fbu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40ebf0: mov byte ptr [0x9dd5fb], cl */
	M8((DWORD)(0x9dd5fcu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40ebf6: mov byte ptr [0x9dd5fc], al */
	m->edi = 0x9dd570u;	/* 40ebfb: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40ec00: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40ec03: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40ec05: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40ec07: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40ec09: sub edi, ecx */
	m->eax = m->ecx;	/* 40ec0b: mov eax, ecx */
	m->esi = m->edi;	/* 40ec0d: mov esi, edi */
	m->edi = M32((DWORD)(0xa0b340u));	/* 40ec0f: mov edi, dword ptr [0xa0b340] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40ec15: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40ec18: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 40ec1a: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40ec1c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 40ec1f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ec21: mov ecx, dword ptr [0xa0b340] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x9dd5f8u))) & 0xff) << 0);	/* 40ec27: mov al, byte ptr [0x9dd5f8] */
	M8((DWORD)(m->ecx + 0x1eu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40ec2c: mov byte ptr [ecx + 0x1e], al */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ec2f: mov ecx, dword ptr [0xa0b340] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x9dd5f9u))) & 0xff) << 0);	/* 40ec35: mov al, byte ptr [0x9dd5f9] */
	M8((DWORD)(m->ecx + 0x1fu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40ec3a: mov byte ptr [ecx + 0x1f], al */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ec3d: mov ecx, dword ptr [0xa0b340] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x9dd5fau))) & 0xff) << 0);	/* 40ec43: mov al, byte ptr [0x9dd5fa] */
	M8((DWORD)(m->ecx + 0x20u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40ec48: mov byte ptr [ecx + 0x20], al */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ec4b: mov ecx, dword ptr [0xa0b340] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x9dd5fbu))) & 0xff) << 0);	/* 40ec51: mov al, byte ptr [0x9dd5fb] */
	M8((DWORD)(m->ecx + 0x21u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40ec56: mov byte ptr [ecx + 0x21], al */
	m->eax = M32((DWORD)(0xa0b340u));	/* 40ec59: mov eax, dword ptr [0xa0b340] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x9dd5fcu))) & 0xff) << 0);	/* 40ec5e: mov cl, byte ptr [0x9dd5fc] */
	M8((DWORD)(m->eax + 0x22u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40ec64: mov byte ptr [eax + 0x22], cl */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40ec67: xor eax, eax */
L_40ec69:
	m->esi = M32((DWORD)(0xa0b340u));	/* 40ec69: mov esi, dword ptr [0xa0b340] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9dd5ffu))) & 0xff) << 0);	/* 40ec6f: mov cl, byte ptr [eax + 0x9dd5ff] */
	M8((DWORD)(m->esi + m->eax*1 + 0x25u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40ec75: mov byte ptr [esi + eax + 0x25], cl */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40ec79: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ec7a: cmp eax, 4 */
	if (m->sf != m->of) goto L_40ec69;	/* 40ec7d: jl 0x40ec69 */
	m->eax = M32((DWORD)(0xa0b340u));	/* 40ec7f: mov eax, dword ptr [0xa0b340] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x9dd5fdu))) & 0xff) << 0);	/* 40ec84: mov cl, byte ptr [0x9dd5fd] */
	m->edi = M32(m->esp); m->esp += 4;	/* 40ec8a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40ec8b: pop esi */
	M8((DWORD)(m->eax + 0x23u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40ec8c: mov byte ptr [eax + 0x23], cl */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ec8f: mov ecx, dword ptr [0xa0b340] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x9dd5feu))) & 0xff) << 0);	/* 40ec95: mov al, byte ptr [0x9dd5fe] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40ec9a: pop ebp */
	M8((DWORD)(m->ecx + 0x24u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40ec9b: mov byte ptr [ecx + 0x24], al */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40ec9e: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40eca0: pop ebx */
L_40eca1:
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40eca1: mov ecx, dword ptr [0xa0b340] */
	m->edx = M32((DWORD)(m->eax + 0x9dd603u));	/* 40eca7: mov edx, dword ptr [eax + 0x9dd603] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x29u)) = m->edx;	/* 40ecad: mov dword ptr [eax + ecx + 0x29], edx */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ecb1: mov ecx, dword ptr [0xa0b340] */
	m->edx = M32((DWORD)(m->eax + 0x9dd607u));	/* 40ecb7: mov edx, dword ptr [eax + 0x9dd607] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x2du)) = m->edx;	/* 40ecbd: mov dword ptr [eax + ecx + 0x2d], edx */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ecc1: mov ecx, dword ptr [0xa0b340] */
	m->edx = M32((DWORD)(m->eax + 0x9dd60bu));	/* 40ecc7: mov edx, dword ptr [eax + 0x9dd60b] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x31u)) = m->edx;	/* 40eccd: mov dword ptr [eax + ecx + 0x31], edx */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ecd1: mov ecx, dword ptr [0xa0b340] */
	m->edx = M32((DWORD)(m->eax + 0x9dd60fu));	/* 40ecd7: mov edx, dword ptr [eax + 0x9dd60f] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x35u)) = m->edx;	/* 40ecdd: mov dword ptr [eax + ecx + 0x35], edx */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ece1: mov ecx, dword ptr [0xa0b340] */
	m->edx = M32((DWORD)(m->eax + 0x9dd613u));	/* 40ece7: mov edx, dword ptr [eax + 0x9dd613] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x39u)) = m->edx;	/* 40eced: mov dword ptr [eax + ecx + 0x39], edx */
	m->ecx = M32((DWORD)(0xa0b340u));	/* 40ecf1: mov ecx, dword ptr [0xa0b340] */
	m->edx = M32((DWORD)(m->eax + 0x9dd617u));	/* 40ecf7: mov edx, dword ptr [eax + 0x9dd617] */
	M32((DWORD)(m->eax + m->ecx*1 + 0x3du)) = m->edx;	/* 40ecfd: mov dword ptr [eax + ecx + 0x3d], edx */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40ed01: add eax, 0x18 */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40ed04: cmp eax, 0x90 */
	if (m->sf != m->of) goto L_40eca1;	/* 40ed09: jl 0x40eca1 */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ed0b: push 0x65 */
	{ DWORD v_ = 0x1bu; m->esp -= 4; M32(m->esp) = v_; }	/* 40ed0d: push 0x1b */
	m->esp -= 4; M32(m->esp) = 0x40ed14u; lift_4521c0(m);	/* 40ed0f: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40ed14: add esp, 8 */
	m->esp += 4 + 0; return;	/* 40ed17: ret  */
}

/* match_4327f0 (0x4327f0), lifted by tools/lift.py */
static void lift_4327f0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4327f0: push ecx */
	m->eax = M32((DWORD)(0x4de72eu));	/* 4327f1: mov eax, dword ptr [0x4de72e] */
	m->ecx = M32((DWORD)(0x4de732u));	/* 4327f6: mov ecx, dword ptr [0x4de732] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4327fc: test eax, eax */
	if (!m->zf) goto L_43280a;	/* 4327fe: jne 0x43280a */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 432800: test ecx, ecx */
	if (!m->zf) goto L_43280a;	/* 432802: jne 0x43280a */
	M32((DWORD)(m->esp + 0x0u)) = m->ecx;	/* 432804: mov dword ptr [esp], ecx */
	goto L_432832;	/* 432808: jmp 0x432832 */
L_43280a:
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43280a: add ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43280c: test ecx, ecx */
	M32((DWORD)(m->esp + 0x0u)) = m->ecx;	/* 43280e: mov dword ptr [esp], ecx */
	if (!m->zf && m->sf == m->of) goto L_43281e;	/* 432812: jg 0x43281e */
	M32((DWORD)(m->esp + 0x0u)) = 0x0u;	/* 432814: mov dword ptr [esp], 0 */
	goto L_432832;	/* 43281c: jmp 0x432832 */
L_43281e:
	FPUSH((long double)(int)M32((DWORD)(0x4de72eu)));	/* 43281e: fild dword ptr [0x4de72e] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 432824: fmul dword ptr [0x4a93f4] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x0u));	/* 43282a: fidiv dword ptr [esp] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43282e: fstp dword ptr [esp] */
L_432832:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x0u)));	/* 432832: fld dword ptr [esp] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 432836: fmul dword ptr [0x4a9420] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x4de722u));	/* 43283c: fimul dword ptr [0x4de722] */
	m->ecx = M32((DWORD)(0x9dd5ecu));	/* 432842: mov ecx, dword ptr [0x9dd5ec] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 432848: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 432849: push edi */
	m->edx = (DWORD)(m->ecx + 0x12cu);	/* 43284a: lea edx, [ecx + 0x12c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 432850: cmp eax, edx */
	MF((DWORD)(0x4de726u)) = (float)ST(0); FPOP();	/* 432852: fstp dword ptr [0x4de726] */
	if (m->zf || m->sf != m->of) goto L_4328c3;	/* 432858: jle 0x4328c3 */
	m->esi = M32((DWORD)(0x9dd5dcu));	/* 43285a: mov esi, dword ptr [0x9dd5dc] */
	m->edx = M32((DWORD)(0x9dd5f0u));	/* 432860: mov edx, dword ptr [0x9dd5f0] */
	M32((DWORD)(0x4de722u)) = m->esi;	/* 432866: mov dword ptr [0x4de722], esi */
	m->esi = M32((DWORD)(0x9dd5e8u));	/* 43286c: mov esi, dword ptr [0x9dd5e8] */
	m->eax = m->ecx;	/* 432872: mov eax, ecx */
	M32((DWORD)(0x4de732u)) = m->edx;	/* 432874: mov dword ptr [0x4de732], edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43287a: test ecx, ecx */
	M32((DWORD)(0x4de72eu)) = m->eax;	/* 43287c: mov dword ptr [0x4de72e], eax */
	M32((DWORD)(0x4de72au)) = m->esi;	/* 432881: mov dword ptr [0x4de72a], esi */
	if (!m->zf) goto L_432893;	/* 432887: jne 0x432893 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 432889: test edx, edx */
	if (!m->zf) goto L_432893;	/* 43288b: jne 0x432893 */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 43288d: mov dword ptr [esp + 8], edx */
	goto L_4328ad;	/* 432891: jmp 0x4328ad */
L_432893:
	FPUSH((long double)(int)M32((DWORD)(0x9dd5ecu)));	/* 432893: fild dword ptr [0x9dd5ec] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 432899: add edx, ecx */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 43289b: mov dword ptr [esp + 8], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 43289f: fmul dword ptr [0x4a93f4] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x8u));	/* 4328a5: fidiv dword ptr [esp + 8] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 4328a9: fstp dword ptr [esp + 8] */
L_4328ad:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 4328ad: fld dword ptr [esp + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4328b1: fmul dword ptr [0x4a9420] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x9dd5dcu));	/* 4328b7: fimul dword ptr [0x9dd5dc] */
	MF((DWORD)(0x4de726u)) = (float)ST(0); FPOP();	/* 4328bd: fstp dword ptr [0x4de726] */
L_4328c3:
	m->ecx = M32((DWORD)(0x9dd254u));	/* 4328c3: mov ecx, dword ptr [0x9dd254] */
	m->edx = (DWORD)(m->ecx + 0x12cu);	/* 4328c9: lea edx, [ecx + 0x12c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4328cf: cmp eax, edx */
	if (m->zf || m->sf != m->of) goto L_432939;	/* 4328d1: jle 0x432939 */
	m->edx = M32((DWORD)(0x9dd244u));	/* 4328d3: mov edx, dword ptr [0x9dd244] */
	m->eax = M32((DWORD)(0x9dd258u));	/* 4328d9: mov eax, dword ptr [0x9dd258] */
	M32((DWORD)(0x4de722u)) = m->edx;	/* 4328de: mov dword ptr [0x4de722], edx */
	m->edx = M32((DWORD)(0x9dd250u));	/* 4328e4: mov edx, dword ptr [0x9dd250] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4328ea: test ecx, ecx */
	M32((DWORD)(0x4de72eu)) = m->ecx;	/* 4328ec: mov dword ptr [0x4de72e], ecx */
	M32((DWORD)(0x4de732u)) = m->eax;	/* 4328f2: mov dword ptr [0x4de732], eax */
	M32((DWORD)(0x4de72au)) = m->edx;	/* 4328f7: mov dword ptr [0x4de72a], edx */
	if (!m->zf) goto L_432909;	/* 4328fd: jne 0x432909 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4328ff: test eax, eax */
	if (!m->zf) goto L_432909;	/* 432901: jne 0x432909 */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 432903: mov dword ptr [esp + 8], eax */
	goto L_432923;	/* 432907: jmp 0x432923 */
L_432909:
	FPUSH((long double)(int)M32((DWORD)(0x9dd254u)));	/* 432909: fild dword ptr [0x9dd254] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43290f: add eax, ecx */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 432911: mov dword ptr [esp + 8], eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 432915: fmul dword ptr [0x4a93f4] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x8u));	/* 43291b: fidiv dword ptr [esp + 8] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 43291f: fstp dword ptr [esp + 8] */
L_432923:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 432923: fld dword ptr [esp + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 432927: fmul dword ptr [0x4a9420] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x9dd244u));	/* 43292d: fimul dword ptr [0x9dd244] */
	MF((DWORD)(0x4de726u)) = (float)ST(0); FPOP();	/* 432933: fstp dword ptr [0x4de726] */
L_432939:
	m->edi = 0x4de700u;	/* 432939: mov edi, 0x4de700 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43293e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 432941: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 432943: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 432945: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 432947: sub edi, ecx */
	m->eax = m->ecx;	/* 432949: mov eax, ecx */
	m->esi = m->edi;	/* 43294b: mov esi, edi */
	m->edi = M32((DWORD)(0xa0b338u));	/* 43294d: mov edi, dword ptr [0xa0b338] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 432953: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 432956: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 432958: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43295a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43295d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b338u));	/* 43295f: mov ecx, dword ptr [0xa0b338] */
	m->edx = M32((DWORD)(0x4de72au));	/* 432965: mov edx, dword ptr [0x4de72a] */
	M32((DWORD)(m->ecx + 0x1eu)) = m->edx;	/* 43296b: mov dword ptr [ecx + 0x1e], edx */
	m->eax = M32((DWORD)(0xa0b338u));	/* 43296e: mov eax, dword ptr [0xa0b338] */
	m->ecx = M32((DWORD)(0x4de72eu));	/* 432973: mov ecx, dword ptr [0x4de72e] */
	M32((DWORD)(m->eax + 0x22u)) = m->ecx;	/* 432979: mov dword ptr [eax + 0x22], ecx */
	m->edx = M32((DWORD)(0xa0b338u));	/* 43297c: mov edx, dword ptr [0xa0b338] */
	m->eax = M32((DWORD)(0x4de732u));	/* 432982: mov eax, dword ptr [0x4de732] */
	M32((DWORD)(m->edx + 0x26u)) = m->eax;	/* 432987: mov dword ptr [edx + 0x26], eax */
	m->ecx = M32((DWORD)(0xa0b338u));	/* 43298a: mov ecx, dword ptr [0xa0b338] */
	m->edx = M32((DWORD)(0x4de722u));	/* 432990: mov edx, dword ptr [0x4de722] */
	M32((DWORD)(m->ecx + 0x2au)) = m->edx;	/* 432996: mov dword ptr [ecx + 0x2a], edx */
	m->eax = M32((DWORD)(0xa0b338u));	/* 432999: mov eax, dword ptr [0xa0b338] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de726u)));	/* 43299e: fld dword ptr [0x4de726] */
	MF((DWORD)(m->eax + 0x32u)) = (float)ST(0); FPOP();	/* 4329a4: fstp dword ptr [eax + 0x32] */
	m->ecx = M32((DWORD)(0x4de722u));	/* 4329a7: mov ecx, dword ptr [0x4de722] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4329ad: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4329b3u; native_call(m, 0x4326f0u);	/* 4329ae: call 0x4326f0 */
	m->edx = M32((DWORD)(0xa0b338u));	/* 4329b3: mov edx, dword ptr [0xa0b338] */
	M32((DWORD)(m->edx + 0x2eu)) = m->eax;	/* 4329b9: mov dword ptr [edx + 0x2e], eax */
	m->eax = M32((DWORD)(0x4de72au));	/* 4329bc: mov eax, dword ptr [0x4de72a] */
	m->ecx = M32((DWORD)(0x4de72eu));	/* 4329c1: mov ecx, dword ptr [0x4de72e] */
	m->edx = M32((DWORD)(0x4de732u));	/* 4329c7: mov edx, dword ptr [0x4de732] */
	M32((DWORD)(0x9dd5e8u)) = m->eax;	/* 4329cd: mov dword ptr [0x9dd5e8], eax */
	m->eax = M32((DWORD)(0x4de722u));	/* 4329d2: mov eax, dword ptr [0x4de722] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4329d7: push eax */
	M32((DWORD)(0x9dd5ecu)) = m->ecx;	/* 4329d8: mov dword ptr [0x9dd5ec], ecx */
	M32((DWORD)(0x9dd5f0u)) = m->edx;	/* 4329de: mov dword ptr [0x9dd5f0], edx */
	M32((DWORD)(0x9dd5dcu)) = m->eax;	/* 4329e4: mov dword ptr [0x9dd5dc], eax */
	m->esp -= 4; M32(m->esp) = 0x4329eeu; native_call(m, 0x4326f0u);	/* 4329e9: call 0x4326f0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4329ee: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(0x4de726u));	/* 4329f2: mov edx, dword ptr [0x4de726] */
	m->eax = (DWORD)(int)(signed char)(((m->eax >> 0) & 0xff));	/* 4329f8: movsx eax, al */
	M32((DWORD)(0x9dd5d8u)) = m->eax;	/* 4329fb: mov dword ptr [0x9dd5d8], eax */
	m->eax = M32((DWORD)(0x4de72au));	/* 432a00: mov eax, dword ptr [0x4de72a] */
	M32((DWORD)(0x9dd250u)) = m->eax;	/* 432a05: mov dword ptr [0x9dd250], eax */
	m->eax = M32((DWORD)(0x4de722u));	/* 432a0a: mov eax, dword ptr [0x4de722] */
	M32((DWORD)(0x9dd5f4u)) = m->ecx;	/* 432a0f: mov dword ptr [0x9dd5f4], ecx */
	m->ecx = M32((DWORD)(0x4de72eu));	/* 432a15: mov ecx, dword ptr [0x4de72e] */
	M32((DWORD)(0x9dd5e4u)) = m->edx;	/* 432a1b: mov dword ptr [0x9dd5e4], edx */
	m->edx = M32((DWORD)(0x4de732u));	/* 432a21: mov edx, dword ptr [0x4de732] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 432a27: push eax */
	M32((DWORD)(0x9dd254u)) = m->ecx;	/* 432a28: mov dword ptr [0x9dd254], ecx */
	M32((DWORD)(0x9dd258u)) = m->edx;	/* 432a2e: mov dword ptr [0x9dd258], edx */
	M32((DWORD)(0x9dd244u)) = m->eax;	/* 432a34: mov dword ptr [0x9dd244], eax */
	m->esp -= 4; M32(m->esp) = 0x432a3eu; native_call(m, 0x4326f0u);	/* 432a39: call 0x4326f0 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 432a3e: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(0x4de726u));	/* 432a42: mov edx, dword ptr [0x4de726] */
	m->eax = (DWORD)(int)(signed char)(((m->eax >> 0) & 0xff));	/* 432a48: movsx eax, al */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 432a4b: push 0x65 */
	{ DWORD v_ = 0x11u; m->esp -= 4; M32(m->esp) = v_; }	/* 432a4d: push 0x11 */
	M32((DWORD)(0x9dd240u)) = m->eax;	/* 432a4f: mov dword ptr [0x9dd240], eax */
	M32((DWORD)(0x9dd25cu)) = m->ecx;	/* 432a54: mov dword ptr [0x9dd25c], ecx */
	M32((DWORD)(0x9dd24cu)) = m->edx;	/* 432a5a: mov dword ptr [0x9dd24c], edx */
	m->esp -= 4; M32(m->esp) = 0x432a65u; lift_4521c0(m);	/* 432a60: call 0x4521c0 */
	m->eax = M32((DWORD)(0x4de72eu));	/* 432a65: mov eax, dword ptr [0x4de72e] */
	m->edx = M32((DWORD)(0x4de722u));	/* 432a6a: mov edx, dword ptr [0x4de722] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 432a70: add esp, 0x14 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 432a73: lea ecx, [eax + eax*2] */
	m->edi = M32(m->esp); m->esp += 4;	/* 432a76: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 432a77: pop esi */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 432a78: lea ecx, [ecx + ecx*4] */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 432a7b: lea ecx, [ecx + ecx*4] */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 432a7e: shl ecx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 432a80: cmp ecx, edx */
	if (m->sf == m->of) goto L_432bdd;	/* 432a82: jge 0x432bdd */
	m->ecx = M32((DWORD)(0x4de732u));	/* 432a88: mov ecx, dword ptr [0x4de732] */
	m->edx = (DWORD)(m->eax + m->eax*1 + 0x0u);	/* 432a8e: lea edx, [eax + eax] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 432a91: test eax, eax */
	M32((DWORD)(0x4de722u)) = m->edx;	/* 432a93: mov dword ptr [0x4de722], edx */
	if (!m->zf) goto L_432aa5;	/* 432a99: jne 0x432aa5 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 432a9b: test ecx, ecx */
	if (!m->zf) goto L_432aa5;	/* 432a9d: jne 0x432aa5 */
	M32((DWORD)(m->esp + 0x0u)) = m->ecx;	/* 432a9f: mov dword ptr [esp], ecx */
	goto L_432abf;	/* 432aa3: jmp 0x432abf */
L_432aa5:
	FPUSH((long double)(int)M32((DWORD)(0x4de72eu)));	/* 432aa5: fild dword ptr [0x4de72e] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 432aab: add ecx, eax */
	M32((DWORD)(m->esp + 0x0u)) = m->ecx;	/* 432aad: mov dword ptr [esp], ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 432ab1: fmul dword ptr [0x4a93f4] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x0u));	/* 432ab7: fidiv dword ptr [esp] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 432abb: fstp dword ptr [esp] */
L_432abf:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x0u)));	/* 432abf: fld dword ptr [esp] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 432ac3: fmul dword ptr [0x4a9420] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(0x4de722u));	/* 432ac9: fimul dword ptr [0x4de722] */
	m->eax = M32((DWORD)(0xa0b338u));	/* 432acf: mov eax, dword ptr [0xa0b338] */
	m->ecx = M32((DWORD)(0x4de72au));	/* 432ad4: mov ecx, dword ptr [0x4de72a] */
	MF((DWORD)(0x4de726u)) = (float)ST(0); FPOP();	/* 432ada: fstp dword ptr [0x4de726] */
	M32((DWORD)(m->eax + 0x1eu)) = m->ecx;	/* 432ae0: mov dword ptr [eax + 0x1e], ecx */
	m->edx = M32((DWORD)(0xa0b338u));	/* 432ae3: mov edx, dword ptr [0xa0b338] */
	m->eax = M32((DWORD)(0x4de72eu));	/* 432ae9: mov eax, dword ptr [0x4de72e] */
	M32((DWORD)(m->edx + 0x22u)) = m->eax;	/* 432aee: mov dword ptr [edx + 0x22], eax */
	m->ecx = M32((DWORD)(0xa0b338u));	/* 432af1: mov ecx, dword ptr [0xa0b338] */
	m->edx = M32((DWORD)(0x4de732u));	/* 432af7: mov edx, dword ptr [0x4de732] */
	M32((DWORD)(m->ecx + 0x26u)) = m->edx;	/* 432afd: mov dword ptr [ecx + 0x26], edx */
	m->eax = M32((DWORD)(0xa0b338u));	/* 432b00: mov eax, dword ptr [0xa0b338] */
	m->ecx = M32((DWORD)(0x4de722u));	/* 432b05: mov ecx, dword ptr [0x4de722] */
	M32((DWORD)(m->eax + 0x2au)) = m->ecx;	/* 432b0b: mov dword ptr [eax + 0x2a], ecx */
	m->edx = M32((DWORD)(0xa0b338u));	/* 432b0e: mov edx, dword ptr [0xa0b338] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de726u)));	/* 432b14: fld dword ptr [0x4de726] */
	MF((DWORD)(m->edx + 0x32u)) = (float)ST(0); FPOP();	/* 432b1a: fstp dword ptr [edx + 0x32] */
	m->eax = M32((DWORD)(0x4de722u));	/* 432b1d: mov eax, dword ptr [0x4de722] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 432b22: push eax */
	m->esp -= 4; M32(m->esp) = 0x432b28u; native_call(m, 0x4326f0u);	/* 432b23: call 0x4326f0 */
	m->ecx = M32((DWORD)(0xa0b338u));	/* 432b28: mov ecx, dword ptr [0xa0b338] */
	M32((DWORD)(m->ecx + 0x2eu)) = m->eax;	/* 432b2e: mov dword ptr [ecx + 0x2e], eax */
	m->eax = M32((DWORD)(0x4de72eu));	/* 432b31: mov eax, dword ptr [0x4de72e] */
	m->edx = M32((DWORD)(0x4de72au));	/* 432b36: mov edx, dword ptr [0x4de72a] */
	m->ecx = M32((DWORD)(0x4de732u));	/* 432b3c: mov ecx, dword ptr [0x4de732] */
	M32((DWORD)(0x9dd5ecu)) = m->eax;	/* 432b42: mov dword ptr [0x9dd5ec], eax */
	m->eax = M32((DWORD)(0x4de722u));	/* 432b47: mov eax, dword ptr [0x4de722] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 432b4c: push eax */
	M32((DWORD)(0x9dd5e8u)) = m->edx;	/* 432b4d: mov dword ptr [0x9dd5e8], edx */
	M32((DWORD)(0x9dd5f0u)) = m->ecx;	/* 432b53: mov dword ptr [0x9dd5f0], ecx */
	M32((DWORD)(0x9dd5dcu)) = m->eax;	/* 432b59: mov dword ptr [0x9dd5dc], eax */
	m->esp -= 4; M32(m->esp) = 0x432b63u; native_call(m, 0x4326f0u);	/* 432b5e: call 0x4326f0 */
	m->ecx = M32((DWORD)(0x4de726u));	/* 432b63: mov ecx, dword ptr [0x4de726] */
	m->edx = (DWORD)(int)(signed char)(((m->eax >> 0) & 0xff));	/* 432b69: movsx edx, al */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 432b6c: mov eax, dword ptr [esp + 8] */
	M32((DWORD)(0x9dd5d8u)) = m->edx;	/* 432b70: mov dword ptr [0x9dd5d8], edx */
	m->edx = M32((DWORD)(0x4de72au));	/* 432b76: mov edx, dword ptr [0x4de72a] */
	M32((DWORD)(0x9dd5f4u)) = m->eax;	/* 432b7c: mov dword ptr [0x9dd5f4], eax */
	m->eax = M32((DWORD)(0x4de72eu));	/* 432b81: mov eax, dword ptr [0x4de72e] */
	M32((DWORD)(0x9dd5e4u)) = m->ecx;	/* 432b86: mov dword ptr [0x9dd5e4], ecx */
	m->ecx = M32((DWORD)(0x4de732u));	/* 432b8c: mov ecx, dword ptr [0x4de732] */
	M32((DWORD)(0x9dd254u)) = m->eax;	/* 432b92: mov dword ptr [0x9dd254], eax */
	m->eax = M32((DWORD)(0x4de722u));	/* 432b97: mov eax, dword ptr [0x4de722] */
	M32((DWORD)(0x9dd250u)) = m->edx;	/* 432b9c: mov dword ptr [0x9dd250], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 432ba2: push eax */
	M32((DWORD)(0x9dd258u)) = m->ecx;	/* 432ba3: mov dword ptr [0x9dd258], ecx */
	M32((DWORD)(0x9dd244u)) = m->eax;	/* 432ba9: mov dword ptr [0x9dd244], eax */
	m->esp -= 4; M32(m->esp) = 0x432bb3u; native_call(m, 0x4326f0u);	/* 432bae: call 0x4326f0 */
	m->ecx = M32((DWORD)(0x4de726u));	/* 432bb3: mov ecx, dword ptr [0x4de726] */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 432bb9: push 0x65 */
	m->edx = (DWORD)(int)(signed char)(((m->eax >> 0) & 0xff));	/* 432bbb: movsx edx, al */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 432bbe: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x11u; m->esp -= 4; M32(m->esp) = v_; }	/* 432bc2: push 0x11 */
	M32((DWORD)(0x9dd240u)) = m->edx;	/* 432bc4: mov dword ptr [0x9dd240], edx */
	M32((DWORD)(0x9dd25cu)) = m->eax;	/* 432bca: mov dword ptr [0x9dd25c], eax */
	M32((DWORD)(0x9dd24cu)) = m->ecx;	/* 432bcf: mov dword ptr [0x9dd24c], ecx */
	m->esp -= 4; M32(m->esp) = 0x432bdau; lift_4521c0(m);	/* 432bd5: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 432bda: add esp, 0x14 */
L_432bdd:
	m->ecx = M32(m->esp); m->esp += 4;	/* 432bdd: pop ecx */
	m->esp += 4 + 0; return;	/* 432bde: ret  */
}

/* match_44aee0 (0x44aee0), lifted by tools/lift.py */
static void lift_44aee0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44aee0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44aee1: push edi */
	m->edi = 0x9dd570u;	/* 44aee2: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44aee7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44aeea: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44aeec: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44aeee: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44aef0: sub edi, ecx */
	m->eax = m->ecx;	/* 44aef2: mov eax, ecx */
	m->esi = m->edi;	/* 44aef4: mov esi, edi */
	m->edi = 0x4de700u;	/* 44aef6: mov edi, 0x4de700 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44aefb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44aefe: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44af00: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44af02: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44af04: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44af07: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4de700u;	/* 44af09: mov edi, 0x4de700 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44af0e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44af11: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44af13: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44af15: dec ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 44af16: pop edi */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44af17: cmp ecx, 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44af1a: pop esi */
	if (m->cf) goto L_44af22;	/* 44af1b: jb 0x44af22 */
	lift_4327f0(m); return;	/* 44af1d: jmp 0x4327f0 */
L_44af22:
	m->esp += 4 + 0; return;	/* 44af22: ret  */
}

/* net_closeAll (0x451600), lifted by tools/lift.py */
static void lift_451600(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x451605u; native_call(m, 0x454690u);	/* 451600: call 0x454690 */
	m->eax = M32((DWORD)(0xa055f8u));	/* 451605: mov eax, dword ptr [0xa055f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45160a: test eax, eax */
	if (m->zf) goto L_45163b;	/* 45160c: je 0x45163b */
	m->esp -= 4; M32(m->esp) = 0x451613u; native_call(m, 0x4a8292u);	/* 45160e: call 0x4a8292 */
	m->eax = M32((DWORD)(0xa055f8u));	/* 451613: mov eax, dword ptr [0xa055f8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 451618: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45161a: push eax */
	m->esp -= 4; M32(m->esp) = 0x451620u; native_call(m, 0x4a828cu);	/* 45161b: call 0x4a828c */
	m->ecx = M32((DWORD)(0xa055f8u));	/* 451620: mov ecx, dword ptr [0xa055f8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451626: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45162cu; native_call(m, 0x4a8286u);	/* 451627: call 0x4a8286 */
	M32((DWORD)(0xa055f8u)) = 0x0u;	/* 45162c: mov dword ptr [0xa055f8], 0 */
	m->esp -= 4; M32(m->esp) = 0x45163bu; native_call(m, 0x4519b0u);	/* 451636: call 0x4519b0 */
L_45163b:
	m->eax = M32((DWORD)(0xa05630u));	/* 45163b: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 451640: test eax, eax */
	if (m->zf) goto L_451671;	/* 451642: je 0x451671 */
	m->esp -= 4; M32(m->esp) = 0x451649u; native_call(m, 0x4a8292u);	/* 451644: call 0x4a8292 */
	m->edx = M32((DWORD)(0xa05630u));	/* 451649: mov edx, dword ptr [0xa05630] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45164f: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451651: push edx */
	m->esp -= 4; M32(m->esp) = 0x451657u; native_call(m, 0x4a828cu);	/* 451652: call 0x4a828c */
	m->eax = M32((DWORD)(0xa05630u));	/* 451657: mov eax, dword ptr [0xa05630] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45165c: push eax */
	m->esp -= 4; M32(m->esp) = 0x451662u; native_call(m, 0x4a8286u);	/* 45165d: call 0x4a8286 */
	M32((DWORD)(0xa05630u)) = 0x0u;	/* 451662: mov dword ptr [0xa05630], 0 */
	m->esp -= 4; M32(m->esp) = 0x451671u; native_call(m, 0x4519b0u);	/* 45166c: call 0x4519b0 */
L_451671:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 451671: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451675: push esi */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 451676: sub eax, 0x64 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 451679: push edi */
	if (m->zf) goto L_4516f3;	/* 45167a: je 0x4516f3 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 45167c: dec eax */
	if (!m->zf) goto L_451759;	/* 45167d: jne 0x451759 */
	{ DWORD v_ = 0xa055fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 451683: push 0xa055fc */
	m->esp -= 4; M32(m->esp) = 0x45168du; native_call(m, 0x4547d0u);	/* 451688: call 0x4547d0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45168d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 451690: test eax, eax */
	if (m->zf) goto L_4516c5;	/* 451692: je 0x4516c5 */
	m->edi = 0xa0d320u;	/* 451694: mov edi, 0xa0d320 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451699: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45169c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 45169e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4516a0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4516a2: sub edi, ecx */
	m->edx = m->ecx;	/* 4516a4: mov edx, ecx */
	m->esi = m->edi;	/* 4516a6: mov esi, edi */
	m->edi = 0xa055e4u;	/* 4516a8: mov edi, 0xa055e4 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4516ad: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4516b0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4516b2: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4516b4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4516b7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(0xa05634u))) & 0xffff);	/* 4516b9: mov cx, word ptr [0xa05634] */
	goto L_451752;	/* 4516c0: jmp 0x451752 */
L_4516c5:
	m->edi = 0xa055fcu;	/* 4516c5: mov edi, 0xa055fc */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4516ca: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4516cd: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4516cf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4516d1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4516d3: sub edi, ecx */
	m->eax = m->ecx;	/* 4516d5: mov eax, ecx */
	m->esi = m->edi;	/* 4516d7: mov esi, edi */
	m->edi = 0xa055e4u;	/* 4516d9: mov edi, 0xa055e4 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4516de: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4516e1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4516e3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4516e5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4516e8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(0xa05634u))) & 0xffff);	/* 4516ea: mov cx, word ptr [0xa05634] */
	goto L_451752;	/* 4516f1: jmp 0x451752 */
L_4516f3:
	{ DWORD v_ = 0xa0b24cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4516f3: push 0xa0b24c */
	m->esp -= 4; M32(m->esp) = 0x4516fdu; native_call(m, 0x4547d0u);	/* 4516f8: call 0x4547d0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4516fd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 451700: test eax, eax */
	if (m->zf) goto L_451726;	/* 451702: je 0x451726 */
	m->edi = 0xa0d320u;	/* 451704: mov edi, 0xa0d320 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451709: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45170c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 45170e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 451710: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 451712: sub edi, ecx */
	m->edx = m->ecx;	/* 451714: mov edx, ecx */
	m->esi = m->edi;	/* 451716: mov esi, edi */
	m->edi = 0xa055e4u;	/* 451718: mov edi, 0xa055e4 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45171d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 451720: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 451722: mov ecx, edx */
	goto L_451746;	/* 451724: jmp 0x451746 */
L_451726:
	m->edi = 0xa0b24cu;	/* 451726: mov edi, 0xa0b24c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45172b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45172e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 451730: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 451732: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 451734: sub edi, ecx */
	m->eax = m->ecx;	/* 451736: mov eax, ecx */
	m->esi = m->edi;	/* 451738: mov esi, edi */
	m->edi = 0xa055e4u;	/* 45173a: mov edi, 0xa055e4 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45173f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 451742: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 451744: mov ecx, eax */
L_451746:
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451746: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 451749: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(0xa055f4u))) & 0xffff);	/* 45174b: mov cx, word ptr [0xa055f4] */
L_451752:
	M16((DWORD)(0xa05326u)) = (WORD)((m->ecx & 0xffff));	/* 451752: mov word ptr [0xa05326], cx */
L_451759:
	m->ecx = 0x1e40u;	/* 451759: mov ecx, 0x1e40 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45175e: xor eax, eax */
	m->edi = 0x9fd960u;	/* 451760: mov edi, 0x9fd960 */
	{ DWORD v_ = 0x5bu; m->esp -= 4; M32(m->esp) = v_; }	/* 451765: push 0x5b */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451767: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x16c0u;	/* 451769: mov ecx, 0x16c0 */
	m->edi = 0xa05748u;	/* 45176e: mov edi, 0xa05748 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451773: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0xaau;	/* 451775: mov ecx, 0xaa */
	m->edi = 0xa05330u;	/* 45177a: mov edi, 0xa05330 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 45177f: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 451781: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x451788u; native_call(m, 0x49eeb0u);	/* 451783: call 0x49eeb0 */
	m->edi = m->eax;	/* 451788: mov edi, eax */
	m->ecx = 0x16u;	/* 45178a: mov ecx, 0x16 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45178f: xor eax, eax */
	M32((DWORD)(0xa0b310u)) = m->edi;	/* 451791: mov dword ptr [0xa0b310], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451797: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 451799: stosw word ptr es:[edi], ax */
	{ DWORD v_ = 0x5bu; m->esp -= 4; M32(m->esp) = v_; }	/* 45179b: push 0x5b */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 45179d: stosb byte ptr es:[edi], al */
	m->esp -= 4; M32(m->esp) = 0x4517a3u; native_call(m, 0x49eeb0u);	/* 45179e: call 0x49eeb0 */
	m->edi = m->eax;	/* 4517a3: mov edi, eax */
	m->ecx = 0x16u;	/* 4517a5: mov ecx, 0x16 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4517aa: xor eax, eax */
	M32((DWORD)(0xa0b314u)) = m->edi;	/* 4517ac: mov dword ptr [0xa0b314], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4517b2: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4517b4: stosw word ptr es:[edi], ax */
	{ DWORD v_ = 0x5bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4517b6: push 0x5b */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 4517b8: stosb byte ptr es:[edi], al */
	m->esp -= 4; M32(m->esp) = 0x4517beu; native_call(m, 0x49eeb0u);	/* 4517b9: call 0x49eeb0 */
	m->edi = m->eax;	/* 4517be: mov edi, eax */
	m->ecx = 0x16u;	/* 4517c0: mov ecx, 0x16 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4517c5: xor eax, eax */
	M32((DWORD)(0xa0b318u)) = m->edi;	/* 4517c7: mov dword ptr [0xa0b318], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4517cd: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4517cf: stosw word ptr es:[edi], ax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4517d1: push 4 */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 4517d3: stosb byte ptr es:[edi], al */
	m->esp -= 4; M32(m->esp) = 0x4517d9u; native_call(m, 0x49eeb0u);	/* 4517d4: call 0x49eeb0 */
	M32((DWORD)(0xa0b31cu)) = m->eax;	/* 4517d9: mov dword ptr [0xa0b31c], eax */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4517de: push 0x10 */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 4517e0: mov dword ptr [eax], 0 */
	m->esp -= 4; M32(m->esp) = 0x4517ebu; native_call(m, 0x49eeb0u);	/* 4517e6: call 0x49eeb0 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4517eb: xor edx, edx */
	M32((DWORD)(0xa0b304u)) = m->eax;	/* 4517ed: mov dword ptr [0xa0b304], eax */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 4517f2: mov dword ptr [eax], edx */
	{ DWORD v_ = 0x10bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4517f4: push 0x10b */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4517f9: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 4517fc: mov dword ptr [eax + 8], edx */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 4517ff: mov dword ptr [eax + 0xc], edx */
	m->esp -= 4; M32(m->esp) = 0x451807u; native_call(m, 0x49eeb0u);	/* 451802: call 0x49eeb0 */
	m->edi = m->eax;	/* 451807: mov edi, eax */
	m->ecx = 0x42u;	/* 451809: mov ecx, 0x42 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45180e: xor eax, eax */
	M32((DWORD)(0xa0b320u)) = m->edi;	/* 451810: mov dword ptr [0xa0b320], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451816: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 451818: stosw word ptr es:[edi], ax */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45181a: push 8 */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 45181c: stosb byte ptr es:[edi], al */
	m->esp -= 4; M32(m->esp) = 0x451822u; native_call(m, 0x49eeb0u);	/* 45181d: call 0x49eeb0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451822: xor ecx, ecx */
	M32((DWORD)(0xa0b324u)) = m->eax;	/* 451824: mov dword ptr [0xa0b324], eax */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 451829: mov dword ptr [eax], ecx */
	{ DWORD v_ = 0x79u; m->esp -= 4; M32(m->esp) = v_; }	/* 45182b: push 0x79 */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 45182d: mov dword ptr [eax + 4], ecx */
	m->esp -= 4; M32(m->esp) = 0x451835u; native_call(m, 0x49eeb0u);	/* 451830: call 0x49eeb0 */
	m->edi = m->eax;	/* 451835: mov edi, eax */
	m->ecx = 0x1eu;	/* 451837: mov ecx, 0x1e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45183c: xor eax, eax */
	M32((DWORD)(0xa0b328u)) = m->edi;	/* 45183e: mov dword ptr [0xa0b328], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451844: rep stosd dword ptr es:[edi], eax */
	{ DWORD v_ = 0x79u; m->esp -= 4; M32(m->esp) = v_; }	/* 451846: push 0x79 */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 451848: stosb byte ptr es:[edi], al */
	m->esp -= 4; M32(m->esp) = 0x45184eu; native_call(m, 0x49eeb0u);	/* 451849: call 0x49eeb0 */
	m->edi = m->eax;	/* 45184e: mov edi, eax */
	m->ecx = 0x1eu;	/* 451850: mov ecx, 0x1e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451855: xor eax, eax */
	M32((DWORD)(0xa0b32cu)) = m->edi;	/* 451857: mov dword ptr [0xa0b32c], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 45185d: rep stosd dword ptr es:[edi], eax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 45185f: stosb byte ptr es:[edi], al */
	{ DWORD v_ = 0x79u; m->esp -= 4; M32(m->esp) = v_; }	/* 451860: push 0x79 */
	m->esp -= 4; M32(m->esp) = 0x451867u; native_call(m, 0x49eeb0u);	/* 451862: call 0x49eeb0 */
	m->edi = m->eax;	/* 451867: mov edi, eax */
	m->ecx = 0x1eu;	/* 451869: mov ecx, 0x1e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45186e: xor eax, eax */
	M32((DWORD)(0xa0b330u)) = m->edi;	/* 451870: mov dword ptr [0xa0b330], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451876: rep stosd dword ptr es:[edi], eax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 451878: push 4 */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 45187a: stosb byte ptr es:[edi], al */
	m->esp -= 4; M32(m->esp) = 0x451880u; native_call(m, 0x49eeb0u);	/* 45187b: call 0x49eeb0 */
	M32((DWORD)(0xa0b334u)) = m->eax;	/* 451880: mov dword ptr [0xa0b334], eax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 451885: push 4 */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 451887: mov dword ptr [eax], 0 */
	m->esp -= 4; M32(m->esp) = 0x451892u; native_call(m, 0x49eeb0u);	/* 45188d: call 0x49eeb0 */
	M32((DWORD)(0xa0b30cu)) = m->eax;	/* 451892: mov dword ptr [0xa0b30c], eax */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 451897: push 0x10 */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 451899: mov dword ptr [eax], 0 */
	m->esp -= 4; M32(m->esp) = 0x4518a4u; native_call(m, 0x49eeb0u);	/* 45189f: call 0x49eeb0 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4518a4: xor edx, edx */
	M32((DWORD)(0xa0b308u)) = m->eax;	/* 4518a6: mov dword ptr [0xa0b308], eax */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 4518ab: mov dword ptr [eax], edx */
	{ DWORD v_ = 0xb9u; m->esp -= 4; M32(m->esp) = v_; }	/* 4518ad: push 0xb9 */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4518b2: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 4518b5: mov dword ptr [eax + 8], edx */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 4518b8: mov dword ptr [eax + 0xc], edx */
	m->esp -= 4; M32(m->esp) = 0x4518c0u; native_call(m, 0x49eeb0u);	/* 4518bb: call 0x49eeb0 */
	m->edi = m->eax;	/* 4518c0: mov edi, eax */
	m->ecx = 0x2eu;	/* 4518c2: mov ecx, 0x2e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4518c7: xor eax, eax */
	M32((DWORD)(0xa0b340u)) = m->edi;	/* 4518c9: mov dword ptr [0xa0b340], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4518cf: rep stosd dword ptr es:[edi], eax */
	{ DWORD v_ = 0x5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4518d1: push 0x5c */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 4518d3: stosb byte ptr es:[edi], al */
	m->esp -= 4; M32(m->esp) = 0x4518d9u; native_call(m, 0x49eeb0u);	/* 4518d4: call 0x49eeb0 */
	m->edi = m->eax;	/* 4518d9: mov edi, eax */
	m->ecx = 0x17u;	/* 4518db: mov ecx, 0x17 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4518e0: xor eax, eax */
	M32((DWORD)(0xa0b344u)) = m->edi;	/* 4518e2: mov dword ptr [0xa0b344], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4518e8: rep stosd dword ptr es:[edi], eax */
	{ DWORD v_ = 0x36u; m->esp -= 4; M32(m->esp) = v_; }	/* 4518ea: push 0x36 */
	m->esp -= 4; M32(m->esp) = 0x4518f1u; native_call(m, 0x49eeb0u);	/* 4518ec: call 0x49eeb0 */
	m->edi = m->eax;	/* 4518f1: mov edi, eax */
	m->ecx = 0xdu;	/* 4518f3: mov ecx, 0xd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4518f8: xor eax, eax */
	M32((DWORD)(0xa0b338u)) = m->edi;	/* 4518fa: mov dword ptr [0xa0b338], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451900: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451902: add esp, 0x40 */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 451905: stosw word ptr es:[edi], ax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 451907: push 1 */
	m->esp -= 4; M32(m->esp) = 0x45190eu; native_call(m, 0x49eeb0u);	/* 451909: call 0x49eeb0 */
	M32((DWORD)(0xa052e4u)) = m->eax;	/* 45190e: mov dword ptr [0xa052e4], eax */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 451913: push 0x1e */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x0u);	/* 451915: mov byte ptr [eax], 0 */
	m->esp -= 4; M32(m->esp) = 0x45191du; native_call(m, 0x49eeb0u);	/* 451918: call 0x49eeb0 */
	m->edi = m->eax;	/* 45191d: mov edi, eax */
	m->ecx = 0x7u;	/* 45191f: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451924: xor eax, eax */
	M32((DWORD)(0xa055e0u)) = m->edi;	/* 451926: mov dword ptr [0xa055e0], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 45192c: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 45192e: stosw word ptr es:[edi], ax */
	m->ecx = 0x8u;	/* 451930: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451935: xor eax, eax */
	m->edi = 0xa052c0u;	/* 451937: mov edi, 0xa052c0 */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 45193c: push 0x1e */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 45193e: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 451940: stosw word ptr es:[edi], ax */
	m->esp -= 4; M32(m->esp) = 0x451947u; native_call(m, 0x49eeb0u);	/* 451942: call 0x49eeb0 */
	m->edi = m->eax;	/* 451947: mov edi, eax */
	m->ecx = 0x7u;	/* 451949: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45194e: xor eax, eax */
	M32((DWORD)(0xa0b33cu)) = m->edi;	/* 451950: mov dword ptr [0xa0b33c], edi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451956: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 451958: stosw word ptr es:[edi], ax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45195a: add esp, 0xc */
	m->ecx = 0x16u;	/* 45195d: mov ecx, 0x16 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451962: xor eax, eax */
	m->edi = 0xa05260u;	/* 451964: mov edi, 0xa05260 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451969: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 45196b: stosw word ptr es:[edi], ax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 45196d: stosb byte ptr es:[edi], al */
	m->ecx = 0x1eu;	/* 45196e: mov ecx, 0x1e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451973: xor eax, eax */
	m->edi = 0xa0b280u;	/* 451975: mov edi, 0xa0b280 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 45197a: rep stosd dword ptr es:[edi], eax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 45197c: stosb byte ptr es:[edi], al */
	m->ecx = 0xfu;	/* 45197d: mov ecx, 0xf */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451982: xor eax, eax */
	m->edi = 0xa052e8u;	/* 451984: mov edi, 0xa052e8 */
	M32((DWORD)(0xa05328u)) = 0x0u;	/* 451989: mov dword ptr [0xa05328], 0 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 451993: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 451995: stosw word ptr es:[edi], ax */
	m->ecx = 0x42u;	/* 451997: mov ecx, 0x42 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45199c: xor eax, eax */
	m->edi = 0xa05638u;	/* 45199e: mov edi, 0xa05638 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4519a3: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4519a5: stosw word ptr es:[edi], ax */
	M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1;	/* 4519a7: stosb byte ptr es:[edi], al */
	m->edi = M32(m->esp); m->esp += 4;	/* 4519a8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4519a9: pop esi */
	m->esp += 4 + 0; return;	/* 4519aa: ret  */
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
