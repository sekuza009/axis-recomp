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

static void lift_4351c0(X86 *m);
static void lift_405cf0(X86 *m);
static void lift_461250(X86 *m);

/* armc_461250 (0x461250), lifted by tools/lift.py */
static void lift_461250(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 461250: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 461254: push esi */
	m->esi = m->ecx;	/* 461255: mov esi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 461257: push eax */
	m->esp -= 4; M32(m->esp) = 0x46125du; native_call(m, 0x461320u);	/* 461258: call 0x461320 */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 46125d: mov ecx, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 461261: push ecx */
	m->ecx = m->esi;	/* 461262: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x461269u; native_call(m, 0x461370u);	/* 461264: call 0x461370 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 461269: mov edx, dword ptr [esp + 0x10] */
	m->ecx = m->esi;	/* 46126d: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46126f: push edx */
	m->esp -= 4; M32(m->esp) = 0x461275u; native_call(m, 0x4613a0u);	/* 461270: call 0x4613a0 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 461275: mov eax, dword ptr [esp + 0x14] */
	m->ecx = m->esi;	/* 461279: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46127b: push eax */
	m->esp -= 4; M32(m->esp) = 0x461281u; native_call(m, 0x4613d0u);	/* 46127c: call 0x4613d0 */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 461281: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 461285: push ecx */
	m->ecx = m->esi;	/* 461286: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x46128du; native_call(m, 0x461410u);	/* 461288: call 0x461410 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 46128d: mov edx, dword ptr [esp + 0x1c] */
	m->ecx = m->esi;	/* 461291: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 461293: push edx */
	m->esp -= 4; M32(m->esp) = 0x461299u; native_call(m, 0x461450u);	/* 461294: call 0x461450 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 461299: mov eax, dword ptr [esp + 0x20] */
	m->ecx = m->esi;	/* 46129d: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46129f: push eax */
	m->esp -= 4; M32(m->esp) = 0x4612a5u; native_call(m, 0x461490u);	/* 4612a0: call 0x461490 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4612a5: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4612a9: push ecx */
	m->ecx = m->esi;	/* 4612aa: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4612b1u; native_call(m, 0x4614d0u);	/* 4612ac: call 0x4614d0 */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 4612b1: mov edx, dword ptr [esp + 0x28] */
	m->ecx = m->esi;	/* 4612b5: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4612b7: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4612b8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4612bfu; native_call(m, 0x461510u);	/* 4612ba: call 0x461510 */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4612bf: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = m->esi;	/* 4612c3: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4612c5: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4612c6: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4612cdu; native_call(m, 0x461510u);	/* 4612c8: call 0x461510 */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4612cd: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4612d1: push ecx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4612d2: push 2 */
	m->ecx = m->esi;	/* 4612d4: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4612dbu; native_call(m, 0x461510u);	/* 4612d6: call 0x461510 */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 4612db: mov edx, dword ptr [esp + 0x34] */
	m->ecx = m->esi;	/* 4612df: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4612e1: push edx */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 4612e2: push 3 */
	m->esp -= 4; M32(m->esp) = 0x4612e9u; native_call(m, 0x461510u);	/* 4612e4: call 0x461510 */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 4612e9: mov eax, dword ptr [esp + 0x38] */
	m->ecx = m->esi;	/* 4612ed: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4612ef: push eax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4612f0: push 4 */
	m->esp -= 4; M32(m->esp) = 0x4612f7u; native_call(m, 0x461510u);	/* 4612f2: call 0x461510 */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 4612f7: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4612fb: push ecx */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 4612fc: push 5 */
	m->ecx = m->esi;	/* 4612fe: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x461305u; native_call(m, 0x461510u);	/* 461300: call 0x461510 */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 461305: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46130b: test eax, eax */
	if (m->sf != m->of) goto L_46131b;	/* 46130d: jl 0x46131b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46130f: push eax */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 461310: lea ecx, [esi + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x46131bu; native_call(m, 0x474390u);	/* 461316: call 0x474390 */
L_46131b:
	m->esi = M32(m->esp); m->esp += 4;	/* 46131b: pop esi */
	m->esp += 4 + 56; return;	/* 46131c: ret 0x38 */
}

/* lobby_checkReservedName3 (0x4351c0), lifted by tools/lift.py */
static void lift_4351c0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4351c0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4351c1: push esi */
	m->esp -= 4; M32(m->esp) = 0x4351c7u; native_call(m, 0x433640u);	/* 4351c2: call 0x433640 */
	m->esi = 0x4ad554u;	/* 4351c7: mov esi, 0x4ad554 */
	m->eax = 0x5b1b30u;	/* 4351cc: mov eax, 0x5b1b30 */
L_4351d1:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4351d1: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4351d3: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4351d5: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4351d7: cmp dl, bl */
	if (!m->zf) goto L_4351f9;	/* 4351d9: jne 0x4351f9 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4351db: test cl, cl */
	if (m->zf) goto L_4351f5;	/* 4351dd: je 0x4351f5 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4351df: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4351e2: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4351e5: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4351e7: cmp dl, bl */
	if (!m->zf) goto L_4351f9;	/* 4351e9: jne 0x4351f9 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4351eb: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4351ee: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4351f1: test cl, cl */
	if (!m->zf) goto L_4351d1;	/* 4351f3: jne 0x4351d1 */
L_4351f5:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4351f5: xor eax, eax */
	goto L_4351fe;	/* 4351f7: jmp 0x4351fe */
L_4351f9:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4351f9: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4351fb: sbb eax, -1 */
L_4351fe:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4351fe: test eax, eax */
	if (m->zf) goto L_4352b7;	/* 435200: je 0x4352b7 */
	m->esi = 0x4ad548u;	/* 435206: mov esi, 0x4ad548 */
	m->eax = 0x5b1b30u;	/* 43520b: mov eax, 0x5b1b30 */
L_435210:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 435210: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 435212: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435214: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435216: cmp dl, bl */
	if (!m->zf) goto L_435238;	/* 435218: jne 0x435238 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43521a: test cl, cl */
	if (m->zf) goto L_435234;	/* 43521c: je 0x435234 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 43521e: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 435221: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435224: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435226: cmp dl, bl */
	if (!m->zf) goto L_435238;	/* 435228: jne 0x435238 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43522a: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43522d: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435230: test cl, cl */
	if (!m->zf) goto L_435210;	/* 435232: jne 0x435210 */
L_435234:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 435234: xor eax, eax */
	goto L_43523d;	/* 435236: jmp 0x43523d */
L_435238:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 435238: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43523a: sbb eax, -1 */
L_43523d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43523d: test eax, eax */
	if (m->zf) goto L_4352b7;	/* 43523f: je 0x4352b7 */
	m->esi = 0x4ad53cu;	/* 435241: mov esi, 0x4ad53c */
	m->eax = 0x5b1b30u;	/* 435246: mov eax, 0x5b1b30 */
L_43524b:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 43524b: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 43524d: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43524f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435251: cmp dl, bl */
	if (!m->zf) goto L_435273;	/* 435253: jne 0x435273 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435255: test cl, cl */
	if (m->zf) goto L_43526f;	/* 435257: je 0x43526f */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 435259: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 43525c: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43525f: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435261: cmp dl, bl */
	if (!m->zf) goto L_435273;	/* 435263: jne 0x435273 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 435265: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 435268: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43526b: test cl, cl */
	if (!m->zf) goto L_43524b;	/* 43526d: jne 0x43524b */
L_43526f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43526f: xor eax, eax */
	goto L_435278;	/* 435271: jmp 0x435278 */
L_435273:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 435273: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 435275: sbb eax, -1 */
L_435278:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435278: test eax, eax */
	if (m->zf) goto L_4352b7;	/* 43527a: je 0x4352b7 */
	m->esi = 0x4ad530u;	/* 43527c: mov esi, 0x4ad530 */
	m->eax = 0x5b1b30u;	/* 435281: mov eax, 0x5b1b30 */
L_435286:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 435286: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 435288: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43528a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43528c: cmp dl, bl */
	if (!m->zf) goto L_4352ae;	/* 43528e: jne 0x4352ae */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435290: test cl, cl */
	if (m->zf) goto L_4352aa;	/* 435292: je 0x4352aa */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 435294: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 435297: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43529a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43529c: cmp dl, bl */
	if (!m->zf) goto L_4352ae;	/* 43529e: jne 0x4352ae */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4352a0: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4352a3: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4352a6: test cl, cl */
	if (!m->zf) goto L_435286;	/* 4352a8: jne 0x435286 */
L_4352aa:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4352aa: xor eax, eax */
	goto L_4352b3;	/* 4352ac: jmp 0x4352b3 */
L_4352ae:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4352ae: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4352b0: sbb eax, -1 */
L_4352b3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4352b3: test eax, eax */
	if (!m->zf) goto L_4352be;	/* 4352b5: jne 0x4352be */
L_4352b7:
	M8((DWORD)(0x5b1b50u)) = (BYTE)(0x18u);	/* 4352b7: mov byte ptr [0x5b1b50], 0x18 */
L_4352be:
	m->esi = 0x4ad524u;	/* 4352be: mov esi, 0x4ad524 */
	m->eax = 0x5b1b30u;	/* 4352c3: mov eax, 0x5b1b30 */
L_4352c8:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4352c8: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4352ca: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4352cc: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4352ce: cmp dl, bl */
	if (!m->zf) goto L_4352f0;	/* 4352d0: jne 0x4352f0 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4352d2: test cl, cl */
	if (m->zf) goto L_4352ec;	/* 4352d4: je 0x4352ec */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4352d6: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4352d9: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4352dc: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4352de: cmp dl, bl */
	if (!m->zf) goto L_4352f0;	/* 4352e0: jne 0x4352f0 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4352e2: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4352e5: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4352e8: test cl, cl */
	if (!m->zf) goto L_4352c8;	/* 4352ea: jne 0x4352c8 */
L_4352ec:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4352ec: xor eax, eax */
	goto L_4352f5;	/* 4352ee: jmp 0x4352f5 */
L_4352f0:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4352f0: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4352f2: sbb eax, -1 */
L_4352f5:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4352f5: test eax, eax */
	if (m->zf) goto L_4353ae;	/* 4352f7: je 0x4353ae */
	m->esi = 0x4ad514u;	/* 4352fd: mov esi, 0x4ad514 */
	m->eax = 0x5b1b30u;	/* 435302: mov eax, 0x5b1b30 */
L_435307:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 435307: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 435309: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43530b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43530d: cmp dl, bl */
	if (!m->zf) goto L_43532f;	/* 43530f: jne 0x43532f */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435311: test cl, cl */
	if (m->zf) goto L_43532b;	/* 435313: je 0x43532b */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 435315: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 435318: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43531b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43531d: cmp dl, bl */
	if (!m->zf) goto L_43532f;	/* 43531f: jne 0x43532f */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 435321: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 435324: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435327: test cl, cl */
	if (!m->zf) goto L_435307;	/* 435329: jne 0x435307 */
L_43532b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43532b: xor eax, eax */
	goto L_435334;	/* 43532d: jmp 0x435334 */
L_43532f:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43532f: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 435331: sbb eax, -1 */
L_435334:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435334: test eax, eax */
	if (m->zf) goto L_4353ae;	/* 435336: je 0x4353ae */
	m->esi = 0x4ad504u;	/* 435338: mov esi, 0x4ad504 */
	m->eax = 0x5b1b30u;	/* 43533d: mov eax, 0x5b1b30 */
L_435342:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 435342: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 435344: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435346: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435348: cmp dl, bl */
	if (!m->zf) goto L_43536a;	/* 43534a: jne 0x43536a */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43534c: test cl, cl */
	if (m->zf) goto L_435366;	/* 43534e: je 0x435366 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 435350: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 435353: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435356: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435358: cmp dl, bl */
	if (!m->zf) goto L_43536a;	/* 43535a: jne 0x43536a */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43535c: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43535f: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435362: test cl, cl */
	if (!m->zf) goto L_435342;	/* 435364: jne 0x435342 */
L_435366:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 435366: xor eax, eax */
	goto L_43536f;	/* 435368: jmp 0x43536f */
L_43536a:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43536a: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43536c: sbb eax, -1 */
L_43536f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43536f: test eax, eax */
	if (m->zf) goto L_4353ae;	/* 435371: je 0x4353ae */
	m->esi = 0x4ad4f4u;	/* 435373: mov esi, 0x4ad4f4 */
	m->eax = 0x5b1b30u;	/* 435378: mov eax, 0x5b1b30 */
L_43537d:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 43537d: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 43537f: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435381: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435383: cmp dl, bl */
	if (!m->zf) goto L_4353a5;	/* 435385: jne 0x4353a5 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435387: test cl, cl */
	if (m->zf) goto L_4353a1;	/* 435389: je 0x4353a1 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 43538b: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 43538e: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435391: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435393: cmp dl, bl */
	if (!m->zf) goto L_4353a5;	/* 435395: jne 0x4353a5 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 435397: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43539a: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43539d: test cl, cl */
	if (!m->zf) goto L_43537d;	/* 43539f: jne 0x43537d */
L_4353a1:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4353a1: xor eax, eax */
	goto L_4353aa;	/* 4353a3: jmp 0x4353aa */
L_4353a5:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4353a5: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4353a7: sbb eax, -1 */
L_4353aa:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4353aa: test eax, eax */
	if (!m->zf) goto L_4353b5;	/* 4353ac: jne 0x4353b5 */
L_4353ae:
	M8((DWORD)(0x5b1b50u)) = (BYTE)(0x16u);	/* 4353ae: mov byte ptr [0x5b1b50], 0x16 */
L_4353b5:
	m->esi = 0x4ad4e8u;	/* 4353b5: mov esi, 0x4ad4e8 */
	m->eax = 0x5b1b30u;	/* 4353ba: mov eax, 0x5b1b30 */
L_4353bf:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4353bf: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4353c1: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4353c3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4353c5: cmp dl, bl */
	if (!m->zf) goto L_4353e7;	/* 4353c7: jne 0x4353e7 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4353c9: test cl, cl */
	if (m->zf) goto L_4353e3;	/* 4353cb: je 0x4353e3 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 4353cd: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4353d0: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4353d3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4353d5: cmp dl, bl */
	if (!m->zf) goto L_4353e7;	/* 4353d7: jne 0x4353e7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4353d9: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4353dc: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4353df: test cl, cl */
	if (!m->zf) goto L_4353bf;	/* 4353e1: jne 0x4353bf */
L_4353e3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4353e3: xor eax, eax */
	goto L_4353ec;	/* 4353e5: jmp 0x4353ec */
L_4353e7:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4353e7: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4353e9: sbb eax, -1 */
L_4353ec:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4353ec: test eax, eax */
	if (m->zf) goto L_4354a5;	/* 4353ee: je 0x4354a5 */
	m->esi = 0x4ad4d8u;	/* 4353f4: mov esi, 0x4ad4d8 */
	m->eax = 0x5b1b30u;	/* 4353f9: mov eax, 0x5b1b30 */
L_4353fe:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4353fe: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 435400: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435402: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435404: cmp dl, bl */
	if (!m->zf) goto L_435426;	/* 435406: jne 0x435426 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435408: test cl, cl */
	if (m->zf) goto L_435422;	/* 43540a: je 0x435422 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 43540c: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 43540f: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435412: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 435414: cmp dl, bl */
	if (!m->zf) goto L_435426;	/* 435416: jne 0x435426 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 435418: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43541b: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43541e: test cl, cl */
	if (!m->zf) goto L_4353fe;	/* 435420: jne 0x4353fe */
L_435422:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 435422: xor eax, eax */
	goto L_43542b;	/* 435424: jmp 0x43542b */
L_435426:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 435426: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 435428: sbb eax, -1 */
L_43542b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43542b: test eax, eax */
	if (m->zf) goto L_4354a5;	/* 43542d: je 0x4354a5 */
	m->esi = 0x4ad4c8u;	/* 43542f: mov esi, 0x4ad4c8 */
	m->eax = 0x5b1b30u;	/* 435434: mov eax, 0x5b1b30 */
L_435439:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 435439: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 43543b: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43543d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43543f: cmp dl, bl */
	if (!m->zf) goto L_435461;	/* 435441: jne 0x435461 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435443: test cl, cl */
	if (m->zf) goto L_43545d;	/* 435445: je 0x43545d */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 435447: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 43544a: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 43544d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43544f: cmp dl, bl */
	if (!m->zf) goto L_435461;	/* 435451: jne 0x435461 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 435453: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 435456: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435459: test cl, cl */
	if (!m->zf) goto L_435439;	/* 43545b: jne 0x435439 */
L_43545d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43545d: xor eax, eax */
	goto L_435466;	/* 43545f: jmp 0x435466 */
L_435461:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 435461: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 435463: sbb eax, -1 */
L_435466:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435466: test eax, eax */
	if (m->zf) goto L_4354a5;	/* 435468: je 0x4354a5 */
	m->esi = 0x4ad4b8u;	/* 43546a: mov esi, 0x4ad4b8 */
	m->eax = 0x5b1b30u;	/* 43546f: mov eax, 0x5b1b30 */
L_435474:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 435474: mov dl, byte ptr [eax] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 435476: mov bl, byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435478: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43547a: cmp dl, bl */
	if (!m->zf) goto L_43549c;	/* 43547c: jne 0x43549c */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43547e: test cl, cl */
	if (m->zf) goto L_435498;	/* 435480: je 0x435498 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 435482: mov dl, byte ptr [eax + 1] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 435485: mov bl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 435488: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43548a: cmp dl, bl */
	if (!m->zf) goto L_43549c;	/* 43548c: jne 0x43549c */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43548e: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 435491: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 435494: test cl, cl */
	if (!m->zf) goto L_435474;	/* 435496: jne 0x435474 */
L_435498:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 435498: xor eax, eax */
	goto L_4354a1;	/* 43549a: jmp 0x4354a1 */
L_43549c:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43549c: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 43549e: sbb eax, -1 */
L_4354a1:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4354a1: test eax, eax */
	if (!m->zf) goto L_4354ac;	/* 4354a3: jne 0x4354ac */
L_4354a5:
	M8((DWORD)(0x5b1b50u)) = (BYTE)(0x17u);	/* 4354a5: mov byte ptr [0x5b1b50], 0x17 */
L_4354ac:
	m->eax = M32((DWORD)(0xa0b328u));	/* 4354ac: mov eax, dword ptr [0xa0b328] */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 4354b1: push 0x1e */
	{ DWORD a_ = m->eax, b_ = 0x43u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4354b3: add eax, 0x43 */
	{ DWORD v_ = 0x9dd570u; m->esp -= 4; M32(m->esp) = v_; }	/* 4354b6: push 0x9dd570 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4354bb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4354c1u; native_call(m, 0x49ea80u);	/* 4354bc: call 0x49ea80 */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 4354c1: mov ecx, dword ptr [0xa0b328] */
	m->esi = M32((DWORD)(0x4a911cu));	/* 4354c7: mov esi, dword ptr [0x4a911c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4354cd: add esp, 0xc */
	M8((DWORD)(m->ecx + 0x0u)) = (BYTE)(0x18u);	/* 4354d0: mov byte ptr [ecx], 0x18 */
	m->edx = M32((DWORD)(0xa0b328u));	/* 4354d3: mov edx, dword ptr [0xa0b328] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b52u))) & 0xff) << 0);	/* 4354d9: mov al, byte ptr [0x5b1b52] */
	{ DWORD v_ = 0x5b1b56u; m->esp -= 4; M32(m->esp) = v_; }	/* 4354de: push 0x5b1b56 */
	M8((DWORD)(m->edx + 0x67u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4354e3: mov byte ptr [edx + 0x67], al */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 4354e6: mov ecx, dword ptr [0xa0b328] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b55u))) & 0xff) << 0);	/* 4354ec: mov dl, byte ptr [0x5b1b55] */
	M8((DWORD)(m->ecx + 0x66u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4354f2: mov byte ptr [ecx + 0x66], dl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 4354f5: mov eax, dword ptr [0xa0b328] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b54u))) & 0xff) << 0);	/* 4354fa: mov cl, byte ptr [0x5b1b54] */
	M8((DWORD)(m->eax + 0x65u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 435500: mov byte ptr [eax + 0x65], cl */
	m->edx = M32((DWORD)(0xa0b328u));	/* 435503: mov edx, dword ptr [0xa0b328] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b53u))) & 0xff) << 0);	/* 435509: mov al, byte ptr [0x5b1b53] */
	M8((DWORD)(m->edx + 0x64u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 43550e: mov byte ptr [edx + 0x64], al */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 435511: mov ecx, dword ptr [0xa0b328] */
	M8((DWORD)(m->ecx + 0x63u)) = (BYTE)(0x1u);	/* 435517: mov byte ptr [ecx + 0x63], 1 */
	m->edx = M32((DWORD)(0xa0b328u));	/* 43551b: mov edx, dword ptr [0xa0b328] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b50u))) & 0xff) << 0);	/* 435521: mov al, byte ptr [0x5b1b50] */
	M8((DWORD)(m->edx + 0x61u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 435526: mov byte ptr [edx + 0x61], al */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 435529: mov ecx, dword ptr [0xa0b328] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b51u))) & 0xff) << 0);	/* 43552f: mov dl, byte ptr [0x5b1b51] */
	M8((DWORD)(m->ecx + 0x62u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 435535: mov byte ptr [ecx + 0x62], dl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 435538: mov eax, dword ptr [0xa0b328] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b5eu))) & 0xff) << 0);	/* 43553d: mov cl, byte ptr [0x5b1b5e] */
	M8((DWORD)(m->eax + 0x70u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 435543: mov byte ptr [eax + 0x70], cl */
	m->edx = M32((DWORD)(0xa0b328u));	/* 435546: mov edx, dword ptr [0xa0b328] */
	{ DWORD a_ = m->edx, b_ = 0x71u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43554c: add edx, 0x71 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43554f: push edx */
	m->esp -= 4; M32(m->esp) = 0x435552u; native_call(m, m->esi);	/* 435550: call esi */
	m->eax = M32((DWORD)(0xa0b328u));	/* 435552: mov eax, dword ptr [0xa0b328] */
	{ DWORD v_ = 0x5b1b30u; m->esp -= 4; M32(m->esp) = v_; }	/* 435557: push 0x5b1b30 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 43555c: inc eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43555d: push eax */
	m->esp -= 4; M32(m->esp) = 0x435560u; native_call(m, m->esi);	/* 43555e: call esi */
	m->esp -= 4; M32(m->esp) = 0x435565u; native_call(m, 0x4532e0u);	/* 435560: call 0x4532e0 */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 435565: mov ecx, dword ptr [0xa0b328] */
	{ DWORD v_ = 0xa0b43cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43556b: push 0xa0b43c */
	{ DWORD a_ = m->ecx, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 435570: add ecx, 0x33 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435573: push ecx */
	m->esp -= 4; M32(m->esp) = 0x435576u; native_call(m, m->esi);	/* 435574: call esi */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 435576: push 0x65 */
	{ DWORD v_ = 0x12u; m->esp -= 4; M32(m->esp) = v_; }	/* 435578: push 0x12 */
	M32((DWORD)(0x4dba88u)) = 0x1u;	/* 43557a: mov dword ptr [0x4dba88], 1 */
	M32((DWORD)(0x4ded60u)) = 0x2u;	/* 435584: mov dword ptr [0x4ded60], 2 */
	m->esp -= 4; M32(m->esp) = 0x435593u; native_call(m, 0x4521c0u);	/* 43558e: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435593: add esp, 8 */
	M32((DWORD)(0x4dbbf4u)) = 0x2u;	/* 435596: mov dword ptr [0x4dbbf4], 2 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4355a0: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4355a1: pop ebx */
	m->esp += 4 + 0; return;	/* 4355a2: ret  */
}

/* lobby_checkReservedName2 (0x405cf0), lifted by tools/lift.py */
static void lift_405cf0(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x405cf5u; native_call(m, 0x405140u);	/* 405cf0: call 0x405140 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 405cf5: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x405cfcu; native_call(m, 0x451b80u);	/* 405cf7: call 0x451b80 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405cfc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405cff: test eax, eax */
	if (!m->zf) goto L_405d10;	/* 405d01: jne 0x405d10 */
	{ DWORD v_ = 0x3du; m->esp -= 4; M32(m->esp) = v_; }	/* 405d03: push 0x3d */
	m->esp -= 4; M32(m->esp) = 0x405d0au; native_call(m, 0x41ee40u);	/* 405d05: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405d0a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405d0d: xor eax, eax */
	m->esp += 4 + 0; return;	/* 405d0f: ret  */
L_405d10:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 405d10: cmp eax, 2 */
	if (!m->zf) goto L_405d22;	/* 405d13: jne 0x405d22 */
	{ DWORD v_ = 0x46u; m->esp -= 4; M32(m->esp) = v_; }	/* 405d15: push 0x46 */
	m->esp -= 4; M32(m->esp) = 0x405d1cu; native_call(m, 0x41ee40u);	/* 405d17: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405d1c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405d1f: xor eax, eax */
	m->esp += 4 + 0; return;	/* 405d21: ret  */
L_405d22:
	m->eax = M32((DWORD)(0x4ded18u));	/* 405d22: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 405d27: push 0x64 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 405d29: push eax */
	m->esp -= 4; M32(m->esp) = 0x405d2fu; native_call(m, 0x452170u);	/* 405d2a: call 0x452170 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405d2f: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405d32: test eax, eax */
	if (!m->zf) goto L_405d43;	/* 405d34: jne 0x405d43 */
	{ DWORD v_ = 0x3eu; m->esp -= 4; M32(m->esp) = v_; }	/* 405d36: push 0x3e */
	m->esp -= 4; M32(m->esp) = 0x405d3du; native_call(m, 0x41ee40u);	/* 405d38: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 405d3d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405d40: xor eax, eax */
	m->esp += 4 + 0; return;	/* 405d42: ret  */
L_405d43:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 405d43: push esi */
	M32((DWORD)(0x4ded54u)) = 0x1u;	/* 405d44: mov dword ptr [0x4ded54], 1 */
	m->esi = 0x4ad554u;	/* 405d4e: mov esi, 0x4ad554 */
	m->eax = 0x4ded20u;	/* 405d53: mov eax, 0x4ded20 */
L_405d58:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405d58: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405d5a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405d5c: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405d7c;	/* 405d5e: jne 0x405d7c */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405d60: test cl, cl */
	if (m->zf) goto L_405d78;	/* 405d62: je 0x405d78 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405d64: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405d67: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405d69: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405d7c;	/* 405d6c: jne 0x405d7c */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405d6e: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405d71: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405d74: test cl, cl */
	if (!m->zf) goto L_405d58;	/* 405d76: jne 0x405d58 */
L_405d78:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405d78: xor eax, eax */
	goto L_405d81;	/* 405d7a: jmp 0x405d81 */
L_405d7c:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405d7c: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405d7e: sbb eax, -1 */
L_405d81:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405d81: test eax, eax */
	if (m->zf) goto L_405e2e;	/* 405d83: je 0x405e2e */
	m->esi = 0x4ad548u;	/* 405d89: mov esi, 0x4ad548 */
	m->eax = 0x4ded20u;	/* 405d8e: mov eax, 0x4ded20 */
L_405d93:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405d93: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405d95: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405d97: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405db7;	/* 405d99: jne 0x405db7 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405d9b: test cl, cl */
	if (m->zf) goto L_405db3;	/* 405d9d: je 0x405db3 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405d9f: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405da2: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405da4: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405db7;	/* 405da7: jne 0x405db7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405da9: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405dac: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405daf: test cl, cl */
	if (!m->zf) goto L_405d93;	/* 405db1: jne 0x405d93 */
L_405db3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405db3: xor eax, eax */
	goto L_405dbc;	/* 405db5: jmp 0x405dbc */
L_405db7:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405db7: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405db9: sbb eax, -1 */
L_405dbc:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405dbc: test eax, eax */
	if (m->zf) goto L_405e2e;	/* 405dbe: je 0x405e2e */
	m->esi = 0x4ad53cu;	/* 405dc0: mov esi, 0x4ad53c */
	m->eax = 0x4ded20u;	/* 405dc5: mov eax, 0x4ded20 */
L_405dca:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405dca: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405dcc: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405dce: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405dee;	/* 405dd0: jne 0x405dee */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405dd2: test cl, cl */
	if (m->zf) goto L_405dea;	/* 405dd4: je 0x405dea */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405dd6: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405dd9: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405ddb: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405dee;	/* 405dde: jne 0x405dee */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405de0: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405de3: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405de6: test cl, cl */
	if (!m->zf) goto L_405dca;	/* 405de8: jne 0x405dca */
L_405dea:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405dea: xor eax, eax */
	goto L_405df3;	/* 405dec: jmp 0x405df3 */
L_405dee:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405dee: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405df0: sbb eax, -1 */
L_405df3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405df3: test eax, eax */
	if (m->zf) goto L_405e2e;	/* 405df5: je 0x405e2e */
	m->esi = 0x4ad530u;	/* 405df7: mov esi, 0x4ad530 */
	m->eax = 0x4ded20u;	/* 405dfc: mov eax, 0x4ded20 */
L_405e01:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405e01: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405e03: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405e05: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405e25;	/* 405e07: jne 0x405e25 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405e09: test cl, cl */
	if (m->zf) goto L_405e21;	/* 405e0b: je 0x405e21 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405e0d: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405e10: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405e12: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405e25;	/* 405e15: jne 0x405e25 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405e17: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405e1a: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405e1d: test cl, cl */
	if (!m->zf) goto L_405e01;	/* 405e1f: jne 0x405e01 */
L_405e21:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405e21: xor eax, eax */
	goto L_405e2a;	/* 405e23: jmp 0x405e2a */
L_405e25:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405e25: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405e27: sbb eax, -1 */
L_405e2a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405e2a: test eax, eax */
	if (!m->zf) goto L_405e35;	/* 405e2c: jne 0x405e35 */
L_405e2e:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x18u);	/* 405e2e: mov byte ptr [0x4ded40], 0x18 */
L_405e35:
	m->esi = 0x4ad524u;	/* 405e35: mov esi, 0x4ad524 */
	m->eax = 0x4ded20u;	/* 405e3a: mov eax, 0x4ded20 */
L_405e3f:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405e3f: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405e41: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405e43: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405e63;	/* 405e45: jne 0x405e63 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405e47: test cl, cl */
	if (m->zf) goto L_405e5f;	/* 405e49: je 0x405e5f */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405e4b: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405e4e: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405e50: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405e63;	/* 405e53: jne 0x405e63 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405e55: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405e58: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405e5b: test cl, cl */
	if (!m->zf) goto L_405e3f;	/* 405e5d: jne 0x405e3f */
L_405e5f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405e5f: xor eax, eax */
	goto L_405e68;	/* 405e61: jmp 0x405e68 */
L_405e63:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405e63: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405e65: sbb eax, -1 */
L_405e68:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405e68: test eax, eax */
	if (m->zf) goto L_405f15;	/* 405e6a: je 0x405f15 */
	m->esi = 0x4ad514u;	/* 405e70: mov esi, 0x4ad514 */
	m->eax = 0x4ded20u;	/* 405e75: mov eax, 0x4ded20 */
L_405e7a:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405e7a: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405e7c: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405e7e: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405e9e;	/* 405e80: jne 0x405e9e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405e82: test cl, cl */
	if (m->zf) goto L_405e9a;	/* 405e84: je 0x405e9a */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405e86: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405e89: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405e8b: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405e9e;	/* 405e8e: jne 0x405e9e */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405e90: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405e93: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405e96: test cl, cl */
	if (!m->zf) goto L_405e7a;	/* 405e98: jne 0x405e7a */
L_405e9a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405e9a: xor eax, eax */
	goto L_405ea3;	/* 405e9c: jmp 0x405ea3 */
L_405e9e:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405e9e: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405ea0: sbb eax, -1 */
L_405ea3:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405ea3: test eax, eax */
	if (m->zf) goto L_405f15;	/* 405ea5: je 0x405f15 */
	m->esi = 0x4ad504u;	/* 405ea7: mov esi, 0x4ad504 */
	m->eax = 0x4ded20u;	/* 405eac: mov eax, 0x4ded20 */
L_405eb1:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405eb1: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405eb3: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405eb5: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405ed5;	/* 405eb7: jne 0x405ed5 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405eb9: test cl, cl */
	if (m->zf) goto L_405ed1;	/* 405ebb: je 0x405ed1 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405ebd: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405ec0: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405ec2: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405ed5;	/* 405ec5: jne 0x405ed5 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405ec7: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405eca: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405ecd: test cl, cl */
	if (!m->zf) goto L_405eb1;	/* 405ecf: jne 0x405eb1 */
L_405ed1:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405ed1: xor eax, eax */
	goto L_405eda;	/* 405ed3: jmp 0x405eda */
L_405ed5:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405ed5: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405ed7: sbb eax, -1 */
L_405eda:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405eda: test eax, eax */
	if (m->zf) goto L_405f15;	/* 405edc: je 0x405f15 */
	m->esi = 0x4ad4f4u;	/* 405ede: mov esi, 0x4ad4f4 */
	m->eax = 0x4ded20u;	/* 405ee3: mov eax, 0x4ded20 */
L_405ee8:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405ee8: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405eea: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405eec: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405f0c;	/* 405eee: jne 0x405f0c */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405ef0: test cl, cl */
	if (m->zf) goto L_405f08;	/* 405ef2: je 0x405f08 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405ef4: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405ef7: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405ef9: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405f0c;	/* 405efc: jne 0x405f0c */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405efe: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405f01: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405f04: test cl, cl */
	if (!m->zf) goto L_405ee8;	/* 405f06: jne 0x405ee8 */
L_405f08:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405f08: xor eax, eax */
	goto L_405f11;	/* 405f0a: jmp 0x405f11 */
L_405f0c:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405f0c: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405f0e: sbb eax, -1 */
L_405f11:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405f11: test eax, eax */
	if (!m->zf) goto L_405f1c;	/* 405f13: jne 0x405f1c */
L_405f15:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x16u);	/* 405f15: mov byte ptr [0x4ded40], 0x16 */
L_405f1c:
	m->esi = 0x4ad4e8u;	/* 405f1c: mov esi, 0x4ad4e8 */
	m->eax = 0x4ded20u;	/* 405f21: mov eax, 0x4ded20 */
L_405f26:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405f26: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405f28: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405f2a: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405f4a;	/* 405f2c: jne 0x405f4a */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405f2e: test cl, cl */
	if (m->zf) goto L_405f46;	/* 405f30: je 0x405f46 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405f32: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405f35: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405f37: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405f4a;	/* 405f3a: jne 0x405f4a */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405f3c: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405f3f: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405f42: test cl, cl */
	if (!m->zf) goto L_405f26;	/* 405f44: jne 0x405f26 */
L_405f46:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405f46: xor eax, eax */
	goto L_405f4f;	/* 405f48: jmp 0x405f4f */
L_405f4a:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405f4a: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405f4c: sbb eax, -1 */
L_405f4f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405f4f: test eax, eax */
	if (m->zf) goto L_405ffc;	/* 405f51: je 0x405ffc */
	m->esi = 0x4ad4d8u;	/* 405f57: mov esi, 0x4ad4d8 */
	m->eax = 0x4ded20u;	/* 405f5c: mov eax, 0x4ded20 */
L_405f61:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405f61: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405f63: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405f65: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405f85;	/* 405f67: jne 0x405f85 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405f69: test cl, cl */
	if (m->zf) goto L_405f81;	/* 405f6b: je 0x405f81 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405f6d: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405f70: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405f72: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405f85;	/* 405f75: jne 0x405f85 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405f77: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405f7a: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405f7d: test cl, cl */
	if (!m->zf) goto L_405f61;	/* 405f7f: jne 0x405f61 */
L_405f81:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405f81: xor eax, eax */
	goto L_405f8a;	/* 405f83: jmp 0x405f8a */
L_405f85:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405f85: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405f87: sbb eax, -1 */
L_405f8a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405f8a: test eax, eax */
	if (m->zf) goto L_405ffc;	/* 405f8c: je 0x405ffc */
	m->esi = 0x4ad4c8u;	/* 405f8e: mov esi, 0x4ad4c8 */
	m->eax = 0x4ded20u;	/* 405f93: mov eax, 0x4ded20 */
L_405f98:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405f98: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405f9a: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405f9c: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405fbc;	/* 405f9e: jne 0x405fbc */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405fa0: test cl, cl */
	if (m->zf) goto L_405fb8;	/* 405fa2: je 0x405fb8 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405fa4: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405fa7: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405fa9: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405fbc;	/* 405fac: jne 0x405fbc */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405fae: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405fb1: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405fb4: test cl, cl */
	if (!m->zf) goto L_405f98;	/* 405fb6: jne 0x405f98 */
L_405fb8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405fb8: xor eax, eax */
	goto L_405fc1;	/* 405fba: jmp 0x405fc1 */
L_405fbc:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405fbc: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405fbe: sbb eax, -1 */
L_405fc1:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405fc1: test eax, eax */
	if (m->zf) goto L_405ffc;	/* 405fc3: je 0x405ffc */
	m->esi = 0x4ad4b8u;	/* 405fc5: mov esi, 0x4ad4b8 */
	m->eax = 0x4ded20u;	/* 405fca: mov eax, 0x4ded20 */
L_405fcf:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 405fcf: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405fd1: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405fd3: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_405ff3;	/* 405fd5: jne 0x405ff3 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405fd7: test cl, cl */
	if (m->zf) goto L_405fef;	/* 405fd9: je 0x405fef */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 405fdb: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 405fde: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 405fe0: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_405ff3;	/* 405fe3: jne 0x405ff3 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 405fe5: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 405fe8: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 405feb: test cl, cl */
	if (!m->zf) goto L_405fcf;	/* 405fed: jne 0x405fcf */
L_405fef:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 405fef: xor eax, eax */
	goto L_405ff8;	/* 405ff1: jmp 0x405ff8 */
L_405ff3:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405ff3: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 405ff5: sbb eax, -1 */
L_405ff8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 405ff8: test eax, eax */
	if (!m->zf) goto L_406003;	/* 405ffa: jne 0x406003 */
L_405ffc:
	M8((DWORD)(0x4ded40u)) = (BYTE)(0x17u);	/* 405ffc: mov byte ptr [0x4ded40], 0x17 */
L_406003:
	m->eax = M32((DWORD)(0xa0b310u));	/* 406003: mov eax, dword ptr [0xa0b310] */
	m->esi = M32((DWORD)(0x4a911cu));	/* 406008: mov esi, dword ptr [0x4a911c] */
	{ DWORD v_ = 0x4ded46u; m->esp -= 4; M32(m->esp) = v_; }	/* 40600e: push 0x4ded46 */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x18u);	/* 406013: mov byte ptr [eax], 0x18 */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 406016: mov ecx, dword ptr [0xa0b310] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded42u))) & 0xff) << 0);	/* 40601c: mov dl, byte ptr [0x4ded42] */
	M8((DWORD)(m->ecx + 0x49u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 406022: mov byte ptr [ecx + 0x49], dl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 406025: mov eax, dword ptr [0xa0b310] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded45u))) & 0xff) << 0);	/* 40602a: mov cl, byte ptr [0x4ded45] */
	M8((DWORD)(m->eax + 0x48u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 406030: mov byte ptr [eax + 0x48], cl */
	m->edx = M32((DWORD)(0xa0b310u));	/* 406033: mov edx, dword ptr [0xa0b310] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded44u))) & 0xff) << 0);	/* 406039: mov al, byte ptr [0x4ded44] */
	M8((DWORD)(m->edx + 0x47u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 40603e: mov byte ptr [edx + 0x47], al */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 406041: mov ecx, dword ptr [0xa0b310] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded43u))) & 0xff) << 0);	/* 406047: mov dl, byte ptr [0x4ded43] */
	M8((DWORD)(m->ecx + 0x46u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 40604d: mov byte ptr [ecx + 0x46], dl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 406050: mov eax, dword ptr [0xa0b310] */
	M8((DWORD)(m->eax + 0x45u)) = (BYTE)(0x1u);	/* 406055: mov byte ptr [eax + 0x45], 1 */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 406059: mov ecx, dword ptr [0xa0b310] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded40u))) & 0xff) << 0);	/* 40605f: mov dl, byte ptr [0x4ded40] */
	M8((DWORD)(m->ecx + 0x43u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 406065: mov byte ptr [ecx + 0x43], dl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 406068: mov eax, dword ptr [0xa0b310] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded41u))) & 0xff) << 0);	/* 40606d: mov cl, byte ptr [0x4ded41] */
	M8((DWORD)(m->eax + 0x44u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 406073: mov byte ptr [eax + 0x44], cl */
	m->edx = M32((DWORD)(0xa0b310u));	/* 406076: mov edx, dword ptr [0xa0b310] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded4eu))) & 0xff) << 0);	/* 40607c: mov al, byte ptr [0x4ded4e] */
	M8((DWORD)(m->edx + 0x52u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 406081: mov byte ptr [edx + 0x52], al */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 406084: mov ecx, dword ptr [0xa0b310] */
	{ DWORD a_ = m->ecx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40608a: add ecx, 0x53 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40608d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x406090u; native_call(m, m->esi);	/* 40608e: call esi */
	m->edx = M32((DWORD)(0xa0b310u));	/* 406090: mov edx, dword ptr [0xa0b310] */
	{ DWORD v_ = 0x4ded20u; m->esp -= 4; M32(m->esp) = v_; }	/* 406096: push 0x4ded20 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 40609b: inc edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40609c: push edx */
	m->esp -= 4; M32(m->esp) = 0x40609fu; native_call(m, m->esi);	/* 40609d: call esi */
	m->esp -= 4; M32(m->esp) = 0x4060a4u; native_call(m, 0x4532e0u);	/* 40609f: call 0x4532e0 */
	m->eax = M32((DWORD)(0xa0b310u));	/* 4060a4: mov eax, dword ptr [0xa0b310] */
	{ DWORD v_ = 0xa0b43cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4060a9: push 0xa0b43c */
	{ DWORD a_ = m->eax, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4060ae: add eax, 0x33 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4060b1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4060b4u; native_call(m, m->esi);	/* 4060b2: call esi */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4060b4: push 0x64 */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 4060b6: push 0xa */
	M32((DWORD)(0x4dba88u)) = 0x1u;	/* 4060b8: mov dword ptr [0x4dba88], 1 */
	M32((DWORD)(0x4ded60u)) = 0x2u;	/* 4060c2: mov dword ptr [0x4ded60], 2 */
	m->esp -= 4; M32(m->esp) = 0x4060d1u; native_call(m, 0x4521c0u);	/* 4060cc: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4060d1: add esp, 8 */
	M32((DWORD)(0x4dbbf4u)) = 0x2u;	/* 4060d4: mov dword ptr [0x4dbbf4], 2 */
	m->eax = 0x1u;	/* 4060de: mov eax, 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4060e3: pop esi */
	m->esp += 4 + 0; return;	/* 4060e4: ret  */
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
