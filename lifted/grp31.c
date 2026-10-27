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

static void lift_48fee0(X86 *m);

/* object_initObjectBy (0x48fee0), lifted by tools/lift.py */
static void lift_48fee0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48fee0: sub esp, 0x8c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48fee6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48fee7: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48fee8: push esi */
	m->esi = m->ecx;	/* 48fee9: mov esi, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x9cu));	/* 48feeb: mov ecx, dword ptr [esp + 0x9c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48fef2: xor ebx, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48fef4: push edi */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 48fef5: mov dword ptr [esp + 0x18], esi */
	m->eax = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 48fef9: lea eax, [ecx + ecx*4] */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 48fefc: mov dword ptr [esp + 0x10], ebx */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 48ff00: lea eax, [eax + eax*8] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ff03: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ff06: sub eax, ecx */
	m->ebp = (DWORD)(m->esi + m->eax*4 + 0x131ae44u);	/* 48ff08: lea ebp, [esi + eax*4 + 0x131ae44] */
	m->eax = M32((DWORD)(m->esi + 0x131ae40u));	/* 48ff0f: mov eax, dword ptr [esi + 0x131ae40] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ff15: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_48ff7d;	/* 48ff17: jle 0x48ff7d */
	m->ecx = (DWORD)(m->esi + 0x130b440u);	/* 48ff19: lea ecx, [esi + 0x130b440] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 48ff1f: mov dword ptr [esp + 0x14], ecx */
L_48ff23:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48ff23: mov eax, dword ptr [esp + 0x14] */
	m->edi = M32((DWORD)(m->esp + 0xa4u));	/* 48ff27: mov edi, dword ptr [esp + 0xa4] */
L_48ff2e:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 48ff2e: mov dl, byte ptr [edi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 48ff30: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->eax + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48ff32: cmp dl, byte ptr [eax] */
	if (!m->zf) goto L_48ff52;	/* 48ff34: jne 0x48ff52 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48ff36: cmp cl, bl */
	if (m->zf) goto L_48ff4e;	/* 48ff38: je 0x48ff4e */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 48ff3a: mov dl, byte ptr [edi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 48ff3d: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->eax + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48ff3f: cmp dl, byte ptr [eax + 1] */
	if (!m->zf) goto L_48ff52;	/* 48ff42: jne 0x48ff52 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48ff44: add edi, 2 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ff47: add eax, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48ff4a: cmp cl, bl */
	if (!m->zf) goto L_48ff2e;	/* 48ff4c: jne 0x48ff2e */
L_48ff4e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48ff4e: xor eax, eax */
	goto L_48ff57;	/* 48ff50: jmp 0x48ff57 */
L_48ff52:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 48ff52: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 48ff54: sbb eax, -1 */
L_48ff57:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ff57: cmp eax, ebx */
	if (m->zf) goto L_48ffec;	/* 48ff59: je 0x48ffec */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 48ff5f: mov ecx, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 48ff63: mov edi, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esi + 0x131ae40u));	/* 48ff67: mov eax, dword ptr [esi + 0x131ae40] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48ff6d: inc ecx */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48ff6e: add edi, 0x40 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ff71: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 48ff73: mov dword ptr [esp + 0x10], ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 48ff77: mov dword ptr [esp + 0x14], edi */
	if (m->sf != m->of) goto L_48ff23;	/* 48ff7b: jl 0x48ff23 */
L_48ff7d:
	{ DWORD a_ = m->eax, b_ = 0x3e8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ff7d: cmp eax, 0x3e8 */
	if (m->sf != m->of) goto L_48ff9b;	/* 48ff82: jl 0x48ff9b */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ff84: push 0x3e8 */
	{ DWORD v_ = 0x4c8364u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ff89: push 0x4c8364 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ff8e: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48ff98u; native_call(m, 0x46c710u);	/* 48ff93: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ff98: add esp, 0xc */
L_48ff9b:
	m->edx = M32((DWORD)(m->esi + 0x131ae40u));	/* 48ff9b: mov edx, dword ptr [esi + 0x131ae40] */
	m->edi = M32((DWORD)(m->esp + 0xa4u));	/* 48ffa1: mov edi, dword ptr [esp + 0xa4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ffa8: or ecx, 0xffffffff */
	m->eax = (DWORD)(m->edx + 0x1u);	/* 48ffab: lea eax, [edx + 1] */
	M32((DWORD)(m->esi + 0x131ae40u)) = m->eax;	/* 48ffae: mov dword ptr [esi + 0x131ae40], eax */
	m->eax = (DWORD)(m->edx + 0x4c2d1u);	/* 48ffb4: lea eax, [edx + 0x4c2d1] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ffba: shl eax, 6 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ffbd: add eax, esi */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 48ffbf: mov dword ptr [esp + 0x10], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48ffc3: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48ffc5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48ffc7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48ffc9: sub edi, ecx */
	m->eax = m->ecx;	/* 48ffcb: mov eax, ecx */
	m->esi = m->edi;	/* 48ffcd: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 48ffcf: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48ffd3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48ffd6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48ffd8: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ffda: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48ffdd: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 48ffdf: mov esi, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0xa4u));	/* 48ffe3: mov ecx, dword ptr [esp + 0xa4] */
	goto L_48fff7;	/* 48ffea: jmp 0x48fff7 */
L_48ffec:
	m->ecx = M32((DWORD)(m->esp + 0xa4u));	/* 48ffec: mov ecx, dword ptr [esp + 0xa4] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 48fff3: mov edx, dword ptr [esp + 0x10] */
L_48fff7:
	m->eax = M32((DWORD)(m->esi + 0x13c9b2cu));	/* 48fff7: mov eax, dword ptr [esi + 0x13c9b2c] */
	M32((DWORD)(m->ebp + 0x0u)) = m->eax;	/* 48fffd: mov dword ptr [ebp], eax */
	m->edi = M32((DWORD)(m->esi + 0x13c9b2cu));	/* 490000: mov edi, dword ptr [esi + 0x13c9b2c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 490006: inc edi */
	M32((DWORD)(m->esi + 0x13c9b2cu)) = m->edi;	/* 490007: mov dword ptr [esi + 0x13c9b2c], edi */
	M32((DWORD)(m->ebp + 0x4u)) = 0x1u;	/* 49000d: mov dword ptr [ebp + 4], 1 */
	M32((DWORD)(m->ebp + 0x8u)) = m->edx;	/* 490014: mov dword ptr [ebp + 8], edx */
	m->edx = M32((DWORD)(m->ecx + 0x40u));	/* 490017: mov edx, dword ptr [ecx + 0x40] */
	M32((DWORD)(m->ebp + 0xcu)) = m->edx;	/* 49001a: mov dword ptr [ebp + 0xc], edx */
	m->eax = M32((DWORD)(m->ecx + 0x44u));	/* 49001d: mov eax, dword ptr [ecx + 0x44] */
	M32((DWORD)(m->ebp + 0x10u)) = m->eax;	/* 490020: mov dword ptr [ebp + 0x10], eax */
	m->edx = M32((DWORD)(m->ecx + 0x48u));	/* 490023: mov edx, dword ptr [ecx + 0x48] */
	m->eax = (DWORD)(m->ecx + 0x4cu);	/* 490026: lea eax, [ecx + 0x4c] */
	M32((DWORD)(m->ebp + 0x14u)) = m->edx;	/* 490029: mov dword ptr [ebp + 0x14], edx */
	{ DWORD a_ = M8((DWORD)(m->eax + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 49002c: cmp byte ptr [eax], bl */
	if (m->zf) goto L_490056;	/* 49002e: je 0x490056 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490030: push eax */
	m->eax = (DWORD)(m->esi + 0x908u);	/* 490031: lea eax, [esi + 0x908] */
	m->ecx = (DWORD)(m->esi + 0x8u);	/* 490037: lea ecx, [esi + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49003a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49003b: push ecx */
	m->edx = (DWORD)(m->ebp + 0x18u);	/* 49003c: lea edx, [ebp + 0x18] */
	{ DWORD v_ = 0x4c7a30u; m->esp -= 4; M32(m->esp) = v_; }	/* 49003f: push 0x4c7a30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 490044: push edx */
	m->esp -= 4; M32(m->esp) = 0x49004au; native_call(m, 0x49e9ddu);	/* 490045: call 0x49e9dd */
	m->ecx = M32((DWORD)(m->esp + 0xb8u));	/* 49004a: mov ecx, dword ptr [esp + 0xb8] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490051: add esp, 0x14 */
	goto L_490059;	/* 490054: jmp 0x490059 */
L_490056:
	M8((DWORD)(m->ebp + 0x18u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 490056: mov byte ptr [ebp + 0x18], bl */
L_490059:
	m->eax = (DWORD)(m->ebp + 0x58u);	/* 490059: lea eax, [ebp + 0x58] */
	{ DWORD a_ = m->ecx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49005c: add ecx, 0x8c */
	m->edx = m->eax;	/* 490062: mov edx, eax */
	M32((DWORD)(m->esp + 0x1cu)) = 0x3f800000u;	/* 490064: mov dword ptr [esp + 0x1c], 0x3f800000 */
	m->edi = M32((DWORD)(m->ecx + 0x0u));	/* 49006c: mov edi, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 49006e: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->edx + 0x0u)) = m->edi;	/* 490076: mov dword ptr [edx], edi */
	M32((DWORD)(m->esp + 0x3cu)) = 0x0u;	/* 490078: mov dword ptr [esp + 0x3c], 0 */
	m->edi = M32((DWORD)(m->ecx + 0x4u));	/* 490080: mov edi, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 490083: mov dword ptr [esp + 0x20], 0 */
	M32((DWORD)(m->edx + 0x4u)) = m->edi;	/* 49008b: mov dword ptr [edx + 4], edi */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f800000u;	/* 49008e: mov dword ptr [esp + 0x30], 0x3f800000 */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 490096: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 490099: mov dword ptr [esp + 0x40], 0 */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 4900a1: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->esp + 0xa4u));	/* 4900a4: mov edx, dword ptr [esp + 0xa4] */
	{ DWORD a_ = m->edx, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4900ab: add edx, 0x98 */
	m->ecx = (DWORD)(m->ebp + 0x64u);	/* 4900b1: lea ecx, [ebp + 0x64] */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 4900b4: mov dword ptr [esp + 0x24], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 4900bc: mov dword ptr [esp + 0x34], 0 */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 4900c4: mov edi, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f800000u;	/* 4900c6: mov dword ptr [esp + 0x44], 0x3f800000 */
	M32((DWORD)(m->ecx + 0x0u)) = m->edi;	/* 4900ce: mov dword ptr [ecx], edi */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 4900d0: mov dword ptr [esp + 0x28], 0 */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 4900d8: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x38u)) = 0x0u;	/* 4900db: mov dword ptr [esp + 0x38], 0 */
	M32((DWORD)(m->ecx + 0x4u)) = m->edi;	/* 4900e3: mov dword ptr [ecx + 4], edi */
	M32((DWORD)(m->esp + 0x48u)) = 0x0u;	/* 4900e6: mov dword ptr [esp + 0x48], 0 */
	m->edi = M32((DWORD)(m->edx + 0x8u));	/* 4900ee: mov edi, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x58u)) = 0x3f800000u;	/* 4900f1: mov dword ptr [esp + 0x58], 0x3f800000 */
	M32((DWORD)(m->ecx + 0x8u)) = m->edi;	/* 4900f9: mov dword ptr [ecx + 8], edi */
	m->edx = M32((DWORD)(m->edx + 0xcu));	/* 4900fc: mov edx, dword ptr [edx + 0xc] */
	M32((DWORD)(m->ecx + 0xcu)) = m->edx;	/* 4900ff: mov dword ptr [ecx + 0xc], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 490102: fld dword ptr [eax] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 490104: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 490108: fld dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 49010b: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49010f: fld dword ptr [eax + 8] */
	m->eax = (DWORD)(m->ebp + 0x64u);	/* 490112: lea eax, [ebp + 0x64] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490115: push eax */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 490116: lea eax, [esp + 0x60] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 49011a: fstp dword ptr [esp + 0x58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49011e: push eax */
	m->esp -= 4; M32(m->esp) = 0x490124u; native_call(m, 0x47d8a0u);	/* 49011f: call 0x47d8a0 */
	m->ecx = (DWORD)(m->esp + 0x64u);	/* 490124: lea ecx, [esp + 0x64] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 490128: lea edx, [esp + 0x24] */
	m->edi = (DWORD)(m->ebp + 0x74u);	/* 49012c: lea edi, [ebp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49012f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 490130: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490131: push edi */
	m->esp -= 4; M32(m->esp) = 0x490137u; native_call(m, 0x47d380u);	/* 490132: call 0x47d380 */
	m->eax = (DWORD)(m->ebp + 0xb4u);	/* 490137: lea eax, [ebp + 0xb4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49013d: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49013e: push eax */
	m->esp -= 4; M32(m->esp) = 0x490144u; native_call(m, 0x47d740u);	/* 49013f: call 0x47d740 */
	m->eax = (DWORD)(m->ebp + 0x74u);	/* 490144: lea eax, [ebp + 0x74] */
	m->edi = (DWORD)(m->ebp + 0xf4u);	/* 490147: lea edi, [ebp + 0xf4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49014d: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49014e: push edi */
	m->esp -= 4; M32(m->esp) = 0x490154u; native_call(m, 0x47d5a0u);	/* 49014f: call 0x47d5a0 */
	m->eax = (DWORD)(m->ebp + 0x134u);	/* 490154: lea eax, [ebp + 0x134] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49015a: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49015b: push eax */
	m->esp -= 4; M32(m->esp) = 0x490161u; native_call(m, 0x47d740u);	/* 49015c: call 0x47d740 */
	m->eax = 0x3f800000u;	/* 490161: mov eax, 0x3f800000 */
	M32((DWORD)(m->ebp + 0x184u)) = m->ebx;	/* 490166: mov dword ptr [ebp + 0x184], ebx */
	M32((DWORD)(m->ebp + 0x174u)) = m->eax;	/* 49016c: mov dword ptr [ebp + 0x174], eax */
	M32((DWORD)(m->ebp + 0x194u)) = m->ebx;	/* 490172: mov dword ptr [ebp + 0x194], ebx */
	M32((DWORD)(m->ebp + 0x1a4u)) = m->ebx;	/* 490178: mov dword ptr [ebp + 0x1a4], ebx */
	M32((DWORD)(m->ebp + 0x178u)) = m->ebx;	/* 49017e: mov dword ptr [ebp + 0x178], ebx */
	M32((DWORD)(m->ebp + 0x188u)) = m->eax;	/* 490184: mov dword ptr [ebp + 0x188], eax */
	M32((DWORD)(m->ebp + 0x198u)) = m->ebx;	/* 49018a: mov dword ptr [ebp + 0x198], ebx */
	M32((DWORD)(m->ebp + 0x1a8u)) = m->ebx;	/* 490190: mov dword ptr [ebp + 0x1a8], ebx */
	M32((DWORD)(m->ebp + 0x17cu)) = m->ebx;	/* 490196: mov dword ptr [ebp + 0x17c], ebx */
	M32((DWORD)(m->ebp + 0x18cu)) = m->ebx;	/* 49019c: mov dword ptr [ebp + 0x18c], ebx */
	M32((DWORD)(m->ebp + 0x19cu)) = m->eax;	/* 4901a2: mov dword ptr [ebp + 0x19c], eax */
	M32((DWORD)(m->ebp + 0x1acu)) = m->ebx;	/* 4901a8: mov dword ptr [ebp + 0x1ac], ebx */
	M32((DWORD)(m->ebp + 0x180u)) = m->ebx;	/* 4901ae: mov dword ptr [ebp + 0x180], ebx */
	M32((DWORD)(m->ebp + 0x190u)) = m->ebx;	/* 4901b4: mov dword ptr [ebp + 0x190], ebx */
	M32((DWORD)(m->ebp + 0x1a0u)) = m->ebx;	/* 4901ba: mov dword ptr [ebp + 0x1a0], ebx */
	M32((DWORD)(m->ebp + 0x1b0u)) = m->eax;	/* 4901c0: mov dword ptr [ebp + 0x1b0], eax */
	M32((DWORD)(m->ebp + 0x1b4u)) = m->eax;	/* 4901c6: mov dword ptr [ebp + 0x1b4], eax */
	M32((DWORD)(m->ebp + 0x1c8u)) = m->eax;	/* 4901cc: mov dword ptr [ebp + 0x1c8], eax */
	M32((DWORD)(m->ebp + 0x1dcu)) = m->eax;	/* 4901d2: mov dword ptr [ebp + 0x1dc], eax */
	M32((DWORD)(m->ebp + 0x1f0u)) = m->eax;	/* 4901d8: mov dword ptr [ebp + 0x1f0], eax */
	m->eax = (DWORD)(m->ebp + 0xb4u);	/* 4901de: lea eax, [ebp + 0xb4] */
	m->ecx = (DWORD)(m->ebp + 0x1f4u);	/* 4901e4: lea ecx, [ebp + 0x1f4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4901ea: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4901eb: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4901ec: push ecx */
	M32((DWORD)(m->ebp + 0x1c4u)) = m->ebx;	/* 4901ed: mov dword ptr [ebp + 0x1c4], ebx */
	M32((DWORD)(m->ebp + 0x1d4u)) = m->ebx;	/* 4901f3: mov dword ptr [ebp + 0x1d4], ebx */
	M32((DWORD)(m->ebp + 0x1e4u)) = m->ebx;	/* 4901f9: mov dword ptr [ebp + 0x1e4], ebx */
	M32((DWORD)(m->ebp + 0x1b8u)) = m->ebx;	/* 4901ff: mov dword ptr [ebp + 0x1b8], ebx */
	M32((DWORD)(m->ebp + 0x1d8u)) = m->ebx;	/* 490205: mov dword ptr [ebp + 0x1d8], ebx */
	M32((DWORD)(m->ebp + 0x1e8u)) = m->ebx;	/* 49020b: mov dword ptr [ebp + 0x1e8], ebx */
	M32((DWORD)(m->ebp + 0x1bcu)) = m->ebx;	/* 490211: mov dword ptr [ebp + 0x1bc], ebx */
	M32((DWORD)(m->ebp + 0x1ccu)) = m->ebx;	/* 490217: mov dword ptr [ebp + 0x1cc], ebx */
	M32((DWORD)(m->ebp + 0x1ecu)) = m->ebx;	/* 49021d: mov dword ptr [ebp + 0x1ec], ebx */
	M32((DWORD)(m->ebp + 0x1c0u)) = m->ebx;	/* 490223: mov dword ptr [ebp + 0x1c0], ebx */
	M32((DWORD)(m->ebp + 0x1d0u)) = m->ebx;	/* 490229: mov dword ptr [ebp + 0x1d0], ebx */
	M32((DWORD)(m->ebp + 0x1e0u)) = m->ebx;	/* 49022f: mov dword ptr [ebp + 0x1e0], ebx */
	m->esp -= 4; M32(m->esp) = 0x49023au; native_call(m, 0x47d380u);	/* 490235: call 0x47d380 */
	m->eax = (DWORD)(m->ebp + 0x1f4u);	/* 49023a: lea eax, [ebp + 0x1f4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490240: push eax */
	m->eax = (DWORD)(m->ebp + 0x234u);	/* 490241: lea eax, [ebp + 0x234] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490247: push eax */
	m->esp -= 4; M32(m->esp) = 0x49024du; native_call(m, 0x47d740u);	/* 490248: call 0x47d740 */
	m->ecx = M32((DWORD)(m->esp + 0xe4u));	/* 49024d: mov ecx, dword ptr [esp + 0xe4] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490254: add esp, 0x40 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 490257: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 490259: push ecx */
	m->ecx = (DWORD)(m->esi + 0xe3c93cu);	/* 49025a: lea ecx, [esi + 0xe3c93c] */
	m->esp -= 4; M32(m->esp) = 0x490265u; native_call(m, 0x466dc0u);	/* 490260: call 0x466dc0 */
	M32((DWORD)(m->ebp + 0x27cu)) = m->eax;	/* 490265: mov dword ptr [ebp + 0x27c], eax */
	m->edx = M32((DWORD)(m->eax + 0x18u));	/* 49026b: mov edx, dword ptr [eax + 0x18] */
	m->eax = M32((DWORD)(m->esi + 0x13016c8u));	/* 49026e: mov eax, dword ptr [esi + 0x13016c8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 490274: add eax, edx */
	{ DWORD a_ = m->eax, b_ = 0xf4240u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490276: cmp eax, 0xf4240 */
	if (m->zf || m->sf != m->of) goto L_49029d;	/* 49027b: jle 0x49029d */
	m->ecx = M32((DWORD)(m->esp + 0xa0u));	/* 49027d: mov ecx, dword ptr [esp + 0xa0] */
	{ DWORD v_ = 0xf4240u; m->esp -= 4; M32(m->esp) = v_; }	/* 490284: push 0xf4240 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490289: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49028a: push ecx */
	{ DWORD v_ = 0x4c8314u; m->esp -= 4; M32(m->esp) = v_; }	/* 49028b: push 0x4c8314 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 490290: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x49029au; native_call(m, 0x46c710u);	/* 490295: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49029a: add esp, 0x14 */
L_49029d:
	m->edx = M32((DWORD)(m->esi + 0x13016c8u));	/* 49029d: mov edx, dword ptr [esi + 0x13016c8] */
	m->ecx = M32((DWORD)(m->ebp + 0x27cu));	/* 4902a3: mov ecx, dword ptr [ebp + 0x27c] */
	m->eax = (DWORD)(m->esi + m->edx*4 + 0xf30dc8u);	/* 4902a9: lea eax, [esi + edx*4 + 0xf30dc8] */
	M32((DWORD)(m->ebp + 0x280u)) = m->eax;	/* 4902b0: mov dword ptr [ebp + 0x280], eax */
	m->edx = M32((DWORD)(m->ecx + 0x18u));	/* 4902b6: mov edx, dword ptr [ecx + 0x18] */
	m->eax = M32((DWORD)(m->esi + 0x13016c8u));	/* 4902b9: mov eax, dword ptr [esi + 0x13016c8] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4902bf: add eax, edx */
	M32((DWORD)(m->esi + 0x13016c8u)) = m->eax;	/* 4902c1: mov dword ptr [esi + 0x13016c8], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x27cu));	/* 4902c7: mov ecx, dword ptr [ebp + 0x27c] */
	m->edx = M32((DWORD)(m->ecx + 0x18u));	/* 4902cd: mov edx, dword ptr [ecx + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4902d0: add eax, edx */
	{ DWORD a_ = m->eax, b_ = 0xf4240u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4902d2: cmp eax, 0xf4240 */
	if (m->zf || m->sf != m->of) goto L_4902f9;	/* 4902d7: jle 0x4902f9 */
	{ DWORD v_ = 0xf4240u; m->esp -= 4; M32(m->esp) = v_; }	/* 4902d9: push 0xf4240 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4902de: push eax */
	m->eax = M32((DWORD)(m->esp + 0xa8u));	/* 4902df: mov eax, dword ptr [esp + 0xa8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4902e6: push eax */
	{ DWORD v_ = 0x4c8314u; m->esp -= 4; M32(m->esp) = v_; }	/* 4902e7: push 0x4c8314 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4902ec: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x4902f6u; native_call(m, 0x46c710u);	/* 4902f1: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4902f6: add esp, 0x14 */
L_4902f9:
	m->ecx = M32((DWORD)(m->esi + 0x13016c8u));	/* 4902f9: mov ecx, dword ptr [esi + 0x13016c8] */
	m->eax = M32((DWORD)(m->ebp + 0x27cu));	/* 4902ff: mov eax, dword ptr [ebp + 0x27c] */
	m->edx = (DWORD)(m->esi + m->ecx*4 + 0xf30dc8u);	/* 490305: lea edx, [esi + ecx*4 + 0xf30dc8] */
	M32((DWORD)(m->ebp + 0x284u)) = m->edx;	/* 49030c: mov dword ptr [ebp + 0x284], edx */
	m->ecx = M32((DWORD)(m->eax + 0x18u));	/* 490312: mov ecx, dword ptr [eax + 0x18] */
	m->edx = M32((DWORD)(m->esi + 0x13016c8u));	/* 490315: mov edx, dword ptr [esi + 0x13016c8] */
	m->eax = M32((DWORD)(m->esp + 0xa4u));	/* 49031b: mov eax, dword ptr [esp + 0xa4] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 490322: add edx, ecx */
	M32((DWORD)(m->esi + 0x13016c8u)) = m->edx;	/* 490324: mov dword ptr [esi + 0x13016c8], edx */
	M32((DWORD)(m->ebp + 0x288u)) = 0x1u;	/* 49032a: mov dword ptr [ebp + 0x288], 1 */
	m->edx = M32((DWORD)(m->eax + 0xa8u));	/* 490334: mov edx, dword ptr [eax + 0xa8] */
	M32((DWORD)(m->ebp + 0x274u)) = m->edx;	/* 49033a: mov dword ptr [ebp + 0x274], edx */
	m->eax = M32((DWORD)(m->eax + 0xacu));	/* 490340: mov eax, dword ptr [eax + 0xac] */
	M32((DWORD)(m->ebp + 0x278u)) = m->eax;	/* 490346: mov dword ptr [ebp + 0x278], eax */
	m->eax = M32((DWORD)(m->ebp + 0x27cu));	/* 49034c: mov eax, dword ptr [ebp + 0x27c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490352: cmp eax, ebx */
	M32((DWORD)(m->ebp + 0x28cu)) = m->ebx;	/* 490354: mov dword ptr [ebp + 0x28c], ebx */
	M32((DWORD)(m->ebp + 0x290u)) = m->ebx;	/* 49035a: mov dword ptr [ebp + 0x290], ebx */
	M32((DWORD)(m->ebp + 0x294u)) = m->ebx;	/* 490360: mov dword ptr [ebp + 0x294], ebx */
	M32((DWORD)(m->ebp + 0x298u)) = m->ebx;	/* 490366: mov dword ptr [ebp + 0x298], ebx */
	M32((DWORD)(m->ebp + 0x29cu)) = m->ebx;	/* 49036c: mov dword ptr [ebp + 0x29c], ebx */
	M32((DWORD)(m->ebp + 0x2a0u)) = m->ebx;	/* 490372: mov dword ptr [ebp + 0x2a0], ebx */
	M32((DWORD)(m->ebp + 0x2a4u)) = m->ebx;	/* 490378: mov dword ptr [ebp + 0x2a4], ebx */
	if (m->zf) goto L_4903de;	/* 49037e: je 0x4903de */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20u)));	/* 490380: fld dword ptr [edi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 490383: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x10u)));	/* 490386: fld dword ptr [edi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 490389: fmul dword ptr [eax + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49038c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 49038e: fld dword ptr [edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 490390: fmul dword ptr [eax + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 490393: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 490395: fadd dword ptr [edi + 0x30] */
	MF((DWORD)(m->ebp + 0x2bcu)) = (float)ST(0); FPOP();	/* 490398: fstp dword ptr [ebp + 0x2bc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x24u)));	/* 49039e: fld dword ptr [edi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 4903a1: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 4903a4: fld dword ptr [edi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 4903a7: fmul dword ptr [eax + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4903aa: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 4903ac: fld dword ptr [edi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 4903af: fmul dword ptr [eax + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4903b2: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x34u));	/* 4903b4: fadd dword ptr [edi + 0x34] */
	MF((DWORD)(m->ebp + 0x2c0u)) = (float)ST(0); FPOP();	/* 4903b7: fstp dword ptr [ebp + 0x2c0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x28u)));	/* 4903bd: fld dword ptr [edi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 4903c0: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 4903c3: fld dword ptr [edi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 4903c6: fmul dword ptr [eax + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4903c9: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x18u)));	/* 4903cb: fld dword ptr [edi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 4903ce: fmul dword ptr [eax + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4903d1: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x38u));	/* 4903d3: fadd dword ptr [edi + 0x38] */
	MF((DWORD)(m->ebp + 0x2c4u)) = (float)ST(0); FPOP();	/* 4903d6: fstp dword ptr [ebp + 0x2c4] */
	goto L_4903f9;	/* 4903dc: jmp 0x4903f9 */
L_4903de:
	m->edx = M32((DWORD)(m->ebp + 0x58u));	/* 4903de: mov edx, dword ptr [ebp + 0x58] */
	m->eax = M32((DWORD)(m->ebp + 0x5cu));	/* 4903e1: mov eax, dword ptr [ebp + 0x5c] */
	m->ecx = (DWORD)(m->ebp + 0x2bcu);	/* 4903e4: lea ecx, [ebp + 0x2bc] */
	M32((DWORD)(m->ebp + 0x2bcu)) = m->edx;	/* 4903ea: mov dword ptr [ebp + 0x2bc], edx */
	m->edx = M32((DWORD)(m->ebp + 0x60u));	/* 4903f0: mov edx, dword ptr [ebp + 0x60] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 4903f3: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 4903f6: mov dword ptr [ecx + 8], edx */
L_4903f9:
	M32((DWORD)(m->ebp + 0x2a8u)) = m->ebx;	/* 4903f9: mov dword ptr [ebp + 0x2a8], ebx */
	M32((DWORD)(m->ebp + 0x2c8u)) = m->ebx;	/* 4903ff: mov dword ptr [ebp + 0x2c8], ebx */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x13016ccu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490405: cmp dword ptr [esi + 0x13016cc], ebx */
	if (!m->zf) goto L_490433;	/* 49040b: jne 0x490433 */
	m->ecx = M32((DWORD)(m->ebp + 0x280u));	/* 49040d: mov ecx, dword ptr [ebp + 0x280] */
	m->eax = (DWORD)(m->ebp + 0x134u);	/* 490413: lea eax, [ebp + 0x134] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490419: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x27cu));	/* 49041a: mov eax, dword ptr [ebp + 0x27c] */
	{ DWORD a_ = m->esi, b_ = 0x9ccffcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 490420: add esi, 0x9ccffc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490426: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490427: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 490428: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49042a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x490430u; native_call(m, 0x466910u);	/* 49042b: call 0x466910 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490430: add esp, 0x14 */
L_490433:
	m->edi = M32(m->esp); m->esp += 4;	/* 490433: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 490434: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 490435: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 490436: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490437: add esp, 0x8c */
	m->esp += 4 + 8; return;	/* 49043d: ret 8 */
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
