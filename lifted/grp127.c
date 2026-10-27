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

static void lift_4062b0(X86 *m);
static void lift_41f540(X86 *m);
static void lift_440840(X86 *m);
static void lift_456ed0(X86 *m);
static void lift_434e70(X86 *m);

/* app_onClose (0x434e70), lifted by tools/lift.py */
static void lift_434e70(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbb78u));	/* 434e70: mov eax, dword ptr [0x4dbb78] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 434e75: push ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 434e76: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434e78: cmp eax, ebx */
	if (m->zf) goto L_434e9f;	/* 434e7a: je 0x434e9f */
	M32((DWORD)(0x4dbb10u)) = m->ebx;	/* 434e7c: mov dword ptr [0x4dbb10], ebx */
	M32((DWORD)(0x4dbb78u)) = m->ebx;	/* 434e82: mov dword ptr [0x4dbb78], ebx */
	m->esp -= 4; M32(m->esp) = 0x434e8du; native_call(m, 0x452fe0u);	/* 434e88: call 0x452fe0 */
	{ DWORD v_ = 0x44u; m->esp -= 4; M32(m->esp) = v_; }	/* 434e8d: push 0x44 */
	m->esp -= 4; M32(m->esp) = 0x434e94u; native_call(m, 0x41ee40u);	/* 434e8f: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434e94: add esp, 4 */
	M32((DWORD)(0x4db8b4u)) = m->ebx;	/* 434e97: mov dword ptr [0x4db8b4], ebx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 434e9d: pop ebx */
	m->esp += 4 + 0; return;	/* 434e9e: ret  */
L_434e9f:
	{ DWORD a_ = M32((DWORD)(0x4db708u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434e9f: cmp dword ptr [0x4db708], ebx */
	if (m->zf) goto L_434fd2;	/* 434ea5: je 0x434fd2 */
	m->eax = M32((DWORD)(0x4db710u));	/* 434eab: mov eax, dword ptr [0x4db710] */
	m->edx = M32((DWORD)(0x4dbbf8u));	/* 434eb0: mov edx, dword ptr [0x4dbbf8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 434eb6: push ebx */
	{ DWORD v_ = 0x9dd570u; m->esp -= 4; M32(m->esp) = v_; }	/* 434eb7: push 0x9dd570 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 434ebc: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 434ebf: lea eax, [eax + ecx*4] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 434ec2: mov ecx, dword ptr [edx] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 434ec4: shl eax, 1 */
	M32((DWORD)(m->eax + 0x9087c0u)) = m->ecx;	/* 434ec6: mov dword ptr [eax + 0x9087c0], ecx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9087edu))) & 0xff) << 0);	/* 434ecc: mov dl, byte ptr [eax + 0x9087ed] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9087eeu))) & 0xff) << 0);	/* 434ed2: mov cl, byte ptr [eax + 0x9087ee] */
	M8((DWORD)(0x5b1b54u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 434ed8: mov byte ptr [0x5b1b54], dl */
	m->edx = M32((DWORD)(m->eax + 0x9087c0u));	/* 434ede: mov edx, dword ptr [eax + 0x9087c0] */
	M8((DWORD)(0x5b1b55u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 434ee4: mov byte ptr [0x5b1b55], cl */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 434eea: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 434eeb: push ebx */
	m->esp -= 4; M32(m->esp) = 0x434ef1u; native_call(m, 0x453180u);	/* 434eec: call 0x453180 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434ef1: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1f4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434ef4: cmp eax, 0x1f4 */
	if (m->zf) goto L_434f3b;	/* 434ef9: je 0x434f3b */
	{ DWORD a_ = m->eax, b_ = 0xfffffe0bu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 434efb: add eax, 0xfffffe0b */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 434f00: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_434f22;	/* 434f03: ja 0x434f22 */
	switch (m->eax) { case 0: goto L_434f0c; case 1: goto L_434f10; case 2: goto L_434f10; case 3: goto L_434f14; case 4: goto L_434f18; default: abort(); }	/* 434f05: jmp dword ptr [eax*4 + 0x434fd4] */
L_434f0c:
	{ DWORD v_ = 0x43u; m->esp -= 4; M32(m->esp) = v_; }	/* 434f0c: push 0x43 */
	goto L_434f1a;	/* 434f0e: jmp 0x434f1a */
L_434f10:
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 434f10: push 0x42 */
	goto L_434f1a;	/* 434f12: jmp 0x434f1a */
L_434f14:
	{ DWORD v_ = 0x44u; m->esp -= 4; M32(m->esp) = v_; }	/* 434f14: push 0x44 */
	goto L_434f1a;	/* 434f16: jmp 0x434f1a */
L_434f18:
	{ DWORD v_ = 0x45u; m->esp -= 4; M32(m->esp) = v_; }	/* 434f18: push 0x45 */
L_434f1a:
	m->esp -= 4; M32(m->esp) = 0x434f1fu; native_call(m, 0x41ee40u);	/* 434f1a: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 434f1f: add esp, 4 */
L_434f22:
	m->esp -= 4; M32(m->esp) = 0x434f27u; native_call(m, 0x452fe0u);	/* 434f22: call 0x452fe0 */
	M32((DWORD)(0x4dbb10u)) = m->ebx;	/* 434f27: mov dword ptr [0x4dbb10], ebx */
	M32((DWORD)(0x4db708u)) = m->ebx;	/* 434f2d: mov dword ptr [0x4db708], ebx */
	M32((DWORD)(0x4db8b4u)) = m->ebx;	/* 434f33: mov dword ptr [0x4db8b4], ebx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 434f39: pop ebx */
	m->esp += 4 + 0; return;	/* 434f3a: ret  */
L_434f3b:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 434f3b: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 434f3c: push edi */
	m->esp -= 4; M32(m->esp) = 0x434f42u; native_call(m, 0x457310u);	/* 434f3d: call 0x457310 */
	m->eax = M32((DWORD)(0x4db710u));	/* 434f42: mov eax, dword ptr [0x4db710] */
	m->edi = 0x67fb44u;	/* 434f47: mov edi, 0x67fb44 */
	M32((DWORD)(0x67ef14u)) = 0x1u;	/* 434f4c: mov dword ptr [0x67ef14], 1 */
	M32((DWORD)(0x67ef04u)) = 0x2u;	/* 434f56: mov dword ptr [0x67ef04], 2 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 434f60: lea ecx, [eax + eax*8] */
	M32((DWORD)(0x9dce48u)) = m->ebx;	/* 434f63: mov dword ptr [0x9dce48], ebx */
	M32((DWORD)(0x4dbb10u)) = m->ebx;	/* 434f69: mov dword ptr [0x4dbb10], ebx */
	M32((DWORD)(0x4db708u)) = m->ebx;	/* 434f6f: mov dword ptr [0x4db708], ebx */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 434f75: lea eax, [eax + ecx*4] */
	m->ecx = 0x8u;	/* 434f78: mov ecx, 8 */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 434f7d: shl eax, 1 */
	M32((DWORD)(0x4db8b4u)) = m->ebx;	/* 434f7f: mov dword ptr [0x4db8b4], ebx */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->eax + 0x9087e5u)));	/* 434f85: movsx edx, byte ptr [eax + 0x9087e5] */
	m->esi = (DWORD)(m->eax + 0x9087c4u);	/* 434f8c: lea esi, [eax + 0x9087c4] */
	M32((DWORD)(0x9dad94u)) = m->edx;	/* 434f92: mov dword ptr [0x9dad94], edx */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->eax + 0x9087ecu)));	/* 434f98: movsx edx, byte ptr [eax + 0x9087ec] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 434f9f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->eax + 0x9087e4u)));	/* 434fa1: movsx ecx, byte ptr [eax + 0x9087e4] */
	M32((DWORD)(0x9da3e0u)) = m->ecx;	/* 434fa8: mov dword ptr [0x9da3e0], ecx */
	M32((DWORD)(0x76d368u)) = m->edx;	/* 434fae: mov dword ptr [0x76d368], edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 434fb4: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 434fb6: xor edx, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9087edu))) & 0xff) << 0);	/* 434fb8: mov cl, byte ptr [eax + 0x9087ed] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9087eeu))) & 0xff) << 0);	/* 434fbe: mov dl, byte ptr [eax + 0x9087ee] */
	m->edi = M32(m->esp); m->esp += 4;	/* 434fc4: pop edi */
	M32((DWORD)(0x4df8e8u)) = m->ecx;	/* 434fc5: mov dword ptr [0x4df8e8], ecx */
	M32((DWORD)(0x76d408u)) = m->edx;	/* 434fcb: mov dword ptr [0x76d408], edx */
	m->esi = M32(m->esp); m->esp += 4;	/* 434fd1: pop esi */
L_434fd2:
	m->ebx = M32(m->esp); m->esp += 4;	/* 434fd2: pop ebx */
	m->esp += 4 + 0; return;	/* 434fd3: ret  */
}

/* app_shutdown (0x4062b0), lifted by tools/lift.py */
static void lift_4062b0(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbb78u));	/* 4062b0: mov eax, dword ptr [0x4dbb78] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4062b5: push ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4062b6: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4062b8: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4062b9: cmp eax, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4062bb: push edi */
	if (m->zf) goto L_4062e3;	/* 4062bc: je 0x4062e3 */
	M32((DWORD)(0x4dbb10u)) = m->ebx;	/* 4062be: mov dword ptr [0x4dbb10], ebx */
	M32((DWORD)(0x4dbb78u)) = m->ebx;	/* 4062c4: mov dword ptr [0x4dbb78], ebx */
	m->esp -= 4; M32(m->esp) = 0x4062cfu; native_call(m, 0x452fe0u);	/* 4062ca: call 0x452fe0 */
	{ DWORD v_ = 0x44u; m->esp -= 4; M32(m->esp) = v_; }	/* 4062cf: push 0x44 */
	m->esp -= 4; M32(m->esp) = 0x4062d6u; native_call(m, 0x41ee40u);	/* 4062d1: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4062d6: add esp, 4 */
	M32((DWORD)(0x4db8b4u)) = m->ebx;	/* 4062d9: mov dword ptr [0x4db8b4], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 4062df: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4062e0: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4062e1: pop ebx */
	m->esp += 4 + 0; return;	/* 4062e2: ret  */
L_4062e3:
	m->eax = M32((DWORD)(0x4db710u));	/* 4062e3: mov eax, dword ptr [0x4db710] */
	{ DWORD a_ = m->eax, b_ = 0x1869fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4062e8: cmp eax, 0x1869f */
	if (!m->zf) goto L_406414;	/* 4062ed: jne 0x406414 */
	m->eax = M32((DWORD)(0x4db708u));	/* 4062f3: mov eax, dword ptr [0x4db708] */
	M32((DWORD)(0x4db710u)) = m->ebx;	/* 4062f8: mov dword ptr [0x4db710], ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4062fe: cmp eax, ebx */
	if (m->zf) goto L_40656a;	/* 406300: je 0x40656a */
	m->eax = M32((DWORD)(0x4dbbf8u));	/* 406306: mov eax, dword ptr [0x4dbbf8] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 40630b: mov ecx, dword ptr [eax] */
	m->edi = (DWORD)(m->eax + 0x2eu);	/* 40630d: lea edi, [eax + 0x2e] */
	M32((DWORD)(0x9dae20u)) = m->ecx;	/* 406310: mov dword ptr [0x9dae20], ecx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x28u))) & 0xff) << 0);	/* 406316: mov dl, byte ptr [eax + 0x28] */
	M8((DWORD)(0x9dae4du)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 406319: mov byte ptr [0x9dae4d], dl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x29u))) & 0xff) << 0);	/* 40631f: mov cl, byte ptr [eax + 0x29] */
	M8((DWORD)(0x9dae4eu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 406322: mov byte ptr [0x9dae4e], cl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x27u))) & 0xff) << 0);	/* 406328: mov dl, byte ptr [eax + 0x27] */
	M8((DWORD)(0x9dae4cu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 40632b: mov byte ptr [0x9dae4c], dl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x24u))) & 0xff) << 0);	/* 406331: mov cl, byte ptr [eax + 0x24] */
	M8((DWORD)(0x9dae45u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 406334: mov byte ptr [0x9dae45], cl */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(m->eax + 0x24u))) & 0xffff);	/* 40633a: mov dx, word ptr [eax + 0x24] */
	{ DWORD a_ = m->edx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 40633e: sar edx, 8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 406341: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 406344: xor eax, eax */
	M8((DWORD)(0x9dae44u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 406346: mov byte ptr [0x9dae44], dl */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 40634c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40634e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 406350: sub edi, ecx */
	m->eax = m->ecx;	/* 406352: mov eax, ecx */
	m->esi = m->edi;	/* 406354: mov esi, edi */
	m->edi = 0x9dae24u;	/* 406356: mov edi, 0x9dae24 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 40635b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40635e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 406360: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 406362: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 406365: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4dedd0u));	/* 406367: mov ecx, dword ptr [0x4dedd0] */
	m->edx = M32((DWORD)(0x9dae20u));	/* 40636d: mov edx, dword ptr [0x9dae20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 406373: push ecx */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 406374: push 0x4dedb0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 406379: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40637a: push ebx */
	m->esp -= 4; M32(m->esp) = 0x406380u; native_call(m, 0x453180u);	/* 40637b: call 0x453180 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406380: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1f4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406383: cmp eax, 0x1f4 */
	if (m->zf) goto L_40639f;	/* 406388: je 0x40639f */
	{ DWORD a_ = m->eax, b_ = 0xfffffe0bu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40638a: add eax, 0xfffffe0b */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40638f: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_4064c8;	/* 406392: ja 0x4064c8 */
	switch (m->eax) { case 0: goto L_406482; case 1: goto L_406496; case 2: goto L_406496; case 3: goto L_4064aa; case 4: goto L_4064be; default: abort(); }	/* 406398: jmp dword ptr [eax*4 + 0x406570] */
L_40639f:
	m->esp -= 4; M32(m->esp) = 0x4063a4u; native_call(m, 0x457310u);	/* 40639f: call 0x457310 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x9dae45u)));	/* 4063a4: movsx eax, byte ptr [0x9dae45] */
	m->ecx = 0x8u;	/* 4063ab: mov ecx, 8 */
	m->esi = 0x9dae24u;	/* 4063b0: mov esi, 0x9dae24 */
	m->edi = 0x67fb44u;	/* 4063b5: mov edi, 0x67fb44 */
	M32((DWORD)(0x9dad94u)) = m->eax;	/* 4063ba: mov dword ptr [0x9dad94], eax */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x9dae4cu)));	/* 4063bf: movsx edx, byte ptr [0x9dae4c] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4063c6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x9dae44u)));	/* 4063c8: movsx ecx, byte ptr [0x9dae44] */
	M32((DWORD)(0x9da3e0u)) = m->ecx;	/* 4063cf: mov dword ptr [0x9da3e0], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4063d5: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x9dae4du))) & 0xff) << 0);	/* 4063d7: mov al, byte ptr [0x9dae4d] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4063dc: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x9dae4eu))) & 0xff) << 0);	/* 4063de: mov cl, byte ptr [0x9dae4e] */
	M32((DWORD)(0x67ef14u)) = 0x1u;	/* 4063e4: mov dword ptr [0x67ef14], 1 */
	M32((DWORD)(0x67ef04u)) = 0x2u;	/* 4063ee: mov dword ptr [0x67ef04], 2 */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 4063f8: mov dword ptr [0x4dbb3c], ebx */
	M32((DWORD)(0x76d368u)) = m->edx;	/* 4063fe: mov dword ptr [0x76d368], edx */
	M32((DWORD)(0x4df8e8u)) = m->eax;	/* 406404: mov dword ptr [0x4df8e8], eax */
	M32((DWORD)(0x76d408u)) = m->ecx;	/* 406409: mov dword ptr [0x76d408], ecx */
	goto L_406553;	/* 40640f: jmp 0x406553 */
L_406414:
	{ DWORD a_ = M32((DWORD)(0x4db708u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406414: cmp dword ptr [0x4db708], ebx */
	if (m->zf) goto L_40656a;	/* 40641a: je 0x40656a */
	m->ecx = M32((DWORD)(0x4dbbf8u));	/* 406420: mov ecx, dword ptr [0x4dbbf8] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 406426: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 406429: lea eax, [eax + edx*4] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 40642c: mov edx, dword ptr [ecx] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40642e: shl eax, 1 */
	M32((DWORD)(m->eax + 0x9087c0u)) = m->edx;	/* 406430: mov dword ptr [eax + 0x9087c0], edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9087edu))) & 0xff) << 0);	/* 406436: mov cl, byte ptr [eax + 0x9087ed] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9087eeu))) & 0xff) << 0);	/* 40643c: mov dl, byte ptr [eax + 0x9087ee] */
	M8((DWORD)(0x4ded44u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 406442: mov byte ptr [0x4ded44], cl */
	m->ecx = M32((DWORD)(0x4dedd0u));	/* 406448: mov ecx, dword ptr [0x4dedd0] */
	M8((DWORD)(0x4ded45u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 40644e: mov byte ptr [0x4ded45], dl */
	m->edx = M32((DWORD)(m->eax + 0x9087c0u));	/* 406454: mov edx, dword ptr [eax + 0x9087c0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40645a: push ecx */
	{ DWORD v_ = 0x4dedb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40645b: push 0x4dedb0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 406460: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 406461: push ebx */
	m->esp -= 4; M32(m->esp) = 0x406467u; native_call(m, 0x453180u);	/* 406462: call 0x453180 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406467: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1f4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40646a: cmp eax, 0x1f4 */
	if (m->zf) goto L_4064d2;	/* 40646f: je 0x4064d2 */
	{ DWORD a_ = m->eax, b_ = 0xfffffe0bu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 406471: add eax, 0xfffffe0b */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406476: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_4064c8;	/* 406479: ja 0x4064c8 */
	switch (m->eax) { case 0: goto L_406482; case 1: goto L_406496; case 2: goto L_406496; case 3: goto L_4064aa; case 4: goto L_4064be; default: abort(); }	/* 40647b: jmp dword ptr [eax*4 + 0x406584] */
L_406482:
	{ DWORD v_ = 0x43u; m->esp -= 4; M32(m->esp) = v_; }	/* 406482: push 0x43 */
	m->esp -= 4; M32(m->esp) = 0x406489u; native_call(m, 0x41ee40u);	/* 406484: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406489: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x406491u; native_call(m, 0x452fe0u);	/* 40648c: call 0x452fe0 */
	goto L_406558;	/* 406491: jmp 0x406558 */
L_406496:
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 406496: push 0x42 */
	m->esp -= 4; M32(m->esp) = 0x40649du; native_call(m, 0x41ee40u);	/* 406498: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40649d: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4064a5u; native_call(m, 0x452fe0u);	/* 4064a0: call 0x452fe0 */
	goto L_406558;	/* 4064a5: jmp 0x406558 */
L_4064aa:
	{ DWORD v_ = 0x44u; m->esp -= 4; M32(m->esp) = v_; }	/* 4064aa: push 0x44 */
	m->esp -= 4; M32(m->esp) = 0x4064b1u; native_call(m, 0x41ee40u);	/* 4064ac: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4064b1: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4064b9u; native_call(m, 0x452fe0u);	/* 4064b4: call 0x452fe0 */
	goto L_406558;	/* 4064b9: jmp 0x406558 */
L_4064be:
	{ DWORD v_ = 0x45u; m->esp -= 4; M32(m->esp) = v_; }	/* 4064be: push 0x45 */
	m->esp -= 4; M32(m->esp) = 0x4064c5u; native_call(m, 0x41ee40u);	/* 4064c0: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4064c5: add esp, 4 */
L_4064c8:
	m->esp -= 4; M32(m->esp) = 0x4064cdu; native_call(m, 0x452fe0u);	/* 4064c8: call 0x452fe0 */
	goto L_406558;	/* 4064cd: jmp 0x406558 */
L_4064d2:
	m->esp -= 4; M32(m->esp) = 0x4064d7u; native_call(m, 0x457310u);	/* 4064d2: call 0x457310 */
	m->eax = M32((DWORD)(0x4db710u));	/* 4064d7: mov eax, dword ptr [0x4db710] */
	m->edi = 0x67fb44u;	/* 4064dc: mov edi, 0x67fb44 */
	M32((DWORD)(0x67ef14u)) = 0x1u;	/* 4064e1: mov dword ptr [0x67ef14], 1 */
	M32((DWORD)(0x67ef04u)) = 0x2u;	/* 4064eb: mov dword ptr [0x67ef04], 2 */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4064f5: lea ecx, [eax + eax*8] */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 4064f8: mov dword ptr [0x4dbb3c], ebx */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 4064fe: lea eax, [eax + ecx*4] */
	m->ecx = 0x8u;	/* 406501: mov ecx, 8 */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 406506: shl eax, 1 */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->eax + 0x9087e5u)));	/* 406508: movsx edx, byte ptr [eax + 0x9087e5] */
	m->esi = (DWORD)(m->eax + 0x9087c4u);	/* 40650f: lea esi, [eax + 0x9087c4] */
	M32((DWORD)(0x9dad94u)) = m->edx;	/* 406515: mov dword ptr [0x9dad94], edx */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->eax + 0x9087ecu)));	/* 40651b: movsx edx, byte ptr [eax + 0x9087ec] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 406522: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->eax + 0x9087e4u)));	/* 406524: movsx ecx, byte ptr [eax + 0x9087e4] */
	M32((DWORD)(0x9da3e0u)) = m->ecx;	/* 40652b: mov dword ptr [0x9da3e0], ecx */
	M32((DWORD)(0x76d368u)) = m->edx;	/* 406531: mov dword ptr [0x76d368], edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 406537: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 406539: xor edx, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9087edu))) & 0xff) << 0);	/* 40653b: mov cl, byte ptr [eax + 0x9087ed] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x9087eeu))) & 0xff) << 0);	/* 406541: mov dl, byte ptr [eax + 0x9087ee] */
	M32((DWORD)(0x4df8e8u)) = m->ecx;	/* 406547: mov dword ptr [0x4df8e8], ecx */
	M32((DWORD)(0x76d408u)) = m->edx;	/* 40654d: mov dword ptr [0x76d408], edx */
L_406553:
	m->esp -= 4; M32(m->esp) = 0x406558u; native_call(m, 0x451e60u);	/* 406553: call 0x451e60 */
L_406558:
	M32((DWORD)(0x4dbb10u)) = m->ebx;	/* 406558: mov dword ptr [0x4dbb10], ebx */
	M32((DWORD)(0x4db708u)) = m->ebx;	/* 40655e: mov dword ptr [0x4db708], ebx */
	M32((DWORD)(0x4db8b4u)) = m->ebx;	/* 406564: mov dword ptr [0x4db8b4], ebx */
L_40656a:
	m->edi = M32(m->esp); m->esp += 4;	/* 40656a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40656b: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40656c: pop ebx */
	m->esp += 4 + 0; return;	/* 40656d: ret  */
}

/* menuState100_intro (0x41f540), lifted by tools/lift.py */
static void lift_41f540(X86 *m)
{
	m->eax = M32((DWORD)(0x76d35cu));	/* 41f540: mov eax, dword ptr [0x76d35c] */
	m->ecx = M32((DWORD)(0x76d358u));	/* 41f545: mov ecx, dword ptr [0x76d358] */
	m->edx = M32((DWORD)(0x76d354u));	/* 41f54b: mov edx, dword ptr [0x76d354] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f551: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f552: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f553: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f554: push eax */
	m->eax = M32((DWORD)(0x76d350u));	/* 41f555: mov eax, dword ptr [0x76d350] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f55a: push ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41f55b: xor edi, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f55d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f55e: push eax */
	M32((DWORD)(0x4df01cu)) = m->edi;	/* 41f55f: mov dword ptr [0x4df01c], edi */
	M32((DWORD)(0x4e0458u)) = m->edi;	/* 41f565: mov dword ptr [0x4e0458], edi */
	M32((DWORD)(0x4dda34u)) = m->edi;	/* 41f56b: mov dword ptr [0x4dda34], edi */
	m->esp -= 4; M32(m->esp) = 0x41f577u; native_call(m, M32(0x4a91e0u));	/* 41f571: call dword ptr [0x4a91e0] */
	{ DWORD v_ = 0x4100u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f577: push 0x4100 */
	m->esp -= 4; M32(m->esp) = 0x41f582u; native_call(m, M32(0x4a91e8u));	/* 41f57c: call dword ptr [0x4a91e8] */
	m->esi = M32((DWORD)(0x4a9228u));	/* 41f582: mov esi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f588: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f58d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f592: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f597: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41f59eu; native_call(m, m->esi);	/* 41f59c: call esi */
	m->ebx = M32((DWORD)(0x4a9224u));	/* 41f59e: mov ebx, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xbe2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5a4: push 0xbe2 */
	m->esp -= 4; M32(m->esp) = 0x41f5abu; native_call(m, m->ebx);	/* 41f5a9: call ebx */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5ab: push 0x3f19999a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5b0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5b5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5ba: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41f5c1u; native_call(m, m->esi);	/* 41f5bf: call esi */
	{ DWORD v_ = 0x303u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5c1: push 0x303 */
	{ DWORD v_ = 0x302u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5c6: push 0x302 */
	m->esp -= 4; M32(m->esp) = 0x41f5d1u; native_call(m, M32(0x4a91ecu));	/* 41f5cb: call dword ptr [0x4a91ec] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5d1: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41f5d8u; native_call(m, 0x41ef90u);	/* 41f5d3: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f5d8: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x41f5e1u; native_call(m, M32(0x4a9218u));	/* 41f5db: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5e1: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41f5e8u; native_call(m, m->ebx);	/* 41f5e6: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5e8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5ed: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5f2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f5f7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41f5feu; native_call(m, m->esi);	/* 41f5fc: call esi */
	m->eax = M32((DWORD)(0x76d3f0u));	/* 41f5fe: mov eax, dword ptr [0x76d3f0] */
	m->ecx = m->eax;	/* 41f603: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41f605: and ecx, 0x800001ff */
	if (!m->sf) goto L_41f615;	/* 41f60b: jns 0x41f615 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41f60d: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41f60e: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 41f614: inc ecx */
L_41f615:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 41f615: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41f616: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f61c: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41f61d: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 41f61f: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41f625: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 41f628: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x41f631u; native_call(m, 0x4566c0u);	/* 41f62c: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f631: push 7 */
	m->esp -= 4; M32(m->esp) = 0x41f639u; native_call(m, M32(0x4a921cu));	/* 41f633: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a9208u));	/* 41f639: mov esi, dword ptr [0x4a9208] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f63f: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f640: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f641: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f642: push edi */
	m->esp -= 4; M32(m->esp) = 0x41f645u; native_call(m, m->esi);	/* 41f643: call esi */
	{ DWORD v_ = 0x3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f645: push 0x3c */
	{ DWORD v_ = 0xa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f647: push 0xa0 */
	m->esp -= 4; M32(m->esp) = 0x41f651u; native_call(m, 0x41ef60u);	/* 41f64c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f651: add esp, 8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f654: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f655: push edi */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f656: push 0x3ff00000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f65b: push edi */
	m->esp -= 4; M32(m->esp) = 0x41f65eu; native_call(m, m->esi);	/* 41f65c: call esi */
	{ DWORD v_ = 0x3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f65e: push 0x3c */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f660: push 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x41f66au; native_call(m, 0x41ef60u);	/* 41f665: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f66a: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f66d: push 0x3ff00000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f672: push edi */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f673: push 0x3ff00000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f678: push edi */
	m->esp -= 4; M32(m->esp) = 0x41f67bu; native_call(m, m->esi);	/* 41f679: call esi */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f67b: push 0x13c */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f680: push 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x41f68au; native_call(m, 0x41ef60u);	/* 41f685: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f68a: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f68d: push 0x3ff00000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f692: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f693: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f694: push edi */
	m->esp -= 4; M32(m->esp) = 0x41f697u; native_call(m, m->esi);	/* 41f695: call esi */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f697: push 0x13c */
	{ DWORD v_ = 0xa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f69c: push 0xa0 */
	m->esp -= 4; M32(m->esp) = 0x41f6a6u; native_call(m, 0x41ef60u);	/* 41f6a1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f6a6: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x41f6afu; native_call(m, M32(0x4a9220u));	/* 41f6a9: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6af: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41f6bau; native_call(m, M32(0x4a922cu));	/* 41f6b4: call dword ptr [0x4a922c] */
	m->esp -= 4; M32(m->esp) = 0x41f6c0u; native_call(m, M32(0x4a91f0u));	/* 41f6ba: call dword ptr [0x4a91f0] */
	m->eax = M32((DWORD)(0x76d480u));	/* 41f6c0: mov eax, dword ptr [0x76d480] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6c5: push eax */
	m->esp -= 4; M32(m->esp) = 0x41f6ccu; native_call(m, M32(0x4a9028u));	/* 41f6c6: call dword ptr [0x4a9028] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6cc: push 0x3f800000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6d1: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6d2: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6d3: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6d8: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41f6e2u; native_call(m, 0x41f0e0u);	/* 41f6dd: call 0x41f0e0 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 41f6e2: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x41f6edu; native_call(m, 0x41f100u);	/* 41f6e8: call 0x41f100 */
	{ DWORD v_ = 0x40140000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6ed: push 0x40140000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f6f2: push edi */
	m->esp -= 4; M32(m->esp) = 0x41f6f8u; native_call(m, 0x41e730u);	/* 41f6f3: call 0x41e730 */
	m->esp -= 4; M32(m->esp) = 0x41f6fdu; native_call(m, 0x4411e0u);	/* 41f6f8: call 0x4411e0 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 41f6fd: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x41f708u; native_call(m, 0x41f100u);	/* 41f703: call 0x41f100 */
	{ DWORD v_ = 0x40000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f708: push 0x40000000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f70d: push edi */
	m->esp -= 4; M32(m->esp) = 0x41f713u; native_call(m, 0x41e730u);	/* 41f70e: call 0x41e730 */
	m->esp -= 4; M32(m->esp) = 0x41f718u; native_call(m, 0x430ca0u);	/* 41f713: call 0x430ca0 */
	m->esp -= 4; M32(m->esp) = 0x41f71du; native_call(m, 0x430bf0u);	/* 41f718: call 0x430bf0 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 41f71d: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x41f728u; native_call(m, 0x41f100u);	/* 41f723: call 0x41f100 */
	m->esp -= 4; M32(m->esp) = 0x41f72du; native_call(m, 0x48b420u);	/* 41f728: call 0x48b420 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 41f72d: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x41f738u; native_call(m, 0x41f100u);	/* 41f733: call 0x41f100 */
	m->eax = 0xc8u;	/* 41f738: mov eax, 0xc8 */
	{ DWORD v_ = 0x4b01ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f73d: push 0x4b01cc */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 41f742: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 41f747: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x4df01cu)) = m->edi;	/* 41f74c: mov dword ptr [0x4df01c], edi */
	M32((DWORD)(0x4e0458u)) = m->edi;	/* 41f752: mov dword ptr [0x4e0458], edi */
	M32((DWORD)(0x680370u)) = m->edi;	/* 41f758: mov dword ptr [0x680370], edi */
	M32((DWORD)(0x4df8e0u)) = m->edi;	/* 41f75e: mov dword ptr [0x4df8e0], edi */
	M32((DWORD)(0x4df03cu)) = m->edi;	/* 41f764: mov dword ptr [0x4df03c], edi */
	M32((DWORD)(0x4df910u)) = 0x0u;	/* 41f76a: mov dword ptr [0x4df910], 0 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 41f774: mov dword ptr [0x4e14fc], 0 */
	M32((DWORD)(0x4deda8u)) = 0x3f800000u;	/* 41f77e: mov dword ptr [0x4deda8], 0x3f800000 */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 41f788: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 41f792: mov dword ptr [0x4df010], 0x3f800000 */
	M32((DWORD)(0x4dda48u)) = 0x0u;	/* 41f79c: mov dword ptr [0x4dda48], 0 */
	M32((DWORD)(0x4ded68u)) = 0x136u;	/* 41f7a6: mov dword ptr [0x4ded68], 0x136 */
	M32((DWORD)(0x4ded6cu)) = 0xe6u;	/* 41f7b0: mov dword ptr [0x4ded6c], 0xe6 */
	m->esp -= 4; M32(m->esp) = 0x41f7bfu; native_call(m, 0x457150u);	/* 41f7ba: call 0x457150 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f7bf: add esp, 0x28 */
	M32((DWORD)(0x4dd560u)) = 0x0u;	/* 41f7c2: mov dword ptr [0x4dd560], 0 */
	M32((DWORD)(0x4dd564u)) = 0x0u;	/* 41f7cc: mov dword ptr [0x4dd564], 0 */
	M32((DWORD)(0x4dd0a8u)) = 0x0u;	/* 41f7d6: mov dword ptr [0x4dd0a8], 0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 41f7e0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41f7e1: pop esi */
	M32((DWORD)(0x4dd0acu)) = 0x0u;	/* 41f7e2: mov dword ptr [0x4dd0ac], 0 */
	M32((DWORD)(0x4dd080u)) = 0x0u;	/* 41f7ec: mov dword ptr [0x4dd080], 0 */
	M32((DWORD)(0x4dd084u)) = 0x0u;	/* 41f7f6: mov dword ptr [0x4dd084], 0 */
	M32((DWORD)(0x4dd0c8u)) = 0x0u;	/* 41f800: mov dword ptr [0x4dd0c8], 0 */
	M32((DWORD)(0x4dd0ccu)) = 0x0u;	/* 41f80a: mov dword ptr [0x4dd0cc], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 41f814: pop ebx */
	m->esp += 4 + 0; return;	/* 41f815: ret  */
}

/* chat_editSubclass (0x440840), lifted by tools/lift.py */
static void lift_440840(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 440840: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 440841: mov ebx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 440845: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 440846: mov ebp, dword ptr [esp + 0x10] */
	m->eax = m->ebp;	/* 44084a: mov eax, ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44084c: push esi */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 44084d: mov esi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 440851: sub eax, 0x100 */
	if (m->zf) goto L_4408ac;	/* 440856: je 0x4408ac */
	{ DWORD a_ = m->eax, b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 440858: sub eax, 0x13 */
	if (!m->zf) goto L_440882;	/* 44085b: jne 0x440882 */
	{ DWORD a_ = m->ebx, b_ = 0x29au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44085d: cmp ebx, 0x29a */
	if (m->zf) goto L_44089d;	/* 440863: je 0x44089d */
	{ DWORD a_ = m->ebx, b_ = 0x115cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 440865: cmp ebx, 0x115c */
	if (!m->zf) goto L_440882;	/* 44086b: jne 0x440882 */
	m->eax = M32((DWORD)(0x9dd84cu));	/* 44086d: mov eax, dword ptr [0x9dd84c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 440872: test eax, eax */
	if (m->zf) goto L_440882;	/* 440874: je 0x440882 */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 440876: push 0x65 */
	{ DWORD v_ = 0x18u; m->esp -= 4; M32(m->esp) = v_; }	/* 440878: push 0x18 */
L_44087a:
	m->esp -= 4; M32(m->esp) = 0x44087fu; native_call(m, 0x4521c0u);	/* 44087a: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44087f: add esp, 8 */
L_440882:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 440882: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(0x9dd868u));	/* 440886: mov ecx, dword ptr [0x9dd868] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44088c: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44088d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44088e: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44088f: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 440890: push ecx */
	m->esp -= 4; M32(m->esp) = 0x440897u; native_call(m, M32(0x4a930cu));	/* 440891: call dword ptr [0x4a930c] */
	m->esi = M32(m->esp); m->esp += 4;	/* 440897: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 440898: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 440899: pop ebx */
	m->esp += 4 + 16; return;	/* 44089a: ret 0x10 */
L_44089d:
	{ DWORD a_ = M32((DWORD)(0x4dbbf4u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44089d: cmp dword ptr [0x4dbbf4], 2 */
	if (!m->zf) goto L_440882;	/* 4408a4: jne 0x440882 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4408a6: push 0x64 */
	{ DWORD v_ = 0x17u; m->esp -= 4; M32(m->esp) = v_; }	/* 4408a8: push 0x17 */
	goto L_44087a;	/* 4408aa: jmp 0x44087a */
L_4408ac:
	m->eax = (DWORD)(m->ebx + 0xfffffff7u);	/* 4408ac: lea eax, [ebx - 9] */
	{ DWORD a_ = m->eax, b_ = 0x1cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4408af: cmp eax, 0x1c */
	if (!m->cf && !m->zf) goto L_440882;	/* 4408b2: ja 0x440882 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4408b4: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x4409f8u))) & 0xff) << 0);	/* 4408b6: mov cl, byte ptr [eax + 0x4409f8] */
	switch (m->ecx) { case 0: goto L_440972; case 1: goto L_4408c3; case 2: goto L_440932; case 3: goto L_4409db; case 4: goto L_440882; default: abort(); }	/* 4408bc: jmp dword ptr [ecx*4 + 0x4409e4] */
L_4408c3:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9da434u)));	/* 4408c3: fld dword ptr [0x9da434] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4408c9: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4408cf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4408d1: test ah, 0x41 */
	if (m->zf) goto L_440882;	/* 4408d4: je 0x440882 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4408d6: push edi */
	m->edi = M32((DWORD)(0x4a92ecu));	/* 4408d7: mov edi, dword ptr [0x4a92ec] */
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4408dd: push 0x9dc92c */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 4408e2: push 0x80 */
	{ DWORD v_ = 0xdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4408e7: push 0xd */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4408e9: push esi */
	m->esp -= 4; M32(m->esp) = 0x4408ecu; native_call(m, m->edi);	/* 4408ea: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4408ec: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4408ee: push 0 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4408f0: push 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4408f2: push esi */
	m->esp -= 4; M32(m->esp) = 0x4408f5u; native_call(m, m->edi);	/* 4408f3: call edi */
	m->edx = M32((DWORD)(0x9dd888u));	/* 4408f5: mov edx, dword ptr [0x9dd888] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4408fb: push edx */
	m->esp -= 4; M32(m->esp) = 0x440902u; native_call(m, M32(0x4a9344u));	/* 4408fc: call dword ptr [0x4a9344] */
	m->eax = M32((DWORD)(0x4ded18u));	/* 440902: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 440907: push eax */
	m->esp -= 4; M32(m->esp) = 0x44090eu; native_call(m, M32(0x4a935cu));	/* 440908: call dword ptr [0x4a935c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44090e: push 1 */
	m->esp -= 4; M32(m->esp) = 0x440915u; native_call(m, 0x431600u);	/* 440910: call 0x431600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440915: add esp, 4 */
	M32((DWORD)(0x9dd900u)) = 0x1u;	/* 440918: mov dword ptr [0x9dd900], 1 */
	M32((DWORD)(0x9dc428u)) = 0x14u;	/* 440922: mov dword ptr [0x9dc428], 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44092c: pop edi */
	goto L_440882;	/* 44092d: jmp 0x440882 */
L_440932:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 440932: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 440934: push 0 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 440936: push 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 440938: push esi */
	m->esp -= 4; M32(m->esp) = 0x44093fu; native_call(m, M32(0x4a92ecu));	/* 440939: call dword ptr [0x4a92ec] */
	m->ecx = M32((DWORD)(0x9dd888u));	/* 44093f: mov ecx, dword ptr [0x9dd888] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 440945: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44094cu; native_call(m, M32(0x4a9344u));	/* 440946: call dword ptr [0x4a9344] */
	m->edx = M32((DWORD)(0x4ded18u));	/* 44094c: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 440952: push edx */
	m->esp -= 4; M32(m->esp) = 0x440959u; native_call(m, M32(0x4a935cu));	/* 440953: call dword ptr [0x4a935c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 440959: push 0 */
	m->esp -= 4; M32(m->esp) = 0x440960u; native_call(m, 0x431600u);	/* 44095b: call 0x431600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440960: add esp, 4 */
	M32((DWORD)(0x9dd900u)) = 0x1u;	/* 440963: mov dword ptr [0x9dd900], 1 */
	goto L_440882;	/* 44096d: jmp 0x440882 */
L_440972:
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x320u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 440972: cmp dword ptr [0x76d3e8], 0x320 */
	if (!m->zf) goto L_440882;	/* 44097c: jne 0x440882 */
	m->eax = M32((DWORD)(0x9dd888u));	/* 440982: mov eax, dword ptr [0x9dd888] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 440987: push eax */
	m->esp -= 4; M32(m->esp) = 0x44098eu; native_call(m, M32(0x4a9344u));	/* 440988: call dword ptr [0x4a9344] */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 44098e: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 440994: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44099bu; native_call(m, M32(0x4a935cu));	/* 440995: call dword ptr [0x4a935c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44099b: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4409a2u; native_call(m, 0x431600u);	/* 44099d: call 0x431600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4409a2: add esp, 4 */
	M32((DWORD)(0x9dc428u)) = 0x14u;	/* 4409a5: mov dword ptr [0x9dc428], 0x14 */
	M32((DWORD)(0x9dd900u)) = 0x1u;	/* 4409af: mov dword ptr [0x9dd900], 1 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4409b9: push 0x10 */
	m->esp -= 4; M32(m->esp) = 0x4409c1u; native_call(m, M32(0x4a9338u));	/* 4409bb: call dword ptr [0x4a9338] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4409c1: xor edx, edx */
	{ DWORD a_ = (m->eax & 0xffff), b_ = (m->eax & 0xffff) & 0xffffu, r_ = a_ & b_; FLAGS(r_, 16); m->cf = 0; m->of = 0; }	/* 4409c3: test ax, ax */
	m->edx = (m->edx & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 4409c6: setge dl */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4409c9: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffff6u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4409ca: and edx, 0xfffffff6 */
	{ DWORD a_ = m->edx, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4409cd: add edx, 0x14 */
	M32((DWORD)(0x9dc428u)) = m->edx;	/* 4409d0: mov dword ptr [0x9dc428], edx */
	goto L_440882;	/* 4409d6: jmp 0x440882 */
L_4409db:
	m->esi = M32(m->esp); m->esp += 4;	/* 4409db: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4409dc: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4409dd: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4409df: pop ebx */
	m->esp += 4 + 16; return;	/* 4409e0: ret 0x10 */
}

/* sound_play3D (0x456ed0), lifted by tools/lift.py */
static void lift_456ed0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e80cu));	/* 456ed0: mov eax, dword ptr [0xa0e80c] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456ed5: sub esp, 0x24 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456ed8: test eax, eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 456eda: push ebp */
	if (m->zf) goto L_45706d;	/* 456edb: je 0x45706d */
	m->ebp = M32((DWORD)(m->esp + 0x2cu));	/* 456ee1: mov ebp, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->ebp*4 + 0xa0e02cu));	/* 456ee5: mov eax, dword ptr [ebp*4 + 0xa0e02c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456eec: test eax, eax */
	if (m->zf) goto L_45706d;	/* 456eee: je 0x45706d */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 456ef4: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 456ef8: mov ecx, dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 456efc: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 456efe: fsub dword ptr [ecx] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 456f00: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 456f04: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 456f07: fsub dword ptr [ecx + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 456f0a: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 456f0e: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 456f11: fsub dword ptr [ecx + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 456f14: mov ecx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 456f18: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x8u)) = m->ecx;	/* 456f1c: mov dword ptr [esp + 8], ecx */
	m->ecx = (DWORD)(m->esp + 0x4u);	/* 456f20: lea ecx, [esp + 4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 456f24: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 456f28: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 456f2c: mov dword ptr [esp + 4], eax */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 456f30: mov dword ptr [esp + 0xc], edx */
	m->esp -= 4; M32(m->esp) = 0x456f39u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 456f34: call 0x467760 */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 456f39: fst dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x3cu)); FPOP();	/* 456f3d: fcomp dword ptr [esp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 456f41: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 456f43: test ah, 1 */
	if (m->zf) goto L_45706d;	/* 456f46: je 0x45706d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 456f4c: fld dword ptr [esp + 0x3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 456f50: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 456f56: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 456f58: test ah, 0x41 */
	if (!m->zf) goto L_45706d;	/* 456f5b: jne 0x45706d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 456f61: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 456f65: fdiv dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(0xa0e66cu));	/* 456f69: mov eax, dword ptr [0xa0e66c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 456f6e: push ebx */
	{ DWORD a_ = m->eax, b_ = 0x2710u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 456f6f: add eax, 0x2710 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456f74: push esi */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 456f75: mov dword ptr [esp + 0x44], eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456f79: push edi */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 456f7a: fsubr dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x48u));	/* 456f80: fimul dword ptr [esp + 0x48] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 456f84: call 0x49ec14 */
	m->esi = m->eax;	/* 456f89: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = 0x2710u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 456f8b: sub esi, 0x2710 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456f91: test esi, esi */
	if (m->zf || m->sf != m->of) goto L_456f97;	/* 456f93: jle 0x456f97 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 456f95: xor esi, esi */
L_456f97:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 456f97: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7e0u));	/* 456f9b: fmul dword ptr [0xa0e7e0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 456fa1: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7dcu));	/* 456fa5: fmul dword ptr [0xa0e7dc] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 456fab: fsubp st(1) */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 456fad: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 456fb1: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7d8u));	/* 456fb5: fmul dword ptr [0xa0e7d8] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7e0u)));	/* 456fbb: fld dword ptr [0xa0e7e0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 456fc1: fmul dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 456fc5: mov ecx, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 456fc9: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 456fcd: lea ecx, [esp + 0x1c] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 456fd1: fsubp st(1) */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 456fd3: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7dcu)));	/* 456fd7: fld dword ptr [0xa0e7dc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 456fdd: fmul dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 456fe1: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0xa0e7d8u));	/* 456fe5: fmul dword ptr [0xa0e7d8] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 456feb: mov edx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 456fef: mov dword ptr [esp + 0x20], edx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 456ff3: fsubp st(1) */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 456ff5: fstp dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 456ff9: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 456ffd: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x457006u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 457001: call 0x467760 */
	m->eax = M32((DWORD)(0x4e0c9cu));	/* 457006: mov eax, dword ptr [0x4e0c9c] */
	ST(0) = ST(0); FPOP();	/* 45700b: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 45700d: fld dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 457011: test eax, eax */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 457013: mov eax, dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 457017: fmul dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 45701a: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 45701e: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 457021: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 457023: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 457027: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 457029: faddp st(1) */
	if (!m->zf) goto L_457035;	/* 45702b: jne 0x457035 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9700u));	/* 45702d: fmul dword ptr [0x4a9700] */
	goto L_45703b;	/* 457033: jmp 0x45703b */
L_457035:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a96fcu));	/* 457035: fmul dword ptr [0x4a96fc] */
L_45703b:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45703b: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->ebp*4 + 0xa0e02cu));	/* 457040: mov ecx, dword ptr [ebp*4 + 0xa0e02c] */
	m->edi = m->eax;	/* 457047: mov edi, eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 457049: xor ebx, ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45704b: push esi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45704c: test edi, edi */
	m->ebx = (m->ebx & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 45704e: setg bl */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 457051: push ecx */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 457052: inc ebx */
	m->esp -= 4; M32(m->esp) = 0x457058u; native_call(m, 0x467db0u);	/* 457053: call 0x467db0 */
	m->edx = M32((DWORD)(m->ebp*4 + 0xa0e02cu));	/* 457058: mov edx, dword ptr [ebp*4 + 0xa0e02c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45705f: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 457060: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 457061: push edx */
	m->esp -= 4; M32(m->esp) = 0x457067u; native_call(m, 0x467dd0u);	/* 457062: call 0x467dd0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 457067: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45706a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45706b: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45706c: pop ebx */
L_45706d:
	m->ebp = M32(m->esp); m->esp += 4;	/* 45706d: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45706e: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 457071: ret  */
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
