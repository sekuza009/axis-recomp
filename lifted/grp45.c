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

static void lift_452620(X86 *m);

/* net_recv (0x452620), lifted by tools/lift.py */
static void lift_452620(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452620: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 452621: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452622: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 452623: push edi */
	m->edi = M32((DWORD)(0x4a9184u));	/* 452624: mov edi, dword ptr [0x4a9184] */
	m->esp -= 4; M32(m->esp) = 0x45262cu; native_call(m, m->edi);	/* 45262a: call edi */
	m->ebp = m->eax;	/* 45262c: mov ebp, eax */
	m->eax = M32((DWORD)(0xa0b300u));	/* 45262e: mov eax, dword ptr [0xa0b300] */
	{ DWORD a_ = m->eax, b_ = 0xfffffff6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452633: add eax, -0xa */
	{ DWORD a_ = m->eax, b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452636: cmp eax, 0x13 */
	if (!m->cf && !m->zf) goto L_45299b;	/* 452639: ja 0x45299b */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45263f: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x4529c8u))) & 0xff) << 0);	/* 452641: mov cl, byte ptr [eax + 0x4529c8] */
	switch (m->ecx) { case 0: goto L_45264e; case 1: goto L_4526e9; case 2: goto L_4526f3; case 3: goto L_4527cf; case 4: goto L_452889; case 5: goto L_452924; case 6: goto L_45292e; case 7: goto L_452938; case 8: goto L_452956; case 9: goto L_45299b; default: abort(); }	/* 452647: jmp dword ptr [ecx*4 + 0x4529a0] */
L_45264e:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 45264e: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 452650: xor esi, esi */
L_452652:
	m->edx = M32((DWORD)(0xa055f8u));	/* 452652: mov edx, dword ptr [0xa055f8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452658: push ebx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 452659: push 4 */
	{ DWORD v_ = 0xa055dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 45265b: push 0xa055dc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452660: push edx */
	m->esp -= 4; M32(m->esp) = 0x452666u; native_call(m, 0x4a82d4u);	/* 452661: call 0x4a82d4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452666: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_45266c;	/* 452668: jle 0x45266c */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 45266a: add esi, eax */
L_45266c:
	m->esp -= 4; M32(m->esp) = 0x45266eu; native_call(m, m->edi);	/* 45266c: call edi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45266e: sub eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0xbb8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452670: cmp eax, 0xbb8 */
	if (!m->cf && !m->zf) goto L_45267e;	/* 452675: ja 0x45267e */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452677: cmp esi, 4 */
	if (m->cf) goto L_452652;	/* 45267a: jb 0x452652 */
	goto L_45268e;	/* 45267c: jmp 0x45268e */
L_45267e:
	M32((DWORD)(0xa0b370u)) = 0x29u;	/* 45267e: mov dword ptr [0xa0b370], 0x29 */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452688: mov dword ptr [0xa0b300], ebx */
L_45268e:
	m->eax = M32((DWORD)(0xa055dcu));	/* 45268e: mov eax, dword ptr [0xa055dc] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452693: cmp eax, 1 */
	if (!m->zf) goto L_4526b2;	/* 452696: jne 0x4526b2 */
	M32((DWORD)(0xa0b370u)) = 0x67u;	/* 452698: mov dword ptr [0xa0b370], 0x67 */
	m->esp -= 4; M32(m->esp) = 0x4526a7u; native_call(m, 0x451e60u);	/* 4526a2: call 0x451e60 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4526a7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4526a8: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 4526a9: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4526af: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4526b0: pop ebx */
	m->esp += 4 + 0; return;	/* 4526b1: ret  */
L_4526b2:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4526b2: cmp eax, ebx */
	if (!m->zf) goto L_4526cb;	/* 4526b4: jne 0x4526cb */
	m->edi = M32(m->esp); m->esp += 4;	/* 4526b6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4526b7: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 4526b8: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4526be: pop ebp */
	M32((DWORD)(0xa0b370u)) = 0x66u;	/* 4526bf: mov dword ptr [0xa0b370], 0x66 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4526c9: pop ebx */
	m->esp += 4 + 0; return;	/* 4526ca: ret  */
L_4526cb:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4526cb: cmp eax, 3 */
	if (!m->zf) goto L_45299b;	/* 4526ce: jne 0x45299b */
	m->edi = M32(m->esp); m->esp += 4;	/* 4526d4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4526d5: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 4526d6: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4526dc: pop ebp */
	M32((DWORD)(0xa0b370u)) = 0x29u;	/* 4526dd: mov dword ptr [0xa0b370], 0x29 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4526e7: pop ebx */
	m->esp += 4 + 0; return;	/* 4526e8: ret  */
L_4526e9:
	m->esp -= 4; M32(m->esp) = 0x4526eeu; native_call(m, 0x452a30u);	/* 4526e9: call 0x452a30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4526ee: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4526ef: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4526f0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4526f1: pop ebx */
	m->esp += 4 + 0; return;	/* 4526f2: ret  */
L_4526f3:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4526f3: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4526f5: xor esi, esi */
L_4526f7:
	m->eax = M32((DWORD)(0xa05630u));	/* 4526f7: mov eax, dword ptr [0xa05630] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4526fc: push ebx */
	{ DWORD v_ = 0x10bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4526fd: push 0x10b */
	{ DWORD v_ = 0xa05638u; m->esp -= 4; M32(m->esp) = v_; }	/* 452702: push 0xa05638 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452707: push eax */
	m->esp -= 4; M32(m->esp) = 0x45270du; native_call(m, 0x4a82d4u);	/* 452708: call 0x4a82d4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45270d: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_452713;	/* 45270f: jle 0x452713 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 452711: add esi, eax */
L_452713:
	m->esp -= 4; M32(m->esp) = 0x452715u; native_call(m, m->edi);	/* 452713: call edi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452715: sub eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0xbb8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452717: cmp eax, 0xbb8 */
	if (!m->cf && !m->zf) goto L_452728;	/* 45271c: ja 0x452728 */
	{ DWORD a_ = m->esi, b_ = 0x10bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45271e: cmp esi, 0x10b */
	if (m->cf) goto L_4526f7;	/* 452724: jb 0x4526f7 */
	goto L_452738;	/* 452726: jmp 0x452738 */
L_452728:
	M32((DWORD)(0xa0b378u)) = 0x28u;	/* 452728: mov dword ptr [0xa0b378], 0x28 */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452732: mov dword ptr [0xa0b300], ebx */
L_452738:
	m->ecx = M32((DWORD)(0xa05638u));	/* 452738: mov ecx, dword ptr [0xa05638] */
	m->eax = (DWORD)(m->ecx + 0xffffffe1u);	/* 45273e: lea eax, [ecx - 0x1f] */
	{ DWORD a_ = m->eax, b_ = 0xbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452741: cmp eax, 0xb */
	if (!m->cf && !m->zf) goto L_45299b;	/* 452744: ja 0x45299b */
	switch (m->eax) { case 0: goto L_452766; case 1: goto L_45277b; case 2: goto L_452751; case 3: goto L_452790; case 4: goto L_45299b; case 5: goto L_45299b; case 6: goto L_45299b; case 7: goto L_45299b; case 8: goto L_45299b; case 9: goto L_4527a5; case 10: goto L_45299b; case 11: goto L_4527ba; default: abort(); }	/* 45274a: jmp dword ptr [eax*4 + 0x4529dc] */
L_452751:
	m->edi = M32(m->esp); m->esp += 4;	/* 452751: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452752: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452753: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 452759: pop ebp */
	M32((DWORD)(0xa0b378u)) = 0x21u;	/* 45275a: mov dword ptr [0xa0b378], 0x21 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452764: pop ebx */
	m->esp += 4 + 0; return;	/* 452765: ret  */
L_452766:
	m->edi = M32(m->esp); m->esp += 4;	/* 452766: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452767: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452768: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45276e: pop ebp */
	M32((DWORD)(0xa0b378u)) = 0x1fu;	/* 45276f: mov dword ptr [0xa0b378], 0x1f */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452779: pop ebx */
	m->esp += 4 + 0; return;	/* 45277a: ret  */
L_45277b:
	m->edi = M32(m->esp); m->esp += 4;	/* 45277b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45277c: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 45277d: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 452783: pop ebp */
	M32((DWORD)(0xa0b378u)) = 0x20u;	/* 452784: mov dword ptr [0xa0b378], 0x20 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45278e: pop ebx */
	m->esp += 4 + 0; return;	/* 45278f: ret  */
L_452790:
	m->edi = M32(m->esp); m->esp += 4;	/* 452790: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452791: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452792: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 452798: pop ebp */
	M32((DWORD)(0xa0b378u)) = 0x22u;	/* 452799: mov dword ptr [0xa0b378], 0x22 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4527a3: pop ebx */
	m->esp += 4 + 0; return;	/* 4527a4: ret  */
L_4527a5:
	m->edi = M32(m->esp); m->esp += 4;	/* 4527a5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4527a6: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 4527a7: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4527ad: pop ebp */
	M32((DWORD)(0xa0b378u)) = 0x28u;	/* 4527ae: mov dword ptr [0xa0b378], 0x28 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4527b8: pop ebx */
	m->esp += 4 + 0; return;	/* 4527b9: ret  */
L_4527ba:
	m->edi = M32(m->esp); m->esp += 4;	/* 4527ba: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4527bb: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 4527bc: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4527c2: pop ebp */
	M32((DWORD)(0xa0b378u)) = 0x2au;	/* 4527c3: mov dword ptr [0xa0b378], 0x2a */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4527cd: pop ebx */
	m->esp += 4 + 0; return;	/* 4527ce: ret  */
L_4527cf:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4527cf: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4527d1: xor esi, esi */
L_4527d3:
	m->edx = M32((DWORD)(0xa05630u));	/* 4527d3: mov edx, dword ptr [0xa05630] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4527d9: push ebx */
	{ DWORD v_ = 0x10bu; m->esp -= 4; M32(m->esp) = v_; }	/* 4527da: push 0x10b */
	{ DWORD v_ = 0xa05638u; m->esp -= 4; M32(m->esp) = v_; }	/* 4527df: push 0xa05638 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4527e4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4527eau; native_call(m, 0x4a82d4u);	/* 4527e5: call 0x4a82d4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4527ea: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_4527f0;	/* 4527ec: jle 0x4527f0 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4527ee: add esi, eax */
L_4527f0:
	m->esp -= 4; M32(m->esp) = 0x4527f2u; native_call(m, m->edi);	/* 4527f0: call edi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4527f2: sub eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0xbb8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4527f4: cmp eax, 0xbb8 */
	if (!m->cf && !m->zf) goto L_452805;	/* 4527f9: ja 0x452805 */
	{ DWORD a_ = m->esi, b_ = 0x10bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4527fb: cmp esi, 0x10b */
	if (m->cf) goto L_4527d3;	/* 452801: jb 0x4527d3 */
	goto L_452815;	/* 452803: jmp 0x452815 */
L_452805:
	M32((DWORD)(0xa0b37cu)) = 0x28u;	/* 452805: mov dword ptr [0xa0b37c], 0x28 */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 45280f: mov dword ptr [0xa0b300], ebx */
L_452815:
	m->eax = M32((DWORD)(0xa05638u));	/* 452815: mov eax, dword ptr [0xa05638] */
	{ DWORD a_ = m->eax, b_ = 0xffffffe2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45281a: add eax, -0x1e */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45281d: cmp eax, 0xc */
	if (!m->cf && !m->zf) goto L_45299b;	/* 452820: ja 0x45299b */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 452826: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x452a20u))) & 0xff) << 0);	/* 452828: mov cl, byte ptr [eax + 0x452a20] */
	switch (m->ecx) { case 0: goto L_45284a; case 1: goto L_452835; case 2: goto L_45285f; case 3: goto L_452874; case 4: goto L_45299b; default: abort(); }	/* 45282e: jmp dword ptr [ecx*4 + 0x452a0c] */
L_452835:
	m->edi = M32(m->esp); m->esp += 4;	/* 452835: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452836: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452837: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45283d: pop ebp */
	M32((DWORD)(0xa0b37cu)) = 0x21u;	/* 45283e: mov dword ptr [0xa0b37c], 0x21 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452848: pop ebx */
	m->esp += 4 + 0; return;	/* 452849: ret  */
L_45284a:
	m->edi = M32(m->esp); m->esp += 4;	/* 45284a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45284b: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 45284c: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 452852: pop ebp */
	M32((DWORD)(0xa0b37cu)) = 0x1eu;	/* 452853: mov dword ptr [0xa0b37c], 0x1e */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45285d: pop ebx */
	m->esp += 4 + 0; return;	/* 45285e: ret  */
L_45285f:
	m->edi = M32(m->esp); m->esp += 4;	/* 45285f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452860: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452861: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 452867: pop ebp */
	M32((DWORD)(0xa0b37cu)) = 0x28u;	/* 452868: mov dword ptr [0xa0b37c], 0x28 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452872: pop ebx */
	m->esp += 4 + 0; return;	/* 452873: ret  */
L_452874:
	m->edi = M32(m->esp); m->esp += 4;	/* 452874: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452875: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452876: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45287c: pop ebp */
	M32((DWORD)(0xa0b37cu)) = 0x2au;	/* 45287d: mov dword ptr [0xa0b37c], 0x2a */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452887: pop ebx */
	m->esp += 4 + 0; return;	/* 452888: ret  */
L_452889:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 452889: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45288b: xor esi, esi */
L_45288d:
	m->edx = M32((DWORD)(0xa05630u));	/* 45288d: mov edx, dword ptr [0xa05630] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452893: push ebx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 452894: push 4 */
	{ DWORD v_ = 0xa0b248u; m->esp -= 4; M32(m->esp) = v_; }	/* 452896: push 0xa0b248 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45289b: push edx */
	m->esp -= 4; M32(m->esp) = 0x4528a1u; native_call(m, 0x4a82d4u);	/* 45289c: call 0x4a82d4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4528a1: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_4528a7;	/* 4528a3: jle 0x4528a7 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4528a5: add esi, eax */
L_4528a7:
	m->esp -= 4; M32(m->esp) = 0x4528a9u; native_call(m, m->edi);	/* 4528a7: call edi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4528a9: sub eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0xbb8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4528ab: cmp eax, 0xbb8 */
	if (!m->cf && !m->zf) goto L_4528b9;	/* 4528b0: ja 0x4528b9 */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4528b2: cmp esi, 4 */
	if (m->cf) goto L_45288d;	/* 4528b5: jb 0x45288d */
	goto L_4528c9;	/* 4528b7: jmp 0x4528c9 */
L_4528b9:
	M32((DWORD)(0xa0b374u)) = 0x28u;	/* 4528b9: mov dword ptr [0xa0b374], 0x28 */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 4528c3: mov dword ptr [0xa0b300], ebx */
L_4528c9:
	m->eax = M32((DWORD)(0xa0b248u));	/* 4528c9: mov eax, dword ptr [0xa0b248] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4528ce: cmp eax, 1 */
	if (!m->zf) goto L_4528ed;	/* 4528d1: jne 0x4528ed */
	M32((DWORD)(0xa0b374u)) = 0x67u;	/* 4528d3: mov dword ptr [0xa0b374], 0x67 */
	m->esp -= 4; M32(m->esp) = 0x4528e2u; native_call(m, 0x451e60u);	/* 4528dd: call 0x451e60 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4528e2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4528e3: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 4528e4: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4528ea: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4528eb: pop ebx */
	m->esp += 4 + 0; return;	/* 4528ec: ret  */
L_4528ed:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4528ed: cmp eax, ebx */
	if (!m->zf) goto L_452906;	/* 4528ef: jne 0x452906 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4528f1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4528f2: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 4528f3: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4528f9: pop ebp */
	M32((DWORD)(0xa0b374u)) = 0x66u;	/* 4528fa: mov dword ptr [0xa0b374], 0x66 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452904: pop ebx */
	m->esp += 4 + 0; return;	/* 452905: ret  */
L_452906:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452906: cmp eax, 3 */
	if (!m->zf) goto L_45299b;	/* 452909: jne 0x45299b */
	m->edi = M32(m->esp); m->esp += 4;	/* 45290f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452910: pop esi */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452911: mov dword ptr [0xa0b300], ebx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 452917: pop ebp */
	M32((DWORD)(0xa0b374u)) = 0x28u;	/* 452918: mov dword ptr [0xa0b374], 0x28 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452922: pop ebx */
	m->esp += 4 + 0; return;	/* 452923: ret  */
L_452924:
	m->esp -= 4; M32(m->esp) = 0x452929u; native_call(m, 0x452bd0u);	/* 452924: call 0x452bd0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 452929: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45292a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45292b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45292c: pop ebx */
	m->esp += 4 + 0; return;	/* 45292d: ret  */
L_45292e:
	m->esp -= 4; M32(m->esp) = 0x452933u; native_call(m, 0x452d70u);	/* 45292e: call 0x452d70 */
	m->edi = M32(m->esp); m->esp += 4;	/* 452933: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452934: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 452935: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452936: pop ebx */
	m->esp += 4 + 0; return;	/* 452937: ret  */
L_452938:
	m->esp -= 4; M32(m->esp) = 0x45293du; native_call(m, 0x452ea0u);	/* 452938: call 0x452ea0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45293d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45293e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45293f: pop ebp */
	M32((DWORD)(0xa0b350u)) = 0x1u;	/* 452940: mov dword ptr [0xa0b350], 1 */
	M32((DWORD)(0xa0b300u)) = 0x0u;	/* 45294a: mov dword ptr [0xa0b300], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452954: pop ebx */
	m->esp += 4 + 0; return;	/* 452955: ret  */
L_452956:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 452956: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 452958: xor esi, esi */
L_45295a:
	m->eax = M32((DWORD)(0xa05630u));	/* 45295a: mov eax, dword ptr [0xa05630] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45295f: push ebx */
	{ DWORD v_ = 0x22u; m->esp -= 4; M32(m->esp) = v_; }	/* 452960: push 0x22 */
	{ DWORD v_ = 0xa052c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452962: push 0xa052c0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452967: push eax */
	m->esp -= 4; M32(m->esp) = 0x45296du; native_call(m, 0x4a82d4u);	/* 452968: call 0x4a82d4 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45296d: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_452973;	/* 45296f: jle 0x452973 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 452971: add esi, eax */
L_452973:
	m->esp -= 4; M32(m->esp) = 0x452975u; native_call(m, m->edi);	/* 452973: call edi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452975: sub eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0xbb8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452977: cmp eax, 0xbb8 */
	if (!m->cf && !m->zf) goto L_452983;	/* 45297c: ja 0x452983 */
	{ DWORD a_ = m->esi, b_ = 0x22u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45297e: cmp esi, 0x22 */
	if (m->cf) goto L_45295a;	/* 452981: jb 0x45295a */
L_452983:
	{ DWORD a_ = M8((DWORD)(0xa052c0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 452983: cmp byte ptr [0xa052c0], bl */
	if (m->zf) goto L_45299b;	/* 452989: je 0x45299b */
	M32((DWORD)(0xa0b354u)) = 0x1u;	/* 45298b: mov dword ptr [0xa0b354], 1 */
	M32((DWORD)(0xa0b300u)) = m->ebx;	/* 452995: mov dword ptr [0xa0b300], ebx */
L_45299b:
	m->edi = M32(m->esp); m->esp += 4;	/* 45299b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45299c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45299d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45299e: pop ebx */
	m->esp += 4 + 0; return;	/* 45299f: ret  */
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
