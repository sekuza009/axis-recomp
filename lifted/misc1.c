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

static void lift_463960(X86 *m);
static void lift_462740(X86 *m);
static void lift_46ff70(X86 *m);
static void lift_4617f0(X86 *m);
static void lift_45ff30(X86 *m);

/* FUN_0045ff30 (0x45ff30), lifted by tools/lift.py */
static void lift_45ff30(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45ff30: push -1 */
	{ DWORD v_ = 0x4a8a62u; m->esp -= 4; M32(m->esp) = v_; }	/* 45ff32: push 0x4a8a62 */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 45ff37: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45ff3d: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 45ff3e: mov dword ptr fs:[0], esp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45ff45: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45ff46: push esi */
	m->esi = m->ecx;	/* 45ff47: mov esi, ecx */
	M32((DWORD)(m->esp + 0x4u)) = m->esi;	/* 45ff49: mov dword ptr [esp + 4], esi */
	m->ecx = (DWORD)(m->esi + 0x701cu);	/* 45ff4d: lea ecx, [esi + 0x701c] */
	M32((DWORD)(m->esp + 0x10u)) = 0x6u;	/* 45ff53: mov dword ptr [esp + 0x10], 6 */
	m->esp -= 4; M32(m->esp) = 0x45ff60u; native_call(m, 0x46f470u);	/* 45ff5b: call 0x46f470 */
	m->ecx = (DWORD)(m->esi + 0x587cu);	/* 45ff60: lea ecx, [esi + 0x587c] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x5u);	/* 45ff66: mov byte ptr [esp + 0x10], 5 */
	m->esp -= 4; M32(m->esp) = 0x45ff70u; native_call(m, 0x46f470u);	/* 45ff6b: call 0x46f470 */
	m->ecx = (DWORD)(m->esi + 0x40dcu);	/* 45ff70: lea ecx, [esi + 0x40dc] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x4u);	/* 45ff76: mov byte ptr [esp + 0x10], 4 */
	m->esp -= 4; M32(m->esp) = 0x45ff80u; native_call(m, 0x46f470u);	/* 45ff7b: call 0x46f470 */
	m->ecx = (DWORD)(m->esi + 0x34f4u);	/* 45ff80: lea ecx, [esi + 0x34f4] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x3u);	/* 45ff86: mov byte ptr [esp + 0x10], 3 */
	m->esp -= 4; M32(m->esp) = 0x45ff90u; native_call(m, 0x46f470u);	/* 45ff8b: call 0x46f470 */
	m->ecx = (DWORD)(m->esi + 0x2524u);	/* 45ff90: lea ecx, [esi + 0x2524] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x2u);	/* 45ff96: mov byte ptr [esp + 0x10], 2 */
	m->esp -= 4; M32(m->esp) = 0x45ffa0u; native_call(m, 0x46f470u);	/* 45ff9b: call 0x46f470 */
	m->ecx = (DWORD)(m->esi + 0x1554u);	/* 45ffa0: lea ecx, [esi + 0x1554] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x1u);	/* 45ffa6: mov byte ptr [esp + 0x10], 1 */
	m->esp -= 4; M32(m->esp) = 0x45ffb0u; native_call(m, 0x46f470u);	/* 45ffab: call 0x46f470 */
	m->ecx = (DWORD)(m->esi + 0xd54u);	/* 45ffb0: lea ecx, [esi + 0xd54] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x0u);	/* 45ffb6: mov byte ptr [esp + 0x10], 0 */
	m->esp -= 4; M32(m->esp) = 0x45ffc0u; native_call(m, 0x46f470u);	/* 45ffbb: call 0x46f470 */
	m->ecx = (DWORD)(m->esi + 0x554u);	/* 45ffc0: lea ecx, [esi + 0x554] */
	M32((DWORD)(m->esp + 0x10u)) = 0xffffffffu;	/* 45ffc6: mov dword ptr [esp + 0x10], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x45ffd3u; native_call(m, 0x46f470u);	/* 45ffce: call 0x46f470 */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 45ffd3: mov ecx, dword ptr [esp + 8] */
	m->esi = M32(m->esp); m->esp += 4;	/* 45ffd7: pop esi */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 45ffd8: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45ffdf: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 45ffe2: ret  */
}

/* ResourceSet_dtor_463960 (0x463960), lifted by tools/lift.py */
static void lift_463960(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 463960: push -1 */
	{ DWORD v_ = 0x4a8caeu; m->esp -= 4; M32(m->esp) = v_; }	/* 463962: push 0x4a8cae */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 463967: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46396d: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 46396e: mov dword ptr fs:[0], esp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 463975: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 463976: push esi */
	m->esi = m->ecx;	/* 463977: mov esi, ecx */
	M32((DWORD)(m->esp + 0x4u)) = m->esi;	/* 463979: mov dword ptr [esp + 4], esi */
	m->ecx = (DWORD)(m->esi + 0x468d4u);	/* 46397d: lea ecx, [esi + 0x468d4] */
	M32((DWORD)(m->esp + 0x10u)) = 0x8u;	/* 463983: mov dword ptr [esp + 0x10], 8 */
	m->esp -= 4; M32(m->esp) = 0x463990u; native_call(m, 0x46ae60u);	/* 46398b: call 0x46ae60 */
	m->ecx = (DWORD)(m->esi + 0x45804u);	/* 463990: lea ecx, [esi + 0x45804] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x7u);	/* 463996: mov byte ptr [esp + 0x10], 7 */
	m->esp -= 4; M32(m->esp) = 0x4639a0u; native_call(m, 0x46ae60u);	/* 46399b: call 0x46ae60 */
	m->ecx = (DWORD)(m->esi + 0x44734u);	/* 4639a0: lea ecx, [esi + 0x44734] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x6u);	/* 4639a6: mov byte ptr [esp + 0x10], 6 */
	m->esp -= 4; M32(m->esp) = 0x4639b0u; native_call(m, 0x46ae60u);	/* 4639ab: call 0x46ae60 */
	m->ecx = (DWORD)(m->esi + 0x43e34u);	/* 4639b0: lea ecx, [esi + 0x43e34] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x5u);	/* 4639b6: mov byte ptr [esp + 0x10], 5 */
	m->esp -= 4; M32(m->esp) = 0x4639c0u; native_call(m, 0x46ae60u);	/* 4639bb: call 0x46ae60 */
	m->ecx = (DWORD)(m->esi + 0x43534u);	/* 4639c0: lea ecx, [esi + 0x43534] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x4u);	/* 4639c6: mov byte ptr [esp + 0x10], 4 */
	m->esp -= 4; M32(m->esp) = 0x4639d0u; native_call(m, 0x46ae60u);	/* 4639cb: call 0x46ae60 */
	m->ecx = (DWORD)(m->esi + 0x2fa68u);	/* 4639d0: lea ecx, [esi + 0x2fa68] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x3u);	/* 4639d6: mov byte ptr [esp + 0x10], 3 */
	m->esp -= 4; M32(m->esp) = 0x4639e0u; native_call(m, 0x466a10u);	/* 4639db: call 0x466a10 */
	m->ecx = (DWORD)(m->esi + 0x1fe1cu);	/* 4639e0: lea ecx, [esi + 0x1fe1c] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x2u);	/* 4639e6: mov byte ptr [esp + 0x10], 2 */
	m->esp -= 4; M32(m->esp) = 0x4639f0u; native_call(m, 0x466a10u);	/* 4639eb: call 0x466a10 */
	m->ecx = (DWORD)(m->esi + 0x101d0u);	/* 4639f0: lea ecx, [esi + 0x101d0] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x1u);	/* 4639f6: mov byte ptr [esp + 0x10], 1 */
	m->esp -= 4; M32(m->esp) = 0x463a00u; native_call(m, 0x466a10u);	/* 4639fb: call 0x466a10 */
	m->ecx = (DWORD)(m->esi + 0x8284u);	/* 463a00: lea ecx, [esi + 0x8284] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x0u);	/* 463a06: mov byte ptr [esp + 0x10], 0 */
	m->esp -= 4; M32(m->esp) = 0x463a10u; native_call(m, 0x466a10u);	/* 463a0b: call 0x466a10 */
	m->ecx = (DWORD)(m->esi + 0x338u);	/* 463a10: lea ecx, [esi + 0x338] */
	M32((DWORD)(m->esp + 0x10u)) = 0xffffffffu;	/* 463a16: mov dword ptr [esp + 0x10], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x463a23u; native_call(m, 0x466a10u);	/* 463a1e: call 0x466a10 */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 463a23: mov ecx, dword ptr [esp + 8] */
	m->esi = M32(m->esp); m->esp += 4;	/* 463a27: pop esi */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 463a28: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463a2f: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 463a32: ret  */
}

/* chat_macro (0x462740), lifted by tools/lift.py */
static void lift_462740(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 462740: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462744: sub esp, 0x100 */
	m->edx = m->ecx;	/* 46274a: mov edx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 46274c: mov cl, byte ptr [eax] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46274e: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46274f: push esi */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x2fu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 462750: cmp cl, 0x2f */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 462753: push edi */
	if (!m->zf) goto L_46283f;	/* 462754: jne 0x46283f */
	m->edi = (DWORD)(m->eax + 0x1u);	/* 46275a: lea edi, [eax + 1] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46275d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 462760: xor eax, eax */
	m->ebx = (DWORD)(m->esp + 0xcu);	/* 462762: lea ebx, [esp + 0xc] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 462766: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 462768: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46276a: sub edi, ecx */
	m->eax = m->ecx;	/* 46276c: mov eax, ecx */
	m->esi = m->edi;	/* 46276e: mov esi, edi */
	m->edi = m->ebx;	/* 462770: mov edi, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462772: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 462775: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 462777: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 462779: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46277c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0xcu))) & 0xff) << 0);	/* 46277e: mov al, byte ptr [esp + 0xc] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x30u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 462782: cmp al, 0x30 */
	if (m->sf != m->of) goto L_46283f;	/* 462784: jl 0x46283f */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x39u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46278a: cmp al, 0x39 */
	if (!m->zf && m->sf == m->of) goto L_46283f;	/* 46278c: jg 0x46283f */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0xdu))) & 0xff) << 0);	/* 462792: mov cl, byte ptr [esp + 0xd] */
	m->eax = (DWORD)(int)(signed char)(((m->eax >> 0) & 0xff));	/* 462796: movsx eax, al */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 462799: sub eax, 0x30 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x30u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46279c: cmp cl, 0x30 */
	if (m->sf != m->of) goto L_4627b0;	/* 46279f: jl 0x4627b0 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x39u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4627a1: cmp cl, 0x39 */
	if (!m->zf && m->sf == m->of) goto L_4627b0;	/* 4627a4: jg 0x4627b0 */
	m->esi = (DWORD)(int)(signed char)(((m->ecx >> 0) & 0xff));	/* 4627a6: movsx esi, cl */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4627a9: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->esi + m->eax*2 + 0xffffffd0u);	/* 4627ac: lea eax, [esi + eax*2 - 0x30] */
L_4627b0:
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x3du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4627b0: cmp cl, 0x3d */
	if (!m->zf) goto L_4627fc;	/* 4627b3: jne 0x4627fc */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4627b5: lea ecx, [eax + eax*8] */
	m->edi = (DWORD)(m->esp + 0xeu);	/* 4627b8: lea edi, [esp + 0xe] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4627bc: lea eax, [eax + ecx*2] */
	m->ecx = (DWORD)(m->edx + m->eax*2 + 0x0u);	/* 4627bf: lea ecx, [edx + eax*2] */
	m->ebx = (DWORD)(m->eax + m->ecx*1 + 0x2340d3du);	/* 4627c2: lea ebx, [eax + ecx + 0x2340d3d] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4627c9: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4627cc: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4627ce: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4627d0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4627d2: sub edi, ecx */
	m->eax = m->ecx;	/* 4627d4: mov eax, ecx */
	m->esi = m->edi;	/* 4627d6: mov esi, edi */
	m->edi = m->ebx;	/* 4627d8: mov edi, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4627da: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4627dd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4627df: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4627e1: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4627e4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = m->edx;	/* 4627e6: mov ecx, edx */
	m->esp -= 4; M32(m->esp) = 0x4627edu; native_call(m, 0x4617b0u);	/* 4627e8: call 0x4617b0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4627ed: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4627ee: pop esi */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4627ef: or eax, 0xffffffff */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4627f2: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4627f3: add esp, 0x100 */
	m->esp += 4 + 8; return;	/* 4627f9: ret 8 */
L_4627fc:
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 4627fc: lea ecx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 4627ff: lea eax, [eax + ecx*2] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 462802: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->edx + m->eax*2 + 0x0u);	/* 462805: lea edx, [edx + eax*2] */
	m->edi = (DWORD)(m->eax + m->edx*1 + 0x2340d3du);	/* 462808: lea edi, [eax + edx + 0x2340d3d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46280f: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 462811: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 462813: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 462815: sub edi, ecx */
	m->eax = m->ecx;	/* 462817: mov eax, ecx */
	m->esi = m->edi;	/* 462819: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x114u));	/* 46281b: mov edi, dword ptr [esp + 0x114] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 462822: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 462825: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 462827: mov ecx, eax */
	m->eax = 0x1u;	/* 462829: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46282e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 462831: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 462833: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 462834: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 462835: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462836: add esp, 0x100 */
	m->esp += 4 + 8; return;	/* 46283c: ret 8 */
L_46283f:
	m->edi = M32(m->esp); m->esp += 4;	/* 46283f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 462840: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 462841: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 462843: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462844: add esp, 0x100 */
	m->esp += 4 + 8; return;	/* 46284a: ret 8 */
}

/* Stage_dtor (0x46ff70), lifted by tools/lift.py */
static void lift_46ff70(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 46ff70: push -1 */
	{ DWORD v_ = 0x4a8df2u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ff72: push 0x4a8df2 */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 46ff77: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ff7d: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 46ff7e: mov dword ptr fs:[0], esp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ff85: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ff86: push esi */
	m->esi = m->ecx;	/* 46ff87: mov esi, ecx */
	M32((DWORD)(m->esp + 0x4u)) = m->esi;	/* 46ff89: mov dword ptr [esp + 4], esi */
	M32((DWORD)(m->esi + 0x0u)) = 0x4aa23cu;	/* 46ff8d: mov dword ptr [esi], 0x4aa23c */
	m->ecx = (DWORD)(m->esi + 0x2148ed8u);	/* 46ff93: lea ecx, [esi + 0x2148ed8] */
	M32((DWORD)(m->esp + 0x10u)) = 0xbu;	/* 46ff99: mov dword ptr [esp + 0x10], 0xb */
	m->esp -= 4; M32(m->esp) = 0x46ffa6u; native_call(m, 0x48b410u);	/* 46ffa1: call 0x48b410 */
	{ DWORD v_ = 0x45ff30u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ffa6: push 0x45ff30 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ffab: push 0x64 */
	m->eax = (DWORD)(m->esi + 0x1cd93a8u);	/* 46ffad: lea eax, [esi + 0x1cd93a8] */
	{ DWORD v_ = 0x8888u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ffb3: push 0x8888 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ffb8: push eax */
	M8((DWORD)(m->esp + 0x20u)) = (BYTE)(0xau);	/* 46ffb9: mov byte ptr [esp + 0x20], 0xa */
	m->esp -= 4; M32(m->esp) = 0x46ffc3u; native_call(m, 0x49fc4fu);	/* 46ffbe: call 0x49fc4f */
	m->ecx = (DWORD)(m->esi + 0x1cbe198u);	/* 46ffc3: lea ecx, [esi + 0x1cbe198] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x9u);	/* 46ffc9: mov byte ptr [esp + 0x10], 9 */
	m->esp -= 4; M32(m->esp) = 0x46ffd3u; native_call(m, 0x46ae60u);	/* 46ffce: call 0x46ae60 */
	m->ecx = (DWORD)(m->esi + 0x19e188cu);	/* 46ffd3: lea ecx, [esi + 0x19e188c] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x8u);	/* 46ffd9: mov byte ptr [esp + 0x10], 8 */
	m->esp -= 4; M32(m->esp) = 0x46ffe3u; native_call(m, 0x466a10u);	/* 46ffde: call 0x466a10 */
	{ DWORD v_ = 0x463960u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ffe3: push 0x463960 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ffe8: push 0x10 */
	m->ecx = (DWORD)(m->esi + 0x1561b68u);	/* 46ffea: lea ecx, [esi + 0x1561b68] */
	{ DWORD v_ = 0x47fd2u; m->esp -= 4; M32(m->esp) = v_; }	/* 46fff0: push 0x47fd2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46fff5: push ecx */
	M8((DWORD)(m->esp + 0x20u)) = (BYTE)(0x7u);	/* 46fff6: mov byte ptr [esp + 0x20], 7 */
	m->esp -= 4; M32(m->esp) = 0x470000u; native_call(m, 0x49fc4fu);	/* 46fffb: call 0x49fc4f */
	m->ecx = (DWORD)(m->esi + 0x13016d0u);	/* 470000: lea ecx, [esi + 0x13016d0] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x6u);	/* 470006: mov byte ptr [esp + 0x10], 6 */
	m->esp -= 4; M32(m->esp) = 0x470010u; native_call(m, 0x46ae60u);	/* 47000b: call 0x46ae60 */
	m->ecx = (DWORD)(m->esi + 0xe3c93cu);	/* 470010: lea ecx, [esi + 0xe3c93c] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x5u);	/* 470016: mov byte ptr [esp + 0x10], 5 */
	m->esp -= 4; M32(m->esp) = 0x470020u; native_call(m, 0x466a10u);	/* 47001b: call 0x466a10 */
	m->ecx = (DWORD)(m->esi + 0xdc0cc4u);	/* 470020: lea ecx, [esi + 0xdc0cc4] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x4u);	/* 470026: mov byte ptr [esp + 0x10], 4 */
	m->esp -= 4; M32(m->esp) = 0x470030u; native_call(m, 0x464ba0u);	/* 47002b: call 0x464ba0 */
	m->ecx = (DWORD)(m->esi + 0xdc0a78u);	/* 470030: lea ecx, [esi + 0xdc0a78] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x3u);	/* 470036: mov byte ptr [esp + 0x10], 3 */
	m->esp -= 4; M32(m->esp) = 0x470040u; native_call(m, 0x464ba0u);	/* 47003b: call 0x464ba0 */
	m->ecx = (DWORD)(m->esi + 0x9e3020u);	/* 470040: lea ecx, [esi + 0x9e3020] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x2u);	/* 470046: mov byte ptr [esp + 0x10], 2 */
	m->esp -= 4; M32(m->esp) = 0x470050u; native_call(m, 0x483d50u);	/* 47004b: call 0x483d50 */
	m->ecx = (DWORD)(m->esi + 0x9d8010u);	/* 470050: lea ecx, [esi + 0x9d8010] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x1u);	/* 470056: mov byte ptr [esp + 0x10], 1 */
	m->esp -= 4; M32(m->esp) = 0x470060u; native_call(m, 0x483d50u);	/* 47005b: call 0x483d50 */
	m->ecx = (DWORD)(m->esi + 0x9ccffcu);	/* 470060: lea ecx, [esi + 0x9ccffc] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x0u);	/* 470066: mov byte ptr [esp + 0x10], 0 */
	m->esp -= 4; M32(m->esp) = 0x470070u; native_call(m, 0x483d50u);	/* 47006b: call 0x483d50 */
	m->ecx = (DWORD)(m->esi + 0xa10u);	/* 470070: lea ecx, [esi + 0xa10] */
	M32((DWORD)(m->esp + 0x10u)) = 0xffffffffu;	/* 470076: mov dword ptr [esp + 0x10], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x470083u; native_call(m, 0x481390u);	/* 47007e: call 0x481390 */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 470083: mov ecx, dword ptr [esp + 8] */
	m->esi = M32(m->esp); m->esp += 4;	/* 470087: pop esi */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 470088: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47008f: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 470092: ret  */
}

/* chat_saveMacros (0x4617f0), lifted by tools/lift.py */
static void lift_4617f0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4617f0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4617f1: push edi */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 4617f2: push 0x4ad170 */
	m->edi = m->ecx;	/* 4617f7: mov edi, ecx */
	{ DWORD v_ = 0x4c45ecu; m->esp -= 4; M32(m->esp) = v_; }	/* 4617f9: push 0x4c45ec */
	m->esp -= 4; M32(m->esp) = 0x461803u; native_call(m, 0x49e9cau);	/* 4617fe: call 0x49e9ca */
	m->esi = m->eax;	/* 461803: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 461805: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 461808: test esi, esi */
	if (m->zf) goto L_461829;	/* 46180a: je 0x461829 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46180c: push esi */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 46180d: push 0x64 */
	{ DWORD a_ = m->edi, b_ = 0x2340d3du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46180f: add edi, 0x2340d3d */
	{ DWORD v_ = 0x39u; m->esp -= 4; M32(m->esp) = v_; }	/* 461815: push 0x39 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 461817: push edi */
	m->esp -= 4; M32(m->esp) = 0x46181du; native_call(m, 0x49e836u);	/* 461818: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46181d: push esi */
	m->esp -= 4; M32(m->esp) = 0x461823u; native_call(m, 0x49e7e0u);	/* 46181e: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 461823: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 461826: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 461827: pop esi */
	m->esp += 4 + 0; return;	/* 461828: ret  */
L_461829:
	m->eax = (DWORD)(m->edi + 0x2340d3du);	/* 461829: lea eax, [edi + 0x2340d3d] */
	m->ecx = 0x64u;	/* 46182f: mov ecx, 0x64 */
L_461834:
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x0u);	/* 461834: mov byte ptr [eax], 0 */
	{ DWORD a_ = m->eax, b_ = 0x39u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 461837: add eax, 0x39 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46183a: dec ecx */
	if (!m->zf) goto L_461834;	/* 46183b: jne 0x461834 */
	m->ecx = m->edi;	/* 46183d: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x461844u; native_call(m, 0x4617b0u);	/* 46183f: call 0x4617b0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 461844: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 461845: pop esi */
	m->esp += 4 + 0; return;	/* 461846: ret  */
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
