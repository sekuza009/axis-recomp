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

static void lift_44ae10(X86 *m);
static void lift_4950a0(X86 *m);
static void lift_41f8d0(X86 *m);
static void lift_44ad60(X86 *m);

/* text_drawSized (0x44ad60), lifted by tools/lift.py */
static void lift_44ad60(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 44ad60: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = 0xfffffffbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ad64: add eax, -5 */
	{ DWORD a_ = m->eax, b_ = 0x1bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ad67: cmp eax, 0x1b */
	if (!m->cf && !m->zf) goto L_44adda;	/* 44ad6a: ja 0x44adda */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44ad6c: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x44adf0u))) & 0xff) << 0);	/* 44ad6e: mov cl, byte ptr [eax + 0x44adf0] */
	switch (m->ecx) { case 0: goto L_44ad7b; case 1: goto L_44ad93; case 2: goto L_44adab; case 3: goto L_44adc3; case 4: goto L_44adda; default: abort(); }	/* 44ad74: jmp dword ptr [ecx*4 + 0x44addc] */
L_44ad7b:
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 44ad7b: mov edx, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 44ad7f: mov eax, dword ptr [esp + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 44ad83: mov ecx, dword ptr [esp + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ad87: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ad88: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ad89: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44ad8fu; native_call(m, 0x403170u);	/* 44ad8a: call 0x403170 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ad8f: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 44ad92: ret  */
L_44ad93:
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 44ad93: mov edx, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 44ad97: mov eax, dword ptr [esp + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 44ad9b: mov ecx, dword ptr [esp + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ad9f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ada0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ada1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44ada7u; native_call(m, 0x402620u);	/* 44ada2: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ada7: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 44adaa: ret  */
L_44adab:
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 44adab: mov edx, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 44adaf: mov eax, dword ptr [esp + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 44adb3: mov ecx, dword ptr [esp + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44adb7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44adb8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44adb9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44adbfu; native_call(m, 0x4028b0u);	/* 44adba: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44adbf: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 44adc2: ret  */
L_44adc3:
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 44adc3: mov edx, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 44adc7: mov eax, dword ptr [esp + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 44adcb: mov ecx, dword ptr [esp + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44adcf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44add0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44add1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44add7u; native_call(m, 0x402c90u);	/* 44add2: call 0x402c90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44add7: add esp, 0xc */
L_44adda:
	m->esp += 4 + 0; return;	/* 44adda: ret  */
}

/* hud_44ae10 (0x44ae10), lifted by tools/lift.py */
static void lift_44ae10(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 44ae10: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0xfffffffbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ae14: add eax, -5 */
	{ DWORD a_ = m->eax, b_ = 0x1bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ae17: cmp eax, 0x1b */
	if (!m->cf && !m->zf) goto L_44aea2;	/* 44ae1a: ja 0x44aea2 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44ae20: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x44aeb8u))) & 0xff) << 0);	/* 44ae22: mov cl, byte ptr [eax + 0x44aeb8] */
	switch (m->ecx) { case 0: goto L_44ae2f; case 1: goto L_44ae4c; case 2: goto L_44ae69; case 3: goto L_44ae86; case 4: goto L_44aea2; default: abort(); }	/* 44ae28: jmp dword ptr [ecx*4 + 0x44aea4] */
L_44ae2f:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 44ae2f: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 44ae33: mov eax, dword ptr [esp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 44ae37: mov ecx, dword ptr [esp + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae3b: push edx */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 44ae3c: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae40: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae41: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae42: push edx */
	m->esp -= 4; M32(m->esp) = 0x44ae48u; native_call(m, 0x403210u);	/* 44ae43: call 0x403210 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ae48: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 44ae4b: ret  */
L_44ae4c:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 44ae4c: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 44ae50: mov ecx, dword ptr [esp + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 44ae54: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae58: push eax */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 44ae59: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae5d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae5e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae5f: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ae65u; native_call(m, 0x402740u);	/* 44ae60: call 0x402740 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ae65: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 44ae68: ret  */
L_44ae69:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 44ae69: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 44ae6d: mov edx, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 44ae71: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae75: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 44ae76: mov ecx, dword ptr [esp + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae7a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae7b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae7c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44ae82u; native_call(m, 0x4029d0u);	/* 44ae7d: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ae82: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 44ae85: ret  */
L_44ae86:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 44ae86: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 44ae8a: mov eax, dword ptr [esp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 44ae8e: mov ecx, dword ptr [esp + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae92: push edx */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 44ae93: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae97: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae98: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ae99: push edx */
	m->esp -= 4; M32(m->esp) = 0x44ae9fu; native_call(m, 0x402db0u);	/* 44ae9a: call 0x402db0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ae9f: add esp, 0x10 */
L_44aea2:
	m->esp += 4 + 0; return;	/* 44aea2: ret  */
}

/* hud_4950a0 (0x4950a0), lifted by tools/lift.py */
static void lift_4950a0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4950a0: push ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4950a1: fild dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4950a5: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4950aeu; native_call(m, 0x4685c0u);	/* 4950a9: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4950ae: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4950b2: fild dword ptr [esp + 0x14] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 4950b6: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x0u));	/* 4950bc: fdivr dword ptr [esp] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4950c0: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4950c5: fild dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4950c9: push eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 4950ca: fstp dword ptr [esp + 0x14] */
	m->esp -= 4; M32(m->esp) = 0x4950d3u; native_call(m, 0x4685b0u);	/* 4950ce: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4950d3: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 4950d7: fild dword ptr [esp + 0x18] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 4950db: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 4950e1: fdivr dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4950e5: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4950ea: fild dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4950ee: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4950ef: fstp dword ptr [esp + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x4950f8u; native_call(m, 0x4685c0u);	/* 4950f3: call 0x4685c0 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4950f8: mov dword ptr [esp + 0x1c], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 4950fc: fild dword ptr [esp + 0x1c] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4aa4acu));	/* 495100: fdivr dword ptr [0x4aa4ac] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 495106: fdivr dword ptr [esp + 0x18] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49510a: call 0x49ec14 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 49510f: fild dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495113: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 495114: fstp dword ptr [esp + 0x1c] */
	m->esp -= 4; M32(m->esp) = 0x49511du; native_call(m, 0x4685b0u);	/* 495118: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 49511d: mov dword ptr [esp + 0x20], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 495121: fild dword ptr [esp + 0x20] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 495125: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 49512b: fdivr dword ptr [esp + 0x1c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49512f: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495134: push eax */
	m->esp -= 4; M32(m->esp) = 0x49513au; native_call(m, 0x46bd60u);	/* 495135: call 0x46bd60 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49513a: add esp, 0x14 */
	m->esp += 4 + 0; return;	/* 49513d: ret  */
}

/* menu_drawVersion (0x41f8d0), lifted by tools/lift.py */
static void lift_41f8d0(X86 *m)
{
	m->eax = M32((DWORD)(0x4df01cu));	/* 41f8d0: mov eax, dword ptr [0x4df01c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41f8d5: test eax, eax */
	if (m->zf) goto L_41f8fd;	/* 41f8d7: je 0x41f8fd */
	m->eax = M32((DWORD)(0x4e0458u));	/* 41f8d9: mov eax, dword ptr [0x4e0458] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 41f8de: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x13u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f8df: cmp eax, 0x13 */
	M32((DWORD)(0x4e0458u)) = m->eax;	/* 41f8e2: mov dword ptr [0x4e0458], eax */
	if (m->sf != m->of) goto L_41f8fd;	/* 41f8e7: jl 0x41f8fd */
	M32((DWORD)(0x76d3e8u)) = 0xd2u;	/* 41f8e9: mov dword ptr [0x76d3e8], 0xd2 */
	M32((DWORD)(0x9da434u)) = 0x40a00000u;	/* 41f8f3: mov dword ptr [0x9da434], 0x40a00000 */
L_41f8fd:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f8fd: push edi */
	m->esp -= 4; M32(m->esp) = 0x41f903u; native_call(m, 0x441740u);	/* 41f8fe: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x41f908u; native_call(m, 0x41f908u + M32(0x41f904u));	/* 0x429170 unless the patch DLL retargets it */	/* 41f903: call 0x429170 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f908: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f90d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f912: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f917: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f91c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41f926u; native_call(m, 0x41f0e0u);	/* 41f921: call 0x41f0e0 */
	{ DWORD v_ = 0x4b0474u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f926: push 0x4b0474 */
	{ DWORD v_ = 0x1d6u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f92b: push 0x1d6 */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f930: push 5 */
	m->esp -= 4; M32(m->esp) = 0x41f937u; native_call(m, 0x403170u);	/* 41f932: call 0x403170 */
	m->edi = 0x4b0384u;	/* 41f937: mov edi, 0x4b0384 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41f93c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 41f93f: xor eax, eax */
	{ DWORD v_ = 0x4b0384u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f941: push 0x4b0384 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 41f946: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 41f948: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41f94a: dec ecx */
	m->eax = 0x69u;	/* 41f94b: mov eax, 0x69 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41f950: sub eax, ecx */
	{ DWORD v_ = 0x1d6u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f952: push 0x1d6 */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 41f957: lea eax, [eax + eax*2] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41f95a: shl eax, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f95c: push eax */
	m->esp -= 4; M32(m->esp) = 0x41f962u; native_call(m, 0x403170u);	/* 41f95d: call 0x403170 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f962: add esp, 0x2c */
	m->edi = M32(m->esp); m->esp += 4;	/* 41f965: pop edi */
	m->esp += 4 + 0; return;	/* 41f966: ret  */
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
